# Pending WAVE loader

2026-09-26. `semantic_candidates/sound_wave_load.cpp` recovers the complete
684-byte routine at `0x0043D390` as ordinary C++ with typed manager fields,
DirectSound vtables, format/description records and buffer-copy loops. It
passes **396 retail comparisons, including eight matching memory faults**.
Production remains the exact assembly body pending native MSVC verification.

## Evidence and interface

Saved Ghidra C and instruction listings for `0043D390` and `0043D250`, the
maintained chunk-search source, and verified retail instructions establish the
behavior. A fresh Ghidra MCP decompilation request remains rejected with
`MCP tool call requires approval, but approval policy is never`.

The public entry is expressible directly: fastcall index in ECX, manager in
EDX, filename at [ESP+4], RET 4, and int result. The manager's device is at
offset 0, secondary-buffer table at 8, device-owner cell at `0x610`, and
pending-wave pointers at `0x5230`. The startup caller preloads 37 entries; the
candidate describes that observed portion of the pending table.
These manager/COM/format types now live in `semantic_candidates/sound_wave_types.hpp`
and are shared with the [full initializer](sound_device_init_0043cd30.md). Its
integration suite executes this loader through 709 actual preload calls.
The [archive producer integration](sound_preload_worker_0043d080.md) separately
executes 672 WAVE handoffs from buffers loaded through actual DAT decoding.

The chunk helper's native private convention remains ECX data, EAX byte count,
EDI output-size pointer and one stack tag. The test compiles its maintained
C++ source with an ordinary cdecl interface and links the candidate loader
directly to it. TextLog Append is also an ordinary C++ declaration in the
candidate; the fixture accounts for its explicit stack receiver, compared with
retail's ECX receiver. These helper ABI differences are not hidden by a byte
match claim.

## Ownership and pending handoff

An absent device-owner cell returns zero immediately. Otherwise, an existing
secondary buffer is released and its slot cleared, including when Release
changes that slot during the callback. While the pending wave is null, the
loader calls Sleep(10), then checks whether the shutdown word at `0x4977B4`
equals 2. Cancellation returns zero without consuming a newly published wave.
A nonnull pending wave at entry bypasses the shutdown check.
The imported Sleep pointer is cached once before the loop. Changing the import
slot during the first Sleep does not redirect subsequent iterations; a test
checks this explicitly.

After observing readiness, retail rereads the pending pointer, then clears the
slot. The candidate's volatile pointer accesses retain that second read. The
test explicitly clears the pointer between the readiness read and the handoff:
both implementations return -1 without logging or freeing a null wave.

Every normal parse/create/lock result after acquiring a nonnull wave frees
that captured pointer exactly once. Create or Lock failure returns -1 but
does not release or clear any buffer they placed in the manager slot. Unlock's
result is ignored. The slot is reread before Unlock, so a Lock callback that
replaces it changes the interface receiving Unlock. Cancellation does not free
the pending image. Exceptions and memory faults do not gain an invented RAII
cleanup path.

## RIFF and DirectSound details

RIFF and WAVE tags are compared with the actual CRT strncmp. Non-RIFF input
logs the message at `0x46FD88`; a bad WAVE tag or missing fmt/data chunk uses
`0x46FD64`. Both include the supplied filename and log object at `0x474F70`.

Retail supplies **stored RIFF length minus 12**, modulo 32 bits, to both chunk
searches. It does not clamp the count or replace this with conventional RIFF
length-minus-four arithmetic. The chunk walker advances by header plus payload
without even-byte padding or bounds checks; a nonzero counter can underflow
and continue reading. The test covers those faults and odd-length chunks.

The loader copies **18 bytes from the fmt payload regardless of its declared
length**. In a common 16-byte PCM fmt chunk, the final two bytes therefore
come from the following chunk header. There is no minimum-size check or
zero-filled short format. The copied WAVEFORMATEX image is packed to 18 bytes.

CreateSoundBuffer receives a zeroed 36-byte description with flags `0x80C8`,
the data chunk's byte count, a pointer to the format snapshot, and zero
algorithm GUID. Negative HRESULT values indicate failure; positive values
continue. Lock receives offset zero, the cached data byte count and flags zero.
It supplies two region pointers and lengths, which are trusted even if their
sum exceeds the declared PCM size. Copies use forward four-byte snapshots and
remaining byte copies, preserving overlap rather than substituting memmove.
The second source begins after the first reported region length.

## Validation and remaining work

```sh
python3 matching2/tests/sound_wave_load_differential.py
```

The test compiles fresh x86 Windows COFF with native Clang and uses Unicorn.
The loader module occupies 801 bytes; the separately compiled chunk walker
occupies 83. These are behavioral fixtures, not MSVC byte matches.

Comparisons cover disabled startup, release ordering, delayed publication,
shutdown precedence, the two-read handoff race, indices 0/1/36, HRESULT signs,
null Create output, changed buffer slots, changed description bytes, raw and
split PCM, zero-length regions, overlap, oversized lock lengths, short fmt
chunks, unknown odd-length chunks, malformed input and seeded random waves.
They compare full manager/data/output bytes, ordered collaborator calls,
format/description contents, frees, pending reads, results, memory faults,
stack cleanup and preserved registers. Independent fixture assertions check
the length arithmetic, 18-byte format snapshot, PCM copies and error ownership.

Only Sleep, DirectSound, logging and free are scripted. The actual retail
strncmp and security-cookie helper execute. The local Python environment is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. No audio device,
Windows exception dispatch or general concurrent execution is exercised.
Native MSVC stack-cookie/frame matching and whole-executable verification are
still required before promotion. The archived environment-based loader is an
older approximate model and is not evidence for the behavior above.


## Native MSVC follow-up (2026-10-02)

The native candidate in `semantic_candidates/sound_wave_load_native/` emits
the correct 684-byte extent, stack frame and helper ABIs. The best probe
matched 682 of 684 bytes without relocation exclusions. At 0x0043D4AA retail
emits `83 C5 F4` (ADD EBP,-12); the candidate emits `83 ED 0C` (SUB EBP,12).
All other bytes match, including both helper calls and buffer copies. The
production manifest retains the verified assembly implementation pending
resolution of that encoding difference. No compiler-output patching was used.

The snapshot mirrors `matching2/msvc/`: it contains the source, private type
header, native helper/context sources and cluster specification needed to
reproduce the probe after temporarily registering the cluster and semantic
region in regions.json. Native probe evidence remains under
`matching2/build/probes/sound_wave_load/`.

Key compiler constraints: explicit early parse-error exits retain the retail
frame; intrinsic memcpy reproduces the 18-byte format snapshot; staged cursor
advances retain the initial LEA/add pair; the chunk helper declaration orders
arguments as data, output size, byte count, tag to recover ECX/EDI/EAX inputs
and the retail caller move order. Integer subtraction/addition variants still
emit SUB 12. Pointer-distance and disabled-global-optimization probes changed
other code and were rejected.
