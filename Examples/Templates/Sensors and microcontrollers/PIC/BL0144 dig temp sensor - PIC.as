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
	FNCALL	_main,_FCD_01c01_temp_hum_sensor__GetTemperatureInt
	FNCALL	_main,_FCD_01c01_temp_hum_sensor__Initialise
	FNCALL	_main,_FCD_029f1_gLCD_EB3__Initialise
	FNCALL	_main,_FCD_029f1_gLCD_EB3__PrintNumber
	FNCALL	_main,_delay_ms
	FNCALL	_FCD_029f1_gLCD_EB3__PrintNumber,_FCD_029f1_gLCD_EB3__Print
	FNCALL	_FCD_029f1_gLCD_EB3__PrintNumber,_FCI_TOSTRING
	FNCALL	_FCI_TOSTRING,___lldiv
	FNCALL	_FCI_TOSTRING,___lmul
	FNCALL	_FCD_029f1_gLCD_EB3__Print,_FCD_029f1_gLCD_EB3__SendCommandWithString
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FCD_029f1_gLCD_EB3__ClearDisplay
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FCD_029f1_gLCD_EB3__SetBackgroundColour
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FCD_029f1_gLCD_EB3__SetDisplayOrientation
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FCD_029f1_gLCD_EB3__SetExternalFont
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FCD_029f1_gLCD_EB3__SetForegroundColour
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_FC_CAL_UART_Init_1
	FNCALL	_FCD_029f1_gLCD_EB3__Initialise,_delay_s
	FNCALL	_delay_s,_delay_ms
	FNCALL	_FCD_029f1_gLCD_EB3__SetForegroundColour,_FCD_029f1_gLCD_EB3__SendCommand
	FNCALL	_FCD_029f1_gLCD_EB3__SetExternalFont,_FCD_029f1_gLCD_EB3__SendCommandWithString
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommandWithString,_FCD_029f1_gLCD_EB3__ReceiveReply
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommandWithString,_FCD_05481_UART1__SendByteArray
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommandWithString,_FCD_05481_UART1__SendString
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommandWithString,_FC_CAL_UART_Send_1
	FNCALL	_FCD_05481_UART1__SendString,_FCI_GETLENGTH
	FNCALL	_FCD_05481_UART1__SendString,_FC_CAL_UART_Send_1
	FNCALL	_FCD_029f1_gLCD_EB3__SetDisplayOrientation,_FCD_029f1_gLCD_EB3__SendCommand
	FNCALL	_FCD_029f1_gLCD_EB3__SetBackgroundColour,_FCD_029f1_gLCD_EB3__SendCommand
	FNCALL	_FCD_029f1_gLCD_EB3__ClearDisplay,_FCD_029f1_gLCD_EB3__SendCommand
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommand,_FCD_029f1_gLCD_EB3__ReceiveReply
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommand,_FCD_05481_UART1__SendByteArray
	FNCALL	_FCD_029f1_gLCD_EB3__SendCommand,_FC_CAL_UART_Send_1
	FNCALL	_FCD_05481_UART1__SendByteArray,_FC_CAL_UART_Send_1
	FNCALL	_FCD_029f1_gLCD_EB3__ReceiveReply,_FCD_01211_RXCB__FlushBuffer
	FNCALL	_FCD_029f1_gLCD_EB3__ReceiveReply,_FCD_01211_RXCB__LookForValue
	FNCALL	_FCD_029f1_gLCD_EB3__ReceiveReply,_FCD_01211_RXCB__PutByte
	FNCALL	_FCD_029f1_gLCD_EB3__ReceiveReply,_FC_CAL_UART_Receive_1
	FNCALL	_FCD_01211_RXCB__LookForValue,_FCD_01211_RXCB__GetByte
	FNCALL	_FCD_01211_RXCB__LookForValue,_FCD_01211_RXCB__GetNumberBytes
	FNCALL	_FCD_01c01_temp_hum_sensor__Initialise,_FCD_01c01_temp_hum_sensor__Sample
	FNCALL	_FCD_01c01_temp_hum_sensor__Initialise,_FC_CAL_I2C_Transaction_Init_1
	FNCALL	_FC_CAL_I2C_Transaction_Init_1,_FC_CAL_I2C_Master_Init_1
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureInt,_FCD_01c01_temp_hum_sensor__GetTemperatureReal
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureInt,___fltol
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,_FCD_01c01_temp_hum_sensor__Sample
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,___fladd
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,___fldiv
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,___flmul
	FNCALL	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,___xxtofl
	FNCALL	_FCD_01c01_temp_hum_sensor__Sample,_FC_CAL_I2C_Transaction_Read_1
	FNCALL	_FCD_01c01_temp_hum_sensor__Sample,_FC_CAL_I2C_Transaction_Write_1
	FNCALL	_FCD_01c01_temp_hum_sensor__Sample,_delay_ms
	FNCALL	_FC_CAL_I2C_Transaction_Write_1,_FC_CAL_I2C_Master_Start_1
	FNCALL	_FC_CAL_I2C_Transaction_Write_1,_FC_CAL_I2C_Master_Stop_1
	FNCALL	_FC_CAL_I2C_Transaction_Write_1,_FC_CAL_I2C_Master_TxByte_1
	FNCALL	_FC_CAL_I2C_Transaction_Read_1,_FC_CAL_I2C_Master_RxByte_1
	FNCALL	_FC_CAL_I2C_Transaction_Read_1,_FC_CAL_I2C_Master_Start_1
	FNCALL	_FC_CAL_I2C_Transaction_Read_1,_FC_CAL_I2C_Master_Stop_1
	FNCALL	_FC_CAL_I2C_Transaction_Read_1,_FC_CAL_I2C_Master_TxByte_1
	FNCALL	_FC_CAL_I2C_Master_TxByte_1,_delay_us
	FNCALL	_FC_CAL_I2C_Master_Stop_1,_delay_us
	FNCALL	_FC_CAL_I2C_Master_Start_1,_delay_us
	FNCALL	_FC_CAL_I2C_Master_RxByte_1,_delay_us
	FNROOT	_main
	FNCALL	intlevel2,_myisr
	global	intlevel2
	FNROOT	intlevel2
	global	_FCV_029f1_gLCD_EB3__TOUCHCOORDS
psect	idataBANK0,class=CODE,space=0,delta=1,noexec
global __pidataBANK0
__pidataBANK0:
	file	"BL0144 dig temp sensor - PIC.c"
	line	2880

;initializer for _FCV_029f1_gLCD_EB3__TOUCHCOORDS
	dw	(-1)&0ffffh
	dw	(-1)&0ffffh
psect	mediumconst,class=MEDIUMCONST,space=0,reloc=2,noexec
global __pmediumconst
__pmediumconst:
	db	0
	file	"BL0144 dig temp sensor - PIC.c"
	line	2176
