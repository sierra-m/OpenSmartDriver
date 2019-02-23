#ifndef COLOR_H
#define COLOR_H

#define RGB_MAX 50

#include <Arduino.h>
#include <inttypes.h>

class Color {
  public:
    uint8_t red, green, blue;

    Color();
    Color(uint32_t color);
    Color(uint8_t _red, uint8_t _green, uint8_t _blue);

    uint32_t scaledR ();
    uint32_t scaledG ();
    uint32_t scaledB ();

    uint32_t getBGR();
    void set(uint8_t _red, uint8_t _green, uint8_t _blue);
    
    void operator =(uint32_t color);
  private:
};

#endif
