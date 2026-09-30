# Name-menu preparation `00423570`: genuine helper and cursor boundaries

**Not promoted.** The full original 377-byte caller now reaches the ordinary
native compiler byte comparator at its original entry with **19 differing
bytes**, first at **`0042362B`**. All first 187 bytes match. The earlier genuine
caller emitted 362 bytes with 203 differing overlap bytes. Production ownership
of both `00423570` (377 bytes) and `00421FA0` (316 bytes) remains assembly.

Evidence is confined to
`matching2/build/experiments/name_menu_caller_2026_09_28`. The terminal normal
caller report is `caller_gate_final.json`; complete MAP/PE measurements and
frozen input checks are reproduced with:

```sh
PYTHONPATH=. python3 matching2/build/experiments/name_menu_caller_2026_09_28/measure.py
```

The full 377-byte caller SHA-256 is
`9eda2039e947f998f8a7bd9be35fd9f56de7af84854c6686cf005602cd183a2b`.
No comparison mask, instruction replacement, address patch, shortened function,
inline assembly, or reference instruction was used. The final compiler report
records zero instruction and address changes during extraction. The complete
native caller contribution is exactly 377 bytes, starting at `00423570`.

## Recovered structural boundaries

Fresh live Ghidra decompilation, disassembly, and existing-head queries cover the
complete caller, insertion, alternate real caller `00432CB0`, genuine bounded
setter `0040AD20`, and cursor helpers. Bounded memory evidence covers all 25 bytes
of `0040ADA0`; Ghidra has no Function head there, and none was created.

The menu contains two adjacent complete `MenuCursor` objects, at `+0x24` and
`+0xFC`. Each occupies `0xD8` bytes. Their count fields are at `+0x2C` and `+0x104`,
and their wrap fields are at `+0xF4` and `+0x1CC`. This corrects the earlier
candidate's unsupported `selection_updated` label at `+0xF4`. The cursor layout
is supported by the shared recovered type and other real menu uses, not just
this caller's accesses. Offset assertions cover both cursors and name storage.

The two paired global writes are the genuine `0040ADA0` publisher operation:
publish `0x474788 + index * 0x30`, then stamp the index at receiver `+0x3C/+0x40`.
With receiver `00474C40`, those stamps reach `00474C7C/00474C80`; indices 8 and 7
produce pointers `00474908/004748D8`. The canonical complete publisher uses
unsigned arithmetic. The final candidate does too. A compiler memory barrier
retains the observed order of the two stamps. The second stamp's historical
meaning is not established by the equal values; its experimental field name
does not supply that evidence.

The best candidate uses a nonnegative-result selection specialization and a
separate zero-selection operation for the alphabet cursor. The insertion result
is proven nonnegative by the enclosing success branch; the alphabet request is
constant zero. These operations preserve the observed behavior for zero,
positive, and negative counts, including unsigned decrement wraparound. They
are not claimed to reproduce the full generic `0040AD20` setter. That genuine
setter additionally clamps negative requests to zero on its lower-bound path.
Its complete canonical body was measured as another co-visible helper model.

Volatile count views and compiler barriers preserve memory reloads and separate
publication boundaries visible in retail. Their presence in the original source
is unproven. The global game-state aggregate physically overlaps separately
declared stage globals through explicit linker bindings; this remains an
experimental type model, not a recovered canonical C++ global declaration.

## Bounded full-body measurements

| Whole caller model | Compiler extent | Unmasked overlap differences | Result |
| --- | ---: | ---: | --- |
| Reproduced earlier full caller | 362 / 377 | 203 | Not exact; shifted entry |
| Two cursor objects, genuine publisher, common clamp | 361 / 377 | 93 | Not exact; shifted entry |
| Success/failure blocks and separate clamp publications | 377 / 377 | 40 | Not exact; shifted entry |
| Selection and zero-reset boundaries | 377 / 377 | 20 | Not exact; shifted entry |
| Full canonical `0040AD20` bounded setter | 361 / 377 | 169 | Not exact; shifted entry |
| Frozen best caller at original entry | 377 / 377 | 19 | Normal byte comparator: not exact |

The 20-byte raw residual includes one relative-call byte caused by the caller's
`+0x10` shifted entry in the joint graph. The isolated original-entry gate removes
that layout effect without changing any selected caller extent or instruction.

The remaining 19 caller bytes occur in two concrete places. At `0042362B`, retail
places the zero-count alphabet path after the positive and negative paths; the
candidate handles zero first and compares the nonzero count against the live
constant one. At `0042368A`, retail materializes the blank-name pointer in EDI
before loading the nine-byte comparison count in ECX; the candidate reverses
those two independent instructions. Every other byte of the complete caller
matches. Both paths preserve the same visible behavior; their native schedule
still differs.

The complete genuine `MenuCursor::Advance` dependency independently matches all
128 original bytes at `0044BEA0` in the final caller gate. This does not establish
exactness of the selected 377-byte caller.

## Insertion gate and compiler context

The frozen joint gate retains both original selected extents, **316 and 377**.
Its insertion is still the same complete **317-byte** contribution, with 102
unmasked differences, first at `00422012`, SHA-256
`c5679fd118f1defbac82a2617a7d5fa996f66bdac4cf3287966482ab99ef7b56`.
None of the seventeen previous insertion copy/spelling trials was repeated.
The improved real caller context does not change this insertion contribution.

The isolated caller gate uses unique candidate source, header, driver, and layout
paths. It includes the full insertion as unselected compiler context. The strict
normalizer forbids a literal alias used only by an unselected body, so this
context expresses its verified 100.0f operands through the real `00470B44`
external constant. That full compiler contribution is **321 bytes**, also with
102 differing bytes in the original 316-byte overlap. Its extent is transparent
in the unselected anchor; no insertion recovery is claimed. Zero-filled layout
gaps account for its actual complete extent so the selected caller can be gated
at its original entry. The synthetic array caller is 37 bytes, is identified as
synthetic, and contributes zero recovered game bytes.

`joint_input_hashes.json` checks all 4,008 files in the frozen joint project;
`caller_only_input_hashes.json` checks all 4,009 files in the isolated caller
project. Terminal source closures are separately archived. All compiler reports,
complete native bodies, original comparison bodies, MAP files, PE files, and
rejected intermediate gate reports remain available. No maintained source,
manifest, shared tool, or historical experiment was modified by this work.

An independent read-only review passed the complete-section measurements,
normal report/PE/MAP/object agreement, frozen file sets, compiler input hashes,
and source specialization semantics. It found no gate weakening. The review
is archived as `independent_terminal_review.json`.

Further useful work requires a justified bounded-setter specialization or
intrinsic argument lifetime that retains the retail alphabet branch layout and
comparison setup order. Repeating the insertion's record-copy spellings or
standalone ABI declarations is not supported by these measurements.
