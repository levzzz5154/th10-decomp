# Familiar refresh native-LTCG attempt: `0x00426F70`

## Result

Still BLOCKED after the follow-up round. The complete semantic recovery
compiles inside a working native-LTCG cluster (schema 1) whose structure now
tracks retail instruction-for-instruction through most of the body, but the
byte gate does not pass.

- Closest state: compiled contribution **2,628 bytes vs 2,520 retail**,
  **506/2520 bytes match**, first divergence at `0x00426F72` (local-frame
  topology `sub esp,0x34` versus retail `sub esp,0x38`). At the
  disassembly level the streams are ~1000 instruction pairs and
  **541 differ** — down from 614 at the start of the round — with the
  sweep loops, the six-entry switch with its embedded jump table, the
  per-case create calls and the x87 conversion blocks structurally aligned.
- Verbatim probe verdict: `native cluster image base or entry address differs`
  followed by `NOT EXACT`. The cluster itself builds green end to end
  (/GL compile, native /LTCG link, map); validation stops once the entry
  extent and register roles diverge, so the gap layout cannot lock.

## What this round changed (two real findings)

1. **x87 operand order is SOLVED** (Main's frame_timer lever): declaring the
   schedule table's row storage `volatile` (`volatile float rows[78]` in
   `FamiliarOffsetTable_00426f70`) makes every conversion emit
   `fld [row]; fmul ds:0x470b44` exactly as retail, in all five paths.
   Restructuring the table access as a float array with a `3k` index also
   reproduced retail's `lea ecx,[eax+eax*2]; [reg+ecx*4+0x20/0x98]`
   addressing (a 12-byte-struct spelling forced `shl` + scale-1 instead).
   Residual: retail spills the row pointer for the second conversion of each
   pair (`lea esi,[edx+ecx*4+0x20]; fld [esi+4]`) where the compiled code
   re-derives the base (`fld [eax+ebx*4+0x24]`) — same bytes-class, minor.
2. **CreatePrimaryFront out-slot customization fixed**: the ABI anchor model
   used to `return out` directly, which kept `out` as a live stack parameter;
   routing it through the registrar's sret
   (`*(AnimationRef*)out = lists->RegisterPrimaryFront(object); return out;`)
   lets the whole-program pass coalesce out into a register, and the caller's
   six switch cases immediately re-shaped to retail's exact per-case
   `mov eax,[player+0x10]; push 0xf; push <idx>; push eax; lea REG,[esp+X];
   call; mov ecx,[eax]; mov [esi],ecx` with the shared 0x16 tail — six
   distinct out slots, no tail-merging, exactly the retail case layout.

## Entry copy (Main's second lever) — exhausted at the source level

Retail's prologue copies the player argument into `EBP` immediately
(`mov ebp,[esp+0x44]` right after `push ebp`, between `sar edx,3` and the
desired-count store) and reuses the dead argument slot for `desired`
(`[esp+0x4c]`); the frame is `0x38` (counter at `[esp+0x10]`, six sweep out
slots, six loop out slots, one row-pointer temp). Every spelling below still
assigns the player to `EDI` (copy after the fourth push), gives `desired` a
fresh `[esp+0x10]` local and hands the argument home to the sweep counter —
the same roles rotated one step around the EBP/EBX/EDI cycle:

