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
owns exactly fourteen assembly bytes there under `asm_FUN_0043a6f0_0043a6f0`
and linker symbol `_asm_FUN_0043a6f0_0043a6f0`; it assigns five padding bytes
to `0x0043A6EB..0x0043A6EF` and two more to `0x0043A6FE..0x0043A6FF`. The
next Ghidra function begins at `0x0043A700` and ends at `0x0043A724`.

Ghidra finds no references to or from `0x0043A6F0`, and the xref map for the
entire sixteen-byte body-plus-padding window is empty. The neighboring
`0x0043A6E0` data region has references to its first byte from `0x0043A69A`,
`0x0043B86F`, and `0x0043AE02`; none target the owned body at `0x0043A6F0`.
The source-level `FUN_0043a6f0` comment is not a Ghidra function alias; Ghidra
currently names the address as `DAT_0043a6f0`. The manifest records only the
canonical linker symbol `_asm_FUN_0043a6f0_0043a6f0`; no second alias or other
source references to that symbol were found.

## Register behavior and conversion decision

The fourteen-byte sequence decodes as:

```asm
push ecx
mov  byte ptr [esp], ah
mov  byte ptr [esp+1], al
mov  ax, word ptr [esp]
pop  ecx
ret
```

The stack round-trip reconstructs the original `AX`, restores `ECX`, and
balances `ESP`; the instructions do not change flags. `EAX`'s upper half is
untouched. The body has no calls or helper dependencies and does not read
stack arguments. Its only observable register behavior is to preserve `AX`
and `ECX` across a plain `ret`.

Normal x86 C++ conventions can return a `uint16_t` in `AX`, but they do not
pass an input argument in `AX`. This body carries its entry `AX` through the
function unchanged; a conventional signature cannot express that register-only
input. A zero-argument `void` function could happen to leave `AX` unchanged in
one build, but that does not express or guarantee the preservation behavior.
Since Ghidra has no function or static callers here, the intended caller
contract is unproven. Retain the byte-exact naked wrapper rather than claiming
a semantic C++ model.
