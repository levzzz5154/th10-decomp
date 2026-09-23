# Floating-text draw callback bridge: `0x0042B9B0`

## Disposition

`matching2/msvc/src/unidentified/FUN_0042b9b0_0042b9b0.cpp` remains the
retail naked body. Its live `regions.json` entry is a 10-byte `asm` region
owned by `0x0042B9B0`; neither that entry nor the source was changed. A normal
C++ declaration cannot express the register-only handoff to the callee at
`0x0042B780`, which consumes its context pointer from `EDI`. No build, probe,
or test was run for this pass.

## Boundary and references

The live manifest assigns `0x0042B9B0..0x0042B9B9` (10 bytes) to
`asm_FUN_0042b9b0_0042b9b0`; the next region begins at `0x0042B9BA`. The
read-only Ghidra view of `th10.exe` has no function object at `0x0042B9B0`, so
function-level decompile/caller queries are unavailable. Raw memory and
`disassemble_bytes` agree on this entry:

```text
0042b9b0  57                 push edi
0042b9b1  8b f9              mov edi,ecx
0042b9b3  e8 c8 fd ff ff     call 0042b780
0042b9b8  5f                 pop edi
0042b9b9  c3                 ret
```

Ghidra reports an unconditional-call xref from `0x0042B9B3` to
`0x0042B780`. Its xref query reports one incoming reference to the callback
entry: a DATA reference from `0x0042B50C` in `FUN_0042b4d0`, where the
instruction pushes `0x0042B9B0` as an immediate callback address. That
initializer then calls
`FUN_00449ed0`, stores its owner pointer at descriptor offset `+0x20`, calls
`FUN_00449b70`, and retains the descriptor at owner offset `+0x0C`. The
maintained symbol declaration names `0x0042B4D0` as
`EffectManagerRuntime_InitializeRetail`.

## Observed ABI and behavior

The callback receives its owner/context in `ECX`, preserves the caller's
`EDI`, copies the context into `EDI`, and makes a no-stack-argument call to
`0x0042B780`. It restores `EDI` and returns without changing `EAX`, so the
callee's return value passes through.

Ghidra identifies `0x0042B780..0x0042B99B` as the callee body. Its displayed
prototype (`undefined4 __stdcall(void)`) is incomplete: the decompile exposes
`unaff_EDI` and uses it as the object base throughout. The body scans 723
0x40-byte records starting at `EDI + 0x3C4`; active records emit their stored
glyph bytes in reverse order through `FUN_00443080`, updating glyph position
and draw state as it goes. This makes `0x0042B9B0` a context-forwarding draw
callback for that floating-text pass.

## Why the naked body stays

A plain `__cdecl` declaration has no context parameter and would not load
`EDI`. A normal `__thiscall` member keeps `this` in `ECX`, but does not specify
that `EDI` must carry it across the call to the existing naked callee; a
`__fastcall` parameter also does not put the context in `EDI`. Preserving the
observed callback entry and the call contract therefore requires an explicit
register bridge. With the requested standard-C++-only promotion condition,
the existing naked body is retained.
