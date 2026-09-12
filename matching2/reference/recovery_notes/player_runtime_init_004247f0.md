# Player runtime initialization: `0x004247F0`

## Result

This lane did not produce an exact semantic replacement. The production
`matching2/msvc/src/game/player_runtime_init.cpp` remains the retail naked
assembly body, and `matching2/msvc/regions.json` was not edited. No semantic
source, LTCG layout/context, or proposal was retained from the failed probe.

The live manifest extent is authoritative: `0x004247F0..0x00424D8A`, 1,435
bytes. Ghidra reports the two body ranges
`0x004247F0..0x00424938` and `0x00424940..0x00424D8A`, separated by the
seven-byte jump-over layout sequence at `0x00424939`.

## Reconstructed behavior

The entry is a caller-carried custom-ABI routine: the player runtime object is
in `EBX`, there are no ordinary arguments, the status is returned in `EAX`,
and the routine uses a plain `RET`. The observed operation is:

1. Select the character-dependent resource name at `0x0046E42C` or
   `0x0046E420` from `[0x00474C68]`. Load it through cached-resource helper
   `0x00447280` with index `8`, owner `[0x00491C10]`, and the name on the
   stack; store the result at `[EBX+0x10]`. A null result calls the exact
   logger `0x0044B810` with logger object `0x00474F70` and error text
   `0x0046E3EC`, then returns `-1`.
2. Reuse `[0x00491BF0]` as the player resource when present, clear that global,
   or select the character parameter record from the three-entry table rooted
   at `[0x00474C6C]`, call `0x00426520` with the caller-carried runtime in
   `ESI` and the selected record in `EAX`, and take the resulting player from
   `[EBX+0x45C]`. A failed load follows the retail error path.
3. Create update and draw callback records for `0x00426500` and `0x00426510`
   through `0x00449ED0`, attach them to the player, and register them through
   `0x00449AE0` and `0x00449B70` at priorities `0x10` and `0x16`. The
   scheduler calls are not ordinary C++ calls: the task is in `ESI`, the
   priority is in `EDI`, and the scheduler argument is stack-carried.
4. Initialize embedded animation/position state through `0x00404F30`, with
   `ESI = EBX+0x14`, `EAX = 0`, and the archive/resource value on the stack.
   That helper continues into `0x0043E710` and returns with `RET 4`.
5. Set the initial position/history values, convert the four player resource
   floats at offsets `0x10..0x1C` using scale `[0x00470B44]` and the retail
   x87 conversion helper `0x00463B2C`, copy the initial pair into 33 history
   records, and reset the timer at `EBX+0x460`.
6. Copy character parameters from the separate tables at
   `0x00476FB8`, `0x00476FB0`, and `0x00476FA0` into player offsets `+4`,
   `+0xC`, and `+8`; derive hitbox/half extents using `[0x00470B0C]`; build
   the four bounds at `+0x404`, `+0x4324`, `+0x433C`, and `+0x4354`; reset
   the remaining timers at `+0x474`, `+0x488`, and `+0x430C`; set `+0x4308`
   to 30; and finish through `0x00426F70` with the runtime on the stack.

## Exact dependency and ABI boundary

The bounded candidate reused these proven semantic or retail dependency
edges without changing their production ownership:

| Address | Role and required call shape |
| --- | --- |
| `0x00447280` | Exact cached-resource semantic dependency; `ECX=index`, `EDX=owner`, name stack-carried, callee `RET 4`. |
| `0x0044B810` | Exact logger semantic dependency; logger object in `ECX`, message stack-carried, custom caller cleanup. |
| `0x00449ED0` | Exact callback-record constructor; callback address stack-carried, `RET 4`. |
| `0x00449AE0`, `0x00449B70` | Exact scheduler dependencies; task `ESI`, priority `EDI`, scheduler pointer stack-carried, internal register ABI. |
| `0x00426520` | Retail parameter loader; runtime in `ESI`, selected parameter record in `EAX`, writes `[ESI+0x45C]`, returns status in `EAX`. |
| `0x00404F30` | Retail animation initializer; embedded position in `ESI`, zero in `EAX`, archive stack-carried, `RET 4`; calls `0x0043E710`. |
| `0x00463B2C` | Retail x87 float-to-integer conversion used four times. |
| `0x00426F70` | Retail final derived-state refresh with the runtime stack-carried. |

The target itself also publishes callback addresses `0x00426500` and
`0x00426510`; those remain retail assembly dependencies. Reproducing the
target therefore needs the caller's `EBX` contract together with the
scheduler's `ESI`/`EDI`/stack register ABI and the custom ABI of the animation,
parameter, and derived-state helpers. The candidate's ordinary member receiver
could express the state behavior, but it did not reproduce that entry ABI or
the compiler's retail instruction schedule.

## Focused probe evidence

A disposable native-LTCG cluster was placed at the declared fixed addresses.
The final compile/link succeeded, but strict validation rejected it before
promotion. Its map recorded:

```text
.text$00layout  0x00401000  0x237F0
.text$10init   0x004247F0  0x003FE   (?Initialize@PlayerRuntimeState_Utility@@QAEHXZ)
.text$20gap    0x00424BEE  0x00075
.text$30context 0x00424C70 0x0002A   (_PlayerRuntimeInitCompilerContext@8)
```

Thus the compiler emitted only 1,022 bytes for the target body, not the
required 1,435 bytes; the synthetic context landed at `0x00424C70` instead of
its declared `0x00424E00`. Direct comparison of the emitted target bytes with
the retail oracle found the first mismatch at the entry, `0x004247F0`:

```text
retail:  A1 68 4C 47 00 83 EC 0C 55 33 ED 3B C5 B8 2C E4 46 00 74 05 ...
native:  83 EC 50 8B 15 68 4C 47 00 53 33 DB 85 D2 8B 15 10 1C 49 00 ...
```

The first difference is the expected consequence of compiling an ordinary
member receiver (`ECX`) rather than preserving the caller's `EBX` state and
retail prologue. The shorter body and shifted context are independent hard
extent failures. This is ordinary semantic/compiler/ABI mismatch evidence,
not evidence that the game behavior is irreducible or that exact assembly is
required.

## Next dependency

The next bounded experiment should make the target's compiler-visible entry
context preserve `EBX` as the state receiver while keeping the three scheduler
calls as noinline internal-ABI callees. It must also retain the stack cleanup
and register setup at `0x00447280`, `0x00426520`, `0x00404F30`, and
`0x00426F70`. A subsequent candidate should be measured against the complete
`0x004247F0..0x00424D8A` body and its two discontiguous ranges before any
manifest or production-source change.

The disposable candidate, cluster manifest, context, probe outputs, and lab
were removed after the failed result.

## Final lane baseline

The focused production baseline was rerun at lane wrap against the current
oracle with `matching2/msvc/src/game/player_runtime_init.cpp` and the live
manifest. It passed exact comparison for `0x004247F0`, all 1,435 bytes, with
all recorded data and relative-call relocations resolving to their declared
retail targets. The result was `EXACT`; this confirms the production asm
fallback is intact after the failed semantic experiment. Its temporary output
directory was removed immediately after the probe.
