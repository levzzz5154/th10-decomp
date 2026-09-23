# 0x0042E5A0 semantic recovery candidate

## Disposition

Keep `matching2/msvc/src/game/fun_0042e5a0_0042e5a0.cpp` as the current retail
assembly definition. Do not add a parallel semantic implementation yet. The
behavior is recognizable as the options-volume display/update routine, but its
live entry contract is an EDI-carried receiver. The current C++ owner cannot
express that entry ABI while preserving the existing retail caller.

No build or byte probe was run for this review, as requested.

## Live Ghidra evidence

Target: open `th10.exe` in project `th10`, queried 2026-09-23.

- `get_function_callers(0x0042E5A0)` reports one caller: `FUN_0042D920`.
- In the caller disassembly, the first call at `0x0042D96A` is preceded by
  `mov edi, ebp`; `EBP` is the caller's panel pointer. Later calls at
  `0x0042DD36`, `0x0042DD4E`, `0x0042DD69`, and `0x0042DD81` likewise load
  `EDI` from `EBP` immediately before calling `0x0042E5A0`. These calls do not
  push a receiver or set `ECX` for the call.
- The callee decompilation uses `unaff_EDI` as its receiver and repeatedly
  reads or clears `*(unaff_EDI + 0x2C8)`. After the initial volume-byte load,
  it saves `EBX`, `EBP`, and `ESI`, but leaves `EDI` live. The decompiler's
  displayed `__fastcall`/`param_1` signature therefore does not describe the
  actual call-site contract.
- The region is still one `kind: "asm"` owner at `0x0042E5A0`, size 3,999
  bytes, in `matching2/msvc/regions.json`; the next region begins at
  `0x0042F53F`.
- Ghidra reports 1,170 instructions, 317 basic blocks, 476 CFG edges, 84 call
  sites, and cyclomatic complexity 161 for this function. Its unique callees
  are `FUN_0043E460`, `FUN_0043E5A0`, `FUN_004491C0`, and `FUN_00463B2C`.

## Recovered behavior

The live decompilation shows the routine publishing the music and sound volume
bytes to `DAT_00497854` and `DAT_00497858`, calling `FUN_0043E460` with the
`"SetVol"` resource, then computing `DAT_0049785C` from the music volume with
x87 arithmetic and `FUN_00463B2C` (or writing `-10000` when sound volume is
zero). It uses the manager at `DAT_00491C10` and the panel's `+0x2C8` handle
slot to resolve animation records through `FUN_004491C0`. It walks child
records by the short tag at `+0x38A`, configures digit records through
`FUN_0043E5A0`, and changes the bit-1 state at `+0x35C` according to music and
sound volume ranges.

The existing `DrawOptions(OptionsView&)` in
`matching2/reference/legacy_semantic/src/game/ui_final_runtime.cpp` is a host
model, not an integrated replacement: its ordinary C++ reference parameter,
callbacks, and mirrored view state do not provide the retail EDI entry or the
exact register-based helper calls. Its presence does not remove the ABI
blocker.

## Concrete integration blocker

The retail call sites deliver the receiver only in `EDI`. MSVC x86 C++ entry
conventions available to this source use stack arguments, `ECX` (`__thiscall`),
or `ECX`/`EDX` (`__fastcall`); none consumes a parameter from `EDI`. A C++ body
cannot replace this definition in place without changing the caller or adding
an assembly entry shim. Caller/manifest ownership is outside this recovery
unit, and an assembly shim would retain inline assembly in the region. The
existing manifest also routes all 3,999 bytes through the assembly owner.

Revisit once the caller and region routing can be migrated together to a
compiler-supported C++ entry contract (or a project-level semantic region
mechanism is added). Until then the exact retail definition remains the
integrated implementation.
