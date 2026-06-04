# Makefile

all: compile execute clean

compile:
	emex64asm -o emex64fw src/*.e64

execute:
	emex64vm --firmware ./emex64fw --memory 1 # necessary to be compatible with 1MB machines

clean:
	rm -rf emex64fw
