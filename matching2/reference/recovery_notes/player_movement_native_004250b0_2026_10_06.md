# Player movement: complete native candidate, not yet selected

The production `0x004250B0 / 1656` region remains assembly. This investigation
adds a complete ordinary C++ candidate in
`reference/semantic_candidates/player_movement_004250b0/`. It does not change
the manifest, shipped bytes, progress accounting, or matching tools.

The strongest diagnostic compiles to the full 1656-byte extent, including the
two eight-entry switch tables. It has the real EDI receiver, no stack input,
an integer EAX result, and plain RET. It is **not exact**: the diagnostic reports
19 difference groups and 363 unequal overlapping bytes. Several groups are
consequences of earlier branch placement, including the table destinations.
There are no accepted differences or masks. The candidate is not a recovery
credited to the build.

## Reproducible evidence

Run from the repository root:

```sh
python matching2/reference/semantic_candidates/player_movement_004250b0/measure.py saved_candidate
```

The source directory contains all ten translation units, checked physical
types, the diagnostic layout, source hashes, and the comparison. The diagnostic
compiles and links before reading the oracle. Address normalization and the
relocated comparison bodies are diagnostic artifacts only; these are not a
fixed-address production proof. Both compiler-native PE images and their map
are retained under
`build/experiments/player_movement_native_2026_10_06/shared_facing_call/`.
The saved-source rerun writes to `.../saved_candidate/`.

The model uses a complete compiler-only call through the real global player
pointer, not a partial PlayerUpdate or additional input. A separate experiment
with the complete real PlayerUpdate and its complete pause, collision,
indicator, timer, and related helper source graph produced identical movement
bytes at that stage. Thus the actual caller did not explain those differences.

## Complete supporting functions

All ten functions below match their retail bodies after diagnostic address
normalization in the strongest graph. No helper is shortened or replaced by a
constant-result surrogate. Only movement is the intended prospective selection.

| Function | Address | Bytes |
| --- | --- | ---: |
| Entity initializer | 0x401DE0 | 273 |
| Non-preserving script loader | 0x43E710 | 203 |
| Preserving script loader | 0x43E7E0 | 194 |
| Primary-list registration | 0x4489D0 | 118 |
| Animation lookup | 0x4491C0 | 73 |
| Frame setter, including children | 0x449210 | 54 |
| Position setter, including children | 0x4492F0 | 90 |
| Translated position setter, including children | 0x449350 | 111 |
| Resource object initializer | 0x449870 | 217 |
| Pool allocator | 0x449950 | 161 |

The translated setter ends after 111 bytes. The earlier 120-byte comparison
extent included nine bytes from the following function. Its child writes use
one local `Vector3*` receiver, yielding the actual contiguous three-field copy.
The diagnostic binds 224 and 16 literals to their real retail addresses.

The full non-preserving loader calls the genuine public fastcall initializer
edge declared by `entity.hpp`. Its leading ECX slot is dead; the actual Entity
input is EDX. The other full initializer contribution remains ordinary stdcall
source for the allocator. The loader's resulting private convention is resource
ECX, object EAX, script EBX, and no stack arguments. The older pause graph's
direct co-compiled initializer edge instead produced a different loader ABI.
The VM boundary is the actual full game routine's public stack call.

## Source findings that changed the native result

* Point assignment must copy X before reading Y. A checked two-component type
  with an explicit reference assignment reproduces the trail and orbit copies.
* Orbit subtraction, multiplication, and division operate on the complete
  two-component value. This evaluates both products before their divisions,
  reproducing the retail arithmetic sequence. A point inequality against zero
  also gives the retail interpolation branch order.
* In the equal-component diagonal cases, `move_y = move_x = speed` gives the
  real X-in-EBP and Y-in-EBX allocation. The old `move_x = move_y = speed`
  form reversed that allocation. Direction bodies are ordered 4, 3, 1, 2, 5,
  7, 6, 8, corresponding to the actual switch-body order.
* Registration returns a nontrivial value while the ID passed to lookup and
  setters remains a trivially copied argument value. The candidate's separate
  registration-result type reproduces the caller's load from its actual stack
  return slot and retains all exact helper argument conventions. Giving every
  ID a user-defined copy constructor fixed that one load but broke the three
  setters, so that alternative is rejected.
* Clearing the ID through its value assignment reproduces the store before
  reading the next direction; writing its scalar field directly reordered it.
* The right-facing and stopped-right transitions share one script-loader call.
  A single semantic label expresses that actual shared tail. Expanding all
  facing flow into explicit gotos caused major register and block-order
  regressions and is not the saved candidate.

The candidate's volatile input union and volatile position view are **source
hypotheses**, not recovered declarations. They express the observed byte/word
polling accesses and stored-float reloads, respectively. Removing those
qualifiers enabled input CSE and retained extended x87 values across lookup.
Alternative nominal render/world-position views did not remove that CSE.
These choices require review before any production promotion. No volatility
was added to supporting helpers, and no compiler output is rewritten.

