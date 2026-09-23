# CRT `write_char` at `0x00454E2A`

## Disposition

Retain the 51-byte naked implementation in
`matching2/msvc/src/unidentified/write_char_00454e2a.cpp`. The operation is
understood, but the entry has a private mixed-register ABI: the stream is in
ECX, the character is in AL, and the output-count pointer is in ESI. The
current callers depend on those live-ins. MSVC's ordinary x86 C++ conventions
do not describe that parameter placement, so replacing the entry with a normal
function would change the call contract. No manifest, shared-header, or layout
changes were made.

## Live Ghidra evidence

Target: `/th10.exe` (`th10.exe`, PE x86 little-endian), queried 2026-09-23.

- `get_function_by_address(0x00454E2A)` identifies `write_char`, with body
  `0x00454E2A–0x00454E5C` inclusive. This is 51 bytes; the next function,
  `write_multi_char`, begins at `0x00454E5D`.
- The disassembly contains 23 instructions and one direct callee, `__flsbuf`
  at `0x00454D11`. The entry has no conventional stack parameters. Its
  decompiler view identifies the incoming values as `ECX` (`FILE*`), `AL`
  (character byte), and `ESI` (`int*` output count).
- There are four direct call references from three caller functions:
  `write_multi_char` at `0x00454E6E`, `write_string` at `0x00454EA3`, and
  `FUN_00454ED7` at `0x0045510F` and `0x00455122`. The call sites set the
  stream in ECX and character in AL; the count pointer is live in ESI. For
  example, `write_multi_char` loads ESI from its incoming EAX, then loads ECX
  from `[EBP+0x10]` and AL from `[EBP+8]` before the call. The formatter sites
  load ECX from `[EBP-0x54]`, ESI with `&[EBP-0x44]`, and AL from BL.
- `get_function_callers` returns those three functions, and
  `get_function_xrefs` reports the four call-site addresses above. The call to
  `__flsbuf` is the only callee.

## Behavior represented by the retained body

If the stream has flag `0x40` and a null base pointer, it skips the stream
write and increments the count at ESI. Otherwise it decrements the remaining
buffer count at stream offset `+4`. A nonnegative result writes AL through the
current pointer at offset `+0`, advances that pointer, and zero-extends AL to
EAX. If the remaining count becomes negative, it sign-extends AL, calls
`__flsbuf(character, stream)`, and removes its two stack arguments. A return
of `-1` sets the output count to `-1`; any other result increments it.

## Symbol and byte-identity status

The source and manifest retain the existing C `__cdecl` decorated symbol
`_asm_write_char_00454e2a`. `write_multi_char` still calls that symbol, so keep
it stable; no compatibility alias is needed while the name remains unchanged.
If a later semantic entry receives a different canonical name, preserve
`_asm_write_char_00454e2a` as an alias for existing assembly callers.

The 51-byte Ghidra body and the inline-assembly instruction sequence agree
line-for-line, including both return paths. The object output was not built or
compared with retail bytes, so byte-for-byte identity is **not verified**. No
build, probe, or test was run.
