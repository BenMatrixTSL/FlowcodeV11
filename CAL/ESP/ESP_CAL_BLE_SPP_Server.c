// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0C50EC9A622BC26BB8DEA673A10B7CD916527A4218AE1DAC1CC23E85E07FE4DA156557CC7FB74F055CCDF56843D14FE724474B131B536F04EA9B11F738DF98E15EC0E8272595EAED0DAC847DBF6DF32148318CD0646F93457785DA27AF0EB19477DD64BF97B2588F98D0153C943D277CFA4486BC3E2BC43F081195D8ABD8E77B6DF4DC114886C69C90D9B6942068BE8E3863DD2A7D5FC2A5E549D34A0D5AD11F3F549048CA9E7A29F0C08A61B592DEF3742DBF82CFF8D6361E907423A8D190A732508A81D4B1C62AB
// REVISION: 4.0
// GUID: D6758F12-7EA3-43C1-A3AF-1CD455707176
// DATE: 24\11\2026
// DIR: CAL\ESP\ESP_CAL_BLE_SPP_Server.c

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatt_common_api.h"
#include "esp_gatts_api.h"
#include "esp_log.h"
#include "nvs_flash.h"

/*
 * This example creates a very small BLE server that behaves similar to a
 * serial (SPP) port. Any connected client can write bytes to the ESP32 and
 * will immediately see them printed in the serial monitor. The ESP32 also
 * sends a short text back to the client every few seconds.
 */

#define BLE_TAG                "BLE_SPP"

// Custom 16-bit UUIDs that keep things simple for a beginner-friendly project.
//#define SPP_SERVICE_UUID       0xFFE0
//#define SPP_CHAR_UUID          0xFFE1

// Attribute database indexes. The order here matches the table below.
enum spp_attr_index {
    IDX_SPP_SERVICE = 0,
    IDX_SPP_CHAR,
    IDX_SPP_CHAR_VAL,
    IDX_SPP_CHAR_CFG,
    IDX_SPP_NB,
};

// Characteristic properties: readable, writable, and supports notifications.
static const uint8_t spp_char_prop = ESP_GATT_CHAR_PROP_BIT_READ |
                                     ESP_GATT_CHAR_PROP_BIT_WRITE |
                                     ESP_GATT_CHAR_PROP_BIT_NOTIFY;

// Common UUID helpers used inside the attribute table.
static const uint16_t primary_service_uuid      = ESP_GATT_UUID_PRI_SERVICE;
static const uint16_t character_declaration_uuid = ESP_GATT_UUID_CHAR_DECLARE;
static const uint16_t character_client_config_uuid = ESP_GATT_UUID_CHAR_CLIENT_CONFIG;
static const uint16_t default_ccc = 0x0000;

static uint16_t spp_service_uuid = SPP_SERVICE_UUID;
static uint16_t spp_char_uuid = SPP_CHAR_UUID;

// Maximum number of characters allowed in the advertised device name so the
// UUID also fits inside the 31-byte advertising frame.
#define BT_ADV_NAME_MAX_LEN 19

// Device name set at runtime by BT_BLE_SSP_Server_SetName. While this is
// empty the fixed BT_DEV_NAME from the Flowcode property is used instead.
static char bt_dev_name[BT_ADV_NAME_MAX_LEN + 1] = {0};

// Set when the name changes while a client is connected, so the advertising
// data is rebuilt with the new name once the client disconnects.
static bool bt_dev_name_adv_pending = false;

// Attribute table definition.
static esp_gatts_attr_db_t spp_gatt_db[IDX_SPP_NB] = {
    // Service Declaration
    [IDX_SPP_SERVICE] =
        {{ESP_GATT_AUTO_RSP},
         {ESP_UUID_LEN_16, (uint8_t *)&primary_service_uuid, ESP_GATT_PERM_READ,
          sizeof(uint16_t), sizeof(uint16_t), (uint8_t *)&spp_service_uuid}},

    // Characteristic Declaration
    [IDX_SPP_CHAR] =
        {{ESP_GATT_AUTO_RSP},
         {ESP_UUID_LEN_16, (uint8_t *)&character_declaration_uuid, ESP_GATT_PERM_READ,
          sizeof(uint8_t), sizeof(uint8_t), (uint8_t *)&spp_char_prop}},

    // Characteristic Value
    [IDX_SPP_CHAR_VAL] =
        {{ESP_GATT_AUTO_RSP},
         {ESP_UUID_LEN_16, (uint8_t *)&spp_char_uuid,
          ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
          ESP_GATT_MAX_ATTR_LEN, sizeof(uint8_t), (uint8_t *)"0"}},

    // Client Characteristic Configuration Descriptor (for notifications)
    [IDX_SPP_CHAR_CFG] =
        {{ESP_GATT_AUTO_RSP},
         {ESP_UUID_LEN_16, (uint8_t *)&character_client_config_uuid,
          ESP_GATT_PERM_READ | ESP_GATT_PERM_WRITE,
          sizeof(uint16_t), sizeof(uint16_t), (uint8_t *)&default_ccc}},
};

