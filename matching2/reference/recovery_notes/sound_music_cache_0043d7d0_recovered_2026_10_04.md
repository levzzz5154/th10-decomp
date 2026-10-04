# 0x0043D7D0 music slot cache: recovered (2026-10-04)

`WaveSoundManager::CacheMusic(int slot, const char* name)` is exact ordinary C++
(369 bytes): `msvc/src/platform/sound_music_cache.cpp`, cluster
`msvc/layout/ltcg/sound_music_cache_0043d7d0.json`. Both `make -j2` and
`make EXACT=1 -j2` pass. Supersedes the Clang-tested candidate described in
`sound_music_cache_0043d7d0.md` (its behavioural description still holds).

## What it took

- **Convention** (manager ESI, name EAX, slot on the stack, RET 4): a noinline
  member called from a synthetic model of the two call sites in the music
  command handler 0x0043DDF0. No permutation needed.
- **Name copy loop**: `while ((*destination++ = *source++) != 0);` with
  `source` declared before `destination`. The pointer declared first is the one
  the loop walks; five other spellings walk the destination.
- **ReadFile argument registers** (`ecx` table, `edx` size, `eax` &received;
  the direct expression gives `edx, eax, ecx`): the track size is read through
  an inline accessor, `TrackBytes(this, index)`, for both `malloc` and
  `ReadFile`. Expression temporaries take EAX, ECX, EDX in strict rotation in
  pre-scheduling instruction order; a call in an argument list is sequenced
  ahead of the other arguments and keeps that place after c2 inlines it. A
  local variable for the size, or an inlined wrapper around `ReadFile`, is
  forwarded back into the argument and changes nothing. Using an accessor that
  returns the record by reference breaks the `malloc` block instead.
- The flag at 0x00491D78 is `Supervisor::flags` (+0x178).

## Controls

Changing `CloseHandle` to return void, removing it from the failure block,
moving or retyping `received`, and a `goto` shared failure exit all left the
ReadFile registers unchanged.
