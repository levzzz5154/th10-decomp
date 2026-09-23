# Sprite test overlay callback shim at `0x0040ABF0`

## Disposition

Keep `0x0040ABF0..0x0040ABF9` as the existing naked assembly definition in
`matching2/msvc/src/unidentified/FUN_0040abf0_0040abf0.cpp`. The shim's
receiver transfer is clear, but its direct call uses a private register input
that a normal MSVC x86 C++ declaration cannot express. No source or manifest
promotion was made.

## Live Ghidra evidence

Queried the open `th10.exe` program on 2026-09-23. Ghidra has no function object
at `0x0040ABF0`: `get_function_by_address`, `get_function_signature`,
`disassemble_function`, and `decompile_function` report no function; caller
lookup likewise reports no function, and `get_xrefs_to(0x0040ABF0)` reports no
references. The byte-range disassembly succeeds and gives:

```asm
0040abf0  push edi
0040abf1  mov  edi, ecx
0040abf3  call 0x0040a940
0040abf8  pop  edi
0040abf9  ret
```

The only outgoing code reference from this body is the direct call at
`0x0040ABF3` to `0x0040A940`. Ghidra recognizes the callee as
`undefined4 __stdcall FUN_0040a940(void)`, and its decompilation repeatedly
uses `unaff_EDI` as the object pointer, including reads at offsets `+0x30`,
`+0x38`, `+0x114`, `+0x34`, `+0x1EC`, `+0x678`, `+0x674`, and `+0x684`. It
returns integer `1` in EAX on its paths. The callee's function-caller query
does not report a containing caller for the shim's call site, while
`get_xrefs_to(0x0040A940)` does report `0x0040ABF3` as an unconditional call.

## ABI blocker

The shim receives its context in ECX, preserves the incoming EDI, copies ECX
to EDI for the call, restores EDI, and leaves the callee's EAX result intact.
The wrapper entry could be represented with an ECX-based C++ entry shape, but
the direct callee boundary cannot be represented by a normal MSVC x86
function-pointer declaration: `__cdecl`/`__stdcall` use stack arguments,
`__thiscall` uses ECX, and `__fastcall` uses ECX/EDX; none supplies the
callee's object pointer in EDI. The current `asm_FUN_0040a940_0040a940`
declaration has no formal parameters even though the body consumes EDI.
Replacing the naked transfer with an ordinary typed C++ call would therefore
not preserve the observed register contract. A recovered typed callee or a
compiler-visible project-level register-ABI mechanism is needed before this
shim can be converted without keeping assembly at the call boundary.

No build, probe, or test was run.
