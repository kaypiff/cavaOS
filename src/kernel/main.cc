/* Call global C++ constructors */
extern "C" void (*ctors_begin)(void);
extern "C" void (*ctors_end)(void);
void call_constructors()
{
    for (auto ctor = ctors_begin; ctor != ctors_end; ctor++)
        ctor();
}


extern "C" void kernel_main()
{
    call_constructors();
    for (;;);
}