_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT:
	db	low(0FEh)
	db	low(014h)
	db	low(01Eh)
	db	low(0)
	db	low(01Eh)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(090h)
	db	low(090h)
	db	low(0F8h)
	db	low(096h)
	db	low(090h)
	db	low(0F8h)
	db	low(096h)
	db	low(090h)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(018h)
	db	low(024h)
	db	low(022h)
	db	low(0FFh)
	db	low(042h)
	db	low(042h)
	db	low(084h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(03Ch)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(01Ch)
	db	low(022h)
	db	low(022h)
	db	low(01Ch)
	db	low(0C0h)
	db	low(030h)
	db	low(08Ch)
	db	low(042h)
	db	low(040h)
	db	low(080h)
	db	low(0)
	db	low(0)
	db	low(010h)
	db	low(0Ch)
	db	low(0)
	db	low(0)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(080h)
	db	low(05Ch)
	db	low(022h)
	db	low(062h)
	db	low(092h)
	db	low(0Ch)
	db	low(080h)
	db	low(0)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(08h)
	db	low(010h)
	db	low(01Eh)
	db	low(0)
	db	low(0F0h)
	db	low(0Ch)
	db	low(02h)
	db	low(01Ch)
	db	low(060h)
	db	low(080h)
	db	low(02h)
	db	low(0Ch)
	db	low(0F0h)
	db	low(080h)
	db	low(060h)
	db	low(01Ch)
	db	low(04h)
	db	low(014h)
	db	low(0Eh)
	db	low(014h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(0F8h)
	db	low(040h)
	db	low(040h)
	db	low(040h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(070h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(010h)
	db	low(0)
	db	low(0C0h)
	db	low(038h)
	db	low(06h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0FCh)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(0FCh)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0Ch)
	db	low(02h)
	db	low(02h)
	db	low(082h)
	db	low(042h)
	db	low(03Ch)
	db	low(010h)
	db	low(018h)
	db	low(014h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(02h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(0DCh)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(080h)
	db	low(040h)
	db	low(030h)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(0)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(01Ch)
	db	low(04h)
	db	low(038h)
	db	low(016h)
	db	low(012h)
	db	low(012h)
	db	low(012h)
	db	low(0E2h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(018h)
	db	low(04h)
	db	low(0F8h)
	db	low(044h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(0C4h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(0E2h)
	db	low(01Ah)
	db	low(06h)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0DCh)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(0DCh)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(03Ch)
	db	low(042h)
	db	low(042h)
	db	low(042h)
	db	low(022h)
	db	low(0FCh)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(08h)
	db	low(070h)
	db	low(040h)
	db	low(0A0h)
	db	low(0A0h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(04h)
	db	low(08h)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(0A0h)
	db	low(0A0h)
	db	low(040h)
	db	low(08h)
	db	low(04h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0Ch)
	db	low(02h)
	db	low(082h)
	db	low(042h)
	db	low(022h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(014h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0E0h)
	db	low(018h)
	db	low(04h)
	db	low(0C4h)
	db	low(022h)
	db	low(012h)
	db	low(012h)
	db	low(012h)
	db	low(0A2h)
	db	low(072h)
	db	low(04h)
	db	low(08h)
	db	low(0F0h)
	db	low(0Ch)
	db	low(030h)
	db	low(040h)
	db	low(04Ch)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(088h)
	db	low(09Ch)
	db	low(090h)
	db	low(050h)
	db	low(04Ch)
	db	low(020h)
	db	low(0)
	db	low(080h)
	db	low(0E0h)
	db	low(09Ch)
	db	low(082h)
	db	low(09Ch)
	db	low(0E0h)
	db	low(080h)
	db	low(0)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(0FEh)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(0DCh)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(0F8h)
	db	low(04h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(04h)
	db	low(08h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(04h)
	db	low(0F8h)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0FEh)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(02h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0F8h)
	db	low(04h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(042h)
	db	low(042h)
	db	low(044h)
	db	low(0C8h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(020h)
	db	low(020h)
	db	low(020h)
	db	low(020h)
	db	low(020h)
	db	low(0FEh)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0FEh)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0FEh)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(0FEh)
	db	low(080h)
	db	low(040h)
	db	low(020h)
	db	low(050h)
	db	low(088h)
	db	low(04h)
	db	low(02h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(0FEh)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0FEh)
	db	low(0Ch)
	db	low(030h)
	db	low(0C0h)
	db	low(0)
	db	low(0C0h)
	db	low(030h)
	db	low(0Ch)
	db	low(0FEh)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0FEh)
	db	low(04h)
	db	low(018h)
	db	low(060h)
	db	low(080h)
	db	low(0)
	db	low(0FEh)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(08h)
	db	low(01Ch)
	db	low(0F8h)
	db	low(04h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(04h)
	db	low(0F8h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(0FEh)
	db	low(042h)
	db	low(042h)
	db	low(042h)
	db	low(042h)
	db	low(042h)
	db	low(03Ch)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0F8h)
	db	low(04h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(04h)
	db	low(0F8h)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(014h)
	db	low(08h)
	db	low(01Ch)
	db	low(010h)
	db	low(0FEh)
	db	low(042h)
	db	low(042h)
	db	low(042h)
	db	low(0C2h)
	db	low(042h)
	db	low(042h)
	db	low(03Ch)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(01Ch)
	db	low(022h)
	db	low(022h)
	db	low(022h)
	db	low(042h)
	db	low(042h)
	db	low(08Ch)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(0FEh)
	db	low(02h)
	db	low(02h)
	db	low(02h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0FEh)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0FEh)
	db	low(04h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(04h)
	db	low(06h)
	db	low(018h)
	db	low(060h)
	db	low(080h)
	db	low(0)
	db	low(080h)
	db	low(060h)
	db	low(018h)
	db	low(06h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(06h)
	db	low(038h)
	db	low(0C0h)
	db	low(0)
	db	low(0C0h)
	db	low(03Ch)
	db	low(02h)
	db	low(03Ch)
	db	low(0C0h)
	db	low(0)
	db	low(0C0h)
	db	low(038h)
	db	low(06h)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(02h)
	db	low(0Ch)
	db	low(090h)
	db	low(060h)
	db	low(060h)
	db	low(090h)
	db	low(0Ch)
	db	low(02h)
	db	low(010h)
	db	low(0Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(0Ch)
	db	low(010h)
	db	low(02h)
	db	low(04h)
	db	low(018h)
	db	low(020h)
	db	low(0C0h)
	db	low(020h)
	db	low(018h)
	db	low(04h)
	db	low(02h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(02h)
	db	low(082h)
	db	low(042h)
	db	low(022h)
	db	low(01Ah)
	db	low(06h)
	db	low(02h)
	db	low(010h)
	db	low(018h)
	db	low(014h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0FEh)
	db	low(02h)
	db	low(0FCh)
	db	low(080h)
	db	low(06h)
	db	low(038h)
	db	low(0C0h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(02h)
	db	low(0FEh)
	db	low(080h)
	db	low(0FCh)
	db	low(020h)
	db	low(01Ch)
	db	low(02h)
	db	low(01Ch)
	db	low(020h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(080h)
	db	low(02h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(010h)
	db	low(088h)
	db	low(048h)
	db	low(048h)
	db	low(048h)
	db	low(0F0h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(01Ch)
	db	low(0FEh)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(01Ch)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(0F0h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(010h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(0F0h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(010h)
	db	low(0FEh)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(01Ch)
	db	low(0F0h)
	db	low(048h)
	db	low(048h)
	db	low(048h)
	db	low(048h)
	db	low(070h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(0FCh)
	db	low(0Ah)
	db	low(0Ah)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0F0h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(010h)
	db	low(0F8h)
	db	low(04Ch)
	db	low(090h)
	db	low(090h)
	db	low(090h)
	db	low(088h)
	db	low(07Ch)
	db	low(0FEh)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0FAh)
	db	low(01Ch)
	db	low(0)
	db	low(0FAh)
	db	low(080h)
	db	low(07Ch)
	db	low(0FEh)
	db	low(080h)
	db	low(040h)
	db	low(0A0h)
	db	low(010h)
	db	low(08h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0Ch)
	db	low(010h)
	db	low(0FEh)
	db	low(01Ch)
	db	low(0F8h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0F8h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(01Ch)
	db	low(0F0h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(0F8h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(0F0h)
	db	low(0FCh)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(0F0h)
	db	low(08h)
	db	low(08h)
	db	low(08h)
	db	low(010h)
	db	low(0F8h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(0FCh)
	db	low(0F8h)
	db	low(010h)
	db	low(08h)
	db	low(08h)
	db	low(01Ch)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(030h)
	db	low(048h)
	db	low(048h)
	db	low(048h)
	db	low(090h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(0Ch)
	db	low(08h)
	db	low(0FEh)
	db	low(08h)
	db	low(08h)
	db	low(0)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(0F8h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0F8h)
	db	low(0Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(08h)
	db	low(01Ch)
	db	low(018h)
	db	low(060h)
	db	low(080h)
	db	low(0)
	db	low(080h)
	db	low(060h)
	db	low(018h)
	db	low(0)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(0)
	db	low(018h)
	db	low(0E0h)
	db	low(0)
	db	low(0E0h)
	db	low(018h)
	db	low(0E0h)
	db	low(0)
	db	low(0E0h)
	db	low(018h)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(04h)
	db	low(018h)
	db	low(04h)
	db	low(0)
	db	low(08h)
	db	low(030h)
	db	low(0C0h)
	db	low(0C0h)
	db	low(030h)
	db	low(08h)
	db	low(010h)
	db	low(0Ch)
	db	low(0)
	db	low(0)
	db	low(0Ch)
	db	low(010h)
	db	low(018h)
	db	low(060h)
	db	low(080h)
	db	low(0)
	db	low(080h)
	db	low(060h)
	db	low(018h)
	db	low(0)
	db	low(080h)
	db	low(08Ch)
	db	low(070h)
	db	low(0Ch)
	db	low(0)
	db	low(0)
	db	low(08h)
	db	low(08h)
	db	low(088h)
	db	low(068h)
	db	low(018h)
	db	low(08h)
	db	low(010h)
	db	low(018h)
	db	low(014h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(080h)
	db	low(07Ch)
	db	low(02h)
	db	low(0)
	db	low(07Ch)
	db	low(080h)
	db	low(0FEh)
	db	low(0FCh)
	db	low(02h)
	db	low(07Ch)
	db	low(080h)
	db	low(080h)
	db	low(07Ch)
	db	low(0)
	db	low(040h)
	db	low(020h)
	db	low(020h)
	db	low(060h)
	db	low(040h)
	db	low(040h)
	db	low(020h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0FCh)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(04h)
	db	low(0FCh)
	db	low(01Ch)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(01Ch)
	global __end_of_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT
__end_of_FCD_00fb1_ASCIIData__INTFIXEDLIST_LUT:
psect	mediumconst
	file	"BL0144 dig temp sensor - PIC.c"
	line	1480
_FCD_00fb6_WidthData__INTFIXEDLIST_LUT:
	db	low(05h)
	db	low(010h)
	db	low(022h)
	db	low(01Dh)
	db	low(02Fh)
	db	low(025h)
	db	low(05h)
	db	low(0Eh)
	db	low(0Eh)
	db	low(014h)
	db	low(01Dh)
	db	low(05h)
	db	low(010h)
	db	low(05h)
	db	low(012h)
	db	low(01Ch)
	db	low(010h)
	db	low(01Dh)
	db	low(01Ch)
	db	low(01Eh)
	db	low(01Ch)
	db	low(01Dh)
	db	low(01Ch)
	db	low(01Ch)
	db	low(01Ch)
	db	low(05h)
	db	low(05h)
	db	low(01Dh)
	db	low(01Dh)
	db	low(01Dh)
	db	low(01Ch)
	db	low(038h)
	db	low(029h)
	db	low(021h)
	db	low(026h)
	db	low(024h)
	db	low(021h)
	db	low(01Dh)
	db	low(028h)
	db	low(022h)
	db	low(06h)
	db	low(018h)
	db	low(024h)
	db	low(01Bh)
	db	low(02Bh)
	db	low(022h)
	db	low(029h)
	db	low(021h)
	db	low(029h)
	db	low(025h)
	db	low(023h)
	db	low(022h)
	db	low(022h)
	db	low(029h)
	db	low(03Bh)
	db	low(027h)
	db	low(028h)
	db	low(022h)
	db	low(0Bh)
	db	low(012h)
	db	low(0Bh)
	db	low(019h)
	db	low(023h)
	db	low(0Bh)
	db	low(01Eh)
	db	low(01Ch)
	db	low(01Dh)
	db	low(01Ch)
	db	low(01Eh)
	db	low(012h)
	db	low(01Ch)
	db	low(01Ah)
	db	low(05h)
	db	low(0Ch)
	db	low(01Ah)
	db	low(05h)
	db	low(02Bh)
	db	low(01Ah)
	db	low(01Eh)
	db	low(01Ch)
	db	low(01Ch)
	db	low(011h)
	db	low(01Bh)
	db	low(010h)
	db	low(01Ah)
	db	low(01Dh)
	db	low(02Bh)
	db	low(01Eh)
	db	low(01Bh)
	db	low(01Ch)
	db	low(011h)
	db	low(05h)
	db	low(011h)
	db	low(01Fh)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(011h)
	global __end_of_FCD_00fb6_WidthData__INTFIXEDLIST_LUT
__end_of_FCD_00fb6_WidthData__INTFIXEDLIST_LUT:
psect	mediumconst
	file	"BL0144 dig temp sensor - PIC.c"
	line	1131
_FCD_00fb8_WidthData__INTFIXEDLIST_LUT:
	db	low(07h)
	db	low(016h)
	db	low(02Dh)
	db	low(027h)
	db	low(040h)
	db	low(031h)
	db	low(07h)
	db	low(013h)
	db	low(013h)
	db	low(01Ch)
	db	low(027h)
	db	low(07h)
	db	low(017h)
	db	low(07h)
	db	low(017h)
	db	low(026h)
	db	low(016h)
	db	low(027h)
	db	low(026h)
	db	low(029h)
	db	low(026h)
	db	low(028h)
	db	low(026h)
	db	low(026h)
	db	low(026h)
	db	low(07h)
	db	low(07h)
	db	low(026h)
	db	low(027h)
	db	low(026h)
	db	low(026h)
	db	low(04Dh)
	db	low(037h)
	db	low(02Ch)
	db	low(034h)
	db	low(031h)
	db	low(02Ch)
	db	low(028h)
	db	low(038h)
	db	low(02Eh)
	db	low(08h)
	db	low(020h)
	db	low(031h)
	db	low(024h)
	db	low(039h)
	db	low(02Eh)
	db	low(039h)
	db	low(02Ch)
	db	low(039h)
	db	low(032h)
	db	low(02Fh)
	db	low(030h)
	db	low(02Eh)
	db	low(037h)
	db	low(051h)
	db	low(037h)
	db	low(036h)
	db	low(02Fh)
	db	low(0Fh)
	db	low(017h)
	db	low(0Fh)
	db	low(022h)
	db	low(030h)
	db	low(0Eh)
	db	low(028h)
	db	low(025h)
	db	low(026h)
	db	low(025h)
	db	low(028h)
	db	low(018h)
	db	low(025h)
	db	low(022h)
	db	low(07h)
	db	low(011h)
	db	low(024h)
	db	low(07h)
	db	low(03Bh)
	db	low(022h)
	db	low(028h)
	db	low(025h)
	db	low(025h)
	db	low(017h)
	db	low(024h)
	db	low(015h)
	db	low(022h)
	db	low(027h)
	db	low(03Bh)
	db	low(028h)
	db	low(025h)
	db	low(025h)
	db	low(017h)
	db	low(06h)
	db	low(017h)
	db	low(029h)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(0)
	db	low(017h)
	global __end_of_FCD_00fb8_WidthData__INTFIXEDLIST_LUT
__end_of_FCD_00fb8_WidthData__INTFIXEDLIST_LUT:
psect	mediumconst
	file	"BL0144 dig temp sensor - PIC.c"
	line	2136
_FCD_00fb2_WidthData__INTFIXEDLIST_LUT:
	db	low(01h)
	db	low(03h)
	db	low(08h)
	db	low(07h)
	db	low(0Ah)
	db	low(08h)
	db	low(01h)
	db	low(03h)
	db	low(03h)
	db	low(05h)
	db	low(07h)
	db	low(01h)
	db	low(04h)
	db	low(01h)
	db	low(04h)
	db	low(06h)
	db	low(03h)
	db	low(06h)
	db	low(06h)
	db	low(07h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(01h)
	db	low(01h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(0Dh)
	db	low(09h)
	db	low(07h)
	db	low(08h)
	db	low(08h)
	db	low(07h)
	db	low(07h)
	db	low(09h)
	db	low(07h)
	db	low(01h)
	db	low(05h)
	db	low(08h)
	db	low(07h)
	db	low(09h)
	db	low(07h)
	db	low(09h)
	db	low(07h)
	db	low(09h)
	db	low(08h)
	db	low(07h)
	db	low(07h)
	db	low(07h)
	db	low(09h)
	db	low(0Dh)
	db	low(08h)
	db	low(09h)
	db	low(08h)
	db	low(02h)
	db	low(04h)
	db	low(02h)
	db	low(05h)
	db	low(08h)
	db	low(02h)
	db	low(06h)
	db	low(06h)
	db	low(05h)
	db	low(06h)
	db	low(06h)
	db	low(04h)
	db	low(06h)
	db	low(06h)
	db	low(01h)
	db	low(02h)
	db	low(06h)
	db	low(01h)
	db	low(09h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(06h)
	db	low(04h)
	db	low(05h)
	db	low(04h)
	db	low(06h)
	db	low(07h)
	db	low(09h)
	db	low(06h)
	db	low(07h)
	db	low(06h)
	db	low(03h)
	db	low(01h)
	db	low(03h)
	db	low(07h)
	db	low(07h)
	global __end_of_FCD_00fb2_WidthData__INTFIXEDLIST_LUT
__end_of_FCD_00fb2_WidthData__INTFIXEDLIST_LUT:
psect	mediumconst
	file	"BL0144 dig temp sensor - PIC.c"
	line	1829
_FCD_00fb4_WidthData__INTFIXEDLIST_LUT:
	db	low(03h)
	db	low(09h)
	db	low(011h)
	db	low(010h)
	db	low(019h)
	db	low(013h)
	db	low(03h)
	db	low(08h)
	db	low(08h)
	db	low(0Ah)
	db	low(0Fh)
	db	low(03h)
	db	low(09h)
	db	low(03h)
	db	low(09h)
	db	low(010h)
	db	low(08h)
	db	low(010h)
	db	low(010h)
	db	low(011h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(010h)
	db	low(03h)
	db	low(03h)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(010h)
	db	low(01Eh)
	db	low(015h)
	db	low(011h)
	db	low(014h)
	db	low(013h)
	db	low(011h)
	db	low(0Fh)
	db	low(016h)
	db	low(012h)
	db	low(03h)
	db	low(0Dh)
	db	low(014h)
	db	low(0Eh)
	db	low(017h)
	db	low(012h)
	db	low(016h)
	db	low(011h)
	db	low(016h)
	db	low(013h)
	db	low(012h)
	db	low(013h)
	db	low(012h)
	db	low(015h)
	db	low(021h)
	db	low(015h)
	db	low(015h)
	db	low(013h)
	db	low(06h)
	db	low(09h)
	db	low(06h)
	db	low(0Ch)
	db	low(013h)
	db	low(06h)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Ah)
	db	low(0Fh)
	db	low(0Eh)
	db	low(03h)
	db	low(06h)
	db	low(0Eh)
	db	low(03h)
	db	low(017h)
	db	low(0Eh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(09h)
	db	low(0Fh)
	db	low(08h)
	db	low(0Eh)
	db	low(0Fh)
	db	low(017h)
	db	low(0Fh)
	db	low(0Fh)
	db	low(0Fh)
	db	low(09h)
	db	low(02h)
	db	low(09h)
	db	low(010h)
	global __end_of_FCD_00fb4_WidthData__INTFIXEDLIST_LUT
__end_of_FCD_00fb4_WidthData__INTFIXEDLIST_LUT:
	global	_FCV_TEMPINT
	global	_FCV_01c01_temp_hum_sensor__HUM
	global	_FCV_01c01_temp_hum_sensor__TEMP
	global	_FCV_01211_RXCB__DATASTART
	global	_FCV_01211_RXCB__DATAEND
	global	_FCV_TEMPBYTE
	global	_FCV_01c01_temp_hum_sensor__PRECISION
	global	_FCV_01c01_temp_hum_sensor__SCALE
	global	_FCV_01c01_temp_hum_sensor__SAMPLEMASK
	global	_FCV_07da1_cal_i2c1__TRANSADDR
	global	_FCV_029f1_gLCD_EB3__TXCOUNT
	global	_FCV_029f1_gLCD_EB3__SIMTOUCHED
	global	_FCV_029f1_gLCD_EB3__RXCOUNT
	global	_FCV_09e51_gLCD_Font1__OLDCHAR
	global	_FCV_09e52_gLCD_Font2__OLDCHAR
	global	_FCV_09e53_gLCD_Font3__OLDCHAR
	global	_FCV_09e54_gLCD_Font4__OLDCHAR
	global	_FCV_05481_UART1__RS485_STATE
	global	_FCV_01211_RXCB__LOOKFORCOUNTER
	global	_MX_I2C_INIT_1
	global	_MX_I2C_ADDRESS_1
	global	_FCV_01211_RXCB__DATA
	global	_FCV_TEMPSTRING
	global	_FCV_TEMP
	global	_FCV_07da1_cal_i2c1__CONSOLELOG
	global	_FCV_09e51_gLCD_Font1__OLDPOSITION
	global	_FCV_09e52_gLCD_Font2__OLDPOSITION
	global	_FCV_09e53_gLCD_Font3__OLDPOSITION
	global	_FCV_09e54_gLCD_Font4__OLDPOSITION
	global	_FCV_05481_UART1__CONSOLE
	global	_FCV_029f1_gLCD_EB3__FOREGROUND_COL_VAR
	global	_FCV_029f1_gLCD_EB3__BACKGROUND_COL_VAR
	global	_FCV_029f1_gLCD_EB3__COMMANDTX
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
	global	_RCREG2
_RCREG2	set	0xEF1
	global	_TXREG2
_TXREG2	set	0xEF2
	global	_PIR3bits
_PIR3bits	set	0xE36
	global	_PIE3bits
_PIE3bits	set	0xE2C
	global	_RC2STAbits
_RC2STAbits	set	0xEF5
	global	_RC2STA
_RC2STA	set	0xEF5
	global	_SPBRG2
_SPBRG2	set	0xEF3
	global	_BAUD2CON
_BAUD2CON	set	0xEF7
	global	_TX2STAbits
_TX2STAbits	set	0xEF6
	global	_PORTC
_PORTC	set	0xF8B
	global	_TRISC
_TRISC	set	0xF83
	
STR_8:
	db	65	;'A'
	db	114	;'r'
	db	105	;'i'
	db	56	;'8'
	db	48	;'0'
	db	46
	db	98	;'b'
	db	105	;'i'
	db	110	;'n'
	db	0
	
STR_6:
	db	65	;'A'
	db	114	;'r'
	db	105	;'i'
	db	51	;'3'
	db	50	;'2'
	db	46
	db	98	;'b'
	db	105	;'i'
	db	110	;'n'
	db	0
	
STR_5:
	db	65	;'A'
	db	114	;'r'
	db	105	;'i'
	db	49	;'1'
	db	52	;'4'
	db	46
	db	98	;'b'
	db	105	;'i'
	db	110	;'n'
	db	0
	
STR_7:
	db	65	;'A'
	db	114	;'r'
	db	105	;'i'
	db	53	;'5'
	db	57	;'9'
	db	46
	db	98	;'b'
	db	105	;'i'
	db	110	;'n'
	db	0
	
STR_2:
	db	59	;';'
	db	10
	db	0
STR_1	equ	STR_2+2
STR_3	equ	STR_2+2
STR_4	equ	STR_2+2
; #config settings
	file	"BL0144 dig temp sensor - PIC.as"
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
	global	_FCV_TEMPINT
_FCV_TEMPINT:
       ds      2
	global	_FCV_01c01_temp_hum_sensor__HUM
_FCV_01c01_temp_hum_sensor__HUM:
       ds      2
	global	_FCV_01c01_temp_hum_sensor__TEMP
_FCV_01c01_temp_hum_sensor__TEMP:
       ds      2
	global	_FCV_01211_RXCB__DATASTART
_FCV_01211_RXCB__DATASTART:
       ds      2
	global	_FCV_01211_RXCB__DATAEND
_FCV_01211_RXCB__DATAEND:
       ds      2
	global	_FCI_TMP_INT
	global	_FCI_TMP_INT
_FCI_TMP_INT:
       ds      2
	global	_FCV_TEMPBYTE
	global	_FCV_TEMPBYTE
_FCV_TEMPBYTE:
       ds      1
	global	_FCV_01c01_temp_hum_sensor__PRECISION
_FCV_01c01_temp_hum_sensor__PRECISION:
       ds      1
	global	_FCV_01c01_temp_hum_sensor__SCALE
_FCV_01c01_temp_hum_sensor__SCALE:
       ds      1
	global	_FCV_01c01_temp_hum_sensor__SAMPLEMASK
_FCV_01c01_temp_hum_sensor__SAMPLEMASK:
       ds      1
	global	_FCV_07da1_cal_i2c1__TRANSADDR
	global	_FCV_07da1_cal_i2c1__TRANSADDR
_FCV_07da1_cal_i2c1__TRANSADDR:
       ds      1
	global	_FCV_029f1_gLCD_EB3__TXCOUNT
_FCV_029f1_gLCD_EB3__TXCOUNT:
       ds      1
	global	_FCV_029f1_gLCD_EB3__SIMTOUCHED
	global	_FCV_029f1_gLCD_EB3__SIMTOUCHED
_FCV_029f1_gLCD_EB3__SIMTOUCHED:
       ds      1
	global	_FCV_029f1_gLCD_EB3__RXCOUNT
_FCV_029f1_gLCD_EB3__RXCOUNT:
       ds      1
	global	_FCV_09e51_gLCD_Font1__OLDCHAR
_FCV_09e51_gLCD_Font1__OLDCHAR:
       ds      1
	global	_FCV_09e52_gLCD_Font2__OLDCHAR
_FCV_09e52_gLCD_Font2__OLDCHAR:
       ds      1
	global	_FCV_09e53_gLCD_Font3__OLDCHAR
_FCV_09e53_gLCD_Font3__OLDCHAR:
       ds      1
	global	_FCV_09e54_gLCD_Font4__OLDCHAR
_FCV_09e54_gLCD_Font4__OLDCHAR:
       ds      1
	global	_FCV_05481_UART1__RS485_STATE
	global	_FCV_05481_UART1__RS485_STATE
_FCV_05481_UART1__RS485_STATE:
       ds      1
	global	_FCV_01211_RXCB__LOOKFORCOUNTER
_FCV_01211_RXCB__LOOKFORCOUNTER:
       ds      1
	global	_MX_I2C_INIT_1
_MX_I2C_INIT_1:
       ds      1
	global	_MX_I2C_ADDRESS_1
_MX_I2C_ADDRESS_1:
       ds      1
	global	_FCLV_LOOP4
	global	_FCLV_LOOP4
_FCLV_LOOP4:
       ds      1
	global	_FCLV_LOOP3
	global	_FCLV_LOOP3
_FCLV_LOOP3:
       ds      1
	global	_FCLV_LOOP2
	global	_FCLV_LOOP2
_FCLV_LOOP2:
       ds      1
	global	_FCLV_LOOP1
	global	_FCLV_LOOP1
_FCLV_LOOP1:
       ds      1
psect	bssBANK0,class=BANK0,space=1,noexec,lowdata
global __pbssBANK0
__pbssBANK0:
	global	_FCV_01211_RXCB__DATA
_FCV_01211_RXCB__DATA:
       ds      32
	global	_FCV_TEMPSTRING
	global	_FCV_TEMPSTRING
_FCV_TEMPSTRING:
       ds      20
FCD_0ba71_Base_GLCD__Prv_ReadFontFileHeader@F15504:
       ds      20
	global	_FCV_TEMP
	global	_FCV_TEMP
_FCV_TEMP:
       ds      4
	global	_FCV_07da1_cal_i2c1__CONSOLELOG
	global	_FCV_07da1_cal_i2c1__CONSOLELOG
_FCV_07da1_cal_i2c1__CONSOLELOG:
       ds      4
	global	_FCV_09e51_gLCD_Font1__OLDPOSITION
_FCV_09e51_gLCD_Font1__OLDPOSITION:
       ds      4
	global	_FCV_09e52_gLCD_Font2__OLDPOSITION
_FCV_09e52_gLCD_Font2__OLDPOSITION:
       ds      4
	global	_FCV_09e53_gLCD_Font3__OLDPOSITION
_FCV_09e53_gLCD_Font3__OLDPOSITION:
       ds      4
	global	_FCV_09e54_gLCD_Font4__OLDPOSITION
_FCV_09e54_gLCD_Font4__OLDPOSITION:
       ds      4
	global	_FCV_05481_UART1__CONSOLE
	global	_FCV_05481_UART1__CONSOLE
_FCV_05481_UART1__CONSOLE:
       ds      4
	global	_MX_Conv_Var
_MX_Conv_Var:
       ds      4
	global	_FCLV_LOOP9
	global	_FCLV_LOOP9
_FCLV_LOOP9:
       ds      4
	global	_FCLV_LOOP8
	global	_FCLV_LOOP8
_FCLV_LOOP8:
       ds      4
	global	_FCLV_LOOP7
	global	_FCLV_LOOP7
_FCLV_LOOP7:
       ds      4
	global	_FCLV_LOOP6
	global	_FCLV_LOOP6
_FCLV_LOOP6:
       ds      4
	global	_FCLV_LOOP5
	global	_FCLV_LOOP5
_FCLV_LOOP5:
       ds      4
	global	_errno
_errno:
       ds      2
	global	_FCV_029f1_gLCD_EB3__FOREGROUND_COL_VAR
	global	_FCV_029f1_gLCD_EB3__FOREGROUND_COL_VAR
_FCV_029f1_gLCD_EB3__FOREGROUND_COL_VAR:
       ds      2
	global	_FCV_029f1_gLCD_EB3__BACKGROUND_COL_VAR
	global	_FCV_029f1_gLCD_EB3__BACKGROUND_COL_VAR
_FCV_029f1_gLCD_EB3__BACKGROUND_COL_VAR:
       ds      2
	global	_MX_I2C_TIMEOUT_1
	global	_MX_I2C_TIMEOUT_1
_MX_I2C_TIMEOUT_1:
       ds      2
	global	_FCV_029f1_gLCD_EB3__COMMANDTX
_FCV_029f1_gLCD_EB3__COMMANDTX:
       ds      20
psect	dataBANK0,class=BANK0,space=1,noexec,lowdata
global __pdataBANK0
__pdataBANK0:
	file	"BL0144 dig temp sensor - PIC.c"
	line	2880
	global	_FCV_029f1_gLCD_EB3__TOUCHCOORDS
_FCV_029f1_gLCD_EB3__TOUCHCOORDS:
       ds      4
	file	"BL0144 dig temp sensor - PIC.as"
	line	#
psect	cinit
; Initialize objects allocated to BANK0 (4 bytes)
	global __pidataBANK0
	; load TBLPTR registers with __pidataBANK0
	movlw	low (__pidataBANK0)
	movwf	tblptrl
	movlw	high(__pidataBANK0)
	movwf	tblptrh
	movlw	low highword(__pidataBANK0)
	movwf	tblptru
	lfsr	0,__pdataBANK0
	lfsr	1,4
	copy_data0:
	tblrd	*+
	movff	tablat, postinc0
	movf	postdec1,w
	movf	fsr1l,w
	bnz	copy_data0
	line	#
; Clear objects allocated to BANK0 (152 bytes)
	global __pbssBANK0
lfsr	0,__pbssBANK0
movlw	152
clear_0:
clrf	postinc0,c
decf	wreg
bnz	clear_0
; Clear objects allocated to COMRAM (32 bytes)
	global __pbssCOMRAM
lfsr	0,__pbssCOMRAM
movlw	32
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
movlb 0
goto _main	;jump to C main() function
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_FCD_01211_RXCB__PutByte:	; 1 bytes @ 0x0
??_FCD_01211_RXCB__PutByte:	; 1 bytes @ 0x0
?_FCD_029f1_gLCD_EB3__SendCommand:	; 1 bytes @ 0x0
?_FCD_01c01_temp_hum_sensor__Sample:	; 1 bytes @ 0x0
?_delay_us:	; 1 bytes @ 0x0
??_delay_us:	; 1 bytes @ 0x0
?_delay_ms:	; 1 bytes @ 0x0
??_delay_ms:	; 1 bytes @ 0x0
?_delay_s:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Master_Init_1:	; 1 bytes @ 0x0
??_FC_CAL_I2C_Master_Init_1:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Master_Start_1:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Master_Stop_1:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Master_TxByte_1:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Master_RxByte_1:	; 1 bytes @ 0x0
?_FC_CAL_I2C_Transaction_Init_1:	; 1 bytes @ 0x0
??_FC_CAL_I2C_Transaction_Init_1:	; 1 bytes @ 0x0
?_FC_CAL_UART_Init_1:	; 1 bytes @ 0x0
??_FC_CAL_UART_Init_1:	; 1 bytes @ 0x0
?_FC_CAL_UART_Send_1:	; 1 bytes @ 0x0
?_FCD_01211_RXCB__FlushBuffer:	; 1 bytes @ 0x0
??_FCD_01211_RXCB__FlushBuffer:	; 1 bytes @ 0x0
?_FCD_029f1_gLCD_EB3__ReceiveReply:	; 1 bytes @ 0x0
?_FCD_029f1_gLCD_EB3__SetDisplayOrientation:	; 1 bytes @ 0x0
?_FCD_029f1_gLCD_EB3__ClearDisplay:	; 1 bytes @ 0x0
?_FCD_029f1_gLCD_EB3__Initialise:	; 1 bytes @ 0x0
?_FCD_01c01_temp_hum_sensor__Initialise:	; 1 bytes @ 0x0
?_main:	; 1 bytes @ 0x0
?_myisr:	; 1 bytes @ 0x0
??_myisr:	; 1 bytes @ 0x0
	global	?_FCD_01211_RXCB__GetNumberBytes
?_FCD_01211_RXCB__GetNumberBytes:	; 2 bytes @ 0x0
	global	?_FCD_01211_RXCB__GetByte
?_FCD_01211_RXCB__GetByte:	; 2 bytes @ 0x0
	global	?_FCI_GETLENGTH
?_FCI_GETLENGTH:	; 2 bytes @ 0x0
	global	?_FC_CAL_UART_Receive_1
?_FC_CAL_UART_Receive_1:	; 2 bytes @ 0x0
	global	?___fladd
?___fladd:	; 4 bytes @ 0x0
	global	?___fldiv
?___fldiv:	; 4 bytes @ 0x0
	global	?___flmul
?___flmul:	; 4 bytes @ 0x0
	global	?___lmul
?___lmul:	; 4 bytes @ 0x0
	global	?___lldiv
?___lldiv:	; 4 bytes @ 0x0
	global	?___xxtofl
?___xxtofl:	; 4 bytes @ 0x0
	global	delay_us@del
delay_us@del:	; 1 bytes @ 0x0
	global	FC_CAL_I2C_Transaction_Init_1@SlaveAddress
FC_CAL_I2C_Transaction_Init_1@SlaveAddress:	; 1 bytes @ 0x0
	global	FCI_GETLENGTH@sStr1
FCI_GETLENGTH@sStr1:	; 2 bytes @ 0x0
	global	FC_CAL_UART_Send_1@nChar
FC_CAL_UART_Send_1@nChar:	; 2 bytes @ 0x0
	global	___lmul@multiplier
___lmul@multiplier:	; 4 bytes @ 0x0
	global	___lldiv@dividend
___lldiv@dividend:	; 4 bytes @ 0x0
	global	___fladd@b
___fladd@b:	; 4 bytes @ 0x0
	global	___fldiv@b
___fldiv@b:	; 4 bytes @ 0x0
	global	___flmul@b
___flmul@b:	; 4 bytes @ 0x0
	global	___xxtofl@val
___xxtofl@val:	; 4 bytes @ 0x0
	ds   1
??_FC_CAL_I2C_Master_Start_1:	; 1 bytes @ 0x1
??_FC_CAL_I2C_Master_Stop_1:	; 1 bytes @ 0x1
??_FC_CAL_I2C_Master_TxByte_1:	; 1 bytes @ 0x1
??_FC_CAL_I2C_Master_RxByte_1:	; 1 bytes @ 0x1
	global	delay_ms@del
delay_ms@del:	; 1 bytes @ 0x1
	global	FC_CAL_I2C_Master_TxByte_1@Data
FC_CAL_I2C_Master_TxByte_1@Data:	; 1 bytes @ 0x1
	global	FC_CAL_I2C_Master_RxByte_1@Last
FC_CAL_I2C_Master_RxByte_1@Last:	; 1 bytes @ 0x1
	global	FCD_01211_RXCB__PutByte@FCL_DATA
FCD_01211_RXCB__PutByte@FCL_DATA:	; 1 bytes @ 0x1
	ds   1
??_FCD_01211_RXCB__GetNumberBytes:	; 1 bytes @ 0x2
??_FCD_01211_RXCB__GetByte:	; 1 bytes @ 0x2
??_delay_s:	; 1 bytes @ 0x2
??_FC_CAL_UART_Send_1:	; 1 bytes @ 0x2
??_FC_CAL_UART_Receive_1:	; 1 bytes @ 0x2
?_FCD_05481_UART1__SendByteArray:	; 1 bytes @ 0x2
	global	delay_s@del
delay_s@del:	; 1 bytes @ 0x2
	global	FC_CAL_I2C_Master_TxByte_1@local_ack
FC_CAL_I2C_Master_TxByte_1@local_ack:	; 1 bytes @ 0x2
	global	FC_CAL_I2C_Master_RxByte_1@Data
FC_CAL_I2C_Master_RxByte_1@Data:	; 1 bytes @ 0x2
	global	FC_CAL_UART_Receive_1@dummy
FC_CAL_UART_Receive_1@dummy:	; 1 bytes @ 0x2
	global	FCD_05481_UART1__SendByteArray@FCL_DATA
FCD_05481_UART1__SendByteArray@FCL_DATA:	; 1 bytes @ 0x2
	global	FCI_GETLENGTH@iStr1_len
FCI_GETLENGTH@iStr1_len:	; 2 bytes @ 0x2
	global	FCD_01211_RXCB__PutByte@FCL_TEMP
FCD_01211_RXCB__PutByte@FCL_TEMP:	; 2 bytes @ 0x2
	ds   1
	global	delay_s@i
delay_s@i:	; 1 bytes @ 0x3
	global	FC_CAL_I2C_Master_TxByte_1@bit_mask
FC_CAL_I2C_Master_TxByte_1@bit_mask:	; 1 bytes @ 0x3
	global	FC_CAL_I2C_Master_RxByte_1@bit_mask
FC_CAL_I2C_Master_RxByte_1@bit_mask:	; 1 bytes @ 0x3
	global	FC_CAL_UART_Receive_1@bWaitForever
FC_CAL_UART_Receive_1@bWaitForever:	; 1 bytes @ 0x3
	global	FCD_01211_RXCB__GetByte@FCR_RETVAL
FCD_01211_RXCB__GetByte@FCR_RETVAL:	; 2 bytes @ 0x3
	global	FCD_05481_UART1__SendByteArray@FCLsz_DATA
FCD_05481_UART1__SendByteArray@FCLsz_DATA:	; 2 bytes @ 0x3
	ds   1
??_FCI_GETLENGTH:	; 1 bytes @ 0x4
??___xxtofl:	; 1 bytes @ 0x4
	global	?_FC_CAL_I2C_Transaction_Read_1
?_FC_CAL_I2C_Transaction_Read_1:	; 2 bytes @ 0x4
?_FC_CAL_I2C_Transaction_Write_1:	; 2 bytes @ 0x4
	global	FC_CAL_I2C_Transaction_Read_1@Buffer
FC_CAL_I2C_Transaction_Read_1@Buffer:	; 1 bytes @ 0x4
	global	FC_CAL_I2C_Transaction_Write_1@Buffer
FC_CAL_I2C_Transaction_Write_1@Buffer:	; 1 bytes @ 0x4
	global	FC_CAL_UART_Receive_1@delaycnt
FC_CAL_UART_Receive_1@delaycnt:	; 2 bytes @ 0x4
	global	FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL
FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL:	; 2 bytes @ 0x4
	global	___lmul@multiplicand
___lmul@multiplicand:	; 4 bytes @ 0x4
	global	___lldiv@divisor
___lldiv@divisor:	; 4 bytes @ 0x4
	global	___fladd@a
___fladd@a:	; 4 bytes @ 0x4
	global	___fldiv@a
___fldiv@a:	; 4 bytes @ 0x4
	global	___flmul@a
___flmul@a:	; 4 bytes @ 0x4
	ds   1
	global	FC_CAL_I2C_Transaction_Read_1@Size
FC_CAL_I2C_Transaction_Read_1@Size:	; 2 bytes @ 0x5
	global	FC_CAL_I2C_Transaction_Write_1@Size
FC_CAL_I2C_Transaction_Write_1@Size:	; 2 bytes @ 0x5
	global	FCD_01211_RXCB__GetByte@FCL_TEMP
FCD_01211_RXCB__GetByte@FCL_TEMP:	; 2 bytes @ 0x5
	global	FCD_05481_UART1__SendByteArray@FCL_NUMBYTES
FCD_05481_UART1__SendByteArray@FCL_NUMBYTES:	; 2 bytes @ 0x5
	ds   1
	global	FC_CAL_UART_Receive_1@delay1
FC_CAL_UART_Receive_1@delay1:	; 1 bytes @ 0x6
	global	FCI_GETLENGTH@tmp
FCI_GETLENGTH@tmp:	; 2 bytes @ 0x6
	ds   1
?_FCD_01211_RXCB__LookForValue:	; 1 bytes @ 0x7
??_FCD_05481_UART1__SendByteArray:	; 1 bytes @ 0x7
	global	FC_CAL_UART_Receive_1@rxStatus
FC_CAL_UART_Receive_1@rxStatus:	; 1 bytes @ 0x7
	global	FC_CAL_I2C_Transaction_Read_1@Length
FC_CAL_I2C_Transaction_Read_1@Length:	; 2 bytes @ 0x7
	global	FC_CAL_I2C_Transaction_Write_1@Length
FC_CAL_I2C_Transaction_Write_1@Length:	; 2 bytes @ 0x7
	global	FCD_01211_RXCB__LookForValue@FCL_VALUE
FCD_01211_RXCB__LookForValue@FCL_VALUE:	; 2 bytes @ 0x7
	ds   1
??___fladd:	; 1 bytes @ 0x8
??___fldiv:	; 1 bytes @ 0x8
??___flmul:	; 1 bytes @ 0x8
?_FCD_05481_UART1__SendString:	; 1 bytes @ 0x8
??___lmul:	; 1 bytes @ 0x8
??___lldiv:	; 1 bytes @ 0x8
	global	___xxtofl@sign
___xxtofl@sign:	; 1 bytes @ 0x8
	global	FC_CAL_UART_Receive_1@retVal
FC_CAL_UART_Receive_1@retVal:	; 2 bytes @ 0x8
	global	FCD_05481_UART1__SendString@FCL_DATA
FCD_05481_UART1__SendString@FCL_DATA:	; 2 bytes @ 0x8
	global	FCD_05481_UART1__SendByteArray@FCL_IDX
FCD_05481_UART1__SendByteArray@FCL_IDX:	; 2 bytes @ 0x8
	global	___lmul@product
___lmul@product:	; 4 bytes @ 0x8
	global	___lldiv@quotient
___lldiv@quotient:	; 4 bytes @ 0x8
	ds   1
??_FC_CAL_I2C_Transaction_Read_1:	; 1 bytes @ 0x9
??_FC_CAL_I2C_Transaction_Write_1:	; 1 bytes @ 0x9
	global	___xxtofl@exp
___xxtofl@exp:	; 1 bytes @ 0x9
	global	FCD_01211_RXCB__LookForValue@FCLsz_VALUE
FCD_01211_RXCB__LookForValue@FCLsz_VALUE:	; 2 bytes @ 0x9
	ds   1
	global	FC_CAL_UART_Receive_1@nTimeout
FC_CAL_UART_Receive_1@nTimeout:	; 1 bytes @ 0xA
	global	FCD_05481_UART1__SendString@FCLsz_DATA
FCD_05481_UART1__SendString@FCLsz_DATA:	; 2 bytes @ 0xA
	global	___xxtofl@arg
___xxtofl@arg:	; 4 bytes @ 0xA
	ds   1
	global	FC_CAL_I2C_Transaction_Read_1@fail
FC_CAL_I2C_Transaction_Read_1@fail:	; 1 bytes @ 0xB
	global	FC_CAL_I2C_Transaction_Write_1@sendStop
FC_CAL_I2C_Transaction_Write_1@sendStop:	; 1 bytes @ 0xB
	global	FC_CAL_UART_Receive_1@regcheck
FC_CAL_UART_Receive_1@regcheck:	; 1 bytes @ 0xB
	global	FCD_01211_RXCB__LookForValue@FCL_NUMCHARS
FCD_01211_RXCB__LookForValue@FCL_NUMCHARS:	; 1 bytes @ 0xB
	ds   1
??_FCD_05481_UART1__SendString:	; 1 bytes @ 0xC
	global	FCD_01211_RXCB__LookForValue@FCL_REMOVECONTENT
FCD_01211_RXCB__LookForValue@FCL_REMOVECONTENT:	; 1 bytes @ 0xC
	global	___lldiv@counter
___lldiv@counter:	; 1 bytes @ 0xC
	global	___fladd@signs
___fladd@signs:	; 1 bytes @ 0xC
	global	___flmul@sign
___flmul@sign:	; 1 bytes @ 0xC
	global	FC_CAL_I2C_Transaction_Read_1@n
FC_CAL_I2C_Transaction_Read_1@n:	; 2 bytes @ 0xC
	global	FC_CAL_I2C_Transaction_Write_1@n
FC_CAL_I2C_Transaction_Write_1@n:	; 2 bytes @ 0xC
	global	___fldiv@rem
___fldiv@rem:	; 4 bytes @ 0xC
	ds   1
?_FCI_TOSTRING:	; 1 bytes @ 0xD
	global	FCD_01211_RXCB__LookForValue@FCL_RESETFIND
FCD_01211_RXCB__LookForValue@FCL_RESETFIND:	; 1 bytes @ 0xD
	global	___fladd@aexp
___fladd@aexp:	; 1 bytes @ 0xD
	global	___flmul@aexp
___flmul@aexp:	; 1 bytes @ 0xD
	global	FCI_TOSTRING@iSrc1
FCI_TOSTRING@iSrc1:	; 4 bytes @ 0xD
	ds   1
??_FCD_01c01_temp_hum_sensor__Sample:	; 1 bytes @ 0xE
??_FCD_01211_RXCB__LookForValue:	; 1 bytes @ 0xE
	global	___fladd@bexp
___fladd@bexp:	; 1 bytes @ 0xE
	global	___flmul@grs
___flmul@grs:	; 4 bytes @ 0xE
	ds   1
	global	___fladd@grs
___fladd@grs:	; 1 bytes @ 0xF
	global	FCD_05481_UART1__SendString@FCL_LEN
FCD_05481_UART1__SendString@FCL_LEN:	; 2 bytes @ 0xF
	ds   1
	global	FCD_01211_RXCB__LookForValue@FCR_RETVAL
FCD_01211_RXCB__LookForValue@FCR_RETVAL:	; 1 bytes @ 0x10
	global	___fldiv@sign
___fldiv@sign:	; 1 bytes @ 0x10
	ds   1
	global	FCI_TOSTRING@sDst
FCI_TOSTRING@sDst:	; 1 bytes @ 0x11
	global	FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX
FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX:	; 2 bytes @ 0x11
	global	FCD_05481_UART1__SendString@FCL_IDX
FCD_05481_UART1__SendString@FCL_IDX:	; 2 bytes @ 0x11
	global	___fldiv@new_exp
___fldiv@new_exp:	; 2 bytes @ 0x11
	global	FCD_01c01_temp_hum_sensor__Sample@FCL_DATA
FCD_01c01_temp_hum_sensor__Sample@FCL_DATA:	; 6 bytes @ 0x11
	ds   1
	global	___flmul@bexp
___flmul@bexp:	; 1 bytes @ 0x12
	global	FCI_TOSTRING@iDst_len
FCI_TOSTRING@iDst_len:	; 2 bytes @ 0x12
	ds   1
	global	FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA
FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA:	; 1 bytes @ 0x13
	global	___fldiv@grs
___fldiv@grs:	; 4 bytes @ 0x13
	global	___flmul@prod
___flmul@prod:	; 4 bytes @ 0x13
	ds   1
??_FCI_TOSTRING:	; 1 bytes @ 0x14
	global	FCD_01211_RXCB__LookForValue@FCL_NUMBYTES
FCD_01211_RXCB__LookForValue@FCL_NUMBYTES:	; 1 bytes @ 0x14
	ds   1
	global	FCD_01211_RXCB__LookForValue@FCL_DATAINDEX
FCD_01211_RXCB__LookForValue@FCL_DATAINDEX:	; 2 bytes @ 0x15
	ds   1
	global	FCI_TOSTRING@tmp1
FCI_TOSTRING@tmp1:	; 1 bytes @ 0x16
	ds   1
??_FCD_029f1_gLCD_EB3__ReceiveReply:	; 1 bytes @ 0x17
	global	FCI_TOSTRING@idx
FCI_TOSTRING@idx:	; 1 bytes @ 0x17
	global	FCD_01c01_temp_hum_sensor__Sample@FCL_RET
FCD_01c01_temp_hum_sensor__Sample@FCL_RET:	; 1 bytes @ 0x17
	global	___fldiv@bexp
___fldiv@bexp:	; 1 bytes @ 0x17
	global	___flmul@temp
___flmul@temp:	; 2 bytes @ 0x17
	ds   1
	global	FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT
FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT:	; 1 bytes @ 0x18
	global	___fldiv@aexp
___fldiv@aexp:	; 1 bytes @ 0x18
	global	FCI_TOSTRING@iSrc
FCI_TOSTRING@iSrc:	; 4 bytes @ 0x18
	ds   1
??_FCD_01c01_temp_hum_sensor__Initialise:	; 1 bytes @ 0x19
	global	?_FCD_01c01_temp_hum_sensor__GetTemperatureReal
?_FCD_01c01_temp_hum_sensor__GetTemperatureReal:	; 4 bytes @ 0x19
	global	FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE
FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE:	; 1 bytes @ 0x19
	ds   1
	global	FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY
FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY:	; 1 bytes @ 0x1A
	ds   1
	global	FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL
FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL:	; 1 bytes @ 0x1B
	ds   1
	global	FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE
FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE:	; 1 bytes @ 0x1C
	global	FCI_TOSTRING@top
FCI_TOSTRING@top:	; 4 bytes @ 0x1C
	ds   1
??_FCD_01c01_temp_hum_sensor__GetTemperatureReal:	; 1 bytes @ 0x1D
	global	FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX
FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX:	; 2 bytes @ 0x1D
	global	FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL
FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL:	; 4 bytes @ 0x1D
	ds   2
??_FCD_029f1_gLCD_EB3__SendCommand:	; 1 bytes @ 0x1F
?_FCD_029f1_gLCD_EB3__SendCommandWithString:	; 1 bytes @ 0x1F
	global	FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR
FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR:	; 2 bytes @ 0x1F
	ds   1
??_FCD_029f1_gLCD_EB3__SetDisplayOrientation:	; 1 bytes @ 0x20
??_FCD_029f1_gLCD_EB3__ClearDisplay:	; 1 bytes @ 0x20
?_FCD_029f1_gLCD_EB3__SetBackgroundColour:	; 1 bytes @ 0x20
?_FCD_029f1_gLCD_EB3__SetForegroundColour:	; 1 bytes @ 0x20
	global	FCD_029f1_gLCD_EB3__SetDisplayOrientation@FCL_ORIENTATION
FCD_029f1_gLCD_EB3__SetDisplayOrientation@FCL_ORIENTATION:	; 1 bytes @ 0x20
	global	FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_GREEN
FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_GREEN:	; 1 bytes @ 0x20
	global	FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_GREEN
FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_GREEN:	; 1 bytes @ 0x20
	ds   1
	global	?___fltol
?___fltol:	; 4 bytes @ 0x21
	global	FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_BLUE
FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_BLUE:	; 1 bytes @ 0x21
	global	FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_BLUE
FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_BLUE:	; 1 bytes @ 0x21
	global	FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR
FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR:	; 2 bytes @ 0x21
	global	___fltol@f1
___fltol@f1:	; 4 bytes @ 0x21
	ds   1
??_FCD_029f1_gLCD_EB3__SetBackgroundColour:	; 1 bytes @ 0x22
??_FCD_029f1_gLCD_EB3__SetForegroundColour:	; 1 bytes @ 0x22
	global	FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_RED
FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_RED:	; 1 bytes @ 0x22
	global	FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_RED
FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_RED:	; 1 bytes @ 0x22
	global	FCD_029f1_gLCD_EB3__ClearDisplay@FCL_X
FCD_029f1_gLCD_EB3__ClearDisplay@FCL_X:	; 2 bytes @ 0x22
	ds   1
??_FCD_029f1_gLCD_EB3__SendCommandWithString:	; 1 bytes @ 0x23
	ds   1
?_FCD_029f1_gLCD_EB3__Print:	; 1 bytes @ 0x24
?_FCD_029f1_gLCD_EB3__SetExternalFont:	; 1 bytes @ 0x24
	global	FCD_029f1_gLCD_EB3__Print@FCL_STR
FCD_029f1_gLCD_EB3__Print@FCL_STR:	; 1 bytes @ 0x24
	global	FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR
FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR:	; 2 bytes @ 0x24
	ds   1
??___fltol:	; 1 bytes @ 0x25
	global	FCD_029f1_gLCD_EB3__Print@FCLsz_STR
FCD_029f1_gLCD_EB3__Print@FCLsz_STR:	; 2 bytes @ 0x25
	ds   1
	global	FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR
FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR:	; 2 bytes @ 0x26
	ds   1
	global	FCD_029f1_gLCD_EB3__Print@FCL_X1
FCD_029f1_gLCD_EB3__Print@FCL_X1:	; 2 bytes @ 0x27
	ds   1
	global	FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING
FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING:	; 1 bytes @ 0x28
	ds   1
	global	FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH
FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH:	; 1 bytes @ 0x29
	global	___fltol@sign1
___fltol@sign1:	; 1 bytes @ 0x29
	global	FCD_029f1_gLCD_EB3__Print@FCL_Y1
FCD_029f1_gLCD_EB3__Print@FCL_Y1:	; 2 bytes @ 0x29
	ds   1
??_FCD_029f1_gLCD_EB3__SetExternalFont:	; 1 bytes @ 0x2A
	global	FCD_029f1_gLCD_EB3__SetExternalFont@FCL_FONT
FCD_029f1_gLCD_EB3__SetExternalFont@FCL_FONT:	; 1 bytes @ 0x2A
	global	___fltol@exp1
___fltol@exp1:	; 1 bytes @ 0x2A
	ds   1
??_FCD_029f1_gLCD_EB3__Initialise:	; 1 bytes @ 0x2B
	global	?_FCD_01c01_temp_hum_sensor__GetTemperatureInt
?_FCD_01c01_temp_hum_sensor__GetTemperatureInt:	; 2 bytes @ 0x2B
	global	FCD_029f1_gLCD_EB3__Print@FCL_FONT
FCD_029f1_gLCD_EB3__Print@FCL_FONT:	; 1 bytes @ 0x2B
	ds   1
	global	FCD_029f1_gLCD_EB3__Print@FCL_TRANSPARENT
FCD_029f1_gLCD_EB3__Print@FCL_TRANSPARENT:	; 1 bytes @ 0x2C
	ds   1
??_FCD_029f1_gLCD_EB3__Print:	; 1 bytes @ 0x2D
?_FCD_029f1_gLCD_EB3__PrintNumber:	; 1 bytes @ 0x2D
??_FCD_01c01_temp_hum_sensor__GetTemperatureInt:	; 1 bytes @ 0x2D
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER
FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER:	; 2 bytes @ 0x2D
	global	FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL
FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL:	; 2 bytes @ 0x2D
	ds   2
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_X
FCD_029f1_gLCD_EB3__PrintNumber@FCL_X:	; 2 bytes @ 0x2F
	ds   2
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y
FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y:	; 2 bytes @ 0x31
	ds   2
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_FONT
FCD_029f1_gLCD_EB3__PrintNumber@FCL_FONT:	; 1 bytes @ 0x33
	ds   1
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_TRANSPARENT
FCD_029f1_gLCD_EB3__PrintNumber@FCL_TRANSPARENT:	; 1 bytes @ 0x34
	ds   1
??_FCD_029f1_gLCD_EB3__PrintNumber:	; 1 bytes @ 0x35
	global	FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP
FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP:	; 8 bytes @ 0x35
	ds   8
??_main:	; 1 bytes @ 0x3D
;!
;!Data Sizes:
;!    Strings     43
;!    Constant    1575
;!    Data        4
;!    BSS         184
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           94     61      93
;!    BANK0           160      0     156
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
;!    FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR	PTR unsigned char  size(2) Largest target is 10
;!		 -> STR_8(CODE[10]), STR_7(CODE[10]), STR_6(CODE[10]), STR_5(CODE[10]), 
;!
;!    FCD_029f1_gLCD_EB3__Print@FCL_STR	PTR unsigned char  size(1) Largest target is 8
;!		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(COMRAM[8]), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), 
;!
;!    FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR	PTR unsigned char  size(2) Largest target is 10
;!		 -> STR_8(CODE[10]), STR_7(CODE[10]), STR_6(CODE[10]), STR_5(CODE[10]), 
;!		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(COMRAM[8]), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), 
;!
;!    FCD_05481_UART1__SendByteArray@FCL_DATA	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCV_029f1_gLCD_EB3__COMMANDTX(BANK0[20]), 
;!
;!    FCD_05481_UART1__SendString@FCL_DATA	PTR unsigned char  size(2) Largest target is 20
;!		 -> STR_8(CODE[10]), STR_7(CODE[10]), STR_6(CODE[10]), STR_5(CODE[10]), 
;!		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(COMRAM[8]), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), STR_4(CODE[1]), STR_3(CODE[1]), 
;!		 -> FCD_05481_UART1__SendNumber@FCL_NUMSTR(COMRAM[20]), 
;!
;!    FCD_01211_RXCB__LookForValue@FCL_VALUE	PTR unsigned char  size(2) Largest target is 3
;!		 -> STR_2(CODE[3]), 
;!
;!    FC_CAL_I2C_Transaction_Write_1@Buffer	PTR unsigned char  size(1) Largest target is 6
;!		 -> FCD_01c01_temp_hum_sensor__Sample@FCL_DATA(COMRAM[6]), 
;!
;!    FC_CAL_I2C_Transaction_Read_1@Buffer	PTR unsigned char  size(1) Largest target is 6
;!		 -> FCD_01c01_temp_hum_sensor__Sample@FCL_DATA(COMRAM[6]), 
;!
;!    sp__FCI_NUMBER_TO_HEX	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_FLOAT_TO_STRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(COMRAM[8]), FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMFLOATARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_TOSTRING	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), FCD_05481_UART1__SendNumber@FCL_NUMSTR(COMRAM[20]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMINTARRAY@sTemp(COMRAM[20]), 
;!
;!    FCI_TOSTRING@sDst	PTR unsigned char  size(1) Largest target is 20
;!		 -> FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), FCD_05481_UART1__SendNumber@FCL_NUMSTR(COMRAM[20]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_IMPLODEFROMINTARRAY@sTemp(COMRAM[20]), 
;!
;!    sp__FCI_RIGHTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_LEFTSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    sp__FCI_MIDSTRING	PTR unsigned char  size(2) Largest target is 0
;!
;!    FCI_GETLENGTH@sStr1	PTR unsigned char  size(2) Largest target is 20
;!		 -> STR_8(CODE[10]), STR_7(CODE[10]), STR_6(CODE[10]), STR_5(CODE[10]), 
;!		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(COMRAM[8]), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(COMRAM[8]), STR_4(CODE[1]), STR_3(CODE[1]), 
;!		 -> FCD_05481_UART1__SendNumber@FCL_NUMSTR(COMRAM[20]), FCI_INTTOFORMATTEDSTRING@sTemp(COMRAM[20]), FCI_FLOATTOFORMATTEDSTRING@sTemp(COMRAM[20]), 
;!


;!
;!Critical Paths under _main in COMRAM
;!
;!    _main->_FCD_029f1_gLCD_EB3__PrintNumber
;!    _FCD_029f1_gLCD_EB3__PrintNumber->_FCD_029f1_gLCD_EB3__Print
;!    _FCI_TOSTRING->___lldiv
;!    _FCD_029f1_gLCD_EB3__Print->_FCD_029f1_gLCD_EB3__SendCommandWithString
;!    _FCD_029f1_gLCD_EB3__Initialise->_FCD_029f1_gLCD_EB3__SetExternalFont
;!    _delay_s->_delay_ms
;!    _FCD_029f1_gLCD_EB3__SetForegroundColour->_FCD_029f1_gLCD_EB3__SendCommand
;!    _FCD_029f1_gLCD_EB3__SetExternalFont->_FCD_029f1_gLCD_EB3__SendCommandWithString
;!    _FCD_029f1_gLCD_EB3__SendCommandWithString->_FCD_029f1_gLCD_EB3__ReceiveReply
;!    _FCD_05481_UART1__SendString->_FCI_GETLENGTH
;!    _FCD_029f1_gLCD_EB3__SetDisplayOrientation->_FCD_029f1_gLCD_EB3__SendCommand
;!    _FCD_029f1_gLCD_EB3__SetBackgroundColour->_FCD_029f1_gLCD_EB3__SendCommand
;!    _FCD_029f1_gLCD_EB3__ClearDisplay->_FCD_029f1_gLCD_EB3__SendCommand
;!    _FCD_029f1_gLCD_EB3__SendCommand->_FCD_029f1_gLCD_EB3__ReceiveReply
;!    _FCD_05481_UART1__SendByteArray->_FC_CAL_UART_Send_1
;!    _FCD_029f1_gLCD_EB3__ReceiveReply->_FCD_01211_RXCB__LookForValue
;!    _FCD_01211_RXCB__LookForValue->_FCD_01211_RXCB__GetByte
;!    _FCD_01c01_temp_hum_sensor__Initialise->_FCD_01c01_temp_hum_sensor__Sample
;!    _FCD_01c01_temp_hum_sensor__GetTemperatureInt->___fltol
;!    ___fltol->_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;!    _FCD_01c01_temp_hum_sensor__GetTemperatureReal->_FCD_01c01_temp_hum_sensor__Sample
;!    _FCD_01c01_temp_hum_sensor__GetTemperatureReal->___fldiv
;!    _FCD_01c01_temp_hum_sensor__GetTemperatureReal->___flmul
;!    _FCD_01c01_temp_hum_sensor__Sample->_FC_CAL_I2C_Transaction_Read_1
;!    _FCD_01c01_temp_hum_sensor__Sample->_FC_CAL_I2C_Transaction_Write_1
;!    _FC_CAL_I2C_Transaction_Write_1->_FC_CAL_I2C_Master_TxByte_1
;!    _FC_CAL_I2C_Transaction_Read_1->_FC_CAL_I2C_Master_RxByte_1
;!    _FC_CAL_I2C_Transaction_Read_1->_FC_CAL_I2C_Master_TxByte_1
;!    _FC_CAL_I2C_Master_TxByte_1->_delay_us
;!    _FC_CAL_I2C_Master_Stop_1->_delay_us
;!    _FC_CAL_I2C_Master_Start_1->_delay_us
;!    _FC_CAL_I2C_Master_RxByte_1->_delay_us
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
;! (0) _main                                                 0     0      0   63698
;!_FCD_01c01_temp_hum_sensor__GetTempe
;!_FCD_01c01_temp_hum_sensor__Initiali
;!     _FCD_029f1_gLCD_EB3__Initialise
;!    _FCD_029f1_gLCD_EB3__PrintNumber
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) _FCD_029f1_gLCD_EB3__PrintNumber                     16     8      8   17589
;!                                             45 COMRAM    16     8      8
;!          _FCD_029f1_gLCD_EB3__Print
;!                       _FCI_TOSTRING
;! ---------------------------------------------------------------------------------
;! (2) _FCI_TOSTRING                                        19    12      7    6090
;!                                             13 COMRAM    19    12      7
;!                            ___lldiv
;!                             ___lmul
;! ---------------------------------------------------------------------------------
;! (3) ___lmul                                              12     4      8    3520
;!                                              0 COMRAM    12     4      8
;! ---------------------------------------------------------------------------------
;! (3) ___lldiv                                             13     5      8    1222
;!                                              0 COMRAM    13     5      8
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__Print                            9     0      9   10957
;!                                             36 COMRAM     9     0      9
;!_FCD_029f1_gLCD_EB3__SendCommandWith
;! ---------------------------------------------------------------------------------
;! (1) _FCD_029f1_gLCD_EB3__Initialise                       1     1      0   33456
;!   _FCD_029f1_gLCD_EB3__ClearDisplay
;!_FCD_029f1_gLCD_EB3__SetBackgroundCo
;!_FCD_029f1_gLCD_EB3__SetDisplayOrien
;!_FCD_029f1_gLCD_EB3__SetExternalFont
;!_FCD_029f1_gLCD_EB3__SetForegroundCo
;!                 _FC_CAL_UART_Init_1
;!                            _delay_s
;! ---------------------------------------------------------------------------------
;! (2) _delay_s                                              2     2      0      45
;!                                              2 COMRAM     2     2      0
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (2) _FC_CAL_UART_Init_1                                   0     0      0       0
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__SetForegroundColour              3     1      2    5638
;!                                             32 COMRAM     3     1      2
;!    _FCD_029f1_gLCD_EB3__SendCommand
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__SetExternalFont                  7     1      6   11271
;!                                             36 COMRAM     7     1      6
;!_FCD_029f1_gLCD_EB3__SendCommandWith
;! ---------------------------------------------------------------------------------
;! (3) _FCD_029f1_gLCD_EB3__SendCommandWithString            5     1      4    9945
;!                                             31 COMRAM     5     1      4
;!   _FCD_029f1_gLCD_EB3__ReceiveReply
;!     _FCD_05481_UART1__SendByteArray
;!        _FCD_05481_UART1__SendString
;!                 _FC_CAL_UART_Send_1
;! ---------------------------------------------------------------------------------
;! (4) _FCD_05481_UART1__SendString                         11     7      4    3673
;!                                              8 COMRAM    11     7      4
;!                      _FCI_GETLENGTH
;!                 _FC_CAL_UART_Send_1
;! ---------------------------------------------------------------------------------
;! (5) _FCI_GETLENGTH                                        8     4      4    1776
;!                                              0 COMRAM     8     4      4
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__SetDisplayOrientation            1     1      0    5442
;!                                             32 COMRAM     1     1      0
;!    _FCD_029f1_gLCD_EB3__SendCommand
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__SetBackgroundColour              3     1      2    5638
;!                                             32 COMRAM     3     1      2
;!    _FCD_029f1_gLCD_EB3__SendCommand
;! ---------------------------------------------------------------------------------
;! (2) _FCD_029f1_gLCD_EB3__ClearDisplay                     5     5      0    5422
;!                                             32 COMRAM     4     4      0
;!    _FCD_029f1_gLCD_EB3__SendCommand
;! ---------------------------------------------------------------------------------
;! (3) _FCD_029f1_gLCD_EB3__SendCommand                      1     1      0    5420
;!                                             31 COMRAM     1     1      0
;!   _FCD_029f1_gLCD_EB3__ReceiveReply
;!     _FCD_05481_UART1__SendByteArray
;!                 _FC_CAL_UART_Send_1
;! ---------------------------------------------------------------------------------
;! (4) _FCD_05481_UART1__SendByteArray                       8     3      5    2345
;!                                              2 COMRAM     8     3      5
;!                 _FC_CAL_UART_Send_1
;! ---------------------------------------------------------------------------------
;! (4) _FC_CAL_UART_Send_1                                   2     0      2    1210
;!                                              0 COMRAM     2     0      2
;! ---------------------------------------------------------------------------------
;! (4) _FCD_029f1_gLCD_EB3__ReceiveReply                     8     8      0    1858
;!                                             23 COMRAM     8     8      0
;!        _FCD_01211_RXCB__FlushBuffer
;!       _FCD_01211_RXCB__LookForValue
;!            _FCD_01211_RXCB__PutByte
;!              _FC_CAL_UART_Receive_1
;! ---------------------------------------------------------------------------------
;! (5) _FC_CAL_UART_Receive_1                               12    10      2     352
;!                                              0 COMRAM    12    10      2
;! ---------------------------------------------------------------------------------
;! (5) _FCD_01211_RXCB__PutByte                              6     6      0      98
;!                                              0 COMRAM     4     4      0
;! ---------------------------------------------------------------------------------
;! (5) _FCD_01211_RXCB__LookForValue                        16     9      7    1154
;!                                              7 COMRAM    16     9      7
;!            _FCD_01211_RXCB__GetByte
;!     _FCD_01211_RXCB__GetNumberBytes
;! ---------------------------------------------------------------------------------
;! (6) _FCD_01211_RXCB__GetNumberBytes                       6     4      2      25
;!                                              0 COMRAM     6     4      2
;! ---------------------------------------------------------------------------------
;! (6) _FCD_01211_RXCB__GetByte                              7     5      2      70
;!                                              0 COMRAM     7     5      2
;! ---------------------------------------------------------------------------------
;! (5) _FCD_01211_RXCB__FlushBuffer                          0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _FCD_01c01_temp_hum_sensor__Initialise                1     1      0    1752
;!                                             25 COMRAM     1     1      0
;!  _FCD_01c01_temp_hum_sensor__Sample
;!      _FC_CAL_I2C_Transaction_Init_1
;! ---------------------------------------------------------------------------------
;! (2) _FC_CAL_I2C_Transaction_Init_1                        1     1      0      15
;!                                              0 COMRAM     1     1      0
;!           _FC_CAL_I2C_Master_Init_1
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_I2C_Master_Init_1                             0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _FCD_01c01_temp_hum_sensor__GetTemperatureInt         8     6      2   10886
;!                                             43 COMRAM     4     2      2
;!_FCD_01c01_temp_hum_sensor__GetTempe
;!                            ___fltol
;! ---------------------------------------------------------------------------------
;! (2) ___fltol                                             10     6      4     557
;!                                             33 COMRAM    10     6      4
;!_FCD_01c01_temp_hum_sensor__GetTempe (ARG)
;! ---------------------------------------------------------------------------------
;! (2) _FCD_01c01_temp_hum_sensor__GetTemperatureReal       10     6      4   10306
;!                                             25 COMRAM     8     4      4
;!  _FCD_01c01_temp_hum_sensor__Sample
;!                            ___fladd
;!                            ___fldiv
;!                            ___flmul
;!                           ___xxtofl
;! ---------------------------------------------------------------------------------
;! (3) ___xxtofl                                            14    10      4     915
;!                                              0 COMRAM    14    10      4
;! ---------------------------------------------------------------------------------
;! (3) ___flmul                                             25    17      8    2401
;!                                              0 COMRAM    25    17      8
;! ---------------------------------------------------------------------------------
;! (3) ___fldiv                                             25    17      8    1929
;!                                              0 COMRAM    25    17      8
;! ---------------------------------------------------------------------------------
;! (3) ___fladd                                             16     8      8    3170
;!                                              0 COMRAM    16     8      8
;! ---------------------------------------------------------------------------------
;! (2) _FCD_01c01_temp_hum_sensor__Sample                   11    11      0    1729
;!                                             14 COMRAM    11    11      0
;!      _FC_CAL_I2C_Transaction_Read_1
;!     _FC_CAL_I2C_Transaction_Write_1
;!                           _delay_ms
;! ---------------------------------------------------------------------------------
;! (1) _delay_ms                                             2     2      0      15
;!                                              0 COMRAM     2     2      0
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_I2C_Transaction_Write_1                      10     5      5     699
;!                                              4 COMRAM    10     5      5
;!          _FC_CAL_I2C_Master_Start_1
;!           _FC_CAL_I2C_Master_Stop_1
;!         _FC_CAL_I2C_Master_TxByte_1
;! ---------------------------------------------------------------------------------
;! (3) _FC_CAL_I2C_Transaction_Read_1                       10     5      5     796
;!                                              4 COMRAM    10     5      5
;!         _FC_CAL_I2C_Master_RxByte_1
;!          _FC_CAL_I2C_Master_Start_1
;!           _FC_CAL_I2C_Master_Stop_1
;!         _FC_CAL_I2C_Master_TxByte_1
;! ---------------------------------------------------------------------------------
;! (4) _FC_CAL_I2C_Master_TxByte_1                           3     3      0     120
;!                                              1 COMRAM     3     3      0
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (4) _FC_CAL_I2C_Master_Stop_1                             0     0      0      45
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (4) _FC_CAL_I2C_Master_Start_1                            0     0      0      45
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (4) _FC_CAL_I2C_Master_RxByte_1                           3     3      0     135
;!                                              1 COMRAM     3     3      0
;!                           _delay_us
;! ---------------------------------------------------------------------------------
;! (5) _delay_us                                             1     1      0      45
;!                                              0 COMRAM     1     1      0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 6
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (7) _myisr                                                0     0      0       0
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 7
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _FCD_01c01_temp_hum_sensor__GetTemperatureInt
;!     _FCD_01c01_temp_hum_sensor__GetTemperatureReal
;!       _FCD_01c01_temp_hum_sensor__Sample
;!         _FC_CAL_I2C_Transaction_Read_1
;!           _FC_CAL_I2C_Master_RxByte_1
;!             _delay_us
;!           _FC_CAL_I2C_Master_Start_1
;!             _delay_us
;!           _FC_CAL_I2C_Master_Stop_1
;!             _delay_us
;!           _FC_CAL_I2C_Master_TxByte_1
;!             _delay_us
;!         _FC_CAL_I2C_Transaction_Write_1
;!           _FC_CAL_I2C_Master_Start_1
;!             _delay_us
;!           _FC_CAL_I2C_Master_Stop_1
;!             _delay_us
;!           _FC_CAL_I2C_Master_TxByte_1
;!             _delay_us
;!         _delay_ms
;!       ___fladd
;!       ___fldiv
;!       ___flmul
;!       ___xxtofl
;!     ___fltol
;!       _FCD_01c01_temp_hum_sensor__GetTemperatureReal (ARG)
;!         _FCD_01c01_temp_hum_sensor__Sample
;!           _FC_CAL_I2C_Transaction_Read_1
;!             _FC_CAL_I2C_Master_RxByte_1
;!               _delay_us
;!             _FC_CAL_I2C_Master_Start_1
;!               _delay_us
;!             _FC_CAL_I2C_Master_Stop_1
;!               _delay_us
;!             _FC_CAL_I2C_Master_TxByte_1
;!               _delay_us
;!           _FC_CAL_I2C_Transaction_Write_1
;!             _FC_CAL_I2C_Master_Start_1
;!               _delay_us
;!             _FC_CAL_I2C_Master_Stop_1
;!               _delay_us
;!             _FC_CAL_I2C_Master_TxByte_1
;!               _delay_us
;!           _delay_ms
;!         ___fladd
;!         ___fldiv
;!         ___flmul
;!         ___xxtofl
;!   _FCD_01c01_temp_hum_sensor__Initialise
;!     _FCD_01c01_temp_hum_sensor__Sample
;!       _FC_CAL_I2C_Transaction_Read_1
;!         _FC_CAL_I2C_Master_RxByte_1
;!           _delay_us
;!         _FC_CAL_I2C_Master_Start_1
;!           _delay_us
;!         _FC_CAL_I2C_Master_Stop_1
;!           _delay_us
;!         _FC_CAL_I2C_Master_TxByte_1
;!           _delay_us
;!       _FC_CAL_I2C_Transaction_Write_1
;!         _FC_CAL_I2C_Master_Start_1
;!           _delay_us
;!         _FC_CAL_I2C_Master_Stop_1
;!           _delay_us
;!         _FC_CAL_I2C_Master_TxByte_1
;!           _delay_us
;!       _delay_ms
;!     _FC_CAL_I2C_Transaction_Init_1
;!       _FC_CAL_I2C_Master_Init_1
;!   _FCD_029f1_gLCD_EB3__Initialise
;!     _FCD_029f1_gLCD_EB3__ClearDisplay
;!       _FCD_029f1_gLCD_EB3__SendCommand
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FCD_029f1_gLCD_EB3__SetBackgroundColour
;!       _FCD_029f1_gLCD_EB3__SendCommand
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FCD_029f1_gLCD_EB3__SetDisplayOrientation
;!       _FCD_029f1_gLCD_EB3__SendCommand
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FCD_029f1_gLCD_EB3__SetExternalFont
;!       _FCD_029f1_gLCD_EB3__SendCommandWithString
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FCD_05481_UART1__SendString
;!           _FCI_GETLENGTH
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FCD_029f1_gLCD_EB3__SetForegroundColour
;!       _FCD_029f1_gLCD_EB3__SendCommand
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FC_CAL_UART_Init_1
;!     _delay_s
;!       _delay_ms
;!   _FCD_029f1_gLCD_EB3__PrintNumber
;!     _FCD_029f1_gLCD_EB3__Print
;!       _FCD_029f1_gLCD_EB3__SendCommandWithString
;!         _FCD_029f1_gLCD_EB3__ReceiveReply
;!           _FCD_01211_RXCB__FlushBuffer
;!           _FCD_01211_RXCB__LookForValue
;!             _FCD_01211_RXCB__GetByte
;!             _FCD_01211_RXCB__GetNumberBytes
;!           _FCD_01211_RXCB__PutByte
;!           _FC_CAL_UART_Receive_1
;!         _FCD_05481_UART1__SendByteArray
;!           _FC_CAL_UART_Send_1
;!         _FCD_05481_UART1__SendString
;!           _FCI_GETLENGTH
;!           _FC_CAL_UART_Send_1
;!         _FC_CAL_UART_Send_1
;!     _FCI_TOSTRING
;!       ___lldiv
;!       ___lmul
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
;!BANK0               A0      0      9C       5       97.5%
;!BITCOMRAM           5E      0       0       0        0.0%
;!COMRAM              5E     3D      5D       1       98.9%
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
;!ABS                  0      0      F9       8        0.0%
;!DATA                 0      0      F9       3        0.0%
;!CODE                 0      0       0       0        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 4317 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, prodl, prodh, cstack
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
;; Hardware stack levels required when called:    7
;; This function calls:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureInt
;;		_FCD_01c01_temp_hum_sensor__Initialise
;;		_FCD_029f1_gLCD_EB3__Initialise
;;		_FCD_029f1_gLCD_EB3__PrintNumber
;;		_delay_ms
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	4317
global __ptext0
__ptext0:
psect	text0
	file	"BL0144 dig temp sensor - PIC.c"
	line	4317
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	callstack 24
	line	4323
	
l4723:
	movlw	low(0)
	movlb	14	; () banked
	movwf	((3730))&0ffh	;volatile
	line	4324
	movlw	low(0)
	movwf	((3738))&0ffh	;volatile
	line	4325
	movlw	low(0)
	movwf	((3751))&0ffh	;volatile
	line	4326
	movlw	low(0)
	movwf	((3759))&0ffh	;volatile
	line	4327
	movlw	low(0)
	movwf	((3764))&0ffh	;volatile
	line	4328
	movlw	low(0)
	movwf	((3772))&0ffh	;volatile
	line	4331
	movlw	low(031h)
	movwf	((3601))&0ffh	;volatile
	line	4332
	movlw	low(0Eh)
	movwf	((3714))&0ffh	;volatile
	line	4333
	movlw	low(033h)
	movwf	((3607))&0ffh	;volatile
	line	4334
	movlw	low(014h)
	movwf	((3716))&0ffh	;volatile
	line	4340
	
l4725:; BSR set to: 14

	call	_FCD_029f1_gLCD_EB3__Initialise	;wreg free
	line	4343
	
l4727:
	call	_FCD_01c01_temp_hum_sensor__Initialise	;wreg free
	line	4349
	
l4729:
	call	_FCD_01c01_temp_hum_sensor__GetTemperatureInt	;wreg free
	movff	0+?_FCD_01c01_temp_hum_sensor__GetTemperatureInt,(c:_FCV_TEMPINT)	;volatile
	movff	1+?_FCD_01c01_temp_hum_sensor__GetTemperatureInt,(c:_FCV_TEMPINT+1)	;volatile
	line	4352
	
l4731:
	movff	(c:_FCV_TEMPINT),(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER)	;volatile
	movff	(c:_FCV_TEMPINT+1),(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER+1)	;volatile
	movlw	high(096h)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_X+1))^00h,c
	movlw	low(096h)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_X))^00h,c
	movlw	high(03Ch)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y+1))^00h,c
	movlw	low(03Ch)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y))^00h,c
	movlw	low(02h)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_FONT))^00h,c
	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_TRANSPARENT))^00h,c
	call	_FCD_029f1_gLCD_EB3__PrintNumber	;wreg free
	line	4355
	
l4733:
	movlw	(0Ah)&0ffh
	
	call	_delay_ms
	goto	l4729
	global	start
	goto	start
	opt callstack 0
	line	4360
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,89
	global	_FCD_029f1_gLCD_EB3__PrintNumber

;; *************** function _FCD_029f1_gLCD_EB3__PrintNumber *****************
;; Defined at:
;;		line 3154 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_NUMBER      2   45[COMRAM] short 
;;  FCL_X           2   47[COMRAM] unsigned short 
;;  FCL_Y           2   49[COMRAM] unsigned short 
;;  FCL_FONT        1   51[COMRAM] unsigned char 
;;  FCL_TRANSPAR    1   52[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_TEMP        8   53[COMRAM] unsigned char [8]
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        16       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       16 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__Print
;;		_FCI_TOSTRING
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,class=CODE,space=0,reloc=2,group=0
	line	3154
global __ptext1
__ptext1:
psect	text1
	file	"BL0144 dig temp sensor - PIC.c"
	line	3154
	global	__size_of_FCD_029f1_gLCD_EB3__PrintNumber
	__size_of_FCD_029f1_gLCD_EB3__PrintNumber	equ	__end_of_FCD_029f1_gLCD_EB3__PrintNumber-_FCD_029f1_gLCD_EB3__PrintNumber
	
_FCD_029f1_gLCD_EB3__PrintNumber:
;incstack = 0
	opt	callstack 24
	line	3161
	
l4677:
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER),(c:FCI_TOSTRING@iSrc1)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_NUMBER+1),(c:FCI_TOSTRING@iSrc1+1)
	movlw	0
	btfsc	((c:FCI_TOSTRING@iSrc1+1))^00h,c,7
	movlw	-1
	movwf	((c:FCI_TOSTRING@iSrc1+2))^00h,c
	movwf	((c:FCI_TOSTRING@iSrc1+3))^00h,c
		movlw	low(FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP)
	movwf	((c:FCI_TOSTRING@sDst))^00h,c

	movlw	high(08h)
	movwf	((c:FCI_TOSTRING@iDst_len+1))^00h,c
	movlw	low(08h)
	movwf	((c:FCI_TOSTRING@iDst_len))^00h,c
	call	_FCI_TOSTRING	;wreg free
	line	3163
	
l4679:
		movlw	low(FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP)
	movwf	((c:FCD_029f1_gLCD_EB3__Print@FCL_STR))^00h,c

	movlw	high(08h)
	movwf	((c:FCD_029f1_gLCD_EB3__Print@FCLsz_STR+1))^00h,c
	movlw	low(08h)
	movwf	((c:FCD_029f1_gLCD_EB3__Print@FCLsz_STR))^00h,c
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_X),(c:FCD_029f1_gLCD_EB3__Print@FCL_X1)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_X+1),(c:FCD_029f1_gLCD_EB3__Print@FCL_X1+1)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y),(c:FCD_029f1_gLCD_EB3__Print@FCL_Y1)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_Y+1),(c:FCD_029f1_gLCD_EB3__Print@FCL_Y1+1)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_FONT),(c:FCD_029f1_gLCD_EB3__Print@FCL_FONT)
	movff	(c:FCD_029f1_gLCD_EB3__PrintNumber@FCL_TRANSPARENT),(c:FCD_029f1_gLCD_EB3__Print@FCL_TRANSPARENT)
	call	_FCD_029f1_gLCD_EB3__Print	;wreg free
	line	3167
	
l1317:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__PrintNumber
	__end_of_FCD_029f1_gLCD_EB3__PrintNumber:
	signat	_FCD_029f1_gLCD_EB3__PrintNumber,20601
	global	_FCI_TOSTRING

;; *************** function _FCI_TOSTRING *****************
;; Defined at:
;;		line 395 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
;; Parameters:    Size  Location     Type
;;  iSrc1           4   13[COMRAM] long 
;;  sDst            1   17[COMRAM] PTR unsigned char 
;;		 -> FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(8), FCD_05481_UART1__SendNumber@FCL_NUMSTR(20), FCI_INTTOFORMATTEDSTRING@sTemp(20), FCI_IMPLODEFROMINTARRAY@sTemp(20), 
;;  iDst_len        2   18[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  top             4   28[COMRAM] unsigned long 
;;  iSrc            4   24[COMRAM] long 
;;  idx             1   23[COMRAM] unsigned char 
;;  tmp1            1   22[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      PTR unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         7       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:        10       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        19       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       19 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		___lldiv
;;		___lmul
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__PrintNumber
;; This function uses a non-reentrant model
;;
psect	text2,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	395
global __ptext2
__ptext2:
psect	text2
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	395
	global	__size_of_FCI_TOSTRING
	__size_of_FCI_TOSTRING	equ	__end_of_FCI_TOSTRING-_FCI_TOSTRING
	
_FCI_TOSTRING:
;incstack = 0
	opt	callstack 27
	line	399
	
l4487:
	movff	(c:FCI_TOSTRING@iSrc1),(c:FCI_TOSTRING@iSrc)
	movff	(c:FCI_TOSTRING@iSrc1+1),(c:FCI_TOSTRING@iSrc+1)
	movff	(c:FCI_TOSTRING@iSrc1+2),(c:FCI_TOSTRING@iSrc+2)
	movff	(c:FCI_TOSTRING@iSrc1+3),(c:FCI_TOSTRING@iSrc+3)
	line	402
	
l4489:
	movlw	low(03B9ACA00h)
	movwf	((c:FCI_TOSTRING@top))^00h,c
	movlw	high(03B9ACA00h)
	movwf	((c:FCI_TOSTRING@top+1))^00h,c
	movlw	low highword(03B9ACA00h)
	movwf	((c:FCI_TOSTRING@top+2))^00h,c
	movlw	high highword(03B9ACA00h)
	movwf	((c:FCI_TOSTRING@top+3))^00h,c
	line	407
	movlw	low(0)
	movwf	((c:FCI_TOSTRING@idx))^00h,c
	line	409
	
l4491:
	movf	((c:FCI_TOSTRING@iDst_len))^00h,c,w
iorwf	((c:FCI_TOSTRING@iDst_len+1))^00h,c,w
	btfss	status,2
	goto	u3291
	goto	u3290

u3291:
	goto	l4495
u3290:
	goto	l284
	line	413
	
l4495:
	btfsc	((c:FCI_TOSTRING@iSrc+3))^00h,c,7
	goto	u3300
	goto	u3301

u3301:
	goto	l4503
u3300:
	line	415
	
l4497:
	movf	((c:FCI_TOSTRING@sDst))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(02Dh)
	movwf	indf2
	line	416
	
l4499:
	incf	((c:FCI_TOSTRING@idx))^00h,c
	line	417
	
l4501:
	comf	((c:FCI_TOSTRING@iSrc+3))^00h,c
	comf	((c:FCI_TOSTRING@iSrc+2))^00h,c
	comf	((c:FCI_TOSTRING@iSrc+1))^00h,c
	negf	((c:FCI_TOSTRING@iSrc))^00h,c
	movlw	0
	addwfc	((c:FCI_TOSTRING@iSrc+1))^00h,c
	addwfc	((c:FCI_TOSTRING@iSrc+2))^00h,c
	addwfc	((c:FCI_TOSTRING@iSrc+3))^00h,c
	line	420
	
l4503:
	movlw	low(0)
	movwf	((c:FCI_TOSTRING@tmp1))^00h,c
	line	421
	
l4505:
	movf	((c:FCI_TOSTRING@iSrc))^00h,c,w
iorwf	((c:FCI_TOSTRING@iSrc+1))^00h,c,w
iorwf	((c:FCI_TOSTRING@iSrc+2))^00h,c,w
iorwf	((c:FCI_TOSTRING@iSrc+3))^00h,c,w
	btfss	status,2
	goto	u3311
	goto	u3310

u3311:
	goto	l4525
u3310:
	line	423
	
l4507:
	movlw	low(01h)
	movwf	((c:FCI_TOSTRING@tmp1))^00h,c
	line	424
	movlw	low(01h)
	movwf	((c:FCI_TOSTRING@top))^00h,c
	movlw	high(01h)
	movwf	((c:FCI_TOSTRING@top+1))^00h,c
	movlw	low highword(01h)
	movwf	((c:FCI_TOSTRING@top+2))^00h,c
	movlw	high highword(01h)
	movwf	((c:FCI_TOSTRING@top+3))^00h,c
	goto	l4525
	line	429
	
l4509:
		movf	((c:FCI_TOSTRING@top))^00h,c,w
	subwf	((c:FCI_TOSTRING@iSrc))^00h,c,w
	movf	((c:FCI_TOSTRING@top+1))^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+1))^00h,c,w
	movf	((c:FCI_TOSTRING@top+2))^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+2))^00h,c,w
	movf	((c:FCI_TOSTRING@top+3))^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+3))^00h,c,w
	btfsc	status,0
	goto	u3321
	goto	u3320

u3321:
	goto	l4513
u3320:
	
l4511:
	movf	((c:FCI_TOSTRING@tmp1))^00h,c,w
	btfsc	status,2
	goto	u3331
	goto	u3330
u3331:
	goto	l4523
u3330:
	line	435
	
l4513:
	movff	(c:FCI_TOSTRING@iSrc),(c:___lldiv@dividend)
	movff	(c:FCI_TOSTRING@iSrc+1),(c:___lldiv@dividend+1)
	movff	(c:FCI_TOSTRING@iSrc+2),(c:___lldiv@dividend+2)
	movff	(c:FCI_TOSTRING@iSrc+3),(c:___lldiv@dividend+3)
	movff	(c:FCI_TOSTRING@top),(c:___lldiv@divisor)
	movff	(c:FCI_TOSTRING@top+1),(c:___lldiv@divisor+1)
	movff	(c:FCI_TOSTRING@top+2),(c:___lldiv@divisor+2)
	movff	(c:FCI_TOSTRING@top+3),(c:___lldiv@divisor+3)
	call	___lldiv	;wreg free
	movf	(0+?___lldiv)^00h,c,w
	movwf	((c:FCI_TOSTRING@tmp1))^00h,c
	line	439
	
l4515:
	movf	((c:FCI_TOSTRING@sDst))^00h,c,w
	addwf	((c:FCI_TOSTRING@idx))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movf	((c:FCI_TOSTRING@tmp1))^00h,c,w
	addlw	low(030h)
	movwf	indf2,c

	line	440
	
l4517:
	incf	((c:FCI_TOSTRING@idx))^00h,c
	line	441
	
l4519:
	movf	((c:FCI_TOSTRING@tmp1))^00h,c,w
	movwf	((c:___lmul@multiplier))^00h,c
	clrf	((c:___lmul@multiplier+1))^00h,c
	clrf	((c:___lmul@multiplier+2))^00h,c
	clrf	((c:___lmul@multiplier+3))^00h,c

	movff	(c:FCI_TOSTRING@top),(c:___lmul@multiplicand)
	movff	(c:FCI_TOSTRING@top+1),(c:___lmul@multiplicand+1)
	movff	(c:FCI_TOSTRING@top+2),(c:___lmul@multiplicand+2)
	movff	(c:FCI_TOSTRING@top+3),(c:___lmul@multiplicand+3)
	call	___lmul	;wreg free
	movf	(0+?___lmul)^00h,c,w
	subwf	((c:FCI_TOSTRING@iSrc))^00h,c
	movf	(1+?___lmul)^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+1))^00h,c
	movf	(2+?___lmul)^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+2))^00h,c
	movf	(3+?___lmul)^00h,c,w
	subwfb	((c:FCI_TOSTRING@iSrc+3))^00h,c

	line	442
	
l4521:
	movlw	low(01h)
	movwf	((c:FCI_TOSTRING@tmp1))^00h,c
	line	444
	
l4523:
	movff	(c:FCI_TOSTRING@top),(c:___lldiv@dividend)
	movff	(c:FCI_TOSTRING@top+1),(c:___lldiv@dividend+1)
	movff	(c:FCI_TOSTRING@top+2),(c:___lldiv@dividend+2)
	movff	(c:FCI_TOSTRING@top+3),(c:___lldiv@dividend+3)
	movlw	low(0Ah)
	movwf	((c:___lldiv@divisor))^00h,c
	movlw	high(0Ah)
	movwf	((c:___lldiv@divisor+1))^00h,c
	movlw	low highword(0Ah)
	movwf	((c:___lldiv@divisor+2))^00h,c
	movlw	high highword(0Ah)
	movwf	((c:___lldiv@divisor+3))^00h,c
	call	___lldiv	;wreg free
	movff	0+?___lldiv,(c:FCI_TOSTRING@top)
	movff	1+?___lldiv,(c:FCI_TOSTRING@top+1)
	movff	2+?___lldiv,(c:FCI_TOSTRING@top+2)
	movff	3+?___lldiv,(c:FCI_TOSTRING@top+3)
	
	line	426
	
l4525:
	movf	((c:FCI_TOSTRING@idx))^00h,c,w
	movwf	(??_FCI_TOSTRING+0+0)^00h,c
	clrf	(??_FCI_TOSTRING+0+0+1)^00h,c

		movf	((c:FCI_TOSTRING@iDst_len))^00h,c,w
	subwf	(??_FCI_TOSTRING+0+0)^00h,c,w
	movf	((c:FCI_TOSTRING@iDst_len+1))^00h,c,w
	subwfb	(??_FCI_TOSTRING+0+1)^00h,c,w
	btfsc	status,0
	goto	u3341
	goto	u3340

u3341:
	goto	l4529
u3340:
	
l4527:
	movf	((c:FCI_TOSTRING@top))^00h,c,w
iorwf	((c:FCI_TOSTRING@top+1))^00h,c,w
iorwf	((c:FCI_TOSTRING@top+2))^00h,c,w
iorwf	((c:FCI_TOSTRING@top+3))^00h,c,w
	btfss	status,2
	goto	u3351
	goto	u3350

u3351:
	goto	l4509
u3350:
	line	447
	
l4529:
	movf	((c:FCI_TOSTRING@idx))^00h,c,w
	movwf	(??_FCI_TOSTRING+0+0)^00h,c
	clrf	(??_FCI_TOSTRING+0+0+1)^00h,c

		movf	((c:FCI_TOSTRING@iDst_len))^00h,c,w
	subwf	(??_FCI_TOSTRING+0+0)^00h,c,w
	movf	((c:FCI_TOSTRING@iDst_len+1))^00h,c,w
	subwfb	(??_FCI_TOSTRING+0+1)^00h,c,w
	btfsc	status,0
	goto	u3361
	goto	u3360

u3361:
	goto	l284
u3360:
	line	448
	
l4531:
	movf	((c:FCI_TOSTRING@sDst))^00h,c,w
	addwf	((c:FCI_TOSTRING@idx))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	low(0)
	movwf	indf2
	line	450
	
l284:
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
;;  multiplier      4    0[COMRAM] unsigned long 
;;  multiplicand    4    4[COMRAM] unsigned long 
;; Auto vars:     Size  Location     Type
;;  product         4    8[COMRAM] unsigned long 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        12       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_TOSTRING
;; This function uses a non-reentrant model
;;
psect	text3,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\Umul32.c"
	line	15
global __ptext3
__ptext3:
psect	text3
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\Umul32.c"
	line	15
	global	__size_of___lmul
	__size_of___lmul	equ	__end_of___lmul-___lmul
	
___lmul:
;incstack = 0
	opt	callstack 27
	line	119
	
l3939:
	movlw	low(0)
	movwf	((c:___lmul@product))^00h,c
	movlw	high(0)
	movwf	((c:___lmul@product+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___lmul@product+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___lmul@product+3))^00h,c
	line	121
	
l3941:
	
	btfss	((c:___lmul@multiplier))^00h,c,(0)&7
	goto	u2341
	goto	u2340
u2341:
	goto	l3945
u2340:
	line	122
	
l3943:
	movf	((c:___lmul@multiplicand))^00h,c,w
	addwf	((c:___lmul@product))^00h,c
	movf	((c:___lmul@multiplicand+1))^00h,c,w
	addwfc	((c:___lmul@product+1))^00h,c
	movf	((c:___lmul@multiplicand+2))^00h,c,w
	addwfc	((c:___lmul@product+2))^00h,c
	movf	((c:___lmul@multiplicand+3))^00h,c,w
	addwfc	((c:___lmul@product+3))^00h,c
	line	123
	
l3945:
	bcf	status,0
	rlcf	((c:___lmul@multiplicand))^00h,c
	rlcf	((c:___lmul@multiplicand+1))^00h,c
	rlcf	((c:___lmul@multiplicand+2))^00h,c
	rlcf	((c:___lmul@multiplicand+3))^00h,c
	line	124
	
l3947:
	bcf	status,0
	rrcf	((c:___lmul@multiplier+3))^00h,c
	rrcf	((c:___lmul@multiplier+2))^00h,c
	rrcf	((c:___lmul@multiplier+1))^00h,c
	rrcf	((c:___lmul@multiplier))^00h,c
	line	125
	movf	((c:___lmul@multiplier))^00h,c,w
iorwf	((c:___lmul@multiplier+1))^00h,c,w
iorwf	((c:___lmul@multiplier+2))^00h,c,w
iorwf	((c:___lmul@multiplier+3))^00h,c,w
	btfss	status,2
	goto	u2351
	goto	u2350

u2351:
	goto	l3941
u2350:
	
l1508:
	line	128
	movff	(c:___lmul@product),(c:?___lmul)
	movff	(c:___lmul@product+1),(c:?___lmul+1)
	movff	(c:___lmul@product+2),(c:?___lmul+2)
	movff	(c:___lmul@product+3),(c:?___lmul+3)
	line	129
	
l1509:
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
;;  dividend        4    0[COMRAM] unsigned long 
;;  divisor         4    4[COMRAM] unsigned long 
;; Auto vars:     Size  Location     Type
;;  quotient        4    8[COMRAM] unsigned long 
;;  counter         1   12[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        13       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       13 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCI_TOSTRING
;; This function uses a non-reentrant model
;;
psect	text4,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\__lldiv.c"
	line	7
global __ptext4
__ptext4:
psect	text4
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\__lldiv.c"
	line	7
	global	__size_of___lldiv
	__size_of___lldiv	equ	__end_of___lldiv-___lldiv
	
___lldiv:
;incstack = 0
	opt	callstack 27
	line	13
	
l3949:
	movlw	low(0)
	movwf	((c:___lldiv@quotient))^00h,c
	movlw	high(0)
	movwf	((c:___lldiv@quotient+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___lldiv@quotient+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___lldiv@quotient+3))^00h,c
	line	14
	
l3951:
	movf	((c:___lldiv@divisor))^00h,c,w
iorwf	((c:___lldiv@divisor+1))^00h,c,w
iorwf	((c:___lldiv@divisor+2))^00h,c,w
iorwf	((c:___lldiv@divisor+3))^00h,c,w
	btfsc	status,2
	goto	u2361
	goto	u2360

u2361:
	goto	l1524
u2360:
	line	15
	
l3953:
	movlw	low(01h)
	movwf	((c:___lldiv@counter))^00h,c
	line	16
	goto	l3957
	line	17
	
l3955:
	bcf	status,0
	rlcf	((c:___lldiv@divisor))^00h,c
	rlcf	((c:___lldiv@divisor+1))^00h,c
	rlcf	((c:___lldiv@divisor+2))^00h,c
	rlcf	((c:___lldiv@divisor+3))^00h,c
	line	18
	incf	((c:___lldiv@counter))^00h,c
	line	16
	
l3957:
	
	btfss	((c:___lldiv@divisor+3))^00h,c,(31)&7
	goto	u2371
	goto	u2370
u2371:
	goto	l3955
u2370:
	line	21
	
l3959:
	bcf	status,0
	rlcf	((c:___lldiv@quotient))^00h,c
	rlcf	((c:___lldiv@quotient+1))^00h,c
	rlcf	((c:___lldiv@quotient+2))^00h,c
	rlcf	((c:___lldiv@quotient+3))^00h,c
	line	22
	
l3961:
		movf	((c:___lldiv@divisor))^00h,c,w
	subwf	((c:___lldiv@dividend))^00h,c,w
	movf	((c:___lldiv@divisor+1))^00h,c,w
	subwfb	((c:___lldiv@dividend+1))^00h,c,w
	movf	((c:___lldiv@divisor+2))^00h,c,w
	subwfb	((c:___lldiv@dividend+2))^00h,c,w
	movf	((c:___lldiv@divisor+3))^00h,c,w
	subwfb	((c:___lldiv@dividend+3))^00h,c,w
	btfss	status,0
	goto	u2381
	goto	u2380

u2381:
	goto	l3967
u2380:
	line	23
	
l3963:
	movf	((c:___lldiv@divisor))^00h,c,w
	subwf	((c:___lldiv@dividend))^00h,c
	movf	((c:___lldiv@divisor+1))^00h,c,w
	subwfb	((c:___lldiv@dividend+1))^00h,c
	movf	((c:___lldiv@divisor+2))^00h,c,w
	subwfb	((c:___lldiv@dividend+2))^00h,c
	movf	((c:___lldiv@divisor+3))^00h,c,w
	subwfb	((c:___lldiv@dividend+3))^00h,c
	line	24
	
l3965:
	bsf	(0+(0/8)+(c:___lldiv@quotient))^00h,c,(0)&7
	line	26
	
l3967:
	bcf	status,0
	rrcf	((c:___lldiv@divisor+3))^00h,c
	rrcf	((c:___lldiv@divisor+2))^00h,c
	rrcf	((c:___lldiv@divisor+1))^00h,c
	rrcf	((c:___lldiv@divisor))^00h,c
	line	27
	
l3969:
	decfsz	((c:___lldiv@counter))^00h,c
	
	goto	l3959
	line	28
	
l1524:
	line	29
	movff	(c:___lldiv@quotient),(c:?___lldiv)
	movff	(c:___lldiv@quotient+1),(c:?___lldiv+1)
	movff	(c:___lldiv@quotient+2),(c:?___lldiv+2)
	movff	(c:___lldiv@quotient+3),(c:?___lldiv+3)
	line	30
	
l1531:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___lldiv
	__end_of___lldiv:
	signat	___lldiv,8316
	global	_FCD_029f1_gLCD_EB3__Print

;; *************** function _FCD_029f1_gLCD_EB3__Print *****************
;; Defined at:
;;		line 3576 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_STR         1   36[COMRAM] PTR unsigned char 
;;		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(8), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(8), 
;;  FCLsz_STR       2   37[COMRAM] unsigned short 
;;  FCL_X1          2   39[COMRAM] unsigned short 
;;  FCL_Y1          2   41[COMRAM] unsigned short 
;;  FCL_FONT        1   43[COMRAM] unsigned char 
;;  FCL_TRANSPAR    1   44[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         9       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         9       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        9 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__PrintNumber
;; This function uses a non-reentrant model
;;
psect	text5,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	3576
global __ptext5
__ptext5:
psect	text5
	file	"BL0144 dig temp sensor - PIC.c"
	line	3576
	global	__size_of_FCD_029f1_gLCD_EB3__Print
	__size_of_FCD_029f1_gLCD_EB3__Print	equ	__end_of_FCD_029f1_gLCD_EB3__Print-_FCD_029f1_gLCD_EB3__Print
	
_FCD_029f1_gLCD_EB3__Print:
;incstack = 0
	opt	callstack 24
	line	3579
	
l4535:
	movlw	low(047h)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3580
	
l4537:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__Print@FCL_X1),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+01h)	;volatile
	line	3581
	
l4539:; BSR set to: 0

	movff	0+((c:FCD_029f1_gLCD_EB3__Print@FCL_X1)+01h),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+02h)	;volatile
	line	3582
	
l4541:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__Print@FCL_Y1),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+03h)	;volatile
	line	3583
	
