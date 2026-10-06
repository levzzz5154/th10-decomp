# Genuine item, animation and sound graph, 2026-10-06

This is the historical 31-function / 405-case checkpoint, preserved under
`evidence/collaborator_graph/`. See the [initializer follow-up](item_update_initializer_0041afd0_2026_10_06.md)
for the current 32-function / 473-case graph and fresh production proofs.

Production's existing conversion, power-add and life-add recoveries now pass
their complete raw fixed-address gates under the genuine full item-update
caller. The former synthetic life-counter caller is no longer selected. The
maintained 31-function graph passes **405 bounded retail/native comparisons**,
including actual banner creation and list/sound/UI side effects.

The full update remains unselected: **2,428 native / 2,320 retail bytes**, with
2,214 unequal overlapping bytes and 114 diagnostic instruction groups. Spawn
still has two differences across its complete 819 bytes. Neither receives
recovery credit, and no source or byte comparison is truncated or masked.

## Complete real collaborators

The preceding graph declared animation removal, life icons, sound queuing and
banner creation as opaque calls. Complete C++ callees now accompany the caller:

| Address | Function | Native / retail bytes | Complete diagnostic equality |
| --- | --- | --- | --- |
| `004491C0` | Animation lookup | 73 / 73 | Yes |
| `004492A0` | Animation removal | 66 / 66 | Yes |
| `00413790` | Life icons | 77 / 77 | Yes |
| `0043DC90` | Sound queue | 123 / 123 | Yes |
| `00448D00` | Primary-back creation | 74 / 73 | No |
| `00449870` | Object initialization | 210 / 217 | No |
| `0043E7E0` | Preserving script load | 194 / 194 | Yes |

Visibility of the first four moves the update from 2,452 to 2,428 bytes, while
power-add and life-add initially remain one byte too long (167/142). Adding the
complete actual creator, initializer and preserving loader makes both counter
bodies exactly 166/141 bytes. No invented caller, prescribed register or
compiler entry function is introduced.

The local animation header declares the initializer consistently as
`void InitializeObject(Entity*, int)`, matching its complete implementation.
It is isolated in this graph; the shared production header is unchanged.
The real driver retains the actual second translation unit, full public line
callers and polar methods. All 64 update and 23 spawn switch-table bytes remain
part of the measured contributions. Twenty-one complete graph bodies have
diagnostic equality; this alone is not a promotion of other bodies.

## Execution evidence

The fixture executes the complete 2,198-slot item loop and the real compiled
lookup/removal, sound queue, life icons, creator, allocator, registrar,
initializer and preserving loader. The animation manager occupies a separate
complete fixture memory range, and its entire memory joins the observations.
Entry hooks record calls and allow these bodies to execute.

The 405 cases retain the previous 370 cases and add primary/secondary banner
lookup, child flag propagation, already-flagged children, queue insertion and
saturation, full queues, valid creation scripts and the first occupied pool
slot. They compare complete item records/pools, HUD/text/sound/animation memory,
call order/arguments, return/stack behavior, preserved registers and x87 state
under control word `0x037F`. The existing binary32 precision boundaries remain.

Entity_Init, VM execution, player power-change and terminal conversion remain
scripted shared boundaries. The allocation fallback to a newly allocated entity
is not exercised by these pool cases. These are bounded execution checks, not
complete game integration or proof that the unselected creator/initializer
match retail bytes.

## Production proof and ownership

The new source is
[`item_collection_genuine_0041afd0.cpp`](../../msvc/src/game/item_collection_genuine_0041afd0.cpp),
with
[`item_collection_genuine_0041afd0.json`](../../msvc/layout/ltcg/item_collection_genuine_0041afd0.json).
Its compiler driver only includes this actual complete graph and defines no
synthetic function. The normal validator checks every selected full contribution
at its retail address:

| Selected function | Address | Bytes | ABI |
| --- | --- | --- | --- |
| ConvertItems | `0041BA50` | 165 | Manager ESI, RET |
| AddPower | `00418930` | 166 | Counters EAX, amount on stack, RET4 |
| AddLives | `004188A0` | 141 | Counters EAX, amount ECX, RET |

The three source/manifest owners are now this graph. The old conversion and
life-stock clusters leave `ltcg_clusters`, and their old source files leave
the maintained translation-unit list. Their files remain as history; their
actual prior inputs, native PE/MAP and reports are copied under
`evidence/precision_graph/retired_production/`. The former 75-byte synthetic
life-counter compiler context is not used by the selected build.

All 472 selected bytes match raw, with zero patches, zero masks and no
reference-code build use. `make` and `make EXACT=1` pass. Exact mode remains
identical to the 487,936-byte oracle (SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`).
The fresh audit verifies 963 native layouts, 1,483 selected functions and
3,985 current unique compiler inputs. Counts remain 2,254 ordinary C++ regions /
199,062 bytes and 60 actual assembly regions / 89,245 bytes. New recovered
bytes: **zero**. The full decompilation goal remains active.

Reproduction commands and current hashed reports are in
[`item_update_0041afd0/`](../semantic_candidates/item_update_0041afd0/).
Its preceding 2,452-byte / 370-case source and proofs are preserved in
`evidence/precision_graph/`, so historical evidence is not relabeled as the new
405-case graph.
