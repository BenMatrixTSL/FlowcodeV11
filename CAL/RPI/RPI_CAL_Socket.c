// CRC: 34358081B117C27F7D8358E612878F8E5F343B66182D417818220CB9C07676CFA534618C6496F499B1DC5F2FC9D3B6739A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF551AE2358A8CE0D3DDAE67ED471F190570629643B8B7DE2B3AEA58DD5D49003B228E5D11605D179BC23F8CE77F36A0245929F98FFA5221E3CD6EDA109571A4CAD1F35CDB2CC398B91D30338D387B678674E7F029C349C2F7A549D34A0D5AD11F32A2F950EE09C87A8F43501E4AFEACC3567BAD706CB962B87B0330AA6FB05B88105A68DA3CE9026E5
// REVISION: 1.0
// GUID: 9A4429DC-FDF9-4EEE-9F8A-2F242E82D43A
// DATE: 08\08\2022
// DIR: CAL\RPI\RPI_CAL_Socket.c
/*********************************************************************
 *                  Flowcode CAL Socket File
 *
 * File: RPI_CAL_Socket.c
 *
 * (c) 2018 Matrix TSL
 * http://www.matrixTSL.com
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
 * 260318 | LM | Created
 *
 */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define DEBUG_PRINT(text)	{printf("\n"); printf(text); mx_delay_m(1000); }

#define MX_SOCKET_HANDLE_X     CAL_APPEND(MX_SOCKET_HANDLE_, MX_SOCKET_NUM)
#define MX_SOCKET_MODE_X       CAL_APPEND(MX_SOCKET_MODE_, MX_SOCKET_NUM)
#define MX_SOCKET_STATE_X       CAL_APPEND(MX_SOCKET_STATE_, MX_SOCKET_NUM)
#define MX_ACCEPT_HANDLE_X     CAL_APPEND(MX_ACCEPT_HANDLE_, MX_SOCKET_NUM)

#define MX_HANDLE_INVALID   (-1)
// Flowcode socket mode definitions
#define MX_SOCKET_MODE_NONE        (-1)
#define MX_SOCKET_MODE_TCP_STREAM  (0)
#define MX_SOCKET_MODE_UDP_DGRAM   (1)
// Socket state
#define MX_SOCKET_STATE_NOT_CONNECTED	(0)
#define MX_SOCKET_STATE_CONNECTED		(1)
#define MX_SOCKET_STATE_ACCEPT          (2)

int           MX_SOCKET_HANDLE_X   = MX_HANDLE_INVALID;
signed char   MX_SOCKET_MODE_X     = MX_SOCKET_MODE_NONE;
signed char   MX_SOCKET_STATE_X    = MX_SOCKET_STATE_NOT_CONNECTED;
int           MX_ACCEPT_HANDLE_X   = MX_HANDLE_INVALID;

CALFUNCTION(MX_UINT8, FC_CAL_SOCKET_SocketOpen_, (MX_UINT8 FCL_TYPE))
{
	// If we are trying to open an existing socket then close it first
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
		close(MX_SOCKET_HANDLE_X);
	
	MX_SOCKET_HANDLE_X = MX_HANDLE_INVALID;
	MX_SOCKET_MODE_X = FCL_TYPE;
	MX_SOCKET_STATE_X = MX_SOCKET_STATE_NOT_CONNECTED;

	switch(MX_SOCKET_MODE_X)
	{
		case MX_SOCKET_MODE_UDP_DGRAM:
			MX_SOCKET_HANDLE_X = socket(AF_INET, SOCK_DGRAM |  SOCK_CLOEXEC, IPPROTO_UDP); // AF_INET or AF_UNSPEC?
			break;
		default:
		case MX_SOCKET_MODE_TCP_STREAM:
			MX_SOCKET_HANDLE_X = socket(AF_INET, SOCK_STREAM |  SOCK_CLOEXEC, IPPROTO_TCP); // AF_INET or AF_UNSPEC?
			break;
	}
	// Return the result, 0=Fail, 1=Successful
	return (MX_SOCKET_HANDLE_X == MX_HANDLE_INVALID)?0:1;
}

CALFUNCTION(MX_UINT8, FC_CAL_SOCKET_Listen_, (MX_UINT16 FCL_PORT))
{
	MX_UINT8 result = 0;
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
	{
		int error;
		struct addrinfo hints;
		struct addrinfo *info_list;
		struct addrinfo *info;
		
		char port[16];
		sprintf(port,"%d", FCL_PORT);
		
		// Setup the hints structure
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    /* Allow IPv4 (AF_INET) or IPv6 */
		hints.ai_flags = AI_PASSIVE;
		hints.ai_protocol = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr = NULL;
		hints.ai_next = NULL;	
		switch(MX_SOCKET_MODE_X)
		{
			case MX_SOCKET_MODE_UDP_DGRAM:
				hints.ai_socktype = SOCK_DGRAM;
				break;
			default:
			case MX_SOCKET_MODE_TCP_STREAM:
				hints.ai_socktype = SOCK_STREAM;
				break;
		}
		
		// Attempt to resolve the host
		if (error = getaddrinfo(NULL, port, &hints, &info_list) == 0)
		{
			// Success, try the addresses
			for (info = info_list; info != NULL; info = info->ai_next)
			{
				if (bind(MX_SOCKET_HANDLE_X, info->ai_addr, info->ai_addrlen) >= 0)
				{
					if (listen(MX_SOCKET_HANDLE_X, 0) == 0)
					{
						result = 1;
						break;
					}
				}
			}
			freeaddrinfo(info_list);
		}
	}
	// Return the result, 0=fail, 1=success
	return result;
}

