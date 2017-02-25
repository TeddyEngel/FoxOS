#include <cstring>

std::size_t strlen(const char* str)
{
	std::size_t len = 0;
	while (str[len])
		len++;
	return len;
}
