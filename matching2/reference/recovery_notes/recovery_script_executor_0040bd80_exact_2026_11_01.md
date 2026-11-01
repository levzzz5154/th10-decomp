# Recovery script executor 0x0040BD80 — byte-exact, 2026-11-01

The 1,568-byte script executor (code plus its 18-entry jump table) is
byte-exact C++ (`src/game/ending/recovery_script_executor.cpp`, function
`RecoveryScript_Execute2`), built in the new cluster
`build_support/layout/ltcg/recovery_script_executor.json`. Its equivalent
layout (7 recorded differences, 13 instructions, 18 differing bytes) and the
assembly owner `build_support/exact/game/ending/event_script_runtime.cpp` are
gone.

## What closed it (18 -> 0 bytes)

1. **The animation manager `g_sprt_ctrl` is a plain global read.** The old
   `MANAGER` macro `(*(void* const volatile*)&g_sprt_ctrl)` took the global's
   address. That stops c2's whole-program CSE of the manager load. With plain
   reads, c2 keeps one load across Find and the path decoder (EBX), which
   cannot write it, and reloads it after the text writer, as retail does.
   This fixed the EBX/EDI swap in case 3 (18 -> 12).
2. **The ring-reset path uses an inline `ValidateInPlace(handle)`**, the body
   of 0x00449450, with the id passed as an expression
   (`*reinterpret_cast<const RecoveryScriptId*>(&handle->value)`). The music
   room 0x00433EF0 has the same split: in place in one path, out of line in
   the other. A named `RecoveryScriptId id` local is a ChoosePhysReg register
   candidate. The same value as an expression is a temporary in RegAssign's
   function-wide EAX->ECX->EDX rotation, which runs in layout order. The else
   branch is one expression,
   `RecoveryMarkText(g_sprt_ctrl, RecoveryValidateHandle(&h[ring]), color, Decode(command + 4))`
   (12 -> 4).
3. **The case-3 ring loop is a plain `for (int i = 0; i < 5; ++i)` index
   loop.** Step 2 removed two named locals, and that flipped the x87 operand
   order of the timer tail (`fld [speed]; fadd [elapsed]`). The base temps of
   those two loads are 5 ids apart. The order is right only when the first id
   is 3 mod 4. The index loop restores that parity (4 -> 0). An index loop in
   case 4 instead of case 3 also gives 0. Index loops in both give 4 again.

Ruled out: speed-accessor or inline tick-helper spellings of the timer tail
(15 variants). Named color or text locals in the post-loop or else branch
(23 bytes). Letting LTCG inline Validate (1,229 bytes). Inline Validate while
the manager stays volatile (1,263-1,320 bytes).

Promotion change: the loop and post-loop text writes now call
`RecoveryMarkText(g_sprt_ctrl, object, ...)` instead of
`object->MarkText(g_sprt_ctrl, ...)`. The equivalence rig bound both
spellings to 0x00447A50. A cluster can place only one compiled body at that
address, so all three calls use the free spelling, which the else branch
needs. Rig bytes are unchanged: 444/444 instructions, 0 differing bytes.

## Cluster

The cluster reproduces the equivalence link in the same object order:

- the executor source, through the driver
  `layout/ltcg/recovery_script_executor_context.cpp`;
- then `recovery_script_executor_dependencies/00..24`, which hold the
  mark-text/dispatcher cluster's driver and sources without its stand-in
  executor.

The entry is the donor's `_RecoveryMarkTextDispatcherCompilerContext@20` at
0x0040A000. There are no roots, as in the rig. The rig's four
equivalent-only context files moved into the dependency folder:

- 02: ASCII factory with the member `Configure`;
- 22: free handle validation, handle in ESI;
- 23: one-push `RecoverySetFlag` and the (buffer, name) `LoadAsset`;
- 24: free `RecoveryMarkText`.

These stand-ins sit at the retail addresses 0x00449450, 0x004492A0,
0x0040B480, 0x0043C970 and 0x00447A50. The donor bodies at three of those
addresses are parked at 0x00401000 through new overridable section macros.
Their defaults are unchanged, and the donor cluster still builds with 0
differing bytes:

- `RecoveryTextVm::MarkText`: `TH10_MARK_TEXT_SECTION` in
  `src/core/sprtlib/recovery_mark_text_and_dispatcher.cpp`;
- `RecoveryLookup::SetFlag` and `RecoveryLookup::Validate`:
  `TH10_LOOKUP_SETFLAG_SECTION` and `TH10_LOOKUP_VALIDATE_SECTION` in
  `marktext_dispatcher_context/recovery_script_executor_core_anchors.cpp`.

The hint update and its scheduler callback are compiled but unreachable here,
because nothing roots them. LINK leaves their sections empty. Two empty
contributions at one address make the cluster map fail with "duplicate
section contributions", so the layout gaps are split at 0x00419650 and
0x004198A0. Each empty section then gets its own address.

Generator: `matching2/build/experiments/goal_2026_11_01/promote_recovery_script_executor/gen.py`
(`apply.sh TREE` applies the whole promotion to a fresh tree copy).
