# DAT index builder at `0x004350D0`

Historical recovery record. Its final promotion and source-location claims
are no longer current: the production region remains assembly. See
[the tested parser recovery](dat_archive_parser_004350d0.md) for the repaired
candidate, 174 normal-path comparisons, and 278 registered-state/unwind-action
comparisons. Native MSVC frame and byte matching remain outstanding.

## Ghidra evidence

Connected Ghidra `th10.exe` reports `FUN_004350d0` as a non-thunk function with
prototype `int* __stdcall (int*, int, int)`. Its body spans `0x004350D0` through
the `ret 0x0c` at `0x00435214` (the following region begins at `0x00435217`).
Ghidra lists one code reference/caller, the call at `0x0043506F` in
`FUN_00434f70` (`DatArchive_LoadIndex`). That call supplies three stack
arguments and consumes the returned pointer from EAX. The callee therefore
must keep the three-argument stdcall cleanup and pointer result.

Ghidra identifies the direct callees as:

- `0x00452493`, `operator new(unsigned int)`, cdecl;
- `0x0045252D`, the Visual Studio 2003 `eh vector constructor iterator`,
  stdcall with `(array, element_size, count, constructor, destructor)`;
- `0x00452706`, `malloc(unsigned int)`, cdecl.

The vector iterator's callback parameters use the x86 instance-callback
contract: the current element is passed in ECX. The callback at `0x004352C0`
stores zero at the start of the element; the callback at `0x00435250` releases
and clears that first pointer. The current source tree names these operations
`HeapBuffer::HeapBuffer` and `HeapBuffer_Release` respectively. The one-pointer
fastcall form used by the latter is compatible with the helper's thiscall
callback invocation on 32-bit x86.

## Recovered data shape and behavior

The existing archive type `DatArchiveEntry_00434d10` is 16 bytes: a 4-byte
`HeapBuffer` name followed by `data_offset`, `uncompressed_size`, and
`reserved_metadata`. The assembly allocates `(record_count + 1) * 16 + 4`
bytes, stores `record_count + 1` in the leading array cookie, and runs the
vector constructor over all entries. For each real record it duplicates the
NUL-terminated name with `malloc`, advances past the name rounded up to a
4-byte boundary, then copies the following three DWORDs into the entry. The
extra entry is the sentinel: it receives the third argument in `data_offset`
and zero in `uncompressed_size`. Its `reserved_metadata` is intentionally
left uninitialized, as in the retail body.

`src/archive/dat.cpp` now expresses that behavior using the shared record type
and ordinary C++, while retaining the allocator calls, vector-iterator call,
and the original stdcall entry contract. The constructor and release callbacks
are passed by their confirmed retail code addresses because C++ does not allow
taking a pointer to a constructor directly.

## Limits

This establishes semantic recovery from Ghidra's body, boundary, xref, and
callee evidence. No build, probe, test, or byte comparison was run for this
change, so compiler-emitted extent and bytes are not claimed to match retail.
The source intentionally preserves the uninitialized sentinel metadata and
assumes the archive-provided record count and packed input are valid, as the
retail routine does.

The manifest now classifies `0x004350D0` as semantic C++, bound to
`_DatArchive_BuildIndex_004350d0@12`. Its old `_asm_FUN_004350d0_004350d0`
symbol remains available for the existing inline-assembly caller.
