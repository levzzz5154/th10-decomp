# Title dispatcher 0x0042CDF0 — byte-exact, 2026-11-01

The 1,128-byte title dispatcher is byte-exact C++
(`src/game/title/title_dispatcher.cpp`, function `TitleDispatcher`), built in
the new cluster `build_support/layout/ltcg/title_dispatcher.json`. Its previous
equivalent layout (4 recorded differences, 116 differing bytes) is gone.

## What closed it

Retail has one copy of mode 2's handler call
(`mov eax,[ebx+0x10]; or [eax+4],2; call 0x42D420` at 0x42D0B6). Mode 2's
jump-table entry and the `transition == 1` arm of mode 0 both jump to it. The
model wrote that tail twice. c2 merges duplicate tails only late, so during
register allocation the constant 2 still had one more `or [mem],2` use, and
that extra use put the constant in EBP (`push ebp / mov ebp,2`). Writing the
tail once (`goto main_menu;` into `case 2: main_menu:`) removes the use; the
idle-demo head can then be the natural `if (mode == 1 || mode == 2)` and the
`case 1: case 2:` workaround from the 2026-10-12 note is no longer needed.

Rule: when retail has one shared tail block that a model writes twice, write
it once and jump into it. Copies merged late still count during allocation.

## Cluster

The cluster reproduces the equivalence link: the dispatcher source (through
the driver `title_dispatcher_context.cpp`, which also holds its caller stand-in
`TitleModel::Update` at 0x0042D2E0 and the escape of `g_globals_score`), the
menu-flow/key-config/joystick context sources, then the difficulty-select
cluster's driver and sources. The donor's dispatcher stand-in
`Title_DispatchUpdate` is parked at 0x00401000 through the new overridable
`TH10_TITLE_DISPATCH_SECTION` macro in
`ending_screen_dependencies/title_dispatcher.cpp`; the key-config and joystick
context bodies are parked after it, since the dispatcher does not call them.
Generator: `matching2/build/experiments/goal_2026_11_01/promote_td/gen.py`.

Side finding (agent trace): c2 decides whether EBP may be allocated in
`InitialSplitPoints` (0x107ABCC0); at 0x107C2D94 it disables EBP when
`local_3c > local_10 + 1`, where `local_3c` counts opcode 0x250/0x254 operands
plus `CmdGetEBPCostBenefit` counts at points needing more than 7 registers.
