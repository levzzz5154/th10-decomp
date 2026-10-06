# Sound initialization and preload

The maintained [native C++ recovery](sound_device_init_exact_0043cd30_2026_10_06.md)
now matches the complete 786-byte initializer and every helper body in its
compiler context. The behavioral work below remains useful; its native-byte
limitation and assembly disposition are historical.

2026-09-26. The complete 786-byte initializer at `0x0043CD30` is recovered in
`semantic_candidates/sound_device_init.cpp`. It passes **354 individual retail
comparisons, including eight matching faults**, and **30 integrated startup
scenarios with 709 actual WAVE preloads and one matching fault**. The candidate
uses the existing thiscall entry shape: ECX manager, one stack window argument,
RET 4, and int result. Production remains assembly.

## Evidence and shared types

The saved Ghidra C and full instruction listing, maintained retail body and
verified executable establish the routine's behavior. Live Ghidra MCP requests
remain rejected by this session's approval policy. Older startup notes focus
on a compiler argument-copy-order difference; they did not reconstruct and
validate this complete function.

`semantic_candidates/sound_wave_types.hpp` now supplies the shared manager,
DirectSound method tables, packed 18-byte WAVEFORMATEX image, 36-byte buffer
description and TextLog declaration. The previously tested WAVE loader now
uses this header and still passes all 396 comparisons. Fields touched here are:

| Offset | Field |
| --- | --- |
| `0x0000` | raw DirectSound device |
| `0x0008` | 256 secondary-buffer pointers |
| `0x0408` | 128 sound handles |
| `0x0608` | streaming buffer |
| `0x060c` | window |
| `0x0610` | allocated device-owner cell |
| `0x0618` | stream cursor |
| `0x0620` | 12 music handles |
| `0x5230` | 37 pending WAVE pointers used by startup |
| `0x52c4`, `0x52c8` | volume words |

The shared layout now also names the [shutdown](sound_shutdown_0043d120_0043dab0.md)
fields. Offset `0x0618` is a union: the initializer zeros its stream cursor,
while music-stream mode stores the worker handle there. New field/COM-slot offset
assertions compile for all sound candidates; the startup suite still passes.

## Startup and failure ownership

The initializer first sets every sound/music handle to -1. It allocates a
four-byte device-owner cell, zeros a nonnull cell, stores it into the manager,
then reads it even if allocation returned null. The candidate preserves that
fault and the preceding manager-field write. The former owner cell is simply
overwritten. A controlled memory-read case also injects an existing device
after the cell is zeroed; retail and candidate release it and clear the cell.

The actual Ordinal_11 import thunk creates the DirectSound device, followed by
SetCooperativeLevel(window, 2). A negative result from either logs the message
at `0x46FE0C`, reloads the manager's current owner cell, releases its current
device if present, clears/frees that cell and clears the manager field. Logging,
Release and free callback mutations confirm which pointers are cached and
which are reloaded. A nonnegative HRESULT is accepted.

The [primary-format helper](sound_primary_format_0044c7e0.md) receives 16 bits,
two channels and 44100 Hz. Its result is ignored. The manager then copies the
device from its current owner cell, zeros the stream cursor and creates the
stream buffer with a zeroed 36-byte description, flags `0x8008`, 32768 bytes,
and the 18-byte PCM format `{1, 2, 44100, 176400, 4, 16, 0}`.

A stream Create/Lock failure returns -1 without the earlier device-owner
cleanup or error log. Lock is requested with offset zero, 32768 bytes and
flags zero. Regardless of the returned region lengths, retail writes **8192
zero dwords to the first region only**. It neither limits this to first_bytes
nor clears a second region separately. Tests include shorter reported regions,
unaligned pointers and an output-boundary fault with preceding writes retained.

Unlock receives the reported pointers/lengths and a freshly loaded stream
interface. Play reloads it again and uses `(0, 0, 1)`. Both results are ignored.
The volume words are set to 100 before SetTimer(window, 0, 250, 0). The timer
result is ignored; the window field is written after the call, so a callback's
window change is overwritten while changes to the volume fields remain.

## Global preload behavior

Each of the 37 filenames comes from `0x474B40`. Before each load, a shutdown
word exactly equal to 2 aborts with -1. The loader receives the **global
manager at `0x492590`**, even if initialization was invoked on another object.
A nonzero WAVE-loader result logs `0x46FDD4` and returns -1. That error path
reloads the filename table after the call; tests replace its entry during the
failed load and require the new name in the diagnostic.

After all 37 loads, the initializer logs `0x46FDAC` and returns zero. Shutdown
set during the last successful preload is not checked again. Shutdown during
an earlier preload stops the next iteration. None of these late exits releases
the already-created device or streaming buffer.

## Validation

```sh
python3 matching2/tests/sound_device_init_differential.py
```

Individual cases script the helper boundaries to vary HRESULT signs, returned
pointers, reported lock regions, shutdown timing, filename changes and state
changes during callbacks. They compare full local/global manager bytes, owner
cells, filename pointers, output bytes, ordered calls, return values and fault
details. Normal calls verify stack cleanup and callee-saved registers. Separate
fixture assertions require complete handle initialization, exact format and
description bytes, the fixed first-region clear, global-manager dispatch,
filename reloading and retained owner state on late failures.

Integrated cases freshly compile the initializer, primary-format setter,
pending-WAVE loader and maintained chunk walker. Candidate calls bind directly
to those implementations; the retail run executes their original bodies.
Thirty scenarios exercise successful startup, a separate receiver, allocation
failure, primary-format failures that startup ignores, stream failures,
malformed pending waves, secondary Create/Lock failures, cancellation and
changed stream interfaces. The 37 pending images use varied PCM payloads and
16/18-byte fmt chunks. All 709 executed preload calls traverse the real WAVE
parser and copy path, with independent checks on the copied PCM bytes.

Only allocation/free, DirectSound, logging and Windows timer/sleep boundaries
are scripted in integrated cases. The Ordinal_11 thunk, CRT comparison and
retail cookie checks execute. The Clang initializer module is 914 bytes, not
a byte match for the retail 786-byte region. The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`.

Native MSVC frame/bytes, private helper/log entry conventions, real DirectSound,
Windows exception dispatch and general concurrent startup remain unverified.
The [historical argument-copy-order investigation](0043cd30_wave11.md) still
applies to native byte recovery. No source or manifest gate was relaxed.
