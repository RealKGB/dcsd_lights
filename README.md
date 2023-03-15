# dcsd_lights
A simple project to light up the LEDs on the Alex DCSD cable arbitrarily. It should support the DCSD 3.1, or the USB-C version, but mine has not arrived yet so I can't test. If it doesn't, I'll update it to work.
The project is based on Mathieu Hautebas' DCSD_STATUS available on https://github.com/matteyeux/dcsd_status

The Alex DCSD cable is a factory cable used most likely for testing at Foxconn for the Apple devices. The cable features a gray, black, or gold box with 3 LEDs labeled "Pass", "Busy", "Fail", which are colored green, yellow, and red respectively. Some extensive research has been carried out by `lululombard`. His research can be found on <a href = "https://github.com/lululombard/DCSD-reverse-engineering"> DCSD reverse engineering </a>

The cable can be controlled using LibFTDI as demonstrated in the program and in Mathieu and lululombard's examples.

### Prerequisites
Before compiling, install LIBFTDI on your Mac.

```bash
brew install libftdi
brew link libftdi
```

### Compiling
```bash
make
```
### Usage

Once compiled and started, the program ensures you have an Alex connected, then prompts you to enter a number, which corresponds to a given light pattern.

```
1 = green LED
2 = yellow LED
3 = red LED
4 = all LEDs
5+ = any combo, could be one, two, or three LEDs. Changes every time the cable is unplugged and replugged. The program segfaults if you input a number higher than 277
```

  Alternatively, you can pass arguments to it. Passing one number will light that LED until another command is sent to override it. Example: `dcsd_lights 3` will light the red LED, until another command is sent to override it, such as `dcsd_lights 1`, which would then enable the green LED.

  If you add a second number, the LED will enable itself only for however many seconds you passed as the second number. Example:
`dcsd_lights 2 5` will enable the yellow LED, and after 5 seconds it will turn off. Note that other commands in your script will have to wait, so if you need to do something during those 5 seconds, it is advised to use a single number and override it later with `dcsd_lights 0` to turn it off, or another argument of your choice.
### Credits
Special thanks to https://twitter.com/matteyeux and https://twitter.com/lululombard. Base project by https://twitter.com/FCE365.

### Contact me
Twitter: https://twitter.com/ragnarok0273