l4543:; BSR set to: 0

	movff	0+((c:FCD_029f1_gLCD_EB3__Print@FCL_Y1)+01h),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+04h)	;volatile
	line	3584
	
l4545:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__Print@FCL_FONT),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+05h)	;volatile
	line	3585
	
l4547:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__Print@FCL_TRANSPARENT),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+06h)	;volatile
	line	3586
	movlw	low(0)
	movwf	(0+(_FCV_029f1_gLCD_EB3__COMMANDTX+07h))&0ffh	;volatile
	line	3587
	movlw	low(08h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3588
	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3590
	
l4549:; BSR set to: 0

		movff	(c:FCD_029f1_gLCD_EB3__Print@FCL_STR),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR)
	clrf	((c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR+1))^00h,c

	movff	(c:FCD_029f1_gLCD_EB3__Print@FCLsz_STR),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR)
	movff	(c:FCD_029f1_gLCD_EB3__Print@FCLsz_STR+1),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR+1)
	call	_FCD_029f1_gLCD_EB3__SendCommandWithString	;wreg free
	line	3592
	
l1367:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__Print
	__end_of_FCD_029f1_gLCD_EB3__Print:
	signat	_FCD_029f1_gLCD_EB3__Print,24697
	global	_FCD_029f1_gLCD_EB3__Initialise

