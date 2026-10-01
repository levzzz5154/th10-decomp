# Buffered-file seek semantics

2026-09-26. The assembly-free candidate at
`semantic_candidates/buffer_file_seek.cpp` passes **8,466 retail comparisons**
for the 107-byte routine at `0x004364F0`. It implements the maintained
BufferFile class's thiscall method, preserving ECX receiver, distance/origin
stack arguments, RET 8 and the AL result.

## Recovered rules

Saved Ghidra pseudocode/instructions and the verified retail function agree:

| Origin | Accepted distance | New position |
| --- | --- | --- |
| 0, start | signed distance is nonnegative and unsigned distance is less than size | data + distance |
| 1, current | signed distance is less than signed32(data + size - position) | position + distance |
| 2, end | signed distance is nonpositive and its unsigned magnitude is less than size | data + size + distance |
| Other | never | unchanged |

All address arithmetic wraps at 32 bits. Every failure returns AL zero and
leaves the complete object unchanged. Success changes only position and
returns AL one; the other EAX bytes are not part of the BYTE result contract.

These rules differ across origins. Start/current seeking exactly to the end
fails. End-relative distance zero succeeds for nonempty files and stores the
end pointer. Current-relative seeking has no lower-bound check, so a negative
distance can move before the allocation. Its signed remaining-count comparison
also matters when the wrapped remaining value has its high bit set.

The candidate uses explicit DWORD address arithmetic to preserve these results
without C++ out-of-allocation pointer arithmetic. Unsigned subtraction forms
the magnitude of a negative distance, including `LONG_MIN`: magnitude
`0x80000000` is accepted when the size is larger. Earlier approximate source
used signed unary negation at this edge, which can overflow in C++.

## Validation

```sh
python3 matching2/tests/buffer_file_seek_differential.py
```

The test compiles the actual candidate with native Clang for x86 Windows,
verifies the retail oracle, then executes both functions under Unicorn. A
boundary matrix covers null/high/wrapping addresses, zero/small/large sizes,
positions around both buffer ends, signed distance limits, and invalid origins.
Three thousand seeded random cases extend the matrix. Six explicit expected
results independently establish strict end bounds, before-start movement,
signed remaining-count rejection and the LONG_MIN magnitude case.

Each call compares AL and position, verifies all other object bytes and guards,
and checks stack cleanup and callee-saved registers. Both emulators are reused
across cases, with input fields and call state reset for every call. No file
contents or OS collaborators are needed because the routine only changes the
position field. The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`.

The Clang body is 91 bytes and is not a native MSVC byte-match result. Earlier
native-MSVC investigations are preserved in the
[wave-16 note](buffer_file_seek_004364f0_wave16.md): their closest 107-byte
source differed in seven bytes around tail ownership/register allocation.
This new arithmetic-explicit candidate has not passed the native region or
whole-executable gates. Production stays assembly until those checks succeed.

## 2026-10-01 retry

Fourteen more shapes (per-case stores with `break`, shared `base` after the
switch, `goto` into the end-origin tail, descending case order, `optimize("s")`)
all produce the right instructions per case.  None reproduces retail's block
ownership: retail lets the current-origin case jump *back* into the
end-origin store (`jg 0x43651a`) and keeps the failure block between it and
the start-origin case, whereas MSVC here either clones the store into the
current-origin case or moves the shared store into the start-origin case.
