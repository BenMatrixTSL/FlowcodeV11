REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D726ED08CAC9C52A7823C831C573D3B64BF6A4CCB7873802B223E4F4A1008A35919A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5FE4940227964E7FEE666E1D7FAC06B8A690D4A7B26E28F74510A1BCB8FEAF9B752EE38B2A0684242C8B1B829CA8C87ECFF9B52C86BC69B19C96BE9F1B8E9E94DAB0B66DE4A3E8048380BEF53650D4771C81A47787168F9882C3050DA273BE4EE3B4EB97306FF2F2DC8A22FC8A912E036A3019BA83595B4AE79849CDE32E3BB2BC44AB45AA6BFFC2C
REM REVISION: 1.0
REM GUID: A9A6F728-8090-499B-9ABD-20AE2511766C
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_jtagice3.bat
@SET Programmer=jtag3isp
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
@SET AVRDUDEcmd="%~dp0..\bin\avrdude.exe" -p %2 -P %DUDEPort% -c %Programmer% -U flash:w:%5
@SHIFT
@GOTO Send


:Config
@SET AVRDUDEcmd="%~dp0..\bin\avrdude.exe" -p %2 -P %DUDEPort% -c %Programmer% -u

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
