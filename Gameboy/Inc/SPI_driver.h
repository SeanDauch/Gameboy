#ifndef _SPI_driver_h
    #define _SPI_driver_h

    #include <stdint.h>

    void spi1_gpioinit();
    void spi1_config();
    void spi1_send(uint8_t *data, uint32_t data_size);
    void spi1_receive(uint8_t *data, uint32_t data_size);
    void CS_enable();
    void CS_disable();
#endif
