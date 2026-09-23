# Recovery emitter update callback: `0x0040B9F0` and `0x0040BA70`

The 111-byte emitter decision routine at `0x0040B9F0` and its 10-byte callback
entry at `0x0040BA70` now have ordinary C++ member-function models. Both
manifest rows are semantic. The implementation shares the emitter and tick
state layouts in `include/th10/game/recovery_emitter_state.hpp` and co-compiles
the two methods with the existing `0x0040BD20` tick body.

## Behavior recovered from Ghidra

`0x0040B9F0` reads the emitter's tick state from `this + 0x18` and ticks it.
When the tick reports completion, it writes 2 to `0x00491FB8` if
`0x00491FF4 & 0x1000` is set, or 15 otherwise, then returns 1. When the tick is
still active, it increments the signed counter at `this + 0x24`. It returns 6
only when tick-state flag bit 2 is clear, emitter flag bit 1 is clear, tick
state flag bit 1 is set, `0x00474E30 & 0x100` is set, and the new counter is
divisible by 12. Other paths return 1.

The C++ model spells the counter increment as unsigned wrap followed by a
defined signed conversion, avoiding C++ signed-overflow behavior while
retaining x86's 32-bit increment result.

## Callback and private-call evidence

The decision routine has one Ghidra code xref: the call at `0x0040BA73`. Its
receiver enters in EDI, with no stack argument; it returns 1 or 6 in EAX and
leaves EDI unchanged. The wrapper at `0x0040BA70` receives the callback context
in ECX, saves EDI, moves ECX to EDI, calls `0x0040B9F0`, restores EDI, and
returns the EAX result.

`FUN_0040B560` stores `0x0040BA70` in the update callback slot at node `+0x08`
and the emitter pointer in the context slot at `+0x20`, then registers the
node. This confirms that `0x0040BA70` is the stable scheduler-facing entry.
The wrapper and decision helper now use methods on
`RecoveryUpdateEmitterState_0040b9f0`; their former private EDI edge becomes a
normal C++ call. `0x0040BD20` remains semantic and is included in the same
native-LTCG cluster so the tick implementation and its new caller are visible
together.

The decision candidate calls `TickRecoveryState_0040bd20` through its typed
C++ prototype. The original optimized tick function's ESI receiver is a
private register choice. The merged cluster has not been rebuilt, so the new
internal call registers and emitted byte layout remain unverified. The
scheduler-facing callback receiver and return value are grounded in the
registered callback address and live Ghidra disassembly.

## Source files and verification limits

The source models are:

* `src/game/recovery_update_emitter_decision_0040b9f0.cpp`
* `src/unidentified/FUN_0040ba70_0040ba70.cpp`
* `src/game/recovery_tick_state_0040bd20.cpp`

The old naked bodies for `0x0040B9F0` and `0x0040BD20` were removed from
`src/game/recovery_leaves.cpp`. The existing
`layout/ltcg/recovery_tick_state_0040bd20.json` now roots the callback route
and reserves the original addresses as separate regions. No build, probe, or
test was run for this merged layout; this note makes no byte-exactness claim.
