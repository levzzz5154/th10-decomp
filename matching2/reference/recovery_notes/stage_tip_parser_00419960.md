# Stage-tip parser recovery note: 0x00419960

Date: 2026-09-12

Status: semantic recovery not integrated this pass. The production source and
region manifest entry were restored after the focused semantic probes failed.
The tracked production probe is exact again.

## Scope and production state

Owned region:

- `matching2/msvc/src/game/stage_tip_parser.cpp`
- virtual address `0x00419960`
- required extent `1498` bytes (`0x5da`), ending immediately before the
  `0x00419f3a` six-byte layout gap
- task-specific LTCG layout/context and only this parser's manifest/cluster
  entries

The source is back to the original naked retail body, with symbol
`_asm_FUN_00419960_00419960`, kind `asm`, and size `1498`. No parser LTCG
manifest or context file remains registered. Shared Python tooling and
unrelated worker changes were not edited.

Focused validation after restoration:

```text
python3 -m matching2.tools.matching.probe \
  --source src/game/stage_tip_parser.cpp \
  --oracle matching2/build/oracle/th10.exe \
  --output /tmp/th10-probe-stage-tip-restored --show 32 --json

EXACT
region asm_FUN_00419960_00419960: different_bytes=0, size=1498
```

## Evidence used

The behavioral model was reconstructed from the archived semantic source
`matching2/reference/legacy_semantic/src/game/stage_tip_parser.cpp:185-345`,
the archived record/layout definitions in
`matching2/reference/legacy_semantic/include/th10/game/stage_tips.hpp:17-49`,
IDA's typed entry and user-call comments in `ida/th10.exe.c:420-423`,
`ida/th10.exe.c:28563-28890`, and the augmented Ghidra references:

- `decompiled/ghidra_augmented/functions/00419960.c:32-426`
- `decompiled/ghidra_augmented/functions/00419960.asm:3-26` and the later
  `0x00419bd0` body range
- `decompiled/ghidra_augmented/functions/00419F40.asm`
- `decompiled/ghidra_augmented/functions/0041A050.asm`
- `decompiled/ghidra_augmented/functions/0041A0A0.asm`
- `decompiled/ghidra_augmented/functions/0041AB10.asm`

The current adjacent MSVC routines are the ABI-preserving implementations in
`matching2/msvc/src/script/script_text_reader.cpp`,
`matching2/msvc/src/game/recovery_split_resource_path_0041a050.cpp`,
`matching2/msvc/src/game/recovery_trim_whitespace_0041a0a0.cpp`, and
`matching2/msvc/src/game/recovery_append_node_0041ab10.cpp`.

## Recovered semantic model

The function is a three-argument `ParseStageTips` routine. It loads the named
tips file with the archive loader (`from_disk = 1`), returning `-1` when the
loader returns null. It allocates three `0x1000` scratch buffers for the line,
key, and value, then repeatedly reads and splits trimmed `key: value` lines.
The reader removes line endings/comments and skips empty lines.

The outer state is `current_stage = -1` and `tip_count = 0`:

- `Version` accepts only `0.0`; any other value calls the retail clear-eight-
  buckets helper and takes the cleanup return path.
- `Stage` parses an integer, resets the per-stage tip count, and accepts only
  stages `1..7`; invalid values set the stage to `-1`.
- `StageEnd` sets the stage to `-1`.
- `Tips` is recognized only for a valid stage and while the count is below
  `255`. It allocates and initializes one `0x88`-byte `StageTip`, increments
  the count, and clears the dword at `+0x18` before consuming its property
  lines. A malformed `Text` line without a closing quote exits this inner
  property walk but still reaches the record-finalization path, matching the
  disassembly's branch structure.

The property-to-record mapping is:

| key | behavior | retail offset |
| --- | --- | --- |
| `Pos` | split at the first comma, trim both pieces, parse two integers as floats | `+0x00`, `+0x04` |
| `Text` | take the first quote and the last quote after it, then `strncpy` `0x41` bytes | `+0x1c` |
| `Count` | parse integer | `+0x60` |
| `Time` | parse integer | `+0x6c` |
| `Base` | lookup in the 61-entry table at `0x004744b0` | `+0x68` |
| `Align` | lookup in the 3-entry table at `0x00474494` | `+0x64` |
| `Remain` | parse integer | `+0x70` |
| `Scale` | parse double, store float, clamp to `[-4.0, 4.0]` | `+0x7c` |
| `Color` | parse three comma-separated integers; write first/second/third to bytes `+0x86/+0x85/+0x84` | `+0x84..+0x86` |
| `Alpha` | parse integer | `+0x87` |
| `End` | finish the property walk | — |

