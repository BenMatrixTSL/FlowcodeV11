REM CRC: 54CD51B8F484283E91B3AD9DE6F4F50C418D34178E0D3D0BD2659E1DA9D69F58D3529BB9468CFC85641793EB31F94A5FFDAF254055AA86A84DE7CC2C2B62544EA5031FD5F734A12219A4FB808A9F55649A0D46BD3B6AACB92DE4D84759EBB5079CA9DA2D2BBCDAE2A4D1C56CD1580BF592D3B3FD9EE90C5974272EC426D793A1AFE86FBDB7D736D8673CE585EC070B87491F441E1C9BB7FB5F3ECAD07D3BE6B346BB010096F343D3261FF4042EDA9A4E3FB62EBE9DD4F0911BC1411822B9A04BC2856CDC24100DB22C3050DA273BE4EE7DFC48FBC2CCDAA60362CA7E4DC0F30221D4703A769EA3E3B64C1696A7E966BD4B005A56FBFB0362
REM REVISION: 1.0
REM GUID: 868F3881-DC22-4531-8E0A-50426848D1C1
REM DATE: 08\08\2022
REM DIR: FCD\PIC16\batchfiles\pic16_C30_link.bat
@REM expected parameters are...
@REM "$(compilerpic16)" "$(outdir)$(target)" $(chip:u) $(family)
@REM   %1 = long compiler path
@REM   %2 = long filename (without extension)
@REM   %3 = device name
@REM   %4 = family name (i.e. PIC24F, PIC24H, dsPIC30F, dsPIC33F)

@SET MX_COMPILER=%~1

@set temppath=%path%

@path=%MX_COMPILER%\bin;

@IF %4==24F xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24F\gld\p%3.gld",-o%2.cof
@IF %4==24E xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24E\gld\p%3.gld",-o%2.cof
@IF %4==24H xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\PIC24H\gld\p%3.gld",-o%2.cof
@IF %4==30F xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC30F\gld\p%3.gld",-o%2.cof
@IF %4==33F xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC33F\gld\p%3.gld",-o%2.cof
@IF %4==33E xc16-gcc -omf=coff -Wl,%2.o,-L"%MX_COMPILER%C_tools\lib",--heap=0,--report-mem,--script="%MX_COMPILER%Support\dsPIC33E\gld\p%3.gld",-o%2.cof

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



