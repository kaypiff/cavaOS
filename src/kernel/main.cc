
#include <sys/gdt.hh>
#include <termio.hh>

using namespace cava;

sys::gdt kernel_gdt;

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
    init_gdt();

    printf("Hello, World!");
    for (;;);
}
