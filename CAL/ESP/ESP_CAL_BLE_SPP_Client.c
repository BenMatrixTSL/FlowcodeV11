// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0C50EC9A622BC26BB8DEA673A10B7CD91531D767EB64352C214B5BF684AB1C5B20AFB77E66B93F23DC0924CC487F83FC5C76D869352E0CB4A0C3CAEE8E7DA6987CB833C3EAE84E60B4A64B3D081913165FD5D754D5F70F347275DE57E70798BB2AAD1C518B458F5137543FC48772F16B3169CF25DAC7C9E1055B27122371657FF611FAC43674E4C7FCBD347366748061D55CB0F632B70ACDD549D34A0D5AD11F3227DB02443E4743A1146A611509FCDA3E2C3A304F4862A265D2E1919BC6D834D57C406BC4A49D3F1
// REVISION: 2.0
// GUID: 836111F2-D0B7-4BCE-961F-EC7C62B9F657
// DATE: 27\11\2025
// DIR: CAL\ESP\ESP_CAL_BLE_SPP_Client.c

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_bt.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"
#include "esp_gatt_common_api.h"
#include "esp_gattc_api.h"
#include "esp_log.h"
#include "nvs_flash.h"

/*
 * This example creates a BLE client that connects to a BLE SPP server.
 * It scans for devices, connects to one advertising the SPP service,
 * discovers the characteristic, enables notifications, and provides
 * simple functions to send/receive data through a circular buffer.
 */

#define BLE_TAG                "BLE_SPP_CLIENT"

// Custom 16-bit UUIDs matching the server project.
//#define SPP_SERVICE_UUID       0xFFE0
//#define SPP_CHAR_UUID          0xFFE1

// Feature toggles for discovery behavior
//#define FILTER_BY_UUID         1   // Set to 1 to require advertised UUID match
//#define AUTO_CONNECT_ON_MATCH  1   // Set to 1 to auto-connect on first match

#ifndef BT_DEBUG
#define BT_DEBUG               0x03
#endif

#if (BT_DEBUG & 1)
#define BLE_LOGI(fmt, ...) BLE_LOGI( fmt, ##__VA_ARGS__)
#define BLE_LOGW(fmt, ...) BLE_LOGW( fmt, ##__VA_ARGS__)
#define BLE_LOGD(fmt, ...) BLE_LOGD( fmt, ##__VA_ARGS__)
#else
#define BLE_LOGI(fmt, ...) ((void)0)
#define BLE_LOGW(fmt, ...) ((void)0)
#define BLE_LOGD(fmt, ...) ((void)0)
#endif

#if (BT_DEBUG & 2)
#define BLE_LOGE(fmt, ...) BLE_LOGE( fmt, ##__VA_ARGS__)
#else
#define BLE_LOGE(fmt, ...) ((void)0)
#endif

// Maximum number of discovered devices to store
//#define MAX_DISCOVERED_DEVICES  10

// Structure to store discovered device information
typedef struct {
    esp_bd_addr_t address;
    bool valid;
    char name[32];
    bool has_name;
} discovered_device_t;

// Array to store discovered devices
static discovered_device_t discovered_devices[MAX_DISCOVERED_DEVICES];
static uint8_t discovered_count = 0;

// Connection state tracking.
static esp_gatt_if_t gattc_if_handle = ESP_GATT_IF_NONE;
static uint16_t connection_id = 0;
static bool server_connected = false;
static esp_bd_addr_t remote_addr = {0};

// Service and characteristic handles discovered from the server.
static uint16_t spp_service_start_handle = 0;
static uint16_t spp_service_end_handle = 0;
static uint16_t spp_char_handle = 0;
static uint16_t spp_char_ccc_handle = 0;

// Circular buffer for received data.
static uint8_t spp_rx_buffer[BT_RX_BUF_SZ];
static uint16_t spp_rx_head = 0;
static uint16_t spp_rx_tail = 0;
static uint16_t spp_rx_count = 0;