- reference parameter (`PlayerFamiliarRuntime_00426f70&`) — identical bytes;
- early player use before the gauge read (coalesced away);
- named function-scope `remove_flag` constant threaded through the retire
  helper (changes the flag's SSA order; register roles still rotate);
- hoisted node declaration in the inline lookup helper;
- alias local for the parameter;
- **unrooting the entry** (per the wave-12 finding that the pass loads a
  one-stack-argument into `EBP` in the prologue only when reached from a real
  call site): removing `roots` and reaching the body from the synthetic
  context instead made the pass go further and *customize the function's
  calling convention entirely* (player in `EDI`, `ret` without `4`). Adding a
  volatile function-pointer read of the entry in the context (address escape)
  restored the public `RET 4` boundary — but the register assignment stayed
  `EDI`. Rooted and unrooted+escape now produce identical prologues.

The residual is therefore one allocator decision (which of EBP/EDI receives
the parameter entry copy) that cascades into the frame size, the argument-home
reuse, the flag register (retail `EBX`), the out-slot register (retail `EDI`)
and the ±4-byte displacement shifts across the whole body.

## Round 3: schema-2 cluster with verbatim callee copies (Main-approved)

Per Main's correction, the real callee sources were copied verbatim under
`layout/ltcg/familiar_refresh_00426f70_dependencies/` (allocate.cpp — the
genuine pool allocator from the player_initialize dependencies including the
one-pointer Entity_Init, register_primary_back.cpp, register_primary_front.cpp,
create_primary_front.cpp, find.cpp, set_stop_frame.cpp) and listed as
`additional_sources` of a schema-2 manifest whose entry is the refresh itself.
The create copy's two thunk calls were re-spelled onto the co-compiled real
members (the verbatim text targets `asm_*` thunks that have no body in this
cluster); everything else is verbatim with address-ordered `code_seg` names.
The six callee regions were re-pointed at the copies in the scratch
`regions.json` and the four superseded manifests removed from the scratch
cluster list (the orchestrator owns that step for the real tree).

**The whole-program scope reproduced retail's entry copy.** The compiled
prologue now performs `push ebx; push ebp; mov ebp,[esp+0x40]` — the EBP
argument copy in retail's exact position — with the scan-loop registers
(node EDI, manager EDX, flag EBX) and the six create cases
(`lea edi,[esp+X]` per case, EDI out slots) matching retail's shape.

Closest state: extent 2644 vs 2520; 548 of ~1000 instruction pairs differ,
all in the same scheduling/home-assignment class. Remaining deltas:

1. **desired/counter argument-home swap (mirrored).** Retail: desired in the
   dead arg home (`[esp+0x4c]`), the sweep/loop counters in `[esp+0x10]`.
   Compiled: desired at `[esp+0x10]`, the counters share the arg home. Frame
   `0x34` vs `0x38` follows (retail's extra slot is the row-pointer temp).
2. **Row-pointer spill shape.** Retail materializes the row pointer once per
   pair (`lea esi,[edx+ecx*4+0x20]; fld [esi+4]`); the compiled code
   re-derives the base for the second conversion (`fld [eax+ebx*4+0x24]`).
   The inline-then-pointer spelling did not sink the materialization.
3. Create wrapper 81 bytes vs 73; callee registers (Allocate/RegisterPrimary*)
   still carry their own scope-derived assignments to tune.

The x87 order and `lea 3k`/scale-4 addressing fixes from round 2 carry over.

## Round 4: allocator follow-ups measured

* Non-volatile rows in the schema-2 scope reverts the fld order to
  constant-first — the `volatile float rows[78]` spelling is required in both
  scopes and stays.
* The 13-vs-14 frame slot difference is identified precisely: retail's frame
  carries one row-pointer temp at `[esp+0x18]` interleaved between the loop
  out slots (`0x14, 0x18, 0x1c, 0x20, 0x24, 0x28, 0x2c`), while the compiled
  code packs the six loop out slots contiguously and keeps the row pointer in
  a register. Defining desired after the sweeps removes the prologue division
  (worse); focused-row pointer temps stay in registers; the inline-then-
  pointer spelling does not sink the materialization.
* The argument-home assignment remains mirrored (desired `[esp+0x10]` /
  counters in the arg home versus retail's exact opposite) and is the last
  home-assignment blocker; everything else in the prologue, sweep, switch and
  create-case regions tracks retail's register roles.

## Round 5: callee exactness confirmed, caller deltas isolated

Re-measuring the callee bodies with the correct base addresses (the earlier
per-callee "differ" counts were a disassembly base-shift artifact):

* `?RegisterPrimaryBack@AnimationLists@@QAE?AUAnimationRef@@PAUEntity@@@Z`
  — **byte-EXACT (0/118)**
* `?RegisterPrimaryFront@AnimationLists@@QAE?AUAnimationRef@@PAUEntity@@@Z`
  — **byte-EXACT (0/112)**
* `?Find@AnimationManager@@QAIPAXPAUAnimationLookupContext@@UAnimationScriptId@@@Z`
  — **byte-EXACT (0/73)**
* `?SetStopFrame@AnimationHandle_00449470@@QAEXG@Z` — **byte-EXACT (0/65)**
* `?Allocate@AnimationPool@@QAEPAUEntity@@XZ` — 12/161 differ, all four
  `Entity_Init`/`Entity_Constructor`/`operator new` call displacements that
  resolve once the whole-image placement locks
* `?AnimationManager_CreatePrimaryFront_00448e30@@YGPAPAXPAXPAPAXHH@Z` —
  **byte-EXACT (73/73)** after restoring the verbatim thunk calls and
  anchoring the registrar model at `0x00448A50` (wave-12 recipe: the thunk's
  explicit `out` parameter is what wires the wrapper's out slot to the
  registrar's sret; the direct member-call spelling allocated a sret temp and
  an 8-byte copy that broke the extent).

The create region's `RegisterPrimaryFront` selection was dropped from the
cluster (the anchored thunk stands in for it, as in wave-12); the region
reverts to its registered source for coverage by its own cluster.

The caller's branch structure was also inverted to retail's shape
(`if (shot != 0)` with the difficulty chain falling through) without moving
the remaining homes.

## Remaining caller deltas (unchanged this round)

1. desired/counter argument-home swap (mirrored), frame 0x34 vs 0x38.
2. Row-pointer spill shape (the second conversion of each x87 pair).
3. My function's extent 2644 vs 2520.

Register-role analysis for the row temp: retail's loop-B keeps EBX=resource
then object, ESI=manager then object, EDI=out slots — no callee-saved register
remains for the row pointer, so it spills to `[esp+0x18]`. The compiled loop-B
keeps the 3k row index in EBX across the conversions (the direct indexed
volatile loads need no pointer), which leaves the temp unallocated. The
resource hoist (loading `player->resource` before the Allocate call, as retail
does) did not shift it.

## Round 6: table-view experiments

Three table spellings were measured for the x87 addressing:

1. single `rows[k*3+30]` array — the carried pair lowers correctly
   (`lea edx,[ebx+ebx*2]; fld [eax+edx*4+0x20]`) but the focused pair
   computes the byte offset (`lea eax,[ebx+ebx*2]; shl eax,2;
   fld [ecx+eax*1+0x98]`).
2. anonymous-union overlay (`unfocused`/`focused` members at +0x20/+0x98) —
   same shl form for the focused member.
3. flat two-member layout (`unfocused[30]` at +0x20, `focused[26*3]` at
   +0x98) — same shl form; the carried pair keeps scale-4 and spills appear
   (`mov [esi],eax` / `mov [esp+0x14],edx`) as the j-removal freed the
   register pressure.

The shl form persists across all three because MSVC materializes the byte
offset 12k for the focused access (its member offset 0x98 rides the disp)
while the carried access keeps 3k with the member offset folded into its own
disp — an asymmetry in the strength reduction that survives every spelled
view tried. The candidate fix for a fresh session: spell the focused pair
through the SAME member the carried pair uses, with the +0x78 (30-float)
skew expressed in the member's own offset — i.e. a union whose second view
starts at +0x98 — and verify whether the anonymous-struct nesting (rather
than the +30 index) is what blocks the disp folding, or accept the
`focused` member access through a dedicated pointer local.

## Round 7: retail addressing decomposition and spill progress

Main's two-register observation was verified against the retail dump: the
focused pair lowers as `FLD [EAX+EDX*4+0x98]` with EAX = the schedule table
pointer and EDX = 3k — the same two-register form as the carried pair, with
the member offset 0x98 riding the disp32 (the member offset exceeds disp8
range, which is why the compact disp8 form the carried pair enjoys at 0x20
is unavailable and the compiler's strength reduction chooses the byte-offset
form `lea eax,[ebx+ebx*2]; shl eax,2; fld [ecx+eax*1+0x98]` in every spelled
view tried).

Spill progress: the current build (single array with the +30 skew, j-locals
removed) spills record-field pointers and row-pointer temporaries
(`mov [esi],eax`, `mov [esp+0x18],eax`, `mov [esp+0x14],ebx/edx`) — the
pressure structure finally matches retail's — but the per-access forms still
churn (carried y via `lea ecx,[ebx+ebx*2+0x9]; fld [edx+ecx*4]` instead of
retail's spilled-pointer `fld [esi+0x4]`; focused y via a second spill
instead of the first).

State: extent 2644 vs 2520; 595 of ~1000 instruction pairs differ (the best
measured combination remains the named-j single-array build at 548).

## Round 8: x87 addressing fully aligned (union second view)

Main's union second-view suggestion resolved the focused-pair addressing: the
table view is now

```cpp
struct FamiliarOffsetTable_00426f70 {
    unsigned char reserved_00[0x20];
    union {
        volatile float carried[26 * 3];          // +0x20, row k at [j]
        struct {
            unsigned char overlay_pad[0x78];
            volatile float second[26 * 3];       // +0x98, row k at [j]
        };
    };
};
```

with the named `j = k * 3` index shared by both views. All four conversions
now use retail's exact two-register form — `fld [reg_table + reg_j*4 + 0x20]`
and `fld [reg_table + reg_j*4 + 0x98]` — with no shl forms anywhere (the
previous best, 548 pairs, still had shl forms and recompute-in-place y
loads). Combined with the carried/focused member split, the disassembly diff
stands at **542 of ~1000 pairs**.

A shared named counter local (one variable for the sweep and loop counters,
matching retail's single shared slot) was also tested: no home change (542,
unchanged) — kept for semantic clarity.

## Remaining blockers (isolated)

1. **desired/counter argument-home swap (mirrored).** Ten experiments have
   not moved it: the compiled frame puts desired at `[esp+0x10]` and the
   shared counter in the dead argument home; retail is the exact opposite.
2. **Row-pointer spill shape.** Some paths still recompute the row address
   for the second conversion instead of spilling the pointer.
3. Extent 2660 vs 2520 follows from the frame difference.

All other structure — prologue EBP entry copy, flag register, scan loops,
six-entry switch with embedded jump table, create-case layout, x87 operand
order and two-register addressing, and the six callee bodies (four
byte-exact, two placement-exact) — matches retail.

## Round 9: arg-home experiments closed

Main's four arg-home experiments were executed: (1) address-taken desired —
no change (542, homes unchanged); (2) the coalescing direction was verified
as already parameter-into-register (the prologue reads the parameter once
into EBP exactly as retail, before the desired store); (3) retail's
first-use ordering was verified as already mirrored (the parameter's only
stack read precedes the desired store in both compiles); (4) the counter
live ranges already do not overlap desired's uses. An early parameter use
(the effects-control base computed before the gauge read, making the
front-end parameter use precede desired's definition) was also tested — the
arg home still went to the counter.

The argument-home assignment has now resisted every source-level lever
identified across nine rounds. The remaining delta is one allocator decision
(desired in the frame vs the counter in the frame) whose frame-size knock-on
(0x34 vs 0x38) accounts for most of the byte residual. Everything else —
prologue EBP entry copy, flag register, scan loops, switch/jump table,
create-case layout, x87 operand order and two-register addressing, and six
callee bodies (four byte-exact, two placement-exact) — matches retail.

## Next lever

Iterate the remaining home-assignment/spill spellings inside this schema-2
scope (the argument-home swap is now an isolated two-slot decision), then
tune the five callee bodies' registers in the same scope. All artifacts are
synced between the real tree and `scratch/gfr/msvc`; probe with
`--project scratch/gfr/msvc --source src/game/familiar_refresh_00426f70.cpp
--output matching2/build/probe-gfr`.


## Artifacts

- `src/game/familiar_refresh_00426f70.cpp` — full readable recovery
  (sweeps, switch/table, five rebuild paths, allocate/initialize/register
  edges, callbacks, stop-frame edge, surplus tail, count/dirty stores).
- `include/th10/game/familiar_refresh_00426f70.hpp` — strided view types
  (orbit slots at 0x98, control block at +0xBC, manager buckets, schedule
  table with `volatile float rows[78]`).
- `layout/ltcg/familiar_refresh_00426f70_context.cpp` — driver with six ABI
  anchor models (Allocate, RegisterPrimaryBack/Front, CreatePrimaryFront with
  the sret chain, Find, SetStopFrame) and the synthetic context with the
  public-boundary escape.
- `layout/ltcg/familiar_refresh_00426f70.json` — schema-1 manifest
  (roots currently set; with `roots: []` the pass customizes the entry ABI —
  documented above).
- `matching2/tools/scratch/fix_gfr_gaps.py`, `diff_gfr.py` — gap recomputation
  from the linker map and aligned retail/native disassembly diffing.
- Scratch project `scratch/gfr/msvc` (reflink copies) is in sync with the
  real tree; probe with `--project scratch/gfr/msvc --source
  src/game/familiar_refresh_00426f70.cpp --output matching2/build/probe-gfr`.

`regions.json` was not edited (scratch copy only). The maintained region for
`0x00426F70` remains the exact naked-assembly implementation in
`src/game/gameplay_final_runtime.cpp`.
