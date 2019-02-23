#ifndef OPEN_SMART_DRIVER_H
#define OPEN_SMART_DRIVER_H

#include <inttypes.h>
#include <Arduino.h>
#include <utility/Color.h>

class OpenSmartDriver {
  public:
    Color * ledStrips;
    int stripCount;
  
    OpenSmartDriver(uint8_t clock, uint8_t data, Color * strips, int count);
    
    void pulseClock();
    void sendEmptyFrame();
    uint32_t antiCode(uint32_t data);
    void sendPacket(uint32_t packet);
    void update();
  private:
    uint8_t clockPin, dataPin;
};
#endif

