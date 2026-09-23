# `write_multi_char` at `0x00454E5D`

## Current disposition

The region remains a naked assembly implementation in
`matching2/msvc/src/unidentified/write_multi_char_00454e5d.cpp`. The live
Ghidra program identifies it as the Microsoft CRT helper `_write_multi_char`,
and confirms a standalone function from `0x00454E5D` through `0x00454E80`
(36 bytes, including `ret`). The disassembly begins with `push ebp; mov ebp,
esp; push esi; mov esi,eax` and ends with `pop esi; pop ebp; ret`.

The entry is cdecl in its stack cleanup, but its full calling convention is a
CRT-private hybrid:

| Location at entry | Meaning | Evidence |
|---|---|---|
| `EAX` | Pointer to the caller's output count / error sentinel | Copied to `ESI` before the loop; `write_char` updates the pointed-to integer through `ESI` |
| `[ESP+4]` | Character value; only its low byte is used | Caller pushes `0x20` or `0x30`; callee loads `AL` from `[EBP+8]` |
| `[ESP+8]` | Number of characters requested | Caller pushes its width; callee decrements `[EBP+0x0C]` per attempted write |
| `[ESP+0xC]` | Buffered stream pointer | Caller pushes the stream; callee loads it into `ECX` from `[EBP+0x10]` |

Ghidra's default signature only reports two stack parameters and cannot
represent the hidden `EAX` input. It also does not include the third stack
argument in that prototype. The direct call sites at `0x00455590`,
`0x004555BB`, and `0x0045562E` are all inside `FUN_00454ED7`; each loads the
count address into `EAX`, then pushes the stream, width, and character in the
order needed for the table above. The cleanup after each call is `add esp,
0x0C`, confirming caller cleanup. Ghidra reports `write_char` at
`0x00454E2A` as the only callee and `FUN_00454ED7` as the caller function.

## Behavior established from the body

The helper emits no characters when the requested count is zero or negative.
For a positive count it repeatedly passes the low byte of the character and
the stream to `write_char`, decrementing the remaining count before each
attempt. After each call it stops if the integer at the `EAX`-supplied address
has become `-1`; otherwise it continues while the remaining count is positive.
It does not set a return value explicitly. The mutable count and `-1` failure
sentinel are the observable result used by the caller.

The stream-buffer mechanics belong to `write_char` at `0x00454E2A`. That
helper normally decrements the stream's available-byte count, stores the
character through the stream's current pointer and advances it, or calls
`__flsbuf` when the count becomes negative. A failed flush writes `-1` through
the shared count pointer, which causes this function to stop after that
attempt. In the special state where stream flag `0x40` is set and the base
pointer is null, `write_char` skips the buffer write and increments the
shared output count. These behaviors are visible in the live disassembly and
decompilation of `write_char`; this region only owns the repetition and
early-stop logic.

## Why it is not converted to ordinary C++ yet

The Microsoft x86 C++ calling conventions available to this project cannot
declare the `EAX`-supplied count pointer as a function parameter. The nested
`write_char` call also depends on a register protocol: `ECX` carries the
stream, `AL` carries the byte, and `ESI` carries the mutable count pointer.
Writing a normal C++ function with an ordinary prototype would therefore
change the entry ABI, while retaining an assembly adapter would leave inline
assembly in this region. This is the precise blocker to an ordinary-C++
replacement. Revisit if the caller and helper call protocol are refactored
together so the count pointer is passed as an explicit C++ parameter.

## Symbols and verification status

- Ghidra name: `write_multi_char` at `0x00454E5D` (CRT library match).
- Project symbol: `asm_write_multi_char_00454e5d` / COFF symbol
  `_asm_write_multi_char_00454e5d`.
- Callee symbol: `asm_write_char_00454e2a` / COFF symbol
  `_asm_write_char_00454e2a`.
- Retail bytes and boundary were checked with live Ghidra against
  `/th10.exe`; the project source preserves those instructions.
- C++ code generation has **not** been verified. No build or binary comparison
  was run for this audit.
