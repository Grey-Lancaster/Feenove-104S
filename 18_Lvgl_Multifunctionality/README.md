# Chapter 18.1 — LVGL Multifunctionality

Ported from Freenove's `Sketch_18.1_Lvgl_Multifunctionality.ino`, FNK0104S
branch. Combines the picture viewer, chronograph, WS2812 color picker, and
music player screens from the earlier LVGL chapters into one app with a
home/launcher screen to switch between them. Includes its own copy of the
SD card and ES8311 audio codec init (for the music screen) alongside the
LVGL/display setup used by the other screens.

Adapted from the sibling FNK0104B project's chapter 18.1, the same way as
the standalone chapters it combines: `display.cpp` uses this panel's
native 320x480; `main_ui.cpp`, `picture_ui.cpp`, `chronograph_ui.cpp`,
`ws2812_ui.cpp`, and `music_ui.cpp` all use Freenove's own official
FNK0104S-specific layout values (extracted the same way as chapters
14–17.1) rather than FNK0104B's; `lv_img.h`'s icon sizes follow the same
official values. `public.h`'s SD/I2S pins and `ws2812_ui.h`'s WS2812 pin
(42) are unchanged — already confirmed identical to FNK0104B.

## Fixes carried over from `07_Music`/`17_Lvgl_Music`

This chapter's `music_ui.cpp` has the same audio bugs those two chapters
had and already fixed — missing MCLK argument in `audio.setPinout()`
(landing in the wrong parameter slot, leaving the codec silent) and the
startup volume slider never actually calling `audio.setVolume()`. Both
fixed the same way; see those chapters' READMEs for the full explanation.

## No-SD-card fallbacks

- **Music screen:** falls back to the same embedded **Olive.mp3** used by
  `07_Music`/`17_Lvgl_Music`, written to SPIFFS and autoplayed.
- **Picture viewer:** shows an embedded fallback image instead of a blank
  screen — "The Grey Fox" logo, converted to a **320x320** (this board's
  picture-viewer size, vs. FNK0104B's 240x240) raw RGB565 C array
  (`src/fallback_img.cpp`/`.h`) matching `lv_img.cpp`'s own image format
  (`LV_COLOR_DEPTH==16`, `LV_COLOR_16_SWAP==0`: 2 bytes/pixel, low byte
  first, no alpha). Regenerated from the same source artwork used for
  chapter 10.2's logo display, resized to 320x320 instead of that
  chapter's 320x480 (this fallback fills a square viewing area, not the
  full panel) and round-tripped through a decoder to confirm the array
  renders correctly before committing. Also carries over a related fix:
  the "no files" check in `picture_imgbtn_display()` now checks for an
  empty string too, not just `NULL` (the SD-listing helper never actually
  returns `NULL`, so the original check was dead code and the screen just
  went blank instead of showing the fallback).
