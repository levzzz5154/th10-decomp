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

## 2026-10-13 addendum: the tracer infrastructure assessment

The winedbg+gdb tracer (adapted from the joystick agent's trace_accum.py) was
attempted for the /LTCG link phase. The hardware breakpoints at the c2.dll
allocator addresses (0x107A991C/0x107A997E) were armed but never hit — the
c2.dll load address in the Wine WoW64 environment could not be verified (the
32-bit address space is not visible in /proc/PID/maps for WoW64 processes, and
gdb's `info sharedlibrary` does not show Wine-internal DLLs). The winedbg
native mode (`attach PID; info share`) also failed to produce the module list.

The tracer approach requires either:
1. a Wine debug build with 32-bit process map exposure, or
2. winedbg's native interactive mode (which the joystick agent may have used
   interactively rather than through the scripted --gdb interface), or
3. the c2.dll base address to be determined through the /LTCG pass's own
   initialization code (a deeper reverse-engineering effort).

The priority-law framework is fully documented and the per-block coverage
census can be computed analytically from the disassembly once the tracer is
available or the law is extended to cover the per-region walk hypothesis.

## 2026-10-14 addendum: the tie-break law and the receiver keystone

The c2.dll candidate-priority tie-break was read DIRECTLY from the disassembly
(no tracer needed — image base 0x10700000, .text maps 1:1 to file offsets):
- The insertion walk at RVA 0x000A9E2B stops (inserts earlier) when the current
  node's +0xc priority EXCEEDS the new candidate's — the ready list is
  descending by +0xc, so the highest priority pops first.
- On priority ties, the walk continues while current->+0x44 < new->+0x44 —
  the list is also descending by +0x44, so among equal-priority candidates the
  LARGER +0x44 pops first. +0x44 is written at candidate creation
  (sequence-like) → ties favor the LATER-created candidate.

Consequence for the receiver keystone: the receiver (this) candidate is created
at entry (earliest), so it CANNOT win ties against later candidates — retail's
EBP receiver must come from a strictly higher +0xc priority. The priority is
live-range driven; unifying the receiver's derivations (routing the manager
access through the bound `record` reference instead of re-casting `this`) did
not change the compiled prologue (still `sub esp,0x214` + `mov ebx,ecx`), so
the remaining lever is the +0xc priority itself — observable only through the
tracer, which remains blocked by the WoW64 address-space invisibility.

The Spawn-side entry-copy lever (documented in the sibling note) recovered the
retail frame (sub esp,0x14) with one hoisted load: 1476/1472 bytes. The pair's
composition coupling persists: Spawn's prologue shape depends on Tick's IL,
which depends on the receiver keystone — the two converge only through the
priority data.

## 2026-10-14 addendum 2: the reference-count experiment

Per the priority law (per-reference values accumulate), the model's cached
`const int index = record.command_index` reduced the receiver's +0x45C reads
to 10 vs retail's 13. Un-caching (`record.commands[record.command_index]` +
`record.command_index = record.command_index + 1` at the four increment sites)
restored per-site re-reads. Resulting receiver-ref census:
- retail: 82 receiver refs, 44 distinct offsets, 13x +0x45C, 12x +0x43C
- model:  87 receiver refs, 48 distinct offsets, 10x +0x45C, 12x +0x43C

The compiled prologue did NOT change (still `sub esp,0x214` + `mov ebx,ecx`),
so the receiver keystone is not the reference count alone. The structural
prologue difference that remains: retail pushes ALL callee saves eagerly
(push ebx; push ebp AGAIN as the frame-pointer spill; push esi; push edi) then
overwrites EBP with the receiver (mov ebp,ecx) — the frame lives in ESP after
the and-alignment. The model pushes ebx only before the first compare and
defers esi/edi past it, keeping the frame pointer in EBP and the receiver in
EBX. The receiver-vs-frame-pointer priority decision is what the tracer must
observe; the deferral shape suggests the model's entry block has lower register
pressure than retail's, which may itself be the priority symptom.

## 2026-10-14 addendum 3: the loop-fusion break (volatile guard) — structure matches, size overflows

