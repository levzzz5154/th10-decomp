# C++ recovery checkpoint, 2026-09-28, sixth checkpoint

**Whole-executable and all current-input hash gates passed.** Five complete
routines totaling **1,137 bytes** are integrated as readable C++ without inline
assembly. Every maintained normal probe and independent source/ownership review
passed. Across all six checkpoints, cumulative recovery is **52 routines /
12,848 bytes**. The full assembly-free decompilation goal remains active.

| Entry | Bytes | Recovered operation | Detail |
| --- | ---: | --- | --- |
| 0x0041F400 | 623 | Destroy line segments within bounds and optionally spawn items | [Recovery note](item_spawn_callers_f400_exact_2026-09-28.md) |
| 0x00424D90 | 273 | Reset pause state and three timers, remove animation and update active count | [Recovery note](pause_reset_00424d90_native_2026-09-28.md) |
| 0x0042AB20 | 93 | Unlink and free all replay pools for one stage | [Recovery note](replay_pool_release_0042ab20_native_2026-09-28.md) |
| 0x0042C6D0 | 83 | Set object/child stop frames and clear the animation slot | [Recovery note](recovery_script_executor_callers_and_slot_frames_2026-09-28.md) |
| 0x0042C770 | 65 | Set object/child frames while preserving the animation slot | [Recovery note](recovery_script_executor_callers_and_slot_frames_2026-09-28.md) |

All five routines compile through four native-LTCG units. The slot pair shares
one new source and cluster, preserving each original complete owner record under
`previous_record`. Its merger reduces the registered total to **2,365 translation
units** and the maintained build to **2,241 units**. Four new clusters since the
fifth checkpoint bring the total to **690**. Unselected dependency models, layout
gaps, compiler contexts and ABI corrections add no recovered bytes.

Pause reset reproduces owner ESI, no stack owner argument at the actual private
entry, saved EDI, and a tail jump to active count with plain RET. It retains state
1, all three lazy timer-default writes, the first timer's previous/current/elapsed
reset to -2/-1/-1.0, the other resets to -1/zero/zero, animation marking and both
handle-zero stores. A plain state-field view and instruction-free compiler
barriers retain retail scheduling. Its full genuine 77-byte active-count model
is independently exact and remains unselected; the 41-byte array context also
remains unselected. The marking helper's public fastcall contract has ignored
ECX, context EDX, stack ID and RET4, supported by fresh lookup/caller evidence.

The bounded line sweep takes owner ECX and a stack flag with RET4. It preserves
all segment visits, bounds and unordered comparisons, optional kind-8 item
spawns, all position/distance increments, count and retirement stores. Separate
distance declaration/assignment and an ordinary position float view give retail
store order. The volatile Z views retain the observed floating add of zero and
both reads, including signed-zero behavior. Its complete unselected allocator,
other line caller and line polar model retain actual emitted extents. The line
polar model emits FCOS/FSIN and serves ABI context; it is not a recovered retail
FSINCOS leaf or proof of identical trigonometric rounding. The item polar setter
uses its authentic opaque public ECX/two-stack-float contract.

Replay release reproduces stage EAX, lists ECX and plain RET. It saves the next
node, preserves null-pool handling, updates both neighbor links, clears released
links, frees each pool through genuine cdecl free and follows the saved next
pointer. The complete layout retains the 0x6284-byte pool and embedded +0x6278
link. Its 18-byte synthetic forwarding context is unselected; it contains no
shortened private dependency or assembly surrogate.

ClearAnimationSlot looks up the stored handle, sets stop frame 1 on the object
and conditionally every child, then clears the slot even on a null lookup.
SetSlotFrame performs the same conditional frame updates with an unsigned
16-bit supplied value while preserving the slot. Native Clear uses EDI/ESI;
SetFrame uses EAX/ECX/SI. Their full 73-byte Find model independently matches,
but remains unselected. The complete executor, text/music callers, genuine
helper graphs and 50-byte synthetic context remain unselected. All 28 explicit
copy-file hashes and 37 native-input hashes match the final pair proof.

The complete **487,936-byte executable equals the stable retail oracle byte for
byte**. All **2,241 build units** completed without failure. Executable SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The `.text` SHA-256 remains
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.

The manifest and all-input gates passed for **3,964 current files**, including
the full added/deleted set. Only the five intended regions changed from the
fifth checkpoint; all original previous records remain intact. All 46 promotion
file hashes match, and the four selected native units use zero masks, instruction
changes, address-operand changes or oracle-built instructions. Independent reviews
found no material source, ABI, semantic, ownership or artifact issues. All five
existing Ghidra Function heads received saved/read-back plate annotations; no
Function objects were invented.

The earlier **273-byte sixth stage-one proof** remains historical and separately
rerunnable from `_stage1_project/`, `_stage1_audit.py` and its report snapshot.
It covered all 3,923 then-current inputs, 687 clusters and 2,242 build units before
the four later routines were integrated. Earlier checkpoints are preserved too.