;; *************** function _FCD_029f1_gLCD_EB3__Initialise *****************
;; Defined at:
;;		line 3900 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_IDX         1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
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
;;		_FCD_029f1_gLCD_EB3__ClearDisplay
;;		_FCD_029f1_gLCD_EB3__SetBackgroundColour
;;		_FCD_029f1_gLCD_EB3__SetDisplayOrientation
;;		_FCD_029f1_gLCD_EB3__SetExternalFont
;;		_FCD_029f1_gLCD_EB3__SetForegroundColour
;;		_FC_CAL_UART_Init_1
;;		_delay_s
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text6,class=CODE,space=0,reloc=2,group=0
	line	3900
global __ptext6
__ptext6:
psect	text6
	file	"BL0144 dig temp sensor - PIC.c"
	line	3900
	global	__size_of_FCD_029f1_gLCD_EB3__Initialise
	__size_of_FCD_029f1_gLCD_EB3__Initialise	equ	__end_of_FCD_029f1_gLCD_EB3__Initialise-_FCD_029f1_gLCD_EB3__Initialise
	
_FCD_029f1_gLCD_EB3__Initialise:
;incstack = 0
	opt	callstack 24
	line	3906
	
l4681:; BSR set to: 14

	movlw	(02h)&0ffh
	
	call	_delay_s
	line	3908
	
l4683:
	call	_FC_CAL_UART_Init_1	;wreg free
	line	3910
	
l4685:; BSR set to: 14

	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_GREEN))^00h,c
	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_BLUE))^00h,c
	movlw	(0)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetBackgroundColour
	line	3912
	
l4687:
	movlw	low(0FFh)
	movwf	((c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_GREEN))^00h,c
	movlw	low(0FFh)
	movwf	((c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_BLUE))^00h,c
	movlw	(0FFh)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetForegroundColour
	line	3914
	
l4689:
	movlw	(01h)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetDisplayOrientation
	line	3916
	
l4691:
	call	_FCD_029f1_gLCD_EB3__ClearDisplay	;wreg free
	line	3918
	
l4693:
		movlw	low(STR_5)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR))^00h,c
	movlw	high(STR_5)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR+1))^00h,c

	movlw	high(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR))^00h,c
	movlw	low(01h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING))^00h,c
	movlw	low(05h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH))^00h,c
	movlw	(0)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetExternalFont
	line	3921
	
l4695:
		movlw	low(STR_6)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR))^00h,c
	movlw	high(STR_6)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR+1))^00h,c

	movlw	high(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR))^00h,c
	movlw	low(01h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING))^00h,c
	movlw	low(06h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH))^00h,c
	movlw	(01h)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetExternalFont
	line	3924
	
l4697:
		movlw	low(STR_7)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR))^00h,c
	movlw	high(STR_7)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR+1))^00h,c

	movlw	high(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR))^00h,c
	movlw	low(02h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING))^00h,c
	movlw	low(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH))^00h,c
	movlw	(02h)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetExternalFont
	line	3927
	
l4699:
		movlw	low(STR_8)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR))^00h,c
	movlw	high(STR_8)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR+1))^00h,c

	movlw	high(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR))^00h,c
	movlw	low(01h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING))^00h,c
	movlw	low(011h)
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH))^00h,c
	movlw	(03h)&0ffh
	
	call	_FCD_029f1_gLCD_EB3__SetExternalFont
	line	3951
	
l1402:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__Initialise
	__end_of_FCD_029f1_gLCD_EB3__Initialise:
	signat	_FCD_029f1_gLCD_EB3__Initialise,89
	global	_delay_s

;; *************** function _delay_s *****************
;; Defined at:
;;		line 114 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    2[COMRAM] unsigned char 
;;  i               1    3[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay_ms
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text7,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	114
global __ptext7
__ptext7:
psect	text7
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	114
	global	__size_of_delay_s
	__size_of_delay_s	equ	__end_of_delay_s-_delay_s
	
_delay_s:
;incstack = 0
	opt	callstack 27
	movwf	((c:delay_s@del))^00h,c
	line	117
	
l3303:
	movlw	low(0)
	movwf	((c:delay_s@i))^00h,c
	goto	l3309
	line	119
	
l3305:
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
	
l3307:
	incf	((c:delay_s@i))^00h,c
	
l3309:
		movf	((c:delay_s@del))^00h,c,w
	subwf	((c:delay_s@i))^00h,c,w
	btfss	status,0
	goto	u1591
	goto	u1590

u1591:
	goto	l3305
u1590:
	line	124
	
l118:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_s
	__end_of_delay_s:
	signat	_delay_s,4217
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
;;		On entry : 0/E
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text8,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	660
global __ptext8
__ptext8:
psect	text8
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	660
	global	__size_of_FC_CAL_UART_Init_1
	__size_of_FC_CAL_UART_Init_1	equ	__end_of_FC_CAL_UART_Init_1-_FC_CAL_UART_Init_1
	
_FC_CAL_UART_Init_1:
;incstack = 0
	opt	callstack 28
	line	939
	
l3369:
	movlb	14	; () banked
	bsf	((3830))&0ffh,2	;volatile
	line	943
	
l3371:; BSR set to: 14

	movlw	low(0)
	movwf	((3831))&0ffh	;volatile
	line	946
	movlw	low(022h)
	movwf	((3827))&0ffh	;volatile
	line	947
	movlw	low(0)
	movwf	((3829))&0ffh	;volatile
	line	958
	
l3373:; BSR set to: 14

	bsf	((3829))&0ffh,7	;volatile
	line	960
	
l3375:; BSR set to: 14

	bsf	((3830))&0ffh,5	;volatile
	line	963
	
l3377:; BSR set to: 14

	bsf	((3829))&0ffh,4	;volatile
	line	971
	
l3379:; BSR set to: 14

	bcf	((3628))&0ffh,7	;volatile
	line	1441
	
l799:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Init_1
	__end_of_FC_CAL_UART_Init_1:
	signat	_FC_CAL_UART_Init_1,89
	global	_FCD_029f1_gLCD_EB3__SetForegroundColour

;; *************** function _FCD_029f1_gLCD_EB3__SetForegroundColour *****************
;; Defined at:
;;		line 3844 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_RED         1    wreg     unsigned char 
;;  FCL_GREEN       1   32[COMRAM] unsigned char 
;;  FCL_BLUE        1   33[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_RED         1   34[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text9,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	3844
global __ptext9
__ptext9:
psect	text9
	file	"BL0144 dig temp sensor - PIC.c"
	line	3844
	global	__size_of_FCD_029f1_gLCD_EB3__SetForegroundColour
	__size_of_FCD_029f1_gLCD_EB3__SetForegroundColour	equ	__end_of_FCD_029f1_gLCD_EB3__SetForegroundColour-_FCD_029f1_gLCD_EB3__SetForegroundColour
	
_FCD_029f1_gLCD_EB3__SetForegroundColour:; BSR set to: 14

;incstack = 0
	opt	callstack 24
	movwf	((c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_RED))^00h,c
	line	3847
	
l4593:
	movlw	low(042h)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3848
	
l4595:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_RED),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+01h)	;volatile
	line	3849
	
l4597:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_GREEN),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+02h)	;volatile
	line	3850
	
l4599:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetForegroundColour@FCL_BLUE),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+03h)	;volatile
	line	3851
	
l4601:; BSR set to: 0

	movlw	low(04h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3852
	
l4603:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3854
	
l4605:; BSR set to: 0

	call	_FCD_029f1_gLCD_EB3__SendCommand	;wreg free
	line	3856
	
l1396:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SetForegroundColour
	__end_of_FCD_029f1_gLCD_EB3__SetForegroundColour:
	signat	_FCD_029f1_gLCD_EB3__SetForegroundColour,12409
	global	_FCD_029f1_gLCD_EB3__SetExternalFont

;; *************** function _FCD_029f1_gLCD_EB3__SetExternalFont *****************
;; Defined at:
;;		line 3646 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_FONT        1    wreg     unsigned char 
;;  FCL_STR         2   36[COMRAM] PTR unsigned char 
;;		 -> STR_8(10), STR_7(10), STR_6(10), STR_5(10), 
;;  FCLsz_STR       2   38[COMRAM] unsigned short 
;;  FCL_CHARACTE    1   40[COMRAM] unsigned char 
;;  FCL_SPACEWID    1   41[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_FONT        1   42[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         7       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text10,class=CODE,space=0,reloc=2,group=0
	line	3646
global __ptext10
__ptext10:
psect	text10
	file	"BL0144 dig temp sensor - PIC.c"
	line	3646
	global	__size_of_FCD_029f1_gLCD_EB3__SetExternalFont
	__size_of_FCD_029f1_gLCD_EB3__SetExternalFont	equ	__end_of_FCD_029f1_gLCD_EB3__SetExternalFont-_FCD_029f1_gLCD_EB3__SetExternalFont
	
_FCD_029f1_gLCD_EB3__SetExternalFont:
;incstack = 0
	opt	callstack 24
	movwf	((c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_FONT))^00h,c
	line	3649
	
l4561:
	movlw	low(02Bh)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3650
	
l4563:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_FONT),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+01h)	;volatile
	line	3651
	
l4565:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_CHARACTERSPACING),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+02h)	;volatile
	line	3652
	
l4567:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_SPACEWIDTH),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+03h)	;volatile
	line	3653
	
l4569:; BSR set to: 0

	movlw	low(04h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3654
	
l4571:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3656
	
l4573:; BSR set to: 0

		movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR)
	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCL_STR+1),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR+1)

	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR)
	movff	(c:FCD_029f1_gLCD_EB3__SetExternalFont@FCLsz_STR+1),(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR+1)
	call	_FCD_029f1_gLCD_EB3__SendCommandWithString	;wreg free
	line	3658
	
l1375:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SetExternalFont
	__end_of_FCD_029f1_gLCD_EB3__SetExternalFont:
	signat	_FCD_029f1_gLCD_EB3__SetExternalFont,20601
	global	_FCD_029f1_gLCD_EB3__SendCommandWithString

;; *************** function _FCD_029f1_gLCD_EB3__SendCommandWithString *****************
;; Defined at:
;;		line 3524 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_STR         2   31[COMRAM] PTR unsigned char 
;;		 -> STR_8(10), STR_7(10), STR_6(10), STR_5(10), 
;;		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(8), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(8), 
;;  FCLsz_STR       2   33[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;;		_FCD_05481_UART1__SendByteArray
;;		_FCD_05481_UART1__SendString
;;		_FC_CAL_UART_Send_1
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Print
;;		_FCD_029f1_gLCD_EB3__SetExternalFont
;; This function uses a non-reentrant model
;;
psect	text11,class=CODE,space=0,reloc=2,group=0
	line	3524
global __ptext11
__ptext11:
psect	text11
	file	"BL0144 dig temp sensor - PIC.c"
	line	3524
	global	__size_of_FCD_029f1_gLCD_EB3__SendCommandWithString
	__size_of_FCD_029f1_gLCD_EB3__SendCommandWithString	equ	__end_of_FCD_029f1_gLCD_EB3__SendCommandWithString-_FCD_029f1_gLCD_EB3__SendCommandWithString
	
_FCD_029f1_gLCD_EB3__SendCommandWithString:
;incstack = 0
	opt	callstack 24
	line	3533
	
l3889:; BSR set to: 0

	movlw	high(03Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(03Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3535
	
l3891:; BSR set to: 14

		movlw	low(_FCV_029f1_gLCD_EB3__COMMANDTX)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCL_DATA))^00h,c

	movlw	high(014h)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCLsz_DATA+1))^00h,c
	movlw	low(014h)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCLsz_DATA))^00h,c
	movff	(c:_FCV_029f1_gLCD_EB3__TXCOUNT),(c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES)	;volatile
	clrf	((c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES+1))^00h,c
	call	_FCD_05481_UART1__SendByteArray	;wreg free
	line	3537
	
l3893:; BSR set to: 14

		movff	(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR),(c:FCD_05481_UART1__SendString@FCL_DATA)
	movff	(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCL_STR+1),(c:FCD_05481_UART1__SendString@FCL_DATA+1)

	movff	(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR),(c:FCD_05481_UART1__SendString@FCLsz_DATA)
	movff	(c:FCD_029f1_gLCD_EB3__SendCommandWithString@FCLsz_STR+1),(c:FCD_05481_UART1__SendString@FCLsz_DATA+1)
	call	_FCD_05481_UART1__SendString	;wreg free
	line	3539
	
l3895:
	movlw	high(0)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3541
	
l3897:; BSR set to: 14

	movlw	high(03Bh)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(03Bh)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3543
	
l3899:; BSR set to: 14

	movlw	high(0Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3545
	
l3901:; BSR set to: 14

	call	_FCD_029f1_gLCD_EB3__ReceiveReply	;wreg free
	line	3549
	
l1361:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SendCommandWithString
	__end_of_FCD_029f1_gLCD_EB3__SendCommandWithString:
	signat	_FCD_029f1_gLCD_EB3__SendCommandWithString,8313
	global	_FCD_05481_UART1__SendString

;; *************** function _FCD_05481_UART1__SendString *****************
;; Defined at:
;;		line 852 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_DATA        2    8[COMRAM] PTR unsigned char 
;;		 -> STR_8(10), STR_7(10), STR_6(10), STR_5(10), 
;;		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(8), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(8), STR_4(1), STR_3(1), 
;;		 -> FCD_05481_UART1__SendNumber@FCL_NUMSTR(20), 
;;  FCLsz_DATA      2   10[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  FCL_IDX         2   17[COMRAM] unsigned short 
;;  FCL_LEN         2   15[COMRAM] unsigned short 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        11       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       11 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_FCI_GETLENGTH
;;		_FC_CAL_UART_Send_1
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function uses a non-reentrant model
;;
psect	text12,class=CODE,space=0,reloc=2,group=0
	line	852
global __ptext12
__ptext12:
psect	text12
	file	"BL0144 dig temp sensor - PIC.c"
	line	852
	global	__size_of_FCD_05481_UART1__SendString
	__size_of_FCD_05481_UART1__SendString	equ	__end_of_FCD_05481_UART1__SendString-_FCD_05481_UART1__SendString
	
_FCD_05481_UART1__SendString:
;incstack = 0
	opt	callstack 25
	line	859
	
l3817:; BSR set to: 14

		movff	(c:FCD_05481_UART1__SendString@FCL_DATA),(c:FCI_GETLENGTH@sStr1)
	movff	(c:FCD_05481_UART1__SendString@FCL_DATA+1),(c:FCI_GETLENGTH@sStr1+1)

	movff	(c:FCD_05481_UART1__SendString@FCLsz_DATA),(c:FCI_GETLENGTH@iStr1_len)
	movff	(c:FCD_05481_UART1__SendString@FCLsz_DATA+1),(c:FCI_GETLENGTH@iStr1_len+1)
	call	_FCI_GETLENGTH	;wreg free
	movff	0+?_FCI_GETLENGTH,(c:FCD_05481_UART1__SendString@FCL_LEN)
	movff	1+?_FCI_GETLENGTH,(c:FCD_05481_UART1__SendString@FCL_LEN+1)
	line	860
	
l3819:
	movlw	high(0)
	movwf	((c:FCD_05481_UART1__SendString@FCL_IDX+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c
	line	862
	goto	l3825
	line	864
	
l3821:
	movf	((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c,w
	addwf	((c:FCD_05481_UART1__SendString@FCL_DATA))^00h,c,w
	movwf	(??_FCD_05481_UART1__SendString+0+0)^00h,c
	movf	((c:FCD_05481_UART1__SendString@FCL_IDX+1))^00h,c,w
	addwfc	((c:FCD_05481_UART1__SendString@FCL_DATA+1))^00h,c,w
	movwf	(??_FCD_05481_UART1__SendString+0+0+1)^00h,c
	movff	??_FCD_05481_UART1__SendString+0+0,tblptrl
	movff	??_FCD_05481_UART1__SendString+0+1,tblptrh
	movlw	low highword(__mediumconst)
	movwf	tblptru
	
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u2227
	tblrd	*
	
	movf	tablat,w
	bra	u2220
u2227:
	movff	tblptrl,fsr2l
	movff	tblptrh,fsr2h
	movf	indf2,w
u2220:
	movwf	(??_FCD_05481_UART1__SendString+2+0)^00h,c
	movf	((??_FCD_05481_UART1__SendString+2+0))^00h,c,w
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	clrf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	866
	
l3823:; BSR set to: 14

	movlw	low(01h)
	addwf	((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c,w
	movwf	((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c
	movlw	high(01h)
	addwfc	((c:FCD_05481_UART1__SendString@FCL_IDX+1))^00h,c,w
	movwf	1+((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c
	line	862
	
l3825:
		movf	((c:FCD_05481_UART1__SendString@FCL_LEN))^00h,c,w
	subwf	((c:FCD_05481_UART1__SendString@FCL_IDX))^00h,c,w
	movf	((c:FCD_05481_UART1__SendString@FCL_LEN+1))^00h,c,w
	subwfb	((c:FCD_05481_UART1__SendString@FCL_IDX+1))^00h,c,w
	btfss	status,0
	goto	u2231
	goto	u2230

u2231:
	goto	l3821
u2230:
	line	870
	
l1013:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_05481_UART1__SendString
	__end_of_FCD_05481_UART1__SendString:
	signat	_FCD_05481_UART1__SendString,8313
	global	_FCI_GETLENGTH

;; *************** function _FCI_GETLENGTH *****************
;; Defined at:
;;		line 150 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
;; Parameters:    Size  Location     Type
;;  sStr1           2    0[COMRAM] PTR unsigned char 
;;		 -> STR_8(10), STR_7(10), STR_6(10), STR_5(10), 
;;		 -> FCD_029f1_gLCD_EB3__PrintFloat@FCL_TEMP(8), FCD_029f1_gLCD_EB3__PrintNumber@FCL_TEMP(8), STR_4(1), STR_3(1), 
;;		 -> FCD_05481_UART1__SendNumber@FCL_NUMSTR(20), FCI_INTTOFORMATTEDSTRING@sTemp(20), FCI_FLOATTOFORMATTEDSTRING@sTemp(20), 
;;  iStr1_len       2    2[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  tmp             2    6[COMRAM] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    0[COMRAM] unsigned short 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_05481_UART1__SendString
;; This function uses a non-reentrant model
;;
psect	text13,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	150
global __ptext13
__ptext13:
psect	text13
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_String.c"
	line	150
	global	__size_of_FCI_GETLENGTH
	__size_of_FCI_GETLENGTH	equ	__end_of_FCI_GETLENGTH-_FCI_GETLENGTH
	
_FCI_GETLENGTH:
;incstack = 0
	opt	callstack 25
	line	153
	
l3613:; BSR set to: 14

	movlw	high(0)
	movwf	((c:FCI_GETLENGTH@tmp+1))^00h,c
	movlw	low(0)
	movwf	((c:FCI_GETLENGTH@tmp))^00h,c
	goto	l3621
	
l3615:
	movf	((c:FCI_GETLENGTH@tmp))^00h,c,w
	addwf	((c:FCI_GETLENGTH@sStr1))^00h,c,w
	movwf	(??_FCI_GETLENGTH+0+0)^00h,c
	movf	((c:FCI_GETLENGTH@tmp+1))^00h,c,w
	addwfc	((c:FCI_GETLENGTH@sStr1+1))^00h,c,w
	movwf	(??_FCI_GETLENGTH+0+0+1)^00h,c
	movff	??_FCI_GETLENGTH+0+0,tblptrl
	movff	??_FCI_GETLENGTH+0+1,tblptrh
	movlw	low highword(__mediumconst)
	movwf	tblptru
	
	movlw	high __ramtop-1
	cpfsgt	tblptrh
	bra	u1857
	tblrd	*
	
	movf	tablat,w
	bra	u1850
u1857:
	movff	tblptrl,fsr2l
	movff	tblptrh,fsr2h
	movf	indf2,w
u1850:
	iorlw	0
	btfss	status,2
	goto	u1861
	goto	u1860
u1861:
	goto	l3619
u1860:
	goto	l177
	
l3619:
	infsnz	((c:FCI_GETLENGTH@tmp))^00h,c
	incf	((c:FCI_GETLENGTH@tmp+1))^00h,c
	
l3621:
		movf	((c:FCI_GETLENGTH@iStr1_len))^00h,c,w
	subwf	((c:FCI_GETLENGTH@tmp))^00h,c,w
	movf	((c:FCI_GETLENGTH@iStr1_len+1))^00h,c,w
	subwfb	((c:FCI_GETLENGTH@tmp+1))^00h,c,w
	btfss	status,0
	goto	u1871
	goto	u1870

u1871:
	goto	l3615
u1870:
	
l177:
	line	154
	movff	(c:FCI_GETLENGTH@tmp),(c:?_FCI_GETLENGTH)
	movff	(c:FCI_GETLENGTH@tmp+1),(c:?_FCI_GETLENGTH+1)
	line	155
	
l178:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCI_GETLENGTH
	__end_of_FCI_GETLENGTH:
	signat	_FCI_GETLENGTH,8314
	global	_FCD_029f1_gLCD_EB3__SetDisplayOrientation

;; *************** function _FCD_029f1_gLCD_EB3__SetDisplayOrientation *****************
;; Defined at:
;;		line 3406 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_ORIENTAT    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_ORIENTAT    1   32[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text14,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	3406
global __ptext14
__ptext14:
psect	text14
	file	"BL0144 dig temp sensor - PIC.c"
	line	3406
	global	__size_of_FCD_029f1_gLCD_EB3__SetDisplayOrientation
	__size_of_FCD_029f1_gLCD_EB3__SetDisplayOrientation	equ	__end_of_FCD_029f1_gLCD_EB3__SetDisplayOrientation-_FCD_029f1_gLCD_EB3__SetDisplayOrientation
	
_FCD_029f1_gLCD_EB3__SetDisplayOrientation:
;incstack = 0
	opt	callstack 24
	movwf	((c:FCD_029f1_gLCD_EB3__SetDisplayOrientation@FCL_ORIENTATION))^00h,c
	line	3409
	
l4551:
	movlw	low(04Bh)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3410
	
l4553:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetDisplayOrientation@FCL_ORIENTATION),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+01h)	;volatile
	line	3411
	
l4555:; BSR set to: 0

	movlw	low(02h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3412
	
l4557:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3414
	
l4559:; BSR set to: 0

	call	_FCD_029f1_gLCD_EB3__SendCommand	;wreg free
	line	3416
	
l1346:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SetDisplayOrientation
	__end_of_FCD_029f1_gLCD_EB3__SetDisplayOrientation:
	signat	_FCD_029f1_gLCD_EB3__SetDisplayOrientation,4217
	global	_FCD_029f1_gLCD_EB3__SetBackgroundColour

;; *************** function _FCD_029f1_gLCD_EB3__SetBackgroundColour *****************
;; Defined at:
;;		line 3745 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_RED         1    wreg     unsigned char 
;;  FCL_GREEN       1   32[COMRAM] unsigned char 
;;  FCL_BLUE        1   33[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_RED         1   34[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text15,class=CODE,space=0,reloc=2,group=0
	line	3745
global __ptext15
__ptext15:
psect	text15
	file	"BL0144 dig temp sensor - PIC.c"
	line	3745
	global	__size_of_FCD_029f1_gLCD_EB3__SetBackgroundColour
	__size_of_FCD_029f1_gLCD_EB3__SetBackgroundColour	equ	__end_of_FCD_029f1_gLCD_EB3__SetBackgroundColour-_FCD_029f1_gLCD_EB3__SetBackgroundColour
	
_FCD_029f1_gLCD_EB3__SetBackgroundColour:
;incstack = 0
	opt	callstack 24
	movwf	((c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_RED))^00h,c
	line	3748
	
l4579:
	movlw	low(043h)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3749
	
l4581:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_RED),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+01h)	;volatile
	line	3750
	
l4583:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_GREEN),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+02h)	;volatile
	line	3751
	
l4585:; BSR set to: 0

	movff	(c:FCD_029f1_gLCD_EB3__SetBackgroundColour@FCL_BLUE),0+(_FCV_029f1_gLCD_EB3__COMMANDTX+03h)	;volatile
	line	3752
	
l4587:; BSR set to: 0

	movlw	low(04h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3753
	
l4589:; BSR set to: 0

	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3755
	
l4591:; BSR set to: 0

	call	_FCD_029f1_gLCD_EB3__SendCommand	;wreg free
	line	3757
	
l1387:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SetBackgroundColour
	__end_of_FCD_029f1_gLCD_EB3__SetBackgroundColour:
	signat	_FCD_029f1_gLCD_EB3__SetBackgroundColour,12409
	global	_FCD_029f1_gLCD_EB3__ClearDisplay

;; *************** function _FCD_029f1_gLCD_EB3__ClearDisplay *****************
;; Defined at:
;;		line 3721 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_X           2   34[COMRAM] unsigned short 
;;  FCL_Y           2    0        unsigned short 
;;  FCL_ORIENTAT    1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__Initialise
;; This function uses a non-reentrant model
;;
psect	text16,class=CODE,space=0,reloc=2,group=0
	line	3721
global __ptext16
__ptext16:
psect	text16
	file	"BL0144 dig temp sensor - PIC.c"
	line	3721
	global	__size_of_FCD_029f1_gLCD_EB3__ClearDisplay
	__size_of_FCD_029f1_gLCD_EB3__ClearDisplay	equ	__end_of_FCD_029f1_gLCD_EB3__ClearDisplay-_FCD_029f1_gLCD_EB3__ClearDisplay
	
_FCD_029f1_gLCD_EB3__ClearDisplay:
;incstack = 0
	opt	callstack 24
	line	3724
	
l4575:
	line	3725
	movlw	high(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ClearDisplay@FCL_X+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ClearDisplay@FCL_X))^00h,c
	line	3729
	movlw	low(044h)
	movlb	0	; () banked
	movwf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh	;volatile
	line	3730
	movlw	low(01h)
	movwf	((c:_FCV_029f1_gLCD_EB3__TXCOUNT))^00h,c	;volatile
	line	3731
	movlw	low(0)
	movwf	((c:_FCV_029f1_gLCD_EB3__RXCOUNT))^00h,c	;volatile
	line	3733
	
l4577:; BSR set to: 0

	call	_FCD_029f1_gLCD_EB3__SendCommand	;wreg free
	line	3735
	
l1384:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__ClearDisplay
	__end_of_FCD_029f1_gLCD_EB3__ClearDisplay:
	signat	_FCD_029f1_gLCD_EB3__ClearDisplay,89
	global	_FCD_029f1_gLCD_EB3__SendCommand

;; *************** function _FCD_029f1_gLCD_EB3__SendCommand *****************
;; Defined at:
;;		line 3072 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;;		_FCD_05481_UART1__SendByteArray
;;		_FC_CAL_UART_Send_1
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__SetDisplayOrientation
;;		_FCD_029f1_gLCD_EB3__ClearDisplay
;;		_FCD_029f1_gLCD_EB3__SetBackgroundColour
;;		_FCD_029f1_gLCD_EB3__SetForegroundColour
;; This function uses a non-reentrant model
;;
psect	text17,class=CODE,space=0,reloc=2,group=0
	line	3072
global __ptext17
__ptext17:
psect	text17
	file	"BL0144 dig temp sensor - PIC.c"
	line	3072
	global	__size_of_FCD_029f1_gLCD_EB3__SendCommand
	__size_of_FCD_029f1_gLCD_EB3__SendCommand	equ	__end_of_FCD_029f1_gLCD_EB3__SendCommand-_FCD_029f1_gLCD_EB3__SendCommand
	
_FCD_029f1_gLCD_EB3__SendCommand:
;incstack = 0
	opt	callstack 24
	line	3081
	
l3877:; BSR set to: 0

	movlw	high(03Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(03Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3083
	
l3879:; BSR set to: 14

		movlw	low(_FCV_029f1_gLCD_EB3__COMMANDTX)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCL_DATA))^00h,c

	movlw	high(014h)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCLsz_DATA+1))^00h,c
	movlw	low(014h)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCLsz_DATA))^00h,c
	movff	(c:_FCV_029f1_gLCD_EB3__TXCOUNT),(c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES)	;volatile
	clrf	((c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES+1))^00h,c
	call	_FCD_05481_UART1__SendByteArray	;wreg free
	line	3085
	
l3881:; BSR set to: 14

	movlw	high(03Bh)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(03Bh)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3087
	
l3883:; BSR set to: 14

	movlw	high(0Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	movlw	low(0Ah)
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	3089
	
l3885:; BSR set to: 14

	call	_FCD_029f1_gLCD_EB3__ReceiveReply	;wreg free
	line	3093
	
l1308:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__SendCommand
	__end_of_FCD_029f1_gLCD_EB3__SendCommand:
	signat	_FCD_029f1_gLCD_EB3__SendCommand,89
	global	_FCD_05481_UART1__SendByteArray

;; *************** function _FCD_05481_UART1__SendByteArray *****************
;; Defined at:
;;		line 990 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_DATA        1    2[COMRAM] PTR unsigned char 
;;		 -> FCV_029f1_gLCD_EB3__COMMANDTX(20), 
;;  FCLsz_DATA      2    3[COMRAM] unsigned short 
;;  FCL_NUMBYTES    2    5[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  FCL_IDX         2    8[COMRAM] unsigned short 
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_FC_CAL_UART_Send_1
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function uses a non-reentrant model
;;
psect	text18,class=CODE,space=0,reloc=2,group=0
	line	990
global __ptext18
__ptext18:
psect	text18
	file	"BL0144 dig temp sensor - PIC.c"
	line	990
	global	__size_of_FCD_05481_UART1__SendByteArray
	__size_of_FCD_05481_UART1__SendByteArray	equ	__end_of_FCD_05481_UART1__SendByteArray-_FCD_05481_UART1__SendByteArray
	
_FCD_05481_UART1__SendByteArray:
;incstack = 0
	opt	callstack 25
	line	996
	
l3827:; BSR set to: 14

	movlw	high(0)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c
	line	998
	goto	l3833
	line	1000
	
l3829:; BSR set to: 14

	movf	((c:FCD_05481_UART1__SendByteArray@FCL_DATA))^00h,c,w
	addwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	(??_FCD_05481_UART1__SendByteArray+0+0)^00h,c
	movf	((??_FCD_05481_UART1__SendByteArray+0+0))^00h,c,w
	movwf	((c:FC_CAL_UART_Send_1@nChar))^00h,c
	clrf	((c:FC_CAL_UART_Send_1@nChar+1))^00h,c
	call	_FC_CAL_UART_Send_1	;wreg free
	line	1002
	
l3831:; BSR set to: 14

	movlw	low(01h)
	addwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c,w
	movwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c
	movlw	high(01h)
	addwfc	((c:FCD_05481_UART1__SendByteArray@FCL_IDX+1))^00h,c,w
	movwf	1+((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c
	line	998
	
l3833:; BSR set to: 14

		movf	((c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES))^00h,c,w
	subwf	((c:FCD_05481_UART1__SendByteArray@FCL_IDX))^00h,c,w
	movf	((c:FCD_05481_UART1__SendByteArray@FCL_NUMBYTES+1))^00h,c,w
	subwfb	((c:FCD_05481_UART1__SendByteArray@FCL_IDX+1))^00h,c,w
	btfss	status,0
	goto	u2241
	goto	u2240

u2241:
	goto	l3829
u2240:
	line	1006
	
l1034:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_05481_UART1__SendByteArray
	__end_of_FCD_05481_UART1__SendByteArray:
	signat	_FCD_05481_UART1__SendByteArray,12409
	global	_FC_CAL_UART_Send_1

;; *************** function _FC_CAL_UART_Send_1 *****************
;; Defined at:
;;		line 1535 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
;; Parameters:    Size  Location     Type
;;  nChar           2    0[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 3F/E
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_05481_UART1__SendString
;;		_FCD_05481_UART1__SendByteArray
;;		_FCD_029f1_gLCD_EB3__SendCommand
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function uses a non-reentrant model
;;
psect	text19,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1535
global __ptext19
__ptext19:
psect	text19
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1535
	global	__size_of_FC_CAL_UART_Send_1
	__size_of_FC_CAL_UART_Send_1	equ	__end_of_FC_CAL_UART_Send_1-_FC_CAL_UART_Send_1
	
_FC_CAL_UART_Send_1:; BSR set to: 14

;incstack = 0
	opt	callstack 26
	line	1581
	
l3623:
	
l805:
	movlb	14	; () banked
	btfss	((3638))&0ffh,6	;volatile
	goto	u1881
	goto	u1880
u1881:
	goto	l805
u1880:
	
l807:; BSR set to: 14

	line	1589
	movff	(c:FC_CAL_UART_Send_1@nChar),(3826)	;volatile
	line	1644
	
l808:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Send_1
	__end_of_FC_CAL_UART_Send_1:
	signat	_FC_CAL_UART_Send_1,4217
	global	_FCD_029f1_gLCD_EB3__ReceiveReply

;; *************** function _FCD_029f1_gLCD_EB3__ReceiveReply *****************
;; Defined at:
;;		line 2888 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_RX          2   29[COMRAM] unsigned short 
;;  FCL_RXMODE      1   28[COMRAM] unsigned char 
;;  FCR_RETVAL      1   27[COMRAM] unsigned char 
;;  FCL_RETRY       1   26[COMRAM] unsigned char 
;;  FCL_RXDONE      1   25[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FCD_01211_RXCB__FlushBuffer
;;		_FCD_01211_RXCB__LookForValue
;;		_FCD_01211_RXCB__PutByte
;;		_FC_CAL_UART_Receive_1
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__SendCommand
;;		_FCD_029f1_gLCD_EB3__SendCommandWithString
;; This function uses a non-reentrant model
;;
psect	text20,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	2888
global __ptext20
__ptext20:
psect	text20
	file	"BL0144 dig temp sensor - PIC.c"
	line	2888
	global	__size_of_FCD_029f1_gLCD_EB3__ReceiveReply
	__size_of_FCD_029f1_gLCD_EB3__ReceiveReply	equ	__end_of_FCD_029f1_gLCD_EB3__ReceiveReply-_FCD_029f1_gLCD_EB3__ReceiveReply
	
_FCD_029f1_gLCD_EB3__ReceiveReply:; BSR set to: 14

;incstack = 0
	opt	callstack 24
	line	2891
	
l3835:; BSR set to: 14

	movlw	low(032h)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY))^00h,c
	line	2892
	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE))^00h,c
	line	2893
	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c
	line	2901
	
l3837:; BSR set to: 14

	call	_FCD_01211_RXCB__FlushBuffer	;wreg free
	line	2903
	
l3839:; BSR set to: 14

	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL))^00h,c
	line	2905
	goto	l3871
	line	2907
	
l3841:
	movlw	(064h)&0ffh
	
	call	_FC_CAL_UART_Receive_1
	movff	0+?_FC_CAL_UART_Receive_1,(c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX)
	movff	1+?_FC_CAL_UART_Receive_1,(c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX+1)
	line	2909
	
l3843:
		decf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX+1))^00h,c,w
	btfss	status,0
	goto	u2251
	goto	u2250

u2251:
	goto	l3851
u2250:
	line	2912
	
l3845:
	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY))^00h,c,w
	btfss	status,2
	goto	u2261
	goto	u2260
u2261:
	goto	l3849
u2260:
	line	2915
	
l3847:
	movlw	low(01h)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE))^00h,c
	line	2917
	goto	l3871
	line	2919
	
l3849:
	decf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY))^00h,c,w
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RETRY))^00h,c
	goto	l3871
	line	2925
	
l3851:
	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c,w
	btfss	status,2
	goto	u2271
	goto	u2270
u2271:
	goto	l3857
u2270:
	line	2928
	
l3853:
		movlw	58
	xorwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX))^00h,c,w
iorwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX+1))^00h,c,w
	btfss	status,2
	goto	u2281
	goto	u2280

u2281:
	goto	l3871
u2280:
	line	2931
	
l3855:
	movlw	low(01h)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c
	goto	l3871
	line	2939
	
l3857:
		decf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c,w
	btfss	status,2
	goto	u2291
	goto	u2290

u2291:
	goto	l3865
u2290:
	line	2942
	
l3859:
	movlb	0	; () banked
	movf	((_FCV_029f1_gLCD_EB3__COMMANDTX))&0ffh,w	;volatile
	movwf	(??_FCD_029f1_gLCD_EB3__ReceiveReply+0+0)^00h,c
	clrf	(??_FCD_029f1_gLCD_EB3__ReceiveReply+0+0+1)^00h,c

	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX))^00h,c,w
xorwf	(??_FCD_029f1_gLCD_EB3__ReceiveReply+0+0)^00h,c,w
	bnz	u2301
movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX+1))^00h,c,w
xorwf	(??_FCD_029f1_gLCD_EB3__ReceiveReply+0+1)^00h,c,w
	btfss	status,2
	goto	u2301
	goto	u2300

u2301:
	goto	l3863
u2300:
	line	2945
	
l3861:; BSR set to: 0

	movlw	low(02h)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c
	line	2947
	goto	l3871
	line	2949
	
l3863:; BSR set to: 0

	movlw	low(0)
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXMODE))^00h,c
	goto	l3871
	line	2955
	
l3865:
	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RX))^00h,c,w
	
	call	_FCD_01211_RXCB__PutByte
	line	2957
	
l3867:
	incf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL))^00h,c,w
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL))^00h,c
	line	2959
	
l3869:
		movlw	low(STR_2)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE))^00h,c
	movlw	high(STR_2)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE+1))^00h,c

	movlw	high(03h)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCLsz_VALUE+1))^00h,c
	movlw	low(03h)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCLsz_VALUE))^00h,c
	movlw	low(02h)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMCHARS))^00h,c
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_REMOVECONTENT))^00h,c
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_RESETFIND))^00h,c
	call	_FCD_01211_RXCB__LookForValue	;wreg free
	movwf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE))^00h,c
	line	2905
	
l3871:
	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCL_RXDONE))^00h,c,w
	btfsc	status,2
	goto	u2311
	goto	u2310
u2311:
	goto	l3841
u2310:
	line	2969
	
l3873:
	movf	((c:FCD_029f1_gLCD_EB3__ReceiveReply@FCR_RETVAL))^00h,c,w
	line	2971
	
l1296:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_029f1_gLCD_EB3__ReceiveReply
	__end_of_FCD_029f1_gLCD_EB3__ReceiveReply:
	signat	_FCD_029f1_gLCD_EB3__ReceiveReply,89
	global	_FC_CAL_UART_Receive_1

;; *************** function _FC_CAL_UART_Receive_1 *****************
;; Defined at:
;;		line 1647 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
;; Parameters:    Size  Location     Type
;;  nTimeout        1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  nTimeout        1   10[COMRAM] unsigned char 
;;  retVal          2    8[COMRAM] unsigned short 
;;  delaycnt        2    4[COMRAM] unsigned short 
;;  regcheck        1   11[COMRAM] unsigned char 
;;  rxStatus        1    7[COMRAM] unsigned char 
;;  delay1          1    6[COMRAM] unsigned char 
;;  bWaitForever    1    3[COMRAM] unsigned char 
;;  dummy           1    2[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    0[COMRAM] short 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:        10       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        12       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;; This function uses a non-reentrant model
;;
psect	text21,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1647
global __ptext21
__ptext21:
psect	text21
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
	line	1647
	global	__size_of_FC_CAL_UART_Receive_1
	__size_of_FC_CAL_UART_Receive_1	equ	__end_of_FC_CAL_UART_Receive_1-_FC_CAL_UART_Receive_1
	
_FC_CAL_UART_Receive_1:
;incstack = 0
	opt	callstack 25
	movwf	((c:FC_CAL_UART_Receive_1@nTimeout))^00h,c
	line	1650
	
l3625:
	movlw	high(0200h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal+1))^00h,c
	movlw	low(0200h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	line	1657
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@delay1))^00h,c
	line	1659
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@bWaitForever))^00h,c
	line	1660
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@rxStatus))^00h,c
	line	1666
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@dummy))^00h,c
	line	1669
	
l3627:
		incf	((c:FC_CAL_UART_Receive_1@nTimeout))^00h,c,w
	btfss	status,2
	goto	u1891
	goto	u1890

u1891:
	goto	l812
u1890:
	line	1670
	
l3629:
	movlw	low(01h)
	movwf	((c:FC_CAL_UART_Receive_1@bWaitForever))^00h,c
	goto	l812
	line	1680
	
l3631:
	movf	((c:FC_CAL_UART_Receive_1@bWaitForever))^00h,c,w
	btfss	status,2
	goto	u1901
	goto	u1900
u1901:
	goto	l3653
u1900:
	line	1682
	
l3633:
	movf	((c:FC_CAL_UART_Receive_1@nTimeout))^00h,c,w
	btfss	status,2
	goto	u1911
	goto	u1910
u1911:
	goto	l3637
u1910:
	line	1684
	
l3635:
	movlw	low(01h)
	movwf	((c:FC_CAL_UART_Receive_1@rxStatus))^00h,c
	line	1685
	goto	l3653
	line	1688
	
l3637:
	movlw	high(0)
	movwf	((c:FC_CAL_UART_Receive_1@delaycnt+1))^00h,c
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@delaycnt))^00h,c
	
l3643:
	infsnz	((c:FC_CAL_UART_Receive_1@delaycnt))^00h,c
	incf	((c:FC_CAL_UART_Receive_1@delaycnt+1))^00h,c
	
l3645:
		movf	((c:FC_CAL_UART_Receive_1@delaycnt+1))^00h,c,w
	bnz	u1920
	movlw	16
	subwf	 ((c:FC_CAL_UART_Receive_1@delaycnt))^00h,c,w
	btfss	status,0
	goto	u1921
	goto	u1920

u1921:
	goto	l3643
u1920:
	line	1689
	
l3647:
	incf	((c:FC_CAL_UART_Receive_1@delay1))^00h,c,w
	movwf	((c:FC_CAL_UART_Receive_1@delay1))^00h,c
	line	1690
		movlw	100
	xorwf	((c:FC_CAL_UART_Receive_1@delay1))^00h,c,w
	btfss	status,2
	goto	u1931
	goto	u1930

u1931:
	goto	l3653
u1930:
	line	1692
	
l3649:
	decf	((c:FC_CAL_UART_Receive_1@nTimeout))^00h,c,w
	movwf	((c:FC_CAL_UART_Receive_1@nTimeout))^00h,c
	line	1693
# 1693 "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_UART.c"
clrwdt ;# 
psect	text21
	line	1694
	
l3651:
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@delay1))^00h,c
	line	1729
	
l3653:
	movlb	14	; () banked
	movlw	0
	btfsc	((3638))&0ffh,7	;volatile
	movlw	1
	movwf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c
	line	1731
	
l3655:; BSR set to: 14

	movf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c,w
	btfsc	status,2
	goto	u1941
	goto	u1940
u1941:
	goto	l812
u1940:
	line	1732
	
l3657:; BSR set to: 14

	movlw	low(02h)
	movwf	((c:FC_CAL_UART_Receive_1@rxStatus))^00h,c
	line	1771
	
l812:
	line	1678
	movf	((c:FC_CAL_UART_Receive_1@rxStatus))^00h,c,w
	btfsc	status,2
	goto	u1951
	goto	u1950
u1951:
	goto	l3631
u1950:
	line	1773
	
l3659:
		movlw	2
	xorwf	((c:FC_CAL_UART_Receive_1@rxStatus))^00h,c,w
	btfss	status,2
	goto	u1961
	goto	u1960

u1961:
	goto	l3681
u1960:
	line	1882
	
l3661:
	movlb	14	; () banked
	movlw	0
	btfsc	((3829))&0ffh,2	;volatile
	movlw	1
	movwf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c
	line	1883
	
l3663:; BSR set to: 14

	movf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c,w
	btfsc	status,2
	goto	u1971
	goto	u1970
u1971:
	goto	l3669
u1970:
	line	1885
	
l3665:; BSR set to: 14

	movf	((3825))&0ffh,w	;volatile
	line	1887
	
l3667:; BSR set to: 14

	movlw	high(0400h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal+1))^00h,c
	movlw	low(0400h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	line	1889
	goto	l3681
	line	1892
	
l3669:; BSR set to: 14

	movlw	0
	btfsc	((3829))&0ffh,1	;volatile
	movlw	1
	movwf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c
	line	1893
	
l3671:; BSR set to: 14

	movf	((c:FC_CAL_UART_Receive_1@regcheck))^00h,c,w
	btfsc	status,2
	goto	u1981
	goto	u1980
u1981:
	goto	l3677
u1980:
	line	1895
	
l3673:; BSR set to: 14

	bcf	((3829))&0ffh,4	;volatile
	line	1896
	bsf	((3829))&0ffh,4	;volatile
	line	1898
	
l3675:; BSR set to: 14

	movlw	high(0800h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal+1))^00h,c
	movlw	low(0800h)
	movwf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	line	1900
	goto	l3681
	line	1903
	
l3677:; BSR set to: 14

	movlw	high(0)
	movwf	((c:FC_CAL_UART_Receive_1@retVal+1))^00h,c
	movlw	low(0)
	movwf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	line	1910
	
l3679:; BSR set to: 14

	movf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c,w
	iorwf	((3825))&0ffh,w	;volatile
	movwf	((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	movf	((c:FC_CAL_UART_Receive_1@retVal+1))^00h,c,w
	movwf	1+((c:FC_CAL_UART_Receive_1@retVal))^00h,c
	line	2117
	
l3681:
	movff	(c:FC_CAL_UART_Receive_1@retVal),(c:?_FC_CAL_UART_Receive_1)
	movff	(c:FC_CAL_UART_Receive_1@retVal+1),(c:?_FC_CAL_UART_Receive_1+1)
	line	2118
	
l827:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_UART_Receive_1
	__end_of_FC_CAL_UART_Receive_1:
	signat	_FC_CAL_UART_Receive_1,4218
	global	_FCD_01211_RXCB__PutByte

;; *************** function _FCD_01211_RXCB__PutByte *****************
;; Defined at:
;;		line 440 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_DATA        1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_DATA        1    1[COMRAM] unsigned char 
;;  FCL_TEMP        2    2[COMRAM] unsigned short 
;;  FCL_TEMP2       2    0        unsigned short 
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;; This function uses a non-reentrant model
;;
psect	text22,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	440
global __ptext22
__ptext22:
psect	text22
	file	"BL0144 dig temp sensor - PIC.c"
	line	440
	global	__size_of_FCD_01211_RXCB__PutByte
	__size_of_FCD_01211_RXCB__PutByte	equ	__end_of_FCD_01211_RXCB__PutByte-_FCD_01211_RXCB__PutByte
	
_FCD_01211_RXCB__PutByte:
;incstack = 0
	opt	callstack 25
	movwf	((c:FCD_01211_RXCB__PutByte@FCL_DATA))^00h,c
	line	448
	
l3731:
	movlw	low(01h)
	addwf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	movwf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP))^00h,c
	movlw	high(01h)
	addwfc	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
	movwf	1+((c:FCD_01211_RXCB__PutByte@FCL_TEMP))^00h,c
	line	450
		movf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP+1))^00h,c,w
	bnz	u2080
	movlw	32
	subwf	 ((c:FCD_01211_RXCB__PutByte@FCL_TEMP))^00h,c,w
	btfss	status,0
	goto	u2081
	goto	u2080

u2081:
	goto	l3735
u2080:
	line	453
	
l3733:
	movlw	high(0)
	movwf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP))^00h,c
	line	459
	
l3735:
	movf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
xorwf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP))^00h,c,w
	bnz	u2090
movf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
xorwf	((c:FCD_01211_RXCB__PutByte@FCL_TEMP+1))^00h,c,w
	btfsc	status,2
	goto	u2091
	goto	u2090

u2091:
	goto	l3743
u2090:
	line	462
	
l3737:
	movf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	addlw	low(_FCV_01211_RXCB__DATA)
	movwf	fsr2l
	clrf	fsr2h
	movff	(c:FCD_01211_RXCB__PutByte@FCL_DATA),indf2

	line	464
	
l3739:
	movff	(c:FCD_01211_RXCB__PutByte@FCL_TEMP),(c:_FCV_01211_RXCB__DATAEND)	;volatile
	movff	(c:FCD_01211_RXCB__PutByte@FCL_TEMP+1),(c:_FCV_01211_RXCB__DATAEND+1)	;volatile
	line	466
	
l3741:
	line	468
	goto	l941
	line	473
	
l3743:
	line	481
	
l941:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01211_RXCB__PutByte
	__end_of_FCD_01211_RXCB__PutByte:
	signat	_FCD_01211_RXCB__PutByte,4217
	global	_FCD_01211_RXCB__LookForValue

;; *************** function _FCD_01211_RXCB__LookForValue *****************
;; Defined at:
;;		line 51 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;  FCL_VALUE       2    7[COMRAM] PTR unsigned char 
;;		 -> STR_2(3), 
;;  FCLsz_VALUE     2    9[COMRAM] unsigned short 
;;  FCL_NUMCHARS    1   11[COMRAM] unsigned char 
;;  FCL_REMOVECO    1   12[COMRAM] unsigned char 
;;  FCL_RESETFIN    1   13[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  FCL_DATAINDE    2   21[COMRAM] unsigned short 
;;  FCL_SEARCHIN    2   17[COMRAM] unsigned short 
;;  FCL_NUMBYTES    1   20[COMRAM] unsigned char 
;;  FCL_COMPARED    1   19[COMRAM] unsigned char 
;;  FCR_RETVAL      1   16[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, tblptrl, tblptrh, tblptru, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         7       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         7       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        16       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       16 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_FCD_01211_RXCB__GetByte
;;		_FCD_01211_RXCB__GetNumberBytes
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;; This function uses a non-reentrant model
;;
psect	text23,class=CODE,space=0,reloc=2,group=0
	line	51
global __ptext23
__ptext23:
psect	text23
	file	"BL0144 dig temp sensor - PIC.c"
	line	51
	global	__size_of_FCD_01211_RXCB__LookForValue
	__size_of_FCD_01211_RXCB__LookForValue	equ	__end_of_FCD_01211_RXCB__LookForValue-_FCD_01211_RXCB__LookForValue
	
_FCD_01211_RXCB__LookForValue:
;incstack = 0
	opt	callstack 24
	line	61
	
l3685:
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCR_RETVAL))^00h,c
	line	63
	
l3687:
		decf	((c:FCD_01211_RXCB__LookForValue@FCL_RESETFIND))^00h,c,w
	btfss	status,2
	goto	u1991
	goto	u1990

u1991:
	goto	l3691
u1990:
	line	66
	
l3689:
	movlw	low(0)
	movwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c	;volatile
	line	72
	
l3691:
	movff	(c:_FCV_01211_RXCB__LOOKFORCOUNTER),(c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX)	;volatile
	clrf	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX+1))^00h,c
	line	74
	
l3693:
	call	_FCD_01211_RXCB__GetNumberBytes	;wreg free
	movf	(0+?_FCD_01211_RXCB__GetNumberBytes)^00h,c,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMBYTES))^00h,c
	line	76
	goto	l3725
	line	78
	
l3695:
	movf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMBYTES))^00h,c,w
	btfsc	status,2
	goto	u2001
	goto	u2000
u2001:
	goto	l3723
u2000:
	line	81
	
l3697:
		decf	((c:FCD_01211_RXCB__LookForValue@FCL_REMOVECONTENT))^00h,c,w
	btfss	status,2
	goto	u2011
	goto	u2010

u2011:
	goto	l3701
u2010:
	line	84
	
l3699:
	call	_FCD_01211_RXCB__GetByte	;wreg free
	movf	(0+?_FCD_01211_RXCB__GetByte)^00h,c,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA))^00h,c
	line	86
	goto	l3709
	line	88
	
l3701:
	movf	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX))^00h,c,w
	addwf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c
	movf	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX+1))^00h,c,w
	addwfc	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	movwf	1+((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c
	line	90
		movf	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX+1))^00h,c,w
	bnz	u2020
	movlw	32
	subwf	 ((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c,w
	btfss	status,0
	goto	u2021
	goto	u2020

u2021:
	goto	l3705
u2020:
	line	93
	
l3703:
	movlw	low(0FFE0h)
	addwf	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c
	movlw	high(0FFE0h)
	addwfc	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX+1))^00h,c,w
	movwf	1+((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c
	line	99
	
l3705:
	movf	((c:FCD_01211_RXCB__LookForValue@FCL_DATAINDEX))^00h,c,w
	addlw	low(_FCV_01211_RXCB__DATA)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA))^00h,c
	line	101
	
l3707:
	movlw	low(01h)
	addwf	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX))^00h,c,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX))^00h,c
	movlw	high(01h)
	addwfc	((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX+1))^00h,c,w
	movwf	1+((c:FCD_01211_RXCB__LookForValue@FCL_SEARCHINDEX))^00h,c
	line	105
	
l3709:
	movf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	addwf	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE))^00h,c,w
	movwf	(??_FCD_01211_RXCB__LookForValue+0+0)^00h,c
	movlw	0
	addwfc	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE+1))^00h,c,w
	movwf	(??_FCD_01211_RXCB__LookForValue+0+0+1)^00h,c
	movff	??_FCD_01211_RXCB__LookForValue+0+0,tblptrl
	movff	??_FCD_01211_RXCB__LookForValue+0+1,tblptrh
	if	0	;tblptru may be non-zero
	clrf	tblptru
	endif
	if	1	;Program memory is > 0xFFFF, there are 3 active tblptr bytes
	global __mediumconst
movlw	low highword(__mediumconst)
	movwf	tblptru
	endif
	tblrd	*
	
	movf	tablat,w
	xorwf	((c:FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA))^00h,c,w
	btfss	status,2
	goto	u2031
	goto	u2030
u2031:
	goto	l3715
u2030:
	line	108
	
l3711:
	incf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	movwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c	;volatile
	line	110
	movf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMCHARS))^00h,c,w
xorwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	btfss	status,2
	goto	u2041
	goto	u2040

u2041:
	goto	l873
u2040:
	line	113
	
l3713:
	movlw	low(0)
	movwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c	;volatile
	line	115
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMCHARS))^00h,c
	line	116
	movlw	low(01h)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCR_RETVAL))^00h,c
	goto	l873
	line	124
	
l3715:
	movf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	btfsc	status,2
	goto	u2051
	goto	u2050
u2051:
	goto	l873
u2050:
	line	127
	
l3717:
	movlw	low(0)
	movwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c	;volatile
	line	129
	
l3719:
	movf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	addwf	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE))^00h,c,w
	movwf	(??_FCD_01211_RXCB__LookForValue+0+0)^00h,c
	movlw	0
	addwfc	((c:FCD_01211_RXCB__LookForValue@FCL_VALUE+1))^00h,c,w
	movwf	(??_FCD_01211_RXCB__LookForValue+0+0+1)^00h,c
	movff	??_FCD_01211_RXCB__LookForValue+0+0,tblptrl
	movff	??_FCD_01211_RXCB__LookForValue+0+1,tblptrh
	if	0	;tblptru may be non-zero
	clrf	tblptru
	endif
	if	1	;Program memory is > 0xFFFF, there are 3 active tblptr bytes
	global __mediumconst
movlw	low highword(__mediumconst)
	movwf	tblptru
	endif
	tblrd	*
	
	movf	tablat,w
	xorwf	((c:FCD_01211_RXCB__LookForValue@FCL_COMPAREDATA))^00h,c,w
	btfss	status,2
	goto	u2061
	goto	u2060
u2061:
	goto	l873
u2060:
	line	132
	
l3721:
	incf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	movwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c	;volatile
	line	142
	
l873:
	line	144
	decf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMBYTES))^00h,c,w
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMBYTES))^00h,c
	line	146
	goto	l3725
	line	148
	
l3723:
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMCHARS))^00h,c
	line	76
	
l3725:
		movf	((c:FCD_01211_RXCB__LookForValue@FCL_NUMCHARS))^00h,c,w
	subwf	((c:_FCV_01211_RXCB__LOOKFORCOUNTER))^00h,c,w	;volatile
	btfss	status,0
	goto	u2071
	goto	u2070

u2071:
	goto	l3695
u2070:
	line	154
	
l3727:
	movf	((c:FCD_01211_RXCB__LookForValue@FCR_RETVAL))^00h,c,w
	line	156
	
l878:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01211_RXCB__LookForValue
	__end_of_FCD_01211_RXCB__LookForValue:
	signat	_FCD_01211_RXCB__LookForValue,20601
	global	_FCD_01211_RXCB__GetNumberBytes

;; *************** function _FCD_01211_RXCB__GetNumberBytes *****************
;; Defined at:
;;		line 339 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      2    4[COMRAM] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    0[COMRAM] unsigned short 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01211_RXCB__LookForValue
;; This function uses a non-reentrant model
;;
psect	text24,class=CODE,space=0,reloc=2,group=0
	line	339
global __ptext24
__ptext24:
psect	text24
	file	"BL0144 dig temp sensor - PIC.c"
	line	339
	global	__size_of_FCD_01211_RXCB__GetNumberBytes
	__size_of_FCD_01211_RXCB__GetNumberBytes	equ	__end_of_FCD_01211_RXCB__GetNumberBytes-_FCD_01211_RXCB__GetNumberBytes
	
_FCD_01211_RXCB__GetNumberBytes:
;incstack = 0
	opt	callstack 24
	line	348
	
l3581:
		movf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	subwf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	movf	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
	subwfb	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	btfsc	status,0
	goto	u1811
	goto	u1810

u1811:
	goto	l3585
u1810:
	line	351
	
l3583:
	movf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	subwf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	movwf	((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL))^00h,c
	movf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	subwfb	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
	movwf	1+((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL))^00h,c
	line	353
	goto	l3591
	line	355
	
l3585:
		movf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	subwf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	movf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	subwfb	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
	btfsc	status,0
	goto	u1821
	goto	u1820

u1821:
	goto	l3589
u1820:
	line	358
	
l3587:
	movf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	subwf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
	movwf	(??_FCD_01211_RXCB__GetNumberBytes+0+0)^00h,c
	movf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	subwfb	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
	movwf	(??_FCD_01211_RXCB__GetNumberBytes+0+0+1)^00h,c
	movlw	low(020h)
	addwf	(??_FCD_01211_RXCB__GetNumberBytes+0+0)^00h,c,w
	movwf	((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL))^00h,c
	movlw	high(020h)
	addwfc	(??_FCD_01211_RXCB__GetNumberBytes+0+1)^00h,c,w
	movwf	1+((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL))^00h,c
	line	360
	goto	l3591
	line	362
	
l3589:
	movlw	high(0)
	movwf	((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL))^00h,c
	line	368
	
l3591:
	movff	(c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL),(c:?_FCD_01211_RXCB__GetNumberBytes)
	movff	(c:FCD_01211_RXCB__GetNumberBytes@FCR_RETVAL+1),(c:?_FCD_01211_RXCB__GetNumberBytes+1)
	line	370
	
l924:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01211_RXCB__GetNumberBytes
	__end_of_FCD_01211_RXCB__GetNumberBytes:
	signat	_FCD_01211_RXCB__GetNumberBytes,90
	global	_FCD_01211_RXCB__GetByte

;; *************** function _FCD_01211_RXCB__GetByte *****************
;; Defined at:
;;		line 489 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_TEMP        2    5[COMRAM] unsigned short 
;;  FCR_RETVAL      2    3[COMRAM] unsigned short 
;; Return value:  Size  Location     Type
;;                  2    0[COMRAM] unsigned short 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         7       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        7 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01211_RXCB__LookForValue
;; This function uses a non-reentrant model
;;
psect	text25,class=CODE,space=0,reloc=2,group=0
	line	489
global __ptext25
__ptext25:
psect	text25
	file	"BL0144 dig temp sensor - PIC.c"
	line	489
	global	__size_of_FCD_01211_RXCB__GetByte
	__size_of_FCD_01211_RXCB__GetByte	equ	__end_of_FCD_01211_RXCB__GetByte-_FCD_01211_RXCB__GetByte
	
_FCD_01211_RXCB__GetByte:
;incstack = 0
	opt	callstack 24
	line	496
	
l3595:
	movf	((c:_FCV_01211_RXCB__DATAEND))^00h,c,w	;volatile
xorwf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	bnz	u1830
movf	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c,w	;volatile
xorwf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	btfsc	status,2
	goto	u1831
	goto	u1830

u1831:
	goto	l3607
u1830:
	line	499
	
l3597:
	movf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	addlw	low(_FCV_01211_RXCB__DATA)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	(??_FCD_01211_RXCB__GetByte+0+0)^00h,c
	movf	((??_FCD_01211_RXCB__GetByte+0+0))^00h,c,w
	movwf	((c:FCD_01211_RXCB__GetByte@FCR_RETVAL))^00h,c
	clrf	((c:FCD_01211_RXCB__GetByte@FCR_RETVAL+1))^00h,c
	line	501
	
l3599:
	movlw	low(01h)
	addwf	((c:_FCV_01211_RXCB__DATASTART))^00h,c,w	;volatile
	movwf	((c:FCD_01211_RXCB__GetByte@FCL_TEMP))^00h,c
	movlw	high(01h)
	addwfc	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c,w	;volatile
	movwf	1+((c:FCD_01211_RXCB__GetByte@FCL_TEMP))^00h,c
	line	503
	
l3601:
		movf	((c:FCD_01211_RXCB__GetByte@FCL_TEMP+1))^00h,c,w
	bnz	u1840
	movlw	32
	subwf	 ((c:FCD_01211_RXCB__GetByte@FCL_TEMP))^00h,c,w
	btfss	status,0
	goto	u1841
	goto	u1840

u1841:
	goto	l3605
u1840:
	line	506
	
l3603:
	movlw	high(0)
	movwf	((c:FCD_01211_RXCB__GetByte@FCL_TEMP+1))^00h,c
	movlw	low(0)
	movwf	((c:FCD_01211_RXCB__GetByte@FCL_TEMP))^00h,c
	line	512
	
l3605:
	movff	(c:FCD_01211_RXCB__GetByte@FCL_TEMP),(c:_FCV_01211_RXCB__DATASTART)	;volatile
	movff	(c:FCD_01211_RXCB__GetByte@FCL_TEMP+1),(c:_FCV_01211_RXCB__DATASTART+1)	;volatile
	line	514
	goto	l3609
	line	519
	
l3607:
	movlw	high(0FFh)
	movwf	((c:FCD_01211_RXCB__GetByte@FCR_RETVAL+1))^00h,c
	setf	((c:FCD_01211_RXCB__GetByte@FCR_RETVAL))^00h,c
	line	525
	
l3609:
	movff	(c:FCD_01211_RXCB__GetByte@FCR_RETVAL),(c:?_FCD_01211_RXCB__GetByte)
	movff	(c:FCD_01211_RXCB__GetByte@FCR_RETVAL+1),(c:?_FCD_01211_RXCB__GetByte+1)
	line	527
	
l947:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01211_RXCB__GetByte
	__end_of_FCD_01211_RXCB__GetByte:
	signat	_FCD_01211_RXCB__GetByte,90
	global	_FCD_01211_RXCB__FlushBuffer

;; *************** function _FCD_01211_RXCB__FlushBuffer *****************
;; Defined at:
;;		line 565 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 3F/E
;;		On exit  : 3F/E
;;		Unchanged: 3F/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_029f1_gLCD_EB3__ReceiveReply
;; This function uses a non-reentrant model
;;
psect	text26,class=CODE,space=0,reloc=2,group=0
	line	565
global __ptext26
__ptext26:
psect	text26
	file	"BL0144 dig temp sensor - PIC.c"
	line	565
	global	__size_of_FCD_01211_RXCB__FlushBuffer
	__size_of_FCD_01211_RXCB__FlushBuffer	equ	__end_of_FCD_01211_RXCB__FlushBuffer-_FCD_01211_RXCB__FlushBuffer
	
_FCD_01211_RXCB__FlushBuffer:
;incstack = 0
	opt	callstack 25
	line	568
	
l3747:; BSR set to: 14

	movlw	high(0)
	movwf	((c:_FCV_01211_RXCB__DATAEND+1))^00h,c	;volatile
	movlw	low(0)
	movwf	((c:_FCV_01211_RXCB__DATAEND))^00h,c	;volatile
	line	569
	movlw	high(0)
	movwf	((c:_FCV_01211_RXCB__DATASTART+1))^00h,c	;volatile
	movlw	low(0)
	movwf	((c:_FCV_01211_RXCB__DATASTART))^00h,c	;volatile
	line	571
	
l954:; BSR set to: 14

	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01211_RXCB__FlushBuffer
	__end_of_FCD_01211_RXCB__FlushBuffer:
	signat	_FCD_01211_RXCB__FlushBuffer,89
	global	_FCD_01c01_temp_hum_sensor__Initialise

;; *************** function _FCD_01c01_temp_hum_sensor__Initialise *****************
;; Defined at:
;;		line 4268 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_01c01_temp_hum_sensor__Sample
;;		_FC_CAL_I2C_Transaction_Init_1
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text27,class=CODE,space=0,reloc=2,group=0
	line	4268
global __ptext27
__ptext27:
psect	text27
	file	"BL0144 dig temp sensor - PIC.c"
	line	4268
	global	__size_of_FCD_01c01_temp_hum_sensor__Initialise
	__size_of_FCD_01c01_temp_hum_sensor__Initialise	equ	__end_of_FCD_01c01_temp_hum_sensor__Initialise-_FCD_01c01_temp_hum_sensor__Initialise
	
_FCD_01c01_temp_hum_sensor__Initialise:; BSR set to: 14

;incstack = 0
	opt	callstack 25
	line	4274
	
l4707:
	movlw	high(0)
	movwf	((c:_FCV_01c01_temp_hum_sensor__HUM+1))^00h,c	;volatile
	movlw	low(0)
	movwf	((c:_FCV_01c01_temp_hum_sensor__HUM))^00h,c	;volatile
	line	4275
	movlw	high(0)
	movwf	((c:_FCV_01c01_temp_hum_sensor__TEMP+1))^00h,c	;volatile
	movlw	low(0)
	movwf	((c:_FCV_01c01_temp_hum_sensor__TEMP))^00h,c	;volatile
	line	4277
	
l4709:
	movlw	(044h)&0ffh
	
	call	_FC_CAL_I2C_Transaction_Init_1
	line	4279
	
l4711:
	call	_FCD_01c01_temp_hum_sensor__Sample	;wreg free
	line	4281
	
l4713:
	movf	((c:_FCV_01c01_temp_hum_sensor__HUM))^00h,c,w	;volatile
iorwf	((c:_FCV_01c01_temp_hum_sensor__HUM+1))^00h,c,w	;volatile
	btfsc	status,2
	goto	u3471
	goto	u3470

u3471:
	goto	l4717
u3470:
	
l4715:
		incf	((c:_FCV_01c01_temp_hum_sensor__HUM))^00h,c,w	;volatile
	bnz	u3481
	incf	((c:_FCV_01c01_temp_hum_sensor__HUM+1))^00h,c,w	;volatile
	btfss	status,2
	goto	u3481
	goto	u3480

u3481:
	goto	l4719
u3480:
	line	4284
	
l4717:
	line	4286
	goto	l1472
	line	4288
	
l4719:
	line	4294
	
l1472:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01c01_temp_hum_sensor__Initialise
	__end_of_FCD_01c01_temp_hum_sensor__Initialise:
	signat	_FCD_01c01_temp_hum_sensor__Initialise,89
	global	_FC_CAL_I2C_Transaction_Init_1

;; *************** function _FC_CAL_I2C_Transaction_Init_1 *****************
;; Defined at:
;;		line 998 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;  SlaveAddress    1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  SlaveAddress    1    0[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_FC_CAL_I2C_Master_Init_1
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__Initialise
;; This function uses a non-reentrant model
;;
psect	text28,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	998
global __ptext28
__ptext28:
psect	text28
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	998
	global	__size_of_FC_CAL_I2C_Transaction_Init_1
	__size_of_FC_CAL_I2C_Transaction_Init_1	equ	__end_of_FC_CAL_I2C_Transaction_Init_1-_FC_CAL_I2C_Transaction_Init_1
	
_FC_CAL_I2C_Transaction_Init_1:
;incstack = 0
	opt	callstack 27
	movwf	((c:FC_CAL_I2C_Transaction_Init_1@SlaveAddress))^00h,c
	line	1000
	
l3359:
	movff	(c:FC_CAL_I2C_Transaction_Init_1@SlaveAddress),(c:_MX_I2C_ADDRESS_1)
	line	1002
	
l3361:
	movf	((c:_MX_I2C_INIT_1))^00h,c,w
	btfss	status,2
	goto	u1681
	goto	u1680
u1681:
	goto	l772
u1680:
	line	1004
	
l3363:
	movlw	low(01h)
	movwf	((c:_MX_I2C_INIT_1))^00h,c
	line	1005
	
l3365:
	call	_FC_CAL_I2C_Master_Init_1	;wreg free
	line	1009
	
l772:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Transaction_Init_1
	__end_of_FC_CAL_I2C_Transaction_Init_1:
	signat	_FC_CAL_I2C_Transaction_Init_1,4217
	global	_FC_CAL_I2C_Master_Init_1

;; *************** function _FC_CAL_I2C_Master_Init_1 *****************
;; Defined at:
;;		line 281 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FC_CAL_I2C_Transaction_Init_1
;; This function uses a non-reentrant model
;;
psect	text29,class=CODE,space=0,reloc=2,group=0
	line	281
global __ptext29
__ptext29:
psect	text29
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	281
	global	__size_of_FC_CAL_I2C_Master_Init_1
	__size_of_FC_CAL_I2C_Master_Init_1	equ	__end_of_FC_CAL_I2C_Master_Init_1-_FC_CAL_I2C_Master_Init_1
	
_FC_CAL_I2C_Master_Init_1:
;incstack = 0
	opt	callstack 27
	line	290
	
l2691:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	291
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	406
	
l719:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Master_Init_1
	__end_of_FC_CAL_I2C_Master_Init_1:
	signat	_FC_CAL_I2C_Master_Init_1,89
	global	_FCD_01c01_temp_hum_sensor__GetTemperatureInt

;; *************** function _FCD_01c01_temp_hum_sensor__GetTemperatureInt *****************
;; Defined at:
;;		line 4061 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_TEMP        4    0        long 
;;  FCR_RETVAL      2   45[COMRAM] short 
;; Return value:  Size  Location     Type
;;                  2   43[COMRAM] short 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    6
;; This function calls:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;;		___fltol
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text30,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	4061
global __ptext30
__ptext30:
psect	text30
	file	"BL0144 dig temp sensor - PIC.c"
	line	4061
	global	__size_of_FCD_01c01_temp_hum_sensor__GetTemperatureInt
	__size_of_FCD_01c01_temp_hum_sensor__GetTemperatureInt	equ	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureInt-_FCD_01c01_temp_hum_sensor__GetTemperatureInt
	
_FCD_01c01_temp_hum_sensor__GetTemperatureInt:
;incstack = 0
	opt	callstack 24
	line	4068
	
l4701:
	call	_FCD_01c01_temp_hum_sensor__GetTemperatureReal	;wreg free
	movff	0+?_FCD_01c01_temp_hum_sensor__GetTemperatureReal,(c:___fltol@f1)
	movff	1+?_FCD_01c01_temp_hum_sensor__GetTemperatureReal,(c:___fltol@f1+1)
	movff	2+?_FCD_01c01_temp_hum_sensor__GetTemperatureReal,(c:___fltol@f1+2)
	movff	3+?_FCD_01c01_temp_hum_sensor__GetTemperatureReal,(c:___fltol@f1+3)
	
	call	___fltol	;wreg free
	movff	0+?___fltol,(c:FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL)
	movff	1+?___fltol,(c:FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL+1)
	line	4070
	
l4703:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureInt)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureInt@FCR_RETVAL+1),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureInt+1)
	line	4072
	
l1430:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureInt
	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureInt:
	signat	_FCD_01c01_temp_hum_sensor__GetTemperatureInt,90
	global	___fltol

