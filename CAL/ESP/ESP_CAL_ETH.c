// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0DA063776A99DA143E62838C53A185F20B82E41E3F05B9517B47821D22B91C490D5EC1178E7B1FA23A9B11F738DF98E1581DB1BF554AC24FAB9FBD1546EB607C6D329EDCBE71492F59DB9C006CC74DBBD489B97A3F15100CDEDB1B51A28E49FB0649CD0BB346F223DE774A26C8188CE6F3B5D6E39C3967D3C138F42C62B4DB888E3387A1848259A8D549D34A0D5AD11F3F7795C0290F840C8C9DB29ABB6FDE46BBD75FF64C9B95BACD2EF1051E39F543AFA58BCB22F86270C
// REVISION: 1.0
// GUID: A083C8A7-739A-494B-AC3D-6697C417515B
// DATE: 23\10\2026
// DIR: CAL\ESP\ESP_CAL_ETH.c
/*********************************************************************
 *                  Flowcode CAL Ethernet File
 *
 * File: ESP_CAL_ETH.c
 *
 * (c) 2026 Matrix TSL.
 * http://www.matrixtsl.com
 *
 * Software License Agreement
 *
 * The software supplied herewith by Matrix TSL (the
 * "Company") for its Flowcode graphical programming language is
 * intended and supplied to you, the Company's customer, for use
 * solely and exclusively on the Company's products. The software
 * is owned by the Company, and is protected under applicable
 * copyright laws. All rights are reserved. Any use in violation
 * of the foregoing restrictions may subject the user to criminal
 * sanctions under applicable laws, as well as to civil liability
 * for the breach of the terms and conditions of this licence.
 *
 * THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Description:
 *
 *  Wired Ethernet driver for ESP32 devices with the internal EMAC and an
 *  external RMII PHY, for example the Olimex ESP32-POE / ESP32-POE-ISO
 *  (LAN8710A PHY, power on GPIO12, MDC GPIO23, MDIO GPIO18, 50MHz RMII
 *  clock output on GPIO17) or the Olimex ESP32-GATEWAY.
 *
 *  The socket function set deliberately mirrors ESP_CAL_WIFI.c so that
 *  the Ethernet (ESP32) component exposes the same socket macro interface
 *  as the WLAN (ESP32) component. Higher level components (Network Comms,
 *  Web Server, MQTT etc.) can therefore sit on top of either without
 *  change. The wireless-only WiFi calls are not provided; eth_initialise()
 *  both sets up the hardware and brings the link up, eth_deinitialise()
 *  tears it all down again.
 *
 *  Both this file and ESP_CAL_WIFI.c may be included in the same
 *  project - every symbol here carries an eth_ / ETH_ prefix.
 *
 * Configuration defines (emitted by the component properties):
 *
 *  ETH_DEBUG       0/1   Verbose logging via ESP_LOGI
 *  ETH_PHY_TYPE    0..4  0=LAN87xx 1=IP101 2=RTL8201 3=DP83848 4=KSZ80xx
 *  ETH_PHY_ADDR    -1..31  PHY SMI address, -1 = auto detect
 *  ETH_PHY_POWER   GPIO used to power the PHY, -1 = not used
 *  ETH_PHY_RESET   GPIO used to reset the PHY, -1 = not used
 *  ETH_MDC         SMI MDC GPIO
 *  ETH_MDIO        SMI MDIO GPIO
 *  ETH_CLK_MODE    0=50MHz input on GPIO0, 1=output GPIO0,
 *                  2=output GPIO16, 3=inverted output GPIO17
 *  ETH_CONNECT_TIMEOUT  seconds eth_initialise waits for link / IP (default 20)
 *  ETH_DHCP        0/1   1 = obtain address from DHCP
 *  ETH_IP0..3, ETH_SN0..3, ETH_GW0..3, ETH_DNS0..3  static settings
 *
 * Changelog:
 *
 *  date  | by | description
 * -------+----+-----------------------------------------------------
 * 231026 | BR | Created, based on ESP_CAL_WIFI.c
 */

#include <string.h>
#include <stdio.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "esp_log.h"
#include "esp_idf_version.h"

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

