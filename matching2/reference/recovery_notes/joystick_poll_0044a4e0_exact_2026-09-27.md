# Joystick polling, 0x0044A4E0

The complete 264-byte routine is recovered as ordinary readable C++ without
inline assembly or a native-LTCG cluster. The normal probe reports zero
differing bytes and validates all twelve relocations, including the security
cookie and its check helper.

Fresh Ghidra evidence corrects the earlier ABI blocker: the pad index arrives
in ECX and the fixed global output buffer is returned in EAX. ESI is local,
saved only on the DirectInput path. There is no incoming output-buffer argument.

The function clears all 128 button bytes, then selects WinMM or DirectInput
using flag 0x400. WinMM requests device zero, zeroes its 0x34-byte JOYINFOEX
record, and maps 32 button bits into bytes with value 0x80. DirectInput polls the
selected device; failure attempts acquisition, including up to 400 retries for
0x8007001E, and does not read state afterward. Poll success reads an
uninitialized 0x110-byte state record and copies all 128 button bytes. The state
read result is deliberately ignored, matching retail.

Two distinct function-scope stack records plus intrinsic memset/memcpy
reproduce the 0x148-byte GS frame, rep stosd/movsd, conditional ESI save, and
COM calls at +0x1C/+0x24/+0x64. The first typed candidate was already 264 bytes
with only three differing bytes: its WinMM loop shifted the button bits before
incrementing the index. Writing the retail sequence as a do/while loop makes
the full contribution exact. No compiler barrier or volatile fields are needed.

The joyGetPosEx import declaration uses dllimport. Its COFF alias binds
`__imp__joyGetPosEx@8` to the existing IAT slot at 0x00466280. The shared globals
and GS symbols retain their existing manifest bindings.

Maintained source:
`src/game/input_poll_joystick_buttons_0044a4e0.cpp`.
Evidence is under `matching2/build/experiments/joystick_poll/`, including fresh
Ghidra disassembly/decompilation, `attempt02.json` (three-byte residual),
`attempt03.json` (exact), and `final.json` (final commented source exact).
This supersedes the previous 349-byte candidate and private-ABI blocker.

Whole-executable validation is recorded in the current recovery checkpoint.
