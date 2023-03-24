# cavaOS
An operating system for running Cava applications. WIP

## Dependencies
- `i686-elf-*` [GCC Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
- `nasm` [Netwide Assembler](https://nasm.us)
- `libisoburn` for grub-mkrescue
- `grub-legacy` (can work with grub2 with small tweaks to the makefile)

## Milestones

### Hello, World!
- [x] Bootloader
- [x] Formatted printing
- [x] GDT set properly
- [x] C++ Constructors/Destructors called

### Heap, Heap, Hurrah!
- [ ] Dynamic memory management
- [ ] Ports

### Stop Interrupting Me!
- [ ] IDT set properly
- [ ] Interrupt support in C++

### Interaction time!
- [ ] Driver abstraction
- [ ] PS/2 Keyboard driver
- [ ] Timer driver

### Wow, such hard!
- [ ] IDE driver & partitions
- [ ] FAT32 driver

### Oh how standard...
- [ ] Standard library
	- [ ] Text I/O
	- [ ] Filesystem
    - [ ] STL (at least vector, map, set)

### Found a seashell!
- [ ] Simple shell
- [ ] Filesystem utilities

### Sailin' to the Port, baby!
- [ ] `editone` text editor
- [ ] `casm` assembler
- [ ] `cald` linker
- [ ] `tucl` compiler
- [ ] `kre` runtime
