# Every-fourth-byte sum, `0x0044C0B0`

`src/unidentified/unassigned_0044c0b0.cpp` now models the 36-byte region as a
regular x86 `__fastcall` helper:

```cpp
unsigned int __fastcall SumEveryFourthByte_0044c0b0(
    const unsigned char* bytes, int count);
```

## Signature and behavior evidence

Ghidra initially had no function boundary at this address. After defining the
36-byte boundary (`0x0044C0B0..0x0044C0D3`), its analysis reports a leaf
`__fastcall` function with the first argument in ECX and the second in EDX.
There are no direct caller xrefs in the current Ghidra database, so this
signature is based on the entry-register use and instructions rather than a
caller.

The machine code copies EDX, masks the low two bits, and subtracts that
remainder. It then uses signed `JLE` on the adjusted count. That establishes
signed count behavior: a nonpositive count performs no reads. For a positive
count, the loop executes once per complete group of four bytes, reads offsets
`0, 4, 8, ...`, and advances the pointer by four each time. The byte additions
wrap modulo 256. `MOVZX EAX,DL` zero-extends the final byte sum into EAX.

Ghidra's raw parameter recovery reports `undefined4` in ECX and `uint` in EDX;
the latter follows its provisional type flow and does not describe the signed
branch. The `int` count in the source follows the `JLE` semantics. The pointer
is read-only, so the candidate uses `const unsigned char*`.

The assembly proves a zero-extended 8-bit result in EAX, but without callers it
does not distinguish an `unsigned char`, `unsigned short`, or `unsigned int`
source return type. This candidate uses `unsigned int` to model the full
zero-extended EAX value, matching the earlier stride-four model recorded in
[`0044xxxx_wave18.md`](0044xxxx_wave18.md). The return width is therefore a
conservative C++ choice, not a uniquely recovered source type.

## Exactness status

This is a readable semantic candidate only. No build, probe, or test was run.
The earlier ordinary C++ attempt recorded in `0044xxxx_wave18.md` emitted 30
bytes against the 36-byte region, primarily missing the retail count-rounding
prelude; this version has not been measured.

## Manifest integration (2026-09-23)

The region now binds the C++ fastcall definition as
`@SumEveryFourthByte_0044c0b0@8`, while retaining the former assembly record in
`previous_record` and its address alias in the symbol table. Exactness remains
unverified.
