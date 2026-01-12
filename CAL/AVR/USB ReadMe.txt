To compile to an AVR device using USB you must point the compiler to a different batch file to allow it to include the various USB libraries in the compilation.

Simply click on Build -> Compiler Options.

Click on the AVR -> Default item and then click the save icon at the top right hand side of the window.

Give the new setting a name e.g. AVRUSB and click OK.

Click on the new item AVR -> AVRUSB and ensure that it is ticked as the default compiler for the AVR platform.


Change the compiler location to this.
$(fcddir)AVR\batchfiles\avra_usb.bat


Change the compiler Parameters to one of the following based on your USB type.
$(chip:l) "$(outdir)" "$(target)" Serial "$(compileravr)"
$(chip:l) "$(outdir)" "$(target)" HID "$(compileravr)"


Not Currently Supported

$(chip:l) "$(outdir)" "$(target)" Slave "$(compileravr)"
$(chip:l) "$(outdir)" "$(target)" MIDI "$(compileravr)"

