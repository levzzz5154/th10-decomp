# Replay score draw 0x004329F0 ABI audit

Date: 2026-09-23

Status: retained the exact 689-byte naked baseline. Live Ghidra confirms that
the page pointer arrives through a private `EDI` register contract, which
ordinary MSVC C++ cannot declare or read without an assembly bridge. The
requested no-inline-assembly conversion is therefore not supportable within
this function's current call boundary.

## Evidence

Audited the live `th10.exe` program in Ghidra (x86 little-endian, 32-bit,
image base `0x00400000`). Decompilation of `0x004329F0` reports an
unprototyped `FUN_004329f0(void)` with `unaff_EDI`; the caller xref is
`0x0042D282`. Disassembly of the dispatcher at `0x0042D260` shows:

```text
0042D261  MOV EDI,EAX
...
0042D282  CALL 0x004329F0
```

There is no stack argument at the call. The dispatcher preserves EDI around
the call and restores it afterward. The draw function itself ends in a plain
`RET` (no stack cleanup), sets `EAX` to 1 on both the state-mismatch and draw
paths, and reads the context from EDI. This establishes the inferred entry
contract as an integer-returning function with a hidden replay-page pointer in
EDI, not a standard `void()` function as Ghidra's incomplete signature
suggests.

The active dispatcher source is
`matching2/msvc/src/unidentified/FUN_0042d260_0042d260.cpp`; this task does
not own that caller. Moving its pointer into a conventional C++ parameter
would require changing that dispatcher. A local bridge that copies EDI into a
formal parameter would require inline assembly. Neither option meets this
task's ownership and no-inline-assembly constraints. MSVC `__cdecl`,
`__thiscall`, and `__fastcall` do not express an incoming EDI parameter.

## Recovered behavior

For `EDI + 0x20 != 2`, the function returns 1 without drawing. In state 2 it
uses the `g_pGameThread` pointer at `0x004776E0`, marks its busy field at
`+0x8988`, and sets its current row color at `+0x8974`. Unless
`EDI + 0x1D4` suppresses the entry list, it walks ten rows from the replay
record storage rooted at `0x0047783C`, using the page at `EDI + 0xFC`, the
selector at `EDI + 0x24`, a `0x437C` selector stride, and `0x18` bytes between
rows. Each row has a score/name/stage display. A zero timestamp at row offset
`+0x28` selects the placeholder-date format; otherwise the function calls
`_localtime` at `0x00452BAA` and formats the date, difficulty label, and clear
percentage. It advances the color shade by `0x10` and row position by 15 for
each of the ten entries. The footer always formats the current score, elapsed
time, and selected stage score. It restores white row color, clears the busy
field, and returns 1.

The globals and call edges remain weakly typed in the active recovery layer:
`g_pGameThread` is a `void *` global, while Ghidra still identifies
`0x0047783C` as `DAT_0047783c` of type `undefined4`. The two helper calls are
separately assembly-owned: `_localtime` at `0x00452BAA` and the cdecl
variadic `AppendFormattedGameThreadRecord` at `0x00401630`. Their ordinary
call conventions appear expressible with local typed wrappers, but doing so
does not solve the entry's EDI-only input contract or supply the replay-table
layout.

The archived semantic reference in
`matching2/reference/legacy_semantic/src/game/replay_score_draw.cpp` gives a
useful behavioral sketch, but its `ReplayScore_Draw(page, env)` signature is
not the retail call ABI: the caller pushes neither parameter and passes its
context in EDI. Its separate environment/data abstraction also is not a
verified layout for `0x0047783C`.

## Production symbol and integration constraints

The active region remains `kind: asm`, symbol
`_asm_FUN_004329f0_004329f0`, address `0x004329F0`, size `689`, in
`matching2/msvc/regions.json`. `matching2/msvc/include/asm_symbols.hpp`
provides the matching `asm_FUN_004329f0_004329f0()` declaration and
`VA_asm_FUN_004329f0_004329f0` address alias. Keep those bindings and the
current body together while the caller boundary remains unchanged. A future
semantic promotion needs an ABI bridge or coordinated caller change plus a
verified typed view of the replay storage; it cannot bind the archived
two-argument function directly to this region.

No build, probe, or test was run, per task instruction.