#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(4, 1, 0)
	#error "ESP_CAL_ETH.c requires ESP-IDF v4.1 or later (esp_netif API)"
#endif

static const char *ETH_TAG = "eth";


/*********************************************************************
 * Configuration defaults - Olimex ESP32-POE
 *********************************************************************/
#ifndef ETH_DEBUG
  #define ETH_DEBUG 0
#endif
#ifndef ETH_PHY_TYPE
  #define ETH_PHY_TYPE 0
#endif
#ifndef ETH_PHY_ADDR
  #define ETH_PHY_ADDR 0
#endif
#ifndef ETH_PHY_POWER
  #define ETH_PHY_POWER 12
#endif
#ifndef ETH_PHY_RESET
  #define ETH_PHY_RESET (-1)
#endif
#ifndef ETH_MDC
  #define ETH_MDC 23
#endif
#ifndef ETH_MDIO
  #define ETH_MDIO 18
#endif
#ifndef ETH_CLK_MODE
  #define ETH_CLK_MODE 3
#endif
#ifndef ETH_CONNECT_TIMEOUT
  #define ETH_CONNECT_TIMEOUT 20
#endif
#ifndef ETH_DHCP
  #define ETH_DHCP 1
#endif
#ifndef ETH_IP0
  #define ETH_IP0 192
  #define ETH_IP1 168
  #define ETH_IP2 1
  #define ETH_IP3 222
#endif
#ifndef ETH_SN0
  #define ETH_SN0 255
  #define ETH_SN1 255
  #define ETH_SN2 255
  #define ETH_SN3 0
#endif
#ifndef ETH_GW0
  #define ETH_GW0 192
  #define ETH_GW1 168
  #define ETH_GW2 1
  #define ETH_GW3 1
#endif
#ifndef ETH_DNS0
  #define ETH_DNS0 8
  #define ETH_DNS1 8
  #define ETH_DNS2 8
  #define ETH_DNS3 8
#endif


//Verbose Debug Output
#if ETH_DEBUG & 1
  #define ETH_LOGI2 ESP_LOGI
  #define ETH_LOGI3 ESP_LOGI
  #define ETH_LOGI4 ESP_LOGI
  #define ETH_LOGI5 ESP_LOGI
#else
  #define ETH_LOGI2(A,B)
  #define ETH_LOGI3(A,B,C)
  #define ETH_LOGI4(A,B,C,D)
  #define ETH_LOGI5(A,B,C,D,E)
#endif


/*********************************************************************
 * State
 *********************************************************************/
#define ETH_CONNECTED_BIT BIT0
#define ETH_LINK_UP_BIT   BIT1

static esp_err_t MX_ESP_ETH_ERROR = ESP_OK;
static esp_eth_handle_t eth_handle = NULL;
static esp_netif_t *eth_netif = NULL;
static esp_eth_netif_glue_handle_t eth_glue = NULL;
static EventGroupHandle_t eth_event_group = NULL;
static bool eth_initialised = false;
static bool eth_started = false;
static bool eth_link_up = false;
static bool eth_have_ip = false;
static esp_ip4_addr_t eth_ip_addr;
static uint8_t eth_mac_addr[6] = {0, 0, 0, 0, 0, 0};


/*********************************************************************
 * Event handlers
 *********************************************************************/
static void eth_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	switch (event_id)
	{
		case ETHERNET_EVENT_CONNECTED:
			eth_link_up = true;
			if (eth_handle) esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, eth_mac_addr);
			ETH_LOGI2(ETH_TAG, "Ethernet link up");
			if (eth_event_group) xEventGroupSetBits(eth_event_group, ETH_LINK_UP_BIT);
			#if !ETH_DHCP
				// Static address - no DHCP event will arrive so treat link up as connected
				eth_have_ip = true;
				if (eth_event_group) xEventGroupSetBits(eth_event_group, ETH_CONNECTED_BIT);
			#endif
			break;

		case ETHERNET_EVENT_DISCONNECTED:
			eth_link_up = false;
			eth_have_ip = false;
			ETH_LOGI2(ETH_TAG, "Ethernet link down");
			if (eth_event_group) xEventGroupClearBits(eth_event_group, ETH_LINK_UP_BIT | ETH_CONNECTED_BIT);
			break;

		case ETHERNET_EVENT_START:
			ETH_LOGI2(ETH_TAG, "Ethernet started");
			break;

		case ETHERNET_EVENT_STOP:
			eth_link_up = false;
			eth_have_ip = false;
			ETH_LOGI2(ETH_TAG, "Ethernet stopped");
			if (eth_event_group) xEventGroupClearBits(eth_event_group, ETH_LINK_UP_BIT | ETH_CONNECTED_BIT);
			break;

		default:
			break;
	}
}

