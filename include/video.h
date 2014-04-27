#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <stdint.h>
#include <io.h>

#define VGA_MEM_START 0xb8000
#define VGA_COLS 80
#define VGA_ROWS 25
#define VGA_FIELDS 2
#define VGA_SIZE (VGA_COLS*VGA_ROWS)
#define VGA_MEM_SIZE (VGA_COLS*VGA_ROWS*VGA_FIELDS)

#define COLOR_BLACK 0X00
#define COLOR_BLUE 0X01
#define COLOR_GREEN 0X02
#define COLOR_CYAN 0X03
#define COLOR_RED 0X04
#define COLOR_MAGENTA 0X05
#define COLOR_BROWN 0X06
#define COLOR_LIGHT_GRAY 0x07
#define COLOR_DARK_GRAY 0X08
#define COLOR_LIGHT_BLUE 0X09
#define COLOR_LIGHT_GREEN 0X0a
#define COLOR_LIGHT_CYAN 0X0b
#define COLOR_LIGHT_RED 0X0c
#define COLOR_LIGHT_MAGENTA 0X0d
#define COLOR_YELLOW 0X0e
#define COLOR_WHITE 0x0f
#define COLOR_DEFAULT COLOR_LIGHT_GRAY

#define BACKCOLOR_BLACK 0X00
#define BACKCOLOR_BLUE 0X10
#define BACKCOLOR_GREEN 0X20
#define BACKCOLOR_CYAN 0X30
#define BACKCOLOR_RED 0X40
#define BACKCOLOR_MAGENTA 0X50
#define BACKCOLOR_BROWN 0X60
#define BACKCOLOR_LIGHT_GRAY 0x70
#define BACKCOLOR_DARK_GRAY 0X80
#define BACKCOLOR_LIGHT_BLUE 0X90
#define BACKCOLOR_LIGHT_GREEN 0Xa0
#define BACKCOLOR_LIGHT_CYAN 0Xb0
#define BACKCOLOR_LIGHT_RED 0Xc0
#define BACKCOLOR_LIGHT_MAGENTA 0Xd0
#define BACKCOLOR_YELLOW 0Xe0
#define BACKCOLOR_WHITE 0xf0
#define BACKCOLOR_DEFAULT BACKCOLOR_BLACK
#define BACKCOLOR_SECOND_DEFAULT (COLOR_DEFAULT << 4)

#define TAB_SPACING 4

void vga_init();
void vga_clear();
uint16_t* vga_get_cursor();
void vga_move_cursor();
void vga_blink_cursor();
void vga_write_char(char c);
void vga_write(char *str);
void vga_test();

#endif /* _VIDEO_H_ */
