# Screen-effect selector — 0x0043C970

> Integration status (2026-09-28): the exact routine or return correction described here is integrated and passes its maintained normal probe. The combined 487,936-byte executable matches retail byte for byte. See [the fifth checkpoint](native_recoveries_2026-09-28_fifth.md) for current proof. Scratch-only status and parent handoff instructions below describe the original investigation; unmatched and unselected context bodies add no recovered bytes.


The complete original 396-byte contribution at `0x0043C970..0x0043CAFB` now matches as assembly-free C++. It includes the 357-byte executable body, three bytes of compiler alignment, and all nine entries of its compiler-generated switch table. Final normal production probe `probe_final_typed.json` reports exact bytes, zero instruction changes, and zero address-operand changes.

The recovered object is a 0x44-byte screen-effect controller. Its private native convention takes the controller in ESI, draw priority in EBX, and five stack arguments (effect selector plus four parameters), then returns with `RET 20`. EBX is the secondary scheduler priority, not the effect selector: the selector is read into EBP from the first stack argument. Update tasks always use priority 14. The apparent old public stdcall declaration omitted both register inputs.

Fresh live Ghidra decompilation, whole 396-byte memory read, bounded disassembly, and incoming xrefs establish the routine and its sole allocator caller `0x0043C8B0`. Separate fresh caller decompilation, 82-byte memory read, and bounded disassembly retain the actual allocation/call topology. The current Ghidra caller name still says ASCII manager; the callbacks establish broader fade, pulse, and camera-shake behavior.

| Selector | Update callback | Draw callback | Effect |
|---|---|---|---|
| 0 | 43BD40 | 43C1A0 | Fade alpha 255→0 over the viewport |
| 1 | 43C550 | none | Linear camera shake |
| 2 | 43C230 | 43C2C0 | Fade alpha 0→255 over the playfield |
| 3 | 43BD40 | 43C2C0 | Fade alpha 255→0 over the playfield; set initial alpha 255 |
| 4 | 43C460 | 43C500 | Repeating fading color pulse |
| 5 | 43C230 | 43C1A0 | Fade alpha 0→255 over the viewport |
| 6 | 43C310 | 43C3C0 | Two-phase half-opacity fade over the screen |
| 7 | 43C310 | 43C410 | The same fade over the playfield |
| 8 | 43C710 | none | Attack/sustain/release camera shake |

The controller stores update/draw tasks at +08/+0C, effect selector at +10, current alpha at +18, duration or shake strength at +1C, and effect-specific parameters at +20/+24/+28. The +2C release-phase trigger is preserved. The embedded +30 FrameTimer is initialized only when its flag bit 0 is clear, using previous=-999999, current=0, elapsed=0, and speed=&00476F78. It is then always reset to previous=-1 and zero current/elapsed. Resetting its first three words through one shared view reproduces the retail scheduling; the elapsed zero word is IEEE-754 +0.0f. No barriers or assembly are needed. Out-of-range selectors create no task, then still use the existing primary task, matching retail without adding guards.

The isolated native cluster co-compiles all genuine scheduler creation and registration logic. `CreateEffectPrimary/Secondary(context, priority, callback)` are complete free stdcall C++ models of `0044A000/0044A030`. Native LTCG assigns callback EAX, priority EDI, and context on the stack. Both full 43-byte creation models and both full 131-byte registration models independently match their retail bytes in `anchor_evidence.json`. Ordinary argument ordering in those models fixes the previously mismatching callback-address and priority instruction order. The initial member-form model had the correct private ABI but reordered those independent loads.

A complete C++ model of the real allocator caller establishes the controller's ESI and the priority's EBX inputs. Its entire compiler contribution is 77 bytes, versus the retail caller's 82 bytes; this allocator model is unselected and is not claimed as a recovery. It performs the complete observed allocation, timer-flag clear, 0x44-byte clear, ownership-flag set, selector call, and null return behavior. The maintained 82-byte allocator remains untouched. A constructor-based source trial emitted 92 bytes and was discarded. No shortened or fake dependency body is used.

Measured progression: first valid ordinary member-selector model was full 396 bytes with 239 differences; restoring shared-tail case order gave 56 differences; shared timer-word reset gave 31 differences; complete free scheduler models with context/priority/callback argument order made all 396 bytes exact. Typed callback declarations, descriptive controller names, expanded ordinary calls, and layout assertions were then independently re-probed exact.

Artifacts are under `matching2/build/experiments/runtime_selector_0043c970_2026_09_28/`:

- `handoff.json`: explicit five-file promotion list and SHA-256 hashes.
- `msvc/src/game/fun_0043c970_0043c970.cpp`.
- `msvc/include/th10/game/runtime_selector_0043c970.hpp`.
- `msvc/layout/ltcg/runtime_selector_0043c970.json`.
- `msvc/layout/ltcg/runtime_selector_0043c970_context.cpp`.
- `msvc/layout/ltcg/runtime_selector_0043c970_scheduler_create.cpp`.
- `probe_final_typed.json`, `proposal.json`, and `anchor_evidence.json`.
- Fresh evidence: `decompile.txt`, `memory.txt`, `disassemble.json`, `xrefs.txt`, `caller_decompile.txt`, `caller_memory.txt`, and `caller_disassemble.txt`.

Selected source SHA-256: `0482be8d0d08d64cc4e3f3fa8f306fcb50fd754e4f32bdb278ad6522b0a35219`.

Full selected machine contribution SHA-256: `9e40ac9bc381add1419309a8693d4098703383a1c1eb36c294b74b11522acd3b`.

Only the isolated scratch project and this note were edited. The parent integrates the five explicit files, registers the unique native cluster against the current manifest, runs its maintained normal probe, and performs the full executable gate. No oracle instructions are used to build the C++ cluster; no assembly, naked function, emitted opcode array, comparison mask, instruction rewrite, or address rewrite is present.
