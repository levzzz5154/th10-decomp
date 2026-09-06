# Semantic audit — score popup and trajectory helpers

Audit scope for the provisional ending partition, 2026-09-05. This report now
contains 14 audited addresses: two trajectory helpers plus 12 addresses from
the FPS, version-marker, and DAT archive batch. The prior sparse-audit
addresses remain cross-references only.

Normalized verdict count: **5 grounded**, **9 partial**.

- `src/app/fps_counter.cpp`
- `src/app/version_marker.cpp`
- `src/archive/dat.cpp`
- `src/archive/dat_file.cpp`
- `src/game/trajectory_evaluate.cpp`, excluding `0x00412AC0
  Trajectory_Evaluate2D`, which is covered by the sparse spot audit.

The registry has no additional semantic function in `score_popup.cpp`. The
remaining two trajectory functions are `0x00404610` and `0x0044C350`.
Each was read against the complete promoted C++ body, the IDA pseudocode and
assembly, and the raw Ghidra export. The existing focused trajectory test was
also rebuilt with warnings as errors.

## `0x00404610 Trajectory_Evaluate3D`

Verdict: credible algorithmic reconstruction for initialized, valid records;
partial contract and numerical fidelity.

The record layout in [the header](../include/th10/game/trajectory_evaluate.hpp:26)
matches the reference offsets: start at `+0`, target at `+12`, control rows at
`+24/+36`, timer fields at `+48..+68`, and mode at `+72`. The timer path in
[the implementation](../src/game/trajectory_evaluate.cpp:168) matches IDA
([pseudocode](../../ida/th10.exe.c:14248)) and assembly `sub_404610`:

- positive duration copies current to previous, uses the speed pointer, and
  treats speeds in `(0.99, 1.01)` as one normal tick;
- other speeds add to the float elapsed accumulator and derive current;
- completion initializes the embedded timer sentinel if needed, publishes
  `current=duration`, `previous=duration-1`, `elapsed=duration`, clears the
  duration, and returns the start row for mode 7 or the target row otherwise;
- the non-completion modes match the reference: mode 7 adds the target row,
  mode 17 adds and then advances control-B, mode 8 evaluates the four-term
  Hermite expression, and all other modes call the easing helper with elapsed,
  duration, and mode.

The mode bodies at [lines 202–235](../src/game/trajectory_evaluate.cpp:202)
correspond to IDA pseudocode lines 14327–14444, the [Ghidra mode branches](../../decompiled/ghidra_raw/00404610_FUN_00404610.c:73), and
assembly `loc_4046F0`, `loc_404755`, and `loc_4047F2`. The existing
[trajectory test](../tests/trajectory_evaluate_test.cpp:18) exercises the
linear, accelerating, Hermite/ease, and completion paths.

Boundaries remain material:

- `static_cast<int>(state->elapsed)` at line 174 is a host conversion
  boundary. Retail uses x87 `__ftol2` after an x87 accumulator; the sparse
  audit's 2D probe already demonstrates a conditional retained-extended versus
  rounded-float difference. The same timer path is shared by this 3D function,
  so the 3D result must not be described as x87-identical.
- The retail function returns the output pointer and receives its record/output
  through a register ABI. The host exposes a `void` function with explicit
  pointers. This is a useful typed adapter, not proof of raw ABI equivalence.
- The function assumes a non-null speed pointer during an active duration and a
  non-null easing callback for non-special modes, as retail assumes initialized
  record pointers and calls `sub_44C350`. Null behavior is therefore outside
  the reconstruction contract.

## `0x0044C350 Trajectory_EaseFraction`

Verdict: credible mode-table reconstruction for ordinary finite inputs;
precision and ABI boundaries remain.

The source [mode table](../src/game/trajectory_evaluate.cpp:98) matches the
IDA pseudocode ([lines 67761–67874](../../ida/th10.exe.c:67761)) and assembly
`sub_44C350` (`loc_44C369` through `loc_44C542`):

- modes 1–3 are powers 2–4;
- modes 4–6 are the corresponding decelerating powers;
- modes 9–10 and 12–14 use the two-half `2*t` curves with the same branch
  boundaries;
- modes 15 and 16 return zero and one;
- modes 0, 7, 8, and unknown values return the linear fraction.

