# `FUN_00436890` at `0x00436890`: live Ghidra ABI audit

Date: 2026-09-23. Read-only review of the live `th10.exe` Ghidra program.

## Boundary, references, and ABI

Ghidra identifies `FUN_00436890` with body `0x00436890..0x004368F2`
inclusive (99 bytes). The last instruction is `ret 4` at `0x004368F0`; bytes
from `0x004368F3` are `INT3` padding. This agrees with the 99-byte body
preserved in `matching2/msvc/src/unidentified/FUN_00436890_00436890.cpp`.

Ghidra's signature is `undefined4 * __stdcall FUN_00436890(undefined4 *)`.
The assembly confirms the contract: it reads the explicit destination pointer
from `[ESP+4]`, holds it in ESI, returns that same pointer in EAX, restores ESI,
and uses `ret 4`. ECX is not an input. The one direct call xref is at
`0x004372B7`; the callsite forms a stack pointer with `lea eax,[esp+8]`, pushes
it, and calls this entry. Ghidra's caller enumeration returns no caller
function, and the callsite does not resolve as a function entry, so the
enclosing caller identity remains unknown.

## Observed initialization

Let `dst` be the explicit pointer. The function writes:

- `dst+0x00`, `dst+0x04`: zero;
- `dst+0x08`: `0x10`;
- a string-shaped subobject beginning at `dst+0x0C`: inline first byte zero
  at `dst+0x10`, length zero at `dst+0x20`, capacity 15 at `dst+0x24`;
- `dst+0x28`: `0x258` (600).

It then calls `FUN_00438420` with ECX=`dst+0x0C`, source
`0x0046F36C`, and count 13. The 13 source bytes decode as the CP932 font name
`ＭＳ ゴシック`. Ghidra's decompilation of `FUN_00438420` confirms the
small-string path uses capacity 15 and writes the assigned length and
terminator. The dword at the start of the subobject (`dst+0x0C`) is not written
here; in the checked-in `LegacyString` view that position is named
`allocator_cookie`.

## Exception cleanup and conversion blocker

The entry installs a registration frame using `FS:[0]` and handler thunk
`0x0046558B`. Before calling `FUN_00438420`, it changes the frame state from
`-1` to zero. Ghidra disassembly shows the handler thunk loads scope-table
address `0x004715FC` and jumps to `___CxxFrameHandler` at `0x0046276D`. The
metadata at `0x004715FC` begins with the C++ EH magic `0x19930520`, has one
unwind state, and points to an unwind entry at `0x004715F4`; that entry moves
state 0 to -1 through funclet `0x00465580`. The cleanup thunk forms
`dst+0x0C` and jumps to `FUN_004381F0`; Ghidra decompiles that helper as freeing
heap storage when capacity is at least 16 and resetting the string's inline
state. Thus the retail body carries real exception-state cleanup for the
embedded string.

The normal-path stores can be described, but the containing record's type and
construction lifetime are still unidentified. A raw readable initializer
would also need to preserve the unmodified allocator-cookie word and the
exception cleanup that runs on a thrown assignment. Without a recovered record
definition and verified ordinary-C++ lowering for this cleanup, retain the
existing exact naked body. The source records older byte-probe results; no
build, probe, or test was run for this audit.

Current Ghidra symbol: `FUN_00436890`. Current source symbol:
`asm_FUN_00436890_00436890`. A cautious semantic candidate, not yet applied,
is `initialize_ms_gothic_record_00436890`; the record's actual type is not
known well enough to justify a permanent rename.

## 2026-09-23 conversion screening

This is the strongest remaining conversion candidate in the surrounding
`0x00430000..0x0043FFFF` asm range with an ordinary explicit-argument ABI and
small, understandable normal-path behavior. The `__stdcall` pointer argument
and `ret 4` are directly expressible, but the body is not just a field
initializer: the embedded `LegacyString` assignment is guarded by a real
MSVC exception frame whose unwind path destroys that subobject. The containing
record type and its construction lifetime are still unknown, so a standalone
C++ rewrite cannot yet justify reproducing the observed cleanup semantics.
Keep the exact body until those types/lifetimes and ordinary-C++ EH lowering
are established. No build, probe, or test was run for this screening.