CALFUNCTION(MX_UINT8, FC_CAL_SOCKET_Connect_, (MX_CHAR *FCL_ADDRESS, MX_UINT16 FCLsz_ADDRESS, MX_UINT16 FCL_PORT))
{
	MX_UINT8 result = 0;
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
	{
		int error;
		struct addrinfo hints;
		struct addrinfo *info_list;
		struct addrinfo *info;
		
		char port[16];
		sprintf(port,"%d", FCL_PORT);
		
		// Setup the hints structure
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    /* Allow IPv4 (AF_INET) or IPv6 */
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_flags = AI_PASSIVE;
		hints.ai_protocol = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr = NULL;
		hints.ai_next = NULL;	

		// Attempt to resolve the host
		if (error = getaddrinfo(FCL_ADDRESS, port, &hints, &info_list) == 0)
		{
			// Success, try the addresses
			for (info = info_list; info != NULL; info = info->ai_next)
			{
				if (connect(MX_SOCKET_HANDLE_X, info->ai_addr, info->ai_addrlen) >= 0)
				{
					MX_SOCKET_STATE_X = MX_SOCKET_STATE_CONNECTED;
					result = 1;
				}
			}
			freeaddrinfo(info_list);
		}
	}
	// Return the result, 0=fail, 1=success
	return result;
}

CALFUNCTION(MX_UINT16, FC_CAL_SOCKET_Send_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT16 FCL_COUNT))
{
	MX_UINT16 sent = 0;
	int result;
	
	if (FCL_COUNT > FCLsz_DATA)
		FCL_COUNT = FCLsz_DATA;

	if (MX_ACCEPT_HANDLE_X != MX_HANDLE_INVALID)
	{
		result = send(MX_ACCEPT_HANDLE_X, FCL_DATA, FCL_COUNT, 0);
		if (result > 0)
		{
			sent = result;
		}
	}
	else if ((MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)&&(MX_SOCKET_STATE_X == MX_SOCKET_STATE_CONNECTED))
	{
		result = send(MX_SOCKET_HANDLE_X, FCL_DATA, FCL_COUNT, 0);
		if (result > 0)
		{
			sent = result;
		}
	}
	return sent;
}

CALFUNCTION(MX_UINT16, FC_CAL_SOCKET_Receive_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT16 FCL_COUNT))
{
	MX_UINT16 received = 0;
	int result;

	if (FCL_COUNT > FCLsz_DATA)
		FCL_COUNT = FCLsz_DATA;
		
	if (MX_ACCEPT_HANDLE_X != MX_HANDLE_INVALID)
	{
		result = recv(MX_ACCEPT_HANDLE_X, FCL_DATA, FCL_COUNT, MSG_DONTWAIT);
		if (result > 0)
			received = result; 
	}
	else if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
	{
		result = recv(MX_SOCKET_HANDLE_X, FCL_DATA, FCL_COUNT, MSG_DONTWAIT);
		if (result > 0)
			received = result; 
	}
	return received;
}

CALFUNCTION(MX_UINT16, FC_CAL_SOCKET_SendTo_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT16 FCL_COUNT, MX_CHAR *FCL_ADDRESS, MX_UINT16 FCLsz_ADDRESS, MX_UINT16 FCL_PORT))
{
	MX_UINT16 sent = 0;

	if ((MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)&&((MX_SOCKET_MODE_X == MX_SOCKET_MODE_UDP_DGRAM)||(MX_SOCKET_STATE_X == MX_SOCKET_STATE_CONNECTED)))
	{
		int result = -1; 
		struct addrinfo hints;
		struct addrinfo *info_list = NULL;
		struct addrinfo *info;

		char port[16];
		sprintf(port,"%d", FCL_PORT);
	
		if (FCL_COUNT > FCLsz_DATA)
			FCL_COUNT = FCLsz_DATA;

		// Setup the hints structure
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    /* Allow IPv4 (AF_INET) or IPv6 */
		hints.ai_flags = AI_PASSIVE;
		hints.ai_protocol = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr = NULL;
		hints.ai_next = NULL;	

		switch(MX_SOCKET_MODE_X)
		{
			case MX_SOCKET_MODE_UDP_DGRAM:
				hints.ai_socktype = SOCK_DGRAM;
				break;
			default:
			case MX_SOCKET_MODE_TCP_STREAM:
				hints.ai_socktype = SOCK_STREAM;
				break;
		}
		
		// Attempt to resolve the host
		if (getaddrinfo(FCL_ADDRESS, port, &hints, &info_list) == 0)
		{
			// Success, try the addresses
			for (info = info_list; info != NULL; info = info->ai_next)
			{
				// Set to block
				int flags = fcntl(MX_SOCKET_HANDLE_X, F_GETFL);
				fcntl(MX_SOCKET_HANDLE_X, F_SETFL, flags & ~O_NONBLOCK);
				result = sendto(MX_SOCKET_HANDLE_X, FCL_DATA, FCL_COUNT, 0, info->ai_addr, info->ai_addrlen);
				if (result > 0)
				{
					// Connect success
					sent = result;
					break;     
				}
			}
			if (info_list)
			{
				freeaddrinfo(info_list);
			}
		}
	}
	return sent;
}

