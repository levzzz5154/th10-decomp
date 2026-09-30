# Complete replay snapshot caller and pool append experiment

## Current result

The maintained routines `0x0042A450` (582 bytes) and `0x0042AA50` (139 bytes)
remain assembly. This experiment retains a complete, readable C++ model of the
real snapshot caller and the entire allocation/constructor/list-append body.
The final original-extent production probe rejects the snapshot: native LTCG
emits 581 bytes rather than the required 582. This is not a one-byte comparison
residual; an independent diagnostic comparison finds 140 differing bytes within
the overlapping 581-byte range, first at `0x0042A5A8`.

The preceding 344 bytes, including the entire recording branch and the start
of the playback-mode test, match exactly. The remaining differences are in the
playback branch's index and pointer lifetimes, register allocation, and loop
padding. No caller portion is selected or promoted as a partial recovery.

The allocator is measured separately by the same normal production probe with
the *entire* 581-byte real caller model as an unselected, complete contribution.
Its 139-byte body retains exactly the same six-byte store/LEA scheduling
residual as the previous forwarding-context experiment. Using a genuine full
caller did not close that residual.

The helper recovered during this work, `0x00424D90`, has a separate complete
273-byte exact normal probe and explicit promotion handoff. See
`pause_reset_00424d90_native_2026-09-28.md`. Its recovery is independent of these
unmatched caller/allocator bodies.

## Canonical artifacts

All scratch artifacts are under
`matching2/build/experiments/replay_pool_full_caller_2026_09_28`.

- `msvc/src/game/slot_snapshot.cpp`: complete snapshot source, expected 582 bytes;
  its selected original-extent gate is `probe_final.json`.
- `msvc/src/game/linked_pool_append.cpp`: complete 139-byte allocation/append
  model. Its exact-required target is included in the original two-body layout.
- `msvc/include/th10/game/replay_snapshot_0042a450.hpp`: typed runtime, stage,
  player/gauge and helper views with compile-time size/offset checks.
- `msvc/include/th10/game/replay_pool_append_0042aa50.hpp`: typed 3,600-record
  input/byte buffers, moving cursors and embedded intrusive link.
- `msvc/layout/ltcg/replay_pool_full_caller.json` and matching context: full
  selected 582/139-byte declarations with complete real dependency bodies.
- `allocator_probe_msvc`: diagnostic project that preserves the entire caller
  as an unselected 581-byte contribution and selects the full 139-byte allocator.
  `allocator_probe_final.json` is its terminal normal comparison; its empty
  `allocator_proposal.json` confirms that it proposes no recovery.
- `full_caller_measured_residual.json`: final extents, overlap-only diagnostic
  differences, native/oracle hashes, all retained input hashes, and invariants.
- `full_model_dependency_comparison.json`: independent whole-body checks for
  all four genuine dependency models in the real-caller native PE.
- `full_caller_variant_results.json`: bounded original-extent probe progression;
  `snapshot_final_actual.asm` and `snapshot_final_expected.asm` retain listings.

All canonical retained input hashes were checked after the last declaration
variant was rejected and the measured model restored. No maintained source,
header, manifest, or layout was edited by this experiment.

## Complete source and genuine dependencies

Fresh Ghidra MCP decompilation and complete disassembly of `th10.exe` are
retained for the caller, allocator, list release, gauge publish and pause reset.
The snapshot has the private runtime-in-EBX entry and plain RET. It marks three
scheduler task flag words, then either captures the recording stage or restores
the playback stage. Both branches and the common frame-count reset are present.

The recording branch clears and recreates the stage's pool, writes the seven
observed record fields, copies 264 bytes of player state, transposes all eight
words of each of four gauge records into the four pair banks, and saves the
last observed record fields and special-mode value. The playback branch republishes the gauge counters,
restores the 264-byte state block and special mode, calls the genuine public
stack-argument `0x00426F70` entry, restores all four eight-word gauge records,
handles character/shot combination 5, clears four dirty flags, and invokes the
complete pause reset before clearing the runtime frame count.

The owner view includes eight stage record pointers, eight twelve-byte list
heads beginning at +0x3C, the current link at +0x9C, eight playback descriptors
with stride 0x24, the frame count at +0x1C8, and active stage at +0x1D0. The
0x1C4-byte stage record's 264-byte block begins at +0x2C and its four banks of
four eight-byte pairs begin at +0x134. Live gauge records have stride 0x98.

Native LTCG uses complete C++ models for the private dependencies. The final
real-caller native PE independently matches every byte of these contributions:

| Routine | Extent | SHA-256 |
| --- | ---: | --- |
| Set active animation count, 0x00413790 | 77 | b422a962a6c53e3f252fe11ecd309708b16473c499e7b15085279aa6311ef39b |
| Pause reset, 0x00424D90 | 273 | a046f949437cc60a16940acb18b4015250d4c2403ff3b222de92be972a82b94f |
| Gauge publish, 0x00428E10 | 83 | 55a90ef9754346b359ca3dbb0f240fc4fd7745d115426ea249a460703f5a63ac |
| Indexed list release, 0x0042AB20 | 93 | 84a48e66ece6617e49b9afd6239363056cb10f063279a5ccade7a4a9dcd6e82f |

These are unselected dependencies in this caller experiment and add no recovered
bytes here. There is no abbreviated caller or register-only substitute. The
ordinary public stdcall `0x00426F70` entry remains an opaque fixed-address
external; its genuine stack argument and RET4 are verified by disassembly. The
pause helper's registry call is a legal public fastcall whose ECX input is
ignored, whose context is in EDX, and whose ID is one stack word followed by
RET4. The separately promoted pause recovery has its own proof and review.

## Residual and next lever

The first complete model emitted 566 bytes. Explicit memory-order boundaries
prevented store/load scheduling changes. Volatile views preserve the observed
per-iteration character/shot reads. The stored singleton address is represented
as a 32-bit word and cast into the typed player view; the canonical version
preserves explicit repeated volatile address reads. The expanded mode expression
retains the observed `shot + character * 2`, then addition of `character`.
These changes produce the 581-byte model and exact recording branch. Genuine
member/free gauge declarations and argument-order variants were bounded and
retained; none passed the original 582-byte gate.

The next concrete caller lever is the playback branch's original-player pointer
lifetime across the full 83-byte gauge publish model and the stage-index lifetime
before that call. Retail holds the original player in EDI, reloads the global
into EAX after the call, and uses EDI for the block-copy destination. The model
still lets the backend retain the original pointer in EAX and use another
register for the explicit singleton reload. Its loop register choice and
alignment also differ. Keep the complete recording/playback source while
refining those aliases and caller/callee declarations.

For the allocator, the remaining lever is still constructor zero/cursor
scheduling: retail stores the first cursor before computing the second buffer
address, whereas the model hoists that LEA ahead of the store. Its full 139-byte
normal comparison proves the private ESI selector, stack owner, returned link
in EAX, and RET4; there is no ABI-impossibility conclusion.

Both terminal experiments reject promotion. Their reports prove no instruction
byte rewrites, no address operand rewrites, no masks, and no oracle bytes used
for building. Comparison uses the oracle only after freshly compiling the C++.
