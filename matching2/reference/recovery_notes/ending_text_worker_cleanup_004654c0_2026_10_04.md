# Ending-text worker cleanup: exact C++; constructor still pending

The ending-text constructor at 0x0040BA90 now has a complete typed native C++
candidate in `src/game/ending_text_constructor_0040ba90.cpp`. It represents the
0xEC-byte object, three timers at +4 / +0x18 / +0x2C, five animation ids at
+0x40, script at +0x54, flags at +0x74, color at +0x7C, and owned worker at
+0xD0. Size and worker-offset assertions check the representation. It creates
five glyph objects through the recovered pool, initializes scripts 0x42..0x46,
registers them, resolves their handles separately for width, height and flags,
restarts the three timers, and installs its script, flags and color.

Automatic worker ownership generates two complete matching cleanup functions:

| Address | Size | Selected C++ contribution |
| --- | ---: | --- |
| 0x004654C0 | 14 | Constructor unwind: destroy the worker at +0xD0 |
| 0x004654CE | 10 | Constructor exception handler |

The complete native unwind map and FuncInfo occupy 36 bytes at 0x0047155C.
All 36 bytes are validated against retail. Independent unmasked SHA-256 checks
confirm zero differences in both selected code windows, the exception data,
the 16-byte unselected worker destructor at 0x0044C130, and its 101-byte Stop
callee at 0x0044C150. No inline assembly, byte patching or masking is involved.

The old unwind assembly source was deleted. The handler had been misattributed
to the library wcerr.obj `_Copy` implementation; it now belongs to the actual
application constructor, retaining its prior record. That library member no
longer owns any maintained region and its translation unit was removed.

## Constructor measurement and limits

The constructor candidate emits 641 bytes versus retail's 648. The production
cluster therefore declares it as a complete, unselected 641-byte anchor. The
648-byte retail constructor remains assembly-owned in ending_text.cpp, and no
constructor bytes receive C++ recovery credit. The context's full contribution
is 22 bytes. The unselected registration helper is 114 bytes (retail 118), and
its gap begins at its actual end 0x00448A42. The pool allocator retains its
complete 161-byte extent. All helpers are declared at their measured complete
extents; none are truncated to their retail extent.

The first successful main-body probe (3) reproduces the prologue, timer flag
initialization, worker initialization, main clear, glyph setup, repeated list
lookups, timer restarts and epilogue operation sequence. Remaining differences
are a swap of the initial stack-local stores, the first returned-id copy
(retail loads EAX then copies it to ECX; candidate loads ECX directly), and
lookup-loop alignment. This changes the following branch displacements and
leaves the candidate seven bytes shorter. The native link's helper gaps were
then corrected before testing the cleanup independently, yielding EXACT for
both selected functions and all exception data.

Source variants 4..13 tested a non-POD id return, named id temporary, id-array
members, by-value id lookup parameter, explicit copy assignment, a grouped
cursor, a cursor with its id temporary, a void registration helper, memcpy for
the id copy, and a volatile id temporary. Most retain 641 bytes. The void
registration helper yields 648 bytes but passes its output on the stack and
changes the manager/object registers, so it does not match. None of those
variants was promoted. The retained constructor is the original scalar-id
candidate from probe 3. Further work should investigate the first handle-copy
IR and lookup-loop alignment rather than repeat these variants.

Live Ghidra decompilation confirms the fields, three stale-id-clearing lookups,
worker initialization and timer restart order. Source/layout snapshots, all
exploration outputs, disassembly and its diff, Ghidra output, the production
probe and independent hashes are retained under
`matching2/build/experiments/ending_text_2026_10_04`.

The normal full build passes outside the three preexisting equivalent C++
regions. Ordinary exact C++ now covers 2,187 regions / 162,091 bytes. Remaining
assembly is 130 regions / 127,488 bytes. The full objective remains incomplete.

The exact-mode full build passes too. Independent cmp confirms the complete
487,936-byte resulting executable matches retail byte for byte.

## Constructor resolved 2026-10-05

The constructor is byte-exact (648 bytes) and selected; `make` and
`make EXACT=1` pass. The loop indexes the member array (`handles[i]`) instead
of walking a separate `int* handle`. The stack-homed handle pointer in retail
is the compiler's own induction variable derived from `i`: it is initialised
after `i`, and the first id copy keeps the value in EAX while the lookup key
is copied to ECX. A source-level pointer gave the opposite store order and a
direct ECX load, seven bytes shorter.