// Track BLE state in easy to read global values.
static uint16_t spp_handle_table[IDX_SPP_NB];
static esp_gatt_if_t server_if = ESP_GATT_IF_NONE;
static uint16_t connection_id = 0;
static bool client_connected = false;

// Simple circular buffer for incoming data.
static uint8_t spp_rx_buffer[BT_RX_BUF_SZ];
static uint16_t spp_rx_head = 0;
static uint16_t spp_rx_tail = 0;
static uint16_t spp_rx_count = 0;

// Forward declarations so the main flow remains easy to read.
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                esp_ble_gatts_cb_param_t *param);
static void start_advertising(void);
static bool send_bytes_to_client(const uint8_t *data, uint16_t length);
static void send_text_to_client(const char *text);
static void send_byte_to_client(uint8_t byte_value);
static void send_byte_array_to_client(const uint8_t *data, uint16_t length);
static void set_device_name_with_limit(void);
static void configure_raw_advertising(void);
static const char *get_device_name(void);

// RX buffer helpers.
static void spp_rx_buffer_reset(void);
static uint16_t spp_rx_data_count(void);
static bool spp_rx_push_byte(uint8_t value);
static bool spp_rx_push_block(const uint8_t *data, uint16_t length);
static bool spp_rx_pop_byte(uint8_t *out_byte);
static uint16_t spp_rx_read_block(uint8_t *out, uint16_t max_length);

// Public-style helpers that other files/tasks can call.
uint16_t spp_rx_data_available(void);
bool spp_read_byte(uint8_t *out_byte);
uint16_t spp_read_bytes(uint8_t *out, uint16_t max_length);
void BT_BLE_SSP_Server_SetName(MX_CHAR *name, MX_UINT16 name_size);

/*
 * Return the name to advertise: the runtime name if one has been set,
 * otherwise the fixed BT_DEV_NAME from the Flowcode property.
 */
static const char *get_device_name(void)
{
    if (bt_dev_name[0] != '\0') {
        return bt_dev_name;
    }
    return BT_DEV_NAME;
}

static void log_adv_payload_size(void)
{
    const char *name = get_device_name();
    size_t trimmed = strlen(name) > BT_ADV_NAME_MAX_LEN ? BT_ADV_NAME_MAX_LEN : strlen(name);

    size_t bytes = 0;
    bytes += 3;                 // Flags
    bytes += 3;                 // Tx Power
    bytes += 4;                 // 16-bit UUID AD structure
    bytes += trimmed + 2;       // Name (length + type + chars)

    ESP_LOGI(BLE_TAG, "Adv size calc: name=%.*s (%d chars) -> %d bytes",
             (int)trimmed, name, (int)trimmed, (int)bytes);
}

/*
 * Copy the device name into a trimmed buffer that fits the advertisement payload.
 */
static void set_device_name_with_limit(void)
{
    const char *source = get_device_name();
    size_t source_len = strlen(source);
    size_t copy_len = source_len > BT_ADV_NAME_MAX_LEN ? BT_ADV_NAME_MAX_LEN : source_len;
    char limited_name[BT_ADV_NAME_MAX_LEN + 1];
    memcpy(limited_name, source, copy_len);
    limited_name[copy_len] = '\0';

    if (source_len > BT_ADV_NAME_MAX_LEN) {
        #if (BT_DEBUG & 1)
          ESP_LOGW(BLE_TAG, "Device name trimmed to \"%s\" to fit advertising packet", limited_name);
        #endif
    }

    esp_ble_gap_set_device_name(limited_name);
}

/*
 * Advertising data keeps the project simple: a name and transmit power field.
 */
/*
 * We build the advertisement payload manually to ensure it always matches
 * the 31-byte limit. That avoids any hidden struct padding issues.
 */
