# Chapter 17.2 — LVGL Mic Record + Playback (unofficial)

Not one of Freenove's own 19 tutorial chapters — pairs `07_Echo`'s mic
record/playback demo with an LVGL touchscreen UI, the way `17_Lvgl_Music`
pairs with `07_Music`.

Two buttons and a status label: **Record (5s)** records from the ES8311's
mic input into a PSRAM buffer, showing "Recording... Ns" while it runs;
**Play** (disabled until a recording exists) plays that buffer back out
through the speaker. Both run on a background FreeRTOS task so the
multi-second blocking I2S read/write doesn't freeze the screen.

Since this chapter has no official Freenove counterpart for this board,
there's no per-board layout to port: this UI's screen (`echo_ui.cpp`) is
laid out entirely with LVGL's `LV_ALIGN_CENTER`/`LV_ALIGN_TOP_MID`
alignment and relative offsets, not absolute pixel positions, so it
carries over from the sibling FNK0104B project unchanged and centers
correctly regardless of screen size. Only `display.cpp` needed updating,
to this panel's native 320x480 (same change as every other LVGL chapter).

I2S/ES8311 pins and the three bugs fixed here (mic gain never set,
playback dropping data via non-blocking writes, and a real bug in the
bundled Arduino-ESP32 `I2S` library's receive path — see
[`07_Echo/README.md`](../07_Echo/README.md) for the full writeup) are
unchanged from FNK0104B; already confirmed identical I2S pins in chapter
7.2.