;; *************** function ___fltol *****************
;; Defined at:
;;		line 43 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
;; Parameters:    Size  Location     Type
;;  f1              4   33[COMRAM] short 
;; Auto vars:     Size  Location     Type
;;  exp1            1   42[COMRAM] unsigned char 
;;  sign1           1   41[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4   33[COMRAM] long 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        10       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureInt
;; This function uses a non-reentrant model
;;
psect	text31,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
	line	43
global __ptext31
__ptext31:
psect	text31
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\fltol.c"
	line	43
	global	__size_of___fltol
	__size_of___fltol	equ	__end_of___fltol-___fltol
	
___fltol:
;incstack = 0
	opt	callstack 28
	line	47
	
l4633:
	rlcf	((c:___fltol@f1+2))^00h,c,w
	rlcf	((c:___fltol@f1+3))^00h,c,w
	movwf	((c:___fltol@exp1))^00h,c
	movf	((c:___fltol@exp1))^00h,c,w
	btfss	status,2
	goto	u3401
	goto	u3400
u3401:
	goto	l4639
u3400:
	line	48
	
l4635:
	movlw	low(0)
	movwf	((c:?___fltol))^00h,c
	movlw	high(0)
	movwf	((c:?___fltol+1))^00h,c
	movlw	low highword(0)
	movwf	((c:?___fltol+2))^00h,c
	movlw	high highword(0)
	movwf	((c:?___fltol+3))^00h,c
	goto	l1786
	line	49
	
l4639:
	movff	(c:___fltol@f1),??___fltol+0+0
	movff	(c:___fltol@f1+1),??___fltol+0+0+1
	movff	(c:___fltol@f1+2),??___fltol+0+0+2
	movff	(c:___fltol@f1+3),??___fltol+0+0+3
	movlw	01Fh+1
	goto	u3410
u3415:
	bcf	status,0
	rrcf	(??___fltol+0+3)^00h,c
	rrcf	(??___fltol+0+2)^00h,c
	rrcf	(??___fltol+0+1)^00h,c
	rrcf	(??___fltol+0+0)^00h,c
u3410:
	decfsz	wreg
	goto	u3415
	movf	(??___fltol+0+0)^00h,c,w
	movwf	((c:___fltol@sign1))^00h,c
	line	50
	
l4641:
	bsf	(0+(23/8)+(c:___fltol@f1))^00h,c,(23)&7
	line	51
	
l4643:
	movlw	0FFh
	andwf	((c:___fltol@f1))^00h,c
	movlw	0FFh
	andwf	((c:___fltol@f1+1))^00h,c
	movlw	0FFh
	andwf	((c:___fltol@f1+2))^00h,c
	movlw	0
	andwf	((c:___fltol@f1+3))^00h,c
	line	52
	
l4645:
	movlw	(096h)&0ffh
	subwf	((c:___fltol@exp1))^00h,c
	line	53
	
l4647:
	btfsc	((c:___fltol@exp1))^00h,c,7
	goto	u3420
	goto	u3421

u3421:
	goto	l4659
u3420:
	line	54
	
l4649:
		movf	((c:___fltol@exp1))^00h,c,w
	xorlw	80h
	addlw	-(80h^-23)
	btfsc	status,0
	goto	u3431
	goto	u3430

u3431:
	goto	l4655
u3430:
	goto	l4635
	line	57
	
l4655:
	bcf	status,0
	rrcf	((c:___fltol@f1+3))^00h,c
	rrcf	((c:___fltol@f1+2))^00h,c
	rrcf	((c:___fltol@f1+1))^00h,c
	rrcf	((c:___fltol@f1))^00h,c
	line	58
	
l4657:
	incfsz	((c:___fltol@exp1))^00h,c
	
	goto	l4655
	goto	l4669
	line	60
	
l4659:
		movlw	020h-1
	cpfsgt	((c:___fltol@exp1))^00h,c
	goto	u3441
	goto	u3440

u3441:
	goto	l4667
u3440:
	goto	l4635
	line	63
	
l4665:
	bcf	status,0
	rlcf	((c:___fltol@f1))^00h,c
	rlcf	((c:___fltol@f1+1))^00h,c
	rlcf	((c:___fltol@f1+2))^00h,c
	rlcf	((c:___fltol@f1+3))^00h,c
	line	64
	decf	((c:___fltol@exp1))^00h,c
	line	62
	
l4667:
	movf	((c:___fltol@exp1))^00h,c,w
	btfss	status,2
	goto	u3451
	goto	u3450
u3451:
	goto	l4665
u3450:
	line	67
	
l4669:
	movf	((c:___fltol@sign1))^00h,c,w
	btfsc	status,2
	goto	u3461
	goto	u3460
u3461:
	goto	l4673
u3460:
	line	68
	
l4671:
	comf	((c:___fltol@f1+3))^00h,c
	comf	((c:___fltol@f1+2))^00h,c
	comf	((c:___fltol@f1+1))^00h,c
	negf	((c:___fltol@f1))^00h,c
	movlw	0
	addwfc	((c:___fltol@f1+1))^00h,c
	addwfc	((c:___fltol@f1+2))^00h,c
	addwfc	((c:___fltol@f1+3))^00h,c
	line	69
	
l4673:
	movff	(c:___fltol@f1),(c:?___fltol)
	movff	(c:___fltol@f1+1),(c:?___fltol+1)
	movff	(c:___fltol@f1+2),(c:?___fltol+2)
	movff	(c:___fltol@f1+3),(c:?___fltol+3)
	line	70
	
l1786:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fltol
	__end_of___fltol:
	signat	___fltol,4220
	global	_FCD_01c01_temp_hum_sensor__GetTemperatureReal

;; *************** function _FCD_01c01_temp_hum_sensor__GetTemperatureReal *****************
;; Defined at:
;;		line 4017 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCR_RETVAL      4   29[COMRAM] float 
;;  FCL_TEMP        2    0        unsigned short 
;; Return value:  Size  Location     Type
;;                  4   25[COMRAM] float 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_FCD_01c01_temp_hum_sensor__Sample
;;		___fladd
;;		___fldiv
;;		___flmul
;;		___xxtofl
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureInt
;; This function uses a non-reentrant model
;;
psect	text32,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	4017
global __ptext32
__ptext32:
psect	text32
	file	"BL0144 dig temp sensor - PIC.c"
	line	4017
	global	__size_of_FCD_01c01_temp_hum_sensor__GetTemperatureReal
	__size_of_FCD_01c01_temp_hum_sensor__GetTemperatureReal	equ	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureReal-_FCD_01c01_temp_hum_sensor__GetTemperatureReal
	
_FCD_01c01_temp_hum_sensor__GetTemperatureReal:
;incstack = 0
	opt	callstack 24
	line	4024
	
l4607:
	movf	((c:_FCV_01c01_temp_hum_sensor__SAMPLEMASK))^00h,c,w	;volatile
	btfsc	status,2
	goto	u3371
	goto	u3370
u3371:
	goto	l4611
u3370:
	
l4609:
	
	btfss	((c:_FCV_01c01_temp_hum_sensor__SAMPLEMASK))^00h,c,(1)&7	;volatile
	goto	u3381
	goto	u3380
u3381:
	goto	l4613
u3380:
	line	4027
	
l4611:
	call	_FCD_01c01_temp_hum_sensor__Sample	;wreg free
	line	4033
	
l4613:
	movf	((c:_FCV_01c01_temp_hum_sensor__SAMPLEMASK))^00h,c,w	;volatile
	iorlw	low(02h)
	movwf	((c:_FCV_01c01_temp_hum_sensor__SAMPLEMASK))^00h,c	;volatile
	line	4035
	
l4615:
	movf	((c:_FCV_01c01_temp_hum_sensor__SCALE))^00h,c,w	;volatile
	btfsc	status,2
	goto	u3391
	goto	u3390
u3391:
	goto	l4623
u3390:
	line	4038
	
l4617:
	movff	(c:_FCV_01c01_temp_hum_sensor__TEMP),(c:___xxtofl@val)	;volatile
	movff	(c:_FCV_01c01_temp_hum_sensor__TEMP+1),(c:___xxtofl@val+1)	;volatile
	clrf	((c:___xxtofl@val+2))^00h,c
	clrf	((c:___xxtofl@val+3))^00h,c
	movlw	(0)&0ffh
	
	call	___xxtofl
	movff	0+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4039
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___fldiv@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___fldiv@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___fldiv@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___fldiv@b+3)
	movlw	low(normalize32(0x477fff00))
	movwf	((c:___fldiv@a))^00h,c
	movlw	high(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+3))^00h,c
	call	___fldiv	;wreg free
	movff	0+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4040
	
l4619:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___flmul@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___flmul@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___flmul@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___flmul@b+3)
	movlw	low(normalize32(0x439d8000))
	movwf	((c:___flmul@a))^00h,c
	movlw	high(normalize32(0x439d8000))
	movwf	((c:___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x439d8000))
	movwf	((c:___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x439d8000))
	movwf	((c:___flmul@a+3))^00h,c
	call	___flmul	;wreg free
	movff	0+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4041
	
l4621:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___fladd@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___fladd@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___fladd@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___fladd@b+3)
	movlw	low(normalize32(0xc2440000))
	movwf	((c:___fladd@a))^00h,c
	movlw	high(normalize32(0xc2440000))
	movwf	((c:___fladd@a+1))^00h,c
	movlw	low highword(normalize32(0xc2440000))
	movwf	((c:___fladd@a+2))^00h,c
	movlw	high highword(normalize32(0xc2440000))
	movwf	((c:___fladd@a+3))^00h,c
	call	___fladd	;wreg free
	movff	0+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4043
	goto	l4629
	line	4045
	
l4623:
	movff	(c:_FCV_01c01_temp_hum_sensor__TEMP),(c:___xxtofl@val)	;volatile
	movff	(c:_FCV_01c01_temp_hum_sensor__TEMP+1),(c:___xxtofl@val+1)	;volatile
	clrf	((c:___xxtofl@val+2))^00h,c
	clrf	((c:___xxtofl@val+3))^00h,c
	movlw	(0)&0ffh
	
	call	___xxtofl
	movff	0+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___xxtofl,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4046
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___fldiv@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___fldiv@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___fldiv@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___fldiv@b+3)
	movlw	low(normalize32(0x477fff00))
	movwf	((c:___fldiv@a))^00h,c
	movlw	high(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x477fff00))
	movwf	((c:___fldiv@a+3))^00h,c
	call	___fldiv	;wreg free
	movff	0+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___fldiv,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4047
	
l4625:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___flmul@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___flmul@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___flmul@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___flmul@b+3)
	movlw	low(normalize32(0x432f0000))
	movwf	((c:___flmul@a))^00h,c
	movlw	high(normalize32(0x432f0000))
	movwf	((c:___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x432f0000))
	movwf	((c:___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x432f0000))
	movwf	((c:___flmul@a+3))^00h,c
	call	___flmul	;wreg free
	movff	0+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___flmul,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4048
	
l4627:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:___fladd@b)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:___fladd@b+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:___fladd@b+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:___fladd@b+3)
	movlw	low(normalize32(0xc2340000))
	movwf	((c:___fladd@a))^00h,c
	movlw	high(normalize32(0xc2340000))
	movwf	((c:___fladd@a+1))^00h,c
	movlw	low highword(normalize32(0xc2340000))
	movwf	((c:___fladd@a+2))^00h,c
	movlw	high highword(normalize32(0xc2340000))
	movwf	((c:___fladd@a+3))^00h,c
	call	___fladd	;wreg free
	movff	0+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL)
	movff	1+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1)
	movff	2+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2)
	movff	3+?___fladd,(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3)
	
	line	4052
	
l4629:
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureReal)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+1),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureReal+1)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+2),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureReal+2)
	movff	(c:FCD_01c01_temp_hum_sensor__GetTemperatureReal@FCR_RETVAL+3),(c:?_FCD_01c01_temp_hum_sensor__GetTemperatureReal+3)
	line	4054
	
l1427:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureReal
	__end_of_FCD_01c01_temp_hum_sensor__GetTemperatureReal:
	signat	_FCD_01c01_temp_hum_sensor__GetTemperatureReal,92
	global	___xxtofl

;; *************** function ___xxtofl *****************
;; Defined at:
;;		line 10 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
;; Parameters:    Size  Location     Type
;;  sign            1    wreg     unsigned char 
;;  val             4    0[COMRAM] long 
;; Auto vars:     Size  Location     Type
;;  sign            1    8[COMRAM] unsigned char 
;;  arg             4   10[COMRAM] unsigned long 
;;  exp             1    9[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         6       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        14       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       14 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;; This function uses a non-reentrant model
;;
psect	text33,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
global __ptext33
__ptext33:
psect	text33
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\xxtofl.c"
	line	10
	global	__size_of___xxtofl
	__size_of___xxtofl	equ	__end_of___xxtofl-___xxtofl
	
___xxtofl:
;incstack = 0
	opt	callstack 27
	movwf	((c:___xxtofl@sign))^00h,c
	line	15
	
l4441:
	movf	((c:___xxtofl@sign))^00h,c,w
	btfsc	status,2
	goto	u3191
	goto	u3190
u3191:
	goto	l2140
u3190:
	
l4443:
	btfsc	((c:___xxtofl@val+3))^00h,c,7
	goto	u3200
	goto	u3201

u3201:
	goto	l2140
u3200:
	line	16
	
l4445:
	movff	(c:___xxtofl@val),??___xxtofl+0+0
	movff	(c:___xxtofl@val+1),??___xxtofl+0+0+1
	movff	(c:___xxtofl@val+2),??___xxtofl+0+0+2
	movff	(c:___xxtofl@val+3),??___xxtofl+0+0+3
	comf	(??___xxtofl+0+0)^00h,c
	comf	(??___xxtofl+0+1)^00h,c
	comf	(??___xxtofl+0+2)^00h,c
	comf	(??___xxtofl+0+3)^00h,c
	incf	(??___xxtofl+0+0)^00h,c
	movlw	0
	addwfc	(??___xxtofl+0+1)^00h,c
	addwfc	(??___xxtofl+0+2)^00h,c
	addwfc	(??___xxtofl+0+3)^00h,c
	movff	??___xxtofl+0+0,(c:___xxtofl@arg)
	movff	??___xxtofl+0+1,(c:___xxtofl@arg+1)
	movff	??___xxtofl+0+2,(c:___xxtofl@arg+2)
	movff	??___xxtofl+0+3,(c:___xxtofl@arg+3)
	line	17
	goto	l4447
	line	18
	
l2140:
	line	19
	movff	(c:___xxtofl@val),(c:___xxtofl@arg)
	movff	(c:___xxtofl@val+1),(c:___xxtofl@arg+1)
	movff	(c:___xxtofl@val+2),(c:___xxtofl@arg+2)
	movff	(c:___xxtofl@val+3),(c:___xxtofl@arg+3)
	line	21
	
l4447:
	movf	((c:___xxtofl@val))^00h,c,w
iorwf	((c:___xxtofl@val+1))^00h,c,w
iorwf	((c:___xxtofl@val+2))^00h,c,w
iorwf	((c:___xxtofl@val+3))^00h,c,w
	btfss	status,2
	goto	u3211
	goto	u3210

u3211:
	goto	l4453
u3210:
	line	22
	
l4449:
	movlw	low(normalize32(0x0))
	movwf	((c:?___xxtofl))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?___xxtofl+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?___xxtofl+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?___xxtofl+3))^00h,c
	goto	l2143
	line	23
	
l4453:
	movlw	low(096h)
	movwf	((c:___xxtofl@exp))^00h,c
	line	24
	goto	l4457
	line	25
	
l4455:
	incf	((c:___xxtofl@exp))^00h,c
	line	26
	bcf	status,0
	rrcf	((c:___xxtofl@arg+3))^00h,c
	rrcf	((c:___xxtofl@arg+2))^00h,c
	rrcf	((c:___xxtofl@arg+1))^00h,c
	rrcf	((c:___xxtofl@arg))^00h,c
	line	24
	
l4457:
	movlw	0
	andwf	((c:___xxtofl@arg))^00h,c,w
	movwf	(??___xxtofl+0+0)^00h,c
	movlw	0
	andwf	((c:___xxtofl@arg+1))^00h,c,w
	movwf	1+(??___xxtofl+0+0)^00h,c
	
	movlw	0
	andwf	((c:___xxtofl@arg+2))^00h,c,w
	movwf	2+(??___xxtofl+0+0)^00h,c
	
	movlw	0FEh
	andwf	((c:___xxtofl@arg+3))^00h,c,w
	movwf	3+(??___xxtofl+0+0)^00h,c
	movf	(??___xxtofl+0+0)^00h,c,w
iorwf	(??___xxtofl+0+1)^00h,c,w
iorwf	(??___xxtofl+0+2)^00h,c,w
iorwf	(??___xxtofl+0+3)^00h,c,w
	btfss	status,2
	goto	u3221
	goto	u3220

u3221:
	goto	l4455
u3220:
	goto	l2147
	line	29
	
l4459:
	incf	((c:___xxtofl@exp))^00h,c
	line	30
	
l4461:
	movlw	low(01h)
	addwf	((c:___xxtofl@arg))^00h,c
	movlw	0
	addwfc	((c:___xxtofl@arg+1))^00h,c
	addwfc	((c:___xxtofl@arg+2))^00h,c
	addwfc	((c:___xxtofl@arg+3))^00h,c
	line	31
	
l4463:
	bcf	status,0
	rrcf	((c:___xxtofl@arg+3))^00h,c
	rrcf	((c:___xxtofl@arg+2))^00h,c
	rrcf	((c:___xxtofl@arg+1))^00h,c
	rrcf	((c:___xxtofl@arg))^00h,c
	line	32
	
l2147:
	line	28
	movlw	0
	andwf	((c:___xxtofl@arg))^00h,c,w
	movwf	(??___xxtofl+0+0)^00h,c
	movlw	0
	andwf	((c:___xxtofl@arg+1))^00h,c,w
	movwf	1+(??___xxtofl+0+0)^00h,c
	
	movlw	0
	andwf	((c:___xxtofl@arg+2))^00h,c,w
	movwf	2+(??___xxtofl+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:___xxtofl@arg+3))^00h,c,w
	movwf	3+(??___xxtofl+0+0)^00h,c
	movf	(??___xxtofl+0+0)^00h,c,w
iorwf	(??___xxtofl+0+1)^00h,c,w
iorwf	(??___xxtofl+0+2)^00h,c,w
iorwf	(??___xxtofl+0+3)^00h,c,w
	btfss	status,2
	goto	u3231
	goto	u3230

u3231:
	goto	l4459
u3230:
	goto	l4467
	line	34
	
l4465:
	decf	((c:___xxtofl@exp))^00h,c
	line	35
	bcf	status,0
	rlcf	((c:___xxtofl@arg))^00h,c
	rlcf	((c:___xxtofl@arg+1))^00h,c
	rlcf	((c:___xxtofl@arg+2))^00h,c
	rlcf	((c:___xxtofl@arg+3))^00h,c
	line	33
	
l4467:
	
	btfsc	((c:___xxtofl@arg+2))^00h,c,(23)&7
	goto	u3241
	goto	u3240
u3241:
	goto	l2154
u3240:
	
l4469:
		movlw	02h-0
	cpfslt	((c:___xxtofl@exp))^00h,c
	goto	u3251
	goto	u3250

u3251:
	goto	l4465
u3250:
	
l2154:
	line	37
	
	btfsc	((c:___xxtofl@exp))^00h,c,(0)&7
	goto	u3261
	goto	u3260
u3261:
	goto	l4473
u3260:
	line	38
	
l4471:
	bcf	(0+(23/8)+(c:___xxtofl@arg))^00h,c,(23)&7
	line	39
	
l4473:
	bcf status,0
	rrcf	((c:___xxtofl@exp))^00h,c

	line	40
	
l4475:
	movff	(c:___xxtofl@exp),??___xxtofl+0+0
	clrf	(??___xxtofl+0+0+1)^00h,c
	clrf	(??___xxtofl+0+0+2)^00h,c
	clrf	(??___xxtofl+0+0+3)^00h,c
	movff	??___xxtofl+0+0,??___xxtofl+0+3
	clrf	(??___xxtofl+0+2)^00h,c
	clrf	(??___xxtofl+0+1)^00h,c
	clrf	(??___xxtofl+0+0)^00h,c
	movf	(??___xxtofl+0+0)^00h,c,w
	iorwf	((c:___xxtofl@arg))^00h,c
	movf	(??___xxtofl+0+1)^00h,c,w
	iorwf	((c:___xxtofl@arg+1))^00h,c
	movf	(??___xxtofl+0+2)^00h,c,w
	iorwf	((c:___xxtofl@arg+2))^00h,c
	movf	(??___xxtofl+0+3)^00h,c,w
	iorwf	((c:___xxtofl@arg+3))^00h,c

	line	41
	
l4477:
	movf	((c:___xxtofl@sign))^00h,c,w
	btfsc	status,2
	goto	u3271
	goto	u3270
u3271:
	goto	l4483
u3270:
	
l4479:
	btfsc	((c:___xxtofl@val+3))^00h,c,7
	goto	u3280
	goto	u3281

u3281:
	goto	l4483
u3280:
	line	42
	
l4481:
	bsf	(0+(31/8)+(c:___xxtofl@arg))^00h,c,(31)&7
	line	43
	
l4483:
	movff	(c:___xxtofl@arg),(c:?___xxtofl)
	movff	(c:___xxtofl@arg+1),(c:?___xxtofl+1)
	movff	(c:___xxtofl@arg+2),(c:?___xxtofl+2)
	movff	(c:___xxtofl@arg+3),(c:?___xxtofl+3)
	line	44
	
l2143:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___xxtofl
	__end_of___xxtofl:
	signat	___xxtofl,8316
	global	___flmul

;; *************** function ___flmul *****************
;; Defined at:
;;		line 8 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[COMRAM] unsigned char 
;;  a               4    4[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  prod            4   19[COMRAM] struct .
;;  grs             4   14[COMRAM] unsigned long 
;;  temp            2   23[COMRAM] struct .
;;  bexp            1   18[COMRAM] unsigned char 
;;  aexp            1   13[COMRAM] unsigned char 
;;  sign            1   12[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  4    0[COMRAM] unsigned char 
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
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;; This function uses a non-reentrant model
;;
psect	text34,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
global __ptext34
__ptext34:
psect	text34
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcmul.c"
	line	8
	global	__size_of___flmul
	__size_of___flmul	equ	__end_of___flmul-___flmul
	
___flmul:
;incstack = 0
	opt	callstack 27
	line	17
	
l4311:
	movf	(0+((c:___flmul@b)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:___flmul@sign))^00h,c
	line	18
	movf	(0+((c:___flmul@b)+03h))^00h,c,w
	addwf	(0+((c:___flmul@b)+03h))^00h,c,w
	movwf	((c:___flmul@bexp))^00h,c
	line	19
	
l4313:
	
	btfss	(0+((c:___flmul@b)+02h))^00h,c,(7)&7
	goto	u3011
	goto	u3010
u3011:
	goto	l4317
u3010:
	line	20
	
l4315:
	bsf	(0+(0/8)+(c:___flmul@bexp))^00h,c,(0)&7
	line	24
	
l4317:
	movf	((c:___flmul@bexp))^00h,c,w
	btfsc	status,2
	goto	u3021
	goto	u3020
u3021:
	goto	l4325
u3020:
	line	26
	
l4319:
		incf	((c:___flmul@bexp))^00h,c,w
	btfss	status,2
	goto	u3031
	goto	u3030

u3031:
	goto	l4323
u3030:
	line	28
	
l4321:
	movlw	low(normalize32(0x0))
	movwf	((c:___flmul@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___flmul@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___flmul@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___flmul@b+3))^00h,c
	line	31
	
l4323:
	bsf	(0+(23/8)+(c:___flmul@b))^00h,c,(23)&7
	line	33
	goto	l4327
	line	36
	
l4325:
	movlw	low(normalize32(0x0))
	movwf	((c:___flmul@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___flmul@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___flmul@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___flmul@b+3))^00h,c
	line	39
	
l4327:
	movf	(0+((c:___flmul@a)+03h))^00h,c,w
	andlw	low(080h)
	xorwf	((c:___flmul@sign))^00h,c
	line	40
	
l4329:
	movf	(0+((c:___flmul@a)+03h))^00h,c,w
	addwf	(0+((c:___flmul@a)+03h))^00h,c,w
	movwf	((c:___flmul@aexp))^00h,c
	line	41
	
l4331:
	
	btfss	(0+((c:___flmul@a)+02h))^00h,c,(7)&7
	goto	u3041
	goto	u3040
u3041:
	goto	l4335
u3040:
	line	42
	
l4333:
	bsf	(0+(0/8)+(c:___flmul@aexp))^00h,c,(0)&7
	line	45
	
l4335:
	movf	((c:___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	u3051
	goto	u3050
u3051:
	goto	l4343
u3050:
	line	48
	
l4337:
		incf	((c:___flmul@aexp))^00h,c,w
	btfss	status,2
	goto	u3061
	goto	u3060

u3061:
	goto	l4341
u3060:
	line	50
	
l4339:
	movlw	low(normalize32(0x0))
	movwf	((c:___flmul@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___flmul@a+3))^00h,c
	line	53
	
l4341:
	bsf	(0+(23/8)+(c:___flmul@a))^00h,c,(23)&7
	line	54
	goto	l2099
	line	57
	
l4343:
	movlw	low(normalize32(0x0))
	movwf	((c:___flmul@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___flmul@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___flmul@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___flmul@a+3))^00h,c
	line	58
	
l2099:
	line	65
	movf	((c:___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	u3071
	goto	u3070
u3071:
	goto	l4347
u3070:
	
l4345:
	movf	((c:___flmul@bexp))^00h,c,w
	btfss	status,2
	goto	u3081
	goto	u3080
u3081:
	goto	l4351
u3080:
	line	66
	
l4347:
	movlw	low(normalize32(0x0))
	movwf	((c:?___flmul))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?___flmul+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?___flmul+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?___flmul+3))^00h,c
	goto	l2103
	line	95
	
l4351:
	movf	(0+((c:___flmul@a)+02h))^00h,c,w
	mulwf	((c:___flmul@b))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	96
	
l4353:
	movf	((c:___flmul@temp))^00h,c,w
	movwf	((c:___flmul@grs))^00h,c
	clrf	((c:___flmul@grs+1))^00h,c
	clrf	((c:___flmul@grs+2))^00h,c
	clrf	((c:___flmul@grs+3))^00h,c

	line	97
	
l4355:
	movf	(0+((c:___flmul@temp)+01h))^00h,c,w
	movwf	((c:___flmul@prod))^00h,c
	clrf	((c:___flmul@prod+1))^00h,c
	clrf	((c:___flmul@prod+2))^00h,c
	clrf	((c:___flmul@prod+3))^00h,c

	line	98
	movf	(0+((c:___flmul@a)+01h))^00h,c,w
	mulwf	(0+((c:___flmul@b)+01h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	99
	
l4357:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@grs))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+1))^00h,c
	addwfc	((c:___flmul@grs+2))^00h,c
	addwfc	((c:___flmul@grs+3))^00h,c
	line	100
	
l4359:
	movf	(0+((c:___flmul@temp)+01h))^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+1))^00h,c
	addwfc	((c:___flmul@prod+2))^00h,c
	addwfc	((c:___flmul@prod+3))^00h,c
	line	101
	movf	((c:___flmul@a))^00h,c,w
	mulwf	(0+((c:___flmul@b)+02h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	102
	
l4361:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@grs))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+1))^00h,c
	addwfc	((c:___flmul@grs+2))^00h,c
	addwfc	((c:___flmul@grs+3))^00h,c
	line	103
	
l4363:
	movf	(0+((c:___flmul@temp)+01h))^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+1))^00h,c
	addwfc	((c:___flmul@prod+2))^00h,c
	addwfc	((c:___flmul@prod+3))^00h,c
	line	104
	
l4365:
	movff	(c:___flmul@grs+2),(c:___flmul@grs+3)
	movff	(c:___flmul@grs+1),(c:___flmul@grs+2)
	movff	(c:___flmul@grs),(c:___flmul@grs+1)
	clrf	((c:___flmul@grs))^00h,c
	line	105
	
l4367:
	movf	((c:___flmul@a))^00h,c,w
	mulwf	(0+((c:___flmul@b)+01h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	106
	
l4369:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@grs))^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	addwfc	((c:___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+3))^00h,c

	line	107
	
l4371:
	movf	(0+((c:___flmul@a)+01h))^00h,c,w
	mulwf	((c:___flmul@b))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	108
	
l4373:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@grs))^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	addwfc	((c:___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+3))^00h,c

	line	109
	
l4375:
	movff	(c:___flmul@grs+2),(c:___flmul@grs+3)
	movff	(c:___flmul@grs+1),(c:___flmul@grs+2)
	movff	(c:___flmul@grs),(c:___flmul@grs+1)
	clrf	((c:___flmul@grs))^00h,c
	line	110
	movf	((c:___flmul@a))^00h,c,w
	mulwf	((c:___flmul@b))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	111
	
l4377:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@grs))^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	addwfc	((c:___flmul@grs+1))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+2))^00h,c
	movlw	0
	addwfc	((c:___flmul@grs+3))^00h,c

	line	112
	
l4379:
	movf	(0+((c:___flmul@a)+02h))^00h,c,w
	mulwf	(0+((c:___flmul@b)+01h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	113
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	addwfc	((c:___flmul@prod+1))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+2))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+3))^00h,c

	line	114
	
l4381:
	movf	(0+((c:___flmul@a)+01h))^00h,c,w
	mulwf	(0+((c:___flmul@b)+02h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	115
	
l4383:
	movf	((c:___flmul@temp))^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	addwfc	((c:___flmul@prod+1))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+2))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+3))^00h,c

	line	116
	movf	(0+((c:___flmul@a)+02h))^00h,c,w
	mulwf	(0+((c:___flmul@b)+02h))^00h,c
	movff	prodl,(c:___flmul@temp)
	movff	prodh,(c:___flmul@temp+1)
	line	117
	
l4385:
	movf	((c:___flmul@temp))^00h,c,w
	movwf	(??___flmul+0+0)^00h,c
	movf	((c:___flmul@temp+1))^00h,c,w
	movwf	1+(??___flmul+0+0)^00h,c
	
	clrf	2+(??___flmul+0+0)^00h,c
	
	clrf	3+(??___flmul+0+0)^00h,c
	movff	??___flmul+0+2,??___flmul+0+3
	movff	??___flmul+0+1,??___flmul+0+2
	movff	??___flmul+0+0,??___flmul+0+1
	clrf	(??___flmul+0+0)^00h,c
	movf	(??___flmul+0+0)^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movf	(??___flmul+0+1)^00h,c,w
	addwfc	((c:___flmul@prod+1))^00h,c
	movf	(??___flmul+0+2)^00h,c,w
	addwfc	((c:___flmul@prod+2))^00h,c
	movf	(??___flmul+0+3)^00h,c,w
	addwfc	((c:___flmul@prod+3))^00h,c

	line	145
	
l4387:
	movf	(0+((c:___flmul@grs)+03h))^00h,c,w
	addwf	((c:___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+1))^00h,c
	addwfc	((c:___flmul@prod+2))^00h,c
	addwfc	((c:___flmul@prod+3))^00h,c
	line	146
	
l4389:
	movff	(c:___flmul@grs+2),(c:___flmul@grs+3)
	movff	(c:___flmul@grs+1),(c:___flmul@grs+2)
	movff	(c:___flmul@grs),(c:___flmul@grs+1)
	clrf	((c:___flmul@grs))^00h,c
	line	149
	
l4391:
	movf	((c:___flmul@aexp))^00h,c,w
	movff	(c:___flmul@bexp),??___flmul+0+0
	clrf	(??___flmul+0+0+1)^00h,c
	addwf	(??___flmul+0+0)^00h,c
	movlw	0
	addwfc	(??___flmul+0+1)^00h,c
	movlw	low(-126)
	addwf	(??___flmul+0+0)^00h,c,w
	movwf	((c:___flmul@temp))^00h,c
	movlw	high(-126)
	addwfc	(??___flmul+0+1)^00h,c,w
	movwf	1+((c:___flmul@temp))^00h,c
	line	152
	goto	l4399
	line	153
	
l4393:
	bcf	status,0
	rlcf	((c:___flmul@prod))^00h,c
	rlcf	((c:___flmul@prod+1))^00h,c
	rlcf	((c:___flmul@prod+2))^00h,c
	rlcf	((c:___flmul@prod+3))^00h,c
	line	154
	
l4395:
	
	btfss	((c:___flmul@grs+3))^00h,c,(31)&7
	goto	u3091
	goto	u3090
u3091:
	goto	l2106
u3090:
	line	155
	
l4397:
	bsf	(0+(0/8)+(c:___flmul@prod))^00h,c,(0)&7
	line	156
	
l2106:
	line	157
	bcf	status,0
	rlcf	((c:___flmul@grs))^00h,c
	rlcf	((c:___flmul@grs+1))^00h,c
	rlcf	((c:___flmul@grs+2))^00h,c
	rlcf	((c:___flmul@grs+3))^00h,c
	line	158
	decf	((c:___flmul@temp))^00h,c
	btfss	status,0
	decf	((c:___flmul@temp+1))^00h,c
	line	152
	
l4399:
	
	btfss	((c:___flmul@prod+2))^00h,c,(23)&7
	goto	u3101
	goto	u3100
u3101:
	goto	l4393
u3100:
	line	163
	
l4401:
	movlw	low(0)
	movwf	((c:___flmul@aexp))^00h,c
	line	164
	
l4403:
	
	btfss	((c:___flmul@grs+3))^00h,c,(31)&7
	goto	u3111
	goto	u3110
u3111:
	goto	l2108
u3110:
	line	165
	
l4405:
	movlw	0FFh
	andwf	((c:___flmul@grs))^00h,c,w
	movwf	(??___flmul+0+0)^00h,c
	movlw	0FFh
	andwf	((c:___flmul@grs+1))^00h,c,w
	movwf	1+(??___flmul+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:___flmul@grs+2))^00h,c,w
	movwf	2+(??___flmul+0+0)^00h,c
	
	movlw	07Fh
	andwf	((c:___flmul@grs+3))^00h,c,w
	movwf	3+(??___flmul+0+0)^00h,c
	movf	(??___flmul+0+0)^00h,c,w
iorwf	(??___flmul+0+1)^00h,c,w
iorwf	(??___flmul+0+2)^00h,c,w
iorwf	(??___flmul+0+3)^00h,c,w
	btfsc	status,2
	goto	u3121
	goto	u3120

u3121:
	goto	l2109
u3120:
	line	166
	
l4407:
	movlw	low(01h)
	movwf	((c:___flmul@aexp))^00h,c
	line	167
	goto	l2108
	line	168
	
l2109:
	line	169
	
	btfss	((c:___flmul@prod))^00h,c,(0)&7
	goto	u3131
	goto	u3130
u3131:
	goto	l2108
u3130:
	goto	l4407
	line	173
	
l2108:
	line	174
	movf	((c:___flmul@aexp))^00h,c,w
	btfsc	status,2
	goto	u3141
	goto	u3140
u3141:
	goto	l4419
u3140:
	line	175
	
l4411:
	movlw	low(01h)
	addwf	((c:___flmul@prod))^00h,c
	movlw	0
	addwfc	((c:___flmul@prod+1))^00h,c
	addwfc	((c:___flmul@prod+2))^00h,c
	addwfc	((c:___flmul@prod+3))^00h,c
	line	176
	
l4413:
	
	btfss	((c:___flmul@prod+3))^00h,c,(24)&7
	goto	u3151
	goto	u3150
u3151:
	goto	l4419
u3150:
	line	177
	
l4415:
	movff	(c:___flmul@prod),??___flmul+0+0
	movff	(c:___flmul@prod+1),??___flmul+0+0+1
	movff	(c:___flmul@prod+2),??___flmul+0+0+2
	movff	(c:___flmul@prod+3),??___flmul+0+0+3
	rlcf	(??___flmul+0+3)^00h,c,w
	rrcf	(??___flmul+0+3)^00h,c
	rrcf	(??___flmul+0+2)^00h,c
	rrcf	(??___flmul+0+1)^00h,c
	rrcf	(??___flmul+0+0)^00h,c
	movff	??___flmul+0+0,(c:___flmul@prod)
	movff	??___flmul+0+1,(c:___flmul@prod+1)
	movff	??___flmul+0+2,(c:___flmul@prod+2)
	movff	??___flmul+0+3,(c:___flmul@prod+3)
	line	178
	
l4417:
	infsnz	((c:___flmul@temp))^00h,c
	incf	((c:___flmul@temp+1))^00h,c
	line	183
	
l4419:
	btfsc	((c:___flmul@temp+1))^00h,c,7
	goto	u3161
	movf	((c:___flmul@temp+1))^00h,c,w
	bnz	u3160
	incf	((c:___flmul@temp))^00h,c,w
	btfss	status,0
	goto	u3161
	goto	u3160

u3161:
	goto	l4423
u3160:
	line	184
	
l4421:
	movlw	low(07F800000h)
	movwf	((c:___flmul@prod))^00h,c
	movlw	high(07F800000h)
	movwf	((c:___flmul@prod+1))^00h,c
	movlw	low highword(07F800000h)
	movwf	((c:___flmul@prod+2))^00h,c
	movlw	high highword(07F800000h)
	movwf	((c:___flmul@prod+3))^00h,c
	line	185
	goto	l4435
	line	187
	
l4423:
	btfsc	((c:___flmul@temp+1))^00h,c,7
	goto	u3170
	movf	((c:___flmul@temp+1))^00h,c,w
	bnz	u3171
	decf	((c:___flmul@temp))^00h,c,w
	btfsc	status,0
	goto	u3171
	goto	u3170

u3171:
	goto	l2116
u3170:
	line	188
	
l4425:
	movlw	low(0)
	movwf	((c:___flmul@prod))^00h,c
	movlw	high(0)
	movwf	((c:___flmul@prod+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___flmul@prod+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___flmul@prod+3))^00h,c
	line	190
	movlw	low(0)
	movwf	((c:___flmul@sign))^00h,c
	line	191
	goto	l4435
	line	192
	
