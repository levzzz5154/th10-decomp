# Reciprocal vector scaling at `0x004051F0`

Ghidra identifies a 41-byte leaf at `0x004051F0..0x00405218`. The receiver
arrives in ECX, the divisor is a `float` at `[esp+4]`, and the three source
components are read at offsets `0`, `4`, and `8`. The value at `0x00470AFC` is
`1.0f`. The body computes its reciprocal against the divisor, multiplies each
source component by that reciprocal, and writes the three results through the
pointer in EAX. `ret 4` removes the divisor from the stack. EAX is not changed
by the body.

The semantic candidate is
`Vec3_004051F0::ScaleByReciprocalTo(float, Vec3_004051F0*)` in
`src/unidentified/unassigned_004051f0.cpp`. It makes the output pointer
explicit so the vector operation is readable. That declaration is a source
model, not a claim about the machine-level signature: the retail body receives
the output address in EAX, which an ordinary MSVC C++ member declaration
cannot express. A normal member returning `Vec3` was previously tried; it
used a stack result pointer and emitted 67 bytes instead of the retail 41.

The `float` source model also does not establish x87 rounding details. Retail
stores the reciprocal to a single-precision stack slot without popping the
x87 value, then uses the still-live x87 value for all three multiplies. The
candidate captures the mathematical operation but its ABI, exact floating
point behavior, context placement, and emitted bytes remain unverified.
