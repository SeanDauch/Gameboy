#ifndef _Delay_h
    #define _Delay_h

    #include <stdint.h>

    void delay_SysTick(uint32_t delay_ms, uint32_t sys_freq);
#endif