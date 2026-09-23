# `write_string` helper recovery at `0x00454E81`

## Disposition

`matching2/msvc/src/unidentified/write_string_00454e81.cpp` now defines the
existing symbol `asm_write_string_00454e81` as an ordinary
`void __cdecl` function with explicit stream, output-count, byte-buffer, and
length parameters. The body models the helper's count-only path and its
byte-at-a-time buffered output path, including `flsbuf` fallback and stopping
after the output count becomes `-1`.

The manifest classifies the 55-byte body as semantic and preserves the old
assembly row in `previous_record`. The shared header now exposes the typed cdecl
signature. No build, probe, or test was run.

## Live Ghidra evidence

Target: `th10`, queried 2026-09-23.

- `get_function_by_address(0x00454E81)` reports `write_string` with body
  `0x00454E81–0x00454EB7`, 55 bytes. The decompiler sees one stack parameter,
  the signed length, plus the private register inputs `EDI` (stream), `EAX`
  (output-count pointer), and `ECX` (byte pointer).
- `get_function_callers(0x00454E81)` reports only `FUN_00454ed7`. The three
  direct call xrefs are `0x004555A4`, `0x00455602`, and `0x00455619`. At each
  call, the retail code supplies stream in `EDI`, count pointer in `EAX`, bytes
  in `ECX`, and pushes the length as the sole stack argument.
- The helper's only callee is `write_char` at `0x00454E2A`. The formatter's
  current semantic body models the same effects with local `writeBytes` and
  `writeCharacter` functions instead of using this private-register helper.
  The new typed cdecl entry therefore normalizes the helper interface without
  reintroducing the old EAX/ECX/EDI edge into that formatter.
- The decompilation and listing show two paths. If `(stream.flags & 0x40) != 0`
  and `stream.base == nullptr`, the helper adds the signed length directly to
  the output count and returns. Otherwise it writes bytes through
  `write_char`, decrementing the remaining length before each write and
  stopping after a write makes the count exactly `-1`. The initial loop test
  checks only that length is positive: if the count is already `-1`, one byte
  is still attempted before the error check. Each `write_char` call decrements
  the stream's remaining capacity, writes directly when capacity remains, and
  uses `flsbuf` when it is exhausted.
- The typed function signature is
  `void __cdecl asm_write_string_00454e81(WriteStringStreamPrefix* stream,
  int* outputCount, const char* bytes, int length)`. The stream prefix fields
  are `current`, `remaining`, `base`, and `flags` at offsets `0`, `4`, `8`, and
  `0xC`. Its C symbol remains unchanged; the ordinary cdecl argument order is
  now explicit in the source.

## Integration boundary

The three retail call sites are represented inside the formatter's current
semantic C++ implementation, which uses local writers and does not call this
helper. The legacy C symbol remains for address mapping; the header declaration
is now typed. No code-generation comparison was performed.