static void configure_raw_advertising(void)
{
    char limited_name[BT_ADV_NAME_MAX_LEN + 1];
    const char *source = get_device_name();
    size_t source_len = strlen(source);
    size_t copy_len = source_len > BT_ADV_NAME_MAX_LEN ? BT_ADV_NAME_MAX_LEN : source_len;
    memcpy(limited_name, source, copy_len);
    limited_name[copy_len] = '\0';

    if (source_len > BT_ADV_NAME_MAX_LEN) {
        #if (BT_DEBUG & 1)
          ESP_LOGW(BLE_TAG, "Device name trimmed to \"%s\" to fit advertising packet", limited_name);
        #endif
    }

    uint8_t adv_payload[31] = {0};
    uint8_t idx = 0;

    // Flags
    adv_payload[idx++] = 0x02;
    adv_payload[idx++] = 0x01;
    adv_payload[idx++] = ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT;

    // 16-bit UUID (complete list)
    adv_payload[idx++] = 0x03;
    adv_payload[idx++] = 0x03;
    adv_payload[idx++] = (uint8_t)(spp_service_uuid & 0xFF);
    adv_payload[idx++] = (uint8_t)(spp_service_uuid >> 8);

    // Complete Local Name
    adv_payload[idx++] = (uint8_t)(copy_len + 1); // length byte includes type
    adv_payload[idx++] = 0x09;                    // type = Complete Local Name
    memcpy(&adv_payload[idx], limited_name, copy_len);
    idx += copy_len;

    ESP_ERROR_CHECK(esp_ble_gap_config_adv_data_raw(adv_payload, idx));

    #if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "Raw adv payload length %d bytes", idx);
    #endif
}

static esp_ble_adv_params_t adv_params = {
    .adv_int_min = 0x20,
    .adv_int_max = 0x40,
    .adv_type = ADV_TYPE_IND,
    .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
    .channel_map = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

/*
 * Core helper that pushes raw bytes to the client characteristic.
 * Returns true when the bytes were accepted by the BLE stack.
 */
static bool send_bytes_to_client(const uint8_t *data, uint16_t length)
{
    if (!client_connected || server_if == ESP_GATT_IF_NONE || data == NULL || length == 0) {
        return false;
    }

    esp_err_t err = esp_ble_gatts_send_indicate(
        server_if,
        connection_id,
        spp_handle_table[IDX_SPP_CHAR_VAL],
        length,
        (uint8_t *)data,
        false);

    if (err != ESP_OK)
    {
		#if (BT_DEBUG & 2)
          ESP_LOGE(BLE_TAG, "Failed to send notification (%s)", esp_err_to_name(err));
        #endif
        return false;
    }

    return true;
}

/*
 * Convenience wrapper for sending plain text.
 */
static void send_text_to_client(const char *text)
{
    if (text == NULL) {
        return;
    }
    send_bytes_to_client((const uint8_t *)text, (uint16_t)strlen(text));
}

/*
 * Send a single byte to the client.
 */
static void send_byte_to_client(uint8_t byte_value)
{
    send_bytes_to_client(&byte_value, 1);
}

/*
 * Send an arbitrary byte array to the client.
 */
static void send_byte_array_to_client(const uint8_t *data, uint16_t length)
{
    send_bytes_to_client(data, length);
}

/*
 * Reset buffer pointers. Call during startup or after a disconnect.
 */
static void spp_rx_buffer_reset(void)
{
    spp_rx_head = 0;
    spp_rx_tail = 0;
    spp_rx_count = 0;
}

/*
 * Return how many bytes currently sit inside the circular buffer.
 */
static uint16_t spp_rx_data_count(void)
{
    return spp_rx_count;
}

/*
 * Push a single byte into the buffer. Returns false if the buffer is full.
 */
static bool spp_rx_push_byte(uint8_t value)
{
    if (spp_rx_count >= BT_RX_BUF_SZ) {
        return false;
    }

    spp_rx_buffer[spp_rx_head] = value;
    spp_rx_head = (spp_rx_head + 1) % BT_RX_BUF_SZ;
    spp_rx_count++;
    return true;
}

/*
 * Push a sequence of bytes into the buffer. Returns false if anything overflowed.
 */
static bool spp_rx_push_block(const uint8_t *data, uint16_t length)
{
    if (data == NULL || length == 0) {
        return false;
    }

    bool success = true;
    for (uint16_t i = 0; i < length; i++) {
        if (!spp_rx_push_byte(data[i])) {
            success = false;
            break;
        }
    }
    return success;
}

/*
 * Pop one byte from the buffer. Returns false if no data is available.
 */
static bool spp_rx_pop_byte(uint8_t *out_byte)
{
    if (spp_rx_count == 0 || out_byte == NULL) {
        return false;
    }

    *out_byte = spp_rx_buffer[spp_rx_tail];
    spp_rx_tail = (spp_rx_tail + 1) % BT_RX_BUF_SZ;
    spp_rx_count--;
    return true;
}

/*
 * Read up to max_length bytes into the caller buffer.
 */
static uint16_t spp_rx_read_block(uint8_t *out, uint16_t max_length)
{
    if (out == NULL || max_length == 0) {
        return 0;
    }

    uint16_t read = 0;
    while (read < max_length && spp_rx_count > 0) {
        spp_rx_pop_byte(&out[read]);
        read++;
    }
    return read;
}

/*
 * Public helper: return buffered byte count.
 */
uint16_t spp_rx_data_available(void)
{
    return spp_rx_data_count();
}

/*
 * Public helper: try to read a single byte.
 */
bool spp_read_byte(uint8_t *out_byte)
{
    return spp_rx_pop_byte(out_byte);
}

/*
 * Public helper: read multiple bytes.
 */
uint16_t spp_read_bytes(uint8_t *out, uint16_t max_length)
{
    return spp_rx_read_block(out, max_length);
}

/*
 * Handle GAP events such as advertising state and connection updates.
 */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Advertising data configured");
        #endif
        // Don't advertise while connected - a name change made during a
        // connection is advertised once the client disconnects.
        if (!client_connected) {
            start_advertising();
        }
        break;
    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS)
        {
			#if (BT_DEBUG & 2)
              ESP_LOGE(BLE_TAG, "Failed to start advertising");
            #endif
        }
        else
        {
			#if (BT_DEBUG & 1)
              ESP_LOGI(BLE_TAG, "Advertising started");
            #endif
        }
        break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:
     	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Advertising stopped");
        #endif
        break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Connection parameters updated: interval=%d latency=%d",
                 param->update_conn_params.conn_int,
                 param->update_conn_params.latency);
        #endif
        break;
    default:
        break;
    }
}

