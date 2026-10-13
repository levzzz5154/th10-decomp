# th10 decompilation handoff — 2026-10-13

## Where the project stands

`make` is green. `make EXACT=1` produces the bit-identical executable.
Progress: **94.4% of .text bytes recovered (303,845 of 321,830), 2,313 of
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

Tooling added: `equivalence.py` audited call-target rebases (explicit
bindings only, verified callee bytes only, recorded, 6 new gate tests,
full suite green, all registered recoveries re-verified unchanged).

## The 9 regions still as inline assembly — all parked with complete analysis

Every one is blocked on the same wall: **whole-program /GL register
assignment that cluster-scale links do not reproduce**. Each has a
readable C++ model, a working LTCG cluster (or equivalent draft), a
reproducible one-command probe loop, and a recovery note with the
complete lever history.

| Region | Model state | Single remaining blocker |
| --- | --- | --- |
| 0x004067D0 Spawn (1,472B) | prologue byte-identical; -8 extent | loop-bottom epilogue merge (retail duplicates it) |
| 0x00406D90 Tick (1,604B, approved extent) | size gate green | receiver in EBX vs retail EBP cascade |
| 0x0044DF70 StartChild (550B) | 547 bytes, SpawnChild EXACT | selector/descriptor allocation order — proven not source-steerable (note Rounds 2–7, incl. priority trajectories + scope ladder) |
| 0x0044A190 joystick poll (833B) | 833/833 bytes, 126/282 identical | parameter-lowering memory home (live-across-call AND written-after) — proven semantic, no spelling avoids it |
| 0x0041CA80 laser script Run (1,272B) | full cluster, everything exact but one rename | pc/opcode ECX-EDX swap; contest gap 5332 quantified, flip needs the original's unseen construct |
| 0x0040BD80 script executor (1,568B) | head byte-exact through 0x40BDD3 | ring-loop ESI/EDI swap + per-case IPSA coloring |
| 0x00426F70 familiar refresh (2,520B) | 6 of 7 cluster functions byte-exact | desired/counter arg-home decision (9 rounds documented) |
| 0x00414900 front HUD update (3,836B) | 579/1124 rows identical | C2 whole-program scheduling (allocate block, block positions), volatile-frame merge trade-offs; FlagStopFrame helper merge defeated (sessions 1-20) |
| 0x00415E90 result dispatcher (4,480B) | 733/1225 rows identical | frame exactly 0xD8, 17/18 create sites with homes aligned; residual = C2 fold decisions (0x20 pair), guard-form trade-offs, partial-TU-set register-threading context (sessions 1-20) |

## What was learned about the compiler (the reusable assets)

1. **The c2 priority law is decoded and validated** (joystick note,
   addenda 3–6): priority = Σ covered-block W×A×L − Σ uncovered-block
   A×L; W = 4 ordinary / 2 addressing-base / loop-depth+1 loop tuples.
   Live tracers: `scratch/eclstart/trace_accum.py`, `trace_refs.py`;
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
- The two most promising continuations: (a) the projectile pair — 4 of 6
  structural blockers solved in the last two sessions, both extents green,
  the byte gate is close; (b) finishing the scope ladder (fix the batched
  harness's header collisions) — if a 100+-TU scope flips any parked
  region's allocation, the mega-cluster endgame opens for all of them.
- Scratch trees are disposable; everything needed to resume is in the
  real tree (models, manifests, notes) plus the documented probe commands.
