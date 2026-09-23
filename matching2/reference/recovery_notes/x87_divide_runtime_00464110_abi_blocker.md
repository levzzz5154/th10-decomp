# x87 divide runtime at `0x00464110`

Audited against the live Ghidra project `th10.exe` on 2026-09-23. The manifest
keeps the 2,054-byte region `0x00464110..0x00464915` as `kind: asm`, sourced
from `matching2/msvc/src/unidentified/unassigned_00464110.cpp`.

## Ghidra boundary and ABI evidence

Ghidra recognizes `FUN_00464110` from `0x00464110` through the `RET` at
`0x00464226`. Its inferred signature is
`uint __cdecl FUN_00464110(int, uint, ushort, undefined4, uint, uint)`, and its
decompiler emits an integer-only model. The disassembly shows why that model is
not a usable C++ contract: the entry loads two 10-byte extended values from
`[ESP+4]` and `[ESP+0x10]`, performs `FDIVP`, and returns with the quotient live
in x87 `ST(0)`. The nominal integer return is incidental; the division paths do
not set `EAX` to a quotient.

The entry reads and edits the x87 control word with `FNSTCW`/`FLDCW`, performs
range-dependent scaling using constants at `0x004770B0`, `0x004770B4`, and
`0x004770B8`, consults a byte table at `0x004770A0`, restores the saved control
word, and divides. Several paths branch around that work for special exponent
or zero cases. This behavior depends on both the extended operand encodings
and the caller's floating-point state.

The remainder of the source region contains the indexed x87 dispatch and
register-stack adapters. At `0x00464227`, the code masks `EAX` with `0x3f` and
jumps through the table at `0x004770FE`; its target blocks include direct
`FDIV`/`FDIVR` instructions, explicit `INT 6` trap paths, and adapters that
spill/reload x87 values with `FSTP`/`FLD` before calling `0x00464110`. Ghidra
does not define a function at `0x00464227`, but it recognizes two adapter
functions:

- `FUN_004646c6` (`0x004646c6..0x004646d8`) stores two 10-byte x87 values at
  `[ESP]` and `[ESP+0x0c]`, calls `0x00464110`, restores `ESP`, and returns.
- `FUN_004646d9` (`0x004646d9..0x004646eb`) stores those values in the opposite
  order, calls the same helper, restores `ESP`, and returns.

Both have Ghidra's inferred signature `undefined __stdcall FUN_x(void)`, which
also misses the live x87 input/output contract. Ghidra's direct xrefs to
`0x00464110` include the many adapter blocks inside the region and calls from
both recognized functions.

## Why the region remains assembly

This is not a conventional scalar divide function. Callers transfer 80-bit
operands through 10-byte x87 stores in 12-byte stack slots, leave the result in
`ST(0)`, depend on the x87 stack depth/order, and preserve precise control-word
and exception behavior. The selector tail also dispatches on a register value
and manipulates particular x87 stack entries directly. MSVC x86 `long double`
does not provide an ordinary C++ type/ABI for this 80-bit stack interface;
using `double` or a typed wrapper would change precision, stack transfer, or
floating-point state. The current naked assembly is therefore the supported
representation of this contract.

No shared declaration or address alias needs to change for this audit. The
existing `asm_symbols.hpp` entries for `asm_unassigned_00464110`,
`asm_target_004641aa`, `asm_target_004646c6`, and `asm_target_004646d9` remain
the required symbol/address names for the body and its branch/call targets.

No build, probe, or test was run.
