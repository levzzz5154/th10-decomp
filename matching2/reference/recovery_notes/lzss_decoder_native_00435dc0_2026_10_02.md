# Native MSVC LZSS decoder measurement

2026-10-02. Live Ghidra decompilation and disassembly of `th10.exe` confirm
the complete 475-byte decoder at `0x00435DC0`, four stack parameters,
`RET 0x10`, shared dictionary at `0x0048F868`, and the single allocation
callee at `0x00452706`. The maintained region remains assembly.

The existing `semantic_candidates/lzss.cpp` model now has a first native
MSVC measurement: **546 bytes** under the manifest's actual MSVC 13.10.6030
flags. The scalar reader model retained as
`semantic_candidates/lzss_decoder_scalar_00435dc0.cpp` emits **503 bytes**.
It restores the retail 12-byte local frame and uses the correct ordinary
stdcall entry, return, and cleanup. It has no assembly or injected barriers.

## Verification

The scalar model's actual native-MSVC object passed the existing differential
suite's **203 cases**, including output, all dictionary bytes, ordered input
reads, allocation failure, preserved registers, stack cleanup, overlap cases,
and guard-page faults:

```sh
matching2/build/lzss-compressor-recovery/venv/bin/python \
  matching2/tests/lzss_decoder_differential.py \
  --object matching2/build/lzss-decoder-recovery-20261002/candidate.obj
```

The test's final output labels any supplied object as a “Clang body”; this run
supplied an object built by the pinned MSVC compiler, not by Clang.

A private project copy then ran the maintained probe with only this region's
candidate symbol proposed. The complete gate rejected the source:

```text
region _DecompressDatLzss_00435dc0@16:
section .text extent 503 differs from requested size 475
```

The raw positional comparison first differs at `0x00435DC8`, where the
candidate saves ESI while retail saves EBP. That comparison is a diagnosis,
not a substitute for the complete-region gate. No region was promoted.

## Remaining source lifetime

Retail keeps the zero/match/length accumulator in EBP. It loads the original
source pointer into EDX at each outer iteration, retains only the input cursor
in EDI, and copies the decoded match position to a local before reading the
length. The scalar model instead caches the original source in EBP through
the flag/literal/offset phases. Its match accumulator occupies a local; EBP
becomes available again for the length phase and copy loop. The changed
exhaustion-zero stores, match position lifetime, and copy loop allocation
account for much of the extent difference.

Measured diagnostics included returned-field and reference-field readers,
directly expanded loops, nested literal loops, signed and unsigned scalar
types, register hints, source pointers and references, explicit consumed
counts, and the genuine shared-zero operand. Equivalent scalar forms keep
the 503-byte allocation. A rooted native LTCG control reproduces it as well.
An aggregate reader can emit 488 bytes, but has a 24-byte frame and differs
from the second instruction. It is not a closer byte match.

The next useful experiment needs a distinct reader state or caller lifetime
that explains the EBP accumulator and the source/match-position reloads.
Repeated spelling and declaration-order changes have not supplied that
evidence. The readable scalar model remains reference-only; the production
assembly and its manifest record are unchanged by this investigation.

Compiler commands, object files, disassembly, compiler-flag controls,
native LTCG PE/MAP files, and the private probe project are retained under
`matching2/build/lzss-decoder-recovery-20261002/`. The source and probing
proposal are `candidate.cpp` and `proposal.json` in that directory.
