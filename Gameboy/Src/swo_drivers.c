#include "swo_drivers.h"
#include <stdint.h>
#include <stdio.h>

#define GPIOB_base 0x40020400
#define GPIOB_MODER *((volatile uint32_t*)(GPIOB_base))
#define GPIOB_AFRL *((volatile uint32_t*)(GPIOB_base + 0x20))

#define ITM_lock_access *((volatile uint32_t*)(0xE0000FB0))
#define ITM_trace_control *((volatile uint32_t*)(0xE0000E80))
#define ITM_trace_enable *((volatile uint32_t*)(0xE0000E00))
#define ITM_stim_port0_32bit *((volatile uint32_t*)(0xE0000000))
#define ITM_stim_port0_8bit *((volatile uint8_t*)(0xE0000000))

void swo_init_printf(){

    // make sure PB3 is SWO
    GPIOB_MODER &= ~(3<<6);
    GPIOB_MODER |= (2<<6);
    GPIOB_AFRL &= ~(0xF << 12); // AF) means System Function

    // specific command to unlock other ITM registers
    ITM_lock_access =  0xC5ACCE55;

    // SWOENA = enable SWV
    ITM_trace_control |= (1<<4);

    // ITMENA = enable ITM
    ITM_trace_control |= (1<<0);

    // enable stimulus port 0 (0 is the prinf port)
    ITM_trace_enable |= (1<<0);

    //* disables the buffer fro printf (goes instantly to _write)
    setvbuf(stdout, NULL, _IONBF, 0);

}

int __io_putchar(int ch){

    // wait for port0 to empty (reading 0 means busy)
    while ((ITM_stim_port0_32bit & 0xF) == 0){}

    // write ch to port0
    ITM_stim_port0_8bit = ((uint8_t)ch << 0); 
    //* need to cast ITM port as 1byte so it sends 1 byte instead of 4

    return 0;
}