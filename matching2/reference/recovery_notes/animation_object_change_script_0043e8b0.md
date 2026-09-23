# Animation object script change at `0x0043E8B0`

## Current disposition

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
