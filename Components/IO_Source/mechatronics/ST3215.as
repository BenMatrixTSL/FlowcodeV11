opt subtitle "Microchip MPLAB XC8 C Compiler v2.10 (Free license) build 20190730164152 Og9 "

opt pagewidth 120

	opt flic

	processor	16F1937
opt include "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\16f1937.cgen.inc"
getbyte	macro	val,pos
	(((val) >> (8 * pos)) and 0xff)
endm
byte0	macro	val
	(getbyte(val,0))
endm
byte1	macro	val
	(getbyte(val,1))
endm
byte2	macro	val
	(getbyte(val,2))
endm
byte3	macro	val
	(getbyte(val,3))
endm
byte4	macro	val
	(getbyte(val,4))
endm
byte5	macro	val
	(getbyte(val,5))
endm
byte6	macro	val
	(getbyte(val,6))
endm
byte7	macro	val
	(getbyte(val,7))
endm
getword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffff)
endm
word0	macro	val
	(getword(val,0))
endm
word1	macro	val
	(getword(val,2))
endm
word2	macro	val
	(getword(val,4))
endm
word3	macro	val
	(getword(val,6))
endm
gettword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffff)
endm
tword0	macro	val
	(gettword(val,0))
endm
tword1	macro	val
	(gettword(val,3))
endm
tword2	macro	val
	(gettword(val,6))
endm
getdword	macro	val,pos
	(((val) >> (8 * pos)) and 0xffffffff)
endm
dword0	macro	val
	(getdword(val,0))
endm
dword1	macro	val
	(getdword(val,4))
endm
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
pushw	macro
	movwi fsr1++
	endm
popw	macro
	moviw --fsr1
	endm
# 54 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INDF0 equ 00h ;# 
# 74 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INDF1 equ 01h ;# 
# 94 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCL equ 02h ;# 
# 114 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STATUS equ 03h ;# 
# 177 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0L equ 04h ;# 
# 197 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0H equ 05h ;# 
# 221 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1L equ 06h ;# 
# 241 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1H equ 07h ;# 
# 261 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BSR equ 08h ;# 
# 313 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WREG equ 09h ;# 
# 333 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCLATH equ 0Ah ;# 
# 353 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INTCON equ 0Bh ;# 
# 431 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTA equ 0Ch ;# 
# 493 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTB equ 0Dh ;# 
# 555 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTC equ 0Eh ;# 
# 617 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTD equ 0Fh ;# 
# 679 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTE equ 010h ;# 
# 717 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR1 equ 011h ;# 
# 779 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR2 equ 012h ;# 
# 836 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR3 equ 013h ;# 
# 882 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR0 equ 015h ;# 
# 902 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1 equ 016h ;# 
# 909 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1L equ 016h ;# 
# 929 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1H equ 017h ;# 
# 949 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T1CON equ 018h ;# 
# 1021 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T1GCON equ 019h ;# 
# 1098 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR2 equ 01Ah ;# 
# 1118 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR2 equ 01Bh ;# 
# 1138 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T2CON equ 01Ch ;# 
# 1209 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CPSCON0 equ 01Eh ;# 
# 1263 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CPSCON1 equ 01Fh ;# 
# 1309 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISA equ 08Ch ;# 
# 1371 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISB equ 08Dh ;# 
# 1433 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISC equ 08Eh ;# 
# 1495 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISD equ 08Fh ;# 
# 1557 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISE equ 090h ;# 
# 1595 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE1 equ 091h ;# 
# 1657 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE2 equ 092h ;# 
# 1714 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE3 equ 093h ;# 
# 1760 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OPTION_REG equ 095h ;# 
# 1843 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCON equ 096h ;# 
# 1894 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WDTCON equ 097h ;# 
# 1953 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCTUNE equ 098h ;# 
# 2011 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCCON equ 099h ;# 
# 2083 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCSTAT equ 09Ah ;# 
# 2145 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRES equ 09Bh ;# 
# 2152 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRESL equ 09Bh ;# 
# 2172 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRESH equ 09Ch ;# 
# 2192 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADCON0 equ 09Dh ;# 
# 2281 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADCON1 equ 09Eh ;# 
# 2353 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATA equ 010Ch ;# 
# 2415 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATB equ 010Dh ;# 
# 2477 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATC equ 010Eh ;# 
# 2539 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATD equ 010Fh ;# 
# 2609 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATE equ 0110h ;# 
# 2647 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM1CON0 equ 0111h ;# 
# 2704 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM1CON1 equ 0112h ;# 
# 2770 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM2CON0 equ 0113h ;# 
# 2827 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM2CON1 equ 0114h ;# 
# 2893 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CMOUT equ 0115h ;# 
# 2919 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BORCON equ 0116h ;# 
# 2946 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FVRCON equ 0117h ;# 
# 3022 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
DACCON0 equ 0118h ;# 
# 3083 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
DACCON1 equ 0119h ;# 
# 3135 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SRCON0 equ 011Ah ;# 
# 3206 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SRCON1 equ 011Bh ;# 
# 3268 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
APFCON equ 011Dh ;# 
# 3324 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELA equ 018Ch ;# 
# 3382 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELB equ 018Dh ;# 
# 3440 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELD equ 018Fh ;# 
# 3510 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELE equ 0190h ;# 
# 3550 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADR equ 0191h ;# 
# 3557 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADRL equ 0191h ;# 
# 3577 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADRH equ 0192h ;# 
# 3597 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDAT equ 0193h ;# 
# 3604 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATL equ 0193h ;# 
# 3609 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATA equ 0193h ;# 
# 3642 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATH equ 0194h ;# 
# 3662 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EECON1 equ 0195h ;# 
# 3724 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EECON2 equ 0196h ;# 
# 3744 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
RCREG equ 0199h ;# 
# 3764 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TXREG equ 019Ah ;# 
# 3784 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRG equ 019Bh ;# 
# 3791 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRGL equ 019Bh ;# 
# 3796 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRG equ 019Bh ;# 
# 3800 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRGL equ 019Bh ;# 
# 3845 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRGH equ 019Ch ;# 
# 3850 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRGH equ 019Ch ;# 
# 3883 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
RCSTA equ 019Dh ;# 
# 3945 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TXSTA equ 019Eh ;# 
# 4007 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BAUDCON equ 019Fh ;# 
# 4059 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WPUB equ 020Dh ;# 
# 4129 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WPUE equ 0210h ;# 
# 4150 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPBUF equ 0211h ;# 
# 4170 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPADD equ 0212h ;# 
# 4190 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPMSK equ 0213h ;# 
# 4210 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPSTAT equ 0214h ;# 
# 4272 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON1 equ 0215h ;# 
# 4277 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON equ 0215h ;# 
# 4394 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON2 equ 0216h ;# 
# 4456 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON3 equ 0217h ;# 
# 4518 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1 equ 0291h ;# 
# 4525 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1L equ 0291h ;# 
# 4545 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1H equ 0292h ;# 
# 4565 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP1CON equ 0293h ;# 
# 4647 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM1CON equ 0294h ;# 
# 4709 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP1AS equ 0295h ;# 
# 4714 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP1AS equ 0295h ;# 
# 4831 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR1CON equ 0296h ;# 
# 4875 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2 equ 0298h ;# 
# 4882 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2L equ 0298h ;# 
# 4902 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2H equ 0299h ;# 
# 4922 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP2CON equ 029Ah ;# 
# 5004 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM2CON equ 029Bh ;# 
# 5066 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP2AS equ 029Ch ;# 
# 5071 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP2AS equ 029Ch ;# 
# 5188 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR2CON equ 029Dh ;# 
# 5232 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPTMRS0 equ 029Eh ;# 
# 5320 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPTMRS1 equ 029Fh ;# 
# 5354 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3 equ 0311h ;# 
# 5361 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3L equ 0311h ;# 
# 5381 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3H equ 0312h ;# 
# 5401 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP3CON equ 0313h ;# 
# 5483 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM3CON equ 0314h ;# 
# 5545 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP3AS equ 0315h ;# 
# 5550 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP3AS equ 0315h ;# 
# 5667 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR3CON equ 0316h ;# 
# 5711 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4 equ 0318h ;# 
# 5718 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4L equ 0318h ;# 
# 5738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4H equ 0319h ;# 
# 5758 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP4CON equ 031Ah ;# 
# 5822 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5 equ 031Ch ;# 
# 5829 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5L equ 031Ch ;# 
# 5849 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5H equ 031Dh ;# 
# 5869 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP5CON equ 031Eh ;# 
# 5933 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBP equ 0394h ;# 
# 6003 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBN equ 0395h ;# 
# 6073 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBF equ 0396h ;# 
# 6143 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR4 equ 0415h ;# 
# 6163 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR4 equ 0416h ;# 
# 6183 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T4CON equ 0417h ;# 
# 6254 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR6 equ 041Ch ;# 
# 6274 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR6 equ 041Dh ;# 
# 6294 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T6CON equ 041Eh ;# 
# 6365 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDCON equ 0791h ;# 
# 6436 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDPS equ 0792h ;# 
# 6506 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDREF equ 0793h ;# 
# 6558 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDCST equ 0794h ;# 
# 6598 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDRL equ 0795h ;# 
# 6676 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE0 equ 0798h ;# 
# 6738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE1 equ 0799h ;# 
# 6800 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE2 equ 079Ah ;# 
# 6862 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA0 equ 07A0h ;# 
# 6924 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA1 equ 07A1h ;# 
# 6986 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA2 equ 07A2h ;# 
# 7048 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA3 equ 07A3h ;# 
# 7110 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA4 equ 07A4h ;# 
# 7172 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA5 equ 07A5h ;# 
# 7234 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA6 equ 07A6h ;# 
# 7296 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA7 equ 07A7h ;# 
# 7358 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA8 equ 07A8h ;# 
# 7420 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA9 equ 07A9h ;# 
# 7482 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA10 equ 07AAh ;# 
# 7544 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA11 equ 07ABh ;# 
# 7606 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STATUS_SHAD equ 0FE4h ;# 
# 7638 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WREG_SHAD equ 0FE5h ;# 
# 7658 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BSR_SHAD equ 0FE6h ;# 
# 7678 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCLATH_SHAD equ 0FE7h ;# 
# 7698 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0L_SHAD equ 0FE8h ;# 
# 7718 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0H_SHAD equ 0FE9h ;# 
# 7738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1L_SHAD equ 0FEAh ;# 
# 7758 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1H_SHAD equ 0FEBh ;# 
# 7778 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STKPTR equ 0FEDh ;# 
# 7798 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TOSL equ 0FEEh ;# 
# 7818 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TOSH equ 0FEFh ;# 
# 54 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INDF0 equ 00h ;# 
# 74 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INDF1 equ 01h ;# 
# 94 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCL equ 02h ;# 
# 114 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STATUS equ 03h ;# 
# 177 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0L equ 04h ;# 
# 197 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0H equ 05h ;# 
# 221 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1L equ 06h ;# 
# 241 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1H equ 07h ;# 
# 261 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BSR equ 08h ;# 
# 313 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WREG equ 09h ;# 
# 333 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCLATH equ 0Ah ;# 
# 353 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
INTCON equ 0Bh ;# 
# 431 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTA equ 0Ch ;# 
# 493 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTB equ 0Dh ;# 
# 555 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTC equ 0Eh ;# 
# 617 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTD equ 0Fh ;# 
# 679 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PORTE equ 010h ;# 
# 717 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR1 equ 011h ;# 
# 779 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR2 equ 012h ;# 
# 836 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIR3 equ 013h ;# 
# 882 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR0 equ 015h ;# 
# 902 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1 equ 016h ;# 
# 909 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1L equ 016h ;# 
# 929 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR1H equ 017h ;# 
# 949 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T1CON equ 018h ;# 
# 1021 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T1GCON equ 019h ;# 
# 1098 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR2 equ 01Ah ;# 
# 1118 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR2 equ 01Bh ;# 
# 1138 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T2CON equ 01Ch ;# 
# 1209 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CPSCON0 equ 01Eh ;# 
# 1263 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CPSCON1 equ 01Fh ;# 
# 1309 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISA equ 08Ch ;# 
# 1371 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISB equ 08Dh ;# 
# 1433 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISC equ 08Eh ;# 
# 1495 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISD equ 08Fh ;# 
# 1557 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TRISE equ 090h ;# 
# 1595 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE1 equ 091h ;# 
# 1657 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE2 equ 092h ;# 
# 1714 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PIE3 equ 093h ;# 
# 1760 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OPTION_REG equ 095h ;# 
# 1843 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCON equ 096h ;# 
# 1894 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WDTCON equ 097h ;# 
# 1953 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCTUNE equ 098h ;# 
# 2011 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCCON equ 099h ;# 
# 2083 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
OSCSTAT equ 09Ah ;# 
# 2145 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRES equ 09Bh ;# 
# 2152 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRESL equ 09Bh ;# 
# 2172 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADRESH equ 09Ch ;# 
# 2192 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADCON0 equ 09Dh ;# 
# 2281 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ADCON1 equ 09Eh ;# 
# 2353 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATA equ 010Ch ;# 
# 2415 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATB equ 010Dh ;# 
# 2477 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATC equ 010Eh ;# 
# 2539 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATD equ 010Fh ;# 
# 2609 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LATE equ 0110h ;# 
# 2647 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM1CON0 equ 0111h ;# 
# 2704 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM1CON1 equ 0112h ;# 
# 2770 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM2CON0 equ 0113h ;# 
# 2827 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CM2CON1 equ 0114h ;# 
# 2893 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CMOUT equ 0115h ;# 
# 2919 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BORCON equ 0116h ;# 
# 2946 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FVRCON equ 0117h ;# 
# 3022 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
DACCON0 equ 0118h ;# 
# 3083 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
DACCON1 equ 0119h ;# 
# 3135 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SRCON0 equ 011Ah ;# 
# 3206 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SRCON1 equ 011Bh ;# 
# 3268 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
APFCON equ 011Dh ;# 
# 3324 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELA equ 018Ch ;# 
# 3382 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELB equ 018Dh ;# 
# 3440 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELD equ 018Fh ;# 
# 3510 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ANSELE equ 0190h ;# 
# 3550 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADR equ 0191h ;# 
# 3557 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADRL equ 0191h ;# 
# 3577 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEADRH equ 0192h ;# 
# 3597 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDAT equ 0193h ;# 
# 3604 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATL equ 0193h ;# 
# 3609 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATA equ 0193h ;# 
# 3642 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EEDATH equ 0194h ;# 
# 3662 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EECON1 equ 0195h ;# 
# 3724 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
EECON2 equ 0196h ;# 
# 3744 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
RCREG equ 0199h ;# 
# 3764 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TXREG equ 019Ah ;# 
# 3784 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRG equ 019Bh ;# 
# 3791 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRGL equ 019Bh ;# 
# 3796 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRG equ 019Bh ;# 
# 3800 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRGL equ 019Bh ;# 
# 3845 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SP1BRGH equ 019Ch ;# 
# 3850 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SPBRGH equ 019Ch ;# 
# 3883 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
RCSTA equ 019Dh ;# 
# 3945 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TXSTA equ 019Eh ;# 
# 4007 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BAUDCON equ 019Fh ;# 
# 4059 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WPUB equ 020Dh ;# 
# 4129 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WPUE equ 0210h ;# 
# 4150 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPBUF equ 0211h ;# 
# 4170 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPADD equ 0212h ;# 
# 4190 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPMSK equ 0213h ;# 
# 4210 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPSTAT equ 0214h ;# 
# 4272 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON1 equ 0215h ;# 
# 4277 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON equ 0215h ;# 
# 4394 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON2 equ 0216h ;# 
# 4456 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
SSPCON3 equ 0217h ;# 
# 4518 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1 equ 0291h ;# 
# 4525 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1L equ 0291h ;# 
# 4545 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR1H equ 0292h ;# 
# 4565 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP1CON equ 0293h ;# 
# 4647 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM1CON equ 0294h ;# 
# 4709 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP1AS equ 0295h ;# 
# 4714 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP1AS equ 0295h ;# 
# 4831 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR1CON equ 0296h ;# 
# 4875 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2 equ 0298h ;# 
# 4882 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2L equ 0298h ;# 
# 4902 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR2H equ 0299h ;# 
# 4922 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP2CON equ 029Ah ;# 
# 5004 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM2CON equ 029Bh ;# 
# 5066 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP2AS equ 029Ch ;# 
# 5071 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP2AS equ 029Ch ;# 
# 5188 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR2CON equ 029Dh ;# 
# 5232 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPTMRS0 equ 029Eh ;# 
# 5320 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPTMRS1 equ 029Fh ;# 
# 5354 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3 equ 0311h ;# 
# 5361 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3L equ 0311h ;# 
# 5381 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR3H equ 0312h ;# 
# 5401 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP3CON equ 0313h ;# 
# 5483 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PWM3CON equ 0314h ;# 
# 5545 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP3AS equ 0315h ;# 
# 5550 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
ECCP3AS equ 0315h ;# 
# 5667 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PSTR3CON equ 0316h ;# 
# 5711 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4 equ 0318h ;# 
# 5718 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4L equ 0318h ;# 
# 5738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR4H equ 0319h ;# 
# 5758 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP4CON equ 031Ah ;# 
# 5822 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5 equ 031Ch ;# 
# 5829 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5L equ 031Ch ;# 
# 5849 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCPR5H equ 031Dh ;# 
# 5869 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
CCP5CON equ 031Eh ;# 
# 5933 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBP equ 0394h ;# 
# 6003 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBN equ 0395h ;# 
# 6073 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
IOCBF equ 0396h ;# 
# 6143 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR4 equ 0415h ;# 
# 6163 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR4 equ 0416h ;# 
# 6183 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T4CON equ 0417h ;# 
# 6254 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TMR6 equ 041Ch ;# 
# 6274 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PR6 equ 041Dh ;# 
# 6294 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
T6CON equ 041Eh ;# 
# 6365 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDCON equ 0791h ;# 
# 6436 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDPS equ 0792h ;# 
# 6506 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDREF equ 0793h ;# 
# 6558 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDCST equ 0794h ;# 
# 6598 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDRL equ 0795h ;# 
# 6676 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE0 equ 0798h ;# 
# 6738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE1 equ 0799h ;# 
# 6800 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDSE2 equ 079Ah ;# 
# 6862 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA0 equ 07A0h ;# 
# 6924 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA1 equ 07A1h ;# 
# 6986 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA2 equ 07A2h ;# 
# 7048 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA3 equ 07A3h ;# 
# 7110 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA4 equ 07A4h ;# 
# 7172 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA5 equ 07A5h ;# 
# 7234 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA6 equ 07A6h ;# 
# 7296 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA7 equ 07A7h ;# 
# 7358 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA8 equ 07A8h ;# 
# 7420 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA9 equ 07A9h ;# 
# 7482 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA10 equ 07AAh ;# 
# 7544 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
LCDDATA11 equ 07ABh ;# 
# 7606 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STATUS_SHAD equ 0FE4h ;# 
# 7638 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
WREG_SHAD equ 0FE5h ;# 
# 7658 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
BSR_SHAD equ 0FE6h ;# 
# 7678 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
PCLATH_SHAD equ 0FE7h ;# 
# 7698 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0L_SHAD equ 0FE8h ;# 
# 7718 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR0H_SHAD equ 0FE9h ;# 
# 7738 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1L_SHAD equ 0FEAh ;# 
# 7758 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
FSR1H_SHAD equ 0FEBh ;# 
# 7778 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
STKPTR equ 0FEDh ;# 
# 7798 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TOSL equ 0FEEh ;# 
# 7818 "D:\Dev\FlowcodeV9\Compilers\PICv2\picv2\pic\include\pic16f1937.h"
TOSH equ 0FEFh ;# 
	FNCALL	_main,_FCM_Ev_Initialise
	FNCALL	_main,_FCM_Initialise
	FNCALL	_main,_FCM_PingServo
	FNCALL	_FCM_PingServo,_FCM_Prv_ReceiveResponse
	FNCALL	_FCM_PingServo,_FCM_Prv_SendPacket
	FNCALL	_FCM_Prv_SendPacket,_FCD_01211_CircularBuffer1__FlushBuffer
	FNCALL	_FCM_Prv_SendPacket,_FCM_Prv_CalculateChecksum
	FNCALL	_FCM_Prv_SendPacket,_FC_CAL_UART_Send_1
	FNCALL	_FCM_Prv_ReceiveResponse,_FCD_01211_CircularBuffer1__GetByte
	FNCALL	_FCM_Prv_ReceiveResponse,_FCD_01211_CircularBuffer1__GetNumberBytes
	FNCALL	_FCM_Prv_ReceiveResponse,_delay_ms
	FNCALL	_FCM_Initialise,_FC_CAL_UART_Init_1
	FNROOT	_main
	FNCALL	_myisr,_FCD_01211_CircularBuffer1__PutByte
	FNCALL	_myisr,_FC_CAL_UART_Receive_1
	FNCALL	intlevel1,_myisr
	global	intlevel1
	FNROOT	intlevel1
	global	_FCV_RESPONSEBUFFER
	global	_FCV_05481_cal_uart__CONSOLE
	global	_FCV_01211_CircularBuffer1__DATASTART
	global	_FCV_01211_CircularBuffer1__DATAEND
	global	_FCV_RESPONSELENGTH
	global	_FCV_05481_cal_uart__RS485_STATE
	global	_FCV_01211_CircularBuffer1__LOOKFORCOUNTER
	global	_FCV_01211_CircularBuffer1__DATA
	global	_FCV_PACKETBUFFER
	global	_PIR1bits
