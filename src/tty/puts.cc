
#include <termio.hh>

namespace cava {

    int puts(const char *__restrict str)
    {
        return printf("%s\n", str);
    }
}
