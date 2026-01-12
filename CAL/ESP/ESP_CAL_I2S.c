// CRC: 84D9E1FE72EA3BCC519B65499DB4B2BCC2E928A318D32B862581E6BBE90394A0F7CEC8E53CB99131B3087F1A47E35D969A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5DFE2BDBFF4DD2F9B64C502B7D111995C382D01CFBD4D13F64A5F412079F0B3EC382D9AD4B3437EDD8EC67D7FAC3D8104DBBA303EC66A19D16D89A83B5FDEE25C5012DCE00CE7F0BA5520FE07A2506E54773B737E27F802A3549D34A0D5AD11F3694E2EBE6BCC634DA3B86236AA5BD63E1A9EA10A2A84C263C1E0961D1CF9D810AE94354B8E74C3BA
// REVISION: 1.0
// GUID: 473AF68D-156C-490A-B5C9-FD87C6C676A0
// DATE: 08\08\2022
// DIR: CAL\ESP\ESP_CAL_I2S.c
/*********************************************************************
 *                  Flowcode CAL I2S File
 *
 * File: ESP_CAL_I2S.c
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
 * 080121 | BR | Created
 */

#include <driver/i2s.h>

//I2S Peripheral Definitions
#define MX_I2S_CHANNEL_X			CAL_APPEND(MX_I2S_CHANNEL_, MX_I2S_NUM)
#define MX_I2S_SAMPLE_RATE_X		CAL_APPEND(MX_I2S_SAMPLE_RATE_, MX_I2S_NUM)
#define MX_I2S_DATA_BITS_X			CAL_APPEND(MX_I2S_DATA_BITS_, MX_I2S_NUM)
#define MX_I2S_MASTER_X				CAL_APPEND(MX_I2S_MASTER_, MX_I2S_NUM)
#define MX_I2S_DDR_X				CAL_APPEND(MX_I2S_DDR_, MX_I2S_NUM)
#define MX_I2S_AUDIO_CHANNELS_X		CAL_APPEND(MX_I2S_AUDIO_CHANNELS_, MX_I2S_NUM)
#define MX_I2S_DMABUFFCOUNT_X		CAL_APPEND(MX_I2S_DMABUFFCOUNT_, MX_I2S_NUM)
#define MX_I2S_DMABUFFSIZE_X		CAL_APPEND(MX_I2S_DMABUFFSIZE_, MX_I2S_NUM)

#define MX_I2S_CK_PIN_X				CAL_APPEND(MX_I2S_CK_PIN_, MX_I2S_NUM)
#define MX_I2S_SD_PIN_X				CAL_APPEND(MX_I2S_SD_PIN_, MX_I2S_NUM)
#define MX_I2S_WS_PIN_X				CAL_APPEND(MX_I2S_WS_PIN_, MX_I2S_NUM)


#define MX_I2S_SAMPLE_BYTES			(MX_I2S_DATA_BITS_X >> 3)


//I2S Function Prototypes
CALFUNCTION(void, FC_CAL_I2S_Initialise_, (void));
CALFUNCTION(MX_UINT16, FC_CAL_I2S_Write_, (MX_SINT16 * Output, MX_UINT16 OutputLen, MX_UINT16 Length, MX_UINT16 Timeout));
CALFUNCTION(MX_UINT16, FC_CAL_I2S_Read_, (MX_SINT16 * Input, MX_UINT16 OutputLen, MX_UINT16 Length, MX_UINT16 Timeout));
CALFUNCTION(void, FC_CAL_I2S_Start_, ());
CALFUNCTION(void, FC_CAL_I2S_Stop_, ());

/*
static void IRAM_ATTR i2s_isr ( )    // Single point entry for all i2s0 module interrupt sources registered and enabled ????
{
    if ( I2S0.int_st.out_eof )
    {
    }

    if ( I2S0.int_st.out_total_eof )
    {
    }

    if ( I2S0.int_st.out_done )
    {
    }

    if ( I2S0.int_st.tx_rempty )
    {
    }

    I2S0.int_clr.val = I2S0.int_st.val;    // Clear all interrupt flags.
}
*/

//I2S Initialise - Sets up the I2S peripheral ready for data
//Auto starts the I2S Read/Write
CALFUNCTION(void, FC_CAL_I2S_Initialise_, (void))
{
	i2s_pin_config_t pin_config;

	MX_UINT8 I2S_Mode;

	#if (MX_I2S_MASTER_X == 0)
		I2S_Mode = I2S_MODE_MASTER;
	#else
		I2S_Mode = I2S_MODE_SLAVE;
	#endif

  #if (MX_I2S_DDR_X == 0)
  	I2S_Mode |= I2S_MODE_TX;		//TX mode
	pin_config.bck_io_num = MX_I2S_CK_PIN_X;
	pin_config.ws_io_num = MX_I2S_WS_PIN_X;
	pin_config.data_out_num = MX_I2S_SD_PIN_X;
	pin_config.data_in_num = -1;
  #endif

  #if (MX_I2S_DDR_X == 1)
    I2S_Mode |= I2S_MODE_RX;		//RX mode
	pin_config.bck_io_num = MX_I2S_CK_PIN_X;
	pin_config.ws_io_num = MX_I2S_WS_PIN_X;
	pin_config.data_out_num = -1;
	pin_config.data_in_num = MX_I2S_SD_PIN_X;
  #endif

	i2s_config_t i2s_config = {
		.mode = I2S_Mode,
		.sample_rate = MX_I2S_SAMPLE_RATE_X,
		.bits_per_sample = 16,
		.channel_format = MX_I2S_AUDIO_CHANNELS_X,
		.communication_format = I2S_COMM_FORMAT_I2S,
		.dma_buf_count = MX_I2S_DMABUFFCOUNT_X,
		.dma_buf_len = MX_I2S_DMABUFFSIZE_X,
		.use_apll = false,
		.tx_desc_auto_clear= true,
		.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
		.fixed_mclk=-1
    };

    i2s_driver_install((MX_I2S_CHANNEL_X - 1), &i2s_config, 0, NULL);
    i2s_set_pin((MX_I2S_CHANNEL_X - 1), &pin_config);
    //i2s_set_clk((MX_I2S_CHANNEL_X - 1), MX_I2S_SAMPLE_RATE_X, MX_I2S_DATA_BITS_X, MX_I2S_AUDIO_CHANNELS_X);
}

