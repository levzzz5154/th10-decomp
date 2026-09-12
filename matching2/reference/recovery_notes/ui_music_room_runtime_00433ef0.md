# UI music-room runtime: `0x00433EF0`

## Result

The 2,796-byte region remains the exact naked-assembly implementation in
`src/game/ui_final_runtime.cpp`. Neither complete-control-flow compiler probe
passed the extent-and-byte gate, so no semantic production source, LTCG
layout/context, or proposal was retained. `regions.json` was not edited.

The final focused maintained-source probe is exact at `0x00433EF0` for all
2,796 bytes. Retail allocates a `0x1C` local frame, saves
`EBP/EBX/ESI/EDI`, reads the room from the sole stack argument, returns zero
with `ret 4`, and owns the four-entry phase jump table in the 18 bytes after
the return.

## Recovered state/update flow

This is the complete music-room update handler dispatched by the title-menu
runtime at `0x0042CDF0` (case `0x0E`). The caller keeps the room in `EBX`,
pushes it, and calls `0x00433EF0`; it does not materialize an ordinary C++
`this` argument.

The room fields used by retail include phase `+0x20`, selection `+0x24`, old
selection `+0x28`, track count `+0x2C`, shared timer `+0x2B4`, timer reset
state `+0x2B0..+0x2C0`, row handles `+0x614`, eight preview-frame handles
`+0x664`, preview cursor/selection/armed fields `+0x68C..+0x694`, parsed
titles at `+0x698`, comments at `+0xE98`, eight 66-byte text rows per track
at `+0x16D8`, scroll origin `+0x58D8`, and the owned file buffer at
`+0x5AAC`.

- Phase 0, on timer 1, seeds six rows and selection zero, validates or
  installs animation slots `0x5F` and `0x67`, loads `musiccmt.txt`, and parses
  records beginning with `@`. Each record contains a 64-byte title, a 66-byte
  comment, and eight 66-byte preview lines. It creates preview animations
  `0x27..0x2E` and progressively creates two track-row animations per frame,
  beginning at script `0xAD`, drawing either the track title or locked text,
  setting visibility for the ten-row viewport, selection depth, and a
  four-frame position transition. Timer 10 advances to phase 1 and resets the
  shared timer state.
- Phase 1 reveals one of the eight preview-frame lines every other timer tick.
  Played tracks use the parsed row text in white; locked tracks can use the
  fixed preview table in color `0x8080FF`. After timer 4 it requests timer
  target/phase 2.
- Phase 2 continues the every-other-frame preview reveal, snapshots the old
  selection, and applies wrapped up/down navigation through exact
  `MenuCursor::Advance`. A change queues sound 12, adjusts the ten-row scroll
  window, updates every live row's visibility/depth/position, and clears the
  preview-armed latch.
- Confirm (`input & 0x1001`) hides the eight preview frames at depth 3, resets
  the preview cursor and timer, and either arms a locked track through the
  `dummy` resource modes or plays the selected title, marks the played-table
  byte, and selects resource mode 2. Cancel (`input & 0x0A`) frees the loaded
  text, pops menu history, stops row animation trees, hides preview frames,
  queues sound 11, and enters phase 3.
- Phase 3 waits through timer 10, clears animation slots `0x67` and `0x5F`,
  dispatches frame/depth 8 to slots `0x5A` and `0x5B`, stops the fallback
  animation tree, disables the timer owner, restores `bgm/th10_02.wav` and
  the BGM state, then pops menu history.

The control flow and offsets are grounded in the complete Ghidra body ranges
`0x00433EF0..0x0043408C` and `0x00434090..0x004349C9`, retail call-site
disassembly, and the archived behaviorally named `UpdateMusicRoom` model.

## Compiler probes and mismatch

A disposable direct translation of the full Ghidra control flow was compiled
with MSVC 13.10.6030 using the project optimization profile.

The stack-call form emitted 2,712 bytes, 84 bytes short of retail. It matched
two leading bytes and first differed at `0x00433EF2`:

```text
retail:    83 EC 1C 55 8B 6C 24 24 8B 45 20 83 F8 03 ...
candidate: 83 EC 14 53 55 56 8B 74 24 28 8D 46 20 89 ...
```

The diagnostic fastcall form emitted 2,688 bytes. It exactly reproduced the
three-byte `sub esp,0x1C`, then first differed at `0x00433EF3`:

```text
retail:    55 8B 6C 24 24 8B 45 20 83 F8 03 ...
candidate: 53 8D 42 20 55 89 54 24 08 89 44 ...
```

This confirms that the local-frame size can be induced, but only by assigning
the room to EDX, which contradicts the real caller and changes register-save
and phase-dispatch scheduling. The stack form had 2,229 differing
non-relocation bytes across its overlap; the fastcall form had 2,208.

Several dependencies are already exact semantic C++ and were treated as
fixed evidence: animation lookup `0x004491C0`, archive load `0x0044B360`,
line skip/extract `0x004349E0`/`0x00434A20`, text transition initialization
`0x00434A80`, timer target `0x0042C620`, and menu advance/history pop
`0x0044BEA0`/`0x0044BE70`.

The remaining calls expose synthetic Ghidra `extraout_ECX` values and cannot
be expressed by ordinary external prototypes. In particular, allocation,
script initialization, and primary-back registration at
`0x00449950 -> 0x00449870 -> 0x004489D0` carry the new animation and output
handle through registers. Slot install/clear (`0x0042C670`/`0x0042C6D0`),
handle validation (`0x00449450`), row-text draw (`0x00447A50`), resource
registration (`0x0043E460`), tree stop (`0x00409E50`), and the sound/BGM
helpers remain assembly with caller-visible custom conventions.

## Next bounded cluster

Retry with the real dispatcher `0x0042CDF0` plus this handler in one native
LTCG topology, preserving `EBX` as the pushed room and the retail absence of
an incoming ECX object. The first callee slice should prove the exact
`0x00449950`/`0x00449870`/`0x004489D0` handle-return pipeline and
`0x0042C670`; then add `0x004491C0` as its existing exact read-only lookup and
recover `0x00449450`, `0x00447A50`, and `0x0042C6D0` in caller-faithful
contexts. That is the minimum cluster capable of reproducing the `0x1C`
frame, EBP-first prologue, output-handle spills, and embedded switch table.

All rejected source/object/probe artifacts were removed. Production assembly,
shared tooling, and concurrent files were preserved.
