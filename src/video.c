#include <video.h>

uint16_t *vga_screen;
int vga_cur_x = 0;
int vga_cur_y = 0;

void vga_init()
{
    vga_screen = (unsigned short *)VGA_MEM_START;
    vga_clear();
}

void vga_clear()
{
    unsigned int j;
    
    for (j = 0; j < VGA_SIZE; j += 2)
        vga_write_char(' ');
        
    vga_cur_x = 0;
    vga_cur_y = 0;
    vga_move_cursor();
}

uint16_t* vga_get_cursor()
{
    return (vga_screen + (vga_cur_y*VGA_COLS + vga_cur_x));
}

void vga_blink_cursor()
{
    uint16_t *vga_ptr = vga_get_cursor();
    char c = *vga_ptr&0xFF;
    int backcolor = (*vga_ptr) >> 12;
    
    /* Blink by changing the backcolor of the current cursor position */
    if (backcolor == BACKCOLOR_DEFAULT)
        *vga_ptr = ((BACKCOLOR_SECOND_DEFAULT|COLOR_DEFAULT) << 8)|c;
    else
        *vga_ptr = ((BACKCOLOR_DEFAULT|COLOR_DEFAULT) << 8)|c;
}

void vga_move_cursor()
{
    unsigned int temp = (vga_cur_y*VGA_COLS + vga_cur_x);
    
    /* Send interrupt to VGA driver */
    outb(0x3d4, 14);
    outb(0x3d5, temp >> 8);
    outb(0x3d4, 15);
    outb(0x3d5, temp);
}

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
            vga_ptr = vga_get_cursor();
            *vga_ptr = (COLOR_DEFAULT << 8)|c;
            ++vga_cur_x;
            break;
    }
    
    /* End of the line */
    if (vga_cur_x >= VGA_COLS)
    {
        ++vga_cur_y;
        vga_cur_x = 0;
    }
    
    vga_move_cursor();
}

void vga_write(char *str)
{
    unsigned int i;
    for (i = 0; str[i] != '\0'; ++i)
        vga_write_char(str[i]);
}

void vga_test()
{
    unsigned int i;
    
    for (i = 0x20; i < 0x7F; ++i)
        vga_write_char(i);
}
