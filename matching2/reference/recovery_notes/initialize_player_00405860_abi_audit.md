# `InitializePlayer` (`0x00405860`) ABI audit

2026-10-02 update: the historical recommendation below is superseded by the
verified complete native-LTCG recovery documented in
[initialize_player_native_00405860_2026_10_02.md](initialize_player_native_00405860_2026_10_02.md).
The maintained 397-byte C++ body and the full rebuilt EXE now match retail
byte for byte. The earlier caller and helper ABI observations remain useful
evidence for the genuine graph.

## Result

Keep `0x00405860` as naked assembly for now. The entry and its two direct
callers have an ordinary one-pointer `__stdcall` shape, but the function's
four helper calls depend on values placed in non-argument registers. A
readable C++ body cannot preserve those call contracts with the current helper
interfaces unless the helper cluster is also recovered or register-setting
assembly bridges are introduced.

The fixed-address owner is
`matching2/msvc/src/game/initialize_player_00405860.cpp`. The same naked
definition is duplicated in `matching2/msvc/src/game/player.cpp` near line
201. Both definitions remain unchanged pending a cluster-level recovery.

## Entry and caller evidence

Live Ghidra identifies the entry as `undefined4 __stdcall InitializePlayer(int
param_1)`, with two xrefs in `FUN_00425730`: `0x004259CF` and `0x00425C3E`.
At both sites the caller executes `push esi; call 0x00405860`. The callee
returns with `ret 4`; its first block reads the pointer from the stack and
returns `0xFFFFFFFF` when `[param_1 + 0x28]` is nonzero. The normal path
returns zero. The source-level entry can therefore be described as a
one-pointer stdcall function returning a 32-bit status, but that alone does
not establish that the body can be emitted safely as ordinary C++.

## Helper ABI dependencies

The body calls these helpers, and their live register inputs are visible in
the current Ghidra disassembly/decompilation:

| Call | Inputs at the call | Ghidra evidence |
| --- | --- | --- |
| `0x00448DB0` | `EDI = param_1 + 0x30`, plus stack arguments | Decompilation marks `unaff_EDI`; the callee reads `[EDI]`, `[EDI+4]`, and `[EDI+8]`. The caller sets EDI at `0x004058C6`. |
| `0x0043DD10` | `EBX = 0x26`, `ESI = 0x00492590`, plus one pushed stack value | Decompilation marks `unaff_EBX` and `unaff_ESI`; disassembly reads the stack value at entry and returns with `ret 4`. The caller sets the registers at `0x00405935` and `0x0040593A`, then calls at `0x00405942`. |
| `0x004054B0` | `ESI = [0x0047770C]`, ECX/EDX values, plus one pushed stack value | The function is recovered as fastcall for ECX/EDX but also marks `unaff_ESI`; its disassembly dereferences ESI. The caller loads ESI at `0x00405956` and calls at `0x00405975`. |
| `0x00405500` | `EAX = [0x004776F4]` | Decompilation identifies `in_EAX`; the function accesses fields through that value. The caller loads it into ESI at `0x0040597A`, copies ESI to EAX at `0x00405980`, and calls at `0x00405982`. |

These are not represented by the current C++ declarations in
`asm_symbols.hpp`, which expose the helper entry points as zero-argument
`__cdecl` symbols for use from naked assembly. In particular, ordinary C++
cannot express the EBX/ESI and EDI live-ins through those declarations, and
the EAX-only input to `0x00405500` is not a normal parameter either. Replacing
the body alone would risk silently changing the state passed to the helper
calls even though its external argument is stack-based.

## Recovery path

The existing blocker in `src/game/initialize_player_00405860.cpp` correctly
points toward a native-LTCG cluster covering caller `0x00425730`,
`InitializePlayer`, and helpers `0x00448DB0`, `0x0043DD10`, `0x004054B0`, and
`0x00405500`. Revisit the conversion when those helper interfaces can be
expressed semantically and their call sites can retain the retail register
and stack behavior. No build, probe, or test was run for this audit.
