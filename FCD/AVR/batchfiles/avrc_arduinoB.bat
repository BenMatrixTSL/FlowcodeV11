REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D79B7332D7455FC12D75A8268EAA28F070F6A4CCB7873802B223E4F4A1008A35919A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF51EB2672309F38B5BC562FCC8E801D34E93AC09C2DF3FF9CFA1C49DFB795D4181815DC88F96A50A238E0C4F48DEC430F3F09E4231F1B2C67DEC5EE0FB715C5DEC1E3E13575D5C99951E93D9EE0D2D0D01E24CC4F36E72E45E2C3050DA273BE4EE525EEC0800A860A656116A2EFD2D48328B23C29D3751446561112B2378F6127E5D3A7ED706D09BBA
REM REVISION: 1.0
REM GUID: 67C6936B-1A8D-4957-91C9-AE352304F2B6
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_arduinoB.bat
@SET ComPort=%3
@SET BaudRate=%4

@REM -------------- AVRDUDE programmer --------------

@SET Fuse1=
@SET Fuse2=
@SET Fuse3=

@REM WSCRIPT.EXE %~dp0usermessage.vbs


@REM %6 is the flag to send fuse data instead of the program
@IF "%6"=="1" GOTO Config


:ProgFlash
@SET AVRDUDEcmd="%~dp0..\bin\oldavrdude\avrdude.exe" -p %1 -P %ComPort% -b %BaudRate% -c %2 -U flash:w:%5
@SHIFT
@GOTO Send


:Config
@SET AVRDUDEcmd="%~dp0..\bin\oldavrdude\avrdude.exe" -p %1 -P %ComPort% -b %BaudRate% -c %2 -u

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

@REM mode %ComPort%: baud=%BaudRate% parity=n data=8 stop=1 to=on xon=off odsr=off octs=off dtr=hs rts=off idsr=off
@REM >mode %ComPort%: baud=%BaudRate% parity=n data=8 stop=1 to=on xon=off odsr=off octs=off dtr=on rts=off idsr=off

%AVRDUDEcmd% %Fuse1% %Fuse2% %Fuse3% %0 %1  %2  %3  %4  %5  %6  %7  %8  %9
@IF %ERRORLEVEL% NEQ 0 GOTO DUDEError
@GOTO End


:DUDEError
@ECHO.
@ECHO Error returned from [avrdude]
@EXIT %ERRORLEVEL%



:End
@ECHO.
@ECHO Programming successful!
@EXIT 0
