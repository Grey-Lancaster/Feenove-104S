# FNK0104S Touch Tutorial Flasher

Browser-based flasher (Web Serial + [esptool-js](https://github.com/espressif/esptool-js), no install) for this repo's chapters. Ported from the sibling [Freenove104b](https://github.com/Grey-Lancaster/Freenove104b) repo's own `docs/` flasher — same mechanism, same board family, different chapter list.

Pick a chapter from the dropdown, connect the board, flash. Each chapter is a standalone demo, so it's always a single full-flash write at `0x0` — no OTA/app-update mode.

## Building a chapter's firmware/*.bin

Each `firmware/<chapter>.bin` is a merged flat image built like this:

```
cd <chapter folder>
pio run

python -m esptool --chip esp32s3 merge_bin \
  -o ../docs/firmware/<chapter>.bin \
  --flash_mode keep --flash_freq keep --flash_size keep \
  0x0     .pio/build/esp32s3/bootloader.bin \
  0x8000  .pio/build/esp32s3/partitions.bin \
  0xe000  ~/.platformio/packages/framework-arduinoespressif32/tools/partitions/boot_app0.bin \
  0x10000 .pio/build/esp32s3/firmware.bin
```

`boot_app0.bin` is identical for every chapter (same Arduino core version) — only the other three files change per chapter. After adding a new chapter's `.bin`, add a matching `<option>` (with `data-bin="firmware/<chapter>.bin"`) to the `<select id="chapterSelect">` in `index.html`.

**Always use `keep`/`keep`/`keep`, never hardcode `--flash_mode`.** Like the FNK0104B board, this board's ESP32-S3-WROOM-1 module uses octal PSRAM, which shares pins with the flash bus in a way that requires **DIO** flash mode specifically — PlatformIO's own build already bakes the right mode into `bootloader.bin`/`firmware.bin`'s image headers, but `merge_bin` will happily overwrite that if you pass an explicit `--flash_mode` other than `keep`. The result boots into an instant, silent watchdog-reset loop before any of our own code (or even the second-stage bootloader's own log line) prints anything, because the ROM's first flash read after `ets_loader.c` already fails. Verify by comparing the merged bin's header byte 2 against the original `bootloader.bin`'s (`xxd -l 8 <file>` — byte offset 2 should read `02`, i.e. DIO) before shipping a new chapter's `.bin`.

## Build/flash split (this repo's workflow)

Firmware is built on `greyhound` (faster machine, PlatformIO toolchain already set up and cached) and flashed from `boron` (where the board is actually plugged in via USB) using this browser flasher — no PlatformIO install needed on boron. Merge the `.bin` on greyhound as above, push it, then open this page in Chrome/Edge on boron to flash.

## Testing a just-pushed firmware fix

GitHub Pages sends `Cache-Control: max-age=600` on files under `firmware/`. `app.js` fetches with `cache: "no-store"` specifically so re-testing a chapter you already picked in the last 10 minutes doesn't silently serve the stale `.bin` from your own browser cache instead of the fix you just pushed — if you ever see old behavior right after a redeploy, hard-refresh the page (or check with `curl -sI .../firmware/<chapter>.bin` for `X-Cache: HIT` vs the file's actual hash) before assuming the fix didn't work.
