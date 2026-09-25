# C++ exception record predicate at 0x00462F4C

Ghidra identifies a 48-byte function with no incoming xrefs. Retail receives
the address of an exception-record pointer in EAX. It returns one only when
the pointed-to record has code `0xE06D7363`, exactly three parameters, magic
`0x19930520` or `0x19930521`, and a null throw-information pointer at
offset `0x1C`. The same eight-word record layout appears in the nearby
`CxxUnregisterExceptionObject_004630ce` source.

The [C++ source](../semantic_candidates/is_cxx_exception_record_00462f4c.cpp)
names the record fields and returns the predicate directly. The manifest
retains the old assembly record in `previous_record`. Its typed cdecl
argument replaces the retail EAX input ABI; byte matching remains unverified,
and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
