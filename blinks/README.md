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
    arm-none-eabi-objcopy -R .stack -O ihex Blink.elf Blink.hex
    arm-none-eabi-objcopy -O binary Blink.elf Blink.bin
    arm-none-eabi-objdump -d -f -M reg-names-std Blink.elf >LPC176x/Blink.disasm
    cp Blink.bin /Volumes/MBED/
    
Then press the reset button to reflash and run the new code.