l2116:
	line	194
	movff	(c:___flmul@temp),(c:___flmul@bexp)
	line	195
	
l4427:
	movlw	0FFh
	andwf	((c:___flmul@prod))^00h,c
	movlw	0FFh
	andwf	((c:___flmul@prod+1))^00h,c
	movlw	07Fh
	andwf	((c:___flmul@prod+2))^00h,c
	movlw	0
	andwf	((c:___flmul@prod+3))^00h,c
	line	196
	
l4429:
	
	btfss	((c:___flmul@bexp))^00h,c,(0)&7
	goto	u3181
	goto	u3180
u3181:
	goto	l4433
u3180:
	line	197
	
l4431:
	bsf	(0+(7/8)+0+((c:___flmul@prod)+02h))^00h,c,(7)&7
	line	199
	
l4433:
	bcf	status,0
	rrcf	((c:___flmul@bexp))^00h,c,w
	movwf	(0+((c:___flmul@prod)+03h))^00h,c
	line	201
	
l4435:
	movf	((c:___flmul@sign))^00h,c,w
	iorwf	(0+((c:___flmul@prod)+03h))^00h,c
	line	203
	
l4437:
	movff	(c:___flmul@prod),(c:?___flmul)
	movff	(c:___flmul@prod+1),(c:?___flmul+1)
	movff	(c:___flmul@prod+2),(c:?___flmul+2)
	movff	(c:___flmul@prod+3),(c:?___flmul+3)
	line	205
	
l2103:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___flmul
	__end_of___flmul:
	signat	___flmul,8316
	global	___fldiv

;; *************** function ___fldiv *****************
;; Defined at:
;;		line 11 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[COMRAM] unsigned char 
;;  a               4    4[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  grs             4   19[COMRAM] unsigned long 
;;  rem             4   12[COMRAM] unsigned long 
;;  new_exp         2   17[COMRAM] int 
;;  aexp            1   24[COMRAM] unsigned char 
;;  bexp            1   23[COMRAM] unsigned char 
;;  sign            1   16[COMRAM] unsigned char 
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
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;; This function uses a non-reentrant model
;;
psect	text35,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
global __ptext35
__ptext35:
psect	text35
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcdiv.c"
	line	11
	global	__size_of___fldiv
	__size_of___fldiv	equ	__end_of___fldiv-___fldiv
	
___fldiv:
;incstack = 0
	opt	callstack 27
	line	26
	
l4173:
	movf	(0+((c:___fldiv@b)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:___fldiv@sign))^00h,c
	line	27
	movf	(0+((c:___fldiv@b)+03h))^00h,c,w
	addwf	(0+((c:___fldiv@b)+03h))^00h,c,w
	movwf	((c:___fldiv@bexp))^00h,c
	line	28
	
l4175:
	
	btfss	(0+((c:___fldiv@b)+02h))^00h,c,(7)&7
	goto	u2781
	goto	u2780
u2781:
	goto	l4179
u2780:
	line	29
	
l4177:
	bsf	(0+(0/8)+(c:___fldiv@bexp))^00h,c,(0)&7
	line	33
	
l4179:
	movf	((c:___fldiv@bexp))^00h,c,w
	btfsc	status,2
	goto	u2791
	goto	u2790
u2791:
	goto	l4189
u2790:
	line	35
	
l4181:
		incf	((c:___fldiv@bexp))^00h,c,w
	btfss	status,2
	goto	u2801
	goto	u2800

u2801:
	goto	l4185
u2800:
	line	37
	
l4183:
	movlw	low(normalize32(0x0))
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fldiv@b+3))^00h,c
	line	40
	
l4185:
	bsf	(0+(23/8)+(c:___fldiv@b))^00h,c,(23)&7
	line	42
	
l4187:
	movlw	low(0)
	movwf	(0+((c:___fldiv@b)+03h))^00h,c
	line	43
	goto	l4191
	line	46
	
l4189:
	movlw	low(normalize32(0x0))
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fldiv@b+3))^00h,c
	line	49
	
l4191:
	movf	(0+((c:___fldiv@a)+03h))^00h,c,w
	andlw	low(080h)
	xorwf	((c:___fldiv@sign))^00h,c
	line	50
	
l4193:
	movf	(0+((c:___fldiv@a)+03h))^00h,c,w
	addwf	(0+((c:___fldiv@a)+03h))^00h,c,w
	movwf	((c:___fldiv@aexp))^00h,c
	line	51
	
l4195:
	
	btfss	(0+((c:___fldiv@a)+02h))^00h,c,(7)&7
	goto	u2811
	goto	u2810
u2811:
	goto	l4199
u2810:
	line	52
	
l4197:
	bsf	(0+(0/8)+(c:___fldiv@aexp))^00h,c,(0)&7
	line	56
	
l4199:
	movf	((c:___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	u2821
	goto	u2820
u2821:
	goto	l4209
u2820:
	line	58
	
l4201:
		incf	((c:___fldiv@aexp))^00h,c,w
	btfss	status,2
	goto	u2831
	goto	u2830

u2831:
	goto	l4205
u2830:
	line	60
	
l4203:
	movlw	low(normalize32(0x0))
	movwf	((c:___fldiv@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fldiv@a+3))^00h,c
	line	63
	
l4205:
	bsf	(0+(23/8)+(c:___fldiv@a))^00h,c,(23)&7
	line	65
	
l4207:
	movlw	low(0)
	movwf	(0+((c:___fldiv@a)+03h))^00h,c
	line	66
	goto	l4211
	line	69
	
l4209:
	movlw	low(normalize32(0x0))
	movwf	((c:___fldiv@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fldiv@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fldiv@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fldiv@a+3))^00h,c
	line	75
	
l4211:
	movf	((c:___fldiv@a))^00h,c,w
iorwf	((c:___fldiv@a+1))^00h,c,w
iorwf	((c:___fldiv@a+2))^00h,c,w
iorwf	((c:___fldiv@a+3))^00h,c,w
	btfss	status,2
	goto	u2841
	goto	u2840

u2841:
	goto	l4223
u2840:
	line	76
	
l4213:
	movlw	low(0)
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fldiv@b+3))^00h,c
	line	77
	
l4215:
	movlw	low(07F80h)
	iorwf	(0+((c:___fldiv@b)+02h))^00h,c
	movlw	high(07F80h)
	iorwf	(1+((c:___fldiv@b)+02h))^00h,c
	line	78
	
l4217:
	movf	((c:___fldiv@sign))^00h,c,w
	iorwf	(0+((c:___fldiv@b)+03h))^00h,c
	line	79
	
l4219:
	movff	(c:___fldiv@b),(c:?___fldiv)
	movff	(c:___fldiv@b+1),(c:?___fldiv+1)
	movff	(c:___fldiv@b+2),(c:?___fldiv+2)
	movff	(c:___fldiv@b+3),(c:?___fldiv+3)
	goto	l2067
	line	83
	
l4223:
	movf	((c:___fldiv@bexp))^00h,c,w
	btfss	status,2
	goto	u2851
	goto	u2850
u2851:
	goto	l4231
u2850:
	line	84
	
l4225:
	line	85
	
l4227:
	movlw	low(0)
	movwf	((c:?___fldiv))^00h,c
	movlw	high(0)
	movwf	((c:?___fldiv+1))^00h,c
	movlw	low highword(0)
	movwf	((c:?___fldiv+2))^00h,c
	movlw	high highword(0)
	movwf	((c:?___fldiv+3))^00h,c
	goto	l2067
	line	89
	
l4231:
	movf	((c:___fldiv@aexp))^00h,c,w
	movff	(c:___fldiv@bexp),??___fldiv+0+0
	clrf	(??___fldiv+0+0+1)^00h,c
	subwf	(??___fldiv+0+0)^00h,c
	movlw	0
	subwfb	(??___fldiv+0+1)^00h,c
	movlw	low(07Fh)
	addwf	(??___fldiv+0+0)^00h,c,w
	movwf	((c:___fldiv@new_exp))^00h,c
	movlw	high(07Fh)
	addwfc	(??___fldiv+0+1)^00h,c,w
	movwf	1+((c:___fldiv@new_exp))^00h,c
	line	92
	
l4233:
	movff	(c:___fldiv@b),(c:___fldiv@rem)
	movff	(c:___fldiv@b+1),(c:___fldiv@rem+1)
	movff	(c:___fldiv@b+2),(c:___fldiv@rem+2)
	movff	(c:___fldiv@b+3),(c:___fldiv@rem+3)
	line	93
	
l4235:
	movlw	low(0)
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fldiv@b+3))^00h,c
	line	94
	
l4237:
	movlw	low(0)
	movwf	((c:___fldiv@grs))^00h,c
	movlw	high(0)
	movwf	((c:___fldiv@grs+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fldiv@grs+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fldiv@grs+3))^00h,c
	line	96
	
l4239:
	movlw	low(0)
	movwf	((c:___fldiv@aexp))^00h,c
	line	97
	goto	l2069
	line	100
	
l4241:
	movf	((c:___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	u2861
	goto	u2860
u2861:
	goto	l4249
u2860:
	line	101
	
l4243:
	bcf	status,0
	rlcf	((c:___fldiv@rem))^00h,c
	rlcf	((c:___fldiv@rem+1))^00h,c
	rlcf	((c:___fldiv@rem+2))^00h,c
	rlcf	((c:___fldiv@rem+3))^00h,c
	line	102
	bcf	status,0
	rlcf	((c:___fldiv@b))^00h,c
	rlcf	((c:___fldiv@b+1))^00h,c
	rlcf	((c:___fldiv@b+2))^00h,c
	rlcf	((c:___fldiv@b+3))^00h,c
	line	103
	
l4245:
	
	btfss	((c:___fldiv@grs+3))^00h,c,(31)&7
	goto	u2871
	goto	u2870
u2871:
	goto	l2072
u2870:
	line	104
	
l4247:
	bsf	(0+(0/8)+(c:___fldiv@b))^00h,c,(0)&7
	line	105
	
l2072:
	line	106
	bcf	status,0
	rlcf	((c:___fldiv@grs))^00h,c
	rlcf	((c:___fldiv@grs+1))^00h,c
	rlcf	((c:___fldiv@grs+2))^00h,c
	rlcf	((c:___fldiv@grs+3))^00h,c
	line	112
	
l4249:
		movf	((c:___fldiv@a))^00h,c,w
	subwf	((c:___fldiv@rem))^00h,c,w
	movf	((c:___fldiv@a+1))^00h,c,w
	subwfb	((c:___fldiv@rem+1))^00h,c,w
	movf	((c:___fldiv@a+2))^00h,c,w
	subwfb	((c:___fldiv@rem+2))^00h,c,w
	movf	((c:___fldiv@a+3))^00h,c,w
	subwfb	((c:___fldiv@rem+3))^00h,c,w
	btfss	status,0
	goto	u2881
	goto	u2880

u2881:
	goto	l4255
u2880:
	line	115
	
l4251:
	bsf	(0+(30/8)+(c:___fldiv@grs))^00h,c,(30)&7
	line	116
	
l4253:
	movf	((c:___fldiv@a))^00h,c,w
	subwf	((c:___fldiv@rem))^00h,c
	movf	((c:___fldiv@a+1))^00h,c,w
	subwfb	((c:___fldiv@rem+1))^00h,c
	movf	((c:___fldiv@a+2))^00h,c,w
	subwfb	((c:___fldiv@rem+2))^00h,c
	movf	((c:___fldiv@a+3))^00h,c,w
	subwfb	((c:___fldiv@rem+3))^00h,c
	line	118
	
l4255:
	incf	((c:___fldiv@aexp))^00h,c
	line	119
	
l2069:
	line	97
		movlw	01Ah-1
	cpfsgt	((c:___fldiv@aexp))^00h,c
	goto	u2891
	goto	u2890

u2891:
	goto	l4241
u2890:
	line	122
	
l4257:
	movf	((c:___fldiv@rem))^00h,c,w
iorwf	((c:___fldiv@rem+1))^00h,c,w
iorwf	((c:___fldiv@rem+2))^00h,c,w
iorwf	((c:___fldiv@rem+3))^00h,c,w
	btfsc	status,2
	goto	u2901
	goto	u2900

u2901:
	goto	l4267
u2900:
	line	123
	
l4259:
	bsf	(0+(0/8)+(c:___fldiv@grs))^00h,c,(0)&7
	goto	l4267
	line	128
	
l4261:
	bcf	status,0
	rlcf	((c:___fldiv@b))^00h,c
	rlcf	((c:___fldiv@b+1))^00h,c
	rlcf	((c:___fldiv@b+2))^00h,c
	rlcf	((c:___fldiv@b+3))^00h,c
	line	129
	
l4263:
	
	btfss	((c:___fldiv@grs+3))^00h,c,(31)&7
	goto	u2911
	goto	u2910
u2911:
	goto	l2078
u2910:
	line	130
	
l4265:
	bsf	(0+(0/8)+(c:___fldiv@b))^00h,c,(0)&7
	line	131
	
l2078:
	line	132
	bcf	status,0
	rlcf	((c:___fldiv@grs))^00h,c
	rlcf	((c:___fldiv@grs+1))^00h,c
	rlcf	((c:___fldiv@grs+2))^00h,c
	rlcf	((c:___fldiv@grs+3))^00h,c
	line	133
	decf	((c:___fldiv@new_exp))^00h,c
	btfss	status,0
	decf	((c:___fldiv@new_exp+1))^00h,c
	line	127
	
l4267:
	
	btfss	((c:___fldiv@b+2))^00h,c,(23)&7
	goto	u2921
	goto	u2920
u2921:
	goto	l4261
u2920:
	line	139
	
l4269:
	movlw	low(0)
	movwf	((c:___fldiv@aexp))^00h,c
	line	140
	
l4271:
	
	btfss	((c:___fldiv@grs+3))^00h,c,(31)&7
	goto	u2931
	goto	u2930
u2931:
	goto	l2080
u2930:
	line	141
	
l4273:
	movlw	0FFh
	andwf	((c:___fldiv@grs))^00h,c,w
	movwf	(??___fldiv+0+0)^00h,c
	movlw	0FFh
	andwf	((c:___fldiv@grs+1))^00h,c,w
	movwf	1+(??___fldiv+0+0)^00h,c
	
	movlw	0FFh
	andwf	((c:___fldiv@grs+2))^00h,c,w
	movwf	2+(??___fldiv+0+0)^00h,c
	
	movlw	07Fh
	andwf	((c:___fldiv@grs+3))^00h,c,w
	movwf	3+(??___fldiv+0+0)^00h,c
	movf	(??___fldiv+0+0)^00h,c,w
iorwf	(??___fldiv+0+1)^00h,c,w
iorwf	(??___fldiv+0+2)^00h,c,w
iorwf	(??___fldiv+0+3)^00h,c,w
	btfsc	status,2
	goto	u2941
	goto	u2940

u2941:
	goto	l2081
u2940:
	line	142
	
l4275:
	movlw	low(01h)
	movwf	((c:___fldiv@aexp))^00h,c
	line	143
	goto	l2080
	line	144
	
l2081:
	line	145
	
	btfss	((c:___fldiv@b))^00h,c,(0)&7
	goto	u2951
	goto	u2950
u2951:
	goto	l2080
u2950:
	goto	l4275
	line	149
	
l2080:
	line	150
	movf	((c:___fldiv@aexp))^00h,c,w
	btfsc	status,2
	goto	u2961
	goto	u2960
u2961:
	goto	l4287
u2960:
	line	151
	
l4279:
	movlw	low(01h)
	addwf	((c:___fldiv@b))^00h,c
	movlw	0
	addwfc	((c:___fldiv@b+1))^00h,c
	addwfc	((c:___fldiv@b+2))^00h,c
	addwfc	((c:___fldiv@b+3))^00h,c
	line	152
	
l4281:
	
	btfss	((c:___fldiv@b+3))^00h,c,(24)&7
	goto	u2971
	goto	u2970
u2971:
	goto	l4287
u2970:
	line	153
	
l4283:
	movff	(c:___fldiv@b),??___fldiv+0+0
	movff	(c:___fldiv@b+1),??___fldiv+0+0+1
	movff	(c:___fldiv@b+2),??___fldiv+0+0+2
	movff	(c:___fldiv@b+3),??___fldiv+0+0+3
	rlcf	(??___fldiv+0+3)^00h,c,w
	rrcf	(??___fldiv+0+3)^00h,c
	rrcf	(??___fldiv+0+2)^00h,c
	rrcf	(??___fldiv+0+1)^00h,c
	rrcf	(??___fldiv+0+0)^00h,c
	movff	??___fldiv+0+0,(c:___fldiv@b)
	movff	??___fldiv+0+1,(c:___fldiv@b+1)
	movff	??___fldiv+0+2,(c:___fldiv@b+2)
	movff	??___fldiv+0+3,(c:___fldiv@b+3)
	line	154
	
l4285:
	infsnz	((c:___fldiv@new_exp))^00h,c
	incf	((c:___fldiv@new_exp+1))^00h,c
	line	159
	
l4287:
	btfsc	((c:___fldiv@new_exp+1))^00h,c,7
	goto	u2981
	movf	((c:___fldiv@new_exp+1))^00h,c,w
	bnz	u2980
	incf	((c:___fldiv@new_exp))^00h,c,w
	btfss	status,0
	goto	u2981
	goto	u2980

u2981:
	goto	l4291
u2980:
	line	160
	
l4289:
	movlw	high(0FFh)
	movwf	((c:___fldiv@new_exp+1))^00h,c
	setf	((c:___fldiv@new_exp))^00h,c
	line	161
	movlw	low(0)
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fldiv@b+3))^00h,c
	line	165
	
l4291:
	btfsc	((c:___fldiv@new_exp+1))^00h,c,7
	goto	u2990
	movf	((c:___fldiv@new_exp+1))^00h,c,w
	bnz	u2991
	decf	((c:___fldiv@new_exp))^00h,c,w
	btfsc	status,0
	goto	u2991
	goto	u2990

u2991:
	goto	l4295
u2990:
	line	166
	
l4293:
	movlw	high(0)
	movwf	((c:___fldiv@new_exp+1))^00h,c
	movlw	low(0)
	movwf	((c:___fldiv@new_exp))^00h,c
	line	167
	movlw	low(0)
	movwf	((c:___fldiv@b))^00h,c
	movlw	high(0)
	movwf	((c:___fldiv@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fldiv@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fldiv@b+3))^00h,c
	line	169
	movlw	low(0)
	movwf	((c:___fldiv@sign))^00h,c
	line	173
	
l4295:
	movff	(c:___fldiv@new_exp),(c:___fldiv@bexp)
	line	175
	
l4297:
	
	btfss	((c:___fldiv@bexp))^00h,c,(0)&7
	goto	u3001
	goto	u3000
u3001:
	goto	l4301
u3000:
	line	176
	
l4299:
	bsf	(0+(7/8)+0+((c:___fldiv@b)+02h))^00h,c,(7)&7
	line	177
	goto	l4303
	line	180
	
l4301:
	bcf	(0+(7/8)+0+((c:___fldiv@b)+02h))^00h,c,(7)&7
	line	182
	
l4303:
	bcf	status,0
	rrcf	((c:___fldiv@bexp))^00h,c,w
	movwf	(0+((c:___fldiv@b)+03h))^00h,c
	goto	l4217
	line	185
	
l2067:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fldiv
	__end_of___fldiv:
	signat	___fldiv,8316
	global	___fladd

;; *************** function ___fladd *****************
;; Defined at:
;;		line 10 in file "C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
;; Parameters:    Size  Location     Type
;;  b               4    0[COMRAM] unsigned char 
;;  a               4    4[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  grs             1   15[COMRAM] unsigned char 
;;  bexp            1   14[COMRAM] unsigned char 
;;  aexp            1   13[COMRAM] unsigned char 
;;  signs           1   12[COMRAM] unsigned char 
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
;;      Locals:         4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          4       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        16       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       16 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;; This function uses a non-reentrant model
;;
psect	text36,class=CODE,space=0,reloc=2,group=1
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
	line	10
global __ptext36
__ptext36:
psect	text36
	file	"C:\Program Files (x86)\Flowcode\Common\Compilers\picv2\pic\sources\c90\common\sprcadd.c"
	line	10
	global	__size_of___fladd
	__size_of___fladd	equ	__end_of___fladd-___fladd
	
___fladd:
;incstack = 0
	opt	callstack 27
	line	21
	
l3971:
	movf	(0+((c:___fladd@b)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:___fladd@signs))^00h,c
	line	22
	movf	(0+((c:___fladd@b)+03h))^00h,c,w
	addwf	(0+((c:___fladd@b)+03h))^00h,c,w
	movwf	((c:___fladd@bexp))^00h,c
	line	23
	
l3973:
	
	btfss	(0+((c:___fladd@b)+02h))^00h,c,(7)&7
	goto	u2391
	goto	u2390
u2391:
	goto	l3977
u2390:
	line	24
	
l3975:
	bsf	(0+(0/8)+(c:___fladd@bexp))^00h,c,(0)&7
	line	28
	
l3977:
	movf	((c:___fladd@bexp))^00h,c,w
	btfsc	status,2
	goto	u2401
	goto	u2400
u2401:
	goto	l3987
u2400:
	line	30
	
l3979:
		incf	((c:___fladd@bexp))^00h,c,w
	btfss	status,2
	goto	u2411
	goto	u2410

u2411:
	goto	l3983
u2410:
	line	32
	
l3981:
	movlw	low(normalize32(0x0))
	movwf	((c:___fladd@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fladd@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fladd@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fladd@b+3))^00h,c
	line	35
	
l3983:
	bsf	(0+(23/8)+(c:___fladd@b))^00h,c,(23)&7
	line	37
	
l3985:
	movlw	low(0)
	movwf	(0+((c:___fladd@b)+03h))^00h,c
	line	38
	goto	l3989
	line	41
	
l3987:
	movlw	low(normalize32(0x0))
	movwf	((c:___fladd@b))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fladd@b+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fladd@b+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fladd@b+3))^00h,c
	line	44
	
l3989:
	movf	(0+((c:___fladd@a)+03h))^00h,c,w
	andlw	low(080h)
	movwf	((c:___fladd@aexp))^00h,c
	line	46
	
l3991:
	movf	((c:___fladd@signs))^00h,c,w
xorwf	((c:___fladd@aexp))^00h,c,w
	btfsc	status,2
	goto	u2421
	goto	u2420

u2421:
	goto	l3995
u2420:
	line	47
	
l3993:
	bsf	(0+(6/8)+(c:___fladd@signs))^00h,c,(6)&7
	line	49
	
l3995:
	movf	(0+((c:___fladd@a)+03h))^00h,c,w
	addwf	(0+((c:___fladd@a)+03h))^00h,c,w
	movwf	((c:___fladd@aexp))^00h,c
	line	50
	
l3997:
	
	btfss	(0+((c:___fladd@a)+02h))^00h,c,(7)&7
	goto	u2431
	goto	u2430
u2431:
	goto	l4001
u2430:
	line	51
	
l3999:
	bsf	(0+(0/8)+(c:___fladd@aexp))^00h,c,(0)&7
	line	55
	
l4001:
	movf	((c:___fladd@aexp))^00h,c,w
	btfsc	status,2
	goto	u2441
	goto	u2440
u2441:
	goto	l4011
u2440:
	line	57
	
l4003:
		incf	((c:___fladd@aexp))^00h,c,w
	btfss	status,2
	goto	u2451
	goto	u2450

u2451:
	goto	l4007
u2450:
	line	59
	
l4005:
	movlw	low(normalize32(0x0))
	movwf	((c:___fladd@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fladd@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fladd@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fladd@a+3))^00h,c
	line	62
	
l4007:
	bsf	(0+(23/8)+(c:___fladd@a))^00h,c,(23)&7
	line	64
	
l4009:
	movlw	low(0)
	movwf	(0+((c:___fladd@a)+03h))^00h,c
	line	65
	goto	l4013
	line	68
	
l4011:
	movlw	low(normalize32(0x0))
	movwf	((c:___fladd@a))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:___fladd@a+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:___fladd@a+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:___fladd@a+3))^00h,c
	line	75
	
l4013:
		movf	((c:___fladd@bexp))^00h,c,w
	subwf	((c:___fladd@aexp))^00h,c,w
	btfsc	status,0
	goto	u2461
	goto	u2460

u2461:
	goto	l4049
u2460:
	line	77
	
l4015:
	
	btfss	((c:___fladd@signs))^00h,c,(6)&7
	goto	u2471
	goto	u2470
u2471:
	goto	l4019
u2470:
	line	78
	
l4017:
	movlw	(080h)&0ffh
	xorwf	((c:___fladd@signs))^00h,c
	line	81
	
l4019:
	movff	(c:___fladd@bexp),(c:___fladd@grs)
	line	82
	
l4021:
	movff	(c:___fladd@aexp),(c:___fladd@bexp)
	line	83
	
l4023:
	movff	(c:___fladd@grs),(c:___fladd@aexp)
	line	84
	
l4025:
	movff	(c:___fladd@b),(c:___fladd@grs)
	line	85
	
l4027:
	movff	(c:___fladd@a),(c:___fladd@b)
	line	86
	
l4029:
	movff	(c:___fladd@grs),(c:___fladd@a)
	line	87
	
l4031:
	movff	0+((c:___fladd@b)+01h),(c:___fladd@grs)
	line	88
	
l4033:
	movff	0+((c:___fladd@a)+01h),0+((c:___fladd@b)+01h)
	line	89
	
l4035:
	movff	(c:___fladd@grs),0+((c:___fladd@a)+01h)
	line	90
	
l4037:
	movff	0+((c:___fladd@b)+02h),(c:___fladd@grs)
	line	91
	
l4039:
	movff	0+((c:___fladd@a)+02h),0+((c:___fladd@b)+02h)
	line	92
	
l4041:
	movff	(c:___fladd@grs),0+((c:___fladd@a)+02h)
	line	93
	
l4043:
	movff	0+((c:___fladd@b)+03h),(c:___fladd@grs)
	line	94
	
l4045:
	movff	0+((c:___fladd@a)+03h),0+((c:___fladd@b)+03h)
	line	95
	
l4047:
	movff	(c:___fladd@grs),0+((c:___fladd@a)+03h)
	line	98
	
l4049:
	movlw	low(0)
	movwf	((c:___fladd@grs))^00h,c
	line	100
	
l4051:
	movf	((c:___fladd@bexp))^00h,c,w
	movff	(c:___fladd@aexp),??___fladd+0+0
	clrf	(??___fladd+0+0+1)^00h,c
	subwf	(??___fladd+0+0)^00h,c
	movlw	0
	subwfb	(??___fladd+0+1)^00h,c
	btfsc	(??___fladd+0+1)^00h,c,7
	goto	u2481
	movf	(??___fladd+0+1)^00h,c,w
	bnz	u2480
	movlw	26
	subwf	 (??___fladd+0+0)^00h,c,w
	btfss	status,0
	goto	u2481
	goto	u2480

u2481:
	goto	l2014
u2480:
	line	101
	
l4053:
	movf	((c:___fladd@b))^00h,c,w
iorwf	((c:___fladd@b+1))^00h,c,w
iorwf	((c:___fladd@b+2))^00h,c,w
iorwf	((c:___fladd@b+3))^00h,c,w
	btfss	status,2
	goto	u2491
	goto	u2490

u2491:
	movlw	1
	goto	u2500
u2490:
	movlw	0
u2500:
	movwf	((c:___fladd@grs))^00h,c
	line	102
	
l4055:
	movlw	low(0)
	movwf	((c:___fladd@b))^00h,c
	movlw	high(0)
	movwf	((c:___fladd@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fladd@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fladd@b+3))^00h,c
	line	103
	
l4057:
	movff	(c:___fladd@aexp),(c:___fladd@bexp)
	line	104
	goto	l2013
	line	106
	
l2015:
	line	109
	
	btfss	((c:___fladd@grs))^00h,c,(0)&7
	goto	u2511
	goto	u2510
u2511:
	goto	l4061
u2510:
	line	110
	
l4059:
	bcf	status,0
	rrcf	((c:___fladd@grs))^00h,c,w
	iorlw	low(01h)
	movwf	((c:___fladd@grs))^00h,c
	line	111
	goto	l4063
	line	113
	
l4061:
	bcf status,0
	rrcf	((c:___fladd@grs))^00h,c

	line	115
	
l4063:
	
	btfss	((c:___fladd@b))^00h,c,(0)&7
	goto	u2521
	goto	u2520
u2521:
	goto	l4067
u2520:
	line	116
	
l4065:
	bsf	(0+(7/8)+(c:___fladd@grs))^00h,c,(7)&7
	line	118
	
l4067:
	rlcf	((c:___fladd@b+3))^00h,c,w
	rrcf	((c:___fladd@b+3))^00h,c
	rrcf	((c:___fladd@b+2))^00h,c
	rrcf	((c:___fladd@b+1))^00h,c
	rrcf	((c:___fladd@b))^00h,c
	line	119
	
l4069:
	incf	((c:___fladd@bexp))^00h,c
	line	120
	
l2014:
	line	106
		movf	((c:___fladd@aexp))^00h,c,w
	subwf	((c:___fladd@bexp))^00h,c,w
	btfss	status,0
	goto	u2531
	goto	u2530

u2531:
	goto	l2015
u2530:
	line	121
	
l2013:
	line	124
	
	btfsc	((c:___fladd@signs))^00h,c,(6)&7
	goto	u2541
	goto	u2540
u2541:
	goto	l4095
u2540:
	line	127
	
l4071:
	movf	((c:___fladd@bexp))^00h,c,w
	btfss	status,2
	goto	u2551
	goto	u2550
u2551:
	goto	l4077
u2550:
	line	128
	
l4073:
	movlw	low(normalize32(0x0))
	movwf	((c:?___fladd))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?___fladd+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?___fladd+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?___fladd+3))^00h,c
	goto	l2022
	line	132
	
l4077:
	movf	((c:___fladd@a))^00h,c,w
	addwf	((c:___fladd@b))^00h,c
	movf	((c:___fladd@a+1))^00h,c,w
	addwfc	((c:___fladd@b+1))^00h,c
	movf	((c:___fladd@a+2))^00h,c,w
	addwfc	((c:___fladd@b+2))^00h,c
	movf	((c:___fladd@a+3))^00h,c,w
	addwfc	((c:___fladd@b+3))^00h,c
	line	134
	
l4079:
	
	btfss	((c:___fladd@b+3))^00h,c,(24)&7
	goto	u2561
	goto	u2560
u2561:
	goto	l4131
u2560:
	line	135
	
l4081:
	
	btfss	((c:___fladd@grs))^00h,c,(0)&7
	goto	u2571
	goto	u2570
u2571:
	goto	l4085
u2570:
	line	136
	
l4083:
	bcf	status,0
	rrcf	((c:___fladd@grs))^00h,c,w
	iorlw	low(01h)
	movwf	((c:___fladd@grs))^00h,c
	line	137
	goto	l4087
	line	139
	
l4085:
	bcf status,0
	rrcf	((c:___fladd@grs))^00h,c

	line	141
	
l4087:
	
	btfss	((c:___fladd@b))^00h,c,(0)&7
	goto	u2581
	goto	u2580
u2581:
	goto	l4091
u2580:
	line	142
	
l4089:
	bsf	(0+(7/8)+(c:___fladd@grs))^00h,c,(7)&7
	line	144
	
l4091:
	rlcf	((c:___fladd@b+3))^00h,c,w
	rrcf	((c:___fladd@b+3))^00h,c
	rrcf	((c:___fladd@b+2))^00h,c
	rrcf	((c:___fladd@b+1))^00h,c
	rrcf	((c:___fladd@b))^00h,c
	line	145
	
l4093:
	incf	((c:___fladd@bexp))^00h,c
	goto	l4131
	line	153
	
l4095:
		movf	((c:___fladd@a))^00h,c,w
	subwf	((c:___fladd@b))^00h,c,w
	movf	((c:___fladd@a+1))^00h,c,w
	subwfb	((c:___fladd@b+1))^00h,c,w
	movf	((c:___fladd@a+2))^00h,c,w
	subwfb	((c:___fladd@b+2))^00h,c,w
	movf	((c:___fladd@b+3))^00h,c,w
	xorlw	80h
	movwf	(??___fladd+0+0)^00h,c
	movf	((c:___fladd@a+3))^00h,c,w
	xorlw	80h
	subwfb	(??___fladd+0+0)^00h,c,w
	btfsc	status,0
	goto	u2591
	goto	u2590

u2591:
	goto	l4105
u2590:
	line	154
	
l4097:
	movf	((c:___fladd@b))^00h,c,w
	subwf	((c:___fladd@a))^00h,c,w
	movwf	(??___fladd+0+0)^00h,c
	movf	((c:___fladd@b+1))^00h,c,w
	subwfb	((c:___fladd@a+1))^00h,c,w
	movwf	1+(??___fladd+0+0)^00h,c
	
	movf	((c:___fladd@b+2))^00h,c,w
	subwfb	((c:___fladd@a+2))^00h,c,w
	movwf	2+(??___fladd+0+0)^00h,c
	
	movf	((c:___fladd@b+3))^00h,c,w
	subwfb	((c:___fladd@a+3))^00h,c,w
	movwf	3+(??___fladd+0+0)^00h,c
	movlw	0FFh
	addwf	(??___fladd+0+0)^00h,c,w
	movwf	((c:___fladd@b))^00h,c
	movlw	0FFh
	addwfc	(??___fladd+0+1)^00h,c,w
	movwf	1+((c:___fladd@b))^00h,c
	
	movlw	0FFh
	addwfc	(??___fladd+0+2)^00h,c,w
	movwf	2+((c:___fladd@b))^00h,c
	
	movlw	0FFh
	addwfc	(??___fladd+0+3)^00h,c,w
	movwf	3+((c:___fladd@b))^00h,c
	line	155
	movlw	(080h)&0ffh
	xorwf	((c:___fladd@signs))^00h,c
	line	156
	
l4099:
	negf	((c:___fladd@grs))^00h,c
	line	157
	
l4101:
	movf	((c:___fladd@grs))^00h,c,w
	btfss	status,2
	goto	u2601
	goto	u2600
u2601:
	goto	l2030
u2600:
	line	158
	
l4103:
	movlw	low(01h)
	addwf	((c:___fladd@b))^00h,c
	movlw	0
	addwfc	((c:___fladd@b+1))^00h,c
	addwfc	((c:___fladd@b+2))^00h,c
	addwfc	((c:___fladd@b+3))^00h,c
	goto	l2030
	line	162
	
l4105:
	movf	((c:___fladd@a))^00h,c,w
	subwf	((c:___fladd@b))^00h,c
	movf	((c:___fladd@a+1))^00h,c,w
	subwfb	((c:___fladd@b+1))^00h,c
	movf	((c:___fladd@a+2))^00h,c,w
	subwfb	((c:___fladd@b+2))^00h,c
	movf	((c:___fladd@a+3))^00h,c,w
	subwfb	((c:___fladd@b+3))^00h,c
	line	163
	
l2030:
	line	166
	movf	((c:___fladd@b))^00h,c,w
iorwf	((c:___fladd@b+1))^00h,c,w
iorwf	((c:___fladd@b+2))^00h,c,w
iorwf	((c:___fladd@b+3))^00h,c,w
	btfss	status,2
	goto	u2611
	goto	u2610

u2611:
	goto	l4129
u2610:
	
l4107:
	movf	((c:___fladd@grs))^00h,c,w
	btfss	status,2
	goto	u2621
	goto	u2620
u2621:
	goto	l4129
u2620:
	line	167
	
l4109:
	movlw	low(normalize32(0x0))
	movwf	((c:?___fladd))^00h,c
	movlw	high(normalize32(0x0))
	movwf	((c:?___fladd+1))^00h,c
	movlw	low highword(normalize32(0x0))
	movwf	((c:?___fladd+2))^00h,c
	movlw	high highword(normalize32(0x0))
	movwf	((c:?___fladd+3))^00h,c
	goto	l2022
	line	172
	
l4113:
	bcf	status,0
	rlcf	((c:___fladd@b))^00h,c
	rlcf	((c:___fladd@b+1))^00h,c
	rlcf	((c:___fladd@b+2))^00h,c
	rlcf	((c:___fladd@b+3))^00h,c
	line	173
	
l4115:
	
	btfss	((c:___fladd@grs))^00h,c,(7)&7
	goto	u2631
	goto	u2630
u2631:
	goto	l4119
u2630:
	line	174
	
l4117:
	bsf	(0+(0/8)+(c:___fladd@b))^00h,c,(0)&7
	line	176
	
l4119:
	
	btfss	((c:___fladd@grs))^00h,c,(0)&7
	goto	u2641
	goto	u2640
u2641:
	goto	l4123
u2640:
	line	177
	
l4121:
	bsf	status,0
	
	rlcf	((c:___fladd@grs))^00h,c
	line	178
	goto	l4125
	line	180
	
l4123:
	bcf status,0
	rlcf	((c:___fladd@grs))^00h,c

	line	182
	
l4125:
	movf	((c:___fladd@bexp))^00h,c,w
	btfsc	status,2
	goto	u2651
	goto	u2650
u2651:
	goto	l4129
u2650:
	line	183
	
l4127:
	decf	((c:___fladd@bexp))^00h,c
	line	171
	