static void eth_got_ip_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
	ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
	memcpy(&eth_ip_addr, &event->ip_info.ip, sizeof(eth_ip_addr));
	eth_have_ip = true;
	ETH_LOGI3(ETH_TAG, "Ethernet got IP: " IPSTR, IP2STR(&event->ip_info.ip));
	if (eth_event_group) xEventGroupSetBits(eth_event_group, ETH_CONNECTED_BIT);
}


/*********************************************************************
 * Static IP configuration
 *********************************************************************/
static void eth_apply_static_ip(void)
{
	#if !ETH_DHCP
		esp_netif_ip_info_t ip_info;
		esp_netif_dns_info_t dns_info;

		esp_netif_dhcpc_stop(eth_netif);

		memset(&ip_info, 0, sizeof(ip_info));
		IP4_ADDR(&ip_info.ip, ETH_IP0, ETH_IP1, ETH_IP2, ETH_IP3);
		IP4_ADDR(&ip_info.netmask, ETH_SN0, ETH_SN1, ETH_SN2, ETH_SN3);
		IP4_ADDR(&ip_info.gw, ETH_GW0, ETH_GW1, ETH_GW2, ETH_GW3);
		MX_ESP_ETH_ERROR = esp_netif_set_ip_info(eth_netif, &ip_info);
		memcpy(&eth_ip_addr, &ip_info.ip, sizeof(eth_ip_addr));

		memset(&dns_info, 0, sizeof(dns_info));
		dns_info.ip.type = ESP_IPADDR_TYPE_V4;
		IP4_ADDR(&dns_info.ip.u_addr.ip4, ETH_DNS0, ETH_DNS1, ETH_DNS2, ETH_DNS3);
		esp_netif_set_dns_info(eth_netif, ESP_NETIF_DNS_MAIN, &dns_info);

		ETH_LOGI3(ETH_TAG, "Static IP: " IPSTR, IP2STR(&ip_info.ip));
	#else
		esp_netif_dns_info_t dns_info;
		// DHCP mode - provide a fallback DNS server in case the lease has none
		memset(&dns_info, 0, sizeof(dns_info));
		dns_info.ip.type = ESP_IPADDR_TYPE_V4;
		IP4_ADDR(&dns_info.ip.u_addr.ip4, ETH_DNS0, ETH_DNS1, ETH_DNS2, ETH_DNS3);
		esp_netif_set_dns_info(eth_netif, ESP_NETIF_DNS_FALLBACK, &dns_info);
	#endif
}


/*********************************************************************
 * PHY creation
 *********************************************************************/
static esp_eth_phy_t* eth_create_phy(eth_phy_config_t *phy_config)
{
	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
		switch (ETH_PHY_TYPE)
		{
			case 1:  return esp_eth_phy_new_ip101(phy_config);
			case 2:  return esp_eth_phy_new_rtl8201(phy_config);
			case 3:  return esp_eth_phy_new_dp83848(phy_config);
			case 4:  return esp_eth_phy_new_ksz80xx(phy_config);
			default: return esp_eth_phy_new_lan87xx(phy_config);
		}
	#else
		switch (ETH_PHY_TYPE)
		{
			case 1:  return esp_eth_phy_new_ip101(phy_config);
			case 2:  return esp_eth_phy_new_rtl8201(phy_config);
			case 3:  return esp_eth_phy_new_dp83848(phy_config);
			case 4:  return esp_eth_phy_new_ksz8041(phy_config);
			default: return esp_eth_phy_new_lan8720(phy_config);
		}
	#endif
}


/*********************************************************************
 * Public API - mirrors ESP_CAL_WIFI.c
 *********************************************************************/

