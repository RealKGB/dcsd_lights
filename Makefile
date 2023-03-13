CC = gcc
TARGET = dcsd_lights

CFLAGS ?=
LDFLAGS ?=

ifeq ($(shell uname), Darwin)
	CFLAGS += -c -Wall -I. -I/usr/local/Cellar/libftdi/*/include/libftdi1/ -g
	LDFLAGS += -L/usr/local/Cellar/libftdi/*/lib -L/usr/local/Cellar/libusb/1.0.22/lib -lftdi1 -lusb-1.0
endif

OBJECTS = program.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean : 
	rm -rf $(OBJECTS) $(TARGET)
