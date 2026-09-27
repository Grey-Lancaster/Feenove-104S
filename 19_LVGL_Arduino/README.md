# Chapter 19.1 — Stock LVGL Widgets Demo

Ported from Freenove's `Sketch_19.1_LVGL_Arduino.ino`, FNK0104S branch.
Wires up the standard `TFT_eSPI` + FT6336U touch driver boilerplate for
LVGL (per LVGL's own official Arduino porting guide) and launches LVGL's
built-in `lv_demo_widgets()` showcase — sliders, buttons, charts, tabs,
and the rest of LVGL's stock widget gallery, all interactive via touch.

Adapted from the sibling FNK0104B project's chapter 19.1: only
`TFT_SCREEN_WIDTH`/`TFT_SCREEN_HEIGHT` change (320x480 vs 240x320,
matching Freenove's own official per-board values for this chapter) —
touch pins, the touch coordinate remap, and everything else are identical.
