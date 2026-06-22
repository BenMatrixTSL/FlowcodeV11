REM CRC: 0000000000000000000000000000000000000000000000000000000000000000
REM REVISION: 1.0
REM GUID: A5B6C7D8-E9F0-1234-8901-345678901234
REM DATE: 22\06\2026
REM DIR: FCD\RE\batch\raprog.bat

@REM Calling parameters (match stm32prog.bat convention):
@REM "$(outdir)" "$(target)" $(devname) "$(compilerstarm)"
@SET MX_LOCATION=%~1
@SET MX_PROJECT=%~2
@SET MX_DEVNAME=%~3
@SET MX_STARM=%~4

@SET MX_PATH=%PATH%

@REM Detect J-Link on PATH or in common install location
@WHERE JLink.exe >nul 2>&1
@IF %ERRORLEVEL% EQU 0 GOTO JLinkProg
@IF EXIST "C:\Program Files\SEGGER\JLink\JLink.exe" GOTO JLinkInstalled

@REM Fall back to dfu-util (Arduino Uno R4 USB bootloader)
@WHERE dfu-util >nul 2>&1
@IF %ERRORLEVEL% EQU 0 GOTO DFUProg

@ECHO ERROR: No programmer found.
@ECHO   - Install J-Link tools (SEGGER) for SWD/JTAG programming, OR
@ECHO   - Install dfu-util and put Arduino Uno R4 into DFU mode for USB programming.
@PATH=%MX_PATH%
@EXIT 1

:JLinkInstalled
@PATH=%PATH%;C:\Program Files\SEGGER\JLink
@GOTO JLinkProg

:JLinkProg
@ECHO Programming %MX_PROJECT% via J-Link SWD ...
@REM Generate J-Link script
@(
  ECHO device R7FA4M1AB
  ECHO si SWD
  ECHO speed 4000
  ECHO connect
  ECHO r
  ECHO loadfile "%MX_LOCATION%%MX_PROJECT%.hex"
  ECHO r
  ECHO g
  ECHO exit
) > "%TEMP%\jlink_prog.jlink"
JLink.exe -NoGui 1 -CommanderScript "%TEMP%\jlink_prog.jlink"
@IF %ERRORLEVEL% NEQ 0 GOTO Error
@GOTO Done

:DFUProg
@ECHO Programming %MX_PROJECT% via USB DFU (Arduino Uno R4 bootloader) ...
@ECHO Ensure the board is in DFU mode (double-press reset button).
dfu-util -a 0 --dfuse-address 0x8000:leave -D "%MX_LOCATION%%MX_PROJECT%.bin"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

:Done
@ECHO Download successful!
@PATH=%MX_PATH%
@EXIT 0

:Error
@ECHO Error(s) in programming!
@PATH=%MX_PATH%
@EXIT 1
