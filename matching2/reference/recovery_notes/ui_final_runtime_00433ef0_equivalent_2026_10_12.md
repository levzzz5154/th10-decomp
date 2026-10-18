# The music room 0x00433EF0 as an equivalent C++ model (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 694 of 741 instructions identical.**
The model is a rewrite from the retail disassembly on top of the title cluster's helpers, linked
with the real stage-text and animation-registrar sources (`context_sources`). The 47 remaining
instructions are in 31 recorded differences: 14 register choices, 9 evaluation-order swaps,
3 alignment fillers, 4 code-shape hunks (a split read-modify-write of the sprite flags, a jump
over loop padding, two copies through another register) and one loop branch whose target moves
with that padding (both ends were compared by hand: the same loop head). No call, callee or
named address differs. Everything below this paragraph describes the earlier parked draft.

Region: 0x00433EF0..0x004349DB (2796 bytes; 2780 code + 16-byte phase table
at 0x004349CC whose fifth entry sits in the padding at 0x004349DC). The
equivalent model lives in `msvc/equivalent/game/ui_final_runtime_00433ef0.cpp`
with the room view `msvc/include/th10/game/ui_final_runtime_00433ef0.hpp`,
compiled in the title cluster
`layout/ltcg/difficulty_select_update_00430320.json` and registered as
`layout/equivalent/ui_final_runtime_00433ef0.json`.

## Semantics

The music room of the title menu (four-entry phase table, dispatch at
0x00433F07 through the table at 0x004349CC):

- Phase 0 (0x00433F0E): on `timer.current == 1`, install the cursor and
  background slots (95 and 103), load `musiccmt.txt` through
  Archive_LoadFile 0x0044B360, and parse it: every section opened by `#` or
  `@` yields one title (32×64 at +0x698), one comment (32×66 at +0xE98) and
  eight preview lines (32×8×66 at +0x16D8) through StageText_ExtractLine
  0x00434A20 / StageText_SkipLine 0x004349E0. Eight preview-line text
  objects are created (0x00449950 allocate, 0x00449870 script start,
  0x004489D0 register, handles at +0x664). The draw loop slides the next
  two rows in (20.0f pitch at 0x00470CA0, base y 96.0f at 0x00470C80) and
  titles unknown tracks with the "No.%d" format at 0x0046ECF4. Confirm at
  `timer.current >= 10` retargets phase 1.
- Phase 1 (0x00434346): reveal two characters of the selected track's
  preview lines per even frame (up to 8), then phase 2 after
  `timer.current > 4`.
- Phase 2 (0x0043441B): the same reveal, cursor movement (0x0044BEA0 with
  the input mask at 0x00474E36), scroll clamping, row repositioning with a
  40.0f slide threshold (0x00470C64), and the confirm/cancel pair. Confirm
  stops the row text objects at frame 3 and starts the preview of the
  selected track; a track whose comment was never heard requires a second
  confirm (the spoiler acknowledgement, `preview_armed` at +0x694). The
  music requests go through the table at 0x00492590 (commands 2/3/4 via
  0x0043E460), the heard flags live at 0x0047783C + 0x1D892 + track.
  Cancel frees the file buffer (0x00452422), stops the rows and previews,
  and retargets phase 3.
- Phase 3 (0x0043494E): after ten frames remove the slots, free the
  fallback handle, disable the timer, load `bgm/th10_02.wav` and return to
  the main menu.

## Recorded differences (155 hunks, 404 instructions; 337 of 741 identical)

Dominated by two compiler choices the source cannot spell differently:

1. The zero register: the model zeroes EBX/ESI once per block and uses it
   as the source of the constant 0 (`push ebx`, `mov [ebp+0x440],ebx`,
   `cmp eax,ebx`) where retail materializes the immediate 0 at every site
   (`push 0x0`, `test eax,eax`). 131 hunks are of this family.
2. Frame slot choices ([esp+0x24] against [esp+0x28]) and the register a
   short-lived value lives in — 24 register-choice hunks.

The phase dispatch compiles to the same jump-table shape (the model's table
at model offset 2528 with entries matching the case order); the tail
comparison bridges the retail table at 0x004349CC with the model's.

## 2026-10-17: zero-candidate family named; parked

The residual is the `msvc-c2-immediate-register-candidates` family in
reverse of `anm_texture_fill_transparent`: here the model shares the zero in
EBX/ESI (`push ebx`, `cmp eax,ebx`) where retail materializes the immediate
at every site (`push 0x0`, `test eax,eax`). The memory's lever is to stop
the zero being shared in the blocks where it competes (an immediate becomes
a candidate only at the second same-value same-type use), but the candidate
spellings that split a type without changing bytes (signed vs unsigned vs
pointer zero) are all one candidate per the memory's own rule, so the split
has to come from the value paths themselves. The 24 register-choice hunks
are the frame-slot/short-lived-value contest of the note's residual 2.

