# Two-dimensional vector rotation at 0x0044BCD0

Ghidra identifies a 40-byte function with no incoming xrefs. Retail reads a
two-float source vector from EAX, writes a two-float destination from ECX, and
takes a float angle from the stack. Its x87 `fsin` and `fcos` produce the
ordinary rotation: x = cos(a) * source.x - sin(a) * source.y, then y =
sin(a) * source.x + cos(a) * source.y. The second component rereads the source
after writing destination.x, so aliasing can affect the y result.

The [C++ source](../semantic_candidates/vector2_rotate_0044bcd0.cpp) keeps that
store/read order and uses `sin` and `cos`. The manifest retains the old
assembly record in `previous_record`. Typed cdecl arguments replace the
retail EAX/ECX and callee-cleanup stack ABI. The x87 extended-precision
rounding and byte identity are unverified; no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
