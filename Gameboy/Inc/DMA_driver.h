#ifndef _DMA_driver_h
    #define _DMA_driver_h

    #include <stdint.h>

    void DMA2_init();
    uint8_t DMA_busy();
    void DMA2_SPI1_config_s2c2(uint8_t* data_start_addr, uint16_t data_length);
#endif