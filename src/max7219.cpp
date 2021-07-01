#include <max7219_pvn.h>

max7219_pvn::max7219_pvn(uint8_t CS_PIN)
{
  this->CS_PIN = CS_PIN;
}

max7219_pvn::~max7219_pvn()
{
}

void max7219_pvn::spiTransmit(uint8_t addr, uint8_t data)
{
  SPI.beginTransaction(SPISettings(MAX7219_SPIMAXSPEED,MSBFIRST,SPI_MODE0));
  digitalWrite(CS_PIN,LOW);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite(CS_PIN,HIGH);
  SPI.endTransaction();
}

void max7219_pvn::init()
{
  pinMode(CS_PIN,OUTPUT);
  digitalWrite(CS_PIN,HIGH);
  SPI.begin();
  spiTransmit(MAX7219_DISPLAYTEST_ADDR, MAX7219_OP_OFF);
  spiTransmit(MAX7219_SHUTDOWN_ADDR, MAX7219_OP_OFF);
  spiTransmit(MAX7219_SCANLIMIT_ADDR, 7);
  spiTransmit(MAX7219_DECODEMODE_ADDR, 0);
   for (unsigned char i = 1; i < 9; ++i)
     spiTransmit(i, MAX7219_DIG_BLANK);        // blank
   spiTransmit(MAX7219_BRIGHTNESS_ADDR, 0); // min power

}