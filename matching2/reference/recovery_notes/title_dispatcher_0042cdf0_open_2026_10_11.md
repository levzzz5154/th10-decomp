# Title dispatcher 0x0042CDF0: open (2026-10-11)

Still assembly. The dispatcher is linked into the title-menu cluster
(`layout/ltcg/difficulty_select_update_00430320.json`) as an unselected
anchor from `layout/ltcg/ending_screen_dependencies/title_dispatcher.cpp`,
which is 205 differing lines from retail. A model at 58 lines is saved in
`reference/semantic_candidates/title_dispatcher_0042cdf0/natural_model_2026_10_11.cpp`;
it is larger than the anchor (0x468 against 0x440 bytes of code), so it
cannot replace the anchor before it is exact: the three clusters that
include the file declare the anchor's size.

## What the model settles

- **The idle-demo logic is an inlined helper with two returns.** Retail ends
  the demo path with `mov edi,ecx; mov [0x491c00],edi; jmp` past the load of
  the entry kind. `return data_00491c00 = mode != 1;` in the helper and
  `return data_00491c00;` at its end give that; an assignment followed by a
  load at the join is reloaded.
- **The game state at 0x00474C44 is one address-taken object.** The idle
  counter is reloaded for the 900-frame test (`cmp [0x474ca4],0x384`) and
  the demo header loads stay behind the stores only when the counters,
  flags and selection fields are members of one object whose address the
  context driver takes. `if (keys) idle = 0; else if (idle >= 900)`.
- `strcpy` for the demo path; `(next + 1) % 4`.
- the cursor of the two history pushes is a named pointer
  (`MenuCursor* cursor = &room->cursor; ... cursor->PushSelection();`); the
  select helper is the handlers' ternary form.
- case bodies in the order 0, 1, 2, 4, 5, 3, 10/13, 6, 7, 8, 9, 14, 11, 12,
  15, 16.
- the tick at the end is the timer's inlined form (`th10/math/timer.hpp`).
  Its two x87 operand orders flip with unrelated edits (operand hash), so
  they are to be settled last.

## Still wrong

1. **Constant 2 in EBP.** The model keeps 2 in EBP (`push ebp; mov ebp,2`);
   retail uses immediates and never touches EBP. The use that carries it is
   `mode == 2` at the top: a `switch` there drops EBP but emits a range test.
   Removing any one of the other six uses changes nothing. Not a callee
   question: every callee preserves EBP.
2. **Demo block.** Retail computes `stage * 3` before the stage stores and
   loads the current difficulty before the shot type; the model emits the
   statements in source order. Putting the stage record statement first
   gives the early `lea` (and the 58 lines) but also an early `shl`.
3. **Key configuration call.** Retail calls 0x0042F540 with the room in EBX
   and no push. The cluster has that handler only as an address, so the
   model pushes; its body (exact in `key_config_update_0042f540.json`) and
   its leaves have to join this cluster first.
