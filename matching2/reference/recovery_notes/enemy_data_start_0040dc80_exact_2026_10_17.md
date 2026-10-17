# Enemy data start 0x0040DC80: byte-exact (2026-10-17)

Follows `enemy_data_start_0040dc80_decode_2026_10_12.md`. The three recorded
hunks (9 bytes) are gone: the 2,412-byte per-enemy update is selected by the
LTCG cluster `msvc/build_support/layout/ltcg/enemy_data_start_0040dc80.json`
from `src/game/enemy/enemy_data_start.cpp`, and the assembly region and the
equivalent layout are removed.

## The last residual (668 -> 671 of 671)

At the spell-slot restart (0x0040E1C7) retail keeps the `AdvanceSlots` result
in ESI and loads the two `BindName` arguments in source order
(`mov ecx,esi` before the record reload); the model kept the result in EDI and
loaded the record first. Both follow one lever: the callee's parameter order
sets the caller's argument load order (`msvc-ltcg-callee-param-order-sets-
caller-load-order`), and the private conventions ignore declarations.
Permuting the context helper's parameters fixes both at once:

```cpp
int __fastcall BindName(EnemyRecord* record, const char* name);
```

with the call sites updated to match. Named record/entry locals around the
block leave the model unchanged or worse.

## Promotion

The cluster compiles the model with the fifteen recovered helper bodies as
anchors at their retail addresses (`src/game/enemy/enemy_data_start_context.cpp`
with one `code_seg` region per helper) and `RigEntry` as the context entry. The
two `Interpolator::Step` bodies come through one-line wrappers on their own
recovered sources (`vec3_interpolator.cpp`, `trajectory_interpolator.cpp`,
already exported byte-exact by `evaluate_curve`): template members take the
section in effect at the end of the file, so they cannot share the helper
translation unit. The context's stand-in globals became `extern` declarations
bound at their retail addresses, which is how the model already sees them. All
2,412 bytes are exact; `make EXACT=1` is unchanged.
