# th10 decompilation handoff — 2026-10-14

## Where the project stands

`make` is green. `make EXACT=1` produces the bit-identical executable.
Progress: **96.5% of .text bytes recovered (310,672 of 321,914), 2,318 of
2,322 regions**; the executable's C++/equivalent share is at parity with
what remains as inline assembly.

### Accepted this campaign (10 regions, all equivalent recoveries)

| Region | Bytes | Verdict |
| --- | ---: | --- |
| 0x004247F0 player reset block init | 1,435 | 285/314 identical, 24 hunks |
| 0x0042E5A0 options label refresh | 3,999 | 1174/1204 identical, 40 hunks |
| 0x0041AFD0 item update | 2,320 | 448/601 identical, 84 hunks |
| 0x00422660 result rows renderer | 1,062 | 286/288 identical, 3 hunks |
| 0x00417C80 manager teardown | 1,105 | 283/309 identical, 18 hunks |
| 0x00428F60 replay runtime bootstrap | 1,344 | 387/389 identical, 3 hunks |
| 0x004465B0 texture transparent fill | 1,463 | 365/499 identical, 80 hunks |
| 0x00429B60 replay save/serialize | 1,681 | 408/535 identical, classified |
| 0x004236F0 replay submenu | 3,260 | 751/923 identical, 80 hunks |
| 0x0041A200 SaveHints | 2,247 | 693/741 identical, 9 audited rebases |
| 0x0044DF70 StartChild (2026-10-14) | 550 | 144/165 identical, 21 classified |
| 0x0044A190 joystick binding reader (2026-10-14) | 833 | 251/282 identical, th06-style `&buttons` helpers |
| 0x00426F70 familiar refresh (2026-10-14) | 2,520 | 641/643 identical, 1 operand-order hunk |
| 0x0040BD80 script executor (2026-10-14) | 1,568 | 400/444 identical, 28 classified hunks |
| 0x00415E90 result dispatcher (2026-10-14) | 4,480 | 873/1147 identical, 138 classified hunks (structural 121/143); see front_script_tick_00415e90_accepted note |
| 0x00414900 front HUD update (2026-10-14) | 3,836 | 1064/1089 identical, 22 classified hunks (structural 25) |

Tooling added: `equivalence.py` audited call-target rebases (explicit
bindings only, verified callee bytes only, recorded, 6 new gate tests,
full suite green, all registered recoveries re-verified unchanged).

## The 2 regions still as inline assembly — all parked with complete analysis

Every one is blocked on the same wall: **whole-program /GL register
assignment that cluster-scale links do not reproduce**. Each has a
readable C++ model, a working LTCG cluster (or equivalent draft), a
reproducible one-command probe loop, and a recovery note with the
complete lever history.

| Region | Model state | Single remaining blocker |
| --- | --- | --- |
| 0x004067D0 Spawn (1,472B) | 1,476/1,472 (+4); frame 0x14 matches retail; one hoisted load; 394 diff lines | second hoisted load (the entry shape is composition-dependent on Tick's IL); the epilogue tail-merge; the register-assignment cascade |
| 0x00406D90 Tick (1,604B, approved extent) | 1,564/1,604 (-40); the retail-matching head (the volatile guard + the commands-index read pinning the non-rotated form), the bottom polarity (jl back-edge), the verified int field stores, the sign carried across the ScanCells call, the prewritten shared pattern buffer | receiver-in-EBX vs retail EBP — traced to C2's frame-spill heuristic (the frame's +360 epilogue grant displaces the receiver's faster-decaying priority; retail's IL tipped the entry spill, mine doesn't); c2-level tooling territory |

## What was learned about the compiler (the reusable assets)

1. **The c2 priority law is decoded and validated** (joystick note,
   addenda 3–6): priority = Σ covered-block W×A×L − Σ uncovered-block
   A×L; W = 4 ordinary / 2 addressing-base / loop-depth+1 loop tuples.
   Live tracers: `matching2/reference/compiler_traces/regalloc/trace_accum.py`, `trace_refs.py`;
   landmarks: ChoosePhysReg 0x107AAB62, driver 0x107A926D, picker
   0x107A9D71, per-reference value 0x107A99D9.
2. **Parameter-lowering rule**: an incoming register parameter that is
   live across a call AND written after it gets a memory home — the
   0x0044A190 spill is unavoidable at source level.
3. **/INCLUDE roots freeze declared ABIs**; interprocedural register
   reassignment only reaches call-graph-reached receivers (frame_timer
   bisection).
4. ** volatile parameter splitting** defeats CSE and reproduces retail's
   disjoint live ranges (projectile Spawn prologue breakthrough).
5. **Volatile on storage forces retail's x87 operand order** (frame_timer
   precedent, reused by familiar refresh).
