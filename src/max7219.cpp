#include <max7219.h>

max7219::max7219()
{
}

max7219::~max7219()
{
}

void max7219::spiTransmit(uint8_t addr, uint8_t data)
{
  SPI.beginTransaction(SPISettings(MAX7219_SPIMAXSPEED, MSBFIRST, SPI_MODE0));
  digitalWrite(cs_pin, LOW);
  SPI.transfer(addr);
  if (addr > 0 && addr < 9)
  {
    lastSendData[addr - 1] = SPI.transfer(data);
  }
  else
    SPI.transfer(data);
  digitalWrite(cs_pin, HIGH);
  SPI.endTransaction();
}

void max7219::sendDigWithoutDP(uint8_t addr, uint8_t data)
{
  if (addr > 0 && addr < 9)
  {
    spiTransmit(addr, (lastSendData[addr-1] & 0b10000000) | (data & 0b1111111));
  }
}

void max7219::setBits(uint8_t addr, uint8_t bits)
{
  if (addr > 0 && addr < 9)
  {
    spiTransmit(addr, bits | lastSendData[addr-1]);
  }
}

void max7219::clearBits(uint8_t addr, uint8_t bits)
{
  if (addr > 0 && addr < 9)
  {
    spiTransmit(addr, ~bits & lastSendData[addr-1]);
  }
}

void max7219::init(uint8_t cs_pin)
{
  this->cs_pin = cs_pin;
  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);
  SPI.begin();
  spiTransmit(MAX7219_DISPLAYTEST_ADDR, MAX7219_OP_OFF);
  spiTransmit(MAX7219_SHUTDOWN_ADDR, MAX7219_OP_OFF);
  spiTransmit(MAX7219_SCANLIMIT_ADDR, 7);
  spiTransmit(MAX7219_DECODEMODE_ADDR, 0);
  for (unsigned char i = 1; i < 9; ++i)
    spiTransmit(i, MAX7219_DIG_BLANK);     // blank
  spiTransmit(MAX7219_BRIGHTNESS_ADDR, 0); // min power
}