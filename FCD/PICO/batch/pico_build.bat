REM CRC: 11E85D0BF540A03612B9D5AB8A950728A3654FDC084B783F85B503651504FC6E8DA967745A187CF8FECF9115B25085A2774D1D3D69D8A99EE7320EAE740A5DB69B0AF84BD9A2B9E26CFA768EA02184EEC4965B289802A73C711B8143522C2B691E456854D22958005824CF181DE22D23B9DE25CDF0E36405D9066202E94705CBBDB038842E43FA4AAC72934211FD4B5DCC661788BEC7C91A063848616D51551DB978AC1A4BAF29AD4517DCDD22FC70DE135D32748FB3D1732C3050DA273BE4EE56E5C488FA71EDB383599EBCE6C99F1BCD19E1FAE96D2DC21970AB48E245A709734CC46D5AB08C67
REM REVISION: 2.0
REM GUID: 9EF5601F-D979-495F-89EB-F1C4F35D9212
REM DATE: 02\06\2023
REM DIR: FCD\PICO\batch\pico_build.bat

@SET PICO_SDK_PATH=%~1
@SET PROJECT=%~2
@SET OUT_DIR=%~3
@REM SET CONFIG=%~4
@SETX PICO_SDK_PATH %PICO_SDK_PATH% > NUL

@SET BUILD_DIR=%OUT_DIR%%PROJECT%
@REM Remove spaces from the path ...
@SET BUILD_DIR=%BUILD_DIR: =_%

@ECHO Building %PROJECT% ...

@REM Create the project tree and copy in default files ...
@PUSHD %~dp0
@REM Now in the batch dir
@MKDIR "%BUILD_DIR%"                           > NUL 2> NUL
@IF NOT EXIST "%BUILD_DIR%\CMakeLists.txt"        COPY CMakeLists.txt            "%BUILD_DIR%"  > NUL
@IF NOT EXIST "%BUILD_DIR%\pico_sdk_import.cmake" COPY pico_sdk_import_cmake.txt "%BUILD_DIR%\pico_sdk_import.cmake"  > NUL
@POPD

@REM Delete any previous output ...
@DEL "%BUILD_DIR%\flowcode.*"    > NUL 2> NUL

@REM Copy in the project C file ...
@COPY "%OUT_DIR%%PROJECT%.c" "%BUILD_DIR%\flowcode.c"   > NUL

@REM Do the build ...
@PUSHD "%BUILD_DIR%"
@if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat" (CALL "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat")
@if exist "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" (CALL "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat")
@cmake -G "NMake Makefiles" .
@nmake
@POPD

@REM Test for the existance of the output file ...
@IF EXIST "%BUILD_DIR%\flowcode.uf2" GOTO SUCCESS
@ECHO.
@ECHO Build Failed
@EXIT 1

:SUCCESS
@REM Copy the output file to the source location ...
@COPY "%BUILD_DIR%\flowcode.uf2" "%OUT_DIR%%PROJECT%.uf2"  > NUL
@ECHO.
@ECHO Build completed successfully 
@EXIT 0

