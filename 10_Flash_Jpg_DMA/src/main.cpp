// Ported from Freenove's Sketch_10.2_Flash_Jpg_DMA.ino (FNK0104S branch,
// 4.0" ST7796) -- see https://github.com/Freenove/Freenove_ESP32_S3_Display
// Draws a JPEG baked into flash (fox_logo.h) full-screen via TJpg_Decoder.
// Unlike the FNK0104N (3.5" ST77922) variant of this sketch, the S board's
// ST7796 panel doesn't need the sprite/QSPI dance -- tft.pushImage() draws
// straight to the panel, same as the FNK0104B port this was adapted from.
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include "fox_logo.h"
#include <TJpg_Decoder.h>

TFT_eSPI tft = TFT_eSPI();

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
  if (y >= tft.height()) return 0;
  tft.pushImage(x, y, w, h, bitmap);
  return 1;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n Displaying fox logo");
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  TJpgDec.setJpgScale(1);
  tft.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);
}

void loop() {
  uint16_t w = 0, h = 0;
  TJpgDec.getJpgSize(&w, &h, fox_logo, sizeof(fox_logo));
  Serial.print("Width = ");
  Serial.print(w);
  Serial.print(", height = ");
  Serial.print(h);

  uint32_t dt = millis();
  tft.startWrite();
  TJpgDec.drawJpg(0, 0, fox_logo, sizeof(fox_logo));
  tft.endWrite();

  dt = millis() - dt;
  Serial.print(", dt = ");
  Serial.print(dt);
  Serial.println(" ms");

  delay(2000);
}
