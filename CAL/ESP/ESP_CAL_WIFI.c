// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A02127FFA3A175B658B46610338B7A9609BB86C748A3A0C466297584E05767F1CDBB8DD6FED976D007711B8143522C2B6962391F2761141C462567AAEE3EA04363BF90AA2ACE3F0B74261E8E64A93889BDDCD64123987BF007FF1689ACFEE55035474CD789DFAC85195CB5D1301131FFD377C2FA0EE6DC6BD4492B9B6A399E05396897A1C64EC68459549D34A0D5AD11F3F336A5E22B45C5BC0A7F9F0D53D53981D1C43A7009C35B67FA0264F21FD71235929CCCA4409E3163
// REVISION: 7.0
// GUID: EAFAF360-E023-4328-9643-77F667477976
// DATE: 11\10\2023
// DIR: CAL\ESP\ESP_CAL_WIFI.c
/*********************************************************************
 *                  Flowcode CAL WIFI File
 *
 * File: ESP_CAL_WIFI.c
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
 * 150620 | LM | Created
 * 110423 | BR | Added support for IDF v5.0
 */

#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_eth.h"
#include "esp_log.h"
#include "nvs_flash.h"

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0
	#include "esp_wifi.h"
#else
	#include "tcpip_adapter.h"
#endif

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"


static const char *TAG = "wifi";

#ifdef WIFI_SCANSIZE
  #define WIFI_SCAN_LIST_MAX WIFI_SCANSIZE
#else
  #define WIFI_SCAN_LIST_MAX 8
#endif

static MX_UINT16 wifi_scan_max = WIFI_SCAN_LIST_MAX;
static MX_UINT16 wifi_scan_count = 0;
static bool wifi_scan_done = false;
static bool wifi_have_ip = false;
static wifi_ap_record_t wifi_scan_info[WIFI_SCAN_LIST_MAX];
static esp_err_t MX_ESP_WIFI_ERROR = 0;
static ip4_addr_t wifi_ip_addr;
static int s_retry_num = 0;

//Verbose Debug Output
#if WIFI_DEBUG & 1
  #define WIFI_LOGI2 ESP_LOGI
  #define WIFI_LOGI3 ESP_LOGI
  #define WIFI_LOGI4 ESP_LOGI
  #define WIFI_LOGI5 ESP_LOGI
#else
  #define WIFI_LOGI2(A,B)
  #define WIFI_LOGI3(A,B,C)
  #define WIFI_LOGI4(A,B,C,D)
  #define WIFI_LOGI5(A,B,C,D,E)
#endif



#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

	/* The event group allows multiple bits for each event, but we only care about two events:
	 * - we are connected to the AP with an IP
	 * - we failed to connect after the maximum amount of retries */
	#define WIFI_CONNECTED_BIT BIT0
	#define WIFI_FAIL_BIT      BIT1

	#define EXAMPLE_ESP_MAXIMUM_RETRY 2

	/* FreeRTOS event group to signal when we are connected*/
	static EventGroupHandle_t s_wifi_event_group;

	static void event_handler(void* arg, esp_event_base_t event_base,
									int32_t event_id, void* event_data)
	{
		if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
			esp_wifi_connect();
		} else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
			if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
				esp_wifi_connect();
				s_retry_num++;
				ESP_LOGI(TAG, "retry to connect to the AP");
			} else {
				xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
			}
			ESP_LOGI(TAG,"connect to the AP fail");
		} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
			ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
			ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
			s_retry_num = 0;
			xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
		}
	}

#endif




static void wifi_connect_got_ip(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	wifi_have_ip = true;
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
	memcpy(&wifi_ip_addr, &event->ip_info.ip, sizeof(wifi_ip_addr));
	WIFI_LOGI3(TAG, "STA got IP: %s", ip4addr_ntoa(&wifi_ip_addr));
}

static void wifi_sta_disconnected(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	if (s_retry_num)
	{
		--s_retry_num;
		WIFI_LOGI2(TAG, "Wi-Fi disconnected, trying to reconnect ...");
		ESP_ERROR_CHECK(esp_wifi_connect());
	}
}

static void wifi_wifi_scan_done(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	wifi_scan_done = true;
}



static void* wifi_scan_ssid(MX_UINT16 index)
{
	if (index < wifi_scan_count)
		return wifi_scan_info[index].ssid;
	else
		return 0;
}



static MX_UINT8 wifi_create_softap(MX_STRING ssid, MX_STRING password, MX_UINT8 mode)
{
	esp_netif_create_default_wifi_ap();

	wifi_config_t wifi_config;
	strncpy((char*)wifi_config.ap.ssid, ssid, sizeof(wifi_config.ap.ssid));
	strncpy((char*)wifi_config.ap.password, password, sizeof(wifi_config.ap.password));
    wifi_config.ap.ssid_len = strlen(ssid);
    wifi_config.ap.max_connection = 1;
    wifi_config.ap.authmode = mode;
	wifi_config.ap.channel = 0;
	wifi_config.ap.ssid_hidden = 0;
	wifi_config.ap.beacon_interval = 100;

    if (strlen(password) == 0)
	{
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

	WIFI_LOGI4(TAG, "wifi_create_softap(SSID:%s password:%s)", ssid, password);

    if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_mode(WIFI_MODE_AP))))
	{
		//if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config))))
		if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_config(WIFI_IF_AP, &wifi_config))))
		{
			if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_start())))
			{
				return 1;
			}
		}
	}
    return 0;
}



