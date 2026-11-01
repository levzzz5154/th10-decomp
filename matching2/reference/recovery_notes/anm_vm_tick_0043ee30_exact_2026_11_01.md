# ANM VM tick 0x0043EE30: byte-exact, 2026-11-01

The ANM VM interpreter `AnmVm::Tick` (9,964 bytes: 9,588 bytes of code plus the
opcode jump table) is now byte-exact C++. The source is
`src/core/sprtanim/anm_vm_tick.cpp`, and it is built in the new cluster
`build_support/layout/ltcg/anm_vm_tick.json`. The old equivalent layout (11
recorded differences, 80 differing bytes) is gone, and so is the asm owner
`build_support/exact/core/sprtanim/anm_vm_tick.cpp`.

## What closed it

1. **Case 60 (scale interpolation), 65 of the 80 bytes.** The callee at
   0x0041AB70 (`AnmVm::StartScale` in the model) is now declared
   `(int end_time, unsigned char mode, const Float2* initial, const Float2* goal)`,
   which is the order the callee stores its fields in. Its own private
   convention stays the same: `this` in EAX, `initial` in EDX, `goal` in ECX,
   with `time` and `mode` pushed. What changes is the caller, because callers
   evaluate arguments in declared-parameter order
   (`msvc-ltcg-callee-param-order-sets-caller-load-order`). `mov eax,ebp` is
   now lowered ahead of the time push. EAX is busy for the whole life of
   `time`, so the duration goes to ESI with a load in each arm, as in retail.
   The case reads naturally:
   `Float2 goal(FARG(2), FARG(3)); int time = IARG(0); vm->StartScale(time, ins->b[4], &vm->scale, &goal);`.
   Only this order gave the retail bytes; 12 member orders were tried.
2. **Strip loop count.** `int count = vm->int_vars[0];` with
   `(float)(count - 1)` in both divisions and
   `for (int i = 0; i < count - 1; ++i)`. c2 still makes this a
   `lea esi,[eax-1]` down-counter, and the temporaries now match retail. That
   closes the strip-head, vertex-body and epilogue register rotations.
3. **Strip origin (the last two x87 operand-order pairs).** `AnmVertex` now
   starts with a `Float3 position`, and each vertex does
   `vertex->position.z = 0.0f; vertex->position += vm->offset + vm->position;`
   through an inline `Float3 operator+=`.

The fix is plain C++: no asm, padding, barrier or flag change.

## Cluster

Schema 1. The cluster reproduces the equivalence rig link. Unit 1 is the Tick
source, through the driver `build_support/layout/ltcg/anm_vm_tick_context.cpp`,
which only includes it. Unit 2 is the rig's context unit, moved from
`src/core/sprtanim/anm_vm_tick_context.cpp` to
`build_support/layout/ltcg/anm_vm_tick_dependencies/callees.cpp`. The link
entry `_RigEntry@8` is the unselected cluster `context`.

- Each of the 29 compiled callees Tick calls is an anchor at its retail
  address, with one `code_seg` per body (the call displacements are baked in).
  That includes the `StartScale` stand-in at 0x0041AB70, kept in place of the
  real `EntityMovementSlot::Initialise` (`src/game/item/entity_movement_slot.cpp`),
  which declares the old parameter order. Using that real body would bring
  case 60 back.
- Bodies Tick does not call are parked at 0x00401000.., at the start of the
  image: `Int3::operator*`, `EvaluateCurve`, `RigEntry` and the escape below.
- The rig defined the game's globals in the context unit. The cluster cannot
  emit .data/.bss and must reference the retail addresses, so they became
  `extern` declarations bound as absolute data symbols:
  - `g_game_speed` 0x00476F78
  - `flt_0` 0x00470B04
  - `g_zero_vector` 0x00491C14
  - `g_scroll_step` 0x00491E6C
  - `g_replay_rng` 0x004918A8
  - `g_effect_rng` 0x004918B0
  - `g_pi`, `g_tau`, `g_neg_pi` 0x00470B18, 0x00470B14, 0x00470B10
- Making them `extern` alone moved Tick in the rig. It gave 6,876 differing
  bytes, all from `g_zero_vector`. Its rig definition (a `Float3` with a
  user-declared constructor) let its address escape. As a bare extern, c2
  CSE'd the three component loads across the stores into the VM, while
  retail re-reads them after each store. The fix is a parked
  `AnmVmTickEscape(void**)` that takes `&g_zero_vector` and `&g_scroll_step`,
  rooted through `anchor_roots`. This is the `TitleDispatcherEscape`
  pattern. With it the rig is back at 0 differing bytes, then the cluster too.
- The seven float literals Tick uses are `constant_aliases` at their retail
  addresses.

Generator: `matching2/build/experiments/goal_2026_11_01/promote_anm_vm_tick/gen.py`.
Its inputs are snapshotted under `inputs/`, and `loop.py` feeds back the map
contribution sizes in `sizes.json`.
