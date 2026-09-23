# `FUN_00457A7C` semantic recovery status

## Disposition

Keep the maintained definition in `src/unidentified/FUN_00457a7c_00457a7c.cpp` as
retail naked assembly. No uncompiled C++ sidecar or manifest change is retained.
The live region is 3,627 bytes (`0xE2B`), from `0x00457A7C` through
`0x004588A6`; the source's opening comment gives only an earlier internal
address (`0x00458219`) and is not the region end.

## Live Ghidra evidence

Ghidra identifies `FUN_00457a7c` as a worker with signature
`int __cdecl(FILE *stream, byte *format, undefined4 *argument_cursor)`. Its
only direct caller is `_sscanf` at `0x00452FB9`, with a call reference at
`0x00452FE3`. The wrapper in `src/unidentified/sscanf_00452fb9.cpp` constructs
a memory-backed stream with 32-bit fields `ptr`, `count`, `base`, and `flags`
at offsets `0`, `4`, `8`, and `0xC`, followed by four padding words. It passes
the format pointer and the address of the first 32-bit variadic argument. The
worker returns the assignment count in EAX and uses caller cleanup, consistent
with `__cdecl`.

The worker is a scanf-family format interpreter. It skips format whitespace,
matches literals, parses field widths and suppression/length modifiers, and
handles numeric, floating-point, character, string, scanset, and `%n`
conversions. The integer path includes base prefixes and 64-bit accumulation.
The character path has narrow and multibyte/wide variants; scansets build a
256-bit membership table. Floating-point text uses the locale decimal point and
calls the function pointer at `PTR_FUN_004739C8`; Ghidra identifies its
initialized target as `__fassign` at `0x0045DC7C`.

Ghidra reports direct calls to `__inc` (`0x00457A3C`), `_ungetc` (`0x0045E204`),
`_isspace`, `_isdigit`, `_isxdigit`, `_mbtowc`, `_memset`, `_free`, `__allmul`,
the SEH/cookie helpers, and `__chkstk`. The decompiler warns that it injects the
SEH, cookie, and stack-probe helpers and removes a block at `0x00458867`; it
also emits placeholder register values around the private `__inc` calling
convention. The disassembly, rather than the pseudocode alone, is needed to
recover exact stream and argument-cursor behavior.

## Integration blocker

This is a complete, stateful CRT scanner rather than a small leaf operation.
The entry signature is known, but a faithful C++ body still has to preserve the
target's private stream read/pushback protocol, variadic cursor advancement,
width exhaustion and rollback rules, and locale-sensitive multibyte and float
conversion paths across every format class. Calling the host `sscanf` would
not preserve the wrapper's private stream layout or the target's initialized
locale callbacks. A short translation from Ghidra's pseudocode would also
discard control-flow details where its register recovery is explicitly
incomplete.

The repository's promotion gate requires an integrated source body to retain
the retail executable bytes. No build, probe, or test was run for this pass, so
there is no evidence that a C++ replacement compiles in the project or meets
that gate. The current concrete blocker is therefore a complete instruction-
grounded model of the scanner's private stream/conversion edge cases; until
that model and an integrated body exist, retaining the exact source definition
is safer than adding a semantic approximation that cannot be reviewed or
verified as a replacement.
