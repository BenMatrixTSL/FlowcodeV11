opt subtitle "Microchip MPLAB XC8 C Compiler v2.10 (Free license) build 20190730164152 Og9 "

opt pagewidth 120

	opt flic

	processor	18F67K40
opt include "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\18f67k40.cgen.inc"
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
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,f
	movf indf1,w
endm
popf macro arg1
	movf postdec1,f
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 54 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PPSLOCK equ 0DEFh ;# 
# 74 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INT0PPS equ 0DF0h ;# 
# 134 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INT1PPS equ 0DF1h ;# 
# 200 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INT2PPS equ 0DF2h ;# 
# 266 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INT3PPS equ 0DF3h ;# 
# 338 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T0CKIPPS equ 0DF4h ;# 
# 398 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1CKIPPS equ 0DF5h ;# 
# 464 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1GPPS equ 0DF6h ;# 
# 530 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3CKIPPS equ 0DF7h ;# 
# 596 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3GPPS equ 0DF8h ;# 
# 662 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5CKIPPS equ 0DF9h ;# 
# 734 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5GPPS equ 0DFAh ;# 
# 806 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7CKIPPS equ 0DFBh ;# 
# 878 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7GPPS equ 0DFCh ;# 
# 950 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2INPPS equ 0DFDh ;# 
# 1016 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4INPPS equ 0DFEh ;# 
# 1088 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6INPPS equ 0DFFh ;# 
# 1154 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8INPPS equ 0E00h ;# 
# 1226 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACTPPS equ 0E01h ;# 
# 1298 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP1PPS equ 0E02h ;# 
# 1370 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP2PPS equ 0E03h ;# 
# 1442 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP3PPS equ 0E04h ;# 
# 1514 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP4PPS equ 0E05h ;# 
# 1586 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP5PPS equ 0E06h ;# 
# 1658 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1WINPPS equ 0E07h ;# 
# 1730 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1SIGPPS equ 0E08h ;# 
# 1802 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2WINPPS equ 0E09h ;# 
# 1874 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2SIGPPS equ 0E0Ah ;# 
# 1946 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1PPS equ 0E0Bh ;# 
# 1951 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWGINPPS equ 0E0Bh ;# 
# 2156 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCARLPPS equ 0E0Ch ;# 
# 2228 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCARHPPS equ 0E0Dh ;# 
# 2300 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDSRCPPS equ 0E0Eh ;# 
# 2372 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RX1PPS equ 0E0Fh ;# 
# 2377 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RXPPS equ 0E0Fh ;# 
# 2502 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CK1PPS equ 0E10h ;# 
# 2507 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX1PPS equ 0E10h ;# 
# 2511 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CKPPS equ 0E10h ;# 
# 2515 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXPPS equ 0E10h ;# 
# 2756 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RX2PPS equ 0E11h ;# 
# 2828 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CK2PPS equ 0E12h ;# 
# 2833 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX2PPS equ 0E12h ;# 
# 2970 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RX3PPS equ 0E13h ;# 
# 3042 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CK3PPS equ 0E14h ;# 
# 3047 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX3PPS equ 0E14h ;# 
# 3184 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RX4PPS equ 0E15h ;# 
# 3250 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CK4PPS equ 0E16h ;# 
# 3255 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX4PPS equ 0E16h ;# 
# 3380 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RX5PPS equ 0E17h ;# 
# 3452 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CK5PPS equ 0E18h ;# 
# 3457 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX5PPS equ 0E18h ;# 
# 3594 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1CLKPPS equ 0E19h ;# 
# 3660 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1DATPPS equ 0E1Ah ;# 
# 3726 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1SSPPS equ 0E1Bh ;# 
# 3798 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2CLKPPS equ 0E1Ch ;# 
# 3864 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2DATPPS equ 0E1Dh ;# 
# 3930 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2SSPPS equ 0E1Eh ;# 
# 3996 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR0 equ 0E1Fh ;# 
# 4046 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR1 equ 0E20h ;# 
# 4094 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR2 equ 0E21h ;# 
# 4148 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR3 equ 0E22h ;# 
# 4226 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR4 equ 0E23h ;# 
# 4284 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR5 equ 0E24h ;# 
# 4373 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR6 equ 0E25h ;# 
# 4411 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR7 equ 0E26h ;# 
# 4455 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR8 equ 0E27h ;# 
# 4494 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IPR9 equ 0E28h ;# 
# 4544 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE0 equ 0E29h ;# 
# 4594 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE1 equ 0E2Ah ;# 
# 4642 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE2 equ 0E2Bh ;# 
# 4696 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE3 equ 0E2Ch ;# 
# 4806 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE4 equ 0E2Dh ;# 
# 4856 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE5 equ 0E2Eh ;# 
# 4918 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE6 equ 0E2Fh ;# 
# 4956 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE7 equ 0E30h ;# 
# 5000 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE8 equ 0E31h ;# 
# 5039 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIE9 equ 0E32h ;# 
# 5089 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR0 equ 0E33h ;# 
# 5139 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR1 equ 0E34h ;# 
# 5187 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR2 equ 0E35h ;# 
# 5241 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR3 equ 0E36h ;# 
# 5319 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR4 equ 0E37h ;# 
# 5369 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR5 equ 0E38h ;# 
# 5431 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR6 equ 0E39h ;# 
# 5469 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR7 equ 0E3Ah ;# 
# 5513 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR8 equ 0E3Bh ;# 
# 5560 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PIR9 equ 0E3Ch ;# 
# 5610 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WDTCON0 equ 0E3Dh ;# 
# 5685 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WDTCON1 equ 0E3Eh ;# 
# 5779 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WDTPSL equ 0E3Fh ;# 
# 5907 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WDTPSH equ 0E40h ;# 
# 6035 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WDTTMR equ 0E41h ;# 
# 6123 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CPUDOZE equ 0E42h ;# 
# 6188 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCCON1 equ 0E43h ;# 
# 6258 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCCON2 equ 0E44h ;# 
# 6328 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCCON3 equ 0E45h ;# 
# 6368 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCSTAT equ 0E46h ;# 
# 6373 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCSTAT1 equ 0E46h ;# 
# 6480 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCEN equ 0E47h ;# 
# 6531 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCTUNE equ 0E48h ;# 
# 6589 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
OSCFRQ equ 0E49h ;# 
# 6635 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
VREGCON equ 0E4Ah ;# 
# 6669 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BORCON equ 0E4Bh ;# 
# 6696 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD0 equ 0E4Ch ;# 
# 6773 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD1 equ 0E4Dh ;# 
# 6843 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD2 equ 0E4Eh ;# 
# 6897 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD3 equ 0E4Fh ;# 
# 6948 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD4 equ 0E50h ;# 
# 7004 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PMD5 equ 0E51h ;# 
# 7060 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA0PPS equ 0E52h ;# 
# 7110 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA1PPS equ 0E53h ;# 
# 7160 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA2PPS equ 0E54h ;# 
# 7210 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA3PPS equ 0E55h ;# 
# 7260 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA4PPS equ 0E56h ;# 
# 7310 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA5PPS equ 0E57h ;# 
# 7360 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA6PPS equ 0E58h ;# 
# 7410 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RA7PPS equ 0E59h ;# 
# 7460 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB0PPS equ 0E5Ah ;# 
# 7510 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB1PPS equ 0E5Bh ;# 
# 7560 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB2PPS equ 0E5Ch ;# 
# 7610 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB3PPS equ 0E5Dh ;# 
# 7660 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB4PPS equ 0E5Eh ;# 
# 7710 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB5PPS equ 0E5Fh ;# 
# 7760 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB6PPS equ 0E60h ;# 
# 7810 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RB7PPS equ 0E61h ;# 
# 7860 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC0PPS equ 0E62h ;# 
# 7910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC1PPS equ 0E63h ;# 
# 7960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC2PPS equ 0E64h ;# 
# 8010 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC3PPS equ 0E65h ;# 
# 8060 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC4PPS equ 0E66h ;# 
# 8110 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC5PPS equ 0E67h ;# 
# 8160 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC6PPS equ 0E68h ;# 
# 8210 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC7PPS equ 0E69h ;# 
# 8260 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD0PPS equ 0E6Ah ;# 
# 8310 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD1PPS equ 0E6Bh ;# 
# 8360 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD2PPS equ 0E6Ch ;# 
# 8410 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD3PPS equ 0E6Dh ;# 
# 8460 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD4PPS equ 0E6Eh ;# 
# 8510 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD5PPS equ 0E6Fh ;# 
# 8560 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD6PPS equ 0E70h ;# 
# 8610 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RD7PPS equ 0E71h ;# 
# 8660 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE0PPS equ 0E72h ;# 
# 8710 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE1PPS equ 0E73h ;# 
# 8760 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE2PPS equ 0E74h ;# 
# 8810 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE3PPS equ 0E75h ;# 
# 8860 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE4PPS equ 0E76h ;# 
# 8910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE5PPS equ 0E77h ;# 
# 8960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE6PPS equ 0E78h ;# 
# 9010 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RE7PPS equ 0E79h ;# 
# 9060 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF0PPS equ 0E7Ah ;# 
# 9110 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF1PPS equ 0E7Bh ;# 
# 9160 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF2PPS equ 0E7Ch ;# 
# 9210 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF3PPS equ 0E7Dh ;# 
# 9260 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF4PPS equ 0E7Eh ;# 
# 9310 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF5PPS equ 0E7Fh ;# 
# 9360 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF6PPS equ 0E80h ;# 
# 9410 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RF7PPS equ 0E81h ;# 
# 9460 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG0PPS equ 0E82h ;# 
# 9510 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG1PPS equ 0E83h ;# 
# 9560 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG2PPS equ 0E84h ;# 
# 9610 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG3PPS equ 0E85h ;# 
# 9660 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG4PPS equ 0E86h ;# 
# 9710 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG6PPS equ 0E88h ;# 
# 9760 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RG7PPS equ 0E89h ;# 
# 9810 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RH0PPS equ 0E8Ah ;# 
# 9860 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RH1PPS equ 0E8Bh ;# 
# 9910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RH2PPS equ 0E8Ch ;# 
# 9960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RH3PPS equ 0E8Dh ;# 
# 10010 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLA equ 0E8Eh ;# 
# 10072 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONA equ 0E8Fh ;# 
# 10134 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONA equ 0E90h ;# 
# 10196 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUA equ 0E91h ;# 
# 10258 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELA equ 0E92h ;# 
# 10320 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCBF equ 0E93h ;# 
# 10382 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCBN equ 0E94h ;# 
# 10444 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCBP equ 0E95h ;# 
# 10506 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLB equ 0E96h ;# 
# 10568 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONB equ 0E97h ;# 
# 10630 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONB equ 0E98h ;# 
# 10692 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUB equ 0E99h ;# 
# 10754 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELB equ 0E9Ah ;# 
# 10816 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCCF equ 0E9Bh ;# 
# 10878 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCCN equ 0E9Ch ;# 
# 10940 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCCP equ 0E9Dh ;# 
# 11002 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLC equ 0E9Eh ;# 
# 11064 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONC equ 0E9Fh ;# 
# 11126 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONC equ 0EA0h ;# 
# 11188 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUC equ 0EA1h ;# 
# 11250 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLD equ 0EA3h ;# 
# 11312 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCOND equ 0EA4h ;# 
# 11374 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCOND equ 0EA5h ;# 
# 11436 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUD equ 0EA6h ;# 
# 11498 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELD equ 0EA7h ;# 
# 11560 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCEF equ 0EA8h ;# 
# 11622 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCEN equ 0EA9h ;# 
# 11684 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCEP equ 0EAAh ;# 
# 11746 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLE equ 0EABh ;# 
# 11808 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONE equ 0EACh ;# 
# 11870 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONE equ 0EADh ;# 
# 11932 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUE equ 0EAEh ;# 
# 11994 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELE equ 0EAFh ;# 
# 12056 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLF equ 0EB0h ;# 
# 12118 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONF equ 0EB1h ;# 
# 12180 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONF equ 0EB2h ;# 
# 12242 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUF equ 0EB3h ;# 
# 12304 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELF equ 0EB4h ;# 
# 12366 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCGF equ 0EB5h ;# 
# 12387 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCGN equ 0EB6h ;# 
# 12408 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
IOCGP equ 0EB7h ;# 
# 12429 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLG equ 0EB8h ;# 
# 12491 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONG equ 0EB9h ;# 
# 12548 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONG equ 0EBAh ;# 
# 12605 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUG equ 0EBBh ;# 
# 12667 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ANSELG equ 0EBCh ;# 
# 12724 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INLVLH equ 0EBDh ;# 
# 12786 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SLRCONH equ 0EBEh ;# 
# 12848 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ODCONH equ 0EBFh ;# 
# 12910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WPUH equ 0EC0h ;# 
# 12972 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
HLVDCON0 equ 0EC2h ;# 
# 13052 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
HLVDCON1 equ 0EC3h ;# 
# 13124 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FVRCON equ 0EC4h ;# 
# 13213 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ZCDCON equ 0EC5h ;# 
# 13293 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DAC1CON0 equ 0EC6h ;# 
# 13394 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DAC1CON1 equ 0EC7h ;# 
# 13446 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM3CON0 equ 0EC8h ;# 
# 13526 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM3CON1 equ 0EC9h ;# 
# 13566 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM3NCH equ 0ECAh ;# 
# 13626 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM3PCH equ 0ECBh ;# 
# 13686 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM2CON0 equ 0ECCh ;# 
# 13766 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM2CON1 equ 0ECDh ;# 
# 13806 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM2NCH equ 0ECEh ;# 
# 13866 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM2PCH equ 0ECFh ;# 
# 13926 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM1CON0 equ 0ED0h ;# 
# 14006 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM1CON1 equ 0ED1h ;# 
# 14046 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM1NCH equ 0ED2h ;# 
# 14106 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CM1PCH equ 0ED3h ;# 
# 14166 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CMOUT equ 0ED4h ;# 
# 14198 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2BUF equ 0ED5h ;# 
# 14218 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2ADD equ 0ED6h ;# 
# 14338 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2MSK equ 0ED7h ;# 
# 14408 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2STAT equ 0ED8h ;# 
# 14862 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2CON1 equ 0ED9h ;# 
# 14982 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2CON2 equ 0EDAh ;# 
# 15169 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP2CON3 equ 0EDBh ;# 
# 15231 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC5REG equ 0EDCh ;# 
# 15236 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG5 equ 0EDCh ;# 
# 15269 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX5REG equ 0EDDh ;# 
# 15274 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG5 equ 0EDDh ;# 
# 15307 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP5BRG equ 0EDEh ;# 
# 15314 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP5BRGL equ 0EDEh ;# 
# 15319 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG5 equ 0EDEh ;# 
# 15352 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP5BRGH equ 0EDFh ;# 
# 15357 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH5 equ 0EDFh ;# 
# 15390 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC5STA equ 0EE0h ;# 
# 15395 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA5 equ 0EE0h ;# 
# 15512 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX5STA equ 0EE1h ;# 
# 15517 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA5 equ 0EE1h ;# 
# 15634 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUD5CON equ 0EE2h ;# 
# 15639 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON5 equ 0EE2h ;# 
# 15643 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL5 equ 0EE2h ;# 
# 15784 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC4REG equ 0EE3h ;# 
# 15789 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG4 equ 0EE3h ;# 
# 15822 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX4REG equ 0EE4h ;# 
# 15827 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG4 equ 0EE4h ;# 
# 15860 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP4BRG equ 0EE5h ;# 
# 15867 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP4BRGL equ 0EE5h ;# 
# 15872 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG4 equ 0EE5h ;# 
# 15905 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP4BRGH equ 0EE6h ;# 
# 15910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH4 equ 0EE6h ;# 
# 15943 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC4STA equ 0EE7h ;# 
# 15948 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA4 equ 0EE7h ;# 
# 16065 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX4STA equ 0EE8h ;# 
# 16070 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA4 equ 0EE8h ;# 
# 16187 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUD4CON equ 0EE9h ;# 
# 16192 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON4 equ 0EE9h ;# 
# 16196 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL4 equ 0EE9h ;# 
# 16337 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC3REG equ 0EEAh ;# 
# 16342 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG3 equ 0EEAh ;# 
# 16375 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX3REG equ 0EEBh ;# 
# 16380 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG3 equ 0EEBh ;# 
# 16413 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP3BRG equ 0EECh ;# 
# 16420 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP3BRGL equ 0EECh ;# 
# 16425 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG3 equ 0EECh ;# 
# 16458 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP3BRGH equ 0EEDh ;# 
# 16463 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH3 equ 0EEDh ;# 
# 16496 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC3STA equ 0EEEh ;# 
# 16501 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA3 equ 0EEEh ;# 
# 16618 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX3STA equ 0EEFh ;# 
# 16623 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA3 equ 0EEFh ;# 
# 16740 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUD3CON equ 0EF0h ;# 
# 16745 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON3 equ 0EF0h ;# 
# 16749 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL3 equ 0EF0h ;# 
# 16890 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC2REG equ 0EF1h ;# 
# 16895 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG2 equ 0EF1h ;# 
# 16928 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX2REG equ 0EF2h ;# 
# 16933 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG2 equ 0EF2h ;# 
# 16966 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP2BRG equ 0EF3h ;# 
# 16973 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP2BRGL equ 0EF3h ;# 
# 16978 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG2 equ 0EF3h ;# 
# 17011 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP2BRGH equ 0EF4h ;# 
# 17016 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH2 equ 0EF4h ;# 
# 17049 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC2STA equ 0EF5h ;# 
# 17054 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA2 equ 0EF5h ;# 
# 17223 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX2STA equ 0EF6h ;# 
# 17228 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA2 equ 0EF6h ;# 
# 17379 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUD2CON equ 0EF7h ;# 
# 17384 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON2 equ 0EF7h ;# 
# 17388 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL2 equ 0EF7h ;# 
# 17744 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2TMR equ 0EF8h ;# 
# 17751 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2TMRL equ 0EF8h ;# 
# 17821 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2TMRH equ 0EF9h ;# 
# 17891 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2TMRU equ 0EFAh ;# 
# 17963 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPR equ 0EFBh ;# 
# 17970 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPRL equ 0EFBh ;# 
# 18040 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPRH equ 0EFCh ;# 
# 18110 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPRU equ 0EFDh ;# 
# 18180 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPW equ 0EFEh ;# 
# 18187 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPWL equ 0EFEh ;# 
# 18257 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPWH equ 0EFFh ;# 
# 18327 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CPWU equ 0F00h ;# 
# 18399 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2PR equ 0F01h ;# 
# 18406 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2PRL equ 0F01h ;# 
# 18476 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2PRH equ 0F02h ;# 
# 18546 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2PRU equ 0F03h ;# 
# 18616 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CON0 equ 0F04h ;# 
# 18681 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CON1 equ 0F05h ;# 
# 18781 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2STAT equ 0F06h ;# 
# 18871 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2CLK equ 0F07h ;# 
# 18999 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2SIG equ 0F08h ;# 
# 19127 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT2WIN equ 0F09h ;# 
# 19257 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1TMR equ 0F0Ah ;# 
# 19264 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1TMRL equ 0F0Ah ;# 
# 19334 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1TMRH equ 0F0Bh ;# 
# 19404 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1TMRU equ 0F0Ch ;# 
# 19476 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPR equ 0F0Dh ;# 
# 19483 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPRL equ 0F0Dh ;# 
# 19553 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPRH equ 0F0Eh ;# 
# 19623 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPRU equ 0F0Fh ;# 
# 19695 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPW equ 0F10h ;# 
# 19702 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPWL equ 0F10h ;# 
# 19772 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPWH equ 0F11h ;# 
# 19842 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CPWU equ 0F12h ;# 
# 19914 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1PR equ 0F13h ;# 
# 19921 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1PRL equ 0F13h ;# 
# 19991 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1PRH equ 0F14h ;# 
# 20061 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1PRU equ 0F15h ;# 
# 20131 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CON0 equ 0F16h ;# 
# 20196 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CON1 equ 0F17h ;# 
# 20296 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1STAT equ 0F18h ;# 
# 20386 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1CLK equ 0F19h ;# 
# 20514 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1SIG equ 0F1Ah ;# 
# 20642 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SMT1WIN equ 0F1Bh ;# 
# 20770 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR5 equ 0F1Ch ;# 
# 20777 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR5L equ 0F1Ch ;# 
# 20797 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR5H equ 0F1Dh ;# 
# 20817 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP5CON equ 0F1Eh ;# 
# 20960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP5CAP equ 0F1Fh ;# 
# 21088 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR4 equ 0F20h ;# 
# 21095 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR4L equ 0F20h ;# 
# 21115 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR4H equ 0F21h ;# 
# 21135 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP4CON equ 0F22h ;# 
# 21278 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP4CAP equ 0F23h ;# 
# 21406 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR3 equ 0F24h ;# 
# 21413 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR3L equ 0F24h ;# 
# 21433 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR3H equ 0F25h ;# 
# 21453 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP3CON equ 0F26h ;# 
# 21596 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP3CAP equ 0F27h ;# 
# 21724 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8TMR equ 0F28h ;# 
# 21729 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR8 equ 0F28h ;# 
# 21778 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8PR equ 0F29h ;# 
# 21783 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR8 equ 0F29h ;# 
# 21832 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8CON equ 0F2Ah ;# 
# 21978 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8HLT equ 0F2Bh ;# 
# 22106 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8CLKCON equ 0F2Ch ;# 
# 22186 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T8RST equ 0F2Dh ;# 
# 22266 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR7 equ 0F2Eh ;# 
# 22273 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR7L equ 0F2Eh ;# 
# 22443 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR7H equ 0F2Fh ;# 
# 22563 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7CON equ 0F30h ;# 
# 22677 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7GCON equ 0F31h ;# 
# 22682 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR7 equ 0F31h ;# 
# 22909 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7GATE equ 0F32h ;# 
# 22914 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR7GATE equ 0F32h ;# 
# 23075 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T7CLK equ 0F33h ;# 
# 23080 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR7CLK equ 0F33h ;# 
# 23217 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CLKRCON equ 0F34h ;# 
# 23321 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CLKRCLK equ 0F35h ;# 
# 23381 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1CLK equ 0F36h ;# 
# 23386 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1CLKCON equ 0F36h ;# 
# 23435 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1ISM equ 0F37h ;# 
# 23481 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1DBR equ 0F38h ;# 
# 23585 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1DBF equ 0F39h ;# 
# 23689 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1CON0 equ 0F3Ah ;# 
# 23790 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1CON1 equ 0F3Bh ;# 
# 23868 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1AS0 equ 0F3Ch ;# 
# 23988 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1AS1 equ 0F3Dh ;# 
# 24050 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CWG1STR equ 0F3Eh ;# 
# 24162 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCDATA equ 0F3Fh ;# 
# 24169 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCDATL equ 0F3Fh ;# 
# 24231 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCDATH equ 0F40h ;# 
# 24293 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCACC equ 0F41h ;# 
# 24300 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCACCL equ 0F41h ;# 
# 24362 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCACCH equ 0F42h ;# 
# 24424 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCSHFT equ 0F43h ;# 
# 24431 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCSHIFTL equ 0F43h ;# 
# 24493 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCSHIFTH equ 0F44h ;# 
# 24555 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCXOR equ 0F45h ;# 
# 24562 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCXORL equ 0F45h ;# 
# 24619 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCXORH equ 0F46h ;# 
# 24681 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCCON0 equ 0F47h ;# 
# 24741 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CRCCON1 equ 0F48h ;# 
# 24819 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANLADR equ 0F49h ;# 
# 24826 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANLADRL equ 0F49h ;# 
# 24954 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANLADRH equ 0F4Ah ;# 
# 25082 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANLADRU equ 0F4Bh ;# 
# 25188 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANHADR equ 0F4Ch ;# 
# 25195 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANHADRL equ 0F4Ch ;# 
# 25323 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANHADRH equ 0F4Dh ;# 
# 25451 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANHADRU equ 0F4Eh ;# 
# 25555 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANCON0 equ 0F4Fh ;# 
# 25682 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SCANTRIG equ 0F50h ;# 
# 25762 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCON0 equ 0F51h ;# 
# 25830 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCON1 equ 0F52h ;# 
# 25896 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDSRC equ 0F53h ;# 
# 25976 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCARL equ 0F54h ;# 
# 26044 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
MDCARH equ 0F55h ;# 
# 26112 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACT equ 0F56h ;# 
# 26164 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCLK equ 0F57h ;# 
# 26222 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADREF equ 0F58h ;# 
# 26263 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCON1 equ 0F59h ;# 
# 26302 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCON2 equ 0F5Ah ;# 
# 26379 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCON3 equ 0F5Bh ;# 
# 26450 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACQ equ 0F5Ch ;# 
# 26520 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCAP equ 0F5Dh ;# 
# 26572 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADPRE equ 0F5Eh ;# 
# 26642 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADPCH equ 0F5Fh ;# 
# 26700 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCON0 equ 0F60h ;# 
# 26795 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADPREV equ 0F61h ;# 
# 26802 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADPREVL equ 0F61h ;# 
# 26872 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADPREVH equ 0F62h ;# 
# 26942 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADRES equ 0F63h ;# 
# 26949 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADRESL equ 0F63h ;# 
# 27019 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADRESH equ 0F64h ;# 
# 27081 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADSTAT equ 0F65h ;# 
# 27146 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADRPT equ 0F66h ;# 
# 27216 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADCNT equ 0F67h ;# 
# 27286 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADSTPT equ 0F68h ;# 
# 27293 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADSTPTL equ 0F68h ;# 
# 27363 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADSTPTH equ 0F69h ;# 
# 27433 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADLTH equ 0F6Ah ;# 
# 27440 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADLTHL equ 0F6Ah ;# 
# 27510 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADLTHH equ 0F6Bh ;# 
# 27580 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADUTH equ 0F6Ch ;# 
# 27587 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADUTHL equ 0F6Ch ;# 
# 27657 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADUTHH equ 0F6Dh ;# 
# 27727 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADERR equ 0F6Eh ;# 
# 27734 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADERRL equ 0F6Eh ;# 
# 27804 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADERRH equ 0F6Fh ;# 
# 27874 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACC equ 0F70h ;# 
# 27881 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACCL equ 0F70h ;# 
# 27951 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADACCH equ 0F71h ;# 
# 28021 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADFLTR equ 0F72h ;# 
# 28028 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADFLTRL equ 0F72h ;# 
# 28098 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
ADFLTRH equ 0F73h ;# 
# 28168 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMADR equ 0F74h ;# 
# 28175 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMADRL equ 0F74h ;# 
# 28303 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMADRH equ 0F75h ;# 
# 28359 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMDAT equ 0F76h ;# 
# 28429 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMCON1 equ 0F77h ;# 
# 28495 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
NVMCON2 equ 0F78h ;# 
# 28515 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATA equ 0F79h ;# 
# 28627 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATB equ 0F7Ah ;# 
# 28739 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATC equ 0F7Bh ;# 
# 28851 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATD equ 0F7Ch ;# 
# 28963 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATE equ 0F7Dh ;# 
# 29075 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATF equ 0F7Eh ;# 
# 29187 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATG equ 0F7Fh ;# 
# 29276 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
LATH equ 0F80h ;# 
# 29376 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISA equ 0F81h ;# 
# 29381 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DDRA equ 0F81h ;# 
# 29498 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISB equ 0F82h ;# 
# 29503 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DDRB equ 0F82h ;# 
# 29620 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISC equ 0F83h ;# 
# 29625 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DDRC equ 0F83h ;# 
# 29742 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISD equ 0F84h ;# 
# 29747 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DDRD equ 0F84h ;# 
# 29864 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISE equ 0F85h ;# 
# 29869 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
DDRE equ 0F85h ;# 
# 29986 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISF equ 0F86h ;# 
# 30048 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISG equ 0F87h ;# 
# 30105 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TRISH equ 0F88h ;# 
# 30143 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTA equ 0F89h ;# 
# 30227 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTB equ 0F8Ah ;# 
# 30298 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTC equ 0F8Bh ;# 
# 30384 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTD equ 0F8Ch ;# 
# 30455 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTE equ 0F8Dh ;# 
# 30626 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTF equ 0F8Eh ;# 
# 30703 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTG equ 0F8Fh ;# 
# 30781 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PORTH equ 0F90h ;# 
# 30819 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1BUF equ 0F91h ;# 
# 30839 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1ADD equ 0F92h ;# 
# 30959 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1MSK equ 0F93h ;# 
# 31029 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1STAT equ 0F94h ;# 
# 31483 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1CON1 equ 0F95h ;# 
# 31603 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1CON2 equ 0F96h ;# 
# 31790 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SSP1CON3 equ 0F97h ;# 
# 31852 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC1REG equ 0F98h ;# 
# 31857 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG equ 0F98h ;# 
# 31861 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCREG1 equ 0F98h ;# 
# 31906 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX1REG equ 0F99h ;# 
# 31911 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG1 equ 0F99h ;# 
# 31915 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXREG equ 0F99h ;# 
# 31960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP1BRG equ 0F9Ah ;# 
# 31967 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP1BRGL equ 0F9Ah ;# 
# 31972 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG equ 0F9Ah ;# 
# 31976 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRG1 equ 0F9Ah ;# 
# 31980 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGL equ 0F9Ah ;# 
# 32037 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SP1BRGH equ 0F9Bh ;# 
# 32042 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH equ 0F9Bh ;# 
# 32046 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
SPBRGH1 equ 0F9Bh ;# 
# 32091 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RC1STA equ 0F9Ch ;# 
# 32096 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA1 equ 0F9Ch ;# 
# 32100 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
RCSTA equ 0F9Ch ;# 
# 32376 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TX1STA equ 0F9Dh ;# 
# 32381 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA1 equ 0F9Dh ;# 
# 32385 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TXSTA equ 0F9Dh ;# 
# 32820 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUD1CON equ 0F9Eh ;# 
# 32825 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON1 equ 0F9Eh ;# 
# 32829 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL1 equ 0F9Eh ;# 
# 32833 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCON equ 0F9Eh ;# 
# 32837 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BAUDCTL equ 0F9Eh ;# 
# 33601 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM7DC equ 0F9Fh ;# 
# 33608 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM7DCL equ 0F9Fh ;# 
# 33674 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM7DCH equ 0FA0h ;# 
# 33844 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM7CON equ 0FA1h ;# 
# 33910 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM6DC equ 0FA2h ;# 
# 33917 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM6DCL equ 0FA2h ;# 
# 33983 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM6DCH equ 0FA3h ;# 
# 34153 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PWM6CON equ 0FA4h ;# 
# 34219 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR2 equ 0FA5h ;# 
# 34226 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR2L equ 0FA5h ;# 
# 34246 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR2H equ 0FA6h ;# 
# 34266 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP2CON equ 0FA7h ;# 
# 34393 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP2CAP equ 0FA8h ;# 
# 34449 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR1 equ 0FA9h ;# 
# 34456 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR1L equ 0FA9h ;# 
# 34476 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPR1H equ 0FAAh ;# 
# 34496 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP1CON equ 0FABh ;# 
# 34623 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCP1CAP equ 0FACh ;# 
# 34679 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPTMRS0 equ 0FADh ;# 
# 34767 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
CCPTMRS1 equ 0FAEh ;# 
# 34837 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6TMR equ 0FAFh ;# 
# 34842 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR6 equ 0FAFh ;# 
# 34891 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6PR equ 0FB0h ;# 
# 34896 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR6 equ 0FB0h ;# 
# 34945 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6CON equ 0FB1h ;# 
# 35091 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6HLT equ 0FB2h ;# 
# 35219 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6CLKCON equ 0FB3h ;# 
# 35299 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T6RST equ 0FB4h ;# 
# 35379 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4TMR equ 0FB5h ;# 
# 35384 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR4 equ 0FB5h ;# 
# 35433 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4PR equ 0FB6h ;# 
# 35438 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR4 equ 0FB6h ;# 
# 35487 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4CON equ 0FB7h ;# 
# 35633 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4HLT equ 0FB8h ;# 
# 35761 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4CLKCON equ 0FB9h ;# 
# 35841 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T4RST equ 0FBAh ;# 
# 35921 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2TMR equ 0FBBh ;# 
# 35926 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR2 equ 0FBBh ;# 
# 35975 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2PR equ 0FBCh ;# 
# 35980 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR2 equ 0FBCh ;# 
# 36029 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2CON equ 0FBDh ;# 
# 36175 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2HLT equ 0FBEh ;# 
# 36303 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2CLKCON equ 0FBFh ;# 
# 36383 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T2RST equ 0FC0h ;# 
# 36463 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR5 equ 0FC1h ;# 
# 36470 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR5L equ 0FC1h ;# 
# 36640 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR5H equ 0FC2h ;# 
# 36760 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5CON equ 0FC3h ;# 
# 36874 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5GCON equ 0FC4h ;# 
# 36879 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR5 equ 0FC4h ;# 
# 37106 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5GATE equ 0FC5h ;# 
# 37111 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR5GATE equ 0FC5h ;# 
# 37248 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T5CLK equ 0FC6h ;# 
# 37253 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR5CLK equ 0FC6h ;# 
# 37390 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR3 equ 0FC7h ;# 
# 37397 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR3L equ 0FC7h ;# 
# 37567 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR3H equ 0FC8h ;# 
# 37687 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3CON equ 0FC9h ;# 
# 37801 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3GCON equ 0FCAh ;# 
# 37806 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR3 equ 0FCAh ;# 
# 38033 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3GATE equ 0FCBh ;# 
# 38038 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR3GATE equ 0FCBh ;# 
# 38175 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T3CLK equ 0FCCh ;# 
# 38180 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR3CLK equ 0FCCh ;# 
# 38317 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR1 equ 0FCDh ;# 
# 38324 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR1L equ 0FCDh ;# 
# 38494 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR1H equ 0FCEh ;# 
# 38614 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1CON equ 0FCFh ;# 
# 38728 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1GCON equ 0FD0h ;# 
# 38733 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR1 equ 0FD0h ;# 
# 38960 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1GATE equ 0FD1h ;# 
# 38965 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR1GATE equ 0FD1h ;# 
# 39102 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T1CLK equ 0FD2h ;# 
# 39107 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR1CLK equ 0FD2h ;# 
# 39244 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR0L equ 0FD3h ;# 
# 39249 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR0 equ 0FD3h ;# 
# 39382 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TMR0H equ 0FD4h ;# 
# 39387 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PR0 equ 0FD4h ;# 
# 39636 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T0CON0 equ 0FD5h ;# 
# 39701 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
T0CON1 equ 0FD6h ;# 
# 39812 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PCON0 equ 0FD7h ;# 
# 39965 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
STATUS equ 0FD8h ;# 
# 40081 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR2 equ 0FD9h ;# 
# 40088 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR2L equ 0FD9h ;# 
# 40108 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR2H equ 0FDAh ;# 
# 40115 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PLUSW2 equ 0FDBh ;# 
# 40135 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PREINC2 equ 0FDCh ;# 
# 40155 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTDEC2 equ 0FDDh ;# 
# 40175 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTINC2 equ 0FDEh ;# 
# 40195 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INDF2 equ 0FDFh ;# 
# 40215 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
BSR equ 0FE0h ;# 
# 40222 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR1 equ 0FE1h ;# 
# 40229 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR1L equ 0FE1h ;# 
# 40249 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR1H equ 0FE2h ;# 
# 40256 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PLUSW1 equ 0FE3h ;# 
# 40276 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PREINC1 equ 0FE4h ;# 
# 40296 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTDEC1 equ 0FE5h ;# 
# 40316 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTINC1 equ 0FE6h ;# 
# 40336 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INDF1 equ 0FE7h ;# 
# 40356 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
WREG equ 0FE8h ;# 
# 40394 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR0 equ 0FE9h ;# 
# 40401 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR0L equ 0FE9h ;# 
# 40421 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
FSR0H equ 0FEAh ;# 
# 40428 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PLUSW0 equ 0FEBh ;# 
# 40448 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PREINC0 equ 0FECh ;# 
# 40468 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTDEC0 equ 0FEDh ;# 
# 40488 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
POSTINC0 equ 0FEEh ;# 
# 40508 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INDF0 equ 0FEFh ;# 
# 40528 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
INTCON equ 0FF2h ;# 
# 40615 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PROD equ 0FF3h ;# 
# 40622 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PRODL equ 0FF3h ;# 
# 40642 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PRODH equ 0FF4h ;# 
# 40662 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TABLAT equ 0FF5h ;# 
# 40684 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TBLPTR equ 0FF6h ;# 
# 40691 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TBLPTRL equ 0FF6h ;# 
# 40711 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TBLPTRH equ 0FF7h ;# 
# 40731 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TBLPTRU equ 0FF8h ;# 
# 40762 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PCLAT equ 0FF9h ;# 
# 40769 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PC equ 0FF9h ;# 
# 40776 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PCL equ 0FF9h ;# 
# 40796 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PCLATH equ 0FFAh ;# 
# 40816 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
PCLATU equ 0FFBh ;# 
# 40836 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
STKPTR equ 0FFCh ;# 
# 40934 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TOS equ 0FFDh ;# 
# 40941 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TOSL equ 0FFDh ;# 
# 40961 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TOSH equ 0FFEh ;# 
# 40981 "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\include\pic18f67k40.h"
TOSU equ 0FFFh ;# 
	FNCALL	_main,_delay_ms
	FNROOT	_main
	FNCALL	intlevel2,_myisr
	global	intlevel2
	FNROOT	intlevel2
	global	_FCV_COUNT
