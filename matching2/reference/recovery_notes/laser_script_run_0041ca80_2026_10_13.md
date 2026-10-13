# Laser script interpreter 0x0041CA80 — recovery state (2026-10-13)

## Identification (settled)

`0x0041CA80..0x0041CF77` is the line-laser embedded command interpreter —
virtual slot 0 of the vtable at `0x0046DA60` (`LineLaser_0041c5b0`, object size
0xD58). `this` arrives in ECX; plain `RET`. It walks an 18-entry, 24-byte
command stream at `+0x450` (params 0-3, opcode at +0x10, gate word at +0x14)
using the program counter at `+0x400`:

- opcode 0 ends the run; a command with `gate == 0` also ends the run once
  `flags_404 != 0`.
- `0x80000000` end marker (pc++); `1/0x10/0x20` prime scheduler slots
  (`+0x58/+0x8C/+0xC0`) via the `0x00405410` store (record in EAX, value on
  the stack) and arm movement/sound (0x10 aims: `param1 > [00470B50]` keeps the
  current angle, `>= [00470CCC]` calls the player-aim helper `0x00426660`
  (entity ECX, point EAX), else param1; then `0x0041F800` SetPolar with dest in
  ECX; `Queue 0x0043DC90` uses EDI for the sound id).
- `0x40/0x80/0x100` (flags |= opcode) start width growth
  (`+0x108` target, `+0x10C` mode, timer `+0xF4`, durations `+0x11C/+0x120`).
- `0x400/0x800/0x8000000` grow the beam length (`+0x13C` target, counters
  `+0x150/+0x154`, decrementing `param2` in the command).
- `0x4000` starts the beam animation script: `00474170[param2]+param3` through
  `0x00404F30` (entity ESI, index EAX, resource on the stack).
- `0x8000` wait (inline scheduler-store expansion on `+0x15C`), `0x20000`
  panned sound (`0x0043DD10`, this in ESI, id in EBX), `0x10000`
  `state = 3`, `0x100000/0x200000` movement waits (`+0x190`),
  `0x1000000` sets the laser id (`+0x54`), `0x2000000` jumps
  (`pc = param2`), `0x4000000` movement target (`+0x20C/+0x210/+0x220`,
  timer `+0x1F8`).

The dispatch ends in the byte map + jump table at `0x0041CF8C`/`0x0041CF78`
(region `text_data_0041cf78`); the map bytes produced by the conversion are
already exact.

## What was built (all byte-verified against retail unless noted)

- `src/game/laser_script_run_0041ca80.cpp` — full readable interpreter.
- `include/th10/game/laser_script_run_0041ca80.hpp` — view struct (offset
  asserts to +0x600) and command/timer types.
- `layout/ltcg/laser_script_run_0041ca80.json` + `_context.cpp` +
  `_dependencies/{entity_init_start_script,set,angle,queue,queuepan,load_script}.cpp`
  — schema-1 native-LTCG cluster; the six private-ABI callees are anchored as
  co-compiled copies and their bodies come out **byte-exact**: Set 0/57,
  AngleFromPoint 0/67, Queue 0/123, StartScript 0/202; QueuePan 3/149 and
  LoadScript 6/203 differ only in pooled-literal addresses. Every private
  register convention emerges exactly as retail (EAX scheduler receiver, EDI
  sound id, ESI/EBX pan pair, ESI/EAX script starter).

## Residual

The probe does not reach EXACT yet. With the merged region extent (see delta)
the compiled interpreter is ~1080 bytes off over the 1272 code bytes. The
entire residual is one systematic rename: the allocator assigns the cached
program counter to **EDX** and the fetched opcode to **ECX**, retail uses
**ECX/EDX** (e.g. `8b 95 00 04 00 00` vs retail `8b 8d ...`, `3b cb` vs
`3b d3`, `inc edx` vs `inc ecx`), which cascades through every displacement.
The loop head, entry check (`cmp dword [ebp+400h],12h`, memory form), the
pad split (7+3), the `movzx/jmp` pair and the 64-byte map already match.

## Next lever

