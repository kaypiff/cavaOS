
#include <sys/tty.hh>
#include <termio.hh>

namespace cava {

    void clear()
    {
        for (size_t y = 0; y < VGA_HEIGHT; y++)
            sys::tty::clear_row(y);
    }
}
