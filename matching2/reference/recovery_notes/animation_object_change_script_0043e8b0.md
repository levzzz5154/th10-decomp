# Animation object script change at `0x0043E8B0`

## 2026-10-01 caller recovery

The real handle wrapper at `0x004496D0` is now ordinary C++ in
`src/render/animation_handle_change_script_004496d0.cpp`. Its complete
36-byte body passes the focused native-LTCG probe, with handle EAX, script
index on the stack, and RET 4. The global manager goes into EDX; the four-byte
ID record stays on the stack for the real `0x004491C0` lookup. The returned
object stays in EAX for the real `0x0043E8B0` script changer, with index ECX
and resource EDX.

`layout/ltcg/script_change.json` selects only that wrapper. The compiler sees
a complete C++ script-change body and the real lookup as unselected ABI
anchors. The lookup anchor's entire 73 bytes match retail. The script-change
anchor has the original 287-byte extent and correct entry/call conventions;
22 bytes differ in register homes and entry scheduling, so its body is not exported
or classified as recovered. The genuine 287-byte assembly region remains the
callee in the final executable. The compiler context and layout gaps are also
unselected. Neither instruction nor address bytes are patched.

The caller-inclusive experiments supersede the old standalone 40-byte match.
See `embedded_child_and_position_wrappers_2026-10-01.md` for the preceding
animation recovery and `animation_array_tick_and_script_change_handle_2026-10-01.md` and its
companion evidence record for this interval. The older discussion below describes the prior checkpoint.

## Prior disposition

Keep `src/render/animation_object_change_script_0043e8b0.cpp` as the retail
assembly overlay until a caller-inclusive native-LTCG replacement is
available. A prior native attempt matched 40 of the 287 retail bytes and
first diverged at `0x0043E8C3`; the mismatch follows the entry-state and
prologue schedule, not an unresolved behavior branch.

## Live Ghidra boundaries

The `th10.exe` analysis identifies one direct caller, `0x004496D0`, and one
callee, `0x0043EE30`. The entry contract is:

| Value | Entry location | Use |
| --- | --- | --- |
| Animation object | EAX | Receives the reset and script fields |
| Script resource | EDX | Supplies the script table, loading state, and resource ID |
| Script index | ECX | Selects the script slot and is stored at object `+0x38A` |

The function returns with a plain `RET`. On the no-op paths, EAX remains the
incoming object pointer; after the successful path, EAX contains the game
state manager loaded from `0x00491C10`. The sole caller does not use the return
value.

At `0x004496D0`, the object returned in EAX by `AnimationManager::Find` is
passed directly to this function. The caller loads the selected index into
ECX and the resource pointer from object `+0x308` into EDX. This is why a
standalone C++ function declaration does not describe the actual entry: EAX
is a live object input but is not an argument in the x86 MSVC C++ conventions
used by the current build.

The call at `0x0043E9BE` enters `0x0043EE30` with ECX zero, EDX equal to the
updated object dword at `+0x6C`, and the object pointer pushed on the stack.
The VM reads that stack argument and returns with `RET 4`. Its caller-visible
shape can be declared as a three-argument x86 `__fastcall` edge (first two
values in ECX/EDX, third on the stack), although the shared assembly symbol
currently has an untyped zero-argument declaration in `asm_symbols.hpp`.

The live analysis calls `0x0043E8B0` `__fastcall(index, resource)`, with those
two values in ECX/EDX; it separately identifies the object use as a phantom
incoming EAX value. The caller/callee instructions and the register values at
the helper call were checked against `disassemble_function` and the owning
source overlays.

## Recovered behavior

The resource's script table pointer is at `+0x11C`, and its loading flag is
at `+0x124`. If the selected slot is null or the resource is loading, the
function leaves the object unchanged. Otherwise it:

1. Stores the index at object `+0x38A` and the resource pointer at `+0x308`.
2. If animation flag `0x200` is set, multiplies the float at `+0x3C` by the
   float at `0x00470B60`. The later word reset and masks leave the low flag
   word as `6`; the upper half of the original flag dword is preserved.
3. Writes `0xFFFFFFFF` at `+0x2FC`; clears dwords `+0x60`, `+0x64`, `+0xB4`,
   `+0x100`, `+0x12C`, `+0x178`, `+0x1B4`, `+0x200`, and `+0x22C`; and writes
   `0xFFF0BDC1` temporarily at `+0x5C` before its final value becomes
   `0xFFFFFFFF`.
