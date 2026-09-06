# Consolidated semantic audit status

This is the consolidated status for the current address-level semantic audit.
The manifest contains 710 semantic ledger addresses; five exact addresses are
tracked separately, of which two remain semantic in the current ledger,
leaving a 708-address scope for this pass. The bounded audit stopped after the reported
coordinator, ending, and player batches at the user's direction. It does not
claim that the remaining addresses are equivalent.

| Status | Addresses |
| --- | ---: |
| Reviewed | 57 |
| Grounded | 28 |
| Partial | 29 |
| Pending | 634 |
| Reference-unresolved | 17 |
| Remaining | 651 |

The machine-readable, deduplicated address ledger is
[semantic_audit_summary.json](semantic_audit_summary.json). It validates that
all 57 reported addresses belong to the 708-address manifest scope, that no
address is reported twice in the consolidated rows, and that the two trajectory
rows shared by the coordinator and ending reports are counted once. The ending
report contains 14 rows because it carries those two trajectory cross-references
alongside its 12 new rows; its new batch is 5 grounded and 7 partial. The
coordinator report therefore contributes 36 unique rows (21 grounded and 15
partial), the ending partition contributes 12 additional rows (5 grounded and
7 partial), and the player report contributes 9 rows (2 grounded and 7
partial). Pending counts are 201 coordinator + 213 ending + 220 player; the 17
reference-unresolved rows are in the player partition.

Grounded means that the reviewed behavior agrees with the available source,
IDA pseudocode/assembly, and raw Ghidra evidence at the stated boundary. A
partial row may record a confirmed behavior mismatch, an owner or ABI adapter,
a precision boundary, or an incomplete but supported slice. Partial therefore
does not mean that every row demonstrates a retail behavior bug. In particular,
player address `0x0044C7E0` remains partial because the local retail decompile is
corrupted and exact ABI/vtable and error-path equivalence is unproven; it is not
presented as a completed correctness check. Reference-unresolved rows make no
semantic claim where required local exports are absent.

The strongest concrete mismatches found in this bounded pass are:

- `0x0044C350` uses the wrong first-half mode-11 formula: for elapsed `2.5`
  and duration `10`, the source gives `0.9375` while the static retail formula
  gives `0.03125`.
- `0x004135D0` omits the retail variadic FPS value passed to the overlay writer.
- `0x00420100` probes `th10.ver`, while retail probes/opens `th10.dat`.
- `0x004134B0` omits the retail fourth-stall reset of the performance-counter
  frequency.
- Other confirmed differences include the inverted supported-path return at
  `0x00420670`, the missing shared-path clear at `0x0040B480`, and the
  caller-supplied schedule replacing retail difficulty-table selection at
  `0x00428160`.

The complete evidence remains in the non-overlapping partition reports:
[coordinator](semantic_audit_coordinator.md),
[ending](semantic_audit_ending.md), and
[player](semantic_player_audit.md). The five earlier spot audits remain in
[semantic_spot_audit.md](semantic_spot_audit.md).
