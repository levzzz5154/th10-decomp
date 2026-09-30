# Indexed animation resource loading: native memory recovery and surface residual

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

Recovery experiment: `matching2/build/experiments/resource_surface_loading_2026_09_27/`.
Only this note was written outside ignored scratch. Maintained loader owners remain unchanged for parent integration.

## Exact memory loader, 0x00447EC0 (169 bytes)

The normal, complete native probes `attempt05.json` and `attempt12.json` both pass all 169 bytes with zero differing bytes. The body SHA-256 is `3fd6fa35061d50c9cfc778755368d7ffc6032f84af502c25090dd99b57bd2a6c`.

Ready files, relative to the experiment's canonical `msvc/` directory:

- `src/unidentified/FUN_00447ec0_00447ec0.cpp`
- `include/th10/render/resource_surface_loading.hpp`
- `layout/ltcg/resource_surface_loading.json`
- `layout/ltcg/resource_surface_loading_context.cpp`
- `layout/ltcg/resource_surface_loading_clear.cpp`
- `layout/ltcg/resource_surface_loading_archive.cpp`
- `layout/ltcg/resource_surface_loading_log.cpp`
- `layout/ltcg/resource_surface_loading_log.hpp`

`proposal.json` supplies the semantic record `_AnimationLoadMemory_00447ec0@12`, address `0x00447EC0`, size 169. Do not copy the canonical scratch's surface source as a recovered owner: its region is deliberately left classified as asm, and the separate native surface model has not passed.

The source's ordinary noinline stdcall declaration has index, manager and filename parameters. Its repeated-name compiler context establishes the observed private ABI: index ECX, manager EDX, filename EBX, plain RET. No register instructions appear in the C++ source. A formal prototype bound externally would not implement that private ABI; the complete co-visible body and its caller topology matter.

The manager has 32 primary pointers at `+0x3AD4E0`, 32 secondary pointers at `+0x3AD560`, 32 memory pointers at `+0x3AD5E0`, and 32 file-size integers at `+0x3AD660`. The file path scratch is **260 bytes**. Using 256 bytes produces the same 169-byte instruction extent but the wrong `/GS` frame and cookie offsets.

The body clears an existing primary resource, formats the filename with the original `%s` data symbol, loads the archive file with an output-size pointer, logs failure through the original Shift-JIS format symbol, and stores the loaded memory and size on success. It returns -1 on failure and 0 on success. It preserves the retail behavior of checking only the primary pointer before clearing the indexed set.

Complete real dependency bodies are compiler-visible anchors. Both successful links were independently compared against the oracle for every byte:

| Address | Dependency | Size | Different bytes |
|---|---|---:|---:|
| `0x00447EC0` | Selected memory loader | 169 | 0 |
| `0x00447F70` | Indexed-resource Clear | 87 | 0 |
| `0x0044B360` | Archive_LoadFile | 360 | 0 |
| `0x0044B8E0` | TextLog::AppendLine | 201 | 0 |

The anchor copies preserve their actual recovered behavior. Clear uses typed stdcall COM Release calls and the established duplicate memory-zero store barrier. Archive_LoadFile receives filename EAX and its remaining two arguments on the stack. The variadic logger receives its log object EDI. The new context is 57 bytes; it is synthetic and is never counted as recovered game code.

Evidence: `attempt05_full_anchor_checks.json`, `attempt12_full_anchor_checks.json`, `memory_exact_disassembly.txt`, the two normal probe reports, and their fresh native PE/MAP outputs. The regular export records zero changed instruction bytes, zero changed address operands, zero masked bytes, and no oracle bytes used for building.

## Surface loader, 0x00447C80 (576 bytes): unresolved

Ghidra had no Function objects at either address. A fresh bounded, read-only disassembly of all 745 target bytes through `0x00447F68` is retained as `retail_listing.json`; it agrees with both maintained instruction listings. Surface entry is public fastcall: manager ECX, filename EDX, index on stack, RET 4.

The complete typed source model is retained separately under `surface_trials_msvc/`, with trial snapshots `surface_attempt04.cpp` through `surface_attempt10.cpp`. Its D3D device interface uses correct stdcall virtual slots: CreateRenderTarget at `+0x70`, CreateOffscreenPlainSurface at `+0x90`. Image records start at manager `+0x3AD6E0`, contain seven 32-bit fields, and have stride 28. The direct D3DX function declarations have correct nine- and eight-argument stdcall signatures. Cleanup preserves both duplicated temporary Release/zero/free blocks, including the initial-surface-creation failure path that returns -1 without running them.

Eight bounded native source trials were measured, excluding two manifest-only setup failures. Ordinary single-pointer image access produced 539/540-byte candidates; retaining both the image-owner base and image pointer produced 573 bytes with a virtual device, or 581 bytes with inline typed-vtable calls. Volatile captures of the already escaped file-size and memory locals produced the nearest candidate: **575 bytes**, with **326 differing bytes in the 575-byte overlap**, plus the one-byte extent deficit. This remains a failed normal probe; it is not a recovered routine.

The nearest candidate SHA-256 is `257c4dc38a6a7d30e2597d7a51c9fb5268b3a6a20ef17ba303ed199c1f308416`. The native map places all real anchors and the memory loader at their correct addresses. The first byte difference is `0x00447D0D`, the displacement of the early failure jump to its shifted epilogue. The first substantive instruction/register difference starts at `0x00447D5B`: retail stages size ECX and memory EDX, computes index*28 through EAX into EBX, then loads temporary EAX and forms image pointer ESI. Native stages size EAX and memory ECX, computes the base directly in EBX using ADD, and loads temporary later after pushes. The later D3D and cleanup instruction sequences otherwise correspond, but remain displaced. No claim of byte-exact success is made from this correspondence.

A third volatile temporary capture, a zero-instruction `_ReadWriteBarrier`, and equivalent typed-image pointer arithmetic did not improve the nearest result. The barrier and typed-pointer variants emitted identical 575-byte bodies, and the extra temporary capture emitted 575 bytes with 328 overlap differences. The simpler nearest source is restored in `surface_trials_msvc/` without the ineffective barrier.

Evidence: `surface_bounded_measurements.json`, `surface_residual_disassembly.txt`, failed normal `attempt08.json` / `attempt09.json` / `attempt10.json` / `attempt11.json`, and their full fresh native images and maps. No source assembly, masked comparison, synthesized instruction bytes, operand rewriting, or instruction transforms were used.