// Forward declarations.
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param);
void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                         esp_ble_gattc_cb_param_t *param);
static void start_scanning(void);
static void enable_notifications(void);
void connect_to_server(const uint8_t *addr);

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
            BLE_LOGW( "RX buffer overflow, dropping data");
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
 * Public helper: check if client is connected to server.
 * Returns true if connected, false otherwise.
 */
bool client_connected(void)
{
    return server_connected;
}

/*
 * Clear the list of discovered devices.
 */
void clear_discovered_devices(void)
{
    discovered_count = 0;
    for (int i = 0; i < MAX_DISCOVERED_DEVICES; i++) {
        discovered_devices[i].valid = false;
        memset(discovered_devices[i].address, 0, sizeof(esp_bd_addr_t));
    }
}

/*
 * Add a discovered device address to the list.
 * Returns true if added successfully, false if list is full.
 */
static bool add_discovered_device(const uint8_t *address, const char *name)
{
    // Check if device already exists in the list
    for (int i = 0; i < discovered_count; i++) {
        if (memcmp(discovered_devices[i].address, address, sizeof(esp_bd_addr_t)) == 0) {
            // Update friendly name if newly provided
            if (name != NULL) {
                strlcpy(discovered_devices[i].name, name, sizeof(discovered_devices[i].name));
                discovered_devices[i].has_name = true;
            }
            return true;
        }
    }

    // Add new device if there's space
    if (discovered_count < MAX_DISCOVERED_DEVICES) {
        memcpy(discovered_devices[discovered_count].address, address, sizeof(esp_bd_addr_t));
        discovered_devices[discovered_count].valid = true;
        if (name != NULL) {
            strlcpy(discovered_devices[discovered_count].name, name, sizeof(discovered_devices[discovered_count].name));
            discovered_devices[discovered_count].has_name = true;
        } else {
            discovered_devices[discovered_count].name[0] = '\0';
            discovered_devices[discovered_count].has_name = false;
        }
        discovered_count++;
        return true;
    }

    return false; // List is full
}

/*
 * Get the number of discovered devices.
 */
uint8_t get_discovered_device_count(void)
{
    return discovered_count;
}

/*
 * Get a discovered device address by index (0 to count-1).
 * Returns true if index is valid, false otherwise.
 * address must point to a 6-byte array to store the address.
 */
bool get_discovered_device(uint8_t index, uint8_t *address)
{
    if (index >= discovered_count || address == NULL) {
        return false;
    }

    memcpy(address, discovered_devices[index].address, sizeof(esp_bd_addr_t));
    return true;
}

/*
 * Look up the friendly name for a discovered device by index.
 * Returns true if the index is valid and a name was recorded.
 */
bool get_discovered_device_name(uint8_t index, char *out_name, size_t max_len)
{
    if (out_name == NULL || max_len == 0 || index >= discovered_count) {
        return false;
    }

    if (!discovered_devices[index].has_name) {
        return false;
    }

    strlcpy(out_name, discovered_devices[index].name, max_len);
    return true;
}

/*
 * Stop scanning (if active) and connect to the discovered device at the given index.
 */
bool connect_to_discovered_device(uint8_t index)
{
    if (index >= discovered_count) {
        BLE_LOGE( "Invalid device index %u", index);
        return false;
    }

    esp_err_t err = esp_ble_gap_stop_scanning();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        BLE_LOGE( "Failed to stop scanning (%s)", esp_err_to_name(err));
        return false;
    }

    // Give the stack a short moment to settle after stopping the scan
    vTaskDelay(pdMS_TO_TICKS(100));

    BLE_LOGI( "Manually connecting to device index %u (%02x:%02x:%02x:%02x:%02x:%02x)",
             index,
             discovered_devices[index].address[0], discovered_devices[index].address[1],
             discovered_devices[index].address[2], discovered_devices[index].address[3],
             discovered_devices[index].address[4], discovered_devices[index].address[5]);

    connect_to_server(discovered_devices[index].address);
    return true;
}

/*
 * Core helper that writes raw bytes to the server characteristic.
 * Returns true when the bytes were accepted by the BLE stack.
 */
