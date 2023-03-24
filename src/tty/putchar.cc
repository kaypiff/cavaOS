
#include <sys/tty.hh>
#include <termio.hh>

namespace cava {

    int putchar(int ic)
    {
        char c = (char)ic;

        if (c == '\n') {
            sys::tty::column = 0;
            
            if (++sys::tty::row >= VGA_HEIGHT) {
                sys::tty::scroll();
                sys::tty::row = VGA_HEIGHT - 1;
            }

            return ic;
        }

        if (c != 0 && ic != -1)
            sys::tty::write_char((char)ic, sys::tty::column, sys::tty::row);
        
        if (++sys::tty::column >= VGA_WIDTH) {
            sys::tty::column = 0;
            
            if (++sys::tty::row >= VGA_HEIGHT) {
                sys::tty::scroll();
                sys::tty::row = VGA_HEIGHT - 1;
            }
        }

        return ic;
    }
}
