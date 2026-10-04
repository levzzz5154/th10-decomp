# Sound-stream allocation cleanup 0x00465330: EXACT

The complete readable native model for file-stream creation, previously parked
in `reference/semantic_candidates/sound_stream_create_file_native`, now supplies
only the selected allocation unwind and its handler. The factory and launch
remain complete unselected anchors; their retail assembly remains owned.

The natural new expression generates the eleven-byte unwind at 0x465330,
loading the raw stream allocation from [EBP-0x48], and the ten-byte handler at
0x46533B. Its complete 36-byte unwind map and FuncInfo at 0x471390 also match.
Independent unmasked SHA-256 comparisons agree for all three spans.

The former handler region contained its ten-byte body plus a final INT3.
That INT3 at 0x465345 is now part of the following contiguous eleven-byte
padding run. No function is truncated or treated as padding to obtain a match.
The previous region records are preserved in the manifest.

## Native context and bounds

The shared type header adds declarations for the actual cursor Open, manager
LaunchMusic and StopMusicWorker methods, without changing any object layouts.
The compiler context contains the complete launch, worker stop, cursor opener,
stream constructor, refill, rewind and read implementations. The 692-byte
factory, 241-byte launch, and 52-byte caller context have their full measured
extents and gaps validated. Factory export is confined to the compiler rig and
preserves its observed ECX/EDX fastcall ABI; its export is not selected into the
final executable. A selected-function root in the prior exploration had the
same machine contract.

Ghidra's live 0x44C8F0 decompile and retail handler-pointer search confirm ownership.
The factory is still 692 bytes versus 702 retail bytes: no recovery of its main
body is claimed. Existing notes describe its remaining segment-count register
allocation problem. Do not redo the count-as-pointer experiment merely to force
allocation; keep the actual integer count semantics.

Evidence and scratch probes are in
`matching2/build/experiments/sound_stream_allocation_cleanup_2026_10_04`.
Scratch project is `/tmp/th10-sound-file/msvc`. Production cluster probe EXACT.
Both full builds pass. Default is exact outside the three existing equivalent
C++ regions; `make EXACT=1` reports Whole EXE exact: 487,936 bytes. Independent
`cmp` against retail exits successfully. Remaining assembly: 127 regions /
127,455 bytes; ordinary exact C++: 2,191 regions / 162,133 bytes.
