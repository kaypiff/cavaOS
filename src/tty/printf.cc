
#include <limits.h>
#include <sys/tty.hh>
#include <termio.hh>
#include <string.hh>

namespace cava {

    int vaprintf(const char *__restrict format, va_list args)
    {
        int written = 0;

        while (*format) {
            size_t maxrem = INT_MAX - written;

            if (format[0] != '%' || format[1] == '%') {
                if (format[0] == '%')
                    format++;
                
                size_t amount = 1;
                while (format[amount] && format[amount] != '%')
                    amount++;
                
                if (maxrem < amount)
                    return -1;
                
                for (size_t i = 0; i < amount; i++)
                    putchar(format[i]);
                
                format += amount;
                written += amount;
                continue;
            }

            const char *format_copy = format++;
            
            switch (*format++) {
            case 'c': {
                char c = (char) va_arg(args, int);

                if (!maxrem)
                    return -1;
                
                putchar(c);
                written++;
                break;
            }
            case 's': {
                const char *s = va_arg(args, const char *);
                size_t len = strlen(s);

                if (maxrem < len)
                    return -1;
                
                for (size_t i = 0; i < len; i++)
                    putchar(s[i]);
                
                written += len;
                break;
            }
            case 'd': {
                int n = va_arg(args, int);

                if (n < 0) {
                    n = -n;
                    putchar('-');
                    written++;
                }

                written += printf("%u", n);
                break;
            }
            case 'u': {
                int n = va_arg(args, int);

                if (n == 0) {
                    putchar('0');
                    break;
                }

                int div = 1000000000, p = 0;

                while (div > 0) {
                    int d = n / div;

                    if (!p && d > 0)
                        p = 1;

                    if (p) {
                        putchar((char)d + '0');
                        written++;
                    }
                    
                    n %= div;
                    div /= 10;
                }

                break;
            }
            default: {
                format = format_copy;
                size_t len = strlen(format);

                if (maxrem < len)
                    return -1;
                
                for (size_t i = 0; i < len; i++)
                    putchar(format[i]);
                
                written += len;
                format += len;
            }
            }
        }

        return written;
    }

    int printf(const char *__restrict format, ...)
    {
        int written;
        va_list args;
        va_start(args, format);
        written = vaprintf(format, args);
        va_end(args);
        return written;
    }
}
