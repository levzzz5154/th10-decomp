# Main-menu dispatch ABI audit: `0x00422660` and `0x00422C80`

2026-10-02 update: the nested `0x004224C0` renderer is now complete,
asm-free native C++ and has passed the whole-EXE byte gate. Its public
boundary is `State*, Vec3` by value with RET16, proven by both actual callers;
the earlier custom-register claim below is superseded. The complete
formatter85 and queue132 bodies also compile exactly in its genuine graph.
See [the verified recovery](name_entry_draw_native_004224c0_2026_10_02.md).
The `0x00422C80` choice updater is also now complete, asm-free C++: its actual
boundary is one state pointer with RET4, and all 1,360 bytes pass the maintained
probe and whole-EXE gate. See [its verified recovery](pause_choice_update_native_00422c80_2026_10_02.md).
Only `0x00422660` remains assembly among these two regions. The historical
status and ABI conclusions below predate these recovered graphs.

Date: 2026-09-23

## Status

Both production regions remain assembly in
`matching2/msvc/src/game/main_menu_dispatch.cpp`. This was a static live-Ghidra
audit only; no build, probe, or test was run. The live control flow and legacy
semantic models are readable, but neither body can yet be expressed as
standalone C++ without losing its actual entry or helper-call ABI.

## `0x00422660`: replay/result row renderer

The manifest extent is 1062 bytes. Live Ghidra identifies the entry as
`undefined4 __stdcall FUN_00422660(int *state)`, with one pointer at `[ESP+4]`
and an observed `EAX = 1; RET 4`. Its only direct code reference is the call
from the callback thunk at `0x00422AA1`; the thunk passes the state pointer as
the callee-cleaned argument. Ghidra lists `_localtime`,
`AppendFormattedGameThreadRecord` at `0x00401630`, and `FUN_004224C0` as
callees.

The routine marks `g_pGameThread+0x8988` busy while drawing and restores it on
exit. It has three row-rendering paths: up to 25 replay records at
`state+0x1EC`, a result-date row, and 10 ranking rows. It formats timestamps
from replay/result records, updates the render color at `g_pGameThread+0x8974`
per selection, and uses x87 arithmetic to advance row positions. The legacy
record model establishes the broad behavior but does not provide a bound
retail replay-record type or logger receiver.

The decisive blocker is the `0x00401630` edge. Its production assembly reads
the format and formatting arguments from a nonstandard stack arrangement and
loads its append receiver from a later stack slot before calling the append
routine. A normal `AppendFormattedGameThreadRecord(thread, format, ...)`
declaration does not describe that edge. The nested `0x004224C0` helper also
uses a custom register/stack convention and remains an exclusive assembly
region. Replacing either with an ordinary C++ call would change the call
contract. The `0x00422660` body is therefore left intact.

### Integration contract

The body’s observed entry prototype is `int __stdcall (void *state)`. The
current assembly alias is `_asm_FUN_00422660_00422660` (cdecl). Semantic
ownership would need a callee-cleaning one-pointer symbol, or a deliberate
linker alias that preserves that ABI; a name-only alias to the current cdecl
prototype is insufficient. A caller-inclusive integration must also bind the
25-row replay view and the actual `0x00401630`/`0x004224C0` receiver and
argument layouts.

## `0x00422C80`: pause/result choice update

The manifest extent is 1360 bytes. Ghidra reports
`void __thiscall FUN_00422C80(void *this, int state)`. The direct caller is
`FUN_004223F0`: it pushes the menu-state address from ESI, retains the incoming
ECX receiver, and calls this entry at `0x00422443`. The body preserves the
callee-cleanup contract with `RET 4`; its return value is ignored.

The state pointer is a menu record. Fields established by the body include
`+0x04` (phase), `+0x14` (timer), `+0x24` (selection/cursor), `+0x28`
(previous selection), `+0x2C` (selection count), `+0xF4` (initialization
flag), and animation handles around `+0x1D4..+0x1DC`. Phases 1 and 4 open or
reopen selection views after timer thresholds; phase 2 handles navigation,
confirm, cancel, restart, and result choices; phase 3 completes the transition
after 12 ticks; phase 5 resolves the selected follow-up after 20 ticks. This
topology agrees with the archived `ResultChoiceMenu_Update` model.

The production helper calls carry the remaining engine effects through
private register tuples. Examples from the live body are:

| Helper | Observed call inputs |
| --- | --- |
| `0x00449470` | Handle address in EAX and stop frame in SI/ESI. |
| `0x0044BEA0` | Cursor address in EAX and movement delta on the stack. |
| `0x0043DC90` | Sound queue receiver in ECX, sound ID in EDI, request on the stack. |
| `0x004497D0` | Animation handle address in ESI, script index in EBX, output address in EDI. |
| `0x004243F0` | Consumes the register result from child lookup and changes the animation tree state. |
| `0x00409E50` | Animation-handle address in EAX with receiver/context inherited in registers. |
| `0x00405410` | Timer/scheduler record in EAX and value on the stack. |
| `0x0040ACE0` | Input-mask record in ECX and mask in EAX. |

Some of these operations have semantic models elsewhere, but their source-level
member signatures do not express the retail caller’s EAX/ESI/EBX/EDI tuple.
Other helpers, notably child lookup, tree marking, and the pause transition
at `0x00422C30`, retain private register inputs. The result-choice model
abstracts these effects behind callbacks and therefore cannot be used as a
drop-in body for the retail record without first binding those effects and
the incoming `this` value.

### Integration contract

The observed source-level shape is a member entry with implicit ECX and one
stack pointer argument, conceptually `void Update(void *state)`. A plain C
function declared with the current cdecl assembly alias would not preserve the
implicit-ECX/`RET 4` contract. The current alias is
`_asm_FUN_00422c80_00422c80`; semantic ownership must provide a member-style
symbol or an explicit linker binding with the same machine-level ABI. The
caller `0x004223F0` and the animation/cursor/sound helper cluster must be
included before promotion.

## Follow-up boundary

This subtask changed only the two blocker comments and this note. It did not
edit `regions.json`, shared headers, layout files, callers, or callee bodies.
No exact byte-match or semantic equivalence is claimed.
