#include "OpenSmartDriver.h"

OpenSmartDriver::OpenSmartDriver (uint8_t clock, uint8_t data, Color * strips, int count) {
  clockPin = clock;
  dataPin = data;
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  ledStrips = strips;
  stripCount = count;
}

void OpenSmartDriver::pulseClock () {
  digitalWrite(clockPin, LOW);
  // optional delay
  digitalWrite(clockPin, HIGH);
  // optional delay
}
 
void OpenSmartDriver::sendEmptyFrame () {
  digitalWrite(dataPin, LOW);
  
  for (uint8_t i = 0; i < 32; i++)
  {
    pulseClock();
  }
}
 
uint32_t OpenSmartDriver::antiCode (uint32_t data) {
  uint8_t temp = 0;
 
  if ((data & 0x80) == 0) {
    temp |= 0x02; 
  }
 
  if ((data & 0x40) == 0) {
    temp |= 0x01; 
  }
 
  return (uint32_t)temp;
}
 
void OpenSmartDriver::sendPacket (uint32_t packet) {
  
  for (uint8_t i = 0; i < 32; i++) {

    // send MSB
    if ((packet & 0x80000000) != 0) {
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }
    
    pulseClock();
    packet <<= 1;
  }
}

void OpenSmartDriver::update () {

  // start condition
  sendEmptyFrame();

  for (int i = 0; i < stripCount; i++) {
    Color strip = ledStrips[i];
    uint32_t color = strip.getBGR();

    // 2-bit start flag
    color |= (0x03 << 30);

    // anti-codes for each color
    color |= antiCode(strip.scaledB()) << 28;
    color |= antiCode(strip.scaledG()) << 26;
    color |= antiCode(strip.scaledR()) << 24;

    // clock out packet
    sendPacket(color);
  }

  // stop condition
  sendEmptyFrame();
}
