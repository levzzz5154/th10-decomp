# DAT cipher: genuine native caller evidence, still unmatched

On 2026-10-02, both cipher entries were inspected through live Ghidra MCP
and compiled in isolated MSVC 13.10.6030 `/GL /LTCG` experiments. Neither
passed its complete byte gate. The maintained assembly owners and
`regions.json` were unchanged; these models receive **zero recovery credit**.
The earlier [cipher behavior note](dat_crypt_0044b0d0_0044b220.md) remains the
semantic reference, but its historical Wine/Ghidra access blockers no longer
apply to this session.

## Calling convention is reproduced natively

Ghidra identifies real decrypt callers at `0x0042A200`, `0x0042B030`,
`0x00434DD0`, and `0x00434F70`, and encrypt callers at `0x00429B60` and
`0x0042B1E0`. Retail takes the rolling key in AL and, in stack order, data,
signed size, byte step, signed block size, and signed limit; both return the
original data pointer in EAX and execute `RET 20`.

The decrypt experiments reused the maintained, complete score-manager graph
in `msvc/layout/ltcg/score_manager_native.json`, including the complete
`LoadSections` caller in `layout/ltcg/score_manager_dependencies/load_sections.cpp`.
The encrypt experiment supplied the complete score serializer's behavior in
`build/archive_cipher_20261002/encrypt/score_save.cpp`: all record checksums,
copies, compression, encryption, and shared-file write/cleanup paths. Its
explicit manager receiver is a diagnostic source representation; the
serializer itself is unmatched and is not claimed to reproduce retail's
private EBX receiver convention.

In both graphs, an ordinary six-argument C++ cipher definition naturally
becomes AL plus five stack arguments and `RET 20`. Symbol decorations such
as `_EncryptDatBuffer@24` describe the source signature, not the resulting
private native convention. No synthetic cipher caller, invented argument,
inline assembly, instruction rewriting, volatile, or barrier was used.
Zero-filled linker gaps and absolute external-symbol metadata supplied only
layout and bindings; retail bytes were used only for comparison.

## Complete native measurements

| Source shape | Retail extent | Native extent | Equal byte positions | First differing byte |
| --- | ---: | ---: | ---: | --- |
| Decrypt, two `for` passes | 323 | 323 | 226 | `0x0044B170` |
| Decrypt, guarded `do` first pass, `for` second pass | 323 | 315 | 243 | `0x0044B126` |
| Encrypt, guarded `do` first pass, `for` second pass | 307 | 307 | 188 | `0x0044B26D` |

Counts compare bytes at equal offsets over the overlapping intervals.
They are diagnostics, not matched regions; a shorter body still fails even
if more positions agree. Native contribution sizes come from the complete
fresh linker MAP contributions at the retail entry addresses.

The exact-extent decrypt baseline matches through `0x0044B16E`. Native then
uses EDI for block length and ESI for block end; retail uses ESI and EDI.
The guarded first pass restores retail's first counter in EAX, byte scratch
in DL, first loop at `0x0044B197`, and second-loop alignment at `0x0044B1C0`.
Its block/end/descending-pointer registers still differ, and it lacks
retail's end reload/store after the second pass. Encryption additionally
swaps the snapshot/cursor slots at `[ESP+10h]` and `[ESP+14h]` and fails to
keep the snapshot cursor in EDI across the outer loop.

Strongest retained complete sources, relative to `matching2/`:

- `build/archive_cipher_20261002/baseline.cpp`.
- `build/archive_cipher_signature_20261002/first_guarded_do.cpp`.
- `build/archive_cipher_20261002/encrypt/first_guarded_do.cpp`, the complete
  caller `build/archive_cipher_20261002/encrypt/score_save.cpp`, and reproducer
  `build/archive_cipher_20261002/encrypt/build.py`.

Complete `cluster.exe` and `cluster.map` evidence is retained below these
directories, relative to `matching2/build/`:

- `archive_cipher_20261002/baseline/clusters/score_manager_native/native-459303ut/`.
- `archive_cipher_signature_20261002/first_guarded_do/clusters/score_manager_native/native-grfzg7jf/`.
- `archive_cipher_20261002/encrypt/first_guarded_do/`.

Machine-readable measurements are in `archive_cipher_20261002/summary.json`
and `archive_cipher_signature_20261002/{results,loop_results,cursor_results,declaration_results}.json`.

## Bounded failed hypotheses and next lever

Const input, shared counters, inline byte/run/block helpers, signed byte
locals and coherent signed key/step signatures, commuted/compound XOR,
real CRT malloc/free names, and speed preference all failed to improve the
323-byte baseline. Wide rolling-key locals, input postincrement, precomputed
half counts, size preference, both-pass or second-pass guarded `do` loops,
direct/late cursor updates, redundant final cursor stores, and four
declaration-order variants also failed. The earlier six explicit increment
permutations were already exhausted and were not repeated here.

The next lever is the cursor storage/lifetime in the asymmetric-loop body:
recover ESI block length, EDI block end, ECX descending pointer, and the
retail second-pass end reload/store; for encryption also recover snapshot
slot `+10h`, cursor slot `+14h`, and the EDI cursor initialization before the
outer loop. ABI discovery, signedness sweeps, and the failed helper variants
need not be repeated. Any new source-lifetime hypothesis must preserve the
full real cipher behavior and pass the entire 323-/307-byte contributions
before a proposal or incremental whole-image integration is warranted.