_PIR1bits	set	0x11
	global	_INTCONbits
_INTCONbits	set	0xB
	global	_OPTION_REG
_OPTION_REG	set	0x95
	global	_PIE1bits
_PIE1bits	set	0x91
	global	_ANSELE
_ANSELE	set	0x190
	global	_ANSELD
_ANSELD	set	0x18F
	global	_ANSELB
_ANSELB	set	0x18D
	global	_ANSELA
_ANSELA	set	0x18C
	global	_RCREG
_RCREG	set	0x199
	global	_TXREG
_TXREG	set	0x19A
	global	_RCSTAbits
_RCSTAbits	set	0x19D
	global	_RCSTA
_RCSTA	set	0x19D
	global	_SPBRG
_SPBRG	set	0x19B
	global	_TXSTAbits
_TXSTAbits	set	0x19E
psect	stringtext1,class=STRCODE,delta=2,noexec
global __pstringtext1
__pstringtext1:
	
STR_8:	
	retlw	10
	retlw	10
	retlw	125	;'}'
	retlw	10
	retlw	10
	retlw	77	;'M'
	retlw	88	;'X'
	retlw	95	;'_'
	retlw	85	;'U'
	retlw	65	;'A'
	retlw	82	;'R'
	retlw	84	;'T'
	retlw	95	;'_'
	retlw	73	;'I'
	retlw	78	;'N'
	retlw	84	;'T'
	retlw	95	;'_'
	retlw	70	;'F'
	retlw	85	;'U'
	retlw	78	;'N'
	retlw	67	;'C'
	retlw	95	;'_'
	retlw	69	;'E'
	retlw	78	;'N'
	retlw	68	;'D'
	retlw	10
	retlw	0
psect	stringtext2,class=STRCODE,delta=2,noexec
global __pstringtext2
__pstringtext2:
	
STR_3:	
	retlw	77	;'M'
	retlw	88	;'X'
	retlw	95	;'_'
	retlw	85	;'U'
	retlw	73	;'I'
	retlw	78	;'N'
	retlw	84	;'T'
	retlw	56	;'8'
	retlw	32	;' '
	retlw	70	;'F'
	retlw	67	;'C'
	retlw	76	;'L'
	retlw	95	;'_'
	retlw	82	;'R'
	retlw	88	;'X'
	retlw	59	;';'
	retlw	10
	retlw	10
	retlw	0
psect	stringtext3,class=STRCODE,delta=2,noexec
global __pstringtext3
__pstringtext3:
	
STR_4:	
	retlw	105	;'i'
	retlw	102	;'f'
	retlw	32	;' '
	retlw	40	;'('
	retlw	77	;'M'
	retlw	88	;'X'
	retlw	95	;'_'
	retlw	85	;'U'
	retlw	65	;'A'
	retlw	82	;'R'
	retlw	84	;'T'
	retlw	95	;'_'
	retlw	73	;'I'
	retlw	78	;'N'
	retlw	84	;'T'
	retlw	95	;'_'
	retlw	67	;'C'
	retlw	72	;'H'
	retlw	0
psect	stringtext4,class=STRCODE,delta=2,noexec
global __pstringtext4
__pstringtext4:
	
STR_5:	
	retlw	95	;'_'
	retlw	68	;'D'
	retlw	69	;'E'
	retlw	84	;'T'
	retlw	41	;')'
	retlw	10
	retlw	123	;'{'
	retlw	10
	retlw	10
	retlw	0
psect	stringtext5,class=STRCODE,delta=2,noexec
global __pstringtext5
__pstringtext5:
	
STR_2:	
	retlw	95	;'_'
	retlw	70	;'F'
	retlw	85	;'U'
	retlw	78	;'N'
	retlw	67	;'C'
	retlw	10
	retlw	10
	retlw	0
psect	stringtext6,class=STRCODE,delta=2,noexec
global __pstringtext6
__pstringtext6:
	
STR_7:	
	retlw	95	;'_'
	retlw	67	;'C'
	retlw	76	;'L'
	retlw	82	;'R'
	retlw	59	;';'
	retlw	0
