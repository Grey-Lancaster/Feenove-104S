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

## Current status: placeholder image

`src/fox_logo.h` currently holds Freenove's own stock demo JPEG (from their
official repo's FNK0104S/N `panda.h` branch) rather than the actual fox
logo — it's there so this chapter builds and can be flashed to confirm the
display path works on real hardware before the real artwork is dropped in.

To swap in the real logo: convert it to a JPEG byte array in the same
`const unsigned char fox_logo[] PROGMEM = { ... };` format (Freenove's own
"Freenove Image Tool", bundled in their official repo, does this crop/encode
step for you) and replace the array in `src/fox_logo.h`, keeping the name
`fox_logo`.

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
