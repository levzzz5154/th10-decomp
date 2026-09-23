# 0x0042ACB0 score defaults: semantic source candidate

2026-09-23. `FUN_0042acb0` is a 274-byte x86 `__stdcall` initializer taking
one storage pointer. Its body has no calls. Ghidra reports the range
`0x0042ACB0..0x0042ADC1`, the decompiler signature
`void __stdcall FUN_0042acb0(undefined4 *param_1)`, and the final instruction
is `RET 4`.

The source candidate is in
`matching2/msvc/src/game/score_file.cpp` as
`ScoreFile_InitializeDefaultsRetail_0042acb0(void*)`. It replaces the former
inline-assembly body with ordinary offset-based C++ stores. The offsets below
are kept literal because the structure and field semantics are not fully
known.

## Behavior supported by Ghidra

- The entry saves EBX, EBP, ESI, and EDI, then reads the sole stack argument
  from `[ESP+0x0c]` after the first two pushes. It clears `0x10DF` dwords
  (`0x437C` bytes) beginning at that pointer.
- It writes the 16-bit tag `0x5243` at `+0x00`, zero at `+0x02`, and the
  32-bit size `0x437C` at `+0x08`. The earlier clear leaves the other header
  bytes zero.
- Starting at `file + 0x10`, it fills five groups of ten rows, each `0x18`
  bytes. Each row receives scores `1,000,000` through `100,000` in steps of
  `-100,000` at `+0x00`, byte `1` at `+0x04`, zero at `+0x05`, raw four-byte
  values from `0x0046E858` and `0x0046E85C` at `+0x06` and `+0x0A`, the byte
  from `0x0046E860` at `+0x0E`, and a zero dword at `+0x10`. The row's final
  dword at `+0x14` remains zero from the initial clear.
- It then fills 22 strided records beginning at `file + 0x624`, with stride
  `0x2D0`. For each base `B = 0, 5, ..., 105`, five signed bytes from the
  110-byte table at `0x004743C0` are sign-extended to dwords and paired with
  their indices. Relative to each record, the `(index, value)` fields are at
  `(+0x00,+0x04)`, `(+0x90,+0x94)`, `(+0x120,+0x124)`,
  `(+0x1B0,+0x1B4)`, and `(+0x240,+0x244)`, with indices `B` through `B+4`.
  The initial values are indices 0 through 4 and table entries 0 through 4.
  This sequence reaches the end of the cleared allocation at `+0x437C`.

The existing model note
[`score_defaults_0042acb0_model.md`](score_defaults_0042acb0_model.md)
records the earlier byte-comparison experiments. One table formula in that
older prose/model is inconsistent with the disassembly: it describes the
third index as `B+2` only in prose ambiguously and its pasted code uses
`i+2` with `i` starting at 1. The live instructions establish the zero-based
sequence used by this candidate: `B`, `B+1`, `B+2`, `B+3`, `B+4`.

## ABI and caller

The `RET 4` establishes callee cleanup of one 32-bit stack argument. The
caller `FUN_0042ae60` pushes its current storage pointer (`ESI`) immediately
before calling `0x0042ACB0`, then advances to the next `0x437C`-byte block.
The initializer returns no value and restores EBX, EBP, ESI, and EDI.

## Exactness status and integration

This is a semantic candidate; exact emitted bytes are unverified. The earlier
plain packed-structure model recorded in the existing note emitted 282 bytes
against the retail 274, with 170 differing bytes. The earlier synthetic
native-LTCG context emitted 282 bytes with 260 differences. The known gap is
register allocation and resulting displacement/prologue choices: retail keeps
the file pointer in EBP and uses a particular register-pressure pattern, while
the ordinary source model does not yet force that allocation. No build or
probe was run for this candidate.

The current `regions.json` entry still identifies the address as the old ASM
symbol `_asm_ScoreFile_InitializeDefaultsRetail_0042acb0`; the existing ASM
caller also still names that symbol. A manifest/caller integration change is
outside this candidate. For the current C++ declaration, the expected MSVC
x86 decorated symbol is
`?ScoreFile_InitializeDefaultsRetail_0042acb0@@YGXPAX@Z` (`void __stdcall
function(void*)`).


## Caller and manifest integration (2026-09-23)

The caller at `0x0042AE60` now names the ordinary C++ `__stdcall` initializer
`ScoreFile_InitializeDefaultsRetail_0042acb0` directly. Its stack argument and
`RET 4` cleanup remain the same. The region record now points at the C++
decorated symbol and retains the former `_asm_ScoreFile_InitializeDefaultsRetail_0042acb0`
record in `previous_record`; the old declaration and address alias remain in
`asm_symbols.hpp`/the manifest symbol table for historical compatibility. This
integration records the semantic source only. The known 282-byte near-matches
remain the reason byte-exact output is unverified.