psect	stringtext7,class=STRCODE,delta=2,noexec
global __pstringtext7
__pstringtext7:
STR_1	equ	STR_4+4
STR_6	equ	STR_4+4
STR_9	equ	STR_3+16
; #config settings
global __CFG_FOSC$HS
__CFG_FOSC$HS equ 0x0
global __CFG_WDTE$OFF
__CFG_WDTE$OFF equ 0x0
global __CFG_PWRTE$OFF
__CFG_PWRTE$OFF equ 0x0
global __CFG_MCLRE$ON
__CFG_MCLRE$ON equ 0x0
global __CFG_CP$OFF
__CFG_CP$OFF equ 0x0
global __CFG_CPD$OFF
__CFG_CPD$OFF equ 0x0
global __CFG_BOREN$ON
__CFG_BOREN$ON equ 0x0
global __CFG_CLKOUTEN$OFF
__CFG_CLKOUTEN$OFF equ 0x0
global __CFG_IESO$OFF
__CFG_IESO$OFF equ 0x0
global __CFG_FCMEN$OFF
__CFG_FCMEN$OFF equ 0x0
global __CFG_WRT$OFF
__CFG_WRT$OFF equ 0x0
global __CFG_VCAPEN$OFF
__CFG_VCAPEN$OFF equ 0x0
global __CFG_PLLEN$OFF
__CFG_PLLEN$OFF equ 0x0
global __CFG_STVREN$ON
__CFG_STVREN$ON equ 0x0
global __CFG_BORV$LO
__CFG_BORV$LO equ 0x0
global __CFG_LVP$OFF
__CFG_LVP$OFF equ 0x0
	file	"ST3215.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

global __initialization
__initialization:
psect	bssBANK0,class=BANK0,space=1,noexec
global __pbssBANK0
__pbssBANK0:
_FCV_RESPONSEBUFFER:
       ds      20

_FCV_05481_cal_uart__CONSOLE:
       ds      4

_MX_Conv_Var:
       ds      4

_FCLV_LOOP2:
       ds      4

_FCLV_LOOP1:
       ds      4

_errno:
       ds      2

_FCV_01211_CircularBuffer1__DATASTART:
       ds      2

_FCV_01211_CircularBuffer1__DATAEND:
       ds      2

_FCI_TMP_INT:
       ds      2

_FCV_RESPONSELENGTH:
       ds      1

_FCV_05481_cal_uart__RS485_STATE:
       ds      1

_FCV_01211_CircularBuffer1__LOOKFORCOUNTER:
       ds      1

psect	bssBANK1,class=BANK1,space=1,noexec
global __pbssBANK1
__pbssBANK1:
_FCV_01211_CircularBuffer1__DATA:
       ds      32

FCM_Ev_AddInterrupts@F3931:
       ds      20

_FCV_PACKETBUFFER:
       ds      20

psect	bssBANK2,class=BANK2,space=1,noexec
global __pbssBANK2
__pbssBANK2:
FCM_Ev_Property@F3971:
       ds      20

FCM_Ev_AddInterrupts@F3933:
       ds      20

	file	"ST3215.as"
	line	#
psect clrtext,class=CODE,delta=2
global clear_ram0
;	Called with FSR0 containing the base address, and
;	WREG with the size to clear
clear_ram0:
	clrwdt			;clear the watchdog before getting into this loop
clrloop0:
	clrf	indf0		;clear RAM location pointed to by FSR
	addfsr	0,1
	decfsz wreg		;Have we reached the end of clearing yet?
	goto clrloop0	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2,merge=1
	global __pbssBANK0
	movlw	low(__pbssBANK0)
	movwf	fsr0l
	movlw	high(__pbssBANK0)
	movwf	fsr0h
	movlw	02Fh
	fcall	clear_ram0
; Clear objects allocated to BANK1
psect cinit,class=CODE,delta=2,merge=1
	global __pbssBANK1
	movlw	low(__pbssBANK1)
	movwf	fsr0l
	movlw	high(__pbssBANK1)
	movwf	fsr0h
	movlw	048h
	fcall	clear_ram0
; Clear objects allocated to BANK2
psect cinit,class=CODE,delta=2,merge=1
	global __pbssBANK2
	movlw	low(__pbssBANK2)
	movwf	fsr0l
	movlw	high(__pbssBANK2)
	movwf	fsr0h
	movlw	028h
	fcall	clear_ram0
psect cinit,class=CODE,delta=2,merge=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
	bcf int$flags,0 ;clear compiler interrupt flag (level 1)
movlb 0
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1,noexec
global __pcstackCOMMON
__pcstackCOMMON:
?_FCD_01211_CircularBuffer1__PutByte:	; 1 bytes @ 0x0
??_FCD_01211_CircularBuffer1__PutByte:	; 1 bytes @ 0x0
?_FCM_PingServo:	; 1 bytes @ 0x0
?_delay_ms:	; 1 bytes @ 0x0
?_FC_CAL_UART_Init_1:	; 1 bytes @ 0x0
?_FCD_01211_CircularBuffer1__FlushBuffer:	; 1 bytes @ 0x0
?_FCM_Initialise:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
?_myisr:	; 1 bytes @ 0x0
	global	?_FC_CAL_UART_Receive_1
?_FC_CAL_UART_Receive_1:	; 2 bytes @ 0x0
?_FCM_Ev_Initialise:	; 4 bytes @ 0x0
	ds	2
??_FC_CAL_UART_Receive_1:	; 1 bytes @ 0x2
	global	FCD_01211_CircularBuffer1__PutByte@FCL_DATA
FCD_01211_CircularBuffer1__PutByte@FCL_DATA:	; 1 bytes @ 0x2
	ds	1
	global	FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2
FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2:	; 2 bytes @ 0x3
	ds	1
	global	FC_CAL_UART_Receive_1@dummy
FC_CAL_UART_Receive_1@dummy:	; 1 bytes @ 0x4
	ds	1
	global	FC_CAL_UART_Receive_1@bWaitForever
FC_CAL_UART_Receive_1@bWaitForever:	; 1 bytes @ 0x5
	global	FCD_01211_CircularBuffer1__PutByte@FCL_TEMP
FCD_01211_CircularBuffer1__PutByte@FCL_TEMP:	; 2 bytes @ 0x5
	ds	1
	global	FC_CAL_UART_Receive_1@delaycnt
FC_CAL_UART_Receive_1@delaycnt:	; 2 bytes @ 0x6
	ds	2
	global	FC_CAL_UART_Receive_1@delay1
FC_CAL_UART_Receive_1@delay1:	; 1 bytes @ 0x8
	ds	1
	global	FC_CAL_UART_Receive_1@rxStatus
FC_CAL_UART_Receive_1@rxStatus:	; 1 bytes @ 0x9
	ds	1
	global	FC_CAL_UART_Receive_1@retVal
FC_CAL_UART_Receive_1@retVal:	; 2 bytes @ 0xA
	ds	2
	global	FC_CAL_UART_Receive_1@nTimeout
FC_CAL_UART_Receive_1@nTimeout:	; 1 bytes @ 0xC
	ds	1
	global	FC_CAL_UART_Receive_1@regcheck
FC_CAL_UART_Receive_1@regcheck:	; 1 bytes @ 0xD
	ds	1
psect	cstackBANK0,class=BANK0,space=1,noexec
global __pcstackBANK0
__pcstackBANK0:
??_myisr:	; 1 bytes @ 0x0
	ds	1
	global	myisr@FCL_RX
myisr@FCL_RX:	; 1 bytes @ 0x1
	ds	1
?_FCM_Prv_CalculateChecksum:	; 1 bytes @ 0x2
??_delay_ms:	; 1 bytes @ 0x2
??_FC_CAL_UART_Init_1:	; 1 bytes @ 0x2
?_FC_CAL_UART_Send_1:	; 1 bytes @ 0x2
??_FCD_01211_CircularBuffer1__FlushBuffer:	; 1 bytes @ 0x2
??_FCM_Ev_Initialise:	; 1 bytes @ 0x2
??_FCM_Initialise:	; 1 bytes @ 0x2
	global	?_FCD_01211_CircularBuffer1__GetNumberBytes
?_FCD_01211_CircularBuffer1__GetNumberBytes:	; 2 bytes @ 0x2
	global	?_FCD_01211_CircularBuffer1__GetByte
?_FCD_01211_CircularBuffer1__GetByte:	; 2 bytes @ 0x2
	global	FCM_Prv_CalculateChecksum@FCL_LENGTH
FCM_Prv_CalculateChecksum@FCL_LENGTH:	; 1 bytes @ 0x2
	global	FC_CAL_UART_Send_1@nChar
FC_CAL_UART_Send_1@nChar:	; 2 bytes @ 0x2
	global	FCM_Ev_Initialise@FCR_RETVAL
FCM_Ev_Initialise@FCR_RETVAL:	; 4 bytes @ 0x2
	ds	1
	global	delay_ms@del
delay_ms@del:	; 1 bytes @ 0x3
	global	FCM_Prv_CalculateChecksum@FCL_INSTRUCTION
FCM_Prv_CalculateChecksum@FCL_INSTRUCTION:	; 1 bytes @ 0x3
	ds	1
??_FCD_01211_CircularBuffer1__GetNumberBytes:	; 1 bytes @ 0x4
??_FCD_01211_CircularBuffer1__GetByte:	; 1 bytes @ 0x4
??_FC_CAL_UART_Send_1:	; 1 bytes @ 0x4
	global	FCM_Prv_CalculateChecksum@FCL_PARAMCOUNT
FCM_Prv_CalculateChecksum@FCL_PARAMCOUNT:	; 1 bytes @ 0x4
	ds	1
??_FCM_Prv_CalculateChecksum:	; 1 bytes @ 0x5
	ds	1
	global	FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL
FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL:	; 2 bytes @ 0x6
	global	FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL
FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL:	; 2 bytes @ 0x6
	ds	2
	global	FCD_01211_CircularBuffer1__GetByte@FCL_TEMP
FCD_01211_CircularBuffer1__GetByte@FCL_TEMP:	; 2 bytes @ 0x8
	ds	1
	global	FCM_Prv_CalculateChecksum@FCL_PACKETID
FCM_Prv_CalculateChecksum@FCL_PACKETID:	; 1 bytes @ 0x9
	ds	1
?_FCM_Prv_ReceiveResponse:	; 1 bytes @ 0xA
	global	FCM_Prv_CalculateChecksum@FCR_RETVAL
FCM_Prv_CalculateChecksum@FCR_RETVAL:	; 1 bytes @ 0xA
	global	FCM_Prv_ReceiveResponse@FCL_TIMEOUT
FCM_Prv_ReceiveResponse@FCL_TIMEOUT:	; 2 bytes @ 0xA
	ds	1
	global	FCM_Prv_CalculateChecksum@FCL_SUM
FCM_Prv_CalculateChecksum@FCL_SUM:	; 2 bytes @ 0xB
	ds	1
??_FCM_Prv_ReceiveResponse:	; 1 bytes @ 0xC
	ds	1
	global	FCM_Prv_ReceiveResponse@FCR_RETVAL
FCM_Prv_ReceiveResponse@FCR_RETVAL:	; 1 bytes @ 0xD
	global	FCM_Prv_CalculateChecksum@FCL_IDX
FCM_Prv_CalculateChecksum@FCL_IDX:	; 1 bytes @ 0xD
	ds	1
?_FCM_Prv_SendPacket:	; 1 bytes @ 0xE
	global	FCM_Prv_ReceiveResponse@FCL_HEADER1
FCM_Prv_ReceiveResponse@FCL_HEADER1:	; 1 bytes @ 0xE
	global	FCM_Prv_SendPacket@FCL_INSTRUCTION
FCM_Prv_SendPacket@FCL_INSTRUCTION:	; 1 bytes @ 0xE
	ds	1
	global	FCM_Prv_ReceiveResponse@FCL_HEADER2
FCM_Prv_ReceiveResponse@FCL_HEADER2:	; 1 bytes @ 0xF
	global	FCM_Prv_SendPacket@FCL_PARAMCOUNT
FCM_Prv_SendPacket@FCL_PARAMCOUNT:	; 1 bytes @ 0xF
	ds	1
??_FCM_Prv_SendPacket:	; 1 bytes @ 0x10
	global	FCM_Prv_ReceiveResponse@FCL_IDX
FCM_Prv_ReceiveResponse@FCL_IDX:	; 1 bytes @ 0x10
	ds	1
	global	FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT
FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT:	; 2 bytes @ 0x11
	ds	4
	global	FCM_Prv_SendPacket@FCL_CHECKSUM
FCM_Prv_SendPacket@FCL_CHECKSUM:	; 1 bytes @ 0x15
	ds	1
	global	FCM_Prv_SendPacket@FCL_SERVOID
FCM_Prv_SendPacket@FCL_SERVOID:	; 1 bytes @ 0x16
	ds	1
	global	FCM_Prv_SendPacket@FCL_LENGTH
FCM_Prv_SendPacket@FCL_LENGTH:	; 1 bytes @ 0x17
	ds	1
	global	FCM_Prv_SendPacket@FCL_IDX
