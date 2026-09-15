# 0x004127A0 — spell-timer slot advance: reconstructed model at 0.87 shape match

2026-09-16. The 593-byte region registered as
`semantic_SpellTimer_AdvanceSlots_004127a0` is still inline assembly in
`src/game/spell_timer.cpp` (the manifest entry was promoted without the source
following it, see `LEDGER_HANDOFF.md`). This note records a complete behavioral
reconstruction and the measured residual so the next attempt does not start from
the previous wave's weaker model.

## Verified facts

- Entry `int __thiscall AdvanceSlots(void* this)`; `this` in ECX, no arguments,
  plain `ret`, result in EAX. The index tests compile as **unsigned** (`cmp r,8`
  / `jb`), the slot-id tests as **signed** (`cmp [slot],0` / `jge`, `jl`).
- Host layout: `EclFrameTimer` at `+0x1158` (`previous +0x1158`, `current
  +0x115C`, `elapsed +0x1160`, `speed +0x1164 = &flt_476F78`, `flags +0x1168`),
  `active_id +0x23FC`, `last_delta +0x2404`, `state_flags +0x2480`, and eight
  16-byte slots at `+0x2494` (`id`, `due`, `payload`, reserved). Globals:
  `data_0047770C + 0x9EC0` (seconds), `data_00474C4C` (clamped countdown),
  `data_004776F4 + 0x378C/0x3738/0x3790/0x0AD4/0x0E80/0x15D8/0x1984/0x1D30/
  0x20DC/0x2488` (stage-side flags).
- Behaviour: scan for the first armed slot (`id >= 0`); if its id is not older
  than `active_id` it is retired (`active_id = id`, `id = -1`, the timer is
  restarted with `previous = -1` and `state_flags &= ~0x10000`, returning the
  slot payload). Otherwise scan for the first slot with `id >= 0 && due > 0`,
  publish `(due - current + 59) / 60` clamped to 99 through `data_0047770C`,
  return 0 while `current < due`, then retire it, restart the timer with
  `state_flags |= 0x10000`, step `data_00474C4C` down by 3000 with a 5000 floor,
  and clear bit 1 of the eight stage flag dwords when bit 3 is clear and
  `+0x3738 >= 60` (returning the payload).

## Measured with the maintained compile path

A member-function reconstruction of the model above compiles to 593–595 bytes
(retail 593) with a **register-normalised instruction-shape similarity of 0.87**
(`python3 matching2/tools/waves/shape.py --source src/game/spell_timer.cpp
--symbol <candidate> --address 0x4127A0 --size 593`)
(145 instructions against retail's 147; the previous wave's generator in
`matching2/build/waves/results2/Y07/variants.py` scores 0.708, and its best
bytes-vs-retail result is 476 differing of 593). The residual is scheduling, not
structure:

- an extra `push`/`pop` of the fourth saved register and its position;
- a redundant loop-bound re-test (`cmp r,8; jae`) on the candidate loop;
- indexed `[base + index*1 + disp]` versus retail's hoisted `shl 4` + `[base+disp]`
  for the slot walk;
- `state_flags |= 0x10000` emitted as load/or/store instead of retail's in-place
  `or DWORD PTR [rcx+2480h],10000h`, and the eight `&= ~2` clears emitted with a
  register mask where retail keeps the mask in ESI;
- the allocator's register roles: retail runs zero→EBP, loop-1 index→EAX,
  loop-2 index→EBX, slot pointer→EAX, block base→EDI; the reconstruction runs
  zero→EBX, indices→EAX, pointer→EDX.

## Next experiments

1. Find the source form that keeps the 0x10000 update in place (single use of
   `state_flags` in that statement) while the clears keep a shared mask register.
2. Tie the two loop indices to separate registers by keeping the first index live
   across the second loop (retail's block layout puts the found-block after the
   loop head, which is what forces `ebx` for the second index).
3. Only then chase the prologue `push` order; LTCG is not a lever here (the ABI is
   already the C++ default, see `ecl_name_table_00450220_allocator_residual.md`).