Region stays equivalent (1640 differing bytes).

## 2026-10-17: the two-value-path rule probed; folds away

The note's rule — an immediate becomes a candidate only at the second
same-value same-type use, and "the split has to come from the value paths
themselves" — was tested by giving zero two distinct sources. Five spellings,
measured with the byte script against the baseline 694/741, 31 hunks, 1,640
differing bytes:

| variant | result |
| --- | --- |
| `two-int-paths` (`int zero_a`, `int zero_b`, each used) | 694/741, 31 hunks, 1,640 — identical to baseline |
| `one-path-two-uses` (one `int zero`, used at two same-type stores) | identical |
| `two-pointer-paths` (two pointer-null sources in the tree walk) | identical |
| `both-types` (both of the above) | identical |
| `call-path-zero` (`int zero = ZeroValue();`) | identical |

Every form folds straight back to the immediates, so two value paths are not
sufficient: c2 discards the sources before the candidate pass sees them. The
24 register-choice hunks stay the frame-slot/short-lived-value contest of
residual 2. Region stays equivalent.

## 2026-10-18: stand-in parameter order closes the argument-load family (706/741, 21 hunks, 1,313 bytes)

The remaining 31-hunk residual was dominated by argument-load order and
temp-rotation questions at private-convention calls. The closing lever is the
callee-parameter-order rule ([[msvc-ltcg-callee-param-order-sets-caller-load-order]])
applied through *equivalent-only stand-ins*: the model now calls
`UiFinalExtractLine` (0x00434A20) and `UiFinalTransition` (0x00434A80) through
copies of the retail bodies in
`build_support/contexts/equivalent/game/context/ui_final_stage_text.cpp`, bound
by name in this layout (`_UiFinalExtractLine@12`, `_UiFinalTransition@20`,
`@UiFinalFind@12`). The caller emits argument loads in the **reverse** of the
declared parameter order, so declaring the parameters reversed reproduces
retail's emission order; extern "C" names and same-typed parameter pairs keep
their mangled names under permutation, so no shared binding changes.

`UiFinalExtractLine(remaining, destination, cursor)` closed 13 hunks at once:
the parse-loop argument order (0xfc/0x10d), the sprite-flags split RMW at 0x1b6
(which now compiles to the fused `or [ebx+0x35c],0x40000000` exactly as retail),
the preview-loop register choices (0x185/0x197/0x1a0/0x1ab/0x1e8), the jump over
loop padding (0x282) and every phase-0 branch target. `UiFinalTransition(self,
target, base, mode, flag)` closed the `push 0x4` interleave (0x37d/0x383) and the
`lea edx,[esi+0x334]` motion (0x6ed) and re-aligned the phase table tail. The
RegAssign trace (`trace_temporary_cursor.py`, focus `TitleMusicRoom`) confirms
the mechanism: expression temporaries rotate a three-slot EAX/ECX/EDX ring and
the head's first two temps are created in the opposite order in the model
(global-load then member-load, retail is the reverse).

