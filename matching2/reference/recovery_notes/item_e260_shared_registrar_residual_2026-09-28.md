# 0041E260 shared registrar: complete source graph, four-byte residual

No routine is promoted by this experiment. A complete ordinary C++ definition
of the actual 004489D0 primary-back registrar is visible to the complete
0041E260 caller and the retained exact 0041F400 caller. Both callers name
the same external function, whose complete implementation delegates to one
static inline core; these are two C++ functions but one shared operation.
The stock MSVC/LTCG build naturally inlines the external call in E260 and
leaves the F400 call outlined. The
original 609-byte E260 selected gate still has four byte differences, all at
the counter's ECX-versus-EDX encodings. A single genuine function identity is
therefore insufficient to change this register choice.

All artifacts are isolated under
`matching2/build/experiments/item_e260_shared_registrar_2026_09_28`.
`attempt04_natural.json` is the canonical unchanged normal selected gate;
`attempt04_natural_measurement.json` and `attempt04_natural_complete/` measure
the entire original-address PE/MAP contributions read-only. The complete
compiler closure is frozen in `terminal_inputs/` with all 15 source/layout/
header hashes in `terminal_input_hashes.json` (SHA-256
`9cd3502ba7b986ab007901f293779b02abe772a120fdc73f6f09c0c2e3e271f8`).
The normal report records zero instruction or address changes, zero masked
bytes, `reference_bytes_used_for_build: false`, and no build/placement failures.
The older four artifacts listed in `preserved_prior_state.json` also retained
their hashes. No maintained source, manifest, or tool was edited.

| Trial | E260 whole original contribution | F400 whole contribution | Outlined registrar whole contribution | Normal E260 gate |
| --- | --- | --- | --- | --- |
| attempt01 typed shared core, old 114-byte registrar placement gap | 609/609, 5 differences, first 0041E315 | 623/623, 1 difference, first 0041F527 | 118/118, 41 differences, first 004489EC | Placement rejected; call targets shifted by 16 bytes |
| attempt02 aligned typed core and complete wrapper | 609/609, 4 differences, first 0041E3A9 | 623/623 exact | 118/118, 41 differences, first 004489EC | No failures; 4 differences |
| attempt03 raw-offset view of the same complete operation | 609/609, 148 differences, first 0041E33B | 623/623 exact | 118/118, 41 differences, first 004489EC | No failures; 148 differences |
| attempt04 one natural registrar function identity, canonical | 609/609, 4 differences, first 0041E3A9 | 623/623 exact | 118/118, 41 differences, first 004489EC | No failures; 4 differences |

The initial placement error came from using the prior registrar model's
114-byte gap despite the genuine shared body emitting 118 bytes. The scratch
layout now declares the full actual 118-byte registrar extent and starts the
following gap at 00448A46. That restores the genuine 00448DB0 positioned
creator and 00449950 allocator addresses, explaining why the extra E260 and
F400 relative-call differences disappear. `setup04_aborted.json` was a setup
run after an assertion prevented a proposed edit; it carries no new semantic
trial or recovery claim.

The canonical complete contributions at their retail addresses are:

| Function | Native / retail size | Whole differences | Native SHA-256 |
| --- | ---: | ---: | --- |
| Allocator 0041BB00, unselected context | 819 / 819 | 736, first 0041BB0E | `6393e9877e1387e611de9fd74e1e64491346bc64f4bc5c9cb8b52a08faee4d59` |
| All-segment E260, selected | 609 / 609 | 4, first 0041E3A9 | `3e2329f7941f10e0a05c6b4455004ca9ab90242f12e522752f16c4305bbdd502` |
| Bounded F400, unselected exact context | 623 / 623 | 0 | `f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f` |
| Outlined primary-back registrar 004489D0, unselected context | 118 / 118 | 41, first 004489EC | `a3a1d7ddb5b8be7754fc38a359ac14eb78e53f34909e4ab27ea94ef8b2b07d22` |

F400 has its separate prior independent exact selected gate; its exact bytes
here are complete-context diagnostics, not a new F400 promotion. The allocator
is likewise a complete but inexact compiler input, not recovered coverage.

Fresh live Ghidra disassembly for all three routines is retained in
`fresh_e260_disassembly.json`, `fresh_f400_disassembly.json`, and
`fresh_registrar_disassembly.json`; the independent retail ABI analysis is
`analysis/shared_registrar_contract.md`. The actual outlined registrar takes
manager in EDX, entity in EBX, and output address in EAX, with plain RET. It
links the entity node, publishes head and tail, increments the manager's
counter with zero correction, rereads the counter into both the entity and
the output address, and returns the output address. Retail E260 inlines that
operation, eliminating only the dead local output write. F400 passes an
actual stack output slot and retains the outlined call. The selected E260
remains public ECX/one stack flag/RET4 and returns its count in EAX. The
source graph also preserves the full offset creator, allocator, script load,
positions, sweep loop, item spawn, floating Z update, retirement, and count.
No source assembly, forced physical register, fake caller, shortened helper,
byte rewrite, or comparison mask was introduced.

The retail outlined registrar conditionally saves EDI only in the existing-
head arm at 004489FC and restores it before the tail-counter update at
00448A13. This shared source emits a full 118-byte registrar but hoists that
EDI save before the branch at 004489EC, restores it after counter publication,
and uses EDI rather than ESI for the working counter. This explains its
41-byte residual and is a concrete source/control-lifetime lever for future
work. It is not evidence that changing that outlined body alone will fix
E260: the canonical one-identity build already shows natural inlining with
the same E260 four-byte residual. E260 itself still uses EDX for the
incremented counter where retail uses ECX; the four changed encodings are
0041E3A9, 0041E3AE, 0041E3B0, and 0041E3B4. A future trial needs a genuine
counter-result or alias lifetime that keeps the incremented value and tested
copy distinct while selecting ECX, validated against all full original extents.

No exact E260 or registrar body, and no new promotion closure, resulted from
this bounded experiment.
