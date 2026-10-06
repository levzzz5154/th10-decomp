# Title spell-list builder: complete native text graph

The 850-byte region at `0x00432690` remains assembly. The retained ordinary
C++ member emits 834 bytes, with 25 instruction comparison hunks. A source
ordering control emits 850 bytes but still differs. Neither is an exact
recovery.

The earlier assembly banner incorrectly said that no readable candidate had
been measured. It now points here. The shared title-menu header also now
declares `BuildSpellList`, which the archived member definition requires.
The declaration adds no data members or code.

## Reproduce the retained source

From the repository root:

```sh
python3 matching2/reference/semantic_candidates/title_spell_list_00432690/probe.py
```

The probe reads the production flags, adds the established native `/GL`
build, and links at both `0x400000` and `0x10000000`. Its three complete
translation units are the archived list builder, the maintained 194-byte
centered formatter, and the maintained text dispatcher anchor. It measures
whole CODE contributions from the MAP, not a prefix of the required size.
The second link identifies absolute references for diagnostic rebasing;
this does not replace any production bytes. No function differences are
accepted, and neither a cluster nor an equivalent recovery is registered.

The menu arrives in ECX through its ordinary public member entry. The
formatter's native private receiver is ESI; the dispatcher's native inputs
are resource in EDI, font height in EAX, text in EBX, and four stack arguments.
The complete formatter and dispatcher match retail at 194 and 127 bytes
respectively in every successful control below. They are compiled bodies,
not ABI stubs. Their external `vsprintf`, float conversion, and two drawing
calls have the maintained signatures.

The source names the existing string data explicitly: named-card format at
`0x46EEF8`, masked-card format at `0x46EEBC`, and a single space at
`0x46CFD4`. The initial scratch build used the wrong address for the space;
`baseline/` is superseded by `corrected_baseline/`. All results below use the
correct address.

## Measurements

Artifacts live in `build/experiments/title_spell_list_native_2026_10_06/`.
Each control retains its exact source, header, layout, two MAPs, native
objects/images, raw full contributions, and comparison JSON. The tracked
probe reproduces `retained_baseline/` directly from the archived source and
the current shared header.

| Source control | Native bytes / retail | Unequal overlapping bytes | Comparison hunks |
| --- | ---: | ---: | ---: |
| Retained member, per-branch record and manager | 834 / 850 | 441 | 25 |
| Lookup as a method of the typed manager view | 834 / 850 | 441 | 25 |
| Complete canonical lookup with a four-byte ID argument | 834 / 850 | 441 | 25 |
| Record and manager before the name terminator | 850 / 850 | 379 | 40 |
| Earlier manager, cached score-manager pointer | 850 / 850 | 379 | 40 |
| Pointer or reference fastcall receiver, original order | 834 / 850 | 441 | 25 |
| Pointer or reference fastcall receiver, earlier manager | 850 / 850 | 379 | 40 |
| Stale-handle resolution in a complete inline helper | 834 / 850 | 441 | 25 |
| Earlier manager plus stale-handle helper | 850 / 850 | 379 | 40 |
| Direct pointer to the selected spell record | 818 / 850 | 580 | 36 |
| Direct spell pointer with earlier manager | 818 / 850 | 587 | 47 |

Combining the direct spell pointer and stale-handle helper reproduces the
same respective 818-byte bodies. The public fastcall controls use a direct
context call and `/INCLUDE` root; no callback slot or altered compile flags
are involved. The member measurements use the public member entry directly.

Unequal overlapping bytes are an offset-based diagnostic, not matching
credit: a shorter body fails regardless of this count, and moving an
instruction changes subsequent byte offsets. Instruction hunks include
branch displacement changes following altered code size and alignment.

## Remaining differences

The original-order body reproduces the GS frame, menu home at stack +0x1C,
page skip loop, card scan, byte string copy/count, and REP space padding.
The first non-branch difference is the blank-line count at +0xAE: EBP in
the candidate, EBX in retail. The main named-card divergence starts at +0x15F.

Retail loads the manager into ESI after reading the selected shot, forms
the selected score-section pointer in ECX, and keeps the lookup result in
EAX. Its found-node object temporarily occupies EBP. Immediately before
the centered-format call it pushes the manager and moves EAX to ESI.
The original-order candidate instead uses EBP for the manager, EDX for the
score section, and ESI for the lookup result. It also reuses the captures
load for the color calculation, whereas retail loads captures again into
ECX. The masked path and blank tail retain further allocation/alignment
differences in this small native graph.

Moving the manager before the terminator changes its allocation to ESI,
but keeps the menu in EBX for the whole function. The score pointer then
occupies EBP and the lookup result still occupies ESI. Correct total size
alone therefore does not resolve the mismatch.

Read-only Wine/GDB linker replays completed normally for original-order
spill costs and register choices, and earlier-manager spill costs. They are
retained in `corrected_baseline_trace/` and `member_reordered_trace/`.
The existing tracers observed compiler allocation without changing the
compiler, input objects, or game. Candidate records do not expose readable
source names through their sampled symbol records, so those traces do not
yet identify the exact C++ local responsible for each allocator choice.

The controls rule out receiver pointer/reference spelling, the typed lookup
method, the four-byte ID wrapper, and isolating stale-handle clearing as
solutions in this graph. A further attempt needs evidence about the named
path's live values or genuine caller context, rather than repeating those
forms. The real `0x00431EE0` caller remains a 1,968-byte assembly owner; it
was not substituted with a shortened caller in these measurements.

## Production validation

`make`, `make EXACT=1`, and `git diff --check` pass after the declaration and
candidate/probe repairs. The exact 487,936-byte executable equals the whole
oracle, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Exact ordinary C++ coverage stays at 191,372 bytes (59.5%); the eight
equivalent recoveries add 33,176 bytes. This investigation adds no new
production C++ region.
