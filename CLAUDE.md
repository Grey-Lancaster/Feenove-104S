# CLAUDE.md

PlatformIO port of Freenove's 19-chapter "Touch Tutorial" for the Freenove FNK0104S (ESP32-S3 N16R8, 4.0" ST7796 480x320, FT6336U touch). Public repo: Grey-Lancaster/Feenove-104S. It mirrors the sibling FNK0104B (2.8" ILI9341) repo, Grey-Lancaster/Freenove104b, chapter by chapter. `README.md` has the chapter table and per-chapter status.

## Layout
- One folder per chapter (`01_SerialRW` ... `19_LVGL_Arduino`), each with its own `platformio.ini` that pulls in `common.ini` and extends one of its envs. Build a chapter from inside its folder: `pio run`.
- `common.ini` - shared base env and the TFT_eSPI config for this panel (translated from Freenove's FNK0104S setup).
- `lib_freenove/`, `boards/`, `include/` - shared libraries, the N16R8 board definition, `lv_conf.h`.
- `docs/` - GitHub Pages browser flasher (`docs/index.html` has a `chapterSelect` dropdown) and `docs/firmware/<chapter>.bin` merged images.

## Rules that matter
- The board definition must be `ESP32-S3-WROOM-1-N16R8` (from `boards/`). The generic devkit board assumes no PSRAM and crash-loops.
- Merged images (`esptool merge_bin`) must use `--flash_mode dio --flash_freq keep --flash_size keep`. Verify byte 2 of the merged `.bin` is `0x02` before shipping.
- When adding or changing a chapter: build, merge into `docs/firmware/<chapter>.bin`, add the `<option>` to the dropdown in `docs/index.html`, commit, merge to `main` (Pages serves `main`'s `docs/`).
- Verify a shipped binary landed by comparing `sha256sum docs/firmware/<x>.bin` with `curl -s https://grey-lancaster.github.io/Feenove-104S/firmware/<x>.bin | sha256sum`.
- LVGL button sizes must match their icon image sizes. A button wider than its single-image icon makes LVGL tile the image, which shows up as stray arcs (this was the real cause of the chapter 18 bug).
- If a visual bug survives one verified fix, reproduce it in a headless host LVGL build (render to a memory buffer / PPM) instead of flashing guesses to hardware.

## Owner's workflow
Code may be written anywhere, but builds run on the "greyhound" server and flashing is done from a browser (Chrome/Edge) on the PC the board is plugged into: open the Pages URL, hold BOOT, tap RESET, release BOOT, connect, flash, then press RESET (this board has no auto-reset). A session without access to those machines should say so and not claim a chapter works on hardware; "not yet flashed" in the README means untested.
