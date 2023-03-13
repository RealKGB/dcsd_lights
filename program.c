// https://github.com/matteyeux/dcsd_status

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ftdi.h>

int lightOn (int led);
int ledNumber = 0;

int lightOn (int led){
    struct ftdi_context *ftdi;
    int fopen;
    long int tab[5] = {0xF0, 0xF2, 0xF8, 0xF1, 0xFB};
    unsigned char buf[1];
    static int led_status = -1;
    
    if (led == led_status)
    {
        return 0;
    } else {
        led_status = led;
    }
    
    ftdi = ftdi_new();
    
    if (ftdi == 0){
        fprintf(stderr, "\n[!] The ftdi_new failed\n");
        return -1;
    }
    
    fopen = ftdi_usb_open(ftdi, 0x0403, 0x8a88);
    
    if (fopen < 0){
        fprintf(stderr, "\n[!] Cannot find a connected DCSD Cable. Please plug it in and try again!\n");
        exit(EXIT_FAILURE);
    }
    
    fopen = ftdi_set_bitmode(ftdi, tab[led], BITMODE_CBUS);
    
    if (fopen < 0){
        ftdi_get_error_string(ftdi);
        ftdi_usb_close(ftdi);
        ftdi_free(ftdi);
        exit(-1);
    }
    fopen = ftdi_read_pins(ftdi, &buf[0]);
    
    if (fopen < 0){
        ftdi_usb_close(ftdi);
        ftdi_free(ftdi);
        exit(-1);
    }
    ftdi_usb_close(ftdi);
    ftdi_free(ftdi);
    
    return 0;
}

int main()
{
    printf("Program to interface with the lights on the Alex DCSD cables.\nBased on @matteyeux's DCSD_STATUS project.\nUpdated fork of geosn0w's thing, without the useless christmas light pattern.\n\n");
    printf("1 = green LED\n2 = yellow LED\n3 = red LED\n4 = all on\n5 = green and yellow LEDs\n7 = yellow and green LEDs\n10 = red and green LEDs\n\n");
    do {
        printf("Turn on: ");
        lightOn(ledNumber);
        
        /*
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
         */
        
    } while (scanf("%d", &ledNumber)); //Get user input
    
	return 0;
}
