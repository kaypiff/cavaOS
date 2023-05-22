
KERNEL := kernel.bin
ISO    := cavaos.iso

# Toolchain
CC  := $(shell which i686-elf-gcc || (echo i686-elf-gcc not found in PATH! && exit 1))
CXX := $(shell which i686-elf-g++ || (echo i686-elf-g++ not found in PATH! && exit 1))
LD  := $(CC)
AS  := $(shell which nasm || (echo nasm not found in PATH! && exit 1))

# Flags
FLAGS_CC  := -O2 -Wall -nostdlib -Iinclude -std=c99
FLAGS_CXX := -O2 -Wall -fno-exceptions -fno-rtti -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-leading-underscore -Iinclude -std=c++20
FLAGS_LD  := -T linker/linker.ld -nostdlib
FLAGS_AS  := -f elf32

# File autodetect
SRC_C   := $(shell find src -name '*.c')
SRC_CXX := $(shell find src -name '*.cc')
SRC_ASM := $(shell find src -name '*.s')

CRTI     := ctors/crti.o
CRTBEGIN := $(shell $(CC) $(FLAGS_CC) -print-file-name=crtbegin.o)
CRTEND   := $(shell $(CC) $(FLAGS_CC) -print-file-name=crtend.o)
CRTN     := ctors/crtn.o

HEADERS := $(shell find include -type f)
SOURCES := $(SRC_C) $(SRC_CXX) $(SRC_ASM)
OBJECTS := $(CRTI) $(CRTBEGIN) $(patsubst src/%,build/%.o,$(SOURCES)) $(CRTEND) $(CRTN)

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

ctors/%.o : ctors/%.s
	$(AS) $(FLAGS_AS) -o $@ $<

# Kernel
$(KERNEL) : $(OBJECTS) $(HEADERS)
	mkdir -p $(dir $@)
	$(LD) $(FLAGS_LD) -o $@ $(OBJECTS)

.PHONY: all clean run

$(ISO): $(KERNEL)
	cp $< dist/boot/kernel.bin
	grub-mkrescue -o $@ dist

all: $(ISO)

run: all
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -rf build/* $(KERNEL)