static bool send_bytes_to_server(const uint8_t *data, uint16_t length)
{
    if (!server_connected || gattc_if_handle == ESP_GATT_IF_NONE || data == NULL || length == 0) {
        return false;
    }

    if (spp_char_handle == 0) {
        BLE_LOGE( "Characteristic handle not discovered yet");
        return false;
    }

    esp_err_t err = esp_ble_gattc_write_char(
        gattc_if_handle,
        connection_id,
        spp_char_handle,
        length,
        (uint8_t *)data,
        ESP_GATT_WRITE_TYPE_NO_RSP,
        ESP_GATT_AUTH_REQ_NONE);

    if (err != ESP_OK) {
        BLE_LOGE( "Failed to write characteristic (%s)", esp_err_to_name(err));
        return false;
    }

    return true;
}

/*
 * Convenience wrapper for sending plain text.
 */
void send_text_to_server(const char *text)
{
    if (text == NULL) {
        return;
    }
    send_bytes_to_server((const uint8_t *)text, (uint16_t)strlen(text));
}

/*
 * Send a single byte to the server.
 */
void send_byte_to_server(uint8_t byte_value)
{
    send_bytes_to_server(&byte_value, 1);
}

/*
 * Send an arbitrary byte array to the server.
 */
void send_byte_array_to_server(const uint8_t *data, uint16_t length)
{
    send_bytes_to_server(data, length);
}

/*
 * Start scanning for BLE devices advertising the SPP service.
 */
static void start_scanning(void)
{
    BLE_LOGI( "Starting scan for SPP servers (UUID: 0xFFE0)...");

    esp_ble_scan_params_t scan_params = {
        .scan_type = BLE_SCAN_TYPE_ACTIVE,
        .own_addr_type = BLE_ADDR_TYPE_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval = 0x50,
        .scan_window = 0x30,
    };

    // Set scan parameters first
    esp_err_t err = esp_ble_gap_set_scan_params(&scan_params);
    if (err != ESP_OK) {
        BLE_LOGE( "Failed to set scan parameters (%s)", esp_err_to_name(err));
        return;
    }

    // Start scanning (duration 0 = continuous until stopped)
    // Note: BLE scanning discovers all devices, but we filter by UUID in software
    err = esp_ble_gap_start_scanning(0);
    if (err != ESP_OK) {
        BLE_LOGE( "Failed to start scanning (%s)", esp_err_to_name(err));
    }
}

/*
 * Connect to a discovered server.
 * addr must be a pointer to a 6-byte array containing the MAC address.
 * This function can be called with either a uint8_t array or esp_bd_addr_t.
 */
