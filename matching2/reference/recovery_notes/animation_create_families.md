# Animation-manager create families — 1,404 bytes in sixteen regular regions

2026-09-18. A shape screen over the remaining game-code assembly (normalised
instruction text, families of two or more) found four *regular* families in the
animation manager, all still assembly:

| family | members | bytes each | shared callees | differing call |
| --- | --- | ---: | --- | --- |
| A | `0x00409E50`, `0x0040C480`, `0x0040C4D0`, `0x004243F0` | 65 | `AnimationManager_Find_004491C0` | none |
| B | `0x00448D00`, `0x00448E30`, `0x00448F60`, `0x00449090` | 73 | `FUN_00449950`, `FUN_00449870` | `RegisterPrimaryBack_004489D0` / `…PrimaryFront_00448A50` / `…SecondaryBack_00448AC0` / `…SecondaryFront_00448B40` |
| C | `0x00448D50`, `0x00448E80`, `0x00448FB0`, `0x004490E0` | 95 | `FUN_00449950`, `AnimationObject_LoadScript_0043E710` | the same four register calls |
| D | `0x00448DB0`, `0x00448EE0`, `0x00449010`, `0x00449140` | 118 | `FUN_00449950`, `AnimationObject_LoadScript_0043E710` | the same four register calls |

**1,404 bytes across sixteen regions**, and inside each family the four members
have *identical* normalised instruction text — the only difference is which
register helper the tail calls. One source shape per family, instantiated four
times with a different final call, therefore recovers a whole family at once.

## Why these need the cluster path

Every callee is assembly with a non-standard convention (`FUN_00449950`,
`FUN_00449870`, the four `Register*` helpers, `LoadScript`), so the call sites
carry registers no plain translation unit can set up; the registry
(`animation_manager_cluster_0043e460_00449950.md`) already records that region's
convention work. With the cluster machinery the shape is attractive because the
four instantiations differ by exactly one bound call target, so a single
validated model should land each family as a batch — the approach the recent
`copy_block`, `destroy_owned` and accessor batches used.

Family A is the cheapest entry point: 65 bytes, one callee, no variants — the
body reads `[eax]`, then `data_00491C10`, pushes the object, calls
`AnimationManager_Find_004491C0`, tests the result, and tails into the usual
`test eax,eax` shape.
