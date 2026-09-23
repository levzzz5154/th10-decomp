# LC_TIME cleanup at `0x0045B39A`

Live Ghidra identifies a 400-byte `__cdecl` routine, spanning
`0x0045B39A..0x0045B529`, with one pointer argument. It has direct call sites
at `0x004558B3` and `0x0045B557`; both pass the record pointer on the stack.
The first is in `___freetlocinfo`, whose C++ model also uses this function.

For a non-null record, the routine calls the existing `_free` helper on 43
pointer slots in this order: indices 1 through 6, index 0, indices 8 through
13, index 7, then indices 14 through 42. The implementation keeps that call
order and returns immediately for a null pointer. The highest freed field is
at byte offset `0xA8`.

Ghidra leaves the return type unresolved because EAX contains a value at the
return instruction. The observed callers discard EAX, so the shared C++ entry
uses a `void` return while preserving the stack argument and linker symbol.
`regions.json` now classifies the 400-byte body as semantic and records the
previous assembly row.

No build, probe, or test was run.