The [raw Ghidra export](../../decompiled/ghidra_raw/0044C350_FUN_0044c350.c:19)
independently shows the same switch and constants, but
it exposes one concrete source defect: retail mode 11 has two different
halves. For `u=2*t < 1`, IDA/Ghidra return `u^4 * 0.5` (IDA lines
67815–67823 / Ghidra lines 54–60; assembly `loc_44C49F`), while the source
shares the reflected cubic expression with the second half at lines 130–134.
For `elapsed=2.5, duration=10`, the source returns `0.9375` and the static
retail formula returns `0.03125`. This is a behavioral mismatch in a directly
called semantic helper, not merely a precision boundary. Modes 9, 10, and
12–14 retain the expected branch formulas; mode 11 needs a separate first-half
case before this helper can be called algorithmically faithful.

No separate score-popup semantic function remains in the assigned source file;
its sole registry entry was the already audited enqueue routine.

## Ending partition batch 1 — FPS, version marker, and DAT archive leaves

The next ending-partition batch covers the first four source files in manifest
order. Each row was compared with the promoted body, the IDA pseudocode and
assembly, and its raw Ghidra export.

| Address | Source / retail evidence | Verdict |
| --- | --- | --- |
| `0x004134B0` | `src/app/fps_counter.cpp:56-95`; IDA `../ida/th10.exe.c:22957-23024`, assembly `../ida/th10.exe.asm:26363-26470`; Ghidra `../decompiled/ghidra_raw/004134B0_FUN_004134b0.c:12-79` | **partial**: elapsed-window, signed frame-count correction, 65/57 thresholds, two/four-stall resynchronization, pause-bit clearing, and counter reset agree. The retail fourth-stall branch also clears the global performance-counter frequency (`Frequency.QuadPart`), while `FrameRateEnv` exposes no equivalent reset target; the callback ABI is an adapter. |
| `0x004135D0` | `src/app/fps_counter.cpp:24-50`; IDA `../ida/th10.exe.c:23026-23064`, assembly `../ida/th10.exe.asm:26476-26542`; Ghidra `../decompiled/ghidra_raw/004135D0_FUN_004135d0.c:12-59` | **partial**: update call, state/thread gate, 30/40 color thresholds, restore-to-white, and skipped-frame increment agree. Retail calls the variadic overlay writer with the current FPS argument; the host callback accepts only a format string and source passes no FPS value, so rendered `%2.1f` output is not equivalent. |
| `0x00420100` | `src/app/version_marker.cpp:5-30`; IDA `../ida/th10.exe.c:33109-33131`, assembly `../ida/th10.exe.asm:45161-45221`; Ghidra `../decompiled/ghidra_raw/00420100_FUN_00420100.c:12-43` | **partial with concrete input mismatch**: retail probes/opens `th10.dat` through `sub_434C30`; source calls the injected probe with `"th10.ver"`. Generated marker naming, publication, success, and diagnostics otherwise follow the reference. |
| `0x00434C20` | `src/archive/dat.cpp:123-126`; IDA `../ida/th10.exe.c:50012-50016`, assembly `../ida/th10.exe.asm:74956-74963`; Ghidra `../decompiled/ghidra_raw/00434C20_FUN_00434c20.c:10-16` | **grounded**: the wrapper delegates directly to archive close/reset. |
| `0x00434C30` | `src/archive/dat.cpp:145-164`; IDA `../ida/th10.exe.c:50018-50053`, assembly `../ida/th10.exe.asm:74969-75020`; Ghidra `../decompiled/ghidra_raw/00434C30_FUN_00434c30.c:12-46` | **partial**: the source split moves retail allocation/vtable construction into `DatArchive_OpenFile`, then retains the same reset, index load, path copy, and reopen sequence. The explicit `FileInterface*` ownership and C++ ABI are a typed host adapter, and allocation/open failure cleanup is delegated across the split. |
| `0x00434CA0` | `src/archive/dat_file.cpp:15-23`; IDA C has no separate `0x00434CA0` block and shares the preceding `0x00434C30` export at `../ida/th10.exe.c:50018-50053`; assembly continuation `../ida/th10.exe.asm:75021-75069`; Ghidra `../decompiled/ghidra_raw/00434CA0_FUN_00434ca0.c:12-47` | **partial**: resource-file allocation and the shared index/path flow are represented by `DatArchive_OpenResource`; the retail resource vtable construction and its `sub_434F70` call are hidden behind `ResourceFile` and the shared typed adapter. |
| `0x00434D10` | `src/archive/dat.cpp:128-143`; IDA `../ida/th10.exe.c:50055-50083`, assembly `../ida/th10.exe.asm:75071-75115`; Ghidra `../decompiled/ghidra_raw/00434D10_FUN_00434d10.c:12-36` | **grounded for initialized archives**: filename, entry-vector, count, and file owner are cleared in the same order. C++ destruction stands in for the retail vtable close/delete path. |
| `0x00434DD0` | `src/archive/dat.cpp:166-199`; IDA `../ida/th10.exe.c:50108-50167`, assembly `../ida/th10.exe.asm:75176-75329`; Ghidra `../decompiled/ghidra_raw/00434DD0_FUN_00434dd0.c:12-78` | **grounded for valid entries/files**: entry lookup, compressed-size selection, seek/read, filename checksum parameter selection, decrypt, optional LZSS decode, output reuse, and temporary cleanup agree. The source factors transforms into helpers and exposes a conventional typed file API. |
| `0x00434EF0` | `src/archive/dat.cpp:219-224`; IDA `../ida/th10.exe.c:50169-50189`, assembly `../ida/th10.exe.asm:75335-75371`; Ghidra `../decompiled/ghidra_raw/00434EF0_FUN_00434ef0.c:12-34` | **grounded**: null/empty checks, case-insensitive linear search, and uncompressed-size return agree. |
| `0x00434F30` | `src/archive/dat.cpp:201-217`; IDA `../ida/th10.exe.c:50191-50211`, assembly `../ida/th10.exe.asm:75377-75417`; Ghidra `../decompiled/ghidra_raw/00434F30_FUN_00434f30.c:12-37` | **grounded**: entry-array traversal and case-insensitive match return the same record or null. |
| `0x00434F70` | `src/archive/dat.cpp:48-113`; IDA `../ida/th10.exe.c:50213-50289`, assembly `../ida/th10.exe.asm:75423-75571`; Ghidra `../decompiled/ghidra_raw/00434F70_FUN_00434f70.c:12-93` | **partial**: header/open, 16-byte decode, biased size/count fields, end-of-file table seek, decrypt/decompress, parse, and cleanup agree. The source requires an exact 16-byte header read where retail accepts a nonzero virtual-read result, and resets `entry_count` on parse failure where retail leaves the owner state to its cleanup path; file/vtable ownership is also typed. |
| `0x004350D0` | `src/archive/dat.cpp:280-308`; IDA `../ida/th10.exe.c:50291-50330` and continuation, assembly `../ida/th10.exe.asm:75577-75730`; Ghidra `../decompiled/ghidra_raw/004350D0_FUN_004350d0.c:12-79` | **partial for allocation/error paths, grounded for valid packed tables**: entry-count-plus-sentinel allocation, aligned names, three metadata words, and terminal offset agree. Retail uses an exception-aware vector constructor and frees through the element destructor; the host `_malloc`/manual loop does not roll back earlier names if a later name allocation fails. |

