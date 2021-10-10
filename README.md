# unicorn_attiny85
 Port of MoodBottle to function with AtTiny85


Pallet Shifting effects designed for maximum portability, using AtTiny85. 

Useful for cosplay, costumes and wearables.


####  Reccomend using Arduino as ISP for programming & burning bootloader to AtTiny85


# Interfacing WS2812b LEDs with AtTiny85 Using FastLED Library.

For sketch to function, AtTiny clock must be set to 16MHz. This can be done by burning the correct bootloader before uploading the sketch. This only needs to be done once.

To set 16MHz internal clock locate the `boards.txt` file, usually found at:

`folder: %USERPROFILE%\AppData\Local\Arduino15\packages\attiny\hardware\avr\1.0.1\boards.txt`

This folder can be easily located by following the "more preferences can be edited directly" link, 
found at the bottom of the preferences menu.


Once file is located, locate the section below starting `attiny.menu.clock.internal8=8 MHz (internal)` 


```
attiny.menu.clock.internal8=8 MHz (internal)
attiny.menu.clock.internal8.bootloader.low_fuses=0xe2
attiny.menu.clock.internal8.bootloader.high_fuses=0xdf
attiny.menu.clock.internal8.bootloader.extended_fuses=0xff
attiny.menu.clock.internal8.build.f_cpu=8000000L
```

Add the text below to this to file, underneath the section above.

```
attiny.menu.clock.internal16=16 MHz (internal)
attiny.menu.clock.internal16.bootloader.low_fuses=0xf1
attiny.menu.clock.internal16.bootloader.high_fuses=0xdf
attiny.menu.clock.internal16.bootloader.extended_fuses=0xff
attiny.menu.clock.internal16.build.f_cpu=16000000L

```

Reboot Arduino IDE, then select correct controller, AtTiny85, and clock speed: "16 MHz (Internal)"

then proceed to "Burn Bootloader"


NOTE:

This action will set internal fuses that need a high voltage reprogrammer to reset.

After completing bootloader burn, upload the sketch in the normal way using Arduino as ISP.
