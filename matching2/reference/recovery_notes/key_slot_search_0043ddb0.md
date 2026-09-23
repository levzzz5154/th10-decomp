# 12-slot key lookup/update at `0x0043DDB0`

The body scans twelve signed key slots beginning at owner offset `+0x620`.
The first negative entry is available; otherwise the scan continues until a
slot equals the requested key. For either a free slot or a matching slot, it
writes `-1` to the paired flag at the corresponding index (`+0x650` onward).
It writes the requested key only when filling a negative slot. If all twelve
entries are nonnegative and none matches, it returns without changing memory.

The recovered model is in
`matching2/msvc/src/unidentified/unassigned_0043ddb0.cpp`. Its local owner
layout names only the observed prefix padding and the two arrays. The C++
function takes an owner pointer and an `int` key and returns `void`.

## ABI and confidence

Retail enters with the owner in `ESI` and key in `EDI`, then returns with a
plain `ret`. These are private register inputs, not a conventional stack
signature. The source keeps the legacy C symbol but gives it an explicit
ordinary `__cdecl` signature for readable modeling; callers requiring the
retail register convention need an adapter. The C++ model describes the
control flow and state changes and does not claim byte-exact output.

The slot sentinel is established by the signed `jl` test, and the key is
compared for equality. The observed code also bounds the search at twelve
slots. The high-level layout and field meanings are inferred from those
accesses and the supplied Ghidra register/offset interpretation; the broader
owner type and the semantic meaning of the paired flag remain unknown. No
build or probe was run for this edit.