CALFUNCTION(MX_UINT8, FC_CAL_SOCKET_AcceptOpen_, (void))
{
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
	{
		struct sockaddr addr;
		socklen_t addrlen = sizeof(addr);
		// Change the socket into non-blocking state
		fcntl(MX_SOCKET_HANDLE_X, F_SETFL, O_NONBLOCK);
		// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
		MX_ACCEPT_HANDLE_X = accept(MX_SOCKET_HANDLE_X, &addr, &addrlen);
		if (MX_ACCEPT_HANDLE_X != MX_HANDLE_INVALID)
		{
			fcntl(MX_ACCEPT_HANDLE_X, F_SETFL, O_NONBLOCK);
			MX_SOCKET_STATE_X = MX_SOCKET_STATE_ACCEPT;
			return 1;  // Success
		}
	}
	return 0; // Fail
}

CALFUNCTION(MX_UINT16, FC_CAL_SOCKET_ReceiveFrom_, (MX_CHAR *FCL_DATA, MX_UINT16 FCLsz_DATA, MX_UINT16 FCL_COUNT, MX_CHAR *FCL_ADDRESS, MX_UINT16 FCLsz_ADDRESS, MX_UINT16 FCL_PORT))
{
	MX_UINT16 received = 0;

	if ((MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)&&((MX_SOCKET_MODE_X == MX_SOCKET_MODE_UDP_DGRAM)||(MX_SOCKET_STATE_X == MX_SOCKET_STATE_CONNECTED)))
	{
		int result = -1; 
		struct addrinfo hints;
		struct addrinfo *info_list = NULL;
		struct addrinfo *info;

		char port[16];
		sprintf(port,"%d", FCL_PORT);
	
		if (FCL_COUNT > FCLsz_DATA)
			FCL_COUNT = FCLsz_DATA;

		// Setup the hints structure
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    /* Allow IPv4 (AF_INET) or IPv6 */
		hints.ai_flags = AI_PASSIVE;
		hints.ai_protocol = 0;
		hints.ai_canonname = NULL;
		hints.ai_addr = NULL;
		hints.ai_next = NULL;	

		switch(MX_SOCKET_MODE_X)
		{
			case MX_SOCKET_MODE_UDP_DGRAM:
				hints.ai_socktype = SOCK_DGRAM;
				break;
			default:
			case MX_SOCKET_MODE_TCP_STREAM:
				hints.ai_socktype = SOCK_STREAM;
				break;
		}
		
		// Attempt to resolve the host
		// if Address is a null string, make pointer null
		if (FCL_ADDRESS[0] == 0) FCL_ADDRESS = 0;
		if (getaddrinfo(FCL_ADDRESS, port, &hints, &info_list) == 0)
		{
			// Success, try the addresses
			for (info = info_list; info != NULL; info = info->ai_next)
			{
				// set to non-blocking
				fcntl(MX_SOCKET_HANDLE_X, F_SETFL, O_NONBLOCK);
				result = recvfrom(MX_SOCKET_HANDLE_X, FCL_DATA, FCL_COUNT, 0, info->ai_addr, info->ai_addrlen);
				if (result > 0)
				{
					// Connect success
					received = result;
					break;     
				}
			}
			if (info_list)
			{
				freeaddrinfo(info_list);
			}
		}
	}
	return received;
}

CALFUNCTION(void, FC_CAL_SOCKET_SocketClose_, (void))
{
	// Close the accept socket if there is one
	if (MX_ACCEPT_HANDLE_X != MX_HANDLE_INVALID)
		close(MX_ACCEPT_HANDLE_X);
	// Close the socket if there is one
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
		close(MX_SOCKET_HANDLE_X);
	MX_SOCKET_HANDLE_X = MX_HANDLE_INVALID;
	MX_ACCEPT_HANDLE_X = MX_HANDLE_INVALID;
	MX_SOCKET_STATE_X = MX_SOCKET_STATE_NOT_CONNECTED;
}

CALFUNCTION(void, FC_CAL_SOCKET_AcceptClose_, (void))
{
	// Close the accept socket if there is one
	if (MX_ACCEPT_HANDLE_X != MX_HANDLE_INVALID)
		close(MX_ACCEPT_HANDLE_X);
	MX_ACCEPT_HANDLE_X = MX_HANDLE_INVALID;
	if (MX_SOCKET_HANDLE_X != MX_HANDLE_INVALID)
		MX_SOCKET_STATE_X = MX_SOCKET_STATE_CONNECTED;
}


