REM CRC: 0796FC1E6A776AF9156B257209C35258CE7C28B3EC20AEA2C632DB392A0E4BFD5B3F53B21811978F7B21FE4085045A7E774D1D3D69D8A99EE7320EAE740A5DB60228F42835EF5B88138FDEE58A4EE9C3A4BAF1B34E38B68E0C3CAEE8E7DA6987B808018476405B65B199900461C78937B42DEF8219F63A24580137A2F6C8FDB7553324EFF791947E8AB6FFD612B81BAA97C798A8F1CFC189DE5D38517747C774AF2DD6F839BAECF83F7F994C7164CE77868F480396BDEF2F2C3050DA273BE4EE69F15C302679453617F9EA00A6A8712D05E485F25DB02304E4565E63FDA312627DD474674123A97D
REM REVISION: 15.0
REM GUID: 955EA920-4961-4C53-BA6B-EF4AF66BB4C2
REM DATE: 07\04\2025
REM DIR: FCD\ESP\Batch\esp32_build.bat

@SET BASE_DIR=%~1
@SET TARGET=%~2
@SET OUT_DIR=%~3
@SET CONFIG=%~4
@SET CHIPTYPE=%~5

@ECHO OFF

@IF "%BASE_DIR:~-2%"=="\\" SET "BASE_DIR=%BASE_DIR:~0,-1%"

@SET DOS_BUILD_DIR=%BASE_DIR%mtx%CONFIG%

@REM Remove spaces from the path ...
@SET DOS_BUILD_DIR=%DOS_BUILD_DIR: =_%

@REM Detect new toolchain install
@IF EXIST %BASE_DIR%esp-tools\ (
@GOTO SETUPTOOLCHAIN
) ELSE (
@SET TOOLS_DIR=%BASE_DIR%
@GOTO SKIPSETUPTOOLCHAIN
)

:SETUPTOOLCHAIN

@REM Create a pyenv.cfg file inside the python folder
@SET IDF_PY_CFG_PATH=%BASE_DIR%\esp-tools\python_env\idf5.3_py3.11_env\pyvenv.cfg
@ECHO Creating python config file 
(
@ECHO home = %BASE_DIR%esp-tools\tools\idf-python\3.11.2
@ECHO include-system-site-packages = false
@ECHO version = 3.11.2
@ECHO executable = %BASE_DIR%esp-tools\tools\idf-python\3.11.2\python.exe
@ECHO command = %BASE_DIR%esp-tools\tools\idf-python\3.11.2\python.exe -m venv %BASE_DIR%esp-tools\python_env\idf5.3_py3.11_env
)>"%IDF_PY_CFG_PATH%"   

@REM Setup paths to the various build tools
SET IDF_TOOLS_PATH=%BASE_DIR%esp-tools\
SET TOOLS_DIR=%BASE_DIR%frameworks\esp-idf-v5.3.1\
SET IDF_PYTHON_DIR=%IDF_TOOLS_PATH%python_env\idf5.3_py3.11_env\Scripts\
SET IDF_GIT_DIR=%IDF_TOOLS_PATH%tools\idf-git\2.44.0\bin
SET PATH=%IDF_PYTHON_DIR%;%IDF_GIT_DIR%;%PATH%

@REM Create a batch file link to the menuconfig inside the build folder
@ECHO Creating menuconfig link file 
(
@ECHO SET IDF_TOOLS_PATH=%IDF_TOOLS_PATH%
@ECHO SET TOOLS_DIR=%TOOLS_DIR%
@ECHO SET IDF_PYTHON_DIR=%IDF_PYTHON_DIR%
@ECHO SET IDF_GIT_DIR=%IDF_GIT_DIR%
@ECHO SET PATH="%IDF_PYTHON_DIR%";"%IDF_GIT_DIR%"
@ECHO @CALL "%TOOLS_DIR%export.bat"   
@ECHO python "%TOOLS_DIR%tools\idf.py" menuconfig -DIDF_TARGET=%CHIPTYPE%
)>"%DOS_BUILD_DIR%\menuconfig.bat" 

:SKIPSETUPTOOLCHAIN