psect	nvCOMRAM,class=COMRAM,space=1,noexec
global __pnvCOMRAM
__pnvCOMRAM:
	global	_FCV_COUNT
_FCV_COUNT:
       ds      2
	global	_RG2PPS
_RG2PPS	set	0xE84
	global	_RX5PPS
_RX5PPS	set	0xE17
	global	_RG0PPS
_RG0PPS	set	0xE82
	global	_RX2PPS
_RX2PPS	set	0xE11
	global	_ANSELG
_ANSELG	set	0xEBC
	global	_ANSELF
_ANSELF	set	0xEB4
	global	_ANSELE
_ANSELE	set	0xEAF
	global	_ANSELD
_ANSELD	set	0xEA7
	global	_ANSELB
_ANSELB	set	0xE9A
	global	_ANSELA
_ANSELA	set	0xE92
	global	_PORTF
_PORTF	set	0xF8E
	global	_TRISF
_TRISF	set	0xF86
	global	_PORTE
_PORTE	set	0xF8D
	global	_TRISE
_TRISE	set	0xF85
	global	_PORTD
_PORTD	set	0xF8C
	global	_TRISD
_TRISD	set	0xF84
	global	_PORTC
_PORTC	set	0xF8B
	global	_TRISC
_TRISC	set	0xF83
	global	_PORTB