4. Copies the resource's 16-bit ID from `+0` to object `+0x386`, and copies
   the selected script pointer to object `+0x38C` and `+0x390`.
5. If object flags at `+0x6C` do not have bit 0 set, sets that bit and
   initializes `+0x68` to `0x00476F78`. It then clears `+0x60` and `+0x64`,
   sets `+0x5C` to `0xFFFFFFFF`, and clears bit 0 in the animation flag dword.
6. Calls the animation VM and increments the dword at
   `*(void**)0x00491C10 + 0x4C`.

## Native-LTCG next step and limits

The existing `layout/ltcg/load_script_preserving_state_0043e7e0.json` uses
`0x0043E8B0` as a synthetic compiler-context address for a different loader;
it does not compile or validate `AnimationObject_ChangeScript`. A dedicated
layout must include the real `0x004496D0` caller and this entry, allowing the
Find result to stay live in EAX across the call. The VM edge can remain an
assembly boundary if its declaration is corrected to the observed ECX/EDX/
stack shape. Then tune from `0x0043E8C3` and compare the full 287-byte region.

This note records Ghidra-backed behavior and ABI evidence; it does not prove
byte equivalence. No build, probe, or test was run during this review.

## Retry (2026-10-02)

The anchor model in `script_change` is 22 bytes from retail, all of them the
ESI/EDI swap (retail: script in ESI, index in EDI). Promoted temporarily as an
additional source of the cluster and probed: all six parameter orders give the
same body (three of them also break the 0x004496D0 caller), and neither a
split early return, a re-read of `scripts[index]`, dropping the `flags` local,
a chained base/cursor store nor a `short` copy of the index moves either
register. The tree was restored; the region stays assembly.

## c2 trace (2026-10-03): why script and flags swap ESI/EDI

Traced `Spillcosts` and `ChoosePhysReg` in c2.dll for the anchor model in the
`script_change` cluster. The register order is decided by candidate priority,
and the model loses by two points:

| candidate | priority | register (model) | register (retail) |
| --- | --- | --- | --- |
| flags | 44 | ESI | EDI |
| script | 42 | EDI | ESI |

`Spillcosts` walks the blocks. For each block it computes `K` = the number of
candidates referenced or flagged live in it (immediates used twice count as
candidates too), then adds `refs * K * weight` to every candidate referenced
there and subtracts `K` from every candidate that is live through the block
without a reference. For the model:

- script = 4*5 (entry) - 2 - 5 - 3 (three blocks it only lives through) + 4*8 (stores) = 42
- flags  = 4*5 (load and test) + 8*3 (or, xor, store) = 44

The immediate `0x200`, shared by the test and the xor, is itself a candidate
(number 2) and raises `K` in both flags blocks. Writing the update as
`(flags | 8) & ~0x200u` removes that candidate, gives script 44 against flags
32, and the body then matches 64 of 66 instructions with every register right;
the only difference left is `and edi,0FFFFFDFFh` where retail has
`xor edi,200h` (and its position relative to the `fmul`). So retail needs a
source that keeps the xor but is worth three more points to script (or three
fewer to flags).

Forms that leave the priorities at 44/42: every spelling of the test and the
xor (shifts, `1u << 9`, split statements, a second local, bitfield test), no
`flags` local, `*=` for the scale, inline helpers taking the object, a `short`
or `int` copy of the index, a `scripts` local, a pointer to the slot. Bitfield
toggles (`flip ^= 1`, `flip = !flip`) expand to five instructions.

Trace recipe: break at 0x107A98EE (`Spillcosts`, EAX = K, `[esp+0x24]` = block
weight, EBX and ESI head the two candidate lists, chained through +0x14; number
at +0x1C, per-block refs at +0x18, priority at +0x0C).

## Ordinary-type follow-up, 2026-10-04

Eight new controls rule out copied/constructed flag value types, script pointer records and reference-returning flag operators: all five ordinary 287-byte bodies are identical and remain 32 bytes from retail after removing the old volatile scale read. Boolean predicates and typed index parameters change extent or ABI. See `script_change_ordinary_type_controls_2026_10_04.md` and the preserved native measurements. No replacement was promoted.
