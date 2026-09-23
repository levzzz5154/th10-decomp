# Recovery emitter callback and tick path: `0x0040B9F0` / `0x0040BA70` / `0x0040BD20`

The emitter decision at `0x0040B9F0`, its registered callback entry at
`0x0040BA70`, and its tick helper at `0x0040BD20` are modeled as ordinary C++
member methods. The sources share the object layouts in
`matching2/msvc/include/th10/game/recovery_emitter_state.hpp`:

* `RecoveryUpdateEmitterState_0040b9f0::RunDecisionCallback()` is the
  scheduler-facing callback method.
* `RecoveryUpdateEmitterState_0040b9f0::UpdateEmitterDecision()` contains the
  emitter decision logic.
* `RecoveryTickState_0040bd20::Tick()` contains the tick-state update.

Each call uses a typed C++ member receiver. The source path no longer relies
on the private EDI receiver for the decision or the private ESI receiver for
the tick. This is a semantic calling-convention change; no byte-equivalence
claim is made for the changed tick method signature.

## Behavior recovered from Ghidra

`0x0040B9F0` reads the emitter's tick state from `this + 0x18` and ticks it.
When the tick reports completion, it writes 2 to `0x00491FB8` if
`0x00491FF4 & 0x1000` is set, or 15 otherwise, then returns 1. When the tick is
still active, it increments the signed counter at `this + 0x24`. It returns 6
only when tick-state flag bit 2 is clear, emitter flag bit 1 is clear, tick
state flag bit 1 is set, `0x00474E30 & 0x100` is set, and the new counter is
divisible by 12. Other paths return 1.

The model spells the counter increment as unsigned wrap followed by a defined
signed conversion, retaining x86's 32-bit increment without relying on signed
overflow in C++.

`0x0040BD20` updates the `FrameTimer` at the beginning of the tick-state
object. It first calls the script-finished query at `0x0040BD80`. If the query
returns nonzero, the tick returns 1. Otherwise it copies `current` to
`previous`; at normal speed it advances `current` and `elapsed` by one frame,
and at other speeds it accumulates the speed and converts elapsed time to the
current frame. The running path returns 0.

## Callback and private-call evidence

Ghidra shows a single code xref to `0x0040B9F0`, the call at `0x0040BA73`.
Retail receives the decision receiver in EDI, with no stack argument, returns
1 or 6 in EAX, and preserves EDI. The wrapper at `0x0040BA70` receives its
callback context in ECX, moves that value to EDI, calls the decision body,
restores EDI, and returns the EAX result.

`FUN_0040B560` stores the absolute address `0x0040BA70` in the update callback
slot at node `+0x08`, stores the emitter pointer in the context slot at
`+0x20`, then registers the node. Thus `0x0040BA70` is the address-stable
scheduler entry and must retain the callback's ECX receiver and EAX result.
The callback path now expresses that boundary as a C++ member function and
uses a normal member call into `UpdateEmitterDecision()`.

The scheduler's callback address is a numeric constant in the registration
code, rather than a C++ address-of expression visible to this LTCG cluster.
The synthetic context calls `RunDecisionCallback()` directly, so it does not
prove the compiler will retain ECX as the entry receiver for the external
callback. The integrated output must be checked for ECX input, EAX result, a
plain return, and preservation of EDI. If LTCG specializes the callback entry
for its synthetic caller, add a C++ address-taking/indirect-call anchor that
preserves the callback ABI, or keep an explicit ABI boundary at `0x0040BA70`.

Retail `0x0040B9F0` loads the tick-state pointer from `[EDI+0x18]` into ESI and
calls `0x0040BD20`; Ghidra lists B9F0 as BD20's only code caller. The earlier
native-LTCG experiment compiled the global `TickRecoveryState_0040bd20` source
with that ESI live-in and matched all 93 retail bytes. This cutover changes
that global function to `RecoveryTickState_0040bd20::Tick()`, called through a
typed member receiver. Its decorated symbol is therefore now
`?Tick@RecoveryTickState_0040bd20@@QAEHXZ`; the old exact result and old
decorated symbol describe the previous source signature only.

## Manifest and cluster mapping

The source interfaces now require these symbols at the same retail entries:

| Address | C++ method | Decorated symbol |
| --- | --- | --- |
| `0x0040B9F0` | `RecoveryUpdateEmitterState_0040b9f0::UpdateEmitterDecision()` | `?UpdateEmitterDecision@RecoveryUpdateEmitterState_0040b9f0@@QAEHXZ` |
| `0x0040BA70` | `RecoveryUpdateEmitterState_0040b9f0::RunDecisionCallback()` | `?RunDecisionCallback@RecoveryUpdateEmitterState_0040b9f0@@QAEHXZ` |
| `0x0040BD20` | `RecoveryTickState_0040bd20::Tick()` | `?Tick@RecoveryTickState_0040bd20@@QAEHXZ` |

The `0x0040BD20` manifest row and LTCG function record now use the member symbol
`?Tick@RecoveryTickState_0040bd20@@QAEHXZ`. The old global-function spelling is
historical and does not describe the current source. Keep the callback route
and synthetic walker in one LTCG cluster so all three function entries retain
their assigned addresses. The callback entry must continue to accept the
emitter through ECX at runtime.

The source edit, shared header, manifest row, and LTCG symbol record were
inspected statically. No build, probe, or test was run; actual compiler register
assignments, address placement, and byte equality remain unverified. In
particular, the numeric callback registration does not itself make BA70's
address visible to the synthetic compiler context, so its ECX/EAX boundary
still needs verification in an allowed recheck.
