#ifndef _adc_drivers_h
    #define _adc_drivers_h

    #include <stdint.h>

    void adc_GPIOA_init(short pin_number);
    void adc_init();
    uint16_t adc_regular_conversion();

#endif