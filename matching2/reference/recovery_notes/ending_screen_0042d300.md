# 0x0042D300 ending screen handler (recovered 2026-10-04)

`src/game/ending_screen.cpp` compiles to the retail 288 bytes (268 of code plus
the five-entry phase table) in its own cluster, `ending_screen_0042d300`.
`make` and `make EXACT=1` both pass.

## Source shapes

* The selection is made through an inlined select-and-clamp
  (`SelectItem_0042d300`). With the three arms written as separate zero stores
  the zero becomes a register candidate and stays in ESI for the whole
  function.
* The slot id goes to `Find` straight from the slot array
  (`*reinterpret_cast<RecoveryScriptId_0040bd80*>(&room->animation_slots[88])`).
  Copied into a local first it is a global register candidate instead of a
  `RegAssign` temporary, the rotation starts one step earlier and the two later
  temporaries come out as EAX/ECX where retail has ECX/EDX.

## Context

The private convention (room in EBX, `out` of 0x448D00 in EDI, the slot
installer taking the room on the stack and the index in EDI) needs both the
real caller and the real callee bodies:

* caller: the title dispatcher 0x0042CDF0
  (`layout/ltcg/ending_screen_dependencies/title_dispatcher.cpp`), reached from
  the cluster context so the linker keeps it;
* callees: the objects of the `recovery_animation_slot_frames_0042c6d0`
  cluster.

The `title_dispatch_callback_0042d2e0` cluster has simpler stand-in callees and
produces 296 bytes for the same source (room passed in EAX, `out` pushed), so
the handler is not selected there; that cluster keeps its older unselected
model.

The handle stop at 0x00409E50 is called as
`RecoveryMusicStopHandle_00409e50`, the one body that sits at the retail
address in this context.

## Cluster tool rules met along the way

* A function's `source` has to be the cluster `source` or an
  `additional_sources` entry, and no source may belong to two clusters. Shared
  context objects are therefore one-line wrappers under
  `ending_screen_dependencies/`, with the real files in `included_sources`.
* An unreferenced caller is removed by the linker; the context function has to
  call it.
