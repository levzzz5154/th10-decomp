# Byte sum and vector return probes

2026-09-23. After restarting Ghidra following the power outage, the Ghidra MCP
endpoint reopened `th10.exe`. Functions at `0x0044C080` (36 bytes),
`0x00427D00` (34 bytes), and `0x004051F0` (41 bytes) were created in the project,
decompiled, and saved. The measurements below are historical ordinary/native
candidate results. Since then, readable semantic candidates have replaced the
assembly at `0x0044C080` and `0x004051F0`; their current source and manifest
status are described in the per-function notes. Neither new candidate has been
built or byte-probed. `0x00427D00` has also been migrated to a readable
mutating-pair-return candidate with a synthetic LTCG context; its ABI and
output remain unverified. None of these migrations claims byte equivalence.

## Alternate byte sum, `0x0044C080`

Ghidra identifies a `__fastcall` function with the byte pointer in ECX and the
signed byte count in EDX. Its decompiler omits the AX result, but the retail
instructions show an 8-bit running sum returned zero-extended in AX. The count
is made even (`count -= count & 1`), and every other byte is added.

An ordinary MSVC 13.10 C++ spelling with `unsigned short` return and sum,
`unsigned char next = *bytes; next += (unsigned char)sum; sum = next;`, and
`((unsigned int)(count - 1) >> 1) + 1` loop count emitted **36 bytes**, the exact
retail extent, with **14 differing bytes**. The entire byte-accumulation loop
matches. The difference is the setup: retail preserves ESI at entry, uses it
for the odd-byte remainder, and retains that saved register through the early
exit; the ordinary compile uses EAX for the remainder and saves ESI only inside
the positive-count branch. `count &= ~1` gave 33 bytes, `% 2` gave 48, and a
divide/multiply roundtrip gave 40. Other normalization spellings retained the
14-byte mismatch.

A native-LTCG cluster with a synthetic array caller emitted the declared
36-byte body but changed the private argument register assignment and differed
in **19 bytes**. The compiler context must pin both the retail ECX/EDX inputs
and the ESI lifetime before that route can help.

## Pair addition and copy, `0x00427D00`

Ghidra identifies `target` in ECX, `delta` in EDX, and an implicit output
pointer in EAX. The function adds two integer components to `target` and copies
the updated pair to the output pointer. A direct `Pair __fastcall` return model
compiled to **27 bytes** rather than retail's 34: ordinary MSVC returned the
pair in EDX:EAX instead of writing through an EAX output pointer. A coupled
compiler context or a different return ABI is needed.

## Reciprocal vector scaling, `0x004051F0`

Ghidra confirms a vector receiver in ECX, a stack `float` divisor, and an
implicit output pointer in EAX. The constant at `0x00470AFC` is `1.0f`; the
operation writes each component multiplied by `1.0f / divisor`. An ordinary
C++ `Vec3` member returning a local `Vec3` compiled to **67 bytes** rather than
retail's 41 because it placed the return pointer on the stack and materialized
the local. A native-LTCG context that pins the EAX return buffer is the next
useful compiler route.
