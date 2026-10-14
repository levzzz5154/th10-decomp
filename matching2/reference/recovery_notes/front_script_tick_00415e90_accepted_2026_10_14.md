# Result dispatcher 0x00415E90: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/front_script_tick_unit_00415e90.cpp` (which wraps
`equivalent/game/front_script_tick_00415e90.cpp` and the helper bodies from
`src/game/front_script_tick_00415e90.cpp`), built through
`layout/equivalent/front_script_tick_00415e90.json`. Result: **873 of 1,147
instructions identical**, 138 recorded hunks (134 register-choice, 65
evaluation-order, 101 code-shape, 20 block-order). The structural weight is
121, against a budget of 143.

## What moved the count (380 -> 873)

- **Drop the ABI-freezing roots.** A `/INCLUDE` on a helper freezes its
  declared ABI. With only the escape function rooted, LTCG gave the
  helpers retail's private register conventions (370 -> 708). All helper
  bodies have to be in the same cluster for this.
- **Escaped game counters.** `FrontScriptTickEscape` returns the addresses
  of 0x474C68/6C/74/7C/70/4C/48/84. This forces retail's reloads after each
  pointer store.
- **Out-record create.** Retail reads the created handle back through the
  returned pointer. The source uses an explicit
  `int* DispatcherCreateAt(resource, int* out, script, 15)` and the
  `CREATE_INTO` macro.
- **Switches, not if chains.** Each `sub eax,0; je; dec eax; jne` sequence
  is a `switch` on 0x474C68 or 0x474C7C (opcodes 1, 2, 12 and 13).
- **Retail opcode numbering and case order.** wait = 10, countdown = 11,
  sprite select = 12. The cases are written in retail block order.
- **Frame size 0xD8.** The voice call takes literal floats per branch
  (`if (c7c != 6) Voice(2.0f); else Voice(8.0f);`), so no float temp is
  stored. The wait test is `<= 0`.

## Remaining differences (recorded)

- The replay `SetInputMode(4)` tail and the clear-count increment:
  retail tail-merges them across the c7c 6 and 7 paths.
- The flags xor in opcode 9.
- `mov ecx,0x474c40` reloads, and the command-advance copy.
- Register choice across the large switch body.