void connect_to_server(const uint8_t *addr)
{
    if (addr == NULL) {
        BLE_LOGE( "Invalid address pointer");
        return;
    }

    BLE_LOGI( "Connecting to server: %02x:%02x:%02x:%02x:%02x:%02x",
             addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

    // Copy address to remote_addr
    memcpy(remote_addr, addr, 6);

    // esp_ble_gattc_open expects esp_bd_addr_t (which is uint8_t[6])
    // Create a temporary esp_bd_addr_t and copy the address
    esp_bd_addr_t bda;
    memcpy(bda, addr, 6);
    esp_err_t err = esp_ble_gattc_open(gattc_if_handle, bda, BLE_ADDR_TYPE_PUBLIC, true);
    if (err != ESP_OK) {
        BLE_LOGE( "Failed to open connection (%s)", esp_err_to_name(err));
    }
}

/*
 * Disconnect from the currently connected server, if any.
 */
void disconnect_from_server(void)
{
    if (!server_connected || gattc_if_handle == ESP_GATT_IF_NONE || connection_id == 0) {
        BLE_LOGW( "No active connection to disconnect");
        return;
    }

    BLE_LOGI( "Disconnecting from server (conn_id=%d)", connection_id);
    esp_err_t err = esp_ble_gattc_close(gattc_if_handle, connection_id);
    if (err != ESP_OK) {
        BLE_LOGE( "Failed to close connection (%s)", esp_err_to_name(err));
    }
}

/*
 * Enable notifications on the SPP characteristic.
 */
static void enable_notifications(void)
{
    if (spp_char_ccc_handle == 0) {
        BLE_LOGE( "CCC handle not available");
        return;
    }

    uint16_t notify_enable = 0x0001; // Enable notifications
    esp_err_t err = esp_ble_gattc_write_char_descr(
        gattc_if_handle,
        connection_id,
        spp_char_ccc_handle,
        sizeof(uint16_t),
        (uint8_t *)&notify_enable,
        ESP_GATT_WRITE_TYPE_RSP,
        ESP_GATT_AUTH_REQ_NONE);

    if (err != ESP_OK) {
        BLE_LOGE( "Failed to enable notifications (%s)", esp_err_to_name(err));
    } else {
        BLE_LOGI( "Notifications enabled");
    }
}

/*
 * Handle GAP events: scan results and connection state.
 */
static void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
    case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
        BLE_LOGI( "Scan parameters set");
        break;

    case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:
        if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            BLE_LOGE( "Scan start failed");
        } else {
            BLE_LOGI( "Scan started");
        }
        break;

    case ESP_GAP_BLE_SCAN_RESULT_EVT:
        if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
            // Log all discovered devices for debugging
            BLE_LOGI( "Device discovered: %02x:%02x:%02x:%02x:%02x:%02x (RSSI: %d)",
                     param->scan_rst.bda[0], param->scan_rst.bda[1], param->scan_rst.bda[2],
                     param->scan_rst.bda[3], param->scan_rst.bda[4], param->scan_rst.bda[5],
                     param->scan_rst.rssi);

            // Prepare storage for friendly name
            char device_name[32] = {0};
            bool device_name_set = false;

            // Check if this device advertises our service UUID
            uint8_t *adv_data = param->scan_rst.ble_adv;
            uint8_t adv_len = param->scan_rst.adv_data_len;
            bool found_service = false;

            // Log raw advertisement data for debugging
            BLE_LOGI( "  Advertisement data length: %d", adv_len);
            char adv_hex[128] = {0};
            int hex_pos = 0;
            for (int i = 0; i < adv_len && hex_pos < 120; i++) {
                hex_pos += sprintf(adv_hex + hex_pos, "%02x ", adv_data[i]);
            }
            BLE_LOGI( "  Raw data: %s", adv_hex);

            // Parse BLE advertisement data to find service UUIDs
            // Advertisement data format: [Length][Type][Data...]
            uint8_t pos = 0;
            bool has_any_uuid = false;
            while (pos < adv_len - 1) {
                uint8_t field_len = adv_data[pos];
                if (field_len == 0 || pos + field_len >= adv_len) {
                    break;
                }

                uint8_t field_type = adv_data[pos + 1];

                // Check for Complete List of 16-bit Service Class UUIDs (0x03)
                // or Incomplete List of 16-bit Service Class UUIDs (0x02)
                if (field_type == 0x02 || field_type == 0x03) {
                    // Data starts at pos + 2, length is field_len - 1
                    uint8_t uuid_count = (field_len - 1) / 2;
                    BLE_LOGI( "  Found %d-bit Service UUID list (type: 0x%02x), %d UUIDs:",
                             16, field_type, uuid_count);
                    for (uint8_t i = 0; i < uuid_count; i++) {
                        uint16_t uuid = adv_data[pos + 2 + i * 2] | (adv_data[pos + 2 + i * 2 + 1] << 8);
                        BLE_LOGI( "    UUID[%d]: 0x%04X", i, uuid);
                        has_any_uuid = true;
                        if (uuid == SPP_SERVICE_UUID) {
                            found_service = true;
                            BLE_LOGI( "    *** MATCH! Found SPP service UUID 0xFFE0 ***");
                        }
                    }
                }

                // Check for 128-bit Service UUIDs (0x06 or 0x07)
                if (field_type == 0x06 || field_type == 0x07) {
                    uint8_t uuid_count = (field_len - 1) / 16;
                    BLE_LOGI( "  Found 128-bit Service UUID list (type: 0x%02x), %d UUIDs:",
                             field_type, uuid_count);
                    for (uint8_t i = 0; i < uuid_count; i++) {
                        BLE_LOGI( "    UUID[%d]: (128-bit, not checking)", i);
                        has_any_uuid = true;
                    }
                }

                // Also check Service Data (0x16) - format: [UUID16][Data...]
                if (field_type == 0x16 && field_len >= 3) {
                    uint16_t uuid = adv_data[pos + 2] | (adv_data[pos + 3] << 8);
                    BLE_LOGI( "  Found Service Data with UUID: 0x%04X", uuid);
                    has_any_uuid = true;
                    if (uuid == SPP_SERVICE_UUID) {
                        found_service = true;
                        BLE_LOGI( "    *** MATCH! Found SPP service UUID 0xFFE0 ***");
                    }
                }

                // Check Service Data - 16-bit UUID (0x12) - format: [UUID16][Data...]
                if (field_type == 0x12 && field_len >= 3) {
                    uint16_t uuid = adv_data[pos + 2] | (adv_data[pos + 3] << 8);
                    BLE_LOGI( "  Found Service Data (16-bit UUID) with UUID: 0x%04X", uuid);
                    has_any_uuid = true;
                    if (uuid == SPP_SERVICE_UUID) {
                        found_service = true;
                        BLE_LOGI( "    *** MATCH! Found SPP service UUID 0xFFE0 ***");
                    }
                }

                // Check Complete Local Name (0x09) for logging purposes
                if (field_type == 0x09) {
                    char name[32] = {0};
                    uint8_t name_len = field_len - 1;
                    if (name_len > 31) name_len = 31;
                    memcpy(name, &adv_data[pos + 2], name_len);
                    BLE_LOGI( "  Device name: %s", name);
                    strlcpy(device_name, name, sizeof(device_name));
                    device_name_set = true;
                }

                // Log other field types for debugging
                if (field_type != 0x02 && field_type != 0x03 && field_type != 0x06 &&
                    field_type != 0x07 && field_type != 0x16) {
                    BLE_LOGI( "  Field type: 0x%02x, length: %d", field_type, field_len);
                }

                if (found_service) {
                    break;
                }

                pos += field_len + 1;
            }

            if (!has_any_uuid) {
                BLE_LOGI( "  No service UUIDs found in advertisement data");
            }

            // Fallback: simple byte search (in case advertisement format is non-standard)
            if (!found_service) {
                for (int i = 0; i < adv_len - 1; i++) {
                    if (adv_data[i] == 0xE0 && adv_data[i + 1] == 0xFF) {
                        found_service = true;
                        BLE_LOGI( "  Found UUID 0xFFE0 in raw byte search");
                        break;
                    }
                }
            }

            // Decide if this device should be considered a match
            bool device_matches = true;
