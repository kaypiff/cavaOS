
KERNEL := kernel.bin

# Toolchain
CC  := i686-elf-gcc
CXX := i686-elf-g++
LD  := i686-elf-gcc
AS  := nasm

# Flags
FLAGS_CC  := -O2 -Wall -nostdlib
FLAGS_CXX := -O2 -Wall -fno-exceptions -fno-rtti -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-leading-underscore
FLAGS_LD  := -T linker/linker.ld -nostdlib
FLAGS_AS  := -f elf32

# File autodetect
SRC_C   := $(wildcard src/*.c)
SRC_CXX := $(wildcard src/*.cc)
SRC_ASM := $(wildcard src/*.s)

HEADERS := $(wildcard include/*)
SOURCES := $(SRC_C) $(SRC_CXX) $(SRC_ASM)
OBJECTS := $(patsubst src/%,build/%.o,$(SOURCES))

# Objects
build/%.c.o : src/%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS_CC) -c -o $@ $<

build/%.cc.o : src/%.cc
	mkdir -p $(dir $@)
	$(CXX) $(FLAGS_CXX) -c -o $@ $<

build/%.s.o : src/%.s
	mkdir -p $(dir $@)
	$(AS) $(FLAGS_AS) -o $@ $<

# Kernel
$(KERNEL) : $(OBJECTS) $(HEADERS)
	mkdir -p $(dir $@)
	$(LD) $(FLAGS_LD) -o $@ $<
	
.PHONY: all clean

all: $(KERNEL)

clean:
	rm -rf build/* $(KERNEL)
