REM CRC: 1CECFE3DB3A1BD5169AEA98AD43ADE6310683869BC3B7A839DC480A0FAD85277132422CE3D4DC8BC8D12F03732EA1AD305C640EF477B79E0C7881D2E5EEC9BD69A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF5E9F0CBF1176B1B57A85B223630B0A44B1D985366A319E7907E04B2A1413F5F66A8EE02E6080175C68C5A825A874D913267163092B3246D8531EBC235A32BE106EE33E44D6C036E2AEAAB9D2596E2A457868F480396BDEF2F2C3050DA273BE4EEF2505040FADDB54F106A04479EEA5BD1B11083917E7D7B77ACA9CE2DF1EA8436E42CFE37638C9748
REM REVISION: 1.0
REM GUID: FA98F86F-FDDE-41D7-8114-CF71B7D7B141
REM DATE: 08\08\2022
REM DIR: FCD\ARM\batch\F429Disco.bat

@setlocal enabledelayedexpansion

@REM These are the calling parameters ...
@REM "$(target)" "$(outdir)" "$(chipalt)" "$(family)" "$(lscript)" "$(romsize)" "$(ramsize)" "$(compilerstarm)"
@PUSHD %~2

@REM Setup the build parameters 
@SET MX_PROJECT=%~1
@SET MX_FAMILY=%~4
@SET MX_LSCRIPT=%~5
@SET MX_DEVICE=STM%~3
@SET MX_HSE_VALUE=%~6
@SET MX_ROMSIZE=%~7
@SET MX_RAMSIZE=%~8
@SET MX_STARM=%~9

@REM Save the cuurent path as we are going to change it
@SET MX_PATH=%PATH%
@REM Setup the path for the tools ...
@PATH=%MX_STARM%gcc\bin

@set MX_FPUType=-mfloat-abi=hard -mfpu=fpv4-sp-d16
::@set FPUType=-mfloat-abi=soft
@set OptLevel=s

@IF "%MX_FAMILY%" == "F0" (
	@SET MX_CORE=cortex-m0
	@SET MX_FPUType=-mfloat-abi=soft -D__SOFTFP__
	)
@IF "%MX_FAMILY%" == "F1" (
	@SET MX_CORE=cortex-m3
	@SET MX_FPUType=-mfloat-abi=soft -D__SOFTFP__
	)
@IF "%MX_FAMILY%" == "F2" (@SET MX_CORE=cortex-m3)
@IF "%MX_FAMILY%" == "F3" (@SET MX_CORE=cortex-m4)
@IF "%MX_FAMILY%" == "F4" (@SET MX_CORE=cortex-m4)
@IF "%MX_FAMILY%" == "F7" (@SET MX_CORE=cortex-m7)

@IF "%MX_FAMILY%" == "L0" (@SET MX_CORE=cortex-l0)
@IF "%MX_FAMILY%" == "L1" (@SET MX_CORE=cortex-l1)
@IF "%MX_FAMILY%" == "L4" (@SET MX_CORE=cortex-l4)

@SET MX_CC=arm-none-eabi-gcc
@SET MX_COPY=arm-none-eabi-objcopy
@SET MX_DUMP=arm-none-eabi-objdump
@SET MX_SIZE=arm-none-eabi-size
@SET MX_CFLAGS=-mcpu=%MX_CORE% -mthumb %MX_FPUType% -Os
@SET MX_DEFINES=-DSTM32 -DSTM32%MX_FAMILY% -D%MX_DEVICE% -DUSE_HAL_DRIVER -DHSE_VALUE=%MX_HSE_VALUE%

@SET MX_DRIVERS=%MX_STARM%stm32cube%MX_FAMILY%\Drivers
@set MX_BSP_COMPONENTS=%MX_DRIVERS%\BSP\Components
@set MX_BSP_BOARD=%MX_DRIVERS%\BSP\STM32F429I-Discovery
@SET MX_HEADERS=-I"%MX_DRIVERS%\CMSIS\Include" -I"%MX_DRIVERS%\CMSIS\Device\ST\STM32%MX_FAMILY%xx\Include" -I"%MX_DRIVERS%\STM32%MX_FAMILY%xx_HAL_Driver\Inc" -I"%MX_DRIVERS%\STM32%MX_FAMILY%xx_HAL_Driver\Inc\Legacy" -I"%MX_DRIVERS%\BSP\STM32F429I-Discovery" -I"%MX_DRIVERS%\BSP\Components" -I"%~dp0..\inc" -I"%~dp0..\boards"
@SET MX_CTRL=-fmessage-length=0 -fdata-sections -ffunction-sections -w -c
@SET MX_HALSRC=%MX_DRIVERS%\STM32%MX_FAMILY%xx_HAL_Driver\Src
@SET MX_OBJECTS=%MX_PROJECT%_%MX_DEVICE%_%MX_HSE_VALUE%
@ECHO.
@ECHO Project %MX_PROJECT% 
@ECHO Device %MX_DEVICE%
@ECHO.

