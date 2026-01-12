
@echo off
  setlocal
  set object="%~1%~2.hex"
  set vName=%3
  set n=0
  set ltrs=ABCDEFGHIJKLMNOPQRSTUVWXYZ
:Loop 
  call set ltr=%%ltrs:~%n%,1%%
  set /a n +=1
  vol %ltr%: 2>nul|find /i " %vname%">nul||if %n% lss 26 goto :loop
  if %n% equ 26 (set "ltr="
    echo %vName% board is not connected.
  ) else if [%object%]==[] (echo Please pass a parameter.
  ) else (copy %object% %ltr%:)
  endlocal & set ltr=%ltr%


