# Three factory-wave recoveries, 477 bytes

Full access resolved Wine's socket-binding failure. The goal is active. This
checkpoint follows `resumed_native_followup_2026-10-01.md` and adds three
complete native C++ contributions:

| Original address | Behavior | New assembly-free bytes |
| --- | --- | ---: |
| 0043C8B0 | Create and initialize the screen-effect controller | 82 |
| 0040D6B0 | Create, publish, and initialize the enemy manager | 95 |
| 0040D530 | Release enemy-manager resources and unregister its tasks | 300 |

The ordinary main probes passed all four selected bodies: the three new owners
and the existing 396-byte screen-effect selector. The fresh full build compiled
1,890 maintained sources and two optional compiler sources without failures.
Its entire 487,936-byte executable equals the retail oracle literally:
SHA256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The compiler profile, toolkit, original aliases, and unaffected owners remain
unchanged. No byte rewriting, masking, or reference bytes were used to build.

Current totals are 1,889 semantic regions /103,208 bytes. Five older semantic
owners still contain six inline x87 blocks totaling4,451 bytes, so fully
assembly-free C++ is **1,884 regions /98,757 bytes**. Remaining ASM ownership is
**412 regions /219,720 bytes**. Library ownership is322 regions /66,470 bytes;
.text data is7,779 bytes and padding15,495 bytes. The goal is not complete.

Independent audits checked current source hashes, every complete new native
owner since the permissions fix, and all16 whole selected/anchor contributions
in the two new clusters, totaling2,429 literal-equal bytes. Only477 bytes are
new credit at this checkpoint; existing selectors and dependencies are counted
once. The generated D3D exception handler's earlier narrow library correction
remains independently audited; this wave adds no library reclassification.

The real game-state fade caller at00404530 is119 original bytes and emits131;
the real enemy-factory caller at0040A350 is101 original bytes and emits109.
Both full contexts remain explicitly unselected and nonmatching. Their
maintained ASM owners receive no credit. The new selector cluster replaces an
older synthetic allocation context with the complete genuine fade caller.

The factories preserve retail's pre-wipe accesses to freshly allocated timer
flag words. This documents MSVC's actual allocation-memory behavior, without
claiming a portable ISO C++ guarantee for uninitialized memory. The screen
factory's native private ABI is six logical arguments: priority inEBX plus
five stack arguments, RET20. The enemy initializer still runs after a null
allocation, preserving the original failure behavior.

The sound initializer remains diagnostic: its109-byte body matches, but its
faithful full caller's generated cleanup is not yet exact. A saved readable
model and Ghidra analysis of the102-byte two-vector score evaluator also remain
diagnostic because no genuine caller establishing its private ABI was found.
Neither candidate changes the current totals.

Artifacts are retained under `matching2/build/resumed_wave5_msvc_2026_10_01`.
The exact manifest snapshot, before-integration backup, main probe JSON,
`wave5_verified.json`, and `wave5_native_verified.json` are under
`matching2/build/experiments/wine_startup_diagnosis_2026_10_01`.
The independent verifier commands are:

```
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_resumed_eh_build.py --build matching2/build/resumed_wave5_msvc_2026_10_01 --snapshot matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave5_regions_before_build.json --evidence matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave5_verified.json
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_wave5_native.py
```
