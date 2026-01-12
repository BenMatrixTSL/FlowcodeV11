REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D7FDF450211C1C7EDD1B26E7E6900D01A705C640EF477B79E0C7881D2E5EEC9BD69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5AF8E843CE3F948F4E0D15CD60797BAFA6962DD75A0CE6BA803FA2A1D6AFD58EB6990D2583E913FCAAF7E7C43797B5D527BDC5AFE4E85741283CDFFC92B31C37CC7ED0FE65232B94A6FFAB882ACBAA5EE69F01B3F3C0F45102C3050DA273BE4EEEB8F083C1249885E4EF3472126DCC4557F475420AD3A302861112B2378F6127E5D3A7ED706D09BBA
REM REVISION: 1.0
REM GUID: A9214695-C8E9-4EAE-A1FD-7E32BFDC5003
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_usbtiny.bat
@REM params = "$(compileravr)" AVRDUDE $(chipalt) $(chip:l) "$(outdir)$(target).hex" "$(target).hex" 0 $(cfgb) $(cfg0) $(cfg1) $(cfg2) $(cfg3)
@SET MX_COMPILER=%~1
@SET MX_PROGRAMMER=%2
@SET MX_CHIPALT=%3
@SET MX_CHIP=%4
@SET MX_HEXFILEPATH=%~dp5
@SET MX_HEXFILE=%6
@SET MX_FUSE=%7
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SHIFT
@SET Programmer=usbtiny
@SET DUDEPort=usb

@SET STKPort=USB
@SET STKPath="C:\Program Files\Atmel\AVR Tools\STK500\Stk500.exe"

@REM PUSHD %MX_HEXFILEPATH%

@REM Select programmer utility
@IF "%MX_PROGRAMMER%" == "STK500" GOTO STKprog


@REM -------------- AVRDUDE programmer --------------

@SET Fuse1=
@SET Fuse2=
@SET Fuse3=


@REM %6 is the flag to send fuse data instead of the program
@IF "%MX_FUSE%"=="1" GOTO Config


:ProgFlash
@SET AVRDUDEcmd="%MX_COMPILER%bin\avrdude.exe" -p %MX_CHIPALT% -P%DUDEPort% -c %Programmer% -U flash:w:%MX_HEXFILE%
@GOTO Send


:Config
@SET AVRDUDEcmd="%MX_COMPILER%bin\avrdude.exe" -p %MX_CHIPALT% -P%DUDEPort% -c %Programmer% -u

@REM %8 is the number of fuses present
@IF "%1"=="1" GOTO ConfigOneFuse

:ConfigThreeFuses
@IF NOT "%2"=="-1" SET Fuse1=-U hfuse:w:%2:m
@IF NOT "%3"=="-1" SET Fuse2=-U lfuse:w:%3:m
@IF NOT "%1"=="3" GOTO Send
@IF NOT "%4"=="-1" SET Fuse3=-U efuse:w:%4:m
@GOTO Send

:ConfigOneFuse
@IF NOT "%2"=="-1" SET Fuse1=-U fuse:w:%2:m
@GOTO Send


:Send
@REM Now add any additional command line parameters here
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

@SET STK500cmd=%STKPath% -c%STKPort% -d%MX_CHIP% -e -if%MX_HEXFILE% -pf -vf
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