FCM_Prv_SendPacket@FCL_IDX:	; 1 bytes @ 0x18
	ds	1
??_FCM_PingServo:	; 1 bytes @ 0x19
	ds	1
	global	FCM_PingServo@FCL_SERVOID
FCM_PingServo@FCL_SERVOID:	; 1 bytes @ 0x1A
	ds	1
	global	FCM_PingServo@FCR_RETVAL
FCM_PingServo@FCR_RETVAL:	; 1 bytes @ 0x1B
	ds	1
??_main:	; 1 bytes @ 0x1C
;!
;!Data Sizes:
;!    Strings     89
;!    Constant    0
;!    Data        0
;!    BSS         159
;!    Persistent  32
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMMON           14     14      14
;!    BANK0            80     30      77
;!    BANK1            80      0      72
;!    BANK2            80      0      40
;!    BANK3            80      0       0
;!    BANK4            80      0       0
;!    BANK5            80      0       0
;!    BANK6            16      0       0

;!
;!Pointer List with Targets:
;!
;!    sp__FCI_NUMBER_TO_HEX	PTR unsigned char  size(1) Largest target is 0
;!
;!    sp__FCI_FLOAT_TO_STRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCI_FLOATTOFORMATTEDSTRING@sTemp(BANK0[20]), FCI_IMPLODEFROMFLOATARRAY@sTemp(BANK0[20]), 
;!
;!    sp__FCI_TOSTRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_05481_cal_uart__SendNumber@FCL_NUMSTR(BANK0[20]), FCI_INTTOFORMATTEDSTRING@sTemp(BANK0[20]), FCI_IMPLODEFROMINTARRAY@sTemp(BANK0[20]), 
;!
;!    sp__FCI_RIGHTSTRING	PTR unsigned char  size(1) Largest target is 0
;!
;!    sp__FCI_LEFTSTRING	PTR unsigned char  size(1) Largest target is 0
;!
;!    sp__FCI_MIDSTRING	PTR unsigned char  size(1) Largest target is 0
;!


;!
;!Critical Paths under _main in COMMON
;!
;!    None.
;!
;!Critical Paths under _myisr in COMMON
;!
;!    _myisr->_FC_CAL_UART_Receive_1
;!
;!Critical Paths under _main in BANK0
;!
;!    _main->_FCM_PingServo
;!    _FCM_PingServo->_FCM_Prv_SendPacket
;!    _FCM_Prv_SendPacket->_FCM_Prv_CalculateChecksum
;!    _FCM_Prv_ReceiveResponse->_FCD_01211_CircularBuffer1__GetByte
;!
;!Critical Paths under _myisr in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK6
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 2     2      0    7022
;!                                             28 BANK0      2     2      0
;!                  _FCM_Ev_Initialise
;!                     _FCM_Initialise
;!                      _FCM_PingServo
;! ---------------------------------------------------------------------------------
;! (1) _FCM_PingServo                                        3     3      0    6991
;!                                             25 BANK0      3     3      0
;!            _FCM_Prv_ReceiveResponse
;!                 _FCM_Prv_SendPacket
;! ---------------------------------------------------------------------------------
;! (2) _FCM_Prv_SendPacket                                  11     9      2    5003
;!                                             14 BANK0     11     9      2
;!_FCD_01211_CircularBuffer1__FlushBuf
;!          _FCM_Prv_CalculateChecksum
;!                 _FC_CAL_UART_Send_1
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_UART_Send_1                                   2     0      2     680
;!                                              2 BANK0      2     0      2
;! ---------------------------------------------------------------------------------
;! (3) _FCM_Prv_CalculateChecksum                           12     9      3     454
;!                                              2 BANK0     12     9      3
;! ---------------------------------------------------------------------------------
;! (3) _FCD_01211_CircularBuffer1__FlushBuffer               0     0      0       0
;! ---------------------------------------------------------------------------------
;! (2) _FCM_Prv_ReceiveResponse                              9     7      2    1943
;!                                             10 BANK0      9     7      2
;! _FCD_01211_CircularBuffer1__GetByte
;!_FCD_01211_CircularBuffer1__GetNumbe
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (3) _delay_ms                                             2     2      0      22
;!                                              2 BANK0      2     2      0
;! ---------------------------------------------------------------------------------
;! (3) _FCD_01211_CircularBuffer1__GetNumberBytes            6     4      2      25
;!                                              2 BANK0      6     4      2
;! ---------------------------------------------------------------------------------
;! (3) _FCD_01211_CircularBuffer1__GetByte                   8     6      2      70
;!                                              2 BANK0      8     6      2
;! ---------------------------------------------------------------------------------
;! (1) _FCM_Initialise                                       0     0      0       0
;!                 _FC_CAL_UART_Init_1
;! ---------------------------------------------------------------------------------
;! (2) _FC_CAL_UART_Init_1                                   0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _FCM_Ev_Initialise                                    4     4      0       6
;!                                              2 BANK0      4     4      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 3
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (4) _myisr                                                2     2      0     563
;!                                              0 BANK0      2     2      0
;! _FCD_01211_CircularBuffer1__PutByte
;!              _FC_CAL_UART_Receive_1
;! ---------------------------------------------------------------------------------
;! (5) _FC_CAL_UART_Receive_1                               14    12      2     352
;!                                              0 COMMON    14    12      2
;! ---------------------------------------------------------------------------------
;! (5) _FCD_01211_CircularBuffer1__PutByte                   7     7      0     188
;!                                              0 COMMON     7     7      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 5
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _FCM_Ev_Initialise
;!   _FCM_Initialise
;!     _FC_CAL_UART_Init_1
;!   _FCM_PingServo
;!     _FCM_Prv_ReceiveResponse
;!       _FCD_01211_CircularBuffer1__GetByte
;!       _FCD_01211_CircularBuffer1__GetNumberBytes
;!       _delay_ms
;!     _FCM_Prv_SendPacket
;!       _FCD_01211_CircularBuffer1__FlushBuffer
;!       _FCM_Prv_CalculateChecksum
;!       _FC_CAL_UART_Send_1
;!
;! _myisr (ROOT)
;!   _FCD_01211_CircularBuffer1__PutByte
;!   _FC_CAL_UART_Receive_1
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BIGRAM             1F0      0       0       0        0.0%
;!EEDATA             100      0       0       0        0.0%
;!NULL                 0      0       0       0        0.0%
;!CODE                 0      0       0       0        0.0%
;!BITCOMMON            E      0       0       1        0.0%
;!BITSFR0              0      0       0       1        0.0%
;!SFR0                 0      0       0       1        0.0%
;!COMMON               E      E       E       2      100.0%
;!BITSFR1              0      0       0       2        0.0%
;!SFR1                 0      0       0       2        0.0%
;!BITSFR2              0      0       0       3        0.0%
;!SFR2                 0      0       0       3        0.0%
;!STACK                0      0       0       3        0.0%
;!BITSFR3              0      0       0       4        0.0%
;!SFR3                 0      0       0       4        0.0%
;!ABS                  0      0      CB       4        0.0%
;!BITBANK0            50      0       0       5        0.0%
;!BITSFR4              0      0       0       5        0.0%
;!SFR4                 0      0       0       5        0.0%
;!BANK0               50     1E      4D       6       96.3%
;!BITSFR5              0      0       0       6        0.0%
;!SFR5                 0      0       0       6        0.0%
;!BITBANK1            50      0       0       7        0.0%
;!BITSFR6              0      0       0       7        0.0%
;!SFR6                 0      0       0       7        0.0%
;!BANK1               50      0      48       8       90.0%
;!BITSFR7              0      0       0       8        0.0%
;!SFR7                 0      0       0       8        0.0%
;!BITBANK2            50      0       0       9        0.0%
;!BITSFR8              0      0       0       9        0.0%
;!SFR8                 0      0       0       9        0.0%
;!BANK2               50      0      28      10       50.0%
;!BITSFR9              0      0       0      10        0.0%
;!SFR9                 0      0       0      10        0.0%
;!BITBANK3            50      0       0      11        0.0%
;!BITSFR10             0      0       0      11        0.0%
;!SFR10                0      0       0      11        0.0%
;!BANK3               50      0       0      12        0.0%
;!BITSFR11             0      0       0      12        0.0%
;!SFR11                0      0       0      12        0.0%
;!BITBANK4            50      0       0      13        0.0%
;!BITSFR12             0      0       0      13        0.0%
;!SFR12                0      0       0      13        0.0%
;!BANK4               50      0       0      14        0.0%
;!BITSFR13             0      0       0      14        0.0%
;!SFR13                0      0       0      14        0.0%
;!BITBANK5            50      0       0      15        0.0%
;!BITSFR14             0      0       0      15        0.0%
;!SFR14                0      0       0      15        0.0%
;!BANK5               50      0       0      16        0.0%
;!BITSFR15             0      0       0      16        0.0%
;!SFR15                0      0       0      16        0.0%
;!BITBANK6            10      0       0      17        0.0%
;!BITSFR16             0      0       0      17        0.0%
;!SFR16                0      0       0      17        0.0%
;!BANK6               10      0       0      18        0.0%
;!BITSFR17             0      0       0      18        0.0%
;!SFR17                0      0       0      18        0.0%
;!BITSFR18             0      0       0      19        0.0%
;!SFR18                0      0       0      19        0.0%
;!DATA                 0      0      CB      19        0.0%
;!BITSFR19             0      0       0      20        0.0%
;!SFR19                0      0       0      20        0.0%
;!BITSFR20             0      0       0      21        0.0%
;!SFR20                0      0       0      21        0.0%
;!BITSFR21             0      0       0      22        0.0%
;!SFR21                0      0       0      22        0.0%
;!BITSFR22             0      0       0      23        0.0%
;!SFR22                0      0       0      23        0.0%
;!BITSFR23             0      0       0      24        0.0%
;!SFR23                0      0       0      24        0.0%
;!BITSFR24             0      0       0      25        0.0%
;!SFR24                0      0       0      25        0.0%
;!BITSFR25             0      0       0      26        0.0%
;!SFR25                0      0       0      26        0.0%
;!BITSFR26             0      0       0      27        0.0%
;!SFR26                0      0       0      27        0.0%
;!BITSFR27             0      0       0      28        0.0%
;!SFR27                0      0       0      28        0.0%
;!BITSFR28             0      0       0      29        0.0%
;!SFR28                0      0       0      29        0.0%
;!BITSFR29             0      0       0      30        0.0%
;!SFR29                0      0       0      30        0.0%
;!BITSFR30             0      0       0      31        0.0%
;!SFR30                0      0       0      31        0.0%
;!BITSFR31             0      0       0      32        0.0%
;!SFR31                0      0       0      32        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 2636 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_TESTSERV    1    0        unsigned char 
;;  FCL_PINGRESU    1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCM_Ev_Initialise
;;		_FCM_Initialise
;;		_FCM_PingServo
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext,global,class=CODE,delta=2,merge=1,split=1,group=0
	file	"ST3215.c"
	line	2636
global __pmaintext
__pmaintext:	;psect for function _main
psect	maintext
	file	"ST3215.c"
	line	2636
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
;incstack = 0
	opt	callstack 11
; Regs used in _main: [wreg+fsr1l+fsr1h+status,2+status,0+pclath+cstack]
	line	2642
	
l2372:	
	line	2643
	
l2374:	
	line	2645
	movlb 3	; select bank3
	clrf	(396)^0180h	;volatile
	line	2646
	clrf	(397)^0180h	;volatile
	line	2647
	clrf	(399)^0180h	;volatile
	line	2648
	clrf	(400)^0180h	;volatile
	line	2650
	
l2376:	
	movlw	low(0C0h)
	movlb 1	; select bank1
	movwf	(149)^080h	;volatile
	line	2654
	
l2378:	
	fcall	_FCM_Ev_Initialise
	line	2657
	
l2380:	
	fcall	_FCM_Initialise
	line	2660
	
l2382:	
	movlw	low(01h)
	fcall	_FCM_PingServo
	line	2662
	
l1136:	
	goto	l1136
	global	start
	ljmp	start
	opt callstack 0
	line	2663
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_FCM_PingServo

;; *************** function _FCM_PingServo *****************
;; Defined at:
;;		line 2152 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;  FCL_SERVOID     1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_SERVOID     1   26[BANK0 ] unsigned char 
;;  FCR_RETVAL      1   27[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B1F/1
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0
;;      Totals:         0       3       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_FCM_Prv_ReceiveResponse
;;		_FCM_Prv_SendPacket
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,local,class=CODE,delta=2,merge=1,group=0
	line	2152
global __ptext1
__ptext1:	;psect for function _FCM_PingServo
psect	text1
	file	"ST3215.c"
	line	2152
	global	__size_of_FCM_PingServo
	__size_of_FCM_PingServo	equ	__end_of_FCM_PingServo-_FCM_PingServo
	
_FCM_PingServo:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCM_PingServo: [wreg+fsr1l+fsr1h+status,2+status,0+pclath+cstack]
	movlb 0	; select bank0
	movwf	(FCM_PingServo@FCL_SERVOID)
	line	2159
	
l2364:	
	clrf	(FCM_Prv_SendPacket@FCL_INSTRUCTION)
	incf	(FCM_Prv_SendPacket@FCL_INSTRUCTION),f
	clrf	(FCM_Prv_SendPacket@FCL_PARAMCOUNT)
	movf	(FCM_PingServo@FCL_SERVOID),w
	fcall	_FCM_Prv_SendPacket
	line	2162
	movlw	014h
	movwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUT)
	movlw	0
	movwf	((FCM_Prv_ReceiveResponse@FCL_TIMEOUT))+1
	fcall	_FCM_Prv_ReceiveResponse
	movwf	(??_FCM_PingServo+0)+0
	movf	(??_FCM_PingServo+0)+0,w
	movwf	(FCM_PingServo@FCR_RETVAL)
	line	2164
	
