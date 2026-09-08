# Keyboard input recovery

The maintained C++98 implementation is
[`src/platform/keyboard_state.cpp`](src/platform/keyboard_state.cpp).

| Ordinary C++ | Retail address | Bytes |
| --- | --- | ---: |
| `Input_UpdateKeyboardState` | `0x0044B010` | 103 |
| `Input_NormalizeKeyboardState` | `0x0044B080` | 75 |
| Total | | 178 |

The pair clears or normalizes the same 256-byte Win32 keyboard snapshot. The
refresh routine always zeroes the caller's destination first. With input
disabled it returns 0. The Win32 route calls `GetKeyboardState` and returns 0
regardless of the API result. The DirectInput route requests all 256 bytes,
attempts `Acquire` once after any failure, and returns 1 whether the read or
acquire succeeded. The normalization routine reads a stack snapshot, clears bit
7 in every byte, publishes it with `SetKeyboardState`, and ignores both API
results.

## ABI evidence

Both known refresh call sites (`0x00431196` and `0x004323C6`) place the output
pointer in EDX and do not establish ECX. The implementation therefore declares
an explicit unused first fastcall argument and the meaningful destination as
the second argument. This is a compiler-facing record of the observed ABI, not
a semantic context parameter or an assembly wrapper. DirectInput is represented
by a typed vtable prefix through slots `Acquire` (`+0x1C`) and `GetDeviceState`
(`+0x24`), using their COM stdcall signatures.

The normalizer's 256-byte local buffer is protected by the retail stack cookie.
The project now states `/GS` explicitly. A fresh full build proves this does not
change any other selected C++ or assembly region and reproduces the cookie load
at `0x00473660` and check call at `0x00458EA5` exactly.

The manifest records all ten relocations across the two routines: the input
enable/mode/device globals, Win32 imports, security cookie, and cookie checker.
The native C++98 contract test covers disabled, Win32, successful DirectInput,
input-lost, and other DirectInput failure paths; verifies all 256 output bytes;
checks acquisition counts; and confirms that Win32 return values are ignored.
The fixed-address MSVC build supplies the authoritative x86 ABI and byte gate.

The larger joystick poller and final input aggregation pipeline remain assembly.
The history-save helpers at `0x0044BE20` use an EAX state pointer and are not
claimed by this recovery.