/*
 * Start BLE advertising using the configuration above.
 */
static void start_advertising(void)
{
    esp_err_t err = esp_ble_gap_start_advertising(&adv_params);
    if (err != ESP_OK)
    {
		#if (BT_DEBUG & 2)
          ESP_LOGE(BLE_TAG, "Failed to start advertising (%s)", esp_err_to_name(err));
        #endif
    }
}

/*
 * Handle all GATT server events. The logic is intentionally linear and
 * heavily commented to stay beginner friendly.
 */
static void gatts_event_handler(esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
                                esp_ble_gatts_cb_param_t *param)
{
    switch (event) {
    case ESP_GATTS_REG_EVT:
		log_adv_payload_size();
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "GATT server registered, starting service setup");
        #endif
        server_if = gatts_if;
        set_device_name_with_limit();
    configure_raw_advertising();
        esp_ble_gatts_create_attr_tab(spp_gatt_db, gatts_if, IDX_SPP_NB, 0);
        break;

    case ESP_GATTS_CREAT_ATTR_TAB_EVT:
        if (param->add_attr_tab.status != ESP_GATT_OK)
        {
			#if (BT_DEBUG & 2)
              ESP_LOGE(BLE_TAG, "Failed to create attribute table");
            #endif
        }
        else
        {
            memcpy(spp_handle_table, param->add_attr_tab.handles, sizeof(spp_handle_table));
            esp_ble_gatts_start_service(spp_handle_table[IDX_SPP_SERVICE]);
        }
        break;

    case ESP_GATTS_START_EVT:
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Service started, waiting for connections");
        #endif
        start_advertising();
        break;

    case ESP_GATTS_CONNECT_EVT:
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Client connected");
        #endif
        client_connected = true;
        connection_id = param->connect.conn_id;
        esp_ble_gap_stop_advertising();
        break;

    case ESP_GATTS_DISCONNECT_EVT:
    	#if (BT_DEBUG & 1)
          ESP_LOGI(BLE_TAG, "Client disconnected");
        #endif
        client_connected = false;
        connection_id = 0;
        spp_rx_buffer_reset();
        if (bt_dev_name_adv_pending) {
            // Name changed while connected: rebuild the advertising data,
            // advertising restarts from ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT.
            bt_dev_name_adv_pending = false;
            configure_raw_advertising();
        } else {
            start_advertising();
        }
        break;

    case ESP_GATTS_WRITE_EVT:
        if (!param->write.is_prep) {
            char incoming[ESP_GATT_MAX_ATTR_LEN] = {0};
            size_t copy_len = param->write.len < sizeof(incoming) - 1 ? param->write.len : sizeof(incoming) - 1;
            memcpy(incoming, param->write.value, copy_len);
            #if (BT_DEBUG & 1)
              ESP_LOGI(BLE_TAG, "Received from client: %s", incoming);
            #endif

            if (!spp_rx_push_block(param->write.value, param->write.len))
            {
				#if (BT_DEBUG & 2)
                  ESP_LOGW(BLE_TAG, "RX buffer full, dropping %d bytes", param->write.len);
                #endif
            }

            if (param->write.need_rsp) {
                esp_ble_gatts_send_response(gatts_if, param->write.conn_id,
                                            param->write.trans_id, ESP_GATT_OK, NULL);
            }

			//Interrupt call macro defined by Flowcode
            #if BT_RX_INT_EN == 1
            	BT_RX_INT_MACRO();
            #endif
        }
        break;

    default:
        break;
    }
}

