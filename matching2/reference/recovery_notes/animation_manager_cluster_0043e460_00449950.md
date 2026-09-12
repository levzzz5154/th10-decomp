# Animation-manager semantic cluster: `0x0043E460` through `0x00449950`

## Status

The requested 15-region, 2274-byte animation-manager cluster remains
production assembly. No region passed the independent exact extent/byte gate,
so no production semantic source, task-local LTCG layout/context, or
integration proposal was retained. `matching2/msvc/regions.json` was not
modified.

The production sources remain the existing naked-assembly owners for:

```text
0x0043E460  104  RegisterResource
0x00449950  161  AllocateObject
0x00448BB0  268  RemoveObject
0x00447810  242  ReleaseResourceBatch
0x00448E30   73  CreatePrimaryFront
0x00448F60   73  CreateSecondaryBack
0x00449090   73  CreateSecondaryFront
0x00449870  217  InitializeScriptState
0x0043E710  203  LoadScript
0x0043E7E0  194  LoadScriptPreservingState
0x00446220  206  DestroyStorage
0x00448A50  112  RegisterPrimaryFront
0x00448B40  112  RegisterSecondaryFront
0x004489D0  118  RegisterPrimaryBack
0x00448AC0  118  RegisterSecondaryBack
```

The archived semantic source used for the candidate was
`matching2/reference/legacy_semantic/src/render/animation_manager.cpp`, with
the layout contracts from
`matching2/reference/legacy_semantic/include/th10/render/animation_manager.hpp`.
The existing exact helper at `0x004493E0` was included read-only as the
proven native-LTCG dependency; its production source and layout were not
changed.

## Bounded cluster attempt

A fresh disposable project copy compiled one semantic TU containing the full
dependency cluster: resource-record installation, pool allocation, list
registration/removal, create wrappers, script loading and initialization,
batch release, storage destruction, plus the exact retired-resource helper.
The candidate used the legacy field offsets and the live custom-ABI calls to
`InitializeEntity`, `Entity` construction/destruction, `free`, `operator new`,
and script execution.

The native cluster did not reach the byte comparison gate because the
cumulative candidate extents moved the synthetic context entry from the
declared `0x00449A00` to `0x00449F30`. The MAP still records each complete
candidate contribution. In requested address order, the candidate lengths
were:

```text
address     candidate  retail
0043E460          69      104
0043E710         201      203
0043E7E0         190      194
00446220         155      206
00447810         178      242
004489D0         128      118
00448A50         100      112
00448AC0         128      118
00448B40         100      112
00448BB0         246      268
00448E30         523       73
00448F60         549       73
00449090         523       73
00449870         261      217
00449950         170      161
```

Thus every requested contribution failed the independently required body
extent before bytes could be promoted. The most significant structural
mismatches are the standard C++ argument/return conventions in the script
and list routines, the inlined shared create path (523/549 bytes versus the
73-byte wrappers), and the missing retail exception/vector-destruction
prologue shape in storage teardown. These are ordinary semantic/compiler
context failures, not evidence that any region is irreducible or
assembly-required.

The attempted candidate also showed initial byte differences in the overlap
for every inspected target; those comparisons were diagnostic only because
the cumulative non-retail extents displaced later functions and the cluster
never satisfied its fixed-address context gate. No byte claim was promoted.

## Cleanup and next dependency

The disposable candidate source, cluster manifest/context, generated MAP/PE,
and probe directories were removed after the failed attempt. No shared
tooling, production code, `regions.json`, or unrelated/concurrent source or
layout file was changed by this recovery attempt.

The next useful dependency is a compiler-visible model of the manager's
internal register ABI that preserves the retail entry conventions while also
preventing the shared create/registration bodies from being inlined across
their 73/112/118-byte ownership boundaries. A future attempt should first
prove one such leaf in a focused cluster, then rebuild the coupled cluster;
until that proof exists, the exact assembly owners are retained.

## Wrapper-only follow-up: `0x004489D0`..`0x004490D9`

The seven-wrapper follow-up also remains unpromoted. The production sources
and `regions.json` were left unchanged; no task-local production layout,
context, or proposal was retained because none of the seven wrappers passed
the exact gate.

The bounded candidate used four distinct `__declspec(noinline)` semantic
`AnimationManager` member methods for primary/secondary front/back list
registration. A synthetic LTCG context invoked member pointers to preserve
the observed internal `this`/object/output-register pressure. The three
create wrappers stayed separate stdcall contributions and called the retail
allocator/initializer dependencies rather than inlining registration bodies.
The exact `0x004493E0` helper was included read-only.

The linked MAP contributions were:

```text
address     emitted entry  candidate extent  retail extent
004489D0    004489D0       124               118
00448A50    00448A60       106               112
00448AC0    00448AD0       124               118
00448B40    00448B60       106               112
00448E30    00448E50        82                73
00448F60    00448F90        82                73
00449090    004490D0        82                73
```

Every wrapper therefore failed its independently required body extent. The
first diagnostic byte differences, compared from each emitted candidate entry
against the corresponding retail entry, were:

```text
004489D0: candidate 57, retail 8D, first +0x00
00448A50: candidate 56, retail 8D, first +0x00 (candidate entry +0x10)
00448AC0: candidate 57, retail 8D, first +0x00 (candidate entry +0x10)
00448B40: candidate 56, retail 8D, first +0x00 (candidate entry +0x20)
00448E30: candidate 56, retail 53, first +0x00 (candidate entry +0x20)
00448F60: candidate 56, retail 53, first +0x00 (candidate entry +0x30)
00449090: candidate 56, retail 53, first +0x00 (candidate entry +0x40)
```

The displaced-entry comparisons are diagnostic only; the extent failures are
already sufficient to reject promotion. An attempted layout-only realignment
was rejected by the cluster loader because shorter/longer candidate bodies
would overlap the declared retail extents. This is a normal compiler
register/prologue and ownership-boundary mismatch, not proof of an
exact-assembly-required classification.

The wrapper lab, compiler output, MAP/PE, and probe directories were removed
after the failed follow-up. The next dependency remains a compiler-visible
internal ABI model that reproduces the exact four list-method prologues and
the three 73-byte create-wrapper call schedule while retaining noinline
ownership boundaries.
