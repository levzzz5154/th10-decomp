# Current verified checkpoint: five recoveries, 665 bytes

Full access resolved Wine's socket-binding startup failure. The goal is active.
This continuation recovered five complete assembly owners as native C++:

| Address | Function | New bytes |
| --- | --- | ---: |
| 0043C8B0 | Screen effect factory | 82 |
| 0040D6B0 | Enemy manager factory | 95 |
| 0040D530 | Enemy manager teardown | 300 |
| 00404530 | Game-state BeginFade | 119 |
| 00425020 | Large player resource factory | 69 |

All five fresh main probes passed. The final whole build compiled 1,889
maintained sources and two optional compiler sources without failures. The
entire 487,936-byte executable equals the original literally, SHA256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The current build is `matching2/build/resumed_wave7_msvc_2026_10_01`.

| Current classification | Regions | Bytes |
| --- | ---: | ---: |
| Fully assembly-free C++ | 1,886 | 98,945 |
| All semantic ownership | 1,891 | 103,396 |
| Remaining ASM ownership | 410 | 219,532 |
| Toolkit library | 322 | 66,470 |
| Embedded .text data | 7 | 7,779 |
| Padding | 1,770 | 15,495 |

Five older semantic functions contain six inline x87 blocks totaling 4,451
bytes. They explain the difference between semantic and fully assembly-free
totals. The goal remains incomplete; this is verified progress.

The final 69-byte factory uses ordinary C++ linkage and a genuine
`new PlayerResetBlock` expression. Its complete constructor contains stores,
intrinsic clears, and pointer publication. The normal `/EHsc /GL` compiler emits
no exception frame or unwind contribution, matching the original. This was
verified with C++ linkage, independently of the earlier C-linkage diagnostic.
The null-allocation path still calls Initialize; no early return was added.
Failure invokes the original stack-argument cleanup and ordinary operator
delete. The full factory's native instructions, call targets, and ABI are exact.

The genuine Reset and Initialize models have complete native extents of 244
and 1,234 bytes, versus original extents of 244 and 1,435. Reset's six differing
bytes select scratch registers and preserve effective addresses, flag masks,
constants, and operation order. Initialize retains the complete resource,
parameter, scheduler, timer, 33-entry history, and four bounds-pair operations.
Both original main ASM owners and sources remain unchanged; neither model
receives recovery credit. The complete real caller also remains unselected:
109 native bytes versus 101 original bytes, with a different entry ABI.

All 11 full helper contributions are declared and measured. Seven match
literally: parameter load229, script load203, primary/secondary registration131
each, menu advance128, archive load360, and log append201. Configure204 versus
202 and callback creation74 versus74 remain nonmatching, alongside Reset and
Initialize. All helpers receive zero new credit. Private helper receivers are
established by their complete co-compiled bodies. Conventional external
boundaries retain their observed ABI, including Entity_Init's unused nominal
ECX register slot and actual entity pointer in EDX.

The current independent whole-build audit verifies all source hashes, the
exact source/manifest snapshot, and all 23 complete new C++ owners since the
permissions fix (2,935 bytes, including the earlier 10-byte D3D handler
attribution correction). The current native PE/MAP audit checks 29 complete
contributions across three clusters: 25 match literally, totaling 4,000 bytes;
four nonmatching models are explicitly unselected. Only 665 bytes are new
credit in this continuation. Existing helpers are counted once.

All original aliases, unaffected ownership, compiler settings, and toolkit
are preserved. The compiler/probe framework is unchanged. There are zero
instruction rewrites, address-operand rewrites, masks, or reference bytes used
to build. Original sources and manifests are backed up before each integration.

The failed sound and enemy-list candidates are retained as diagnostics with
zero credit. Sound109 matches, but its genuine caller's cleanup has a one-byte
frame-offset mismatch. Sixteen full enemy-list variants failed the 118-byte
gate. The 102-byte score evaluator has a readable behavior model and saved
Ghidra analysis, but no genuine caller establishing its private ABI.

Current proof files are under
`matching2/build/experiments/wine_startup_diagnosis_2026_10_01`:
`wave7_verified.json`, `wave7_native_verified.json`,
`wave7_regions_before_build.json`, and `wave7_main_large_factory_probe.json`.
Earlier wave5/wave6 receipts and recovery notes are historical checkpoints.
The separate large-factory `audit.md` and `evidence.json` are under
`matching2/build/experiments/native_large_resource_state_2026_10_01`.

```
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_resumed_eh_build.py --build matching2/build/resumed_wave7_msvc_2026_10_01 --snapshot matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave7_regions_before_build.json --evidence matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave7_verified.json
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_wave7_native.py
```
