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
* DrivingMethods.ino
* ------------------
* Author: Sierra MacLeod <sierra.m.macleod@gmail.com>
* 
* This sketch demonstrates different ways to drive colors
* to the Open-Smart driver.
*
*/

#include <OpenSmartDriver.h>

// A few standard colors from CSS
#define DEEP_PINK 0xFF1493
#define ORANGE_RED 0xFF4500
#define DARK_ORCHID 0x9932CC

// You can use any GPIO pins here
#define CLOCK 13
#define DATA 11

// Define number of drivers daisy-chained
#define NUM_STRIPS 3

// Create an array of colors, one for each driver
Color colors[NUM_STRIPS];

// Create driver instance
OpenSmartDriver driver(CLOCK, DATA, colors, NUM_STRIPS);

void setup () {
    
}

void loop () {
    // These three are equivalent:
    colors[0] = 0xFF0000;
    colors[0] = Color(0xFF0000);
    colors[0] = Color(255, 0, 0);
    driver.update();
    delay(1000);
    
    // Only the final color assigned to a driver before
    // update() will be pushed out
    colors[0] = DEEP_PINK;
    colors[0] = ORANGE_RED;
    driver.update();
    delay(500);
    
    // You can change multiple colors concurrently
    // (Make sure you have enough strips chained to see this update)
    colors[0] = DARK_ORCHID;
    colors[1] = DEEP_PINK;
    colors[2] = ORANGE_RED;
    driver.update();
    delay(500);
}