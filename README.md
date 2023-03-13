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

After the Christmas Light Pattern procedure, you can specify the number of the LED you want to light up.
```
1 = green LED
2 = yellow LED
3 = red LED
4 = all LEDs
5 = green and yellow LEDs
6 = red LED
7 = yellow and green LEDs
8 = red and yellow LEDs
9 = red LED
10 = red and green LEDs
11 = yellow and green LEDs
12+ = all LEDs
```
### Credits
Special thanks to https://twitter.com/matteyeux and https://twitter.com/lululombard. Base project by https://twitter.com/FCE365.

### Contact me
Twitter: https://twitter.com/ragnarok0273
