REM CRC: 90CF26913586BBA787FE92D553771933222DCF72B25FEB4608E17FBD060500D8A6D7AF8357042D9E8B5C2E833010A32BF027A71B5063E26FCEB8F7289B53FE8C9A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5581B71D2DC91E5E86092CB0130E7F64D5E760BC301A657C495F231BD1F7F16C2234C61EA68EC33371CF9F9CCE1B4199D0526F50F556AD6857D7B6BFE29D2FC252F689825F99F2B52F7948FFF724D4A74F301E900E471C6EF2C3050DA273BE4EECAB4C15199B97C929403230FF3994A4A00787857F9A099C9F97B3AD2E0D541FFE19252820FE3EB9C
REM REVISION: 1.0
REM GUID: 5922F39B-A301-4E71-B829-276A39165F53
REM DATE: 08\08\2022
REM DIR: FCD\PIC\batch\pic_xc8_comp_a.bat
@REM "$(compilerpic)" $(chip) "$(outdir)" "$(target)"
@SET MX_COMPILER=%~1
@SET MX_CHIP=%~2
@SET MX_OUTDIR=%~3
@SET MX_PROJECT=%~4
@PUSHD %MX_OUTDIR%

"%MX_COMPILER%bin\xc8.exe" --pass1  --chip=%MX_CHIP% -Q -G  --double=32 --float=32 --opt=none --addrqual=ignore -P -N255 --warn=-3 --asmlist -DXPRJ_default=default  --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib   --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -o%MX_PROJECT%.p1 %MX_PROJECT%.c 
"%MX_COMPILER%bin\xc8.exe"  --chip=%MX_CHIP% -G -m%MX_PROJECT%.map  -DXPRJ_default=default  --double=32 --float=32 --opt=none --addrqual=ignore -P -N255 --warn=-3 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-osccal,-resetbits,-download,-stackcall,+clib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"      --memorysummary %MX_PROJECT%.xml -o%MX_PROJECT%.elf  %MX_PROJECT%.p1     

@POPD
@IF %ERRORLEVEL% NEQ 0 GOTO Error
@ECHO.
@ECHO Compilation successful!
@EXIT 0
:Error
@ECHO.
@ECHO Error returned from [xc8.exe]
@EXIT 1
