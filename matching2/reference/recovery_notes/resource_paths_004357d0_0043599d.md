# Resource registration and file dispatch

2026-09-26. Assembly-free candidates now cover resource registration
(`0x004357D0`, 36 bytes), resource loading (`0x00435800`, 214 bytes), resource
size queries (`0x004358E0`, 190 bytes), and archive entry-size lookup
(`0x00434EF0`, 51 bytes). They pass 518 retail comparisons. Production entries
remain assembly pending native MSVC and private-ABI recovery.

## Source and evidence

The candidates are `reference/semantic_candidates/resource_paths.cpp`,
`unassigned_004357d0.cpp`, and `dat_archive_find_size_00434ef0.cpp`. They reuse
the tested archive layouts in `dat_archive_types.hpp` and the maintained
FileHandle class declaration. Standalone constructor, destructor, Close and
GetSize definitions follow `msvc/src/platform/file.cpp` so the compiler can
inline stack-file lifetime management. They are not additional production
definitions.

Saved Ghidra bodies for `00435800`, `004358E0`, `00434EF0`, `004356F0`, and
`00452730` establish their complete behavior and helper interfaces. The saved
registration audit and maintained 36-byte body establish `004357D0`; its
instructions were executed from the verified image during testing.

| Entry | Retail interface | Candidate interface |
| --- | --- | --- |
| RegisterArchive | path in EAX; AL result; plain RET | stdcall path parameter |
| Resource Load | path in ECX; output on stack; RET 4 | stdcall path/output |
| Resource GetFileSize | path in ECX; plain RET | stdcall path |
| Archive FindSize | archive in EAX, name in EBX; plain RET | stdcall archive/name |

## First-slash routing correction

The helper at `0x00452730` finds the **first** matching byte, not the last.
Earlier resource notes described it incorrectly. The maintained archive
selector at `0x004356F0` substitutes `.dat` starting at the first `/` and
compares the resulting archive filename case-sensitively. The outer resource
functions pass everything after that first slash to the selected archive.

For example, `pack/dir/asset.bin` selects `pack.dat` and looks up
`dir/asset.bin`. `PACK/asset.bin` does not select a stored `pack.dat`.
Backslashes do not act as separators here. With no slash, the complete path
is used for both archive selection and, if selected, entry lookup. Entry
lookup itself uses the CRT case-insensitive comparison.

## Lifetime and state

Registration selects `archives[count]` from `0x004923B0` using the count at
`0x00477850`, then calls the recovered disk opener. It does not check capacity
or separately initialize that slot. Success increments the **current** count
after the call, with 32-bit wrapping. The candidate's unsigned count preserves
this even when the callback changes the global. The real opener always
returns AL 0/1; upper EAX bits are unspecified.

When an archive is selected, Load forwards the supplied buffer to the archive
reader. GetFileSize returns the first matching entry's unpacked size; null
entries, nonpositive signed counts, or no match return zero. The lookup caches
the entries pointer/count and uses the existing sixteen-byte entry stride.

Without an archive, both functions construct a twelve-byte stack FileHandle,
call Open with the global mode, and ignore its return value. The actual handle
field controls whether GetFileSize is called and whether cleanup closes it.
Load calls ReadWhole with the queried size even after a failed Open or an
invalid handle. This branch ignores the caller's supplied output buffer.
Changes to the handle during GetFileSize or ReadWhole are observed by cleanup.
GetFileSize's result is retained even if its callback changes the handle.

The stack FileHandle supplies ordinary C++ destruction on normal and exceptional
exit. Retail's recorded unwind actions at `0x00465380` and `0x004653A0` call
the maintained destructor at `0x00435340`. The C++ exception state is inactive
during archive selection/dispatch and active once the local file is constructed.

## Validation

```sh
python3 matching2/tests/resource_paths_differential.py
```

The test uses native Clang, Python Unicorn, and the verified retail `.text`.
It executes the actual retail archive selector, first-byte search, security
cookie check, entry-size lookup and CRT C-locale comparison. Open, ReadWhole,
archive reads and Windows imports are scripted collaborators. The candidate
COFF module retains its generated C++ cleanup actions and metadata; the test
loader now resolves the compiler's weak deleting-destructor aliases too.

All **180 load, 178 resource-size, 120 registration, and 40 entry-size cases**
agree on collaborator calls, state visible at calls, results, count updates,
output preservation, normal callee-saved registers and stack cleanup. Cases
include nested/repeated/trailing slashes, case differences, backslashes,
missing archives, null entries, signed count boundaries, ignored Open
results, zero/large sizes, supplied buffers, and callback changes to handles
and the registration count. Registration tests retain valid AL 0/1 opener
results while varying unspecified upper EAX bits.

Twelve cases stop at selected call boundaries and manually invoke the action
from the live frame's unwind map. These cover both inactive archive-path
states and active disk-file states with valid/invalid handles. The original
and candidate actions make the same CloseHandle calls. As with the parser
unwind tests, Windows exception dispatch and catch selection are not executed.

The standalone resource module includes 1,098 bytes of code, vtable data,
alignment and EH metadata. This is not a like-for-like byte comparison with
the two retail main functions. No MSVC byte match is claimed. The local run
used `matching2/build/lzss-compressor-recovery/venv/bin/python`.

## Remaining work

The resource candidates now pass [full recovered DAT integration](resource_archive_integration.md):
456 resource loads, 228 size queries and 73 registration attempts, including
simultaneously open archives and registration retries. The
[loose-file integration](resource_loose_file_integration.md) also passes 420
resource loads, 210 size queries and 108 direct ReadWhole calls with the
recovered opener/resolver, maintained ReadWhole and scripted Windows imports.
Their private entry conventions and generated frame layout need native MSVC
recovery before region and whole-executable byte gates can permit promotion.
Ghidra MCP calls remain denied by the session's approval policy; this work
uses saved Ghidra evidence and the verified executable.