Verified raw manifest totals are **1,659 semantic regions / 83,181 bytes** and
**1,119 assembly regions / 305,917 bytes**. Six partial semantic regions still
contain **4,525 bytes**: two 1,111-byte sprite submissions at 0x00442670/0x00442AD0
retain FRNDINT; two 591-byte rotated builders at 0x004436C0/0x00443910 and the
1,047-byte projection builder at 0x00443B60 retain FSINCOS; callback creation at
0x00449ED0 retains 74 bytes of register assembly. Thus there are **1,653 fully
C++ semantic regions / 78,656 bytes**, and **1,125 regions / 310,442 bytes** still
containing assembly across classifications. The complete goal is not achieved.

The additional full-body experiments are terminal and remain unpromoted:

- Replay snapshot 0x0042A450 emits 581/582 bytes with 140 diagnostic overlap
  differences, first 0x0042A5A8. Its recording branch and first 344 bytes match;
  playback stage-index, original-player pointer/global-reload lifetimes and loop
  register/padding remain unresolved. The normal extent gate rejects it. Under
  its full context, allocator 0x0042AA50 still compares all 139 bytes with six
  differences. Four full dependency bodies (77/273/83/93) match independently;
  only separately selected routines contribute checkpoint bytes.
  [Caller residual](replay_pool_full_caller_2026-09-28.md).
- Replay constructor POD Initialize trials emit 135/139 and fail the original
  extent gate. Positional diagnostics report 69/70 differences including the
  four-byte length delta; the success/null convergence disappears. The barrier
  variant fixes cursor-store/LEA order but swaps MOV ECX/XOR EAX setup. MOV 8B D0
  agrees with retail. Earlier __stosd trials are unsupported-intrinsic/unresolved
  symbol failures, not body measurements. Scratch is restored to 139/6.
  [Structural evidence](replay_pool_constructor_structural_2026-09-28.md).
- The full item allocator remains 823/819 with 774 overlap differences, and E260
  remains 601/609 with 303. Manager EAX/position ECX plus kind/id/angle/speed stack
  and RET16 agreement is established. The next allocator levers are search-loop
  form and kind/remap liveness; E260 needs next-handle increment/return lifetime
  and coordinate-store recovery. Earlier 815/827-byte candidates remain preserved.
  [Caller family](item_spawn_callers_f400_exact_2026-09-28.md).
- Executor remains 1500/1568 with 1300 diagnostic overlap differences; original
  extent verification rejects it before normalization. Final pair context has
  indicator 1343/1317 and music 2764/2796; earlier 1340/2748 models are retained.
  The full 141-byte MarkText normal gate has 21 differences from text/colour
  register-versus-stack allocation. Movement 136 is already exact; player-create
  118/44 differences, right-aligned text 204/115 and centered text 194/104 remain
  nonmatching. Concrete next contexts are the genuine 571-byte indicator caller
  0x00419650 and 4480-byte MarkText caller 0x00415E90, lawful full dispatcher ABI,
  and retail 12-byte/native 16-byte animation-handle local lifetimes.
  [Executor/caller evidence](recovery_script_executor_callers_and_slot_frames_2026-09-28.md).
- Callback allocation remains full 74/74 with 22 differences after both complete
  now-exact player/screen-controller caller trials. Its complete factory model is
  77/82 with 60 overlap differences and remains unselected. Player reset retains
  its prior 244/6 residual after a correct disjoint layout check; the 69-byte
  factory has unresolved typed-initializer compile/link diagnostics, with no fake
  opaque EBX ABI or new 244-byte match.
- MinGW GCC 16.2.0 emits complete 30-byte polar bodies at 0x0041BEB0/0x004458B0
  with one differing leading PUSH each (EAX versus retail ECX). Their genuine
  COFF sections are 32 bytes with two padding NOPs; all later 29 instruction
  bytes match, including FSINCOS and extended scaled stores. Faithful `__frnd`
  emits a representative 22-byte body versus 17, plus separate padding, with a
  stack-realignment residual. These complete compiler comparisons recover zero
  exact routines and are not passed maintained promotion gates.
  [Compiler evidence](gcc_x87_full_bodies_2026-09-28.md).

Unequal-extent overlaps are diagnostics, not weakened promotion gates. Prior
geometry, name-history, emitter and other residuals remain preserved. No bounded
measurement establishes an impossibility claim. No probe remains active at this
checkpoint; the unbounded complete decompilation goal remains active.

Artifacts under `matching2/build/experiments/`:

- `native_recoveries_2026-09-28_sixth_verified.json` and `_port_report.json`
- `native_recoveries_2026-09-28_sixth_build.log`, `_audit.py` and `_integration.json`
- `native_recoveries_2026-09-28_sixth_reviews.json`
- `native_recoveries_2026-09-28_sixth_next_leads.json` and `.md`
- `native_recoveries_2026-09-28_sixth_partial_semantic_audit.json` and `.md`
- `native_recoveries_2026-09-28_sixth_ghidra_before.json`, `_annotate.py` and `_ghidra_verified.json`
- `native_recoveries_2026-09-28_sixth_stage1_verified.json`, `_stage1_port_report.json`,
  `_stage1_project/` and `_stage1_audit.py` (historical first-routine proof)
