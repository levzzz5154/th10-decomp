# Rotated quad trigonometry in ordinary C++

`src/render/quad_build_rotated.cpp` now computes the angle pair in both
`BuildRotatedQuad_004436c0` (`0x004436C0`) and
`BuildRotatedQuadAlt_00443910` (`0x00443910`) with `cosf(angle)` and
`sinf(angle)`. The retail bodies use x87 `FSINCOS`; the C++ calls preserve the
cosine/sine roles in the existing corner equations, while allowing ordinary
floating-point differences. In particular, separate math calls can round
differently and can have different exceptional-input behavior from the fused
x87 instruction. This is a semantic recovery, not a claim of bit-identical
coordinates or byte-identical machine code.

Live Ghidra (`th10.exe`) reports both entries as 591-byte
`__fastcall` functions with parameter 1 in ECX and parameter 2 in EDX. The
dispatcher at `0x004451C0` branches to `0x004436C0` from `0x00445203` and to
`0x00443910` from `0x00445263`; both branches move the entity from EAX to EDX
and tail-jump, preserving the manager in ECX. Ghidra lists the same two callees
for each body: the zero-angle fallback at `0x00443290` and sprite-quad submit
at `0x00442670`. The call-site disassembly confirms the existing nonstandard
argument homes: the fallback path pushes the manager and moves the entity to
EAX; the submit path pushes the zero byte argument and moves the entity to EAX,
with the manager still in ECX. Ghidra classifies those targets as `__stdcall`
(fallback) and `__thiscall` (submit). Ghidra leaves the rotated functions'
return type unresolved, but each caller tail leaves EAX untouched after the
callee call and returns, matching the existing C++ `int` result forwarding.

The live `regions.json` records for both addresses are already `semantic`, with
the earlier assembly records retained under `previous_record`; no manifest
edit is part of this source change. No build, probe, or test was run for this
conversion.
