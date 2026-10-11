# Difficulty selection screen 0x00430320: exact C++ (2026-10-11)

`src/game/difficulty_select_update_00430320.cpp`, 888 bytes with its phase
table, cluster `layout/ltcg/difficulty_select_update_00430320.json` (cloned
from the key configuration cluster; the title dispatcher stand-in is the
caller, the room is a stack argument and ends up in EBP, `ret 4`).

## What decided each residual

| retail | model before | source reason |
| --- | --- | --- |
| `movsx esi,word [esi]; add si,7` before the slot-frame call | `movzx` | the frame parameter of 0x0042C770 is `short`, not `unsigned short`. The pause menu 0x00422C80 already had a `short` stop-frame parameter and the same `movsx`. The header and the four clusters that name the symbol were changed (`...QAEXHF@Z`); every other caller stayed exact. `sel + 0x11` in phase 0 still gives `xor esi,esi; mov si,..`. |
| `mov ecx,slot; mov eax,room` before 0x0042C750 | reversed | arguments of a private-convention callee are loaded last parameter first. A free `__fastcall(slot, state)` loads the state first; as a member `owner->RestartSlot(slot)` the slot comes first and the callee keeps owner EAX / slot ECX. The cluster carries a member stand-in at 0x0042C750; the maintained free-function form stays in the stop-at-frame cluster. |
| `lea eax,[child]; mov esi,2; call 0x449470`, call path jumps to the `lea` | `mov esi,2; lea eax,..` | see below |
| `test ax,ax` after 0x0040ACE0 | `test eax,eax` | `(short)data_00474e30.InputMaskActive(mask)` with the maintained `int` return type, as in the pause menu. |

## The stop-frame call

Scheduler trace of the cluster link (graph of the block: `mov esi,2`, `lea`,
call, ...): both nodes have priority 17, one successor each, so the scheduler
keeps the emission order. No spelling of the call changes that order: the
address of a local and a constant are both leaves, and the frame is loaded
first (member on the reference, pointer local, wrapper functions, `short`
frame, array local were all tried).

Retail's order comes from tail merging. The search and the stop are inside an
inlined helper with one stop-frame call per branch, each on its own named
child:

```cpp
if (difficulty < 4) { Ref child = handle->FindChildRef(sel + 0x6d); child.SetStopFrame(2); }
else                { Ref child = handle->FindChildRef(0x71);       child.SetStopFrame(2); }
```

Both branches end in `lea eax,[child]; mov esi,2; call`, the two children
share the stack slot, and the merged tail starts at the `lea`. Variants:

- one call after the branches (value returned from a helper): `mov esi,2`
  first;
- call on the returned temporary (`FindChildRef(..).SetStopFrame(2)` through
  a reference wrapper): the call branch reuses the pointer the search returns
  in EAX and jumps past the `lea`;
- the same two branches written in the handler instead of a helper: neither
  search is inlined (the block weight of a switch case is too low) and the two
  calls merge. Inside the helper each branch has half the entry weight, which
  inlines the constant-id search and leaves the computed one a call, as in
  retail.

## Cluster notes

- The animation leaves (0x00449250, 0x00449470, 0x004497D0) are included
  with `#define AnimationManager RecoveryLookup_0040bd80` (and the context and
  id types) so that the handler, the inlined search and the leaves all call
  the one lookup at 0x004491C0.
- 0x004497D0 is included with `noinline` defined away; the handler's
  declaration has no `noinline` either.
- Context size is the `.text$0040a000_context` contribution in cluster.map
  (92 here); the map is under `build/probe/clusters/<name>/native-*`.
- The rig diff normalises jump targets, so a tail merged at a different
  instruction looks exact there; check the probe.
