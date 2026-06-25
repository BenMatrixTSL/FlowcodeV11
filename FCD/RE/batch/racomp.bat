REM CRC: 1B8A31553071B640B15EDBAD63B810CBD6F094C6924281B1C7D1CEA7408CBE85F23BFF3064C25A11BAFA61B701B8D046A54A2ADCDF3B87E1237188660FCD9BBC2BBB7B1CC80F12CBA9B11F738DF98E15AE6A43207D464148D171E860E2D64E01F09204F64CE5B896F4AC301AB9DE17AA564956DEB1E34B5B003CFC01F2A961FE4957E1FF9FF8CC26EAEDC56B9CA8ED6F152536D475FA8D09220F6971E2AA525AC81A47787168F9882C3050DA273BE4EEECF7075E5D7912F6DFA77E7E2733D9964BDA31D120CEEC4A3E7DF3EE771A32107C30AF6F6246FD52
REM REVISION: 1.0
REM GUID: F4A5B6C7-D8E9-0123-7890-234567890123
REM DATE: 25\06\2026
REM DIR: FCD\RE\batch\racomp.bat

@setlocal enabledelayedexpansion

@REM Calling parameters (match stm32comp.bat convention):
@REM "$(target)" "$(outdir)" "$(chipalt)" "$(family)" "$(lscript)" "$(clock)" "$(romsize)" "$(ramsize)" "$(compilerstarm)"
@PUSHD %~2

@SET MX_PROJECT=%~1
@SET MX_CHIPALT=%~3
@SET MX_FAMILY=%~4
@SET MX_LSCRIPT=%~5
@SET MX_CLOCK=%~6
@SET MX_ROMSIZE=%~7
@SET MX_RAMSIZE=%~8
@SET MX_STARM=%~9

@REM Save path and add arm-none-eabi toolchain (reuse STARM toolchain)
@SET MX_PATH=%PATH%
@PATH=%MX_STARM%gcc\bin

@REM Derive FCD RE directory from the batch script location
@SET MX_RE=%~dp0..

@REM All RA4/RA6 devices are Cortex-M4 with hardware FPU
@SET MX_CORE=cortex-m4
@SET MX_FPU=-mfpu=fpv4-sp-d16 -mfloat-abi=hard

@SET MX_CC=arm-none-eabi-gcc
@SET MX_COPY=arm-none-eabi-objcopy
@SET MX_DUMP=arm-none-eabi-objdump
@SET MX_SIZE=arm-none-eabi-size

@SET MX_CFLAGS=-mcpu=%MX_CORE% -mthumb %MX_FPU% -Os
@SET MX_DEFINES=-D%MX_CHIPALT% -DRA_%MX_FAMILY% -DUSE_FULL_ASSERT=0 -DRA4M1_SYSCLK=%MX_CLOCK%UL
@SET MX_HEADERS=-I"%MX_RE%\inc"
@SET MX_CTRL=-fmessage-length=0 -fdata-sections -ffunction-sections -w -c

@REM Select system clock init based on device family (RA4=HOCO, RA6=HOCO+PLL)
@SET MX_SYSFILE=%MX_RE%\src\system_ra4m1.c
@SET MX_SYSOBJNAME=system_ra4m1.o
@IF "%MX_FAMILY:~0,3%" == "RA6" (
    @SET MX_SYSFILE=%MX_RE%\src\system_ra6.c
    @SET MX_SYSOBJNAME=system_ra6.o
)

@SET MX_OBJECTS=%MX_PROJECT%_%MX_CHIPALT%_%MX_CLOCK%

@ECHO.
@ECHO Project  : %MX_PROJECT%
@ECHO Device   : %MX_CHIPALT%
@ECHO Family   : %MX_FAMILY%
@ECHO Clock    : %MX_CLOCK%
@ECHO ROM      : %MX_ROMSIZE%
@ECHO RAM      : %MX_RAMSIZE%
@ECHO Linker   : %MX_LSCRIPT%
@ECHO.

@MKDIR "%MX_OBJECTS%" >nul 2>&1

@REM Compile main project file
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_PROJECT%.c" -o "%MX_OBJECTS%\%MX_PROJECT%.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Compile startup code
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_RE%\src\ra4m1_startup.c" -o "%MX_OBJECTS%\ra4m1_startup.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Compile system clock init (family-selected)
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_SYSFILE%" -o "%MX_OBJECTS%\%MX_SYSOBJNAME%"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Compile newlib syscalls
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_RE%\src\syscalls.c" -o "%MX_OBJECTS%\syscalls.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Compile IRQ stubs
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_RE%\src\MX_IRQs.c" -o "%MX_OBJECTS%\MX_IRQs.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Link
@cd /D %MX_OBJECTS%

@set ObjFileList=
@for %%G in (*.o) do @(set ObjFileName=%%G
call :ListObj
)

@SET MX_LFLAGS=-O -g -w -Wl,-T"%MX_RE%\link\%MX_LSCRIPT%",--gc-sections %MX_CFLAGS% -Xlinker --defsym=_ROMSIZE=%MX_ROMSIZE% -Xlinker --defsym=_RAMSIZE=%MX_RAMSIZE%
%MX_CC% %MX_LFLAGS% %ObjFileList% -o "..\%MX_PROJECT%.elf" -lm -lc
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Generate hex and bin
%MX_COPY% -O ihex   "..\%MX_PROJECT%.elf" "..\%MX_PROJECT%.hex"
@IF %ERRORLEVEL% NEQ 0 GOTO Error
%MX_COPY% -O binary "..\%MX_PROJECT%.elf" "..\%MX_PROJECT%.bin"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Generate listing
%MX_DUMP% -t -d -h "..\%MX_PROJECT%.elf" > "%MX_PROJECT%.lst"

@REM Show memory usage
%MX_SIZE% -B "..\%MX_PROJECT%.elf"

@ECHO Compilation successful!
@PATH=%MX_PATH%
@POPD
@EXIT 0

:Error
@ECHO Error(s) in build!
@PATH=%MX_PATH%
@POPD
@EXIT 1

:ListObj
@set ObjFileList=%ObjFileList% "%ObjFileName%"
:ObjDone
@goto :eof
