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

| Chapter | Folder | Covers | Status |
|---|---|---|---|
| 1 | `01_SerialRW/` | Serial read/write | Ported (identical to FNK0104B — no board-specific pins in this chapter) |
| 2.1 | `02_LedPixel/` | Onboard WS2812 RGB LED | Ported (identical to FNK0104B) |
| 2.2 | `02_Rainbow/` | WS2812 color wheel animation | Ported (identical to FNK0104B) |
| 3.1 | `03_Button_RGB/` | Button input + RGB LED | Ported (identical to FNK0104B) |
| 4.1 | `04_Button_Interrupt_UART/` | Button interrupt + debounce | Ported (identical to FNK0104B) |
| 5.1 | `05_Battery_Voltage/` | Battery ADC reading | Ported (identical to FNK0104B) |
| 6.1 | `06_SDMMC_Test/` | SD card (SD_MMC) file I/O | Ported (identical to FNK0104B) |
| 7.1 | `07_Music/` | MP3 playback via ES8311 codec | Ported (identical to FNK0104B, incl. its documented audio bugfixes) |
| 7.2 | `07_Echo/` | Mic record + playback loopback | Ported (identical to FNK0104B, incl. its documented I2S bugfixes) |
| 8.1 | `08_BLE_USART/` | BLE UART bridge | Ported (identical to FNK0104B) |
| 8.2 | `08_BLE_RGB/` | BLE-controlled RGB LED | Ported, with one pin correction — see chapter README |
| 9.1 | `09_WiFi_Web_LED/` | WiFi web server LED control | Ported (identical to FNK0104B) |
| 10.1 | `10_TFT_Rainbow/` | Raw TFT_eSPI drawing/fonts | Not yet ported (genuine per-board layout, 320x480 vs 240x320) |
| 10.2 | `10_Flash_Jpg_DMA/` | JPEG decode from flash to TFT | **Ported and confirmed working on hardware** — displays "The Grey Fox" logo |
| 11.1 | `11_Touch/` | FT6336U capacitive touch (raw) | Ported (identical to FNK0104B) |
| 12.1 | `12_TFT_Touch_Draw/` | Touch-driven drawing on TFT | Not yet ported (genuine per-board layout) |
| 13.1 | `13_LVGL/` | Baseline LVGL setup | Not yet ported (genuine per-board resolution) |
| 14.1 | `14_Lvgl_Picture/` | LVGL image viewer from SD card | Not yet ported (genuine per-board layout + image asset) |
| 15.1 | `15_Lvgl_Timer/` | LVGL chronograph/stopwatch UI | Not yet ported (genuine per-board layout) |
| 16.1 | `16_Lvgl_WS2812/` | LVGL-driven WS2812 color picker | Not yet ported (genuine per-board layout) |
| 17.1 | `17_Lvgl_Music/` | LVGL music player UI | Not yet ported (genuine per-board layout) |
| 17.2 | `17_Lvgl_Echo/` | LVGL mic record + playback (unofficial) | Not yet ported |
| 18.1 | `18_Lvgl_Multifunctionality/` | All LVGL screens combined | Not yet ported (genuine per-board layout, many files) |
| 19.1 | `19_LVGL_Arduino/` | Stock LVGL widgets demo | Not yet ported (genuine per-board resolution) |

Chapters marked "identical to FNK0104B" have no display/resolution
dependency and cross-checked byte-for-byte against Freenove's official
per-board `#ifdef` branches: the FNK0104S and FNK0104B code paths are
provably the same for these (only the FNK0104N/3.5" variant differs), so
these were ported by direct copy. The still-outstanding chapters all touch
the TFT/LVGL and genuinely differ (320x480 vs 240x320 layout, rotation,
image assets) — these are being ported one at a time, each compiled and
then verified on real hardware before moving to the next, the same way
chapter 10.2 was.

## Shared across chapters

- `boards/ESP32-S3-WROOM-1-N16R8.json` — board def, carried over from the
  FNK0104B project on the assumption the module is the same across the
  FNK0104 line. **Confirmed correct**: chapter 10.2 boots and runs fine on
  real FNK0104S hardware with this board def.
- `common.ini` — shared PlatformIO environments (`base` → `tft_base`),
  translated from Freenove's own `Libraries/FNK0104S/TFT_eSPI_Setups_v1.2.zip`
  setup header rather than the FNK0104B board's.
- `lib_freenove/TJpg_Decoder` — vendored from the FNK0104B project; this
  library is board-agnostic (same version ships in both boards' official
  library bundles).
- `lib_freenove/ESP32-audioI2S`, `FT6336U_CTP_Controller`,
  `Freenove_WS2812_Lib_for_ESP32` — also vendored from the FNK0104B
  project for the same reason: these libraries are board-agnostic, only
  the pins passed into them differ (and for every chapter ported so far,
  don't even differ from FNK0104B).

Build any chapter with:
```
cd 01_SerialRW
pio run
```