l4129:
	
	btfss	((c:___fladd@b+2))^00h,c,(23)&7
	goto	u2661
	goto	u2660
u2661:
	goto	l4113
u2660:
	line	192
	
l4131:
	movlw	low(0)
	movwf	((c:___fladd@aexp))^00h,c
	line	193
	
l4133:
	
	btfss	((c:___fladd@grs))^00h,c,(7)&7
	goto	u2671
	goto	u2670
u2671:
	goto	l2039
u2670:
	line	194
	
l4135:
	movff	(c:___fladd@grs),??___fladd+0+0
	movlw	07Fh
	andwf	(??___fladd+0+0)^00h,c
	btfsc	status,2
	goto	u2681
	goto	u2680
u2681:
	goto	l2040
u2680:
	line	195
	
l4137:
	movlw	low(01h)
	movwf	((c:___fladd@aexp))^00h,c
	line	196
	goto	l2039
	line	197
	
l2040:
	line	198
	
	btfss	((c:___fladd@b))^00h,c,(0)&7
	goto	u2691
	goto	u2690
u2691:
	goto	l2039
u2690:
	goto	l4137
	line	202
	
l2039:
	line	203
	movf	((c:___fladd@aexp))^00h,c,w
	btfsc	status,2
	goto	u2701
	goto	u2700
u2701:
	goto	l4149
u2700:
	line	204
	
l4141:
	movlw	low(01h)
	addwf	((c:___fladd@b))^00h,c
	movlw	0
	addwfc	((c:___fladd@b+1))^00h,c
	addwfc	((c:___fladd@b+2))^00h,c
	addwfc	((c:___fladd@b+3))^00h,c
	line	205
	
l4143:
	
	btfss	((c:___fladd@b+3))^00h,c,(24)&7
	goto	u2711
	goto	u2710
u2711:
	goto	l4149
u2710:
	line	206
	
l4145:
	movff	(c:___fladd@b),??___fladd+0+0
	movff	(c:___fladd@b+1),??___fladd+0+0+1
	movff	(c:___fladd@b+2),??___fladd+0+0+2
	movff	(c:___fladd@b+3),??___fladd+0+0+3
	rlcf	(??___fladd+0+3)^00h,c,w
	rrcf	(??___fladd+0+3)^00h,c
	rrcf	(??___fladd+0+2)^00h,c
	rrcf	(??___fladd+0+1)^00h,c
	rrcf	(??___fladd+0+0)^00h,c
	movff	??___fladd+0+0,(c:___fladd@b)
	movff	??___fladd+0+1,(c:___fladd@b+1)
	movff	??___fladd+0+2,(c:___fladd@b+2)
	movff	??___fladd+0+3,(c:___fladd@b+3)
	line	207
		incf	((c:___fladd@bexp))^00h,c,w
	btfsc	status,2
	goto	u2721
	goto	u2720

u2721:
	goto	l4149
u2720:
	line	208
	
l4147:
	incf	((c:___fladd@bexp))^00h,c
	line	215
	
l4149:
		incf	((c:___fladd@bexp))^00h,c,w
	btfsc	status,2
	goto	u2731
	goto	u2730

u2731:
	goto	l4153
u2730:
	
l4151:
	movf	((c:___fladd@bexp))^00h,c,w
	btfss	status,2
	goto	u2741
	goto	u2740
u2741:
	goto	l4157
u2740:
	line	216
	
l4153:
	movlw	low(0)
	movwf	((c:___fladd@b))^00h,c
	movlw	high(0)
	movwf	((c:___fladd@b+1))^00h,c
	movlw	low highword(0)
	movwf	((c:___fladd@b+2))^00h,c
	movlw	high highword(0)
	movwf	((c:___fladd@b+3))^00h,c
	line	218
	movf	((c:___fladd@bexp))^00h,c,w
	btfss	status,2
	goto	u2751
	goto	u2750
u2751:
	goto	l4157
u2750:
	line	219
	
l4155:
	movlw	low(0)
	movwf	((c:___fladd@signs))^00h,c
	line	225
	
l4157:
	
	btfss	((c:___fladd@bexp))^00h,c,(0)&7
	goto	u2761
	goto	u2760
u2761:
	goto	l4161
u2760:
	line	226
	
l4159:
	bsf	(0+(7/8)+0+((c:___fladd@b)+02h))^00h,c,(7)&7
	line	227
	goto	l4163
	line	230
	
l4161:
	bcf	(0+(7/8)+0+((c:___fladd@b)+02h))^00h,c,(7)&7
	line	232
	
l4163:
	bcf	status,0
	rrcf	((c:___fladd@bexp))^00h,c,w
	movwf	(0+((c:___fladd@b)+03h))^00h,c
	line	233
	
l4165:
	
	btfss	((c:___fladd@signs))^00h,c,(7)&7
	goto	u2771
	goto	u2770
u2771:
	goto	l4169
u2770:
	line	234
	
l4167:
	bsf	(0+(7/8)+0+((c:___fladd@b)+03h))^00h,c,(7)&7
	line	236
	
l4169:
	movff	(c:___fladd@b),(c:?___fladd)
	movff	(c:___fladd@b+1),(c:?___fladd+1)
	movff	(c:___fladd@b+2),(c:?___fladd+2)
	movff	(c:___fladd@b+3),(c:?___fladd+3)
	line	237
	
l2022:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of___fladd
	__end_of___fladd:
	signat	___fladd,8316
	global	_FCD_01c01_temp_hum_sensor__Sample

;; *************** function _FCD_01c01_temp_hum_sensor__Sample *****************
;; Defined at:
;;		line 4097 in file "BL0144 dig temp sensor - PIC.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  FCL_DATA        6   17[COMRAM] unsigned char [6]
;;  FCL_RETRYCOU    1   24[COMRAM] unsigned char 
;;  FCL_RET         1   23[COMRAM] unsigned char 
;;  FCR_RETVAL      1    0        unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         9       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        11       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       11 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_FC_CAL_I2C_Transaction_Read_1
;;		_FC_CAL_I2C_Transaction_Write_1
;;		_delay_ms
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__GetTemperatureReal
;;		_FCD_01c01_temp_hum_sensor__Initialise
;; This function uses a non-reentrant model
;;
psect	text37,class=CODE,space=0,reloc=2,group=0
	file	"BL0144 dig temp sensor - PIC.c"
	line	4097
global __ptext37
__ptext37:
psect	text37
	file	"BL0144 dig temp sensor - PIC.c"
	line	4097
	global	__size_of_FCD_01c01_temp_hum_sensor__Sample
	__size_of_FCD_01c01_temp_hum_sensor__Sample	equ	__end_of_FCD_01c01_temp_hum_sensor__Sample-_FCD_01c01_temp_hum_sensor__Sample
	
_FCD_01c01_temp_hum_sensor__Sample:
;incstack = 0
	opt	callstack 25
	line	4102
	
l3905:
	movlw	low(02h)
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT))^00h,c
	line	4109
	movlw	low(0)
	movwf	((c:_FCV_01c01_temp_hum_sensor__SAMPLEMASK))^00h,c	;volatile
	line	4111
	goto	l3913
	line	4116
	
l3907:
	movlw	low(0F6h)
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA))^00h,c
	line	4118
	goto	l3915
	line	4123
	
l3909:
	movlw	low(0FDh)
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA))^00h,c
	line	4125
	goto	l3915
	line	4129
	
l3911:
	movlw	low(0E0h)
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA))^00h,c
	line	4132
	goto	l3915
	line	4111
	
l3913:
	movf	((c:_FCV_01c01_temp_hum_sensor__PRECISION))^00h,c,w	;volatile
	; Switch size 1, requested type "simple"
; Number of cases is 2, Range of values is 1 to 2
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
;	Chosen strategy is simple_byte

	xorlw	1^0	; case 1
	skipnz
	goto	l3907
	xorlw	2^1	; case 2
	skipnz
	goto	l3909
	goto	l3911

	line	4134
	
l3915:
		movlw	low(FCD_01c01_temp_hum_sensor__Sample@FCL_DATA)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Buffer))^00h,c

	movlw	high(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Size+1))^00h,c
	movlw	low(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Size))^00h,c
	movlw	high(01h)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Length+1))^00h,c
	movlw	low(01h)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c
	call	_FC_CAL_I2C_Transaction_Write_1	;wreg free
	line	4136
	goto	l3937
	line	4143
	
l3917:
	movlw	(05h)&0ffh
	
	call	_delay_ms
	line	4145
	goto	l3925
	line	4150
	
l3919:
	movlw	(09h)&0ffh
	
	call	_delay_ms
	line	4152
	goto	l3925
	line	4156
	
l3921:
	movlw	(02h)&0ffh
	
	call	_delay_ms
	line	4159
	goto	l3925
	line	4138
	
l3923:
	movf	((c:_FCV_01c01_temp_hum_sensor__PRECISION))^00h,c,w	;volatile
	; Switch size 1, requested type "simple"
; Number of cases is 2, Range of values is 1 to 2
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
;	Chosen strategy is simple_byte

	xorlw	1^0	; case 1
	skipnz
	goto	l3917
	xorlw	2^1	; case 2
	skipnz
	goto	l3919
	goto	l3921

	line	4161
	
l3925:
		movlw	low(FCD_01c01_temp_hum_sensor__Sample@FCL_DATA)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@Buffer))^00h,c

	movlw	high(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@Size+1))^00h,c
	movlw	low(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@Size))^00h,c
	movlw	high(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@Length+1))^00h,c
	movlw	low(06h)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@Length))^00h,c
	call	_FC_CAL_I2C_Transaction_Read_1	;wreg free
	movf	(0+?_FC_CAL_I2C_Transaction_Read_1)^00h,c,w
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RET))^00h,c
	line	4163
	
l3927:
		movlw	6
	xorwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RET))^00h,c,w
	btfss	status,2
	goto	u2321
	goto	u2320

u2321:
	goto	l3935
u2320:
	line	4166
	
l3929:
	movf	(0+((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA)+01h))^00h,c,w
	movff	(c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA),??_FCD_01c01_temp_hum_sensor__Sample+0+0
	clrf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0+1)^00h,c
	movff	??_FCD_01c01_temp_hum_sensor__Sample+0+0,??_FCD_01c01_temp_hum_sensor__Sample+0+1
	clrf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0)^00h,c
	iorwf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0)^00h,c,w
	movwf	((c:_FCV_01c01_temp_hum_sensor__TEMP))^00h,c	;volatile
	movf	(??_FCD_01c01_temp_hum_sensor__Sample+0+1)^00h,c,w
	movwf	1+((c:_FCV_01c01_temp_hum_sensor__TEMP))^00h,c	;volatile
	line	4167
	movf	(0+((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA)+04h))^00h,c,w
	movff	0+((c:FCD_01c01_temp_hum_sensor__Sample@FCL_DATA)+03h),??_FCD_01c01_temp_hum_sensor__Sample+0+0
	clrf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0+1)^00h,c
	movff	??_FCD_01c01_temp_hum_sensor__Sample+0+0,??_FCD_01c01_temp_hum_sensor__Sample+0+1
	clrf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0)^00h,c
	iorwf	(??_FCD_01c01_temp_hum_sensor__Sample+0+0)^00h,c,w
	movwf	((c:_FCV_01c01_temp_hum_sensor__HUM))^00h,c	;volatile
	movf	(??_FCD_01c01_temp_hum_sensor__Sample+0+1)^00h,c,w
	movwf	1+((c:_FCV_01c01_temp_hum_sensor__HUM))^00h,c	;volatile
	line	4169
	
l3931:
	line	4171
	
l3933:
	movlw	low(0)
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT))^00h,c
	line	4173
	goto	l3937
	line	4175
	
l3935:
	decf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT))^00h,c,w
	movwf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT))^00h,c
	line	4136
	
l3937:
	movf	((c:FCD_01c01_temp_hum_sensor__Sample@FCL_RETRYCOUNT))^00h,c,w
	btfss	status,2
	goto	u2331
	goto	u2330
u2331:
	goto	l3923
u2330:
	line	4185
	
l1451:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FCD_01c01_temp_hum_sensor__Sample
	__end_of_FCD_01c01_temp_hum_sensor__Sample:
	signat	_FCD_01c01_temp_hum_sensor__Sample,89
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
;;		_delay_s
;;		_FCD_01c01_temp_hum_sensor__Sample
;;		_main
;; This function uses a non-reentrant model
;;
psect	text38,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
global __ptext38
__ptext38:
psect	text38
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	105
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:
;incstack = 0
	opt	callstack 29
	movwf	((c:delay_ms@del))^00h,c
	line	107
	
l2557:
	goto	l2561
	line	109
	
l2559:
	opt asmopt_push
opt asmopt_off
movlw	21
movwf	(??_delay_ms+0+0)^00h,c,f
	movlw	198
u3497:
decfsz	wreg,f
	bra	u3497
	decfsz	(??_delay_ms+0+0)^00h,c,f
	bra	u3497
	nop2
opt asmopt_pop

	line	107
	
l2561:
	decf	((c:delay_ms@del))^00h,c
		incf	((c:delay_ms@del))^00h,c,w
	btfss	status,2
	goto	u391
	goto	u390

u391:
	goto	l2559
u390:
	line	111
	
l112:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4217
	global	_FC_CAL_I2C_Transaction_Write_1

;; *************** function _FC_CAL_I2C_Transaction_Write_1 *****************
;; Defined at:
;;		line 1077 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;  Buffer          1    4[COMRAM] PTR unsigned char 
;;		 -> FCD_01c01_temp_hum_sensor__Sample@FCL_DATA(6), 
;;  Size            2    5[COMRAM] unsigned short 
;;  Length          2    7[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  n               2   12[COMRAM] unsigned short 
;;  fail            2    0        unsigned short 
;;  sendStop        1   11[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    4[COMRAM] unsigned short 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        10       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FC_CAL_I2C_Master_Start_1
;;		_FC_CAL_I2C_Master_Stop_1
;;		_FC_CAL_I2C_Master_TxByte_1
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__Sample
;; This function uses a non-reentrant model
;;
psect	text39,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	1077
global __ptext39
__ptext39:
psect	text39
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	1077
	global	__size_of_FC_CAL_I2C_Transaction_Write_1
	__size_of_FC_CAL_I2C_Transaction_Write_1	equ	__end_of_FC_CAL_I2C_Transaction_Write_1-_FC_CAL_I2C_Transaction_Write_1
	
_FC_CAL_I2C_Transaction_Write_1:
;incstack = 0
	opt	callstack 25
	line	1079
	
l3781:
	movlw	low(01h)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@sendStop))^00h,c
	line	1081
	
l3783:
	
	btfss	((c:FC_CAL_I2C_Transaction_Write_1@Length+1))^00h,c,(15)&7
	goto	u2161
	goto	u2160
u2161:
	goto	l3789
u2160:
	line	1083
	
l3785:
	movlw	0FFh
	andwf	((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c,w
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c
	movlw	07Fh
	andwf	((c:FC_CAL_I2C_Transaction_Write_1@Length+1))^00h,c,w
	movwf	1+((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c
	line	1084
	
l3787:
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@sendStop))^00h,c
	line	1086
	
l3789:
		movf	((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c,w
	subwf	((c:FC_CAL_I2C_Transaction_Write_1@Size))^00h,c,w
	movf	((c:FC_CAL_I2C_Transaction_Write_1@Length+1))^00h,c,w
	subwfb	((c:FC_CAL_I2C_Transaction_Write_1@Size+1))^00h,c,w
	btfsc	status,0
	goto	u2171
	goto	u2170

u2171:
	goto	l3793
u2170:
	goto	l786
	line	1112
	
l3793:
	movlw	high(0)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@n+1))^00h,c
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Transaction_Write_1@n))^00h,c
	line	1113
	
l3795:
	call	_FC_CAL_I2C_Master_Start_1	;wreg free
	line	1122
	
l3797:
	movf	((c:_MX_I2C_ADDRESS_1))^00h,c,w
	addwf	((c:_MX_I2C_ADDRESS_1))^00h,c,w
	
	call	_FC_CAL_I2C_Master_TxByte_1
	iorlw	0
	btfsc	status,2
	goto	u2181
	goto	u2180
u2181:
	goto	l3807
u2180:
	goto	l786
	line	1128
	
l3801:
	movf	((c:FC_CAL_I2C_Transaction_Write_1@Buffer))^00h,c,w
	addwf	((c:FC_CAL_I2C_Transaction_Write_1@n))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	
	call	_FC_CAL_I2C_Master_TxByte_1
	iorlw	0
	btfsc	status,2
	goto	u2191
	goto	u2190
u2191:
	goto	l3805
u2190:
	line	1129
	
l3803:
	line	1130
	
l3805:
	infsnz	((c:FC_CAL_I2C_Transaction_Write_1@n))^00h,c
	incf	((c:FC_CAL_I2C_Transaction_Write_1@n+1))^00h,c
	line	1126
	
l3807:
		movf	((c:FC_CAL_I2C_Transaction_Write_1@Length))^00h,c,w
	subwf	((c:FC_CAL_I2C_Transaction_Write_1@n))^00h,c,w
	movf	((c:FC_CAL_I2C_Transaction_Write_1@Length+1))^00h,c,w
	subwfb	((c:FC_CAL_I2C_Transaction_Write_1@n+1))^00h,c,w
	btfss	status,0
	goto	u2201
	goto	u2200

u2201:
	goto	l3801
u2200:
	line	1133
	
l3809:
	movf	((c:FC_CAL_I2C_Transaction_Write_1@sendStop))^00h,c,w
	btfsc	status,2
	goto	u2211
	goto	u2210
u2211:
	goto	l3813
u2210:
	line	1134
	
l3811:
	call	_FC_CAL_I2C_Master_Stop_1	;wreg free
	goto	l786
	line	1156
	
l3813:
	line	1160
	
l786:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Transaction_Write_1
	__end_of_FC_CAL_I2C_Transaction_Write_1:
	signat	_FC_CAL_I2C_Transaction_Write_1,12410
	global	_FC_CAL_I2C_Transaction_Read_1

;; *************** function _FC_CAL_I2C_Transaction_Read_1 *****************
;; Defined at:
;;		line 1012 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;  Buffer          1    4[COMRAM] PTR unsigned char 
;;		 -> FCD_01c01_temp_hum_sensor__Sample@FCL_DATA(6), 
;;  Size            2    5[COMRAM] unsigned short 
;;  Length          2    7[COMRAM] unsigned short 
;; Auto vars:     Size  Location     Type
;;  n               2   12[COMRAM] unsigned short 
;;  fail            1   11[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    4[COMRAM] unsigned short 
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         5       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          2       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:        10       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:       10 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_FC_CAL_I2C_Master_RxByte_1
;;		_FC_CAL_I2C_Master_Start_1
;;		_FC_CAL_I2C_Master_Stop_1
;;		_FC_CAL_I2C_Master_TxByte_1
;; This function is called by:
;;		_FCD_01c01_temp_hum_sensor__Sample
;; This function uses a non-reentrant model
;;
psect	text40,class=CODE,space=0,reloc=2,group=0
	line	1012
global __ptext40
__ptext40:
psect	text40
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	1012
	global	__size_of_FC_CAL_I2C_Transaction_Read_1
	__size_of_FC_CAL_I2C_Transaction_Read_1	equ	__end_of_FC_CAL_I2C_Transaction_Read_1-_FC_CAL_I2C_Transaction_Read_1
	
_FC_CAL_I2C_Transaction_Read_1:
;incstack = 0
	opt	callstack 25
	line	1014
	
l3749:
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@fail))^00h,c
	line	1016
	
l3751:
		movf	((c:FC_CAL_I2C_Transaction_Read_1@Length))^00h,c,w
	subwf	((c:FC_CAL_I2C_Transaction_Read_1@Size))^00h,c,w
	movf	((c:FC_CAL_I2C_Transaction_Read_1@Length+1))^00h,c,w
	subwfb	((c:FC_CAL_I2C_Transaction_Read_1@Size+1))^00h,c,w
	btfsc	status,0
	goto	u2101
	goto	u2100

u2101:
	goto	l3757
u2100:
	
l3753:
	movlw	high(0)
	movwf	((c:?_FC_CAL_I2C_Transaction_Read_1+1))^00h,c
	movlw	low(0)
	movwf	((c:?_FC_CAL_I2C_Transaction_Read_1))^00h,c
	goto	l776
	line	1036
	
l3757:
	movlw	high(0)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@n+1))^00h,c
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Transaction_Read_1@n))^00h,c
	line	1037
	
l3759:
	call	_FC_CAL_I2C_Master_Start_1	;wreg free
	line	1058
	
l3761:
	bsf	status,0
	
	rlcf	((c:_MX_I2C_ADDRESS_1))^00h,c,w
	
	call	_FC_CAL_I2C_Master_TxByte_1
	iorlw	0
	btfsc	status,2
	goto	u2111
	goto	u2110
u2111:
	goto	l3771
u2110:
	goto	l3753
	line	1064
	
l3767:
	movf	((c:FC_CAL_I2C_Transaction_Read_1@Buffer))^00h,c,w
	addwf	((c:FC_CAL_I2C_Transaction_Read_1@n))^00h,c,w
	movwf	fsr2l
	clrf	fsr2h
	movlw	01h
	addwf	((c:FC_CAL_I2C_Transaction_Read_1@n))^00h,c,w
	movwf	(??_FC_CAL_I2C_Transaction_Read_1+0+0)^00h,c
	movlw	0
	addwfc	((c:FC_CAL_I2C_Transaction_Read_1@n+1))^00h,c,w
	movwf	(??_FC_CAL_I2C_Transaction_Read_1+0+0+1)^00h,c
	movf	((c:FC_CAL_I2C_Transaction_Read_1@Length))^00h,c,w
xorwf	(??_FC_CAL_I2C_Transaction_Read_1+0+0)^00h,c,w
	bnz	u2120
movf	((c:FC_CAL_I2C_Transaction_Read_1@Length+1))^00h,c,w
xorwf	(??_FC_CAL_I2C_Transaction_Read_1+0+1)^00h,c,w
	btfsc	status,2
	goto	u2121
	goto	u2120

u2121:
	movlw	1
	goto	u2130
u2120:
	movlw	0
u2130:
	
	call	_FC_CAL_I2C_Master_RxByte_1
	movwf	indf2,c

	line	1065
	
l3769:
	infsnz	((c:FC_CAL_I2C_Transaction_Read_1@n))^00h,c
	incf	((c:FC_CAL_I2C_Transaction_Read_1@n+1))^00h,c
	line	1062
	
l3771:
		movf	((c:FC_CAL_I2C_Transaction_Read_1@Length))^00h,c,w
	subwf	((c:FC_CAL_I2C_Transaction_Read_1@n))^00h,c,w
	movf	((c:FC_CAL_I2C_Transaction_Read_1@Length+1))^00h,c,w
	subwfb	((c:FC_CAL_I2C_Transaction_Read_1@n+1))^00h,c,w
	btfss	status,0
	goto	u2141
	goto	u2140

u2141:
	goto	l3767
u2140:
	line	1068
	
l3773:
	call	_FC_CAL_I2C_Master_Stop_1	;wreg free
	line	1070
	
l3775:
	movf	((c:FC_CAL_I2C_Transaction_Read_1@fail))^00h,c,w
	btfsc	status,2
	goto	u2151
	goto	u2150
u2151:
	goto	l781
u2150:
	goto	l3753
	line	1071
	
l781:
	line	1073
	movff	(c:FC_CAL_I2C_Transaction_Read_1@n),(c:?_FC_CAL_I2C_Transaction_Read_1)
	movff	(c:FC_CAL_I2C_Transaction_Read_1@n+1),(c:?_FC_CAL_I2C_Transaction_Read_1+1)
	line	1074
	
l776:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Transaction_Read_1
	__end_of_FC_CAL_I2C_Transaction_Read_1:
	signat	_FC_CAL_I2C_Transaction_Read_1,12410
	global	_FC_CAL_I2C_Master_TxByte_1

;; *************** function _FC_CAL_I2C_Master_TxByte_1 *****************
;; Defined at:
;;		line 599 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;  Data            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Data            1    1[COMRAM] unsigned char 
;;  bit_mask        1    3[COMRAM] unsigned char 
;;  local_ack       1    2[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay_us
;; This function is called by:
;;		_FC_CAL_I2C_Transaction_Read_1
;;		_FC_CAL_I2C_Transaction_Write_1
;; This function uses a non-reentrant model
;;
psect	text41,class=CODE,space=0,reloc=2,group=0
	line	599
global __ptext41
__ptext41:
psect	text41
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	599
	global	__size_of_FC_CAL_I2C_Master_TxByte_1
	__size_of_FC_CAL_I2C_Master_TxByte_1	equ	__end_of_FC_CAL_I2C_Master_TxByte_1-_FC_CAL_I2C_Master_TxByte_1
	
_FC_CAL_I2C_Master_TxByte_1:
;incstack = 0
	opt	callstack 25
	movwf	((c:FC_CAL_I2C_Master_TxByte_1@Data))^00h,c
	line	603
	
l2347:
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Master_TxByte_1@local_ack))^00h,c
	line	604
	movlw	low(080h)
	movwf	((c:FC_CAL_I2C_Master_TxByte_1@bit_mask))^00h,c
	goto	l2365
	line	606
	
l2349:
	movf	((c:FC_CAL_I2C_Master_TxByte_1@Data))^00h,c,w
	andwf	((c:FC_CAL_I2C_Master_TxByte_1@bit_mask))^00h,c,w
	iorlw	0
	btfsc	status,2
	goto	u111
	goto	u110
u111:
	goto	l2353
u110:
	line	608
	
l2351:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	609
	goto	l2355
	line	612
	
l2353:
	bcf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	bcf	(0+(4/8)+(c:3979))^0f00h,c,(4)&7	;volatile
	line	614
	
l2355:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	615
	
l2357:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	616
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	623
	
l2359:
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	
l2361:
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	604
	
l2363:
	bcf	status,0
	rrcf	((c:FC_CAL_I2C_Master_TxByte_1@bit_mask))^00h,c,w
	movwf	((c:FC_CAL_I2C_Master_TxByte_1@bit_mask))^00h,c
	
l2365:
	movf	((c:FC_CAL_I2C_Master_TxByte_1@bit_mask))^00h,c,w
	btfss	status,2
	goto	u121
	goto	u120
u121:
	goto	l2349
u120:
	line	626
	
l2367:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	627
	
l2369:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	628
	
l2371:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	629
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	630
	
l2373:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	631
	
l2375:
	
	btfss	((c:3979))^0f00h,c,(4)&7	;volatile
	goto	u131
	goto	u130
u131:
	goto	l2379
u130:
	line	632
	
l2377:
	movlw	low(01h)
	movwf	((c:FC_CAL_I2C_Master_TxByte_1@local_ack))^00h,c
	line	634
	
l2379:
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	
l2381:
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	636
	movf	((c:FC_CAL_I2C_Master_TxByte_1@local_ack))^00h,c,w
	line	684
	
l740:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Master_TxByte_1
	__end_of_FC_CAL_I2C_Master_TxByte_1:
	signat	_FC_CAL_I2C_Master_TxByte_1,4217
	global	_FC_CAL_I2C_Master_Stop_1

;; *************** function _FC_CAL_I2C_Master_Stop_1 *****************
;; Defined at:
;;		line 550 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
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
;;		_delay_us
;; This function is called by:
;;		_FC_CAL_I2C_Transaction_Read_1
;;		_FC_CAL_I2C_Transaction_Write_1
;; This function uses a non-reentrant model
;;
psect	text42,class=CODE,space=0,reloc=2,group=0
	line	550
global __ptext42
__ptext42:
psect	text42
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	550
	global	__size_of_FC_CAL_I2C_Master_Stop_1
	__size_of_FC_CAL_I2C_Master_Stop_1	equ	__end_of_FC_CAL_I2C_Master_Stop_1-_FC_CAL_I2C_Master_Stop_1
	
_FC_CAL_I2C_Master_Stop_1:
;incstack = 0
	opt	callstack 25
	line	553
	
l2339:
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	554
	bcf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	bcf	(0+(4/8)+(c:3979))^0f00h,c,(4)&7	;volatile
	line	555
	
l2341:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	556
	
l2343:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	557
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	558
	
l2345:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	596
	
l731:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Master_Stop_1
	__end_of_FC_CAL_I2C_Master_Stop_1:
	signat	_FC_CAL_I2C_Master_Stop_1,89
	global	_FC_CAL_I2C_Master_Start_1

;; *************** function _FC_CAL_I2C_Master_Start_1 *****************
;; Defined at:
;;		line 444 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      void 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
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
;;		_delay_us
;; This function is called by:
;;		_FC_CAL_I2C_Transaction_Read_1
;;		_FC_CAL_I2C_Transaction_Write_1
;; This function uses a non-reentrant model
;;
psect	text43,class=CODE,space=0,reloc=2,group=0
	line	444
global __ptext43
__ptext43:
psect	text43
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	444
	global	__size_of_FC_CAL_I2C_Master_Start_1
	__size_of_FC_CAL_I2C_Master_Start_1	equ	__end_of_FC_CAL_I2C_Master_Start_1-_FC_CAL_I2C_Master_Start_1
	
_FC_CAL_I2C_Master_Start_1:
;incstack = 0
	opt	callstack 25
	line	448
	
l2329:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	449
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	450
	
l2331:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	451
	
l2333:
	bcf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	
l2335:
	bcf	(0+(4/8)+(c:3979))^0f00h,c,(4)&7	;volatile
	line	452
	
l2337:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	453
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	496
	
l725:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Master_Start_1
	__end_of_FC_CAL_I2C_Master_Start_1:
	signat	_FC_CAL_I2C_Master_Start_1,89
	global	_FC_CAL_I2C_Master_RxByte_1

;; *************** function _FC_CAL_I2C_Master_RxByte_1 *****************
;; Defined at:
;;		line 687 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
;; Parameters:    Size  Location     Type
;;  Last            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Last            1    1[COMRAM] unsigned char 
;;  bit_mask        1    3[COMRAM] unsigned char 
;;  Data            1    2[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/E
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7   BANK8   BANK9  BANK10  BANK11  BANK12  BANK13
;;      Params:         0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         3       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_delay_us
;; This function is called by:
;;		_FC_CAL_I2C_Transaction_Read_1
;; This function uses a non-reentrant model
;;
psect	text44,class=CODE,space=0,reloc=2,group=0
	line	687
global __ptext44
__ptext44:
psect	text44
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_I2C.c"
	line	687
	global	__size_of_FC_CAL_I2C_Master_RxByte_1
	__size_of_FC_CAL_I2C_Master_RxByte_1	equ	__end_of_FC_CAL_I2C_Master_RxByte_1-_FC_CAL_I2C_Master_RxByte_1
	
_FC_CAL_I2C_Master_RxByte_1:
;incstack = 0
	opt	callstack 25
	movwf	((c:FC_CAL_I2C_Master_RxByte_1@Last))^00h,c
	line	691
	
l2385:
	movlw	low(0)
	movwf	((c:FC_CAL_I2C_Master_RxByte_1@Data))^00h,c
	line	692
	
l2387:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	693
	
l2389:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	694
	
l2391:
	movlw	low(080h)
	movwf	((c:FC_CAL_I2C_Master_RxByte_1@bit_mask))^00h,c
	goto	l2411
	line	696
	
l2393:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	697
	
l2395:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	704
	
l2397:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	705
	
l2399:
	
	btfss	((c:3979))^0f00h,c,(4)&7	;volatile
	goto	u141
	goto	u140
u141:
	goto	l2403
u140:
	line	706
	
l2401:
	movf	((c:FC_CAL_I2C_Master_RxByte_1@Data))^00h,c,w
	iorwf	((c:FC_CAL_I2C_Master_RxByte_1@bit_mask))^00h,c,w
	movwf	((c:FC_CAL_I2C_Master_RxByte_1@Data))^00h,c
	line	707
	
l2403:
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	
l2405:
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	708
	
l2407:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	694
	
l2409:
	bcf	status,0
	rrcf	((c:FC_CAL_I2C_Master_RxByte_1@bit_mask))^00h,c,w
	movwf	((c:FC_CAL_I2C_Master_RxByte_1@bit_mask))^00h,c
	
l2411:
	movf	((c:FC_CAL_I2C_Master_RxByte_1@bit_mask))^00h,c,w
	btfss	status,2
	goto	u151
	goto	u150
u151:
	goto	l2393
u150:
	line	710
	
l2413:
	movf	((c:FC_CAL_I2C_Master_RxByte_1@Last))^00h,c,w
	btfsc	status,2
	goto	u161
	goto	u160
u161:
	goto	l2417
u160:
	line	712
	
l2415:
	bsf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	line	713
	goto	l2419
	line	716
	
l2417:
	bcf	(0+(4/8)+(c:3971))^0f00h,c,(4)&7	;volatile
	bcf	(0+(4/8)+(c:3979))^0f00h,c,(4)&7	;volatile
	line	718
	
l2419:
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	719
	
l2421:
	bsf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	line	720
	movlw	(04h)&0ffh
	
	call	_delay_us
	line	721
	
l2423:
	bcf	(0+(5/8)+(c:3971))^0f00h,c,(5)&7	;volatile
	
l2425:
	bcf	(0+(5/8)+(c:3979))^0f00h,c,(5)&7	;volatile
	line	723
	
l2427:
	movf	((c:FC_CAL_I2C_Master_RxByte_1@Data))^00h,c,w
	line	773
	
l749:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_FC_CAL_I2C_Master_RxByte_1
	__end_of_FC_CAL_I2C_Master_RxByte_1:
	signat	_FC_CAL_I2C_Master_RxByte_1,4217
	global	_delay_us

;; *************** function _delay_us *****************
;; Defined at:
;;		line 85 in file "C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
;; Parameters:    Size  Location     Type
;;  del             1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  del             1    0[COMRAM] unsigned char 
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
;;      Temps:          0       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;      Totals:         1       0       0       0       0       0       0       0       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_FC_CAL_I2C_Master_Start_1
;;		_FC_CAL_I2C_Master_Stop_1
;;		_FC_CAL_I2C_Master_TxByte_1
;;		_FC_CAL_I2C_Master_RxByte_1
;; This function uses a non-reentrant model
;;
psect	text45,class=CODE,space=0,reloc=2,group=0
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	85
global __ptext45
__ptext45:
psect	text45
	file	"C:\ProgramData\MatrixTSL\FlowcodeV11\CAL\PIC\PIC_CAL_Delay.c"
	line	85
	global	__size_of_delay_us
	__size_of_delay_us	equ	__end_of_delay_us-_delay_us
	
_delay_us:
;incstack = 0
	opt	callstack 25
	movwf	((c:delay_us@del))^00h,c
	line	87
	
l2269:
	goto	l2275
	line	89
	
l2271:
	opt asmopt_push
opt asmopt_off
	movlw	228
u3507:
	nop2
	nop2
decfsz	wreg,f
	bra	u3507
	nop2
	nop2
opt asmopt_pop

	line	90
	
l2273:
	movlw	(064h)&0ffh
	subwf	((c:delay_us@del))^00h,c
	line	87
	
l2275:
		movlw	064h-0
	cpfslt	((c:delay_us@del))^00h,c
	goto	u11
	goto	u10

u11:
	goto	l2271
u10:
	goto	l2281
	line	94
	
l2277:
	opt asmopt_push
opt asmopt_off
	movlw	53
u3517:
decfsz	wreg,f
	bra	u3517
	nop
opt asmopt_pop

	line	95
	
l2279:
	movlw	(0Ah)&0ffh
	subwf	((c:delay_us@del))^00h,c
	line	92
	
l2281:
		movlw	0Ah-0
	cpfslt	((c:delay_us@del))^00h,c
	goto	u21
	goto	u20

u21:
	goto	l2277
u20:
	goto	l2285
	line	99
	
l2283:
	opt asmopt_push
opt asmopt_off
	movlw	5
u3527:
decfsz	wreg,f
	bra	u3527
	nop
opt asmopt_pop

	line	97
	
l2285:
	decf	((c:delay_us@del))^00h,c
		incf	((c:delay_us@del))^00h,c,w
	btfss	status,2
	goto	u31
	goto	u30

u31:
	goto	l2283
u30:
	line	101
	
l106:
	return	;funcret
	opt callstack 0
GLOBAL	__end_of_delay_us
	__end_of_delay_us:
	signat	_delay_us,4217
	global	_myisr

;; *************** function _myisr *****************
;; Defined at:
;;		line 4367 in file "BL0144 dig temp sensor - PIC.c"
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
	file	"BL0144 dig temp sensor - PIC.as"
	line	#
global __pintcode
__pintcode:
psect	intcode
	file	"BL0144 dig temp sensor - PIC.c"
	line	4367
	global	__size_of_myisr
	__size_of_myisr	equ	__end_of_myisr-_myisr
	
_myisr:
;incstack = 0
	opt	callstack 24
	bsf int$flags,1,c ;set compiler interrupt flag (level 2)
	line	4373
	
i2l1494:
	bcf int$flags,1,c ;clear compiler interrupt flag (level 2)
	retfie f
	opt callstack 0
GLOBAL	__end_of_myisr
	__end_of_myisr:
	signat	_myisr,89
psect	mediumconst
	db 0	; dummy byte at the end
	global	__mediumconst
	GLOBAL	__activetblptr
__activetblptr	EQU	3
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
