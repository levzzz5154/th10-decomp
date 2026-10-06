# DirectSound initialization 0x0043CD30: byte-exact C++ recovery

`msvc/src/platform/sound_device_init.cpp` now owns the complete 786-byte
initializer as readable, assembly-free C++. The public member
`WaveSoundManager::Initialize` receives the manager in ECX and the window on
the stack, returns an integer in EAX, and uses RET 4. The existing assembly
aliases still bind to 0x0043CD30 for callers awaiting further recovery.

The routine initializes all 128 sound handles and twelve music handles,
allocates and configures the device-owner cell, sets the primary PCM format,
creates the streaming buffer, clears its fixed first 32 KiB span, starts looping
playback and the Windows timer, then preloads 37 WAVE files through the global
manager. It preserves the original failure ownership and callback-visible
reloads documented in `sound_device_init_0043cd30.md`, including the allocation
failure dereference and retention of the owner/buffer on late failure.

The recovery reuses the maintained complete sound-manager, DirectSound method
tables, packed WAVE format and buffer-description types. Local compile-time
checks additionally cover the allocated owner cell, all accessed manager fields
and the Create/Cooperative/Lock/Play/Unlock method slots. It uses ordinary
`memset` for the original 8192-dword clear and ordinary owner-cell accesses;
no added volatile qualifier or compiler barrier is required. The existing
shared shutdown/pending-WAVE fields retain their synchronization qualifiers.

## Complete native helper graph

`layout/ltcg/sound_device_init_0043cd30.json` includes complete C++ bodies for
the primary-format setter, WAVE loader, chunk walker and text log. Only the
initializer is selected as new game code. Native LTCG derives the actual
register homes from the logical helper declarations; the initializer is
explicitly rooted to preserve its public member entry. A direct compiler caller
has a complete 17-byte contribution and no recovered game ownership.

The context's WAVE loader uses logical inputs `(manager, index, filename)` with
an ordinary stdcall declaration. Its native body still receives index in ECX,
manager in EDX and filename on the stack, and matches all 684 retail bytes.
This source order also gives the initializer its original
`MOV ECX,ESI; MOV EDX,0x492590` call setup. The primary-format context uses logical
inputs `(channels, rate, bits, owner)`; its native body still uses channels BX,
rate EDI, bits CX and one stack owner cell, matching all 260 retail bytes.
The separately maintained public WAVE-loader and primary-format source owners
and their existing signatures are unchanged.

Thus the historical immediate-copy-order diagnosis in `0043cd30_wave11.md`
was limited to the tested opaque/fixed-home declarations. Its general claim
that no source declaration or visible callee could reproduce the site is
superseded by this complete equal caller/callee graph. No compiler replacement,
per-source flag, output rewrite or matching allowance was needed.

## Source-shape evidence

The first complete native model emitted 746 bytes. Allocating a typed owner
with its zeroing constructor reproduced the allocation branch. Its inlined
`Configure` method reproduced the retail failure/return graph and restored the
full 786-byte extent. Zero-initializing both descriptor and format before setting
their fields corrected the local initialization order. Setting descriptor fields
before PCM fields, and setting `extra_bytes` before the other PCM fields, removed
the remaining store scheduling differences. The helper parameter orders above
removed both argument-materialization differences while preserving the helpers'
complete byte matches.

Full candidate sources, contexts, maps, images, emitted bodies and comparison
receipts are retained under
`matching2/build/experiments/sound_device_init_exact_2026_10_06/`.
`format_extra_first/` is the first equal relocated native model.
`native-probe-complete-context/` proves the complete fixed-address graph;
`integrated-probe/` proves the final maintained source with its offset checks.
Preparatory failed declaration/layout checks are diagnostics, not matching
proof. The context's initially guessed 16-byte size was corrected to its actual
17-byte compiler contribution before promotion; no selected region was padded
or truncated.

`native-helper-audit.json` records independent full-byte comparisons of all
five bodies: initializer 786, chunk walker 71, WAVE loader 684, log 201 and
primary-format setter 260. `integrated-helper-audit.json` repeats this check
against the final maintained cluster. Each is exact, with zero differing bytes. Helpers
receive no additional recovery credit because their production owners already
existed. The compiler uses no oracle bytes to build any contribution.

Validation on 2026-10-06:

- Scratch and maintained strict probes: all 786 bytes EXACT, including the whole
  native contribution and every linker-filled target.
- Complete native helper audit: all four helpers also match their full retail
  extents and bytes.
- `make`: full-image and eight existing equivalence gates passed.
- `make EXACT=1`: all 487,936 executable bytes exact.
- `git diff --check`: passed.

Progress: 2,247 ordinary C++ regions / 191,372 bytes; 8 equivalent regions /
33,176 bytes; 67 remaining assembly regions / 96,935 bytes. The full readable,
byte-exact, assembly-free objective remains incomplete.
