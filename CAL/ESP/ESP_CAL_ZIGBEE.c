// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0C0485D618A8A0D6A2E0DBBE3A8C992AF17B470248A3E565D848C9455C852E4567AAB8FF6C48BFC20A9B11F738DF98E15D72313C19DA3B62ED24FF070E06731FC4E1867832CA089378DCA0D3E8E588ACB25CD108F2B5A95DEAE4B3B9ACF0A776F8F56B479B964EE0591B3B207566DF8DA5DD6B141144A2C894DCA2643045941B981550AF89ACAA868549D34A0D5AD11F358C1C9ED1E94A86A14ECC1358A03204DEADBA373F19FF157C7E9BF2E0A60D235BB3AB4325F399FDA
// REVISION: 1.0
// GUID: 0C5073DE-2679-4899-9D34-8C569D223BD8
// DATE: 28\04\2026
// DIR: CAL\ESP\ESP_CAL_ZIGBEE.c

/*********************************************************************
 *                  Flowcode CAL ZIGBEE File
 *
 * File: ESP_CAL_ZIGBEE.c
 *
 * (c) 2020 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * “Company”) for its Flowcode graphical programming language is
 * intended and supplied to you, the Company’s customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 280426 | BR | Created
 */

/*
 * Simple Flowcode ESP32 Zigbee helper layer.
 * Designed for ESP-IDF v5.3.1 Zigbee examples (ESP32-C6 / ESP32-H2).
 *
 * How this file is used:
 * - Flowcode macros call the functions in this file.
 * - Component properties/macros configure role, channels, and TX/RX routing.
 * - This file stores that configuration and applies it to Zigbee runtime behavior.
 *
 * Important current scope:
 * - Initialisation / commissioning is implemented.
 * - TX/RX routing model is implemented.
 * - Payload transport path is currently a simple local hook (not full OTA APS/ZCL yet).
 */

#include <stdint.h>
#include <stdbool.h>

#ifdef ESP_PLATFORM
#include "esp_err.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_zigbee_core.h"
#include "ha/esp_zigbee_ha_standard.h"
#endif

/* ---- Core Zigbee state ---- */
/* Set to 1 once commissioning/startup has completed sufficiently for traffic. */
static uint8_t fc_zb_ready = 0;
/* Set to 1 after stack/platform init is performed once. */
static uint8_t fc_zb_initialised = 0;
/* 0 = coordinator, 1 = router, 2 = end device. */
static uint8_t fc_zb_role = 0;
/* Local endpoint registered by this component instance. */
static uint8_t fc_zb_endpoint = 10;
/* Zigbee channel bitmask. Default enables channels 11-26. */
static uint32_t fc_zb_channel_mask = 0x07FFF800UL;

/* ---- Runtime routing configuration (set from Flowcode macros/properties) ---- */
/* TX mode: 0 unicast, 1 groupcast, 2 broadcast. */
static uint8_t fc_zb_tx_mode = 0;
/* TX destination short address (or group id in groupcast mode). */
static uint16_t fc_zb_tx_short_addr = 0x0000U;
/* TX destination endpoint and cluster. */
static uint8_t fc_zb_tx_endpoint = 10;
static uint16_t fc_zb_tx_cluster = 0xFC00U;
/* RX filter endpoint and cluster. */
static uint8_t fc_zb_rx_endpoint = 10;
static uint16_t fc_zb_rx_cluster = 0xFC00U;

/* ---- Simple FIFO receive buffer ----
 * Receive path pushes accepted bytes here.
 * Flowcode ReceiveByte / BytesAvailable consume/query this buffer.
 */
static uint8_t fc_zb_rx_buffer[256];
static uint16_t fc_zb_rx_head = 0;
static uint16_t fc_zb_rx_tail = 0;
static uint16_t fc_zb_rx_count = 0;

