#include <cstdio>

int putint(int d)
{
    bool isNegative = false;

    if (d == 0)
    {
        putchar('0');
        return d;
    }
    else if (d < 0)
    {
        isNegative = true;
        putchar('-');
        d = -d;
    }

    int index = 0;
    int characters[64] = { 0 };
    while (d != 0 && index < 64)
    {
        int lastDigit = d % 10;
        characters[index] = '0' + lastDigit;
        ++index;
        d /= 10;
    }

    --index;
    while (index >= 0 && index < 64)
    {
        putchar(characters[index]);
        --index;
    }
    return d;
}
