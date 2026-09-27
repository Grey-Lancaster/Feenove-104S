# Chapter 12.1 — Touch-Driven Drawing

Ported from Freenove's `Sketch_12.1_TFT_Touch_Draw.ino`, FNK0104S branch.
A simple finger-paint app built on raw `TFT_eSPI` + FT6336U touch (no
LVGL): a color-swatch strip along the top of the screen picks the current
color, and dragging a finger anywhere else draws a line that follows it.
Tapping the palette area again clears the canvas.

Adapted from the sibling FNK0104B project's chapter 12.1. Unlike most of
the earlier chapters, this one isn't a straight copy — Freenove's own
official sketch lays out this chapter's UI differently per board: the
2.8" board's "Clear" button and current-color swatch are hardcoded pixel
positions, while the 4.0" board's are positioned relative to `tft.width()`.
Ported the FNK0104S-specific layout code here rather than the 2.8" one.
`ColorPalette` (the swatch strip's height) is also larger here (30 vs 21)
to match the bigger panel, per Freenove's own value for this board.

Touch pins (FT6336U over I2C) and the touch coordinate remapping are
otherwise identical to FNK0104B — only the `SCREEN_WIDTH` constant used in
that remap (320 here vs. 240) differs, matching the panel's native
(pre-rotation) width.
