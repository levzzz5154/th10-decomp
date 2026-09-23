# Joystick button polling at `0x0044A4E0`

The live Ghidra analysis and listing were used to replace the inline-assembly
body in `matching2/msvc/src/game/input_poll_joystick_buttons_0044a4e0.cpp` with
ordinary C++. The retail extent is `0x108` bytes, from `0x0044A4E0` through
`0x0044A5E7`.

## ABI and caller evidence

Ghidra resolves the entry as `undefined4* __fastcall FUN_0044a4e0(int pad)`;
the parameter is stored in ECX. The only direct caller is at `0x0042F6B6`.
That caller clears ECX before the call and then indexes bytes through the EAX
return value, so the source prototype is
`unsigned char* __fastcall Input_PollJoystickButtons_0044A4E0(int pad)`.
Its x86 decorated C symbol is `@Input_PollJoystickButtons_0044A4E0@4`. The
manifest row now records that semantic symbol and retains the old raw label
through a linker fallback for the assembly caller.

## Recovered behavior

The function first clears 32 dwords (128 bytes) at `0x00497BB0`. If bit
`0x400` of the 32-bit mode word at `0x00491FF4` is clear, it zero-initializes a 52-byte
`JOYINFOEX`, sets `dwSize` to `0x34` and `dwFlags` to `0xFF`, then calls the
WinMM import at `0x00466280` as `joyGetPosEx(0, &info)`. The pad argument is
ignored on this path. On success, the low 32 bits of `dwButtons` become the
first 32 byte values (`0x80` for pressed, zero otherwise); the remaining
96 output bytes stay zero. On failure, the zeroed output remains unchanged.

When bit `0x400` is set, the pad index selects a raw device pointer from the
table at `0x00491C3C`. The function calls its vtable slot `+0x64` (`Poll`). A
nonnegative result leads to a `GetDeviceState` call through slot `+0x24`,
with size `0x110` and a stack buffer. The function ignores that call's HRESULT
and copies 128 bytes from offset `0x30` of the buffer to `0x00497BB0`, which is
the `rgbButtons` portion of `DIJOYSTATE2`. Retail does not clear the stack
buffer first, so if `GetDeviceState` fails without writing it, the subsequent
copy still reads its prior stack contents.

A negative `Poll` result triggers one `Acquire` call through vtable slot
`+0x1C`. If its result is `DIERR_INPUTLOST` (`0x8007001E`), retail makes up to
400 additional `Acquire` calls, stopping early on any other result. It does
not call `Poll` or `GetDeviceState` again after acquisition. Since the output
was already cleared, this failure/reacquisition path returns 128 zero bytes.

There are no null or bounds checks around the device table, device pointers,
vtable pointers, or method slots. The listing reloads the table entry before
the `GetDeviceState` call and before every `Acquire` call; the semantic source
keeps those reloads explicit.

## Code generation status

The current source is a semantic C++ reconstruction with no inline assembly.
Exact 264-byte code generation, including the retail security-cookie frame,
has not been verified. No build, probe, or test was run for this change.
