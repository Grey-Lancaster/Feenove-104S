# Chapter 10.2 — Display Logo (JPEG Decode From Flash)

Ported from Freenove's `Sketch_10.2_Flash_Jpg_DMA.ino`, FNK0104S branch
(4.0" ST7796). Decodes a JPEG baked directly into flash (`src/fox_logo.h`,
via the `TJpg_Decoder` library) and draws it full-screen every 2 seconds,
printing the image dimensions and decode time over serial each time.

Adapted from the sibling FNK0104B project's chapter 10.2
(github.com/Grey-Lancaster/Freenove104b) — the display logic is unchanged;
what differs for this board is `../common.ini`'s `tft_base` env (ST7796
driver, different pins/SPI speed than the 2.8" ILI9341 board) and the
embedded image, which is sized for this panel's 320x480 resolution.

## The logo

`src/fox_logo.h` holds "The Grey Fox" logo (Est. 1967), converted from the
1254x1254 source artwork: resized to 320px wide (full panel width, keeping
its native 1:1 aspect ratio) and centered vertically on a 320x480 white
canvas matching the logo's own background, then re-encoded as a baseline
JPEG (quality 90, ~35.6KB) — `TJpg_Decoder` requires baseline, not
progressive, JPEG data. Round-tripped the embedded bytes back through a
JPEG decoder to confirm the array matches the source exactly before
committing.

To regenerate with new artwork: resize/pad to 320x480 the same way (Pillow,
or Freenove's own "Freenove Image Tool" bundled in their official repo),
save as a baseline JPEG, and re-emit the `const unsigned char fox_logo[]
PROGMEM = { ... };` array from those bytes.

## Build

```
cd 10_Flash_Jpg_DMA
pio run
pio run -t upload
```

See the flashing notes (BOOT/RESET sequence, COM port changes) in the
sibling FNK0104B project's top-level README — the native-USB-CDC behavior
is the same ESP32-S3 SoC quirk, not board-specific.

## Unverified assumptions (no FNK0104S hardware access from this session)

- The board uses the same ESP32-S3-WROOM-1 N16R8 module (16MB flash / 8MB
  octal PSRAM) as the FNK0104B board `../boards/ESP32-S3-WROOM-1-N16R8.json`
  was written for. If boot crashes immediately, check this first.
- Touch pins are not wired up in this chapter (not needed for it) and
  haven't been ported yet.
