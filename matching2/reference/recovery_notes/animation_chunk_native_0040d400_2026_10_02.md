# Animation-chunk parser at 0x0040D400

The complete 239-byte routine is now readable, inline-assembly-free C++ in
`msvc/src/unidentified/FUN_0040d400_0040d400.cpp`. The maintained native probe
and the incremental whole-executable gate both pass. The rebuilt EXE is all
487,936 retail bytes, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The entry is public thiscall: receiver ECX, one chunk pointer on the stack,
integer result EAX, RET4. The actual dispatch table at 0x0046D0B4 contains
0x00450220, this entry, and 0x0040CD20. The source represents those three
virtual slots and uses the genuine typed enemy-manager animation file array.
It loads ANIM resources into animation_files[index + 1] through the existing
fastcall cache loader and reports the first failure. After aligning the cursor
to a four-byte offset relative to the original chunk, it invokes virtual Load
for each name in an optional ECLI chunk.

Three source details resolve the full native body. A guarded counted do-loop
initializes the resource-table cursor only when the count permits an iteration.
Repeating the signed alignment expression lets the compiler reuse EAX directly,
matching the retail modulo calculation. Indexing the actual manager array
provides the correct address expression through ordinary strength reduction;
the earlier manual byte-offset model differed by one equivalent SIB byte.
No instructions or operands were rewritten.

The dedicated schema-1 layout compiles the entire real front.anm loader at
0x00413B50 as its unselected no-argument entry and the complete TextLog::Append
at 0x0044B810 as its unselected helper. All 50 and 201 helper bytes also match
retail. Those existing owners receive no new credit. The logger graph derives
its private ECX variadic receiver naturally; no dummy argument, synthetic
caller, added volatile, or scheduling barrier is used. Shared headers and all
other maintained owners are unchanged.

Evidence is in
`build/experiments/animation_chunk_0040d400_20261002/maintained.json`, its full
native cluster report, and `whole_verification.json`. The whole build reused
1,607 units, compiled three, and reported zero failures. Recovery credit is
only 239 bytes. Progress now records 140,564 semantic bytes; the direct-source
assembly audit excludes six older mixed routines (4,525 bytes), leaving
136,039 bytes with asm-free selected-body source and 187,092 bytes still
containing assembly across 219 selected regions. The full goal remains open.
