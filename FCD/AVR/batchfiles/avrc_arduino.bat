REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B69041072C26934F62BA2AD18E3139D88C14D7D52A5267262C133672476D09DF645E1305C640EF477B79E0C7881D2E5EEC9BD69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF597E410CFCC25A9782C8434689A3D5088235D5D5B1E1DC78EA61C9B6250B0AF3D0E13E40D678CA9671783EC9BAE8885B1FA992E6D6917A04345078DFA8C627C4B5B1F7430C7AEBF8C91C9A8ACBD6A6CF33912C5479DAFCAEB2C3050DA273BE4EE0EA0D97D4FD6345C4154E0EAC5B8709551FEADAF4EA8F1AC6FF949B8D8BFAD15599C160227117CAC
REM REVISION: 1.0
REM GUID: 52FACCE2-D3BF-4A76-A83A-C45172D0FE4B
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avrc_arduino.bat
@SET ComPort=%3
@SET BaudRate=%4

@REM -------------- AVRDUDE programmer --------------

@SET Fuse1=
@SET Fuse2=
@SET Fuse3=


@REM %6 is the flag to send fuse data instead of the program
@IF "%6"=="1" GOTO Config


:ProgFlash
@SET AVRDUDEcmd="%~dp0..\bin\avrdude.exe" -p %1 -P %ComPort% -b %BaudRate% -c %2 -U flash:w:%5
@SHIFT
@GOTO Send


:Config
@SET AVRDUDEcmd="%~dp0..\bin\avrdude.exe" -p %1 -P %ComPort% -b %BaudRate% -c %2 -u

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

@mode %ComPort%: baud=%BaudRate% parity=n data=8 stop=1 to=on xon=off odsr=off octs=off dtr=hs rts=off idsr=off

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