After the property walk, it computes
`strlen(name) * scale * 7.5f` at `+0x80`, appends the embedded node to
the current stage list, and, when the duplicate flag is zero, allocates a
second `0x88`-byte record, copies all `0x88` bytes, repairs its owner/next/
previous node words, and appends it to the corresponding list eight slots
later. It frees the three scratch buffers and the loaded file, then returns
zero. The raw call graph and field offsets are consistent with the archived
semantic implementation and the IDA/Ghidra output.

## ABI and register constraints

These contracts are part of the byte shape and cannot be represented by
ordinary source prototypes without checking the generated call sequence:

- Entry is `__stdcall` with manager, filename, and duplicate flag as the
  three stack arguments; the retail epilogue is `ret 0xc`.
- `0x0044b360` receives the filename in `EAX`, the output-size slot and
  `from_disk` on the stack, returns the loaded buffer in `EAX`, and uses its
  own callee cleanup shape.
- `0x00419f40` receives the input cursor in `EAX`; destination, remaining-size
  pointer, and capacity are stack arguments. It returns the advanced cursor
  in `EAX` and cleans `0xc` bytes.
- `0x0041a050` receives the line in `EAX`, value destination in `EBX`, and
  key destination in `EDI`; it has no ordinary three-stack-argument ABI.
- `0x0041a0a0` receives and returns its string pointer in `EAX`.
- `0x004198c0` is `__fastcall` with the compared name in `EDX`; the table
  pointer and count are stack operands, and the first register parameter is
  an ignored compiler artifact. The parser uses table/count pairs
  `(0x004744b0, 61)` and `(0x00474494, 3)`.
- `StageTip_Initialize` is the existing `__fastcall` initializer with the
  new tip in `EDX`; the parser calls it after `operator new(0x88)`.
- `0x0041ab10` receives the list sentinel in `EAX` and the embedded node in
  `EDX`, links at the tail, and returns with a plain `ret`.
- CRT `malloc`/`free`/`atol`/`atof`/string helpers retain their observed
  stack-call forms, but their surrounding register setup is still relevant
  to the parser's exact bytes.

## Semantic/LTCG experiment and mismatch

A temporary readable C++ candidate was built with a task-specific native-LTCG
cluster. Its manifest reserved:

```text
.text$00layout  0x00401000..0x00419960
.text$01parser  0x00419960, size 1498
.text$02layout  0x00419f3a, size 6
.text$03context 0x00419f40, size 77
```

The direct, unclustered focused probe failed before byte comparison because the
candidate contribution was `2057` bytes rather than `1498`:

```text
NOT EXACT
failure: region ... extent 2057 differs from requested size 1498
```

The native-LTCG attempt also failed its layout/context gate. The generated map
was `/tmp/th10-probe-stage-tip-semantic-cluster3/clusters/stage_tip_parser/native-jqtkyv7t/cluster.map`:

```text
.text$01parsetips  length 0x7f9, address 0x00419960
.text$02layout    address 0x0041a159, length 0x6
.text$03context   address 0x0041a160, length 0x4d
```

Thus the parser contribution was about `0x7f9` bytes and pushed the context
to `0x0041a160`, so the probe reported
`native cluster image base or compiler-context entry address differs` before
the body could be compared.

The first generated bytes already show a calling-convention/code-generation
problem, not a small late-tail discrepancy. Retail begins:

```text
83 ec 24 56 6a 01 8d 44 24 34 50 8b 44 24 38
```

The candidate began:

```text
83 ec 28 53 55 6a 01 8d 44 24 28 50 33 db 51
```

The candidate marshalled the archive filename through a normal stack call,
used a conventional stack call shape for the EAX-cursor line reader, emitted
local literal-string comparison code/rdata instead of the retail
`repe cmpsb` comparisons against the fixed `0x0046d5xx` strings, and had a
different prologue/register allocation. These differences explain both the
extent expansion and why changing only the manifest gap sizes would not make
the body exact.

## Next experiment

Keep the restored naked body as the production baseline. The next semantic
attempt should be an isolated parser cluster only after its compiler context
can express or preserve every custom helper ABI above. In particular, test
ABI-safe shims or a coupled helper cluster for the EAX/EBX/EDI calls, bind the
retail lookup/string data at their absolute addresses rather than introducing
new local literals, and require the parser section itself to measure exactly
`0x5da` before registering its context at `0x00419f40`. Compare the focused
probe before changing `regions.json`; coordinate with the existing owners of
the adjacent helper files instead of editing their sources or shared Python
tooling.

