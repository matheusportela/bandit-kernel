#include <video.h>

uint16_t *vga_screen_ptr;
int vga_cur_x = 0;
int vga_cur_y = 0;

/**
 * Initialize VGA cursors and screen.
 */
void vga_init()
{
    vga_screen_ptr = (unsigned short *)VGA_MEM_START;
    vga_clear();
}

/**
 * Completely clear the screen with spaces.
 */
void vga_clear()
{
    unsigned int j;
    
    for (j = 0; j < VGA_SIZE; j += 2)
        vga_write_char(' ');
        
    vga_cur_x = 0;
    vga_cur_y = 0;
    vga_move_cursor();
}

/**
 * Calculate current VGA memory address being pointer by the cursor.
 * @return 16-bit memory address.
 */
uint16_t* vga_get_cursor()
{
    return (vga_screen_ptr + (vga_cur_y*VGA_COLS + vga_cur_x));
}

/**
 * Toggle cursor color for blinking effect.
 */
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

/**
 * Send new position for VGA cursor via driver interruption.
 */
void vga_move_cursor()
{
    unsigned int temp = (vga_cur_y*VGA_COLS + vga_cur_x);
    
    /* Send interrupt to VGA driver */
    outb(0x3d4, 14);
    outb(0x3d5, temp >> 8);
    outb(0x3d4, 15);
    outb(0x3d5, temp);
}

/**
 * Write a single char on the current VGA cursor position.
 * @param c Character to be displayed.
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
            vga_ptr = vga_get_cursor();
            *vga_ptr = (COLOR_DEFAULT << 8)|c;
            ++vga_cur_x;
            break;
    }
    
    /* End of screen */
    if (vga_cur_x >= VGA_COLS)
    {
        ++vga_cur_y;
        vga_cur_x = 0;
    }
    
    vga_move_cursor();
}

/**
 * Write a string to the current VGA cursor position.
 * @param str String pointer.
 */
void vga_write(char *str)
{
    unsigned int i;
    for (i = 0; str[i] != '\0'; ++i)
        vga_write_char(str[i]);
}

/**
 * Write printable characters on the screen for testing purposes.
 */
void vga_test()
{
    unsigned int i;

    vga_write("VGA Test\n");
    
    for (i = 0x20; i < 0x7F; ++i)
        vga_write_char(i);
}