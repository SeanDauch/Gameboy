#include <stdint.h>
#include "SPI_driver.h"
#include "ILI9341_driver.h"
#include "Delay.h"
#include "main.h"

#define GPIOA_Base 0x40020000
#define GPIOA_MODER *((volatile uint32_t*)(GPIOA_Base + 0x00))
#define GPIOA_OSPEEDR *((volatile uint32_t*)(GPIOA_Base + 0x08))
#define GPIOA_ODR *((volatile uint32_t*)(GPIOA_Base + 0x14))

#define SPI1_Base 0x40013000
#define SPI_CR1 *((volatile uint32_t*)(SPI1_Base + 0x00))
#define SPI_SR *((volatile uint32_t*)(SPI1_Base + 0x08))
#define SPI_DR *((volatile uint32_t*)(SPI1_Base + 0x0C))

static void DC_Command(){
    GPIOA_ODR &= ~(1<<1); // Pull PA1 LOW for Commands
}

static void DC_Data(){
    GPIOA_ODR |= (1<<1);  // Pull PA1 HIGH for Data
}

// pin A2
static void RST_LOW(){
    GPIOA_ODR &= ~(1<<2);
}

// pin A2
static void RST_HIGH(){
    GPIOA_ODR |= (1<<2);
}

static void WriteCommand(uint8_t cmd){
    DC_Command();
    CS_enable();
    spi1_send(&cmd, 1);
    CS_disable();
}

static void WriteData(uint8_t data){
    DC_Data();
    CS_enable();
    spi1_send(&data, 1);
    CS_disable();
}

void ILI9341_Init(){

    // config for SPI
    spi1_gpioinit();
    spi1_config();
    
    // initilize P1,2 for output
    GPIOA_MODER &= ~((3<<2)|(3<<4));
    GPIOA_MODER |= (1<<2)|(1<<4);
    // set P1,2 to high speed
    GPIOA_OSPEEDR |= (3<<2)|(3<<4);

    // begining init sequence for LCD
    RST_LOW();
    delay_SysTick(50, system_frequency);
    RST_HIGH();
    delay_SysTick(50, system_frequency);

    WriteCommand(0x01); // Software Reset
    delay_SysTick(120, system_frequency);

    WriteCommand(0x11); // Sleep Out
    delay_SysTick(120, system_frequency);
    
    WriteCommand(0x3A); // Pixel Format Set
    WriteData(0b01010101); // 16bits/pixel

    WriteCommand(0x36); // Memory Access Control
    WriteData(0); //! Change to rearagne display

    WriteCommand(0x29); // Display ON
    delay_SysTick(20, system_frequency);
}

void draw_Square(uint16_t start_col, uint16_t end_col, uint16_t start_row, uint16_t end_row, char color){
    if(start_col > max_cols || end_col > max_cols || start_row > max_rows || end_row > max_rows){return;}

    if(start_col > end_col || start_row > end_row){return;}

    uint16_t RGB_color;
    switch (color){
        case 'b': // black
            RGB_color = 0x0000;
            break;
        
        case 'w': // white
            RGB_color = 0xFFFF;
            break;
        
        case 'r': // red
            RGB_color = 0xF800;
            break;
        
        case 'g': // green
            RGB_color = 0x07E0;
            break;
    }

    WriteCommand(0x2a); // set col address
        WriteData(start_col >> 8); // send high  byte
        WriteData((uint8_t)start_col);
        WriteData(end_col >> 8); // send high byte
        WriteData((uint8_t)end_col);

    WriteCommand(0x2b); // set row address
        WriteData(start_row >> 8); // send high  byte
        WriteData((uint8_t)start_row);
        WriteData(end_row >> 8); // send high byte
        WriteData((uint8_t)end_row);

    uint64_t total_pixel = ((end_col-start_col+1)*(end_row-start_row+1));
    WriteCommand(0x2C); // Memory Write

        DC_Data();
        CS_enable();

        for(int i = 0; i<total_pixel; i++){
            
            while(!(SPI_SR & (1<<1))){} // wait for TXE to empty
            SPI_DR = (RGB_color>>8); // High bit

            while(!(SPI_SR & (1<<1))){} // wait for TXE to empty
            SPI_DR = ((uint8_t) RGB_color); // Low bit
        }

        while(SPI_SR & (1<<7)){} // wait for busyflag to finish
        CS_disable();
}

void fill_screen(char color){
    draw_Square(0, max_cols, 0, max_rows, color);
}