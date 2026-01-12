// CRC: 675B15CA0DE03A7497A65F03351863B93D8DFBB3B6960DACF67DB601F837E3BE3B9339BD1F6CB45BB0C4A20ACC10A5FF9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51266B7A6B578CF12E7DB71276E5C0452159130C8851479196BFBA641C2F72991F99348F4E2DAD8BE7B43053D66AC74641F5F4392511BD793CC664BE759134ECAEB41BA395431B3BA8A0F02DA7BE5BA2906E289E88807B31E549D34A0D5AD11F3039599B9221F86A8F346BDDF6C1E4867C641ED9608936EE22E2E537ED3A62AD834F73E07AA889468
// REVISION: 1.0
// GUID: DCEA29CA-1560-40D6-8826-57DBD5127806
// DATE: 08\08\2022
// DIR: CAL\STARM\STARM_CAL_IO.h
/*********************************************************************
 *                  Flowcode CAL IO File
 *
 * File: STARM_CAL_IO.h
 *
 * (c) 2016 Matrix TSL
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
 * 280416 | SK | Created
 */


// FC8 Port/Pin macros

#define GET_PORT(p) 					FCP_GET(F,p,0xFFFF,0)
#define GET_PORT_PIN(p,b) 				FCP_GET(B,p,(1<<b),b)
#define GET_PORT_SHIFT(p,s) 			FCP_GET(M,p,0xFFFF,s)
#define GET_PORT_MASK_SHIFT(p,m,s) 		FCP_GET(M,p,m,s)
#define GET_PORT_MASK(p,m) 				FCP_GET(M,p,m,0)

#define SET_PORT(p,v) 					FCP_SET(F,p,0xFFFF,0,v)
#define SET_PORT_PIN(p,b,v) 			FCP_SET(B,p,(1<<b),b,((v)?0xFFFF:0))
#define SET_PORT_SHIFT(p,s,v) 			FCP_SET(M,p,0xFFFF,s,v)
#define SET_PORT_MASK_SHIFT(p,m,s,v)	FCP_SET(M,p,m,s,v)
#define SET_PORT_MASK(p,m,v)			FCP_SET(M,p,m,0,v)



#ifdef MX_BL0061_PINMAP

	#define FCP_GET(Type, Port, Mask, Shift) 			FC_CAL_Port_In_DDR__##Port(Mask, Shift)
	#define FCP_SET(Type, Port, Mask, Shift, Source) 	FC_CAL_Port_Out_DDR__##Port(Mask, Source)

	#define porta 0
	#define portb 1
	#define portc 2
	#define portd 3
	#define porte 4
	#define portf 5

	#define trisa 0
	#define trisb 1
	#define trisc 2
	#define trisd 3
	#define trise 4
	#define trisf 5

