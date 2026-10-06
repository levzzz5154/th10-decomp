# WAVE loader C++ equivalence recovery, 2026-10-05

Superseded by [the byte-exact promotion](sound_wave_load_exact_2026_10_06.md).
The source and layout paths below describe the former equivalent checkpoint.

The complete 684-byte loader at `0x0043D390` is now selected by
`layout/equivalent/sound_wave_load_0043d390.json`. The default build uses
`equivalent/platform/sound_wave_load_0043d390.cpp`; the exact build keeps its
assembly owner. This is an equivalent recovery, not a byte-exact promotion.

The model preserves the native source checkpoint in
`semantic_candidates/sound_wave_load_native/`, including two volatile pending
pointer reads, the cached Sleep import, explicit parse-error cleanup, 18-byte
format snapshot, and two forward buffer copies. Chunk and log definitions
establish their private compiler ABIs; the selected function's calls bind to
their existing production addresses. An escaping function pointer preserves
the loader's ECX=index, EDX=manager, stack filename, RET 4 public boundary.

All but one of 225 instructions match. The single `code-shape` difference at
offset `0x11A` is:

```text
retail: add ebp,0xfffffff4
C++:    sub ebp,0xc
```

For every initial 32-bit EBP value, both produce `(EBP - 12) mod 2^32`.
No other register or memory is modified. Carry/auxiliary-carry differences
are dead: the following PUSH/MOV/LEA/MOV/CALL neither consume them nor branch,
and the real chunk helper's prologue is
`push ebx; push ebp; mov ebp,[esp+0xc]; mov ebx,eax; test ebx,ebx`.
TEST replaces the arithmetic flags before its first conditional branch.
After the helper returns, the loader tests EAX before branching. Thus neither
callee nor caller observes the differing incoming flags. No input range
restriction or overflow assumption is required for this equivalence.

The existing checker rejects any drift outside that exact instruction pair.
No frame offsets, base/index substitutions, unproven branch targets, ABI
changes, truncation or compiler-output rewriting are accepted.

## Native differential validation

The existing `sound_wave_load_differential.py` now has a
`--native-equivalent` mode. It compiles the maintained model through the strict
equivalence gate and executes the resulting relocated bytes at `0x0043D390`,
using the actual retail chunk walker, CRT comparison and cookie-check helper.
The older Clang fixture remains available through the default mode.

All **396 native comparisons pass**, including **eight matching memory
faults**. Cases cover pointer handoff races, cancellation precedence, cached
imports, Release/Lock callbacks that change slots, malformed RIFF data,
short/odd chunks, HRESULT signs, split/overlapping copies and ownership of
the captured wave. The fixture compares manager/output memory, calls, return
values, frees, reads, stack/register preservation and fault details. Sleep,
DirectSound, log and free collaborators are scripted; no live audio device
or general thread interleaving is claimed.

```sh
python3 matching2/tests/sound_wave_load_differential.py --native-equivalent
```

Requires Unicorn; the local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Both full image
gates are run after integration with the atlas-text recovery.