l2366:	
	movf	(FCM_PingServo@FCR_RETVAL),w
	line	2166
	
l1075:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_PingServo
	__end_of_FCM_PingServo:
	signat	_FCM_PingServo,4217
	global	_FCM_Prv_SendPacket

;; *************** function _FCM_Prv_SendPacket *****************
;; Defined at:
;;		line 2220 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;  FCL_SERVOID     1    wreg     unsigned char 
;;  FCL_INSTRUCT    1   14[BANK0 ] unsigned char 
;;  FCL_PARAMCOU    1   15[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_SERVOID     1   22[BANK0 ] unsigned char 
;;  FCL_IDX         1   24[BANK0 ] unsigned char 
;;  FCL_LENGTH      1   23[BANK0 ] unsigned char 
;;  FCL_CHECKSUM    1   21[BANK0 ] unsigned char 
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       2       0       0       0       0       0       0
;;      Locals:         0       5       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0
;;      Totals:         0      11       0       0       0       0       0       0
;;Total ram usage:       11 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FCD_01211_CircularBuffer1__FlushBuffer
;;		_FCM_Prv_CalculateChecksum
;;		_FC_CAL_UART_Send_1
;; This function is called by:
;;		_FCM_PingServo
;; This function uses a non-reentrant model
;;
psect	text2,local,class=CODE,delta=2,merge=1,group=0
	line	2220
global __ptext2
__ptext2:	;psect for function _FCM_Prv_SendPacket
psect	text2
	file	"ST3215.c"
	line	2220
	global	__size_of_FCM_Prv_SendPacket
	__size_of_FCM_Prv_SendPacket	equ	__end_of_FCM_Prv_SendPacket-_FCM_Prv_SendPacket
	
_FCM_Prv_SendPacket:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCM_Prv_SendPacket: [wreg+fsr1l+fsr1h+status,2+status,0+pclath+cstack]
	movwf	(FCM_Prv_SendPacket@FCL_SERVOID)
	line	2223
	
l2186:	
	line	2224
	clrf	(FCM_Prv_SendPacket@FCL_CHECKSUM)
	line	2225
	clrf	(FCM_Prv_SendPacket@FCL_IDX)
	line	2230
	
l2188:	
	movf	(FCM_Prv_SendPacket@FCL_PARAMCOUNT),w
	addlw	02h
	movwf	(??_FCM_Prv_SendPacket+0)+0
	movf	(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FCM_Prv_SendPacket@FCL_LENGTH)
	line	2233
	
l2190:	
	movf	(FCM_Prv_SendPacket@FCL_LENGTH),w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	movf	(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_LENGTH)
	movf	(FCM_Prv_SendPacket@FCL_INSTRUCTION),w
	movwf	(??_FCM_Prv_SendPacket+1)+0
	movf	(??_FCM_Prv_SendPacket+1)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_INSTRUCTION)
	movf	(FCM_Prv_SendPacket@FCL_PARAMCOUNT),w
	movwf	(??_FCM_Prv_SendPacket+2)+0
	movf	(??_FCM_Prv_SendPacket+2)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_PARAMCOUNT)
	movf	(FCM_Prv_SendPacket@FCL_SERVOID),w
	fcall	_FCM_Prv_CalculateChecksum
	movwf	(??_FCM_Prv_SendPacket+3)+0
	movf	(??_FCM_Prv_SendPacket+3)+0,w
	movwf	(FCM_Prv_SendPacket@FCL_CHECKSUM)
	line	2236
	
l2192:	
	movlw	0FFh
	movwf	(FC_CAL_UART_Send_1@nChar)
	movlw	0
	movwf	((FC_CAL_UART_Send_1@nChar))+1
	fcall	_FC_CAL_UART_Send_1
	line	2239
	
l2194:	
	movlw	0FFh
	movlb 0	; select bank0
	movwf	(FC_CAL_UART_Send_1@nChar)
	movlw	0
	movwf	((FC_CAL_UART_Send_1@nChar))+1
	fcall	_FC_CAL_UART_Send_1
	line	2242
	
l2196:	
	movlb 0	; select bank0
	movf	(FCM_Prv_SendPacket@FCL_SERVOID),w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	clrf	(??_FCM_Prv_SendPacket+0)+0+1
	movf	0+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar)
	movf	1+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar+1)
	fcall	_FC_CAL_UART_Send_1
	line	2245
	
l2198:	
	movlb 0	; select bank0
	movf	(FCM_Prv_SendPacket@FCL_LENGTH),w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	clrf	(??_FCM_Prv_SendPacket+0)+0+1
	movf	0+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar)
	movf	1+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar+1)
	fcall	_FC_CAL_UART_Send_1
	line	2248
	
l2200:	
	movlb 0	; select bank0
	movf	(FCM_Prv_SendPacket@FCL_INSTRUCTION),w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	clrf	(??_FCM_Prv_SendPacket+0)+0+1
	movf	0+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar)
	movf	1+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar+1)
	fcall	_FC_CAL_UART_Send_1
	line	2251
	goto	l2206
	line	2254
	
l2202:	
	movf	(FCM_Prv_SendPacket@FCL_IDX),w
	addlw	low(_FCV_PACKETBUFFER|((0x0)<<8))&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	clrf	(??_FCM_Prv_SendPacket+0)+0+1
	movf	0+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar)
	movf	1+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar+1)
	fcall	_FC_CAL_UART_Send_1
	line	2257
	
l2204:	
	movlb 0	; select bank0
	movf	(FCM_Prv_SendPacket@FCL_IDX),w
	addlw	01h
	movwf	(??_FCM_Prv_SendPacket+0)+0
	movf	(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FCM_Prv_SendPacket@FCL_IDX)
	line	2251
	
l2206:	
	movlb 0	; select bank0
	movf	(FCM_Prv_SendPacket@FCL_PARAMCOUNT),w
	subwf	(FCM_Prv_SendPacket@FCL_IDX),w
	skipc
	goto	u421
	goto	u420
u421:
	goto	l2202
u420:
	line	2262
	
l2208:	
	movf	(FCM_Prv_SendPacket@FCL_CHECKSUM),w
	movwf	(??_FCM_Prv_SendPacket+0)+0
	clrf	(??_FCM_Prv_SendPacket+0)+0+1
	movf	0+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar)
	movf	1+(??_FCM_Prv_SendPacket+0)+0,w
	movwf	(FC_CAL_UART_Send_1@nChar+1)
	fcall	_FC_CAL_UART_Send_1
	line	2265
	
l2210:	
	fcall	_FCD_01211_CircularBuffer1__FlushBuffer
	line	2268
	
l2212:	
	line	2270
	movlw	low(01h)
	line	2272
	
l1086:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_Prv_SendPacket
	__end_of_FCM_Prv_SendPacket:
	signat	_FCM_Prv_SendPacket,12409
	global	_FC_CAL_UART_Send_1

;; *************** function _FC_CAL_UART_Send_1 *****************
;; Defined at:
;;		line 1535 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
;; Parameters:    Size  Location     Type
;;  nChar           2    2[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/3
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       2       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_SendPacket
;; This function uses a non-reentrant model
;;
psect	text3,local,class=CODE,delta=2,merge=1,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1535
global __ptext3
__ptext3:	;psect for function _FC_CAL_UART_Send_1
psect	text3
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1535
	global	__size_of_FC_CAL_UART_Send_1
	__size_of_FC_CAL_UART_Send_1	equ	__end_of_FC_CAL_UART_Send_1-_FC_CAL_UART_Send_1
	
_FC_CAL_UART_Send_1:	
;incstack = 0
	opt	callstack 11
; Regs used in _FC_CAL_UART_Send_1: [wreg]
	line	1564
	
l2116:	
	
l697:	
	btfss	(17),4	;volatile
	goto	u361
	goto	u360
u361:
	goto	l697
u360:
	line	1572
	
l2118:	
	movf	(FC_CAL_UART_Send_1@nChar),w
	movlb 3	; select bank3
	movwf	(410)^0180h	;volatile
	line	1644
	
l700:	
	return
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Send_1
	__end_of_FC_CAL_UART_Send_1:
	signat	_FC_CAL_UART_Send_1,4217
	global	_FCM_Prv_CalculateChecksum

;; *************** function _FCM_Prv_CalculateChecksum *****************
;; Defined at:
;;		line 2550 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;  FCL_PACKETID    1    wreg     unsigned char 
;;  FCL_LENGTH      1    2[BANK0 ] unsigned char 
;;  FCL_INSTRUCT    1    3[BANK0 ] unsigned char 
;;  FCL_PARAMCOU    1    4[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_PACKETID    1    9[BANK0 ] unsigned char 
;;  FCL_SUM         2   11[BANK0 ] unsigned short 
;;  FCL_IDX         1   13[BANK0 ] unsigned char 
;;  FCR_RETVAL      1   10[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0
;; Tracked objects:
;;		On entry : B1F/0
;;		On exit  : B1F/0
;;		Unchanged: B00/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       3       0       0       0       0       0       0
;;      Locals:         0       5       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0
;;      Totals:         0      12       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_SendPacket
;; This function uses a non-reentrant model
;;
psect	text4,local,class=CODE,delta=2,merge=1,group=0
	file	"ST3215.c"
	line	2550
global __ptext4
__ptext4:	;psect for function _FCM_Prv_CalculateChecksum
psect	text4
	file	"ST3215.c"
	line	2550
	global	__size_of_FCM_Prv_CalculateChecksum
	__size_of_FCM_Prv_CalculateChecksum	equ	__end_of_FCM_Prv_CalculateChecksum-_FCM_Prv_CalculateChecksum
	
_FCM_Prv_CalculateChecksum:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCM_Prv_CalculateChecksum: [wreg+fsr1l+fsr1h+status,2+status,0]
	movwf	(FCM_Prv_CalculateChecksum@FCL_PACKETID)
	line	2553
	
l2152:	
	line	2554
	clrf	(FCM_Prv_CalculateChecksum@FCL_IDX)
	line	2559
	
l2154:	
	movf	(FCM_Prv_CalculateChecksum@FCL_INSTRUCTION),w
	movwf	(??_FCM_Prv_CalculateChecksum+0)+0
	clrf	(??_FCM_Prv_CalculateChecksum+0)+0+1
	movf	(FCM_Prv_CalculateChecksum@FCL_PACKETID),w
	addwf	(FCM_Prv_CalculateChecksum@FCL_LENGTH),w
	movwf	(??_FCM_Prv_CalculateChecksum+2)+0
	clrf	(??_FCM_Prv_CalculateChecksum+2)+0+1
	rlf	1+(??_FCM_Prv_CalculateChecksum+2)+0,f
	
	movf	0+(??_FCM_Prv_CalculateChecksum+0)+0,w
	addwf	0+(??_FCM_Prv_CalculateChecksum+2)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_SUM)
	movf	1+(??_FCM_Prv_CalculateChecksum+0)+0,w
	addwfc	1+(??_FCM_Prv_CalculateChecksum+2)+0,w
	movwf	1+(FCM_Prv_CalculateChecksum@FCL_SUM)
	line	2562
	goto	l2160
	line	2565
	
l2156:	
	movf	(FCM_Prv_CalculateChecksum@FCL_IDX),w
	addlw	low(_FCV_PACKETBUFFER|((0x0)<<8))&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	addwf	(FCM_Prv_CalculateChecksum@FCL_SUM),w
	movwf	(??_FCM_Prv_CalculateChecksum+0)+0
	movf	(FCM_Prv_CalculateChecksum@FCL_SUM+1),w
	skipnc
	incf	(FCM_Prv_CalculateChecksum@FCL_SUM+1),w
	movwf	((??_FCM_Prv_CalculateChecksum+0)+0)+1
	movf	0+(??_FCM_Prv_CalculateChecksum+0)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_SUM)
	movf	1+(??_FCM_Prv_CalculateChecksum+0)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_SUM+1)
	line	2566
	
l2158:	
	movf	(FCM_Prv_CalculateChecksum@FCL_IDX),w
	addlw	01h
	movwf	(??_FCM_Prv_CalculateChecksum+0)+0
	movf	(??_FCM_Prv_CalculateChecksum+0)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCL_IDX)
	line	2562
	