_PORTB	set	0xF8A
	global	_TRISB
_TRISB	set	0xF82
	global	_PORTA
_PORTA	set	0xF89
	global	_TRISA
_TRISA	set	0xF81
; #config settings
	file	"Counter - PIC.as"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect	bssCOMRAM,class=COMRAM,space=1,noexec
global __pbssCOMRAM
__pbssCOMRAM:
	global	_errno
_errno:
       ds      2
	global	_FCI_TMP_INT
	global	_FCI_TMP_INT
_FCI_TMP_INT:
       ds      2
	file	"Counter - PIC.as"
	line	#
psect	cinit
; Clear objects allocated to COMRAM (4 bytes)
	global __pbssCOMRAM
clrf	(__pbssCOMRAM+3)&0xffh,c
clrf	(__pbssCOMRAM+2)&0xffh,c
clrf	(__pbssCOMRAM+1)&0xffh,c
clrf	(__pbssCOMRAM+0)&0xffh,c
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
	bcf int$flags,0,c ;clear compiler interrupt flag (level 1)
	bcf int$flags,1,c ;clear compiler interrupt flag (level 2)
movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_delay_ms:	; 1 bytes @ 0x0
??_delay_ms:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
?_myisr:	; 1 bytes @ 0x0
??_myisr:	; 1 bytes @ 0x0
	ds   1
	global	delay_ms@del
