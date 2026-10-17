# Familiar refresh 0x00426F70: byte-exact (2026-10-17)

Follows `familiar_refresh_00426f70_accepted_2026_10_14.md`. The last recorded
`evaluation-order` hunk is gone: the 2,520-byte refresh is selected by the
LTCG cluster `msvc/build_support/layout/ltcg/familiar_refresh_00426f70.json`
from `src/game/player/familiar_refresh.cpp`, and the assembly region and the
equivalent layout are removed.

## The last residual (643 -> 643 of 643)

At 0x4272D7 (third shot-type column, rebuild of an idle familiar) retail
loads `anchor.x` before `carried.x` and the model loaded them the other way
round, with the y pair already matching. The four loads are scheduled as one
group; the x pair's operand order is the commutative hash tie-break and the y
pair's two address temps tie, so only the x pair moves with the temporary
parity (`msvc-c2-operand-order-mechanism`).

The lever that lands retail's parity: one value-returning inline accessor at
the scaled-row position, per `msvc-c2-temp-register-rotation-named-local`:

```cpp
static __forceinline const FamiliarOffsetTable* Rows(
        PlayerFamiliarRuntime* player) { return player->offsets; }
...
ScaleOffset(&player->familiars[i].carried,
            &Rows(player)->carried[data_00476f7c[desired] + i]);
```

The accessor result is one more expression temporary before the add, which
rotates the x pair's loads into retail's order and leaves the tied y pair
alone. Everything else tried first left the model unchanged or worse:
statement order (the position store before the scale, which breaks the store
order), named value locals at the scale statement and at the add, a named
anchor local, splitting the reused `record` sweep local, pointer-local
removal, and accessor temps far from the statement (they fold away).

## Promotion

The cluster keeps the accepted model's context: the five recovered
schedule/animation callee bodies as anchors at their retail addresses (the
`familiar_refresh_dependencies` sources, with `entity_init.cpp` taken from the
local copy whose section name sorts with the layout), the rig bindings as
absolute symbols, and `FamiliarRefreshEscape` as the compiler-context entry —
its address-taken `g_globals_score` is what keeps the character/shot-type
stores ahead of their reloads, so it moved from the source into the driver as
the link entry. All 2,520 bytes are exact; `make EXACT=1` is unchanged.
