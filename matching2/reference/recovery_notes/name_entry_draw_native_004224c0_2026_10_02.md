# Name-entry drawing `0x004224C0`: native recovery

2026-10-02. Maintained promotion verified by the native probe and whole-image
byte gate.

The complete 404-byte routine is readable, inline-assembly-free C++ in
`matching2/msvc/src/game/fun_004224c0_004224c0.cpp`. The maintained probe reports
zero differing bytes and selected-body SHA-256
`013e5f0df7c82e68d432003234f09660e05adf30240dd40fa60cfc780de2b298`.
Only DrawNameEntry404 receives new recovery credit.

## Actual public boundary

The entry is ordinary public stdcall: a state pointer and a genuine by-value
three-float position occupy 16 stack bytes, followed by RET16. Both callers
at `0x004227FE` and `0x004228F4` reserve 12 bytes, copy all three position
words, and push the state pointer before calling. Incoming EAX is not an
argument: the entry overwrites it at `0x004224C1` with the character-table
pointer before reading it. The older main-menu dispatch ABI audit's claim
that this helper needs a custom incoming register convention is superseded
by these actual caller sequences and the complete native proof.

Static layout checks bind selected glyph to `+0xFC`, name length to `+0x1E0`,
the 12-byte name buffer to `+0x2B4`, and the position value to 12 bytes.
The source formats the current name at the supplied position, moves x by
name length times nine, applies the eight-character cursor correction, and
draws the yellow underline. It draws the character grid from `(112,320,0)`
with 13 columns, spacing `(18,16)`, selected yellow and unselected gray, then
restores white. The final three glyphs use `0x81`, `0x7F`, and `0x80`.

## Complete genuine compiler graph

The native scope contains the entire queue writer132 at `0x00401530`,
variadic formatter85 at `0x00401630`, and real AppPresent callback6 at
`0x004200C0`. All three complete helper bodies match retail literally but
remain unselected and receive zero new credit. Their existing maintained
owners are unchanged.

AppPresent is the actual scheduler callback registered by the pointer push
at `0x004204EF`. Its complete implementation returns one and uses the real
task callback boundary. It is an independent linker entry; DrawNameEntry is
separately rooted at its public stdcall boundary. No invented call edge joins
the callback to the renderer. The complete formatter and queue bodies let
LTCG derive position EBX for formatting and the queue writer's private
receiver/name/position registers naturally.

The dedicated `name_entry_queue_00401530.hpp` wrapper declares the local
formatter while including the existing queue types. The shared
`game_thread_queue_native.hpp` remains byte-for-byte unchanged, as recorded
by `integration.json`. The local formatter implements the full variadic
formatting and queue append behavior. Float literals 9, 16, and 18 use
verified constant aliases at their actual retail pool addresses; no selected
instruction or address operand is rewritten.

## Source form that resolves the body

The exact grid has two genuine formatter call branches: one for table
characters, and one for the last three symbols using a nested conditional
expression. Combining those branches into a single formatter call produced
a shorter, different body. Four individual calls retained a 33-byte
difference. The two-call form produces the entire exact 404-byte body and is
also present in the maintained score-entry and replay-save renderers at
`0x00433230` and `0x00433B30`. Controls varying loop signedness, queue-pointer
caching, and color type preserve the exact result. No synthetic register
pressure, dummy input, added volatile, assembly bridge, byte mask, or partial
body extraction is used.

## Evidence

The original frozen investigation is
`matching2/build/experiments/name_entry_branch_shape_20261002`: `proof.json`
records all four complete body hashes and measurements, and
`final_probe.json` records the normal exact byte gate.

The integrated lab is
`matching2/build/experiments/name_entry_draw_real_graph_20261002`:
`integration.json` lists the six installed files and unchanged shared-header
hash; `production_probe.json` and `maintained_probe.json` are exact.
The maintained native cluster report pins the final compiler inputs after
the private wrapper, layout checks, removed unused declarations, and comment
cleanup. Its final primary-source SHA-256 is
`c84b1cc495bfa9fd74776efa44a749be48893aacc590fed82dc3ea2169609e2a`.
The report records zero changed instruction bytes and zero changed address
operands.

The subsequent incremental whole gate reused 1,606 unchanged units, compiled
three units, and extracted 150 runtime-library members with zero failures.
The rebuilt 487,936-byte EXE equals retail literally, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
`whole_verification.json` independently checks the four complete native
bodies, final compiler-input hashes, unchanged shared-header hash, and
zero instruction/address normalization. The before/after manifest changes
only the selected 404-byte body and adds its cluster registration.

At this verification point, asm-free selected source totals 2,105 regions /
137,600 bytes (42.5833% of project-owned code); assembly remains in 215
selected regions / 185,531 bytes. Six older mixed semantic bodies / 4,525
bytes remain excluded from asm-free credit. This recovery adds 404 bytes;
combined with the preceding Bounce410 and InitializePlayer397 gate, the
latest verified batch adds 1,211 bytes. The overall goal remains open.
