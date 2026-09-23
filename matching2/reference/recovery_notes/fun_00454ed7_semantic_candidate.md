# 0x00454ED7 formatter recovery

## Disposition

`matching2/msvc/src/unidentified/FUN_00454ed7_00454ed7.cpp` now contains an
ordinary C++ formatter body and preserves the existing C symbol
`asm_FUN_00454ed7_00454ed7`. The entry and writer semantics are recoverable from
the standard cdecl entry plus call-site evidence; no private register entry is
needed for the formatter itself. The live manifest now gives the function a
1,946-byte semantic row and represents the post-return bytes separately as a
two-byte padding row and a 32-byte data row.

No build, probe, or test was run for this function recovery.

## Live Ghidra evidence

Target: `th10`, queried 2026-09-23.

- `get_function_by_address(0x00454ED7)` reports
  `int __cdecl FUN_00454ed7(undefined4, byte *, wchar_t *)`, with body
  `0x00454ED7–0x00455670` and 613 instructions. The first argument is the
  FILE-like stream prefix; the second is the format byte string; the third is
  the byte-addressed variadic cursor. Call sites advance it by four bytes for
  scalar/pointer arguments and eight for `I64` integers and `double` values.
- Live callers are `FUN_004524fd`, `FUN_00452b40`, `_sprintf`, and `_vsprintf`.
  The latter two construct the same stream prefix at offsets 0, 4, 8, and 0xC
  (current pointer, remaining count, base pointer, flags) and consume the
  formatter's integer result.
- Live callees are `write_char` (0x00454E2A), `write_multi_char`
  (0x00454E5D), `write_string` (0x00454E81), `_malloc` (0x00452706), `_free`
  (0x00452422), `_strlen` (0x00456720), `_wctomb` (0x0045A16E),
  `__aulldvrm` (0x0045A1B0), the float-conversion hook at 0x0045DF97, and the
  stack-cookie checker at 0x00458EA5.
- The parser indexes the class bytes at `0x0046A770` and the nine-by-eight
  transition matrix at `0x0046A790`. The source keeps their observed shared
  byte sequence and makes the state transitions explicit while preserving the
  32-bit arithmetic used for width, precision, and output-count updates.
  The 89 observed bytes at `0x0046A790` are:

  ```text
  06 00 00 06 00 01 00 00 10
  00 03 06 00 06 02 10 04 45
  45 45 45 05 05 05 05 05 35
  30 00 50 00 00 00 00 20 28
  38 50 58 07 08 00 37 30 30
  57 50 07 00 00 20 20 08 00
  00 00 08 60 68 60 60 60 60
  00 00 70 70 78 78 78 78 08
  07 08 00 00 07 00 08 08 08
  00 00 08 00 08 00 07 08
  ```
- The naked output helpers have private register interfaces, but those
  interfaces are contained at their call boundary and are modeled by local
  C++ writers: `write_char` receives stream in ECX, count pointer in ESI, and
  byte in AL; `write_multi_char` receives count pointer in EAX and stack
  arguments `(byte, count, stream)`; `write_string` receives count pointer in
  EAX, bytes in ECX, stream in EDI, and length on the stack. Their effects are
  direct stream writes, count-only accounting, and `flsbuf` fallback on a full
  buffer.
- Ghidra's inclusive function body `0x00454ED7–0x00455670` is `0x79A`
  (1,946) bytes and ends in RET at `0x00455670`. The live manifest now records
  that exact span as `kind: "semantic"`, owner `0x00454ED7`; its previous
  1,980-byte assembly owner has been split. Bytes `0x00455671–0x00455672`
  decode as `MOV EDI,EDI` (`8B FF`) and are now a separate two-byte
  `kind: "padding"` row. The table occupies exactly
  `0x00455673–0x00455692` (`0x20` bytes, eight 32-bit entries) and is now a
  separate `kind: "data"` row. Together these rows end exclusive at
  `0x00455693`, preserving the original `0x7BC`-byte owner extent. A live memory
  read returned these table targets in order:

  | Entry address | Target |
  | --- | --- |
  | `0x00455673` | `0x004550F3` |
  | `0x00455677` | `0x00454F75` |
  | `0x0045567B` | `0x00454F92` |
  | `0x0045567F` | `0x00454FDE` |
  | `0x00455683` | `0x00455019` |
  | `0x00455687` | `0x00455022` |
  | `0x0045568B` | `0x0045505A` |
  | `0x0045568F` | `0x0045512C` |

  The jump at `0x00454F6E` indexes this table for the parser-state switch.
  The table is after the `RET`, outside Ghidra's function body. The live
  manifest/header and text-data row now represent it separately from the
  semantic function; those shared integration files were handled outside this
  function-source recovery.

## Recovered behavior

The function implements a table-driven printf-family formatter. It parses
space, `#`, `+`, `-`, and `0` flags; numeric or `*` widths and precisions;
`h`, `l`, `w`, `I32`, and `I64` modifiers; and `c`, `C`, `s`, `S`, `Z`, `n`,
integer, pointer, and floating conversions. It writes bytes through the stream
prefix, counts bytes for the count-only stream mode, returns `-1` after the
stream reports failure, and stores the current count for `%n`. Wide strings
and wide characters are converted to the active multibyte encoding. Counted
`%Z` strings use a signed 16-bit byte length, halved for wide input. Integer
formatting includes signed magnitude, radix conversion, precision padding,
alternate prefixes, and 64-bit values; floating formatting uses the initialized
runtime hook slots and allocates a larger temporary buffer for high precision.

The standard entry contract and every output-helper effect are represented in
the replacement body. The live region layout keeps the ordinary function,
two-byte post-return instruction, and switch-table data as separate rows.
