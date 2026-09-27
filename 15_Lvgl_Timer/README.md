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

## Bug fixed: stray scrollbar arc at screen edge

This screen's root object (`lv_obj_create(NULL)`) is scrollable by
default in LVGL, and showed a small stray arc at the screen edge on
hardware -- `17_Lvgl_Music`/`17_Lvgl_Echo` already disable this for their
own screens; applied the same `lv_obj_clear_flag(ui->chronograph,
LV_OBJ_FLAG_SCROLLABLE)` fix here.

## Bug fixed: chronograph display jumping

See commit history / project notes -- the elapsed-time readout is now
four separate fixed-width labels (HH/MM/SS/CS) in a centered flex row,
rather than one auto-sizing label holding the whole string. A first
attempt (zero-padding + a single centered fixed-width label) wasn't
enough: this project's font is proportional, so the rendered text width
still wobbles a few pixels tick to tick even at constant character count,
and a centered label re-anchors on that wobble every redraw. Splitting
into small per-field labels bounds each field's wobble to its own box.
