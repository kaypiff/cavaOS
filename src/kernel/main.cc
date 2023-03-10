
#include <sys/gdt.hh>
#include <termio.hh>

using namespace cava;

sys::gdt kernel_gdt;

/* Call global C++ constructors */
extern "C" void (*ctors_begin)(void);
extern "C" void (*ctors_end)(void);
void call_constructors()
{
    for (auto ctor = ctors_begin; ctor != ctors_end; ctor++)
        ctor();
}

void init_gdt()
{
    /* Null, Kernel Code, Kernel Data, User Code, User Data */
    kernel_gdt.encode(0, 0, 0, 0);
    kernel_gdt.encode(0, 0xfffff, 0x9a, 0xc);
    kernel_gdt.encode(0, 0xfffff, 0x92, 0xc);
    kernel_gdt.encode(0, 0xfffff, 0xfa, 0xc);
    kernel_gdt.encode(0, 0xfffff, 0xf2, 0xc);

    kernel_gdt.load();
}

extern "C" void kernel_main()
{
    call_constructors();
    init_gdt();

    printf("Hello, World!");
    for (;;);
}
