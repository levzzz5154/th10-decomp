# Scheduler task constructors: exact C++

Both adjacent 32-byte routines are now readable C++ in
`src/game/task_constructors_00449a50.cpp`:

| Address | Recovered operation |
| --- | --- |
| 0x00449A50 | EmptyTask constructor: clear all three callbacks |
| 0x00449A70 | RoutineTask constructor: retain the supplied tick callback, clear the other two |

Both zero priority, clear only the heap-owned flag bit, and initialize their
embedded link to self / null next / null previous. Their context word is not
written, matching retail. The types derive from the established 36-byte
SchedulerTask layout. Original class names are not claimed.

The earlier candidates treated the first routine as a Reset member and failed
to derive its EAX receiver; the second also hoisted its flags update. Natural
constructors plus the separate inline InitializeTaskLink operation resolve
both issues. Native LTCG supplies EAX as the object and ECX as the routine
argument, and retains EDX for the flags word with the exact retail store order.
No register overlay, forced instruction, byte mask or inline assembly is used.

A compiler-only array caller placement-constructs both task types. Its complete
native contribution is 70 bytes and is never selected into the final image.
Both selected function contributions are exactly 32 bytes. The production
probe reports EXACT for both, and independent SHA-256 comparisons find zero
byte differences across both complete windows. Live Ghidra disassembly confirms
all 24 instructions and both RET boundaries.

The old unassigned sources were deleted and manifest ownership migrated to
the semantic constructors, preserving the original records as provenance.
Native PE/MAP/compiler outputs, final source/layout snapshots, Ghidra output,
and unmasked byte hashes are retained under
`matching2/build/experiments/task_constructors_2026_10_04`.

The normal full build passes outside the three preexisting equivalent C++
regions. Ordinary exact C++ now covers 2,185 regions / 162,067 bytes; remaining
assembly is 131 regions / 127,502 bytes. The full objective remains incomplete.

The exact-mode full build passes as well. Independent cmp confirms all
487,936 bytes of the resulting executable match retail.
