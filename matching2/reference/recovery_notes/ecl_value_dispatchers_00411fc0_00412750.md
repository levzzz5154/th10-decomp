# ECL value dispatch fragments at `0x00411FC0`–`0x00412750`

## 2026-10-05: floating-point dispatcher recovered byte-exact

`msvc/src/script/ecl_float_value_00412350.cpp` now owns the complete native
884-byte contribution at `0x00412350`: 679 machine-code bytes, one compiler
alignment byte, and 204 bytes of generated switch-table data. The standalone
raw alignment/table rows and the naked assembly source were removed. The
12-byte padding after the table is unchanged.

The original candidate's ABI blocker was stale: this is a public ECX member
receiver, stack integer selector, x87 ST(0) float result, and RET 4. The native
cluster contains the full recovered 67-byte AngleFromPoint body as compiler
context, so the point argument naturally arrives in EAX. No call shim is used.

Three source facts determine the match:

1. Flags occupy the known 32-bit word at `+0x2480`. Returning bit 16 via
   `(flags_2480 >> 16) & 1` produces the retail zero-extension and integer
   conversion sequence. The byte-field candidate masks in AL and then MOVZXs
   the value, which changes subsequent temporary register allocation.
2. The origin-selector pairs (-9991/-9965 and -9990/-9964) are separate source
   cases. Combining each pair into adjacent case labels removes two temporary
   pointer evaluations before register allocation, shifting every subsequent
   pointer temporary and causing an unwanted tail merge with an entity field.
3. Each arm assigns one result variable and breaks. The shared return lets the
   compiler retain the later duplicate origin blocks, as retail does. Direct
   returns keep the earlier copies instead; the extent is still 884 but the
   byte positions and table entries differ.

The last four selectors compare the integer global against float constants
0, 1, 2 and 3. They do **not** test unordered values: after FUCOMPP, TEST AH,44h
and JNP select true for ordered equality, false for inequality or unordered.
The historical candidate is explicitly marked incorrect on this point.

Native strict probe: **884 bytes EXACT**, including all 51 jump-table entries.
No instruction/operand edits, masked bytes, verifier changes, or new equivalent
recovery. Both `make` and `make EXACT=1` passed after integration; the
487,936-byte exact executable has the same SHA-256 as the oracle.
`git diff --check` passed. Artifacts and full build logs are in
`/tmp/codex-ecl-float`.

```sh
python3 matching2/tools/matching/probe.py \
  --source src/script/ecl_float_value_00412350.cpp \
  --output /tmp/ecl-float-value-probe
```

The newly replaced assembly is 679 bytes. The semantic-byte denominator also
absorbs the former 204-byte table and one alignment byte. Current ownership is
72 assembly regions / 101,325 bytes, 186,298 ordinary C++ bytes, and the unchanged
33,860 equivalent C++ bytes. Total reported recovery is 220,158 / 321,483 bytes.

## 2026-10-05: integer dispatcher recovered byte-exact

The older mixed-return blocker below is superseded. `0x00411FC0` is an
integer-returning member function: float paths call the toolkit's `__ftol2`,
then return the integer in EAX. The toolkit symbol is already identified at
`0x00463B2C` in the manifest. No mixed-return ABI or handwritten table is needed.

Production source: `msvc/src/script/ecl_integer_value_00411fc0.cpp`.
Native layout: `msvc/layout/ltcg/ecl_integer_value_00411fc0.json`.
The complete 820-byte compiler contribution (616-byte function plus 51 dword
switch entries) matches retail at `0x00411FC0..0x004122F3`. The old raw table
row and its byte-array definition were removed; its 204 bytes are now generated
by the switch. The following 12-byte padding row is unchanged.

The first native candidate already reproduced every dispatcher instruction
except an extra `push ecx` / `add esp,4` around the handle resolver. That came
from declaring the dependency as a cdecl member with an unused manager
receiver. Expressing the same genuine lookup-and-clear body as a function of
its handle removes that unused argument. LTCG derives the retail ESI handle
convention. Both the full lookup and full validation bodies remain compiler
context, placed at their retail addresses; neither is an ABI stub. The selected
resolver is rooted to retain its public ECX receiver and stack selector.

The production source has compile-time offset checks and a typed signed-short
animation field at `+0x38A`. Resolving a stale handle may update the handle
cache, represented by a mutable member. Case order reproduces retail's body
layout; the compiler also naturally shares the `value_106c` conversion tail
with the current-entity branch. The switch's default covers the unused selectors
and values outside the 51-entry range.

Validation completed:

- Strict native probe: **820 bytes EXACT, zero differences**, including all
  switch entries. No instruction or address operand rewrites, masked bytes,
  retail bytes used to build, or new equivalence registrations.
- `make`: passed, including existing equivalence checks.
- `make EXACT=1`: passed; whole 487,936-byte EXE identical to oracle.
- EXE SHA-256: `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- `git diff --check`: passed.

Probe artifacts and both build logs: `/tmp/codex-ecl-int`. The focused
production probe can be repeated with:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/script/ecl_integer_value_00411fc0.cpp \
  --output /tmp/ecl-integer-value-probe
```

Checkpoint: 73 assembly regions / 102,004 bytes remain. Ordinary C++ is
185,414 bytes; equivalent C++ remains 33,860 bytes. The progress denominator
increased by 204 because the former embedded table now belongs to its complete
semantic compiler contribution. The newly replaced machine code is 616 bytes.

## Historical scope and live Ghidra state

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
