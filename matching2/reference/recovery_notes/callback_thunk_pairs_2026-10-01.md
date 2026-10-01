# Scheduler callback thunks recovered with their callees (2026-10-01)

The small `mov reg,ecx` adapters in front of private-register routines are
ordinary `__fastcall` callbacks whose only statement calls a member function.
Compiled in one native `/LTCG` link with the callee, and with their address
published by a context function the way the real initializers do, they come
out byte-exact together with the callee's private receiver register:

| callback | callee | receiver | source |
|---|---|---|---|
| `0x00403050` (`mov eax,ecx; jmp`) | `0x00402720` stage update | EAX | `src/game/stage_state_update_00402720.cpp` |
| `0x0040D810` (`push edi; mov edi,ecx; call`) | `0x0040D750` enemy sweep | EDI | `src/game/enemy_timer_sweep_retail_0040d750.cpp` |

`tools/waves/adopt_cluster.py` writes the layout (gaps computed from the
placed functions) and converts the regions from a short spec.

Two source details were needed. The stage update publishes its camera with
`memcpy`, which makes the frame counter reload after the copy. The enemy
sweep's timer reads its speed through an inline accessor and adds the elapsed
time to it (`elapsed = Speed() + elapsed`); that is the only spelling found
that loads the speed first on the slow path.

## Open: `0x00427950` -> `0x00427960` (ESI receiver)

The same recipe reproduces the thunk and the loop of the 359-byte routine.
The source shape is: copy the trail head into `position`; when not dragging
set `offset = position - cursor`, otherwise set the head to `cursor + offset`
and interpolate the seven trail points in eighths; then
`position = offset + cursor` on both paths. The remaining difference is that
retail recomputes the head address for the drag-path store, where every
spelling tried so far reuses the first address and so allocates registers
differently. Passing the two sums by value to an inline setter gives retail's
load order (`offset.y`, `cursor.y`, `offset.x`, `cursor.x`) but not the
recomputed address.
