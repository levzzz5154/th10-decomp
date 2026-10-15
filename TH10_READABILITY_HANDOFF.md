# TH10 readability handoff — 2026-10-16

Steps 5 and 6 of the readability plan are complete and verified. The working tree has been committed on `main`.

## What this batch does

- Splits 25 mixed compiler owners and reattributes 121 region records to their physical implementations in the retail source folders.
- Merges 65 compatible fragments into 21 files, keeping compiler scopes and input order.
- Promotes into maintained `src/` ownership:
  - the Hint lifecycle
  - the score factory
  - the archive, item and allocator helpers
  - 46 default C++ recovery sources

  Runtime declarations move to `include/th10/runtime/`.
- Splits the independent x87 setters across their retail owners, with each owner's pinned compiler settings.
- Moves the build machinery into `matching2/msvc/build_support/`:
  - placement manifests
  - exact counterparts
  - compiler wrappers
  - ABI contexts
  - import thunks
  - embedded bytes

  Metadata now lives in `build_support/regions.json` and `build_support/pe_layout.json`.
- Adds `owned_includes` and `compilation_units` support and removes 58 unused cluster specs.

## Fixed at the end

The default build's equivalence check failed at `enemy_execute_0040e770` with "differences are not the recorded set". The cause was not the 6361bef9 renames. A scratch merge script deduplicated every string list in each JSON it rewrote, which damaged 22 `differences` lists in 10 `build_support/layout/equivalent/*.json` files. Those lists repeat instructions on purpose. Restoring them from 6361bef9 made all 40 equivalence checks pass.

The three `source` asset paths in `pe_layout.json` (`rdata.bin`, `data.bin` and `rsrc.bin`) had not been rebased to `../../reference/data/`. They are fixed.

## Verification

- `make`: SHA-256 `19efafbd58a4e4c0…`
- `make EXACT=1`: SHA-256 `2f14760b6fbbf575…`
- Recovered: 100.0% of bytes (322,064) and 100.0% of regions (2,322); 72.7% byte-exact.
- All 40 equivalence checks pass.
- `callsite_abi.py` (`make abi-check`) passes. It needs `capstone`, which is now installed in `.venv`, so run `.venv/bin/python matching2/tools/matching/callsite_abi.py`.
- All 129 unit tests pass, and `git diff --check` is clean.

## Next

- Remaining step 1/3 leftovers: duplicate views such as `game_thread_text_00401a50.hpp` vs `ascii_manager.hpp`, and the screen-effect structs spread across several files.
- The scratch migration scripts in `/tmp/th10_*.py` are one-shot; do not rerun them.
