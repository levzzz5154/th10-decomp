# 0x0043A6F0 private-ABI audit

## Boundary and references

The live Ghidra program is `th10.exe` (`x86:LE:32:default`, image base
`0x00400000`). Ghidra reports no Function at `0x0043A6F0`; its data-region
analysis classifies `0x0043A6F0..0x0043A6FF` as undefined data named
`DAT_0043a6f0`, with an xref count of zero. Function lookup and decompilation
at the entry therefore fail. A program-wide instruction search scanned 124,633
instructions and found no `call` operand containing `43a6f0`. There is no
static caller set from which to infer an actual calling contract.

The raw bytes at `0x0043A6F0` are
`51 88 24 24 88 44 24 01 66 8B 04 24 59 C3 CC CC`. The first fourteen bytes
match the wrapper body; the final two `CC` bytes are padding. Ghidra's byte
pattern search finds that fourteen-byte sequence at `0x0043A6F0`. The manifest
now assigns its fourteen code bytes to the C++ function
`SwapLowWordBytes_0043a6f0` and retains the original assembly ownership under
`previous_record`. Five padding bytes precede the body at
`0x0043A6EB..0x0043A6EF`; two follow it at `0x0043A6FE..0x0043A6FF`. The
next Ghidra function begins at `0x0043A700` and ends at `0x0043A724`.

Ghidra finds no references to or from `0x0043A6F0`, and the xref map for the
entire sixteen-byte body-plus-padding window is empty. The neighboring
`0x0043A6E0` data region has references to its first byte from `0x0043A69A`,
`0x0043B86F`, and `0x0043AE02`; none target the owned body at `0x0043A6F0`.
The source-level name does not establish a Ghidra function boundary; Ghidra
currently names the address `DAT_0043a6f0`. No other source references its
old linker symbol. The replacement has the same entry address and full bytes.

## Register behavior and exact C++ recovery

The fourteen-byte sequence decodes as:

```asm
push ecx
mov  byte ptr [esp], ah
mov  byte ptr [esp+1], al
mov  ax, word ptr [esp]
pop  ecx
ret
```

The two byte stores **swap** the low word: input `AX=0x1234` produces
`AX=0x3412`. The sequence restores `ECX`, balances `ESP`, preserves the high
half of `EAX`, and leaves flags unchanged. It has no calls, helper dependencies,
or stack arguments.

The production C++ signature uses GCC i386 `regparm(1)` to receive a 16-bit
word in `AX` and return it there. A four-byte volatile union exposes the two
ordered byte stores and the word reload; the pinned GCC profile's existing
`-Oz -fcall-saved-edx` settings choose `push ecx` for that four-byte stack
home. An ordinary compiler-generated focused probe matched **all 14 bytes**
without inline assembly or byte patching. The same profile's output with a
two-byte scratch instead uses `[esp+2]`; without saved EDX it begins with
`push edx`. Neither alternate is equivalent to the retail bytes. Since no
static caller is known, this source models the proven AX-level transformation,
not a claimed historical C++ declaration.

The integrated full build remains byte-identical across all **487,936**
executable bytes. After this promotion it reports 1,784 ordinary C++ regions
(90,928 bytes) and 519 remaining assembly regions (232,112 bytes). A separate
host smoke exercised `0x1234→0x3412`, `0x00FF→0xFF00`, `0x8001→0x0180`, and
`0x0000→0x0000`; the x86 exact-byte probe supplies the ABI check.
