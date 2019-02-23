/* 
* ==============================================================================
* MIT License
* 
* Copyright (c) 2019 Sierra MacLeod
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* ==============================================================================
*
* Fade.ino
* --------
* Author: Sierra MacLeod <sierra.m.macleod@gmail.com>
* 
* This sketch shows a simple method to fade between colors
*
*/

#include <OpenSmartDriver.h>

// A few colors to fade between
#define YELLOW 0xFFFF00
#define ORANGE 0xFF8C00
#define RED 0xFF0000

// You can use any GPIO pins here
#define CLOCK 13
#define DATA 11

// Define number of drivers daisy-chained
#define NUM_STRIPS 1

// Create an array of colors, one for each driver
Color colors[NUM_STRIPS];

// Create driver instance
OpenSmartDriver driver(CLOCK, DATA, colors, NUM_STRIPS);

void setup () {
    colors[0] = YELLOW;
    driver.update();
    delay(3000);
}

void loop () {
    transitionTo(ORANGE, 100, 4000);
    delay(4000);
    
    transitionTo(RED, 100, 2000);
    delay(2000);
    
    transitionTo(YELLOW, 100, 3000);
    delay(2000);
}

void transitionTo (Color target, int steps, int duration) {
  float cRed = (float)colors[0].red;
  float cGreen = (float)colors[0].green;
  float cBlue = (float)colors[0].blue;
  
  float redStep = (( (float)target.red - cRed) / (float)steps);
  float blueStep = (( (float)target.blue - cBlue) / (float)steps);
  float greenStep = (( (float)target.green - cGreen) / (float)steps);

  unsigned int _delay = (int)(duration / steps);

  for (int i = 0; i < steps; i++) {
    if (colors[0].red != target.red) {
      cRed += redStep;
      colors[0].red = (uint8_t)cRed;
    }
    if (colors[0].blue != target.blue) {
      cBlue += blueStep;
      colors[0].blue = (uint8_t)cBlue;
    }
    if (colors[0].green != target.green) {
      cGreen += greenStep;
      colors[0].green = (uint8_t)cGreen;
    }
    
    driver.update();
    delay(_delay);
  }
}