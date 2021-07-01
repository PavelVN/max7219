#ifndef MAX7219_PVN_H
#define MAX7219_PVN_H

#include <Arduino.h>
#include <SPI.h>

#define MAX7219_SPIMAXSPEED 10000000UL
#define MAX7219_NOOP_ADDR (0x00)
#define MAX7219_DECODEMODE_ADDR (0x09)
#define MAX7219_BRIGHTNESS_ADDR (0x0A)
#define MAX7219_SCANLIMIT_ADDR (0x0B)
#define MAX7219_SHUTDOWN_ADDR (0X0C)
#define MAX7219_DISPLAYTEST_ADDR (0x0F)

#define MAX7219_OP_OFF 0x0
#define MAX7219_OP_ON 0x1
#define MAX7219_DIG_MINUS 0b1
#define MAX7219_DIG_BLANK 0b0
#define MAX7219_DIG_DP 0b10000000


class max7219_pvn
{
private:
    uint8_t cs_pin;
    uint8_t activeDigits;
public:
    max7219_pvn();
    ~max7219_pvn();
    void spiTransmit(uint8_t addr, uint8_t data);
    void init(uint8_t cs_pin);
};


#endif