A `volatile` guard read (`*reinterpret_cast<volatile int*>(&record.command_index) >= 18`)
broke the loop-rotation fusion and produced retail's EXACT two-load structure:
```
cmpl $0x12,0x45c(%ebx)   ; the guard's memory-form compare (retail: cmp [ebp+45Ch],12h)
push %esi / push %edi
jge  exit
mov  0x45c(%ebx),%edx    ; the loop-top re-read (retail: mov edx,[ebp+45Ch] at L_00406db0)
```
Cost: +4 bytes (1608 vs the approved 1604 extent — the extent is a hard gate),
so the spelling was reverted pending a -4 compensation. The fused form (one
load serving guard + loop head) is what keeps the frame slot at 0x214 vs
retail's 0x210 — the two structures differ by exactly one 4-byte slot plus
one load. Finding the -4/-8 of legitimate body content with the volatile guard
in place is the next Spawn-side-style lever for Tick.

The exit order difference stands as the receiver-keystone signature:
retail pops edi,esi,ebp,ebx then mov esp,ebp; pop ebp (the frame-pointer SPILL
form) vs the model's pop edi,esi,ebx; mov ebp,esp; pop ebp. Retail's form only
arises when the allocator spills the frame pointer to free EBP for the receiver
— i.e. the receiver wins only when the body's register pressure forces the
spill. The model's lower entry pressure (deferred esi/edi saves) and the fused
guard are two faces of the same deficit: retail's body keeps one more value
live at the loop head.

## 2026-10-14 addendum 4: the full structural map (volatile guard form, 1608)

The volatile-guard form was re-applied and diffed structurally against the
retail bytes (extracted from decompiled/ghidra_augmented/memory.hex at
0x406D90, 1604 bytes). Retail: 421 instructions; model: 426. The structural
deltas beyond the known receiver/frame/prologue items:

1. The volatile guard's +4 is exactly the loop-head re-read (mov edx,[45Ch])
   minus the memory-form compare saving (-2): the fused form reused the
   guard's EDX for the commands lea; retail re-reads. Retail is structurally
   IDENTICAL at the head — the -4 must come from the body.

2. The model INLINES duplicated case bodies where retail jump-threads them:
   the timer-reset store sequence (6d8/6dc/6e0 and 7dc/7e0/7e4) appears once
   in retail (a shared jump target at 0x40731C) but twice in the model (once
   inline per case). The link uses /OPT:NOICF, so retail's sharing is the
   COMPILER's jump threading, not ICF. The model's case ordering blocked the
   threading — the jump table base differs (retail movzbl 0x407354, model
   0x407368) and the case bodies land in a different order.

3. The copy-loop block (the rep movsl at the 0x40000 case) is byte-similar in
   both; the volatile guard did not shift it.

4. The bottom-of-loop: retail's loop bottom ends with
   mov eax,[45Ch]; inc; mov [45Ch]; cmpl $0x12,[45Ch]; jl 0x406DB0 —
   the increment re-reads and the check is the memory form. The model's
   bottom inline-handles the next-iteration head (the rotation) —
   reproducing retail's flat jump-back requires the bottom check to be the
   memory form WITHOUT the head inline.

The -4 candidates in priority order: (a) recover retail's jump-threaded
shared timer-reset block (saves ~10 bytes, then re-balance), (b) merge one
of the duplicated fildl/fstps float-store pairs, (c) the case-table order
convergence. All are switch-lowering shapes driven by the source case order
and the goto structure inside the switch — not by register assignment.

## 2026-10-14 addendum 5: the retype verification and the case-order check

### Retail store-form verification (all confirmed)
+0x6D8 mov ecx / +0x6DC mov edx,[esi+0xC] / +0x6E0 mov edi / +0x7DC mov ecx /
+0x6A4 mov eax / +0x420 mov ecx / +0x6F8 mov edx / +0x710 mov eax — all plain
int moves; +0x660 and +0x6C8 stay float (fstps, the AngleFromPoint results).
The int retype of the seven fields is verified correct against the retail
encoding.

### The jump-table check
Retail's byte map (128 bytes at 0x407354) and the model's match — the
meaningful entries ([0]=00, [15]=01, [31]=02, [63]=03, [127]=03) align after
correcting a 4-byte table-base extraction artifact. The case COVERAGE and the
dispatch tree pivots (both trees open with the cmp $0x1000) are equivalent;
the source case order does not need reordering.