static MX_SINT8 wifi_scan_rssi(MX_UINT16 index)
{
	if (index < wifi_scan_count)
		return wifi_scan_info[index].rssi;
	else
		return 0;
}



static MX_UINT8 wifi_scan_authmode(MX_UINT16 index)
{
	if (index < wifi_scan_count)
	{
		switch (wifi_scan_info[index].authmode)
		{
			case WIFI_AUTH_OPEN:
				return 0;
			case WIFI_AUTH_WEP:
				return 1;
			case WIFI_AUTH_WPA_PSK:
				return 2;
			case WIFI_AUTH_WPA2_PSK:
				return 3;
			case WIFI_AUTH_WPA_WPA2_PSK:
				return 4;
			case WIFI_AUTH_WPA2_ENTERPRISE:
				return 5;
			case WIFI_AUTH_WPA3_PSK:
				return 6;
			case WIFI_AUTH_WPA2_WPA3_PSK:
				return 7;
			default:
				return 0xff;
		}
	}
	else
		return 0xff;
}


static MX_UINT8 wifi_connect_to_ssid(MX_STRING ssid, MX_STRING password, MX_UINT8 timeout)
{
		wifi_config_t wifi_config = {};
		wifi_have_ip = false;
		strncpy((char*)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
		strncpy((char*)wifi_config.sta.password, password, sizeof(wifi_config.sta.password));

		// default timeout to 20 seconds
		if (timeout == 0) timeout = 20;

		ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_connect_got_ip, NULL));

		WIFI_LOGI3(TAG, "Connecting to %s...", wifi_config.sta.ssid);

		if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_mode(WIFI_MODE_STA))))
		{
			if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config))))
			{
				if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_start())))
				{

					#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

						s_wifi_event_group = xEventGroupCreate();
						MX_UINT16 tout = (timeout * 1000) / portTICK_PERIOD_MS;

						/* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
						 * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
						EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
								WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
								pdFALSE,
								pdFALSE,
								tout);

						/* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
						 * happened. */
						if (bits & WIFI_CONNECTED_BIT)
						{
							WIFI_LOGI4(TAG, "connected to ap SSID:%s password:%s", ssid, password);
							return 1;
						} else if (bits & WIFI_FAIL_BIT)
						{
							WIFI_LOGI4(TAG, "Failed to connect to SSID:%s, password:%s", ssid, password);
							return 0;
						} else
						{
							WIFI_LOGI2(TAG, "UNEXPECTED EVENT");
							return 0;
						}

					#else

						if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_connect())))
						{
							while ((!wifi_have_ip)&&(--timeout))
							{
								vTaskDelay(1000 / portTICK_PERIOD_MS);
							}
							if (wifi_have_ip)
								return 1;
						}

					#endif
				}
			}
		}
		return 0;

}


static MX_UINT8 wifi_disconnect()
{
	if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_disconnect())))
	{
		if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_stop())))
		{
			return 1;
		}
	}
	return 0;
}



static MX_UINT8 wifi_initialise(void)
{
	// set logging level for all ...
	// esp_log_level_set("*", ESP_LOG_INFO);
	WIFI_LOGI2(TAG, "wifi_initialise()");

	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)	// enable functionality present in IDF v5.0

		ESP_ERROR_CHECK(esp_netif_init());

		//ESP_ERROR_CHECK(esp_event_loop_create_default());
		esp_netif_create_default_wifi_sta();

		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		ESP_ERROR_CHECK(esp_wifi_init(&cfg));

		esp_event_handler_instance_t instance_any_id;
		esp_event_handler_instance_t instance_got_ip;
		ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
															ESP_EVENT_ANY_ID,
															&event_handler,
															NULL,
															&instance_any_id));
		ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
															IP_EVENT_STA_GOT_IP,
															&event_handler,
															NULL,
															&instance_got_ip));

	#else

		tcpip_adapter_init();

		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		if (ESP_OK == (MX_ESP_WIFI_ERROR = esp_wifi_init(&cfg)))
		{
			ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
			return 1;
		}

	#endif


	return 0;
}



static MX_UINT8 wifi_uninitialise(void)
{
	if (ESP_OK == (MX_ESP_WIFI_ERROR = esp_wifi_deinit()))
	{
		return 1;
	}
	return 0;
}



