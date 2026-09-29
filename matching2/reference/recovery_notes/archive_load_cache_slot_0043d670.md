# Music-table publication at `0x0043D670`

The 32-byte wrapper now builds from ordinary C++ in
`msvc/src/unidentified/unassigned_0043d670.cpp`. Its native MSVC 13.10 LTCG
probe matches every retail byte and relocation in the archive-loader cluster.
The earlier standalone Clang candidate in `semantic_candidates/` did not match.

The wrapper calls `Archive_LoadFile(filename, 0, 0)` and stores its result at
`manager + 0x1f84`, the loaded music metadata image. It returns 0 for nonnull
or -1 for null. It stores null too, overwrites any old pointer without freeing
it and does not validate the loaded bytes as music metadata. The loader's
zero mode selects the cached DAT path, not a direct disk open.

Retail takes filename in EAX and manager as one stack argument with RET 4.
The native LTCG cluster compiles two explicit stdcall source arguments into
that private convention, including the EAX filename forwarded to
`Archive_LoadFile` and the same RET 4. The synthetic compiler context keeps
this transformation live; the standalone Clang candidate produced 37 bytes
and RET 8 rather than retail's 32 bytes.

The [music-cache differential suite](sound_music_cache_0043d7d0.md) tests this
wrapper alongside music caching. Its wrapper cases cover local/global manager
objects, null/non-null loader results, previous field values, changes to the
metadata field during the loader callback and null-owner faults. Even an
invalid owner invokes Archive_LoadFile before the pointer store faults. No
extra free or input check was introduced.

Saved Ghidra and maintained instruction evidence are checked against the
verified retail image. The suite observes complete manager/data state,
loader arguments, results, faults, preserved registers and stack cleanup.
The wrapper's Archive_LoadFile call is scripted in this suite; the maintained
loader and DAT closure have separate full integration coverage described in
[sound_preload_worker_0043d080.md](sound_preload_worker_0043d080.md).

`probe.py --source src/unidentified/unassigned_0043d670.cpp` reports EXACT
for the wrapper and all selected archive-loader functions. The production
region and LTCG layout now select this C++ body instead of inline assembly.
The whole-image `make` gate also passed: 487,936 executable bytes matched
retail. Overall progress remains 1,771 C++ regions and 532 inline-assembly
regions; this conversion does not make the executable assembly-free.