Recorded: 21 differences (13 register-choice, 3 evaluation-order pairs, 3
code-shape, 1 alignment-padding), 706 of 741 instructions identical, 1,313
differing bytes, tail clean. The two length deltas left are the head's
`mov eax,ds:0x4776e0` (a1 form, one byte under retail's `mov ecx,ds:...`) and
the missing `mov edx,esi` reload at the row-loop Find call (two bytes); every
other hunk is fixed-length register/order noise and follows automatically once
those two land.

Ruled out this session (all measured): the `AnimationFlagValue` typed
flags-copy lever and pointer/reference stores at the flags statement (they move
the store one scheduling notch but never fuse; the permutation fixed the fusion
outright), signed-vs-unsigned spellings of the shared `0x40000000` constant
(identical bytes — one candidate per the memory rule), named locals at the head
and the row loop (`named-manager`, `result-named`, `named-handle`,
`named-created-value`, `extract-named-next` fold or regress), statement order
inside the register-object helper, `__stdcall`/`__fastcall` declarations of the
shared `extern "C"` asm stand-ins (name decoration breaks the link against the
anchors; the ESP-edge lever needs member-shaped anchors instead), all six
`UiFinalFind` parameter permutations, the stand-in body statement orders, and
the remaining `UiFinalTransition` permutations (only `(self, target, base, …)`
and `(self, target, base, flag, mode)` keep the code extent; the others fix the
two pointer-lea registers but re-introduce the lea motion and a 16-byte tail
shift).

## 2026-10-18: stand-in parameter order closes the argument-load family (706/741, 21 hunks, 1,313 bytes)

The remaining 31-hunk residual was dominated by argument-load order and
temp-rotation questions at private-convention calls. The closing lever is the
callee-parameter-order rule ([[msvc-ltcg-callee-param-order-sets-caller-load-order]])
applied through *equivalent-only stand-ins*: the model now calls
`UiFinalExtractLine` (0x00434A20) and `UiFinalTransition` (0x00434A80) through
copies of the retail bodies in
`build_support/contexts/equivalent/game/context/ui_final_stage_text.cpp`, bound
by name in this layout (`_UiFinalExtractLine@12`, `_UiFinalTransition@20`,
`@UiFinalFind@12`). The caller emits argument loads in the **reverse** of the
declared parameter order, so declaring the parameters reversed reproduces
retail's emission order; extern "C" names and same-typed parameter pairs keep
their mangled names under permutation, so no shared binding changes.

`UiFinalExtractLine(remaining, destination, cursor)` closed 13 hunks at once:
the parse-loop argument order (0xfc/0x10d), the sprite-flags split RMW at 0x1b6
(which now compiles to the fused `or [ebx+0x35c],0x40000000` exactly as retail),
the preview-loop register choices (0x185/0x197/0x1a0/0x1ab/0x1e8), the jump over
loop padding (0x282) and every phase-0 branch target. `UiFinalTransition(self,
target, base, mode, flag)` closed the `push 0x4` interleave (0x37d/0x383) and the
`lea edx,[esi+0x334]` motion (0x6ed) and re-aligned the phase table tail. The
RegAssign trace (`trace_temporary_cursor.py`, focus `TitleMusicRoom`) confirms
the mechanism: expression temporaries rotate a three-slot EAX/ECX/EDX ring and
the head's first two temps are created in the opposite order in the model
(global-load then member-load, retail is the reverse).

Recorded: 21 differences (13 register-choice, 3 evaluation-order pairs, 3
code-shape, 1 alignment-padding), 706 of 741 instructions identical, 1,313
differing bytes, tail clean. The two length deltas left are the head's
`mov eax,ds:0x4776e0` (a1 form, one byte under retail's `mov ecx,ds:...`) and
the missing `mov edx,esi` reload at the row-loop Find call (two bytes); every
other hunk is fixed-length register/order noise and follows automatically once
those two land.

Ruled out this session (all measured): the `AnimationFlagValue` typed
flags-copy lever and pointer/reference stores at the flags statement (they move
the store one scheduling notch but never fuse; the permutation fixed the fusion
outright), signed-vs-unsigned spellings of the shared `0x40000000` constant
(identical bytes — one candidate per the memory rule), named locals at the head
and the row loop (`named-manager`, `result-named`, `named-handle`,
`named-created-value`, `extract-named-next` fold or regress), statement order
inside the register-object helper, `__stdcall`/`__fastcall` declarations of the
shared `extern "C"` asm stand-ins (name decoration breaks the link against the
anchors; the ESP-edge lever needs member-shaped anchors instead), all six
`UiFinalFind` parameter permutations, the stand-in body statement orders, and
the remaining `UiFinalTransition` permutations (only `(self, target, base, …)`
and `(self, target, base, flag, mode)` keep the code extent; the others fix the
two pointer-lea registers but re-introduce the lea motion and a 16-byte tail
shift).


## 2026-10-18 addendum: row-loop store order and the member stand-in (708/741, 1299 bytes)

Two follow-up levers on the stand-in family. Moving the `row_handles[index].value
= …` store statement after the `MusicFind` call statement (the id forwarded
through a named `created_value`) reproduces retail's push-before-store order:
706 -> 708 identical, 1313 -> 1299 bytes, at the cost of three
stack-slot-order hunks (the value local and the spilled resource swap frame
slots). A thiscall member stand-in for the transition setup
(`UiFinalVmView::Start`, mangled name order-sensitive: only adjacent same-typed
pairs keep the `0` back-reference) with the parameters `(mode, base, target,
flag)` fixes the base/target pointer-lea register pair (710/741 identical,
22 hunks) but drags a 16-byte code-extent drift (tail 16, 2083 bytes); the
`(target, base, mode, flag)` order keeps the clean tail (1299 bytes) with the
pair swapped. The two families are one length delta apart from each other.

Ruled out in this round (each measured): every statement-order spelling of the
head's `g_ascii_manager->animation_resource` expression (resource hoisted,
manager-then-member, no-arg and argument accessors, dot-form, pointer
arithmetic `*(void**)((char*)g_ascii_manager + 0x8994)`, `*(&…->animation_resource)`,
indexed `[0x2265]` — all fold or lose 4+ identical instructions), the
phase-2 loop store rewrite (byte-identical), the `created`-only row-loop form
(byte-identical), and the remaining Transition permutations (the register pair
and the clean tail live in opposite permutation families).
## 2026-10-18 addendum (worker UiFinalLengths): row-loop store-first closes the
## statement-order family (702/741, 21 hunks, 1,287 bytes)

Semantic audit first: the Ghidra decompile of 0x00433EF0 shows the row loop
stores `row_handles[index].value` BEFORE the Find statement
(`*param_1 = local_1c;` then `FUN_004491c0(local_1c, pvVar4, local_1c)`), and
the Find's first register argument is an unused receiver passed through
unchanged (the head passes the entry ECX; the row loop happens to hold the
created value in it). With the id forwarded through a named `created_value` and
the store statement moved back BEFORE the Find statement, the Find's argument
setup hoists above the store exactly as retail schedules it: the `@0x2dc` hunk
now matches retail's instruction ORDER (value load, target load, push, store,
call) and the stack-slot-order hunks at 0x297/0x2a0/0x2d1 vanish (the `created`
slot and the spilled resource now take retail's slots). 708 -> 702 identical
(badly placed filler and the store/Find interleave account for the delta),
23 -> 21 hunks, 1,299 -> 1,287 differing bytes. Layout re-recorded: 21
differences (8 register-choice, 7 evaluation-order, 4 code-shape, 1
alignment-padding, 1 branch-target); the registered check reports
`2,796 of 2,796 bytes used, 702 of 741 instructions identical, 0 base/index
swaps, 0 frame-offset, 39 instructions in 21 recorded differences`.

What remains, in bytes: the head's `a1`-form manager load (the one-expression
form rotates `g_ascii_manager`'s temp into EAX where retail keeps it in ECX:
`mov ecx,ds:0x4776e0` / `mov eax,[ecx+0x8994]` vs the model reversed, -1 byte)
and the row-loop push copy (`mov edx,ecx; push edx; mov edx,esi` vs the model's
direct `push eax`, -2 bytes). Every other hunk is fixed-length register/order
noise and the alignment fillers follow the length deltas.

