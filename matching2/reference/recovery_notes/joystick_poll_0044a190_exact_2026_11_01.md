# Joystick binding reader 0x0044A190: byte-exact, 2026-11-01

The 833-byte joystick/pad reader `ReadPad` is now byte-exact C++. The source is
`src/core/zunlib/joystick_poll.cpp`, and it is built in the new cluster
`build_support/layout/ltcg/joystick_poll.json`. The old equivalent layout (4
recorded differences: the Y threshold's register scheduling and the
loop-alignment filler) is gone, and so is the asm owner
`build_support/exact/core/zunlib/joystick_poll.cpp`.

## What closed it

The winmm branch now has the shape of th06's `Controller::GetControllerInput`
all the way through the axis tests:

1. **Plain locals.** `JoyInfoEx info; unsigned int deadzone;`. The 2026-10-19
   model kept a `struct State { deadzone; ymid; JoyInfoEx info; }` record to
   fill the 8 bytes below `info` in retail's frame. Those 8 bytes are the spill
   slot of the low Y threshold. It is computed in EBX, and EBX is needed for
   the Y position, so it spills. Plain locals give that frame without the record.
2. **No cached `ymax`.** The cached caps are read directly at every use
   (`g_joystick_caps[pad].wYmin` / `.wYmax`), as th06 does.
3. **th06 argument order for the Y tests.** The high test is written with the
   midpoint threshold on the left:
   `JOYSTICK_BUTTON_PRESSED_INVERT(0x20, MIDPOINT(wYmin, wYmax) + deadzone, info.dwYpos)`.
4. **Y dead zone spelled `-(wYmin - wYmax) / 4`.** This loads wYmin first and
   schedules the low threshold's sum ahead of the dead zone, as retail does.
   With all four changes, every recorded difference is gone: the
   `mov ebx,edi / add ebx,edx / shr ebx,1 / sub ebx,ecx` threshold and its
   `[esp+0x20]` reload, and also the loop-alignment filler (`jmp` +
   `lea ecx,[ecx+0]` vs `lea esp,[esp+0]`).

In the rig the result was 282/282 instructions identical and 833/833 bytes
(DIFFBYTES 0). The fix is plain C++: no asm, padding, barrier or flag change.

## Cluster

Schema 1, with no context sources, the same as the rig. The driver
`build_support/layout/ltcg/joystick_poll_context.cpp` includes the source into
`.text$01read` (0x0044A190, 833 bytes). Its synthetic direct caller
`JoystickPollEntry` (`_JoystickPollEntry@12`, `.text$03context`, 25 bytes at
0x0044A4E0) is the link entry. It is the caller that makes the LTCG pass give
`buttons` the private ECX convention: `set` and `pad` stay on the stack, with
`RET 8`. Retail's callers are at 0x0044A8B8, 0x0044AC96 and 0x0044AFEA. That
caller used to sit at the end of the source file; moving it into the driver
changed nothing in the rig (282/282, DIFFBYTES 0 before the cluster was built).

Gaps:
- `.text$00layout` from 0x00401000 (299,408 bytes).
- `.text$02layout` at 0x0044A4D1 (15 bytes, retail's padding).

Absolute symbols are the layout's data (`g_input_keys_raw`, `g_joystick_caps`,
`g_pad_devices`, the two DirectInput thresholds, `g_app_flags`), the
`joyGetPosEx` import pointer, `___security_cookie`, and
`@__security_check_cookie@4` (relative_code 0x00458EA5). The body calls no
compiled function: both button helpers are inlined and memset is `rep stos`.
So the cluster has no anchors.

The plain-unit route does not work. Ordinary units compile `/O2 /Gz` without
`/GL`, so `buttons` would be a stdcall stack argument (`RET 0xC`), while retail
starts with `mov esi,ecx`.

The callers still reach the function through the `_asm_FUN_0044a190_0044a190`
entry in the regions.json symbols table.

Generator: `matching2/build/experiments/goal_2026_11_01/promote_joystick_poll/gen.py`.
