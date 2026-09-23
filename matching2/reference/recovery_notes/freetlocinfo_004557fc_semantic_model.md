# `0x004557FC` `___freetlocinfo` semantic model

The ordinary C++ model is in
[`freetlocinfo_004557fc.cpp`](../../msvc/src/unidentified/freetlocinfo_004557fc.cpp).
It preserves the existing C-linkage symbol with a `void __cdecl(void*)`
signature.

## Behavior

The function frees a thread locale-information object using its recovered
offset layout. At `+0x3C` is the locale-data pointer; locale subobject cleanup
is enabled only when that pointer is non-null, differs from the default at
`0x00477624`, and the dword reached through the pointer at `+0x2C` is zero.
In that case it conditionally frees the owned monetary pointer at `+0x34`
unless it is the static object at `0x004981C8`, then calls the monetary
subobject cleanup with the locale-data pointer. It similarly handles the
numeric pointer at `+0x30` and static object at `0x004981D0`, then frees the
objects at `+0x2C` and `+0x3C`.

Independently, it conditionally frees the pointer at `+0x40` unless it is null
or the static object at `0x004981C4`; this path also frees the allocation base
stored at `+0x44` minus `0xFE`. It conditionally tears down the time-locale
pointer at `+0x50` unless it is null or the default at `0x00477620`, and only
when the dword at that object plus `0xB4` is zero. Finally, it frees the
thread-locale-information object itself.

The model keeps the pointer and count checks in their retail order and retains
the `+0xFE` allocation-base adjustment. The field names remain offset-based;
their higher-level structure is not established by this function alone.

## ABI and call graph

Ghidra shows one stack pointer argument at `[ESP+4]`, a plain `RET`, and no
private register inputs. Direct callers are `___updatetlocinfo_lk` at
`0x004558CC` and `__freefls@4` at `0x004563C8`. Direct callees are `_free` at
`0x00452422`, `___free_lc_time` at `0x0045B39A`, `___free_lconv_mon` at
`0x0045B81B`, and `___free_lconv_num` at `0x0045B5BC`.

## Model status

The active manifest now marks `0x004557FC` as semantic and retains the prior
assembly row in `previous_record`. The C-linkage entry and helper calls match
the recovered cdecl ABI. This is a behavior-level model; retail byte identity
and exact compiler output remain unverified. No build, probe, or test was run.
