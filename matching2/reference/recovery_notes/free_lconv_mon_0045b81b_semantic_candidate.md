# `___free_lconv_mon` at `0x0045B81B`

The source in `msvc/src/unidentified/free_lconv_mon_0045b81b.cpp` expresses the
cleanup as ordinary C++. Its entry keeps the existing C-linkage cdecl symbol.
The shared declaration now takes the pointer argument, and the manifest marks
the 217-byte entry as semantic while preserving the previous assembly record.

## Ghidra evidence

- Ghidra identifies `0x0045B81B..0x0045B8F3` as the Visual Studio 2003 CRT
  worker `___free_lconv_mon`. The inclusive span is 217 bytes, ending in a
  plain `RET` at `0x0045B8F3`.
- The function takes one pointer from the stack and uses cdecl cleanup. It
  preserves ESI, has no private register inputs, and has no callers that use a
  return value.
- Direct callers are `___freetlocinfo` at `0x00455836` and `___init_monetary`
  at `0x0045BA96`. The direct callee is `_free` at `0x00452422`.

## Recovered behavior

If the input pointer is null, the function returns immediately. Otherwise it
checks seven pointer fields at byte offsets `+0x0C`, `+0x10`, `+0x14`, `+0x18`,
`+0x1C`, `+0x20`, and `+0x24`. For each field, it calls `_free` only when the
value differs from both the corresponding pointer in the active locale table
at `0x00473AD4` and the matching static default pointer at `0x00473AB0` through
`0x00473AC8`.

The field offsets and comparisons are directly visible in Ghidra's listing;
the higher-level names for these seven fields are not established here. The
source keeps the seven checks in their original order and does not add a null
filter for individual fields, so a null field still reaches `_free` when it
differs from both defaults.

## Limits

This is a behavior-level C++ model. It does not reproduce the original
register allocation or `pop ecx` argument cleanup after `_free`; exact compiler
output and retail byte identity are unverified. No build, probe, or test was
run.
