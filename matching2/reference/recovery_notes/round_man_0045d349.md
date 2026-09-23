# `__RoundMan` at `0x0045D349`

The source now models this 114-byte CRT routine as ordinary C++ with the
observed `__cdecl` ABI: a pointer to three 32-bit mantissa words and a
significant-bit count. Ghidra identifies the body as `__RoundMan`, ending at
`0x0045D3BA` with a plain `RET`. The function reads both arguments from the
stack, preserves `EBX`, `ESI`, and `EDI`, and returns its overflow/status value
in `EAX`.

The code inspects the guard bit at the requested precision. It increments the
last retained mantissa bit only when that guard bit is set and there are
nonzero bits below it, propagates carry toward the most significant word,
clears the discarded suffix, and reports a carry out of the 96-bit mantissa.
Its direct helper calls are `__ZeroTail` at `0x0045D2CA` and `__IncMan` at
`0x0045D2FC`. The C++ expresses the increment locally so the carry result
observed by `__RoundMan` is explicit even though the current semantic
`__IncMan` declaration returns `void`.

Ghidra lists three direct call sites: `0x0045D4EF` and `0x0045D538` in
`__ld12cvt` (`0x0045D476`), and `0x0045D63A` in `__ld12told` (`0x0045D5FA`).
The caller code supplies a temporary three-word mantissa and a precision
count; `__ld12told` passes `0x40`.

The source keeps the existing C-linkage symbol name and address binding. The
shared declaration now records the two-argument return type and the manifest
marks the 114-byte region as semantic while preserving its previous assembly
record. No build, probe, or test was run.