l2160:	
	movf	(FCM_Prv_CalculateChecksum@FCL_PARAMCOUNT),w
	subwf	(FCM_Prv_CalculateChecksum@FCL_IDX),w
	skipc
	goto	u411
	goto	u410
u411:
	goto	l2156
u410:
	line	2571
	
l2162:	
	comf	(FCM_Prv_CalculateChecksum@FCL_SUM),w
	movwf	(??_FCM_Prv_CalculateChecksum+0)+0
	movf	(??_FCM_Prv_CalculateChecksum+0)+0,w
	movwf	(FCM_Prv_CalculateChecksum@FCR_RETVAL)
	line	2573
	
l2164:	
	movf	(FCM_Prv_CalculateChecksum@FCR_RETVAL),w
	line	2575
	
l1123:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_Prv_CalculateChecksum
	__end_of_FCM_Prv_CalculateChecksum:
	signat	_FCM_Prv_CalculateChecksum,16505
	global	_FCD_01211_CircularBuffer1__FlushBuffer

;; *************** function _FCD_01211_CircularBuffer1__FlushBuffer *****************
;; Defined at:
;;		line 584 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		status,2
;; Tracked objects:
;;		On entry : 1F/3
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_SendPacket
;; This function uses a non-reentrant model
;;
psect	text5,local,class=CODE,delta=2,merge=1,group=0
	line	584
global __ptext5
__ptext5:	;psect for function _FCD_01211_CircularBuffer1__FlushBuffer
psect	text5
	file	"ST3215.c"
	line	584
	global	__size_of_FCD_01211_CircularBuffer1__FlushBuffer
	__size_of_FCD_01211_CircularBuffer1__FlushBuffer	equ	__end_of_FCD_01211_CircularBuffer1__FlushBuffer-_FCD_01211_CircularBuffer1__FlushBuffer
	
_FCD_01211_CircularBuffer1__FlushBuffer:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCD_01211_CircularBuffer1__FlushBuffer: [status,2]
	line	587
	
l2150:	
	movlb 0	; select bank0
	clrf	(_FCV_01211_CircularBuffer1__DATAEND)	;volatile
	clrf	(_FCV_01211_CircularBuffer1__DATAEND+1)	;volatile
	line	588
	clrf	(_FCV_01211_CircularBuffer1__DATASTART)	;volatile
	clrf	(_FCV_01211_CircularBuffer1__DATASTART+1)	;volatile
	line	590
	
l847:	
	return
	opt callstack 0
GLOBAL	__end_of_FCD_01211_CircularBuffer1__FlushBuffer
	__end_of_FCD_01211_CircularBuffer1__FlushBuffer:
	signat	_FCD_01211_CircularBuffer1__FlushBuffer,89
	global	_FCM_Prv_ReceiveResponse

;; *************** function _FCM_Prv_ReceiveResponse *****************
;; Defined at:
;;		line 1800 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;  FCL_TIMEOUT     2   10[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;  FCL_TIMEOUTC    2   17[BANK0 ] unsigned short 
;;  FCL_IDX         1   16[BANK0 ] unsigned char 
;;  FCL_HEADER2     1   15[BANK0 ] unsigned char 
;;  FCL_HEADER1     1   14[BANK0 ] unsigned char 
;;  FCR_RETVAL      1   13[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       2       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0
;;      Totals:         0       9       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FCD_01211_CircularBuffer1__GetByte
;;		_FCD_01211_CircularBuffer1__GetNumberBytes
;;		_delay_ms
;; This function is called by:
;;		_FCM_PingServo
;; This function uses a non-reentrant model
;;
psect	text6,local,class=CODE,delta=2,merge=1,group=0
	line	1800
global __ptext6
__ptext6:	;psect for function _FCM_Prv_ReceiveResponse
psect	text6
	file	"ST3215.c"
	line	1800
	global	__size_of_FCM_Prv_ReceiveResponse
	__size_of_FCM_Prv_ReceiveResponse	equ	__end_of_FCM_Prv_ReceiveResponse-_FCM_Prv_ReceiveResponse
	
_FCM_Prv_ReceiveResponse:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCM_Prv_ReceiveResponse: [wreg+fsr1l+fsr1h+status,2+status,0+pclath+cstack]
	line	1803
	
l2216:	
	clrf	(FCM_Prv_ReceiveResponse@FCL_HEADER1)
	line	1804
	clrf	(FCM_Prv_ReceiveResponse@FCL_HEADER2)
	line	1805
	clrf	(FCM_Prv_ReceiveResponse@FCL_IDX)
	line	1806
	clrf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	clrf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1)
	line	1811
	clrf	(_FCV_RESPONSELENGTH)	;volatile
	line	1812
	clrf	(FCM_Prv_ReceiveResponse@FCR_RETVAL)
	line	1815
	goto	l2226
	line	1818
	
l2218:	
	fcall	_FCD_01211_CircularBuffer1__GetNumberBytes
	movf	((0+(?_FCD_01211_CircularBuffer1__GetNumberBytes))),w
iorwf	((1+(?_FCD_01211_CircularBuffer1__GetNumberBytes))),w
	btfsc	status,2
	goto	u431
	goto	u430
u431:
	goto	l2222
u430:
	line	1822
	
l2220:	
	fcall	_FCD_01211_CircularBuffer1__GetByte
	movf	(0+(?_FCD_01211_CircularBuffer1__GetByte)),w
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	(FCM_Prv_ReceiveResponse@FCL_HEADER1)
	line	1824
	goto	l2226
	line	1827
	
l2222:	
	movlw	low(01h)
	fcall	_delay_ms
	line	1830
	
l2224:	
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT),w
	addlw	01h
	movwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	movlw	0
	addwfc	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1),w
	movwf	1+(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	line	1815
	
l2226:	
		incf	((FCM_Prv_ReceiveResponse@FCL_HEADER1)),w
	btfsc	status,2
	goto	u441
	goto	u440
u441:
	goto	l2230
u440:
	
l2228:	
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUT+1),w
	subwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1),w
	skipz
	goto	u455
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUT),w
	subwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT),w
u455:
	skipc
	goto	u451
	goto	u450
u451:
	goto	l2218
u450:
	line	1837
	
l2230:	
		incf	((FCM_Prv_ReceiveResponse@FCL_HEADER1)),w
	btfss	status,2
	goto	u461
	goto	u460
u461:
	goto	l2268
u460:
	goto	l2242
	line	1844
	
l2234:	
	fcall	_FCD_01211_CircularBuffer1__GetNumberBytes
	movlw	0
	subwf	(1+(?_FCD_01211_CircularBuffer1__GetNumberBytes)),w
	movlw	03h
	skipnz
	subwf	(0+(?_FCD_01211_CircularBuffer1__GetNumberBytes)),w
	skipc
	goto	u471
	goto	u470
u471:
	goto	l2238
u470:
	line	1848
	
l2236:	
	fcall	_FCD_01211_CircularBuffer1__GetByte
	movf	(0+(?_FCD_01211_CircularBuffer1__GetByte)),w
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	(FCM_Prv_ReceiveResponse@FCL_HEADER2)
	line	1850
	goto	l2242
	line	1853
	
l2238:	
	movlw	low(01h)
	fcall	_delay_ms
	line	1856
	
l2240:	
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT),w
	addlw	01h
	movwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	movlw	0
	addwfc	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1),w
	movwf	1+(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	line	1841
	
l2242:	
	movf	((FCM_Prv_ReceiveResponse@FCL_HEADER2)),w
	btfss	status,2
	goto	u481
	goto	u480
u481:
	goto	l2246
u480:
	
l2244:	
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUT+1),w
	subwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1),w
	skipz
	goto	u495
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUT),w
	subwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT),w
u495:
	skipc
	goto	u491
	goto	u490
u491:
	goto	l2234
u490:
	line	1863
	
l2246:	
		incf	((FCM_Prv_ReceiveResponse@FCL_HEADER2)),w
	btfss	status,2
	goto	u501
	goto	u500
u501:
	goto	l2268
u500:
	line	1867
	
l2248:	
	fcall	_FCD_01211_CircularBuffer1__GetByte
	movf	(0+(?_FCD_01211_CircularBuffer1__GetByte)),w
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	(_FCV_RESPONSEBUFFER)	;volatile
	line	1870
	fcall	_FCD_01211_CircularBuffer1__GetByte
	movf	(0+(?_FCD_01211_CircularBuffer1__GetByte)),w
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	0+(_FCV_RESPONSEBUFFER)+01h	;volatile
	line	1873
	
l2250:	
	movf	0+(_FCV_RESPONSEBUFFER)+01h,w	;volatile
	addlw	0FEh
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	(_FCV_RESPONSELENGTH)	;volatile
	line	1876
	goto	l2266
	line	1879
	
l2252:	
	fcall	_FCD_01211_CircularBuffer1__GetNumberBytes
	movlw	0
	subwf	(1+(?_FCD_01211_CircularBuffer1__GetNumberBytes)),w
	movlw	03h
	skipnz
	subwf	(0+(?_FCD_01211_CircularBuffer1__GetNumberBytes)),w
	skipc
	goto	u511
	goto	u510
u511:
	goto	l2262
u510:
	line	1883
	
l2254:	
	fcall	_FCD_01211_CircularBuffer1__GetByte
	movf	(0+(?_FCD_01211_CircularBuffer1__GetByte)),w
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(FCM_Prv_ReceiveResponse@FCL_IDX),w
	addlw	low(_FCV_RESPONSEBUFFER|((0x0)<<8)+02h)&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	indf1
	line	1886
	
l2256:	
	movf	(FCM_Prv_ReceiveResponse@FCL_IDX),w
	addlw	01h
	movwf	(??_FCM_Prv_ReceiveResponse+0)+0
	movf	(??_FCM_Prv_ReceiveResponse+0)+0,w
	movwf	(FCM_Prv_ReceiveResponse@FCL_IDX)
	line	1889
	
l2258:	
	movlw	low(012h)
	subwf	(FCM_Prv_ReceiveResponse@FCL_IDX),w
	skipc
	goto	u521
	goto	u520
u521:
	goto	l2266
u520:
	goto	l2268
	line	1902
	
l2262:	
	movlw	low(01h)
	fcall	_delay_ms
	line	1905
	
l2264:	
	movf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT),w
	addlw	01h
	movwf	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	movlw	0
	addwfc	(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT+1),w
	movwf	1+(FCM_Prv_ReceiveResponse@FCL_TIMEOUTCOUNT)
	line	1876
	
l2266:	
	movf	(_FCV_RESPONSELENGTH),w	;volatile
	subwf	(FCM_Prv_ReceiveResponse@FCL_IDX),w
	skipc
	goto	u531
	goto	u530
u531:
	goto	l2252
u530:
	
l1048:	
	line	1912
	clrf	(FCM_Prv_ReceiveResponse@FCR_RETVAL)
	incf	(FCM_Prv_ReceiveResponse@FCR_RETVAL),f
	line	1926
	
l2268:	
	movf	(FCM_Prv_ReceiveResponse@FCR_RETVAL),w
	line	1928
	
l1049:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_Prv_ReceiveResponse
	__end_of_FCM_Prv_ReceiveResponse:
	signat	_FCM_Prv_ReceiveResponse,4217
	global	_delay_ms

;; *************** function _delay_ms *****************
;; Defined at:
;;		line 105 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_ReceiveResponse
;; This function uses a non-reentrant model
;;
psect	text7,local,class=CODE,delta=2,merge=1,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
global __ptext7
__ptext7:	;psect for function _delay_ms
psect	text7
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:	
;incstack = 0
	opt	callstack 11
; Regs used in _delay_ms: [wreg+status,2+status,0]
	movwf	(delay_ms@del)
	line	107
	
l2110:	
	goto	l2114
	line	109
	
l2112:	
	opt asmopt_push
opt asmopt_off
movlw	7
	movlb 0	; select bank0
movwf	((??_delay_ms+0)+0),f
	movlw	96
u697:
decfsz	wreg
	goto	u697
	decfsz	((??_delay_ms+0)+0),f
	goto	u697
	nop2
opt asmopt_pop

	line	107
	
l2114:	
	movlw	01h
	movlb 0	; select bank0
	subwf	(delay_ms@del),f
		incf	(((delay_ms@del))),w
	btfss	status,2
	goto	u351
	goto	u350
u351:
	goto	l2112
u350:
	line	111
	
l96:	
	return
	opt callstack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4217
	global	_FCD_01211_CircularBuffer1__GetNumberBytes

;; *************** function _FCD_01211_CircularBuffer1__GetNumberBytes *****************
;; Defined at:
;;		line 341 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      2    6[BANK0 ] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    2[BANK0 ] unsigned short 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       2       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0
;;      Totals:         0       6       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_ReceiveResponse
;; This function uses a non-reentrant model
;;
psect	text8,local,class=CODE,delta=2,merge=1,group=0
	file	"ST3215.c"
	line	341
