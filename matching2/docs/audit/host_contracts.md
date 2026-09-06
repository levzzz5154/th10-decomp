# Host callback contract review queue

27 heuristic candidates require contract review. This count is neither a bug count nor an exhaustive placeholder count.

The ordinary placeholder gate checks different syntax. Its zero result does not clear these rows.

For each candidate establish whether the operation is unreachable, owned elsewhere, intentionally adapted, or missing. Cite the binding and retail effect before accepting an adapter.

- Regex candidates include inactive preprocessor branches and intentional adapters.
- Only the listed return types and shallow function syntax are recognized; this is not a C++ parser.
- No nested-body/lambda/indirect-call completeness claim; absence of a candidate proves nothing.
- A token occurrence is not proof of execution. Verify providers and their exact retail contracts.
- Existing placeholder exemptions are prior claims, not inherited audit verdicts.

| Function | Source | Signal | Status |
| --- | --- | --- | --- |
| `HostMaybeCaptureFrame` | `standalone/host_main.cpp:4219` | no_work | pending |
| `HostNop` | `standalone/host_main.cpp:5591` | no_work | pending |
| `HostDestroyScheduler` | `standalone/host_main.cpp:6736` | no_work | pending |
| `HostSoundNothingToRelease` | `standalone/host_main.cpp:6772` | no_work | pending |
| `HostMidiNothingToRelease` | `standalone/host_main.cpp:6878` | no_work | pending |
| `HostDestroyNoop` | `standalone/host_stage.cpp:393` | no_work | pending |
| `HostSleep` | `standalone/host_stage.cpp:394` | no_work | pending |
| `BulletVmIntSlot` | `standalone/host_stage.cpp:883` | shared_fallback_slot | pending |
| `BulletVmFloatSlot` | `standalone/host_stage.cpp:890` | shared_fallback_slot | pending |
| `BulletVmRandFloat` | `standalone/host_stage.cpp:906` | constant_result | pending |
| `BulletVmRandU32` | `standalone/host_stage.cpp:911` | constant_result | pending |
| `BulletVmNoRing` | `standalone/host_stage.cpp:925` | no_work | pending |
| `BulletVmNoChild` | `standalone/host_stage.cpp:929` | no_work | pending |
| `BulletVmNoRingUpdate` | `standalone/host_stage.cpp:936` | no_work | pending |
| `HostScoreConstructBase` | `standalone/host_stage.cpp:1075` | no_work | pending |
| `HostScoreDestroy` | `standalone/host_stage.cpp:1077` | no_work | pending |
| `HostReplaySeed` | `standalone/host_stage.cpp:1596` | no_work | pending |
| `HostRegisterBulletSprite` | `standalone/host_stage.cpp:1733` | no_work | pending |
| `HostPlayerRequestsDestroy` | `standalone/host_stage.cpp:3104` | constant_result | pending |
| `HostDestroyPlayer` | `standalone/host_stage.cpp:3105` | no_work | pending |
| `StageDigitIntSlot` | `standalone/host_stage.cpp:3187` | shared_fallback_slot | pending |
| `StageDigitFloatSlot` | `standalone/host_stage.cpp:3194` | shared_fallback_slot | pending |
| `StageDigitNoRing` | `standalone/host_stage.cpp:3229` | no_work | pending |
| `StageDigitNoChild` | `standalone/host_stage.cpp:3233` | no_work | pending |
| `StageDigitNoRingUpdate` | `standalone/host_stage.cpp:3240` | no_work | pending |
| `HostModeEnterCritical` | `standalone/host_stage.cpp:3643` | no_work | pending |
| `HostModeLeaveCritical` | `standalone/host_stage.cpp:3644` | no_work | pending |

The JSON companion preserves bodies, hashes and all textual occurrences in `src/**/*.cpp` and `standalone/*.cpp`.

`--check` verifies freshness only. `--strict` returns nonzero while this review queue is nonempty.
