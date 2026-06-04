# Makefile

all: compile execute clean

compile:
	emex64asm -o emex64fw src/*.e64

execute:
	emex64vm --firmware ./emex64fw

clean:
	rm -rf emex64fw
