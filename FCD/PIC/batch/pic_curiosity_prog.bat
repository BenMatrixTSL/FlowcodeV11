REM CRC: 90CF26913586BBA787FE92D553771933222DCF72B25FEB4608E17FBD060500D832EA69991C50407C530D2EE49A57F1A83F0566FD086E950376A73730A1945479F6A4CCB7873802B223E4F4A1008A359162F72D27E9D34842BF9B97A3AFBBCBEE3027571EAD75915DA9B11F738DF98E1571305FCDA71BBD20BC1E610139B3823DBF5E2E5848C1064D472917F3C4CBF78029F345D221BF8DDF5E35CE670E537329E886BF5981B456579027E07E455782209A30B5F1181A29DD6FE03EEA69E1A6218DBB5D5F7F4B8D092C3050DA273BE4EEDD22836BF8DD7B043EFF79CFDBCF3B2E4390C405E0D20754F0B9F6FEC6D77E3F44FB7D5555DAC58F
REM REVISION: 2.0
REM GUID: 938795F8-3A27-49ED-9038-9FC80252394B
REM DATE: 06\10\2026
REM DIR: FCD\PIC\batch\pic_curiosity_prog.bat

@echo off
setlocal enabledelayedexpansion

REM Parse arguments
set "hexFile=%~1%~2.hex"
set "volumeName=%~3"

REM Validate inputs
if "%hexFile%"==".hex" (
    start "PIC Programming Error" cmd /k "echo Error: No .hex file specified && echo Usage: pic_curiosity_prog.bat [path] [filename] [volume_name] && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

if not exist "%hexFile%" (
    start "PIC Programming Error" cmd /k "echo Error: File not found: %hexFile% && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

if "%volumeName%"=="" (
    start "PIC Programming Error" cmd /k "echo Error: Volume name not specified && echo Usage: pic_curiosity_prog.bat [path] [filename] [volume_name] && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

REM Show programming window
start "PIC Programming" cmd /c "echo Programming %volumeName% board... && echo Searching for drive... && timeout /t 1 /nobreak >nul"

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
start "PIC Programming Error" cmd /k "echo Error: %volumeName% board is not connected && echo Please connect the board in BOOTSEL mode and try again && echo. && echo Press any key to close... && pause >nul && exit"
exit /b 1

:found
REM Copy file with visible progress
start "PIC Programming" /wait cmd /c "echo Found %volumeName% on drive %targetDrive% && echo Copying %hexFile%... && copy /Y "%hexFile%" "%targetDrive%" && echo. && echo Success: Programming complete! && echo Board will reboot automatically. && timeout /t 3 /nobreak >nul"

if errorlevel 1 (
    start "PIC Programming Error" cmd /k "echo Error: Failed to copy file && echo. && echo Press any key to close... && pause >nul && exit"
    exit /b 1
)

exit /b 0