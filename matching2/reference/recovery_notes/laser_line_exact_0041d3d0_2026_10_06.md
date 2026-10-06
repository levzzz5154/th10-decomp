# Line laser: complete exact C++ at 0x0041D3D0

The maintained [laser_line.cpp](../../msvc/src/game/laser_line.cpp) now owns
the complete 1,001-byte callback as readable C++, without inline assembly.
Its raw body SHA-256 is
`eb83a5c7f05ecb4c6ff76d2055eeaaf4f5781dc6e64381a37654c60534f97bd8`.
The region is all instructions, with no trailing switch table. Its public
virtual member entry receives the laser in ECX, returns 0/1 in EAX and uses
plain RET with no stack arguments. The manifest keeps the original assembly
record as `previous_record`.

The [native layout](../../msvc/layout/ltcg/laser_line_0041d3d0.json) compiles
the complete callback together with eight full supporting C++ bodies. It
reuses the actual graph and inline vector/scale helper forms established by
the [growing-laser recovery](laser_grow_exact_0041e700_2026_10_06.md).

## Complete behavior

The first virtual call executes the laser's command stream. Motion callbacks
then run in the original order for flags 1, 10, 20, 40, 100, 80, 08000C00,
100000, 200000 and 04000000 (all hexadecimal). Each later test reloads flags,
so a callback's changes affect the following dispatches. Bit 8000 advances
the flash timer by -1 while its current frame is positive, and toggles itself
off when that timer has expired.

While length is below its limit, the callback grows and clamps length. Once
the beam is fully emitted, it advances traveled distance and all three tail
coordinates by the frame-speed-scaled velocity. A positive total emission
length limits the remaining beam: the same difference becomes both length and
length limit, and a nonpositive remainder returns 1 immediately. The source
retains the original unordered branches rather than imposing a finite-only
interpretation on the floating-point comparisons.

A positive hold timer postpones viewport retirement and advances by -1.
Otherwise the callback constructs the polar head point and retires only when
both tail and head are outside, using width for both viewport margins. These
two calls preserve the original shared margin value and actual ECX receiver.

Beams longer than 16 and wider than 3 test player collision at a point 10%
along the beam. The narrow-width branch multiplies by 0.5; the other branch
uses `width - (width + 16) * 0.5`. This factor differs from the growing-laser
type and is retained. A direct hit calls the existing virtual slot +0x18 with
the player's position, a 32/32/0 size and mode zero. A graze every fifth age
frame creates script 434 at the player's position and queues sound 28 using
the laser's X coordinate as pan.

Both original transform-dirty flag updates and width/height, length/width
scale divisions are retained before running the primary animation VM. The
secondary VM runs only while traveled distance compares equal to zero.
Signed zero compares equal; NaN does not.

Both polar local points preserve the original third stack word. The actual
setter at 0x0041F800 writes X/Y only, but this caller still adds position Z to
the remaining local word. The archived environment model initialized Z to
zero; that substitute is not used in production. This preserves the original
indeterminate read and is not a claim of portable defined initialization.
All position and size arguments otherwise use actual typed vector objects.

The checked physical view covers age +0x10, position +0x24, velocity +0x30,
traveled +0x4C, flash timer +0x15C, flags +0x404, hold timer +0x410, length
limit +0x434, total length +0x43C and embedded animations +0x600/+0x9AC.
Virtual declarations describe the existing vtable; no replacement objects,
dummy virtual bodies or stand-in command/motion implementations are emitted.

## Native graph and evidence

The full supporting graph contains the timer advance, viewport test, rotated
classifier, pan queue, positioned animation creator, loader, registrar and
pool allocator. These contributions establish the actual private input
registers used by the callback. They are unselected and earn no new recovery
credit. The callback calls the real public polar and VM boundaries and the
real virtual command, motion and hit slots.

The timer advance (88 bytes), viewport test (91), rotated classifier (471)
and loader (203) matched after diagnostic relocation. In the fixed native
graph, the timer, viewport and loader are also raw exact. The classifier's
helper-only literal addresses remain in the native data pool. The pan helper
has a multiplication-load scheduling difference, and the creator, registrar
and allocator have complete 111/114/165-byte unselected bodies. None is
exported as part of this promotion or given a comparison allowance.

The native link entry is the actual complete seven-byte fastcall wrapper at
0x004187C0, forwarding to the existing public StageUpdate stack entry. It
also matches raw retail bytes and earns no new coverage. The laser's real
virtual callback is rooted directly. There is no synthetic caller, register
bridge, compiler-output edit or shortened dependency.

Ghidra was revalidated against the open `th10.exe` in project `th10` before
reading the full callback and its incoming vtable reference at 0x0046DA68.
Those read-only responses are retained under
`matching2/build/experiments/laser_line_native_2026_10_06/`.
No Ghidra prototype or function definition was changed.

The first complete source graph matched all 1,001 bytes after diagnostic
relocation. A stale section name in the diagnostic specification was corrected
and the existing native artifact re-read; no source or instruction changed.
The first fixed-layout attempt was correctly rejected because the gap before
the timer sorted after its section, placing that helper at the wrong address.
Reordering the gap fixed layout placement. The formatted final source then
passed the normal native verifier and direct raw-byte comparison at
0x0041D3D0 before any production promotion.

Production repeated the complete fixed-address proof. Its report records
zero changed instruction bytes, zero address-operand changes, zero masked
bytes and `reference_bytes_used_for_build: false`. The current source and
include hashes were checked against that fresh compiler report. The exact
body needs no diagnostic relocation or comparison normalization.

Both `make` and `make EXACT=1` pass. The exact image equals all 487,936 oracle
bytes and retains SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
All 963 current cluster reports and 1,483 selected function hashes pass the
manifest-based audit, with zero instruction changes, masks or reference build
bytes. The production report is
`matching2/build/msvc/clusters/laser_line_0041d3d0/report.json`.
The scratch directory retains the first full graph, both native PE/MAP pairs,
the fixed-address proof, and the final `production_receipt.json` with the
manifest-based audit of current selected clusters.

Coverage is now 2,254 ordinary regions / 199,062 bytes (61.9% byte-exact C++),
eight equivalent regions / 33,176 bytes and 60 assembly regions / 89,245 bytes.
Including the explicitly equivalent regions, C++ covers 72.2% of game-code
bytes. The full readable, byte-matching, inline-assembly-free decompilation
goal remains active and incomplete.
