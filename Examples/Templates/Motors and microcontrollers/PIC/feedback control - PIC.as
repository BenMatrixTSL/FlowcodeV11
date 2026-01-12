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
	FNCALL	_main,_FCD_00a21_Potentiometer1__GetByte
	FNCALL	_main,_FCD_026e1_Timer1__StartCounter
	FNCALL	_main,_FCD_04891_DCMotor1__Enable
	FNCALL	_main,_FCD_04891_DCMotor1__Forwards
	FNCALL	_main,_FCD_049e1_LCD_BL0169__Clear
	FNCALL	_main,_FCD_049e1_LCD_BL0169__Start
	FNCALL	_main,_FCM_update_display
	FNCALL	_main,___fldiv
	FNCALL	_main,___flmul
	FNCALL	_main,_delay_ms
	FNCALL	_main,_delay_s
	FNCALL	_delay_s,_delay_ms
	FNCALL	_FCM_update_display,_FCD_049e1_LCD_BL0169__Cursor
	FNCALL	_FCM_update_display,_FCD_049e1_LCD_BL0169__PrintFloat
	FNCALL	_FCM_update_display,_FCD_049e1_LCD_BL0169__PrintNumber
	FNCALL	_FCM_update_display,_FCD_049e1_LCD_BL0169__PrintString
	FNCALL	_FCD_049e1_LCD_BL0169__PrintNumber,_FCD_04071_LCD1__PrintNumber
	FNCALL	_FCD_04071_LCD1__PrintNumber,_FCD_04071_LCD1__PrintString
	FNCALL	_FCD_04071_LCD1__PrintNumber,_FCI_TOSTRING
	FNCALL	_FCI_TOSTRING,___lldiv
	FNCALL	_FCI_TOSTRING,___lmul
	FNCALL	_FCD_049e1_LCD_BL0169__PrintFloat,_FCD_049e1_LCD_BL0169__PrintString
	FNCALL	_FCD_049e1_LCD_BL0169__PrintFloat,_FCI_FLOAT_TO_STRING
	FNCALL	_FCI_FLOAT_TO_STRING,___aldiv
	FNCALL	_FCI_FLOAT_TO_STRING,___almod
	FNCALL	_FCI_FLOAT_TO_STRING,___fladd
	FNCALL	_FCI_FLOAT_TO_STRING,___flmul
	FNCALL	_FCI_FLOAT_TO_STRING,___flneg
	FNCALL	_FCI_FLOAT_TO_STRING,___flsub
	FNCALL	_FCI_FLOAT_TO_STRING,___fltol
	FNCALL	_FCI_FLOAT_TO_STRING,___xxtofl
	FNCALL	_FCI_FLOAT_TO_STRING,_floor
	FNCALL	_floor,___fladd
	FNCALL	_floor,___flge
	FNCALL	_floor,___fltol
	FNCALL	_floor,___xxtofl
	FNCALL	_floor,_frexp
	FNCALL	_frexp,___fleq
	FNCALL	___flsub,___fladd
	FNCALL	_FCD_049e1_LCD_BL0169__PrintString,_FCD_04071_LCD1__PrintString
	FNCALL	_FCD_04071_LCD1__PrintString,_FCD_04071_LCD1__RawSend
	FNCALL	_FCD_04071_LCD1__PrintString,_FCI_GETLENGTH
	FNCALL	_FCD_049e1_LCD_BL0169__Cursor,_FCD_04071_LCD1__Cursor
	FNCALL	_FCD_04071_LCD1__Cursor,_FCD_04071_LCD1__RawSend
	FNCALL	_FCD_04071_LCD1__Cursor,_delay_ms
	FNCALL	_FCD_049e1_LCD_BL0169__Start,_FCD_04071_LCD1__Start
	FNCALL	_FCD_04071_LCD1__Start,_FCD_04071_LCD1__Clear
	FNCALL	_FCD_04071_LCD1__Start,_FCD_04071_LCD1__RawSend
	FNCALL	_FCD_04071_LCD1__Start,_delay_ms
	FNCALL	_FCD_049e1_LCD_BL0169__Clear,_FCD_04071_LCD1__Clear
	FNCALL	_FCD_04071_LCD1__Clear,_FCD_04071_LCD1__RawSend
	FNCALL	_FCD_04071_LCD1__Clear,_delay_ms
	FNCALL	_FCD_04071_LCD1__RawSend,_delay_us
	FNCALL	_FCD_04891_DCMotor1__Enable,_FCD_00a91_TimedInterval1__StartTimerInterval
	FNCALL	_FCD_026e1_Timer1__StartCounter,_FCD_026e1_Timer1__ResetCounter
	FNCALL	_FCD_026e1_Timer1__StartCounter,_FCD_026e1_Timer1__RestoreCounter
	FNCALL	_FCD_00a21_Potentiometer1__GetByte,_FCD_0cc51_adc_base1__GetByte
	FNCALL	_FCD_0cc51_adc_base1__GetByte,_FC_CAL_ADC_Disable_1
	FNCALL	_FCD_0cc51_adc_base1__GetByte,_FC_CAL_ADC_Enable_1
	FNCALL	_FCD_0cc51_adc_base1__GetByte,_FC_CAL_ADC_Sample_1
	FNCALL	_FC_CAL_ADC_Enable_1,_delay_us
	FNROOT	_main
	FNCALL	_myisr,_FCD_04891_DCMotor1__TimerRoutine
	FNCALL	_myisr,_FCM_feedback_interrupt
	FNCALL	_FCM_feedback_interrupt,_FCD_026e1_Timer1__GetCountReal
	FNCALL	_FCM_feedback_interrupt,i2_FCD_026e1_Timer1__ResetCounter
	FNCALL	_FCD_026e1_Timer1__GetCountReal,_FCD_026e1_Timer1__GetRawCount
	FNCALL	_FCD_026e1_Timer1__GetCountReal,i2___fldiv
	FNCALL	_FCD_026e1_Timer1__GetCountReal,i2___flmul
	FNCALL	_FCD_026e1_Timer1__GetCountReal,i2___xxtofl
	FNCALL	intlevel2,_myisr
	global	intlevel2
	FNROOT	intlevel2
psect	mediumconst,class=MEDIUMCONST,space=0,reloc=2,noexec
global __pmediumconst
__pmediumconst:
	db	0
	file	"feedback control - PIC.c"
	line	1870
_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT:
	db	low(0)
	db	low(06h)
	db	low(05Fh)
	db	low(06h)
	db	low(0)
	db	low(07h)
	db	low(03h)
	db	low(0)
	db	low(07h)
	db	low(03h)
	db	low(024h)
	db	low(07Eh)
	db	low(024h)
	db	low(07Eh)
	db	low(024h)
	db	low(024h)
	db	low(02Bh)
	db	low(06Ah)
	db	low(012h)
	db	low(0)
	db	low(063h)
	db	low(013h)
	db	low(08h)
	db	low(064h)
	db	low(063h)
	db	low(036h)
	db	low(049h)
	db	low(056h)
	db	low(020h)
	db	low(050h)
	db	low(0)
	db	low(07h)
	db	low(03h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(03Eh)
	db	low(041h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(041h)
	db	low(03Eh)
	db	low(0)
	db	low(0)
	db	low(08h)
	db	low(03Eh)
	db	low(01Ch)
	db	low(03Eh)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(03Eh)
	db	low(08h)
	db	low(08h)
	db	low(0)
	db	low(0E0h)
	db	low(060h)
	db	low(0)
	db	low(0)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0)
	db	low(060h)
	db	low(060h)
	db	low(0)
	db	low(0)
	db	low(020h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(02h)
	db	low(03Eh)
	db	low(051h)
	db	low(049h)
	db	low(045h)
	db	low(03Eh)
	db	low(0)
	db	low(042h)
	db	low(07Fh)
	db	low(040h)
	db	low(0)
	db	low(062h)
	db	low(051h)
	db	low(049h)
	db	low(049h)
	db	low(046h)
	db	low(022h)
	db	low(049h)
	db	low(049h)
	db	low(049h)
	db	low(036h)
	db	low(018h)
	db	low(014h)
	db	low(012h)
	db	low(07Fh)
	db	low(010h)
	db	low(027h)
	db	low(045h)
	db	low(045h)
	db	low(045h)
	db	low(039h)
	db	low(03Ch)
	db	low(04Ah)
	db	low(049h)
	db	low(049h)
	db	low(030h)
	db	low(01h)
	db	low(071h)
	db	low(09h)
	db	low(05h)
	db	low(03h)
	db	low(036h)
	db	low(049h)
	db	low(049h)
	db	low(049h)
	db	low(036h)
	db	low(06h)
	db	low(049h)
	db	low(049h)
	db	low(029h)
	db	low(01Eh)
	db	low(0)
	db	low(06Ch)
	db	low(06Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0ECh)
	db	low(06Ch)
	db	low(0)
	db	low(0)
	db	low(08h)
	db	low(014h)
	db	low(022h)
	db	low(041h)
	db	low(0)
	db	low(024h)
	db	low(024h)
	db	low(024h)
	db	low(024h)
	db	low(024h)
	db	low(0)
	db	low(041h)
	db	low(022h)
	db	low(014h)
	db	low(08h)
	db	low(02h)
	db	low(01h)
	db	low(059h)
	db	low(09h)
	db	low(06h)
	db	low(03Eh)
	db	low(041h)
	db	low(05Dh)
	db	low(055h)
	db	low(01Eh)
	db	low(07Eh)
	db	low(09h)
	db	low(09h)
	db	low(09h)
	db	low(07Eh)
	db	low(07Fh)
	db	low(049h)
	db	low(049h)
	db	low(049h)
	db	low(036h)
	db	low(03Eh)
	db	low(041h)
	db	low(041h)
	db	low(041h)
	db	low(022h)
	db	low(07Fh)
	db	low(041h)
	db	low(041h)
	db	low(041h)
	db	low(03Eh)
	db	low(07Fh)
	db	low(049h)
	db	low(049h)
	db	low(049h)
	db	low(041h)
	db	low(07Fh)
	db	low(09h)
	db	low(09h)
	db	low(09h)
	db	low(01h)
	db	low(03Eh)
	db	low(041h)
	db	low(049h)
	db	low(049h)
	db	low(07Ah)
	db	low(07Fh)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(07Fh)
	db	low(0)
	db	low(041h)
	db	low(07Fh)
	db	low(041h)
	db	low(0)
	db	low(030h)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(03Fh)
	db	low(07Fh)
	db	low(08h)
	db	low(014h)
	db	low(022h)
	db	low(041h)
	db	low(07Fh)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(07Fh)
	db	low(02h)
	db	low(04h)
	db	low(02h)
	db	low(07Fh)
	db	low(07Fh)
	db	low(02h)
	db	low(04h)
	db	low(08h)
	db	low(07Fh)
	db	low(03Eh)
	db	low(041h)
	db	low(041h)
	db	low(041h)
	db	low(03Eh)
	db	low(07Fh)
	db	low(09h)
	db	low(09h)
	db	low(09h)
	db	low(06h)
	db	low(03Eh)
	db	low(041h)
	db	low(051h)
	db	low(021h)
	db	low(05Eh)
	db	low(07Fh)
	db	low(09h)
	db	low(09h)
	db	low(019h)
	db	low(066h)
	db	low(026h)
	db	low(049h)
	db	low(049h)
	db	low(049h)
	db	low(032h)
	db	low(01h)
	db	low(01h)
	db	low(07Fh)
	db	low(01h)
	db	low(01h)
	db	low(03Fh)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(03Fh)
	db	low(01Fh)
	db	low(020h)
	db	low(040h)
	db	low(020h)
	db	low(01Fh)
	db	low(03Fh)
	db	low(040h)
	db	low(03Ch)
	db	low(040h)
	db	low(03Fh)
	db	low(063h)
	db	low(014h)
	db	low(08h)
	db	low(014h)
	db	low(063h)
	db	low(07h)
	db	low(08h)
	db	low(070h)
	db	low(08h)
	db	low(07h)
	db	low(071h)
	db	low(049h)
	db	low(045h)
	db	low(043h)
	db	low(0)
	db	low(0)
	db	low(07Fh)
	db	low(041h)
	db	low(041h)
	db	low(0)
	db	low(02h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(020h)
	db	low(0)
	db	low(041h)
	db	low(041h)
	db	low(07Fh)
	db	low(0)
	db	low(04h)
	db	low(02h)
	db	low(01h)
	db	low(02h)
	db	low(04h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(0)
	db	low(03h)
	db	low(07h)
	db	low(0)
	db	low(0)
	db	low(020h)
	db	low(054h)
	db	low(054h)
	db	low(054h)
	db	low(078h)
	db	low(07Fh)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(038h)
	db	low(038h)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(028h)
	db	low(038h)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(07Fh)
	db	low(038h)
	db	low(054h)
	db	low(054h)
	db	low(054h)
	db	low(018h)
	db	low(08h)
	db	low(07Eh)
	db	low(09h)
	db	low(09h)
	db	low(0)
	db	low(018h)
	db	low(0A4h)
	db	low(0A4h)
	db	low(0A4h)
	db	low(07Ch)
	db	low(07Fh)
	db	low(04h)
	db	low(04h)
	db	low(078h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(07Dh)
	db	low(0)
	db	low(0)
	db	low(040h)
	db	low(080h)
	db	low(084h)
	db	low(07Dh)
	db	low(0)
	db	low(07Fh)
	db	low(010h)
	db	low(028h)
	db	low(044h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(07Fh)
	db	low(040h)
	db	low(0)
	db	low(07Ch)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(078h)
	db	low(07Ch)
	db	low(04h)
	db	low(04h)
	db	low(078h)
	db	low(0)
	db	low(038h)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(038h)
	db	low(0FCh)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(038h)
	db	low(038h)
	db	low(044h)
	db	low(044h)
	db	low(044h)
	db	low(0FCh)
	db	low(044h)
	db	low(078h)
	db	low(044h)
	db	low(04h)
	db	low(08h)
	db	low(08h)
	db	low(054h)
	db	low(054h)
	db	low(054h)
	db	low(020h)
	db	low(04h)
	db	low(03Eh)
	db	low(044h)
	db	low(024h)
	db	low(0)
	db	low(03Ch)
	db	low(040h)
	db	low(020h)
	db	low(07Ch)
	db	low(0)
	db	low(01Ch)
	db	low(020h)
	db	low(040h)
	db	low(020h)
	db	low(01Ch)
	db	low(03Ch)
	db	low(060h)
	db	low(030h)
	db	low(060h)
	db	low(03Ch)
	db	low(06Ch)
	db	low(010h)
	db	low(010h)
	db	low(06Ch)
	db	low(0)
	db	low(09Ch)
	db	low(0A0h)
	db	low(060h)
	db	low(03Ch)
	db	low(0)
	db	low(064h)
	db	low(054h)
	db	low(054h)
	db	low(04Ch)
	db	low(0)
	db	low(08h)
	db	low(03Eh)
	db	low(041h)
	db	low(041h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(07Fh)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(041h)
	db	low(041h)
	db	low(03Eh)
	db	low(08h)
	db	low(02h)
	db	low(01h)
	db	low(02h)
	db	low(01h)
	db	low(0)
	db	low(06h)
	db	low(09h)
	db	low(09h)
	db	low(06h)
	db	low(0)
	global __end_of_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT
__end_of_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT:
	global	_FCV_00a91_TimedInterval1__INTCOUNT
	global	_FCV_00a21_Potentiometer1__H
	global	_TIM_2_COUNTER
	global	_FCV_04891_DCMotor1__SW_PWM_COUNT
	global	_FCV_00a21_Potentiometer1__CHANNEL
	global	_FCV_COUNT
	global	_FCV_09e51_gLCD_Font1__OLDCHAR
	global	_FCV_04891_DCMotor1__ENABLED
	global	_FCV_00a91_TimedInterval1__RUNNING
	global	_FCV_026e1_Timer1__RUNNING
	global	_FCV_RPM
	global	_FCV_09e51_gLCD_Font1__OLDPOSITION
	global	_FCV_04891_DCMotor1__SW_PWM_DUTY
	global	_FCV_026e1_Timer1__TCOUNTSAVE
	global	_FCV_DATAREADY
	global	_FCV_PWMVALUE
	global	_FCV_DISPLAYUPDATECOUNT
	global	_FCV_04891_DCMotor1__SW_PWM_STATE
	global	_FCV_REVOLUTIONTIME
	global	_INT3PPS
_INT3PPS	set	0xDF3
	global	_PIR5bits
_PIR5bits	set	0xE38
	global	_PIR0bits
_PIR0bits	set	0xE33
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
	global	_PIE0bits
_PIE0bits	set	0xE29
	global	_PIE5bits
_PIE5bits	set	0xE2E
	global	_ANSELA
_ANSELA	set	0xE92
	global	_ADPCH
_ADPCH	set	0xF5F
	global	_ADREF
_ADREF	set	0xF58
	global	_ADCLK
_ADCLK	set	0xF57
	global	_TMR0
_TMR0	set	0xFD3
	global	_LATB
_LATB	set	0xF7A
	global	_PORTB
_PORTB	set	0xF8A
	global	_TRISB
_TRISB	set	0xF82
	global	_LATE
_LATE	set	0xF7D
	global	_PORTE
_PORTE	set	0xF8D
	global	_TRISE
_TRISE	set	0xF85
	global	_T0CON0
_T0CON0	set	0xFD5
	global	_T0CON1
_T0CON1	set	0xFD6
	global	_TMR2
_TMR2	set	0xFBB
	global	_T2CLKCON
_T2CLKCON	set	0xFBF
	global	_T2CON
_T2CON	set	0xFBD
	global	_INTCONbits
_INTCONbits	set	0xFF2
	global	_ADRESL
_ADRESL	set	0xF63
	global	_ADRESH
_ADRESH	set	0xF64
	global	_ADCON0
_ADCON0	set	0xF60
	global	_TRISA
_TRISA	set	0xF81
	
STR_2:; BSR set to: 0

	db	70	;'F'
	db	111	;'o'
	db	114	;'r'
	db	119	;'w'
	db	97	;'a'
	db	114	;'r'
	db	100	;'d'
	db	115	;'s'
	db	32
	db	0
	
STR_4:; BSR set to: 0

	db	80	;'P'
	db	101	;'e'
	db	114	;'r'
	db	105	;'i'
	db	111	;'o'
	db	100	;'d'
	db	32
	db	0
	
STR_6:; BSR set to: 0

	db	82	;'R'
	db	80	;'P'
	db	77	;'M'
	db	32
	db	0
	
STR_3:; BSR set to: 0

	db	32
	db	32
	db	0
STR_5	equ	STR_3+0
STR_7	equ	STR_3+0
STR_1	equ	STR_3+2
; #config settings
	file	"feedback control - PIC.as"
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
	global	_FCV_00a91_TimedInterval1__INTCOUNT
_FCV_00a91_TimedInterval1__INTCOUNT:
       ds      4
	global	_FCV_00a21_Potentiometer1__H
	global	_FCV_00a21_Potentiometer1__H
_FCV_00a21_Potentiometer1__H:
       ds      4
	global	_TIM_2_COUNTER
_TIM_2_COUNTER:
       ds      4
	global	_FCLV_LOOP3
	global	_FCLV_LOOP3
_FCLV_LOOP3:
       ds      4
	global	_FCLV_LOOP2
	global	_FCLV_LOOP2
_FCLV_LOOP2:
       ds      4
	global	_FCLV_LOOP1
	global	_FCLV_LOOP1
_FCLV_LOOP1:
       ds      4
	global	_errno
_errno:
       ds      2
	global	_FCV_04891_DCMotor1__SW_PWM_COUNT
_FCV_04891_DCMotor1__SW_PWM_COUNT:
       ds      2
	global	_FCV_00a21_Potentiometer1__CHANNEL
	global	_FCV_00a21_Potentiometer1__CHANNEL
_FCV_00a21_Potentiometer1__CHANNEL:
       ds      2
	global	_FCI_TMP_INT
	global	_FCI_TMP_INT
_FCI_TMP_INT:
       ds      2
	global	_FCV_COUNT
_FCV_COUNT:
       ds      1
	global	_FCV_09e51_gLCD_Font1__OLDCHAR
_FCV_09e51_gLCD_Font1__OLDCHAR:
       ds      1
	global	_FCV_04891_DCMotor1__ENABLED
_FCV_04891_DCMotor1__ENABLED:
       ds      1
	global	_FCV_00a91_TimedInterval1__RUNNING
_FCV_00a91_TimedInterval1__RUNNING:
       ds      1
	global	_FCV_026e1_Timer1__RUNNING
_FCV_026e1_Timer1__RUNNING:
       ds      1
	global	_FCLV_LOOP5
	global	_FCLV_LOOP5
_FCLV_LOOP5:
       ds      1
	global	_FCLV_LOOP4
	global	_FCLV_LOOP4
_FCLV_LOOP4:
       ds      1
psect	bssBANK0,class=BANK0,space=1,noexec,lowdata
global __pbssBANK0
__pbssBANK0:
FCD_0ba71_Base_GLCD1__Prv_ReadFontFileHeader@F15312:
       ds      20
	global	_FCV_RPM
_FCV_RPM:
       ds      4
	global	_FCV_09e51_gLCD_Font1__OLDPOSITION
_FCV_09e51_gLCD_Font1__OLDPOSITION:
       ds      4
	global	_FCV_04891_DCMotor1__SW_PWM_DUTY
_FCV_04891_DCMotor1__SW_PWM_DUTY:
       ds      2
	global	_FCV_026e1_Timer1__TCOUNTSAVE
_FCV_026e1_Timer1__TCOUNTSAVE:
       ds      2
	global	_FCV_DATAREADY
_FCV_DATAREADY:
       ds      1
	global	_FCV_PWMVALUE
_FCV_PWMVALUE:
       ds      1
	global	_FCV_DISPLAYUPDATECOUNT
_FCV_DISPLAYUPDATECOUNT:
       ds      1
	global	_FCV_04891_DCMotor1__SW_PWM_STATE
_FCV_04891_DCMotor1__SW_PWM_STATE:
       ds      1
	global	_FCV_REVOLUTIONTIME
_FCV_REVOLUTIONTIME:
       ds      4
	file	"feedback control - PIC.as"
	line	#
psect	cinit
; Clear objects allocated to BANK0 (40 bytes)
	global __pbssBANK0
lfsr	0,__pbssBANK0
movlw	40
clear_0:
clrf	postinc0,c
decf	wreg
bnz	clear_0
; Clear objects allocated to COMRAM (39 bytes)
	global __pbssCOMRAM
lfsr	0,__pbssCOMRAM
movlw	39
clear_1:
clrf	postinc0,c
decf	wreg
bnz	clear_1
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:
	bcf int$flags,0,c ;clear compiler interrupt flag (level 1)
	bcf int$flags,1,c ;clear compiler interrupt flag (level 2)
	GLOBAL	__Lmediumconst
	movlw	low highword(__Lmediumconst)
	movwf	tblptru
movlb 0
goto _main	;jump to C main() function
psect	cstackBANK0,class=BANK0,space=1,noexec
global __pcstackBANK0
__pcstackBANK0:
?___fleq:	; 1 bit 
?___flge:	; 1 bit 
??_FCD_026e1_Timer1__ResetCounter:	; 1 bytes @ 0x0
??_FCD_026e1_Timer1__RestoreCounter:	; 1 bytes @ 0x0
??_delay_us:	; 1 bytes @ 0x0
??_delay_ms:	; 1 bytes @ 0x0
??_FC_CAL_ADC_Disable_1:	; 1 bytes @ 0x0
??_FCD_00a91_TimedInterval1__StartTimerInterval:	; 1 bytes @ 0x0
?_FCD_04891_DCMotor1__Forwards:	; 1 bytes @ 0x0
??_FCD_04891_DCMotor1__Enable:	; 1 bytes @ 0x0
	global	?_FCI_GETLENGTH
?_FCI_GETLENGTH:	; 2 bytes @ 0x0
	global	?_FC_CAL_ADC_Sample_1
?_FC_CAL_ADC_Sample_1:	; 2 bytes @ 0x0
	global	?___fladd
?___fladd:	; 4 bytes @ 0x0
	global	?___fldiv
?___fldiv:	; 4 bytes @ 0x0
	global	?___lmul
?___lmul:	; 4 bytes @ 0x0
	global	?___lldiv
?___lldiv:	; 4 bytes @ 0x0
	global	?___aldiv
?___aldiv:	; 4 bytes @ 0x0
	global	?___almod
?___almod:	; 4 bytes @ 0x0
	global	?___flneg
?___flneg:	; 4 bytes @ 0x0
	global	?___fltol
?___fltol:	; 4 bytes @ 0x0
	global	delay_us@del
delay_us@del:	; 1 bytes @ 0x0
	global	FCI_GETLENGTH@sStr1
FCI_GETLENGTH@sStr1:	; 2 bytes @ 0x0
	global	FCD_026e1_Timer1__RestoreCounter@FCL_COUNTSAVE
FCD_026e1_Timer1__RestoreCounter@FCL_COUNTSAVE:	; 2 bytes @ 0x0
	global	FCD_04891_DCMotor1__Forwards@FCL_DUTY
FCD_04891_DCMotor1__Forwards@FCL_DUTY:	; 2 bytes @ 0x0
	global	___lmul@multiplier
___lmul@multiplier:	; 4 bytes @ 0x0
	global	___lldiv@dividend
___lldiv@dividend:	; 4 bytes @ 0x0
	global	___aldiv@dividend
___aldiv@dividend:	; 4 bytes @ 0x0
	global	___almod@dividend
___almod@dividend:	; 4 bytes @ 0x0
	global	___fleq@ff1
___fleq@ff1:	; 4 bytes @ 0x0
	global	___flge@ff1
___flge@ff1:	; 4 bytes @ 0x0
	global	___flneg@f1
___flneg@f1:	; 4 bytes @ 0x0
	global	___fltol@f1
___fltol@f1:	; 4 bytes @ 0x0
	global	___fladd@b
___fladd@b:	; 4 bytes @ 0x0
	global	___fldiv@b
___fldiv@b:	; 4 bytes @ 0x0
	ds   1
?_FCD_04071_LCD1__RawSend:	; 1 bytes @ 0x1
?_FC_CAL_ADC_Enable_1:	; 1 bytes @ 0x1
	global	delay_ms@del
delay_ms@del:	; 1 bytes @ 0x1
	global	FC_CAL_ADC_Enable_1@Conv_Speed
FC_CAL_ADC_Enable_1@Conv_Speed:	; 1 bytes @ 0x1
	global	FCD_04071_LCD1__RawSend@FCL_TYPE
FCD_04071_LCD1__RawSend@FCL_TYPE:	; 1 bytes @ 0x1
	ds   1
??_FCD_04071_LCD1__RawSend:	; 1 bytes @ 0x2
??_delay_s:	; 1 bytes @ 0x2
??_FC_CAL_ADC_Sample_1:	; 1 bytes @ 0x2
??_FCD_026e1_Timer1__StartCounter:	; 1 bytes @ 0x2
??_FCD_04891_DCMotor1__Forwards:	; 1 bytes @ 0x2
	global	delay_s@del
delay_s@del:	; 1 bytes @ 0x2
	global	FC_CAL_ADC_Enable_1@Vref
FC_CAL_ADC_Enable_1@Vref:	; 1 bytes @ 0x2
	global	FCD_026e1_Timer1__StartCounter@FCL_RESETCOUNTERS
FCD_026e1_Timer1__StartCounter@FCL_RESETCOUNTERS:	; 1 bytes @ 0x2
	global	FCD_04071_LCD1__RawSend@FCL_DATA
FCD_04071_LCD1__RawSend@FCL_DATA:	; 1 bytes @ 0x2
	global	FCI_GETLENGTH@iStr1_len
FCI_GETLENGTH@iStr1_len:	; 2 bytes @ 0x2
	ds   1
	global	delay_s@i
delay_s@i:	; 1 bytes @ 0x3
	global	FC_CAL_ADC_Enable_1@T_Charge
FC_CAL_ADC_Enable_1@T_Charge:	; 1 bytes @ 0x3
	global	FCD_04071_LCD1__RawSend@FCL_NIBBLE
FCD_04071_LCD1__RawSend@FCL_NIBBLE:	; 1 bytes @ 0x3
	ds   1
?_FCD_04071_LCD1__Cursor:	; 1 bytes @ 0x4
??_FCI_GETLENGTH:	; 1 bytes @ 0x4
??_FC_CAL_ADC_Enable_1:	; 1 bytes @ 0x4
??_FCD_04071_LCD1__Clear:	; 1 bytes @ 0x4
??_FCD_04071_LCD1__Start:	; 1 bytes @ 0x4
??_FCD_049e1_LCD_BL0169__Clear:	; 1 bytes @ 0x4
??_FCD_049e1_LCD_BL0169__Start:	; 1 bytes @ 0x4
??___flneg:	; 1 bytes @ 0x4
??___fltol:	; 1 bytes @ 0x4
	global	FC_CAL_ADC_Sample_1@Sample_Mode
FC_CAL_ADC_Sample_1@Sample_Mode:	; 1 bytes @ 0x4
	global	FCD_04071_LCD1__Cursor@FCL_Y
FCD_04071_LCD1__Cursor@FCL_Y:	; 1 bytes @ 0x4
	global	___lmul@multiplicand
___lmul@multiplicand:	; 4 bytes @ 0x4
	global	___lldiv@divisor
___lldiv@divisor:	; 4 bytes @ 0x4
	global	___aldiv@divisor
___aldiv@divisor:	; 4 bytes @ 0x4
	global	___almod@divisor
___almod@divisor:	; 4 bytes @ 0x4
	global	___fleq@ff2
___fleq@ff2:	; 4 bytes @ 0x4
	global	___flge@ff2
___flge@ff2:	; 4 bytes @ 0x4
	global	___fladd@a
___fladd@a:	; 4 bytes @ 0x4
	global	___fldiv@a
___fldiv@a:	; 4 bytes @ 0x4
	ds   1
??_FCD_04071_LCD1__Cursor:	; 1 bytes @ 0x5
	global	FCD_04071_LCD1__Cursor@FCL_X
FCD_04071_LCD1__Cursor@FCL_X:	; 1 bytes @ 0x5
	global	FC_CAL_ADC_Sample_1@iRetVal
FC_CAL_ADC_Sample_1@iRetVal:	; 2 bytes @ 0x5
	ds   1
?_FCD_049e1_LCD_BL0169__Cursor:	; 1 bytes @ 0x6
	global	FC_CAL_ADC_Enable_1@Channel
FC_CAL_ADC_Enable_1@Channel:	; 1 bytes @ 0x6
	global	FCD_049e1_LCD_BL0169__Cursor@FCL_Y
FCD_049e1_LCD_BL0169__Cursor@FCL_Y:	; 1 bytes @ 0x6
	global	FCI_GETLENGTH@tmp
FCI_GETLENGTH@tmp:	; 2 bytes @ 0x6
	ds   1
??_FCD_0cc51_adc_base1__GetByte:	; 1 bytes @ 0x7
??_FCD_049e1_LCD_BL0169__Cursor:	; 1 bytes @ 0x7
	global	FCD_0cc51_adc_base1__GetByte@FCR_RETVAL
FCD_0cc51_adc_base1__GetByte@FCR_RETVAL:	; 1 bytes @ 0x7
	global	FCD_049e1_LCD_BL0169__Cursor@FCL_X
FCD_049e1_LCD_BL0169__Cursor@FCL_X:	; 1 bytes @ 0x7
	ds   1
??___fladd:	; 1 bytes @ 0x8
??___fldiv:	; 1 bytes @ 0x8
??_FCD_00a21_Potentiometer1__GetByte:	; 1 bytes @ 0x8
?_FCD_04071_LCD1__PrintString:	; 1 bytes @ 0x8
??___lmul:	; 1 bytes @ 0x8
??___lldiv:	; 1 bytes @ 0x8
??___aldiv:	; 1 bytes @ 0x8
??___almod:	; 1 bytes @ 0x8
??___fleq:	; 1 bytes @ 0x8
??___flge:	; 1 bytes @ 0x8
	global	FCD_00a21_Potentiometer1__GetByte@FCR_RETVAL
FCD_00a21_Potentiometer1__GetByte@FCR_RETVAL:	; 1 bytes @ 0x8
	global	___aldiv@counter
___aldiv@counter:	; 1 bytes @ 0x8
	global	___almod@counter
___almod@counter:	; 1 bytes @ 0x8
	global	___fltol@sign1
___fltol@sign1:	; 1 bytes @ 0x8
	global	FCD_04071_LCD1__PrintString@FCL_TEXT
FCD_04071_LCD1__PrintString@FCL_TEXT:	; 2 bytes @ 0x8
	global	___lmul@product
___lmul@product:	; 4 bytes @ 0x8
	global	___lldiv@quotient
___lldiv@quotient:	; 4 bytes @ 0x8
	ds   1
	global	___aldiv@sign
___aldiv@sign:	; 1 bytes @ 0x9
	global	___almod@sign
___almod@sign:	; 1 bytes @ 0x9
	global	___fltol@exp1
___fltol@exp1:	; 1 bytes @ 0x9
	ds   1
	global	?___xxtofl
?___xxtofl:	; 4 bytes @ 0xA
	global	FCD_04071_LCD1__PrintString@FCLsz_TEXT
FCD_04071_LCD1__PrintString@FCLsz_TEXT:	; 2 bytes @ 0xA
	global	___aldiv@quotient
___aldiv@quotient:	; 4 bytes @ 0xA
	global	___xxtofl@val
___xxtofl@val:	; 4 bytes @ 0xA
	ds   2
??_FCD_04071_LCD1__PrintString:	; 1 bytes @ 0xC
?_frexp:	; 4 bytes @ 0xC
	global	___lldiv@counter
___lldiv@counter:	; 1 bytes @ 0xC
	global	___fladd@signs
___fladd@signs:	; 1 bytes @ 0xC
	global	___fldiv@rem
___fldiv@rem:	; 4 bytes @ 0xC
	global	frexp@value
frexp@value:	; 4 bytes @ 0xC
	ds   1
?_FCI_TOSTRING:	; 1 bytes @ 0xD
	global	___fladd@aexp
___fladd@aexp:	; 1 bytes @ 0xD
	global	FCI_TOSTRING@iSrc1
FCI_TOSTRING@iSrc1:	; 4 bytes @ 0xD
	ds   1
??___xxtofl:	; 1 bytes @ 0xE
	global	FCD_04071_LCD1__PrintString@FCL_COUNT
FCD_04071_LCD1__PrintString@FCL_COUNT:	; 1 bytes @ 0xE
	global	___fladd@bexp
___fladd@bexp:	; 1 bytes @ 0xE
	ds   1
	global	FCD_04071_LCD1__PrintString@FCL_IDX
FCD_04071_LCD1__PrintString@FCL_IDX:	; 1 bytes @ 0xF
	global	___fladd@grs
___fladd@grs:	; 1 bytes @ 0xF
	ds   1
?_FCD_049e1_LCD_BL0169__PrintString:	; 1 bytes @ 0x10
	global	?___flsub
?___flsub:	; 4 bytes @ 0x10
	global	___fldiv@sign
___fldiv@sign:	; 1 bytes @ 0x10
	global	frexp@eptr
frexp@eptr:	; 1 bytes @ 0x10
	global	FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT
FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT:	; 2 bytes @ 0x10
	global	___flsub@b
___flsub@b:	; 4 bytes @ 0x10
	ds   1
??_frexp:	; 1 bytes @ 0x11
	global	FCI_TOSTRING@sDst
FCI_TOSTRING@sDst:	; 1 bytes @ 0x11
	global	___fldiv@new_exp
___fldiv@new_exp:	; 2 bytes @ 0x11
	ds   1
	global	___xxtofl@sign
___xxtofl@sign:	; 1 bytes @ 0x12
	global	FCI_TOSTRING@iDst_len
FCI_TOSTRING@iDst_len:	; 2 bytes @ 0x12
	global	FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT
FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT:	; 2 bytes @ 0x12
	ds   1
	global	___xxtofl@exp
___xxtofl@exp:	; 1 bytes @ 0x13
	global	___fldiv@grs
___fldiv@grs:	; 4 bytes @ 0x13
	ds   1
??_FCI_TOSTRING:	; 1 bytes @ 0x14
??_FCD_049e1_LCD_BL0169__PrintString:	; 1 bytes @ 0x14
	global	___flsub@a
___flsub@a:	; 4 bytes @ 0x14
	global	___xxtofl@arg
___xxtofl@arg:	; 4 bytes @ 0x14
	ds   2
	global	FCI_TOSTRING@tmp1
FCI_TOSTRING@tmp1:	; 1 bytes @ 0x16
	ds   1
	global	FCI_TOSTRING@idx
FCI_TOSTRING@idx:	; 1 bytes @ 0x17
	global	___fldiv@bexp
___fldiv@bexp:	; 1 bytes @ 0x17
	ds   1
??___flsub:	; 1 bytes @ 0x18
	global	?_floor
?_floor:	; 4 bytes @ 0x18
	global	___fldiv@aexp
___fldiv@aexp:	; 1 bytes @ 0x18
	global	FCI_TOSTRING@iSrc
FCI_TOSTRING@iSrc:	; 4 bytes @ 0x18
	global	floor@x
floor@x:	; 4 bytes @ 0x18
	ds   1
	global	?___flmul
?___flmul:	; 4 bytes @ 0x19
	global	___flmul@b
___flmul@b:	; 4 bytes @ 0x19
	ds   3
??_floor:	; 1 bytes @ 0x1C
	global	FCI_TOSTRING@top
FCI_TOSTRING@top:	; 4 bytes @ 0x1C
	global	floor@i
floor@i:	; 4 bytes @ 0x1C
	ds   1
	global	___flmul@a
___flmul@a:	; 4 bytes @ 0x1D
	ds   3
?_FCD_04071_LCD1__PrintNumber:	; 1 bytes @ 0x20
	global	FCD_04071_LCD1__PrintNumber@FCL_NUMBER
FCD_04071_LCD1__PrintNumber@FCL_NUMBER:	; 2 bytes @ 0x20
	global	floor@expon
floor@expon:	; 2 bytes @ 0x20
	ds   1
??___flmul:	; 1 bytes @ 0x21
	ds   1
??_FCD_04071_LCD1__PrintNumber:	; 1 bytes @ 0x22
	global	FCD_04071_LCD1__PrintNumber@FCL_S
FCD_04071_LCD1__PrintNumber@FCL_S:	; 10 bytes @ 0x22
	ds   3
	global	___flmul@sign
___flmul@sign:	; 1 bytes @ 0x25
	ds   1
	global	___flmul@aexp
___flmul@aexp:	; 1 bytes @ 0x26
	ds   1
	global	___flmul@grs
___flmul@grs:	; 4 bytes @ 0x27
	ds   4
	global	___flmul@bexp
___flmul@bexp:	; 1 bytes @ 0x2B
	ds   1
?_FCD_049e1_LCD_BL0169__PrintNumber:	; 1 bytes @ 0x2C
	global	FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER
FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER:	; 2 bytes @ 0x2C
	global	___flmul@prod
___flmul@prod:	; 4 bytes @ 0x2C
	ds   2
??_FCD_049e1_LCD_BL0169__PrintNumber:	; 1 bytes @ 0x2E
	ds   2
	global	___flmul@temp
___flmul@temp:	; 2 bytes @ 0x30
	ds   2
?_FCI_FLOAT_TO_STRING:	; 1 bytes @ 0x32
	global	FCI_FLOAT_TO_STRING@Number
FCI_FLOAT_TO_STRING@Number:	; 4 bytes @ 0x32
	ds   4
	global	FCI_FLOAT_TO_STRING@Precision
FCI_FLOAT_TO_STRING@Precision:	; 1 bytes @ 0x36
	ds   1
	global	FCI_FLOAT_TO_STRING@String
FCI_FLOAT_TO_STRING@String:	; 1 bytes @ 0x37
	ds   1
	global	FCI_FLOAT_TO_STRING@MSZ_String
FCI_FLOAT_TO_STRING@MSZ_String:	; 2 bytes @ 0x38
	ds   2
??_FCI_FLOAT_TO_STRING:	; 1 bytes @ 0x3A
	global	FCI_FLOAT_TO_STRING@rev_digits
FCI_FLOAT_TO_STRING@rev_digits:	; 12 bytes @ 0x3A
	ds   12
	global	FCI_FLOAT_TO_STRING@temp_string
FCI_FLOAT_TO_STRING@temp_string:	; 12 bytes @ 0x46
	ds   12
	global	FCI_FLOAT_TO_STRING@temp_idx
FCI_FLOAT_TO_STRING@temp_idx:	; 2 bytes @ 0x52
	ds   2
	global	FCI_FLOAT_TO_STRING@temp_whole
FCI_FLOAT_TO_STRING@temp_whole:	; 4 bytes @ 0x54
	ds   4
	global	FCI_FLOAT_TO_STRING@rev_idx
FCI_FLOAT_TO_STRING@rev_idx:	; 2 bytes @ 0x58
	ds   2
	global	FCI_FLOAT_TO_STRING@real
FCI_FLOAT_TO_STRING@real:	; 4 bytes @ 0x5A
	ds   4
	global	FCI_FLOAT_TO_STRING@whole
FCI_FLOAT_TO_STRING@whole:	; 4 bytes @ 0x5E
	ds   4
	global	FCI_FLOAT_TO_STRING@temp
FCI_FLOAT_TO_STRING@temp:	; 4 bytes @ 0x62
	ds   4
	global	FCI_FLOAT_TO_STRING@idx
FCI_FLOAT_TO_STRING@idx:	; 1 bytes @ 0x66
	ds   1
	global	FCI_FLOAT_TO_STRING@stringidx
FCI_FLOAT_TO_STRING@stringidx:	; 2 bytes @ 0x67
	ds   2
?_FCD_049e1_LCD_BL0169__PrintFloat:	; 1 bytes @ 0x69
	global	FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER
FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER:	; 4 bytes @ 0x69
	ds   4
	global	FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES
FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES:	; 1 bytes @ 0x6D
	ds   1
??_FCD_049e1_LCD_BL0169__PrintFloat:	; 1 bytes @ 0x6E
	global	FCD_049e1_LCD_BL0169__PrintFloat@FCL_S
FCD_049e1_LCD_BL0169__PrintFloat@FCL_S:	; 10 bytes @ 0x6E
	ds   10
??_FCM_update_display:	; 1 bytes @ 0x78
??_main:	; 1 bytes @ 0x78
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_FCD_026e1_Timer1__ResetCounter:	; 1 bytes @ 0x0
?_FCD_026e1_Timer1__RestoreCounter:	; 1 bytes @ 0x0
?_delay_us:	; 1 bytes @ 0x0
?_delay_ms:	; 1 bytes @ 0x0
?_delay_s:	; 1 bytes @ 0x0
?_FC_CAL_ADC_Disable_1:	; 1 bytes @ 0x0
?_FCD_026e1_Timer1__StartCounter:	; 1 bytes @ 0x0
?_FCD_0cc51_adc_base1__GetByte:	; 1 bytes @ 0x0
?_FCD_00a21_Potentiometer1__GetByte:	; 1 bytes @ 0x0
?_FCD_00a91_TimedInterval1__StartTimerInterval:	; 1 bytes @ 0x0
?_FCD_04891_DCMotor1__Enable:	; 1 bytes @ 0x0
?_FCD_04891_DCMotor1__TimerRoutine:	; 1 bytes @ 0x0
??_FCD_04891_DCMotor1__TimerRoutine:	; 1 bytes @ 0x0
?_FCD_04071_LCD1__Clear:	; 1 bytes @ 0x0
?_FCD_04071_LCD1__Start:	; 1 bytes @ 0x0
?_FCD_049e1_LCD_BL0169__Clear:	; 1 bytes @ 0x0
?_FCD_049e1_LCD_BL0169__Start:	; 1 bytes @ 0x0
?_FCM_update_display:	; 1 bytes @ 0x0
?_FCM_feedback_interrupt:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
?_myisr:	; 1 bytes @ 0x0
?i2_FCD_026e1_Timer1__ResetCounter:	; 1 bytes @ 0x0
??i2_FCD_026e1_Timer1__ResetCounter:	; 1 bytes @ 0x0
	global	?_FCD_026e1_Timer1__GetRawCount
?_FCD_026e1_Timer1__GetRawCount:	; 4 bytes @ 0x0
	global	?i2___fldiv
?i2___fldiv:	; 4 bytes @ 0x0
	global	?i2___xxtofl
?i2___xxtofl:	; 4 bytes @ 0x0
	global	i2___fldiv@b
i2___fldiv@b:	; 4 bytes @ 0x0
	global	i2___xxtofl@val
i2___xxtofl@val:	; 4 bytes @ 0x0
	ds   4
??_FCD_026e1_Timer1__GetRawCount:	; 1 bytes @ 0x4
??i2___xxtofl:	; 1 bytes @ 0x4
	global	i2___fldiv@a
i2___fldiv@a:	; 4 bytes @ 0x4
	ds   4
??i2___fldiv:	; 1 bytes @ 0x8
	global	i2___xxtofl@sign
i2___xxtofl@sign:	; 1 bytes @ 0x8
	global	FCD_026e1_Timer1__GetRawCount@FCR_RETVAL
FCD_026e1_Timer1__GetRawCount@FCR_RETVAL:	; 4 bytes @ 0x8
	ds   1
	global	i2___xxtofl@exp
i2___xxtofl@exp:	; 1 bytes @ 0x9
	ds   1
	global	i2___xxtofl@arg
i2___xxtofl@arg:	; 4 bytes @ 0xA
	ds   2
	global	i2___fldiv@rem
i2___fldiv@rem:	; 4 bytes @ 0xC
	ds   2
	global	?i2___flmul
?i2___flmul:	; 4 bytes @ 0xE
	global	i2___flmul@b
i2___flmul@b:	; 4 bytes @ 0xE
	ds   2
	global	i2___fldiv@sign
i2___fldiv@sign:	; 1 bytes @ 0x10
	ds   1
	global	i2___fldiv@new_exp
i2___fldiv@new_exp:	; 2 bytes @ 0x11
	ds   1
	global	i2___flmul@a
i2___flmul@a:	; 4 bytes @ 0x12
	ds   1
	global	i2___fldiv@grs
i2___fldiv@grs:	; 4 bytes @ 0x13
	ds   3
??i2___flmul:	; 1 bytes @ 0x16
	ds   1
	global	i2___fldiv@bexp
i2___fldiv@bexp:	; 1 bytes @ 0x17
	ds   1
	global	i2___fldiv@aexp
i2___fldiv@aexp:	; 1 bytes @ 0x18
	ds   2
	global	i2___flmul@sign
i2___flmul@sign:	; 1 bytes @ 0x1A
	ds   1
	global	i2___flmul@aexp
i2___flmul@aexp:	; 1 bytes @ 0x1B
	ds   1
	global	i2___flmul@grs
i2___flmul@grs:	; 4 bytes @ 0x1C
	ds   4
	global	i2___flmul@bexp
i2___flmul@bexp:	; 1 bytes @ 0x20
	ds   1
	global	i2___flmul@prod
i2___flmul@prod:	; 4 bytes @ 0x21
	ds   4
	global	i2___flmul@temp
i2___flmul@temp:	; 2 bytes @ 0x25
	ds   2
	global	?_FCD_026e1_Timer1__GetCountReal
?_FCD_026e1_Timer1__GetCountReal:	; 4 bytes @ 0x27
	ds   4
??_FCD_026e1_Timer1__GetCountReal:	; 1 bytes @ 0x2B
	global	FCD_026e1_Timer1__GetCountReal@FCL_COUNT
FCD_026e1_Timer1__GetCountReal@FCL_COUNT:	; 4 bytes @ 0x2B
	ds   4
	global	FCD_026e1_Timer1__GetCountReal@FCR_RETVAL
FCD_026e1_Timer1__GetCountReal@FCR_RETVAL:	; 4 bytes @ 0x2F
	ds   4
??_FCM_feedback_interrupt:	; 1 bytes @ 0x33
??_myisr:	; 1 bytes @ 0x33
	ds   2
;!
;!Data Sizes:
;!    Strings     26
;!    Constant    475
;!    Data        0
;!    BSS         79
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           94     53      92
;!    BANK0           160    120     160
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
;!    frexp@eptr	PTR int  size(1) Largest target is 2
;!		 -> floor@expon(BANK0[2]), 
;!
;!    FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT	PTR unsigned char  size(2) Largest target is 10
;!		 -> STR_7(CODE[3]), STR_6(CODE[5]), STR_5(CODE[3]), STR_4(CODE[8]), 
;!		 -> STR_3(CODE[3]), STR_2(CODE[10]), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(BANK0[10]), 
;!
;!    FCD_04071_LCD1__PrintString@FCL_TEXT	PTR unsigned char  size(2) Largest target is 15
;!		 -> STR_7(CODE[3]), STR_6(CODE[5]), STR_5(CODE[3]), STR_4(CODE[8]), 
;!		 -> STR_3(CODE[3]), STR_2(CODE[10]), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(BANK0[10]), FCD_04071_LCD1__PrintFloat@FCL_S(COMRAM[10]), 
;!		 -> FCD_04071_LCD1__PrintFormattedNumber@FCL_S(COMRAM[15]), FCD_04071_LCD1__PrintNumber@FCL_S(BANK0[10]), 
;!
;!    sp__FCI_NUMBER_TO_HEX	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_FLOAT_TO_STRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(BANK0[10]), FCD_04071_LCD1__PrintFloat@FCL_S(COMRAM[10]), FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMFLOATARRAY@sTemp(COMRAM[20]), 
;!
;!    FCI_FLOAT_TO_STRING@String	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(BANK0[10]), FCD_04071_LCD1__PrintFloat@FCL_S(COMRAM[10]), FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMFLOATARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_TOSTRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_04071_LCD1__PrintNumber@FCL_S(BANK0[10]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMINTARRAY@sTemp(COMRAM[20]), 
;!
;!    FCI_TOSTRING@sDst	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_04071_LCD1__PrintNumber@FCL_S(BANK0[10]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMINTARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_RIGHTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_LEFTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_MIDSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    FCI_GETLENGTH@sStr1	PTR unsigned char  size(2) Largest target is 20
;!		 -> STR_7(CODE[3]), STR_6(CODE[5]), STR_5(CODE[3]), STR_4(CODE[8]), 
;!		 -> STR_3(CODE[3]), STR_2(CODE[10]), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(BANK0[10]), FCD_04071_LCD1__PrintFloat@FCL_S(COMRAM[10]), 
;!		 -> FCD_04071_LCD1__PrintFormattedNumber@FCL_S(COMRAM[15]), FCD_04071_LCD1__PrintNumber@FCL_S(BANK0[10]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), 
;!


;!
;!Critical Paths under _main in COMRAM
;!
;!    None.
;!
;!Critical Paths under _myisr in COMRAM
;!
;!    _FCM_feedback_interrupt->_FCD_026e1_Timer1__GetCountReal
;!    _FCD_026e1_Timer1__GetCountReal->i2___flmul
;!    i2___flmul->i2___xxtofl
;!
;!Critical Paths under _main in BANK0
;!
;!    _delay_s->_delay_ms
;!    _FCM_update_display->_FCD_049e1_LCD_BL0169__PrintFloat
;!    _FCD_049e1_LCD_BL0169__PrintNumber->_FCD_04071_LCD1__PrintNumber
;!    _FCD_04071_LCD1__PrintNumber->_FCI_TOSTRING
;!    _FCI_TOSTRING->___lldiv
;!    _FCD_049e1_LCD_BL0169__PrintFloat->_FCI_FLOAT_TO_STRING
;!    _FCI_FLOAT_TO_STRING->___flmul
;!    _floor->___xxtofl
;!    _frexp->___fleq
;!    ___xxtofl->___fltol
;!    ___flsub->___fladd
;!    ___flmul->___fldiv
;!    _FCD_049e1_LCD_BL0169__PrintString->_FCD_04071_LCD1__PrintString
;!    _FCD_04071_LCD1__PrintString->_FCI_GETLENGTH
;!    _FCD_049e1_LCD_BL0169__Cursor->_FCD_04071_LCD1__Cursor
;!    _FCD_04071_LCD1__Cursor->_FCD_04071_LCD1__RawSend
;!    _FCD_04071_LCD1__Start->_FCD_04071_LCD1__RawSend
;!    _FCD_04071_LCD1__Clear->_FCD_04071_LCD1__RawSend
;!    _FCD_04071_LCD1__RawSend->_delay_us
;!    _FCD_026e1_Timer1__StartCounter->_FCD_026e1_Timer1__RestoreCounter
;!    _FCD_00a21_Potentiometer1__GetByte->_FCD_0cc51_adc_base1__GetByte
;!    _FCD_0cc51_adc_base1__GetByte->_FC_CAL_ADC_Enable_1
;!    _FCD_0cc51_adc_base1__GetByte->_FC_CAL_ADC_Sample_1
;!    _FC_CAL_ADC_Enable_1->_delay_us
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
;! (0) _main                                                 0     0      0   64374
;!  _FCD_00a21_Potentiometer1__GetByte
;!     _FCD_026e1_Timer1__StartCounter
;!         _FCD_04891_DCMotor1__Enable
;!       _FCD_04891_DCMotor1__Forwards
;!        _FCD_049e1_LCD_BL0169__Clear
;!        _FCD_049e1_LCD_BL0169__Start
;!                 _FCM_update_display
;!                            ___fldiv
;!                            ___flmul
;!                           _delay_ms
;!                            _delay_s
;! ---------------------------------------------------------------------------------
;! (1) _delay_s                                              2     2      0      68
;!                                              2 BANK0      2     2      0
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) ___fldiv                                             25    17      8    2003
;!                                              0 BANK0     25    17      8
;! ---------------------------------------------------------------------------------
;! (1) _FCM_update_display                                   0     0      0   49896
;!       _FCD_049e1_LCD_BL0169__Cursor
;!   _FCD_049e1_LCD_BL0169__PrintFloat
;!  _FCD_049e1_LCD_BL0169__PrintNumber
;!  _FCD_049e1_LCD_BL0169__PrintString
;! ---------------------------------------------------------------------------------
;! (2) _FCD_049e1_LCD_BL0169__PrintNumber                    2     0      2   11736
;!                                             44 BANK0      2     0      2
;!        _FCD_04071_LCD1__PrintNumber
;! ---------------------------------------------------------------------------------
;! (3) _FCD_04071_LCD1__PrintNumber                         12    10      2   11638
;!                                             32 BANK0     12    10      2
;!        _FCD_04071_LCD1__PrintString
;!                       _FCI_TOSTRING
;! ---------------------------------------------------------------------------------
;! (4) _FCI_TOSTRING                                        19    12      7    6783
;!                                             13 BANK0     19    12      7
;!                            ___lldiv
;!                             ___lmul
;! ---------------------------------------------------------------------------------
;! (5) ___lmul                                              12     4      8    3898
;!                                              0 BANK0     12     4      8
;! ---------------------------------------------------------------------------------
;! (5) ___lldiv                                             13     5      8    1726
;!                                              0 BANK0     13     5      8
;! ---------------------------------------------------------------------------------
;! (2) _FCD_049e1_LCD_BL0169__PrintFloat                    15    10      5   29351
;!                                            105 BANK0     15    10      5
;!  _FCD_049e1_LCD_BL0169__PrintString
;!                _FCI_FLOAT_TO_STRING
;! ---------------------------------------------------------------------------------
;! (3) _FCI_FLOAT_TO_STRING                                 55    47      8   23088
;!                                             50 BANK0     55    47      8
;!                            ___aldiv
;!                            ___almod
;!                            ___fladd
;!                            ___flmul
;!                            ___flneg
;!                            ___flsub
;!                            ___fltol
;!                           ___xxtofl
;!                              _floor
;! ---------------------------------------------------------------------------------
;! (4) _floor                                               10     6      4    6511
;!                                             24 BANK0     10     6      4
;!                            ___fladd
;!                             ___flge
;!                            ___fltol
;!                           ___xxtofl
;!                              _frexp
;! ---------------------------------------------------------------------------------
;! (5) _frexp                                                7     2      5     980
;!                                             12 BANK0      7     2      5
;!                             ___fleq
;! ---------------------------------------------------------------------------------
;! (6) ___fleq                                              12     4      8     620
;!                                              0 BANK0     12     4      8
;! ---------------------------------------------------------------------------------
;! (5) ___xxtofl                                            14    10      4    1028
;!                                             10 BANK0     14    10      4
;!                            ___fltol (ARG)
;! ---------------------------------------------------------------------------------
;! (5) ___fltol                                             10     6      4     646
;!                                              0 BANK0     10     6      4
;! ---------------------------------------------------------------------------------
;! (5) ___flge                                              12     4      8     586
;!                                              0 BANK0     12     4      8
;! ---------------------------------------------------------------------------------
;! (4) ___flsub                                              8     0      8    4301
;!                                             16 BANK0      8     0      8
;!                            ___fladd
;! ---------------------------------------------------------------------------------
;! (5) ___fladd                                             16     8      8    2944
;!                                              0 BANK0     16     8      8
;! ---------------------------------------------------------------------------------
;! (4) ___flneg                                              4     0      4     121
;!                                              0 BANK0      4     0      4
;! ---------------------------------------------------------------------------------
;! (1) ___flmul                                             25    17      8    3031
;!                                             25 BANK0     25    17      8
;!                            ___fldiv (ARG)
;! ---------------------------------------------------------------------------------
;! (4) ___almod                                             10     2      8     448
;!                                              0 BANK0     10     2      8
;! ---------------------------------------------------------------------------------
;! (4) ___aldiv                                             14     6      8     830
;!                                              0 BANK0     14     6      8
;! ---------------------------------------------------------------------------------
;! (2) _FCD_049e1_LCD_BL0169__PrintString                    4     0      4    5813
;!                                             16 BANK0      4     0      4
;!        _FCD_04071_LCD1__PrintString
;! ---------------------------------------------------------------------------------
;! (3) _FCD_04071_LCD1__PrintString                          8     4      4    4705
;!                                              8 BANK0      8     4      4
;!            _FCD_04071_LCD1__RawSend
;!                      _FCI_GETLENGTH
;! ---------------------------------------------------------------------------------
;! (4) _FCI_GETLENGTH                                        8     4      4    1650
;!                                              0 BANK0      8     4      4
;! ---------------------------------------------------------------------------------
;! (2) _FCD_049e1_LCD_BL0169__Cursor                         2     1      1    2996
;!                                              6 BANK0      2     1      1
;!             _FCD_04071_LCD1__Cursor
;! ---------------------------------------------------------------------------------
;! (3) _FCD_04071_LCD1__Cursor                               2     1      1    2724
;!                                              4 BANK0      2     1      1
;!            _FCD_04071_LCD1__RawSend
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) _FCD_049e1_LCD_BL0169__Start                          0     0      0    4728
;!              _FCD_04071_LCD1__Start
;! ---------------------------------------------------------------------------------
;! (2) _FCD_04071_LCD1__Start                                0     0      0    4728
;!              _FCD_04071_LCD1__Clear
;!            _FCD_04071_LCD1__RawSend
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) _FCD_049e1_LCD_BL0169__Clear                          0     0      0    2364
;!              _FCD_04071_LCD1__Clear
;! ---------------------------------------------------------------------------------
;! (3) _FCD_04071_LCD1__Clear                                0     0      0    2364
;!            _FCD_04071_LCD1__RawSend
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (2) _delay_ms                                             2     2      0      22
;!                                              0 BANK0      2     2      0
;! ---------------------------------------------------------------------------------
;! (4) _FCD_04071_LCD1__RawSend                              3     2      1    2342
;!                                              1 BANK0      3     2      1
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (1) _FCD_04891_DCMotor1__Forwards                         2     0      2     174
;!                                              0 BANK0      2     0      2
;! ---------------------------------------------------------------------------------
;! (1) _FCD_04891_DCMotor1__Enable                           0     0      0       0
;!_FCD_00a91_TimedInterval1__StartTime
;! ---------------------------------------------------------------------------------
;! (2) _FCD_00a91_TimedInterval1__StartTimerInterval         0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _FCD_026e1_Timer1__StartCounter                       1     1      0      45
;!                                              2 BANK0      1     1      0
;!     _FCD_026e1_Timer1__ResetCounter
;!   _FCD_026e1_Timer1__RestoreCounter
;! ---------------------------------------------------------------------------------
;! (2) _FCD_026e1_Timer1__RestoreCounter                     2     2      0      23
;!                                              0 BANK0      2     2      0
;! ---------------------------------------------------------------------------------
;! (2) _FCD_026e1_Timer1__ResetCounter                       0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _FCD_00a21_Potentiometer1__GetByte                    1     1      0    2043
;!                                              8 BANK0      1     1      0
;!       _FCD_0cc51_adc_base1__GetByte
;! ---------------------------------------------------------------------------------
;! (2) _FCD_0cc51_adc_base1__GetByte                         1     1      0    2019
;!                                              7 BANK0      1     1      0
;!               _FC_CAL_ADC_Disable_1
;!                _FC_CAL_ADC_Enable_1
;!                _FC_CAL_ADC_Sample_1
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_ADC_Sample_1                                  7     5      2      69
;!                                              0 BANK0      7     5      2
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_ADC_Enable_1                                  6     3      3    1927
;!                                              1 BANK0      6     3      3
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (5) _delay_us                                             1     1      0      68
;!                                              0 BANK0      1     1      0
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_ADC_Disable_1                                 0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 6
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (7) _myisr                                                2     2      0    3201
;!                                             51 COMRAM     2     2      0
;!   _FCD_04891_DCMotor1__TimerRoutine
;!             _FCM_feedback_interrupt
;! ---------------------------------------------------------------------------------
;! (8) _FCM_feedback_interrupt                               0     0      0    3201
;!     _FCD_026e1_Timer1__GetCountReal
;!   i2_FCD_026e1_Timer1__ResetCounter
;! ---------------------------------------------------------------------------------
;! (9) i2_FCD_026e1_Timer1__ResetCounter                     0     0      0       0
;! ---------------------------------------------------------------------------------
;! (9) _FCD_026e1_Timer1__GetCountReal                      12     8      4    3201
;!                                             39 COMRAM    12     8      4
;!      _FCD_026e1_Timer1__GetRawCount
;!                          i2___fldiv
;!                          i2___flmul
;!                         i2___xxtofl
;! ---------------------------------------------------------------------------------
;! (10) i2___xxtofl                                         14    10      4     348
;!                                              0 COMRAM    14    10      4
;! ---------------------------------------------------------------------------------
;! (10) i2___flmul                                          25    17      8    1519
;!                                             14 COMRAM    25    17      8
;!                         i2___xxtofl (ARG)
;! ---------------------------------------------------------------------------------
;! (10) i2___fldiv                                          25    17      8    1173
;!                                              0 COMRAM    25    17      8
;! ---------------------------------------------------------------------------------
;! (10) _FCD_026e1_Timer1__GetRawCount                      12     8      4      92
;!                                              0 COMRAM    12     8      4
;! ---------------------------------------------------------------------------------
;! (8) _FCD_04891_DCMotor1__TimerRoutine                     0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 10
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _FCD_00a21_Potentiometer1__GetByte
;!     _FCD_0cc51_adc_base1__GetByte
;!       _FC_CAL_ADC_Disable_1
;!       _FC_CAL_ADC_Enable_1
;!         _delay_us
;!       _FC_CAL_ADC_Sample_1
;!   _FCD_026e1_Timer1__StartCounter
;!     _FCD_026e1_Timer1__ResetCounter
;!     _FCD_026e1_Timer1__RestoreCounter
;!   _FCD_04891_DCMotor1__Enable
;!     _FCD_00a91_TimedInterval1__StartTimerInterval
;!   _FCD_04891_DCMotor1__Forwards
;!   _FCD_049e1_LCD_BL0169__Clear
;!     _FCD_04071_LCD1__Clear
;!       _FCD_04071_LCD1__RawSend
;!         _delay_us
;!       _delay_ms
;!   _FCD_049e1_LCD_BL0169__Start
;!     _FCD_04071_LCD1__Start
;!       _FCD_04071_LCD1__Clear
;!         _FCD_04071_LCD1__RawSend
;!           _delay_us
;!         _delay_ms
;!       _FCD_04071_LCD1__RawSend
;!         _delay_us
;!       _delay_ms
;!   _FCM_update_display
;!     _FCD_049e1_LCD_BL0169__Cursor
;!       _FCD_04071_LCD1__Cursor
;!         _FCD_04071_LCD1__RawSend
;!           _delay_us
;!         _delay_ms
;!     _FCD_049e1_LCD_BL0169__PrintFloat
;!       _FCD_049e1_LCD_BL0169__PrintString
;!         _FCD_04071_LCD1__PrintString
;!           _FCD_04071_LCD1__RawSend
;!             _delay_us
;!           _FCI_GETLENGTH
;!       _FCI_FLOAT_TO_STRING
;!         ___aldiv
;!         ___almod
;!         ___fladd
;!         ___flmul
;!           ___fldiv (ARG)
;!         ___flneg
;!         ___flsub
;!           ___fladd
;!         ___fltol
;!         ___xxtofl
;!           ___fltol (ARG)
;!         _floor
;!           ___fladd
;!           ___flge
;!           ___fltol
;!           ___xxtofl
;!             ___fltol (ARG)
;!           _frexp
;!             ___fleq
;!     _FCD_049e1_LCD_BL0169__PrintNumber
;!       _FCD_04071_LCD1__PrintNumber
;!         _FCD_04071_LCD1__PrintString
;!           _FCD_04071_LCD1__RawSend
;!             _delay_us
;!           _FCI_GETLENGTH
;!         _FCI_TOSTRING
;!           ___lldiv
;!           ___lmul
;!     _FCD_049e1_LCD_BL0169__PrintString
;!       _FCD_04071_LCD1__PrintString
;!         _FCD_04071_LCD1__RawSend
;!           _delay_us
;!         _FCI_GETLENGTH
;!   ___fldiv
;!   ___flmul
;!     ___fldiv (ARG)
;!   _delay_ms
;!   _delay_s
;!     _delay_ms
;!
;! _myisr (ROOT)
;!   _FCD_04891_DCMotor1__TimerRoutine
;!   _FCM_feedback_interrupt
;!     _FCD_026e1_Timer1__GetCountReal
;!       _FCD_026e1_Timer1__GetRawCount
;!       i2___fldiv
;!       i2___flmul
;!         i2___xxtofl (ARG)
;!       i2___xxtofl
;!     i2_FCD_026e1_Timer1__ResetCounter
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
;!BANK0               A0     78      A0       5      100.0%
;!BITCOMRAM           5E      0       0       0        0.0%
;!COMRAM              5E     35      5C       1       97.9%
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
;!ABS                  0      0      FC       8        0.0%
;!DATA                 0      0      FC       3        0.0%
;!CODE                 0      0       0       0        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 3446 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:   10
;; This function calls:
;;		_FCD_00a21_Potentiometer1__GetByte
;;		_FCD_026e1_Timer1__StartCounter
;;		_FCD_04891_DCMotor1__Enable
;;		_FCD_04891_DCMotor1__Forwards
;;		_FCD_049e1_LCD_BL0169__Clear
;;		_FCD_049e1_LCD_BL0169__Start
;;		_FCM_update_display
;;		___fldiv
;;		___flmul
;;		_delay_ms
;;		_delay_s
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	3446
global __ptext0
__ptext0:
psect	text0
	file	"feedback control - PIC.c"
	line	3446
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	callstack 21
	line	3452
	
l5883:
	movlw	low(0)
	movlb	14	; () banked
	movwf	((3730))&0ffh	;volatile
	line	3453
	movlw	low(0)
	movwf	((3738))&0ffh	;volatile
	line	3454
	movlw	low(0)
	movwf	((3751))&0ffh	;volatile
	line	3455
	movlw	low(0)
	movwf	((3759))&0ffh	;volatile
	line	3456
	movlw	low(0)
	movwf	((3764))&0ffh	;volatile
	line	3457
	movlw	low(0)
	movwf	((3772))&0ffh	;volatile
	line	3460
	movlw	low(031h)
	movwf	((3601))&0ffh	;volatile
	line	3461
	movlw	low(0Eh)
	movwf	((3714))&0ffh	;volatile
	line	3462
	movlw	low(033h)
	movwf	((3607))&0ffh	;volatile
	line	3463
	movlw	low(014h)
	movwf	((3716))&0ffh	;volatile
	line	3473
	
l5885:; BSR set to: 14

	call	_FCD_049e1_LCD_BL0169__Start	;wreg free
	line	3476
	
l5887:; BSR set to: 0

	call	_FCD_04891_DCMotor1__Enable	;wreg free
	line	3479
	
l5889:; BSR set to: 14

	call	_FCD_049e1_LCD_BL0169__Clear	;wreg free
	line	3482
	
l5891:; BSR set to: 0

	movlw	high(07Dh)
	movwf	((FCD_04891_DCMotor1__Forwards@FCL_DUTY+1))&0ffh
	movlw	low(07Dh)
	movwf	((FCD_04891_DCMotor1__Forwards@FCL_DUTY))&0ffh
	call	_FCD_04891_DCMotor1__Forwards	;wreg free
	line	3485
	
l5893:; BSR set to: 0

	movlw	(01h)&0ffh
	
	call	_delay_s
	line	3488
	
l5895:; BSR set to: 0

	movlw	(01h)&0ffh
	
	call	_FCD_026e1_Timer1__StartCounter
	line	3491
	
l5897:; BSR set to: 14

	bsf	((c:4082))^0f00h,c,3	;volatile
	line	3492
	
l5899:; BSR set to: 14

	movlw	low(027h)
	movlb	13	; () banked
	movwf	((3571))&0ffh	;volatile
	line	3493
	
l5901:; BSR set to: 13

	bsf	((c:4082))^0f00h,c,7	;volatile
	line	3494
	
l5903:; BSR set to: 13

	bsf	((c:4082))^0f00h,c,6	;volatile
	line	3495
	
l5905:; BSR set to: 13

	movlb	14	; () banked
	bsf	((3625))&0ffh,3	;volatile
	line	3501
	
l5907:
	movlb	0	; () banked
	incf	((_FCV_DISPLAYUPDATECOUNT))&0ffh,w	;volatile
	movwf	((_FCV_DISPLAYUPDATECOUNT))&0ffh	;volatile
	line	3504
	
l5909:; BSR set to: 0

		movlw	100
	xorwf	((_FCV_DISPLAYUPDATECOUNT))&0ffh,w	;volatile
	btfss	status,2
	goto	u4991
	goto	u4990

u4991:
	goto	l5919
u4990:
	line	3511
	
l5911:; BSR set to: 0

	call	_FCD_00a21_Potentiometer1__GetByte	;wreg free
	movwf	((_FCV_PWMVALUE))&0ffh	;volatile
	line	3514
	
l5913:; BSR set to: 0

	movff	(_FCV_PWMVALUE),(FCD_04891_DCMotor1__Forwards@FCL_DUTY)	;volatile
	clrf	((FCD_04891_DCMotor1__Forwards@FCL_DUTY+1))&0ffh
	call	_FCD_04891_DCMotor1__Forwards	;wreg free
	line	3520
	
l5915:; BSR set to: 0

	call	_FCM_update_display	;wreg free
	line	3523
	
l5917:; BSR set to: 0

	movlw	low(0)
	movwf	((_FCV_DISPLAYUPDATECOUNT))&0ffh	;volatile
	line	3530
	
l5919:; BSR set to: 0

	movf	((_FCV_DATAREADY))&0ffh,w	;volatile
	btfsc	status,2
	goto	u5001
	goto	u5000
u5001:
	goto	l5925
u5000:
	line	3534
	
l5921:; BSR set to: 0

	movff	(_FCV_REVOLUTIONTIME),(___fldiv@a)	;volatile
	movff	(_FCV_REVOLUTIONTIME+1),(___fldiv@a+1)	;volatile
	movff	(_FCV_REVOLUTIONTIME+2),(___fldiv@a+2)	;volatile
	movff	(_FCV_REVOLUTIONTIME+3),(___fldiv@a+3)	;volatile
	movlw	low(normalize32(0x3f800000))
	movwf	((___fldiv@b))&0ffh
	movlw	high(normalize32(0x3f800000))
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(normalize32(0x3f800000))
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(normalize32(0x3f800000))
	movwf	((___fldiv@b+3))&0ffh
	call	___fldiv	;wreg free
	movff	0+?___fldiv,(___flmul@b)
	movff	1+?___fldiv,(___flmul@b+1)
	movff	2+?___fldiv,(___flmul@b+2)
	movff	3+?___fldiv,(___flmul@b+3)
	
	movlw	low(normalize32(0x42700000))
	movwf	((___flmul@a))&0ffh
	movlw	high(normalize32(0x42700000))
	movwf	((___flmul@a+1))&0ffh
	movlw	low highword(normalize32(0x42700000))
	movwf	((___flmul@a+2))&0ffh
	movlw	high highword(normalize32(0x42700000))
	movwf	((___flmul@a+3))&0ffh
	call	___flmul	;wreg free
	movff	0+?___flmul,(_FCV_RPM)	;volatile
	movff	1+?___flmul,(_FCV_RPM+1)	;volatile
	movff	2+?___flmul,(_FCV_RPM+2)	;volatile
	movff	3+?___flmul,(_FCV_RPM+3)	;volatile
	
	line	3537
	
l5923:; BSR set to: 0

	movlw	low(0)
	movwf	((_FCV_DATAREADY))&0ffh	;volatile
	line	3544
	
l5925:; BSR set to: 0

	movlw	(01h)&0ffh
	
	call	_delay_ms
	goto	l5907
	global	start
	goto	start
	opt callstack 0
	line	3549
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_delay_s

;; *************** function _delay_s *****************
;; Defined at:
;;		line 114 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    2[BANK0 ] unsigned char 
;;  i               1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_delay_ms
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	114
global __ptext1
__ptext1:
psect	text1
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	114
	global	__size_of_delay_s
	__size_of_delay_s	equ	__end_of_delay_s-_delay_s
	
_delay_s:; BSR set to: 0

;incstack = 0
	opt	callstack 25
	movwf	((delay_s@del))&0ffh
	line	117
	
l5597:
	movlw	low(0)
	movlb	0	; () banked
	movwf	((delay_s@i))&0ffh
	goto	l5603
	line	119
	
l5599:; BSR set to: 0

	movlw	(0FAh)&0ffh
	
	call	_delay_ms
	line	120
	movlw	(0FAh)&0ffh
	
	call	_delay_ms
	line	121
	movlw	(0FAh)&0ffh
	
	call	_delay_ms
	line	122
	movlw	(0FAh)&0ffh
	
	call	_delay_ms
	line	117
	
l5601:; BSR set to: 0

	incf	((delay_s@i))&0ffh
	
l5603:; BSR set to: 0

		movf	((delay_s@del))&0ffh,w
	subwf	((delay_s@i))&0ffh,w
	btfss	status,0
	goto	u4691
	goto	u4690

u4691:
	goto	l5599
u4690:
	line	124
	
l134:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_s
	__end_of_delay_s:
	signat	_delay_s,4217
	global	___fldiv

;; *************** function ___fldiv *****************
;; Defined at:
;;		line 11 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[BANK0 ] void 
;;  a               4    4[BANK0 ] void 
;; Auto vars:     Size  Location     Type
;;  grs             4   19[BANK0 ] unsigned long 
;;  rem             4   12[BANK0 ] unsigned long 
;;  new_exp         2   17[BANK0 ] int 
;;  aexp            1   24[BANK0 ] unsigned char 
;;  bexp            1   23[BANK0 ] unsigned char 
;;  sign            1   16[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      13       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      25       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       25 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text2,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
global __ptext2
__ptext2:
psect	text2
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
	global	__size_of___fldiv
	__size_of___fldiv	equ	__end_of___fldiv-___fldiv
	
___fldiv:; BSR set to: 0

;incstack = 0
	opt	callstack 26
	line	26
	
l5745:; BSR set to: 0

	movf	(0+(___fldiv@b+03h))&0ffh,w
	andlw	low(080h)
	movwf	((___fldiv@sign))&0ffh
	line	27
	movf	(0+(___fldiv@b+03h))&0ffh,w
	addwf	(0+(___fldiv@b+03h))&0ffh,w
	movwf	((___fldiv@bexp))&0ffh
	line	28
	
l5747:; BSR set to: 0

	
	btfss	(0+(___fldiv@b+02h))&0ffh,(7)&7
	goto	u4761
	goto	u4760
u4761:
	goto	l5751
u4760:
	line	29
	
l5749:; BSR set to: 0

	bsf	(0+(0/8)+(___fldiv@bexp))&0ffh,(0)&7
	line	33
	
l5751:; BSR set to: 0

	movf	((___fldiv@bexp))&0ffh,w
	btfsc	status,2
	goto	u4771
	goto	u4770
u4771:
	goto	l5761
u4770:
	line	35
	
l5753:; BSR set to: 0

		incf	((___fldiv@bexp))&0ffh,w
	btfss	status,2
	goto	u4781
	goto	u4780

u4781:
	goto	l5757
u4780:
	line	37
	
l5755:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fldiv@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fldiv@b+3))&0ffh
	line	40
	
l5757:; BSR set to: 0

	bsf	(0+(23/8)+(___fldiv@b))&0ffh,(23)&7
	line	42
	
l5759:; BSR set to: 0

	movlw	low(0)
	movwf	(0+(___fldiv@b+03h))&0ffh
	line	43
	goto	l5763
	line	46
	
l5761:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fldiv@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fldiv@b+3))&0ffh
	line	49
	
l5763:; BSR set to: 0

	movf	(0+(___fldiv@a+03h))&0ffh,w
	andlw	low(080h)
	xorwf	((___fldiv@sign))&0ffh
	line	50
	
l5765:; BSR set to: 0

	movf	(0+(___fldiv@a+03h))&0ffh,w
	addwf	(0+(___fldiv@a+03h))&0ffh,w
	movwf	((___fldiv@aexp))&0ffh
	line	51
	
l5767:; BSR set to: 0

	
	btfss	(0+(___fldiv@a+02h))&0ffh,(7)&7
	goto	u4791
	goto	u4790
u4791:
	goto	l5771
u4790:
	line	52
	
l5769:; BSR set to: 0

	bsf	(0+(0/8)+(___fldiv@aexp))&0ffh,(0)&7
	line	56
	
l5771:; BSR set to: 0

	movf	((___fldiv@aexp))&0ffh,w
	btfsc	status,2
	goto	u4801
	goto	u4800
u4801:
	goto	l5781
u4800:
	line	58
	
l5773:; BSR set to: 0

		incf	((___fldiv@aexp))&0ffh,w
	btfss	status,2
	goto	u4811
	goto	u4810

u4811:
	goto	l5777
u4810:
	line	60
	
l5775:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fldiv@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fldiv@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fldiv@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fldiv@a+3))&0ffh
	line	63
	
l5777:; BSR set to: 0

	bsf	(0+(23/8)+(___fldiv@a))&0ffh,(23)&7
	line	65
	
l5779:; BSR set to: 0

	movlw	low(0)
	movwf	(0+(___fldiv@a+03h))&0ffh
	line	66
	goto	l5783
	line	69
	
l5781:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fldiv@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fldiv@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fldiv@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fldiv@a+3))&0ffh
	line	75
	
l5783:; BSR set to: 0

	movf	((___fldiv@a))&0ffh,w
iorwf	((___fldiv@a+1))&0ffh,w
iorwf	((___fldiv@a+2))&0ffh,w
iorwf	((___fldiv@a+3))&0ffh,w
	btfss	status,2
	goto	u4821
	goto	u4820

u4821:
	goto	l5795
u4820:
	line	76
	
l5785:; BSR set to: 0

	movlw	low(0)
	movwf	((___fldiv@b))&0ffh
	movlw	high(0)
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fldiv@b+3))&0ffh
	line	77
	
l5787:; BSR set to: 0

	movlw	low(07F80h)
	iorwf	(0+(___fldiv@b+02h))&0ffh
	movlw	high(07F80h)
	iorwf	(1+(___fldiv@b+02h))&0ffh
	line	78
	
l5789:; BSR set to: 0

	movf	((___fldiv@sign))&0ffh,w
	iorwf	(0+(___fldiv@b+03h))&0ffh
	line	79
	
l5791:; BSR set to: 0

	movff	(___fldiv@b),(?___fldiv)
	movff	(___fldiv@b+1),(?___fldiv+1)
	movff	(___fldiv@b+2),(?___fldiv+2)
	movff	(___fldiv@b+3),(?___fldiv+3)
	goto	l1901
	line	83
	
l5795:; BSR set to: 0

	movf	((___fldiv@bexp))&0ffh,w
	btfss	status,2
	goto	u4831
	goto	u4830
u4831:
	goto	l5803
u4830:
	line	84
	
l5797:; BSR set to: 0

	line	85
	
l5799:; BSR set to: 0

	movlw	low(0)
	movwf	((?___fldiv))&0ffh
	movlw	high(0)
	movwf	((?___fldiv+1))&0ffh
	movlw	low highword(0)
	movwf	((?___fldiv+2))&0ffh
	movlw	high highword(0)
	movwf	((?___fldiv+3))&0ffh
	goto	l1901
	line	89
	
l5803:; BSR set to: 0

	movf	((___fldiv@aexp))&0ffh,w
	movff	(___fldiv@bexp),??___fldiv+0+0
	clrf	(??___fldiv+0+0+1)&0ffh
	subwf	(??___fldiv+0+0)&0ffh
	movlw	0
	subwfb	(??___fldiv+0+1)&0ffh
	movlw	low(07Fh)
	addwf	(??___fldiv+0+0)&0ffh,w
	movwf	((___fldiv@new_exp))&0ffh
	movlw	high(07Fh)
	addwfc	(??___fldiv+0+1)&0ffh,w
	movwf	1+((___fldiv@new_exp))&0ffh
	line	92
	
l5805:; BSR set to: 0

	movff	(___fldiv@b),(___fldiv@rem)
	movff	(___fldiv@b+1),(___fldiv@rem+1)
	movff	(___fldiv@b+2),(___fldiv@rem+2)
	movff	(___fldiv@b+3),(___fldiv@rem+3)
	line	93
	
l5807:; BSR set to: 0

	movlw	low(0)
	movwf	((___fldiv@b))&0ffh
	movlw	high(0)
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fldiv@b+3))&0ffh
	line	94
	
l5809:; BSR set to: 0

	movlw	low(0)
	movwf	((___fldiv@grs))&0ffh
	movlw	high(0)
	movwf	((___fldiv@grs+1))&0ffh
	movlw	low highword(0)
	movwf	((___fldiv@grs+2))&0ffh
	movlw	high highword(0)
	movwf	((___fldiv@grs+3))&0ffh
	line	96
	
l5811:; BSR set to: 0

	movlw	low(0)
	movwf	((___fldiv@aexp))&0ffh
	line	97
	goto	l1903
	line	100
	
l5813:; BSR set to: 0

	movf	((___fldiv@aexp))&0ffh,w
	btfsc	status,2
	goto	u4841
	goto	u4840
u4841:
	goto	l5821
u4840:
	line	101
	
l5815:; BSR set to: 0

	bcf	status,0
	rlcf	((___fldiv@rem))&0ffh
	rlcf	((___fldiv@rem+1))&0ffh
	rlcf	((___fldiv@rem+2))&0ffh
	rlcf	((___fldiv@rem+3))&0ffh
	line	102
	bcf	status,0
	rlcf	((___fldiv@b))&0ffh
	rlcf	((___fldiv@b+1))&0ffh
	rlcf	((___fldiv@b+2))&0ffh
	rlcf	((___fldiv@b+3))&0ffh
	line	103
	
l5817:; BSR set to: 0

	
	btfss	((___fldiv@grs+3))&0ffh,(31)&7
	goto	u4851
	goto	u4850
u4851:
	goto	l1906
u4850:
	line	104
	
l5819:; BSR set to: 0

	bsf	(0+(0/8)+(___fldiv@b))&0ffh,(0)&7
	line	105
	
l1906:; BSR set to: 0

	line	106
	bcf	status,0
	rlcf	((___fldiv@grs))&0ffh
	rlcf	((___fldiv@grs+1))&0ffh
	rlcf	((___fldiv@grs+2))&0ffh
	rlcf	((___fldiv@grs+3))&0ffh
	line	112
	
l5821:; BSR set to: 0

		movf	((___fldiv@a))&0ffh,w
	subwf	((___fldiv@rem))&0ffh,w
	movf	((___fldiv@a+1))&0ffh,w
	subwfb	((___fldiv@rem+1))&0ffh,w
	movf	((___fldiv@a+2))&0ffh,w
	subwfb	((___fldiv@rem+2))&0ffh,w
	movf	((___fldiv@a+3))&0ffh,w
	subwfb	((___fldiv@rem+3))&0ffh,w
	btfss	status,0
	goto	u4861
	goto	u4860

u4861:
	goto	l5827
u4860:
	line	115
	
l5823:; BSR set to: 0

	bsf	(0+(30/8)+(___fldiv@grs))&0ffh,(30)&7
	line	116
	
l5825:; BSR set to: 0

	movf	((___fldiv@a))&0ffh,w
	subwf	((___fldiv@rem))&0ffh
	movf	((___fldiv@a+1))&0ffh,w
	subwfb	((___fldiv@rem+1))&0ffh
	movf	((___fldiv@a+2))&0ffh,w
	subwfb	((___fldiv@rem+2))&0ffh
	movf	((___fldiv@a+3))&0ffh,w
	subwfb	((___fldiv@rem+3))&0ffh
	line	118
	
l5827:; BSR set to: 0

	incf	((___fldiv@aexp))&0ffh
	line	119
	
l1903:; BSR set to: 0

	line	97
		movlw	01Ah-1
	cpfsgt	((___fldiv@aexp))&0ffh
	goto	u4871
	goto	u4870

u4871:
	goto	l5813
u4870:
	line	122
	
l5829:; BSR set to: 0

	movf	((___fldiv@rem))&0ffh,w
iorwf	((___fldiv@rem+1))&0ffh,w
iorwf	((___fldiv@rem+2))&0ffh,w
iorwf	((___fldiv@rem+3))&0ffh,w
	btfsc	status,2
	goto	u4881
	goto	u4880

u4881:
	goto	l5839
u4880:
	line	123
	
l5831:; BSR set to: 0

	bsf	(0+(0/8)+(___fldiv@grs))&0ffh,(0)&7
	goto	l5839
	line	128
	
l5833:; BSR set to: 0

	bcf	status,0
	rlcf	((___fldiv@b))&0ffh
	rlcf	((___fldiv@b+1))&0ffh
	rlcf	((___fldiv@b+2))&0ffh
	rlcf	((___fldiv@b+3))&0ffh
	line	129
	
l5835:; BSR set to: 0

	
	btfss	((___fldiv@grs+3))&0ffh,(31)&7
	goto	u4891
	goto	u4890
u4891:
	goto	l1912
u4890:
	line	130
	
l5837:; BSR set to: 0

	bsf	(0+(0/8)+(___fldiv@b))&0ffh,(0)&7
	line	131
	
l1912:; BSR set to: 0

	line	132
	bcf	status,0
	rlcf	((___fldiv@grs))&0ffh
	rlcf	((___fldiv@grs+1))&0ffh
	rlcf	((___fldiv@grs+2))&0ffh
	rlcf	((___fldiv@grs+3))&0ffh
	line	133
	decf	((___fldiv@new_exp))&0ffh
	btfss	status,0
	decf	((___fldiv@new_exp+1))&0ffh
	line	127
	
l5839:; BSR set to: 0

	
	btfss	((___fldiv@b+2))&0ffh,(23)&7
	goto	u4901
	goto	u4900
u4901:
	goto	l5833
u4900:
	line	139
	
l5841:; BSR set to: 0

	movlw	low(0)
	movwf	((___fldiv@aexp))&0ffh
	line	140
	
l5843:; BSR set to: 0

	
	btfss	((___fldiv@grs+3))&0ffh,(31)&7
	goto	u4911
	goto	u4910
u4911:
	goto	l1914
u4910:
	line	141
	
l5845:; BSR set to: 0

	movlw	0FFh
	andwf	((___fldiv@grs))&0ffh,w
	movwf	(??___fldiv+0+0)&0ffh
	movlw	0FFh
	andwf	((___fldiv@grs+1))&0ffh,w
	movwf	1+(??___fldiv+0+0)&0ffh
	
	movlw	0FFh
	andwf	((___fldiv@grs+2))&0ffh,w
	movwf	2+(??___fldiv+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___fldiv@grs+3))&0ffh,w
	movwf	3+(??___fldiv+0+0)&0ffh
	movf	(??___fldiv+0+0)&0ffh,w
iorwf	(??___fldiv+0+1)&0ffh,w
iorwf	(??___fldiv+0+2)&0ffh,w
iorwf	(??___fldiv+0+3)&0ffh,w
	btfsc	status,2
	goto	u4921
	goto	u4920

u4921:
	goto	l1915
u4920:
	line	142
	
l5847:; BSR set to: 0

	movlw	low(01h)
	movwf	((___fldiv@aexp))&0ffh
	line	143
	goto	l1914
	line	144
	
l1915:; BSR set to: 0

	line	145
	
	btfss	((___fldiv@b))&0ffh,(0)&7
	goto	u4931
	goto	u4930
u4931:
	goto	l1914
u4930:
	goto	l5847
	line	149
	
l1914:; BSR set to: 0

	line	150
	movf	((___fldiv@aexp))&0ffh,w
	btfsc	status,2
	goto	u4941
	goto	u4940
u4941:
	goto	l5859
u4940:
	line	151
	
l5851:; BSR set to: 0

	movlw	low(01h)
	addwf	((___fldiv@b))&0ffh
	movlw	0
	addwfc	((___fldiv@b+1))&0ffh
	addwfc	((___fldiv@b+2))&0ffh
	addwfc	((___fldiv@b+3))&0ffh
	line	152
	
l5853:; BSR set to: 0

	
	btfss	((___fldiv@b+3))&0ffh,(24)&7
	goto	u4951
	goto	u4950
u4951:
	goto	l5859
u4950:
	line	153
	
l5855:; BSR set to: 0

	movff	(___fldiv@b),??___fldiv+0+0
	movff	(___fldiv@b+1),??___fldiv+0+0+1
	movff	(___fldiv@b+2),??___fldiv+0+0+2
	movff	(___fldiv@b+3),??___fldiv+0+0+3
	rlcf	(??___fldiv+0+3)&0ffh,w
	rrcf	(??___fldiv+0+3)&0ffh
	rrcf	(??___fldiv+0+2)&0ffh
	rrcf	(??___fldiv+0+1)&0ffh
	rrcf	(??___fldiv+0+0)&0ffh
	movff	??___fldiv+0+0,(___fldiv@b)
	movff	??___fldiv+0+1,(___fldiv@b+1)
	movff	??___fldiv+0+2,(___fldiv@b+2)
	movff	??___fldiv+0+3,(___fldiv@b+3)
	line	154
	
l5857:; BSR set to: 0

	infsnz	((___fldiv@new_exp))&0ffh
	incf	((___fldiv@new_exp+1))&0ffh
	line	159
	
l5859:; BSR set to: 0

	btfsc	((___fldiv@new_exp+1))&0ffh,7
	goto	u4961
	movf	((___fldiv@new_exp+1))&0ffh,w
	bnz	u4960
	incf	((___fldiv@new_exp))&0ffh,w
	btfss	status,0
	goto	u4961
	goto	u4960

u4961:
	goto	l5863
u4960:
	line	160
	
l5861:; BSR set to: 0

	movlw	high(0FFh)
	movwf	((___fldiv@new_exp+1))&0ffh
	setf	((___fldiv@new_exp))&0ffh
	line	161
	movlw	low(0)
	movwf	((___fldiv@b))&0ffh
	movlw	high(0)
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fldiv@b+3))&0ffh
	line	165
	
l5863:; BSR set to: 0

	btfsc	((___fldiv@new_exp+1))&0ffh,7
	goto	u4970
	movf	((___fldiv@new_exp+1))&0ffh,w
	bnz	u4971
	decf	((___fldiv@new_exp))&0ffh,w
	btfsc	status,0
	goto	u4971
	goto	u4970

u4971:
	goto	l5867
u4970:
	line	166
	
l5865:; BSR set to: 0

	movlw	high(0)
	movwf	((___fldiv@new_exp+1))&0ffh
	movlw	low(0)
	movwf	((___fldiv@new_exp))&0ffh
	line	167
	movlw	low(0)
	movwf	((___fldiv@b))&0ffh
	movlw	high(0)
	movwf	((___fldiv@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fldiv@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fldiv@b+3))&0ffh
	line	169
	movlw	low(0)
	movwf	((___fldiv@sign))&0ffh
	line	173
	
l5867:; BSR set to: 0

	movff	(___fldiv@new_exp),(___fldiv@bexp)
	line	175
	
l5869:; BSR set to: 0

	
	btfss	((___fldiv@bexp))&0ffh,(0)&7
	goto	u4981
	goto	u4980
u4981:
	goto	l5873
u4980:
	line	176
	
l5871:; BSR set to: 0

	bsf	(0+(7/8)+0+(___fldiv@b+02h))&0ffh,(7)&7
	line	177
	goto	l5875
	line	180
	
l5873:; BSR set to: 0

	bcf	(0+(7/8)+0+(___fldiv@b+02h))&0ffh,(7)&7
	line	182
	
l5875:; BSR set to: 0

	bcf	status,0
	rrcf	((___fldiv@bexp))&0ffh,w
	movwf	(0+(___fldiv@b+03h))&0ffh
	goto	l5789
	line	185
	
l1901:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fldiv
	__end_of___fldiv:
	signat	___fldiv,8316
	global	_FCM_update_display

;; *************** function _FCM_update_display *****************
;; Defined at:
;;		line 3357 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    9
;; This function calls:
;;		_FCD_049e1_LCD_BL0169__Cursor
;;		_FCD_049e1_LCD_BL0169__PrintFloat
;;		_FCD_049e1_LCD_BL0169__PrintNumber
;;		_FCD_049e1_LCD_BL0169__PrintString
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text3,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	3357
global __ptext3
__ptext3:
psect	text3
	file	"feedback control - PIC.c"
	line	3357
	global	__size_of_FCM_update_display
	__size_of_FCM_update_display	equ	__end_of_FCM_update_display-_FCM_update_display
	
_FCM_update_display:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	3361
	
l5689:; BSR set to: 0

	bcf	(0+(3/8)+(c:3973))^0f00h,c,(3)&7	;volatile
	
l5691:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	iorlw	low(08h)
	movwf	((c:3981))^0f00h,c	;volatile
	line	3364
	
l5695:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_049e1_LCD_BL0169__Cursor@FCL_Y))&0ffh
	movlw	(0)&0ffh
	
	call	_FCD_049e1_LCD_BL0169__Cursor
	line	3367
	
l5697:; BSR set to: 0

		movlw	low(STR_2)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_2)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(0Ah)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(0Ah)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3370
	
l5699:; BSR set to: 0

	movff	(_FCV_PWMVALUE),(FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER)	;volatile
	clrf	((FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER+1))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintNumber	;wreg free
	line	3373
	
l5701:; BSR set to: 0

		movlw	low(STR_3)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_3)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3376
	
l5703:; BSR set to: 0

	movlw	low(01h)
	movwf	((FCD_049e1_LCD_BL0169__Cursor@FCL_Y))&0ffh
	movlw	(0)&0ffh
	
	call	_FCD_049e1_LCD_BL0169__Cursor
	line	3379
	
l5705:; BSR set to: 0

		movlw	low(STR_4)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_4)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(08h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(08h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3382
	
l5707:; BSR set to: 0

	movff	(_FCV_REVOLUTIONTIME),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER)	;volatile
	movff	(_FCV_REVOLUTIONTIME+1),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+1)	;volatile
	movff	(_FCV_REVOLUTIONTIME+2),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+2)	;volatile
	movff	(_FCV_REVOLUTIONTIME+3),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+3)	;volatile
	movlw	low(04h)
	movwf	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintFloat	;wreg free
	line	3385
	
l5709:; BSR set to: 0

		movlw	low(STR_5)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_5)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3388
	
l5711:; BSR set to: 0

	movlw	low(02h)
	movwf	((FCD_049e1_LCD_BL0169__Cursor@FCL_Y))&0ffh
	movlw	(0)&0ffh
	
	call	_FCD_049e1_LCD_BL0169__Cursor
	line	3391
	
l5713:; BSR set to: 0

		movlw	low(STR_6)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_6)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(05h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(05h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3394
	
l5715:; BSR set to: 0

	movff	(_FCV_RPM),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER)	;volatile
	movff	(_FCV_RPM+1),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+1)	;volatile
	movff	(_FCV_RPM+2),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+2)	;volatile
	movff	(_FCV_RPM+3),(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+3)	;volatile
	movlw	low(02h)
	movwf	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintFloat	;wreg free
	line	3397
	
l5717:; BSR set to: 0

		movlw	low(STR_7)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	movlw	high(STR_7)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(03h)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3400
	
l5719:; BSR set to: 0

	bcf	(0+(3/8)+(c:3973))^0f00h,c,(3)&7	;volatile
	
l5723:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3981))^0f00h,c	;volatile
	line	3402
	
l1294:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCM_update_display
	__end_of_FCM_update_display:
	signat	_FCM_update_display,89
	global	_FCD_049e1_LCD_BL0169__PrintNumber

;; *************** function _FCD_049e1_LCD_BL0169__PrintNumber *****************
;; Defined at:
;;		line 3183 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_NUMBER      2   44[BANK0 ] short 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    8
;; This function calls:
;;		_FCD_04071_LCD1__PrintNumber
;; This function is called by:
;;		_FCM_update_display
;; This function uses a non-reentrant model
;;
psect	text4,class=CODE,space=0,reloc=2,group=0
	line	3183
global __ptext4
__ptext4:
psect	text4
	file	"feedback control - PIC.c"
	line	3183
	global	__size_of_FCD_049e1_LCD_BL0169__PrintNumber
	__size_of_FCD_049e1_LCD_BL0169__PrintNumber	equ	__end_of_FCD_049e1_LCD_BL0169__PrintNumber-_FCD_049e1_LCD_BL0169__PrintNumber
	
_FCD_049e1_LCD_BL0169__PrintNumber:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	3186
	
l5579:; BSR set to: 0

	movff	(FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER),(FCD_04071_LCD1__PrintNumber@FCL_NUMBER)
	movff	(FCD_049e1_LCD_BL0169__PrintNumber@FCL_NUMBER+1),(FCD_04071_LCD1__PrintNumber@FCL_NUMBER+1)
	call	_FCD_04071_LCD1__PrintNumber	;wreg free
	line	3188
	
l1244:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__PrintNumber
	__end_of_FCD_049e1_LCD_BL0169__PrintNumber:
	signat	_FCD_049e1_LCD_BL0169__PrintNumber,4217
	global	_FCD_04071_LCD1__PrintNumber

;; *************** function _FCD_04071_LCD1__PrintNumber *****************
;; Defined at:
;;		line 2580 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_NUMBER      2   32[BANK0 ] short 
;; Auto vars:     Size  Location     Type
;;  FCL_S          10   34[BANK0 ] unsigned char [10]
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      12       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_04071_LCD1__PrintString
;;		_FCI_TOSTRING
;; This function is called by:
;;		_FCD_049e1_LCD_BL0169__PrintNumber
;; This function uses a non-reentrant model
;;
psect	text5,class=CODE,space=0,reloc=2,group=0
	line	2580
global __ptext5
__ptext5:
psect	text5
	file	"feedback control - PIC.c"
	line	2580
	global	__size_of_FCD_04071_LCD1__PrintNumber
	__size_of_FCD_04071_LCD1__PrintNumber	equ	__end_of_FCD_04071_LCD1__PrintNumber-_FCD_04071_LCD1__PrintNumber
	
_FCD_04071_LCD1__PrintNumber:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	2587
	
l5125:; BSR set to: 0

	movff	(FCD_04071_LCD1__PrintNumber@FCL_NUMBER),(FCI_TOSTRING@iSrc1)
	movff	(FCD_04071_LCD1__PrintNumber@FCL_NUMBER+1),(FCI_TOSTRING@iSrc1+1)
	movlw	0
	btfsc	((FCI_TOSTRING@iSrc1+1))&0ffh,7
	movlw	-1
	movwf	((FCI_TOSTRING@iSrc1+2))&0ffh
	movwf	((FCI_TOSTRING@iSrc1+3))&0ffh
		movlw	low(FCD_04071_LCD1__PrintNumber@FCL_S)
	movwf	((FCI_TOSTRING@sDst))&0ffh

	movlw	high(0Ah)
	movwf	((FCI_TOSTRING@iDst_len+1))&0ffh
	movlw	low(0Ah)
	movwf	((FCI_TOSTRING@iDst_len))&0ffh
	call	_FCI_TOSTRING	;wreg free
	line	2589
	
l5127:; BSR set to: 0

		movlw	low(FCD_04071_LCD1__PrintNumber@FCL_S)
	movwf	((FCD_04071_LCD1__PrintString@FCL_TEXT))&0ffh
	clrf	((FCD_04071_LCD1__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(0Ah)
	movwf	((FCD_04071_LCD1__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(0Ah)
	movwf	((FCD_04071_LCD1__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_04071_LCD1__PrintString	;wreg free
	line	2593
	
l1055:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__PrintNumber
	__end_of_FCD_04071_LCD1__PrintNumber:
	signat	_FCD_04071_LCD1__PrintNumber,4217
	global	_FCI_TOSTRING

;; *************** function _FCI_TOSTRING *****************
;; Defined at:
;;		line 395 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
;; Parameters:    Size  Location     Type
;;  iSrc1           4   13[BANK0 ] long 
;;  sDst            1   17[BANK0 ] PTR unsigned char 
;;		 -> FCD_04071_LCD1__PrintNumber@FCL_S(10), FCI_INTTOFORMATTEDSTRING@sTemp(20), FCI_IMPLODEFROMINTARRAY@sTemp(20), 
;;  iDst_len        2   18[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;  top             4   28[BANK0 ] unsigned long 
;;  iSrc            4   24[BANK0 ] long 
;;  idx             1   23[BANK0 ] unsigned char 
;;  tmp1            1   22[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      PTR unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       7       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      19       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       19 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		___lldiv
;;		___lmul
;; This function is called by:
;;		_FCD_04071_LCD1__PrintNumber
;; This function uses a non-reentrant model
;;
psect	text6,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	395
global __ptext6
__ptext6:
psect	text6
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	395
	global	__size_of_FCI_TOSTRING
	__size_of_FCI_TOSTRING	equ	__end_of_FCI_TOSTRING-_FCI_TOSTRING
	
_FCI_TOSTRING:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	399
	
l4645:; BSR set to: 0

	movff	(FCI_TOSTRING@iSrc1),(FCI_TOSTRING@iSrc)
	movff	(FCI_TOSTRING@iSrc1+1),(FCI_TOSTRING@iSrc+1)
	movff	(FCI_TOSTRING@iSrc1+2),(FCI_TOSTRING@iSrc+2)
	movff	(FCI_TOSTRING@iSrc1+3),(FCI_TOSTRING@iSrc+3)
	line	402
	
l4647:; BSR set to: 0

	movlw	low(03B9ACA00h)
	movwf	((FCI_TOSTRING@top))&0ffh
	movlw	high(03B9ACA00h)
	movwf	((FCI_TOSTRING@top+1))&0ffh
	movlw	low highword(03B9ACA00h)
	movwf	((FCI_TOSTRING@top+2))&0ffh
	movlw	high highword(03B9ACA00h)
	movwf	((FCI_TOSTRING@top+3))&0ffh
	line	407
	movlw	low(0)
	movwf	((FCI_TOSTRING@idx))&0ffh
	line	409
	
l4649:; BSR set to: 0

	movf	((FCI_TOSTRING@iDst_len))&0ffh,w
iorwf	((FCI_TOSTRING@iDst_len+1))&0ffh,w
	btfss	status,2
	goto	u3431
	goto	u3430

u3431:
	goto	l4653
u3430:
	goto	l300
	line	413
	
l4653:; BSR set to: 0

	btfsc	((FCI_TOSTRING@iSrc+3))&0ffh,7
	goto	u3440
	goto	u3441

u3441:
	goto	l4661
u3440:
	line	415
	
l4655:; BSR set to: 0

	movf	((FCI_TOSTRING@sDst))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(02Dh)
	movwf	indf2
	line	416
	
l4657:; BSR set to: 0

	incf	((FCI_TOSTRING@idx))&0ffh
	line	417
	
l4659:; BSR set to: 0

	comf	((FCI_TOSTRING@iSrc+3))&0ffh
	comf	((FCI_TOSTRING@iSrc+2))&0ffh
	comf	((FCI_TOSTRING@iSrc+1))&0ffh
	negf	((FCI_TOSTRING@iSrc))&0ffh
	movlw	0
	addwfc	((FCI_TOSTRING@iSrc+1))&0ffh
	addwfc	((FCI_TOSTRING@iSrc+2))&0ffh
	addwfc	((FCI_TOSTRING@iSrc+3))&0ffh
	line	420
	
l4661:; BSR set to: 0

	movlw	low(0)
	movwf	((FCI_TOSTRING@tmp1))&0ffh
	line	421
	
l4663:; BSR set to: 0

	movf	((FCI_TOSTRING@iSrc))&0ffh,w
iorwf	((FCI_TOSTRING@iSrc+1))&0ffh,w
iorwf	((FCI_TOSTRING@iSrc+2))&0ffh,w
iorwf	((FCI_TOSTRING@iSrc+3))&0ffh,w
	btfss	status,2
	goto	u3451
	goto	u3450

u3451:
	goto	l4683
u3450:
	line	423
	
l4665:; BSR set to: 0

	movlw	low(01h)
	movwf	((FCI_TOSTRING@tmp1))&0ffh
	line	424
	movlw	low(01h)
	movwf	((FCI_TOSTRING@top))&0ffh
	movlw	high(01h)
	movwf	((FCI_TOSTRING@top+1))&0ffh
	movlw	low highword(01h)
	movwf	((FCI_TOSTRING@top+2))&0ffh
	movlw	high highword(01h)
	movwf	((FCI_TOSTRING@top+3))&0ffh
	goto	l4683
	line	429
	
l4667:; BSR set to: 0

		movf	((FCI_TOSTRING@top))&0ffh,w
	subwf	((FCI_TOSTRING@iSrc))&0ffh,w
	movf	((FCI_TOSTRING@top+1))&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+1))&0ffh,w
	movf	((FCI_TOSTRING@top+2))&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+2))&0ffh,w
	movf	((FCI_TOSTRING@top+3))&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+3))&0ffh,w
	btfsc	status,0
	goto	u3461
	goto	u3460

u3461:
	goto	l4671
u3460:
	
l4669:; BSR set to: 0

	movf	((FCI_TOSTRING@tmp1))&0ffh,w
	btfsc	status,2
	goto	u3471
	goto	u3470
u3471:
	goto	l4681
u3470:
	line	435
	
l4671:; BSR set to: 0

	movff	(FCI_TOSTRING@iSrc),(___lldiv@dividend)
	movff	(FCI_TOSTRING@iSrc+1),(___lldiv@dividend+1)
	movff	(FCI_TOSTRING@iSrc+2),(___lldiv@dividend+2)
	movff	(FCI_TOSTRING@iSrc+3),(___lldiv@dividend+3)
	movff	(FCI_TOSTRING@top),(___lldiv@divisor)
	movff	(FCI_TOSTRING@top+1),(___lldiv@divisor+1)
	movff	(FCI_TOSTRING@top+2),(___lldiv@divisor+2)
	movff	(FCI_TOSTRING@top+3),(___lldiv@divisor+3)
	call	___lldiv	;wreg free
	movf	(0+?___lldiv)&0ffh,w
	movwf	((FCI_TOSTRING@tmp1))&0ffh
	line	439
	
l4673:; BSR set to: 0

	movf	((FCI_TOSTRING@sDst))&0ffh,w
	addwf	((FCI_TOSTRING@idx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movf	((FCI_TOSTRING@tmp1))&0ffh,w
	addlw	low(030h)
	movwf	indf2,c

	line	440
	
l4675:; BSR set to: 0

	incf	((FCI_TOSTRING@idx))&0ffh
	line	441
	
l4677:; BSR set to: 0

	movf	((FCI_TOSTRING@tmp1))&0ffh,w
	movwf	((___lmul@multiplier))&0ffh
	clrf	((___lmul@multiplier+1))&0ffh
	clrf	((___lmul@multiplier+2))&0ffh
	clrf	((___lmul@multiplier+3))&0ffh

	movff	(FCI_TOSTRING@top),(___lmul@multiplicand)
	movff	(FCI_TOSTRING@top+1),(___lmul@multiplicand+1)
	movff	(FCI_TOSTRING@top+2),(___lmul@multiplicand+2)
	movff	(FCI_TOSTRING@top+3),(___lmul@multiplicand+3)
	call	___lmul	;wreg free
	movf	(0+?___lmul)&0ffh,w
	subwf	((FCI_TOSTRING@iSrc))&0ffh
	movf	(1+?___lmul)&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+1))&0ffh
	movf	(2+?___lmul)&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+2))&0ffh
	movf	(3+?___lmul)&0ffh,w
	subwfb	((FCI_TOSTRING@iSrc+3))&0ffh

	line	442
	
l4679:; BSR set to: 0

	movlw	low(01h)
	movwf	((FCI_TOSTRING@tmp1))&0ffh
	line	444
	
l4681:; BSR set to: 0

	movff	(FCI_TOSTRING@top),(___lldiv@dividend)
	movff	(FCI_TOSTRING@top+1),(___lldiv@dividend+1)
	movff	(FCI_TOSTRING@top+2),(___lldiv@dividend+2)
	movff	(FCI_TOSTRING@top+3),(___lldiv@dividend+3)
	movlw	low(0Ah)
	movwf	((___lldiv@divisor))&0ffh
	movlw	high(0Ah)
	movwf	((___lldiv@divisor+1))&0ffh
	movlw	low highword(0Ah)
	movwf	((___lldiv@divisor+2))&0ffh
	movlw	high highword(0Ah)
	movwf	((___lldiv@divisor+3))&0ffh
	call	___lldiv	;wreg free
	movff	0+?___lldiv,(FCI_TOSTRING@top)
	movff	1+?___lldiv,(FCI_TOSTRING@top+1)
	movff	2+?___lldiv,(FCI_TOSTRING@top+2)
	movff	3+?___lldiv,(FCI_TOSTRING@top+3)
	
	line	426
	
l4683:; BSR set to: 0

	movf	((FCI_TOSTRING@idx))&0ffh,w
	movwf	(??_FCI_TOSTRING+0+0)&0ffh
	clrf	(??_FCI_TOSTRING+0+0+1)&0ffh

		movf	((FCI_TOSTRING@iDst_len))&0ffh,w
	subwf	(??_FCI_TOSTRING+0+0)&0ffh,w
	movf	((FCI_TOSTRING@iDst_len+1))&0ffh,w
	subwfb	(??_FCI_TOSTRING+0+1)&0ffh,w
	btfsc	status,0
	goto	u3481
	goto	u3480

u3481:
	goto	l4687
u3480:
	
l4685:; BSR set to: 0

	movf	((FCI_TOSTRING@top))&0ffh,w
iorwf	((FCI_TOSTRING@top+1))&0ffh,w
iorwf	((FCI_TOSTRING@top+2))&0ffh,w
iorwf	((FCI_TOSTRING@top+3))&0ffh,w
	btfss	status,2
	goto	u3491
	goto	u3490

u3491:
	goto	l4667
u3490:
	line	447
	
l4687:; BSR set to: 0

	movf	((FCI_TOSTRING@idx))&0ffh,w
	movwf	(??_FCI_TOSTRING+0+0)&0ffh
	clrf	(??_FCI_TOSTRING+0+0+1)&0ffh

		movf	((FCI_TOSTRING@iDst_len))&0ffh,w
	subwf	(??_FCI_TOSTRING+0+0)&0ffh,w
	movf	((FCI_TOSTRING@iDst_len+1))&0ffh,w
	subwfb	(??_FCI_TOSTRING+0+1)&0ffh,w
	btfsc	status,0
	goto	u3501
	goto	u3500

u3501:
	goto	l300
u3500:
	line	448
	
l4689:; BSR set to: 0

	movf	((FCI_TOSTRING@sDst))&0ffh,w
	addwf	((FCI_TOSTRING@idx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	450
	
l300:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCI_TOSTRING
	__end_of_FCI_TOSTRING:
	signat	_FCI_TOSTRING,12410
	global	___lmul

;; *************** function ___lmul *****************
;; Defined at:
;;		line 15 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\Umul32.c"
;; Parameters:    Size  Location     Type
;;  multiplier      4    0[BANK0 ] unsigned long 
;;  multiplicand    4    4[BANK0 ] unsigned long 
;; Auto vars:     Size  Location     Type
;;  product         4    8[BANK0 ] unsigned long 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      12       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_TOSTRING
;; This function uses a non-reentrant model
;;
psect	text7,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\Umul32.c"
	line	15
global __ptext7
__ptext7:
psect	text7
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\Umul32.c"
	line	15
	global	__size_of___lmul
	__size_of___lmul	equ	__end_of___lmul-___lmul
	
___lmul:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	119
	
l4277:; BSR set to: 0

	movlw	low(0)
	movwf	((___lmul@product))&0ffh
	movlw	high(0)
	movwf	((___lmul@product+1))&0ffh
	movlw	low highword(0)
	movwf	((___lmul@product+2))&0ffh
	movlw	high highword(0)
	movwf	((___lmul@product+3))&0ffh
	line	121
	
l4279:; BSR set to: 0

	
	btfss	((___lmul@multiplier))&0ffh,(0)&7
	goto	u2741
	goto	u2740
u2741:
	goto	l4283
u2740:
	line	122
	
l4281:; BSR set to: 0

	movf	((___lmul@multiplicand))&0ffh,w
	addwf	((___lmul@product))&0ffh
	movf	((___lmul@multiplicand+1))&0ffh,w
	addwfc	((___lmul@product+1))&0ffh
	movf	((___lmul@multiplicand+2))&0ffh,w
	addwfc	((___lmul@product+2))&0ffh
	movf	((___lmul@multiplicand+3))&0ffh,w
	addwfc	((___lmul@product+3))&0ffh
	line	123
	
l4283:; BSR set to: 0

	bcf	status,0
	rlcf	((___lmul@multiplicand))&0ffh
	rlcf	((___lmul@multiplicand+1))&0ffh
	rlcf	((___lmul@multiplicand+2))&0ffh
	rlcf	((___lmul@multiplicand+3))&0ffh
	line	124
	
l4285:; BSR set to: 0

	bcf	status,0
	rrcf	((___lmul@multiplier+3))&0ffh
	rrcf	((___lmul@multiplier+2))&0ffh
	rrcf	((___lmul@multiplier+1))&0ffh
	rrcf	((___lmul@multiplier))&0ffh
	line	125
	movf	((___lmul@multiplier))&0ffh,w
iorwf	((___lmul@multiplier+1))&0ffh,w
iorwf	((___lmul@multiplier+2))&0ffh,w
iorwf	((___lmul@multiplier+3))&0ffh,w
	btfss	status,2
	goto	u2751
	goto	u2750

u2751:
	goto	l4279
u2750:
	
l1342:; BSR set to: 0

	line	128
	movff	(___lmul@product),(?___lmul)
	movff	(___lmul@product+1),(?___lmul+1)
	movff	(___lmul@product+2),(?___lmul+2)
	movff	(___lmul@product+3),(?___lmul+3)
	line	129
	
l1343:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___lmul
	__end_of___lmul:
	signat	___lmul,8316
	global	___lldiv

;; *************** function ___lldiv *****************
;; Defined at:
;;		line 7 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\__lldiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        4    0[BANK0 ] unsigned long 
;;  divisor         4    4[BANK0 ] unsigned long 
;; Auto vars:     Size  Location     Type
;;  quotient        4    8[BANK0 ] unsigned long 
;;  counter         1   12[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      13       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       13 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_TOSTRING
;; This function uses a non-reentrant model
;;
psect	text8,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\__lldiv.c"
	line	7
global __ptext8
__ptext8:
psect	text8
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\__lldiv.c"
	line	7
	global	__size_of___lldiv
	__size_of___lldiv	equ	__end_of___lldiv-___lldiv
	
___lldiv:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	13
	
l4287:; BSR set to: 0

	movlw	low(0)
	movwf	((___lldiv@quotient))&0ffh
	movlw	high(0)
	movwf	((___lldiv@quotient+1))&0ffh
	movlw	low highword(0)
	movwf	((___lldiv@quotient+2))&0ffh
	movlw	high highword(0)
	movwf	((___lldiv@quotient+3))&0ffh
	line	14
	
l4289:; BSR set to: 0

	movf	((___lldiv@divisor))&0ffh,w
iorwf	((___lldiv@divisor+1))&0ffh,w
iorwf	((___lldiv@divisor+2))&0ffh,w
iorwf	((___lldiv@divisor+3))&0ffh,w
	btfsc	status,2
	goto	u2761
	goto	u2760

u2761:
	goto	l1358
u2760:
	line	15
	
l4291:; BSR set to: 0

	movlw	low(01h)
	movwf	((___lldiv@counter))&0ffh
	line	16
	goto	l4295
	line	17
	
l4293:; BSR set to: 0

	bcf	status,0
	rlcf	((___lldiv@divisor))&0ffh
	rlcf	((___lldiv@divisor+1))&0ffh
	rlcf	((___lldiv@divisor+2))&0ffh
	rlcf	((___lldiv@divisor+3))&0ffh
	line	18
	incf	((___lldiv@counter))&0ffh
	line	16
	
l4295:; BSR set to: 0

	
	btfss	((___lldiv@divisor+3))&0ffh,(31)&7
	goto	u2771
	goto	u2770
u2771:
	goto	l4293
u2770:
	line	21
	
l4297:; BSR set to: 0

	bcf	status,0
	rlcf	((___lldiv@quotient))&0ffh
	rlcf	((___lldiv@quotient+1))&0ffh
	rlcf	((___lldiv@quotient+2))&0ffh
	rlcf	((___lldiv@quotient+3))&0ffh
	line	22
	
l4299:; BSR set to: 0

		movf	((___lldiv@divisor))&0ffh,w
	subwf	((___lldiv@dividend))&0ffh,w
	movf	((___lldiv@divisor+1))&0ffh,w
	subwfb	((___lldiv@dividend+1))&0ffh,w
	movf	((___lldiv@divisor+2))&0ffh,w
	subwfb	((___lldiv@dividend+2))&0ffh,w
	movf	((___lldiv@divisor+3))&0ffh,w
	subwfb	((___lldiv@dividend+3))&0ffh,w
	btfss	status,0
	goto	u2781
	goto	u2780

u2781:
	goto	l4305
u2780:
	line	23
	
l4301:; BSR set to: 0

	movf	((___lldiv@divisor))&0ffh,w
	subwf	((___lldiv@dividend))&0ffh
	movf	((___lldiv@divisor+1))&0ffh,w
	subwfb	((___lldiv@dividend+1))&0ffh
	movf	((___lldiv@divisor+2))&0ffh,w
	subwfb	((___lldiv@dividend+2))&0ffh
	movf	((___lldiv@divisor+3))&0ffh,w
	subwfb	((___lldiv@dividend+3))&0ffh
	line	24
	
l4303:; BSR set to: 0

	bsf	(0+(0/8)+(___lldiv@quotient))&0ffh,(0)&7
	line	26
	
l4305:; BSR set to: 0

	bcf	status,0
	rrcf	((___lldiv@divisor+3))&0ffh
	rrcf	((___lldiv@divisor+2))&0ffh
	rrcf	((___lldiv@divisor+1))&0ffh
	rrcf	((___lldiv@divisor))&0ffh
	line	27
	
l4307:; BSR set to: 0

	decfsz	((___lldiv@counter))&0ffh
	
	goto	l4297
	line	28
	
l1358:; BSR set to: 0

	line	29
	movff	(___lldiv@quotient),(?___lldiv)
	movff	(___lldiv@quotient+1),(?___lldiv+1)
	movff	(___lldiv@quotient+2),(?___lldiv+2)
	movff	(___lldiv@quotient+3),(?___lldiv+3)
	line	30
	
l1365:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___lldiv
	__end_of___lldiv:
	signat	___lldiv,8316
	global	_FCD_049e1_LCD_BL0169__PrintFloat

;; *************** function _FCD_049e1_LCD_BL0169__PrintFloat *****************
;; Defined at:
;;		line 3275 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_NUMBER      4  105[BANK0 ] float 
;;  FCL_DECIMALP    1  109[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_S          10  110[BANK0 ] unsigned char [10]
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      15       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       15 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    8
;; This function calls:
;;		_FCD_049e1_LCD_BL0169__PrintString
;;		_FCI_FLOAT_TO_STRING
;; This function is called by:
;;		_FCM_update_display
;; This function uses a non-reentrant model
;;
psect	text9,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	3275
global __ptext9
__ptext9:
psect	text9
	file	"feedback control - PIC.c"
	line	3275
	global	__size_of_FCD_049e1_LCD_BL0169__PrintFloat
	__size_of_FCD_049e1_LCD_BL0169__PrintFloat	equ	__end_of_FCD_049e1_LCD_BL0169__PrintFloat-_FCD_049e1_LCD_BL0169__PrintFloat
	
_FCD_049e1_LCD_BL0169__PrintFloat:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	3282
	
l5583:; BSR set to: 0

		movlw	07h-1
	cpfsgt	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh
	goto	u4671
	goto	u4670

u4671:
	goto	l5587
u4670:
	line	3285
	
l5585:; BSR set to: 0

	movlw	low(06h)
	movwf	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh
	line	3287
	goto	l5591
	line	3289
	
l5587:; BSR set to: 0

	movf	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh,w
	btfss	status,2
	goto	u4681
	goto	u4680
u4681:
	goto	l5591
u4680:
	line	3292
	
l5589:; BSR set to: 0

	movlw	low(01h)
	movwf	((FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES))&0ffh
	line	3300
	
l5591:; BSR set to: 0

	movff	(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER),(FCI_FLOAT_TO_STRING@Number)
	movff	(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+1),(FCI_FLOAT_TO_STRING@Number+1)
	movff	(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+2),(FCI_FLOAT_TO_STRING@Number+2)
	movff	(FCD_049e1_LCD_BL0169__PrintFloat@FCL_NUMBER+3),(FCI_FLOAT_TO_STRING@Number+3)
	movff	(FCD_049e1_LCD_BL0169__PrintFloat@FCL_DECIMALPLACES),(FCI_FLOAT_TO_STRING@Precision)
		movlw	low(FCD_049e1_LCD_BL0169__PrintFloat@FCL_S)
	movwf	((FCI_FLOAT_TO_STRING@String))&0ffh

	movlw	high(0Ah)
	movwf	((FCI_FLOAT_TO_STRING@MSZ_String+1))&0ffh
	movlw	low(0Ah)
	movwf	((FCI_FLOAT_TO_STRING@MSZ_String))&0ffh
	call	_FCI_FLOAT_TO_STRING	;wreg free
	line	3302
	
l5593:; BSR set to: 0

		movlw	low(FCD_049e1_LCD_BL0169__PrintFloat@FCL_S)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT))&0ffh
	clrf	((FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1))&0ffh

	movlw	high(0Ah)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1))&0ffh
	movlw	low(0Ah)
	movwf	((FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT))&0ffh
	call	_FCD_049e1_LCD_BL0169__PrintString	;wreg free
	line	3306
	
l1265:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__PrintFloat
	__end_of_FCD_049e1_LCD_BL0169__PrintFloat:
	signat	_FCD_049e1_LCD_BL0169__PrintFloat,8313
	global	_FCI_FLOAT_TO_STRING

;; *************** function _FCI_FLOAT_TO_STRING *****************
;; Defined at:
;;		line 560 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
;; Parameters:    Size  Location     Type
;;  Number          4   50[BANK0 ] float 
;;  Precision       1   54[BANK0 ] unsigned char 
;;  String          1   55[BANK0 ] PTR unsigned char 
;;		 -> FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(10), FCD_04071_LCD1__PrintFloat@FCL_S(10), FCI_FLOATTOFORMATTEDSTRING@sTemp(20), FCI_IMPLODEFROMFLOATARRAY@sTemp(20), 
;;  MSZ_String      2   56[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;  rev_digits     12   58[BANK0 ] unsigned char [12]
;;  temp_whole      4   84[BANK0 ] long 
;;  rev_idx         2   88[BANK0 ] int 
;;  temp_string    12   70[BANK0 ] unsigned char [12]
;;  temp            4   98[BANK0 ] float 
;;  whole           4   94[BANK0 ] long 
;;  real            4   90[BANK0 ] float 
;;  stringidx       2  103[BANK0 ] unsigned short 
;;  temp_idx        2   82[BANK0 ] unsigned short 
;;  idx             1  102[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      PTR unsigned char 
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      47       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      55       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       55 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		___aldiv
;;		___almod
;;		___fladd
;;		___flmul
;;		___flneg
;;		___flsub
;;		___fltol
;;		___xxtofl
;;		_floor
;; This function is called by:
;;		_FCD_049e1_LCD_BL0169__PrintFloat
;; This function uses a non-reentrant model
;;
psect	text10,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	560
global __ptext10
__ptext10:
psect	text10
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	560
	global	__size_of_FCI_FLOAT_TO_STRING
	__size_of_FCI_FLOAT_TO_STRING	equ	__end_of_FCI_FLOAT_TO_STRING-_FCI_FLOAT_TO_STRING
	
_FCI_FLOAT_TO_STRING:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	564
	
l4951:; BSR set to: 0

	movlw	high(0)
	movwf	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh
	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	line	565
	movlw	low(normalize32(0x3f000000))
	movwf	((FCI_FLOAT_TO_STRING@temp))&0ffh
	movlw	high(normalize32(0x3f000000))
	movwf	((FCI_FLOAT_TO_STRING@temp+1))&0ffh
	movlw	low highword(normalize32(0x3f000000))
	movwf	((FCI_FLOAT_TO_STRING@temp+2))&0ffh
	movlw	high highword(normalize32(0x3f000000))
	movwf	((FCI_FLOAT_TO_STRING@temp+3))&0ffh
	line	570
	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	line	571
	
l4957:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@temp_string)
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	570
	
l4959:; BSR set to: 0

	incf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	
l4961:; BSR set to: 0

		movlw	0Ch-1
	cpfsgt	((FCI_FLOAT_TO_STRING@idx))&0ffh
	goto	u3881
	goto	u3880

u3881:
	goto	l4957
u3880:
	line	574
	
l4963:; BSR set to: 0

	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	goto	l4969
	
l4965:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@temp),(___flmul@b)
	movff	(FCI_FLOAT_TO_STRING@temp+1),(___flmul@b+1)
	movff	(FCI_FLOAT_TO_STRING@temp+2),(___flmul@b+2)
	movff	(FCI_FLOAT_TO_STRING@temp+3),(___flmul@b+3)
	movlw	low(normalize32(0x3dcccccd))
	movwf	((___flmul@a))&0ffh
	movlw	high(normalize32(0x3dcccccd))
	movwf	((___flmul@a+1))&0ffh
	movlw	low highword(normalize32(0x3dcccccd))
	movwf	((___flmul@a+2))&0ffh
	movlw	high highword(normalize32(0x3dcccccd))
	movwf	((___flmul@a+3))&0ffh
	call	___flmul	;wreg free
	movff	0+?___flmul,(FCI_FLOAT_TO_STRING@temp)
	movff	1+?___flmul,(FCI_FLOAT_TO_STRING@temp+1)
	movff	2+?___flmul,(FCI_FLOAT_TO_STRING@temp+2)
	movff	3+?___flmul,(FCI_FLOAT_TO_STRING@temp+3)
	
	
l4967:; BSR set to: 0

	incf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	
l4969:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@Precision))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@idx))&0ffh,w
	btfss	status,0
	goto	u3891
	goto	u3890

u3891:
	goto	l4965
u3890:
	line	575
	
l4971:; BSR set to: 0

	btfsc	((FCI_FLOAT_TO_STRING@Number+3))&0ffh,7
	goto	u3900
	goto	u3901

u3901:
	goto	l4979
u3900:
	line	577
	
l4973:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@Number),(___flneg@f1)
	movff	(FCI_FLOAT_TO_STRING@Number+1),(___flneg@f1+1)
	movff	(FCI_FLOAT_TO_STRING@Number+2),(___flneg@f1+2)
	movff	(FCI_FLOAT_TO_STRING@Number+3),(___flneg@f1+3)
	call	___flneg	;wreg free
	movff	0+?___flneg,(FCI_FLOAT_TO_STRING@Number)
	movff	1+?___flneg,(FCI_FLOAT_TO_STRING@Number+1)
	movff	2+?___flneg,(FCI_FLOAT_TO_STRING@Number+2)
	movff	3+?___flneg,(FCI_FLOAT_TO_STRING@Number+3)
	
	line	578
	
l4975:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@String))&0ffh,w
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(02Dh)
	movwf	indf2
	
l4977:; BSR set to: 0

	infsnz	((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	incf	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh
	line	580
	
l4979:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@Number),(___fladd@b)
	movff	(FCI_FLOAT_TO_STRING@Number+1),(___fladd@b+1)
	movff	(FCI_FLOAT_TO_STRING@Number+2),(___fladd@b+2)
	movff	(FCI_FLOAT_TO_STRING@Number+3),(___fladd@b+3)
	movff	(FCI_FLOAT_TO_STRING@temp),(___fladd@a)
	movff	(FCI_FLOAT_TO_STRING@temp+1),(___fladd@a+1)
	movff	(FCI_FLOAT_TO_STRING@temp+2),(___fladd@a+2)
	movff	(FCI_FLOAT_TO_STRING@temp+3),(___fladd@a+3)
	call	___fladd	;wreg free
	movff	0+?___fladd,(FCI_FLOAT_TO_STRING@Number)
	movff	1+?___fladd,(FCI_FLOAT_TO_STRING@Number+1)
	movff	2+?___fladd,(FCI_FLOAT_TO_STRING@Number+2)
	movff	3+?___fladd,(FCI_FLOAT_TO_STRING@Number+3)
	
	line	581
	
l4981:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@Number),(floor@x)
	movff	(FCI_FLOAT_TO_STRING@Number+1),(floor@x+1)
	movff	(FCI_FLOAT_TO_STRING@Number+2),(floor@x+2)
	movff	(FCI_FLOAT_TO_STRING@Number+3),(floor@x+3)
	call	_floor	;wreg free
	movff	0+?_floor,(FCI_FLOAT_TO_STRING@temp)
	movff	1+?_floor,(FCI_FLOAT_TO_STRING@temp+1)
	movff	2+?_floor,(FCI_FLOAT_TO_STRING@temp+2)
	movff	3+?_floor,(FCI_FLOAT_TO_STRING@temp+3)
	
	line	582
	
l4983:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@temp),(___fltol@f1)
	movff	(FCI_FLOAT_TO_STRING@temp+1),(___fltol@f1+1)
	movff	(FCI_FLOAT_TO_STRING@temp+2),(___fltol@f1+2)
	movff	(FCI_FLOAT_TO_STRING@temp+3),(___fltol@f1+3)
	call	___fltol	;wreg free
	movff	0+?___fltol,(FCI_FLOAT_TO_STRING@whole)
	movff	1+?___fltol,(FCI_FLOAT_TO_STRING@whole+1)
	movff	2+?___fltol,(FCI_FLOAT_TO_STRING@whole+2)
	movff	3+?___fltol,(FCI_FLOAT_TO_STRING@whole+3)
	
	line	583
	
l4985:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@Number),(___flsub@b)
	movff	(FCI_FLOAT_TO_STRING@Number+1),(___flsub@b+1)
	movff	(FCI_FLOAT_TO_STRING@Number+2),(___flsub@b+2)
	movff	(FCI_FLOAT_TO_STRING@Number+3),(___flsub@b+3)
	movff	(FCI_FLOAT_TO_STRING@temp),(___flsub@a)
	movff	(FCI_FLOAT_TO_STRING@temp+1),(___flsub@a+1)
	movff	(FCI_FLOAT_TO_STRING@temp+2),(___flsub@a+2)
	movff	(FCI_FLOAT_TO_STRING@temp+3),(___flsub@a+3)
	call	___flsub	;wreg free
	movff	0+?___flsub,(FCI_FLOAT_TO_STRING@real)
	movff	1+?___flsub,(FCI_FLOAT_TO_STRING@real+1)
	movff	2+?___flsub,(FCI_FLOAT_TO_STRING@real+2)
	movff	3+?___flsub,(FCI_FLOAT_TO_STRING@real+3)
	
	line	586
	
l4987:; BSR set to: 0

	movlw	high(0)
	movwf	((FCI_FLOAT_TO_STRING@temp_idx+1))&0ffh
	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@temp_idx))&0ffh
	line	587
	
l4989:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@whole))&0ffh,w
iorwf	((FCI_FLOAT_TO_STRING@whole+1))&0ffh,w
iorwf	((FCI_FLOAT_TO_STRING@whole+2))&0ffh,w
iorwf	((FCI_FLOAT_TO_STRING@whole+3))&0ffh,w
	btfss	status,2
	goto	u3911
	goto	u3910

u3911:
	goto	l369
u3910:
	line	588
	
l4991:; BSR set to: 0

	movlw	low(030h)
	movwf	((FCI_FLOAT_TO_STRING@temp_string))&0ffh
	
l4993:; BSR set to: 0

	infsnz	((FCI_FLOAT_TO_STRING@temp_idx))&0ffh
	incf	((FCI_FLOAT_TO_STRING@temp_idx+1))&0ffh
	line	589
	goto	l5011
	
l369:; BSR set to: 0

	line	590
	movff	(FCI_FLOAT_TO_STRING@whole),(FCI_FLOAT_TO_STRING@temp_whole)
	movff	(FCI_FLOAT_TO_STRING@whole+1),(FCI_FLOAT_TO_STRING@temp_whole+1)
	movff	(FCI_FLOAT_TO_STRING@whole+2),(FCI_FLOAT_TO_STRING@temp_whole+2)
	movff	(FCI_FLOAT_TO_STRING@whole+3),(FCI_FLOAT_TO_STRING@temp_whole+3)
	line	592
	
l4995:; BSR set to: 0

	movlw	high(0)
	movwf	((FCI_FLOAT_TO_STRING@rev_idx+1))&0ffh
	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh
	line	594
	goto	l5003
	line	595
	
l4997:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@rev_digits)
	movwf	fsr2l
	clrf	fsr2h
	movff	(FCI_FLOAT_TO_STRING@temp_whole),(___almod@dividend)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+1),(___almod@dividend+1)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+2),(___almod@dividend+2)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+3),(___almod@dividend+3)
	movlw	low(0Ah)
	movwf	((___almod@divisor))&0ffh
	movlw	high(0Ah)
	movwf	((___almod@divisor+1))&0ffh
	movlw	low highword(0Ah)
	movwf	((___almod@divisor+2))&0ffh
	movlw	high highword(0Ah)
	movwf	((___almod@divisor+3))&0ffh
	call	___almod	;wreg free
	movf	(0+?___almod)&0ffh,w
	addlw	low(030h)
	movwf	indf2,c

	
l4999:; BSR set to: 0

	infsnz	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh
	incf	((FCI_FLOAT_TO_STRING@rev_idx+1))&0ffh
	line	596
	
l5001:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@temp_whole),(___aldiv@dividend)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+1),(___aldiv@dividend+1)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+2),(___aldiv@dividend+2)
	movff	(FCI_FLOAT_TO_STRING@temp_whole+3),(___aldiv@dividend+3)
	movlw	low(0Ah)
	movwf	((___aldiv@divisor))&0ffh
	movlw	high(0Ah)
	movwf	((___aldiv@divisor+1))&0ffh
	movlw	low highword(0Ah)
	movwf	((___aldiv@divisor+2))&0ffh
	movlw	high highword(0Ah)
	movwf	((___aldiv@divisor+3))&0ffh
	call	___aldiv	;wreg free
	movff	0+?___aldiv,(FCI_FLOAT_TO_STRING@temp_whole)
	movff	1+?___aldiv,(FCI_FLOAT_TO_STRING@temp_whole+1)
	movff	2+?___aldiv,(FCI_FLOAT_TO_STRING@temp_whole+2)
	movff	3+?___aldiv,(FCI_FLOAT_TO_STRING@temp_whole+3)
	
	line	594
	
l5003:; BSR set to: 0

	btfsc	((FCI_FLOAT_TO_STRING@temp_whole+3))&0ffh,7
	goto	u3920
	movf	((FCI_FLOAT_TO_STRING@temp_whole+3))&0ffh,w
	iorwf	((FCI_FLOAT_TO_STRING@temp_whole+2))&0ffh,w
	iorwf	((FCI_FLOAT_TO_STRING@temp_whole+1))&0ffh,w
	bnz	u3921
	decf	((FCI_FLOAT_TO_STRING@temp_whole))&0ffh,w
	btfsc	status,0
	goto	u3921
	goto	u3920

u3921:
	goto	l4997
u3920:
	goto	l5009
	line	601
	
l5005:; BSR set to: 0

	decf	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh
	btfss	status,0
	decf	((FCI_FLOAT_TO_STRING@rev_idx+1))&0ffh
	movf	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@rev_digits)
	movwf	fsr2l
	clrf	fsr2h
	movf	((FCI_FLOAT_TO_STRING@temp_idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@temp_string)
	movwf	fsr1l
	clrf	fsr1h
	movff	indf2,indf1
	
l5007:; BSR set to: 0

	infsnz	((FCI_FLOAT_TO_STRING@temp_idx))&0ffh
	incf	((FCI_FLOAT_TO_STRING@temp_idx+1))&0ffh
	line	600
	
l5009:; BSR set to: 0

	btfsc	((FCI_FLOAT_TO_STRING@rev_idx+1))&0ffh,7
	goto	u3930
	movf	((FCI_FLOAT_TO_STRING@rev_idx+1))&0ffh,w
	bnz	u3931
	decf	((FCI_FLOAT_TO_STRING@rev_idx))&0ffh,w
	btfsc	status,0
	goto	u3931
	goto	u3930

u3931:
	goto	l5005
u3930:
	line	606
	
l5011:; BSR set to: 0

	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	goto	l5021
	line	607
	
l5013:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@MSZ_String))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movf	((FCI_FLOAT_TO_STRING@MSZ_String+1))&0ffh,w
	subwfb	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	btfsc	status,0
	goto	u3941
	goto	u3940

u3941:
	goto	l5019
u3940:
	line	608
	
l5015:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@temp_string)
	movwf	fsr2l
	clrf	fsr2h
	movf	((FCI_FLOAT_TO_STRING@String))&0ffh,w
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	fsr1l
	clrf	fsr1h
	movff	indf2,indf1
	
l5017:; BSR set to: 0

	infsnz	((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	incf	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh
	line	606
	
l5019:; BSR set to: 0

	incf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	
l5021:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@idx))&0ffh,w
	addlw	low(FCI_FLOAT_TO_STRING@temp_string)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	btfss	status,2
	goto	u3951
	goto	u3950
u3951:
	goto	l5013
u3950:
	line	612
	
l5023:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@Precision))&0ffh,w
	btfsc	status,2
	goto	u3961
	goto	u3960
u3961:
	goto	l5053
u3960:
	line	614
	
l5025:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@MSZ_String))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movf	((FCI_FLOAT_TO_STRING@MSZ_String+1))&0ffh,w
	subwfb	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	btfsc	status,0
	goto	u3971
	goto	u3970

u3971:
	goto	l5031
u3970:
	line	616
	
l5027:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@String))&0ffh,w
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(02Eh)
	movwf	indf2
	line	617
	
l5029:; BSR set to: 0

	movlw	low(01h)
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	movlw	high(01h)
	addwfc	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	movwf	1+((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	line	620
	
l5031:; BSR set to: 0

	movlw	low(0)
	movwf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	goto	l5051
	line	622
	
l5033:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@MSZ_String))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movf	((FCI_FLOAT_TO_STRING@MSZ_String+1))&0ffh,w
	subwfb	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	btfss	status,0
	goto	u3981
	goto	u3980

u3981:
	goto	l5037
u3980:
	goto	l5053
	line	625
	
l5037:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@real),(___flmul@b)
	movff	(FCI_FLOAT_TO_STRING@real+1),(___flmul@b+1)
	movff	(FCI_FLOAT_TO_STRING@real+2),(___flmul@b+2)
	movff	(FCI_FLOAT_TO_STRING@real+3),(___flmul@b+3)
	movlw	low(normalize32(0x41200000))
	movwf	((___flmul@a))&0ffh
	movlw	high(normalize32(0x41200000))
	movwf	((___flmul@a+1))&0ffh
	movlw	low highword(normalize32(0x41200000))
	movwf	((___flmul@a+2))&0ffh
	movlw	high highword(normalize32(0x41200000))
	movwf	((___flmul@a+3))&0ffh
	call	___flmul	;wreg free
	movff	0+?___flmul,(FCI_FLOAT_TO_STRING@real)
	movff	1+?___flmul,(FCI_FLOAT_TO_STRING@real+1)
	movff	2+?___flmul,(FCI_FLOAT_TO_STRING@real+2)
	movff	3+?___flmul,(FCI_FLOAT_TO_STRING@real+3)
	
	line	626
	
l5039:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@real),(___fltol@f1)
	movff	(FCI_FLOAT_TO_STRING@real+1),(___fltol@f1+1)
	movff	(FCI_FLOAT_TO_STRING@real+2),(___fltol@f1+2)
	movff	(FCI_FLOAT_TO_STRING@real+3),(___fltol@f1+3)
	call	___fltol	;wreg free
	movff	0+?___fltol,(FCI_FLOAT_TO_STRING@whole)
	movff	1+?___fltol,(FCI_FLOAT_TO_STRING@whole+1)
	movff	2+?___fltol,(FCI_FLOAT_TO_STRING@whole+2)
	movff	3+?___fltol,(FCI_FLOAT_TO_STRING@whole+3)
	
	line	627
	
l5041:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@whole),(___xxtofl@val)
	movff	(FCI_FLOAT_TO_STRING@whole+1),(___xxtofl@val+1)
	movff	(FCI_FLOAT_TO_STRING@whole+2),(___xxtofl@val+2)
	movff	(FCI_FLOAT_TO_STRING@whole+3),(___xxtofl@val+3)
	movlw	(01h)&0ffh
	
	call	___xxtofl
	movff	0+?___xxtofl,(FCI_FLOAT_TO_STRING@temp)
	movff	1+?___xxtofl,(FCI_FLOAT_TO_STRING@temp+1)
	movff	2+?___xxtofl,(FCI_FLOAT_TO_STRING@temp+2)
	movff	3+?___xxtofl,(FCI_FLOAT_TO_STRING@temp+3)
	
	line	628
	
l5043:; BSR set to: 0

	movff	(FCI_FLOAT_TO_STRING@real),(___flsub@b)
	movff	(FCI_FLOAT_TO_STRING@real+1),(___flsub@b+1)
	movff	(FCI_FLOAT_TO_STRING@real+2),(___flsub@b+2)
	movff	(FCI_FLOAT_TO_STRING@real+3),(___flsub@b+3)
	movff	(FCI_FLOAT_TO_STRING@temp),(___flsub@a)
	movff	(FCI_FLOAT_TO_STRING@temp+1),(___flsub@a+1)
	movff	(FCI_FLOAT_TO_STRING@temp+2),(___flsub@a+2)
	movff	(FCI_FLOAT_TO_STRING@temp+3),(___flsub@a+3)
	call	___flsub	;wreg free
	movff	0+?___flsub,(FCI_FLOAT_TO_STRING@real)
	movff	1+?___flsub,(FCI_FLOAT_TO_STRING@real+1)
	movff	2+?___flsub,(FCI_FLOAT_TO_STRING@real+2)
	movff	3+?___flsub,(FCI_FLOAT_TO_STRING@real+3)
	
	line	630
	
l5045:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@String))&0ffh,w
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movf	((FCI_FLOAT_TO_STRING@whole))&0ffh,w
	addlw	low(030h)
	movwf	indf2,c

	line	631
	
l5047:; BSR set to: 0

	movlw	low(01h)
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	movlw	high(01h)
	addwfc	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	movwf	1+((FCI_FLOAT_TO_STRING@stringidx))&0ffh
	line	620
	
l5049:; BSR set to: 0

	incf	((FCI_FLOAT_TO_STRING@idx))&0ffh
	
l5051:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@Precision))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@idx))&0ffh,w
	btfss	status,0
	goto	u3991
	goto	u3990

u3991:
	goto	l5033
u3990:
	line	636
	
l5053:; BSR set to: 0

		movf	((FCI_FLOAT_TO_STRING@MSZ_String))&0ffh,w
	subwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movf	((FCI_FLOAT_TO_STRING@MSZ_String+1))&0ffh,w
	subwfb	((FCI_FLOAT_TO_STRING@stringidx+1))&0ffh,w
	btfsc	status,0
	goto	u4001
	goto	u4000

u4001:
	goto	l388
u4000:
	line	637
	
l5055:; BSR set to: 0

	movf	((FCI_FLOAT_TO_STRING@String))&0ffh,w
	addwf	((FCI_FLOAT_TO_STRING@stringidx))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	641
	
l388:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCI_FLOAT_TO_STRING
	__end_of_FCI_FLOAT_TO_STRING:
	signat	_FCI_FLOAT_TO_STRING,16506
	global	_floor

;; *************** function _floor *****************
;; Defined at:
;;		line 13 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\floor.c"
;; Parameters:    Size  Location     Type
;;  x               4   24[BANK0 ] PTR unsigned char 
;; Auto vars:     Size  Location     Type
;;  i               4   28[BANK0 ] PTR unsigned char 
;;  expon           2   32[BANK0 ] int 
;; Return value:  Size  Location     Type
;;                  4   24[BANK0 ] int 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		___fladd
;;		___flge
;;		___fltol
;;		___xxtofl
;;		_frexp
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;; This function uses a non-reentrant model
;;
psect	text11,class=CODE,space=0,reloc=2,group=2
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\floor.c"
	line	13
global __ptext11
__ptext11:
psect	text11
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\floor.c"
	line	13
	global	__size_of_floor
	__size_of_floor	equ	__end_of_floor-_floor
	
_floor:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	18
	
l4693:; BSR set to: 0

	movff	(floor@x),(frexp@value)
	movff	(floor@x+1),(frexp@value+1)
	movff	(floor@x+2),(frexp@value+2)
	movff	(floor@x+3),(frexp@value+3)
		movlw	low(floor@expon)
	movwf	((frexp@eptr))&0ffh

	call	_frexp	;wreg free
	line	19
	
l4695:; BSR set to: 0

	btfsc	((floor@expon+1))&0ffh,7
	goto	u3510
	goto	u3511

u3511:
	goto	l4707
u3510:
	line	20
	
l4697:; BSR set to: 0

	btfsc	((floor@x+3))&0ffh,7
	goto	u3520
	goto	u3521

u3521:
	goto	l4703
u3520:
	line	21
	
l4699:; BSR set to: 0

	movlw	low(normalize32(0xbf800000))
	movwf	((?_floor))&0ffh
	movlw	high(normalize32(0xbf800000))
	movwf	((?_floor+1))&0ffh
	movlw	low highword(normalize32(0xbf800000))
	movwf	((?_floor+2))&0ffh
	movlw	high highword(normalize32(0xbf800000))
	movwf	((?_floor+3))&0ffh
	goto	l1997
	line	22
	
l4703:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((?_floor))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((?_floor+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((?_floor+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((?_floor+3))&0ffh
	goto	l1997
	line	24
	
l4707:; BSR set to: 0

		movf	((floor@expon+1))&0ffh,w
	bnz	u3530
	movlw	29
	subwf	 ((floor@expon))&0ffh,w
	btfss	status,0
	goto	u3531
	goto	u3530

u3531:
	goto	l4711
u3530:
	line	25
	
l4709:; BSR set to: 0

	movff	(floor@x),(?_floor)
	movff	(floor@x+1),(?_floor+1)
	movff	(floor@x+2),(?_floor+2)
	movff	(floor@x+3),(?_floor+3)
	goto	l1997
	line	26
	
l4711:; BSR set to: 0

	movff	(floor@x),(___fltol@f1)
	movff	(floor@x+1),(___fltol@f1+1)
	movff	(floor@x+2),(___fltol@f1+2)
	movff	(floor@x+3),(___fltol@f1+3)
	call	___fltol	;wreg free
	movff	0+?___fltol,(___xxtofl@val)
	movff	1+?___fltol,(___xxtofl@val+1)
	movff	2+?___fltol,(___xxtofl@val+2)
	movff	3+?___fltol,(___xxtofl@val+3)
	
	movlw	(01h)&0ffh
	
	call	___xxtofl
	movff	0+?___xxtofl,(floor@i)
	movff	1+?___xxtofl,(floor@i+1)
	movff	2+?___xxtofl,(floor@i+2)
	movff	3+?___xxtofl,(floor@i+3)
	
	line	27
	movff	(floor@x),(___flge@ff1)
	movff	(floor@x+1),(___flge@ff1+1)
	movff	(floor@x+2),(___flge@ff1+2)
	movff	(floor@x+3),(___flge@ff1+3)
	movff	(floor@i),(___flge@ff2)
	movff	(floor@i+1),(___flge@ff2+1)
	movff	(floor@i+2),(___flge@ff2+2)
	movff	(floor@i+3),(___flge@ff2+3)
	call	___flge	;wreg free
	btfsc	status,0
	goto	u3541
	goto	u3540
u3541:
	goto	l1999
u3540:
	line	28
	
l4713:; BSR set to: 0

	movff	(floor@i),(___fladd@b)
	movff	(floor@i+1),(___fladd@b+1)
	movff	(floor@i+2),(___fladd@b+2)
	movff	(floor@i+3),(___fladd@b+3)
	movlw	low(normalize32(0xbf800000))
	movwf	((___fladd@a))&0ffh
	movlw	high(normalize32(0xbf800000))
	movwf	((___fladd@a+1))&0ffh
	movlw	low highword(normalize32(0xbf800000))
	movwf	((___fladd@a+2))&0ffh
	movlw	high highword(normalize32(0xbf800000))
	movwf	((___fladd@a+3))&0ffh
	call	___fladd	;wreg free
	movff	0+?___fladd,(?_floor)
	movff	1+?___fladd,(?_floor+1)
	movff	2+?___fladd,(?_floor+2)
	movff	3+?___fladd,(?_floor+3)
	
	goto	l1997
	
l1999:; BSR set to: 0

	line	29
	movff	(floor@i),(?_floor)
	movff	(floor@i+1),(?_floor+1)
	movff	(floor@i+2),(?_floor+2)
	movff	(floor@i+3),(?_floor+3)
	line	30
	
l1997:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_floor
	__end_of_floor:
	signat	_floor,4220
	global	_frexp

;; *************** function _frexp *****************
;; Defined at:
;;		line 254 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\frexp.c"
;; Parameters:    Size  Location     Type
;;  value           4   12[BANK0 ] int 
;;  eptr            1   16[BANK0 ] PTR int 
;;		 -> floor@expon(2), 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  4   12[BANK0 ] PTR int 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       5       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       7       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		___fleq
;; This function is called by:
;;		_floor
;; This function uses a non-reentrant model
;;
psect	text12,class=CODE,space=0,reloc=2,group=2
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\frexp.c"
	line	254
global __ptext12
__ptext12:
psect	text12
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\frexp.c"
	line	254
	global	__size_of_frexp
	__size_of_frexp	equ	__end_of_frexp-_frexp
	
_frexp:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	256
	
l4623:; BSR set to: 0

	movff	(frexp@value),(___fleq@ff1)
	movff	(frexp@value+1),(___fleq@ff1+1)
	movff	(frexp@value+2),(___fleq@ff1+2)
	movff	(frexp@value+3),(___fleq@ff1+3)
	movlw	low(normalize32(0x0))
	movwf	((___fleq@ff2))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fleq@ff2+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fleq@ff2+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fleq@ff2+3))&0ffh
	call	___fleq	;wreg free
	btfss	status,0
	goto	u3401
	goto	u3400
u3401:
	goto	l4629
u3400:
	line	257
	
l4625:; BSR set to: 0

	movf	((frexp@eptr))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	postinc2,c
	movlw	high(0)
	movwf	postdec2,c
	goto	l2005
	line	261
	
l4629:; BSR set to: 0

	movf	(0+(frexp@value+03h))&0ffh,w
	andlw	(1<<7)-1
	movwf	(??_frexp+0+0)&0ffh
	clrf	(??_frexp+0+0+1)&0ffh

	bcf	status,0
	rlcf	(??_frexp+0+0)&0ffh,f
	rlcf	(??_frexp+0+1)&0ffh,f
	movf	((frexp@eptr))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movff	??_frexp+0+0,postinc2
	movff	??_frexp+0+1,postdec2

	line	262
	movf	((frexp@eptr))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	btfsc	(0+(frexp@value+02h))&0ffh,7
	goto	u3411
	goto	u3410
u3411:
	clrf	(??_frexp+0+0)&0ffh
	incf	(??_frexp+0+0)&0ffh
	goto	u3418
u3410:
	movlb	0	; () banked
	clrf	(??_frexp+0+0)&0ffh
u3418:
	movf	(??_frexp+0+0)&0ffh,w
	iorwf	postinc2
	movlw	0
	iorwf	postdec2
	line	263
	
l4631:; BSR set to: 0

	movf	((frexp@eptr))&0ffh,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(-126)
	addwf	postinc2
	movlw	high(-126)
	addwfc	postdec2
	line	268
	
l4633:; BSR set to: 0

	movf	(0+(frexp@value+03h))&0ffh,w
	andlw	not (((1<<7)-1)<<0)
	iorlw	(03Fh & ((1<<7)-1))<<0
	movwf	(0+(frexp@value+03h))&0ffh
	line	269
	
l4635:; BSR set to: 0

	bcf	(0+(frexp@value+02h))&0ffh,7
	line	274
	
l2005:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_frexp
	__end_of_frexp:
	signat	_frexp,8316
	global	___fleq

;; *************** function ___fleq *****************
;; Defined at:
;;		line 4 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fleq.c"
;; Parameters:    Size  Location     Type
;;  ff1             4    0[BANK0 ] PTR int 
;;  ff2             4    4[BANK0 ] PTR int 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      12       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_frexp
;; This function uses a non-reentrant model
;;
psect	text13,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fleq.c"
	line	4
global __ptext13
__ptext13:
psect	text13
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fleq.c"
	line	4
	global	__size_of___fleq
	__size_of___fleq	equ	__end_of___fleq-___fleq
	
___fleq:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	7
	
l4065:; BSR set to: 0

	movlw	0
	andwf	((___fleq@ff1))&0ffh,w
	movwf	(??___fleq+0+0)&0ffh
	movlw	0
	andwf	((___fleq@ff1+1))&0ffh,w
	movwf	1+(??___fleq+0+0)&0ffh
	
	movlw	080h
	andwf	((___fleq@ff1+2))&0ffh,w
	movwf	2+(??___fleq+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___fleq@ff1+3))&0ffh,w
	movwf	3+(??___fleq+0+0)&0ffh
	movf	(??___fleq+0+0)&0ffh,w
iorwf	(??___fleq+0+1)&0ffh,w
iorwf	(??___fleq+0+2)&0ffh,w
iorwf	(??___fleq+0+3)&0ffh,w
	btfss	status,2
	goto	u2581
	goto	u2580

u2581:
	goto	l4069
u2580:
	line	8
	
l4067:; BSR set to: 0

	movlw	low(0)
	movwf	((___fleq@ff1))&0ffh
	movlw	high(0)
	movwf	((___fleq@ff1+1))&0ffh
	movlw	low highword(0)
	movwf	((___fleq@ff1+2))&0ffh
	movlw	high highword(0)
	movwf	((___fleq@ff1+3))&0ffh
	line	9
	
l4069:; BSR set to: 0

	movlw	0
	andwf	((___fleq@ff2))&0ffh,w
	movwf	(??___fleq+0+0)&0ffh
	movlw	0
	andwf	((___fleq@ff2+1))&0ffh,w
	movwf	1+(??___fleq+0+0)&0ffh
	
	movlw	080h
	andwf	((___fleq@ff2+2))&0ffh,w
	movwf	2+(??___fleq+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___fleq@ff2+3))&0ffh,w
	movwf	3+(??___fleq+0+0)&0ffh
	movf	(??___fleq+0+0)&0ffh,w
iorwf	(??___fleq+0+1)&0ffh,w
iorwf	(??___fleq+0+2)&0ffh,w
iorwf	(??___fleq+0+3)&0ffh,w
	btfss	status,2
	goto	u2591
	goto	u2590

u2591:
	goto	l4073
u2590:
	line	10
	
l4071:; BSR set to: 0

	movlw	low(0)
	movwf	((___fleq@ff2))&0ffh
	movlw	high(0)
	movwf	((___fleq@ff2+1))&0ffh
	movlw	low highword(0)
	movwf	((___fleq@ff2+2))&0ffh
	movlw	high highword(0)
	movwf	((___fleq@ff2+3))&0ffh
	line	11
	
l4073:; BSR set to: 0

	movf	((___fleq@ff2))&0ffh,w
xorwf	((___fleq@ff1))&0ffh,w
	bnz	u2600
movf	((___fleq@ff2+1))&0ffh,w
xorwf	((___fleq@ff1+1))&0ffh,w
	bnz	u2600
movf	((___fleq@ff2+2))&0ffh,w
xorwf	((___fleq@ff1+2))&0ffh,w
	bnz	u2600
movf	((___fleq@ff2+3))&0ffh,w
xorwf	((___fleq@ff1+3))&0ffh,w
	btfsc	status,2
	goto	u2601
	goto	u2600

u2601:
	goto	l4077
u2600:
	
l4075:; BSR set to: 0

	bcf	status,0
	goto	l1586
	
l4077:; BSR set to: 0

	bsf	status,0
	line	12
	
l1586:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fleq
	__end_of___fleq:
	signat	___fleq,8312
	global	___xxtofl

;; *************** function ___xxtofl *****************
;; Defined at:
;;		line 10 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
;; Parameters:    Size  Location     Type
;;  sign            1    wreg     unsigned char 
;;  val             4   10[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;  sign            1   18[BANK0 ] unsigned char 
;;  arg             4   20[BANK0 ] unsigned long 
;;  exp             1   19[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4   10[BANK0 ] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      14       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;;		_floor
;; This function uses a non-reentrant model
;;
psect	text14,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
global __ptext14
__ptext14:
psect	text14
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
	global	__size_of___xxtofl
	__size_of___xxtofl	equ	__end_of___xxtofl-___xxtofl
	
___xxtofl:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	movwf	((___xxtofl@sign))&0ffh
	line	15
	
l4577:
	movlb	0	; () banked
	movf	((___xxtofl@sign))&0ffh,w
	btfsc	status,2
	goto	u3301
	goto	u3300
u3301:
	goto	l1974
u3300:
	
l4579:; BSR set to: 0

	btfsc	((___xxtofl@val+3))&0ffh,7
	goto	u3310
	goto	u3311

u3311:
	goto	l1974
u3310:
	line	16
	
l4581:; BSR set to: 0

	movff	(___xxtofl@val),??___xxtofl+0+0
	movff	(___xxtofl@val+1),??___xxtofl+0+0+1
	movff	(___xxtofl@val+2),??___xxtofl+0+0+2
	movff	(___xxtofl@val+3),??___xxtofl+0+0+3
	comf	(??___xxtofl+0+0)&0ffh
	comf	(??___xxtofl+0+1)&0ffh
	comf	(??___xxtofl+0+2)&0ffh
	comf	(??___xxtofl+0+3)&0ffh
	incf	(??___xxtofl+0+0)&0ffh
	movlw	0
	addwfc	(??___xxtofl+0+1)&0ffh
	addwfc	(??___xxtofl+0+2)&0ffh
	addwfc	(??___xxtofl+0+3)&0ffh
	movff	??___xxtofl+0+0,(___xxtofl@arg)
	movff	??___xxtofl+0+1,(___xxtofl@arg+1)
	movff	??___xxtofl+0+2,(___xxtofl@arg+2)
	movff	??___xxtofl+0+3,(___xxtofl@arg+3)
	line	17
	goto	l4583
	line	18
	
l1974:; BSR set to: 0

	line	19
	movff	(___xxtofl@val),(___xxtofl@arg)
	movff	(___xxtofl@val+1),(___xxtofl@arg+1)
	movff	(___xxtofl@val+2),(___xxtofl@arg+2)
	movff	(___xxtofl@val+3),(___xxtofl@arg+3)
	line	21
	
l4583:; BSR set to: 0

	movf	((___xxtofl@val))&0ffh,w
iorwf	((___xxtofl@val+1))&0ffh,w
iorwf	((___xxtofl@val+2))&0ffh,w
iorwf	((___xxtofl@val+3))&0ffh,w
	btfss	status,2
	goto	u3321
	goto	u3320

u3321:
	goto	l4589
u3320:
	line	22
	
l4585:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((?___xxtofl))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((?___xxtofl+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((?___xxtofl+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((?___xxtofl+3))&0ffh
	goto	l1977
	line	23
	
l4589:; BSR set to: 0

	movlw	low(096h)
	movwf	((___xxtofl@exp))&0ffh
	line	24
	goto	l4593
	line	25
	
l4591:; BSR set to: 0

	incf	((___xxtofl@exp))&0ffh
	line	26
	bcf	status,0
	rrcf	((___xxtofl@arg+3))&0ffh
	rrcf	((___xxtofl@arg+2))&0ffh
	rrcf	((___xxtofl@arg+1))&0ffh
	rrcf	((___xxtofl@arg))&0ffh
	line	24
	
l4593:; BSR set to: 0

	movlw	0
	andwf	((___xxtofl@arg))&0ffh,w
	movwf	(??___xxtofl+0+0)&0ffh
	movlw	0
	andwf	((___xxtofl@arg+1))&0ffh,w
	movwf	1+(??___xxtofl+0+0)&0ffh
	
	movlw	0
	andwf	((___xxtofl@arg+2))&0ffh,w
	movwf	2+(??___xxtofl+0+0)&0ffh
	
	movlw	0FEh
	andwf	((___xxtofl@arg+3))&0ffh,w
	movwf	3+(??___xxtofl+0+0)&0ffh
	movf	(??___xxtofl+0+0)&0ffh,w
iorwf	(??___xxtofl+0+1)&0ffh,w
iorwf	(??___xxtofl+0+2)&0ffh,w
iorwf	(??___xxtofl+0+3)&0ffh,w
	btfss	status,2
	goto	u3331
	goto	u3330

u3331:
	goto	l4591
u3330:
	goto	l1981
	line	29
	
l4595:; BSR set to: 0

	incf	((___xxtofl@exp))&0ffh
	line	30
	
l4597:; BSR set to: 0

	movlw	low(01h)
	addwf	((___xxtofl@arg))&0ffh
	movlw	0
	addwfc	((___xxtofl@arg+1))&0ffh
	addwfc	((___xxtofl@arg+2))&0ffh
	addwfc	((___xxtofl@arg+3))&0ffh
	line	31
	
l4599:; BSR set to: 0

	bcf	status,0
	rrcf	((___xxtofl@arg+3))&0ffh
	rrcf	((___xxtofl@arg+2))&0ffh
	rrcf	((___xxtofl@arg+1))&0ffh
	rrcf	((___xxtofl@arg))&0ffh
	line	32
	
l1981:; BSR set to: 0

	line	28
	movlw	0
	andwf	((___xxtofl@arg))&0ffh,w
	movwf	(??___xxtofl+0+0)&0ffh
	movlw	0
	andwf	((___xxtofl@arg+1))&0ffh,w
	movwf	1+(??___xxtofl+0+0)&0ffh
	
	movlw	0
	andwf	((___xxtofl@arg+2))&0ffh,w
	movwf	2+(??___xxtofl+0+0)&0ffh
	
	movlw	0FFh
	andwf	((___xxtofl@arg+3))&0ffh,w
	movwf	3+(??___xxtofl+0+0)&0ffh
	movf	(??___xxtofl+0+0)&0ffh,w
iorwf	(??___xxtofl+0+1)&0ffh,w
iorwf	(??___xxtofl+0+2)&0ffh,w
iorwf	(??___xxtofl+0+3)&0ffh,w
	btfss	status,2
	goto	u3341
	goto	u3340

u3341:
	goto	l4595
u3340:
	goto	l4603
	line	34
	
l4601:; BSR set to: 0

	decf	((___xxtofl@exp))&0ffh
	line	35
	bcf	status,0
	rlcf	((___xxtofl@arg))&0ffh
	rlcf	((___xxtofl@arg+1))&0ffh
	rlcf	((___xxtofl@arg+2))&0ffh
	rlcf	((___xxtofl@arg+3))&0ffh
	line	33
	
l4603:; BSR set to: 0

	
	btfsc	((___xxtofl@arg+2))&0ffh,(23)&7
	goto	u3351
	goto	u3350
u3351:
	goto	l1988
u3350:
	
l4605:; BSR set to: 0

		movlw	02h-0
	cpfslt	((___xxtofl@exp))&0ffh
	goto	u3361
	goto	u3360

u3361:
	goto	l4601
u3360:
	
l1988:; BSR set to: 0

	line	37
	
	btfsc	((___xxtofl@exp))&0ffh,(0)&7
	goto	u3371
	goto	u3370
u3371:
	goto	l4609
u3370:
	line	38
	
l4607:; BSR set to: 0

	bcf	(0+(23/8)+(___xxtofl@arg))&0ffh,(23)&7
	line	39
	
l4609:; BSR set to: 0

	bcf status,0
	rrcf	((___xxtofl@exp))&0ffh

	line	40
	
l4611:; BSR set to: 0

	movff	(___xxtofl@exp),??___xxtofl+0+0
	clrf	(??___xxtofl+0+0+1)&0ffh
	clrf	(??___xxtofl+0+0+2)&0ffh
	clrf	(??___xxtofl+0+0+3)&0ffh
	movff	??___xxtofl+0+0,??___xxtofl+0+3
	clrf	(??___xxtofl+0+2)&0ffh
	clrf	(??___xxtofl+0+1)&0ffh
	clrf	(??___xxtofl+0+0)&0ffh
	movf	(??___xxtofl+0+0)&0ffh,w
	iorwf	((___xxtofl@arg))&0ffh
	movf	(??___xxtofl+0+1)&0ffh,w
	iorwf	((___xxtofl@arg+1))&0ffh
	movf	(??___xxtofl+0+2)&0ffh,w
	iorwf	((___xxtofl@arg+2))&0ffh
	movf	(??___xxtofl+0+3)&0ffh,w
	iorwf	((___xxtofl@arg+3))&0ffh

	line	41
	
l4613:; BSR set to: 0

	movf	((___xxtofl@sign))&0ffh,w
	btfsc	status,2
	goto	u3381
	goto	u3380
u3381:
	goto	l4619
u3380:
	
l4615:; BSR set to: 0

	btfsc	((___xxtofl@val+3))&0ffh,7
	goto	u3390
	goto	u3391

u3391:
	goto	l4619
u3390:
	line	42
	
l4617:; BSR set to: 0

	bsf	(0+(31/8)+(___xxtofl@arg))&0ffh,(31)&7
	line	43
	
l4619:; BSR set to: 0

	movff	(___xxtofl@arg),(?___xxtofl)
	movff	(___xxtofl@arg+1),(?___xxtofl+1)
	movff	(___xxtofl@arg+2),(?___xxtofl+2)
	movff	(___xxtofl@arg+3),(?___xxtofl+3)
	line	44
	
l1977:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___xxtofl
	__end_of___xxtofl:
	signat	___xxtofl,8316
	global	___fltol

;; *************** function ___fltol *****************
;; Defined at:
;;		line 43 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
;; Parameters:    Size  Location     Type
;;  f1              4    0[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  exp1            1    9[BANK0 ] unsigned char 
;;  sign1           1    8[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;;		_floor
;; This function uses a non-reentrant model
;;
psect	text15,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
	line	43
global __ptext15
__ptext15:
psect	text15
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
	line	43
	global	__size_of___fltol
	__size_of___fltol	equ	__end_of___fltol-___fltol
	
___fltol:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	47
	
l4533:; BSR set to: 0

	rlcf	((___fltol@f1+2))&0ffh,w
	rlcf	((___fltol@f1+3))&0ffh,w
	movwf	((___fltol@exp1))&0ffh
	movf	((___fltol@exp1))&0ffh,w
	btfss	status,2
	goto	u3231
	goto	u3230
u3231:
	goto	l4539
u3230:
	line	48
	
l4535:; BSR set to: 0

	movlw	low(0)
	movwf	((?___fltol))&0ffh
	movlw	high(0)
	movwf	((?___fltol+1))&0ffh
	movlw	low highword(0)
	movwf	((?___fltol+2))&0ffh
	movlw	high highword(0)
	movwf	((?___fltol+3))&0ffh
	goto	l1620
	line	49
	
l4539:; BSR set to: 0

	movff	(___fltol@f1),??___fltol+0+0
	movff	(___fltol@f1+1),??___fltol+0+0+1
	movff	(___fltol@f1+2),??___fltol+0+0+2
	movff	(___fltol@f1+3),??___fltol+0+0+3
	movlw	01Fh+1
	goto	u3240
u3245:
	bcf	status,0
	rrcf	(??___fltol+0+3)&0ffh
	rrcf	(??___fltol+0+2)&0ffh
	rrcf	(??___fltol+0+1)&0ffh
	rrcf	(??___fltol+0+0)&0ffh
u3240:
	decfsz	wreg
	goto	u3245
	movf	(??___fltol+0+0)&0ffh,w
	movwf	((___fltol@sign1))&0ffh
	line	50
	
l4541:; BSR set to: 0

	bsf	(0+(23/8)+(___fltol@f1))&0ffh,(23)&7
	line	51
	
l4543:; BSR set to: 0

	movlw	0FFh
	andwf	((___fltol@f1))&0ffh
	movlw	0FFh
	andwf	((___fltol@f1+1))&0ffh
	movlw	0FFh
	andwf	((___fltol@f1+2))&0ffh
	movlw	0
	andwf	((___fltol@f1+3))&0ffh
	line	52
	
l4545:; BSR set to: 0

	movlw	(096h)&0ffh
	subwf	((___fltol@exp1))&0ffh
	line	53
	
l4547:; BSR set to: 0

	btfsc	((___fltol@exp1))&0ffh,7
	goto	u3250
	goto	u3251

u3251:
	goto	l4559
u3250:
	line	54
	
l4549:; BSR set to: 0

		movf	((___fltol@exp1))&0ffh,w
	xorlw	80h
	addlw	-(80h^-23)
	btfsc	status,0
	goto	u3261
	goto	u3260

u3261:
	goto	l4555
u3260:
	goto	l4535
	line	57
	
l4555:; BSR set to: 0

	bcf	status,0
	rrcf	((___fltol@f1+3))&0ffh
	rrcf	((___fltol@f1+2))&0ffh
	rrcf	((___fltol@f1+1))&0ffh
	rrcf	((___fltol@f1))&0ffh
	line	58
	
l4557:; BSR set to: 0

	incfsz	((___fltol@exp1))&0ffh
	
	goto	l4555
	goto	l4569
	line	60
	
l4559:; BSR set to: 0

		movlw	020h-1
	cpfsgt	((___fltol@exp1))&0ffh
	goto	u3271
	goto	u3270

u3271:
	goto	l4567
u3270:
	goto	l4535
	line	63
	
l4565:; BSR set to: 0

	bcf	status,0
	rlcf	((___fltol@f1))&0ffh
	rlcf	((___fltol@f1+1))&0ffh
	rlcf	((___fltol@f1+2))&0ffh
	rlcf	((___fltol@f1+3))&0ffh
	line	64
	decf	((___fltol@exp1))&0ffh
	line	62
	
l4567:; BSR set to: 0

	movf	((___fltol@exp1))&0ffh,w
	btfss	status,2
	goto	u3281
	goto	u3280
u3281:
	goto	l4565
u3280:
	line	67
	
l4569:; BSR set to: 0

	movf	((___fltol@sign1))&0ffh,w
	btfsc	status,2
	goto	u3291
	goto	u3290
u3291:
	goto	l4573
u3290:
	line	68
	
l4571:; BSR set to: 0

	comf	((___fltol@f1+3))&0ffh
	comf	((___fltol@f1+2))&0ffh
	comf	((___fltol@f1+1))&0ffh
	negf	((___fltol@f1))&0ffh
	movlw	0
	addwfc	((___fltol@f1+1))&0ffh
	addwfc	((___fltol@f1+2))&0ffh
	addwfc	((___fltol@f1+3))&0ffh
	line	69
	
l4573:; BSR set to: 0

	movff	(___fltol@f1),(?___fltol)
	movff	(___fltol@f1+1),(?___fltol+1)
	movff	(___fltol@f1+2),(?___fltol+2)
	movff	(___fltol@f1+3),(?___fltol+3)
	line	70
	
l1620:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fltol
	__end_of___fltol:
	signat	___fltol,4220
	global	___flge

;; *************** function ___flge *****************
;; Defined at:
;;		line 4 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flge.c"
;; Parameters:    Size  Location     Type
;;  ff1             4    0[BANK0 ] long 
;;  ff2             4    4[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      12       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_floor
;; This function uses a non-reentrant model
;;
psect	text16,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flge.c"
	line	4
global __ptext16
__ptext16:
psect	text16
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flge.c"
	line	4
	global	__size_of___flge
	__size_of___flge	equ	__end_of___flge-___flge
	
___flge:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	7
	
l4511:; BSR set to: 0

	movlw	0
	andwf	((___flge@ff1))&0ffh,w
	movwf	(??___flge+0+0)&0ffh
	movlw	0
	andwf	((___flge@ff1+1))&0ffh,w
	movwf	1+(??___flge+0+0)&0ffh
	
	movlw	080h
	andwf	((___flge@ff1+2))&0ffh,w
	movwf	2+(??___flge+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___flge@ff1+3))&0ffh,w
	movwf	3+(??___flge+0+0)&0ffh
	movf	(??___flge+0+0)&0ffh,w
iorwf	(??___flge+0+1)&0ffh,w
iorwf	(??___flge+0+2)&0ffh,w
iorwf	(??___flge+0+3)&0ffh,w
	btfss	status,2
	goto	u3181
	goto	u3180

u3181:
	goto	l4515
u3180:
	line	8
	
l4513:; BSR set to: 0

	movlw	low(0)
	movwf	((___flge@ff1))&0ffh
	movlw	high(0)
	movwf	((___flge@ff1+1))&0ffh
	movlw	low highword(0)
	movwf	((___flge@ff1+2))&0ffh
	movlw	high highword(0)
	movwf	((___flge@ff1+3))&0ffh
	line	9
	
l4515:; BSR set to: 0

	movlw	0
	andwf	((___flge@ff2))&0ffh,w
	movwf	(??___flge+0+0)&0ffh
	movlw	0
	andwf	((___flge@ff2+1))&0ffh,w
	movwf	1+(??___flge+0+0)&0ffh
	
	movlw	080h
	andwf	((___flge@ff2+2))&0ffh,w
	movwf	2+(??___flge+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___flge@ff2+3))&0ffh,w
	movwf	3+(??___flge+0+0)&0ffh
	movf	(??___flge+0+0)&0ffh,w
iorwf	(??___flge+0+1)&0ffh,w
iorwf	(??___flge+0+2)&0ffh,w
iorwf	(??___flge+0+3)&0ffh,w
	btfss	status,2
	goto	u3191
	goto	u3190

u3191:
	goto	l4519
u3190:
	line	10
	
l4517:; BSR set to: 0

	movlw	low(0)
	movwf	((___flge@ff2))&0ffh
	movlw	high(0)
	movwf	((___flge@ff2+1))&0ffh
	movlw	low highword(0)
	movwf	((___flge@ff2+2))&0ffh
	movlw	high highword(0)
	movwf	((___flge@ff2+3))&0ffh
	line	12
	
l4519:; BSR set to: 0

	
	btfss	((___flge@ff1+3))&0ffh,(31)&7
	goto	u3201
	goto	u3200
u3201:
	goto	l4523
u3200:
	line	13
	
l4521:; BSR set to: 0

	negf	((___flge@ff1))&0ffh
	comf	((___flge@ff1+1))&0ffh
	btfsc	status,0
	incf	((___flge@ff1+1))&0ffh
	comf	((___flge@ff1+2))&0ffh
	btfsc	status,0
	incf	((___flge@ff1+2))&0ffh
	movlw	high highword(080000000h)
	subfwb	((___flge@ff1+3))&0ffh
	line	14
	
l4523:; BSR set to: 0

	
	btfss	((___flge@ff2+3))&0ffh,(31)&7
	goto	u3211
	goto	u3210
u3211:
	goto	l1592
u3210:
	line	15
	
l4525:; BSR set to: 0

	negf	((___flge@ff2))&0ffh
	comf	((___flge@ff2+1))&0ffh
	btfsc	status,0
	incf	((___flge@ff2+1))&0ffh
	comf	((___flge@ff2+2))&0ffh
	btfsc	status,0
	incf	((___flge@ff2+2))&0ffh
	movlw	high highword(080000000h)
	subfwb	((___flge@ff2+3))&0ffh
	
l1592:; BSR set to: 0

	line	16
	movlw	0
	xorwf	((___flge@ff1))&0ffh
	movlw	0
	xorwf	((___flge@ff1+1))&0ffh
	movlw	0
	xorwf	((___flge@ff1+2))&0ffh
	movlw	080h
	xorwf	((___flge@ff1+3))&0ffh
	line	17
	movlw	0
	xorwf	((___flge@ff2))&0ffh
	movlw	0
	xorwf	((___flge@ff2+1))&0ffh
	movlw	0
	xorwf	((___flge@ff2+2))&0ffh
	movlw	080h
	xorwf	((___flge@ff2+3))&0ffh
	line	18
		movf	((___flge@ff2))&0ffh,w
	subwf	((___flge@ff1))&0ffh,w
	movf	((___flge@ff2+1))&0ffh,w
	subwfb	((___flge@ff1+1))&0ffh,w
	movf	((___flge@ff2+2))&0ffh,w
	subwfb	((___flge@ff1+2))&0ffh,w
	movf	((___flge@ff2+3))&0ffh,w
	subwfb	((___flge@ff1+3))&0ffh,w
	btfsc	status,0
	goto	u3221
	goto	u3220

u3221:
	goto	l4529
u3220:
	
l4527:; BSR set to: 0

	bcf	status,0
	goto	l1593
	
l4529:; BSR set to: 0

	bsf	status,0
	line	19
	
l1593:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___flge
	__end_of___flge:
	signat	___flge,8312
	global	___flsub

;; *************** function ___flsub *****************
;; Defined at:
;;		line 245 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
;; Parameters:    Size  Location     Type
;;  b               4   16[BANK0 ] long 
;;  a               4   20[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  4   16[BANK0 ] long 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		___fladd
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;; This function uses a non-reentrant model
;;
psect	text17,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
	line	245
global __ptext17
__ptext17:
psect	text17
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
	line	245
	global	__size_of___flsub
	__size_of___flsub	equ	__end_of___flsub-___flsub
	
___flsub:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	248
	
l4937:; BSR set to: 0

	movlw	0
	xorwf	((___flsub@a))&0ffh
	movlw	0
	xorwf	((___flsub@a+1))&0ffh
	movlw	0
	xorwf	((___flsub@a+2))&0ffh
	movlw	080h
	xorwf	((___flsub@a+3))&0ffh
	line	249
	
l4939:; BSR set to: 0

	movff	(___flsub@b),(___fladd@b)
	movff	(___flsub@b+1),(___fladd@b+1)
	movff	(___flsub@b+2),(___fladd@b+2)
	movff	(___flsub@b+3),(___fladd@b+3)
	movff	(___flsub@a),(___fladd@a)
	movff	(___flsub@a+1),(___fladd@a+1)
	movff	(___flsub@a+2),(___fladd@a+2)
	movff	(___flsub@a+3),(___fladd@a+3)
	call	___fladd	;wreg free
	movff	0+?___fladd,(?___flsub)
	movff	1+?___fladd,(?___flsub+1)
	movff	2+?___fladd,(?___flsub+2)
	movff	3+?___fladd,(?___flsub+3)
	
	line	250
	
l1889:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___flsub
	__end_of___flsub:
	signat	___flsub,8316
	global	___fladd

;; *************** function ___fladd *****************
;; Defined at:
;;		line 10 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[BANK0 ] long 
;;  a               4    4[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;  grs             1   15[BANK0 ] unsigned char 
;;  bexp            1   14[BANK0 ] unsigned char 
;;  aexp            1   13[BANK0 ] unsigned char 
;;  signs           1   12[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      16       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       16 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;;		___flsub
;;		_floor
;; This function uses a non-reentrant model
;;
psect	text18,class=CODE,space=0,reloc=2,group=1
	line	10
global __ptext18
__ptext18:
psect	text18
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
	line	10
	global	__size_of___fladd
	__size_of___fladd	equ	__end_of___fladd-___fladd
	
___fladd:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	21
	
l4309:; BSR set to: 0

	movf	(0+(___fladd@b+03h))&0ffh,w
	andlw	low(080h)
	movwf	((___fladd@signs))&0ffh
	line	22
	movf	(0+(___fladd@b+03h))&0ffh,w
	addwf	(0+(___fladd@b+03h))&0ffh,w
	movwf	((___fladd@bexp))&0ffh
	line	23
	
l4311:; BSR set to: 0

	
	btfss	(0+(___fladd@b+02h))&0ffh,(7)&7
	goto	u2791
	goto	u2790
u2791:
	goto	l4315
u2790:
	line	24
	
l4313:; BSR set to: 0

	bsf	(0+(0/8)+(___fladd@bexp))&0ffh,(0)&7
	line	28
	
l4315:; BSR set to: 0

	movf	((___fladd@bexp))&0ffh,w
	btfsc	status,2
	goto	u2801
	goto	u2800
u2801:
	goto	l4325
u2800:
	line	30
	
l4317:; BSR set to: 0

		incf	((___fladd@bexp))&0ffh,w
	btfss	status,2
	goto	u2811
	goto	u2810

u2811:
	goto	l4321
u2810:
	line	32
	
l4319:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fladd@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fladd@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fladd@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fladd@b+3))&0ffh
	line	35
	
l4321:; BSR set to: 0

	bsf	(0+(23/8)+(___fladd@b))&0ffh,(23)&7
	line	37
	
l4323:; BSR set to: 0

	movlw	low(0)
	movwf	(0+(___fladd@b+03h))&0ffh
	line	38
	goto	l4327
	line	41
	
l4325:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fladd@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fladd@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fladd@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fladd@b+3))&0ffh
	line	44
	
l4327:; BSR set to: 0

	movf	(0+(___fladd@a+03h))&0ffh,w
	andlw	low(080h)
	movwf	((___fladd@aexp))&0ffh
	line	46
	
l4329:; BSR set to: 0

	movf	((___fladd@signs))&0ffh,w
xorwf	((___fladd@aexp))&0ffh,w
	btfsc	status,2
	goto	u2821
	goto	u2820

u2821:
	goto	l4333
u2820:
	line	47
	
l4331:; BSR set to: 0

	bsf	(0+(6/8)+(___fladd@signs))&0ffh,(6)&7
	line	49
	
l4333:; BSR set to: 0

	movf	(0+(___fladd@a+03h))&0ffh,w
	addwf	(0+(___fladd@a+03h))&0ffh,w
	movwf	((___fladd@aexp))&0ffh
	line	50
	
l4335:; BSR set to: 0

	
	btfss	(0+(___fladd@a+02h))&0ffh,(7)&7
	goto	u2831
	goto	u2830
u2831:
	goto	l4339
u2830:
	line	51
	
l4337:; BSR set to: 0

	bsf	(0+(0/8)+(___fladd@aexp))&0ffh,(0)&7
	line	55
	
l4339:; BSR set to: 0

	movf	((___fladd@aexp))&0ffh,w
	btfsc	status,2
	goto	u2841
	goto	u2840
u2841:
	goto	l4349
u2840:
	line	57
	
l4341:; BSR set to: 0

		incf	((___fladd@aexp))&0ffh,w
	btfss	status,2
	goto	u2851
	goto	u2850

u2851:
	goto	l4345
u2850:
	line	59
	
l4343:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fladd@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fladd@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fladd@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fladd@a+3))&0ffh
	line	62
	
l4345:; BSR set to: 0

	bsf	(0+(23/8)+(___fladd@a))&0ffh,(23)&7
	line	64
	
l4347:; BSR set to: 0

	movlw	low(0)
	movwf	(0+(___fladd@a+03h))&0ffh
	line	65
	goto	l4351
	line	68
	
l4349:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___fladd@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___fladd@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___fladd@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___fladd@a+3))&0ffh
	line	75
	
l4351:; BSR set to: 0

		movf	((___fladd@bexp))&0ffh,w
	subwf	((___fladd@aexp))&0ffh,w
	btfsc	status,0
	goto	u2861
	goto	u2860

u2861:
	goto	l4387
u2860:
	line	77
	
l4353:; BSR set to: 0

	
	btfss	((___fladd@signs))&0ffh,(6)&7
	goto	u2871
	goto	u2870
u2871:
	goto	l4357
u2870:
	line	78
	
l4355:; BSR set to: 0

	movlw	(080h)&0ffh
	xorwf	((___fladd@signs))&0ffh
	line	81
	
l4357:; BSR set to: 0

	movff	(___fladd@bexp),(___fladd@grs)
	line	82
	
l4359:; BSR set to: 0

	movff	(___fladd@aexp),(___fladd@bexp)
	line	83
	
l4361:; BSR set to: 0

	movff	(___fladd@grs),(___fladd@aexp)
	line	84
	
l4363:; BSR set to: 0

	movff	(___fladd@b),(___fladd@grs)
	line	85
	
l4365:; BSR set to: 0

	movff	(___fladd@a),(___fladd@b)
	line	86
	
l4367:; BSR set to: 0

	movff	(___fladd@grs),(___fladd@a)
	line	87
	
l4369:; BSR set to: 0

	movff	0+(___fladd@b+01h),(___fladd@grs)
	line	88
	
l4371:; BSR set to: 0

	movff	0+(___fladd@a+01h),0+(___fladd@b+01h)
	line	89
	
l4373:; BSR set to: 0

	movff	(___fladd@grs),0+(___fladd@a+01h)
	line	90
	
l4375:; BSR set to: 0

	movff	0+(___fladd@b+02h),(___fladd@grs)
	line	91
	
l4377:; BSR set to: 0

	movff	0+(___fladd@a+02h),0+(___fladd@b+02h)
	line	92
	
l4379:; BSR set to: 0

	movff	(___fladd@grs),0+(___fladd@a+02h)
	line	93
	
l4381:; BSR set to: 0

	movff	0+(___fladd@b+03h),(___fladd@grs)
	line	94
	
l4383:; BSR set to: 0

	movff	0+(___fladd@a+03h),0+(___fladd@b+03h)
	line	95
	
l4385:; BSR set to: 0

	movff	(___fladd@grs),0+(___fladd@a+03h)
	line	98
	
l4387:; BSR set to: 0

	movlw	low(0)
	movwf	((___fladd@grs))&0ffh
	line	100
	
l4389:; BSR set to: 0

	movf	((___fladd@bexp))&0ffh,w
	movff	(___fladd@aexp),??___fladd+0+0
	clrf	(??___fladd+0+0+1)&0ffh
	subwf	(??___fladd+0+0)&0ffh
	movlw	0
	subwfb	(??___fladd+0+1)&0ffh
	btfsc	(??___fladd+0+1)&0ffh,7
	goto	u2881
	movf	(??___fladd+0+1)&0ffh,w
	bnz	u2880
	movlw	26
	subwf	 (??___fladd+0+0)&0ffh,w
	btfss	status,0
	goto	u2881
	goto	u2880

u2881:
	goto	l1848
u2880:
	line	101
	
l4391:; BSR set to: 0

	movf	((___fladd@b))&0ffh,w
iorwf	((___fladd@b+1))&0ffh,w
iorwf	((___fladd@b+2))&0ffh,w
iorwf	((___fladd@b+3))&0ffh,w
	btfss	status,2
	goto	u2891
	goto	u2890

u2891:
	movlw	1
	goto	u2900
u2890:
	movlw	0
u2900:
	movwf	((___fladd@grs))&0ffh
	line	102
	
l4393:; BSR set to: 0

	movlw	low(0)
	movwf	((___fladd@b))&0ffh
	movlw	high(0)
	movwf	((___fladd@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fladd@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fladd@b+3))&0ffh
	line	103
	
l4395:; BSR set to: 0

	movff	(___fladd@aexp),(___fladd@bexp)
	line	104
	goto	l1847
	line	106
	
l1849:; BSR set to: 0

	line	109
	
	btfss	((___fladd@grs))&0ffh,(0)&7
	goto	u2911
	goto	u2910
u2911:
	goto	l4399
u2910:
	line	110
	
l4397:; BSR set to: 0

	bcf	status,0
	rrcf	((___fladd@grs))&0ffh,w
	iorlw	low(01h)
	movwf	((___fladd@grs))&0ffh
	line	111
	goto	l4401
	line	113
	
l4399:; BSR set to: 0

	bcf status,0
	rrcf	((___fladd@grs))&0ffh

	line	115
	
l4401:; BSR set to: 0

	
	btfss	((___fladd@b))&0ffh,(0)&7
	goto	u2921
	goto	u2920
u2921:
	goto	l4405
u2920:
	line	116
	
l4403:; BSR set to: 0

	bsf	(0+(7/8)+(___fladd@grs))&0ffh,(7)&7
	line	118
	
l4405:; BSR set to: 0

	rlcf	((___fladd@b+3))&0ffh,w
	rrcf	((___fladd@b+3))&0ffh
	rrcf	((___fladd@b+2))&0ffh
	rrcf	((___fladd@b+1))&0ffh
	rrcf	((___fladd@b))&0ffh
	line	119
	
l4407:; BSR set to: 0

	incf	((___fladd@bexp))&0ffh
	line	120
	
l1848:; BSR set to: 0

	line	106
		movf	((___fladd@aexp))&0ffh,w
	subwf	((___fladd@bexp))&0ffh,w
	btfss	status,0
	goto	u2931
	goto	u2930

u2931:
	goto	l1849
u2930:
	line	121
	
l1847:; BSR set to: 0

	line	124
	
	btfsc	((___fladd@signs))&0ffh,(6)&7
	goto	u2941
	goto	u2940
u2941:
	goto	l4433
u2940:
	line	127
	
l4409:; BSR set to: 0

	movf	((___fladd@bexp))&0ffh,w
	btfss	status,2
	goto	u2951
	goto	u2950
u2951:
	goto	l4415
u2950:
	line	128
	
l4411:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((?___fladd))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((?___fladd+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((?___fladd+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((?___fladd+3))&0ffh
	goto	l1856
	line	132
	
l4415:; BSR set to: 0

	movf	((___fladd@a))&0ffh,w
	addwf	((___fladd@b))&0ffh
	movf	((___fladd@a+1))&0ffh,w
	addwfc	((___fladd@b+1))&0ffh
	movf	((___fladd@a+2))&0ffh,w
	addwfc	((___fladd@b+2))&0ffh
	movf	((___fladd@a+3))&0ffh,w
	addwfc	((___fladd@b+3))&0ffh
	line	134
	
l4417:; BSR set to: 0

	
	btfss	((___fladd@b+3))&0ffh,(24)&7
	goto	u2961
	goto	u2960
u2961:
	goto	l4469
u2960:
	line	135
	
l4419:; BSR set to: 0

	
	btfss	((___fladd@grs))&0ffh,(0)&7
	goto	u2971
	goto	u2970
u2971:
	goto	l4423
u2970:
	line	136
	
l4421:; BSR set to: 0

	bcf	status,0
	rrcf	((___fladd@grs))&0ffh,w
	iorlw	low(01h)
	movwf	((___fladd@grs))&0ffh
	line	137
	goto	l4425
	line	139
	
l4423:; BSR set to: 0

	bcf status,0
	rrcf	((___fladd@grs))&0ffh

	line	141
	
l4425:; BSR set to: 0

	
	btfss	((___fladd@b))&0ffh,(0)&7
	goto	u2981
	goto	u2980
u2981:
	goto	l4429
u2980:
	line	142
	
l4427:; BSR set to: 0

	bsf	(0+(7/8)+(___fladd@grs))&0ffh,(7)&7
	line	144
	
l4429:; BSR set to: 0

	rlcf	((___fladd@b+3))&0ffh,w
	rrcf	((___fladd@b+3))&0ffh
	rrcf	((___fladd@b+2))&0ffh
	rrcf	((___fladd@b+1))&0ffh
	rrcf	((___fladd@b))&0ffh
	line	145
	
l4431:; BSR set to: 0

	incf	((___fladd@bexp))&0ffh
	goto	l4469
	line	153
	
l4433:; BSR set to: 0

		movf	((___fladd@a))&0ffh,w
	subwf	((___fladd@b))&0ffh,w
	movf	((___fladd@a+1))&0ffh,w
	subwfb	((___fladd@b+1))&0ffh,w
	movf	((___fladd@a+2))&0ffh,w
	subwfb	((___fladd@b+2))&0ffh,w
	movf	((___fladd@b+3))&0ffh,w
	xorlw	80h
	movwf	(??___fladd+0+0)&0ffh
	movf	((___fladd@a+3))&0ffh,w
	xorlw	80h
	subwfb	(??___fladd+0+0)&0ffh,w
	btfsc	status,0
	goto	u2991
	goto	u2990

u2991:
	goto	l4443
u2990:
	line	154
	
l4435:; BSR set to: 0

	movf	((___fladd@b))&0ffh,w
	subwf	((___fladd@a))&0ffh,w
	movwf	(??___fladd+0+0)&0ffh
	movf	((___fladd@b+1))&0ffh,w
	subwfb	((___fladd@a+1))&0ffh,w
	movwf	1+(??___fladd+0+0)&0ffh
	
	movf	((___fladd@b+2))&0ffh,w
	subwfb	((___fladd@a+2))&0ffh,w
	movwf	2+(??___fladd+0+0)&0ffh
	
	movf	((___fladd@b+3))&0ffh,w
	subwfb	((___fladd@a+3))&0ffh,w
	movwf	3+(??___fladd+0+0)&0ffh
	movlw	0FFh
	addwf	(??___fladd+0+0)&0ffh,w
	movwf	((___fladd@b))&0ffh
	movlw	0FFh
	addwfc	(??___fladd+0+1)&0ffh,w
	movwf	1+((___fladd@b))&0ffh
	
	movlw	0FFh
	addwfc	(??___fladd+0+2)&0ffh,w
	movwf	2+((___fladd@b))&0ffh
	
	movlw	0FFh
	addwfc	(??___fladd+0+3)&0ffh,w
	movwf	3+((___fladd@b))&0ffh
	line	155
	movlw	(080h)&0ffh
	xorwf	((___fladd@signs))&0ffh
	line	156
	
l4437:; BSR set to: 0

	negf	((___fladd@grs))&0ffh
	line	157
	
l4439:; BSR set to: 0

	movf	((___fladd@grs))&0ffh,w
	btfss	status,2
	goto	u3001
	goto	u3000
u3001:
	goto	l1864
u3000:
	line	158
	
l4441:; BSR set to: 0

	movlw	low(01h)
	addwf	((___fladd@b))&0ffh
	movlw	0
	addwfc	((___fladd@b+1))&0ffh
	addwfc	((___fladd@b+2))&0ffh
	addwfc	((___fladd@b+3))&0ffh
	goto	l1864
	line	162
	
l4443:; BSR set to: 0

	movf	((___fladd@a))&0ffh,w
	subwf	((___fladd@b))&0ffh
	movf	((___fladd@a+1))&0ffh,w
	subwfb	((___fladd@b+1))&0ffh
	movf	((___fladd@a+2))&0ffh,w
	subwfb	((___fladd@b+2))&0ffh
	movf	((___fladd@a+3))&0ffh,w
	subwfb	((___fladd@b+3))&0ffh
	line	163
	
l1864:; BSR set to: 0

	line	166
	movf	((___fladd@b))&0ffh,w
iorwf	((___fladd@b+1))&0ffh,w
iorwf	((___fladd@b+2))&0ffh,w
iorwf	((___fladd@b+3))&0ffh,w
	btfss	status,2
	goto	u3011
	goto	u3010

u3011:
	goto	l4467
u3010:
	
l4445:; BSR set to: 0

	movf	((___fladd@grs))&0ffh,w
	btfss	status,2
	goto	u3021
	goto	u3020
u3021:
	goto	l4467
u3020:
	line	167
	
l4447:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((?___fladd))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((?___fladd+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((?___fladd+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((?___fladd+3))&0ffh
	goto	l1856
	line	172
	
l4451:; BSR set to: 0

	bcf	status,0
	rlcf	((___fladd@b))&0ffh
	rlcf	((___fladd@b+1))&0ffh
	rlcf	((___fladd@b+2))&0ffh
	rlcf	((___fladd@b+3))&0ffh
	line	173
	
l4453:; BSR set to: 0

	
	btfss	((___fladd@grs))&0ffh,(7)&7
	goto	u3031
	goto	u3030
u3031:
	goto	l4457
u3030:
	line	174
	
l4455:; BSR set to: 0

	bsf	(0+(0/8)+(___fladd@b))&0ffh,(0)&7
	line	176
	
l4457:; BSR set to: 0

	
	btfss	((___fladd@grs))&0ffh,(0)&7
	goto	u3041
	goto	u3040
u3041:
	goto	l4461
u3040:
	line	177
	
l4459:; BSR set to: 0

	bsf	status,0
	
	rlcf	((___fladd@grs))&0ffh
	line	178
	goto	l4463
	line	180
	
l4461:; BSR set to: 0

	bcf status,0
	rlcf	((___fladd@grs))&0ffh

	line	182
	
l4463:; BSR set to: 0

	movf	((___fladd@bexp))&0ffh,w
	btfsc	status,2
	goto	u3051
	goto	u3050
u3051:
	goto	l4467
u3050:
	line	183
	
l4465:; BSR set to: 0

	decf	((___fladd@bexp))&0ffh
	line	171
	
l4467:; BSR set to: 0

	
	btfss	((___fladd@b+2))&0ffh,(23)&7
	goto	u3061
	goto	u3060
u3061:
	goto	l4451
u3060:
	line	192
	
l4469:; BSR set to: 0

	movlw	low(0)
	movwf	((___fladd@aexp))&0ffh
	line	193
	
l4471:; BSR set to: 0

	
	btfss	((___fladd@grs))&0ffh,(7)&7
	goto	u3071
	goto	u3070
u3071:
	goto	l1873
u3070:
	line	194
	
l4473:; BSR set to: 0

	movff	(___fladd@grs),??___fladd+0+0
	movlw	07Fh
	andwf	(??___fladd+0+0)&0ffh
	btfsc	status,2
	goto	u3081
	goto	u3080
u3081:
	goto	l1874
u3080:
	line	195
	
l4475:; BSR set to: 0

	movlw	low(01h)
	movwf	((___fladd@aexp))&0ffh
	line	196
	goto	l1873
	line	197
	
l1874:; BSR set to: 0

	line	198
	
	btfss	((___fladd@b))&0ffh,(0)&7
	goto	u3091
	goto	u3090
u3091:
	goto	l1873
u3090:
	goto	l4475
	line	202
	
l1873:; BSR set to: 0

	line	203
	movf	((___fladd@aexp))&0ffh,w
	btfsc	status,2
	goto	u3101
	goto	u3100
u3101:
	goto	l4487
u3100:
	line	204
	
l4479:; BSR set to: 0

	movlw	low(01h)
	addwf	((___fladd@b))&0ffh
	movlw	0
	addwfc	((___fladd@b+1))&0ffh
	addwfc	((___fladd@b+2))&0ffh
	addwfc	((___fladd@b+3))&0ffh
	line	205
	
l4481:; BSR set to: 0

	
	btfss	((___fladd@b+3))&0ffh,(24)&7
	goto	u3111
	goto	u3110
u3111:
	goto	l4487
u3110:
	line	206
	
l4483:; BSR set to: 0

	movff	(___fladd@b),??___fladd+0+0
	movff	(___fladd@b+1),??___fladd+0+0+1
	movff	(___fladd@b+2),??___fladd+0+0+2
	movff	(___fladd@b+3),??___fladd+0+0+3
	rlcf	(??___fladd+0+3)&0ffh,w
	rrcf	(??___fladd+0+3)&0ffh
	rrcf	(??___fladd+0+2)&0ffh
	rrcf	(??___fladd+0+1)&0ffh
	rrcf	(??___fladd+0+0)&0ffh
	movff	??___fladd+0+0,(___fladd@b)
	movff	??___fladd+0+1,(___fladd@b+1)
	movff	??___fladd+0+2,(___fladd@b+2)
	movff	??___fladd+0+3,(___fladd@b+3)
	line	207
		incf	((___fladd@bexp))&0ffh,w
	btfsc	status,2
	goto	u3121
	goto	u3120

u3121:
	goto	l4487
u3120:
	line	208
	
l4485:; BSR set to: 0

	incf	((___fladd@bexp))&0ffh
	line	215
	
l4487:; BSR set to: 0

		incf	((___fladd@bexp))&0ffh,w
	btfsc	status,2
	goto	u3131
	goto	u3130

u3131:
	goto	l4491
u3130:
	
l4489:; BSR set to: 0

	movf	((___fladd@bexp))&0ffh,w
	btfss	status,2
	goto	u3141
	goto	u3140
u3141:
	goto	l4495
u3140:
	line	216
	
l4491:; BSR set to: 0

	movlw	low(0)
	movwf	((___fladd@b))&0ffh
	movlw	high(0)
	movwf	((___fladd@b+1))&0ffh
	movlw	low highword(0)
	movwf	((___fladd@b+2))&0ffh
	movlw	high highword(0)
	movwf	((___fladd@b+3))&0ffh
	line	218
	movf	((___fladd@bexp))&0ffh,w
	btfss	status,2
	goto	u3151
	goto	u3150
u3151:
	goto	l4495
u3150:
	line	219
	
l4493:; BSR set to: 0

	movlw	low(0)
	movwf	((___fladd@signs))&0ffh
	line	225
	
l4495:; BSR set to: 0

	
	btfss	((___fladd@bexp))&0ffh,(0)&7
	goto	u3161
	goto	u3160
u3161:
	goto	l4499
u3160:
	line	226
	
l4497:; BSR set to: 0

	bsf	(0+(7/8)+0+(___fladd@b+02h))&0ffh,(7)&7
	line	227
	goto	l4501
	line	230
	
l4499:; BSR set to: 0

	bcf	(0+(7/8)+0+(___fladd@b+02h))&0ffh,(7)&7
	line	232
	
l4501:; BSR set to: 0

	bcf	status,0
	rrcf	((___fladd@bexp))&0ffh,w
	movwf	(0+(___fladd@b+03h))&0ffh
	line	233
	
l4503:; BSR set to: 0

	
	btfss	((___fladd@signs))&0ffh,(7)&7
	goto	u3171
	goto	u3170
u3171:
	goto	l4507
u3170:
	line	234
	
l4505:; BSR set to: 0

	bsf	(0+(7/8)+0+(___fladd@b+03h))&0ffh,(7)&7
	line	236
	
l4507:; BSR set to: 0

	movff	(___fladd@b),(?___fladd)
	movff	(___fladd@b+1),(?___fladd+1)
	movff	(___fladd@b+2),(?___fladd+2)
	movff	(___fladd@b+3),(?___fladd+3)
	line	237
	
l1856:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fladd
	__end_of___fladd:
	signat	___fladd,8316
	global	___flneg

;; *************** function ___flneg *****************
;; Defined at:
;;		line 15 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flneg.c"
;; Parameters:    Size  Location     Type
;;  f1              4    0[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;; This function uses a non-reentrant model
;;
psect	text19,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flneg.c"
	line	15
global __ptext19
__ptext19:
psect	text19
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\flneg.c"
	line	15
	global	__size_of___flneg
	__size_of___flneg	equ	__end_of___flneg-___flneg
	
___flneg:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	17
	
l4943:; BSR set to: 0

	movf	((___flneg@f1))&0ffh,w
iorwf	((___flneg@f1+1))&0ffh,w
iorwf	((___flneg@f1+2))&0ffh,w
iorwf	((___flneg@f1+3))&0ffh,w
	btfsc	status,2
	goto	u3871
	goto	u3870

u3871:
	goto	l4947
u3870:
	line	18
	
l4945:; BSR set to: 0

	movlw	0
	xorwf	((___flneg@f1))&0ffh
	movlw	0
	xorwf	((___flneg@f1+1))&0ffh
	movlw	0
	xorwf	((___flneg@f1+2))&0ffh
	movlw	080h
	xorwf	((___flneg@f1+3))&0ffh
	line	19
	
l4947:; BSR set to: 0

	movff	(___flneg@f1),(?___flneg)
	movff	(___flneg@f1+1),(?___flneg+1)
	movff	(___flneg@f1+2),(?___flneg+2)
	movff	(___flneg@f1+3),(?___flneg+3)
	line	20
	
l1597:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___flneg
	__end_of___flneg:
	signat	___flneg,4220
	global	___flmul

;; *************** function ___flmul *****************
;; Defined at:
;;		line 8 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
;; Parameters:    Size  Location     Type
;;  b               4   25[BANK0 ] unsigned char 
;;  a               4   29[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  prod            4   44[BANK0 ] struct .
;;  grs             4   39[BANK0 ] unsigned long 
;;  temp            2   48[BANK0 ] struct .
;;  bexp            1   43[BANK0 ] unsigned char 
;;  aexp            1   38[BANK0 ] unsigned char 
;;  sign            1   37[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4   25[BANK0 ] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0      13       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      25       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       25 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;;		_main
;; This function uses a non-reentrant model
;;
psect	text20,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
global __ptext20
__ptext20:
psect	text20
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
	global	__size_of___flmul
	__size_of___flmul	equ	__end_of___flmul-___flmul
	
___flmul:; BSR set to: 0

;incstack = 0
	opt	callstack 26
	line	17
	
l4807:; BSR set to: 0

	movf	(0+(___flmul@b+03h))&0ffh,w
	andlw	low(080h)
	movwf	((___flmul@sign))&0ffh
	line	18
	movf	(0+(___flmul@b+03h))&0ffh,w
	addwf	(0+(___flmul@b+03h))&0ffh,w
	movwf	((___flmul@bexp))&0ffh
	line	19
	
l4809:; BSR set to: 0

	
	btfss	(0+(___flmul@b+02h))&0ffh,(7)&7
	goto	u3691
	goto	u3690
u3691:
	goto	l4813
u3690:
	line	20
	
l4811:; BSR set to: 0

	bsf	(0+(0/8)+(___flmul@bexp))&0ffh,(0)&7
	line	24
	
l4813:; BSR set to: 0

	movf	((___flmul@bexp))&0ffh,w
	btfsc	status,2
	goto	u3701
	goto	u3700
u3701:
	goto	l4821
u3700:
	line	26
	
l4815:; BSR set to: 0

		incf	((___flmul@bexp))&0ffh,w
	btfss	status,2
	goto	u3711
	goto	u3710

u3711:
	goto	l4819
u3710:
	line	28
	
l4817:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___flmul@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___flmul@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___flmul@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___flmul@b+3))&0ffh
	line	31
	
l4819:; BSR set to: 0

	bsf	(0+(23/8)+(___flmul@b))&0ffh,(23)&7
	line	33
	goto	l4823
	line	36
	
l4821:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___flmul@b))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___flmul@b+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___flmul@b+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___flmul@b+3))&0ffh
	line	39
	
l4823:; BSR set to: 0

	movf	(0+(___flmul@a+03h))&0ffh,w
	andlw	low(080h)
	xorwf	((___flmul@sign))&0ffh
	line	40
	
l4825:; BSR set to: 0

	movf	(0+(___flmul@a+03h))&0ffh,w
	addwf	(0+(___flmul@a+03h))&0ffh,w
	movwf	((___flmul@aexp))&0ffh
	line	41
	
l4827:; BSR set to: 0

	
	btfss	(0+(___flmul@a+02h))&0ffh,(7)&7
	goto	u3721
	goto	u3720
u3721:
	goto	l4831
u3720:
	line	42
	
l4829:; BSR set to: 0

	bsf	(0+(0/8)+(___flmul@aexp))&0ffh,(0)&7
	line	45
	
l4831:; BSR set to: 0

	movf	((___flmul@aexp))&0ffh,w
	btfsc	status,2
	goto	u3731
	goto	u3730
u3731:
	goto	l4839
u3730:
	line	48
	
l4833:; BSR set to: 0

		incf	((___flmul@aexp))&0ffh,w
	btfss	status,2
	goto	u3741
	goto	u3740

u3741:
	goto	l4837
u3740:
	line	50
	
l4835:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___flmul@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___flmul@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___flmul@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___flmul@a+3))&0ffh
	line	53
	
l4837:; BSR set to: 0

	bsf	(0+(23/8)+(___flmul@a))&0ffh,(23)&7
	line	54
	goto	l1933
	line	57
	
l4839:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((___flmul@a))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((___flmul@a+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((___flmul@a+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((___flmul@a+3))&0ffh
	line	58
	
l1933:; BSR set to: 0

	line	65
	movf	((___flmul@aexp))&0ffh,w
	btfsc	status,2
	goto	u3751
	goto	u3750
u3751:
	goto	l4843
u3750:
	
l4841:; BSR set to: 0

	movf	((___flmul@bexp))&0ffh,w
	btfss	status,2
	goto	u3761
	goto	u3760
u3761:
	goto	l4847
u3760:
	line	66
	
l4843:; BSR set to: 0

	movlw	low(normalize32(0x0))
	movwf	((?___flmul))&0ffh
	movlw	high(normalize32(0x0))
	movwf	((?___flmul+1))&0ffh
	movlw	low highword(normalize32(0x0))
	movwf	((?___flmul+2))&0ffh
	movlw	high highword(normalize32(0x0))
	movwf	((?___flmul+3))&0ffh
	goto	l1937
	line	95
	
l4847:; BSR set to: 0

	movf	(0+(___flmul@a+02h))&0ffh,w
	mulwf	((___flmul@b))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	96
	
l4849:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	movwf	((___flmul@grs))&0ffh
	clrf	((___flmul@grs+1))&0ffh
	clrf	((___flmul@grs+2))&0ffh
	clrf	((___flmul@grs+3))&0ffh

	line	97
	
l4851:; BSR set to: 0

	movf	(0+(___flmul@temp+01h))&0ffh,w
	movwf	((___flmul@prod))&0ffh
	clrf	((___flmul@prod+1))&0ffh
	clrf	((___flmul@prod+2))&0ffh
	clrf	((___flmul@prod+3))&0ffh

	line	98
	movf	(0+(___flmul@a+01h))&0ffh,w
	mulwf	(0+(___flmul@b+01h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	99
	
l4853:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@grs))&0ffh
	movlw	0
	addwfc	((___flmul@grs+1))&0ffh
	addwfc	((___flmul@grs+2))&0ffh
	addwfc	((___flmul@grs+3))&0ffh
	line	100
	
l4855:; BSR set to: 0

	movf	(0+(___flmul@temp+01h))&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movlw	0
	addwfc	((___flmul@prod+1))&0ffh
	addwfc	((___flmul@prod+2))&0ffh
	addwfc	((___flmul@prod+3))&0ffh
	line	101
	movf	((___flmul@a))&0ffh,w
	mulwf	(0+(___flmul@b+02h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	102
	
l4857:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@grs))&0ffh
	movlw	0
	addwfc	((___flmul@grs+1))&0ffh
	addwfc	((___flmul@grs+2))&0ffh
	addwfc	((___flmul@grs+3))&0ffh
	line	103
	
l4859:; BSR set to: 0

	movf	(0+(___flmul@temp+01h))&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movlw	0
	addwfc	((___flmul@prod+1))&0ffh
	addwfc	((___flmul@prod+2))&0ffh
	addwfc	((___flmul@prod+3))&0ffh
	line	104
	
l4861:; BSR set to: 0

	movff	(___flmul@grs+2),(___flmul@grs+3)
	movff	(___flmul@grs+1),(___flmul@grs+2)
	movff	(___flmul@grs),(___flmul@grs+1)
	clrf	((___flmul@grs))&0ffh
	line	105
	
l4863:; BSR set to: 0

	movf	((___flmul@a))&0ffh,w
	mulwf	(0+(___flmul@b+01h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	106
	
l4865:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@grs))&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	addwfc	((___flmul@grs+1))&0ffh
	movlw	0
	addwfc	((___flmul@grs+2))&0ffh
	movlw	0
	addwfc	((___flmul@grs+3))&0ffh

	line	107
	
l4867:; BSR set to: 0

	movf	(0+(___flmul@a+01h))&0ffh,w
	mulwf	((___flmul@b))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	108
	
l4869:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@grs))&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	addwfc	((___flmul@grs+1))&0ffh
	movlw	0
	addwfc	((___flmul@grs+2))&0ffh
	movlw	0
	addwfc	((___flmul@grs+3))&0ffh

	line	109
	
l4871:; BSR set to: 0

	movff	(___flmul@grs+2),(___flmul@grs+3)
	movff	(___flmul@grs+1),(___flmul@grs+2)
	movff	(___flmul@grs),(___flmul@grs+1)
	clrf	((___flmul@grs))&0ffh
	line	110
	movf	((___flmul@a))&0ffh,w
	mulwf	((___flmul@b))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	111
	
l4873:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@grs))&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	addwfc	((___flmul@grs+1))&0ffh
	movlw	0
	addwfc	((___flmul@grs+2))&0ffh
	movlw	0
	addwfc	((___flmul@grs+3))&0ffh

	line	112
	
l4875:; BSR set to: 0

	movf	(0+(___flmul@a+02h))&0ffh,w
	mulwf	(0+(___flmul@b+01h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	113
	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	addwfc	((___flmul@prod+1))&0ffh
	movlw	0
	addwfc	((___flmul@prod+2))&0ffh
	movlw	0
	addwfc	((___flmul@prod+3))&0ffh

	line	114
	
l4877:; BSR set to: 0

	movf	(0+(___flmul@a+01h))&0ffh,w
	mulwf	(0+(___flmul@b+02h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	115
	
l4879:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	addwfc	((___flmul@prod+1))&0ffh
	movlw	0
	addwfc	((___flmul@prod+2))&0ffh
	movlw	0
	addwfc	((___flmul@prod+3))&0ffh

	line	116
	movf	(0+(___flmul@a+02h))&0ffh,w
	mulwf	(0+(___flmul@b+02h))&0ffh
	movff	prodl,(___flmul@temp)
	movff	prodh,(___flmul@temp+1)
	line	117
	
l4881:; BSR set to: 0

	movf	((___flmul@temp))&0ffh,w
	movwf	(??___flmul+0+0)&0ffh
	movf	((___flmul@temp+1))&0ffh,w
	movwf	1+(??___flmul+0+0)&0ffh
	
	clrf	2+(??___flmul+0+0)&0ffh
	
	clrf	3+(??___flmul+0+0)&0ffh
	movff	??___flmul+0+2,??___flmul+0+3
	movff	??___flmul+0+1,??___flmul+0+2
	movff	??___flmul+0+0,??___flmul+0+1
	clrf	(??___flmul+0+0)&0ffh
	movf	(??___flmul+0+0)&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movf	(??___flmul+0+1)&0ffh,w
	addwfc	((___flmul@prod+1))&0ffh
	movf	(??___flmul+0+2)&0ffh,w
	addwfc	((___flmul@prod+2))&0ffh
	movf	(??___flmul+0+3)&0ffh,w
	addwfc	((___flmul@prod+3))&0ffh

	line	145
	
l4883:; BSR set to: 0

	movf	(0+(___flmul@grs+03h))&0ffh,w
	addwf	((___flmul@prod))&0ffh
	movlw	0
	addwfc	((___flmul@prod+1))&0ffh
	addwfc	((___flmul@prod+2))&0ffh
	addwfc	((___flmul@prod+3))&0ffh
	line	146
	
l4885:; BSR set to: 0

	movff	(___flmul@grs+2),(___flmul@grs+3)
	movff	(___flmul@grs+1),(___flmul@grs+2)
	movff	(___flmul@grs),(___flmul@grs+1)
	clrf	((___flmul@grs))&0ffh
	line	149
	
l4887:; BSR set to: 0

	movf	((___flmul@aexp))&0ffh,w
	movff	(___flmul@bexp),??___flmul+0+0
	clrf	(??___flmul+0+0+1)&0ffh
	addwf	(??___flmul+0+0)&0ffh
	movlw	0
	addwfc	(??___flmul+0+1)&0ffh
	movlw	low(-126)
	addwf	(??___flmul+0+0)&0ffh,w
	movwf	((___flmul@temp))&0ffh
	movlw	high(-126)
	addwfc	(??___flmul+0+1)&0ffh,w
	movwf	1+((___flmul@temp))&0ffh
	line	152
	goto	l4895
	line	153
	
l4889:; BSR set to: 0

	bcf	status,0
	rlcf	((___flmul@prod))&0ffh
	rlcf	((___flmul@prod+1))&0ffh
	rlcf	((___flmul@prod+2))&0ffh
	rlcf	((___flmul@prod+3))&0ffh
	line	154
	
l4891:; BSR set to: 0

	
	btfss	((___flmul@grs+3))&0ffh,(31)&7
	goto	u3771
	goto	u3770
u3771:
	goto	l1940
u3770:
	line	155
	
l4893:; BSR set to: 0

	bsf	(0+(0/8)+(___flmul@prod))&0ffh,(0)&7
	line	156
	
l1940:; BSR set to: 0

	line	157
	bcf	status,0
	rlcf	((___flmul@grs))&0ffh
	rlcf	((___flmul@grs+1))&0ffh
	rlcf	((___flmul@grs+2))&0ffh
	rlcf	((___flmul@grs+3))&0ffh
	line	158
	decf	((___flmul@temp))&0ffh
	btfss	status,0
	decf	((___flmul@temp+1))&0ffh
	line	152
	
l4895:; BSR set to: 0

	
	btfss	((___flmul@prod+2))&0ffh,(23)&7
	goto	u3781
	goto	u3780
u3781:
	goto	l4889
u3780:
	line	163
	
l4897:; BSR set to: 0

	movlw	low(0)
	movwf	((___flmul@aexp))&0ffh
	line	164
	
l4899:; BSR set to: 0

	
	btfss	((___flmul@grs+3))&0ffh,(31)&7
	goto	u3791
	goto	u3790
u3791:
	goto	l1942
u3790:
	line	165
	
l4901:; BSR set to: 0

	movlw	0FFh
	andwf	((___flmul@grs))&0ffh,w
	movwf	(??___flmul+0+0)&0ffh
	movlw	0FFh
	andwf	((___flmul@grs+1))&0ffh,w
	movwf	1+(??___flmul+0+0)&0ffh
	
	movlw	0FFh
	andwf	((___flmul@grs+2))&0ffh,w
	movwf	2+(??___flmul+0+0)&0ffh
	
	movlw	07Fh
	andwf	((___flmul@grs+3))&0ffh,w
	movwf	3+(??___flmul+0+0)&0ffh
	movf	(??___flmul+0+0)&0ffh,w
iorwf	(??___flmul+0+1)&0ffh,w
iorwf	(??___flmul+0+2)&0ffh,w
iorwf	(??___flmul+0+3)&0ffh,w
	btfsc	status,2
	goto	u3801
	goto	u3800

u3801:
	goto	l1943
u3800:
	line	166
	
l4903:; BSR set to: 0

	movlw	low(01h)
	movwf	((___flmul@aexp))&0ffh
	line	167
	goto	l1942
	line	168
	
l1943:; BSR set to: 0

	line	169
	
	btfss	((___flmul@prod))&0ffh,(0)&7
	goto	u3811
	goto	u3810
u3811:
	goto	l1942
u3810:
	goto	l4903
	line	173
	
l1942:; BSR set to: 0

	line	174
	movf	((___flmul@aexp))&0ffh,w
	btfsc	status,2
	goto	u3821
	goto	u3820
u3821:
	goto	l4915
u3820:
	line	175
	
l4907:; BSR set to: 0

	movlw	low(01h)
	addwf	((___flmul@prod))&0ffh
	movlw	0
	addwfc	((___flmul@prod+1))&0ffh
	addwfc	((___flmul@prod+2))&0ffh
	addwfc	((___flmul@prod+3))&0ffh
	line	176
	
l4909:; BSR set to: 0

	
	btfss	((___flmul@prod+3))&0ffh,(24)&7
	goto	u3831
	goto	u3830
u3831:
	goto	l4915
u3830:
	line	177
	
l4911:; BSR set to: 0

	movff	(___flmul@prod),??___flmul+0+0
	movff	(___flmul@prod+1),??___flmul+0+0+1
	movff	(___flmul@prod+2),??___flmul+0+0+2
	movff	(___flmul@prod+3),??___flmul+0+0+3
	rlcf	(??___flmul+0+3)&0ffh,w
	rrcf	(??___flmul+0+3)&0ffh
	rrcf	(??___flmul+0+2)&0ffh
	rrcf	(??___flmul+0+1)&0ffh
	rrcf	(??___flmul+0+0)&0ffh
	movff	??___flmul+0+0,(___flmul@prod)
	movff	??___flmul+0+1,(___flmul@prod+1)
	movff	??___flmul+0+2,(___flmul@prod+2)
	movff	??___flmul+0+3,(___flmul@prod+3)
	line	178
	
l4913:; BSR set to: 0

	infsnz	((___flmul@temp))&0ffh
	incf	((___flmul@temp+1))&0ffh
	line	183
	
l4915:; BSR set to: 0

	btfsc	((___flmul@temp+1))&0ffh,7
	goto	u3841
	movf	((___flmul@temp+1))&0ffh,w
	bnz	u3840
	incf	((___flmul@temp))&0ffh,w
	btfss	status,0
	goto	u3841
	goto	u3840

u3841:
	goto	l4919
u3840:
	line	184
	
l4917:; BSR set to: 0

	movlw	low(07F800000h)
	movwf	((___flmul@prod))&0ffh
	movlw	high(07F800000h)
	movwf	((___flmul@prod+1))&0ffh
	movlw	low highword(07F800000h)
	movwf	((___flmul@prod+2))&0ffh
	movlw	high highword(07F800000h)
	movwf	((___flmul@prod+3))&0ffh
	line	185
	goto	l4931
	line	187
	
l4919:; BSR set to: 0

	btfsc	((___flmul@temp+1))&0ffh,7
	goto	u3850
	movf	((___flmul@temp+1))&0ffh,w
	bnz	u3851
	decf	((___flmul@temp))&0ffh,w
	btfsc	status,0
	goto	u3851
	goto	u3850

u3851:
	goto	l1950
u3850:
	line	188
	
l4921:; BSR set to: 0

	movlw	low(0)
	movwf	((___flmul@prod))&0ffh
	movlw	high(0)
	movwf	((___flmul@prod+1))&0ffh
	movlw	low highword(0)
	movwf	((___flmul@prod+2))&0ffh
	movlw	high highword(0)
	movwf	((___flmul@prod+3))&0ffh
	line	190
	movlw	low(0)
	movwf	((___flmul@sign))&0ffh
	line	191
	goto	l4931
	line	192
	
l1950:; BSR set to: 0

	line	194
	movff	(___flmul@temp),(___flmul@bexp)
	line	195
	
l4923:; BSR set to: 0

	movlw	0FFh
	andwf	((___flmul@prod))&0ffh
	movlw	0FFh
	andwf	((___flmul@prod+1))&0ffh
	movlw	07Fh
	andwf	((___flmul@prod+2))&0ffh
	movlw	0
	andwf	((___flmul@prod+3))&0ffh
	line	196
	
l4925:; BSR set to: 0

	
	btfss	((___flmul@bexp))&0ffh,(0)&7
	goto	u3861
	goto	u3860
u3861:
	goto	l4929
u3860:
	line	197
	
l4927:; BSR set to: 0

	bsf	(0+(7/8)+0+(___flmul@prod+02h))&0ffh,(7)&7
	line	199
	
l4929:; BSR set to: 0

	bcf	status,0
	rrcf	((___flmul@bexp))&0ffh,w
	movwf	(0+(___flmul@prod+03h))&0ffh
	line	201
	
l4931:; BSR set to: 0

	movf	((___flmul@sign))&0ffh,w
	iorwf	(0+(___flmul@prod+03h))&0ffh
	line	203
	
l4933:; BSR set to: 0

	movff	(___flmul@prod),(?___flmul)
	movff	(___flmul@prod+1),(?___flmul+1)
	movff	(___flmul@prod+2),(?___flmul+2)
	movff	(___flmul@prod+3),(?___flmul+3)
	line	205
	
l1937:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___flmul
	__end_of___flmul:
	signat	___flmul,8316
	global	___almod

;; *************** function ___almod *****************
;; Defined at:
;;		line 7 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\almod.c"
;; Parameters:    Size  Location     Type
;;  dividend        4    0[BANK0 ] long 
;;  divisor         4    4[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;  sign            1    9[BANK0 ] unsigned char 
;;  counter         1    8[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      10       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;; This function uses a non-reentrant model
;;
psect	text21,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\almod.c"
	line	7
global __ptext21
__ptext21:
psect	text21
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\almod.c"
	line	7
	global	__size_of___almod
	__size_of___almod	equ	__end_of___almod-___almod
	
___almod:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	12
	
l4771:; BSR set to: 0

	movlw	low(0)
	movwf	((___almod@sign))&0ffh
	line	13
	
l4773:; BSR set to: 0

	btfsc	((___almod@dividend+3))&0ffh,7
	goto	u3630
	goto	u3631

u3631:
	goto	l4779
u3630:
	line	14
	
l4775:; BSR set to: 0

	comf	((___almod@dividend+3))&0ffh
	comf	((___almod@dividend+2))&0ffh
	comf	((___almod@dividend+1))&0ffh
	negf	((___almod@dividend))&0ffh
	movlw	0
	addwfc	((___almod@dividend+1))&0ffh
	addwfc	((___almod@dividend+2))&0ffh
	addwfc	((___almod@dividend+3))&0ffh
	line	15
	
l4777:; BSR set to: 0

	movlw	low(01h)
	movwf	((___almod@sign))&0ffh
	line	17
	
l4779:; BSR set to: 0

	btfsc	((___almod@divisor+3))&0ffh,7
	goto	u3640
	goto	u3641

u3641:
	goto	l4783
u3640:
	line	18
	
l4781:; BSR set to: 0

	comf	((___almod@divisor+3))&0ffh
	comf	((___almod@divisor+2))&0ffh
	comf	((___almod@divisor+1))&0ffh
	negf	((___almod@divisor))&0ffh
	movlw	0
	addwfc	((___almod@divisor+1))&0ffh
	addwfc	((___almod@divisor+2))&0ffh
	addwfc	((___almod@divisor+3))&0ffh
	line	19
	
l4783:; BSR set to: 0

	movf	((___almod@divisor))&0ffh,w
iorwf	((___almod@divisor+1))&0ffh,w
iorwf	((___almod@divisor+2))&0ffh,w
iorwf	((___almod@divisor+3))&0ffh,w
	btfsc	status,2
	goto	u3651
	goto	u3650

u3651:
	goto	l4799
u3650:
	line	20
	
l4785:; BSR set to: 0

	movlw	low(01h)
	movwf	((___almod@counter))&0ffh
	line	21
	goto	l4789
	line	22
	
l4787:; BSR set to: 0

	bcf	status,0
	rlcf	((___almod@divisor))&0ffh
	rlcf	((___almod@divisor+1))&0ffh
	rlcf	((___almod@divisor+2))&0ffh
	rlcf	((___almod@divisor+3))&0ffh
	line	23
	incf	((___almod@counter))&0ffh
	line	21
	
l4789:; BSR set to: 0

	
	btfss	((___almod@divisor+3))&0ffh,(31)&7
	goto	u3661
	goto	u3660
u3661:
	goto	l4787
u3660:
	line	26
	
l4791:; BSR set to: 0

		movf	((___almod@divisor))&0ffh,w
	subwf	((___almod@dividend))&0ffh,w
	movf	((___almod@divisor+1))&0ffh,w
	subwfb	((___almod@dividend+1))&0ffh,w
	movf	((___almod@divisor+2))&0ffh,w
	subwfb	((___almod@dividend+2))&0ffh,w
	movf	((___almod@divisor+3))&0ffh,w
	subwfb	((___almod@dividend+3))&0ffh,w
	btfss	status,0
	goto	u3671
	goto	u3670

u3671:
	goto	l4795
u3670:
	line	27
	
l4793:; BSR set to: 0

	movf	((___almod@divisor))&0ffh,w
	subwf	((___almod@dividend))&0ffh
	movf	((___almod@divisor+1))&0ffh,w
	subwfb	((___almod@dividend+1))&0ffh
	movf	((___almod@divisor+2))&0ffh,w
	subwfb	((___almod@dividend+2))&0ffh
	movf	((___almod@divisor+3))&0ffh,w
	subwfb	((___almod@dividend+3))&0ffh
	line	28
	
l4795:; BSR set to: 0

	bcf	status,0
	rrcf	((___almod@divisor+3))&0ffh
	rrcf	((___almod@divisor+2))&0ffh
	rrcf	((___almod@divisor+1))&0ffh
	rrcf	((___almod@divisor))&0ffh
	line	29
	
l4797:; BSR set to: 0

	decfsz	((___almod@counter))&0ffh
	
	goto	l4791
	line	31
	
l4799:; BSR set to: 0

	movf	((___almod@sign))&0ffh,w
	btfsc	status,2
	goto	u3681
	goto	u3680
u3681:
	goto	l4803
u3680:
	line	32
	
l4801:; BSR set to: 0

	comf	((___almod@dividend+3))&0ffh
	comf	((___almod@dividend+2))&0ffh
	comf	((___almod@dividend+1))&0ffh
	negf	((___almod@dividend))&0ffh
	movlw	0
	addwfc	((___almod@dividend+1))&0ffh
	addwfc	((___almod@dividend+2))&0ffh
	addwfc	((___almod@dividend+3))&0ffh
	line	33
	
l4803:; BSR set to: 0

	movff	(___almod@dividend),(?___almod)
	movff	(___almod@dividend+1),(?___almod+1)
	movff	(___almod@dividend+2),(?___almod+2)
	movff	(___almod@dividend+3),(?___almod+3)
	line	34
	
l1423:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___almod
	__end_of___almod:
	signat	___almod,8316
	global	___aldiv

;; *************** function ___aldiv *****************
;; Defined at:
;;		line 7 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\aldiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        4    0[BANK0 ] long 
;;  divisor         4    4[BANK0 ] long 
;; Auto vars:     Size  Location     Type
;;  quotient        4   10[BANK0 ] long 
;;  sign            1    9[BANK0 ] unsigned char 
;;  counter         1    8[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[BANK0 ] long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0      14       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_FLOAT_TO_STRING
;; This function uses a non-reentrant model
;;
psect	text22,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\aldiv.c"
	line	7
global __ptext22
__ptext22:
psect	text22
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\aldiv.c"
	line	7
	global	__size_of___aldiv
	__size_of___aldiv	equ	__end_of___aldiv-___aldiv
	
___aldiv:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	13
	
l4727:; BSR set to: 0

	movlw	low(0)
	movwf	((___aldiv@sign))&0ffh
	line	14
	
l4729:; BSR set to: 0

	btfsc	((___aldiv@divisor+3))&0ffh,7
	goto	u3570
	goto	u3571

u3571:
	goto	l4735
u3570:
	line	15
	
l4731:; BSR set to: 0

	comf	((___aldiv@divisor+3))&0ffh
	comf	((___aldiv@divisor+2))&0ffh
	comf	((___aldiv@divisor+1))&0ffh
	negf	((___aldiv@divisor))&0ffh
	movlw	0
	addwfc	((___aldiv@divisor+1))&0ffh
	addwfc	((___aldiv@divisor+2))&0ffh
	addwfc	((___aldiv@divisor+3))&0ffh
	line	16
	
l4733:; BSR set to: 0

	movlw	low(01h)
	movwf	((___aldiv@sign))&0ffh
	line	18
	
l4735:; BSR set to: 0

	btfsc	((___aldiv@dividend+3))&0ffh,7
	goto	u3580
	goto	u3581

u3581:
	goto	l4741
u3580:
	line	19
	
l4737:; BSR set to: 0

	comf	((___aldiv@dividend+3))&0ffh
	comf	((___aldiv@dividend+2))&0ffh
	comf	((___aldiv@dividend+1))&0ffh
	negf	((___aldiv@dividend))&0ffh
	movlw	0
	addwfc	((___aldiv@dividend+1))&0ffh
	addwfc	((___aldiv@dividend+2))&0ffh
	addwfc	((___aldiv@dividend+3))&0ffh
	line	20
	
l4739:; BSR set to: 0

	movlw	(01h)&0ffh
	xorwf	((___aldiv@sign))&0ffh
	line	22
	
l4741:; BSR set to: 0

	movlw	low(0)
	movwf	((___aldiv@quotient))&0ffh
	movlw	high(0)
	movwf	((___aldiv@quotient+1))&0ffh
	movlw	low highword(0)
	movwf	((___aldiv@quotient+2))&0ffh
	movlw	high highword(0)
	movwf	((___aldiv@quotient+3))&0ffh
	line	23
	
l4743:; BSR set to: 0

	movf	((___aldiv@divisor))&0ffh,w
iorwf	((___aldiv@divisor+1))&0ffh,w
iorwf	((___aldiv@divisor+2))&0ffh,w
iorwf	((___aldiv@divisor+3))&0ffh,w
	btfsc	status,2
	goto	u3591
	goto	u3590

u3591:
	goto	l4763
u3590:
	line	24
	
l4745:; BSR set to: 0

	movlw	low(01h)
	movwf	((___aldiv@counter))&0ffh
	line	25
	goto	l4749
	line	26
	
l4747:; BSR set to: 0

	bcf	status,0
	rlcf	((___aldiv@divisor))&0ffh
	rlcf	((___aldiv@divisor+1))&0ffh
	rlcf	((___aldiv@divisor+2))&0ffh
	rlcf	((___aldiv@divisor+3))&0ffh
	line	27
	incf	((___aldiv@counter))&0ffh
	line	25
	
l4749:; BSR set to: 0

	
	btfss	((___aldiv@divisor+3))&0ffh,(31)&7
	goto	u3601
	goto	u3600
u3601:
	goto	l4747
u3600:
	line	30
	
l4751:; BSR set to: 0

	bcf	status,0
	rlcf	((___aldiv@quotient))&0ffh
	rlcf	((___aldiv@quotient+1))&0ffh
	rlcf	((___aldiv@quotient+2))&0ffh
	rlcf	((___aldiv@quotient+3))&0ffh
	line	31
	
l4753:; BSR set to: 0

		movf	((___aldiv@divisor))&0ffh,w
	subwf	((___aldiv@dividend))&0ffh,w
	movf	((___aldiv@divisor+1))&0ffh,w
	subwfb	((___aldiv@dividend+1))&0ffh,w
	movf	((___aldiv@divisor+2))&0ffh,w
	subwfb	((___aldiv@dividend+2))&0ffh,w
	movf	((___aldiv@divisor+3))&0ffh,w
	subwfb	((___aldiv@dividend+3))&0ffh,w
	btfss	status,0
	goto	u3611
	goto	u3610

u3611:
	goto	l4759
u3610:
	line	32
	
l4755:; BSR set to: 0

	movf	((___aldiv@divisor))&0ffh,w
	subwf	((___aldiv@dividend))&0ffh
	movf	((___aldiv@divisor+1))&0ffh,w
	subwfb	((___aldiv@dividend+1))&0ffh
	movf	((___aldiv@divisor+2))&0ffh,w
	subwfb	((___aldiv@dividend+2))&0ffh
	movf	((___aldiv@divisor+3))&0ffh,w
	subwfb	((___aldiv@dividend+3))&0ffh
	line	33
	
l4757:; BSR set to: 0

	bsf	(0+(0/8)+(___aldiv@quotient))&0ffh,(0)&7
	line	35
	
l4759:; BSR set to: 0

	bcf	status,0
	rrcf	((___aldiv@divisor+3))&0ffh
	rrcf	((___aldiv@divisor+2))&0ffh
	rrcf	((___aldiv@divisor+1))&0ffh
	rrcf	((___aldiv@divisor))&0ffh
	line	36
	
l4761:; BSR set to: 0

	decfsz	((___aldiv@counter))&0ffh
	
	goto	l4751
	line	38
	
l4763:; BSR set to: 0

	movf	((___aldiv@sign))&0ffh,w
	btfsc	status,2
	goto	u3621
	goto	u3620
u3621:
	goto	l4767
u3620:
	line	39
	
l4765:; BSR set to: 0

	comf	((___aldiv@quotient+3))&0ffh
	comf	((___aldiv@quotient+2))&0ffh
	comf	((___aldiv@quotient+1))&0ffh
	negf	((___aldiv@quotient))&0ffh
	movlw	0
	addwfc	((___aldiv@quotient+1))&0ffh
	addwfc	((___aldiv@quotient+2))&0ffh
	addwfc	((___aldiv@quotient+3))&0ffh
	line	40
	
l4767:; BSR set to: 0

	movff	(___aldiv@quotient),(?___aldiv)
	movff	(___aldiv@quotient+1),(?___aldiv+1)
	movff	(___aldiv@quotient+2),(?___aldiv+2)
	movff	(___aldiv@quotient+3),(?___aldiv+3)
	line	41
	
l1410:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of___aldiv
	__end_of___aldiv:
	signat	___aldiv,8316
	global	_FCD_049e1_LCD_BL0169__PrintString

;; *************** function _FCD_049e1_LCD_BL0169__PrintString *****************
;; Defined at:
;;		line 3157 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_TEXT        2   16[BANK0 ] PTR unsigned char 
;;		 -> STR_7(3), STR_6(5), STR_5(3), STR_4(8), 
;;		 -> STR_3(3), STR_2(10), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(10), 
;;  FCLsz_TEXT      2   18[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_04071_LCD1__PrintString
;; This function is called by:
;;		_FCD_049e1_LCD_BL0169__PrintFloat
;;		_FCM_update_display
;; This function uses a non-reentrant model
;;
psect	text23,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	3157
global __ptext23
__ptext23:
psect	text23
	file	"feedback control - PIC.c"
	line	3157
	global	__size_of_FCD_049e1_LCD_BL0169__PrintString
	__size_of_FCD_049e1_LCD_BL0169__PrintString	equ	__end_of_FCD_049e1_LCD_BL0169__PrintString-_FCD_049e1_LCD_BL0169__PrintString
	
_FCD_049e1_LCD_BL0169__PrintString:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	3160
	
l5151:; BSR set to: 0

		movff	(FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT),(FCD_04071_LCD1__PrintString@FCL_TEXT)
	movff	(FCD_049e1_LCD_BL0169__PrintString@FCL_TEXT+1),(FCD_04071_LCD1__PrintString@FCL_TEXT+1)

	movff	(FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT),(FCD_04071_LCD1__PrintString@FCLsz_TEXT)
	movff	(FCD_049e1_LCD_BL0169__PrintString@FCLsz_TEXT+1),(FCD_04071_LCD1__PrintString@FCLsz_TEXT+1)
	call	_FCD_04071_LCD1__PrintString	;wreg free
	line	3162
	
l1238:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__PrintString
	__end_of_FCD_049e1_LCD_BL0169__PrintString:
	signat	_FCD_049e1_LCD_BL0169__PrintString,8313
	global	_FCD_04071_LCD1__PrintString

;; *************** function _FCD_04071_LCD1__PrintString *****************
;; Defined at:
;;		line 2529 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_TEXT        2    8[BANK0 ] PTR unsigned char 
;;		 -> STR_7(3), STR_6(5), STR_5(3), STR_4(8), 
;;		 -> STR_3(3), STR_2(10), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(10), FCD_04071_LCD1__PrintFloat@FCL_S(10), 
;;		 -> FCD_04071_LCD1__PrintFormattedNumber@FCL_S(15), FCD_04071_LCD1__PrintNumber@FCL_S(10), 
;;  FCLsz_TEXT      2   10[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;  FCL_IDX         1   15[BANK0 ] unsigned char 
;;  FCL_COUNT       1   14[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FCD_04071_LCD1__RawSend
;;		_FCI_GETLENGTH
;; This function is called by:
;;		_FCD_04071_LCD1__PrintNumber
;;		_FCD_049e1_LCD_BL0169__PrintString
;; This function uses a non-reentrant model
;;
psect	text24,class=CODE,space=0,reloc=2,group=0
	line	2529
global __ptext24
__ptext24:
psect	text24
	file	"feedback control - PIC.c"
	line	2529
	global	__size_of_FCD_04071_LCD1__PrintString
	__size_of_FCD_04071_LCD1__PrintString	equ	__end_of_FCD_04071_LCD1__PrintString-_FCD_04071_LCD1__PrintString
	
_FCD_04071_LCD1__PrintString:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	2532
	
l4717:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__PrintString@FCL_IDX))&0ffh
	line	2536
	
l4719:; BSR set to: 0

		movff	(FCD_04071_LCD1__PrintString@FCL_TEXT),(FCI_GETLENGTH@sStr1)
	movff	(FCD_04071_LCD1__PrintString@FCL_TEXT+1),(FCI_GETLENGTH@sStr1+1)

	movff	(FCD_04071_LCD1__PrintString@FCLsz_TEXT),(FCI_GETLENGTH@iStr1_len)
	movff	(FCD_04071_LCD1__PrintString@FCLsz_TEXT+1),(FCI_GETLENGTH@iStr1_len+1)
	call	_FCI_GETLENGTH	;wreg free
	movlb	0	; () banked
	movf	(0+?_FCI_GETLENGTH)&0ffh,w
	movwf	((FCD_04071_LCD1__PrintString@FCL_COUNT))&0ffh
	line	2538
	goto	l4725
	line	2545
	
l4721:; BSR set to: 0

	movlw	low(010h)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movf	((FCD_04071_LCD1__PrintString@FCL_IDX))&0ffh,w
	addwf	((FCD_04071_LCD1__PrintString@FCL_TEXT))&0ffh,w
	movwf	(??_FCD_04071_LCD1__PrintString+0+0)&0ffh
	movlw	0
	addwfc	((FCD_04071_LCD1__PrintString@FCL_TEXT+1))&0ffh,w
	movwf	(??_FCD_04071_LCD1__PrintString+0+0+1)&0ffh
	movff	??_FCD_04071_LCD1__PrintString+0+0,tblptrl
	movff	??_FCD_04071_LCD1__PrintString+0+1,tblptrh
	movlw	low highword(__mediumconst)
	movwf	tblptru
	
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u3557
	tblrd	*
	
	movf	tablat,w
	bra	u3550
u3557:
	movff	tblptrl,fsr0l
	movff	tblptrh,fsr0h
	movf	indf0,w
u3550:
	
	call	_FCD_04071_LCD1__RawSend
	line	2549
	
l4723:; BSR set to: 0

	incf	((FCD_04071_LCD1__PrintString@FCL_IDX))&0ffh,w
	movwf	((FCD_04071_LCD1__PrintString@FCL_IDX))&0ffh
	line	2538
	
l4725:; BSR set to: 0

		movf	((FCD_04071_LCD1__PrintString@FCL_COUNT))&0ffh,w
	subwf	((FCD_04071_LCD1__PrintString@FCL_IDX))&0ffh,w
	btfss	status,0
	goto	u3561
	goto	u3560

u3561:
	goto	l4721
u3560:
	line	2555
	
l1049:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__PrintString
	__end_of_FCD_04071_LCD1__PrintString:
	signat	_FCD_04071_LCD1__PrintString,8313
	global	_FCI_GETLENGTH

;; *************** function _FCI_GETLENGTH *****************
;; Defined at:
;;		line 150 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
;; Parameters:    Size  Location     Type
;;  sStr1           2    0[BANK0 ] PTR unsigned char 
;;		 -> STR_7(3), STR_6(5), STR_5(3), STR_4(8), 
;;		 -> STR_3(3), STR_2(10), FCD_049e1_LCD_BL0169__PrintFloat@FCL_S(10), FCD_04071_LCD1__PrintFloat@FCL_S(10), 
;;		 -> FCD_04071_LCD1__PrintFormattedNumber@FCL_S(15), FCD_04071_LCD1__PrintNumber@FCL_S(10), FCI_INTTOFORMATTEDSTRING@sTemp(20), FCI_FLOATTOFORMATTEDSTRING@sTemp(20), 
;;  iStr1_len       2    2[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;  tmp             2    6[BANK0 ] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    0[BANK0 ] unsigned short 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, tblptrl, tblptrh, tblptru
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       4       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       8       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_04071_LCD1__PrintString
;; This function uses a non-reentrant model
;;
psect	text25,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	150
global __ptext25
__ptext25:
psect	text25
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	150
	global	__size_of_FCI_GETLENGTH
	__size_of_FCI_GETLENGTH	equ	__end_of_FCI_GETLENGTH-_FCI_GETLENGTH
	
_FCI_GETLENGTH:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	153
	
l4081:; BSR set to: 0

	movlw	high(0)
	movwf	((FCI_GETLENGTH@tmp+1))&0ffh
	movlw	low(0)
	movwf	((FCI_GETLENGTH@tmp))&0ffh
	goto	l4089
	
l4083:; BSR set to: 0

	movf	((FCI_GETLENGTH@tmp))&0ffh,w
	addwf	((FCI_GETLENGTH@sStr1))&0ffh,w
	movwf	(??_FCI_GETLENGTH+0+0)&0ffh
	movf	((FCI_GETLENGTH@tmp+1))&0ffh,w
	addwfc	((FCI_GETLENGTH@sStr1+1))&0ffh,w
	movwf	(??_FCI_GETLENGTH+0+0+1)&0ffh
	movff	??_FCI_GETLENGTH+0+0,tblptrl
	movff	??_FCI_GETLENGTH+0+1,tblptrh
	movlw	low highword(__mediumconst)
	movwf	tblptru
	
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u2617
	tblrd	*
	
	movf	tablat,w
	bra	u2610
u2617:
	movff	tblptrl,fsr0l
	movff	tblptrh,fsr0h
	movf	indf0,w
u2610:
	iorlw	0
	btfss	status,2
	goto	u2621
	goto	u2620
u2621:
	goto	l4087
u2620:
	goto	l193
	
l4087:
	movlb	0	; () banked
	infsnz	((FCI_GETLENGTH@tmp))&0ffh
	incf	((FCI_GETLENGTH@tmp+1))&0ffh
	
l4089:; BSR set to: 0

		movf	((FCI_GETLENGTH@iStr1_len))&0ffh,w
	subwf	((FCI_GETLENGTH@tmp))&0ffh,w
	movf	((FCI_GETLENGTH@iStr1_len+1))&0ffh,w
	subwfb	((FCI_GETLENGTH@tmp+1))&0ffh,w
	btfss	status,0
	goto	u2631
	goto	u2630

u2631:
	goto	l4083
u2630:
	
l193:
	line	154
	movff	(FCI_GETLENGTH@tmp),(?_FCI_GETLENGTH)
	movff	(FCI_GETLENGTH@tmp+1),(?_FCI_GETLENGTH+1)
	line	155
	
l194:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCI_GETLENGTH
	__end_of_FCI_GETLENGTH:
	signat	_FCI_GETLENGTH,8314
	global	_FCD_049e1_LCD_BL0169__Cursor

;; *************** function _FCD_049e1_LCD_BL0169__Cursor *****************
;; Defined at:
;;		line 3231 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_X           1    wreg     unsigned char 
;;  FCL_Y           1    6[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_X           1    7[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_04071_LCD1__Cursor
;; This function is called by:
;;		_FCM_update_display
;; This function uses a non-reentrant model
;;
psect	text26,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	3231
global __ptext26
__ptext26:
psect	text26
	file	"feedback control - PIC.c"
	line	3231
	global	__size_of_FCD_049e1_LCD_BL0169__Cursor
	__size_of_FCD_049e1_LCD_BL0169__Cursor	equ	__end_of_FCD_049e1_LCD_BL0169__Cursor-_FCD_049e1_LCD_BL0169__Cursor
	
_FCD_049e1_LCD_BL0169__Cursor:
;incstack = 0
	opt	callstack 22
	movwf	((FCD_049e1_LCD_BL0169__Cursor@FCL_X))&0ffh
	line	3234
	
l5581:
	movff	(FCD_049e1_LCD_BL0169__Cursor@FCL_Y),(FCD_04071_LCD1__Cursor@FCL_Y)
	movlb	0	; () banked
	movf	((FCD_049e1_LCD_BL0169__Cursor@FCL_X))&0ffh,w
	
	call	_FCD_04071_LCD1__Cursor
	line	3236
	
l1253:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__Cursor
	__end_of_FCD_049e1_LCD_BL0169__Cursor:
	signat	_FCD_049e1_LCD_BL0169__Cursor,8313
	global	_FCD_04071_LCD1__Cursor

;; *************** function _FCD_04071_LCD1__Cursor *****************
;; Defined at:
;;		line 2680 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_X           1    wreg     unsigned char 
;;  FCL_Y           1    4[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_X           1    5[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FCD_04071_LCD1__RawSend
;;		_delay_ms
;; This function is called by:
;;		_FCD_049e1_LCD_BL0169__Cursor
;; This function uses a non-reentrant model
;;
psect	text27,class=CODE,space=0,reloc=2,group=0
	line	2680
global __ptext27
__ptext27:
psect	text27
	file	"feedback control - PIC.c"
	line	2680
	global	__size_of_FCD_04071_LCD1__Cursor
	__size_of_FCD_04071_LCD1__Cursor	equ	__end_of_FCD_04071_LCD1__Cursor-_FCD_04071_LCD1__Cursor
	
_FCD_04071_LCD1__Cursor:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	movwf	((FCD_04071_LCD1__Cursor@FCL_X))&0ffh
	line	2698
	
l5129:
	movlb	0	; () banked
	movf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh,w
	btfss	status,2
	goto	u4131
	goto	u4130
u4131:
	goto	l5133
u4130:
	line	2701
	
l5131:; BSR set to: 0

	movlw	low(080h)
	movwf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh
	line	2703
	goto	l5143
	line	2705
	
l5133:; BSR set to: 0

		decf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh,w
	btfss	status,2
	goto	u4141
	goto	u4140

u4141:
	goto	l5137
u4140:
	line	2708
	
l5135:; BSR set to: 0

	movlw	low(0C0h)
	movwf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh
	line	2710
	goto	l5143
	line	2716
	
l5137:; BSR set to: 0

		movlw	2
	xorwf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh,w
	btfss	status,2
	goto	u4151
	goto	u4150

u4151:
	goto	l5141
u4150:
	line	2719
	
l5139:; BSR set to: 0

	movlw	low(094h)
	movwf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh
	line	2721
	goto	l5143
	line	2723
	
l5141:; BSR set to: 0

	movlw	low(0D4h)
	movwf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh
	line	2741
	
l5143:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh,w
	addwf	((FCD_04071_LCD1__Cursor@FCL_X))&0ffh,w
	
	call	_FCD_04071_LCD1__RawSend
	line	2743
	
l5145:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	2748
	
l5147:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movf	((FCD_04071_LCD1__Cursor@FCL_Y))&0ffh,w
	addwf	((FCD_04071_LCD1__Cursor@FCL_X))&0ffh,w
	
	call	_FCD_04071_LCD1__RawSend
	line	2750
	
l5149:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	2752
	
l1074:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__Cursor
	__end_of_FCD_04071_LCD1__Cursor:
	signat	_FCD_04071_LCD1__Cursor,8313
	global	_FCD_049e1_LCD_BL0169__Start

;; *************** function _FCD_049e1_LCD_BL0169__Start *****************
;; Defined at:
;;		line 3328 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    8
;; This function calls:
;;		_FCD_04071_LCD1__Start
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text28,class=CODE,space=0,reloc=2,group=0
	line	3328
global __ptext28
__ptext28:
psect	text28
	file	"feedback control - PIC.c"
	line	3328
	global	__size_of_FCD_049e1_LCD_BL0169__Start
	__size_of_FCD_049e1_LCD_BL0169__Start	equ	__end_of_FCD_049e1_LCD_BL0169__Start-_FCD_049e1_LCD_BL0169__Start
	
_FCD_049e1_LCD_BL0169__Start:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	3331
	
l5687:; BSR set to: 14

	call	_FCD_04071_LCD1__Start	;wreg free
	line	3333
	
l1271:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__Start
	__end_of_FCD_049e1_LCD_BL0169__Start:
	signat	_FCD_049e1_LCD_BL0169__Start,89
	global	_FCD_04071_LCD1__Start

;; *************** function _FCD_04071_LCD1__Start *****************
;; Defined at:
;;		line 3047 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_04071_LCD1__Clear
;;		_FCD_04071_LCD1__RawSend
;;		_delay_ms
;; This function is called by:
;;		_FCD_049e1_LCD_BL0169__Start
;; This function uses a non-reentrant model
;;
psect	text29,class=CODE,space=0,reloc=2,group=0
	line	3047
global __ptext29
__ptext29:
psect	text29
	file	"feedback control - PIC.c"
	line	3047
	global	__size_of_FCD_04071_LCD1__Start
	__size_of_FCD_04071_LCD1__Start	equ	__end_of_FCD_04071_LCD1__Start-_FCD_04071_LCD1__Start
	
_FCD_04071_LCD1__Start:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	3055
	
l5507:; BSR set to: 14

	bcf	(0+(0/8)+(c:3970))^0f00h,c,(0)&7	;volatile
	
l5511:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FEh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3056
	
l5513:; BSR set to: 14

	bcf	(0+(1/8)+(c:3970))^0f00h,c,(1)&7	;volatile
	
l5517:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3057
	
l5519:; BSR set to: 14

	bcf	(0+(2/8)+(c:3970))^0f00h,c,(2)&7	;volatile
	
l5523:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3058
	
l5525:; BSR set to: 14

	bcf	(0+(3/8)+(c:3970))^0f00h,c,(3)&7	;volatile
	
l5529:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3059
	
l5531:; BSR set to: 14

	bcf	(0+(4/8)+(c:3970))^0f00h,c,(4)&7	;volatile
	
l5535:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0EFh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3060
	
l5537:; BSR set to: 14

	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l5541:; BSR set to: 14

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0DFh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	3081
	
l5543:; BSR set to: 14

	movlw	(0Ch)&0ffh
	
	call	_delay_ms
	line	3083
	
l5545:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(033h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3085
	
l5547:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3087
	
l5549:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(033h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3089
	
l5551:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3094
	
l5553:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(032h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3096
	
l5555:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3098
	
l5557:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(02Ch)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3102
	
l5559:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3104
	
l5561:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(06h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3106
	
l5563:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3108
	
l5565:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(0Ch)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3110
	
l5567:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3112
	
l5569:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(01h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3114
	
l5571:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3116
	
l5573:; BSR set to: 0

	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(02h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	3118
	
l5575:; BSR set to: 0

	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	3120
	
l5577:; BSR set to: 0

	call	_FCD_04071_LCD1__Clear	;wreg free
	line	3127
	
l1232:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__Start
	__end_of_FCD_04071_LCD1__Start:
	signat	_FCD_04071_LCD1__Start,89
	global	_FCD_049e1_LCD_BL0169__Clear

;; *************** function _FCD_049e1_LCD_BL0169__Clear *****************
;; Defined at:
;;		line 3144 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_04071_LCD1__Clear
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text30,class=CODE,space=0,reloc=2,group=0
	line	3144
global __ptext30
__ptext30:
psect	text30
	file	"feedback control - PIC.c"
	line	3144
	global	__size_of_FCD_049e1_LCD_BL0169__Clear
	__size_of_FCD_049e1_LCD_BL0169__Clear	equ	__end_of_FCD_049e1_LCD_BL0169__Clear-_FCD_049e1_LCD_BL0169__Clear
	
_FCD_049e1_LCD_BL0169__Clear:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	3147
	
l5685:; BSR set to: 14

	call	_FCD_04071_LCD1__Clear	;wreg free
	line	3149
	
l1235:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_049e1_LCD_BL0169__Clear
	__end_of_FCD_049e1_LCD_BL0169__Clear:
	signat	_FCD_049e1_LCD_BL0169__Clear,89
	global	_FCD_04071_LCD1__Clear

;; *************** function _FCD_04071_LCD1__Clear *****************
;; Defined at:
;;		line 2504 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 31/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FCD_04071_LCD1__RawSend
;;		_delay_ms
;; This function is called by:
;;		_FCD_04071_LCD1__Start
;;		_FCD_049e1_LCD_BL0169__Clear
;; This function uses a non-reentrant model
;;
psect	text31,class=CODE,space=0,reloc=2,group=0
	line	2504
global __ptext31
__ptext31:
psect	text31
	file	"feedback control - PIC.c"
	line	2504
	global	__size_of_FCD_04071_LCD1__Clear
	__size_of_FCD_04071_LCD1__Clear	equ	__end_of_FCD_04071_LCD1__Clear-_FCD_04071_LCD1__Clear
	
_FCD_04071_LCD1__Clear:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	line	2513
	
l5123:
	movlw	low(0)
	movlb	0	; () banked
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(01h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	2515
	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	2517
	movlw	low(0)
	movwf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh
	movlw	(02h)&0ffh
	
	call	_FCD_04071_LCD1__RawSend
	line	2519
	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	2521
	
l1043:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__Clear
	__end_of_FCD_04071_LCD1__Clear:
	signat	_FCD_04071_LCD1__Clear,89
	global	_delay_ms

;; *************** function _delay_ms *****************
;; Defined at:
;;		line 105 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_delay_s
;;		_FCD_04071_LCD1__Clear
;;		_FCD_04071_LCD1__Cursor
;;		_FCD_04071_LCD1__Start
;;		_main
;; This function uses a non-reentrant model
;;
psect	text32,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
global __ptext32
__ptext32:
psect	text32
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:; BSR set to: 0

;incstack = 0
	opt	callstack 25
	movlb	0	; () banked
	movwf	((delay_ms@del))&0ffh
	line	107
	
l4639:
	goto	l4643
	line	109
	
l4641:; BSR set to: 0

	opt asmopt_push
opt asmopt_off
movlw	21
	movlb	0	; () banked
movwf	(??_delay_ms+0+0)&0ffh,f
	movlw	198
u5097:
decfsz	wreg,f
	bra	u5097
	decfsz	(??_delay_ms+0+0)&0ffh,f
	bra	u5097
	nop
opt asmopt_pop

	line	107
	
l4643:
	movlb	0	; () banked
	decf	((delay_ms@del))&0ffh
		incf	((delay_ms@del))&0ffh,w
	btfss	status,2
	goto	u3421
	goto	u3420

u3421:
	goto	l4641
u3420:
	line	111
	
l128:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4217
	global	_FCD_04071_LCD1__RawSend

;; *************** function _FCD_04071_LCD1__RawSend *****************
;; Defined at:
;;		line 2859 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_DATA        1    wreg     unsigned char 
;;  FCL_TYPE        1    1[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_DATA        1    2[BANK0 ] unsigned char 
;;  FCL_NIBBLE      1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_delay_us
;; This function is called by:
;;		_FCD_04071_LCD1__Clear
;;		_FCD_04071_LCD1__PrintString
;;		_FCD_04071_LCD1__Cursor
;;		_FCD_04071_LCD1__Start
;; This function uses a non-reentrant model
;;
psect	text33,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	2859
global __ptext33
__ptext33:
psect	text33
	file	"feedback control - PIC.c"
	line	2859
	global	__size_of_FCD_04071_LCD1__RawSend
	__size_of_FCD_04071_LCD1__RawSend	equ	__end_of_FCD_04071_LCD1__RawSend-_FCD_04071_LCD1__RawSend
	
_FCD_04071_LCD1__RawSend:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	movlb	0	; () banked
	movwf	((FCD_04071_LCD1__RawSend@FCL_DATA))&0ffh
	line	2869
	
l4091:
	bcf	(0+(0/8)+(c:3970))^0f00h,c,(0)&7	;volatile
	
l4095:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FEh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2870
	
l4097:
	bcf	(0+(1/8)+(c:3970))^0f00h,c,(1)&7	;volatile
	
l4101:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2871
	
l4103:
	bcf	(0+(2/8)+(c:3970))^0f00h,c,(2)&7	;volatile
	
l4107:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2872
	
l4109:
	bcf	(0+(3/8)+(c:3970))^0f00h,c,(3)&7	;volatile
	
l4113:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2873
	
l4115:
	bcf	(0+(4/8)+(c:3970))^0f00h,c,(4)&7	;volatile
	
l4119:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0EFh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2874
	
l4121:
	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l4125:
	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0DFh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1117:
	line	2881
	movlb	0	; () banked
	swapf	((FCD_04071_LCD1__RawSend@FCL_DATA))&0ffh,w
	andlw	(0ffh shr 4) & 0ffh
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2882
	
l4127:; BSR set to: 0

	bcf	(0+(0/8)+(c:3970))^0f00h,c,(0)&7	;volatile
	
l4129:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2641
	goto	u2640
u2641:
	goto	l4133
u2640:
	
l4131:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(01h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1121
	
l4133:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FEh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1121:; BSR set to: 0

	line	2883
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2884
	
l4135:; BSR set to: 0

	bcf	(0+(1/8)+(c:3970))^0f00h,c,(1)&7	;volatile
	
l4137:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2651
	goto	u2650
u2651:
	goto	l4141
u2650:
	
l4139:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(02h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1125
	
l4141:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1125:; BSR set to: 0

	line	2885
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2886
	
l4143:; BSR set to: 0

	bcf	(0+(2/8)+(c:3970))^0f00h,c,(2)&7	;volatile
	
l4145:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2661
	goto	u2660
u2661:
	goto	l4149
u2660:
	
l4147:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(04h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1129
	
l4149:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1129:; BSR set to: 0

	line	2887
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2888
	
l4151:; BSR set to: 0

	bcf	(0+(3/8)+(c:3970))^0f00h,c,(3)&7	;volatile
	
l4153:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2671
	goto	u2670
u2671:
	goto	l4157
u2670:
	
l4155:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(08h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l4159
	
l4157:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2910
	
l4159:; BSR set to: 0

	movf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh,w
	btfsc	status,2
	goto	u2681
	goto	u2680
u2681:
	goto	l4167
u2680:
	line	2913
	
l4161:; BSR set to: 0

	bcf	(0+(4/8)+(c:3970))^0f00h,c,(4)&7	;volatile
	
l4163:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(010h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2920
	
l4167:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2922
	
l4169:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2928
	
l4171:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2935
	
l4173:; BSR set to: 0

	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l4175:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(020h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2937
	
l4179:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2939
	
l4181:; BSR set to: 0

	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l4185:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0DFh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2941
	
l4187:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2944
	
l4189:; BSR set to: 0

	bcf	(0+(0/8)+(c:3970))^0f00h,c,(0)&7	;volatile
	
l4193:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FEh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2945
	
l4195:; BSR set to: 0

	bcf	(0+(1/8)+(c:3970))^0f00h,c,(1)&7	;volatile
	
l4199:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2946
	
l4201:; BSR set to: 0

	bcf	(0+(2/8)+(c:3970))^0f00h,c,(2)&7	;volatile
	
l4205:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2947
	
l4207:; BSR set to: 0

	bcf	(0+(3/8)+(c:3970))^0f00h,c,(3)&7	;volatile
	
l4211:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2948
	
l4213:; BSR set to: 0

	bcf	(0+(4/8)+(c:3970))^0f00h,c,(4)&7	;volatile
	
l4217:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0EFh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1166:; BSR set to: 0

	line	2950
	movf	((FCD_04071_LCD1__RawSend@FCL_DATA))&0ffh,w
	andlw	low(0Fh)
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2951
	
l4219:; BSR set to: 0

	bcf	(0+(0/8)+(c:3970))^0f00h,c,(0)&7	;volatile
	
l4221:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2691
	goto	u2690
u2691:
	goto	l4225
u2690:
	
l4223:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(01h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1170
	
l4225:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FEh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1170:; BSR set to: 0

	line	2952
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2953
	
l4227:; BSR set to: 0

	bcf	(0+(1/8)+(c:3970))^0f00h,c,(1)&7	;volatile
	
l4229:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2701
	goto	u2700
u2701:
	goto	l4233
u2700:
	
l4231:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(02h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1174
	
l4233:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1174:; BSR set to: 0

	line	2954
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2955
	
l4235:; BSR set to: 0

	bcf	(0+(2/8)+(c:3970))^0f00h,c,(2)&7	;volatile
	
l4237:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2711
	goto	u2710
u2711:
	goto	l4241
u2710:
	
l4239:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(04h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l1178
	
l4241:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3978))^0f00h,c	;volatile
	
l1178:; BSR set to: 0

	line	2956
	bcf	status,0
	rrcf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,w
	movwf	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh
	line	2957
	
l4243:; BSR set to: 0

	bcf	(0+(3/8)+(c:3970))^0f00h,c,(3)&7	;volatile
	
l4245:; BSR set to: 0

	
	btfss	((FCD_04071_LCD1__RawSend@FCL_NIBBLE))&0ffh,(0)&7
	goto	u2721
	goto	u2720
u2721:
	goto	l4249
u2720:
	
l4247:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(08h)
	movwf	((c:3978))^0f00h,c	;volatile
	goto	l4251
	
l4249:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0F7h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2959
	
l4251:; BSR set to: 0

	movf	((FCD_04071_LCD1__RawSend@FCL_TYPE))&0ffh,w
	btfsc	status,2
	goto	u2731
	goto	u2730
u2731:
	goto	l4259
u2730:
	line	2962
	
l4253:; BSR set to: 0

	bcf	(0+(4/8)+(c:3970))^0f00h,c,(4)&7	;volatile
	
l4255:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(010h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2968
	
l4259:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2970
	
l4261:; BSR set to: 0

	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l4263:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	iorlw	low(020h)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2972
	
l4267:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2974
	
l4269:; BSR set to: 0

	bcf	(0+(5/8)+(c:3970))^0f00h,c,(5)&7	;volatile
	
l4273:; BSR set to: 0

	movf	((c:3962))^0f00h,c,w	;volatile
	andlw	low(0DFh)
	movwf	((c:3978))^0f00h,c	;volatile
	line	2976
	
l4275:; BSR set to: 0

	movlw	(064h)&0ffh
	
	call	_delay_us
	line	2982
	
l1196:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04071_LCD1__RawSend
	__end_of_FCD_04071_LCD1__RawSend:
	signat	_FCD_04071_LCD1__RawSend,8313
	global	_FCD_04891_DCMotor1__Forwards

;; *************** function _FCD_04891_DCMotor1__Forwards *****************
;; Defined at:
;;		line 1625 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_DUTY        2    0[BANK0 ] unsigned short 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text34,class=CODE,space=0,reloc=2,group=0
	line	1625
global __ptext34
__ptext34:
psect	text34
	file	"feedback control - PIC.c"
	line	1625
	global	__size_of_FCD_04891_DCMotor1__Forwards
	__size_of_FCD_04891_DCMotor1__Forwards	equ	__end_of_FCD_04891_DCMotor1__Forwards-_FCD_04891_DCMotor1__Forwards
	
_FCD_04891_DCMotor1__Forwards:; BSR set to: 0

;incstack = 0
	opt	callstack 26
	line	1649
	
l5633:; BSR set to: 0

	movlw	low(0)
	movwf	((_FCV_04891_DCMotor1__SW_PWM_STATE))&0ffh	;volatile
	line	1650
	
l5635:; BSR set to: 0

	movff	(FCD_04891_DCMotor1__Forwards@FCL_DUTY),(_FCV_04891_DCMotor1__SW_PWM_DUTY)	;volatile
	movff	(FCD_04891_DCMotor1__Forwards@FCL_DUTY+1),(_FCV_04891_DCMotor1__SW_PWM_DUTY+1)	;volatile
	line	1661
	
l938:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04891_DCMotor1__Forwards
	__end_of_FCD_04891_DCMotor1__Forwards:
	signat	_FCD_04891_DCMotor1__Forwards,4217
	global	_FCD_04891_DCMotor1__Enable

;; *************** function _FCD_04891_DCMotor1__Enable *****************
;; Defined at:
;;		line 1666 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_00a91_TimedInterval1__StartTimerInterval
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text35,class=CODE,space=0,reloc=2,group=0
	line	1666
global __ptext35
__ptext35:
psect	text35
	file	"feedback control - PIC.c"
	line	1666
	global	__size_of_FCD_04891_DCMotor1__Enable
	__size_of_FCD_04891_DCMotor1__Enable	equ	__end_of_FCD_04891_DCMotor1__Enable-_FCD_04891_DCMotor1__Enable
	
_FCD_04891_DCMotor1__Enable:; BSR set to: 0

;incstack = 0
	opt	callstack 25
	line	1669
	
l5637:; BSR set to: 0

	movlw	low(01h)
	movwf	((c:_FCV_04891_DCMotor1__ENABLED))^00h,c	;volatile
	line	1692
	
l5639:; BSR set to: 0

	call	_FCD_00a91_TimedInterval1__StartTimerInterval	;wreg free
	line	1698
	
l941:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04891_DCMotor1__Enable
	__end_of_FCD_04891_DCMotor1__Enable:
	signat	_FCD_04891_DCMotor1__Enable,89
	global	_FCD_00a91_TimedInterval1__StartTimerInterval

;; *************** function _FCD_00a91_TimedInterval1__StartTimerInterval *****************
;; Defined at:
;;		line 1425 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_04891_DCMotor1__Enable
;; This function uses a non-reentrant model
;;
psect	text36,class=CODE,space=0,reloc=2,group=0
	line	1425
global __ptext36
__ptext36:
psect	text36
	file	"feedback control - PIC.c"
	line	1425
	global	__size_of_FCD_00a91_TimedInterval1__StartTimerInterval
	__size_of_FCD_00a91_TimedInterval1__StartTimerInterval	equ	__end_of_FCD_00a91_TimedInterval1__StartTimerInterval-_FCD_00a91_TimedInterval1__StartTimerInterval
	
_FCD_00a91_TimedInterval1__StartTimerInterval:; BSR set to: 14

;incstack = 0
	opt	callstack 25
	line	1428
	
l5491:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	movlw	high(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+1))^00h,c	;volatile
	movlw	low highword(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+2))^00h,c	;volatile
	movlw	high highword(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+3))^00h,c	;volatile
	line	1432
	
l5493:; BSR set to: 0

	bsf	((c:4082))^0f00h,c,7	;volatile
	
l5495:; BSR set to: 0

	bsf	((c:4082))^0f00h,c,6	;volatile
	
l5497:; BSR set to: 0

	movlb	14	; () banked
	bsf	((3625))&0ffh,5	;volatile
	
l5499:; BSR set to: 14

	movf	((c:4054))^0f00h,c,w	;volatile
	andlw	low(0Fh)
	iorlw	low(040h)
	movwf	((c:4054))^0f00h,c	;volatile
	
l5501:; BSR set to: 14

	movf	((c:4054))^0f00h,c,w	;volatile
	andlw	low(0F0h)
	iorlw	low(04h)
	movwf	((c:4054))^0f00h,c	;volatile
	
l5503:; BSR set to: 14

	movf	((c:4053))^0f00h,c,w	;volatile
	andlw	low(0F0h)
	iorlw	low(080h)
	movwf	((c:4053))^0f00h,c	;volatile
	line	1457
	
l5505:; BSR set to: 14

	movlw	low(01h)
	movwf	((c:_FCV_00a91_TimedInterval1__RUNNING))^00h,c	;volatile
	line	1459
	
l915:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_00a91_TimedInterval1__StartTimerInterval
	__end_of_FCD_00a91_TimedInterval1__StartTimerInterval:
	signat	_FCD_00a91_TimedInterval1__StartTimerInterval,89
	global	_FCD_026e1_Timer1__StartCounter

;; *************** function _FCD_026e1_Timer1__StartCounter *****************
;; Defined at:
;;		line 70 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_RESETCOU    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_RESETCOU    1    2[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_026e1_Timer1__ResetCounter
;;		_FCD_026e1_Timer1__RestoreCounter
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text37,class=CODE,space=0,reloc=2,group=0
	line	70
global __ptext37
__ptext37:
psect	text37
	file	"feedback control - PIC.c"
	line	70
	global	__size_of_FCD_026e1_Timer1__StartCounter
	__size_of_FCD_026e1_Timer1__StartCounter	equ	__end_of_FCD_026e1_Timer1__StartCounter-_FCD_026e1_Timer1__StartCounter
	
_FCD_026e1_Timer1__StartCounter:; BSR set to: 14

;incstack = 0
	opt	callstack 25
	movwf	((FCD_026e1_Timer1__StartCounter@FCL_RESETCOUNTERS))&0ffh
	line	73
	
l5605:
	movlb	0	; () banked
	movf	((FCD_026e1_Timer1__StartCounter@FCL_RESETCOUNTERS))&0ffh,w
	btfsc	status,2
	goto	u4701
	goto	u4700
u4701:
	goto	l5609
u4700:
	line	76
	
l5607:; BSR set to: 0

	call	_FCD_026e1_Timer1__ResetCounter	;wreg free
	line	78
	goto	l5611
	line	80
	
l5609:; BSR set to: 0

	call	_FCD_026e1_Timer1__RestoreCounter	;wreg free
	line	96
	
l5611:; BSR set to: 0

	bsf	((c:4082))^0f00h,c,7	;volatile
	
l5613:; BSR set to: 0

	movf	((c:4029))^0f00h,c,w	;volatile
	andlw	low(0F0h)
	movwf	((c:4029))^0f00h,c	;volatile
	
l5615:; BSR set to: 0

	movf	((c:4029))^0f00h,c,w	;volatile
	andlw	low(0Fh)
	iorlw	low(0F0h)
	movwf	((c:4029))^0f00h,c	;volatile
	
l5617:; BSR set to: 0

	movlw	low(01h)
	movwf	((c:4031))^0f00h,c	;volatile
	
l5619:; BSR set to: 0

	bsf	((c:4082))^0f00h,c,6	;volatile
	
l5621:; BSR set to: 0

	movlb	14	; () banked
	bsf	((3630))&0ffh,1	;volatile
	line	146
	
l5623:; BSR set to: 14

	movlw	low(01h)
	movwf	((c:_FCV_026e1_Timer1__RUNNING))^00h,c	;volatile
	line	148
	
l763:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_026e1_Timer1__StartCounter
	__end_of_FCD_026e1_Timer1__StartCounter:
	signat	_FCD_026e1_Timer1__StartCounter,4217
	global	_FCD_026e1_Timer1__RestoreCounter

;; *************** function _FCD_026e1_Timer1__RestoreCounter *****************
;; Defined at:
;;		line 173 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_COUNTSAV    2    0[BANK0 ] unsigned short 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__StartCounter
;; This function uses a non-reentrant model
;;
psect	text38,class=CODE,space=0,reloc=2,group=0
	line	173
global __ptext38
__ptext38:
psect	text38
	file	"feedback control - PIC.c"
	line	173
	global	__size_of_FCD_026e1_Timer1__RestoreCounter
	__size_of_FCD_026e1_Timer1__RestoreCounter	equ	__end_of_FCD_026e1_Timer1__RestoreCounter-_FCD_026e1_Timer1__RestoreCounter
	
_FCD_026e1_Timer1__RestoreCounter:; BSR set to: 14

;incstack = 0
	opt	callstack 25
	line	182
	
l5469:; BSR set to: 0

	movff	(_FCV_026e1_Timer1__TCOUNTSAVE),(FCD_026e1_Timer1__RestoreCounter@FCL_COUNTSAVE)	;volatile
	movff	(_FCV_026e1_Timer1__TCOUNTSAVE+1),(FCD_026e1_Timer1__RestoreCounter@FCL_COUNTSAVE+1)	;volatile
	line	201
	movff	(FCD_026e1_Timer1__RestoreCounter@FCL_COUNTSAVE),(c:4027)	;volatile
	line	242
	
l5471:; BSR set to: 0

	movlw	high(0)
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE+1))&0ffh	;volatile
	movlw	low(0)
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE))&0ffh	;volatile
	line	246
	
l769:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_026e1_Timer1__RestoreCounter
	__end_of_FCD_026e1_Timer1__RestoreCounter:
	signat	_FCD_026e1_Timer1__RestoreCounter,89
	global	_FCD_026e1_Timer1__ResetCounter

;; *************** function _FCD_026e1_Timer1__ResetCounter *****************
;; Defined at:
;;		line 402 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__StartCounter
;; This function uses a non-reentrant model
;;
psect	text39,class=CODE,space=0,reloc=2,group=0
	line	402
global __ptext39
__ptext39:
psect	text39
	file	"feedback control - PIC.c"
	line	402
	global	__size_of_FCD_026e1_Timer1__ResetCounter
	__size_of_FCD_026e1_Timer1__ResetCounter	equ	__end_of_FCD_026e1_Timer1__ResetCounter-_FCD_026e1_Timer1__ResetCounter
	
_FCD_026e1_Timer1__ResetCounter:; BSR set to: 0

;incstack = 0
	opt	callstack 25
	line	408
	
l5467:; BSR set to: 0

	movlw	high(0)
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE+1))&0ffh	;volatile
	movlw	low(0)
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE))&0ffh	;volatile
	line	422
	movlw	low(01h)
	movwf	((c:4027))^0f00h,c	;volatile
	line	430
	movlw	low(0)
	movwf	((c:_TIM_2_COUNTER))^00h,c
	movlw	high(0)
	movwf	((c:_TIM_2_COUNTER+1))^00h,c
	movlw	low highword(0)
	movwf	((c:_TIM_2_COUNTER+2))^00h,c
	movlw	high highword(0)
	movwf	((c:_TIM_2_COUNTER+3))^00h,c
	line	473
	
l781:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_026e1_Timer1__ResetCounter
	__end_of_FCD_026e1_Timer1__ResetCounter:
	signat	_FCD_026e1_Timer1__ResetCounter,89
	global	_FCD_00a21_Potentiometer1__GetByte

;; *************** function _FCD_00a21_Potentiometer1__GetByte *****************
;; Defined at:
;;		line 1393 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      1    8[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_0cc51_adc_base1__GetByte
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text40,class=CODE,space=0,reloc=2,group=0
	line	1393
global __ptext40
__ptext40:
psect	text40
	file	"feedback control - PIC.c"
	line	1393
	global	__size_of_FCD_00a21_Potentiometer1__GetByte
	__size_of_FCD_00a21_Potentiometer1__GetByte	equ	__end_of_FCD_00a21_Potentiometer1__GetByte-_FCD_00a21_Potentiometer1__GetByte
	
_FCD_00a21_Potentiometer1__GetByte:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	1399
	
l5625:; BSR set to: 0

	line	1401
	
l5627:; BSR set to: 0

	call	_FCD_0cc51_adc_base1__GetByte	;wreg free
	movwf	((FCD_00a21_Potentiometer1__GetByte@FCR_RETVAL))&0ffh
	line	1403
	
l5629:; BSR set to: 0

	movf	((FCD_00a21_Potentiometer1__GetByte@FCR_RETVAL))&0ffh,w
	line	1405
	
l908:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_00a21_Potentiometer1__GetByte
	__end_of_FCD_00a21_Potentiometer1__GetByte:
	signat	_FCD_00a21_Potentiometer1__GetByte,89
	global	_FCD_0cc51_adc_base1__GetByte

;; *************** function _FCD_0cc51_adc_base1__GetByte *****************
;; Defined at:
;;		line 884 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      1    7[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FC_CAL_ADC_Disable_1
;;		_FC_CAL_ADC_Enable_1
;;		_FC_CAL_ADC_Sample_1
;; This function is called by:
;;		_FCD_00a21_Potentiometer1__GetByte
;; This function uses a non-reentrant model
;;
psect	text41,class=CODE,space=0,reloc=2,group=0
	line	884
global __ptext41
__ptext41:
psect	text41
	file	"feedback control - PIC.c"
	line	884
	global	__size_of_FCD_0cc51_adc_base1__GetByte
	__size_of_FCD_0cc51_adc_base1__GetByte	equ	__end_of_FCD_0cc51_adc_base1__GetByte-_FCD_0cc51_adc_base1__GetByte
	
_FCD_0cc51_adc_base1__GetByte:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	line	890
	
l5483:; BSR set to: 0

	movlw	low(01Fh)
	movwf	((FC_CAL_ADC_Enable_1@Conv_Speed))&0ffh
	movlw	low(0)
	movwf	((FC_CAL_ADC_Enable_1@Vref))&0ffh
	movlw	low(028h)
	movwf	((FC_CAL_ADC_Enable_1@T_Charge))&0ffh
	movlw	(01h)&0ffh
	
	call	_FC_CAL_ADC_Enable_1
	line	892
	movlw	(0)&0ffh
	
	call	_FC_CAL_ADC_Sample_1
	movf	(0+?_FC_CAL_ADC_Sample_1)&0ffh,w
	movwf	((FCD_0cc51_adc_base1__GetByte@FCR_RETVAL))&0ffh
	line	894
	
l5485:; BSR set to: 0

	call	_FC_CAL_ADC_Disable_1	;wreg free
	line	896
	
l5487:; BSR set to: 0

	movf	((FCD_0cc51_adc_base1__GetByte@FCR_RETVAL))&0ffh,w
	line	898
	
l841:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_0cc51_adc_base1__GetByte
	__end_of_FCD_0cc51_adc_base1__GetByte:
	signat	_FCD_0cc51_adc_base1__GetByte,89
	global	_FC_CAL_ADC_Sample_1

;; *************** function _FC_CAL_ADC_Sample_1 *****************
;; Defined at:
;;		line 4794 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
;; Parameters:    Size  Location     Type
;;  Sample_Mode     1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Sample_Mode     1    4[BANK0 ] unsigned char 
;;  iRetVal         2    5[BANK0 ] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    0[BANK0 ] unsigned short 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       7       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_0cc51_adc_base1__GetByte
;; This function uses a non-reentrant model
;;
psect	text42,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
	line	4794
global __ptext42
__ptext42:
psect	text42
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
	line	4794
	global	__size_of_FC_CAL_ADC_Sample_1
	__size_of_FC_CAL_ADC_Sample_1	equ	__end_of_FC_CAL_ADC_Sample_1-_FC_CAL_ADC_Sample_1
	
_FC_CAL_ADC_Sample_1:; BSR set to: 0

;incstack = 0
	opt	callstack 24
	movwf	((FC_CAL_ADC_Sample_1@Sample_Mode))&0ffh
	line	4798
	
l5099:
	bsf	(0+(0/8)+(c:3936))^0f00h,c,(0)&7	;volatile
	line	4800
	
l743:
	
	btfsc	((c:3936))^0f00h,c,(0)&7	;volatile
	goto	u4091
	goto	u4090
u4091:
	goto	l743
u4090:
	line	4801
	
l5101:
	movlb	0	; () banked
	movf	((FC_CAL_ADC_Sample_1@Sample_Mode))&0ffh,w
	btfsc	status,2
	goto	u4101
	goto	u4100
u4101:
	goto	l746
u4100:
	line	4807
	
l5103:; BSR set to: 0

	movf	((c:3940))^0f00h,c,w	;volatile
	movwf	(??_FC_CAL_ADC_Sample_1+0+0)&0ffh
	clrf	(??_FC_CAL_ADC_Sample_1+0+0+1)&0ffh

	bcf	status,0
	rlcf	(??_FC_CAL_ADC_Sample_1+0+0)&0ffh
	rlcf	(??_FC_CAL_ADC_Sample_1+0+1)&0ffh
	bcf	status,0
	rlcf	(??_FC_CAL_ADC_Sample_1+0+0)&0ffh
	rlcf	(??_FC_CAL_ADC_Sample_1+0+1)&0ffh
	movff	??_FC_CAL_ADC_Sample_1+0+0,(FC_CAL_ADC_Sample_1@iRetVal)
	movff	??_FC_CAL_ADC_Sample_1+0+1,(FC_CAL_ADC_Sample_1@iRetVal+1)
	line	4808
	
l5105:; BSR set to: 0

	movff	(c:3939),??_FC_CAL_ADC_Sample_1+0+0	;volatile
	movlw	06h
	movwf	(??_FC_CAL_ADC_Sample_1+1+0)&0ffh
u4115:
	bcf	status,0
	rrcf	(??_FC_CAL_ADC_Sample_1+0+0)&0ffh
	decfsz	(??_FC_CAL_ADC_Sample_1+1+0)&0ffh
	goto	u4115
	movf	((FC_CAL_ADC_Sample_1@iRetVal))&0ffh,w
	iorwf	(??_FC_CAL_ADC_Sample_1+0+0)&0ffh,w
	movwf	((FC_CAL_ADC_Sample_1@iRetVal))&0ffh
	movf	((FC_CAL_ADC_Sample_1@iRetVal+1))&0ffh,w
	movwf	1+((FC_CAL_ADC_Sample_1@iRetVal))&0ffh
	line	4810
	goto	l747
	line	4811
	
l746:; BSR set to: 0

	line	4812
	movff	(c:3940),(FC_CAL_ADC_Sample_1@iRetVal)	;volatile
	clrf	((FC_CAL_ADC_Sample_1@iRetVal+1))&0ffh
	
l747:; BSR set to: 0

	line	4814
	movff	(FC_CAL_ADC_Sample_1@iRetVal),(?_FC_CAL_ADC_Sample_1)
	movff	(FC_CAL_ADC_Sample_1@iRetVal+1),(?_FC_CAL_ADC_Sample_1+1)
	line	4815
	
l748:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_ADC_Sample_1
	__end_of_FC_CAL_ADC_Sample_1:
	signat	_FC_CAL_ADC_Sample_1,4218
	global	_FC_CAL_ADC_Enable_1

;; *************** function _FC_CAL_ADC_Enable_1 *****************
;; Defined at:
;;		line 4725 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
;; Parameters:    Size  Location     Type
;;  Channel         1    wreg     unsigned char 
;;  Conv_Speed      1    1[BANK0 ] unsigned char 
;;  Vref            1    2[BANK0 ] unsigned char 
;;  T_Charge        1    3[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  Channel         1    6[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       3       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       6       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_delay_us
;; This function is called by:
;;		_FCD_0cc51_adc_base1__GetByte
;; This function uses a non-reentrant model
;;
psect	text43,class=CODE,space=0,reloc=2,group=0
	line	4725
global __ptext43
__ptext43:
psect	text43
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
	line	4725
	global	__size_of_FC_CAL_ADC_Enable_1
	__size_of_FC_CAL_ADC_Enable_1	equ	__end_of_FC_CAL_ADC_Enable_1-_FC_CAL_ADC_Enable_1
	
_FC_CAL_ADC_Enable_1:; BSR set to: 0

;incstack = 0
	opt	callstack 23
	movwf	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	line	4727
	
l5059:
		movlw	08h-0
	movlb	0	; () banked
	cpfslt	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	goto	u4011
	goto	u4010

u4011:
	goto	l5063
u4010:
	line	4730
	
l5061:; BSR set to: 0

	movff	(FC_CAL_ADC_Enable_1@Channel),??_FC_CAL_ADC_Enable_1+0+0
	movlw	07h
	andwf	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	movlw	(01h)&0ffh
	movwf	(??_FC_CAL_ADC_Enable_1+1+0)&0ffh
	incf	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	goto	u4024
u4025:
	bcf	status,0
	rlcf	((??_FC_CAL_ADC_Enable_1+1+0))&0ffh
u4024:
	decfsz	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	goto	u4025
	movlb	0	; () banked
	movf	((??_FC_CAL_ADC_Enable_1+1+0))&0ffh,w
	iorwf	((c:3969))^0f00h,c	;volatile
	line	4731
	movff	(FC_CAL_ADC_Enable_1@Channel),??_FC_CAL_ADC_Enable_1+0+0
	movlw	07h
	andwf	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	movlw	(01h)&0ffh
	movwf	(??_FC_CAL_ADC_Enable_1+1+0)&0ffh
	incf	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	goto	u4034
u4035:
	bcf	status,0
	rlcf	((??_FC_CAL_ADC_Enable_1+1+0))&0ffh
u4034:
	decfsz	(??_FC_CAL_ADC_Enable_1+0+0)&0ffh
	goto	u4035
	movlb	0	; () banked
	movf	((??_FC_CAL_ADC_Enable_1+1+0))&0ffh,w
	movlb	14	; () banked
	iorwf	((3730))&0ffh	;volatile
	line	4733
	goto	l726
	line	4734
	
l5063:; BSR set to: 0

		movlw	010h-0
	cpfslt	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	goto	u4041
	goto	u4040

u4041:
	goto	l5067
u4040:
	goto	l726
	line	4741
	
l5067:; BSR set to: 0

		movlw	018h-0
	cpfslt	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	goto	u4051
	goto	u4050

u4051:
	goto	l5071
u4050:
	goto	l726
	line	4748
	
l5071:; BSR set to: 0

		movlw	020h-0
	cpfslt	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	goto	u4061
	goto	u4060

u4061:
	goto	l5075
u4060:
	goto	l726
	line	4755
	
l5075:; BSR set to: 0

		movlw	028h-0
	cpfslt	((FC_CAL_ADC_Enable_1@Channel))&0ffh
	goto	u4071
	goto	u4070

u4071:
	goto	l5079
u4070:
	goto	l726
	line	4762
	
l5079:; BSR set to: 0

	line	4777
	
l726:
	movlb	0	; () banked
	
	btfss	((FC_CAL_ADC_Enable_1@Conv_Speed))&0ffh,(6)&7
	goto	u4081
	goto	u4080
u4081:
	goto	l5087
u4080:
	line	4779
	
l5085:; BSR set to: 0

	movlw	low(010h)
	movwf	((c:3936))^0f00h,c	;volatile
	line	4780
	goto	l5091
	line	4783
	
l5087:; BSR set to: 0

	movlw	low(0)
	movwf	((c:3936))^0f00h,c	;volatile
	line	4784
	
l5089:; BSR set to: 0

	movf	((FC_CAL_ADC_Enable_1@Conv_Speed))&0ffh,w
	andlw	low(03Fh)
	movlb	15	; () banked
	movwf	((3927))&0ffh	;volatile
	line	4787
	
l5091:
	movff	(FC_CAL_ADC_Enable_1@Vref),(3928)	;volatile
	line	4788
	
l5093:
	movff	(FC_CAL_ADC_Enable_1@Channel),(3935)	;volatile
	line	4789
	
l5095:
	bsf	(0+(7/8)+(c:3936))^0f00h,c,(7)&7	;volatile
	line	4791
	
l5097:
	movlb	0	; () banked
	movf	((FC_CAL_ADC_Enable_1@T_Charge))&0ffh,w
	
	call	_delay_us
	line	4792
	
l740:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_ADC_Enable_1
	__end_of_FC_CAL_ADC_Enable_1:
	signat	_FC_CAL_ADC_Enable_1,16505
	global	_delay_us

;; *************** function _delay_us *****************
;; Defined at:
;;		line 85 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    0[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FC_CAL_ADC_Enable_1
;;		_FCD_04071_LCD1__RawSend
;; This function uses a non-reentrant model
;;
psect	text44,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	85
global __ptext44
__ptext44:
psect	text44
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	85
	global	__size_of_delay_us
	__size_of_delay_us	equ	__end_of_delay_us-_delay_us
	
_delay_us:; BSR set to: 0

;incstack = 0
	opt	callstack 22
	movwf	((delay_us@del))&0ffh
	line	87
	
l4047:
	goto	l4053
	line	89
	
l4049:; BSR set to: 0

	opt asmopt_push
opt asmopt_off
	movlw	228
u5107:
	nop2
	nop2
decfsz	wreg,f
	bra	u5107
	nop2
	nop2
opt asmopt_pop

	line	90
	
l4051:
	movlw	(064h)&0ffh
	movlb	0	; () banked
	subwf	((delay_us@del))&0ffh
	line	87
	
l4053:
		movlw	064h-0
	movlb	0	; () banked
	cpfslt	((delay_us@del))&0ffh
	goto	u2551
	goto	u2550

u2551:
	goto	l4049
u2550:
	goto	l4059
	line	94
	
l4055:; BSR set to: 0

	opt asmopt_push
opt asmopt_off
	movlw	53
u5117:
decfsz	wreg,f
	bra	u5117
	nop
opt asmopt_pop

	line	95
	
l4057:
	movlw	(0Ah)&0ffh
	movlb	0	; () banked
	subwf	((delay_us@del))&0ffh
	line	92
	
l4059:; BSR set to: 0

		movlw	0Ah-0
	cpfslt	((delay_us@del))&0ffh
	goto	u2561
	goto	u2560

u2561:
	goto	l4055
u2560:
	goto	l4063
	line	99
	
l4061:; BSR set to: 0

	opt asmopt_push
opt asmopt_off
	movlw	5
u5127:
decfsz	wreg,f
	bra	u5127
	nop
opt asmopt_pop

	line	97
	
l4063:
	movlb	0	; () banked
	decf	((delay_us@del))&0ffh
		incf	((delay_us@del))&0ffh,w
	btfss	status,2
	goto	u2571
	goto	u2570

u2571:
	goto	l4061
u2570:
	line	101
	
l122:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_us
	__end_of_delay_us:
	signat	_delay_us,4217
	global	_FC_CAL_ADC_Disable_1

;; *************** function _FC_CAL_ADC_Disable_1 *****************
;; Defined at:
;;		line 4817 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 3F/0
;;		Unchanged: 3F/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_0cc51_adc_base1__GetByte
;; This function uses a non-reentrant model
;;
psect	text45,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
	line	4817
global __ptext45
__ptext45:
psect	text45
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_ADC.c"
	line	4817
	global	__size_of_FC_CAL_ADC_Disable_1
	__size_of_FC_CAL_ADC_Disable_1	equ	__end_of_FC_CAL_ADC_Disable_1-_FC_CAL_ADC_Disable_1
	
_FC_CAL_ADC_Disable_1:; BSR set to: 0

;incstack = 0
	opt	callstack 24
	line	4819
	
l5107:; BSR set to: 0

	movlw	low(0)
	movwf	((c:3936))^0f00h,c	;volatile
	line	4841
	
l751:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_ADC_Disable_1
	__end_of_FC_CAL_ADC_Disable_1:
	signat	_FC_CAL_ADC_Disable_1,89
	global	_myisr

;; *************** function _myisr *****************
;; Defined at:
;;		line 3556 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FCD_04891_DCMotor1__TimerRoutine
;;		_FCM_feedback_interrupt
;; This function is called by:
;;		Interrupt level 2
;; This function uses a non-reentrant model
;;
psect	intcode,class=CODE,space=0,reloc=2
	file	"feedback control - PIC.as"
	line	#
global __pintcode
__pintcode:
psect	intcode
	file	"feedback control - PIC.c"
	line	3556
	global	__size_of_myisr
	__size_of_myisr	equ	__end_of_myisr-_myisr
	
_myisr:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	bsf int$flags,1,c ;set compiler interrupt flag (level 2)
	movff	prodl+0,??_myisr+0
	movff	prodh+0,??_myisr+1
	line	3565
	
i2l5927:
	movlb	14	; () banked
	btfss	((3635))&0ffh,3	;volatile
	goto	i2u501_41
	goto	i2u501_40
i2u501_41:
	goto	i2l5935
i2u501_40:
	
i2l5929:; BSR set to: 14

	btfss	((3625))&0ffh,3	;volatile
	goto	i2u502_41
	goto	i2u502_40
i2u502_41:
	goto	i2l5935
i2u502_40:
	line	3567
	
i2l5931:; BSR set to: 14

	call	_FCM_feedback_interrupt	;wreg free
	line	3568
	
i2l5933:
	movlb	14	; () banked
	bcf	((3635))&0ffh,3	;volatile
	line	3575
	
i2l5935:; BSR set to: 14

	btfss	((3635))&0ffh,5	;volatile
	goto	i2u503_41
	goto	i2u503_40
i2u503_41:
	goto	i2l5951
i2u503_40:
	
i2l5937:; BSR set to: 14

	btfss	((3625))&0ffh,5	;volatile
	goto	i2u504_41
	goto	i2u504_40
i2u504_41:
	goto	i2l5951
i2u504_40:
	line	3576
	
i2l5939:; BSR set to: 14

	movlw	01h
	addwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c,w	;volatile
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	movlw	0
	addwfc	((c:_FCV_00a91_TimedInterval1__INTCOUNT+1))^00h,c,w	;volatile
	movwf	1+((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	
	movlw	0
	addwfc	((c:_FCV_00a91_TimedInterval1__INTCOUNT+2))^00h,c,w	;volatile
	movwf	2+((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	
	movlw	0
	addwfc	((c:_FCV_00a91_TimedInterval1__INTCOUNT+3))^00h,c,w	;volatile
	movwf	3+((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	line	3578
	movf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+1))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+2))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+3))^00h,c,w	;volatile
	btfss	status,2
	goto	i2u505_41
	goto	i2u505_40

i2u505_41:
	goto	i2l5943
i2u505_40:
	line	3588
	
i2l5941:; BSR set to: 14

	movlw	low(0D9h)
	movwf	((c:4051))^0f00h,c	;volatile
	line	3710
	goto	i2l5949
	line	3712
	
i2l5943:; BSR set to: 14

	movf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+1))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+2))^00h,c,w	;volatile
iorwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+3))^00h,c,w	;volatile
	btfsc	status,2
	goto	i2u506_41
	goto	i2u506_40

i2u506_41:
	goto	i2l5949
i2u506_40:
	line	3715
	
i2l5945:; BSR set to: 14

	movlw	low(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT))^00h,c	;volatile
	movlw	high(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+1))^00h,c	;volatile
	movlw	low highword(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+2))^00h,c	;volatile
	movlw	high highword(0)
	movwf	((c:_FCV_00a91_TimedInterval1__INTCOUNT+3))^00h,c	;volatile
	line	3724
	movlw	low(0D9h)
	movwf	((c:4051))^0f00h,c	;volatile
	line	3808
	
i2l5947:; BSR set to: 14

	call	_FCD_04891_DCMotor1__TimerRoutine	;wreg free
	line	3850
	
i2l5949:
	movlb	14	; () banked
	bcf	((3635))&0ffh,5	;volatile
	line	3853
	
i2l5951:; BSR set to: 14

	btfss	((3640))&0ffh,1	;volatile
	goto	i2u507_41
	goto	i2u507_40
i2u507_41:
	goto	i2l1328
i2u507_40:
	
i2l5953:; BSR set to: 14

	btfss	((3630))&0ffh,1	;volatile
	goto	i2u508_41
	goto	i2u508_40
i2u508_41:
	goto	i2l1328
i2u508_40:
	
i2l5955:; BSR set to: 14

	movlw	low(01h)
	addwf	((c:_TIM_2_COUNTER))^00h,c
	movlw	0
	addwfc	((c:_TIM_2_COUNTER+1))^00h,c
	addwfc	((c:_TIM_2_COUNTER+2))^00h,c
	addwfc	((c:_TIM_2_COUNTER+3))^00h,c
	
i2l5957:; BSR set to: 14

	bcf	((3640))&0ffh,1	;volatile
	line	3855
	
i2l1328:; BSR set to: 14

	movff	??_myisr+1,prodh+0
	movff	??_myisr+0,prodl+0
	bcf int$flags,1,c ;clear compiler interrupt flag (level 2)
	retfie f
	opt callstack 0
GLOBAL	__end_of_myisr
	__end_of_myisr:
	signat	_myisr,89
	global	_FCM_feedback_interrupt

;; *************** function _FCM_feedback_interrupt *****************
;; Defined at:
;;		line 3407 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 31/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_FCD_026e1_Timer1__GetCountReal
;;		i2_FCD_026e1_Timer1__ResetCounter
;; This function is called by:
;;		_myisr
;; This function uses a non-reentrant model
;;
psect	text47,class=CODE,space=0,reloc=2,group=0
	line	3407
global __ptext47
__ptext47:
psect	text47
	file	"feedback control - PIC.c"
	line	3407
	global	__size_of_FCM_feedback_interrupt
	__size_of_FCM_feedback_interrupt	equ	__end_of_FCM_feedback_interrupt-_FCM_feedback_interrupt
	
_FCM_feedback_interrupt:; BSR set to: 14

;incstack = 0
	opt	callstack 21
	line	3411
	
i2l5725:; BSR set to: 14

	bcf	(0+(5/8)+(c:3973))^0f00h,c,(5)&7	;volatile
	
i2l5727:; BSR set to: 14

	movf	((c:3965))^0f00h,c,w	;volatile
	iorlw	low(020h)
	movwf	((c:3981))^0f00h,c	;volatile
	
i2l1300:; BSR set to: 14

	line	3414
	incf	((c:_FCV_COUNT))^00h,c,w	;volatile
	movwf	((c:_FCV_COUNT))^00h,c	;volatile
	line	3417
		movlw	3
	xorwf	((c:_FCV_COUNT))^00h,c,w	;volatile
	btfss	status,2
	goto	i2u475_41
	goto	i2u475_40

i2u475_41:
	goto	i2l5739
i2u475_40:
	line	3421
	
i2l5731:; BSR set to: 14

	call	_FCD_026e1_Timer1__GetCountReal	;wreg free
	movff	0+?_FCD_026e1_Timer1__GetCountReal,(_FCV_REVOLUTIONTIME)	;volatile
	movff	1+?_FCD_026e1_Timer1__GetCountReal,(_FCV_REVOLUTIONTIME+1)	;volatile
	movff	2+?_FCD_026e1_Timer1__GetCountReal,(_FCV_REVOLUTIONTIME+2)	;volatile
	movff	3+?_FCD_026e1_Timer1__GetCountReal,(_FCV_REVOLUTIONTIME+3)	;volatile
	
	line	3424
	
i2l5733:
	call	i2_FCD_026e1_Timer1__ResetCounter	;wreg free
	line	3427
	
i2l5735:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_COUNT))^00h,c	;volatile
	line	3430
	
i2l5737:; BSR set to: 0

	movlw	low(01h)
	movwf	((_FCV_DATAREADY))&0ffh	;volatile
	line	3437
	
i2l5739:
	bcf	(0+(5/8)+(c:3973))^0f00h,c,(5)&7	;volatile
	
i2l5743:
	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0DFh)
	movwf	((c:3981))^0f00h,c	;volatile
	line	3439
	
i2l1306:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCM_feedback_interrupt
	__end_of_FCM_feedback_interrupt:
	signat	_FCM_feedback_interrupt,89
	global	i2_FCD_026e1_Timer1__ResetCounter

;; *************** function i2_FCD_026e1_Timer1__ResetCounter *****************
;; Defined at:
;;		line 402 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 3F/0
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
;;		_FCM_feedback_interrupt
;; This function uses a non-reentrant model
;;
psect	text48,class=CODE,space=0,reloc=2,group=0
	line	402
global __ptext48
__ptext48:
psect	text48
	file	"feedback control - PIC.c"
	line	402
	global	__size_ofi2_FCD_026e1_Timer1__ResetCounter
	__size_ofi2_FCD_026e1_Timer1__ResetCounter	equ	__end_ofi2_FCD_026e1_Timer1__ResetCounter-i2_FCD_026e1_Timer1__ResetCounter
	
i2_FCD_026e1_Timer1__ResetCounter:
;incstack = 0
	opt	callstack 22
	line	408
	
i2l5595:
	movlw	high(0)
	movlb	0	; () banked
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE+1))&0ffh	;volatile
	movlw	low(0)
	movwf	((_FCV_026e1_Timer1__TCOUNTSAVE))&0ffh	;volatile
	line	422
	movlw	low(01h)
	movwf	((c:4027))^0f00h,c	;volatile
	line	430
	movlw	low(0)
	movwf	((c:_TIM_2_COUNTER))^00h,c
	movlw	high(0)
	movwf	((c:_TIM_2_COUNTER+1))^00h,c
	movlw	low highword(0)
	movwf	((c:_TIM_2_COUNTER+2))^00h,c
	movlw	high highword(0)
	movwf	((c:_TIM_2_COUNTER+3))^00h,c
	line	473
	
i2l781:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_ofi2_FCD_026e1_Timer1__ResetCounter
	__end_ofi2_FCD_026e1_Timer1__ResetCounter:
	signat	i2_FCD_026e1_Timer1__ResetCounter,89
	global	_FCD_026e1_Timer1__GetCountReal

;; *************** function _FCD_026e1_Timer1__GetCountReal *****************
;; Defined at:
;;		line 480 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      4   47[COMRAM] float 
;;  FCL_COUNT       4   43[COMRAM] unsigned long 
;; Return value:  Size  Location     Type
;;                  4   39[COMRAM] float 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        12       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		_FCD_026e1_Timer1__GetRawCount
;;		i2___fldiv
;;		i2___flmul
;;		i2___xxtofl
;; This function is called by:
;;		_FCM_feedback_interrupt
;; This function uses a non-reentrant model
;;
psect	text49,class=CODE,space=0,reloc=2,group=0
	line	480
global __ptext49
__ptext49:
psect	text49
	file	"feedback control - PIC.c"
	line	480
	global	__size_of_FCD_026e1_Timer1__GetCountReal
	__size_of_FCD_026e1_Timer1__GetCountReal	equ	__end_of_FCD_026e1_Timer1__GetCountReal-_FCD_026e1_Timer1__GetCountReal
	
_FCD_026e1_Timer1__GetCountReal:; BSR set to: 0

;incstack = 0
	opt	callstack 21
	line	487
	
i2l5473:; BSR set to: 14

	call	_FCD_026e1_Timer1__GetRawCount	;wreg free
	movff	0+?_FCD_026e1_Timer1__GetRawCount,(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT)
	movff	1+?_FCD_026e1_Timer1__GetRawCount,(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+1)
	movff	2+?_FCD_026e1_Timer1__GetRawCount,(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+2)
	movff	3+?_FCD_026e1_Timer1__GetRawCount,(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+3)
	
	line	492
	
i2l5475:
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT),(c:i2___xxtofl@val)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+1),(c:i2___xxtofl@val+1)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+2),(c:i2___xxtofl@val+2)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCL_COUNT+3),(c:i2___xxtofl@val+3)
	movlw	(0)&0ffh
	
	call	i2___xxtofl
	movff	0+?i2___xxtofl,(c:i2___flmul@b)
	movff	1+?i2___xxtofl,(c:i2___flmul@b+1)
	movff	2+?i2___xxtofl,(c:i2___flmul@b+2)
	movff	3+?i2___xxtofl,(c:i2___flmul@b+3)
	
	movlw	low(normalize32(0x3c03126f))
	movwf	((c:i2___flmul@a))^00h,c
	movlw	high(normalize32(0x3c03126f))
	movwf	((c:i2___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x3c03126f))
	movwf	((c:i2___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x3c03126f))
	movwf	((c:i2___flmul@a+3))^00h,c
	call	i2___flmul	;wreg free
	movff	0+?i2___flmul,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL)
	movff	1+?i2___flmul,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+1)
	movff	2+?i2___flmul,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+2)
	movff	3+?i2___flmul,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+3)
	
	line	493
	
i2l5477:
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL),(c:i2___fldiv@b)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+1),(c:i2___fldiv@b+1)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+2),(c:i2___fldiv@b+2)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+3),(c:i2___fldiv@b+3)
	movlw	low(normalize32(0x447a0000))
	movwf	((c:i2___fldiv@a))^00h,c
	movlw	high(normalize32(0x447a0000))
	movwf	((c:i2___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x447a0000))
	movwf	((c:i2___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x447a0000))
	movwf	((c:i2___fldiv@a+3))^00h,c
	call	i2___fldiv	;wreg free
	movff	0+?i2___fldiv,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL)
	movff	1+?i2___fldiv,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+1)
	movff	2+?i2___fldiv,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+2)
	movff	3+?i2___fldiv,(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+3)
	
	line	497
	
i2l5479:
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL),(c:?_FCD_026e1_Timer1__GetCountReal)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+1),(c:?_FCD_026e1_Timer1__GetCountReal+1)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+2),(c:?_FCD_026e1_Timer1__GetCountReal+2)
	movff	(c:FCD_026e1_Timer1__GetCountReal@FCR_RETVAL+3),(c:?_FCD_026e1_Timer1__GetCountReal+3)
	line	499
	
i2l784:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_026e1_Timer1__GetCountReal
	__end_of_FCD_026e1_Timer1__GetCountReal:
	signat	_FCD_026e1_Timer1__GetCountReal,92
	global	i2___xxtofl

;; *************** function i2___xxtofl *****************
;; Defined at:
;;		line 10 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
;; Parameters:    Size  Location     Type
;;  sign            1    wreg     unsigned char 
;;  val             4    0[COMRAM] long 
;; Auto vars:     Size  Location     Type
;;  sign            1    8[COMRAM] unsigned char 
;;  __xxtofl        4   10[COMRAM] unsigned long 
;;  __xxtofl        1    9[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 31/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        14       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__GetCountReal
;; This function uses a non-reentrant model
;;
psect	text50,class=CODE,space=0,reloc=2,group=0
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
global __ptext50
__ptext50:
psect	text50
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
	global	__size_ofi2___xxtofl
	__size_ofi2___xxtofl	equ	__end_ofi2___xxtofl-i2___xxtofl
	
i2___xxtofl:
;incstack = 0
	opt	callstack 21
	movwf	((c:i2___xxtofl@sign))^00h,c
	line	15
	
i2l5421:
	movf	((c:i2___xxtofl@sign))^00h,c,w
	btfsc	status,2
	goto	i2u457_41
	goto	i2u457_40
i2u457_41:
	goto	i2l1974
i2u457_40:
	
i2l5423:
	btfsc	((c:i2___xxtofl@val+3))^00h,c,7
	goto	i2u458_40
	goto	i2u458_41

i2u458_41:
	goto	i2l1974
i2u458_40:
	line	16
	
i2l5425:
	movff	(c:i2___xxtofl@val),??i2___xxtofl+0+0
	movff	(c:i2___xxtofl@val+1),??i2___xxtofl+0+0+1
	movff	(c:i2___xxtofl@val+2),??i2___xxtofl+0+0+2
	movff	(c:i2___xxtofl@val+3),??i2___xxtofl+0+0+3
	comf	(??i2___xxtofl+0+0)^00h,c
	comf	(??i2___xxtofl+0+1)^00h,c
	comf	(??i2___xxtofl+0+2)^00h,c
	comf	(??i2___xxtofl+0+3)^00h,c
	incf	(??i2___xxtofl+0+0)^00h,c
	movlw	0
	addwfc	(??i2___xxtofl+0+1)^00h,c
	addwfc	(??i2___xxtofl+0+2)^00h,c
	addwfc	(??i2___xxtofl+0+3)^00h,c
	movff	??i2___xxtofl+0+0,(c:i2___xxtofl@arg)
	movff	??i2___xxtofl+0+1,(c:i2___xxtofl@arg+1)
	movff	??i2___xxtofl+0+2,(c:i2___xxtofl@arg+2)
	movff	??i2___xxtofl+0+3,(c:i2___xxtofl@arg+3)
	line	17
	goto	i2l5427
	line	18
	
i2l1974:
	line	19
	movff	(c:i2___xxtofl@val),(c:i2___xxtofl@arg)
	movff	(c:i2___xxtofl@val+1),(c:i2___xxtofl@arg+1)
	movff	(c:i2___xxtofl@val+2),(c:i2___xxtofl@arg+2)
	movff	(c:i2___xxtofl@val+3),(c:i2___xxtofl@arg+3)
	line	21
	
i2l5427:
	movf	((c:i2___xxtofl@val))^00h,c,w
iorwf	((c:i2___xxtofl@val+1))^00h,c,w
iorwf	((c:i2___xxtofl@val+2))^00h,c,w
iorwf	((c:i2___xxtofl@val+3))^00h,c,w
	btfss	status,2
	goto	i2u459_41
	goto	i2u459_40

i2u459_41:
	goto	i2l5433
i2u459_40:
	line	22
	
i2l5429:
	movlw	low(normalize32(0x0))
	movwf	((c:?i2___xxtofl))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?i2___xxtofl+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?i2___xxtofl+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?i2___xxtofl+3))^00h,c
	goto	i2l1977
	line	23
	
i2l5433:
	movlw	low(096h)
	movwf	((c:i2___xxtofl@exp))^00h,c
	line	24
	goto	i2l5437
	line	25
	
i2l5435:
	incf	((c:i2___xxtofl@exp))^00h,c
	line	26
	bcf	status,0
	rrcf	((c:i2___xxtofl@arg+3))^00h,c
	rrcf	((c:i2___xxtofl@arg+2))^00h,c
	rrcf	((c:i2___xxtofl@arg+1))^00h,c
	rrcf	((c:i2___xxtofl@arg))^00h,c
	line	24
	
i2l5437:
	movlw	0
	andwf	((c:i2___xxtofl@arg))^00h,c,w
	movwf	(??i2___xxtofl+0+0)^00h,c
	movlw	0
	andwf	((c:i2___xxtofl@arg+1))^00h,c,w
	movwf	1+(??i2___xxtofl+0+0)^00h,c
	
	movlw	0
	andwf	((c:i2___xxtofl@arg+2))^00h,c,w
	movwf	2+(??i2___xxtofl+0+0)^00h,c
	
	movlw	0FEh
	andwf	((c:i2___xxtofl@arg+3))^00h,c,w
	movwf	3+(??i2___xxtofl+0+0)^00h,c
	movf	(??i2___xxtofl+0+0)^00h,c,w
iorwf	(??i2___xxtofl+0+1)^00h,c,w
iorwf	(??i2___xxtofl+0+2)^00h,c,w
iorwf	(??i2___xxtofl+0+3)^00h,c,w
	btfss	status,2
	goto	i2u460_41
	goto	i2u460_40

i2u460_41:
	goto	i2l5435
i2u460_40:
	goto	i2l1981
	line	29
	
i2l5439:
	incf	((c:i2___xxtofl@exp))^00h,c
	line	30
	
i2l5441:
	movlw	low(01h)
	addwf	((c:i2___xxtofl@arg))^00h,c
	movlw	0
	addwfc	((c:i2___xxtofl@arg+1))^00h,c
	addwfc	((c:i2___xxtofl@arg+2))^00h,c
	addwfc	((c:i2___xxtofl@arg+3))^00h,c
	line	31
	
i2l5443:
	bcf	status,0
	rrcf	((c:i2___xxtofl@arg+3))^00h,c
	rrcf	((c:i2___xxtofl@arg+2))^00h,c
	rrcf	((c:i2___xxtofl@arg+1))^00h,c
	rrcf	((c:i2___xxtofl@arg))^00h,c
	line	32
	
i2l1981:
	line	28
	movlw	0
	andwf	((c:i2___xxtofl@arg))^00h,c,w
	movwf	(??i2___xxtofl+0+0)^00h,c
	movlw	0
	andwf	((c:i2___xxtofl@arg+1))^00h,c,w
	movwf	1+(??i2___xxtofl+0+0)^00h,c
	
	movlw	0
	andwf	((c:i2___xxtofl@arg+2))^00h,c,w
	movwf	2+(??i2___xxtofl+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:i2___xxtofl@arg+3))^00h,c,w
	movwf	3+(??i2___xxtofl+0+0)^00h,c
	movf	(??i2___xxtofl+0+0)^00h,c,w
iorwf	(??i2___xxtofl+0+1)^00h,c,w
iorwf	(??i2___xxtofl+0+2)^00h,c,w
iorwf	(??i2___xxtofl+0+3)^00h,c,w
	btfss	status,2
	goto	i2u461_41
	goto	i2u461_40

i2u461_41:
	goto	i2l5439
i2u461_40:
	goto	i2l5447
	line	34
	
i2l5445:
	decf	((c:i2___xxtofl@exp))^00h,c
	line	35
	bcf	status,0
	rlcf	((c:i2___xxtofl@arg))^00h,c
	rlcf	((c:i2___xxtofl@arg+1))^00h,c
	rlcf	((c:i2___xxtofl@arg+2))^00h,c
	rlcf	((c:i2___xxtofl@arg+3))^00h,c
	line	33
	
i2l5447:
	
	btfsc	((c:i2___xxtofl@arg+2))^00h,c,(23)&7
	goto	i2u462_41
	goto	i2u462_40
i2u462_41:
	goto	i2l1988
i2u462_40:
	
i2l5449:
		movlw	02h-0
	cpfslt	((c:i2___xxtofl@exp))^00h,c
	goto	i2u463_41
	goto	i2u463_40

i2u463_41:
	goto	i2l5445
i2u463_40:
	
i2l1988:
	line	37
	
	btfsc	((c:i2___xxtofl@exp))^00h,c,(0)&7
	goto	i2u464_41
	goto	i2u464_40
i2u464_41:
	goto	i2l5453
i2u464_40:
	line	38
	
i2l5451:
	bcf	(0+(23/8)+(c:i2___xxtofl@arg))^00h,c,(23)&7
	line	39
	
i2l5453:
	bcf status,0
	rrcf	((c:i2___xxtofl@exp))^00h,c

	line	40
	
i2l5455:
	movff	(c:i2___xxtofl@exp),??i2___xxtofl+0+0
	clrf	(??i2___xxtofl+0+0+1)^00h,c
	clrf	(??i2___xxtofl+0+0+2)^00h,c
	clrf	(??i2___xxtofl+0+0+3)^00h,c
	movff	??i2___xxtofl+0+0,??i2___xxtofl+0+3
	clrf	(??i2___xxtofl+0+2)^00h,c
	clrf	(??i2___xxtofl+0+1)^00h,c
	clrf	(??i2___xxtofl+0+0)^00h,c
	movf	(??i2___xxtofl+0+0)^00h,c,w
	iorwf	((c:i2___xxtofl@arg))^00h,c
	movf	(??i2___xxtofl+0+1)^00h,c,w
	iorwf	((c:i2___xxtofl@arg+1))^00h,c
	movf	(??i2___xxtofl+0+2)^00h,c,w
	iorwf	((c:i2___xxtofl@arg+2))^00h,c
	movf	(??i2___xxtofl+0+3)^00h,c,w
	iorwf	((c:i2___xxtofl@arg+3))^00h,c

	line	41
	
i2l5457:
	movf	((c:i2___xxtofl@sign))^00h,c,w
	btfsc	status,2
	goto	i2u465_41
	goto	i2u465_40
i2u465_41:
	goto	i2l5463
i2u465_40:
	
i2l5459:
	btfsc	((c:i2___xxtofl@val+3))^00h,c,7
	goto	i2u466_40
	goto	i2u466_41

i2u466_41:
	goto	i2l5463
i2u466_40:
	line	42
	
i2l5461:
	bsf	(0+(31/8)+(c:i2___xxtofl@arg))^00h,c,(31)&7
	line	43
	
i2l5463:
	movff	(c:i2___xxtofl@arg),(c:?i2___xxtofl)
	movff	(c:i2___xxtofl@arg+1),(c:?i2___xxtofl+1)
	movff	(c:i2___xxtofl@arg+2),(c:?i2___xxtofl+2)
	movff	(c:i2___xxtofl@arg+3),(c:?i2___xxtofl+3)
	line	44
	
i2l1977:
	return	;funcret
	opt callstack 0
GLOBAL	__end_ofi2___xxtofl
	__end_ofi2___xxtofl:
	signat	i2___xxtofl,8284
	global	i2___flmul

;; *************** function i2___flmul *****************
;; Defined at:
;;		line 8 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
;; Parameters:    Size  Location     Type
;;  b               4   14[COMRAM] unsigned char 
;;  a               4   18[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  __flmul         4   33[COMRAM] struct .
;;  __flmul         4   28[COMRAM] unsigned long 
;;  __flmul         2   37[COMRAM] struct .
;;  __flmul         1   32[COMRAM] unsigned char 
;;  __flmul         1   27[COMRAM] unsigned char 
;;  __flmul         1   26[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4   14[COMRAM] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:        13       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        25       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       25 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__GetCountReal
;; This function uses a non-reentrant model
;;
psect	text51,class=CODE,space=0,reloc=2,group=0
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
global __ptext51
__ptext51:
psect	text51
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
	global	__size_ofi2___flmul
	__size_ofi2___flmul	equ	__end_ofi2___flmul-i2___flmul
	
i2___flmul:
;incstack = 0
	opt	callstack 21
	line	17
	
i2l5291:
	movf	(0+((c:i2___flmul@b)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:i2___flmul@sign))^00h,c
	line	18
	movf	(0+((c:i2___flmul@b)+03h))^00h,c,w
	addwf	(0+((c:i2___flmul@b)+03h))^00h,c,w
	movwf	((c:i2___flmul@bexp))^00h,c
	line	19
	
i2l5293:
	
	btfss	(0+((c:i2___flmul@b)+02h))^00h,c,(7)&7
	goto	i2u439_41
	goto	i2u439_40
i2u439_41:
	goto	i2l5297
i2u439_40:
	line	20
	
i2l5295:
	bsf	(0+(0/8)+(c:i2___flmul@bexp))^00h,c,(0)&7
	line	24
	
i2l5297:
	movf	((c:i2___flmul@bexp))^00h,c,w
	btfsc	status,2
	goto	i2u440_41
	goto	i2u440_40
i2u440_41:
	goto	i2l5305
i2u440_40:
	line	26
	
i2l5299:
		incf	((c:i2___flmul@bexp))^00h,c,w
	btfss	status,2
	goto	i2u441_41
	goto	i2u441_40

i2u441_41:
	goto	i2l5303
i2u441_40:
	line	28
	
i2l5301:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___flmul@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___flmul@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___flmul@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___flmul@b+3))^00h,c
	line	31
	
i2l5303:
	bsf	(0+(23/8)+(c:i2___flmul@b))^00h,c,(23)&7
	line	33
	goto	i2l5307
	line	36
	
i2l5305:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___flmul@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___flmul@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___flmul@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___flmul@b+3))^00h,c
	line	39
	
i2l5307:
	movf	(0+((c:i2___flmul@a)+03h))^00h,c,w
	andlw	low(080h)
	xorwf	((c:i2___flmul@sign))^00h,c
	line	40
	
i2l5309:
	movf	(0+((c:i2___flmul@a)+03h))^00h,c,w
	addwf	(0+((c:i2___flmul@a)+03h))^00h,c,w
	movwf	((c:i2___flmul@aexp))^00h,c
	line	41
	
i2l5311:
	
	btfss	(0+((c:i2___flmul@a)+02h))^00h,c,(7)&7
	goto	i2u442_41
	goto	i2u442_40
i2u442_41:
	goto	i2l5315
i2u442_40:
	line	42
	
i2l5313:
	bsf	(0+(0/8)+(c:i2___flmul@aexp))^00h,c,(0)&7
	line	45
	
i2l5315:
	movf	((c:i2___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u443_41
	goto	i2u443_40
i2u443_41:
	goto	i2l5323
i2u443_40:
	line	48
	
i2l5317:
		incf	((c:i2___flmul@aexp))^00h,c,w
	btfss	status,2
	goto	i2u444_41
	goto	i2u444_40

i2u444_41:
	goto	i2l5321
i2u444_40:
	line	50
	
i2l5319:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___flmul@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___flmul@a+3))^00h,c
	line	53
	
i2l5321:
	bsf	(0+(23/8)+(c:i2___flmul@a))^00h,c,(23)&7
	line	54
	goto	i2l1933
	line	57
	
i2l5323:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___flmul@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___flmul@a+3))^00h,c
	line	58
	
i2l1933:
	line	65
	movf	((c:i2___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u445_41
	goto	i2u445_40
i2u445_41:
	goto	i2l5327
i2u445_40:
	
i2l5325:
	movf	((c:i2___flmul@bexp))^00h,c,w
	btfss	status,2
	goto	i2u446_41
	goto	i2u446_40
i2u446_41:
	goto	i2l5331
i2u446_40:
	line	66
	
i2l5327:
	movlw	low(normalize32(0x0))
	movwf	((c:?i2___flmul))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?i2___flmul+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?i2___flmul+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?i2___flmul+3))^00h,c
	goto	i2l1937
	line	95
	
i2l5331:
	movf	(0+((c:i2___flmul@a)+02h))^00h,c,w
	mulwf	((c:i2___flmul@b))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	96
	
i2l5333:
	movf	((c:i2___flmul@temp))^00h,c,w
	movwf	((c:i2___flmul@grs))^00h,c
	clrf	((c:i2___flmul@grs+1))^00h,c
	clrf	((c:i2___flmul@grs+2))^00h,c
	clrf	((c:i2___flmul@grs+3))^00h,c

	line	97
	
i2l5335:
	movf	(0+((c:i2___flmul@temp)+01h))^00h,c,w
	movwf	((c:i2___flmul@prod))^00h,c
	clrf	((c:i2___flmul@prod+1))^00h,c
	clrf	((c:i2___flmul@prod+2))^00h,c
	clrf	((c:i2___flmul@prod+3))^00h,c

	line	98
	movf	(0+((c:i2___flmul@a)+01h))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+01h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	99
	
i2l5337:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@grs))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+1))^00h,c
	addwfc	((c:i2___flmul@grs+2))^00h,c
	addwfc	((c:i2___flmul@grs+3))^00h,c
	line	100
	
i2l5339:
	movf	(0+((c:i2___flmul@temp)+01h))^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+1))^00h,c
	addwfc	((c:i2___flmul@prod+2))^00h,c
	addwfc	((c:i2___flmul@prod+3))^00h,c
	line	101
	movf	((c:i2___flmul@a))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+02h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	102
	
i2l5341:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@grs))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+1))^00h,c
	addwfc	((c:i2___flmul@grs+2))^00h,c
	addwfc	((c:i2___flmul@grs+3))^00h,c
	line	103
	
i2l5343:
	movf	(0+((c:i2___flmul@temp)+01h))^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+1))^00h,c
	addwfc	((c:i2___flmul@prod+2))^00h,c
	addwfc	((c:i2___flmul@prod+3))^00h,c
	line	104
	
i2l5345:
	movff	(c:i2___flmul@grs+2),(c:i2___flmul@grs+3)
	movff	(c:i2___flmul@grs+1),(c:i2___flmul@grs+2)
	movff	(c:i2___flmul@grs),(c:i2___flmul@grs+1)
	clrf	((c:i2___flmul@grs))^00h,c
	line	105
	
i2l5347:
	movf	((c:i2___flmul@a))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+01h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	106
	
i2l5349:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@grs))^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	addwfc	((c:i2___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+3))^00h,c

	line	107
	
i2l5351:
	movf	(0+((c:i2___flmul@a)+01h))^00h,c,w
	mulwf	((c:i2___flmul@b))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	108
	
i2l5353:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@grs))^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	addwfc	((c:i2___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+3))^00h,c

	line	109
	
i2l5355:
	movff	(c:i2___flmul@grs+2),(c:i2___flmul@grs+3)
	movff	(c:i2___flmul@grs+1),(c:i2___flmul@grs+2)
	movff	(c:i2___flmul@grs),(c:i2___flmul@grs+1)
	clrf	((c:i2___flmul@grs))^00h,c
	line	110
	movf	((c:i2___flmul@a))^00h,c,w
	mulwf	((c:i2___flmul@b))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	111
	
i2l5357:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@grs))^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	addwfc	((c:i2___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@grs+3))^00h,c

	line	112
	
i2l5359:
	movf	(0+((c:i2___flmul@a)+02h))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+01h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	113
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	addwfc	((c:i2___flmul@prod+1))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+2))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+3))^00h,c

	line	114
	
i2l5361:
	movf	(0+((c:i2___flmul@a)+01h))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+02h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	115
	
i2l5363:
	movf	((c:i2___flmul@temp))^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	addwfc	((c:i2___flmul@prod+1))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+2))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+3))^00h,c

	line	116
	movf	(0+((c:i2___flmul@a)+02h))^00h,c,w
	mulwf	(0+((c:i2___flmul@b)+02h))^00h,c
	movff	prodl,(c:i2___flmul@temp)
	movff	prodh,(c:i2___flmul@temp+1)
	line	117
	
i2l5365:
	movf	((c:i2___flmul@temp))^00h,c,w
	movwf	(??i2___flmul+0+0)^00h,c
	movf	((c:i2___flmul@temp+1))^00h,c,w
	movwf	1+(??i2___flmul+0+0)^00h,c
	
	clrf	2+(??i2___flmul+0+0)^00h,c
	
	clrf	3+(??i2___flmul+0+0)^00h,c
	movff	??i2___flmul+0+2,??i2___flmul+0+3
	movff	??i2___flmul+0+1,??i2___flmul+0+2
	movff	??i2___flmul+0+0,??i2___flmul+0+1
	clrf	(??i2___flmul+0+0)^00h,c
	movf	(??i2___flmul+0+0)^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movf	(??i2___flmul+0+1)^00h,c,w
	addwfc	((c:i2___flmul@prod+1))^00h,c
	movf	(??i2___flmul+0+2)^00h,c,w
	addwfc	((c:i2___flmul@prod+2))^00h,c
	movf	(??i2___flmul+0+3)^00h,c,w
	addwfc	((c:i2___flmul@prod+3))^00h,c

	line	145
	
i2l5367:
	movf	(0+((c:i2___flmul@grs)+03h))^00h,c,w
	addwf	((c:i2___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+1))^00h,c
	addwfc	((c:i2___flmul@prod+2))^00h,c
	addwfc	((c:i2___flmul@prod+3))^00h,c
	line	146
	
i2l5369:
	movff	(c:i2___flmul@grs+2),(c:i2___flmul@grs+3)
	movff	(c:i2___flmul@grs+1),(c:i2___flmul@grs+2)
	movff	(c:i2___flmul@grs),(c:i2___flmul@grs+1)
	clrf	((c:i2___flmul@grs))^00h,c
	line	149
	
i2l5371:
	movf	((c:i2___flmul@aexp))^00h,c,w
	movff	(c:i2___flmul@bexp),??i2___flmul+0+0
	clrf	(??i2___flmul+0+0+1)^00h,c
	addwf	(??i2___flmul+0+0)^00h,c
	movlw	0
	addwfc	(??i2___flmul+0+1)^00h,c
	movlw	low(-126)
	addwf	(??i2___flmul+0+0)^00h,c,w
	movwf	((c:i2___flmul@temp))^00h,c
	movlw	high(-126)
	addwfc	(??i2___flmul+0+1)^00h,c,w
	movwf	1+((c:i2___flmul@temp))^00h,c
	line	152
	goto	i2l5379
	line	153
	
i2l5373:
	bcf	status,0
	rlcf	((c:i2___flmul@prod))^00h,c
	rlcf	((c:i2___flmul@prod+1))^00h,c
	rlcf	((c:i2___flmul@prod+2))^00h,c
	rlcf	((c:i2___flmul@prod+3))^00h,c
	line	154
	
i2l5375:
	
	btfss	((c:i2___flmul@grs+3))^00h,c,(31)&7
	goto	i2u447_41
	goto	i2u447_40
i2u447_41:
	goto	i2l1940
i2u447_40:
	line	155
	
i2l5377:
	bsf	(0+(0/8)+(c:i2___flmul@prod))^00h,c,(0)&7
	line	156
	
i2l1940:
	line	157
	bcf	status,0
	rlcf	((c:i2___flmul@grs))^00h,c
	rlcf	((c:i2___flmul@grs+1))^00h,c
	rlcf	((c:i2___flmul@grs+2))^00h,c
	rlcf	((c:i2___flmul@grs+3))^00h,c
	line	158
	decf	((c:i2___flmul@temp))^00h,c
	btfss	status,0
	decf	((c:i2___flmul@temp+1))^00h,c
	line	152
	
i2l5379:
	
	btfss	((c:i2___flmul@prod+2))^00h,c,(23)&7
	goto	i2u448_41
	goto	i2u448_40
i2u448_41:
	goto	i2l5373
i2u448_40:
	line	163
	
i2l5381:
	movlw	low(0)
	movwf	((c:i2___flmul@aexp))^00h,c
	line	164
	
i2l5383:
	
	btfss	((c:i2___flmul@grs+3))^00h,c,(31)&7
	goto	i2u449_41
	goto	i2u449_40
i2u449_41:
	goto	i2l1942
i2u449_40:
	line	165
	
i2l5385:
	movlw	0FFh
	andwf	((c:i2___flmul@grs))^00h,c,w
	movwf	(??i2___flmul+0+0)^00h,c
	movlw	0FFh
	andwf	((c:i2___flmul@grs+1))^00h,c,w
	movwf	1+(??i2___flmul+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:i2___flmul@grs+2))^00h,c,w
	movwf	2+(??i2___flmul+0+0)^00h,c
	
	movlw	07Fh
	andwf	((c:i2___flmul@grs+3))^00h,c,w
	movwf	3+(??i2___flmul+0+0)^00h,c
	movf	(??i2___flmul+0+0)^00h,c,w
iorwf	(??i2___flmul+0+1)^00h,c,w
iorwf	(??i2___flmul+0+2)^00h,c,w
iorwf	(??i2___flmul+0+3)^00h,c,w
	btfsc	status,2
	goto	i2u450_41
	goto	i2u450_40

i2u450_41:
	goto	i2l1943
i2u450_40:
	line	166
	
i2l5387:
	movlw	low(01h)
	movwf	((c:i2___flmul@aexp))^00h,c
	line	167
	goto	i2l1942
	line	168
	
i2l1943:
	line	169
	
	btfss	((c:i2___flmul@prod))^00h,c,(0)&7
	goto	i2u451_41
	goto	i2u451_40
i2u451_41:
	goto	i2l1942
i2u451_40:
	goto	i2l5387
	line	173
	
i2l1942:
	line	174
	movf	((c:i2___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u452_41
	goto	i2u452_40
i2u452_41:
	goto	i2l5399
i2u452_40:
	line	175
	
i2l5391:
	movlw	low(01h)
	addwf	((c:i2___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:i2___flmul@prod+1))^00h,c
	addwfc	((c:i2___flmul@prod+2))^00h,c
	addwfc	((c:i2___flmul@prod+3))^00h,c
	line	176
	
i2l5393:
	
	btfss	((c:i2___flmul@prod+3))^00h,c,(24)&7
	goto	i2u453_41
	goto	i2u453_40
i2u453_41:
	goto	i2l5399
i2u453_40:
	line	177
	
i2l5395:
	movff	(c:i2___flmul@prod),??i2___flmul+0+0
	movff	(c:i2___flmul@prod+1),??i2___flmul+0+0+1
	movff	(c:i2___flmul@prod+2),??i2___flmul+0+0+2
	movff	(c:i2___flmul@prod+3),??i2___flmul+0+0+3
	rlcf	(??i2___flmul+0+3)^00h,c,w
	rrcf	(??i2___flmul+0+3)^00h,c
	rrcf	(??i2___flmul+0+2)^00h,c
	rrcf	(??i2___flmul+0+1)^00h,c
	rrcf	(??i2___flmul+0+0)^00h,c
	movff	??i2___flmul+0+0,(c:i2___flmul@prod)
	movff	??i2___flmul+0+1,(c:i2___flmul@prod+1)
	movff	??i2___flmul+0+2,(c:i2___flmul@prod+2)
	movff	??i2___flmul+0+3,(c:i2___flmul@prod+3)
	line	178
	
i2l5397:
	infsnz	((c:i2___flmul@temp))^00h,c
	incf	((c:i2___flmul@temp+1))^00h,c
	line	183
	
i2l5399:
	btfsc	((c:i2___flmul@temp+1))^00h,c,7
	goto	i2u454_41
	movf	((c:i2___flmul@temp+1))^00h,c,w
	bnz	i2u454_40
	incf	((c:i2___flmul@temp))^00h,c,w
	btfss	status,0
	goto	i2u454_41
	goto	i2u454_40

i2u454_41:
	goto	i2l5403
i2u454_40:
	line	184
	
i2l5401:
	movlw	low(07F800000h)
	movwf	((c:i2___flmul@prod))^00h,c
	movlw	high(07F800000h)
	movwf	((c:i2___flmul@prod+1))^00h,c
	movlw	low highword(07F800000h)
	movwf	((c:i2___flmul@prod+2))^00h,c
	movlw	high highword(07F800000h)
	movwf	((c:i2___flmul@prod+3))^00h,c
	line	185
	goto	i2l5415
	line	187
	
i2l5403:
	btfsc	((c:i2___flmul@temp+1))^00h,c,7
	goto	i2u455_40
	movf	((c:i2___flmul@temp+1))^00h,c,w
	bnz	i2u455_41
	decf	((c:i2___flmul@temp))^00h,c,w
	btfsc	status,0
	goto	i2u455_41
	goto	i2u455_40

i2u455_41:
	goto	i2l1950
i2u455_40:
	line	188
	
i2l5405:
	movlw	low(0)
	movwf	((c:i2___flmul@prod))^00h,c
	movlw	high(0)
	movwf	((c:i2___flmul@prod+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___flmul@prod+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___flmul@prod+3))^00h,c
	line	190
	movlw	low(0)
	movwf	((c:i2___flmul@sign))^00h,c
	line	191
	goto	i2l5415
	line	192
	
i2l1950:
	line	194
	movff	(c:i2___flmul@temp),(c:i2___flmul@bexp)
	line	195
	
i2l5407:
	movlw	0FFh
	andwf	((c:i2___flmul@prod))^00h,c
	movlw	0FFh
	andwf	((c:i2___flmul@prod+1))^00h,c
	movlw	07Fh
	andwf	((c:i2___flmul@prod+2))^00h,c
	movlw	0
	andwf	((c:i2___flmul@prod+3))^00h,c
	line	196
	
i2l5409:
	
	btfss	((c:i2___flmul@bexp))^00h,c,(0)&7
	goto	i2u456_41
	goto	i2u456_40
i2u456_41:
	goto	i2l5413
i2u456_40:
	line	197
	
i2l5411:
	bsf	(0+(7/8)+0+((c:i2___flmul@prod)+02h))^00h,c,(7)&7
	line	199
	
i2l5413:
	bcf	status,0
	rrcf	((c:i2___flmul@bexp))^00h,c,w
	movwf	(0+((c:i2___flmul@prod)+03h))^00h,c
	line	201
	
i2l5415:
	movf	((c:i2___flmul@sign))^00h,c,w
	iorwf	(0+((c:i2___flmul@prod)+03h))^00h,c
	line	203
	
i2l5417:
	movff	(c:i2___flmul@prod),(c:?i2___flmul)
	movff	(c:i2___flmul@prod+1),(c:?i2___flmul+1)
	movff	(c:i2___flmul@prod+2),(c:?i2___flmul+2)
	movff	(c:i2___flmul@prod+3),(c:?i2___flmul+3)
	line	205
	
i2l1937:
	return	;funcret
	opt callstack 0
GLOBAL	__end_ofi2___flmul
	__end_ofi2___flmul:
	signat	i2___flmul,8284
	global	i2___fldiv

;; *************** function i2___fldiv *****************
;; Defined at:
;;		line 11 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[COMRAM] unsigned char 
;;  a               4    4[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  __fldiv         4   19[COMRAM] unsigned long 
;;  __fldiv         4   12[COMRAM] unsigned long 
;;  __fldiv         2   17[COMRAM] int 
;;  __fldiv         1   24[COMRAM] unsigned char 
;;  __fldiv         1   23[COMRAM] unsigned char 
;;  __fldiv         1   16[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:        13       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        25       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       25 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__GetCountReal
;; This function uses a non-reentrant model
;;
psect	text52,class=CODE,space=0,reloc=2,group=0
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
global __ptext52
__ptext52:
psect	text52
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
	global	__size_ofi2___fldiv
	__size_ofi2___fldiv	equ	__end_ofi2___fldiv-i2___fldiv
	
i2___fldiv:
;incstack = 0
	opt	callstack 21
	line	26
	
i2l5153:
	movf	(0+((c:i2___fldiv@b)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:i2___fldiv@sign))^00h,c
	line	27
	movf	(0+((c:i2___fldiv@b)+03h))^00h,c,w
	addwf	(0+((c:i2___fldiv@b)+03h))^00h,c,w
	movwf	((c:i2___fldiv@bexp))^00h,c
	line	28
	
i2l5155:
	
	btfss	(0+((c:i2___fldiv@b)+02h))^00h,c,(7)&7
	goto	i2u416_41
	goto	i2u416_40
i2u416_41:
	goto	i2l5159
i2u416_40:
	line	29
	
i2l5157:
	bsf	(0+(0/8)+(c:i2___fldiv@bexp))^00h,c,(0)&7
	line	33
	
i2l5159:
	movf	((c:i2___fldiv@bexp))^00h,c,w
	btfsc	status,2
	goto	i2u417_41
	goto	i2u417_40
i2u417_41:
	goto	i2l5169
i2u417_40:
	line	35
	
i2l5161:
		incf	((c:i2___fldiv@bexp))^00h,c,w
	btfss	status,2
	goto	i2u418_41
	goto	i2u418_40

i2u418_41:
	goto	i2l5165
i2u418_40:
	line	37
	
i2l5163:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	40
	
i2l5165:
	bsf	(0+(23/8)+(c:i2___fldiv@b))^00h,c,(23)&7
	line	42
	
i2l5167:
	movlw	low(0)
	movwf	(0+((c:i2___fldiv@b)+03h))^00h,c
	line	43
	goto	i2l5171
	line	46
	
i2l5169:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	49
	
i2l5171:
	movf	(0+((c:i2___fldiv@a)+03h))^00h,c,w
	andlw	low(080h)
	xorwf	((c:i2___fldiv@sign))^00h,c
	line	50
	
i2l5173:
	movf	(0+((c:i2___fldiv@a)+03h))^00h,c,w
	addwf	(0+((c:i2___fldiv@a)+03h))^00h,c,w
	movwf	((c:i2___fldiv@aexp))^00h,c
	line	51
	
i2l5175:
	
	btfss	(0+((c:i2___fldiv@a)+02h))^00h,c,(7)&7
	goto	i2u419_41
	goto	i2u419_40
i2u419_41:
	goto	i2l5179
i2u419_40:
	line	52
	
i2l5177:
	bsf	(0+(0/8)+(c:i2___fldiv@aexp))^00h,c,(0)&7
	line	56
	
i2l5179:
	movf	((c:i2___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u420_41
	goto	i2u420_40
i2u420_41:
	goto	i2l5189
i2u420_40:
	line	58
	
i2l5181:
		incf	((c:i2___fldiv@aexp))^00h,c,w
	btfss	status,2
	goto	i2u421_41
	goto	i2u421_40

i2u421_41:
	goto	i2l5185
i2u421_40:
	line	60
	
i2l5183:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___fldiv@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___fldiv@a+3))^00h,c
	line	63
	
i2l5185:
	bsf	(0+(23/8)+(c:i2___fldiv@a))^00h,c,(23)&7
	line	65
	
i2l5187:
	movlw	low(0)
	movwf	(0+((c:i2___fldiv@a)+03h))^00h,c
	line	66
	goto	i2l5191
	line	69
	
i2l5189:
	movlw	low(normalize32(0x0))
	movwf	((c:i2___fldiv@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:i2___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:i2___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:i2___fldiv@a+3))^00h,c
	line	75
	
i2l5191:
	movf	((c:i2___fldiv@a))^00h,c,w
iorwf	((c:i2___fldiv@a+1))^00h,c,w
iorwf	((c:i2___fldiv@a+2))^00h,c,w
iorwf	((c:i2___fldiv@a+3))^00h,c,w
	btfss	status,2
	goto	i2u422_41
	goto	i2u422_40

i2u422_41:
	goto	i2l5203
i2u422_40:
	line	76
	
i2l5193:
	movlw	low(0)
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	77
	
i2l5195:
	movlw	low(07F80h)
	iorwf	(0+((c:i2___fldiv@b)+02h))^00h,c
	movlw	high(07F80h)
	iorwf	(1+((c:i2___fldiv@b)+02h))^00h,c
	line	78
	
i2l5197:
	movf	((c:i2___fldiv@sign))^00h,c,w
	iorwf	(0+((c:i2___fldiv@b)+03h))^00h,c
	line	79
	
i2l5199:
	movff	(c:i2___fldiv@b),(c:?i2___fldiv)
	movff	(c:i2___fldiv@b+1),(c:?i2___fldiv+1)
	movff	(c:i2___fldiv@b+2),(c:?i2___fldiv+2)
	movff	(c:i2___fldiv@b+3),(c:?i2___fldiv+3)
	goto	i2l1901
	line	83
	
i2l5203:
	movf	((c:i2___fldiv@bexp))^00h,c,w
	btfss	status,2
	goto	i2u423_41
	goto	i2u423_40
i2u423_41:
	goto	i2l5211
i2u423_40:
	line	84
	
i2l5205:
	line	85
	
i2l5207:
	movlw	low(0)
	movwf	((c:?i2___fldiv))^00h,c
	movlw	high(0)
	movwf	((c:?i2___fldiv+1))^00h,c
	movlw	low highword(0)
	movwf	((c:?i2___fldiv+2))^00h,c
	movlw	high highword(0)
	movwf	((c:?i2___fldiv+3))^00h,c
	goto	i2l1901
	line	89
	
i2l5211:
	movf	((c:i2___fldiv@aexp))^00h,c,w
	movff	(c:i2___fldiv@bexp),??i2___fldiv+0+0
	clrf	(??i2___fldiv+0+0+1)^00h,c
	subwf	(??i2___fldiv+0+0)^00h,c
	movlw	0
	subwfb	(??i2___fldiv+0+1)^00h,c
	movlw	low(07Fh)
	addwf	(??i2___fldiv+0+0)^00h,c,w
	movwf	((c:i2___fldiv@new_exp))^00h,c
	movlw	high(07Fh)
	addwfc	(??i2___fldiv+0+1)^00h,c,w
	movwf	1+((c:i2___fldiv@new_exp))^00h,c
	line	92
	
i2l5213:
	movff	(c:i2___fldiv@b),(c:i2___fldiv@rem)
	movff	(c:i2___fldiv@b+1),(c:i2___fldiv@rem+1)
	movff	(c:i2___fldiv@b+2),(c:i2___fldiv@rem+2)
	movff	(c:i2___fldiv@b+3),(c:i2___fldiv@rem+3)
	line	93
	
i2l5215:
	movlw	low(0)
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	94
	
i2l5217:
	movlw	low(0)
	movwf	((c:i2___fldiv@grs))^00h,c
	movlw	high(0)
	movwf	((c:i2___fldiv@grs+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___fldiv@grs+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___fldiv@grs+3))^00h,c
	line	96
	
i2l5219:
	movlw	low(0)
	movwf	((c:i2___fldiv@aexp))^00h,c
	line	97
	goto	i2l1903
	line	100
	
i2l5221:
	movf	((c:i2___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u424_41
	goto	i2u424_40
i2u424_41:
	goto	i2l5229
i2u424_40:
	line	101
	
i2l5223:
	bcf	status,0
	rlcf	((c:i2___fldiv@rem))^00h,c
	rlcf	((c:i2___fldiv@rem+1))^00h,c
	rlcf	((c:i2___fldiv@rem+2))^00h,c
	rlcf	((c:i2___fldiv@rem+3))^00h,c
	line	102
	bcf	status,0
	rlcf	((c:i2___fldiv@b))^00h,c
	rlcf	((c:i2___fldiv@b+1))^00h,c
	rlcf	((c:i2___fldiv@b+2))^00h,c
	rlcf	((c:i2___fldiv@b+3))^00h,c
	line	103
	
i2l5225:
	
	btfss	((c:i2___fldiv@grs+3))^00h,c,(31)&7
	goto	i2u425_41
	goto	i2u425_40
i2u425_41:
	goto	i2l1906
i2u425_40:
	line	104
	
i2l5227:
	bsf	(0+(0/8)+(c:i2___fldiv@b))^00h,c,(0)&7
	line	105
	
i2l1906:
	line	106
	bcf	status,0
	rlcf	((c:i2___fldiv@grs))^00h,c
	rlcf	((c:i2___fldiv@grs+1))^00h,c
	rlcf	((c:i2___fldiv@grs+2))^00h,c
	rlcf	((c:i2___fldiv@grs+3))^00h,c
	line	112
	
i2l5229:
		movf	((c:i2___fldiv@a))^00h,c,w
	subwf	((c:i2___fldiv@rem))^00h,c,w
	movf	((c:i2___fldiv@a+1))^00h,c,w
	subwfb	((c:i2___fldiv@rem+1))^00h,c,w
	movf	((c:i2___fldiv@a+2))^00h,c,w
	subwfb	((c:i2___fldiv@rem+2))^00h,c,w
	movf	((c:i2___fldiv@a+3))^00h,c,w
	subwfb	((c:i2___fldiv@rem+3))^00h,c,w
	btfss	status,0
	goto	i2u426_41
	goto	i2u426_40

i2u426_41:
	goto	i2l5235
i2u426_40:
	line	115
	
i2l5231:
	bsf	(0+(30/8)+(c:i2___fldiv@grs))^00h,c,(30)&7
	line	116
	
i2l5233:
	movf	((c:i2___fldiv@a))^00h,c,w
	subwf	((c:i2___fldiv@rem))^00h,c
	movf	((c:i2___fldiv@a+1))^00h,c,w
	subwfb	((c:i2___fldiv@rem+1))^00h,c
	movf	((c:i2___fldiv@a+2))^00h,c,w
	subwfb	((c:i2___fldiv@rem+2))^00h,c
	movf	((c:i2___fldiv@a+3))^00h,c,w
	subwfb	((c:i2___fldiv@rem+3))^00h,c
	line	118
	
i2l5235:
	incf	((c:i2___fldiv@aexp))^00h,c
	line	119
	
i2l1903:
	line	97
		movlw	01Ah-1
	cpfsgt	((c:i2___fldiv@aexp))^00h,c
	goto	i2u427_41
	goto	i2u427_40

i2u427_41:
	goto	i2l5221
i2u427_40:
	line	122
	
i2l5237:
	movf	((c:i2___fldiv@rem))^00h,c,w
iorwf	((c:i2___fldiv@rem+1))^00h,c,w
iorwf	((c:i2___fldiv@rem+2))^00h,c,w
iorwf	((c:i2___fldiv@rem+3))^00h,c,w
	btfsc	status,2
	goto	i2u428_41
	goto	i2u428_40

i2u428_41:
	goto	i2l5247
i2u428_40:
	line	123
	
i2l5239:
	bsf	(0+(0/8)+(c:i2___fldiv@grs))^00h,c,(0)&7
	goto	i2l5247
	line	128
	
i2l5241:
	bcf	status,0
	rlcf	((c:i2___fldiv@b))^00h,c
	rlcf	((c:i2___fldiv@b+1))^00h,c
	rlcf	((c:i2___fldiv@b+2))^00h,c
	rlcf	((c:i2___fldiv@b+3))^00h,c
	line	129
	
i2l5243:
	
	btfss	((c:i2___fldiv@grs+3))^00h,c,(31)&7
	goto	i2u429_41
	goto	i2u429_40
i2u429_41:
	goto	i2l1912
i2u429_40:
	line	130
	
i2l5245:
	bsf	(0+(0/8)+(c:i2___fldiv@b))^00h,c,(0)&7
	line	131
	
i2l1912:
	line	132
	bcf	status,0
	rlcf	((c:i2___fldiv@grs))^00h,c
	rlcf	((c:i2___fldiv@grs+1))^00h,c
	rlcf	((c:i2___fldiv@grs+2))^00h,c
	rlcf	((c:i2___fldiv@grs+3))^00h,c
	line	133
	decf	((c:i2___fldiv@new_exp))^00h,c
	btfss	status,0
	decf	((c:i2___fldiv@new_exp+1))^00h,c
	line	127
	
i2l5247:
	
	btfss	((c:i2___fldiv@b+2))^00h,c,(23)&7
	goto	i2u430_41
	goto	i2u430_40
i2u430_41:
	goto	i2l5241
i2u430_40:
	line	139
	
i2l5249:
	movlw	low(0)
	movwf	((c:i2___fldiv@aexp))^00h,c
	line	140
	
i2l5251:
	
	btfss	((c:i2___fldiv@grs+3))^00h,c,(31)&7
	goto	i2u431_41
	goto	i2u431_40
i2u431_41:
	goto	i2l1914
i2u431_40:
	line	141
	
i2l5253:
	movlw	0FFh
	andwf	((c:i2___fldiv@grs))^00h,c,w
	movwf	(??i2___fldiv+0+0)^00h,c
	movlw	0FFh
	andwf	((c:i2___fldiv@grs+1))^00h,c,w
	movwf	1+(??i2___fldiv+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:i2___fldiv@grs+2))^00h,c,w
	movwf	2+(??i2___fldiv+0+0)^00h,c
	
	movlw	07Fh
	andwf	((c:i2___fldiv@grs+3))^00h,c,w
	movwf	3+(??i2___fldiv+0+0)^00h,c
	movf	(??i2___fldiv+0+0)^00h,c,w
iorwf	(??i2___fldiv+0+1)^00h,c,w
iorwf	(??i2___fldiv+0+2)^00h,c,w
iorwf	(??i2___fldiv+0+3)^00h,c,w
	btfsc	status,2
	goto	i2u432_41
	goto	i2u432_40

i2u432_41:
	goto	i2l1915
i2u432_40:
	line	142
	
i2l5255:
	movlw	low(01h)
	movwf	((c:i2___fldiv@aexp))^00h,c
	line	143
	goto	i2l1914
	line	144
	
i2l1915:
	line	145
	
	btfss	((c:i2___fldiv@b))^00h,c,(0)&7
	goto	i2u433_41
	goto	i2u433_40
i2u433_41:
	goto	i2l1914
i2u433_40:
	goto	i2l5255
	line	149
	
i2l1914:
	line	150
	movf	((c:i2___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	i2u434_41
	goto	i2u434_40
i2u434_41:
	goto	i2l5267
i2u434_40:
	line	151
	
i2l5259:
	movlw	low(01h)
	addwf	((c:i2___fldiv@b))^00h,c
	movlw	0
	addwfc	((c:i2___fldiv@b+1))^00h,c
	addwfc	((c:i2___fldiv@b+2))^00h,c
	addwfc	((c:i2___fldiv@b+3))^00h,c
	line	152
	
i2l5261:
	
	btfss	((c:i2___fldiv@b+3))^00h,c,(24)&7
	goto	i2u435_41
	goto	i2u435_40
i2u435_41:
	goto	i2l5267
i2u435_40:
	line	153
	
i2l5263:
	movff	(c:i2___fldiv@b),??i2___fldiv+0+0
	movff	(c:i2___fldiv@b+1),??i2___fldiv+0+0+1
	movff	(c:i2___fldiv@b+2),??i2___fldiv+0+0+2
	movff	(c:i2___fldiv@b+3),??i2___fldiv+0+0+3
	rlcf	(??i2___fldiv+0+3)^00h,c,w
	rrcf	(??i2___fldiv+0+3)^00h,c
	rrcf	(??i2___fldiv+0+2)^00h,c
	rrcf	(??i2___fldiv+0+1)^00h,c
	rrcf	(??i2___fldiv+0+0)^00h,c
	movff	??i2___fldiv+0+0,(c:i2___fldiv@b)
	movff	??i2___fldiv+0+1,(c:i2___fldiv@b+1)
	movff	??i2___fldiv+0+2,(c:i2___fldiv@b+2)
	movff	??i2___fldiv+0+3,(c:i2___fldiv@b+3)
	line	154
	
i2l5265:
	infsnz	((c:i2___fldiv@new_exp))^00h,c
	incf	((c:i2___fldiv@new_exp+1))^00h,c
	line	159
	
i2l5267:
	btfsc	((c:i2___fldiv@new_exp+1))^00h,c,7
	goto	i2u436_41
	movf	((c:i2___fldiv@new_exp+1))^00h,c,w
	bnz	i2u436_40
	incf	((c:i2___fldiv@new_exp))^00h,c,w
	btfss	status,0
	goto	i2u436_41
	goto	i2u436_40

i2u436_41:
	goto	i2l5271
i2u436_40:
	line	160
	
i2l5269:
	movlw	high(0FFh)
	movwf	((c:i2___fldiv@new_exp+1))^00h,c
	setf	((c:i2___fldiv@new_exp))^00h,c
	line	161
	movlw	low(0)
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	165
	
i2l5271:
	btfsc	((c:i2___fldiv@new_exp+1))^00h,c,7
	goto	i2u437_40
	movf	((c:i2___fldiv@new_exp+1))^00h,c,w
	bnz	i2u437_41
	decf	((c:i2___fldiv@new_exp))^00h,c,w
	btfsc	status,0
	goto	i2u437_41
	goto	i2u437_40

i2u437_41:
	goto	i2l5275
i2u437_40:
	line	166
	
i2l5273:
	movlw	high(0)
	movwf	((c:i2___fldiv@new_exp+1))^00h,c
	movlw	low(0)
	movwf	((c:i2___fldiv@new_exp))^00h,c
	line	167
	movlw	low(0)
	movwf	((c:i2___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:i2___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:i2___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:i2___fldiv@b+3))^00h,c
	line	169
	movlw	low(0)
	movwf	((c:i2___fldiv@sign))^00h,c
	line	173
	
i2l5275:
	movff	(c:i2___fldiv@new_exp),(c:i2___fldiv@bexp)
	line	175
	
i2l5277:
	
	btfss	((c:i2___fldiv@bexp))^00h,c,(0)&7
	goto	i2u438_41
	goto	i2u438_40
i2u438_41:
	goto	i2l5281
i2u438_40:
	line	176
	
i2l5279:
	bsf	(0+(7/8)+0+((c:i2___fldiv@b)+02h))^00h,c,(7)&7
	line	177
	goto	i2l5283
	line	180
	
i2l5281:
	bcf	(0+(7/8)+0+((c:i2___fldiv@b)+02h))^00h,c,(7)&7
	line	182
	
i2l5283:
	bcf	status,0
	rrcf	((c:i2___fldiv@bexp))^00h,c,w
	movwf	(0+((c:i2___fldiv@b)+03h))^00h,c
	goto	i2l5197
	line	185
	
i2l1901:
	return	;funcret
	opt callstack 0
GLOBAL	__end_ofi2___fldiv
	__end_ofi2___fldiv:
	signat	i2___fldiv,8284
	global	_FCD_026e1_Timer1__GetRawCount

;; *************** function _FCD_026e1_Timer1__GetRawCount *****************
;; Defined at:
;;		line 506 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      4    8[COMRAM] unsigned long 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 31/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        12       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_026e1_Timer1__GetCountReal
;; This function uses a non-reentrant model
;;
psect	text53,class=CODE,space=0,reloc=2,group=0
	file	"feedback control - PIC.c"
	line	506
global __ptext53
__ptext53:
psect	text53
	file	"feedback control - PIC.c"
	line	506
	global	__size_of_FCD_026e1_Timer1__GetRawCount
	__size_of_FCD_026e1_Timer1__GetRawCount	equ	__end_of_FCD_026e1_Timer1__GetRawCount-_FCD_026e1_Timer1__GetRawCount
	
_FCD_026e1_Timer1__GetRawCount:
;incstack = 0
	opt	callstack 21
	line	527
	
i2l5109:; BSR set to: 14

	movff	(c:_TIM_2_COUNTER),(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL)
	movff	(c:_TIM_2_COUNTER+1),(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1)
	movff	(c:_TIM_2_COUNTER+2),(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2)
	movff	(c:_TIM_2_COUNTER+3),(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+3)
	line	529
	
i2l5111:; BSR set to: 14

	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL),??_FCD_026e1_Timer1__GetRawCount+0+0+1
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1),??_FCD_026e1_Timer1__GetRawCount+0+0+2
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2),??_FCD_026e1_Timer1__GetRawCount+0+0+3
	clrf	(??_FCD_026e1_Timer1__GetRawCount+0+0)^00h,c
	movff	??_FCD_026e1_Timer1__GetRawCount+0+0,(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL)
	movff	??_FCD_026e1_Timer1__GetRawCount+0+1,(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1)
	movff	??_FCD_026e1_Timer1__GetRawCount+0+2,(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2)
	movff	??_FCD_026e1_Timer1__GetRawCount+0+3,(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+3)
	line	531
	
i2l5113:; BSR set to: 14

	movf	((c:_FCV_026e1_Timer1__RUNNING))^00h,c,w	;volatile
	btfsc	status,2
	goto	i2u412_41
	goto	i2u412_40
i2u412_41:
	goto	i2l5117
i2u412_40:
	line	535
	
i2l5115:; BSR set to: 14

	movf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c,w
	iorwf	((c:4027))^0f00h,c,w	;volatile
	movwf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	movf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1))^00h,c,w
	movwf	1+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	
	movf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2))^00h,c,w
	movwf	2+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	
	movf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+3))^00h,c,w
	movwf	3+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	line	542
	goto	i2l5119
	line	544
	
i2l5117:; BSR set to: 14

	movlb	0	; () banked
	movf	((_FCV_026e1_Timer1__TCOUNTSAVE))&0ffh,w	;volatile
	addwf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c,w
	movwf	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	movf	((_FCV_026e1_Timer1__TCOUNTSAVE+1))&0ffh,w	;volatile
	addwfc	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1))^00h,c,w
	movwf	1+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	
	movlw	0
	addwfc	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2))^00h,c,w
	movwf	2+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	
	movlw	0
	addwfc	((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+3))^00h,c,w
	movwf	3+((c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL))^00h,c
	line	589
	
i2l5119:
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL),(c:?_FCD_026e1_Timer1__GetRawCount)
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+1),(c:?_FCD_026e1_Timer1__GetRawCount+1)
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+2),(c:?_FCD_026e1_Timer1__GetRawCount+2)
	movff	(c:FCD_026e1_Timer1__GetRawCount@FCR_RETVAL+3),(c:?_FCD_026e1_Timer1__GetRawCount+3)
	line	591
	
i2l789:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_026e1_Timer1__GetRawCount
	__end_of_FCD_026e1_Timer1__GetRawCount:
	signat	_FCD_026e1_Timer1__GetRawCount,92
	global	_FCD_04891_DCMotor1__TimerRoutine

;; *************** function _FCD_04891_DCMotor1__TimerRoutine *****************
;; Defined at:
;;		line 1752 in file "feedback control - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/0
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
;;		_myisr
;; This function uses a non-reentrant model
;;
psect	text54,class=CODE,space=0,reloc=2,group=0
	line	1752
global __ptext54
__ptext54:
psect	text54
	file	"feedback control - PIC.c"
	line	1752
	global	__size_of_FCD_04891_DCMotor1__TimerRoutine
	__size_of_FCD_04891_DCMotor1__TimerRoutine	equ	__end_of_FCD_04891_DCMotor1__TimerRoutine-_FCD_04891_DCMotor1__TimerRoutine
	
_FCD_04891_DCMotor1__TimerRoutine:
;incstack = 0
	opt	callstack 23
	line	1755
	
i2l5641:; BSR set to: 14

	movlw	low(01h)
	addwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c,w	;volatile
	movwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c	;volatile
	movlw	high(01h)
	addwfc	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT+1))^00h,c,w	;volatile
	movwf	1+((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c	;volatile
	line	1757
		incf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c,w	;volatile
iorwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT+1))^00h,c,w	;volatile
	btfss	status,2
	goto	i2u471_41
	goto	i2u471_40

i2u471_41:
	goto	i2l947
i2u471_40:
	line	1760
	
i2l5643:; BSR set to: 14

	movlw	high(0)
	movwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT+1))^00h,c	;volatile
	movlw	low(0)
	movwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c	;volatile
	line	1762
	
i2l5645:; BSR set to: 14

	movlb	0	; () banked
	movf	((_FCV_04891_DCMotor1__SW_PWM_DUTY))&0ffh,w	;volatile
iorwf	((_FCV_04891_DCMotor1__SW_PWM_DUTY+1))&0ffh,w	;volatile
	btfsc	status,2
	goto	i2u472_41
	goto	i2u472_40

i2u472_41:
	goto	i2l947
i2u472_40:
	line	1765
	
i2l5647:; BSR set to: 0

	movf	((_FCV_04891_DCMotor1__SW_PWM_STATE))&0ffh,w	;volatile
	btfsc	status,2
	goto	i2u473_41
	goto	i2u473_40
i2u473_41:
	goto	i2l5661
i2u473_40:
	line	1768
	
i2l5649:; BSR set to: 0

	bcf	(0+(1/8)+(c:3973))^0f00h,c,(1)&7	;volatile
	
i2l5653:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3981))^0f00h,c	;volatile
	line	1771
	
i2l5655:; BSR set to: 0

	bcf	(0+(2/8)+(c:3973))^0f00h,c,(2)&7	;volatile
	
i2l5657:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	iorlw	low(04h)
	movwf	((c:3981))^0f00h,c	;volatile
	goto	i2l947
	line	1779
	
i2l5661:; BSR set to: 0

	bcf	(0+(1/8)+(c:3973))^0f00h,c,(1)&7	;volatile
	
i2l5663:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	iorlw	low(02h)
	movwf	((c:3981))^0f00h,c	;volatile
	line	1782
	
i2l5667:; BSR set to: 0

	bcf	(0+(2/8)+(c:3973))^0f00h,c,(2)&7	;volatile
	
i2l5671:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3981))^0f00h,c	;volatile
	line	1796
	
i2l947:
	line	1798
	movlb	0	; () banked
	movf	((_FCV_04891_DCMotor1__SW_PWM_DUTY))&0ffh,w	;volatile
xorwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT))^00h,c,w	;volatile
	bnz	i2u474_41
movf	((_FCV_04891_DCMotor1__SW_PWM_DUTY+1))&0ffh,w	;volatile
xorwf	((c:_FCV_04891_DCMotor1__SW_PWM_COUNT+1))^00h,c,w	;volatile
	btfss	status,2
	goto	i2u474_41
	goto	i2u474_40

i2u474_41:
	goto	i2l976
i2u474_40:
	line	1804
	
i2l5673:; BSR set to: 0

	bcf	(0+(1/8)+(c:3973))^0f00h,c,(1)&7	;volatile
	
i2l5677:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0FDh)
	movwf	((c:3981))^0f00h,c	;volatile
	line	1807
	
i2l5679:; BSR set to: 0

	bcf	(0+(2/8)+(c:3973))^0f00h,c,(2)&7	;volatile
	
i2l5683:; BSR set to: 0

	movf	((c:3965))^0f00h,c,w	;volatile
	andlw	low(0FBh)
	movwf	((c:3981))^0f00h,c	;volatile
	line	1819
	
i2l976:; BSR set to: 0

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_04891_DCMotor1__TimerRoutine
	__end_of_FCD_04891_DCMotor1__TimerRoutine:
	signat	_FCD_04891_DCMotor1__TimerRoutine,89
psect	mediumconst
	db 0	; dummy byte at the end
	global	__mediumconst
	GLOBAL	__activetblptr
__activetblptr	EQU	2
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
