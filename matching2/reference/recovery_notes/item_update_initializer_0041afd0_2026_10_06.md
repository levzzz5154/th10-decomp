# Complete entity initialization in the item graph, 2026-10-06

This is the historical 2,436-byte initializer checkpoint, preserved under
`evidence/initializer_graph/`. The [motion follow-up](item_update_motion_0041afd0_2026_10_06.md)
records the current 2,232-byte typed motion graph and fresh proofs.

The maintained item graph now includes the complete 273-byte entity initializer
and passes **473 bounded retail/native comparisons**. Its three selected existing
recoveries—conversion, power-add and life-add—still match all **472 bytes** in
the normal raw fixed-address gate. An independent gate also proves the complete
161-byte allocator under this graph. Production retains the allocator's existing
genuine player-initialization owner. New recovered bytes: **zero**.

## Genuine initializer and constructor controls

The initializer retains the render bucket and position across the entity clear,
then restores its identity transform, colors, frame state and intrinsic list
nodes. Its definition and calls use the actual single entity argument. The
existing shared two-argument declaration is unused in this graph; the shared
header is unchanged. LTCG chooses the private EDX convention from the visible
body, without an artificial live parameter or prescribed register.

| Complete source control | Allocator bytes | Result |
| --- | --- | --- |
| Constructor visible, initializer opaque | 165 / 161 | Unselected |
| Constructor and initializer visible | 161 / 161 | One unequal byte: constructor argument EDX versus retail ECX |
| Initializer visible, constructor external | 161 / 161 | Complete diagnostic and fixed-address equality |
| Single-argument initializer, constructor external | 161 / 161 | Same equality; maintained source |

Making the initializer visible removes the two extra ECX-zeroing instructions
at its calls. Making the constructor visible changes its private convention and
produces an 86-byte constructor instead of retail's 88 bytes. These constructor
controls remain unselected. Their full sources, two native link bases, maps and
comparisons are preserved in `evidence/initializer_controls/`.

The graph has 32 complete contributions, of which 20 have diagnostic equality.
The larger graph changes other unselected contributions:

| Function | Native / retail bytes | Unequal overlapping bytes |
| --- | --- | --- |
| Complete item update | 2,436 / 2,320 | 2,211 |
| Item spawn | 823 / 819 | 425 |
| Script-start helper | 200 / 202 | 177 |
| Script loader | 197 / 203 | 165 |
| Entity initializer | 273 / 273 | 0 |
| Pool allocator | 161 / 161 | 0 |

Update and spawn remain assembly-owned. Both complete switch tables are included
in every comparison; no source, contribution or comparison is truncated. The
previous 2,428-byte update and 819-byte/two-difference spawn graph is preserved
independently in `evidence/collaborator_graph/`.

## Execution evidence

The previous 405 cases remain. Forty-eight added cases cover free slots, one
occupied slot, two occupied slots requiring heap allocation, cursor 4095 wrapping
to zero, and primary/secondary/existing-child banner lists for both power and life
collection. Twenty added cases execute delayed item scripts with valid script
slots or a loading resource. Entry traces establish **38 cases executing the
initializer** and **16 heap-fallback/constructor cases**; explicit assertions
check the expected initializer and allocation counts in the new cases.

The fixture maps a separate heap block, initially filled with `0xA5`, and includes
all heap and animation-manager memory in the comparisons. It executes the actual
constructor at its retail address in both runs and the complete native initializer
in the native run. Successful `operator new`, animation VM callbacks, player
power-change and terminal conversion are shared scripted boundaries. Allocation
failure and complete game integration are not established by these comparisons.
The existing x87 control-word and binary32 rounding cases remain covered.

## Production validation

The complete initializer joins
[`item_collection_genuine_0041afd0.cpp`](../../msvc/src/game/item_collection_genuine_0041afd0.cpp)
as ordinary C++; its driver still only includes the genuine source graph. The
layout retains exactly the same three selected functions and every manifest
owner. The allocator and initializer are complete unselected anchors in this
production cluster. The optional `--allocator` gate uses a separate isolated
project and selects the allocator as a fourth function for an independent raw
proof. Neither gate changes the matching tools or uses reference code to build.

`make` and `make EXACT=1` pass. Exact mode remains identical to the 487,936-byte
oracle, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The fresh audit verifies 963 native layouts, 1,483 selected functions and 3,986
current unique compiler inputs. Counts remain 2,254 ordinary C++ regions /
199,062 bytes and **60 actual assembly regions / 89,245 bytes**. Patches, masks
and new recovered-byte credit remain zero. The full goal remains active.

Current commands and hashed evidence are in
[`item_update_0041afd0/`](../semantic_candidates/item_update_0041afd0/).
