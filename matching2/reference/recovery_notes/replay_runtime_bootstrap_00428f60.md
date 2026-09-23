# Replay runtime bootstrap at 0x00428F60

## Audit result

The 1,344-byte region remains the retail assembly body in
`matching2/msvc/src/game/replay_runtime_bootstrap.cpp`. Live Ghidra analysis of
`th10.exe` recovers the behavior, but the function's register-only entry and
its helper contracts do not permit a plain MSVC C++ replacement at this
address.

`decompile_function(0x00428F60)` renders the function as
`undefined4 __fastcall FUN_00428f60(char *path)`. That signature is incomplete:
the decompiler also reports `in_EAX` and `unaff_EBX` as live-ins. The first
instructions store EAX at `[EBX+0x10]`; the subsequent comparisons use that
mode value, and ECX supplies the path passed to the replay loader. EBX is the
runtime object. EAX is the return value (0 for success and -1 for load
failure), and the function returns with `ret`, leaving stack cleanup to the
caller.

The direct call at `0x00429684` is the only xref Ghidra reported. Its caller
`FUN_00429610` loads ECX and EAX from its two incoming stack arguments, moves
the allocated runtime from ESI to EBX, and then calls this entry; it tests EAX
afterward. `FUN_00417870` calls that factory with the current mode and replay
path. This confirms the three input values, while showing that the existing
call site supplies them through custom register setup rather than a C++
prototype.

## Recovered behavior

- **Mode 0, create recording runtime:** Store mode, publish the runtime through
  `DAT_00477838`, clear the current stage's prior linked pool with
  `FUN_0042AB20`, and append a new `0x6284`-byte pool through
  `FUN_0042AA50` (saved at runtime offset `0x9C`). Allocate a `0x24`-byte
  replay header with magic `0x72303174`, version 5, and capacity `0x100`;
  allocate the `0x64`-byte config block and zero it after the call to
  `FUN_00418C40`; then allocate and clear a `0x1C4`-byte current-stage record.
  Copy selected runtime globals and optional profile data into the record.
  Create and register three `0x24`-byte scheduler nodes: callbacks
  `0x0042A3D0` and `0x0042A3E0` in the primary scheduler at priorities `0x0B`
  and `0x1B`, plus callback `0x0042A430` in the secondary scheduler at
  priority 5. Return 0.
- **Mode 1, load and restore:** Call `FUN_0042A200(path)`. On its zero return,
  copy the current stage record back into live globals, restore the timer and
  score-gauge fields through `FUN_0042A930` and `FUN_00418B80`, and register
  the same three scheduler nodes. Set the active-stage field at offset
  `0x1D0` to `-1`, then return 0. A nonzero loader result returns `-1`.
- **Mode 2, validate/load path:** Call `FUN_0042A200(path)` and return its
  success as 0; return `-1` when it fails. Other mode values return 0 without
  further work.

The loader at `0x0042A200` copies the path into the runtime, reads
`replay/<path>` unless the memory-replay flag is set, checks the same magic
and version, decrypts and decompresses the payload, and builds per-stage
pointers into the loaded records. The bootstrap's direct offset accesses
depend on those layouts; no production replay-record or runtime type is
available in the current headers.

## Why the assembly remains

MSVC's normal `__cdecl`, `__stdcall`, `__thiscall`, and `__fastcall` prototypes
cannot express this entry as `(runtime in EBX, mode in EAX, path in ECX)`.
Several helpers add more private register contracts: for example,
`FUN_0042AB20` takes the runtime in ECX and stage in EAX, while the scheduler
registration helpers consume a node and priority through ESI and EDI. The
replay/config layouts and the exact nested allocation/initialization order
also have no checked-in production declarations. Replacing the body with
ordinary C++ would therefore require a register-bridging shim and explicit
layout definitions; the shim would still need assembly at this entry.

## Alias and caller integration

`regions.json` maps this region to `_asm_FUN_00428f60_00428f60`. The existing
`include/asm_symbols.hpp` declaration is
`extern "C" void __cdecl asm_FUN_00428f60_00428f60();`; it exposes the symbol
to assembly callers and intentionally declares no C++ arguments. The caller
sets EBX/EAX/ECX itself and reads the integer result in EAX, so the `void`
declaration is only a link-time alias, not a complete behavioral prototype.
Keep that alias, the region mapping, and the caller edge unchanged. A future
typed semantic helper would need a separate ordinary C++ symbol plus an
explicit register bridge or caller-inclusive native-LTCG integration.

## Live Ghidra evidence

- `decompile_function(0x00428F60)` and `analyze_function_complete` report the
  incomplete fastcall view, hidden EAX/EBX live-ins, the xref at `0x00429684`,
  and the callee set including `0x0042A200`, `0x0042AA50`, `0x0042AB20`,
  `0x00418C40`, `0x00418B80`, `0x0042A930`, `0x00449AE0`, and `0x00449B70`.
- `decompile_function(0x00429610)` confirms the allocation, custom register
  setup, result check, and factory return behavior.
- `decompile_function(0x00417870)` shows the game-runtime factory call with
  its current mode and replay path.
- Focused decompilations of `0x0042A200`, `0x0042AB20`, `0x0042AA50`,
  `0x00418C40`, `0x00418B80`, `0x0042A930`, `0x00449AE0`, and `0x00449B70`
  support the helper roles and buffer/list/task observations above.