/*
 * Initialize the Bluetooth controller, the Bluedroid stack, and the BLE services.
 */
static void BT_BLE_SSP_Server_Init(void)
{
    spp_rx_buffer_reset();
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));
    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_ERROR_CHECK(esp_ble_gatts_register_callback(gatts_event_handler));
    #if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "GATTS cb registered");
    #endif
    ESP_ERROR_CHECK(esp_ble_gap_register_callback(gap_event_handler));
    #if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "GAP cb registered");
    #endif
    ESP_ERROR_CHECK(esp_ble_gatts_app_register(0));
    #if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "GATTS app register requested");
	#endif
}

/*
 * Change the Bluetooth device name at runtime.
 *
 * name      - new name, max 19 characters (longer names are trimmed to fit
 *             the advertising packet). Pass an empty string to go back to
 *             the fixed name from the Flowcode Device Name property.
 * name_size - size of the name buffer, so names that fill the whole
 *             Flowcode string with no null terminator are handled.
 *
 * Can be called before or after BT_BLE_SSP_Server_Init:
 *  - Before init (or before the stack is ready) the name is stored and used
 *    when advertising starts.
 *  - While advertising, the name is changed straight away.
 *  - While a client is connected, the GAP device name is updated straight
 *    away and the new name is advertised once the client disconnects.
 * The name is kept across BT_BLE_SSP_Server_Deinit / Init.
 */
void BT_BLE_SSP_Server_SetName(MX_CHAR *name, MX_UINT16 name_size)
{
    MX_UINT16 len = 0;

    if (name != NULL) {
        while (len < name_size && len < BT_ADV_NAME_MAX_LEN && name[len] != '\0') {
            len++;
        }
        memcpy(bt_dev_name, name, len);
    }
    bt_dev_name[len] = '\0';

    #if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "Device name set to \"%s\"", get_device_name());
    #endif

    // Stack not up yet - the name is picked up at ESP_GATTS_REG_EVT.
    if (server_if == ESP_GATT_IF_NONE) {
        return;
    }

    set_device_name_with_limit();

    if (client_connected) {
        bt_dev_name_adv_pending = true;
    } else {
        // Rebuild the advertising data, advertising restarts from
        // ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT with the new name.
        esp_ble_gap_stop_advertising();
        configure_raw_advertising();
    }
}

/*
 * Completely shut down and uninitialize Bluetooth functionality.
 * This stops advertising, disconnects clients, and powers down the BLE stack.
 * Call this when you want to save power or completely disable BLE.
 */
void BT_BLE_SSP_Server_Deinit(void)
{
	#if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "Shutting down BLE...");
	#endif

    // Stop advertising if it's active
    if (server_if != ESP_GATT_IF_NONE) {
        esp_ble_gap_stop_advertising();
        vTaskDelay(pdMS_TO_TICKS(100)); // Wait for stop to complete
    }

    // Disconnect any connected client
    if (client_connected && server_if != ESP_GATT_IF_NONE && connection_id != 0) {
        esp_ble_gatts_close(server_if, connection_id);
        vTaskDelay(pdMS_TO_TICKS(200)); // Wait for disconnect
    }

    // Disable Bluedroid stack
    esp_bluedroid_disable();
    esp_bluedroid_deinit();

    // Disable and deinitialize Bluetooth controller
    esp_bt_controller_disable();
    esp_bt_controller_deinit();

    // Reset all state variables
    server_if = ESP_GATT_IF_NONE;
    connection_id = 0;
    client_connected = false;
    bt_dev_name_adv_pending = false;
    spp_rx_buffer_reset();

	#if (BT_DEBUG & 1)
      ESP_LOGI(BLE_TAG, "BLE shutdown complete");
    #endif
}


