# Projectile command interpreter `0x00406D90` — equivalent-recovery path

Status: not yet accepted. The readable C++ model is complete
(`matching2/msvc/equivalent/game/projectile_command_runtime_00406d90.cpp`) and
the draft layout `matching2/msvc/layout/equivalent/projectile_command_runtime_00406d90.json`
(absolute_symbols/bindings/context_sources filled in) compiles and links; the
first equivalence run stopped at the size gate: the model's code extent is
1464 bytes against the 1454-byte region (10 bytes over), and the compiled body
currently differs in ~532 of ~700 disassembly lines — dominated by the
receiver being kept in EBX (retail: EBP, with the realigned-frame
`push ebp; ...; push ebp` anchor prologue) and a `sub esp,0x214` frame versus
retail's exact 0x210 buffer-only frame.

## Why this region cannot go semantic

The retail switch dispatch compiles to a byte index table at `0x00407354` and a
five-entry jump table at `0x00407340`, both OUTSIDE the fixed 1454-byte region
(they are today covered by the data region `text_data_00407340` plus two
padding regions from `src/data/text_0040.cpp`). A compiled body always emits
its jump tables inside its own section, so the compiled section is
code (1454) + pad + tables = 0x644 bytes, while the cluster tooling requires
`contributions[0].length == function['size']` and the cluster function size is
pinned to the region extent. Verified against the tooling: the schema-2 link
produces exactly retail's 0x644 contribution, and the validation rejects it.
`equivalence.py` explicitly supports this shape ("the model's code may be a few
bytes longer or shorter; its tables follow its own code"), so the region keeps
its assembly source and takes the equivalent-recovery path.

## The model

`void ProjectileCommandRuntime::Tick()` (symbol
`?Tick@ProjectileCommandRuntime@@QAEXXZ`, thiscall, receiver in ECX — the same
symbol `src/game/bullet_runtime_update.cpp` already calls). Full command
coverage: ids 1, 0x10, 0x20, 0x40/0x80/0x100, 0x400/0x800/0x8000000, 0x1000,
0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x400000 (stack pattern +
`EnemyGrid_ScanCells_004073e0` + conditional `Activate`), 0x100000, 0x200000,
0x4000000, 0x1000000, 0x2000000, 0x80000000, plus the zero-id and guard-word
exits. The 0x210 stack pattern is an `unsigned int[132]` local (retail frame
has no /GS cookie; a char array or `memset(&struct, ...)` spelling makes the
7.1 compiler insert one). The frame-timer first-use blocks and the aim-angle
fallback chain (`< -990` keeps the slot angle, `< 990` is the angle, else
`?AngleFromPoint@EntityAngleFromPoint_00426660@@QAEMPBM@Z` with the point in
EAX) are spelled per retail.

The model needs these co-compiled ABI anchors as context sources so the /GL
pass derives the retail register states at its call sites:
`?SetSchedulerValue@PlayerSchedulerRecord@@QAEXH@Z` (receiver in EAX — bodies
in `layout/ltcg/projectile_spawn_runtime/scheduler_set.cpp`),
`?Activate@PlayerCollisionRecord@@QAEHXZ` (ESI — `activate.cpp`),
`?AngleFromPoint@EntityAngleFromPoint_00426660@@QAEMPBM@Z` (point in EAX —
`angle_from_point.cpp`), `?Queue@SoundQueue@@QAEHHH@Z` (sound id in EDI —
`queue.cpp`), `?QueuePan@SoundQueue@@QAEXHM@Z` (receiver ESI, sound id EBX —
`queue_pan.cpp`), `?SetScorePolar@ScoreGameplayPolarVector@@QAEPAU1@MM@Z`
(`polar_set.cpp`), `?Entity_StartScript_00404f30@@...` (object ESI, script EAX —
`start_script.cpp`).

## Schema-1 composition (latest working state — first ALIGNED-WINDOW verdicts)

With the schema-1 switch, the re-extended Tick region and the restored gap
tiling, the probe reaches the byte comparison for BOTH functions for the first
time: Spawn 0x004067D0 (1472 bytes, extent gate green) and Tick 0x00406D90
(1604 bytes, extent gate green) both DIFFERENT — Tick's first difference is
0x00406D96 (`sub esp,0x214` vs retail `0x210`, and the prologue register
cascade `push ebx; mov ebx,ecx` vs retail `push ebx; push ebp; push esi;
push edi; mov ebp,ecx`); the receiver-in-EBP trigger and the Spawn manager
register remain the open items.

Main's TU-placement hypothesis was tested by converting the manifest to
schema 1: the driver TU textually includes the VERBATIM scan source (plus the
queue_pan anchor and the real Spawn source), the scan compiles as the cluster
CONTEXT at 0x004073E0 (declared size 210 - its drifted size; it is never
exported, and the outer link keeps taking ScanCells' exact 194 bytes from the
registered enemy_grid_scan cluster whose call displacement bakes to 0x004067D0
= the real Spawn), and the selected functions are Spawn (1472, exact extent)
and Tick. Result: Spawn's selected size gate stayed green (1472) across
the schema-1 switch, but the scan context is
STILL 210 bytes in the driver TU - the TU placement does not reproduce the
old cluster's 194-byte promotion either. The remaining delta: Tick's code is
1600 bytes vs the 1604-byte contribution (4 short; reverting the field-store
reorder per Main did not change it - the 4 bytes moved with an earlier edit in
the raw_c/anchor-include era, not with the reorder). The promotion
therefore depends on the CALLEE body (stand-in vs real Spawn) through the
whole-program inlining analysis, not on TU placement - the stand-in era and
the real-body era are different allocator states for the same scan source.

## Main-approved extent change (2026-10-13, earlier session state)

Main approved re-extending the region to 1604 bytes (0x406D90..0x4073D4,
absorbing text_data_00407340 + text_padding_0040733e) once the model reaches
the gate, so Tick goes SEMANTIC through the projectile_spawn_runtime cluster
(functions 0x4067D0/0x406D90/0x4073E0) and the equivalent-recovery path is
superseded. With the extent applied in the scratch project the cluster link
produces a Tick contribution of EXACTLY 0x644 = 1604 bytes (the size gate
passes); the remaining work is byte content: 1360/1604 bytes differ, dominated
by the receiver-in-EBX versus retail EBP allocation and a 3-entry jump table
the model's death switch produced where retail has the 5-entry form at
0x00406D7C. The working model copy is scratch/projectile/tick_golf.cpp (it
includes the four Tick-side anchors before the Tick body; PlayerCollisionRecord
and EntityAngleFromPoint_00426660 come from those anchors, not local
declarations). Follow-up measurement: the 1360-byte diff decomposes into the
coupled Spawn drift (Spawn's section is +12, so its death-switch table sits at
0x406D88 instead of 0x00406D7C and the diff window misaligns) - Spawn reaching
1472 exactly realigns both functions' comparison windows. Main's two levers
were applied and probed: naming the raw command word (`const int raw_c`) and
re-spelling the spawn entry (manager local first) changed neither the Tick
receiver register (still EBX; retail EBP with the anchor prologue) nor the
spawn entry. Additional probes: the 0x400000 pattern-field store order was
re-sequenced to retail's order (no allocator change), a BulletRuntimeTick
co-compile was attempted and abandoned (its source belongs to the
bullet_runtime_caller cluster - clusters must have distinct maintained
sources), a synthetic hot-loop caller anchor did not trigger the missing
ScanCells pattern→EAX promotion, and the cluster entry was moved to Tick
(workable; kept). The receiver trigger is not reachable from statement order
or value naming in this body. Verified from the retail bytes: the value EBX
holds across the ScanCells call IS the case-0x400000 sign (value_c &
0x80000000, loaded at 0x0040718F, masked at 0x004071CC, tested at 0x00407233).
Every spelling of that value (int local, bool, early/late mask, retail-order
field stores) still spilled it - the compiler can always re-read
command.value_c through the still-valid command pointer. A verbatim-copy
co-compile of BulletRuntimeTick (Main's suggestion) is blocked by the
distinct-sources rule (its source owns five functions in
bullet_runtime_caller.json). A ScanCells pattern-use split (Main's other
suggestion) changed its codegen to 226 bytes without triggering the missing
pattern->EAX promotion and was reverted; a TU-merge test (textually including
the scan source into the spawn TU) is blocked by the schema-2 rule that every
selected function's source must be a compiled source path. The promotion that
the old enemy_grid_scan cluster achieved for the identical ScanCells source
remains unexplained - the difference is that the old link was schema 1 with
the scan textually inside its driver TU and a 170-byte stand-in callee, while
this link compiles the scan as its own /GL object beside the real 1472-byte
callee - and is the single blocker for ScanCells' 194 bytes (its source is
untouched and exact under the old cluster).

## Verified this session

The equivalence pipeline reaches the model link and byte relocation; the
layout's `absolute_symbols` is a dict of `name -> {address, kind}` and
`bindings` a dict of mangled symbol -> retail address; context anchors compile
as separate /GL objects. The model's forceinlined aim helper must stay inlined
(an out-of-line copy becomes an unbound call target).

## Next lever

Write `matching2/msvc/layout/equivalent/projectile_command_runtime_00406d90.json`
(schema 1: sources, `entry_symbol`, `function`, `code_bytes` ≈ 1454,
`absolute_symbols`/`bindings` for `_data_00477834`, `_data_004776f0`,
`_data_00492590`, `_data_00474170`, `_data_00470b50/ccc/cc8`, `_data_00476f78`,
`_RunAnimationVm@4`, `?Tick@...` externals; `context_sources` = the seven
anchors above; `context_cluster` may point at
`layout/ltcg/projectile_spawn_runtime.json`), then iterate
`PYTHONPATH=. python3 matching2/tools/matching/equivalence.py --layout ...`
against the model. Expected residual: the frame is 0x14-aligned in retail with
the realigned-ESP prologue (`push ebp; mov ebp,esp; and esp,-8; sub esp,0x210;
push ebx; push ebp; push esi; push edi; mov ebp,ecx`) — the model must keep the
receiver in EBP, which requires the same callee/register pressure as retail;
the whole-program cluster for the caller `0x004067D0` (see
projectile_spawn_004067d0_2026_10_13.md) is the sibling effort.

## 2026-10-13 addendum: the priority law applied to the receiver question

The joystick allocator law (priority = covered-block weight sums minus one
`edx` decay per uncovered block; per-reference weights 4 ordinary / 2 base /
loop-depth+1 loop) explains why the model's case-0x400000 sign value spills:
the sign's live range covers only the 0x400000 case's blocks, so it decays by
`edx` in every other block of the walk - under the law as written it should
never earn a callee-saved register, yet retail keeps it in EBX across the
ScanCells call. Two readings are possible and both are testable next session:

1. the allocator scopes the walk per region (the 0x400000 case is its own
   region: the sign covers all of it and wins EBX there, while `this` covers
   the whole walk and takes EBP via the anchor prologue);
2. the decay only applies from a candidate's birth block onward.

Either way the source lever is the same shape: the sign value's live range
must be a computed intermediate whose every re-derivation is more expensive
than the register (retail's `and ebx,0x80000000` at 0x004071CC, three blocks
before the test at 0x00407233), and `this` must cover the same blocks. The
model already satisfies the second half; the first half needs a spelling
whose recomputation the compiler cannot hoist (the command pointer advancing
past the current record before the mask, making the reload address
unrecoverable, is the untried candidate - `command` must move on BEFORE the
mask and the record base must not be restorable, e.g. by consuming the
command reference through the pattern build).

## 2026-10-13 addendum: the zero-candidate experiment

Naming the zero constant (`const int zero = 0` used in the loop-head checks)
to create a cross-block zero candidate did not tip the receiver: the C2
constant-propagation folds the named local back to immediates before register
allocation, so no zero candidate materializes. The receiver-in-EBP keystone
requires either the allocator's per-region walk scoping (which would give the
sign value a fair priority comparison within the 0x400000 case) or a source
spelling that creates a genuine 4th cross-call callee-saved candidate with
higher priority than the receiver.
