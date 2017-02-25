#include <climits>
#include <cstdarg>
#include <cstdio>
#include <cstring>

static bool print(const char* data, std::size_t length)
{
    const unsigned char* bytes = (const unsigned char*) data;
    for (std::size_t i = 0; i < length; i++)
        if (putchar(bytes[i]) == EOF)
            return false;
    return true;
}

int printf(const char* format, ...)
{
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        std::size_t maxrem = INT_MAX - written;

        if (format[0] != '%' || format[1] == '%') {
            if (format[0] == '%')
                format++;
            std::size_t amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            if (maxrem < amount) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, amount))
                return -1;
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if (*format == 'c')
        {
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if (!maxrem) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(&c, sizeof(c)))
                return -1;
            written++;
        }
        else if (*format == 'd')
        {
            format++;
            int d = va_arg(parameters, int);
            if (!maxrem)
            {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            putint(d);
            written++;
        }
        else if (*format == 's')
        {
            format++;
            const char* str = va_arg(parameters, const char*);
            std::size_t len = strlen(str);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(str, len))
                return -1;
            written += len;
        } 
        else
        {
            format = format_begun_at;
            std::size_t len = strlen(format);
            if (maxrem < len) {
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if (!print(format, len))
                return -1;
            written += len;
            format += len;
        }
    }

    va_end(parameters);
    return written;
}
