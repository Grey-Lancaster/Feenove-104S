# Chapter 15.1 — LVGL Chronograph

Ported from Freenove's `Sketch_15.1_Lvgl_Timer.ino`, FNK0104S branch. An
LVGL stopwatch/chronograph UI — start, stop, and reset controls on a
touchscreen timer display.

Adapted from the sibling FNK0104B project's chapter 15.1. `display.cpp`
uses this panel's native 320x480 (vs. 240x320); its touch-pin setup and
touchpad-read logic are otherwise identical to FNK0104B (already
confirmed the same FT6336U pins across boards). `chronograph_ui.cpp`'s
layout is almost entirely computed from `screen_width`/`screen_height` at
runtime, so it needed no other changes — the one exception is the home
button's icon size, which Freenove's official sketch hardcodes larger
(100x100 vs 80x80) for this board's bigger panel; `lv_img.h`'s other
icon-size selections follow the same official FNK0104S values.
