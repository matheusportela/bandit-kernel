#include <memory.h>

/**
 * Set `count` bytes to `value`, beginning at `dest` memory address.
 * @param dest Initial memory address.
 * @param value Value to be written in memory.
 * @param count Number of bytes to be written in.
 * @return Memory address of written memory.
 */
void *memset(void *dest, int value, unsigned int count)
{
    int i;

    for (i = 0; i < count; ++i)
        i[(int*)dest] = value;

    return dest;
}