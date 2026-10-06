# Item-update precision follow-up, 2026-10-06

This records the 2,452-byte / 370-case precision checkpoint. The
[collaborator follow-up](item_update_collaborators_0041afd0_2026_10_06.md)
supersedes the maintained measurements with 31 complete graph bodies, 405
comparisons and a 2,428-byte unselected update. The precision boundaries remain
in the source; the archived checkpoint is `evidence/precision_graph/`.

The maintained complete item-update candidate now passes **370 bounded
retail/native comparisons**, including two newly exposed rounding errors.
Its genuine caller graph still proves all 165 conversion bytes raw-exact at
`0x0041BA50`. Update remains unselected: the full native body is 2,452 bytes,
against 2,320 retail bytes, with 2,228 unequal overlapping bytes. This is a
semantic correction, not a new byte recovery or a size-based promotion.

Source: [`update.cpp`](../semantic_candidates/item_update_0041afd0/update.cpp).
Reports and full control sources:
[`evidence/`](../semantic_candidates/item_update_0041afd0/evidence/).
The current [receipt](../semantic_candidates/item_update_0041afd0/receipt.json)
distinguishes the maintained graph from the archived initial and intermediate
checkpoints. Reproduction commands are in the candidate README.

## What the new checks caught

The previous 238-case fixture did not expose a falling-Y displacement spill.
An additional 120 cases select actual float inputs for which retaining the
product through addition and rounding it first yield different position bits.
The initial full candidate fails all 20 Y cases in state 1. For example:

| Value | Float input/result |
| --- | --- |
| Initial Y | -0.8311082720756531 |
| Y velocity | 1.7306534051895142 |
| Time scale | 0.3153214156627655 |
| Retail final Y | -0.28539618849754333 (`73 1f 92 be`) |
| Initial candidate final Y | -0.2853962182998657 (`74 1f 92 be`) |

Retail keeps the planar products in x87 through the additions. The ordinary
falling branch now expresses those products as doubles and narrows the final
coordinate stores. The other integration paths retain the existing constructed
vector, which preserves their required Z displacement boundary.

That correction passed 358 cases, but a screen-limit probe caught a second
error. Retail's limit is the float 472 at `0x00470BE0`. An item starting there,
with Y velocity 1 and scale `1e-6`, still stores Y=472 after rounding. Retail
reloads that stored float and keeps the item alive. The intermediate candidate
compared its retained extended result and retired it. Two of 12 new boundary
cases expose this behavior; the failures include call order and live count as
well as the whole item record.

The maintained falling branch now makes two evidenced binary32 boundaries
explicit: a volatile float Z displacement and a const volatile read of the
stored Y for the offscreen test. These qualifiers preserve numeric stores and
reads that MSVC 7.1 otherwise eliminates or retains in extended precision.
They do not prescribe registers, introduce a caller, or patch emitted code.
Plain vector/scalar copies alone corrected the screen test but removed the Z
rounding in that branch; all 20 targeted Z cases then failed.

## Complete compiler controls

Sixteen complete ordinary-source controls are preserved in
`evidence/control_ledger.json` and `evidence/controls/`. Each keeps the complete
24-function graph and full switch tables. The controls vary the conversion
flag's type, motion/animation record composition, loop induction, shared vector
operators, scalar precision and stored-coordinate reads. None makes the entire
update raw-exact. The 2,212-byte nested-record controls still fail the falling-Y
cases; the 2,296-byte vector-operator control fails 62 of 120 precision cases.
Those shorter outputs do not earn recovery credit.

The final flat record preserves the existing coherent 2,198-element pool and
its three-component velocity. All 64 update and 23 spawn table bytes are
included in the complete comparisons. Fourteen graph bodies retain diagnostic
equality. Spawn remains 819 bytes with two unequal bytes; its ownership is
unchanged. The full update has 117 diagnostic instruction groups, including
register, frame, pointer-base and call-convention differences. No difference
is masked.

## Current proof and limits

All 370 comparisons execute the complete unmodified native/retail item loops
and compare whole memory observations, callbacks, return/stack behavior,
preserved registers and x87 state under control word `0x037F`. Animation,
banner, life-icon, sound-queue, power-change and terminal-conversion boundaries
remain scripted as described in the original note. This is bounded execution
evidence, not complete game integration or a raw update gate.

The full fixed-address conversion gate passes with the corrected 2,452-byte
caller as unselected context. Production changes only that caller source and
its context/gap extent. The selected conversion source and all other graph
inputs are unchanged. Its 165-byte SHA-256 remains
`d31835ee23314e37e524ed1ab5357a8354a94ad3f41cede33600555aa3aacd9a`.

Both `make` and `make EXACT=1` pass; the exact-mode EXE remains raw-identical to
the 487,936-byte oracle. The production audit verifies 964 native layouts,
1,483 selected functions and 3,984 current compiler inputs. Counts remain
2,254 ordinary C++ regions / 199,062 bytes and 60 actual assembly regions /
89,245 bytes. New recovered bytes, instruction patches and comparison masks
are all zero. The full inline-asm-free decompilation goal remains active.
