# Archive-load pending slot helper at `0x0043D640`

2026-09-26. The 37-byte helper now has a tested ordinary C++ candidate in
`semantic_candidates/unassigned_0043d640.cpp`. Production still uses the
original assembly in `msvc/src/unidentified/unassigned_0043d640.cpp`; the
earlier note's semantic-promotion claim does not describe the current manifest.

The helper calls `Archive_LoadFile(filename, 0, 0)`, stores the returned pointer
at `owner + 0x5230 + index * 4`, and returns 0 for nonnull or -1 for null. It
stores null too, does not free an existing pointer and does not bound the index.
The candidate computes the slot address with unsigned 32-bit arithmetic to
preserve wraparound, including negative indices and multiplication wrap. It
uses shared sound manager types and a volatile pending-pointer store.

Retail supplies filename in EAX and owner/index on the stack, returning with
RET 8. The candidate exposes three stdcall arguments with RET 12. The loader
also has a private EAX filename input in retail. Neither convention is claimed
recovered by Clang behavioral compilation. The candidate occupies 44 bytes,
compared with retail's 37.

`tests/sound_preload_worker_differential.py` tests this helper together with the
[37-slot producer](sound_preload_worker_0043d080.md): 167 comparisons include
negative/out-of-range/wrapping indices, null results, overwritten pointers,
callback mutations, two matching null-owner invalid writes, stack cleanup and
preserved registers. Null-owner cases invoke the loader before the invalid
store, matching retail.

`tests/sound_archive_preload_integration.py` executes five helper calls through
the maintained cached loader and recovered DAT closure. Four resulting buffers
pass through actual WAVE parsing and PCM copying. Publishing twice to one
pending slot loses the first allocation without freeing it; the fixture records
that ownership explicitly. Existing secondary COM buffers are released when
the WAVE consumer later replaces them.

Live Ghidra confirms the retail wrapper's two stack loads after the archive
call: owner into ECX from `[ESP+4]`, index into EDX from `[ESP+8]`, then a
single indexed pointer store. A native MSVC 13.10 LTCG trial with the same
loader cluster generated an exact 37-byte extent and control flow, but loaded
index into ECX and owner into EDX instead. Making both parameters volatile
added an address LEA and increased the body to 39 bytes. Neither trial was
promoted; the production region remains inline assembly. The neighboring
32-byte music-table wrapper at `0x0043D670` now matches as ordinary C++.
