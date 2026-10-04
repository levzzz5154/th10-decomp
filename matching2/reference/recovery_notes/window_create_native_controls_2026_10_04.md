# Window creation native controls, 2026-10-04

`0x00439730` remains its complete 341-byte retail assembly region. A fresh isolated project from current production compiled a readable native-LTCG model with actual Win32 import slots, the real WndProc address, the 40-byte window-class layout, both window-handle publications and the full minimize/sleep/restore sequence. No maintained source, header, layout, compiler contract or ownership changed.

Nine native controls are preserved under `matching2/build/experiments/window_create_2026_10_04/`:

| control | complete native size |
| --- | ---: |
| Explicit ten-field zero constructor | 339 |
| Aggregate `{0}` | 333 |
| Aggregate with all ten zeros | 339 |
| `memset` initialization | 352 |
| Internal-linkage constructor | 339 |
| Internal-linkage `memset` | 352 |
| Fastcall-declared `memset` | 352 |
| Member-declared `memset` | 352 |
| Member with single-call context | 352 |

The constructor and explicit aggregate-all-zero bodies are byte-identical. All five `memset` bodies are byte-identical despite declaration/caller changes. The `memset` model reproduces the first 28 retail bytes, but then saves EBP and loads the instance from the stack, whereas retail leaves EBX as the incoming instance and continues the zero stores. In the constructor model EBX holds zero instead. The loop caller keeps the instance in EBP and pushes it; the single-call context tail-jumps under the same stack convention. Changing only linkage, calling-convention spelling or method spelling therefore does not recreate the original caller's EBX handoff.

The synthetic loop contributes 45 bytes and the single-call context 5 bytes. These are unselected context measurements, not recovery credit. Extent and shifted-entry rejections were preserved; no region sizes or gaps were changed to conceal an oversized/undersized target body. `measurements.json` records actual complete MAP sizes, raw native body hashes, first differences and overlap mismatch counts; an overlap comparison is not a full-byte-gate pass.

The disposable project was restored to the coherent 339-byte constructor model and original loop context. All complete compiler outputs and per-control sources remain archived. The next justified lever is the genuine WinMain caller graph or concrete compiler evidence for its EBX argument selection, rather than another declaration or zero-initializer spelling.
