# `fast_error_exit` at `0x00453762`

Superseded 2026-09-30: the 36-byte `wincrt0.obj` `_fast_error_exit` section is now linked from `libcmt.lib`; see [the MSVC port note](foreign_compiler_regions_to_msvc_2026-09-30.md).

Updated 2026-09-30. The active region is now semantic and is owned by
`src/unidentified/fast_error_exit_00453762.cpp`. The function checks the
runtime error-message mode at `0x0047720C`, optionally calls
`FF_MSGBANNER`, reports the supplied stack argument through `0x00458EFD`,
then enters the non-returning `___crtExitProcess(0xFF)` path. The Ghidra
listing at `decompiled/ghidra_augmented/functions/00453762.asm` confirms the
33-byte control flow and argument reread from `[ESP+4]` after the banner call.

The maintained source is ordinary C++ with no inline assembly. Its pinned
Clang i386 GNU COFF profile passes `probe.py` exactly for all 33 bytes, and
all three call relocations resolve to the retail targets: `0x0045909F`,
`0x00458EFD`, and `0x00457547`.
An ABI-honest behavioral model using the helper's true cdecl declaration
remains in `reference/semantic_candidates/fast_error_exit_00453762.cpp`.

One local call edge preserves an unusual but verified terminal stack state.
The real `0x00458EFD` handler uses cdecl and ends in plain `RET`; retail leaves
its pushed error argument on the stack, then pushes `0xFF` and calls the
non-returning process-exit routine. The maintained source declares that one
call edge with the callee-pop attribute so Clang omits cleanup that retail also
omits. A COFF alias maps the decorated reference back to the real cdecl
symbol. This is safe only because the next operation terminates the process;
the function never returns with an imbalanced stack. Keep that caveat beside
the source declaration if the exit path changes.
