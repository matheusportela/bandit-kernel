#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <stdint.h>

#define VGA_MEM_START 0xb8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define VGA_FIELDS 2
#define VGA_SIZE (VGA_COLS*VGA_ROWS)
#define VGA_MEM_SIZE (VGA_COLS*VGA_ROWS*VGA_FIELDS)

#define COLOR_LIGHT_GRAY 0x07
#define COLOR_WHITE 0xF0

#define TAB_SPACING 4

void vga_init();
void vga_clear();
void vga_write_char(char c);
void vga_write(char *str);

#endif /* _VIDEO_H_ */
