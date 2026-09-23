# Recovery emitter decision candidate at `0x0040B9F0`

`matching2/msvc/src/game/recovery_update_emitter_decision_0040b9f0.cpp` now
contains an ordinary C++ semantic model of the 111-byte retail region
`0x0040B9F0..0x0040BA5E`. The model is not an integrated ABI replacement:
`regions.json` remains unchanged, with this region still classified as `asm`.
No build or byte comparison was run for this candidate.

## Behavior

Retail reads the receiver from EDI. Its field at `+0x18` points to the tick
state; the routine calls `TickRecoveryState_0040bd20` with that pointer in ESI.
If the tick reports completion, it writes `0x00491FB8` and returns 1. The
write is 2 when `data_00491FF4 & 0x1000` is nonzero, and 15 otherwise. This is
the result of retail's `and`/`neg`/`sbb`/`and`/`add` sequence.

When the tick is still active, the routine increments the signed 32-bit
counter at receiver offset `+0x24`, then reads the tick state's flags at
`+0x74`. It returns 6 only when all of these conditions hold:

* bit 2 (`0x04`) of the tick-state flags is clear;
* bit 1 (`0x02`) of the receiver byte at `+0x20` is clear;
* bit 1 (`0x02`) of the tick-state flags is set;
* `data_00474E30 & 0x100` is nonzero; and
* the incremented signed counter is divisible by 12.

All other active-tick cases return 1. The only writes in the body are the
counter increment and, on the completed-tick path, the `0x00491FB8` update.
The source spells the increment's 32-bit wrap explicitly so it does not rely
on C++ signed-overflow behavior before the signed modulo check.

## Retail ABI evidence

Ghidra identifies no stack parameters and an unresolved 32-bit return value.
The instructions set EAX to 1 or 6 on the two active paths and to 1 on the
completed-tick path. The wrapper at `0x0040BA70` moves its ECX input to EDI,
calls `0x0040B9F0` at `0x0040BA73`, restores EDI, and leaves EAX untouched.
Thus the machine-level contract is a private EDI receiver, no stack-passed
receiver, and an integer result in EAX. The function saves/restores ESI and
does not modify EDI.

The tick call at `0x0040B9F4` receives `[EDI+0x18]` in ESI, with no stack
argument. The already semantic `TickRecoveryState_0040bd20` source has an
ordinary `__stdcall` pointer parameter; the C++ call in this candidate uses
that source-level signature and therefore does not reproduce the retail ESI
handoff by itself.

## Ordinary-C++ model and remaining work

The model gives the private receiver an explicit pointer parameter and returns
`int`. That expresses the behavior but does not implement the retail EDI
entry. The C symbol retains the old linker name, while other code still sees
the no-argument declaration from `asm_symbols.hpp` and the raw wrapper still
calls without pushing a receiver. The source-level signatures therefore do
not yet form a safe runtime cutover. A caller-context/LTCG solution or another
ABI plan is needed before changing the manifest record from `asm`.

The exact register and stack schedule of ordinary C++ output is unresolved;
this note makes no byte-equivalence claim. The previous `recovery_tick_state`
note documents the ESI live-in at `0x0040BD20` and names this function as its
retail caller.
