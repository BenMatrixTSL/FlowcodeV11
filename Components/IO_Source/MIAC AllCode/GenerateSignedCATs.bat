"C:\Program Files (x86)\Windows Kits\10\bin\10.0.19041.0\x86\inf2cat" /v /driver:"USBDriver\inf" /os:XP_X86,Vista_X86,Vista_X64,7_X86,7_X64,8_X86,8_X64


PAUSE

"C:\Program Files (x86)\Windows Kits\10\bin\10.0.18362.0\x86\signtool" sign /ac "\\IRONMAN-PC2\Dev\Drivers\Certificate\GlobalSign Root CA.crt" /a /tr http://rfc3161timestamp.globalsign.com/advanced /td SHA256 "USBDriver\inf\*.cat"

PAUSE