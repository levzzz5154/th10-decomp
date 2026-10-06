# MIDI parser native compilation, 2026-10-06

The complete ordinary-C++ candidate at
`reference/semantic_candidates/midi_event_runtime.cpp` has now been compiled
with the real MIDI decoder and header-completion bodies under MSVC
13.10.6030 native LTCG and the shared project flags. This supersedes the
syntax-only disposition in `midi_event_parser_followup_2026-09-30.md`.
It remains outside the production inventory: the parser has not matched.

The parser is the link entry, retaining its two stack arguments and RET 8.
The joint graph also retains the existing tick/volume compiler context via
`/INCLUDE:_MidiTickContext@12`. No parser callback trampoline, inline assembly,
per-source compiler flag, register constraint, or instruction-byte edit is
used. Models are linked at two image bases to identify relocation fields;
only diagnostic comparisons rebase those fields and known helper targets.
These model bytes are never supplied to the game build.

The first candidate emitted a 1474-byte contribution with only the controller
dispatch table. Expressing the two message-type dispatches as switches emits
all three pointer/index table pairs. The retained candidate also:

- Uses `memset` for the 64-byte Win32 header, producing retail's `rep stosd`.
- Reloads the SysEx header through its sequencer slot after allocation and
  assignment, matching retail's separate header-index accesses.
- Calls each typed import without an artificial volatile function-pointer
  read, producing the direct memory-indirect IAT calls.
- Traverses a cached track pointer for loop save/restore, advancing 32 bytes
  per track while reloading the sequencer's track count.
- Computes channel addresses within the selected event case rather than
  computing and preserving an unused channel address before dispatch.

The retained `cached_tracks_joint` model has 1311 code bytes, one alignment
byte and 346 table bytes, versus retail's 1323 + 1 + 346. All three compressed
byte tables match their complete retail extents (113, 65 and 94 bytes).
The pointer-table targets and full code still differ; those byte-table
matches do not establish parser equality or validate every branch target.
The aligned instruction comparison has 47 difference hunks. Raw overlapping
code has 1246 differing bytes, largely because block addresses differ; that
number is not a recovered-prefix metric.

The joint build independently compares these complete existing bodies:

| Function | Bytes | Differing bytes |
| --- | ---: | ---: |
| ReadMidiVariableLength, `0x0043A730` | 26 | 0 |
| CompleteMidiHeader, `0x0043AEB0` | 79 | 0 |
| ApplyChannelVolumes, `0x0043B7A0` | 140 | 0 |
| ResetTracks, `0x0043ACE0` | 132 | 0 |
| Tick, `0x0043AF30` | 473 | 7 |

Thus the actual parser callers naturally derive cursor-address ESI and
sequencer EDX / header ESI for the two private helper edges. Giving the tick
the complete parser body does **not** resolve its already-recorded three-
instruction address-calculation difference at `+0x100`. No additional
recovery credit or equivalence allowance was introduced.

Lexically ordering the switch blocks, removing the packed-message initializer,
copying the loop clock with `memcpy`, sharing the channel byte with metadata,
reordering the data-byte initialization and introducing a named error result
were also measured. None matched. The uninitialized packed-message controls
reuse the incoming track-pointer slot but change register allocation; they
are experiments only. The maintained candidate preserves its explicit
track-pointer initialization and resulting fourth message byte.

The remaining parser work includes the initial parameter/byte spill homes,
SysEx boolean-result normalization, physical switch-block ordering, loop-
clock load/store scheduling and final message packing. Retail loads the
sequencer before reusing its incoming stack slot for the second data byte;
the retained candidate keeps that byte in a separate local and has a
16-byte frame instead of 12. These are measured source/compiler differences,
rather than missing dependencies or an external blocker.

All source controls, full native executables, maps, complete function bodies
and comparisons are preserved under
`build/experiments/midi_parser_native_2026_10_06/`. `joint.py` rebuilds both
full-graph controls. `cached_tracks_joint/comparison.json` records the retained
candidate and all six complete body comparisons. The earliest baseline's
helper report used an incorrect 43-byte requested extent for the decoder;
all subsequent reports use its authoritative 26-byte production extent.
