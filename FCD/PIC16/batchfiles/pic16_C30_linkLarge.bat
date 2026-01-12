REM CRC: 54CD51B8F484283E91B3AD9DE6F4F50C418D34178E0D3D0BD2659E1DA9D69F58D3529BB9468CFC85641793EB31F94A5FFDAF254055AA86A84DE7CC2C2B62544E406B9EA7386D3B92FEE9D29B9F34F8E6F6A4CCB7873802B223E4F4A1008A3591B1A9EACCE460CD7E52657CD1D71BE0544C8FC9214E5E1424711B8143522C2B698D27A320FF9121E4CE65F245857889C09F0CA2646A2959D519E21D712E695CF242F74606D391DF23BBB578CF46013BD78528D507427B86D3712788D9C8DD95A9B6D2FC7620C63BB8573027F8A99AB52722A50E3C987EEFC52C3050DA273BE4EE7DCFA1DC668E77ACE9ECF6B589768B3D9BEAA63716679FE5AFA22E870078457321B85372DCE0C3F0
REM REVISION: 1.0
REM GUID: A71233A8-E9BC-43AA-890B-A6B6E095A1DE
REM DATE: 05\09\2023
REM DIR: FCD\PIC16\batchfiles\pic16_C30_linkLarge.bat
@REM expected parameters are...
@REM "$(compilerpic16)" "$(outdir)$(target)" $(chip:u) $(family)
@REM   %1 = long compiler path
@REM   %2 = long filename (without extension)
@REM   %3 = device name
@REM   %4 = family name (i.e. PIC24F, PIC24H, dsPIC30F, dsPIC33F)

@SET MX_COMPILER=%~1

@set temppath=%path%

@path=%MX_COMPILER%\bin;

@IF %4==24F xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24F\gld\p%3.gld",-o%2.cof
@IF %4==24E xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24E\gld\p%3.gld",-o%2.cof
@IF %4==24H xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24H\gld\p%3.gld",-o%2.cof
@IF %4==30F xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC30F\gld\p%3.gld",-o%2.cof
@IF %4==33F xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC33F\gld\p%3.gld",-o%2.cof
@IF %4==33E xc16-gcc -omf=coff -mlarge-code -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC33E\gld\p%3.gld",-o%2.cof

@GOTO DONE

:DONE

@IF %ERRORLEVEL% NEQ 0 GOTO Error1
@ECHO Generating HEX file
xc16-bin2hex -omf=coff %2.cof


@IF %ERRORLEVEL% NEQ 0 GOTO Error2
@ECHO Generating Assembler file
xc16-objdump -omf=coff -S %2.cof > %2.asm


@ECHO.
@ECHO HEX file creation successful!
@path=temppath
@EXIT 0


:Error1
@ECHO.
@ECHO Error returned from [xc16-gcc.exe]
@GOTO Error

:Error2
@ECHO.
@ECHO Error returned from [xc16-bin2hex.exe]
@GOTO Error

:Error
@path=temppath
@EXIT 1



