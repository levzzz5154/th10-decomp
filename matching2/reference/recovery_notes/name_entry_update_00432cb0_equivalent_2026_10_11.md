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

## 2026-10-17: the stackpack tracer fixed, and what it shows

The named route was attempted directly:
`compiler_traces/stackpack/trace_stackcolors_cl.py` on
`src/game/title/name_entry_update.cpp`. It initially produced only
`ERR error('No registers.')`. The compile itself was fine (a 5,363-byte
`.obj`); the failure was that `hbreak *0x1076953f` was armed at script start,
before `c2.dll` was mapped, so gdb parked it ("Temporarily disabling
breakpoints for unloaded shared library c2.dll") and never re-armed it before
`cl.exe` exited.

That is fixed in the tracer: it now runs with `set stop-on-solib-events 1`
until `c2.dll` appears in `gdb.objfiles()`, and only then arms the
breakpoints. Verified working — `src/game/laser/laser_rectangle_split.cpp`
produces a 295-line dump with named elements, weights and conflict sets.

With the tracer working, this unit still reaches no `colorElemental` call at
all, so its six `stack-slot-order` hunks cannot be read from a colour dump
here; the `msvc-c2-stack-slot-order-by-reference-weight` mechanics remain the
route, but only for units whose compile reaches the colour pass.

## 2026-10-17: the `push ecx` dead slot measured; the lever folds away

The residual read instruction by instruction is sharper than the class list
suggests. Retail's prologue has `push ecx` — a dead argument slot, 4 bytes of
frame — and four `pop ecx` on its exits; the model emits none of them. The
rest is the frame home at +0x6a (`lea edi,[esp+0x1c]` against `[esp+0x20]`),
three filler placements, and `mov edi,edi` against `nop`.

The "locals in dead parameter slots" lever was tried six ways, measured with
the byte script against the baseline 368/378, 10 hunks, 1,082 differing bytes,
8 tail bytes:

| variant | result |
| --- | --- |
| `slot-local`, `slot-helper`, `slot-pointer`, `slot-dead`, `slot-two`, `slot-beside-handle` | all 368/378, 10 hunks, 1,082 bytes — identical to baseline |

Every form folds away entirely, so no declaration of ordinary state produces
the `push ecx`/`pop ecx` pair. A survey found the same pattern in 39 hunks
across 10 regions (`enemy_execute` 8, `anm_vm_tick` 7,
`name_entry_update`/`recovery_script_executor`/`ui_final_runtime` 5), so this
is a class, not a quirk of this function — and in each case it is the
compiler's choice to keep an argument slot, not a source declaration.

The alignment fillers are the same story: `lea ebx,[ebx+0x0]` against
`lea esp,[esp+0x0]` is only the filler's register, and the pair at +0x349 /
+0x454 is the same filler one block earlier or later. Region stays
equivalent.

## 2026-10-18: frame mechanism fully solved; parked on the zero-traffic escape

The `push ecx`/`pop ecx`x4 single-slot frame idiom is fully explained: the
slot is the handle's home (`lea edi,[esp+0x1c]` = entry-4), opened by a
SECOND function-scope kind-4 (address-taken) local that conflicts with the
handle as a separate stack element. Proven against exact siblings
(TitleMode6/TitleMode11) with a calibrated stack-colour probe harness
(trace_build.py / trace_all.py / probe_elements.py, ~22 s per element list):
a kind-4 local whose address escapes transitively (stored into a member a
later real call reads, or passed as a real call's pointer argument) and whose
range covers the creation window [0x432d1a, 0x432d1e] reproduces retail's
prologue and handle lea byte-for-byte (outspan2 / s1 / helperstore probes).

Conflict-rule facts (measured): kind-4 locals conflict with the handle as
separate elements; kind-3 temps and kind-5 params do not even with
overlapping ranges; dropped-argument and immediate-dereference "escapes" do
not create elements; union/struct aggregates are ONE element; recycled
strcpy/free-list temps shift symbol ids but never widen their range across
the window; a parameter or receiver written after a call gets the GameMain
EAX-to-ESI promotion, not a spill.

Open item: the zero-traffic spelling of the second local's escape + read —
every construction adds an lea/store/reload retail's image does not have, and
no existing store's operand list has room for the local's address. Region
stays at baseline (1,082 differing bytes). Probe corpus in
/tmp/campaign/name_entry/.
