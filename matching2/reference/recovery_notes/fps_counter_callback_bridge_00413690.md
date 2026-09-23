# FPS counter callback bridge at 0x00413690

Date: 2026-09-23  
Scope: `0x00413690` and the scheduler callback path needed to establish its
entry ABI. The live source remains
`matching2/msvc/src/unidentified/FUN_00413690_00413690.cpp`.

## Result

Keep the ten-byte naked bridge unchanged. It is called through a scheduler
callback pointer with its context in `ECX`, then copies that pointer to `EDI`
before calling `FUN_004135D0`. The callee reads its object from `EDI` and does
not expose an ordinary parameter. A plain C++ call would not reproduce that
register contract.

## Boundary and bytes

The live entry in `matching2/msvc/regions.json` is `asm_FUN_00413690_00413690`
at `0x00413690`, size 10, kind `asm`, owner `0x00413690`; the next entry is six
bytes of padding at `0x0041369A`. Ghidra did not have a function object at
`0x00413690` (`get_function_by_address`, `get_function_signature`,
`decompile_function`, and `disassemble_function` all reported no function).
Its read-only `disassemble_bytes(start=0x00413690, length=10)` result covers the
ten bytes and ends at the `RET`:

| Address | Retail instruction | Bytes |
|---|---|---|
| `0x00413690` | `push edi` | `57` |
| `0x00413691` | `mov edi, ecx` | `8B F9` |
| `0x00413693` | `call 0x004135D0` | `E8 38 FF FF FF` |
| `0x00413698` | `pop edi` | `5F` |
| `0x00413699` | `ret` | `C3` |

This also confirms the helper call is the bridge's only control-flow call.
Ghidra's `get_xrefs_to(0x004135D0)` reports the unconditional call at
`0x00413693`.

## Callback references and entry ABI

Ghidra's `get_xrefs_to(0x00413690)` reports two `DATA` references, not direct
calls:

- `0x004133C5` in `FUN_00413350` stores `0x00413690` in callback-record field
  `+0x08`.
- `0x004132C2` pushes `0x00413690` as the callback argument to
  `FUN_00449ED0` (`SchedulerCallback_Create`).

The current sources `src/game/stats_task.cpp` and
`src/unidentified/unassigned_004132c0.cpp` show those same registrations. In
the `FUN_00413350` setup, the callback record's `+0x20` field is set to its
owner/context object before `FUN_00449B70` registers it. The retained legacy
description calls the 0x8C-byte owner the gameplay stats manager.

The scheduler dispatcher `FUN_00449C00` supplies the callback context in
`ECX`: at `0x00449C6D` it loads `[ESI+0x20]` into `ECX`, then at `0x00449C70`
indirectly calls `[ESI+0x08]`. It consumes the callback result in `EAX` for its
status switch. Thus the bridge is entered with the owner/context pointer in
`ECX`, and its return value is the helper's `EAX` value.

## Helper contract and promotion decision

Ghidra recognizes `FUN_004135D0` as a body spanning `0x004135D0..0x00413683`,
with signature `undefined4 __stdcall FUN_004135D0(void)`. Its decompilation
marks the counter pointer as `unaff_EDI` and accesses fields at `+0x34` and
`+0x20`; its instructions call `FUN_004134B0` and conditionally call
`0x00401690` to append the FPS overlay. The maintained source for this helper
is also naked assembly at `src/app/fun_004135d0_004135d0.cpp`. The readable
legacy semantic description in `reference/legacy_semantic/src/app/fps_counter.cpp`
confirms the update, overlay, frame-skip accumulation, and return value of 1,
but its C++ signature does not model the hidden `EDI` input.

The current bridge is therefore the adapter that moves the scheduler's `ECX`
context into the callee's required `EDI` register while preserving the caller's
`EDI`. Leaving the source unchanged retains this custom ABI exactly. No build,
probe, or test was run.
