# Host callback contract review queue

21 heuristic candidates require contract review. This count is neither a bug count nor an exhaustive placeholder count.

The ordinary placeholder gate checks different syntax. Its zero result does not clear these rows.

For each candidate establish whether the operation is unreachable, owned elsewhere, intentionally adapted, or missing. Cite the binding and retail effect before accepting an adapter.

- Regex candidates include inactive preprocessor branches and intentional adapters.
- Only the listed return types and shallow function syntax are recognized; this is not a C++ parser.
- No nested-body/lambda/indirect-call completeness claim; absence of a candidate proves nothing.
- A token occurrence is not proof of execution. Verify providers and their exact retail contracts.
- Existing placeholder exemptions are prior claims, not inherited audit verdicts.

| Function | Source | Signal | Status |
| --- | --- | --- | --- |
| `HostMaybeCaptureFrame` | `standalone/host_main.cpp:4164` | no_work | pending |
| `HostNop` | `standalone/host_main.cpp:5536` | no_work | pending |
| `HostDestroyScheduler` | `standalone/host_main.cpp:6681` | no_work | pending |
| `HostSoundNothingToRelease` | `standalone/host_main.cpp:6717` | no_work | pending |
| `HostMidiNothingToRelease` | `standalone/host_main.cpp:6823` | no_work | pending |
| `HostDestroyNoop` | `standalone/host_stage.cpp:432` | no_work | pending |
| `HostSleep` | `standalone/host_stage.cpp:433` | no_work | pending |
| `BulletVmNoRing` | `standalone/host_stage.cpp:924` | no_work | pending |
| `BulletVmNoChild` | `standalone/host_stage.cpp:928` | no_work | pending |
| `BulletVmNoRingUpdate` | `standalone/host_stage.cpp:935` | no_work | pending |
| `HostScoreConstructBase` | `standalone/host_stage.cpp:1074` | no_work | pending |
| `HostScoreDestroy` | `standalone/host_stage.cpp:1076` | no_work | pending |
| `HostReplaySeed` | `standalone/host_stage.cpp:1595` | no_work | pending |
| `HostRegisterBulletSprite` | `standalone/host_stage.cpp:1732` | no_work | pending |
| `HostPlayerRequestsDestroy` | `standalone/host_stage.cpp:3103` | constant_result | pending |
| `HostDestroyPlayer` | `standalone/host_stage.cpp:3104` | no_work | pending |
| `StageDigitNoRing` | `standalone/host_stage.cpp:3187` | no_work | pending |
| `StageDigitNoChild` | `standalone/host_stage.cpp:3191` | no_work | pending |
| `StageDigitNoRingUpdate` | `standalone/host_stage.cpp:3198` | no_work | pending |
| `HostModeEnterCritical` | `standalone/host_stage.cpp:3601` | no_work | pending |
| `HostModeLeaveCritical` | `standalone/host_stage.cpp:3602` | no_work | pending |

The JSON companion preserves bodies, hashes and all textual occurrences in `src/**/*.cpp` and `standalone/*.cpp`.

`--check` verifies freshness only. `--strict` returns nonzero while this review queue is nonempty.
