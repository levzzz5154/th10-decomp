# Name-history insertion `00421FA0`: measured native candidate

Recovery performed 2026-09-27–28. **Not promoted.** Production ownership remains
`kind: asm`, extent 316 bytes, in `src/game/fun_00421fa0_00421fa0.cpp`.
The old D3305 comment described an exact retail overlay with no retained readable
candidate. This pass supplies the first bounded native C++ body measurement;
it does not replace that maintained overlay.

The retained candidate is in
`matching2/build/experiments/name_entry_select_00421fa0_2026_09_27/msvc`.
Its full compiler contribution is **317 bytes**, compared with the original
316-byte region. Comparing the complete 316-byte overlap without any masks gives
**102 differing bytes**, first at **`00422012`**. The first 114 bytes match.
Native body SHA-256:
`c5679fd118f1defbac82a2617a7d5fa996f66bdac4cf3287966482ab99ef7b56`.

The final normal `probe.py` run is `probe_final_02.json`. It correctly reports
`exact: false` and rejects the cluster's shifted entry address. The candidate's
317-byte extent and the unselected caller's 362-byte extent move later layout
symbols. No function extents, comparison masks, or verifier checks were weakened.
`measured_residual.json` independently records the native section size, unmasked
comparison, compiler paths, source hashes, and the earlier bounded attempts;
`measure.py` reproduces that diagnostic. This is residual evidence, not a passed
normal promotion gate.

## Recovered behavior and layout

Fresh live Ghidra decompilation and complete disassembly were retained for
`00421FA0`, both real callers `00423570` and `00432CB0`, and `0044BEA0` in the
experiment directory. The target reads its history owner from **EDI**, returns
its selected position in **EAX**, and uses a plain `RET`. Both callers construct
the owner as global save-base plus `(3 * character + variant) * 0x437C + 8`.

The routine scans ten descending score records in the selected difficulty bank.
If no record can accept the current signed score, it returns -1. Otherwise it
shifts records from index nine down to the insertion position, copies all six
32-bit words per record, and fills the selected entry. The bank stride is `0xF0`
and each record is `0x18` bytes:

| Offset | Observed field |
| --- | --- |
| `+0x00` | signed score |
| `+0x04` | stage byte |
| `+0x05` | score suffix digit |
| `+0x06` | nine-byte name |
| `+0x0F` | untouched padding/unknown byte |
| `+0x10` | 32-bit timestamp passed to genuine cdecl `__time32` |
| `+0x14` | float measurement, `100 * (1 - counter_24 / counter_2C)` |

A separate read-only codebase audit checked the field names against the retail
`004329F0` renderer. It uses byte `+4` to select the stage label and byte `+5`
immediately after the score for `%9ld%d`; the byte is therefore a score suffix
rather than lives. The maintained life counter is at `00474C70`. No canonical
maintained 24-byte record type exists. Earlier legacy score-file descriptions
conflict and were not adopted as evidence.

The candidate keeps the genuine time call and the x87 `FLD`, `FDIV`, `FMUL`,
`FSUBR`, `FSTP` sequence. The two multiplier/subtractor memory operands are the
verified float32 `100.0` at `00470B44`, bound through a standard compiler literal
alias. The `+24/+2C` double view has compile-time packing and offset checks.
Its field names remain arithmetic roles, avoiding an unsupported domain claim
about the measurement. Experimental scoped volatile global declarations retain
the difficulty and score reloads visible in the retail body; they are not a
claim that these globals are thread synchronization primitives.

## Compiler context and remaining differences

The complete authentic `00423570` menu preparation body is co-visible as an
unselected C++ ABI anchor, together with the complete genuine `MenuCursor::Advance`
body. The compiler chooses EDI for the target receiver without an entry adapter.
The cursor anchor independently emits all **128 original bytes exactly**. The
caller emits 362/377 bytes and remains unselected and nonmatching. The array loop
at the cluster's end is explicitly synthetic compiler context.

The retained target's first remaining mismatch is the compiler loading the sixth
copied word before storing the fifth word at `00422012`; retail stores the fifth
word first. The two operations occupy the same six-byte span. A later difficulty
reload moves before the new score store. The timestamp address and name-copy
pointer use different temporary registers; stack cleanup occurs before the name
copy, and the final percentage address uses EAX, delaying the result move and
saved-register pops until after `FSTP`. Retail uses ECX for the final index and
pops the saved registers before its last x87 arithmetic.

Seventeen bounded shape variants covered whole record assignment, explicit
six-word views, a five-word prefix copy, volatile tail-word views, ordinary
member versus free function declarations, and zero-instruction compiler barriers.
None passed the original full-extent gate. The explicit word variants change the
register allocation or introduce extra saved/spilled values; they should not be
repeated as an unguided register sweep.

A concrete remaining lever is a compiler-visible record copy operation that
retains the typed whole-record alias information while constraining the fifth
store before the sixth load, followed by authentic-caller ordering recovery.
The current C++ caller's reversed paired global stores, clamped-selection
constant propagation, and branch placement are known differences from its full
retail body; recovering that caller's original 377-byte schedule provides a
stronger context than the present genuine but nonmatching anchor. The target's
private ABI is established now, so repeating standalone ABI declarations is no
longer the useful next action.

All edits are confined to the unique experiment and this recovery note.
No maintained inputs or shared manifest were edited. No inline assembly, naked
body, encoded instruction, instruction/address rewrite, comparison mask, or
reference instruction appears in the candidate build.

## 2026-10-05: recovered

`src/game/score_table_insert_00421fa0.cpp` is byte-exact (316 bytes) in the new
cluster `layout/ltcg/score_table_insert_00421fa0.json`; `make` and
`make EXACT=1` pass. No `volatile`, no barriers.

The reloads of the difficulty and score that the earlier candidate forced with
`volatile` come from aliasing: the game counters at 0x00474C44 are one object
whose address is taken, so each store through the table makes c2 reload them.
Declared as lone `extern int` globals, LTCG knows they cannot be aliased and
hoists everything (262 bytes). Declared as fields of one struct whose address
escapes in the cluster (the context passes `&data_00474c44` to an external
function), the plain source — every statement written as
`records[difficulty][rank].field = ...`, the shift as a struct assignment, the
name as `strcpy` of eight blanks — gives retail's bytes, including the copy
order, the late `add esp,4` and the pops before the last x87 steps.

Rig: `build/experiments/score_insert_421fa0_claude` (`run.py c`).
