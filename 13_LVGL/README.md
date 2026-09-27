# Chapter 13.1 — LVGL (baseline setup)

Ported from Freenove's `Sketch_13.1_LVGL.ino`, FNK0104S branch. The
simplest possible LVGL bring-up on this board: initializes the TFT_eSPI
display driver and LVGL itself, then shows a single centered label reading
"Hello ESP32-S3!" along with the LVGL version in use.

Touch input is registered with LVGL (`my_touchpad_read`) but left as an
empty stub — this chapter doesn't actually read the touch controller, it
just establishes the display pipeline that every later LVGL chapter
(14 through 19) builds on.

Adapted from the sibling FNK0104B project's chapter 13.1: `display.cpp`'s
`screenWidth`/`screenHeight` are 320x480 here (this panel's native
portrait resolution) instead of 240x320, and `TFT_DIRECTION` stays at `0`
(no rotation) either way — this chapter runs portrait, unlike 10.1/12.1
which rotate to landscape.

`display.h` hardcodes the FT6336U touch pins directly: Freenove's own
official `display.h` for this chapter only has explicit branches for
FNK0104N and FNK0104B (it wasn't updated when FNK0104S was added to the
tutorial), but every other chapter confirms FNK0104S uses the same touch
pins as FNK0104B, so those values carry over unchanged.
