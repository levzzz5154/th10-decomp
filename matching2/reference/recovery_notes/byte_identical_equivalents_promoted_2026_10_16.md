# Byte-identical equivalent models promoted to exact (2026-10-16)

Three equivalent recoveries recorded zero differences. Comparing the linked
model bytes with retail (not just the checker's instruction verdict, which
also accepts branch-target copies) showed two of them, and 0x0042E5A0 after
its last fix, identical in every byte. Each now has an LTCG cluster and its
assembly region and equivalent layout are removed. `make EXACT=1` is
unchanged; byte-exact rose from 74.0% to 74.6%.

| Region | Bytes | Cluster | Context |
| --- | ---: | --- | --- |
| 0x00437750 font atlas blend | 645 | `font_atlas_blend.json` | the rig's array-walking caller, moved from the source into the driver |
| 0x00439890 Direct3D initialize | 1,159 | `d3d_initialize.json` | rooted; TextLog Append/AppendLine (0x0044B810/0x0044B8E0) as `code_seg`-macro anchors; the `__real@` double binding becomes a data alias, the float a constant alias |

Still byte-identical but not promoted: 0x00438AD0 GameMain (1,389 bytes). Its
rig compiles fifteen callee sources, four of them with `/EHsc` and bound
`__ehhandler` funclets, which needs the exception-cluster machinery
(`ordinary_sources`) rather than plain anchors.

Not byte-identical despite zero recorded differences: 0x0042A3E0 replay
frame step (4 bytes, branch to another `ret` copy) and 0x00433570 replay save
update (2 bytes).

Recipe: one function entry (rooted when the rig rooted it), each context
source as an anchor through a one-line `#define code_seg(name)` wrapper at its
retail address, gaps computed from the placed items, `bindings` turned into
`relative_code` absolute symbols (or `__real@` constant/data aliases), and the
`headers` list filled from the probe's "undeclared source/header" errors one
at a time. The rig's entry caller moves from the source into the driver.
