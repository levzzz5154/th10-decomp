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

## Main-approved extent change (2026-10-13, later session state)

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
spawn entry (manager still loaded after the pushes into EDI; retail EAX at
entry). The receiver trigger is not reachable from statement order or value
naming in this body; the next attempt should treat the allocator's
callee-saved assignment as the primary unknown (what retail's source held in
EBX across the ScanCells call such that `this` was pushed to EBP).

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
