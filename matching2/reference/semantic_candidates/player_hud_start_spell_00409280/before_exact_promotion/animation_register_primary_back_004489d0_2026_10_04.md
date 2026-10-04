# Primary-back animation registration at 0x004489D0 — exact C++

The complete 118-byte region is now ordinary C++, selected from
`msvc/src/render/animation_manager_register_primary_back_004489d0.cpp` through
`msvc/layout/ltcg/animation_register_primary_back_004489d0.json`. The private ABI
is manager in EDX, entity in EBX, hidden handle-result pointer in EAX, and RET.
The original assembly body has been replaced only after the production probe
reported EXACT. Its old linker symbol remains an address alias for existing
callers.

The handle uses unsigned 32-bit storage, a prefix increment returning a reference
to itself, and comparison against another handle. The registrar spells the guard
as `++next_id; if (next_id == 0) ++next_id;`. This ordinary class operation
produces retail's load/increment/copied test/store sequence and the increment in
the zero arm. The scalar-field spellings previously folded the zero arm or used
a different scratch register. Both signed storage and explicitly wrapping or
unsigned storage were tested; they produce the same complete registrar bytes.
The selected header uses unsigned storage to define wrapping. Unused postfix
increment and integer-assignment operators are unnecessary and were removed.
There are no compiler barriers, volatile accesses, inline assembly or byte edits.

The cluster retains the complete unselected spell-card caller and all its native
callee bodies, plus a synthetic array caller. The spell-card caller is not
recovered by this cluster: it differs by one SIB byte at 0x004093A4. It is kept
in `equivalent/game/player_hud_start_spell_00409280.cpp` as the maintained
equivalent recovery. This cluster uses it solely for compiler context. The selected registrar is compiled in the driver's translation
unit; the seven separate dependency wrappers have unique cluster ownership.
This full graph naturally gives the selected function its retail ABI and keeps
its complete contribution at the retail address.

Focused production probe:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_manager_register_primary_back_004489d0.cpp
```

Evidence is in `animation_register_primary_back_004489d0_2026_10_04_evidence.json`;
the native compiler/linker artifacts are under
`matching2/build/experiments/spell_goal_2026_10_04/registration_production_probe/`.
The full normal and EXACT builds pass. `cmp` independently confirmed the exact
487,936-byte executable equals the retail oracle. Recovery is now 2,201 ordinary
C++ regions / 166,279 bytes and 117 assembly regions / 123,309 bytes: 61.6% of
application bytes including equivalent C++, and 95.0% of application regions.

This supersedes the primary-back disposition in
`animation_register_004489d0_riscify_2026_10_03.md` and the older wave notes.
The sibling registrars are not claimed recovered by this result.
