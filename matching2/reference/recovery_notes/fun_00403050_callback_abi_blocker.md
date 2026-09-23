# `0x00403050`: callback adapter has a private `EAX` target ABI

Checked against the live Ghidra project `th10.exe` on 2026-09-23. The current
manifest keeps `0x00403050..0x00403056` (7 bytes) as `kind: asm`, sourced from
`matching2/msvc/src/unidentified/FUN_00403050_00403050.cpp`.

## Entry and observed edge

Ghidra has no function object at `0x00403050`, and `get_function_callers` cannot
report a function caller there. Its byte listing is nevertheless clear:

```text
00403050  8B C1             mov eax, ecx
00403052  E9 C9 F6 FF FF    jmp 00402720
```

The only xref to the entry is a data reference from `InitializeGameState` at
`0x00402355`. The decompilation shows the corresponding function pointer
passed to `FUN_00449ed0` at `0x00402367`; that routine allocates a callback
record and stores the pointer. This is callback-registration evidence, not a
direct call site from which to recover all invocation details.

Ghidra recognizes `0x00402720` as `FUN_00402720`, but gives it no parameters
and reports `in_EAX` as a phantom input. The thunk supplies its object pointer
by moving the incoming `ECX` value to `EAX`, then tail-jumping. Ghidra reports
no ordinary callers for `FUN_00402720`; its only xref is the branch from
`0x00403052`. The target is a 304-byte body with many state offsets and
callbacks. Its checked-in implementation remains naked assembly in
`matching2/msvc/src/game/bullet_manager.cpp` and its manifest row is still
`kind: asm`.

## Why this entry is not independently expressible as ordinary C++

The seven-byte region is an ABI adapter: it accepts an object in `ECX`, places
that value in `EAX`, and transfers control without creating a new stack frame.
A normal C++ call to the target cannot express its hidden `EAX` input using the
observed no-argument target prototype. Replacing the thunk with an ordinary
wrapper would require either retaining an assembly bridge or first recovering
and converting the 304-byte target together with its private register-based
helper calls. That dependency and its callback invocation contract are outside
this isolated region.

Therefore this pass leaves the source and manifest unchanged. The callback
registration and instruction behavior are known, but the target's `EAX` ABI
and unconverted body prevent a standalone, inline-assembly-free C++ conversion.
No build, probe, or test was run.
