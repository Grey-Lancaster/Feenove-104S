# FNK0104S Projects

Firmware projects for Grey's Freenove FNK0104S (ESP32-S3, 4.0" ST7796
display, touch) board. Same product family and tutorial set as the
[FNK0104B](https://github.com/Grey-Lancaster/Freenove104b) (2.8" ILI9341)
board — Freenove's official
[Freenove_ESP32_S3_Display](https://github.com/Freenove/Freenove_ESP32_S3_Display)
repo covers both (plus the FNK0104A and FNK0104N variants) with the same
19-chapter "Touch Tutorial", just with per-board `#ifdef` branches for
pins/driver/resolution.

This repo ports that tutorial to PlatformIO the same way the FNK0104B repo
did, chapter by chapter, swapping in this board's TFT_eSPI config (ST7796
driver, 320x480, different pins/SPI speed — see `common.ini`) in place of
the 2.8" board's ILI9341 config.

## Projects

- `10_Flash_Jpg_DMA/` — decodes and displays "The Grey Fox" logo, a JPEG
  baked into flash (see that chapter's README)

Further chapters will be ported on request the same way — see the FNK0104B
repo for the full 19-chapter list this one is expected to eventually mirror.

## Shared across chapters

- `boards/ESP32-S3-WROOM-1-N16R8.json` — board def, carried over from the
  FNK0104B project on the assumption the module is the same across the
  FNK0104 line (unconfirmed for this specific board — see each chapter's
  README).
- `common.ini` — shared PlatformIO environments (`base` → `tft_base`),
  translated from Freenove's own `Libraries/FNK0104S/TFT_eSPI_Setups_v1.2.zip`
  setup header rather than the FNK0104B board's.
- `lib_freenove/TJpg_Decoder` — vendored from the FNK0104B project; this
  library is board-agnostic (same version ships in both boards' official
  library bundles).

Build any chapter with:
```
cd 10_Flash_Jpg_DMA
pio run
```

## Flashing

`docs/` is a browser-based flasher (Web Serial, no install) — see
`docs/README.md` for how to build and add a chapter's merged `.bin`, and
for the build-on-greyhound/flash-on-boron split this repo uses. Once
GitHub Pages is enabled for this repo, it'll be live the same way the
[FNK0104B flasher](https://grey-lancaster.github.io/Freenove104b/) is.
