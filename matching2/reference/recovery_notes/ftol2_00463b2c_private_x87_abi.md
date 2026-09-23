# `__ftol2` at `0x00463B2C`

Checked against the live Ghidra project `th10.exe` on 2026-09-23. The current
manifest keeps the 117-byte region `0x00463B2C..0x00463BA0` as `kind: asm`,
sourced from `matching2/msvc/src/unidentified/FUN_00463b2c_00463b2c.cpp`.
The address-to-symbol map identifies it as `__ftol2`.

## Boundary and ABI

Ghidra's function body starts at `0x00463B2C` and ends at the `RET` at
`0x00463BA0`; the manifest size makes the half-open range
`[0x00463B2C, 0x00463BA1)`. Ghidra gives it the nominal signature
`ulonglong __stdcall FUN_00463b2c(void)`, but its variable analysis includes a
phantom `float10 in_ST0`. There are no stack parameters, and the final plain
`RET` does not pop any. The instructions return the low and high halves in
`EAX` and `EDX`.

The call sites confirm the hidden x87 input. For example, `ResolveEclIntValue`
loads `[ESP+8]` into `ST(0)` at `0x0044FF61`, calls this helper at
`0x0044FF65`, then returns with `RET 8`. `ResolveEclFloatValue` does the same
at `0x0044FFA6..0x0044FFAA`. `ResolveEclFloatOperand` loads a float and tail
jumps to the helper at `0x0043EC9E..0x0043ECA4`. These transfers provide no
helper argument on the stack. Ghidra reports 75 caller functions and 226
unconditional-call references (including tail-jump edges), with no callees;
the helper itself is a leaf.

## Behavior

The routine duplicates the incoming `ST(0)`, stores a single-precision copy
for its sign, and executes `FISTP qword` using the active x87 rounding mode.
It reloads that integer with `FILD` and checks the low/high halves. If the
initial integer is zero or has the `INT64_MIN` bit pattern, the helper skips
correction and returns it unchanged. Otherwise it subtracts the initial
integer from the original x87 value, stores the residual as `float`, and
examines the residual sign. For a negative input with a positive residual it
increments `EDX:EAX`; for a nonnegative input with a negative residual it
decrements the pair. This corrects a rounding step that went away from zero.
Both paths pop the x87 values they own before the plain `RET`.

If an invalid conversion completes with the x87 invalid exception masked,
`FISTP` produces the indefinite integer for NaN, infinity, or an out-of-range
value. Its bit pattern is `INT64_MIN`, so the special-case branch returns
that pattern without attempting the correction. The routine also leaves an
actual `INT64_MIN` conversion unchanged. Thus the documented operation is
the observed `FISTP` plus correction sequence, including its active-rounding-
mode and sentinel behavior.

## Why the assembly remains

A scalar C++ signature would pass a floating argument according to the
compiler's normal stack ABI. This entry instead receives an already-live x87
`ST(0)` value and must produce the 64-bit integer in `EDX:EAX`, with several
existing callers relying on that private transfer. Replacing only this body
with a normally compiled typed function cannot preserve that contract. A
semantic C++ conversion would require migrating the call sites and their
register/result use together; keeping an assembly bridge would still leave
inline assembly in this region. The current source therefore retains the
retail instructions while documenting their operation and ABI.

No build, probe, or test was run.