static MX_UINT16 wifi_scan(void)
{
	MX_UINT16 timeout = 100;	// 10 seconds timeout
	wifi_scan_max = WIFI_SCAN_LIST_MAX;
	wifi_scan_count = 0;
	wifi_scan_done = false;
	memset(wifi_scan_info, 0, sizeof(wifi_scan_info));

	WIFI_LOGI2(TAG, "wifi_scan()");

	// wifi stop ?

	ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_SCAN_DONE, &wifi_wifi_scan_done, NULL));

    if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_set_mode(WIFI_MODE_STA))))
	{
		if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_start())))
		{
			if (ESP_OK == (MX_ESP_WIFI_ERROR = (esp_wifi_scan_start(NULL, true))))
			{
				while ((!wifi_scan_done)&&(--timeout))
				{
					vTaskDelay(100 / portTICK_PERIOD_MS);
				}
			}
		}
	}

	if (wifi_scan_done)
	{
		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&wifi_scan_count));
		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&wifi_scan_max, wifi_scan_info));

		WIFI_LOGI3(TAG, "wifi_scan() done, count = %d", wifi_scan_count);

		{
			int x = 0;
			while (x< wifi_scan_count)
			{
				WIFI_LOGI5(TAG, "SSID: %s\tRSSI: %d\tAUTH: %d", wifi_scan_info[x].ssid, wifi_scan_info[x].rssi, wifi_scan_info[x].authmode);
				++x;
			}
		}

		if (wifi_scan_count > wifi_scan_max)
			wifi_scan_count = wifi_scan_max;

		return wifi_scan_count;
	}
	return 0;
}


/**
	Would be better if this takes the socket type and returns the socket handle
	Network comms component just returns 0=fail or 1=successful
	So just do that for now and keep a copy of the single socket handle
**/
static int wifi_socket_handle = 0;
static int wifi_accept_handle = 0;

static void wifi_accept_close(void)
{
	if (wifi_accept_handle) close(wifi_accept_handle);
	wifi_accept_handle = 0;
}

static void wifi_socket_close(void)
{
	wifi_accept_close();
	if (wifi_socket_handle) close(wifi_socket_handle);
	wifi_socket_handle = 0;
}

static int wifi_socket_open(void)
{
	wifi_accept_close();
	wifi_socket_close();

	// use some defaults for family and socket type
	if (0 < (wifi_socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
		{
			return 1;
		}
	wifi_socket_handle = 0;
	return 0;
}

static MX_UINT8 wifi_socket_connect(MX_STRING url, MX_UINT16 urlLen, MX_UINT16 port)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
	char s_port[8];
	sprintf(s_port, "%d", port);
    int err = getaddrinfo(url, s_port, &hints, &res);

    if(err != 0 || res == NULL)
     {
            WIFI_LOGI4(TAG, "FLOWCODE DNS lookup failed err=%d res=%p", err, res);
			if (res) freeaddrinfo(res);
            return 0;
     }
     else
     {
            WIFI_LOGI2(TAG, "FLOWCODE DNS lookup OK");

			if (connect(wifi_socket_handle, res->ai_addr, res->ai_addrlen) == 0)
			{
				WIFI_LOGI2(TAG, "... connected");
				fcntl(wifi_socket_handle, F_SETFL, O_NONBLOCK);
				if (res) freeaddrinfo(res);
				return 1;
			}
			else
			{
				WIFI_LOGI3(TAG, "... socket connect failed errno=%d", errno);
				if (res) freeaddrinfo(res);
				return 0;
			}
     }
}

static MX_UINT16 wifi_socket_read(void* buffer, MX_UINT16 bufferLen, MX_UINT16 size)
{
	int n = 0;
	if (wifi_accept_handle)
	{
		n = read(wifi_accept_handle, buffer, size);
	}
	else if (wifi_socket_handle)
	{
		n = read(wifi_socket_handle, buffer, size);
	}
	return (n < 0)?0:n;
}

static MX_UINT16 wifi_socket_write(void* buffer, MX_UINT16 bufferLen, MX_UINT16 size)
{
	int n = 0;
	if (wifi_accept_handle)
	{
		n = write(wifi_accept_handle, buffer, size);
	}
	else if (wifi_socket_handle)
	{
		n = write(wifi_socket_handle, buffer, size);
	}
	return (n < 0)?0:n;
}

static MX_UINT8 wifi_socket_listen(MX_UINT16 port)
{
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);
	if (0 == bind(wifi_socket_handle, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
	{
		if (0 == listen(wifi_socket_handle, 1))
		{
			return 1;
		}
	}
	return 0;
}

static MX_UINT8 wifi_accept_open(void)
{
	if (wifi_socket_handle)
	{
		struct sockaddr addr;
		socklen_t addrlen = sizeof(addr);
		fcntl(wifi_socket_handle, F_SETFL, O_NONBLOCK);
		wifi_accept_handle = accept(wifi_socket_handle, &addr, &addrlen);
		if (wifi_accept_handle > 0)
		{
			fcntl(wifi_accept_handle, F_SETFL, O_NONBLOCK);
			return 1;  // Success
		}
	}
	wifi_accept_handle = 0;
	return 0;
}






