# Parked stage-tip parser candidate, 0x00419960

Checkpoint: 2026-10-05. **Not exact; not a production build input.**

The `claude_checkpoint/` files preserve the four `sp_improved*` files from
Claude's interrupted session, byte for byte. Their original layout still
describes a 1486-byte parser context, although that source emits 1499 bytes.
They are historical experiment inputs, not a passing cluster.

`parser_candidate.cpp` builds on that checkpoint with a float scale temporary
and float comparison literals, plus an explicit `TipNode*` for duplicate-node
repair. The emitted scale comparison sequence and duplicate-node repair now
match retail. `parser_candidate.json` binds pooled strings and float constants
to their retail addresses, reserves the actual 1498-byte parser extent and
six-byte gap, and selects both parser and reader in a schema-2 cluster. This
makes the normal probe compare the parser's full bytes instead of checking it
only as the reader's compiler context. No instruction bytes are rewritten.

Run from any directory:

```sh
python3 /path/to/th10Decomp/matching2/reference/semantic_candidates/stage_tip_parser_00419960/reproduce.py
```

The script copies the maintained MSVC project into a new temporary directory,
installs the candidate there, changes ownership only in that copy, and runs
the existing matching probe. `--output /new/directory` retains artifacts at a
chosen location; an existing directory is rejected. The project toolchain and
the probe's supported retail oracle are required. Full reports, native PE/MAP,
compiler/linker logs, and extracted bodies stay under that output directory.

Expected result: exit status **1**, because this is a failed candidate:

```text
0x00419960 1498 bytes _ParseStageTips@12: DIFFERENT (571 differing bytes)
  expected: 0x00419963: 56  push   esi
  actual:   0x00419963: 57  push   edi
0x00419f40 260 bytes _ReadLine@16: EXACT (0 differing bytes)
```

`probe_summary.json` records the checked source and emitted-body hashes. The
first two inlined key copies still walk the opposite pointers from retail;
data/line register allocation, stack slots, and the color branch also differ.
An equal total extent is not evidence of an exact or accepted equivalent
recovery. The constructor and other ABI anchors are not selected recoveries
and must be checked independently before any ownership expansion.

Experiments resumed in this pass:

| Source experiment | Result |
| --- | --- |
| Original saved source | 1499-byte parser; stale context/gap prevents reader address validation |
| Comma expression or discarded equality joining the two split calls | Same 1499-byte instruction shape |
| Empty inline wrapper taking the two call results | 1484 bytes; different frame and copy structure |
| Six explicit copy-loop spellings in the splitter | 1480 or 1500 bytes; no match |
| Explicit first-copy helper | 1480 or 1499 bytes; no match |
| Double-split wrapper, all six parameter orders | Unchanged 1499-byte shape |
| Splitter parameter permutations with all callers updated | 1498 or 1499 bytes, still different |
| Double scale temporary compared with float literals | 1498 bytes, but QWORD comparison operands instead of retail DWORD operands |
| Named external float bounds with double scale temporary | Still emits extra x87 loads; no match |
| Float scale temporary, float literals, explicit duplicate-node pointer | 1498 bytes; archived strict-probe result above |
| Parameter permutations on the refined candidate | 1489 or 1498 bytes; no exact result |

These experiments do not prove or disprove the prior compiler-temporary
free-list hypothesis. In particular, changing source order alone is not
proof that native compilation order or temporary reuse changed. Continue
from the full strict probe above; do not treat a reader-only `EXACT` result
as parser validation.