delay_ms@del:	; 1 bytes @ 0x1
	ds   1
??_main:	; 1 bytes @ 0x2
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    0
;!    Data        0
;!    BSS         4
;!    Persistent  2
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           94      2       8
;!    BANK0           160      0       0
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0
;!    BANK8           256      0       0
;!    BANK9           256      0       0
;!    BANK10          256      0       0
;!    BANK11          256      0       0
;!    BANK12          256      0       0
;!    BANK13          234      0       0

;!
;!Pointer List with Targets:
;!
;!    sp__FCI_NUMBER_TO_HEX	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_FLOAT_TO_STRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMFLOATARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_TOSTRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMINTARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_RIGHTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_LEFTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_MIDSTRING	PTR unsigned char  size(2) Largest target is 0
;!


;!
;!Critical Paths under _main in COMRAM
;!
;!    _main->_delay_ms
;!
;!Critical Paths under _myisr in COMRAM
;!
;!    None.
;!
;!Critical Paths under _main in BANK0
;!
;!    None.
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
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK7
;!
;!    None.
;!
;!Critical Paths under _main in BANK8
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK8
;!
;!    None.
;!
;!Critical Paths under _main in BANK9
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK9
;!
;!    None.
;!
;!Critical Paths under _main in BANK10
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK10
;!
;!    None.
;!
;!Critical Paths under _main in BANK11
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK11
;!
;!    None.
;!
;!Critical Paths under _main in BANK12
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK12
;!
;!    None.
;!
;!Critical Paths under _main in BANK13
;!
;!    None.
;!
;!Critical Paths under _myisr in BANK13
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
;! (0) _main                                                 0     0      0      15
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) _delay_ms                                             2     2      0      15
;!                                              0 COMRAM     2     2      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 1
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (2) _myisr                                                0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 2
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _delay_ms
;!
;! _myisr (ROOT)
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BIGRAM             DE9      0       0      33        0.0%
;!EEDATA             400      0       0       0        0.0%
;!BITBANK12          100      0       0      29        0.0%
;!BANK12             100      0       0      30        0.0%
;!BITBANK11          100      0       0      27        0.0%
;!BANK11             100      0       0      28        0.0%
;!BITBANK10          100      0       0      25        0.0%
;!BANK10             100      0       0      26        0.0%
;!BITBANK9           100      0       0      23        0.0%
;!BANK9              100      0       0      24        0.0%
;!BITBANK8           100      0       0      21        0.0%
;!BANK8              100      0       0      22        0.0%
;!BITBANK7           100      0       0      19        0.0%
;!BANK7              100      0       0      20        0.0%
;!BITBANK6           100      0       0      17        0.0%
;!BANK6              100      0       0      18        0.0%
;!BITBANK5           100      0       0      15        0.0%
;!BANK5              100      0       0      16        0.0%
;!BITBANK4           100      0       0      13        0.0%
;!BANK4              100      0       0      14        0.0%
;!BITBANK3           100      0       0      11        0.0%
;!BANK3              100      0       0      12        0.0%
;!BITBANK2           100      0       0       9        0.0%
;!BANK2              100      0       0      10        0.0%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!BITBANK13           EA      0       0      31        0.0%
;!BANK13              EA      0       0      32        0.0%
;!BITBANK0            A0      0       0       4        0.0%
;!BANK0               A0      0       0       5        0.0%
;!BITCOMRAM           5E      0       0       0        0.0%
;!COMRAM              5E      2       8       1        8.5%
;!BITSFR_3             0      0       0     200        0.0%
;!SFR_3                0      0       0     200        0.0%
;!BITSFR_2             0      0       0     200        0.0%
;!SFR_2                0      0       0     200        0.0%
;!BITSFR_1             0      0       0     200        0.0%
;!SFR_1                0      0       0     200        0.0%
;!BITSFR               0      0       0     200        0.0%
;!SFR                  0      0       0     200        0.0%
;!STACK                0      0       0       2        0.0%
;!NULL                 0      0       0       0        0.0%
;!ABS                  0      0       8       8        0.0%
;!DATA                 0      0       8       3        0.0%
;!CODE                 0      0       0       0        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 623 in file "Counter - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay_ms
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2,group=0
	file	"Counter - PIC.c"
	line	623
