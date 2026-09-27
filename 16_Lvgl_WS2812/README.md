# Chapter 16.1 — LVGL WS2812 Color Picker

Ported from Freenove's `Sketch_16.1_Lvgl_WS2812.ino`, FNK0104S branch. An
LVGL UI with four sliders (red/green/blue/brightness) that drive the
onboard WS2812 LED's color in real time.

Adapted from the sibling FNK0104B project's chapter 16.1. Unlike chapter
15's chronograph screen, this one's layout is hardcoded absolute pixel
positions rather than computed from screen size — Freenove's official
sketch has a distinct, larger set of positions/sizes for the FNK0104S/N
boards (home button, label, and slider placement all differ from
FNK0104B's), so those values were extracted directly rather than adapted.
`display.cpp` uses this panel's native 320x480; touch pins and WS2812 pin
(42) are identical to FNK0104B.

## Bug fixed: stray scrollbar arc at screen edge

This screen's root object (`lv_obj_create(NULL)`) is scrollable by
default in LVGL, and showed a small stray arc at the screen edge on
hardware -- `17_Lvgl_Music`/`17_Lvgl_Echo` already disable this for their
own screens; applied the same `lv_obj_clear_flag(ui->ws2812,
LV_OBJ_FLAG_SCROLLABLE)` fix here.