static MX_UINT8 eth_initialise(void)
{
	ETH_LOGI2(ETH_TAG, "eth_initialise()");

	if (eth_initialised)
		return eth_have_ip ? 1 : 0;

	// The target start-up code already calls esp_event_loop_create_default() and nvs_flash_init()
	MX_ESP_ETH_ERROR = esp_netif_init();
	if ((MX_ESP_ETH_ERROR != ESP_OK) && (MX_ESP_ETH_ERROR != ESP_ERR_INVALID_STATE))
		return 0;

	if (eth_event_group == NULL)
		eth_event_group = xEventGroupCreate();

	// Power up the PHY if a power pin is used (e.g. GPIO12 on the ESP32-POE)
	#if (ETH_PHY_POWER >= 0)
		{
			gpio_config_t io_conf;
			memset(&io_conf, 0, sizeof(io_conf));
			io_conf.pin_bit_mask = (1ULL << ETH_PHY_POWER);
			io_conf.mode = GPIO_MODE_OUTPUT;
			io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
			io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
			io_conf.intr_type = GPIO_INTR_DISABLE;
			gpio_config(&io_conf);
			gpio_set_level(ETH_PHY_POWER, 1);
			vTaskDelay(pdMS_TO_TICKS(20));
		}
	#endif

	// MAC
	eth_mac_config_t mac_config = ETH_MAC_DEFAULT_CONFIG();
	#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 0, 0)
		eth_esp32_emac_config_t emac_config = ETH_ESP32_EMAC_DEFAULT_CONFIG();
		#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5, 3, 0)
			emac_config.smi_gpio.mdc_num = ETH_MDC;
			emac_config.smi_gpio.mdio_num = ETH_MDIO;
		#else
			emac_config.smi_mdc_gpio_num = ETH_MDC;
			emac_config.smi_mdio_gpio_num = ETH_MDIO;
		#endif
		#if (ETH_CLK_MODE == 1)
			emac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			emac_config.clock_config.rmii.clock_gpio = EMAC_APPL_CLK_OUT_GPIO;
		#elif (ETH_CLK_MODE == 2)
			emac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			emac_config.clock_config.rmii.clock_gpio = EMAC_CLK_OUT_GPIO;
		#elif (ETH_CLK_MODE == 3)
			emac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			emac_config.clock_config.rmii.clock_gpio = EMAC_CLK_OUT_180_GPIO;
		#else
			emac_config.clock_config.rmii.clock_mode = EMAC_CLK_EXT_IN;
			emac_config.clock_config.rmii.clock_gpio = EMAC_CLK_IN_GPIO;
		#endif
		esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&emac_config, &mac_config);
	#else
		mac_config.smi_mdc_gpio_num = ETH_MDC;
		mac_config.smi_mdio_gpio_num = ETH_MDIO;
		#if (ETH_CLK_MODE == 1)
			mac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			mac_config.clock_config.rmii.clock_gpio = EMAC_APPL_CLK_OUT_GPIO;
		#elif (ETH_CLK_MODE == 2)
			mac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			mac_config.clock_config.rmii.clock_gpio = EMAC_CLK_OUT_GPIO;
		#elif (ETH_CLK_MODE == 3)
			mac_config.clock_config.rmii.clock_mode = EMAC_CLK_OUT;
			mac_config.clock_config.rmii.clock_gpio = EMAC_CLK_OUT_180_GPIO;
		#else
			mac_config.clock_config.rmii.clock_mode = EMAC_CLK_EXT_IN;
			mac_config.clock_config.rmii.clock_gpio = EMAC_CLK_IN_GPIO;
		#endif
		esp_eth_mac_t *mac = esp_eth_mac_new_esp32(&mac_config);
	#endif
	if (mac == NULL)
	{
		ETH_LOGI2(ETH_TAG, "esp_eth_mac_new_esp32 failed");
		return 0;
	}

	// PHY
	eth_phy_config_t phy_config = ETH_PHY_DEFAULT_CONFIG();
	phy_config.phy_addr = ETH_PHY_ADDR;
	phy_config.reset_gpio_num = ETH_PHY_RESET;
	esp_eth_phy_t *phy = eth_create_phy(&phy_config);
	if (phy == NULL)
	{
		ETH_LOGI2(ETH_TAG, "PHY creation failed");
		mac->del(mac);
		return 0;
	}

	// Driver
	esp_eth_config_t eth_config = ETH_DEFAULT_CONFIG(mac, phy);
	if (ESP_OK != (MX_ESP_ETH_ERROR = esp_eth_driver_install(&eth_config, &eth_handle)))
	{
		ETH_LOGI3(ETH_TAG, "esp_eth_driver_install failed: %d", MX_ESP_ETH_ERROR);
		phy->del(phy);
		mac->del(mac);
		eth_handle = NULL;
		return 0;
	}

	// Network interface
	esp_netif_config_t netif_cfg = ESP_NETIF_DEFAULT_ETH();
	eth_netif = esp_netif_new(&netif_cfg);
	if (eth_netif == NULL)
	{
		ETH_LOGI2(ETH_TAG, "esp_netif_new failed");
		esp_eth_driver_uninstall(eth_handle);
		eth_handle = NULL;
		return 0;
	}
	eth_glue = esp_eth_new_netif_glue(eth_handle);
	if (ESP_OK != (MX_ESP_ETH_ERROR = esp_netif_attach(eth_netif, eth_glue)))
	{
		ETH_LOGI3(ETH_TAG, "esp_netif_attach failed: %d", MX_ESP_ETH_ERROR);
		return 0;
	}

	// Events
	esp_event_handler_register(ETH_EVENT, ESP_EVENT_ANY_ID, &eth_event_handler, NULL);
	esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &eth_got_ip_handler, NULL);

	eth_apply_static_ip();

	esp_eth_ioctl(eth_handle, ETH_CMD_G_MAC_ADDR, eth_mac_addr);

	eth_initialised = true;

	// Bring the link up and wait for it to become usable
	eth_have_ip = false;
	xEventGroupClearBits(eth_event_group, ETH_LINK_UP_BIT | ETH_CONNECTED_BIT);
	ETH_LOGI2(ETH_TAG, "Starting Ethernet ...");
	if (ESP_OK != (MX_ESP_ETH_ERROR = esp_eth_start(eth_handle)))
	{
		ETH_LOGI3(ETH_TAG, "esp_eth_start failed: %d", MX_ESP_ETH_ERROR);
		return 0;
	}
	eth_started = true;

	EventBits_t bits = xEventGroupWaitBits(eth_event_group,
			ETH_CONNECTED_BIT,
			pdFALSE,
			pdFALSE,
			pdMS_TO_TICKS((uint32_t)ETH_CONNECT_TIMEOUT * 1000UL));

	if (bits & ETH_CONNECTED_BIT)
	{
		ETH_LOGI3(ETH_TAG, "Ethernet ready, IP: " IPSTR, IP2STR(&eth_ip_addr));
		return 1;
	}

	ETH_LOGI2(ETH_TAG, "Ethernet connect timed out (no link / no DHCP lease)");
	return 0;
}



