# Packed color fill at 0x00436CA0

Ghidra identifies a 72-byte function called by `0x00437FE0`. Earlier native
LTCG source probes found a readable body with the correct extent and loop tail,
but a different instruction schedule in the color setup. The maintained source
now contains a semantic C++ candidate and a synthetic LTCG context; this new
candidate has not been compiled or byte-verified.

Ghidra identifies a 72-byte function called by `0x00437FE0`. It receives a
color in ECX and a buffer owner in ESI. It builds a 12-bit color from nibbles
at input bit positions 20, 12, and 4, then writes that 16-bit word repeatedly
to the pointer at owner offset `0x120`. The loop covers the byte length at
offset `0x10C` in two-byte steps and rereads the length on each iteration.

A readable C++ member body with a synthetic array-walking LTCG caller matched
the retail extent of 72 bytes and its first 21 bytes. It also compiled the
loop tail exactly. The remaining 27 differing bytes came from instruction
scheduling and register selection: retail loads the output pointer into EDX at
`0x00436CB5`, before the final nibble calculation, and uses ECX as the loop
offset. The compiler first finishes the color, then loads the pointer into ECX
at `0x00436CC7` and uses EDX as the offset. Both bodies produce the same result,
but they are not byte identical.

Moving the pointer read earlier in C++ made the compiler use EDX for the
pointer and reproduce the loop tail, but it hoisted the load to the first
instruction. That version differed in 42 bytes. Splitting the color calculation
into staged assignments changed the function extent; making the pointer member
volatile did not select the retail schedule. No candidate was promoted.

The current source remains a candidate for the result described above. The
schema-1 context uses a synthetic owner/color-array caller to model ESI/ECX;
the real `0x00437FE0` caller is still assembly and continues to target the
retail address through its legacy linker alias. The old instruction-scheduling
mismatch is unresolved, and exact output remains unverified.
