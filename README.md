# OpenSmartDriver
A simple Arduino control library for use with Open-Smart LED drivers

# Overview
This library provides a simple-to-use, lightweight, FastLED-like interface for Open-Smart and similar LED drivers implementing the P9813 IC.

# Boards
This library was designed to run on boards styled like this:
![Open-Smart Driver](https://img.dxcdn.com/productimages/sku_314667_1.jpg "Open-Smart Driver")
Open-Smart makes lots of these useful little drivers. Each can drive one standard (5 meter) RGB LED strip, and you can daisy chain multiple together if you need.

# Motivations
I wrote this library for a few reasons. One was that while there are several libraries available for Python and shell control, I found only one working C++ library, [this](https://github.com/SeeedDocument/Grove-LED_Strip_Driver/) basic library from Seeed Studio. While it works, the provided interface is clunky not very scalable. My implementation is based on much of the internal parts of this library.

I will note here that though FastLED works for the P9813, it does not, for whatever reason, work correctly with the Open-Smart boards. While you can certainly send something to the driver, the RGB values do not increment correctly after about 50, leading to bizarre behavior in the upper limits of each byte.

To fix this, I allow traditional 3-byte color assignments and then scale them down to a fraction of 50 before transmission. This works very well from testing, although it is limiting in colors as you have only 50^3 colors to work with instead of 255^3. If anyone has suggestions as to why the board handles data this way or how to fix this, I'd love the help.

# Use
You can use this library very similarly to the FastLED method, as it's an easy and intuitive method.

Start with this line at the top:
```
#include <OpenSmartDriver.h>
```
Define pins, an array to hold a color for each driver in the chain, and create a driver object:
```
#define CLOCK 13
#define DATA 11

// Define number of drivers daisy-chained
#define NUM_STRIPS 3

// Create an array of colors, one for each driver
Color colors[NUM_STRIPS];

// Create driver instance
OpenSmartDriver driver(CLOCK, DATA, colors, NUM_STRIPS);
```
You can make your clock and data pins any two digital pins.

To assign a color, there are several options available:
```
colors[0] = 0xFF0000;
colors[0] = Color(0xFF0000);
colors[0] = Color(255, 0, 0);
```
These three statements are identical. Choose whatever works best for you!

Finally, call `driver.update()` to update all drivers at once.
```
colors[0] = 0xFF0000;
colors[1] = 0x00FF00;
colors[2] = 0x0000FF;
driver.update();
```
And that's it!

# A Few Notes
**Clock Rate:** in most implementations of the library, a clock period is defined and data is clocked out at that speed. The Seeed Studio library uses a clock rate of 50kHz (40us period). This really isn't optimally fast as the P9813 can clock at 10MHz. At a rate this high, we're looking at a period of 100ns. Since the Arduino Uno's 16MHz ticks every 62.4 ns, you'd have to write the code very carefully to try to get near 10MHz rates. Instead, I just opted to take all delays out and let the library pulse as fast as it can (which is indeed fast enough). If you run this code on something with a much higher clock rate, like 50MHz, and you notice trasnmission errors, it would make sense to add some kind of delay to the clock function in `OpenSmartDriver.cpp`.

**Color Accuracy:** In many RGB led systems, one main challenge is balancing all three LED intensities. You may find your driver skews toward green, which is natural and common. Mine sure do. To fix this I just tone the green down in the color codes, but I may add a library option for scaling green in the future.

Enjoy!
