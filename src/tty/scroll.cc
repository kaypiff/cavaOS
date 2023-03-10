
#include <sys/tty.hh>
#include <termio.hh>

namespace cava {
    
    void scroll()
    {
        sys::tty::scroll();
    }
}
