#ifndef _ILI9341_driver_h
    #define _ILI9341_driver_h

    #include <stdint.h>

    void ILI9341_Init();

    void draw_Square(uint16_t start_col, uint16_t end_col, uint16_t start_row, uint16_t end_row, char color);
    void fill_screen(char color);
#endif