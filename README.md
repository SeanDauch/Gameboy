# LCD "Gameboy"
Uses STM32F411ceu6

### To Do:
    1. Make SPI driver - DONE
    2. Use spi to make lcd drivers - DONE
        2a. Decide if we need DMA - Dont have time
    3. Make game - PONG
        3a. make bouncing box - DONE
            i. make ball struct
                - has a/y/dx/dy
            ii. create fuction for drawing 
            iii. add if statement for boundries
        3b. add user input to make pong - UNTESTED
            i. make paddle struct
                - has x/y
            ii. create fuction for drawing 
            iii. add if statements for paddle colision
