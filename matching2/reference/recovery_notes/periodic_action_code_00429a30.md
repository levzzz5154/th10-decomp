# Periodic action code at 0x00429A30

Ghidra identifies a 58-byte function with no incoming xrefs. Retail receives
a state pointer in EAX. It returns `6` only while a scene exists at
`data_00477810`, the state word at `+0x10` equals one, input bit `0x100` is
set in `data_00474E30`, and the counter at `+0x1C8` is not a multiple of
four. Otherwise it returns `1`. The retail signed-remainder sequence has the
same zero/nonzero outcome as checking the low two counter bits.

The [C++ source](../semantic_candidates/periodic_action_code_00429a30.cpp)
uses a typed pointer argument and names the four conditions. The manifest
retains the old assembly record in `previous_record`. The cdecl argument
replaces the retail EAX input ABI; byte matching remains unverified, and no
build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
