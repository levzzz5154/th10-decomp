# ECL value dispatch fragments at `0x00411FC0`–`0x00412750`

## Scope and live Ghidra state

Read-only audit of the live `/th10.exe` program at
`/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe`. Ghidra currently has
no function object at `0x00411FC0`, `0x00412300`, `0x00412350`, or
`0x00412750`; `get_function_by_address` returns “No function found” for those
addresses. The executable bytes still disassemble as code at all four entries.
Consequently, Ghidra cannot provide a formal function signature or resolved
code-caller list for them.

The observed incoming references are data references only: `0x0046D0C4` points
to `0x00411FC0`, `0x0046D0C8` points to `0x00412300`, and `0x0046D0CC` points
to `0x00412350`. There is no xref to `0x00412750`. The data references suggest
entries in a callback table, but the table's owner and indirect call sites are
not resolved by the current Ghidra analysis.

## Semantic candidates now in source

`src/unidentified/unassigned_00412300.cpp` models the small four-way accessor
as an `int*` member method. Its observed contract is conventional x86
`__thiscall`: receiver in `ECX`, one selector at `[ESP+4]`, pointer result in
`EAX`, and `RET 4`. The selector is adjusted by `0x2701`; values that normalize
to 0–3 return the addresses of the four consecutive integer fields at
`this+0x1138` through `this+0x1144`, and all other values return null. The
four-entry jump table is separately anchored at `0x00412340`. The 62-byte
method row now ends at its `RET 4` at `0x0041233D`; the two-byte `MOV EDI,EDI`
at `0x0041233E` is separately represented as padding.

`src/unidentified/unassigned_00412350.cpp` models the adjacent 51-way scalar
resolver as a `float` member method. Its observed contract is also conventional
`__thiscall`: receiver in `ECX`, selector at `[ESP+4]`, x87 `ST(0)` float
result, and `RET 4`. The live disassembly of the 51 jump-table targets shows
each return path producing an x87 float: integer fields are converted with
`FILD`, float fields with `FLD`, and the RNG/angle paths return their float in
`ST(0)`. This corrects the earlier source comment that characterized these
leaves as mixed integer/x87 returns. The normalized selector ranges from 0
through 50; out-of-range selectors return the float at `0x00470B04`.

The 51-entry table is separately anchored at `0x004125F8`. Both candidates
are now integrated as semantic region rows using their emitted MSVC member
symbols. The existing jump-table and padding rows remain separate. Exact
compiler output and code/table placement have not been built or byte-compared;
those remain unverified.

## Remaining blockers in this range

### `0x00411FC0` — 616 bytes, ending at `0x00412227`

The entry normalizes its stack selector by `0x2710`, checks against `0x32`,
and dispatches through the 51-entry table at `0x00412228`. Every leaf consumes
the receiver from `ECX` or process globals and the entry returns with `RET 4`.
However, the return register shape varies across leaves: direct integer paths
leave `EAX`, while x87 paths call `FUN_00463B2C`, which Ghidra identifies as a
helper consuming `ST(0)` and returning `EDX:EAX`. The absent indirect caller
prevents establishing how that path-dependent result is consumed. Preserving
the absolute jump-table placement is an additional unresolved code-layout
constraint. Keep the raw entry until the table and its indirect caller
protocol are modeled together.

### `0x00412750` — 56 bytes, ending at `0x00412787`

This fragment reads `EDX` as an index and `ESI` as a base pointer, stores the
incoming `ECX` value at `[ESI + EDX*16 + 0x2494]`, conditionally writes three
stack arguments into the record at offsets `+0x2498`/`+0x249C` and a second
indexed slot, then returns with `RET 0xC`. The entry therefore has two hidden
live-in registers (`EDX` and `ESI`) in addition to `ECX` and three stack
arguments. Ghidra has no function object or xref for this address, so there is
no caller context from which to derive a conventional C++ signature. Keep the
raw entry until its driver/caller cluster is identified.

`0x00412720` was deliberately excluded from this audit; its focused ABI
analysis is in `ecl_set_resource_slot_00412720.md`.
