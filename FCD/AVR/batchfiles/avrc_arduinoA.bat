REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D7BD8C8CEEE570C34335B9BD40DC91ABF9F6A4CCB7873802B223E4F4A1008A35919A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF56C9BC3BB2590B5192C2BCACE9467A07961E9396118791606FB531939F6539CFCA719F5A675CCBEE4B35B6B3E06A3B6EA1F1C802F1E0729A39B031A08340CB3AD07D220268868A23DD35657CD8CE9A282EF4678980A2C5F4D2C3050DA273BE4EE2CC1E88F2D5F77FA0C3AE4CE7890CA0B515E308238372D4FCC6735C2880B0855018D7FE4AA495AC4
REM REVISION: 1.0
REM GUID: BC89C337-8FBB-43B7-A3A7-C7902C121931
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_arduinoA.bat
@REM params = $(compileravr) $(chipalt) arduino $(comport) 115200 $(outdir)$(target).hex
@SET MX_COMPILER=%~1
@SET MX_CHIP=%2

@SET ComPort=%4
@SET BaudRate=%5

@REM -------------- AVRDUDE programmer --------------

@SET Fuse1=
@SET Fuse2=
@SET Fuse3=

@REM WSCRIPT.EXE %~dp0usermessage.vbs

@SET FilePath=%~dp6
@SET FileName=%~nx6
@PUSHD %FilePath%

@REM %6 is the flag to send fuse data instead of the program
@IF "%7"=="1" GOTO Config


:ProgFlash
@SET AVRDUDEcmd="%MX_COMPILER%bin\avrdude.exe" -p%MX_CHIP% -P%ComPort% -b%BaudRate% -c%3 -D -Uflash:w:"%FileName%"
@SHIFT
@GOTO Send


:Config
@SET AVRDUDEcmd="%MX_COMPILER%bin\avrdude.exe" -p%MX_CHIP% -P%ComPort% -b%BaudRate% -c%3 -u

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
