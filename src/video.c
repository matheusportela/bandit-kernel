#include "video.h"

uint16_t *vga_screen;
int vga_cur_x = 0;
int vga_cur_y = 0;

/**
 * Init vga_screen pointer and clear screen
 */
void vga_init()
{
    vga_screen = (unsigned short *)VGA_MEM_START;
    vga_clear();
}

/**
 * Clear screen
 */
void vga_clear()
{
    unsigned int j;
    
    for (j = 0; j < VGA_SIZE; j += 2)
        vga_write_char(' ');
        
    vga_cur_x = 0;
    vga_cur_y = 0;
}

/**
 * Write a character on the screen
 */
void vga_write_char(char c)
{
    uint16_t *vga_ptr;
    
    /* Evaluate special characters */
    switch (c)
    {
        case '\n':
            vga_cur_x = 0;
            ++vga_cur_y;
            break;
        case '\r':
            vga_cur_x = 0;
            break;
        case '\t':
            vga_cur_x += TAB_SPACING;
            break;
        case '\b':
            if (vga_cur_x != 0)
                --vga_cur_x;
            break;
        default:
            vga_ptr = vga_screen + (vga_cur_y*VGA_COLS + vga_cur_x);
            *vga_ptr = (COLOR_LIGHT_GRAY << 8)|c;
            ++vga_cur_x;
            break;
    }
    
    /* End of the line */
    if (vga_cur_x >= VGA_COLS)
    {
        ++vga_cur_y;
        vga_cur_x = 0;
    }
}

/**
 * Write string on the screen
 */
void vga_write(char *str)
{
    unsigned int i;
    for (i = 0; str[i] != '\0'; ++i)
        vga_write_char(str[i]);
}