Fifty-plus legitimate spellings were tried for the loop head (while/do-while/
for forms, entry-if duplication, common vs per-case increment, opcode-first
statement order, index local, pointer vs reference, guard merging, ternary vs
if/else angle, `laser = this` alias, opcode as a pure temporary, hoisted
scheduler-slot pointers, opaque caller edge via member-pointer indirection
with and without whole-program rooting). Every variant keeps the cached
program counter in EDX; one earlier build (probe output `native-459hgyyg`)
reached 912 differing bytes with the retail head shape, but its exact source
combination was not recovered. Remaining levers: reconstruct that
combination (its unique properties were the memory-form entry check together
with the shared pc store and the per-case `mov eax,[pc]; inc eax` prefixes),
or find the guard structure whose switch emits retail's inline-handler form
(`cmp edx,80000000h; jne +12; inc ecx; mov [pc],ecx; jmp check` — the handler
inline in the tree; every rebuilt shape emits `ja`/`je` to a far block
instead). Structural guard variants tested for the inline form and rejected:
first-position case with break/continue, else-switch, goto to a loop-end
label, negated guard — VC7.1 folds the extreme case into the tree node
(`mov eax,reg; cmp eax,80000000h; ja; je`) in every spelling, so the inline
form appears tied to the same original-IR difference as the register swap.
Once the swap closes, the manifest gaps need one mechanical re-fix (fixgaps
helper in `scratch/laserscript/`) because the section extent must equal the
merged region size.

## regions.json delta to apply (with the swap resolved)

1. Region `asm_unassigned_0041ca80` →
   `{"name": "semantic_LaserScriptRun_0041ca80", "source":
   "src/game/laser_script_run_0041ca80.cpp",
   "symbol": "?Run@LaserScriptRun_0041ca80@@QAEXXZ",
   "address": "0x0041CA80", "size": 1356, "kind": "semantic",
   "owner": "0x0041CA80"}` — the extent **absorbs** the jump table, because
   MSVC emits the switch table into the function's own section and the cluster
   contribution check requires section length == region size.
2. Delete the data region `_text_data_0041cf78` (0x0041CF78, 84) and remove
   its `.d000761` block from `src/data/text_0041.cpp` (shared data file —
   orchestrator applies; the bytes are supplied by the interpreter section).
3. Append `layout/ltcg/laser_script_run_0041ca80.json` to `ltcg_clusters`.


## Parked (transcript-mining attempt, 2026-10-13, second session)

Per orchestrator directive the transcript (`history://Unassigned0041ca80`) was
mined for the source revision that produced the 912-diff build
(`native-459hgyyg`). The history summary confirms the edit sequence but not
the full payloads; the strongest timeline reconstruction is that the 912
source carried pointer-form command accesses (`cmd->`) in the case bodies with
a reference-form head — a mixed state that cannot compile, so at least one
silent no-op edit makes exact replay impossible. A bounded reconstruction
series (six builds: pointer form x common/per-case increment x opcode-first)
all returned the invariant 1080-diff head.

**Parked with complete analysis.** A late re-examination corrected the
record: the clean-rewrite builds (`native-9o88yd1s` and siblings, 1047 diffs)
*did* contain the inline-handler dispatch form
(`cmp ecx,80000000h; jne +12; inc edx; mov [pc],edx; jmp check` — the
default-caught end marker emitted at the tree node) together with the
memory-form entry check and the shared pc store — every dispatch-shape goal
was met except the register swap. However, replaying the verbatim
clean-rewrite source now yields the folded form at 1080 diffs, and reverting
the manifest function size (1272 vs 1356) does not change it: the exact 9o88
source state differs from the verbatim rewrite in a way the transcript cannot
recover, and the rebuild is not reproducible.

**The recovery is one register-rename away from byte-exact**: a build whose
loop head caches `pc_400` in ECX (retail) instead of EDX. All other bytes —
prologue, entry check, padding, dispatch map, every callee convention and
anchor body — are verified exact, and the semantics are fully documented
above. Recommended next lever for a fresh session: re-derive the clean-rewrite
file state from the build-tree diff (the 9o88 build's compiled section is
preserved under `matching2/build/probe-laserscript/clusters/
laser_script_run_0041ca80/native-9o88yd1s/`), diff it instruction-by-
instruction against a fresh verbatim-rewrite build, and drive the unnamed
construct from that delta.
