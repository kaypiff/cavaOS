
#include <sys/tty.hh>

namespace cava::sys::tty {

    colour fgcolour = colour::light_grey;
    colour bgcolour = colour::black;
    size_t column = 0, row = 0;

    void scroll()
    {
        for (size_t y = 1; y < VGA_HEIGHT; y++) {
            for (size_t x = 0; x < VGA_WIDTH; x++)
                vga_buffer[x + (y-1) * VGA_WIDTH] = vga_buffer[x + y * VGA_WIDTH];
        }

        clear_row(VGA_HEIGHT - 1);
    }

    void clear_row(size_t n)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
            write_char(' ', x, n);
    }

}