#if FILTER_BY_UUID
            device_matches = found_service;
#endif

            // Only process devices that match our filter criteria
            if (device_matches) {
                BLE_LOGI( "  -> SPP service found! (UUID: 0xFFE0)");

                // Add this device to the discovered list (only SPP devices)
                add_discovered_device(param->scan_rst.bda, device_name_set ? device_name : NULL);

#if AUTO_CONNECT_ON_MATCH
                BLE_LOGI( "Connecting to SPP server: %02x:%02x:%02x:%02x:%02x:%02x",
                         param->scan_rst.bda[0], param->scan_rst.bda[1], param->scan_rst.bda[2],
                         param->scan_rst.bda[3], param->scan_rst.bda[4], param->scan_rst.bda[5]);
                esp_ble_gap_stop_scanning();
                // Small delay to ensure scan is fully stopped before connecting
                vTaskDelay(pdMS_TO_TICKS(100));
                connect_to_server(param->scan_rst.bda);
#else
                BLE_LOGI( "  -> Device recorded, waiting for manual connection");
#endif
            } else {
                BLE_LOGI( "  -> No SPP service (UUID: 0xFFE0)");
            }
        } else if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_CMPL_EVT) {
            BLE_LOGI( "Scan complete. Found %d devices", discovered_count);
            // Restart scan after a delay
            vTaskDelay(pdMS_TO_TICKS(2000));
            start_scanning();
        }
        break;

    case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
        BLE_LOGI( "Scan stopped");
        break;

    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:
        BLE_LOGI( "Connection parameters updated: interval=%d latency=%d",
                 param->update_conn_params.conn_int,
                 param->update_conn_params.latency);
        break;

    default:
        break;
    }
}

