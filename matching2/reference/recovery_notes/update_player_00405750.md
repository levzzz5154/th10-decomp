# 0x00405750 player update (recovered 2026-10-04)

`src/game/update_player_00405750.cpp` compiles to the retail 223 bytes in the
`player_update_callback10` cluster (with the scheduler callback 0x00405840 as
its real caller). `make` and `make EXACT=1` both pass.

The previous model was 218 bytes: zero tested with `test`, the manager in ESI,
all callee saves at the entry. Three independent source facts were missing.
Each was found by tracing c2.dll rather than by sweeping spellings.

## 1. Zero in ESI, manager in EBP: callee parameter order

c2 rewrites every eligible immediate as a register candidate
(`GrgRewriteImmedAsReg`), so the zero is *always* a candidate. In the old model
`ChoosePhysReg` gave it EBP (the manager had ESI, the node EBX) and the EBP
cost/benefit step then turned it back into immediates. Zero stores do not help:
up to four extra stores still left it in EBP.

Retail has the zero in ESI because the manager cannot use ESI there: the
render-position pointer (the callee's ESI parameter) is evaluated *before* the
manager is loaded into EDX, so the manager is live across the ESI definition.
Declaring `SetAnimationPosition_004492f0(context, position, id)` instead of
`(position, context, id)` produces that evaluation order. The callee's own 90
bytes do not change.

## 2. EBX/EBP saved after the first test: one shared return

`MscShrinkWrap` computes a save block and restore blocks per register and
expands them until the restores have a common successor that also has other
predecessors. With `return 1` written inside the missing-animation path, that
path owns a return block, the restores have no shared successor short of the
exit, and the saves are expanded to the entry.

Retail's missing-animation path joins the function's only `return 1`. Writing
the active-state step as an inlined `void` helper (`Step`) gives that edge:
its early `return;` lands after the helper, in front of the shared return.
(`goto` to a label before the final return, or a `do { ... } while (0)` with
`continue`, produce the same bytes.)

## 3. `pop ebp / mov / pop ebx / mov`: an aliasing store

In the miss block the list scheduler orders two stores and two pops. With two
plain member stores they are independent (priority 3 each) and both pops go
first. Retail has a dependency edge from the id store to the state store, which
raises the first store to the second pop's priority. That edge exists when the
id is cleared through a pointer (`id->value = 0` in the lookup helper); a
reference parameter or a by-value temporary does not create it.

## Also needed

`224.0f`, `16.0f`, `0.5f`, `1.3f` are literals bound with `data_aliases`
(`1.0f` through `constants`); with `extern float` globals the two additions
have their operands reversed.

Tracers: `reference/compiler_traces/regalloc/` (Spillcosts, ChoosePhysReg) and
`reference/compiler_traces/shrinkwrap/`, plus the existing scheduler tracer.
