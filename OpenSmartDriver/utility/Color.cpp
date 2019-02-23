#include "Color.h"

Color::Color () {
  red = 0;
  green = 0;
  blue = 0;
}

// RGB color expected
Color::Color (uint32_t color) {
  red = (color >> 16) & 0xFF;
  green = (color >> 8) & 0xFF;
  blue = color & 0xFF;
}

Color::Color (uint8_t _red, uint8_t _green, uint8_t _blue) {
  red = _red;
  green = _green;
  blue = _blue;
}

uint32_t Color::scaledR () {
  return (uint32_t)map((uint32_t)red, 0, 255, 0, RGB_MAX);
}

uint32_t Color::scaledG () {
  return (uint32_t)map((uint32_t)green, 0, 255, 0, RGB_MAX);
}

uint32_t Color::scaledB () {
  return (uint32_t)map((uint32_t)blue, 0, 255, 0, RGB_MAX);
}

uint32_t Color::getBGR () {
  // driver takes 0 - 50 because it's stupid
  return (scaledB() << 16) | (scaledG() << 8) | scaledR();
}

void Color::operator =(uint32_t color) {
  red = (color >> 16) & 0xFF;
  green = (color >> 8) & 0xFF;
  blue = color & 0xFF;
}

void Color::set(uint8_t _red, uint8_t _green, uint8_t _blue) {
  red = _red;
  green = _green;
  blue = _blue;
}
