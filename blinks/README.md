A collection of small "blink" apps used to test various boards and toolchains.

mbed-gcc4mbed - Win/Mac/Lin (2012-09-10)
----------------------------------------

This is just a copy of the "samples/Blink" code included in the
[gcc4mbed](https://github.com/adamgreen/gcc4mbed) toolchain.
  
    $ make clean all deploy
    ...
    arm-none-eabi-size Blink.elf
       text	   data	    bss	    dec	    hex	filename
       1672	     12	     40	   1724	    6bc	Blink.elf
    ...
    cp Blink.bin /Volumes/MBED/
    
Then press the reset button to reflash and run the new code.

lpc1769 - Mac (2012-09-11)
--------------------------

Same copy, modified to run on an LPCXpresso 1769, with LED on the P0.22 pin.
Still with mbed.ar linked in as runtime

    $ make clean all deploy
    ...
    arm-none-eabi-size Blink.elf
       text	   data	    bss	    dec	    hex	filename
       1692	     12	     40	   1744	    6d0	Blink.elf

Then put the LPCX in ISP mode (press both buttons, in right order) and do:
    lpc21isp Blink.hex /dev/tty.usbserial-A600K1PM 115200 12000
Finally, press reset to exit ISP mode and launch the new code.
