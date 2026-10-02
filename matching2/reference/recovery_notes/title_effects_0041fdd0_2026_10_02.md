# Title effects worker 0x0041FDD0 — complete native recovery

The complete 220-byte worker is readable C++ with no inline assembly. Its existing seven-byte scheduler callback at 0x0041FEF0 is also compiled with the worker and remains exact. No other recovered owner changes: the 95-byte positioned creator at 0x00448D50 stays in its existing cluster.

## Genuine topology and matching lever

The new schema-2 cluster has the real scheduler callback as its entry and the actual `0x0041FEF1` callback-to-worker CALL as its declared edge. The worker is rooted because retail's callback pushes the context as the sole stack argument and the worker returns with `RET 4`.

The second branch retains the address of the game-thread cached animation handle while creating script 6 at `{480.0f, 392.0f, 0.0f}`. Keeping a whole game-thread local instead produces a 219-byte body: the compiler retains that base in ESI rather than the cached field address. Accessing the cached field directly through the global, and using an ordinary inline `AsciiResource()` field getter, produces the retail EAX thread load, ESI field address, EAX resource load, and EDX copy of the returned handle. The getter adds no call or instructions. There is no volatile access, forced inlining/no-inlining beyond the existing selected/helper declarations, synthetic caller, fabricated parameter, byte patch, or operand rewrite.

The first branch allocates the signature animation, applies render bucket 15 and flag 0x40000000, initializes script 0, registers the handle, and increments readiness. The second branch fills the cached interface handle once and increments interface readiness. Every invocation increments the frame counter and returns 1.

## Unselected dependencies

The source includes the existing `layout/ltcg/animation_public_callers_anchors.cpp` unchanged. Its complete native contributions provide the genuine allocator, script loader, registrar, entity initializer, and positioned creator semantics and private LTCG ABIs. The empty discarded finder section imposes a one-byte alignment gap; the declared layout gap after the positioned creator starts at 0x00448DB0 to respect that native section origin.

Only worker and callback bytes are exported. The initializer (273 bytes), positioned creator (95 bytes), and allocator (161 bytes) are also independently exact in this visibility context. The existing script-loader model (207 bytes) and primary-registrar model (114 bytes) are complete unselected ABI dependencies, not exact recovered bodies; they receive no recovery credit.

## Evidence

Experiment directory: `matching2/build/experiments/title_pair_native_2026_10_02`.

Latest normal probe: `ready.json`. It passes both complete selected extents with zero differing or masked bytes. `complete_measurements.json` additionally compares each complete declared helper with the retail PE and records the distinction above.

Selected body SHA-256:

- Worker220: `5b9ae6a08ac91c207c6f27a758a463e5c88690f5b28e080a3d0ea0bd90df1621`
- Callback7: `dd2cd85cf6a28e8e8329d1d9066f07182abfd7c0c8cc76db846579ec6625b4ba`

Ready integration artifacts are in `landing/`. The root owns the region-manifest update and final incremental full-image verification.

## Integrated whole-executable gate

Root integrated the maintained ownership metadata and the incremental build
passed with zero failures, 1,606 unchanged units reused, four units compiled,
and 150 toolkit library members extracted. The complete 487,936-byte output
is byte-identical to retail, with zero masked bytes. Whole-executable SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Linked selected-body hashes and package evidence are recorded in
`matching2/build/experiments/faded_title_2026_10_02_verification.json`.
The full inline-assembly-removal goal remains incomplete.