/**
	Stops the link, removes the driver and netif, powers down the PHY.
	Returns 1 if successful.
**/
static MX_UINT8 eth_deinitialise(void)
{
	if (!eth_initialised)
		return 1;

	if (eth_started)
	{
		esp_eth_stop(eth_handle);
		eth_started = false;
	}

	esp_event_handler_unregister(IP_EVENT, IP_EVENT_ETH_GOT_IP, &eth_got_ip_handler);
	esp_event_handler_unregister(ETH_EVENT, ESP_EVENT_ANY_ID, &eth_event_handler);

	if (eth_glue)
	{
		esp_eth_del_netif_glue(eth_glue);
		eth_glue = NULL;
	}
	if (eth_netif)
	{
		esp_netif_destroy(eth_netif);
		eth_netif = NULL;
	}
	if (eth_handle)
	{
		MX_ESP_ETH_ERROR = esp_eth_driver_uninstall(eth_handle);
		eth_handle = NULL;
	}

	#if (ETH_PHY_POWER >= 0)
		gpio_set_level(ETH_PHY_POWER, 0);
	#endif

	eth_link_up = false;
	eth_have_ip = false;
	eth_initialised = false;
	return (MX_ESP_ETH_ERROR == ESP_OK) ? 1 : 0;
}





/**
	Link status and MAC address
**/
static MX_UINT8 eth_link_status(void)
{
	return eth_link_up ? 1 : 0;
}

