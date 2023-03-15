// https://github.com/matteyeux/dcsd_status

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <ftdi.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

bool isInteger(char* str) {
    // Check if the string is empty or null
    if (str == NULL || *str == '\0') {
        return false;
    }
    
    // Check if the string starts with a minus sign
    if (*str == '-') {
        ++str;
    }
    
    // Loop through the remaining characters
    while (*str != '\0') {
        // Check if the character is not a digit
        if (!isdigit(*str)) {
            return false;
        }
        ++str;
    }
    
    // All characters are digits, so the string is an integer
    return true;
}


int lightOn (int led){
    struct ftdi_context *ftdi;
    int fopen;
    long int tab[5] = {0xF0, 0xF2, 0xF8, 0xF1, 0xFB};
    unsigned char buf[1];
    static int led_status = -1;
    
    if (led == led_status){
        return 0;
    } else {
        led_status = led;
    }
    
    if (led == 69){
        printf("geosn0w is a dumbass\n");
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

int main(int argc, char **argv){
	if (argc > 3){
		printf("Invalid arguments");
    } else if (argc == 2){
        if(isInteger(argv[1])){
            lightOn(atoi(argv[1]));
        }
        else if(strcmp(argv[1], "--help") == 0){
            printf("\nProgram to interface with the lights on the Alex DCSD cables.\nBased on @matteyeux's DCSD_STATUS project.\nUpdated fork of geosn0w's thing, without the useless christmas light pattern.\n\n");
            printf("   To enable LEDs in a script, simply pass the integer value that you would enter. Example: 'dcsd_lights 2' will turn on the yellow LED.\n");
            printf("   You can also have them enabled for a set amount of time - just add the amount of time in seconds you want to sleep after. Example: 'dcsd_lights 2 5' will turn on the yellow LED, and then turn it off after 5 seconds.\n");
            printf("   A key for what number corresponds to which light is below:\n\n");
            printf("0 = all LEDs off\n1 = green LED\n2 = yellow LED\n3 = red LED\n4 = all on\n5+ = any combo, could be one, two, or three LEDs. Changes every time the cable is unplugged and replugged. The program segfaults if you input a number higher than 277\n");
        }
	} else if (argc == 3){
		lightOn(atoi(argv[1]));
        sleep(atoi(argv[2]));
        lightOn(0);
	} else {
    int ledNumber = 0;
    
	printf("\nProgram to interface with the lights on the Alex DCSD cables.\nBased on @matteyeux's DCSD_STATUS project.\nUpdated fork of geosn0w's thing, without the useless christmas light pattern.\nSee --help for more details.\n\n");
    printf("0 = all LEDs off\n1 = green LED\n2 = yellow LED\n3 = red LED\n4 = all on\n5+ = any combo, could be one, two, or three LEDs. Changes every time the cable is unplugged and replugged. The program segfaults if you input a number higher than 277\n\n");
    do {
        lightOn(ledNumber);
        printf("> ");
    } while (scanf("%d", &ledNumber)); //Get user input
        return 0;
    }
}