@MKDIR "%MX_OBJECTS%" >nul 2>&1
@REM Compile the project ...
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_PROJECT%.c" -o "%MX_OBJECTS%\%MX_PROJECT%.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

::HAL Files
::@if not %CompileHAL% == 1 goto :HALdone
@set SrcPath="%MX_HALSRC%\"
@for %%G in (%SrcPath%*.c) do @(set srcFile=%%G
call :MakeObj "%%G"
)
::HALdone

::BSP Files (optional)
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\STM32f429i_Discovery.o" "%MX_BSP_BOARD%\STM32f429i_Discovery.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\STM32f429i_discovery_sdram.o" "%MX_BSP_BOARD%\STM32f429i_discovery_sdram.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\STM32f429i_discovery_lcd.o" "%MX_BSP_BOARD%\STM32f429i_discovery_lcd.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\STM32f429i_discovery_ts.o" "%MX_BSP_BOARD%\STM32f429i_discovery_ts.c"
::%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\STM32f429i_discovery_qspi.o" "%MX_BSP_BOARD%\STM32f429i_discovery_qspi.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\stm32f429i_discovery_gyroscope.o" "%MX_BSP_BOARD%\stm32f429i_discovery_gyroscope.c"

%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\ili9341.o" "%MX_BSP_COMPONENTS%\ili9341\ili9341.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\stmpe811.o" "%MX_BSP_COMPONENTS%\stmpe811\stmpe811.c"
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% -o "%MX_OBJECTS%\l3gd20.o" "%MX_BSP_COMPONENTS%\l3gd20\l3gd20.c"

@REM Build the startup objects ...
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_DRIVERS%\CMSIS\Device\ST\STM32%MX_FAMILY%xx\Source\Templates\gcc\startup_%MX_DEVICE%.s" -o "%MX_OBJECTS%\startup.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%MX_DRIVERS%\CMSIS\Device\ST\STM32%MX_FAMILY%xx\Source\Templates\system_stm32%MX_FAMILY%xx.c" -o "%MX_OBJECTS%\system.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%~dp0..\src\syscalls.c" -o "%MX_OBJECTS%\syscalls.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error
%MX_CC% %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% %MX_CTRL% "%~dp0..\src\MX_IRQs.c" -o "%MX_OBJECTS%\MX_IRQs.o"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Link ...

@cd /D %MX_OBJECTS%

::Make .o file list
@set ObjFileList=
@for %%G in (*.o) do @(set ObjFileName=%%G
call :ListObj
)

@SET MX_LFLAGS=-O -g -w -Wl,-T"%~dp0..\link\%MX_LSCRIPT%",--gc-sections %MX_CFLAGS% -Xlinker --defsym=_ROMSIZE=%MX_ROMSIZE% -Xlinker --defsym=_RAMSIZE=%MX_RAMSIZE%
%MX_CC% %MX_LFLAGS% %ObjFileList% -o "..\%MX_PROJECT%.elf" -lm 
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM elf to hex ...
@REM 
%MX_COPY% -O ihex "..\%MX_PROJECT%.elf" "..\%MX_PROJECT%.hex"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM elf to bin ...
@REM 
%MX_COPY% -O binary "..\%MX_PROJECT%.elf" "..\%MX_PROJECT%.bin"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Create a list file ...
@REM 
%MX_DUMP% -t -d  -h "..\%MX_PROJECT%.elf" > "%MX_PROJECT%.lst"
@IF %ERRORLEVEL% NEQ 0 GOTO Error

@REM Display memory usage ...
@REM 
%MX_SIZE% -B "..\%MX_PROJECT%.elf"

@ECHO Compilation successful!
@PATH=%MX_PATH%
@POPD
@EXIT 0

@:Error
@ECHO Error(s) in build!
@PATH=%MX_PATH%
@POPD
@EXIT 1


:MakeObj
::Resolve path to filename only
@set ObjFileName=%~n1

::Ignore files ending in template
@set IsTemplate=%ObjFileName:~-8%
@if %IsTemplate% == template goto :FileDone

::Change .c extension to .o
@set ObjFileName=%ObjFileName%.o

::Skip if object already exists
@if exist "%MX_OBJECTS%\%ObjFileName%" goto :FileDone

::Compile .c file and add resulting .o file to project folder
"%MX_CC%" %MX_CFLAGS% %MX_DEFINES% %MX_HEADERS% -O%OptLevel% %MX_CTRL% -o "%MX_OBJECTS%\%ObjFileName%" "%SrcFile%"

:FileDone
@goto :eof


:ListObj
@set ObjFileList=%ObjFileList% "%ObjFileName%"
:ObjDone
@goto :eof
