# Makefile

all: compile execute clean

compile:
	emex64asm -o badapple.o src/*.e64 -fno_page_align
	cat badapple.o ../badapple/vid.bitmask > badapple
	rm badapple.o

execute:
	emex64vm --firmware ./badapple

clean:
	rm -rf badapple
