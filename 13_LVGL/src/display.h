#ifndef __DISPLAY_H
#define __DISPLAY_H

#include "lvgl.h"
#include "Arduino.h"
#include "TFT_eSPI.h"

// Freenove's own official display.h only has explicit branches for
// FNK0104N and FNK0104AB here (this one file wasn't updated when FNK0104S
// was added) -- FNK0104S follows the same plain-SPI/FT6336U path as AB in
// every other file for this chapter, so using AB's values directly.
#define LV_COLOR_16_SWAP 0
#define I2C_SCL 15
#define I2C_SDA 16
#define INT_N_PIN 17
#define RST_N_PIN 18

#define TFT_DIRECTION 0   //TFT direction

class Display
{
private:

public:
    void init();
    void routine();
};

#endif