@ECHO .
@ECHO ============================== Toolchain Check ==============================
@ python --version  > nul 2>&1
@IF ERRORLEVEL 1 (ECHO ERROR: Python is not installed) ELSE (python --version)
@ git --version  > nul 2>&1
@IF ERRORLEVEL 1 (ECHO ERROR: Git is not installed) ELSE (git --version)
@IF EXIST "%TOOLS_DIR%export.bat" (ECHO ESP toolchain found at "%TOOLS_DIR%") ELSE (ECHO ERROR: ESP toolchain not found at "%TOOLS_DIR%")
@ECHO =============================================================================
@ECHO .


@ECHO Building: %TARGET% ...

@REM Create the project tree and copy in default files ...
@PUSHD %~dp0
@MKDIR "%DOS_BUILD_DIR%"                           > NUL 2> NUL
@MKDIR "%DOS_BUILD_DIR%\main"                      > NUL 2> NUL
@IF NOT EXIST "%DOS_BUILD_DIR%\Makefile"            COPY Makefile.txt        "%DOS_BUILD_DIR%\Makefile"            > NUL
@IF NOT EXIST "%DOS_BUILD_DIR%\CMakeLists.txt"      COPY CMakeLists.txt      "%DOS_BUILD_DIR%"                     > NUL
@IF NOT EXIST "%DOS_BUILD_DIR%\main\component.mk"   COPY component.mk        "%DOS_BUILD_DIR%\main"                > NUL
@IF NOT EXIST "%DOS_BUILD_DIR%\sdkconfig"           COPY %CONFIG%.txt        "%DOS_BUILD_DIR%\sdkconfig"           > NUL

@REM Always keep this file up to date from library updates
@COPY mainCMakeLists.txt  "%DOS_BUILD_DIR%\main\CMakeLists.txt" > NUL

@REM Create a batch file link to the menuconfig inside the build folder
@IF EXIST "%DOS_BUILD_DIR%\menuconfig.bat"          GOTO CONFIGDONE
@ECHO @CALL  "%TOOLS_DIR%export.bat" > "%DOS_BUILD_DIR%\menuconfig.bat"     
@ECHO python "%TOOLS_DIR%tools\idf.py" menuconfig -DIDF_TARGET=%CHIPTYPE% >> "%DOS_BUILD_DIR%\menuconfig.bat"
:CONFIGDONE

@POPD

@REM Copy in the target C file ...
@COPY "%OUT_DIR%%TARGET%.c" "%DOS_BUILD_DIR%\main\esp-project.c"   > NUL

@REM Delete any previous output ...
@DEL "%DOS_BUILD_DIR%\build\esp-project.elf"    > NUL 2> NUL

@REM Get the ESP IDF Version ...
@PUSHD "%TOOLS_DIR%"
@FOR /F "tokens=*" %%g IN ('git describe') do @(SET IDFVERSION=%%g)
@ECHO IDF Version: %IDFVERSION% ...
@POPD

@REM Do the build ...
@PUSHD "%DOS_BUILD_DIR%"
@CALL  "%TOOLS_DIR%export.bat"

@ECHO Target: %CHIPTYPE% ...

@IF "%IDFVERSION:~1,1%"=="4" (GOTO BUILDV4) ELSE (GOTO BUILDV5)

:BUILDV4
@idf.py build -DIDF_TARGET=%CHIPTYPE%
GOTO BUILDDONE

:BUILDV5
@idf.py --no-hints build -DIDF_TARGET=%CHIPTYPE%
GOTO BUILDDONE

:BUILDDONE

@POPD

@REM Test for the existance of the output file ...
@IF EXIST "%DOS_BUILD_DIR%\build\esp-project.elf" GOTO SUCCESS
@ECHO.
@ECHO Build Failed.
@EXIT 1

:SUCCESS
@REM Copy the output file to the source location ...
@COPY "%DOS_BUILD_DIR%\build\esp-project.elf" "%OUT_DIR%%TARGET%.elf"  > NUL
@ECHO.

@ECHO Get Project Build Statistics
@PUSHD "%DOS_BUILD_DIR%"

@IF "%IDFVERSION:~1,1%"=="4" (GOTO SIZEV4) ELSE (GOTO SIZEV5)

:SIZEV4
@idf.py size
GOTO SIZEDONE

:SIZEV5
@idf.py --no-hints size
GOTO SIZEDONE

:SIZEDONE
@POPD

@ECHO Build completed successfully 

@EXIT 0



