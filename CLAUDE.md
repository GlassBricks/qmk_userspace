## Overview

A QMK _userspace_ overlay (not a fork of QMK) for the SplitKB Halcyon Kyria rev4. QMK core lives outside
this tree: `~/qmk_firmware` locally, `splitkb/vial-qmk@halcyon` in CI.

Two files actively developed:

- `keyboards/splitkb/halcyon/kyria/keymaps/glassbricks/keymap.c` -- the keymap.
- `users/halcyon_modules/hlc_tft_display/hlc_tft_display.c` -- the TFT display UI, locally modified from
  the stock SplitKB module to read keymap state.

The rest of `users/halcyon_modules/`, plus `modules/getreuer/` (submodule), `default_hlc/`, `vial_hlc/`
and `examples/`, is vendored or upstream: read for reference, edit only with reason.

QMK documentation available at `~/qmk_firmware/docs`.

## Build

There are no tests; compiling is the only verification.

```sh
qmk compile -kb splitkb/halcyon/kyria/rev4 -km glassbricks -e HLC_TFT_DISPLAY=1 -e TARGET=left
qmk userspace-compile   # every target in qmk.json (left with display, right without)
```

- The root `Makefile` needs `qmk config user.qmk_home` set explicitly; it is not, so `make` there errors.
  Use `qmk compile`.
- Builds and their output land in `~/qmk_firmware`, outside this repo.

## Gotchas

- `hlc_tft_display.c` `extern`s globals straight out of `keymap.c` -- no shared header, and one array
  bound is hardcoded. Renaming or resizing on one side breaks or silently mismatches the other.
- Display state that has to cross the halves needs a split transaction (`KEYMAP_CONFIG_SYNC`), since the
  panel may sit on the slave.
- `update_display()` redraws only on change, off per-element `static` last-value comparisons. New elements
  must follow that; drawing unconditionally costs SPI on every housekeeping tick.
- Everything under `graphics/` is generated: `qmk painter-convert-graphics` for images,
  `qmk painter-make-font-image` then `qmk painter-convert-font-image` for fonts.
- `halcyon.c` owns the `_kb` hooks; keymap and module code hooks in via the `_user` variants.
- Config is layered: `users/halcyon_modules/config.h` (MCU/pins, `LAYOUT_split_3x6_5_hlc`) sits under the
  keymap's `config.h` and `rules.mk`.
