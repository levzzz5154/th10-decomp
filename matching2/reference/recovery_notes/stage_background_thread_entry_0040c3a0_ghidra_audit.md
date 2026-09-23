# Stage-background thread entry 0x0040C3A0: live Ghidra audit

## Boundary and Ghidra state

The live program is `th10.exe` at image base `0x00400000`. Ghidra currently has
no function object at `0x0040C3A0`; address lookup and decompilation report no
function. Raw disassembly gives this exact 18-byte body:

```asm
0040c3a0  mov eax,[0x00477700]
0040c3a5  push ebx
0040c3a6  mov ebx,[eax+0x18]
0040c3a9  call 0x0040c3c0
0040c3ae  xor eax,eax
0040c3b0  pop ebx
0040c3b1  ret
```

The following bytes `0x0040C3B2..0x0040C3BF` are INT3 padding. Ghidra's next
defined function is `FUN_0040c3c0`, whose body ends at `0x0040C43D`. This agrees
with the 18-byte asm region currently assigned to this source in
`matching2/msvc/regions.json`.

## Inbound reference and callback use

Ghidra's only xref to `0x0040C3A0` is the immediate at `0x0040C313` inside
`FUN_0040bd80`: `mov edi,0x40c3a0`. A program-wide search of parsed instructions
found no direct `call 0x0040c3a0`, so Ghidra cannot report ordinary function
callers while this address remains undefined as a function.

At `0x0040C31B`, `FUN_0040bd80` calls `FUN_0044c1c0`. That function stores its
live-in EDI value as the thread start address and passes it, with the supplied
thread parameter, to `__beginthreadex`. The observed inbound use is therefore
thread-start registration through EDI, rather than a direct call. The address
is passed only at `0x0040C313` in the current parsed instruction set.

## ABI and helper dependency

The entry reads the singleton at `0x00477700`, loads its `+0x18` pointer into
EBX, and calls `0x0040C3C0` without stack arguments. It saves and restores EBX,
sets EAX to zero, and returns with plain `ret`. The helper's decompilation
identifies EBX as its live-in object pointer and reads fields at `+0x70`,
`+0x54`, `+0x80`, and `+0x74`. Its two direct callees are
`FUN_00447280` and `FUN_00409e50`.

The private EBX handoff is not expressible by an ordinary standalone MSVC x86
function declaration. There is also a callback-signature wrinkle: the thread
wrapper passes the address to `__beginthreadex`, while this entry's observed
epilogue is plain `ret` rather than `ret 4`. Preserve the retail instruction
sequence and do not normalize the callback prototype without resolving that
stack-cleanup discrepancy. A normal C++ body cannot faithfully replace the
entry while retaining its EBX input to the existing naked helper.

## Symbol integration and recovery decision

Keep the existing naked assembly in
`matching2/msvc/src/unidentified/FUN_0040c3a0_0040c3a0.cpp`. The region record
names `asm_FUN_0040c3a0_0040c3a0`, maps the source to
`_asm_FUN_0040c3a0_0040c3a0`, and owns `0x0040C3A0` for 18 bytes. The source's
`extern "C"` definition supplies that x86 COFF symbol. There is no matching
`asm_FUN_0040c3a0_0040c3a0` declaration or `VA_` macro in
`asm_symbols.hpp`; the inbound asm owner embeds the callback address directly.
The direct helper is already declared there as
`asm_StageBackground_RebindTextureRetail_0040c3c0`. No shared declaration or
manifest change is needed for this audit.

No build, probe, or test was run.
