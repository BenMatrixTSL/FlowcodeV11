REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D7ADA81469D82675ABD73A2DC3969D1D219A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5FA7E327E37BF19DD12B8C59A5712261405A96CEC75238CAD0BD632FBC18DB6313D7B0ABBC9744472ADA131ED6BF44D7498963012D0054281431980367D0F326BAD5349234DB340BF4E2BCB557FB1BABF1AD4D56F2E68ABA22C3050DA273BE4EEDAEB8AF057BC6A1AB66C00666BB3818690F2D656EE0F325679849CDE32E3BB2BC44AB45AA6BFFC2C
REM REVISION: 1.0
REM GUID: CAB14D8E-7CFE-4771-832A-6D09E915ED48
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_asp.bat
@SET Programmer=usbasp
@SET DUDEPort=usb

@SET STKPort=USB
@SET STKPath="C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"


@REM Select programmer utility
@IF "%1" == "STK500" GOTO STKprog


@REM -------------- AVRDUDE programmer --------------

@SET Fuse1=
@SET Fuse2=
@SET Fuse3=


@REM %6 is the flag to send fuse data instead of the program
@IF "%6"=="1" GOTO Config


:ProgFlash
@SET AVRDUDEcmd="%~dp0..\AVRDUDEusb\avrdude.exe" -p %2 -P %DUDEPort% -c %Programmer% -U flash:w:%5
@SHIFT
@GOTO Send


:Config
@SET AVRDUDEcmd="%~dp0..\AVRDUDEusb\avrdude.exe" -p %2 -P %DUDEPort% -c %Programmer% -u

@REM %7 is the number of fuses present
@IF "%7"=="1" GOTO ConfigOneFuse


:ConfigThreeFuses
@IF NOT "%8"=="-1" SET Fuse1=-U hfuse:w:%8:m
@IF NOT "%9"=="-1" SET Fuse2=-U lfuse:w:%9:m
@SHIFT
@IF NOT "%9"=="-1" SET Fuse3=-U efuse:w:%9:m
@GOTO Send


:ConfigOneFuse
@IF NOT "%8"=="-1" SET Fuse1=-U fuse:w:%8:m
@SHIFT
@GOTO Send


:Send
@REM Now add any additional command line parameters here
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
%AVRDUDEcmd% %Fuse1% %Fuse2% %Fuse3% %0 %1  %2  %3  %4  %5  %6  %7  %8  %9
@IF %ERRORLEVEL% NEQ 0 GOTO DUDEError
@GOTO End


:DUDEError
@ECHO.
@ECHO Error returned from [avrdude]
@EXIT %ERRORLEVEL%


:STKprog
@REM -------------- STK500 programmer --------------

@SET STK500cmd=%STKPath% -c%STKPort% -d%3 -e -if%4 -pf -vf
%STK500cmd%

@IF %ERRORLEVEL% NEQ 0 GOTO STKError
@GOTO End

:STKError
@ECHO.
@ECHO Error returned from [stk500]
@EXIT %ERRORLEVEL%

:End
@ECHO.
@ECHO Programming successful!
@EXIT 0
