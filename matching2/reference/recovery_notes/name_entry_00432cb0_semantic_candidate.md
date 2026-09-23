# Name-entry update recovery note — `0x00432CB0`

Date: 2026-09-23

## Disposition

The 1400-byte (`0x578`) production region remains the retail naked body in
`matching2/msvc/src/game/name_entry.cpp`. No semantic sidecar or uncompiled
candidate was added, and `regions.json` was not changed. The behavior is
recoverable at a useful level, but this pass did not establish an ordinary
C++ entry and helper-call ABI that can replace the existing body without
inline assembly.

## Live Ghidra evidence

The open Ghidra program was `th10.exe`. `FUN_00432cb0` has one caller,
`FUN_0042cdf0`, at `0x0042D000`; the caller pushes `EBX` and calls the target.
Ghidra presents the target as
`undefined4 __thiscall FUN_00432cb0(void *this, int param_1)`, with `this` in
`ECX` and `param_1` at `Stack[0x4]`. The raw entry instead makes its relevant
state pointer explicit: after `push ecx; push ebp`, it loads `EBP` from
`[esp+0x0c]`, which is the one stack argument. Every return sets `EAX` to 1,
restores the saved `ECX`, and executes `ret 4`. The caller's `ECX` value is not
explicitly initialized for this call. Thus the decompiler's automatic
`__thiscall` parameter does not establish a meaningful receiver; a normal
replacement would need to preserve the observed one-stack-argument,
callee-cleanup behavior and decide whether the `ECX` preservation is part of
the callable contract.

The live disassembly and decompilation show a four-way switch on the argument
object's `+0x20` field. The jump table is stored at `0x00433218`, inside the
owned region, with entries targeting `0x00432CCC`, `0x00432EDA`, `0x00432F00`,
and `0x004331AC`. The function's final `ret 4` is at `0x00433213`; the region
also owns the alignment bytes and that four-entry table through exclusive end
`0x00433228`.

The sole caller dispatches this callback when its outer game-state value is
`0x0f` (the `case 0xf` branch in `FUN_0042cdf0`). The target's own phases are:

- `+0x20 == 0`: initialize the name-entry state, play `bgm/th10_17.wav`,
  install animation resources, set up timer state, copy the current eight
  character name into the local buffer at `+0x58dc`, and initialize the
  alphabet cursor and last non-space position. A negative result from
  `FUN_00421fa0` selects the failure path and sets `+0x58ec`; otherwise the
  editable path initializes `+0x58f4`, `+0x58fc`, `+0x59c4`, and `+0x58e8`.
  Initialization falls through to the phase-1 timer check.
- `+0x20 == 1`: wait until `+0x2b4 > 6`, then set timer target 2.
- `+0x20 == 2`: process directional input while `+0x58ec == 0`. The cursor
  moves by one or by thirteen entries; the special alphabet entries insert a
  space, delete the previous character, or commit the name. Confirmation
  copies the buffer into the selected record, resets the visible name buffer,
  and targets phase 3. Input transitions queue animation resources and return
  the constant result 1.
- `+0x20 == 3`: after `+0x2b4 >= 6`, clear the four installed animation slots
  and disable timer owner `0x10`.

## Integration blocker

The entry and its callees use register contracts that a direct typed C++ call
does not express. The current `asm_symbols.hpp` declaration for this symbol is
`extern "C" void __cdecl asm_FUN_00432cb0_00432cb0()`; converting the entry to
the observed one-stack-argument / `ret 4` form requires changing that shared
declaration and its manifest classification, both outside this task's owned
files. More concretely, important helper calls pass live arguments in
nonstandard registers:

- At `0x00432D04`, the caller sets `EDI` to slot `0x5e` and pushes the state
  pointer before calling `0x0042C670`. The callee indexes the state's slot
  table with `EDI` (`[EBP + EDI*4 + 0x2c4]`). The same helper is called with
  several other `EDI` slot values.
- The teardown helper `0x0042C6D0` reads its object from `EDI` and its slot
  index from `ESI`, with no explicit stack arguments.
- `0x0043DC90` is called with an animation manager in `ECX`, resource id in
  `EDI`, and a stack flag. Its decompiled `__thiscall` prototype does not
  capture the `EDI` input.
- Cursor helper `0x0044BEA0` receives the cursor pointer in `EAX` and a delta
  on the stack.

These conventions are visible in both the caller and callee disassembly; an
ordinary `__stdcall`, `__thiscall`, or `__fastcall` declaration cannot marshal
the `EDI`/`ESI`/`EAX` inputs. Faithful C++ would first need reusable non-ASM
entry adapters or recovered semantic replacements for those helpers. This
source-only pass cannot supply the shared ABI declarations/adapters or promote
the `kind: "asm"` ownership row. The existing exact retail body is therefore
retained pending that dependency.

## Sources inspected

- Live Ghidra `th10.exe`: `FUN_00432cb0` decompilation, disassembly, callers,
  callees, and variable storage; caller `FUN_0042cdf0`; callees
  `FUN_0042c670`, `FUN_0042c6d0`, `FUN_0042c620`, `FUN_0043dc90`, and
  `FUN_0044bea0`.
- `matching2/msvc/src/game/name_entry.cpp` and
  `matching2/msvc/src/game/title_menu_runtime.cpp`.
- `matching2/msvc/include/asm_symbols.hpp` and the existing `0x00432CB0`
  entry in `matching2/msvc/regions.json`.

No build, probe, or test was run for this note.
