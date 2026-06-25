REM CRC: 1B8A31553071B640B15EDBAD63B810CB6F3D84C3B066AD4CF6F780238A3A665C4ACACED02C13B4AC3809EC856F905CF4A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E155570B71660F69F8F7ED04CCBBADC75718BF666BCA193F2F15C1F7D3FAFA55B6718382998DDAC5FA01EFD948B61141B39B8A67B1693D8C55D394C0B20DF6611567DC749AC864174C374EA8D4BAD01BA4F2BC96222220CB4F02C3050DA273BE4EEEE33DC9E186EE3DC8141095B3218D43EAC5139B4A3315925699D3FB0243A924976D21B2897729CBF
REM REVISION: 1.0
REM GUID: A5B6C7D8-E9F0-1234-8901-345678901234
REM DATE: 25\06\2026
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
