COMMON_OBJECTS  = main.o
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf


button.elf: ${COMMON_OBJECTS} ../11-buzzer-change-tone/buzzer.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ../../demos/lib/libTimer.a

load: button.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

