REM CRC: EA277D0C7EF9B4E537B79187D0BE7A25FA6080B4B01BE48BAF713429E4B690419B94A2D6A3574DE81AD988BF47196F327C5404221427AD8C1AB07864162D3B0B9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5FD304FEF9C9E1392E45F0AD91CDDF624D07B25716C37243B002DBD375EE4AC9BFA49D77510D8282CCEFC6F9103873C29EBC2CEE35AFAB7D7BECC9044C0DD087BC515143D92981CE52B4EEF5C8CB4E2C40F160C430B0168FE2C3050DA273BE4EEA821F8E70EDC982977365D5B72AD6EB0DF0E317B8405FEF3EA7459FBAA187747CD4C0F0302B21EE1
REM REVISION: 1.0
REM GUID: 9DC18A82-4A43-4D41-B988-C53C3CD412BD
REM DATE: 08\08\2022
REM DIR: FCD\AVR\batchfiles\avra_usb.bat

::Set the device specific series folder

@IF %1 EQU at90usb82 GOTO :Series2
@IF %1 EQU at90usb162 GOTO :Series2
@IF %1 EQU at90usb646 GOTO :Series67
@IF %1 EQU at90usb647 GOTO :Series67
@IF %1 EQU at90usb1286 GOTO :Series67
@IF %1 EQU at90usb1287 GOTO :Series67
@IF %1 EQU atmega8u2 GOTO :Series2
@IF %1 EQU atmega16u2 GOTO :Series2
@IF %1 EQU atmega16u4 GOTO :Series4
@IF %1 EQU atmega32u2 GOTO :Series2
@IF %1 EQU atmega32u4 GOTO :Series4
@ECHO USB device not recognised
@EXIT 1

:Series2
@set SerFolder=Series2
@GOTO :Descript

:Series4
@set SerFolder=Series4
@GOTO :Descript

:Series67
@set SerFolder=Series67
@GOTO :Descript

:: Set the application specific filder and file options

:Descript
@IF %4 EQU Serial GOTO :USBSer
@IF %4 EQU HID GOTO :USBHID
@IF %4 EQU Slave GOTO :USBSlave
@IF %4 EQU MIDI GOTO :USBMIDI
@ECHO USB task not recognised
@EXIT 1

:USBSer
@set Typefolder=CDC
@set TypeFile=uart_usb_lib
@GOTO :CompStart

:USBHID
@set Typefolder=HID
@set TypeFile=hid_task
@GOTO :CompStart

:USBSlave
@set Typefolder=Slave
@set TypeFile=slave_task
@GOTO :CompStart

:USBSlave
@set Typefolder=MIDI
@set TypeFile=midi_task
@GOTO :CompStart

:CompStart
@set P1=%~dp0..\..\..\CAL\AVR\USB\%SerFolder%
@set P2=%P1%\demo\%TypeFolder%
@set P3=%P2%\conf
@set Psrc=%~2.
@set CompDir=%~5.

@ECHO .
@ECHO Deleting existing .o files
del "%~2%~3.o"
del "%~2usb_specific_request.o"
del "%~2usb_descriptors.o"
del "%~2power_drv.o"
del "%~2usb_drv.o"
del "%~2usb_task.o"
del "%~2usb_standard_request.o"
del "%~2usb_device_task.o"

::Flowcode source
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -funsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2%~3.o" -c "%~2%~3.c" -lm

::usb_specific_request
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_specific_request.o" -c "%P2%\usb_specific_request.c"

::usb_descriptors
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_descriptors.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\demo\%Typefolder%\usb_descriptors.c"

::power_drv
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2power_drv.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\lib_mcu\power\power_drv.c"

::usb_drv
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_drv.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\lib_mcu\usb\usb_drv.c"

::usb_task
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_task.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\modules\usb\usb_task.c"

::usb_standard_request
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_standard_request.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\modules\usb\device_chap9\usb_standard_request.c"

::usb_device_task
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2usb_device_task.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\modules\usb\device_chap9\usb_device_task.c"

::required task
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 -w -Os -fsigned-char -I"%P1%" -I"%P2%" -I"%P3%" -I"%Psrc%" -o "%~2%TypeFile%.o" -c "%~dp0..\..\..\CAL\AVR\USB\%SerFolder%\demo\%Typefolder%\%TypeFile%.c"


:: make .elf file
"%CompDir%\bin\avr-gcc.exe" -mmcu=%1 "%~2%~3.o" "%~2usb_specific_request.o"  "%~2usb_descriptors.o" "%~2power_drv.o" "%~2usb_drv.o" "%~2usb_task.o" "%~2usb_standard_request.o" "%~2usb_device_task.o" "%~2%TypeFile%.o" -o "%~2%~3.elf"

@GOTO :CompDone


:CompDone
@IF %ERRORLEVEL% NEQ 0 GOTO Error1

"%CompDir%\bin\avr-objdump.exe" -S "%~2%~3.elf" > "%~2%~3.lst"
@IF %ERRORLEVEL% NEQ 0 GOTO Error2

"%CompDir%\bin\avr-size.exe" -B -d "%~2%~3.elf"

@ECHO.
@ECHO Compilation successful!
@GOTO :End

:Error1
@ECHO.
@ECHO Error returned from [avr-gcc.exe]
@EXIT %ERRORLEVEL%

:Error2
@ECHO.
@ECHO Error returned from [avr-objdump.exe]
@EXIT %ERRORLEVEL%

:End
@EXIT 0
