# Permissions restored: eleven native C++ recoveries

Full access resolved the session's Unix socket restriction. Wine's server
can bind its socket, the pinned MSVC toolchain starts, and Ghidra MCP works.
The resumed goal is active. No compiler-framework change, Wine reinstall,
or prefix reset was required. Builds use the existing writable prefix
`/tmp/th10-decomp-wine-20261001`.

The fresh build in `matching2/build/resumed_wave2_msvc_2026_10_01` compiled
1,894 maintained translation units with no failures. Its complete
487,936-byte executable literally equals the retail oracle. Every maintained
source hash is current. Executable SHA-256 is
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

Compared with the verified pre-resumption baseline, these eleven complete
native functions moved from assembly ownership to ordinary C++:

| Address | Function | Bytes |
| --- | --- | ---: |
| `00405AC0` | Player Draw | 124 |
| `00408100` | Collision Check | 260 |
| `0040A3C0` | CounterState Create | 67 |
| `00419F40` | Stage ReadLine | 260 |
| `0041FD00` | TitleState Create | 69 |
| `00421F00` | LargeState Initialize | 71 |
| `0042B660` | HugeResource Create | 71 |
| `0042BF30` | EffectPool Create | 67 |
| `0042CD50` | ProgressManager CreateAndStartWorker | 96 |
| `0044D110` | SoundStream Fill | 483 |
| `0044DE10` | ArchiveCursor Read | 202 |
| **Total** | | **1,770** |

All eleven bodies have their complete original extents, original addresses,
and literal original instruction bytes in native compiler output. The
production reports record zero instruction rewriting, zero operand
rewriting, zero masked bytes, and no retail bytes used to construct native
output. Original owner records and symbol bindings are preserved. Already
semantic constructors, callers, and helper functions in these clusters
receive no additional recovery credit.

The factories share the actual class definitions with their real
constructors and initializers. Extracting GameConfig's definition also
required preserving the surrounding code sections of its existing worker
and UI consumers; the source guard and both include wrappers were verified
through those complete original callers and the whole build.

Sound filling retains callback reloads, restore behavior, ignored results,
and the original possibility of no progress. Its isolated native
differential fixtures cover callback aliasing and matching faults. Collision
checking retains the unordered floating-point comparison behavior.
Archive reading uses the pinned compiler's forward intrinsic memcpy
sequence; no portable overlap guarantee or new dynamic archive test is
claimed. Stage reading retains its original unchecked caller contracts.

At this checkpoint:

| Ownership | Regions | Bytes |
| --- | ---: | ---: |
| Semantic C++ | 1,879 | 102,231 |
| Fully assembly-free C++ | 1,874 | 97,780 |
| Assembly | 421 | 220,687 |
| Toolkit runtime library | 323 | 66,480 |
| Embedded .text data | 7 | 7,779 |
| Padding | 1,770 | 15,495 |

Fully assembly-free C++ is a subset of semantic C++. Five semantic functions
still contain six x87 assembly blocks, covering 4,451 bytes. The overall
decompilation goal remains incomplete. Nonmatching player-update, pixel-fill,
parser, and x87 diagnostics retain their original ownership.

Repeat the whole-build and complete native-owner provenance audit with:

```sh
python3 matching2/build/experiments/wine_startup_diagnosis_2026_10_01/verify_resumed_build.py \
  --build matching2/build/resumed_wave2_msvc_2026_10_01 \
  --snapshot matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave2_regions_before_build.json \
  --evidence matching2/build/experiments/wine_startup_diagnosis_2026_10_01/wave2_verified.json
```

The audit checks the current manifest against its frozen snapshot, every
current source hash, whole executable equality, complete new native bodies,
compiler inputs and includes, native PE/MAP/object/report hashes, unchanged
compiler profiles and historical symbol bindings. Subsequent integrations
require a fresh build and snapshot; the current-source audit then correctly
rejects this older checkpoint. The companion evidence JSON preserves the
verified result. Earlier baseline, archive-only, and eight-function build
artifacts remain separate historical checkpoints.
