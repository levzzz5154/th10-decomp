# `0x0041A200` score-save lane recovery note

Date: 2026-09-12

Status: semantic recovery was attempted but not promoted.  The production
`matching2/msvc/src/archive/score_save.cpp` body remains the retail assembly,
and its manifest entry remains `2247` bytes.  No `regions.json` entry was
changed.

## Scope and authoritative extent

The live entry is:

```text
address  0x0041A200
extent   2247 bytes
range    [0x0041A200, 0x0041AAC7)
source   src/archive/score_save.cpp
```

Ghidra's augmented listing reports the same body range ending at
`0x0041AAC6`.  The normal return is at `0x0041AAAC`; the small dispatch stubs
at `0x0041AAAF` and `0x0041AABB` are still inside the manifest region.  The
next live manifest item is padding at `0x0041AAC7`, followed by unrelated
unassigned/padding bytes and `Recovery_AppendNode` at `0x0041AB10`.

The archived legacy registry, coverage, and standalone-readiness records are
stale for this lane: they call the function semantic, assign it `2320` bytes,
and also assign `0x0041AB10` as a separate function.  `2320` is exactly the
span from `0x0041A200` to `0x0041AB10`, so the archived extent crosses the
current padding/unassigned partition and ends at the next function.  It was
not used as an exact extent.

## Recovered behavior

IDA/Ghidra, the caller at `0x00418EE0`, retail strings, and the live assembly
identify this as the hint text exporter, not the archived hook-based
`ScoreFile_ExportText` abstraction.  The caller passes
`"hint/hint_auto.txt"` when the hint mode is `2`.

The function allocates a `0x1000`-byte formatting buffer, prepares the `hint`
directory through `FUN_00452ABC`, opens the requested shared output, and
returns after cleanup.  On a successful open it emits the retail banner:
the Japanese title rows at `0x0046D510`, `0x0046D4D8`, and `0x0046D490`, the
timestamp formatted from `localtime`, the blank rows, and `Version = %s`
using the retail version string at `0x0046D654` (`"0.0"`).

It then walks eight stage-list slots beginning at `manager + 0x7C`, with a
12-byte slot stride.  Each linked node contains the record pointer at word
zero and its next link at word one.  Records with `record + 0x70 == 0` are
skipped; each stage is capped at 255 emitted records.  A nonempty stage emits
the divider, stage number, `Tips`, optional `Remain`, and the record fields:

```text
text   +0x1C       count  +0x60       align  +0x64
base   +0x68       time   +0x6C       remain +0x70
scale  +0x7C       color  +0x84..86   alpha  +0x87
position floats at +0x00 and +0x04
```

Base and alignment IDs are translated through the retail tables at
`0x004744B0` and `0x00474494`.  The position values pass through the direct
`0x00463B2C` float-to-integer helper.  Each stage ends with `StageEnd`; the
file handle is closed, the file lock is left, and the buffer is freed on all
exits.  The two direct internal callees recorded by the legacy readiness data
are `0x00452ABC` and `0x00463B2C`; the repeated Win32 writes/lock operations
are through the retail import-table topology.

## Candidate and exactness result

A probe-only readable `Hint_ExportText` candidate reconstructed the eight-list
walk, all banner/record format strings, the fixed record offsets, timestamp
conversion, shared-writer error cleanup, and the two direct internal calls.
It was compiled with the project MSVC profile and was never put in the live
manifest.

The first candidate's base-profile body measured `2455` bytes.  A bounded
native-LTCG layout put the candidate contribution at `0x0041A200` and kept
the synthetic compiler context after it, but the focused comparison rejected
the candidate before byte comparison because `2455 != 2247`.  Comparing the
linked prefix for diagnosis found the first instruction mismatch at
`0x0041A208`:

```text
retail     83 e4 f8 83 ec 4c 53 56 57
candidate  83 e4 f8 83 ec 14 53 56 57
```

A second probe-only revision gave each write result its own source-level
scratch slot.  That reproduced the retail `sub esp,4Ch` prologue but measured
`2519` bytes, so it also failed the exact extent gate.  The candidate's
temporary layout, compiler-context source, native image, and probe outputs
were removed after the failed attempt.

The restored production source was then checked with the focused unit probe:

```text
python3 -m matching2.tools.matching.probe \
  --source src/archive/score_save.cpp \
  --project matching2/msvc \
  --oracle matching2/build/oracle/th10.exe \
  --output /tmp/score-save-production-probe-restored \
  --show 32 --json

EXACT
0x0041a200  2247 bytes  _asm_FUN_0041a200_0041a200  EXACT
0x004359b0  1029 bytes  _asm_FUN_004359b0_004359b0  EXACT
0x00436000   516 bytes  _asm_FUN_00436000_00436000  EXACT
```

## Concrete blocker and next dependency

The blocker is not the high-level record walk.  The archived semantic source
models a generic hook interface, while the retail body depends on the
original hint TU's direct shared-file writer, import-table `WriteFile`/lock
failure path, compiler-generated 20-byte float conversion call, fixed
Japanese banner data, and scratch-slot/lifetime topology.  Ordinary C++ and
the tested native-LTCG context can place the contribution, but cannot yet
reproduce both the retail scratch schedule and the exact 2247-byte extent.

The next dependency is the original `hint.cpp` semantic topology (including
the `0x0044B740` custom register writer and its caller-visible handle/lock
state), followed by a compiler context that preserves the distinct write
result slots and retail string addresses.  Coordinate that as a hint-export
source carve before changing the current `score_save.cpp` ownership; do not
consume the unrelated `0x0041AB10` or `0x0041AFD0` work in this lane.