## Remaining differences

The saved comparison shows:

1. Shot-type loading is scheduled before the shift/slow-state work rather than
   after the character load. A combined configuration snapshot changed several
   later register choices and was worse.
2. Facing control flow still places or folds the zero-movement tests differently,
   despite the correct shared right-facing call and actual register inputs.
3. The slow-animation ID load/push is scheduled before the two position stores.
   The X-offset floating add and Z load also exchange order.
4. The first trail loop needs additional alignment/jump placement.
5. In the final orbit position setup, `mov edx, ebp` moves across the local
   position-address setup.

Reordering declarations, changing point components to `long`, changing the
loader from free function to member function, giving it the observed manager
pointer result, and placing all supporting bodies in one translation unit did
not resolve the major facing differences. Whole-vector assignments to every
switch case introduced unwanted zero stores. Keep those diagnostics as rejected
alternatives, not production helpers.

Before promotion, require a raw fixed-address native cluster proof for the
entire code and both jump tables, followed by the normal and EXACT=1 builds and
the whole-file oracle equality check. Current verified game progress remains
197229 / 321483 ordinary C++ bytes (61.3%), with 62 actually unrecovered assembly
functions. The active whole-program goal is incomplete.


## Receiver, layout, and scheduling audit

A fresh Ghidra MCP decompile covers the complete movement function, including
its orbit tail. Read-only calls used the connected Ghidra server's advertised
`/decompile_function` endpoint over its Unix-domain socket; responses are saved
under the experiment directory. No function, signature, or listing was changed.
Ghidra's apparent unused ECX input is not an additional logical argument: the
actual movement receiver remains EDI, as confirmed by the full caller and
native output. The native root at `0x401120` and retail root at `0x4250B0` both
have 16-byte alignment, so function-head alignment does not explain the trail
loop's remaining padding difference.

The saved candidate now uses the actual `FrameTimer` at `+0x488` and tests its
`current` field at `+0x48C`, rather than calling that scalar `playable_state`.
The surrounding complete PlayerUpdate source advances this timer. The gate
field is named `active`, movement directions have named enum values, and the
three float literals have const declarations bound to their retail `.rdata`
addresses. Static checks retain the timer, current-frame, direction-size, and
subsequent member offsets. These semantic corrections compile to the identical
normalized movement body, SHA-256
`76624e6f788f627d40e2c1e9ea95c9b1ee69509d6a03db377fa7db472dc0dae4`.

The maintained `rejected_variants.json` records 19 isolated full-graph trials.
Each keeps all ten supporting functions exact after diagnostic normalization.
Free stdcall/cdecl/fastcall and member loader forms with four independent
facing conditions give the same 1672-byte result (24 groups, 974 overlapping
byte differences). Changing the root receiver to a genuine fastcall free
function or genuine member function retains 1656 bytes and 19 groups / 363
unequal bytes. Neither declared receiver convention explains the residual.

An explicit two-loop do/while trail gives 1664 bytes and 27 groups / 758 unequal
bytes. An outer moving/stopped facing branch gives 1656 bytes and 29 groups /
785 unequal bytes. The precision pragma with an ordinary position view gives
1704 bytes and 28 groups / 833 unequal bytes. Scalar coordinate wrapper and
comparison-operator types retain the original 19 / 363 result. The equivalent
`previous > -1` / `previous < 1` condition spelling instead gives 19 / 464.

Volatile configuration reads repair the first load schedule but disturb later
register allocation (31 / 816 with explicit local copies, 30 / 811 with direct
expressions). An observed slow-handle read gives 20 groups / 362 unequal bytes:
that one-byte aggregate reduction introduces another instruction difference
and does not establish an improved match. None of these variants is selected.

The final combined maintained-source rebuild again gives the full 1656-byte
extent, 19 instruction difference groups, 363 unequal overlapping bytes, and
ten exact supporting helpers after diagnostic normalization. No production
source, selected region, build tool, mask, or equivalence declaration changed.


## Complete diagnostic artifact correction

The diagnostic disassembler previously reused the normalized full-body filename
for its code-only input, overwriting that saved file after comparison. The
in-memory full comparison was unchanged, but the saved artifact omitted the
jump tables. The runner now writes a separate `_body_code.bin` and retains both
`_body.bin` (1656 bytes) and `_retail_full.bin` (1656 bytes). A reuse comparison
of the already-built native images confirms the same 19 groups / 363 unequal
bytes and ten exact helpers. The receipt retains the earlier code-only SHA
under `normalized_movement_code_sha256`; the complete body SHA is now
`0dff114940012b47cdd7ef24377a38ef2db170a494c40973d4f75cb42a95c07d`.
No production build tool or comparison rule changed.