/*
 * Handle GATT client events: connection, service discovery, notifications.
 */
void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if,
                         esp_ble_gattc_cb_param_t *param)
{
    switch (event) {
    case ESP_GATTC_REG_EVT:
        BLE_LOGI( "GATT client registered");
        if (param->reg.status == ESP_GATT_OK) {
            gattc_if_handle = gattc_if;
        }
        start_scanning();
        break;

    case ESP_GATTC_CONNECT_EVT:
        BLE_LOGI( "Connected to server, conn_id=%d", param->connect.conn_id);
        server_connected = true;
        connection_id = param->connect.conn_id;
        spp_rx_buffer_reset();
        // Start service discovery
        esp_ble_gattc_search_service(gattc_if_handle, param->connect.conn_id, NULL);
        break;

    case ESP_GATTC_DISCONNECT_EVT:
        BLE_LOGI( "Disconnected from server, reason=%d", param->disconnect.reason);
        server_connected = false;
        connection_id = 0;
        spp_service_start_handle = 0;
        spp_service_end_handle = 0;
        spp_char_handle = 0;
        spp_char_ccc_handle = 0;
        spp_rx_buffer_reset();
        // Restart scanning after a delay
        vTaskDelay(pdMS_TO_TICKS(2000));
        start_scanning();
        break;

    case ESP_GATTC_SEARCH_RES_EVT:
        {
            esp_gatt_srvc_id_t *srvc_id = &param->search_res.srvc_id;
            if (srvc_id->id.uuid.len == ESP_UUID_LEN_16 &&
                srvc_id->id.uuid.uuid.uuid16 == SPP_SERVICE_UUID) {
                BLE_LOGI( "Found SPP service");
                // Store service handles for characteristic discovery
                spp_service_start_handle = param->search_res.start_handle;
                spp_service_end_handle = param->search_res.end_handle;
                BLE_LOGI( "Service handles: start=%d, end=%d",
                         spp_service_start_handle, spp_service_end_handle);

                // Discover all characteristics in this service
                // Allocate buffer for characteristics
                #define MAX_CHARS 10
                esp_gattc_char_elem_t char_result[MAX_CHARS];
                uint16_t char_count = MAX_CHARS;

                esp_err_t err = esp_ble_gattc_get_all_char(
                    gattc_if_handle,
                    param->search_res.conn_id,
                    spp_service_start_handle,
                    spp_service_end_handle,
                    char_result,
                    &char_count,
                    0  // offset
                );

                if (err != ESP_OK) {
                    BLE_LOGE( "Failed to get characteristics: %s", esp_err_to_name(err));
                } else {
                    BLE_LOGI( "Found %d characteristics", char_count);
                    // Process characteristics
                    for (int i = 0; i < char_count; i++) {
                        if (char_result[i].uuid.len == ESP_UUID_LEN_16 &&
                            char_result[i].uuid.uuid.uuid16 == SPP_CHAR_UUID) {
                            spp_char_handle = char_result[i].char_handle;
                            BLE_LOGI( "Found SPP characteristic, handle=%d", spp_char_handle);

                            // Register for notifications from this characteristic
                            esp_err_t reg_err = esp_ble_gattc_register_for_notify(
                                gattc_if_handle,
                                remote_addr,
                                spp_char_handle);
                            if (reg_err != ESP_OK) {
                                BLE_LOGE( "Failed to register for notifications (%s)", esp_err_to_name(reg_err));
                            } else {
                                BLE_LOGI( "Registered for notifications");
                            }

                            // Get descriptors (including CCC)
                            // Allocate buffer for descriptors
                            #define MAX_DESCR 10
                            esp_gattc_descr_elem_t descr_result[MAX_DESCR];
                            uint16_t descr_count = MAX_DESCR;

                            esp_err_t descr_err = esp_ble_gattc_get_all_descr(
                                gattc_if_handle,
                                connection_id,
                                spp_char_handle,
                                descr_result,
                                &descr_count,
                                0  // offset
                            );

                            if (descr_err != ESP_OK) {
                                BLE_LOGE( "Failed to get descriptors: %s", esp_err_to_name(descr_err));
                            } else {
                                // Process descriptors
                                for (int j = 0; j < descr_count; j++) {
                                    if (descr_result[j].uuid.len == ESP_UUID_LEN_16 &&
                                        descr_result[j].uuid.uuid.uuid16 == ESP_GATT_UUID_CHAR_CLIENT_CONFIG) {
                                        spp_char_ccc_handle = descr_result[j].handle;
                                        BLE_LOGI( "Found CCC descriptor, handle=%d", spp_char_ccc_handle);
                                        enable_notifications();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        break;

    case ESP_GATTC_SEARCH_CMPL_EVT:
        BLE_LOGI( "Service discovery complete");
        break;

    case ESP_GATTC_NOTIFY_EVT:

        // Data received from server via notification
        if (param->notify.handle == spp_char_handle) {
            spp_rx_push_block(param->notify.value, param->notify.value_len);
        }

        //Flowcode RX Interrupt Callback
        #if (BT_RX_INT_EN == 1)
          BT_RX_INT_MACRO();
        #endif
        break;

    case ESP_GATTC_WRITE_CHAR_EVT:
        if (param->write.status != ESP_GATT_OK) {
            BLE_LOGE( "Write char failed, status=%d", param->write.status);
        }
        break;

    case ESP_GATTC_WRITE_DESCR_EVT:
        if (param->write.status != ESP_GATT_OK) {
            BLE_LOGE( "Write descr failed, status=%d", param->write.status);
        }
        break;

    default:
        break;
    }
}

/*
 * Initialize NVS, the Bluetooth controller, the Bluedroid stack, and the BLE client.
 */
void BT_BLE_SSP_Client_Init(void)
{
    BLE_LOGI( "Initializing BLE client");

    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));
    ESP_ERROR_CHECK(esp_bluedroid_init());
    ESP_ERROR_CHECK(esp_bluedroid_enable());

    ESP_ERROR_CHECK(esp_ble_gattc_register_callback(gattc_event_handler));
    ESP_ERROR_CHECK(esp_ble_gap_register_callback(gap_event_handler));
    ESP_ERROR_CHECK(esp_ble_gattc_app_register(0));

    spp_rx_buffer_reset();
    clear_discovered_devices();
    BLE_LOGI( "BLE client initialized, waiting for registration...");
}

/*
 * Completely shut down and uninitialize Bluetooth functionality.
 * This stops scanning, disconnects from the server, and powers down the BLE stack.
 * Call this when you want to save power or completely disable BLE.
 */
void BT_BLE_SSP_Client_Deinit(void)
{
    BLE_LOGI( "Shutting down BLE...");

    // Stop scanning if active
    if (gattc_if_handle != ESP_GATT_IF_NONE) {
        esp_ble_gap_stop_scanning();
        vTaskDelay(pdMS_TO_TICKS(100)); // Wait for stop to complete
    }

    // Disconnect from server if connected
    if (server_connected && gattc_if_handle != ESP_GATT_IF_NONE && connection_id != 0) {
        esp_ble_gattc_close(gattc_if_handle, connection_id);
        vTaskDelay(pdMS_TO_TICKS(200)); // Wait for disconnect
    }

    // Disable Bluedroid stack
    esp_bluedroid_disable();
    esp_bluedroid_deinit();

    // Disable and deinitialize Bluetooth controller
    esp_bt_controller_disable();
    esp_bt_controller_deinit();

    // Reset all state variables
    gattc_if_handle = ESP_GATT_IF_NONE;
    connection_id = 0;
    server_connected = false;
    spp_char_handle = 0;
    spp_char_ccc_handle = 0;
    memset(remote_addr, 0, sizeof(remote_addr));
    spp_rx_buffer_reset();

    BLE_LOGI( "BLE shutdown complete");
}



