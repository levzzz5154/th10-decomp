# Verified stage fade and factory checkpoint

The goal remains active after full access resolved Wine's socket-binding
failure. This continuation recovered four complete functions, totaling
**596 additional assembly-free bytes**: screen effect factory (82), enemy factory
(95), enemy teardown (300), and game-state BeginFade (119). The first 477 bytes are recorded
in `resumed_factory_wave_2026-10-01.md`; this checkpoint adds BeginFade.

Fresh main probes and the whole executable build passed. All 487,936 executable
bytes equal the original literally. The build compiled 1,889 maintained sources
and two optional compiler sources with zero failures. SHA256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

| Current classification | Regions | Bytes |
| --- | ---: | ---: |
| Fully assembly-free C++ | 1,885 | 98,876 |
| All semantic ownership | 1,890 | 103,327 |
| Remaining ASM ownership | 411 | 219,601 |
| Toolkit library | 322 | 66,470 |
| Embedded .text data | 7 | 7,779 |
| Padding | 1,770 | 15,495 |

Five older semantic functions contain six inline x87 blocks totaling 4,451 bytes,
so semantic ownership is larger than fully assembly-free C++ ownership. The
remaining assembly is substantial and the goal is not complete.

BeginFade's 119-byte contribution at 00404530 preserves its private ESI receiver,
effect factory call, lazy timer initialization, three final timer stores, and
flags update. The ordinary `_ReadWriteBarrier` intrinsic emits no instructions
and preserves the original ordering before the final flags read/modify/write.
Its original ASM record, owner, extent, and old symbol alias are retained in
the manifest's recovery history. Existing factory82 and selector396 ownership
records and sources remain unchanged.

The complete original stage-update caller is 1,544 bytes. Its full readable
compiler context emits 1,570 bytes, is explicitly nonmatching, and remains
unselected with zero ownership credit. All 20 external helper declarations are
documented separately: their logical inputs come from original bodies and
call sites, while several ordinary source ABIs differ from the original private
register agreements. The context cannot run against those original private
helper ABIs. It is retained to reconstruct the compiler's selected contributions;
the maintained stage-update ASM owner is unchanged. No synthetic caller or
additional helper argument was used. The unused nominal receiver of the music
dummy was removed after its original body confirmed only two stack inputs.

Independent current audits verify the entire executable, exact manifest
snapshot, every source hash, and 22 complete new C++ owners since the permissions
fix totaling 2,866 bytes, including the earlier 10-byte D3D handler attribution
correction. A separate native PE/MAP audit verifies 17 complete contributions
across the two factory clusters totaling 2,548 exact bytes. Existing
helpers receive no duplicate recovery credit. Compiler settings, toolkit,
framework, all previous aliases, and unaffected owners are preserved. There
are zero byte rewrites, masks, or reference bytes used to build.

The enemy list-release followup tested 16 complete native candidates and recovered
zero additional bytes. Its faithful baseline emits 109 versus 118 original bytes,
with different parameter homing, register allocation, and loop alignment. The
sound constructor remains diagnostic: 109 bytes and its full 879-byte helper
closure match, but the faithful caller's cleanup has a one-byte frame-offset
difference. Neither failed candidate changes these totals. The separately
documented 102-byte score evaluator also remains ASM with no genuine caller.

The current artifact is `matching2/build/resumed_wave6_msvc_2026_10_01/th10.exe`.
Evidence, before-integration backups, source snapshot, and focused probes are
under `matching2/build/experiments/wine_startup_diagnosis_2026_10_01`:
`wave6_verified.json`, `wave6_native_verified.json`, and
`wave6_regions_before_build.json`. Earlier wave5 receipts remain unchanged as
historical checkpoints. Reproduce the current audits with:

```
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_resumed_eh_build.py --build matching2/build/resumed_wave6_msvc_2026_10_01 --snapshot matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave6_regions_before_build.json --evidence matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave6_verified.json
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_wave6_native.py
```