These rows add 12 address-level findings to the ending report. No production,
coverage, or shared status file was changed.

The source returns `float`, while retail returns an x87 `double`/extended
result and uses global constants (`1.0`, `2.0`, `0.5`, `0.0`) in the assembly.
The helper is called by trajectory code that stores output in floats, so this
is generally a downstream precision boundary, but callers requiring the raw
return format are outside the host API. Arithmetic order and extended-register
precision can also differ from the C++ float temporaries; the available static
references do not establish a live retail floating-point control word.

## Validation

```text
g++ -std=c++17 -Wall -Wextra -Werror -Iinclude \
  src/game/trajectory_evaluate.cpp tests/trajectory_evaluate_test.cpp \
  -o /tmp/trajectory_evaluate_test
/tmp/trajectory_evaluate_test
recovery_batch38_test passed

g++ -std=c++17 -Wall -Wextra -Werror -Iinclude \
  src/game/trajectory_evaluate.cpp /tmp/trajectory3d_audit_probe.cpp \
  -o /tmp/trajectory3d_audit_probe
/tmp/trajectory3d_audit_probe
TRAJECTORY3D_PASS current=2 duration=0 output=10
```

The temporary probe covers representative 3D mode/completion cases and the
same near-half-speed conversion boundary seen in the earlier 2D probe. It also
prints the mode-11 counterexample:

```text
TRAJECTORY_CASE11 source=0.9375 retail_reference=0.03125
TRAJECTORY3D_PASS current=2 duration=0 output=10
```

The repository test driver also completed with exit code 0 (`./test.sh`),
including the archive, FPS-counter, and version-marker focused tests. Its
trace-comparison negative cases intentionally print `TRACE_COMPARE_FAIL` while
the enclosing test validates that those diagnostics are detected.

The `current=2` result is host behavior and is retained as a precision
boundary, not presented as a live retail mismatch.

No production code, registry, coverage ledger, or shared status file was
changed for this audit.
