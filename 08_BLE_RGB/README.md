# Chapter 8.2 — BLE-Controlled RGB LED

Ported from Freenove's `Sketch_08.2_BLE_RGB.ino`. Same BLE UART bridge as
chapter 8.1, but incoming text commands (`red_on`/`red_off`,
`green_on`/`green_off`, `blue_on`/`blue_off`) drive the onboard WS2812
LED's color instead of just being echoed back.

## Pin correction: LEDS_PIN

Freenove's official sketch for this one chapter hardcodes `LEDS_PIN` to
40 for the non-N boards, but every other WS2812 chapter (LedPixel,
Rainbow, WiFi_Web_LED, Lvgl_WS2812) uses 42 for the same physical LED —
looks like a copy-paste slip in their template. Using 42 here too, to
match the one LED that's actually wired on the board.