### The remaining structural delta
The case-body EMISSION layout: retail's previous case ends with an explicit
jmp to the loop bottom (0x40731C) and the next case's body follows; the model
falls through differently, inlining what retail shares. The tail-coincidence
that drives C2's jump threading is a fallthrough-structure property the
source influences only weakly. The 6d8/6dc/6e0 duplication itself FOLDED
after the int retype (the float conversions had made the two copies
non-identical) — the remaining layout deltas are block ORDER, not
duplication.

## 2026-10-14 addendum 6: the goto-bottom re-spell and the final state

Re-spelling all 14 switch-case `break;` as explicit `goto bottom;` recovered
-4 bytes (1628→1624): every case now ends with the same explicit jump to the
loop bottom, matching retail's explicit jmp-to-bottom-between-bodies layout.

The receiver keystone is unchanged by every applied lever (the int retype,
the volatile guard, the goto re-spell): the model still compiles with
`sub esp,0x214` + receiver-in-EBX + the `pop edi,esi,ebx; mov ebp,esp; pop ebp`
exit, vs retail's `sub esp,0x210` + receiver-in-EBP + the
`pop edi,esi,ebp,ebx; mov esp,ebp; pop ebp` exit (the frame-pointer spill
form). The remaining 10-line instruction-count delta is block order.

The per-region walk hypothesis test requires the tracer (the walk order is
runtime data). The tracer remains blocked by the WoW64 address-space
invisibility — see the addendum in the sibling note.

FINAL PAIR STATE (this session):
- Spawn 0x004067D0: 1476/1472 bytes (+4), frame 0x14 ✓, one hoisted load,
  394 diff lines.
- Tick 0x00406D90: 1624/1604 bytes (+20), the retail-matching head structure
  (the memory-form guard cmp + the loop-top re-read), the verified int field
  stores, 431 vs 421 instructions.
Both functions' structures converge; the byte gates remain open on the
allocator-composition residuals (the receiver keystone + the frame slot).

## 2026-10-14 addendum 7: the loop-rotation break at the commands binding

Adding the volatile qualifier to the COMMANDS BINDING's index read (the
`record.commands[*reinterpret_cast<volatile int*>(&record.command_index)]`
form — the same loop-rotation break as the guard's) collapsed the bottom
rotation: Tick dropped 1624→1580 bytes (-44) and the instruction count hit
420 vs retail's 421 — the closest structural convergence of the session.
The head now shows the retail form (the guard cmp + the loop-top re-read +
the lea), and the 0xc(%esp) spill/reload of the command pointer remains
(4 refs) — the model's allocator still spills ESI across the guard branch
where retail carries it.

The loop-rotation control emerged as the dominant structural lever: retail's
Tick does NOT rotate the command loop (the back-edge re-executes the full
head at L_00406DB0); the model's compiler rotated it (the back-edge skipped
the head, requiring the spill/reload). Both volatile reads (the guard + the
commands index) are required to pin the non-rotated form.

Remaining after this lever: the receiver keystone (EBX vs EBP, the frame
0x214 vs 0x210, the exit form) and the -24 byte gap (the model now shares
MORE than retail — the duplicated per-case exit work retail performs is not
reproduced).

## 2026-10-14 addendum 8: the branch-polarity fix — retail's loop bottom reproduced

Inverting the bottom check's polarity (`if (record.command_index < 18) goto top; return;`
with a `top:` label at the loop head) produced retail's EXACT bottom:
```
cmpl $0x12,0x45c(%ebx)   ; (retail: [ebp+45Ch])
jl   0x406db0            ; the hot path jumps BACK to the head (retail: identical)
pop  %edi / pop %esi / pop %ebx   ; the exit falls through
```
The tail-duplicated head copy at the bottom is GONE — the model's back-edge
now re-executes the head like retail's. The command pointer's spill/reload
dropped from 4 refs to 2 (one store in the head + one reload after the
EnemyGrid_ScanCells call, where the call legitimately clobbers ESI).

