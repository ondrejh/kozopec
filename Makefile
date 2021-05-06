TARGET=kozo

MCU        = msp430g2231
TARGETMCU  = F20x2_G2x2x_G2x3x

SOURCES=main.c
MAP=main.map
MAKEFILE=Makefile

RM= rm -rf

GCC_DIR = C:/ti/msp430-gcc/bin
SUPPORT_FILE_DIRECTORY = C:/ti/msp430-gcc/include

DEVICE  = $(MCU)
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb
OBJCOPY = $(GCC_DIR)/msp430-elf-objcopy
SIZEOF  = $(GCC_DIR)/msp430-elf-size

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -Og -Wall -g
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -Wl,-Map,$(MAP),--gc-sections

OBJECTS = $(SOURCES:.c=.o)

Release: all

all: $(TARGET).elf $(TARGET).hex
$(TARGET).elf: $(OBJECTS)
	echo "Linking $@"
	$(CC) $(OBJECTS) $(CFLAGS) $(LFLAGS) -o $@
	echo
	echo ">>> Size of firmware <<<"
	$(SIZEOF) $(TARGET).elf
	echo
%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

cleanRelease: clean

clean:
	$(RM) $(OBJECTS)
	$(RM) *.elf
	$(RM) *.hex

debug: all
	$(GDB) $(DEVICE).out

program:
	mspdebug rf2500 "prog $(TARGET).hex"

program_win:
	C:/ti/MSPFlasher_1.3.17/MSP430Flasher -i TIUSB -m SBW2 -g -n $(TARGETMCU) -e ERASE_ALL -w $(TARGET).hex -v -z [VCC]