global __ptext0
__ptext0:
psect	text0
	file	"Counter - PIC.c"
	line	623
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	callstack 29
	line	629
	
l1685:
	movlw	low(0)
	movlb	14	; () banked
	movwf	((3730))&0ffh	;volatile
	line	630
	movlw	low(0)
	movwf	((3738))&0ffh	;volatile
	line	631
	movlw	low(0)
	movwf	((3751))&0ffh	;volatile
	line	632
	movlw	low(0)
	movwf	((3759))&0ffh	;volatile
	line	633
	movlw	low(0)
	movwf	((3764))&0ffh	;volatile
	line	634
	movlw	low(0)
	movwf	((3772))&0ffh	;volatile
	line	637
	movlw	low(031h)
	movwf	((3601))&0ffh	;volatile
	line	638
	movlw	low(0Eh)
	movwf	((3714))&0ffh	;volatile
	line	639
	movlw	low(033h)
	movwf	((3607))&0ffh	;volatile
	line	640
	movlw	low(014h)
	movwf	((3716))&0ffh	;volatile
	line	646
	
l895:
	line	649
	movlw	low(0)
	movwf	((c:3969))^0f00h,c	;volatile
	
l1687:
	movff	(c:_FCV_COUNT),(c:3977)	;volatile
	line	652
	movlw	low(0)
	movwf	((c:3970))^0f00h,c	;volatile
	