global __ptext8
__ptext8:	;psect for function _FCD_01211_CircularBuffer1__GetNumberBytes
psect	text8
	file	"ST3215.c"
	line	341
	global	__size_of_FCD_01211_CircularBuffer1__GetNumberBytes
	__size_of_FCD_01211_CircularBuffer1__GetNumberBytes	equ	__end_of_FCD_01211_CircularBuffer1__GetNumberBytes-_FCD_01211_CircularBuffer1__GetNumberBytes
	
_FCD_01211_CircularBuffer1__GetNumberBytes:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCD_01211_CircularBuffer1__GetNumberBytes: [wreg+status,2+status,0]
	line	350
	
l2120:	
	movf	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	skipz
	goto	u375
	movf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
u375:
	skipnc
	goto	u371
	goto	u370
u371:
	goto	l2124
u370:
	line	353
	
l2122:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	movwf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL)
	movf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	subwfb	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	movwf	1+(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL)
	line	355
	goto	l2130
	line	357
	
l2124:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	skipz
	goto	u385
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
u385:
	skipnc
	goto	u381
	goto	u380
u381:
	goto	l2128
u380:
	line	360
	
l2126:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	subwf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	movwf	(??_FCD_01211_CircularBuffer1__GetNumberBytes+0)+0
	movf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	subwfb	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	movwf	1+(??_FCD_01211_CircularBuffer1__GetNumberBytes+0)+0
	movf	0+(??_FCD_01211_CircularBuffer1__GetNumberBytes+0)+0,w
	addlw	020h
	movwf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL)
	movlw	0
	addwfc	1+(??_FCD_01211_CircularBuffer1__GetNumberBytes+0)+0,w
	movwf	1+(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL)
	line	362
	goto	l2130
	line	364
	
l2128:	
	clrf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL)
	clrf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL+1)
	line	370
	
l2130:	
	movf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL+1),w
	movwf	(?_FCD_01211_CircularBuffer1__GetNumberBytes+1)
	movf	(FCD_01211_CircularBuffer1__GetNumberBytes@FCR_RETVAL),w
	movwf	(?_FCD_01211_CircularBuffer1__GetNumberBytes)
	line	372
	
l816:	
	return
	opt callstack 0
GLOBAL	__end_of_FCD_01211_CircularBuffer1__GetNumberBytes
	__end_of_FCD_01211_CircularBuffer1__GetNumberBytes:
	signat	_FCD_01211_CircularBuffer1__GetNumberBytes,90
	global	_FCD_01211_CircularBuffer1__GetByte

;; *************** function _FCD_01211_CircularBuffer1__GetByte *****************
;; Defined at:
;;		line 508 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_TEMP        2    8[BANK0 ] unsigned short 
;;  FCR_RETVAL      2    6[BANK0 ] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    2[BANK0 ] unsigned short 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       2       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0
;;      Totals:         0       8       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Prv_ReceiveResponse
;; This function uses a non-reentrant model
;;
psect	text9,local,class=CODE,delta=2,merge=1,group=0
	line	508
global __ptext9
__ptext9:	;psect for function _FCD_01211_CircularBuffer1__GetByte
psect	text9
	file	"ST3215.c"
	line	508
	global	__size_of_FCD_01211_CircularBuffer1__GetByte
	__size_of_FCD_01211_CircularBuffer1__GetByte	equ	__end_of_FCD_01211_CircularBuffer1__GetByte-_FCD_01211_CircularBuffer1__GetByte
	
_FCD_01211_CircularBuffer1__GetByte:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCD_01211_CircularBuffer1__GetByte: [wreg+fsr1l+fsr1h+status,2+status,0]
	line	515
	
l2134:	
	movf	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	xorwf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	skipz
	goto	u395
	movf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	xorwf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
u395:

	skipnz
	goto	u391
	goto	u390
u391:
	goto	l2146
u390:
	line	518
	
l2136:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	addlw	low(_FCV_01211_CircularBuffer1__DATA|((0x0)<<8))&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	indf1,w
	movwf	(??_FCD_01211_CircularBuffer1__GetByte+0)+0
	clrf	(??_FCD_01211_CircularBuffer1__GetByte+0)+0+1
	movf	0+(??_FCD_01211_CircularBuffer1__GetByte+0)+0,w
	movwf	(FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL)
	movf	1+(??_FCD_01211_CircularBuffer1__GetByte+0)+0,w
	movwf	(FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL+1)
	line	520
	
l2138:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	addlw	01h
	movwf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP)
	movlw	0
	addwfc	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	movwf	1+(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP)
	line	522
	
l2140:	
	movlw	0
	subwf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP+1),w
	movlw	020h
	skipnz
	subwf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP),w
	skipc
	goto	u401
	goto	u400
u401:
	goto	l2144
u400:
	line	525
	
l2142:	
	clrf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP)
	clrf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP+1)
	line	531
	
l2144:	
	movf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP+1),w
	movwf	(_FCV_01211_CircularBuffer1__DATASTART+1)	;volatile
	movf	(FCD_01211_CircularBuffer1__GetByte@FCL_TEMP),w
	movwf	(_FCV_01211_CircularBuffer1__DATASTART)	;volatile
	line	533
	goto	l839
	line	538
	
l2146:	
	movlw	0FFh
	movwf	(FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL)
	movlw	0
	movwf	((FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL))+1
	line	542
	
l839:	
	line	544
	movf	(FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL+1),w
	movwf	(?_FCD_01211_CircularBuffer1__GetByte+1)
	movf	(FCD_01211_CircularBuffer1__GetByte@FCR_RETVAL),w
	movwf	(?_FCD_01211_CircularBuffer1__GetByte)
	line	546
	
l840:	
	return
	opt callstack 0
GLOBAL	__end_of_FCD_01211_CircularBuffer1__GetByte
	__end_of_FCD_01211_CircularBuffer1__GetByte:
	signat	_FCD_01211_CircularBuffer1__GetByte,90
	global	_FCM_Initialise

;; *************** function _FCM_Initialise *****************
;; Defined at:
;;		line 2580 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : B1F/1
;;		On exit  : B1F/1
;;		Unchanged: B00/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FC_CAL_UART_Init_1
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text10,local,class=CODE,delta=2,merge=1,group=0
	line	2580
global __ptext10
__ptext10:	;psect for function _FCM_Initialise
psect	text10
	file	"ST3215.c"
	line	2580
	global	__size_of_FCM_Initialise
	__size_of_FCM_Initialise	equ	__end_of_FCM_Initialise-_FCM_Initialise
	
_FCM_Initialise:	
;incstack = 0
	opt	callstack 12
; Regs used in _FCM_Initialise: [wreg+status,2+status,0+pclath+cstack]
	line	2584
	
l2370:	
	fcall	_FC_CAL_UART_Init_1
	line	2586
	
l1126:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_Initialise
	__end_of_FCM_Initialise:
	signat	_FCM_Initialise,89
	global	_FC_CAL_UART_Init_1

;; *************** function _FC_CAL_UART_Init_1 *****************
;; Defined at:
;;		line 660 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : B1F/1
;;		On exit  : B1F/1
;;		Unchanged: B00/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCM_Initialise
;; This function uses a non-reentrant model
;;
psect	text11,local,class=CODE,delta=2,merge=1,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	660
global __ptext11
__ptext11:	;psect for function _FC_CAL_UART_Init_1
psect	text11
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	660
	global	__size_of_FC_CAL_UART_Init_1
	__size_of_FC_CAL_UART_Init_1	equ	__end_of_FC_CAL_UART_Init_1-_FC_CAL_UART_Init_1
	
_FC_CAL_UART_Init_1:	
;incstack = 0
	opt	callstack 12
; Regs used in _FC_CAL_UART_Init_1: [wreg+status,2]
	line	786
	
l2168:	
	movlb 3	; select bank3
	bsf	(414)^0180h,2	;volatile
	line	793
	
l2170:	
	movlw	low(0Ah)
	movwf	(411)^0180h	;volatile
	line	794
	
l2172:	
	clrf	(413)^0180h	;volatile
	line	805
	
l2174:	
	bsf	(413)^0180h,7	;volatile
	line	808
	
l2176:	
	bsf	(414)^0180h,5	;volatile
	line	811
	
l2178:	
	bsf	(413)^0180h,4	;volatile
	line	815
	
l2180:	
	movlb 1	; select bank1
	bsf	(145)^080h,5	;volatile
	line	816
	
l2182:	
	bsf	(11),6	;volatile
	line	817
	
l2184:	
	bsf	(11),7	;volatile
	line	1441
	
l691:	
	return
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Init_1
	__end_of_FC_CAL_UART_Init_1:
	signat	_FC_CAL_UART_Init_1,89
	global	_FCM_Ev_Initialise

;; *************** function _FCM_Ev_Initialise *****************
;; Defined at:
;;		line 1423 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      4    2[BANK0 ] unsigned long 
;; Return value:  Size  Location     Type
;;                  4  980[None  ] unsigned long 
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : B1F/1
;;		On exit  : B1F/1
;;		Unchanged: B1F/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text12,local,class=CODE,delta=2,merge=1,group=0
	file	"ST3215.c"
	line	1423
global __ptext12
__ptext12:	;psect for function _FCM_Ev_Initialise
psect	text12
	file	"ST3215.c"
	line	1423
	global	__size_of_FCM_Ev_Initialise
	__size_of_FCM_Ev_Initialise	equ	__end_of_FCM_Ev_Initialise-_FCM_Ev_Initialise
	
_FCM_Ev_Initialise:	
;incstack = 0
	opt	callstack 13
; Regs used in _FCM_Ev_Initialise: []
	line	1429
	
l2362:	
	line	1431
;	Return value of _FCM_Ev_Initialise is never used
	
l981:	
	return
	opt callstack 0
GLOBAL	__end_of_FCM_Ev_Initialise
	__end_of_FCM_Ev_Initialise:
	signat	_FCM_Ev_Initialise,92
	global	_myisr

;; *************** function _myisr *****************
;; Defined at:
;;		line 2670 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_RX          1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 1E/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_FCD_01211_CircularBuffer1__PutByte
;;		_FC_CAL_UART_Receive_1
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
psect	intentry
	file	"ST3215.c"
	line	2670
	global	__size_of_myisr
	__size_of_myisr	equ	__end_of_myisr-_myisr
	
_myisr:	
;incstack = 0
	opt	callstack 11
	bsf int$flags,0 ;set compiler interrupt flag (level 1)
; Regs used in _myisr: [wreg+fsr1l+fsr1h+status,2+status,0+pclath+cstack]
psect	intentry
	pagesel	$
	line	2679
	
i1l2384:	
	movlb 0	; select bank0
	btfss	(17),5	;volatile
	goto	u67_21
	goto	u67_20
u67_21:
	goto	i1l1143
u67_20:
	
i1l2386:	
	movlb 1	; select bank1
	btfss	(145)^080h,5	;volatile
	goto	u68_21
	goto	u68_20
u68_21:
	goto	i1l1143
u68_20:
	line	2683
	
i1l2388:	
	movlw	low(0)
	fcall	_FC_CAL_UART_Receive_1
	movf	(0+(?_FC_CAL_UART_Receive_1)),w
	movlb 0	; select bank0
	movwf	(??_myisr+0)+0
	movf	(??_myisr+0)+0,w
	movwf	(myisr@FCL_RX)
	line	2686
	
i1l2390:	
	movf	(myisr@FCL_RX),w
	fcall	_FCD_01211_CircularBuffer1__PutByte
	line	2688
	
i1l2392:	
	bcf	(17),5	;volatile
	line	2693
	
i1l1143:	
	bcf int$flags,0 ;clear compiler interrupt flag (level 1)
	retfie
	opt callstack 0
GLOBAL	__end_of_myisr
	__end_of_myisr:
	signat	_myisr,89
	global	_FC_CAL_UART_Receive_1

