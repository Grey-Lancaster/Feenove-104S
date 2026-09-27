# Chapter 10.1 — Raw TFT Drawing

Ported from Freenove's `Sketch_10.1_TFT_Rainbow.ino`, FNK0104S branch.
Flashes the screen through solid red/green/blue/black/white on boot, then
repeatedly draws a shifting rainbow gradient plus a few font-size and
float-formatting samples — all using raw `TFT_eSPI` calls, no LVGL.

Adapted from the sibling FNK0104B project's chapter 10.1 — the only
difference is `SCREEN_WIDTH`/`SCREEN_HEIGHT` (480x320 here after
`tft.setRotation(1)`, vs. 320x240 on the 2.8" board), matching Freenove's
own official per-board `#ifdef` for this chapter exactly. The rainbow
fills the full width either way; the font/text samples are drawn at the
same fixed coordinates Freenove's own sketch uses regardless of panel
size, so they stay anchored to the top-left rather than centering on the
wider screen — that's upstream's own behavior, not something specific to
this port.
