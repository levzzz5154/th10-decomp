# Recovery emitter decision and scheduler callback

The scheduler callback at `0x0040BA70` is now recovered as ordinary C++ and
matches all 10 retail bytes. The tick helper at `0x0040BD20` remains exact C++
and matches all 93 bytes. The adjacent 111-byte decision routine at
`0x0040B9F0` remains inline assembly: its readable C++ model is used only as a
compiler context anchor because its native output still differs from retail.

## Recovered behavior and interfaces

The decision routine receives its emitter in EDI, reads the tick-state pointer
at `this + 0x18`, and calls the tick helper with the tick state in ESI. If the
tick reports completion, it writes 2 to `0x00491FB8` when
`0x00491FF4 & 0x1000` is set, or 15 otherwise, then returns 1. Otherwise it
increments the signed counter at `this + 0x24` with 32-bit wrapping. It returns
6 when the eligibility flags pass and the new counter has a nonzero remainder
modulo 12; multiples of 12 and ineligible paths return 1.

The callback at `0x0040BA70` is the address-stable scheduler entry. It receives
the callback context in ECX, preserves EDI, moves the context to EDI for the
decision routine, and returns its EAX result. `FUN_0040B560` stores `0x0040BA70`
in the callback slot at node `+0x08`, stores the emitter at `+0x20`, and
registers the node. The C++ callback models this as
`RecoveryUpdateEmitterState_0040b9f0::RunDecisionCallback()`.

## Native LTCG and exact verification

[`recovery_tick_state_0040bd20.json`](../../msvc/layout/ltcg/recovery_tick_state_0040bd20.json)
builds the exact tick helper and callback together. The decision model in
[`recovery_emitter_decision_anchor_0040b9f0.cpp`](../../msvc/layout/ltcg/recovery_emitter_decision_anchor_0040b9f0.cpp)
is an ABI anchor at the retail decision address; the layout validates its
address and complete contribution but does not export it as recovered code.
The synthetic tick-array caller is compiler context only.

The focused probe reports zero differing bytes and no relocations for the
callback. Its body SHA-256 is
`8ef2d2ab1293f1b8b5ab8631bc92c74414d1648c0a8920f5bc7f93aea11c4115`. The tick
body remains exact with SHA-256
`d1bc1c78e012303753f162d91e806e04cf6cca533efa529e99ab054dc96c7892`.
The probe is retained under
`matching2/build/probe_emitter_callback_exact_20260930`.

The separate decision-body probe measured 48 differing bytes in the 111-byte
C++ candidate, with its first mismatch in the counter-load/register allocation.
That candidate is not selected in the production build; the existing assembly
region remains authoritative while it serves as compiler context for the
callback ABI.

The full build compiled 1,944 maintained C++ translation units and reproduced
the exact 487,936-byte executable with SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