static void fc_esp32_zigbee_rx_push(uint8_t value)
{
    /* Ignore incoming bytes when buffer is full. */
    if (fc_zb_rx_count >= sizeof(fc_zb_rx_buffer)) {
        return;
    }
    fc_zb_rx_buffer[fc_zb_rx_head] = value;
    fc_zb_rx_head = (uint16_t)((fc_zb_rx_head + 1U) % sizeof(fc_zb_rx_buffer));
    fc_zb_rx_count++;
}

static uint8_t fc_esp32_zigbee_rx_accept(uint8_t endpoint, uint16_t cluster)
{
    /* Endpoint and cluster must match current RX filter settings. */
    if (endpoint != fc_zb_rx_endpoint) {
        return 0;
    }
    if (cluster != fc_zb_rx_cluster) {
        return 0;
    }
    return 1;
}

void fc_esp32_zigbee_receive_payload(const uint8_t *data, uint16_t length, uint8_t endpoint, uint16_t cluster)
{
    uint16_t index = 0;
    /* Basic null guard for safety. */
    if (data == 0) {
        return;
    }
    /* Drop payload when it does not match configured RX endpoint/cluster. */
    if (!fc_esp32_zigbee_rx_accept(endpoint, cluster)) {
        return;
    }
    /* Push all bytes to FIFO (subject to FIFO capacity). */
    while (index < length) {
        fc_esp32_zigbee_rx_push(data[index]);
        index++;
    }
}

#ifdef ESP_PLATFORM
/* Zigbee action callback: collects incoming attribute payloads and pushes bytes
 * into the component RX FIFO when endpoint/cluster filters match. */
static esp_err_t fc_esp32_zigbee_action_handler(esp_zb_core_action_callback_id_t callback_id, const void *message)
{
    if (callback_id == ESP_ZB_CORE_SET_ATTR_VALUE_CB_ID) {
        const esp_zb_zcl_set_attr_value_message_t *attr_msg = (const esp_zb_zcl_set_attr_value_message_t *)message;
        if (attr_msg == 0) {
            return ESP_OK;
        }
        if (attr_msg->info.status != ESP_ZB_ZCL_STATUS_SUCCESS) {
            return ESP_OK;
        }
        if (attr_msg->attribute.data.value == 0) {
            return ESP_OK;
        }
        if (attr_msg->attribute.data.size == 0) {
            return ESP_OK;
        }
        fc_esp32_zigbee_receive_payload((const uint8_t *)attr_msg->attribute.data.value,
                                        (uint16_t)attr_msg->attribute.data.size,
                                        attr_msg->info.dst_endpoint,
                                        attr_msg->info.cluster);
    }
    return ESP_OK;
}
#endif

void fc_esp32_zigbee_config(uint8_t role, uint8_t endpoint, uint32_t channel_mask)
{
    /* Store high-level role + local endpoint + channel selection.
     * Actual stack usage happens during init/commissioning calls. */
    fc_zb_role = role;
    fc_zb_endpoint = endpoint;
    /* Keep previous mask if caller passes 0 (acts as "no change"). */
    if (channel_mask != 0) {
        fc_zb_channel_mask = channel_mask;
    }
}

void fc_esp32_zigbee_transfer_config_tx(uint8_t tx_mode,
                                     uint16_t tx_short_addr,
                                     uint8_t tx_endpoint,
                                     uint16_t tx_cluster)
{
    /* Runtime routing can be changed at any time by Flowcode macros. */
    fc_zb_tx_mode = tx_mode;
    fc_zb_tx_short_addr = tx_short_addr;
    fc_zb_tx_endpoint = tx_endpoint;
    fc_zb_tx_cluster = tx_cluster;
}

void fc_esp32_zigbee_transfer_config_rx(uint8_t rx_endpoint,
                                     uint16_t rx_cluster)
{
    /* Runtime routing can be changed at any time by Flowcode macros. */
    fc_zb_rx_endpoint = rx_endpoint;
    fc_zb_rx_cluster = rx_cluster;
}