State: 1592 bytes (12 UNDER retail's 1604), 420/421 instructions, the bottom
polarity and the head structure retail-matching. The receiver keystone
(EBX vs EBP, the frame 0x214 vs 0x210, the pop edi,esi,ebp,ebx exit form)
is the single remaining structural delta plus the -12 byte gap.

## 2026-10-14 addendum 9: the sign hoist and the final session state

The sign value's cross-call carry was spelled as Main's pressure test
requested: `const int sign = command.value_c >> 31;` before the ScanCells
call, tested after (`if (sign >= 0) goto bottom;`) — reproducing retail's
`test %ebx,%ebx` before the call / the sign test after. Result: 1596 bytes
(-8 from retail's 1604), the entry guard now jumps FORWARD on the hot path
(jl — the polarity propagated to the entry), but the receiver keystone did
not tip: still `sub esp,0x214` + receiver-in-EBX + the pop edi,esi,ebx exit.

The timer-reset tail-merge hypothesis was tested and disproved: both timer
blocks are unmerged in the model (the constants appear twice in both
binaries). The -12 gap is alignment/padding plus small encoding deltas.

FINAL SESSION STATE:
- Spawn 0x004067D0: 1476/1472 (+4), frame 0x14 ✓, one hoisted load.
- Tick 0x00406D90: 1596/1604 (-8), the retail-matching bottom polarity
  (jl back-edge), the retail-matching head, the int field stores, the
  sign carried across the ScanCells call.
The receiver keystone (EBX vs EBP, the frame 0x214 vs 0x210, the exit pop
order) is the single remaining structural delta on Tick; Spawn's residual
is the second hoisted load (the entry shape) and the register-assignment
cascade. Both require the tracer for the allocator's +0xc priority data.

## 2026-10-14 addendum 10: the tracer campaign — what works and the exact gap

The tracer was pursued through four mechanisms; the findings are concrete:

WORKS:
- winedbg NATIVE (--command "info proc"/"info share"): lists all Wine
  processes with hex Windows pids and the loaded PE modules with bases.
  Attaching by Windows pid works (the earlier failure used a stale Linux
  pid; attach needs the hex Windows pid from info proc).
- winedbg --gdb + gdb: the remote protocol works; gdb RECOGNIZES c2.dll
  as a shared library (it reports the load/unload: "Temporarily disabling
  breakpoints for unloaded shared library c2.dll"), and hardware breakpoints
  set at the PE-preferred base (0x10700000, verified in c2.dll's PE header —
  file offsets map 1:1 through .text) are re-armed at load time by gdb.
- The c2.dll decode: the tie-break at RVA 0xA9E2B (the descending +0xc /
  +0x44 list insert) was read statically from the file — no process needed.

DOES NOT WORK (the exact gap):
- The link phase under winedbg is ~1.5-2s wall (the cluster is small); the
  c2.dll load-to-unload window inside the /LTCG phase is well under 1s.
  Every attach mechanism missed it: the winedbg attach/detach poll cycle
  costs ~0.3-0.5s per cycle; the /proc maps scan shows NO file-backed
  mappings for the 32-bit DLLs (new-WOW64 maps them anonymously — no
  'c2.dll' path appears); the direct link re-runs hit stale-cluster-dir
  argument issues (the probe regenerates the dir per run).
- The breakpoints at 0x107A991C/0x107A997E were armed correctly through a
  full compile and a full link and NEVER HIT — those addresses (from the
  joystick agent's session) do not execute in this environment's runs,
  despite being valid c2.dll code. They may be hit only under specific
  allocator states (or the joystick addresses were from a different
  c2.dll build than this toolkit's — the toolkit is the same, but their
  trace was of a /GL compile, where the backend may exercise different
  entry paths than the /LTCG link).

The working recipe for the next session: launch the probe, get the link's
Windows pid from `wine winedbg --command "info proc"` (verified: the link
appears at ~0.87s), attach winedbg NATIVE to that pid (verified working),
and poll `info share` in-process (a single persistent attach — the command
loop stops the process, so use `break` BEFORE the c2 load by breaking on
the LoadLibrary path or accept the sub-second window with a fast script).
Alternatively trace the COMPILE phase (the allocator may also run there
for non-/GL TUs) with a big multi-file compile to widen the window.

## 2026-10-14 addendum 11: THE TRACER WORKS — the receiver-keystone mechanism captured

The window-widening solved it: 60 unity copies of the tick source compiled in
ONE cl invocation (~7.4s) widened the c2 window enough for the gdb+winedbg--gdb
tracer to capture 4000 events; then the REAL tick source's single compile gave
2486 events (the full priority walk). The breakpoint addresses
(0x107A991C/0x107A997E) are CONFIRMED on the compile path — the earlier misses
were the sub-second single-TU window racing the breakpoint arming.

The candidate-struct decode at the breakpoint (c2 RVA 0xA991C is the
live-range bookkeeping: [a+0xc] += [a+0x18] * edx, the priority accumulator):
- num ([a+0x1c]) = the variable id (not the register)
- f18 ([a+0x18]) = the per-event increment (weight × loop factor)
- w ([a+0x40]) = the candidate's loop-depth weight
- prio ([a+0xc]) = the running priority
- ADD = priority grants; SUB = the per-block decay

THE MECHANISM (the two whole-function candidates):
- var 31 (w=12 — the deeper/loop-weighted candidate = the RECEIVER): 88 SUB
  decays vs 15 ADDs, ending at prio=-182 → it LOSES the register race.
- var 40 (w=8 — the shallower candidate = the ALIGNED FRAME POINTER): 37 SUBs
  + a final ADD with w=144 prio=+360 — a huge epilogue grant (the `mov ebp,esp`
  frame restore USE) → it WINS and holds EBP.
Retail's compiler SPILLS the aligned frame pointer to the stack at entry (the
second `push ebp`): the frame value lives in a stack slot, the register
candidate DIES (no exit grant), and the receiver — despite its faster decay —
takes EBP. My model's lower entry pressure leaves the frame in a register,
whose epilogue use grants +360 and displaces the receiver to EBX.

THE SPELLING TARGET (now precise): raise the entry pressure so the compiler
spills the aligned frame pointer at entry (retail's `push ebp` form) — the
exit's frame use then reads the stack, no grant happens, and the receiver
takes EBP. The observable: the exit form `pop edi,esi,ebp,ebx; mov esp,ebp`
(the spill form) instead of `pop edi,esi,ebx; mov ebp,esp`.

## 2026-10-14 addendum 12: the grant-stability experiments (all null)

Three spellings aimed at the var-40 frame grant all left the allocator's
scoring byte-identical (var 31: 3260 ADD-grants → prio -182; var 40: 2518 →
the +360 epilogue grant):
- an early 5th entry value (the pre-computed commands base) — folded into
  the loop-head lea;
- the commands reads routed through the base local — the compiler
  propagates the const (it equals receiver+0x464);
- the receiver-probe delta test — the scores are config-level, not
  use-count-level.

The mechanism is now fully mapped: the frame's EBP residency is fixed by
the `mov ebp,esp` prologue convention; the allocator's second-push spill
(the retail form) fires when it judges the frame not worth a register —
in retail's IL the judgment differed, in mine it doesn't, and no source
spelling tested moved it. The var-40/var-31 grant data from the tracer is
the definitive map of the remaining delta.

FINAL PAIR STATE: Spawn 1476/1472 (+4, frame 0x14, one hoist); Tick
1596/1604 (-8, the retail-matching bottom polarity, the int stores, the
sign carry, 420/421 instructions). The keystone residual is the allocator's
frame-worth judgment, observable but not source-controllable with the
spellings tested.

## 2026-10-14 addendum 13: the entry-pressure tests and the buffer hoist

- The entry-scoped case reads (the 0x400000 case's opening values) were DCE'd
  as dead code — no pressure change.
- The pattern buffer hoisted to entry scope (one allocation shared by the
  0x400000 case instead of a per-case frame slot): Tick 1596→1592 (-4) — the
  frame slot merged. The prologue is unchanged (still no spill form).
- The record spelled as a pointer local: folded into the receiver (same
  value), 1592 unchanged.

Retail's EBX census (from the retail disassembly): EBX is NOT a fifth
whole-function value — it carries the SIGN (and $0x80000000; test %ebx,%ebx)
across the ScanCells call, case-local. Retail's register budget: ebp=receiver,
esi=command, edi=zero, ebx=sign(case-local), frame=SPILLED. The spill fired
with only two whole-function candidates — the receiver's priority at its
defining copy must have exceeded the frame's in retail's IL. My tracer shows
both at 48 at the copy with the frame later recharged +360 at its epilogue
use. The initial-grant weight (w=12 vs the frame's w=8) already favors the
receiver; the missing differential is inside C2's assignment order, which the
spellings tested do not reach.

STATE: Tick 1592/1604 (-12), Spawn 1476/1472 (+4).

## 2026-10-14 addendum 14: the creation-order lever, the buffer write, and the link-trace boundary

The frame-first write (pattern_words[0] = 0 before the guard) moved the
prologue's schedule (the receiver copy now sits AFTER the push esi — the
eager-saves shape emerging) and merged 28 more bytes (1592→1564). The
compile-side grants are invariant (var 31 → -182, var 40 → +360) — the
scoring is an IL property, fixed before allocation.

The link-phase trace attempt: the direct link under winedbg --gdb ran ONCE
for 11.3s (the window exists) but the first stop reads pc=0 through the
remote stub and subsequent runs die at launch (~2.2s, "The program is not
being run") — link.exe's /LTCG backend appears to run in a child process
the debugger session loses, or the killed first run poisoned the state.

THE STRUCTURAL BOUNDARY: the compile-side trace measures the per-function
priority data correctly (the same c2, the same struct), but the receiver-
in-EBP decision happens at the LINK, where the anchors are INLINED into
Tick's IL — the link's Tick body has more pressure than the compile-side
IL shows. The compile-tuned spellings cannot observe the link-side IL.

FINAL STATE: Spawn 1476/1472 (+4); Tick 1564/1604 (-40 — the buffer write
+ the hoist + the polarity + the rotation pins). The prologue now shows the
emerging eager-saves order. The keystone (receiver-in-EBP) requires the
link-phase IL — tracer-blocked by the child-process flake, or reachable by
reproducing the anchor-inlined IL at compile time (manually inlining the
anchors into the tick source and re-tracing — the next session's opening
move).

## 2026-10-14 addendum 15: the unity-inlined-TU attempt (blocked) and the closing state

The link-side IL reproduction attempt: a single TU with the anchors first,
then the spawn, then the tick — so /O2's inliner sees the anchor bodies
before their call sites (reproducing what the /LTCG link does). Three
rounds of assembly fixes (the tick-source duplicate in additional_sources
— the manifest lists the selected function as its own context; the
struct-redefinition dedup; the helper dedup) hit a hard blocker: the
recovery headers DECLARE functions with type modifiers that conflict with
the source definitions when both appear in one TU (SpawnPatternCell_004067d0
declared __stdcall in enemy_grid_scan_004073e0.hpp vs the source's
declaration). The unity TU needs the header contracts aligned — a
structural cleanup beyond this session's scope.

The manifest fact discovered: additional_sources contains the SELECTED
function's own source (projectile_command_runtime.cpp lists itself as
context) — the schema-2 mechanism; the unity assembler must dedupe it.

CLOSING STATE: Spawn 1476/1472 (+4); Tick 1564/1604 (-40) with the
retail-matching bottom polarity, the int stores, the sign carry, the
prewritten shared pattern buffer, and the emerging eager-saves prologue.
The tracer (gdb + winedbg --gdb + the window widening) and the full
priority-walk mechanism are delivered and reusable; the link-phase IL
remains observable only at the link (the child-process flake) or via the
unity TU after the header-contract cleanup.

## 2026-10-14 addendum 16: the unity TU compiles — the inlined-IL invariance

The header-contract alignment (enemy_grid_scan_004073e0.hpp's
SpawnPatternCell declaration aligned to the source's form — the __stdcall
qualifier removed; the header copy is manifest-local and the source
definitions are what compile) unblocked the unity TU: it compiles clean
(rc=0, 12641 bytes after the struct dedup).

The traced unity compile (the anchors inlined before their call sites —
the link-side IL proxy): 2486 events, and the priority structure is
IDENTICAL to the plain tick trace (var 31 → -182, var 40 → +360, the same
grant pattern). THE ANCHOR INLINING DOES NOT CHANGE THE PRIORITY WALK —
the frame-worth judgment is invariant under the inlined IL.

Closing characterization: the receiver-vs-frame decision in retail's link
was made from the same priority data my compile shows; the divergence is
in C2's frame-spill heuristic interacting with the and-alignment epilogue
form — not in the priority data, not in the block layout, not in the
inlined-IL pressure. The heuristic is the last unexplored internal; the
tracer data and the recipes are delivered for whoever attacks it with a
c2-level tool.

FINAL SESSION STATE: Spawn 1476/1472 (+4); Tick 1564/1604 (-40) with the
retail-matching structure everywhere except the receiver register and the
frame slot.

## Continuation recipe index (complete)

1. **Iteration loop**: scratch/projectile/{spawn_golf.cpp,tick_golf.cpp} are
   the working models; `cp tick_golf.cpp scratch/projectile/msvc/src/game/
   projectile_command_runtime.cpp` (spawn likewise) then
   `PYTHONPATH=. python3 matching2/tools/matching/probe.py --project
   scratch/projectile/msvc --source src/game/<src>.cpp --output
   matching2/build/probe-spawn`. NOTE: sync.sh does NOT copy tick_golf.cpp —
   the tick sync is manual.
2. **Compile tracer** (works, validated): launch
   `winedbg --gdb --no-start cl.exe <args>`; parse the port from stdout;
   run the gdb script (/tmp/gdb_single2.gdb.py is the working template:
   hbreak *0x107a991c / *0x107a997e, continue-loop, read
   [a+0x1c]=num [a+0x18]=f18 [a+0x40]=w [a+0xc]=prio). For short compiles
   widen the window: N unity copies of the source compiled in ONE cl
   invocation (~7.4s for 60) — /tmp/gdb_bulk.gdb.py.
3. **Link tracer** (blocked): the direct link under winedbg --gdb ran once
   for 11.3s then died consistently — the /LTCG backend appears to fork a
   child the session loses. The batch-file route also dies. Retry with a
   fresh process state or a child-following debugger.
4. **Unity-inlined TU** (the link-side IL proxy at compile time): the
   assembler dedup rules — (a) remove the selected function's own source
   from additional_sources (the manifest lists it as its own context);
   (b) skip duplicate struct/class blocks; (c) skip the duplicate
   SpawnCommand_AimAngle helper; (d) hoist all #includes to the top. The
   header-contract alignment: enemy_grid_scan_004073e0.hpp's
   SpawnPatternCell declaration must match the source's form (no __stdcall) —
   the manifest-local header copies are editable.
5. **The proven spelling levers** (in effect in the current models): the
   volatile guard + the volatile commands-index read (the rotation pins),
   the bottom-check polarity inversion (goto top), the goto-bottom case
   exits, the prewritten shared pattern buffer, the entry-copy lever on
   Spawn, the int field types in the header.

## Runtime fix, 2026-10-14: StartScript call convention

The accepted model crashed the default build ~5,766 frames into replay `th10_05`
(Stage 1): access violation at 0x0043E71D in the script loader, reached from
the model's command 0x4000 through the installed retail StartScript 0x00404F30.
Retail passes the script pointer (`data_00474170[value_c] + value_d`) in EAX;
the model passed it in EDI and left the manager pointer `[0x004776F0]` in EAX.

Cause: the cluster's stand-in `layout/ltcg/projectile_spawn_runtime/start_script.cpp`
calls a bodiless `LoadScript_0043e710`, so the pass parked the script in EDI and
made EDI the stand-in's private register parameter. The layout listed the hunk
as a reviewed difference. Fix: the Tick cluster now uses the spawner's proven
context `equivalent/game/context/projectile_spawn_cell_start_script_00404f30.cpp`,
which compiles the real loader (index in EBX), so the starter takes the index
in EAX like retail. The call site is now identical to retail; the model went
from 302 to 323 of 337 identical instructions (17 recorded differences, one
new: two independent stores to the scratch vector in the other order).

`tools/matching/callsite_abi.py` (`make abi-check`) now checks every model's
calls into retail code for this class of mismatch.