l1689:
	movff	(c:_FCV_COUNT),(c:3978)	;volatile
	line	655
	movlw	low(0)
	movwf	((c:3971))^0f00h,c	;volatile
	
l1691:
	movff	(c:_FCV_COUNT),(c:3979)	;volatile
	line	658
	movlw	low(0)
	movwf	((c:3972))^0f00h,c	;volatile
	
l1693:
	movff	(c:_FCV_COUNT),(c:3980)	;volatile
	line	661
	movlw	low(0)
	movwf	((c:3973))^0f00h,c	;volatile
	
l1695:
	movff	(c:_FCV_COUNT),(c:3981)	;volatile
	line	664
	movlw	low(0)
	movwf	((c:3974))^0f00h,c	;volatile
	
l1697:
	movff	(c:_FCV_COUNT),(c:3982)	;volatile
	line	667
	
l1699:
	movlw	low(01h)
	addwf	((c:_FCV_COUNT))^00h,c,w	;volatile
	movwf	((c:_FCV_COUNT))^00h,c	;volatile
	movlw	high(01h)
	addwfc	((c:_FCV_COUNT+1))^00h,c,w	;volatile
	movwf	1+((c:_FCV_COUNT))^00h,c	;volatile
	line	670
	
l1701:
	movlw	(0Ah)&0ffh
	
	call	_delay_ms
	goto	l895
	global	start
	goto	start
	opt callstack 0
	line	675
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_delay_ms