;; *************** function _FC_CAL_UART_Receive_1 *****************
;; Defined at:
;;		line 1647 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
;; Parameters:    Size  Location     Type
;;  nTimeout        1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  nTimeout        1   12[COMMON] unsigned char 
;;  retVal          2   10[COMMON] unsigned short 
;;  delaycnt        2    6[COMMON] unsigned short 
;;  regcheck        1   13[COMMON] unsigned char 
;;  rxStatus        1    9[COMMON] unsigned char 
;;  delay1          1    8[COMMON] unsigned char 
;;  bWaitForever    1    5[COMMON] unsigned char 
;;  dummy           1    4[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    0[COMMON] short 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 1F/1
;;		On exit  : 1C/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         2       0       0       0       0       0       0       0
;;      Locals:        10       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0
;;      Totals:        14       0       0       0       0       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_myisr
;; This function uses a non-reentrant model
;;
psect	text14,local,class=CODE,delta=2,merge=1,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1647
global __ptext14
__ptext14:	;psect for function _FC_CAL_UART_Receive_1
psect	text14
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1647
	global	__size_of_FC_CAL_UART_Receive_1
	__size_of_FC_CAL_UART_Receive_1	equ	__end_of_FC_CAL_UART_Receive_1-_FC_CAL_UART_Receive_1
	
_FC_CAL_UART_Receive_1:	
;incstack = 0
	opt	callstack 11
; Regs used in _FC_CAL_UART_Receive_1: [wreg+status,2+status,0]
	movwf	(FC_CAL_UART_Receive_1@nTimeout)
	line	1650
	
i1l2272:	
	movlw	0
	movwf	(FC_CAL_UART_Receive_1@retVal)
	movlw	02h
	movwf	((FC_CAL_UART_Receive_1@retVal))+1
	line	1657
	
i1l2274:	
	clrf	(FC_CAL_UART_Receive_1@delay1)
	line	1659
	clrf	(FC_CAL_UART_Receive_1@bWaitForever)
	line	1660
	clrf	(FC_CAL_UART_Receive_1@rxStatus)
	line	1666
	clrf	(FC_CAL_UART_Receive_1@dummy)
	line	1669
	
i1l2276:	
		incf	((FC_CAL_UART_Receive_1@nTimeout)),w
	btfss	status,2
	goto	u54_21
	goto	u54_20
u54_21:
	goto	i1l2306
u54_20:
	line	1670
	
i1l2278:	
	clrf	(FC_CAL_UART_Receive_1@bWaitForever)
	incf	(FC_CAL_UART_Receive_1@bWaitForever),f
	goto	i1l2306
	line	1680
	
i1l2280:	
	movf	((FC_CAL_UART_Receive_1@bWaitForever)),w
	btfss	status,2
	goto	u55_21
	goto	u55_20
u55_21:
	goto	i1l2300
u55_20:
	line	1682
	
i1l2282:	
	movf	((FC_CAL_UART_Receive_1@nTimeout)),w
	btfss	status,2
	goto	u56_21
	goto	u56_20
u56_21:
	goto	i1l2286
u56_20:
	line	1684
	
i1l2284:	
	clrf	(FC_CAL_UART_Receive_1@rxStatus)
	incf	(FC_CAL_UART_Receive_1@rxStatus),f
	line	1685
	goto	i1l2300
	line	1688
	
i1l2286:	
	clrf	(FC_CAL_UART_Receive_1@delaycnt)
	clrf	(FC_CAL_UART_Receive_1@delaycnt+1)
	
i1l2292:	
	movlw	01h
	addwf	(FC_CAL_UART_Receive_1@delaycnt),f
	movlw	0
	addwfc	(FC_CAL_UART_Receive_1@delaycnt+1),f
	movlw	0
	subwf	(FC_CAL_UART_Receive_1@delaycnt+1),w
	movlw	04h
	skipnz
	subwf	(FC_CAL_UART_Receive_1@delaycnt),w
	skipc
	goto	u57_21
	goto	u57_20
u57_21:
	goto	i1l2292
u57_20:
	line	1689
	
i1l2294:	
	movf	(FC_CAL_UART_Receive_1@delay1),w
	addlw	01h
	movwf	(??_FC_CAL_UART_Receive_1+0)+0
	movf	(??_FC_CAL_UART_Receive_1+0)+0,w
	movwf	(FC_CAL_UART_Receive_1@delay1)
	line	1690
		movlw	100
	xorwf	((FC_CAL_UART_Receive_1@delay1)),w
	btfss	status,2
	goto	u58_21
	goto	u58_20
u58_21:
	goto	i1l2300
u58_20:
	line	1692
	
i1l2296:	
	movf	(FC_CAL_UART_Receive_1@nTimeout),w
	addlw	0FFh
	movwf	(??_FC_CAL_UART_Receive_1+0)+0
	movf	(??_FC_CAL_UART_Receive_1+0)+0,w
	movwf	(FC_CAL_UART_Receive_1@nTimeout)
	line	1693
# 1693 "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
clrwdt ;# 
psect	text14
	line	1694
	
i1l2298:	
	clrf	(FC_CAL_UART_Receive_1@delay1)
	line	1714
	
i1l2300:	
	movlw	0
	movlb 0	; select bank0
	btfsc	(17),5	;volatile
	movlw	1
	movwf	(FC_CAL_UART_Receive_1@regcheck)
	line	1716
	
i1l2302:	
	movf	((FC_CAL_UART_Receive_1@regcheck)),w
	btfsc	status,2
	goto	u59_21
	goto	u59_20
u59_21:
	goto	i1l2306
u59_20:
	line	1717
	
i1l2304:	
	movlw	low(02h)
	movwf	(??_FC_CAL_UART_Receive_1+0)+0
	movf	(??_FC_CAL_UART_Receive_1+0)+0,w
	movwf	(FC_CAL_UART_Receive_1@rxStatus)
	line	1678
	
i1l2306:	
	movf	((FC_CAL_UART_Receive_1@rxStatus)),w
	btfsc	status,2
	goto	u60_21
	goto	u60_20
u60_21:
	goto	i1l2280
u60_20:
	line	1773
	
i1l2308:	
		movlw	2
	xorwf	((FC_CAL_UART_Receive_1@rxStatus)),w
	btfss	status,2
	goto	u61_21
	goto	u61_20
u61_21:
	goto	i1l2328
u61_20:
	line	1818
	
i1l2310:	
	movlw	0
	movlb 3	; select bank3
	btfsc	(413)^0180h,2	;volatile
	movlw	1
	movwf	(FC_CAL_UART_Receive_1@regcheck)
	line	1819
	
i1l2312:	
	movf	((FC_CAL_UART_Receive_1@regcheck)),w
	btfsc	status,2
	goto	u62_21
	goto	u62_20
u62_21:
	goto	i1l2316
u62_20:
	line	1821
	
i1l2314:	
	movf	(409)^0180h,w	;volatile
	line	1823
	movlw	0
	movwf	(FC_CAL_UART_Receive_1@retVal)
	movlw	04h
	movwf	((FC_CAL_UART_Receive_1@retVal))+1
	line	1825
	goto	i1l2328
	line	1828
	
i1l2316:	
	movlw	0
	btfsc	(413)^0180h,1	;volatile
	movlw	1
	movwf	(FC_CAL_UART_Receive_1@regcheck)
	line	1829
	
i1l2318:	
	movf	((FC_CAL_UART_Receive_1@regcheck)),w
	btfsc	status,2
	goto	u63_21
	goto	u63_20
u63_21:
	goto	i1l2324
u63_20:
	line	1831
	
i1l2320:	
	bcf	(413)^0180h,4	;volatile
	line	1832
	bsf	(413)^0180h,4	;volatile
	line	1835
	
i1l2322:	
	movlw	0
	movwf	(FC_CAL_UART_Receive_1@retVal)
	movlw	08h
	movwf	((FC_CAL_UART_Receive_1@retVal))+1
	line	1837
	goto	i1l2328
	line	1840
	
i1l2324:	
	clrf	(FC_CAL_UART_Receive_1@retVal)
	clrf	(FC_CAL_UART_Receive_1@retVal+1)
	line	1847
	
i1l2326:	
	movf	(FC_CAL_UART_Receive_1@retVal),w
	iorwf	(409)^0180h,w	;volatile
	movwf	(??_FC_CAL_UART_Receive_1+0)+0
	movf	(FC_CAL_UART_Receive_1@retVal+1),w
	movwf	1+(??_FC_CAL_UART_Receive_1+0)+0
	movf	0+(??_FC_CAL_UART_Receive_1+0)+0,w
	movwf	(FC_CAL_UART_Receive_1@retVal)
	movf	1+(??_FC_CAL_UART_Receive_1+0)+0,w
	movwf	(FC_CAL_UART_Receive_1@retVal+1)
	line	2117
	
i1l2328:	
	movf	(FC_CAL_UART_Receive_1@retVal+1),w
	movwf	(?_FC_CAL_UART_Receive_1+1)
	movf	(FC_CAL_UART_Receive_1@retVal),w
	movwf	(?_FC_CAL_UART_Receive_1)
	line	2118
	
i1l719:	
	return
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Receive_1
	__end_of_FC_CAL_UART_Receive_1:
	signat	_FC_CAL_UART_Receive_1,4218
	global	_FCD_01211_CircularBuffer1__PutByte

;; *************** function _FCD_01211_CircularBuffer1__PutByte *****************
;; Defined at:
;;		line 442 in file "ST3215.c"
;; Parameters:    Size  Location     Type
;;  FCL_DATA        1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_DATA        1    2[COMMON] unsigned char 
;;  FCL_TEMP        2    5[COMMON] unsigned short 
;;  FCL_TEMP2       2    3[COMMON] unsigned short 
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, status,2, status,0
;; Tracked objects:
;;		On entry : 1F/0
;;		On exit  : 1F/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6
;;      Params:         0       0       0       0       0       0       0       0
;;      Locals:         6       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0
;;      Totals:         7       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_myisr
;; This function uses a non-reentrant model
;;
psect	text15,local,class=CODE,delta=2,merge=1,group=0
	file	"ST3215.c"
	line	442
global __ptext15
__ptext15:	;psect for function _FCD_01211_CircularBuffer1__PutByte
psect	text15
	file	"ST3215.c"
	line	442
	global	__size_of_FCD_01211_CircularBuffer1__PutByte
	__size_of_FCD_01211_CircularBuffer1__PutByte	equ	__end_of_FCD_01211_CircularBuffer1__PutByte-_FCD_01211_CircularBuffer1__PutByte
	
_FCD_01211_CircularBuffer1__PutByte:	
;incstack = 0
	opt	callstack 11
; Regs used in _FCD_01211_CircularBuffer1__PutByte: [wreg+fsr1l+fsr1h+status,2+status,0]
	movwf	(FCD_01211_CircularBuffer1__PutByte@FCL_DATA)
	line	450
	
i1l2332:	
	movf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	addlw	01h
	movwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP)
	movlw	0
	addwfc	(_FCV_01211_CircularBuffer1__DATAEND+1),w	;volatile
	movwf	1+(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP)
	line	452
	
i1l2334:	
	movlw	0
	subwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP+1),w
	movlw	020h
	skipnz
	subwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP),w
	skipc
	goto	u64_21
	goto	u64_20
u64_21:
	goto	i1l2338
u64_20:
	line	455
	
i1l2336:	
	clrf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP)
	clrf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP+1)
	line	461
	
i1l2338:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	xorwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP+1),w
	skipz
	goto	u65_25
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	xorwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP),w
u65_25:

	skipnz
	goto	u65_21
	goto	u65_20
u65_21:
	goto	i1l2346
u65_20:
	line	464
	
i1l2340:	
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_DATA),w
	movwf	(??_FCD_01211_CircularBuffer1__PutByte+0)+0
	movf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	addlw	low(_FCV_01211_CircularBuffer1__DATA|((0x0)<<8))&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	(??_FCD_01211_CircularBuffer1__PutByte+0)+0,w
	movwf	indf1
	line	466
	
i1l2342:	
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP+1),w
	movwf	(_FCV_01211_CircularBuffer1__DATAEND+1)	;volatile
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP),w
	movwf	(_FCV_01211_CircularBuffer1__DATAEND)	;volatile
	line	468
	
i1l2344:	
	line	470
	goto	i1l834
	line	473
	
i1l2346:	
	movf	(_FCV_01211_CircularBuffer1__DATASTART),w	;volatile
	addlw	01h
	movwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2)
	movlw	0
	addwfc	(_FCV_01211_CircularBuffer1__DATASTART+1),w	;volatile
	movwf	1+(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2)
	line	475
	
i1l2348:	
	movlw	0
	subwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2+1),w
	movlw	020h
	skipnz
	subwf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2),w
	skipc
	goto	u66_21
	goto	u66_20
u66_21:
	goto	i1l2352
u66_20:
	line	478
	
i1l2350:	
	clrf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2)
	clrf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2+1)
	line	484
	
i1l2352:	
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2+1),w
	movwf	(_FCV_01211_CircularBuffer1__DATASTART+1)	;volatile
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_TEMP2),w
	movwf	(_FCV_01211_CircularBuffer1__DATASTART)	;volatile
	line	486
	
i1l2354:	
	movf	(FCD_01211_CircularBuffer1__PutByte@FCL_DATA),w
	movwf	(??_FCD_01211_CircularBuffer1__PutByte+0)+0
	movf	(_FCV_01211_CircularBuffer1__DATAEND),w	;volatile
	addlw	low(_FCV_01211_CircularBuffer1__DATA|((0x0)<<8))&0ffh
	movwf	fsr1l
	clrf fsr1h	
	
	movf	(??_FCD_01211_CircularBuffer1__PutByte+0)+0,w
	movwf	indf1
	goto	i1l2342
	line	500
	
i1l834:	
	return
	opt callstack 0
GLOBAL	__end_of_FCD_01211_CircularBuffer1__PutByte
	__end_of_FCD_01211_CircularBuffer1__PutByte:
	signat	_FCD_01211_CircularBuffer1__PutByte,4217
global	___latbits
___latbits	equ	2
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	int$flags
	int$flags	set btemp
	global	wtemp0
	wtemp0 set btemp+0
	end
