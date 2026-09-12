# Title-options recovery evidence: 0x0042D920

Status: the handler remains exact retail assembly; one directly coupled timer
callee is promoted to readable semantic C++.

Focused handler:

```text
0x0042d920    3188 bytes  _asm_FUN_0042d920_0042d920  EXACT
```

## Recovered behavior

The function is a callee-cleaning one-argument handler (`ret 4`) whose state
pointer is at `[esp+8]`. Useful state offsets are mode/phase `+0x20`, selected
row `+0x24`, prior row `+0x28`, row count `+0x2c`, frame counter `+0x2b4`,
animation resource `+0x2c8`, and the frame-counter pair at `+0x2b0`.

- Mode 0 initializes six rows, installs the primary animation slot, updates
  the option sprites, and arms timer targets 1/2; it falls through to mode 1
  once the entry animation has advanced.
- Mode 1 selects the sprite set for `data_00491d6a` (three display modes),
  configures rows `0x1f`/`0x20`, and publishes the selected-row frame.
- Mode 2 handles cursor repeat (`0x10`/`0x20`), row navigation, left/right
  changes to the two volume bytes `data_00491d68`/`data_00491d69` and the
  three-state `data_00491d6a`, default restoration (`100/80/0`), sounds,
  sprite refresh, and transition to mode 4.
- Mode 4 waits for the exit timer, then pushes key configuration for row 3 or
  dispatches/pops the score input history for row 5. Other modes return 1.

This agrees with the archived semantic model in
`reference/legacy_semantic/src/game/title_options_menu.cpp`, while the retail
assembly supplies the animation/resource and transition details absent from
that model.

## Timer/animation dependency probes

All seven bounded cluster bodies retain focused retail-baseline matches:

```text
0x0042c5c0  83 bytes  _asm_GameState_DisableTimerWithOwner_0042c5c0       EXACT
0x0042c620  80 bytes  ?SetTimerTarget@GameStateTimer_0042c620@@QAEXH@Z     EXACT
0x0042c670  95 bytes  _asm_Recovery_InstallAnimationSlot_0042c670         EXACT
0x0042c6d0  83 bytes  _asm_Recovery_ClearAnimationSlot_0042c6d0           EXACT
0x0042c730  27 bytes  _asm_GameState_DispatchAnimationSlot_0042c730       EXACT
0x0042c750  27 bytes  _asm_GameState_DispatchAnimationSlotSecondary_0042c750 EXACT
0x0042c770  65 bytes  _asm_FUN_0042c770_0042c770                         EXACT
```

Only `0x0042C620` is retained semantically. Its readable body is in
`src/math/timer.cpp`; the task-specific native-LTCG layout and compiler
context are `layout/ltcg/title_options_timer_0042c620.json` and
`layout/ltcg/title_options_timer_0042c620_context.cpp`. Its focused probe is:

```text
0x0042c620  80 bytes  ?SetTimerTarget@GameStateTimer_0042c620@@QAEXH@Z EXACT
```

Non-exact semantic candidates were restored to their retail assembly sources:

- `0x0042C5C0`: the compiler preserved the 83-byte body but delayed the
  leading `xor edx,edx` until its first use, changing the retail instruction
  order. An inline-assembly repair disabled the required custom ABI and grew
  the body to 90 bytes.
- `0x0042C770`: the compiler produced the complete 65-byte propagation body,
  including the `0x00491C0` lookup, but used `ecx` instead of retail `edx` for
  the child pointer load at `0x0042C7A1`.

The remaining directly coupled work is `0x0042C670` installation (calls
`0x00449950`, `0x00449870`, and `0x004489D0`), `0x0042C6D0` clearing
(`0x004491C0` plus root/child updates), and `0x0042C730`/`0x0042C750` frame
dispatch through `0x00449250`. Those bodies preserve custom owner/index,
manager, handle, and frame conventions that are not yet represented by exact
semantic callees.

The handler retry remains exact at 3188 bytes, but semantic handler promotion
is not topology-safe while `0x0042C5C0`, `0x0042C670`,
`0x0042C730`/`0x0042C750`, and `0x0042C770` remain unresolved. The next
concrete dependency is a task-local multi-source native-LTCG topology for the
timer/animation methods, beginning with the leading-zero ordering at
`0x0042C5C0` and the `0x00449250` manager/frame edge.

No non-exact production candidate or temporary animation manifest remains.
Temporary probe outputs were cleaned from `/tmp`. Full project validation is
currently blocked by unrelated concurrent manifest changes: the validator
reports a translation-unit ownership mismatch (missing semantic recovery
sources and an older whitespace-source entry), with a partition overlap also
observed near `0x004269C7`/`0x004269D2`; no files in those areas were modified.
