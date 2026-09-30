# Archive opening and filename ownership

2026-09-26. `reference/semantic_candidates/dat_archive_open.cpp` recovers the
disk and resource opener bodies as typed, assembly-free C++.
`legacy_string_duplicate.cpp` recovers their filename-copy helper. They pass
470 isolated retail comparisons and execute with the rest of the recovered
DAT lifecycle. None has been promoted into the exact-build manifest.

## Evidence and interfaces

The saved Ghidra bodies are `00434C30.{c,asm}`, `00434CA0.{c,asm}`, and
`00435220.{c,asm}` under `decompiled/ghidra_augmented/functions`. The openers
take archive in ECX and path in EAX, have no stack arguments, and define only
AL as their boolean result. The string helper receives its source in EDI,
has no stack arguments, and returns the copied pointer in EAX. The candidates
expose ordinary stdcall parameters for testing; private register recovery
still requires a native MSVC caller/callee cluster.

| Function | Retail address | Retail bytes | Clang test bytes |
| --- | --- | ---: | ---: |
| Disk Open | `0x00434C30` | 108 | 117 |
| Resource Open | `0x00434CA0` | 100 | 110 |
| String duplicate | `0x00435220` | 47 | 64 |

The openers reuse the maintained FileHandle, BufferFile and ResourceFile
class declarations. Their standalone candidate context repeats the existing
constructor definitions from `msvc/src/platform/file.cpp`, `memory_file.cpp`
and `resource_lifetime.cpp` so initialization can inline. It is not a second
production definition. The object loader binds their compiler-generated
vtable references to the retail tables. Integrating the candidate later must
use one definition of each constructor in the real compiler-visible cluster.

## Recovered behavior

Both openers first close the existing archive. Disk Open allocates twelve
bytes through `0x00452493` and initializes FileHandle's vptr `0x0046F230`,
handle -1, and access 0. Resource Open allocates sixteen bytes and initializes
the three buffer fields to zero plus vptr `0x0046F328`. Explicit allocation
and placement construction retain the retail null-allocation branch.

The new file pointer is stored even when null. A null result returns false
without another Close call. Otherwise, LoadIndex receives the original path.
Its AL result decides whether to copy that path and assign archive.filename.
Failed loading or failed filename allocation invokes Close again, then
returns false. Loading may already have deleted the file on failure; the
second Close still executes to clear the remaining archive state.

After a successful copy, disk Open calls the current file's Open again using
the owned filename and the global read-mode pointer. Its return value is
ignored: the opener returns true even when this second Open returns zero.
Resource Open returns true immediately after assigning the filename.

String duplication allocates the NUL-inclusive size found before malloc,
then copies through the source's current NUL after malloc. The second pass
does not use a cached byte count. This preserves callback-visible source
mutations and leaves the source untouched on ordinary paths. A null malloc
result returns null without copying.

## Validation

```sh
python3 matching2/tests/dat_archive_open_differential.py
python3 matching2/tests/dat_archive_integration_differential.py
```

The isolated test compiles the actual sources and compares **97 disk-open,
97 resource-open, and 276 string-copy cases** against verified retail x86.
Close, loading, allocation, and the final virtual Open are scripted; the
actual string-copy instructions execute in both runs. Cases cover all failure
stages, AL-only boolean results with nonzero upper bits, ignored reopening
results, every object-initialization word, archive/file/path mutations during
callbacks, empty and long paths, high-bit bytes, and source changes during
malloc. Allocations use mapped guard storage, so changed-source cases
characterize retail behavior rather than claiming bounds safety.

The comparison includes ordered collaborator calls, archive state visible at
those calls, full file/copy storage, source bytes, AL or pointer result,
preserved registers and each entry's own stack cleanup.

The integrated test executes all ten recovered lifecycle bodies together:
each of 56 fixtures is entered through the loader, disk opener, and resource
opener. **168 scenarios, 1,236 entry reads, 19 allocation-failure paths, and
355 cleanup calls** agree. Only the virtual file operations and allocator
remain scripted around these recovered routines; see the
[integration note](dat_archive_integration.md) for supporting retail helpers
and validation limits.

## Remaining work

Ghidra MCP is still unavailable under the session approval policy; Wine's
MSVC environment setup fails at `winepath`. Native region and whole-image
byte gates remain outstanding. The parser's allocation guard now has separate
unwind-action tests; the integration result does not establish exception equivalence or
execution against real Windows files/resources.
