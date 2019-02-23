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
* Cycle.ino
* ---------
* Author: Sierra MacLeod <sierra.m.macleod@gmail.com>
* 
* This sketch demonstrates the basic requirements to
* set up and run the OpenSmartDriver library.
*
*/

#include <OpenSmartDriver.h>

// Some example colors. You can choose from any
// valid three-byte code.
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff

// You can use any GPIO pins here
#define CLOCK 13
#define DATA 11

// Define number of drivers daisy-chained. This will
// usually be 1 if you have only one strip.
#define NUM_STRIPS 1

// Create an array of colors, one for each driver
Color colors[NUM_STRIPS];

// Create driver instance
OpenSmartDriver driver(CLOCK, DATA, colors, NUM_STRIPS);

void setup () {
  // Set up things
}

void loop () {
  
  // Simply assign the colors you desire and call update()
  colors[0] = RED;
  driver.update();
  delay(1000);

  colors[0] = GREEN;
  driver.update();
  delay(1000);

  colors[0] = BLUE;
  driver.update();
  delay(1000);
}
