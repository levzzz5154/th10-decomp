# 0x004127A0 — exact spell-timer slot advance

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27: ordinary C++ now emits all 593 retail bytes under native MSVC
13.10.6030 `/GL` + LINK `/LTCG`. The external receiver is a public, rooted
`SpellTimerState_004127a0::AdvanceSlots()` member: ECX receiver, EAX resource
result, no stack arguments and plain RET. The synthetic array caller is compiler
context only and contributes no recovered code.

Fresh Ghidra MCP `decompile_function`, `disassemble_function`, and 593-byte
`read_memory` responses for `th10.exe` are retained in the experiment directory.
The memory response equals the retail oracle. Both byte strings have SHA-256
`ef3572398ce7dd9d852c81897b40950cce7879b93f9fcbf0bc9f3fea9f303113`.

The global countdown is typed as an integer, the timer-display pointer uses a
padded structure with `remaining_seconds` at +0x9EC0, and the clock speed points
to the named float symbol `data_00476f78`. These remove every reinterpret cast
and raw memory-field access while preserving all 593 emitted bytes.

The C++ distinguishes the armed resource at slot +8 from the due resource at
slot +12, preserves the indexed slot result after stage effects, models the
20-byte clock and padded stage fields, and uses a shared null-result exit.
The inlined clock reset and shared exit are necessary source shapes: direct
clock stores plus separate returns emitted 611 bytes; an inlined reset alone
emitted 595. With both shapes, 593 bytes differed only in the schedule of the
charge-zero store at +0x3790. `_ReadWriteBarrier()` immediately after that store
emits no machine instruction and preserves its position before mask setup.

This is compiler scheduling control, with no inline assembly, naked body, byte
payload, post-compilation instruction rewriting, masked bytes, or reference
bytes as build inputs. A fresh maintained `probe.py` invocation in the copied
project reports `exact: true`, `different_bytes: 0`, zero relocations, and zero
instruction/address-operand changes for the complete 593-byte region.

The historical 0.870 note reported 593–595 emitted bytes and instruction-shape
similarity. It did not prove the later annotation that 554 of 593 bytes matched.
This fresh byte comparison supersedes that unsupported historical wording.

## Promotion files

- `msvc/src/game/spell_timer.cpp`
- `msvc/layout/ltcg/spell_timer_advance_slots_004127a0.json`
- `msvc/layout/ltcg/spell_timer_advance_slots_004127a0_context.cpp`
- this note, as `reference/recovery_notes/spell_timer_advance_slots_004127a0_model.md`

Register only the final layout. The scratch manifest contains exactly one
spell-timer cluster; previous experimental layouts must not be registered.
Keep the old assembly name as the fixed-address alias used by unrecovered
callers. The member symbol is the selected recovered region.

## Verification

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/spell_timer/msvc \
  --source src/game/spell_timer.cpp \
  --output matching2/build/experiments/spell_timer/typed_globals_probe --json
```

Full probe evidence: `typed_globals_probe.json` and
`typed_globals_probe/clusters/spell_timer_advance_slots_004127a0/report.json`.

Promoted on 2026-09-27 through the staged manifest/touched-cluster gates in `promote_scratch.py`. The current maintained source uses typed globals and the named default-speed symbol, as verified by `typed_globals_probe.json`. The full-executable rebuild remains the final integration gate.