//I2S Write - Wait timeout ticks to send length number of samples, returns samples sent
CALFUNCTION(MX_UINT16, FC_CAL_I2S_Write_, (MX_SINT16 * Output, MX_UINT16 OutputLen, MX_UINT16 Length, MX_UINT16 Timeout))
{

  #if (MX_I2S_DDR_X == 0)
	size_t i2s_bytes_write = 0;
	size_t byte_count = (size_t) Length * MX_I2S_SAMPLE_BYTES;

    //uint32_t Value32Bit = Output[0];
    //Value32Bit = (Output[0]<<16) | (Output[0] & 0xffff); // Output same value on both left and right channels

	i2s_write((MX_I2S_CHANNEL_X - 1), &Output[0], byte_count, &i2s_bytes_write, Timeout);

	return ((MX_UINT16) i2s_bytes_write / MX_I2S_SAMPLE_BYTES);
  #endif


/*
  static const uint16_t Volume=0x3ff;             // Highest value the peak will get to, bigger gives louder vol, but
                                                  // too high can lead to distortion on cheap or small speakers
  static const int16_t Peak=Volume;               // Max height/peak
  static const int16_t Trough=-Volume;            // Max low/trough

  static int16_t OutputValue=Peak;                // Value to send to each channel (left/right), start off at the peak
  static const uint16_t WaveLength=100;           // Bigger =longer wavelength and higher frequency
  static uint16_t TimeAtPeakOrTrough=WaveLength;  // Var to count down how long we hold at either peak or trough
                                                  // (high/low)
  uint32_t Value32Bit;                            // This holds the value we actually send to the I2S buffers, it basically
                                                  // will hold the "OutputValue" but combined for both left/right channels

  size_t BytesWritten;                            // Returned by the I2S write routine, we are not interested in it but
                                                  // must supply it as a param to the routine.

  if(TimeAtPeakOrTrough==0)                       // If 0 then we're ready to switch to a peak (high) or trough (low)
  {
    if(OutputValue==Peak)                         // If we were a peak (high), switch to trough (low) value
        OutputValue=Trough;
    else                                          // else we were a trough (low) switch to peak (high)
        OutputValue=Peak;
    TimeAtPeakOrTrough=WaveLength;                // Reset this counter back to max, ready to countdown again
  }
  TimeAtPeakOrTrough--;                           // Decrement this counter that controls wavelenght/ frequency

  // This next line just creates the 32 bit word we send to the I2S interface/buffers. 16 bits for the righ channel
  // and 16 bits for the left, as we are sending the same wave to both channels we just combine them using some
  // bit shifting and masking. If you're not sure what's happening here then look up bit shifting/ manipulation
  // on a C programming website.
*/
//size_t BytesWritten;
//uint32_t Value32Bit;
//  Value32Bit = (Output[0]<<16) | (Output[1] & 0xffff); // Output same value on both left and right channels

  // Output the combined 32bit value, will not return from this routine until written (blocks your code). Look
  // up this function for further info
 // i2s_write(0,&Value32Bit,4,&BytesWritten,portMAX_DELAY );

	return 0;
}

//I2S Read - Wait timeout ticks to receive length number of samples, returns samples received
CALFUNCTION(MX_UINT16, FC_CAL_I2S_Read_, (MX_SINT16 * Input, MX_UINT16 OutputLen, MX_UINT16 Length, MX_UINT16 Timeout))
{
  #if (MX_I2S_DDR_X == 1)
	size_t i2s_bytes_read = 0;
	size_t byte_count = (size_t) Length * MX_I2S_SAMPLE_BYTES;

	i2s_read((MX_I2S_CHANNEL_X - 1), &Input, byte_count, &i2s_bytes_read, Timeout);

	return ((MX_UINT16) i2s_bytes_read / MX_I2S_SAMPLE_BYTES);
  #endif

	return 0;
}

//Starts the I2S Read/Write - Auto started after Init so only required after calling stop to restart.
CALFUNCTION(void, FC_CAL_I2S_Start_, ())
{
	i2s_start(MX_I2S_CHANNEL_X - 1);
}

//Stops the I2S Red/Write
CALFUNCTION(void, FC_CAL_I2S_Stop_, ())
{
	i2s_stop(MX_I2S_CHANNEL_X - 1);
}


#undef MX_I2S_SAMPLE_BYTES
