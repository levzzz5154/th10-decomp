# Player reset constructor at `0x004246C0`: measured native residual

The complete, assembly-free C++ candidate compiles to the retail extent of **244 bytes**, but remains unpromoted. Normal probes `attempt02` and `attempt05` both differ in **six register operand bytes**, with the other 238 bytes equal. The maintained region remains the original assembly body in `matching2/msvc/src/game/player_reset.cpp`; its older D3603 comment predates this retained measurement.

Fresh Ghidra evidence for `th10.exe` is retained as plain text in `matching2/build/experiments/player_reset_004246c0_2026_09_27/ghidra_decompile_004246c0.txt` and `ghidra_disassembly_004246c0.txt`. The machine listing spans `0x004246C0` through the plain `RET` at `0x004247B3`. It takes the block pointer in **ESI** and returns it in **EAX**; Ghidra's displayed `void FUN_004246c0(void)` does not express that private register ABI.

The typed candidate preserves the complete instruction-backed operation sequence: clear bit 0 in nine fields of the embedded `0x3AC`-byte slot at `+0x14`; clear that slot and set its `+0x384` short to `0xFFFF`; clear three flags at `+0x470`, `+0x484`, and `+0x498`; clear 128 flag words from `+0x4AC` at stride `0x5C`; clear four animation flags at `+0x3320` and stride `0x98`; clear 33 flag words from `+0x3560` at stride `0x6C`; clear the flag at `+0x431C`; zero the whole `0x4478`-byte block; publish its pointer to `0x00477834`. Stores overwritten by the final clear are preserved. The scratch record names are descriptive layout views, not independently verified gameplay type identities.

The source is `matching2/build/experiments/player_reset_004246c0_2026_09_27/msvc/src/game/player_reset.cpp`. A synthetic, unselected placement-construction loop in `msvc/layout/ltcg/player_reset_004246c0_context.cpp` establishes the ESI receiver under MSVC 13.10 native LTCG. It is compiler context, not recovered retail code.

| Retained normal probe | Compiled size | Different bytes | Result |
| --- | ---: | ---: | --- |
| `attempt01.json` | 244 | 35 | Animation load/store ordering and temporary registers differ. |
| `attempt02.json` | 244 | 6 | Three zero-instruction `_ReadWriteBarrier` intrinsics reproduce the ordering; two temporary registers differ. |
| `attempt05.json` | 244 | 6 | Distinct flag locals and an inline retirement helper emit the identical body as attempt02. |

Attempts 03 and 04 failed to compile because generated declarations contained malformed `second_const` tokens. They produced no byte measurements and do not count as additional register-allocation results.

The six differences are confined to the load, AND, and store for the **first** animation flag (`EDI` in retail, `ECX` in the candidate), and the same three instructions for the **third** flag (`EDX` in retail, `ECX` in the candidate). The second flag's ECX sequence and the fourth flag's direct memory AND already match. Differing byte addresses are `0x0042473F`, `0x0042474B`, `0x0042474D`, `0x00424766`, `0x00424771`, and `0x00424773`; the first differing instruction begins at `0x0042473E`.

Attempt05 source SHA-256: `aff570b214156832f20357c5a0241025a0123c4378e8b858e837623ae0b12dbb`. Attempt02's retained `barrier_source.cpp` SHA-256: `1106b2d33a121a374e962aa79331597112e01c950fea3b97cfcbc3dba2b2b652`. Both compiled bodies have SHA-256 `f29b52106c457aaa47b0c671f6ad3471453b83f9dbe08bde47c72120d33c930e`; the oracle body has SHA-256 `3cb7342902c69e8581681565d5270dcc9b7f131bc311041118fcc84b146a9351`.

The retained probes report zero instruction-byte rewriting, zero address-operand rewriting, zero masked bytes, and `reference_bytes_used_for_build: false`. Full paths, report hashes, source/context hashes, and byte offsets are in `matching2/build/experiments/player_reset_004246c0_2026_09_27/measured_residual.json`.

A concrete next step is to recover the real allocation/call context and express animation subobject lifetime or aliasing naturally in that context. The current placement loop recovers the receiver and exact body length, but the remaining temporary-register choices are unresolved; these measurements do not establish that ordinary C++ cannot match them.
