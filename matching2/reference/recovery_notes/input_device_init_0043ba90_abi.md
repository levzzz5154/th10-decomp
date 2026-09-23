# Input device initialization callback at 0x0043BA90

2026-09-23. Audited against the live `th10.exe` Ghidra program. The function
boundary is `0x0043BA90..0x0043BAE2`, with the `ret` at `0x0043BAE2`.

## Behavior

The entry clears bits `0x200` and `0x400` of the 32-bit flags word at
`0x00491FF4`, then initializes the input state rooted at `0x00491C28`. After
the callee returns, it rebuilds those two bits from the pointers at
`0x00491C38` and `0x00491C3C`, respectively. Other bits are preserved from
the post-call flags word.

The flag merge is equivalent to:

```cpp
flags = (flags & ~0x200u) | (keyboard_device ? 0x200u : 0);
flags = (flags & ~0x400u) | (joystick_device ? 0x400u : 0);
```

The actual implementation reads `flags` again after initialization, so any
unrelated flag changes by the callee remain intact. `0x00491C38` and
`0x00491C3C` are four-byte fields at offsets `+0x10` and `+0x14` inside the
state rooted at `0x00491C28`; neighboring DirectInput setup code treats them
as the keyboard and joystick device pointers.

## ABI and references

- The function takes no stack arguments and ends in plain `ret`; there is no
  callee stack cleanup. Ghidra reports `void __stdcall(void)`, while the source
  declaration is `void __cdecl(void)`. With no arguments these have the same
  machine-level entry/exit contract.
- It uses/clobbers `EAX`, `ECX`, and `EDX`, and leaves the nonvolatile
  `EBX`, `ESI`, `EDI`, and `EBP` untouched. Its caller-visible result is void.
- The nested call loads `EAX = 0x00491C28` and calls `0x0043B8D0`; that callee
  immediately copies `EAX` to `ESI` and treats it as its receiver, reading
  fields at offsets `+0x0C`, `+0x10`, `+0x14`, `+0x48`, and `+0x150`. The
  callee's return value is ignored here.
- Ghidra reports no direct call callers. Incoming references are at
  `0x00420222` / `0x0042022B` and `0x0043BBB7` / `0x0043BBC0`: each site pushes
  and stores the function address as part of a callback-registration sequence.
  These are function-pointer references, not direct `call 0x0043BA90`
  instructions.

## Why the body remains naked assembly

The flag update itself is straightforward C++, but the initializer call has a
private EAX-receiver convention. The existing `0x0043B8D0` entry point has no
formal parameter and consumes `EAX`; a normal C++ call cannot guarantee the
receiver in that register, and `__thiscall` would use `ECX`. Converting only
this body to ordinary C++ would therefore lose the observed contract unless
the callee were also changed or an assembly adapter were introduced. Keep the
retail body intact until the caller and callee can be converted as a cluster.
