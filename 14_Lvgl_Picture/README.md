# Chapter 14.1 — LVGL Image Viewer

Ported from Freenove's `Sketch_14.1_Lvgl_Picture.ino`, FNK0104S branch. An
LVGL touchscreen gallery viewer: left/right buttons page through image
files found in the SD card's `/picture` folder, and a home button returns
to the folder's first image.

Adapted from the sibling FNK0104B project's chapter 14.1. `display.cpp`/
`display.h` are unchanged from chapter 13/15's version of this board's
FT6336U + plain-TFT_eSPI setup (320x480, no ST77922 sprite path needed).
`picture_ui.cpp`'s button positions/sizes and the image-viewing area
(320x320 here, vs. 240x240 on FNK0104B) come from Freenove's own
official FNK0104S-specific values, not a resolution-independent
calculation — this board's numbers were extracted directly rather than
scaled from the 2.8" board's.

Images themselves are read from the SD card at runtime (not baked into
flash), so no new image assets were needed for this port.
