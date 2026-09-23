# Semantic model for `__close_lk` at `0x00462107`

`matching2/msvc/src/unidentified/close_lk_00462107.cpp` now expresses this
131-byte region as ordinary C++.

Ghidra identifies the function as `__close_lk` with a single 32-bit cdecl file
descriptor on the stack and a 32-bit result in EAX. Its only direct caller is
`FUN_0046218A` at the call site `0x004621D6`; direct callees are
`__get_osfhandle` (`0x0045F6D4`), `CloseHandle`, `GetLastError`,
`__free_osfhnd` (`0x0045F655`), and `__dosmaperr` (`0x00456B04`). The function
has no private register input.

The behavior follows the Ghidra decompilation and the retail listing:

- Check the descriptor with `__get_osfhandle`.
- For descriptor 1 or 2, preserve the underlying OS handle when stdout and
  stderr refer to the same handle.
- Otherwise close the OS handle and capture `GetLastError` immediately if
  `CloseHandle` fails.
- Free the descriptor's OS-handle entry, then clear its flag byte at record
  offset `+4`. Entries occupy `0x24` bytes and are held in blocks of 32.
- Translate a captured OS error through `__dosmaperr` and return `-1`; return
  zero when no OS error was captured.

The source calls the existing helpers by their established C symbols and uses
the Windows `CloseHandle` and `GetLastError` imports. The manifest classifies
the region as semantic under the unchanged `_asm_close_lk_00462107` C symbol and
preserves the old assembly record in `previous_record`. No build or
code-generation check was run, so object-level matching remains unverified.
