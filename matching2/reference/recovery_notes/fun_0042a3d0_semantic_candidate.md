# 0x0042A3D0 — ECX-to-EDI callback bridge

## Current disposition

The complete 10-byte callback is now maintained ordinary C++. Its genuine complete update graph lets LTCG derive the private EDI receiver from the real callback. Fresh probing and literal whole-EXE comparison pass. See [input_recorder_callback_packet_0042a3d0_0042a8a0.md](input_recorder_callback_packet_0042a3d0_0042a8a0.md) and `matching2/build/experiments/input_recorder_2026_10_02/whole_verification.json`. The existing 85-byte packet owner was also cleaned to ordinary typed stores and cursor source, adding zero new credit.

The remaining sections preserve the earlier investigation and its unsuccessful isolated-call model. The earlier conclusion that an assembly bridge was required is superseded by the complete real call graph.

## Live Ghidra evidence

Target: open `th10.exe` in the current Ghidra project, queried 2026-09-23.

- `get_function_by_address(0x0042A3D0)` and
  `disassemble_function(0x0042A3D0)` report no function object. The raw memory
  and byte-disassembly tools do work at this address. `read_memory` returns
  `57 8B F9 E8 F8 F3 FF FF 5F C3 CC CC CC CC CC CC`; disassembly of the first
  ten bytes is `push edi; mov edi,ecx; call 0x004297D0; pop edi; ret`. The
  checked-in augmented listing records the body as `0x0042A3D0..0x0042A3D9`,
  followed by six `int3` padding bytes before the next entry at `0x0042A3E0`.
- Ghidra's xrefs to `0x0042A3D0` are two data references in `FUN_00428F60`, at
  `0x00429154` and `0x00429390`. Raw disassembly at both sites confirms the
  caller writes `0x0042A3D0` to `[ESI+8]`, then calls `FUN_00449AE0`; these are
  scheduler/task registrations, not direct call instructions. The decompiled
  `FUN_00449AE0` enters a critical section and links the ESI node into its
  ordered queue. The Ghidra caller query cannot resolve `0x0042A3D0` because
  the database has no function object there, so the runtime callback
  invocations are indirect.
- The only direct call in the ten-byte body is at `0x0042A3D3`; Ghidra's xref
  to `0x004297D0` records it as an unconditional call. The helper is defined
  from `0x004297D0` through `0x00429A23`. Its displayed prototype is
  `undefined4 __stdcall FUN_004297D0(void)`, but its decompilation repeatedly
  uses `unaff_EDI` as the instance pointer. It accesses instance fields and
  global state, and its decompiled return paths produce `1`.

## ABI and behavior

The entry's first instruction saves the caller's EDI, then copies ECX to EDI.
The direct helper call has no explicit parameters; EDI carries its instance
context. The wrapper restores the original EDI and executes a plain `ret`, so
it has no stack arguments or callee cleanup. It leaves EAX untouched after the
helper call, forwarding the helper's result (which the helper decompiles as
`1`).

The checked-in C declaration uses `void __cdecl` with no formal parameters,
but that spelling does not describe the live ECX-to-EDI register contract. A
normal `__thiscall` or `__fastcall` body can accept a context in ECX, but cannot
make the no-parameter `FUN_004297D0` read it from EDI. Replacing the body with
ordinary C++ would therefore break the direct-call ABI even if its high-level
intent were restated. No source change was made.
