#ifndef _main_h
    #define _main_h

    #include <stdint.h>

    #define system_frequency 20000000
    #define max_cols 240 // max y in games
    #define max_rows 320 // max x in games
    
    #define RCC_base 0x40023800
    #define RCC_CR *((volatile uint32_t*)(RCC_base + 0x00))
    #define RCC_PLLCFGR *((volatile uint32_t*)(RCC_base + 0x04))
    #define RCC_CFGR *((volatile uint32_t*)(RCC_base + 0x08))
#endif