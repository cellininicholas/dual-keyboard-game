# dual-keyboard-game
Play keyboard games together


## Installation
### Wiring

I had QUITE a hard time getting both displays to work at the same time, I ended up just trying lots of different pin combinations.
The pins below seem to work!

My methodology was to make sure the RS pins were on PWM ports and try different things from there.
Also, pins 5,6,7 seemed to work consistently with 1 display.
```
const int D1_PIN_E = 7, D1_PIN_RW = 8, D1_PIN_RS = 5;
const int D2_PIN_E = 3, D2_PIN_RW = 4, D2_PIN_RS = 6;

// 7 and 8 are digital and NOT PWM
// 3 is PWN, 4 is digital and NOT PWM
// 5 and 6 are BOTH PWM
```

### USB Host Shield
Download the USB Host Shield Library
https://github.com/felis/USB_Host_Shield_2.0

#### Using with Arduino Mega 2560
https://forum.arduino.cc/index.php?topic=176975.0

#### Important learnings about using the USB Host Shield with Keyboards

If you are using a keyboard that has a built in USB Hub (Female USB plugs on the keyboard itself)
Make sure you include and use the "usbhub.h" header and USBHub class, otherwise the keyboard may not be recognised.
It would perhaps be fine not to include "usbhub.h" if the keyboard has no USB plugs on it.
```
#include <usbhub.h>

USB     Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

if (Usb.Init() == -1) Serial.println("OSC did not start.");
delay( 200 );
if (!Hid.SetReportParser(0, &KbdParser)) Serial.println("SetReportParser error");
```

### SD Card
An SD Card will hold a number of word lists, because the program memory isn't large enough to hold them all.
Additionally, I have split a number of word lists into multiple files, so a huge file doesn't have to be loaded into memory

```
# Splitting a .txt doc into multiple files
# https://stackoverflow.com/questions/25249516/split-text-file-into-smaller-multiple-text-file-using-command-line
gsplit -l 128 -d --additional-suffix=.txt words-8_0-spread.txt w
```

## Word Dictionaries
### Manually Removed Words
#### Innapropriate
"womanise","womanize","whoppers","whoredom","whoreson","whitiest","virilise","virilize","uteritis","vaginant","knockers"

#### Obscure
"windocks","zaddikim","wudjulas","xenurine","xeraphin","xylocarp","yakhdans","yamalkas","yarmelke","yashmaks","yataghan","aborigen","pussleys","pusslies"

## Memory Issues
### Uno
Sketch uses 22844 bytes (70%) of program storage space. Maximum is 32256 bytes.
Global variables use 1362 bytes (66%) of dynamic memory, leaving 686 bytes for local variables. Maximum is 2048 bytes.

Sketch uses 48386 bytes (150%) of program storage space. Maximum is 32256 bytes.
Global variables use 26338 bytes (1286%) of dynamic memory, leaving -24290 bytes for local variables. Maximum is 2048 bytes.

Using PROGMEM
Sketch uses 48386 bytes (150%) of program storage space. Maximum is 32256 bytes.
Global variables use 21798 bytes (1064%) of dynamic memory, leaving -19750 bytes for local variables. Maximum is 2048 bytes.

## DEPRECATED Instructions
### PS2 Keyboard Library
Download the PS2 Keyboard library
https://github.com/PaulStoffregen/PS2Keyboard

Place the downloaded 'PS2Keyboard' folder into the 'libraries' folder inside your Arduino Sketchbook folder...
~/Documents/Arduino ( <- default location, otherwise [Arduino -> Preferences] )


This will allow your Arduino sketches to find the library by just including the lib like so:
#include <PS2Keyboard.h>

#### PS2 Wiring

The keyboard's clock signal must connect to an interrupt pin. The data signal may connect to any pin, but do not use the pin with an LED connected to ground because the LED current will interfere with the data signal.

Interupt Pins
Uno, Nano, Mini, other 328-based: 2, 3
Mega, Mega2560, MegaADK: 2, 3, 18, 19, 20, 21

https://www.pjrc.com/teensy/td_libs_PS2Keyboard.html
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
