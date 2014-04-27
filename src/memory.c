#include <memory.h>

unsigned char* memory_copy(unsigned char *dest, unsigned char *src, int count)
{
    int i;
    
    for (i = 0; i < count; ++i)
        dest[i] = src[i];
        
    return dest;
}
