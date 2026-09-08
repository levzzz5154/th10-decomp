# Input pattern count recovery

The maintained C++98 implementation is
[`src/game/input_pattern_count.cpp`](src/game/input_pattern_count.cpp). It
replaces the 75-byte routine at `0x004088C0`.

The function counts matches in the complete fixed 110-byte table at
`0x004743C0`. MSVC unrolls the loop five entries at a time, reflecting the
retail table's 22 groups of five. Its `movsx` loads establish that table values
are signed bytes and are compared to the full integer query; consequently
`-128` can match a stored `0x80`, while `128` cannot.

Both known callers at `0x00431F60` and `0x004321C1` place the query in EDX and
do not establish a semantic ECX argument. The unused first fastcall parameter
records that ABI directly. The manifest captures the five absolute table
relocations emitted by the unrolled loop. The C++98 contract test exercises
several result counts, no-match behavior, all 110 entries, signed extension,
and the irrelevant first register argument.
