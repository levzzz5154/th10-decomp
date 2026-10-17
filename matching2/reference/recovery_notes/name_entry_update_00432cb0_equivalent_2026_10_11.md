# High score name entry 0x00432CB0: equivalent (2026-10-11)

`matching2/msvc/equivalent/game/name_entry_update_00432cb0.cpp`, verified by
`layout/equivalent/name_entry_update_00432cb0.json` in the context of the
title-menu cluster (`layout/ltcg/difficulty_select_update_00430320.json`) plus
the real score insertion 0x00421FA0: 1,392 of 1,400 bytes, 368 of 378
instructions identical.

## The difference

Retail gives the handle written by the back-layer creation 0x00448D00 a
stack slot of its own (`push ecx` at entry, `pop ecx` in the four epilogues,
`lea edi,[esp+0x1c]`). The model puts it in the room argument's dead slot
(`lea edi,[esp+0x20]`). The remaining recorded items are loop-alignment
filler that moves with those five bytes.

c2 `ColorStackElements` lets an element take the newest colour it does not
conflict with, and parameters are colours. Dumped during the cluster link
(element list at [0x108A98A4], conflict sets at [0x108A9894], breakpoint on
0x10768B01):

| function | elements | handle conflicts |
| --- | --- | --- |
| 0x00430320 (exact) | `child`, `slot`, `child`, `room`, `handle` | both `child`, `slot` |
| 0x00432CB0 model | one unnamed temporary, `room`, `handle` | none |

In 0x00430320 the other locals claim the argument's colour first and conflict
with the handle, so it opens a new slot. Here nothing conflicts with it.
`MdmFlagUnsafeForStackPackParams` (0x1075D64C) is not involved: it only
leaves a parameter unsafe when no must-execute block reads it outside
argument pushes, and both functions read `room->phase` at entry.

So retail's function had one more stack element that conflicts with the
handle: a local live across the creation call, or another address-taken
local, with no instruction left in the image. Tried without effect: handle
at function or block scope, the room view as a local or as casts, the phase
in a local, `rank` at function scope, no block around case 0, a duplicated
phase 1, an out-parameter through an inline helper, a temporary object as
the result target. A state pointer `&room->name` as a local moves the room
to EBX and is wrong.

## Source shapes that mattered for the rest

- the four input tests are **calls** to 0x0040ACE0 here and inlined in the
  save screen. The inline score counts a constant argument 5 and a variable
  one 2, and at this block weight (5,000,000) the call survives only with
  the receiver in a local: `KeyRepeatState* input = &data_00474e30;` (final
  score 92 against the limit 89; 81 with the global named directly);
- the grid pointer is a local of the navigation block only; the confirm
  block names `entry->grid` again;
- the score file is reached through an inline accessor at each use, not a
  local, so its load follows the table index and no fourth register is
  needed (a local costs EBX and breaks the shared tail);
- every edit branch ends in its own `Queue(10, 0)`; the survivor of the tail
  merge has retail's operand order (`mov ecx; mov edi; push 0`). One shared
  call after the chain gives the usual order;
- `InsertScore` only keeps its retail body when the game counters object
  0x00474C44 has its address taken in the link.

## 2026-10-17: the forceinline-helper out-target spelling probed; parked

The `msvc-c2-stack-slot-order-by-reference-weight` "locals in dead parameter
slots" lever (the out-target declared inside a `__forceinline` helper with
its lookup, use and release all in the helper, so its bounded lifetime can
take the dead argument slot where retail has `push ecx`) was transplanted
from 0x437FE0: the 10 hunks are unchanged. This joins the memory's 0x432CB0
entry ("scope, view-pointer and temporary-object spellings do nothing") as a
fourth negative: the helper spelling too.

Region stays equivalent (1090 differing bytes). The ColorStackElements dump
the memory names remains the route.
