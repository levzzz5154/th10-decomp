# Item-spawn resource lowering and compiler provenance, 2026-10-06

The maintained candidate at `0x0041BB00` remains an unselected, complete
819-byte C++ function with two literal diagnostic differences. No production
source, selection, compiler flag, comparison allowance or build tool changed.
The preceding spilling follow-up was progress: its verified compiler trace
identified the byte-only immediate replacement and its controls excluded the
tested counter records and `/G5` family build. This follow-up advances the
separate item-spawn expression-temporary investigation.

## Compiler revision evidence

`reference/compiler_traces/symbols/read_rich_header.py` decodes the Rich header,
checks the DanS padding and recomputes its checksum. Both the oracle and an
existing complete native rectangle graph pass. They share product/build
records `(100, 6030)` and `(90, 6030)`. The native example was actually compiled
as ordinary C++ with `/GL` and linked with `/LTCG` using the installed tools.
The oracle counts are 52 and 1; the example counts are 10 and 1. Numeric
product identifiers are retained instead of relying on guessed product names.

The installed `cl.exe`, `c1xx.dll` and `c2.dll` have fixed file version
`13.10.6030.0`; `link.exe` has `7.10.6030.0`. The decoded records, tool hashes,
file versions, installation record and reader hash are retained in
`reference/compiler_traces/symbols/evidence/rich_6030.json`. This supports the
pinned compiler/linker revision. It does **not** establish an identical
original backend binary, the source of all original translation units, or the
availability of an unverified later VC2003 compiler package.

## Complete genuine-caller controls

The current candidate source/header/evidence receipt was verified before the
controls. The saved recipe is
`reference/semantic_candidates/item_spawn_0041bb00/evidence/resource_graph_followup/reproduce.py`.
Run it from the workspace root. It prepares isolated snapshots and measures
all complete functions, retaining the actual line and polar methods in the
existing no-entry native module. Full sources, commands, comparisons, traces
and proof are retained alongside it.

| Graph | Spawn extent | Literal unequal bytes | Complete exact supporting bodies after diagnostic address normalization |
| --- | ---: | ---: | --- |
| Current pointer resource formal | 819 | 2 | Both line callers, script loader |
| One-pointer constructed resource value formal | 819 | 4 | Both line callers, script loader |
| Pointer formal plus complete real `ConvertItems` caller | 819 | 2 | Both line callers, script loader |

All 23 switch-table bytes are present and equal after diagnostic address
normalization. No emitted function entry collides with a bound external code
address. These are diagnostics; they are not the normal fixed-layout gate.
The resource value control rechecks the earlier aggregate hypothesis using
the current genuine graph and embedded timer, rather than the superseded
synthetic entry.

The `ConvertItems` control adapts the existing full production C++ body to
the candidate's typed `Vector3` position, retaining its original branches and
flash call. Spawn's complete normalized body is unchanged. `ConvertItems` is
retained as a diagnostic public root, which gives its own non-exact 167-byte
contribution instead of retail's private 165-byte body. Its public-root ABI
is not evidence for the original private entry and is not promoted. A fresh
Ghidra query, explicitly targeting `th10.exe`, identifies its actual game
caller as `0x0041B889` in `0x0041AFD0`; that 2320-byte update remains assembly.
The full current decompilation is archived as reference evidence, not as a
complete C++ recovery. A genuine update/convert/spawn graph is still open.

## Read-only allocation comparison

Both compiler replays finish, each with one function cursor reset and no
marker resets. They use the maintained fingerprint-checked temporary-cursor
trace tool. All **3072 raw native code bytes** reproduce their uninstrumented
builds, including complete contributions, switch tables and compiler padding:

| Resource formal | Trace events | Raw `.text` SHA-256 |
| --- | ---: | --- |
| Pointer | 72 | `526605813f01140d2c57d17cc7f59c008515bbc895128bc3ddb635df567f20d2` |
| Value | 66 | `c31765e18dbd97bb3a54cd221d2396eb24589e31d46f7999dbad8e25a386d576` |

The first eleven allocation records agree in opcode, relevant displacement,
cursor and chosen physical register. After them, the pointer graph allocates
a resource-load temporary to EAX. Its cursor advances to ECX, and the first
identifier copy consequently uses ECX. It then allocates the later resource
load to EDX, wraps the cursor to EAX, and assigns the second identifier to
EAX. The value graph lacks those two resource-load allocation records: its
first identifier starts at EAX and its second starts at ECX. The value graph's
later resource load also uses ECX in the final native code. This accounts for
its four literal differences at offsets `0x1AF`, `0x1B4`, `0x1BB`, `0x1C0`.

Thus changing both arguments to values fixes the first copy by changing
allocation history, but changes the second call path. It is not a register
liveness fix or a later encoding fix. No compiler data/registers or allocation
results were forced. A successful source recovery still needs a consistent,
faithful interface and expression representation, or the remaining genuine
caller graph, that produces both retail paths. The next step is not to insert
an artificial call, dead operation or per-arm register shim.

The measured ledger now contains 69 rejected controls. The production total
remains 2254 ordinary C++ regions / 199062 bytes; no new bytes are claimed.
