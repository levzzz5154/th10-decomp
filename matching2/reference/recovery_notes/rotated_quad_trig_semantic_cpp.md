# Rotated quad trigonometry in ordinary C++

[`quad_build_rotated.cpp`](../../msvc/src/core/sprtfunc/quad_build_rotated.cpp)
still uses inline `FSINCOS` in both 591-byte functions. The pinned MSVC 7.1
compiler emits separate `FCOS` and `FSIN` for the ordinary math intrinsics;
declaring `sincos` emits a call. Its `float_intrin` selector maps the two
scalar operations separately; `sincos` has no entry in its intrinsic attribute table. A separate GCC x87 check produced `FSINCOS`
in all 54 tested compilations of the **whole** first function. None matched
the surrounding retail instructions. Clang 21 feeding Intel LLVM 22 on i686
also emitted library calls, not `FSINCOS`, for the two complete functions.
Both 591-byte entries and the 1,047-byte projected billboard now use the
[same vertex type and C++ anchor/rotation calculation](../../msvc/include/th10/render/textured_quad.hpp).
Their trigonometric instructions are still inline assembly.

In native `/GL` + `/LTCG` links, both MSVC 13.10.3052 and 6030 compile
`std::polar` on `float` and `double` to separate `FCOS` and `FSIN`. Using
the exponential of a pure-imaginary complex number also emits the separate
instructions and introduces two CRT calls. Neither library spelling produces
the paired instruction. In the 6030 backend the encoder has an `FSINCOS`
entry (operation `0xD5`), but the only producer identified was the inline
assembler. The floating-point peepholes examined do not combine the scalar
sine and cosine. This is not a proof about every possible compiler.

Open Watcom's unmodified 32-bit C++ compiler can fuse ordinary `sin` and `cos`
and honor the private entry and callee registers. Of 111 complete builds of
`0x004436C0`, 28 emitted `FSINCOS`; the smallest fused body was 608 bytes,
against retail's 591. Its first instruction was `push ebx`, not the retail
floating-point load, and it spilled a trigonometric result to double before
narrowing to float. The correct instruction and calling convention are not a
whole-function match.

The projected billboard (`0x00443B60`) computes the pair twice. With `-op`,
Watcom kept both computations and all four binary32 stores, but emitted
separate `FCOS` and `FSIN` at each site. The 914-byte body retained the two
projection calls and the EAX entry/result convention; retail is 1,047 bytes.

Digital Mars C++ 8.57.0n emitted separate `FCOS` and `FSIN` in a 774-byte
build of `0x004436C0`. The complex-exponential version called `_cexp` and
occupied 851 bytes. Neither had the retail entry convention.

Calling the game's real polar-vector setter (`0x004458B0`) with unit radius
from ordinary MSVC C++ gives 590 bytes for each 591-byte rotated entry and
1,056 for the 1,047-byte projected entry. The native contributions contain
one, one and two new calls, respectively. Neither the size nor the instruction
sequence matches; the comparison does not establish floating-point equivalence.

## Historical semantic-only experiment

An earlier version computed the angle pair in
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

The `semantic` manifest classification describes the region's C++ owner; it
does not certify that its source contains no inline assembly.
