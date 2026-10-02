# Pause/result choice update at `0x00422C80`

The complete 1,360-byte pause/result choice updater is recovered as ordinary
C++ in `src/game/pause_choice_update_00422c80.cpp`. The frozen native probe is
byte-identical to retail, including the switch table and alignment bytes:

`40afabc287174a74c3fd3c28c318f71c36d73d173096dd011f30fc37c16e3c49`

The fresh maintained-source probe passes exactly, and the incremental normal
build produces the literal retail executable: 487,936 bytes, SHA256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
It reuses 1,604 unchanged units and compiles six changed units. The independent
full native PE/MAP comparisons and current compiler-input hashes are recorded
in `matching2/build/experiments/pause_choice_real_graph_00422c80_20261002/whole_verification.json`.

## Actual boundary and behavior

The verified updater at `0x004223F0` pushes its state pointer in ESI at
`0x00422442` and calls `0x00422C80` at `0x00422443`; retail bytes are
`56 E8 38 08 00 00`. The callee reads that sole stack pointer and returns with
`RET 4`. Incoming ECX is unused. Its public symbol is
`_PauseMenu_Update_00422c80@4`; the old inferred two-input `thiscall` description
does not describe the actual boundary.

The source retains all five phases: opening the menu after 10 frames;
navigation, confirmation and shortcut handling; completing transitions after
12 frames; opening the confirmation view at frame 20 and enabling its input at
frame 30; and restoring the saved cursor or completing the choice after 20
frames. Original key masks, sound requests, animation child scripts, handle
ordering, timer resets, replay-dependent choices, and global writes remain.
Assertions establish the timer at +0x10, cursor at +0x24, background handle at
+0x1D4, and saved speed at +0x2C0. The +0xF4 word is the cursor wrapping flag.

The scoped cursor's inline upper clamp uses
`selected >= item_count ? item_count - 1 : selected` when the count is nonzero,
and stores the selected value directly when the count is zero. This inverse
conditional preserves the original upper-clamp behavior and naturally emits
the retail branch order. It adds no work, input, or pressure operation.

The real stop-frame argument is a signed 16-bit value. A `short` formal and the
phase-five local `short frame` preserve the low-word frame arithmetic and
restore the retail sign extension after popping cursor history. The complete
frame-setting helper remains exact; its stores use the same 16-bit value.

## Complete native graph and evidence

`final_probe.json` records strict equality with zero failures.
`final_receipt.json` independently compares entire native compiler
contributions against retail. Review also rechecked every compiler input hash,
the native MAP contributions, and the raw native PE bytes.

All 14 complete helpers are exact at their real addresses: timer setter
405410/57; stop-frame-one 409E50/65; input mode 40AC90/37; input mask 40ACE0/33;
stop-frame-six 4243F0/65; sound queue 43DC90/123; resource registrar 43E460/104;
animation lookup 4491C0/73; transition flags 4492A0/66; variable stop frame
449470/65; child lookup 4497D0/70; cursor push 44BE20/66, pop 44BE70/47, and
advance 44BEA0/128. These helpers are unselected and receive zero new credit.
Native LTCG derives their private register contracts from genuine arguments
and complete bodies, including the real aggregate-result pointer.

The independent linker entry is the actual AppPresent scheduler callback at
`0x004200C0`, whose complete six-byte return-one body is also exact. Its actual
registration pushes `0x004200C0` at `0x004204EF`. It supplies no call edge or
synthetic live input to the separately rooted public updater.

Unpause at `0x00422C30` is a complete ordinary 74-byte helper in this graph. It
differs in 12 bytes, beginning at `0x00422C63`, because its animation clearing
and saved-speed accesses use ordinary stores and loads. It remains unselected;
its maintained owner is unchanged and it earns zero recovery credit.

The native pipeline changes no instruction bytes or address operands, uses no
masked bytes, and does not use reference bytes to build the candidate. The
graph contains no inline assembly, dummy ABI slots, artificial volatile
accesses, barriers, or fabricated call edges. Only the 1,360-byte owner at
`0x00422C80` changes from assembly to semantic source; the retained
`previous_record` records its former owner. The credited gain is **1,360 bytes**
with both the maintained-source and whole-EXE gates passed.
