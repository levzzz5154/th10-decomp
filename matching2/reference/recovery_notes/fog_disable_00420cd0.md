# 0x00420CD0 — disable fog state

## Current source

`msvc/src/render/fog_disable.cpp` now contains ordinary C++ for the routine.
The canonical source symbol is
`RenderStageState_DisableFog_00420CD0` (`_RenderStageState_DisableFog_00420CD0`
in the x86 object). The linker fallback
`_asm_FUN_00420cd0_00420cd0` preserves the raw name used by existing callers.
The associated address macro remains `VA_asm_FUN_00420cd0_00420cd0` at
`0x00420CD0`. The manifest now marks the 53-byte region semantic with
`_RenderStageState_DisableFog_00420CD0` as its canonical symbol and preserves
`_asm_FUN_00420cd0_00420cd0` as the legacy alias. The shared header continues
to declare the raw caller symbol, which the source's linker fallback resolves.

## Ghidra audit

The live program was `/th10.exe`, loaded from
`/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe` (x86 little-endian,
image base `0x00400000`). Ghidra identifies one function from `0x00420CD0`
through the RET at `0x00420D04`, a 53-byte extent. `0x00420D05` begins INT3
padding. Its apparent `__stdcall(void)` prototype is misleading: there are no
stack arguments, and the body consumes a live-in EDI value. It returns zero
when the flag is clear; when set, it returns the result of a device vtable
call in EAX. Both known callers ignore EAX.

Ghidra reports exactly two code references:

| Caller | EDI setup and call | Result use |
| --- | --- | --- |
| `FUN_00402850` (`0x00402850`) | At `0x00402AF1`, `EDI = ESI`; ESI was loaded with `0x00491C28` at `0x00402AE7`. Direct call at `0x00402AF3`. | EAX is overwritten by the following load at `0x00402AF8`. |
| `FUN_00439390` (`0x00439390`) | Loads `EDI = 0x00491C28` at `0x004394BD`; sets `0x00492378` to `0xFF`; direct call at `0x004394CC`. | EAX is overwritten by the following load at `0x004394D1`. |

Thus EDI is an implicit receiver for the global render-stage state, and both
callers pass the same singleton at `0x00491C28`. No other inbound function
references were found. Naming that singleton directly in C++ removes the need
to model a compiler-specific EDI parameter while retaining the observed
behavior. The `0x00439390` frame code independently models the same state
layout: the render-device pointer is at `+0x08` and `fog_dirty` at `+0x750`
(`0x00492378`).

The only direct callee is `FUN_00442F50` (`0x00442F50`). Its live-in ESI is the
animation-manager pointer stored in `data_00491C10`; when its quad count at
`+0x3ADAC8` is nonzero, it submits the pending batch through the D3D device
vtable, updates the manager's batch pointers and clears the count. The fog
routine then clears the singleton's `+0x750` flag and calls the device stored
at `data_00491C28 + 0x08`, through vtable slot `0xE4`, with render-state index
`0x1C` and value `0`. The call result is returned in EAX. If the flag was
already zero, neither the flush nor the device call occurs and EAX is zero.

The semantic source expresses this as `data_00491c10->Flush()`, clears
`fog_dirty`, then returns `device->State(28, 0)`. It uses the global singleton
because both observed callers establish that exact receiver. Existing callers
still target the raw cdecl label through the linker fallback.

## Byte-match status

No build, probe, or test was run for this edit, so the new C++ body's retail
byte match is **unverified**. Before this change, the source was a naked body
with the retail instruction sequence. A prior isolated typed-member probe was
reported as 15/53 matching bytes with its first difference at `0x00420CD1`;
that result does not measure this global-singleton implementation. Exact
codegen and final address ownership still require the normal matching pass.