#else

	// FC Legacy Port/Pin macros
	#define FCP_GET(Type, Port, Mask, Shift) FCP_GET_##Type(GPIO##Port, Mask, Shift)
	#define FCP_SET(Type, Port, Mask, Shift, Source) FCP_SET_##Type(GPIO##Port, Mask, Shift, Source)

	#define FC_CAL_Bit_In_DDR(Port, Tris, Pin)		(FC_CAL_Bit_In_DDR__x((Port), (Pin)))
	#define FC_CAL_Bit_High_DDR(Port, Tris, Pin)	FCP_SET_B(Port, (1 << Pin), Pin, (1 << Pin))
	#define FC_CAL_Bit_Low_DDR(Port, Tris, Pin)		FCP_SET_B(Port, (1 << Pin), Pin, (0 << Pin))

	#define FC_CAL_Bit_In(Port, Pin)				(FC_CAL_Port_In__x((Port), (1 << Pin), (Pin)))
	#define FC_CAL_Bit_High(Port, Pin)				FC_CAL_Port_Out__x ((Port), (1 << Pin), (1 << Pin))
	#define FC_CAL_Bit_Low(Port, Pin)				FC_CAL_Port_Out__x ((Port), (1 << Pin), (0 << Pin))


	#define FCP_GET_B(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((Port), (Mask), (Shift)))
	#define FCP_GET_M(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((Port), (Mask), (Shift)))
	#define FCP_GET_F(Port, Mask, Shift)   (FC_CAL_Port_In_DDR__x((Port), (Mask), (Shift)))

	// Bit setting macro
	#if defined GPIO_MODER_MODER0
	#define FCP_SET_B(Port, Mask, Shift, Source)	{Port->MODER = (Port->MODER & ~(3<<((Shift)*2))) | (1<<((Shift)*2)); Port->BSRR = 1 << (Shift + ((Source)?0:16));}
	#elif defined GPIO_CRH_MODE
		#define FCP_SET_B(Port, Mask, Shift, Source)    {if(Shift<8){Port->CRL=(Port->CRL&~(3<<((Shift)*4)))|(1<<((Shift)*4));}else{Port->CRH=(Port->CRH&~(3<<((Shift&7)*4)))|(1<<((Shift&7)*4));};Port->BSRR=1<<(Shift+((Source)?0:16));}
	#else
		#define FCP_SET_B(Port, Mask, Shift, Source)    FC_CAL_Port_Out_DDR__x (Port, Mask,(Source))
	#endif

	// Mask setting macro
	#if defined GPIO_MODER_MODER0
		#define FCP_SET_M(Port, Mask, Shift, Source) \
			{ uint32_t p; for(p = 0U; p < 16; p++) {if (Mask & (1<<p)) {Port->MODER = (Port->MODER & ~(3<<((p)*2))) | (1<<((p)*2));}} \
			Port->ODR = (Port->ODR & ~Mask) | ((Source << Shift) & Mask); }
	#else
	#define FCP_SET_M(Port, Mask, Shift, Source)    FC_CAL_Port_Out_DDR__x (Port, Mask,(Source << Shift))
	#endif

	// Full port setting macro
	#if defined GPIO_MODER_MODER0
		#define FCP_SET_F(Port, Mask, Shift, Source) ({Port->MODER = 0x55555555; Port->ODR = Source;})
	#else
	#define FCP_SET_F(Port, Mask, Shift, Source)    FC_CAL_Port_Out_DDR__x (Port, Mask,(Source << Shift))
	#endif



	//GPIOA
	#define porta GPIOA
	#define PORTA GPIOA
	#define trisa GPIOA
	#define TRISA GPIOA
	//GPIOB
	#define portb GPIOB
	#define PORTB GPIOB
	#define trisb GPIOB
	#define TRISB GPIOB
	//GPIOC
	#define portc GPIOC
	#define PORTC GPIOC
	#define trisc GPIOC
	#define TRISC GPIOC
	//GPIOD
	#define portd GPIOD
	#define PORTD GPIOD
	#define trisd GPIOD
	#define TRISD GPIOD
	//GPIOE
	#define porte GPIOE
	#define PORTE GPIOE
	#define trise GPIOE
	#define TRISE GPIOE
	//GPIOF
	#define portf GPIOF
	#define PORTF GPIOF
	#define trisf GPIOF
	#define TRISF GPIOF
	//GPIOG
	#define portg GPIOG
	#define PORTG GPIOG
	#define trisg GPIOG
	#define TRISG GPIOG
	//GPIOH
	#define porth GPIOH
	#define PORTH GPIOH
	#define trish GPIOH
	#define TRISH GPIOH
	//GPIOI
	#define porti GPIOI
	#define PORTI GPIOI
	#define trisi GPIOI
	#define TRISI GPIOI
	//GPIOJ
	#define portj GPIOJ
	#define PORTJ GPIOJ
	#define trisj GPIOJ
	#define TRISJ GPIOJ
	//GPIOK
	#define portk GPIOK
	#define PORTK GPIOK
	#define trisk GPIOK
	#define TRISK GPIOK
	//GPIOL
	#define portl GPIOL
	#define PORTL GPIOL
	#define trisl GPIOL
	#define TRISL GPIOL
	//GPIOM
	#define portm GPIOM
	#define PORTM GPIOM
	#define trism GPIOM
	#define TRISM GPIOM
	//GPION
	#define portn GPION
	#define PORTN GPION
	#define trisn GPION
	#define TRISN GPION
	//GPIOO
	#define porto GPIOO
	#define PORTO GPIOO
	#define triso GPIOO
	#define TRISO GPIOO
	//GPIOP
	#define portp GPIOP
	#define PORTP GPIOP
	#define trisp GPIOP
	#define TRISP GPIOP

#endif



#define FCP_SET_NODDR(Port, Pin, Value)			GPIO##Port->BSRR = 1 << (Pin + (Value?0:16))


void MX_EXTI_PinInit(GPIO_TypeDef *EXTI_Port, uint32_t EXTI_Pin, uint32_t EXTI_Mode, uint32_t WeakBias);


