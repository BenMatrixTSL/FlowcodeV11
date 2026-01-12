REM CRC: 11E85D0BF540A03612B9D5AB8A950728A3654FDC084B783F85B503651504FC6ECECA6F644019FEC137D1B791B1CE3DD8F6A4CCB7873802B223E4F4A1008A359162F72D27E9D34842BF9B97A3AFBBCBEE79486D63975370310C3CAEE8E7DA6987CA332F5CF1C50D8FCF6BBCD90664ECA38D77124003869A39205AAAF779DFA9F40B90AFE0C9F100733EC1BCCF07991D2337ED5FD0E93581AB44CD403517DE67C9820FAE8BA024F5B051D0C25B0E9FDF00BB01E6EAF3ADA0062C3050DA273BE4EE49D344CD39215A57ADAD2514ABB6B107229735A15A4B96E7A8B2FE2536E6C50FEBD31FED13C8BAD2
REM REVISION: 2.0
REM GUID: 2E1A487E-A894-44B9-9841-7C341FE7D17B
REM DATE: 06\10\2025
REM DIR: FCD\PICO\batch\pico_prog.bat
@echo off
setlocal enabledelayedexpansion

REM Parse arguments
set "uf2File=%~1%~2.uf2"
set "volumeName=%~3"

REM Validate inputs
if "%uf2File%"==".uf2" (
    start "PICO Programming Error" cmd /k "echo Error: No .uf2 file specified && echo Usage: pico_prog.bat [path] [filename] [volume_name] && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

if not exist "%uf2File%" (
    start "PICO Programming Error" cmd /k "echo Error: File not found: %uf2File% && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

if "%volumeName%"=="" (
    start "PICO Programming Error" cmd /k "echo Error: Volume name not specified && echo Usage: pico_prog.bat [path] [filename] [volume_name] && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

REM Show programming window
start "PICO Programming" cmd /c "echo Programming %volumeName% board... && echo Searching for drive... && timeout /t 1 /nobreak >nul"

REM Search for the volume
set "targetDrive="
for %%d in (D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
    vol %%d: 2>nul | findstr /i "%volumeName%" >nul
    if not errorlevel 1 (
        set "targetDrive=%%d:"
        goto :found
    )
)

REM Volume not found
start "PICO Programming Error" cmd /k "echo Error: %volumeName% board is not connected && echo Please connect the board in BOOTSEL mode and try again && echo. && echo Press any key to close... && pause >nul && exit"
exit /b 1

:found
REM Copy file with visible progress
start "PICO Programming" /wait cmd /c "echo Found %volumeName% on drive %targetDrive% && echo Copying %uf2File%... && copy /Y "%uf2File%" "%targetDrive%" && echo. && echo Success: Programming complete! && echo Board will reboot automatically. && timeout /t 3 /nobreak >nul"

if errorlevel 1 (
    start "PICO Programming Error" cmd /k "echo Error: Failed to copy file && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

exit /b 0