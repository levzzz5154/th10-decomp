# Item allocator callers: full bounded sweep recovery, 2026-09-28

Maintained integration is complete after independent review and exact normal probes. The sixth checkpoint matches all 487,936 retail executable bytes using all 3,964 current project inputs. Five existing Ghidra Function annotations were saved and read back. Proof: `matching2/build/experiments/native_recoveries_2026-09-28_sixth_verified.json` and `native_recoveries_2026-09-28_sixth_ghidra_verified.json`.

This isolated continuation recovered the entire original **0041F400..0041F66E,
623-byte** bounded line destruction sweep as ordinary C++, with the original
source owner `src/game/fun_0041f400_0041f400.cpp`. Maintained inputs were not
changed by this experiment. The full allocator and the other real caller remain
unpromoted.

The canonical experiment is
`matching2/build/experiments/item_spawn_callers_2026_09_28`. The prior
`item_spawn_0041bb00_2026_09_28` experiment was preserved; its 827-byte allocator
inputs were hash-revalidated before the new scratch copy. Fresh Ghidra th10.exe
was confirmed at socket `/run/user/1000/ghidra-mcp/ghidra-2136235.sock`; fresh
allocator/sweep decompositions and polar disassemblies are retained in the new
experiment. No Ghidra program mutations were used.

## Exact normal result and handoff

`independent_f400/probe04.json` is the ordinary native probe's **EXACT** result
for the original full623-byte region. `independent_f400/f400_proposal.json`
preserves its source, address, size and owner. The report records zero
instruction-byte changes, zero address-operand changes, zero masked bytes and
`reference_bytes_used_for_build=false`. This is a normal selected contribution
result, beyond the prior joint raw-section diagnostic.

Body SHA256:
`f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f`.
Source SHA256:
`ba6539f059baeed0c25d4536b338ad9caedf80ac3601591db3a5aa1fb0c48979`.
Normalized object SHA256:
`0935bccb2b87c5b39abb5bbd3947e6ae829c6f130cf87f107eca297eef1ea724`.

`f400_handoff/inputs/` freezes the **11 explicit input files** and
`f400_handoff/handoff.json` records their hashes, the required unchanged shared
headers, all actual unselected extents, the proposal, native report and exact
body hashes. Parent integration must copy only those explicit files and register
`layout/ltcg/item_line_bounded_0041f400_2026_09_28.json`. It must not overwrite the
manifest or the maintained allocator / all-segment source files. Their complete
ordinary models live under unique `layout/ltcg/item_spawn_caller_*` paths in the
handoff. Parent independent review, the maintained normal probe, and whole-executable validation subsequently passed.

## Behavior and concrete source levers

The complete routine visits every segment, returns an integer count including
out-of-bounds segments, tests its outer16-unit rectangle, allocates/configures/
loads/registers each eligible animation, optionally spawns kind8 within the
inner32-unit rectangle, advances all three position coordinates and its distance,
and sets retired on both empty and completed paths. Its negated bounds retain
the observed x87 unordered behavior; the initial/continuation length tests reject
unordered values.

Separating the distance declaration from its assignment keeps the original stack
layout while scheduling count0 before distance6. A `float*` view of the actual
animation position subrecord yields retail bucket/Z/X/Y store scheduling without
removing operations. The step Z is retained as a volatile float because the real
loop explicitly performs a floating add of zero; replacing that with no operation
can change signed-zero behavior. A local volatile reference to point Z preserves
both floating reads and the retail FLDpoint/FADDstep order. No assembly, register
stub, shortened helper, byte rewrite or instruction mask is present in the
handed-off C++ inputs.

The line polar helper is a complete ordinary cos/sin C++ body. Its published
member pointer keeps public ECX receiver, EAX destination return and preserves
EDX in the emitted30-byte context. It emits FCOS/FSIN; it is **ABI context only**,
not an exact recovery of the retail FSINCOS leaf or proof of identical rounding.
The actual item polar setter is separately declared opaque with its genuine
public ECX/stack8 contract and direct address binding. This conservative callee
contract permits the allocator's retail EAX manager / ECX position / kind-id-
angle-speed stack / RET16 call agreement. Publishing both full polar bodies had
instead promoted kind into EDX and RET12; retained attempts07/08 document that
concrete failed closure.

## Complete remaining residuals

The original joint three-function layout still requires all819/609/623 bytes.
`attempt15.json` honestly fails that normal gate because the allocator emits823
instead of819. `attempt15_measurement.json` reads each complete emitted native
CODE contribution; these diagnostics do not override the normal joint gate:

| Original | Complete native | Overlap differences | First difference |
|---|---:|---:|---|
| 0041BB00 allocator819 | 823 | 774 | 0041BB02 |
| 0041E260 all segments609 | 601 | 303 | 0041E2E7 |
| 0041F400 bounded623 | 623 | 0 | none |

The independent F400 layout declares the full actual unselected allocator823,
all-segment601, Configure204, loader203, registrar114, positioned-create111,
Allocate165 and line polar30 contributions, plus genuine compiler context56.
These extents and addresses are validated by the normal native gate. None is
claimed exact merely because F400 is exact.

The new allocator lever is the established manager/position/stack call agreement.
Its remaining source levers are allocation-search loop form and kind/remapping
liveness. For E260, the first303 residual bytes follow a common exact prefix; the
inline next-handle update is8 bytes shorter than retail and needs the genuine
increment/return value lifetime rather than an increment-in-memory fold. The
position subrecord lever from F400 is also concrete context for E260's field
schedule. Full original contributions remain required for their recovery.
