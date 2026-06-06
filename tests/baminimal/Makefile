# Makefile

all: compile execute clean

compile:
	emex64asm -o badapple src/*.e64 -fno_page_align

execute:
	emex64vm --firmware ./badapple --memory 512

clean:
	rm -rf badapple