void fc_esp32_zigbee_init(void)
{
#ifdef ESP_PLATFORM
    /* Protect against double init calls. */
    if (fc_zb_initialised) {
        return;
    }

    esp_zb_platform_config_t config = {
        .radio_config = ESP_ZB_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_ZB_DEFAULT_HOST_CONFIG(),
    };

    /* Initialise platform + Zigbee host/radio configuration. */
    esp_zb_platform_config(&config);

    /* Select stack role config based on runtime role setting. */
    if (fc_zb_role == 0) {
        esp_zb_cfg_t zb_cfg = ESP_ZB_ZC_CONFIG();
        esp_zb_init(&zb_cfg);
    } else if (fc_zb_role == 1) {
        esp_zb_cfg_t zb_cfg = ESP_ZB_ZR_CONFIG();
        esp_zb_init(&zb_cfg);
    } else {
        esp_zb_cfg_t zb_cfg = ESP_ZB_ZED_CONFIG();
        esp_zb_init(&zb_cfg);
    }

    /* Register one endpoint profile so the stack has an app endpoint. */
    esp_zb_on_off_switch_cfg_t switch_cfg = ESP_ZB_DEFAULT_ON_OFF_SWITCH_CONFIG();
    esp_zb_ep_list_t *ep_list = esp_zb_on_off_switch_ep_create(fc_zb_endpoint, &switch_cfg);
    esp_zb_device_register(ep_list);
    /* Register callback so incoming attribute updates can be routed into RX FIFO. */
    esp_zb_core_action_handler_register(fc_esp32_zigbee_action_handler);
    /* Apply enabled channel mask from component settings. */
    esp_zb_set_primary_network_channel_set(fc_zb_channel_mask);

    /* Start stack scheduler/tasking. */
    esp_zb_start(false);
    fc_zb_initialised = 1;
#endif
}

void fc_esp32_zigbee_start_commissioning(void)
{
#ifdef ESP_PLATFORM
    /* Commissioning requires stack init first. */
    if (!fc_zb_initialised) {
        return;
    }

    /* Coordinator forms network; others try to join via steering. */
    if (fc_zb_role == 0) {
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_FORMATION);
    } else {
        esp_zb_bdb_start_top_level_commissioning(ESP_ZB_BDB_MODE_NETWORK_STEERING);
    }
    fc_zb_ready = 1;
#endif
}

void fc_esp32_zigbee_permit_join(uint8_t seconds)
{
#ifdef ESP_PLATFORM
    /* No action if stack not ready for network commands yet. */
    if (!fc_zb_initialised) {
        return;
    }
    /* Open/close join window (seconds=0 closes it). */
    esp_zb_bdb_open_network(seconds);
#else
    (void)seconds;
#endif
}

uint8_t fc_esp32_zigbee_is_ready(void)
{
    /* Flowcode can poll this before attempting data transfer. */
    return fc_zb_ready;
}

uint8_t fc_esp32_zigbee_is_joined(void)
{
#ifdef ESP_PLATFORM
    if (!fc_zb_initialised || !fc_zb_ready) {
        return 0;
    }
    /* Simple joined check: PAN id set to a valid value. */
    return (esp_zb_get_pan_id() != 0xFFFFU) ? 1 : 0;
#else
    return fc_zb_ready;
#endif
}

uint16_t fc_esp32_zigbee_get_short_address(void)
{
#ifdef ESP_PLATFORM
    return esp_zb_get_short_address();
#else
    return fc_zb_tx_short_addr;
#endif
}

uint16_t fc_esp32_zigbee_get_pan_id(void)
{
#ifdef ESP_PLATFORM
    return esp_zb_get_pan_id();
#else
    return 0x1234U;
#endif
}

uint8_t fc_esp32_zigbee_get_channel(void)
{
#ifdef ESP_PLATFORM
    return esp_zb_get_current_channel();
#else
    return 11;
#endif
}