## Bounded helper-cluster checkpoint

The requested helper cluster was checked with tracked focused probes after
restoring the production manifest. All four owned helper regions remain
byte-exact in their current ABI-preserving sources; no manifest change is
needed to retain them:

```text
src/game/recovery_leaves.cpp
  asm_Recovery_FindNamedValue_004198c0  0x004198C0 / 98 bytes  EXACT
src/script/script_text_reader.cpp
  asm_FUN_00419f40_00419f40             0x00419F40 / 260 bytes EXACT
src/game/recovery_split_resource_path_0041a050.cpp
  asm_Recovery_SplitResourcePath_0041a050 0x0041A050 / 75 bytes EXACT
src/game/recovery_trim_whitespace_0041a0a0.cpp
  asm_Recovery_TrimWhitespace_0041a0a0  0x0041A0A0 / 114 bytes EXACT
```

The parser was rechecked in the same focused pass and is also restored
EXACT (`0x00419960`, 1498 bytes, `different_bytes=0`). The probe commands
were run against `matching2/build/oracle/th10.exe` with the repository
matching probe; each returned `EXACT` and the listed extent.

No semantic helper candidate passed. The lookup candidate retained the
correct 98-byte extent only under one spelling, but its entry register/load
ordering differed from retail; the explicit comparator spelling produced a
different body. The trim candidate experiments produced bodies of 130, 98,
and 117 bytes (the 117-byte form used a dword-copy sequence instead of the
retail byte-copy loop); the final inline-assembly spelling did not compile
under the cluster's compiler (`C2400`, inline assembler operand syntax).
All candidate sources, temporary manifests, and cluster contexts were
removed, and the two temporary semantic region substitutions were restored.

The next dependency is therefore an ABI-aware semantic bridge for the
uncaptured helper calls, not another ordinary standalone spelling: the
reader's EAX cursor plus stack arguments, split helper's EAX/EBX/EDI triple,
and lookup helper's EDX name plus stack table/count must be expressible in
one native-LTCG context. The parser also depends on the existing raw
`Archive_LoadFile`, `StageTip_Initialize`, and append-node contracts. Until
that coupled context is available, retain the exact helper/parser sources
above and do not promote the failed semantic candidates.

## Addendum: readable `FindNamedValue` body at `0x004198C0`

Date: 2026-09-23

The source body for `0x004198C0` is now ordinary C++ in
`src/game/recovery_leaves.cpp`; the region manifest remains ASM pending a
separate ownership decision. Ghidra shows a linear scan of `recordCount`
eight-byte entries. Each entry contains a NUL-terminated key pointer followed
by a 32-bit value. The helper compares the requested key from `EDX` to each
entry key and returns the matching value in `EAX`, or zero when the count is
nonpositive or no key matches. A value of zero can also be a real table value
(the three-entry alignment table begins with zero), so the return convention
does not distinguish that match from a miss.

The source signature is `unsigned int __fastcall` with an ignored first
parameter, then `key`, `records`, and `recordCount`. This preserves the
observed register/stack layout: the ignored first parameter occupies `ECX`,
`key` occupies `EDX`, the remaining two parameters are stack arguments, and
the callee removes eight stack bytes (`ret 8`). In parser calls at
`0x00419D11` and `0x00419D39`, `ECX` contains unrelated parser-local values
while the key is explicitly placed in `EDX`; the callee never reads `ECX`.
That dummy parameter exists to keep the actual key in the second fastcall
register, not because the lookup needs a context object.

The legacy cdecl declaration from `asm_symbols.hpp` is locally renamed while
that header is included by this translation unit, avoiding a conflicting
prototype without changing the shared header or its existing fastcall symbol
alias. No build or byte probe was run for this edit. The semantic body and
ABI are grounded in Ghidra, but exact compiler output, symbol selection, and
the 98-byte extent remain unverified; the earlier exactness result above is
the historical naked-assembly baseline, not evidence for this C++ body.


## Named-value helper binding (2026-09-23)

The `0x004198C0` region now binds the ordinary C++ fastcall definition as
`@asm_Recovery_FindNamedValue_004198c0@16`. `asm_symbols.hpp` declares the
ignored ECX slot, key in EDX, and two stack arguments. The existing inline
assembly callers keep their instruction sequences and now resolve the matching
fastcall symbol. The old cdecl alias is retained in manifest history and its
raw symbol table. Exact compiler output remains unverified.