static void eth_mac_string(char *buffer, MX_UINT16 bufferLen)
{
	if (bufferLen < 18)
	{
		if (bufferLen) buffer[0] = 0;
		return;
	}
	snprintf(buffer, bufferLen, "%02X:%02X:%02X:%02X:%02X:%02X",
		eth_mac_addr[0], eth_mac_addr[1], eth_mac_addr[2],
		eth_mac_addr[3], eth_mac_addr[4], eth_mac_addr[5]);
}



/**
	Socket layer - identical behaviour to ESP_CAL_WIFI.c
	Network comms component just returns 0=fail or 1=successful
	So just do that for now and keep a copy of the single socket handle
**/
static int eth_socket_handle = 0;
static int eth_accept_handle = 0;

static void eth_accept_close(void)
{
	if (eth_accept_handle) close(eth_accept_handle);
	eth_accept_handle = 0;
}

static void eth_socket_close(void)
{
	eth_accept_close();
	if (eth_socket_handle) close(eth_socket_handle);
	eth_socket_handle = 0;
}

static int eth_socket_open(void)
{
	eth_accept_close();
	eth_socket_close();

	// use some defaults for family and socket type
	if (0 < (eth_socket_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		return 1;
	}
	eth_socket_handle = 0;
	return 0;
}

static MX_UINT8 eth_socket_connect(MX_STRING url, MX_UINT16 urlLen, MX_UINT16 port)
{
	const struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM,
	};
	struct addrinfo *res;
	char s_port[8];
	sprintf(s_port, "%d", port);
	int err = getaddrinfo(url, s_port, &hints, &res);

	if (err != 0 || res == NULL)
	{
		ETH_LOGI4(ETH_TAG, "FLOWCODE DNS lookup failed err=%d res=%p", err, res);
		if (res) freeaddrinfo(res);
		return 0;
	}
	else
	{
		ETH_LOGI2(ETH_TAG, "FLOWCODE DNS lookup OK");

		if (connect(eth_socket_handle, res->ai_addr, res->ai_addrlen) == 0)
		{
			ETH_LOGI2(ETH_TAG, "... connected");
			fcntl(eth_socket_handle, F_SETFL, O_NONBLOCK);
			if (res) freeaddrinfo(res);
			return 1;
		}
		else
		{
			ETH_LOGI3(ETH_TAG, "... socket connect failed errno=%d", errno);
			if (res) freeaddrinfo(res);
			return 0;
		}
	}
}

static MX_UINT16 eth_socket_read(void* buffer, MX_UINT16 bufferLen, MX_UINT16 size)
{
	int n = 0;
	if (eth_accept_handle)
	{
		n = read(eth_accept_handle, buffer, size);
	}
	else if (eth_socket_handle)
	{
		n = read(eth_socket_handle, buffer, size);
	}
	return (n < 0)?0:n;
}

static MX_UINT16 eth_socket_write(void* buffer, MX_UINT16 bufferLen, MX_UINT16 size)
{
	int n = 0;
	if (eth_accept_handle)
	{
		n = write(eth_accept_handle, buffer, size);
	}
	else if (eth_socket_handle)
	{
		n = write(eth_socket_handle, buffer, size);
	}
	return (n < 0)?0:n;
}

static MX_UINT8 eth_socket_listen(MX_UINT16 port)
{
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);
	if (0 == bind(eth_socket_handle, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
	{
		if (0 == listen(eth_socket_handle, 1))
		{
			return 1;
		}
	}
	return 0;
}

static MX_UINT8 eth_accept_open(void)
{
	if (eth_socket_handle)
	{
		struct sockaddr addr;
		socklen_t addrlen = sizeof(addr);
		fcntl(eth_socket_handle, F_SETFL, O_NONBLOCK);
		eth_accept_handle = accept(eth_socket_handle, &addr, &addrlen);
		if (eth_accept_handle > 0)
		{
			fcntl(eth_accept_handle, F_SETFL, O_NONBLOCK);
			return 1;  // Success
		}
	}
	eth_accept_handle = 0;
	return 0;
}
