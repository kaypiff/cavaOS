
#pragma once

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#include <types.hh>

namespace cava::sys::tty {

    struct vga_entry {
        char chr;
        uint8_t colour;
    };

    static inline vga_entry *vga_buffer = (vga_entry *)0xb8000;

    enum class colour {
        black, blue,
        green, cyan,
        red, magenta,
        brown, light_grey,
        dark_grey, light_blue,
        light_green, light_cyan,
        light_red, light_magenta,
        light_brown, white,
    };
    
    extern colour fgcolour, bgcolour;
    extern size_t column, row;

    static inline uint8_t termcolour()
    {
        return (uint8_t)fgcolour | ((uint8_t)bgcolour << 4);
    }

    static inline void setfgcolour(colour c)
    {
        fgcolour = c;
    }

    static inline void setbgcolour(colour c)
    {
        bgcolour = c;
    }

    static inline void write_char(char c, size_t x, size_t y)
    {
        vga_buffer[y * VGA_HEIGHT + x] = { .chr = c, .colour = termcolour() };
    }
    
    void scroll();
    void clear_row(size_t n);

}