;; *************** function _delay_ms *****************
;; Defined at:
;;		line 105 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    1[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
global __ptext1
__ptext1:
psect	text1
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:
;incstack = 0
	opt	callstack 29
	movwf	((c:delay_ms@del))^00h,c
	line	107
	
l1679:
	goto	l1683
	line	109
	
l1681:
	opt asmopt_push
opt asmopt_off
movlw	21
movwf	(??_delay_ms+0+0)^00h,c,f
	movlw	198
u27:
decfsz	wreg,f
	bra	u27
	decfsz	(??_delay_ms+0+0)^00h,c,f
	bra	u27
	nop2
opt asmopt_pop

	line	107
	
l1683:
	decf	((c:delay_ms@del))^00h,c
		incf	((c:delay_ms@del))^00h,c,w
	btfss	status,2
	goto	u11
	goto	u10

u11:
	goto	l1681
u10:
	line	111
	
l90:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4217
	global	_myisr

;; *************** function _myisr *****************
;; Defined at:
;;		line 682 in file "Counter - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 2
;; This function uses a non-reentrant model
;;
psect	intcode,class=CODE,space=0,reloc=2
	file	"Counter - PIC.as"
	line	#
global __pintcode
__pintcode:
psect	intcode
	file	"Counter - PIC.c"
	line	682
	global	__size_of_myisr
	__size_of_myisr	equ	__end_of_myisr-_myisr
	
_myisr:
;incstack = 0
	opt	callstack 29
	bsf int$flags,1,c ;set compiler interrupt flag (level 2)
	line	688
	
i2l904:
	bcf int$flags,1,c ;clear compiler interrupt flag (level 2)
	retfie f
	opt callstack 0
GLOBAL	__end_of_myisr
	__end_of_myisr:
	signat	_myisr,89
	GLOBAL	__activetblptr
__activetblptr	EQU	0
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
	GLOBAL	___rparam_used
	___rparam_used EQU 1
	GLOBAL	___param_bank
	___param_bank EQU 0
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
       psect   temp,common,ovrld,class=COMRAM,space=1
	global	btemp
btemp:
	ds	1
	global	int$flags
	int$flags	set btemp
	global	wtemp8
	wtemp8 set btemp+1
	global	ttemp5
	ttemp5 set btemp+1
	global	ttemp6
	ttemp6 set btemp+4
	global	ttemp7
	ttemp7 set btemp+8
	end
