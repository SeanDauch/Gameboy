#ifndef _adc_drivers_h
    #define _adc_drivers_h

    #include <stdint.h>

    void adc_GPIOA_init(uint8_t pin_number);
    void adc_init(uint8_t ADC_channel_go_first);
    uint16_t adc_regular_conversion();

#endif