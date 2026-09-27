# Chapter 17.1 — LVGL Music Player

Ported from Freenove's `Sketch_17.1_Lvgl_Music.ino`, FNK0104S branch. An
LVGL touchscreen UI (play/pause/stop/prev/next, volume slider, progress
bar) for `.mp3` files on the root of an SD card's `/music` folder, played
through the onboard ES8311 codec.

Adapted from the sibling FNK0104B project's chapter 17.1: `display.cpp`
uses this panel's native 320x480; `music_ui.cpp`'s button/slider layout
uses Freenove's own official FNK0104S-specific positions (larger icons,
different placement) rather than FNK0104B's; `lv_img.h`'s icon sizes
follow the same official values as chapters 14–16. I2S/audio pins and the
audio-side bugfixes below are unchanged — already confirmed identical to
FNK0104B in chapter 7.1.

## No-SD-card fallback

Mirrors the fallback added in `07_Music`: if the SD card's `/music` folder
has no files (or there's no card at all), the firmware writes an embedded
track, **Olive.mp3** (`src/olive_mp3.h`, ~327KB, same asset as `07_Music`),
to SPIFFS on first boot and plays it from there instead. This fallback
**autoplays immediately** on load — the on-screen label already reads "No
files found on SD card - playing local file". The left/right/play controls
work fine on the single fallback track too (they just keep replaying it).

## Bug fixed: silent speaker (missing MCLK)

Same root cause as `07_Music` (see that chapter's README): `setPinout()`'s
4th parameter is DIN (mic input), not MCLK — passing the MCLK pin there
left the real MCK parameter untouched, so the codec never got a real
MCLK signal and stayed silent even though init reported success. Fixed by
passing `I2S_PIN_NO_CHANGE` for DIN and the MCLK pin explicitly as the 5th
argument.

## Bug fixed: startup volume ignored the slider

`lv_slider_set_value()` only moves the widget — it doesn't fire LVGL's
value-changed event, which is what actually calls `audio.setVolume()`. So
the slider *displayed* a value at startup but the codec was left at its
uninitialized default (`m_vol = 64`, louder than max) until the user
dragged the slider once. Fixed by calling the volume-set function directly
right after positioning the slider.

## Periodic status line for debugging

Same addition as `07_Music`: this board's native USB CDC port drops and
re-enumerates on every reset, so a serial monitor connecting even
slightly late misses all of `setup()`'s boot prints. `loop()` prints a
`status: i2s=<ok|FAILED> playing=<yes|no> vol=<n>` line every 2 seconds so
current state is visible within a couple seconds regardless of timing.