void fc_esp32_zigbee_task_poll(void)
{
#ifdef ESP_PLATFORM
    /* Regularly run one Zigbee stack iteration. */
    if (fc_zb_initialised) {
        esp_zb_main_loop_iteration();
    }
#endif
}

uint8_t fc_esp32_zigbee_send_byte(uint8_t value)
{
#ifdef ESP_PLATFORM
    uint16_t local_short_addr = 0xFFFFU;
    uint8_t route_matches = 0;
    /* Do not send before init/commissioning stages are done. */
    if (!fc_zb_initialised || !fc_zb_ready) {
        return 0;
    }
    local_short_addr = esp_zb_get_short_address();

    /* Concrete addressing behavior:
     * - unicast: only accepted when target short address matches this node
     * - broadcast: accepted by all nodes (including this one)
     * - groupcast: hook present but group membership check is not implemented here */
    if (fc_zb_tx_mode == 0) {
        route_matches = (fc_zb_tx_short_addr == local_short_addr) ? 1 : 0;
    } else if (fc_zb_tx_mode == 2) {
        route_matches = 1;
    } else {
        route_matches = 0;
    }

    /* If route doesn't match this node in current local hook model, ignore. */
    if (!route_matches) {
        return 1;
    }

    /* Current local payload hook:
     * push to local receive path using configured TX endpoint/cluster.
     * Replace with real OTA Zigbee frame transmission as needed. */
    fc_esp32_zigbee_receive_payload(&value, 1, fc_zb_tx_endpoint, fc_zb_tx_cluster);
    return 1;
#else
    /* In non-ESP builds, keep behavior deterministic for simulation/testing. */
    fc_esp32_zigbee_receive_payload(&value, 1, fc_zb_tx_endpoint, fc_zb_tx_cluster);
    return 1;
#endif
}

uint16_t fc_esp32_zigbee_send_array(const uint8_t *data, uint16_t length)
{
    uint16_t sent = 0;
    /* Null pointer guard. */
    if (data == 0) {
        return 0;
    }
    /* Send byte-by-byte using the single-byte TX function. */
    while (sent < length) {
        if (!fc_esp32_zigbee_send_byte(data[sent])) {
            break;
        }
        sent++;
    }
    return sent;
}

uint16_t fc_esp32_zigbee_bytes_available(void)
{
    /* Number of bytes currently queued in RX FIFO. */
    return fc_zb_rx_count;
}

uint16_t fc_esp32_zigbee_receive_byte(void)
{
    uint8_t value = 0;
    /* 256 is used as "no data available" sentinel for Flowcode callers. */
    if (fc_zb_rx_count == 0) {
        return 256;
    }
    /* Pop one byte from FIFO. */
    value = fc_zb_rx_buffer[fc_zb_rx_tail];
    fc_zb_rx_tail = (uint16_t)((fc_zb_rx_tail + 1U) % sizeof(fc_zb_rx_buffer));
    fc_zb_rx_count--;
    return value;
}

uint16_t fc_esp32_zigbee_receive_array(uint8_t *buffer, uint16_t max_len)
{
    uint16_t count = 0;
    if (buffer == 0) {
        return 0;
    }
    while ((count < max_len) && (fc_zb_rx_count > 0)) {
        buffer[count] = (uint8_t)fc_esp32_zigbee_receive_byte();
        count++;
    }
    return count;
}

uint16_t fc_esp32_zigbee_receive_string(uint8_t *buffer, uint16_t max_len)
{
    uint16_t count = 0;
    if (buffer == 0) {
        return 0;
    }
    if (max_len == 0) {
        return 0;
    }
    /* Reserve one byte for the null terminator. */
    count = fc_esp32_zigbee_receive_array(buffer, (uint16_t)(max_len - 1U));
    buffer[count] = 0;
    return count;
}