Ruled out in this round (each measured on the store-first base):

- Statement SPLIT of the head expression into the name_entry_update form
  (resource named + result named, every placement around InstallSlot): the two
  loads coalesce into one register (`mov eax,ds` / `mov eax,[eax+0x8994]`), the
  named resource kills the second rotation temporary. The named-manager form
  makes the member load ring temporary #1 (-> EAX, retail's member register!)
  but the manager candidate lands in EAX again (or, declared before
  InstallSlot, in ESI with the load hoisted above the call - 1,211 bytes of
  cascade realignment but not retail's shape). Declared-then-assigned, scoped
  blocks, typed/reference resources, result splits: fold or regress.
- Range-extending constant-true ternaries at the head (`manager != 0 ? resource
  : resource`, `(manager == g_ascii_manager) ? … : …`, pointer-to-member): the
  unknown-condition ternary survives as a real compare but the chain coalesces
  into EAX anyway (693/741, 1,295 B); the equality re-reads fold (LTCG sees
  through the stand-in bodies - JoystickEBX confirms the same for
  `(a == b) ? v : v` with CSE-able sides).
- Lever (d) on the row loop: the constant-true re-read of `created` folds at
  every placement except the if-condition (which regresses); the re-read
  through the Find's result object (`object->id != created_value`) materialises
  but grows the body past the extent (drafts gate). By-value struct id probes
  (`MusicFindId(RecoveryScriptId)` fed from `&created`, the row_handles field, a
  named id, direct `UiFinalFind` calls with the value as lookup, the Find's
  parameter permutations on the new base): all fold to the store-first shape -
  the `mov edx,ecx` argument copy is not an argument-shape question here.
- The multi-use named reference local (campaign lever 4) at both swapped pairs:
  byte-identical no-ops or drafts.

Trace note: `rebuild.py` + the temporary-cursor tracer (cmds.json patched with
the `ui_final_stage_text.cpp` stand-in compile) confirm the mechanism: the
one-expression head's RegAssign entries are the global load, the member load,
the deref (rotation EAX/ECX/EDX in emitted order); the named-manager form
removes the global's entry so the member takes EAX first and the deref slides
to ECX. Retail's pick order (member EAX, manager ECX, deref EDX) therefore
needs either the member's entry to precede the global's in one expression
(no spelling reached this) or the manager candidate in ECX with the deref's
pick skipping it.
