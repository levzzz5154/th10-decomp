# Word byte reversal at 0x0043A700

Ghidra decompilation confirms a 37-byte `RET 4` function that reverses the
four bytes of its stack argument. Earlier MSVC 13.10 source probes compared
several readable forms and retained the exact assembly when those candidates
missed. The reference tree contains a direct masked-shift C++ model. An offline
Clang probe of that spelling and a second local-buffer spelling is recorded
below; neither matched the complete retail body.

Ghidra decompiles a 37-byte `RET 4` function that reverses the four bytes of
its stack argument. Retail reserves one local word with `push ecx`, loads the
argument once, copies it to ECX and EDX, shifts those copies by 24 and 16,
writes CL, DL, AH, and AL into the local word, then returns it in EAX.

Readable C++ union, byte-array, aggregate-initializer, and pointer-alias
versions were compiled in earlier attempts. Straight scalar shifts made MSVC
reuse the argument's stack slot and emit a 42-byte body. Addressing the
argument's bytes forced a separate local slot but emitted a 34-byte body using
two source loads and different shift order. A volatile argument forced the
retail `push ecx` prologue but repeated argument loads, yielding a 48-byte
body. Mixed pointer and shift versions did not reproduce all 37 bytes. The
current masked-shift spelling is a semantic model, not an exact-output claim.

The next compiler experiment should preserve a separate local word while
loading the argument once and keeping its original value in EAX through the
four byte stores. Behavior and function boundary are clear; exact code
generation remains open.

## Offline compiler probes (2026-09-30)

Because Wine cannot start a `wineserver` in this sandbox (`bind: Operation not
permitted`), these probes used the pinned local Clang and LLVM assembler, with
the retail image only as the comparison oracle. The standard Clang profile
also exposes an assembler issue for this C `__stdcall` symbol: with
`-ffunction-sections`, LLVM MC rejects the generated section name containing
the decorated `@4` suffix. The focused body comparison therefore used a
temporary single-function profile without `-ffunction-sections`; it is
diagnostic evidence, not a project profile. These probes did not change the
maintained source or its assembly region.

The masked-shift candidate optimized to a 9-byte `RET 4` body (`bswap` plus
load/return), so it fails the 37-byte extent. A second typed spelling used an
uninitialized volatile word as the local byte buffer and computed the high and
middle bytes before storing them. Its Clang COFF body has the exact 37-byte
extent, but differs at eight byte positions. The retained suffix and all four
byte stores match; the differences are the local-slot reservation (`push eax`
instead of `push ecx`) and the equivalent register moves/shift order near the
entry:

```text
retail: 51 8b 44 24 08 8b c8 8b d0 c1 e9 18 c1 ea 10 88 ...
Clang:  50 8b 44 24 08 89 c1 c1 e9 18 89 c2 c1 ea 10 88 ...
```

Direct `clang-cl` compilation for the MSVC target at `/O2` emitted the same
37-byte candidate body and the same eight differing bytes. The typed source is
therefore still not promotable. The remaining distinction is compiler code
generation, not function extent or byte-reversal behavior.

## Native MSVC recheck (2026-09-30)

The current environment can run Wine and MSVC again. The maintained assembly
baseline passed `probe.py` with all 37 bytes exact in
`build/probe-current-word-reverse`. The earlier Wine restriction is therefore
not a current blocker.

Live Ghidra MCP decompilation of `th10.exe` at `0x0043A700` reconfirmed the
four-byte reversal and stack argument. Eight fresh ordinary MSVC C++ variants
were rejected by the complete-function extent check: each generated 42 bytes
instead of 37. These combined ordinary word storage, union byte storage,
volatile union bytes, and volatile byte pointers with either direct shifts or
explicit high/middle temporaries. A ninth variant with a volatile output word
also emitted 42 bytes. Sources, proposal, and individual probe logs are in
`build/experiments/word_reverse_current/`. The exact assembly source was
restored after the experiment; no semantic region was promoted.

Native compiler experiments are available again. The next attempt can inspect
MSVC output directly and seek a source-level reason for a distinct local word;
the result must pass the 37-byte gate before adoption.

Direct compilation of `v0_1.cpp` retained a raw object in
`build/experiments/word_reverse_current/raw/objects/unit0000.obj`. Its
42-byte disassembly explains the residual: MSVC stores the result into the
argument's original `[ESP+4..7]` slot, and implements the third byte with
`SHR ECX,8` and `CL` rather than retail's `AH`. The high/middle temporaries
are optimized away as scheduling constraints. A successful spelling must
address both distinctions, not just introduce a nominal output variable.

After restoring the baseline, `make` succeeded for all 1,944 maintained
sources and verified the entire 487,936-byte executable as exact. Current
counts remain 1,794 ordinary C++ regions (91,442 bytes), 509 assembly regions
(231,598 bytes), and 321 toolkit runtime library regions (66,357 bytes).