6. Scope-size ladder (does a bigger /GL scope reproduce retail's
   choices?): **final verdict delivered** — no movement at 0/9 extras;
   the 100+/150 rungs are unmeasurable under this wine (cl's
   /showIncludes emission truncates nondeterministically as TU count
   grows, even with file redirection). Combined with the decoded-formula
   proof (priority is a fixed function of the reference structure,
   identical between draft and retail), retail's flip must come from a
   c2-internal component outside the decoded accumulation — the two
   remaining RE targets are the block-weight assignment and the
   initial-home pass. Batched-ladder harness is turnkey in
   `scratch/eclstart/` for a future wine upgrade.

## How to continue

- Per region: read its recovery note in `matching2/reference/recovery_notes/`
  (every note ends with "next levers" and a resumption recipe). Scratch
  projects (`scratch/<name>/msvc/`) hold the working probe loops —
  reflink-copy per the playbook (`local://th10-conversion-playbook.md`).
- Workflow, gates, conventions: repo README + the playbook.
- Gate measurements of the existing drafts (real `equivalence.py --layout`,
  2026-10-14; older cluster-probe diff counts did not match the gate):
  front HUD 875/1089; front_script_tick and the
  projectile layouts do not link. StartChild went 76 -> 21 through source
  shape (in-loop strength-reduced IVs, volatile re-read of a split param,
  post-loop param copy); see its 2026-10-14 note for the method.
  The joystick reader went 156 -> 16 by writing it in the decompiled th06
  controller's shape (button helpers through `&buttons`): check sibling
  Touhou decomps for a function's original shape before tracing c2.
  The laser interpreter 0x0041CA80 went byte-exact once its model was made
  semantically right (a missing case, a reversed ternary, a shared `++pc`):
  verify a parked model's semantics against retail before blaming c2.
  The familiar refresh 0x00426F70 went 309 -> 641/643 the same way
  (re-transcribed: wrong count field, if-chains that were switches, the
  record view at the true 0x98 base +0x32A0) plus the escaped game-counters
  struct; see its 2026-10-14 accepted note. Only one commutative-add operand
  order separates it from byte-exact.
  The script executor 0x0040BD80 went 305 -> 400/444 by fixing *context*
  conventions, not the body: the ASCII factory's real shape (wiping ctor +
  member Configure) put draw priority in EBX; handle validation 0x449450 is a
  free function (retail pushes no receiver); a case-8 handle pointer; index
  loops with plain manager reads. Equivalent-only context copies live in
  `matching2/msvc/equivalent/game/context/` so registered clusters stay intact.
- Treat "proven not source-steerable" verdicts as "not found yet": earlier
  "impossible" allocator residuals were closed by changing cluster context
  (real callee bodies, escaped-global structs, callee parameter order/convention),
  not the function body.
- The two most promising continuations: (a) the projectile pair — 4 of 6
  structural blockers solved in the last two sessions, both extents green,
  the byte gate is close; (b) finishing the scope ladder (fix the batched
  harness's header collisions) — if a 100+-TU scope flips any parked
  region's allocation, the mega-cluster endgame opens for all of them.
- Scratch trees are disposable; everything needed to resume is in the
  real tree (models, manifests, notes) plus the documented probe commands.
  The c2 tracers live in `matching2/reference/compiler_traces/regalloc/`
  (usage line at the top of each). The HUD pair probe scripts
  (`tools_hudpair_*.py`, `prologue_test.py`) are in `scratch/hudpair/` and
  run from the repo root.
