# 0x00420A90 — WAV resource path rewrite

Updated 2026-09-23 from the live `th10.exe` Ghidra analysis. The 120-byte
function at `0x00420A90..0x00420B07` is an ordinary two-argument operation
wrapped around a call with a private register convention. The local string work
is expressible in C++; the resource-registration call currently prevents an
exact inline-assembly-free version.

## Verified entry and return contract

Ghidra identifies `undefined4 __stdcall FUN_00420a90(undefined4, char *)`.
The raw body ends in `RET 8`, so the function accepts two 32-bit stack
arguments and removes them itself. Its direct xrefs contain ten call sites in
eight functions. For example, `FUN_00417870` calls it twice, with `(0, pathA)`
and `(1, pathB)`, and makes no post-call stack adjustment. `FUN_0040bd80`
passes `0` with the path stored in the event record.

The source-level behavior is:

```cpp
int __stdcall Recovery_ReplaceExtensionWav(int selector, const char* source);
```

The first argument is not an output pointer. Callers use `0` or `1`, and this
value is forwarded to a registration record. The function returns `1` after
the registration call; it does not return the record or registration result.

## Body behavior

The instructions establish a `0x100`-byte local buffer and a stack cookie.
The loop at `0x00420AA4..0x00420AB8` copies the second argument, including its
terminator, into that buffer; it is an inlined `strcpy`-shaped loop. The call at
`0x00420AC0` is the CRT `strrchr(buffer, '.')` at `0x00452930`. That function
uses the cdecl ABI and returns the last dot in EAX. The wrapper unconditionally
writes `'w'`, `'a'`, and `'v'` to the next three bytes. It does not check for a
missing dot or explicitly write another terminator.

Then the wrapper calls `0x0043E460` with:

| Location at callee entry | Value |
| --- | --- |
| EAX | manager address `0x00492590` |
| EDX | rewritten name in the local buffer |
| first stack argument | `1` |
| second stack argument | the wrapper's `selector` |

ECX is not an input to this call. `0x0043E460` removes its two stack arguments
with `RET 8`. Its Ghidra body confirms the data effect: it scans 31 records
starting at manager offset `+0x1F88`, with `0x10C` bytes per record; in the
first free record it writes `1` at `+0x1F88`, copies `selector` to `+0x1F8C`,
copies the rewritten path to `+0x1F94`, and clears `+0x1F90`. If no record is
free, it makes no record update. The wrapper ignores that outcome and returns
`1`.

Ghidra's decompiler confirms the stack-cookie check and `return 1`; its
disassembly confirms the exact `RET 8`, cdecl `strrchr` call, argument pushes,
EAX/EDX setup, and the private registration call. The sibling registration
helper has 23 xrefs across 13 callers, so changing only this wrapper would not
remove the shared ABI blocker.

## Why the current source retains assembly

The registered body remains in
[`recovery_replace_extension_wav_00420a90.cpp`](../../msvc/src/game/recovery_replace_extension_wav_00420a90.cpp)
as a naked retail body. A normal MSVC x86 `__fastcall` declaration places
arguments in ECX and EDX; it cannot put this manager receiver in EAX while
keeping the name in EDX and two more arguments on the stack. Declaring the
manager as an ordinary C++ parameter would therefore change the call's meaning.

A previous throwaway measurement of a semantic candidate produced 121 bytes
for the 120-byte retail region. The candidate's closest byte count was 120,
but it saved the selector in ESI across `strrchr` where retail reloads it from
the stack. It also moved the manager value to ECX, which would be byte-sized
similarly but semantically wrong for `0x0043E460`. That experiment is historical
evidence; this update did not run a build, probe, or test.

## Next step

The next step toward an inline-assembly-free result is to add or use compiler
support for the actual private call shape—EAX receiver, EDX name, two stack
arguments, and callee `RET 8`—and make that ABI visible across
`0x0043E460` and its callers. Then re-evaluate this wrapper's selector reload
and frame-cookie layout. With ordinary MSVC calling conventions alone, the
current obstacle remains; retaining the retail body is more accurate than a
readable but misdirected call.
