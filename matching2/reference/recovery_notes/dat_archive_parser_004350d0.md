# Packed DAT index parser `0x004350D0`

2026-09-26. `reference/semantic_candidates/dat.cpp` is a typed, assembly-free
model of the parser's normal paths and raw-allocation exception cleanup. It
passes 174 normal-path retail comparisons and 278 registered-state/unwind-action
comparisons. Both tests execute the actual retail array helper and callbacks.
The maintained 327-byte region has not been promoted; native MSVC frame/byte
matching and Windows exception dispatch remain unverified.

## Evidence and layout

Saved Ghidra files `decompiled/ghidra_augmented/functions/004350D0.{c,asm}`
cover `[0x004350D0, 0x00435217)`. The three stack arguments are packed bytes,
signed entry count, and terminal data offset; the function returns an entry
pointer in EAX and uses `RET 12`. The candidate reproduces this entry ABI.

The allocation contains a four-byte array cookie followed by sixteen-byte
entries. The cookie and vector-constructor count both include the sentinel.
The allocation size is `16 * (unsigned(count) + 1) + 4`, with 32-bit wraparound.
Allocation uses operator new at `0x00452493`. Its null result returns null.
The vector helper at `0x0045252D` takes five stack arguments and uses `RET 20`;
its callbacks receive the entry in ECX. Construction at `0x004352C0` clears
only the entry's name word. The release callback is `0x00435250`.

Each packed record contains a NUL-terminated name, padding through the next
four-byte boundary relative to that record, then offset, unpacked size and
metadata words. Each name is separately allocated by `0x00452706`. A failed
name allocation leaves a null name but still consumes the record and copies
its metadata. Retail scans the name again after allocation/copy to locate
the metadata; the candidate preserves this even when an allocator callback
changes the packed bytes.

The final entry receives the supplied terminal offset and zero unpacked size.
Its name is already null from construction. Its metadata word is untouched.
The legacy model's plain allocation without a cookie and zeroed sentinel
metadata do not reproduce these details.

## Exception-cleanup evidence

Retail registers the handler thunk at `0x004653CB` before allocation. The
thunk selects FuncInfo at `0x004714B4`, which has one unwind-map entry at
`0x004714AC`, no try blocks, and an unwind action at `0x004653C0`. The saved
Ghidra action loads the allocation pointer from `[EBP-0x10]`, calls
`0x004524A1`, and returns. This is the array's raw allocation, including its
cookie; it is not the name-free entry at `0x00452422`.

The state changes from -1 to 0 after operator new returns, before the null
check and vector construction. It remains 0 through parsing until the normal
epilogue unlinks the frame. Consequently, modeling only constructor cleanup
is insufficient: later throwing calls are covered by the outer frame too.

The candidate now gives that allocation to a noncopyable
`PendingIndexAllocation` guard after successful allocation. Its destructor
calls `0x004524A1`; normal return releases the guard without freeing storage.
The guard covers vector construction and the entire name-copy loop. Partial
construction remains the vector helper's responsibility. If a later name
allocation throws, the outer action frees only the raw array: already copied
names are not individually released or cleared. This intentionally preserves
the behavior of the retail unwind map.

## Verification

`matching2/tests/dat_archive_parser_differential.py` compiles the actual
candidate with native Clang targeting x86 Windows COFF, verifies the retail
`.text` hash, and compares the two under Unicorn. Only allocation results are
scripted; the retail vector helper and constructors execute in both runs.
The parser is compiled as C++03 with exceptions enabled. A small COFF module
loader retains its cleanup code, handler thunk and `.xdata` alongside the
main function, rather than discarding them during function extraction.

All **174 cases** agree on allocation sizes, callback arguments, complete
array storage, separately copied names, source mutations, return pointer,
preserved registers, stack cleanup, and normal-path restoration of FS:[0].
Cases cover empty indexes and names, alignment offsets 0 through 3, long and
high-bit names, random records, individual/all name allocation failures,
source mutation during allocation, and wrapped allocation-size calculations.
One malformed count of -1 also reproduces retail's write before the returned
entry pointer; this is characterization, not a valid archive format.

```sh
python3 matching2/tests/dat_archive_parser_differential.py
python3 matching2/tests/dat_archive_parser_unwind.py
```

Requires native `clang++` and Python's `unicorn`; the local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. The earlier
exception-disabled Clang body was 236 bytes. The current complete emulated
module is 428 bytes, including code, alignment and unwind metadata; this is
not a like-for-like comparison with the retail parser's 327-byte main body.
The [DAT integration test](dat_archive_integration.md) additionally exercises
this parser between the recovered index decoder and archive reader.

## Unwind-action test

`dat_archive_parser_unwind.py` stops at selected operator-new, vector-helper,
constructor and name-malloc call boundaries. It reads the live FS:[0] frame
chain, follows each parser handler thunk to FuncInfo, verifies one unwind
state and no try blocks, and reads the actual action pointer from the map.
State is -1 before operator new returns and 0 at the subsequent tested calls.

For a constructor interruption, the helper also has an active SEH finally
scope. The test follows its scope table, invokes its recorded funclet and
executes the real ArrayUnwind routine and entry-release callbacks in reverse
order. It then invokes the parser's table-selected outer action. Retail and
Clang actions both free the raw array exactly once; an interruption in
operator new itself frees nothing. Interrupting a later name allocation
leaves earlier names allocated, as the retail metadata requires.

All **278 comparisons** agree on observed states, action effects, callback
order, freed pointers, complete array/name storage, and nested-frame
restoration. Cases cover counts 0/1/2/7/16, every constructor including the
sentinel, every name allocation, four input alignments and prior null name
allocations.

This test manually performs frame removal and invokes actions under the
documented x86 frame conventions. It does **not** raise a Windows exception,
run catch selection, or execute the runtime frame handlers. Clang emits
FuncInfo version `0x19930522` and references CxxFrameHandler3; retail uses
version `0x19930520` with its older handler. The test does not substitute one
runtime handler for the other. It also does not prove asynchronous-fault
coverage at memory instructions between the tested call boundaries.

## Remaining recovery

Ghidra MCP calls and Wine's server socket remain denied by session settings.
The work uses saved Ghidra evidence and verified executable bytes. Recover
the exact compiler-generated frame with native MSVC, retain the array cookie
and callback conventions, verify the associated handler/unwind metadata, and
then run region and whole-image byte gates before replacing the maintained
assembly. Behavioral cleanup agreement does not establish byte identity or
complete Windows exception equivalence.
