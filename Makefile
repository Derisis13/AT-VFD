# Credits to Łukasz Podkalicki: https://blog.podkalicki.com/how-to-compile-and-burn-the-code-to-avr-chip-on-linuxmacosxwindows/
MCU=atmega88
F_CPU=8000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mcall-prologues -mmcu=${MCU} -DF_CPU=${F_CPU} -I/usr/lib/avr/include/
TARGET=main
SRCS=main.c PT6302.c PT6302.h

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -p ${MCU} -c usbasp -U flash:w:${TARGET}.hex:i -F -P usb

clean:
	rm -f *.bin *.hex
