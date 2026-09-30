# Loose-file resource integration

2026-09-26. **420 resource loads, 210 resource size queries and 108 direct
ReadWhole calls** agree with the verified retail executable. Five primary C++
functions execute together: Resource Load/GetFileSize, FileHandle Open, path
resolution and ReadWhole. No production region was promoted.

## Test scope

`matching2/tests/resource_loose_file_integration.py` freshly compiles the four
unpromoted resource/file candidates and extracts ReadWhole from the maintained
`msvc/src/platform/file.cpp`. Candidate resource calls bind directly to the
compiled Open and ReadWhole; Open binds to the compiled resolver. Typed stack
FileHandle construction, GetSize, Close and destruction also run from the
resource module's C++ context. The actual retail Read, Tell, Seek, string
search helpers and security-cookie check execute as applicable. Only Windows
imports and allocation/free are scripted. No file methods are substituted
with virtual-I/O mocks in this test.

The resource registry count is zero so all resource calls exercise disk
fallback. Inputs cover relative/nested, colon-containing and rooted paths;
payload sizes zero through 4096; valid, zero and invalid handles; allocation
failure; full, short and zero-byte reads; independent ReadFile Boolean and
byte-count results; changing size between the resource query and ReadWhole;
and failed SetFilePointer results. Import callbacks can change the handle and
access fields during either size call, seeking, reading or closing.

Direct ReadWhole tests vary read/write/no access, handle validity, capacity
and starting position. This checks the maintained C++ implementation against
the original body as well as exercising it through resource dispatch.

## Confirmed behavior

- Disk resource loads always request fresh allocation. They leave caller
  output untouched, even when one is supplied.
- ReadWhole accepts only exact access `0x80000000`. It obtains the current size
  through the vtable and rejects a size exceeding capacity before allocating.
  Thus a file that grows between the resource's outer size query and the inner
  query is rejected.
- ReadWhole remembers the current position and seeks to that same position,
  without seeking to the beginning. It requests the complete reported file
  size from there, so a nonzero starting position can produce a short read.
- Read returns the byte count written by ReadFile, ignoring its Boolean
  result. ReadWhole treats any nonzero byte count as success, returns the
  allocation and attempts to restore the saved position. Unread bytes remain
  untouched. Independent fixture assertions cover both short successful reads
  and nonzero byte counts paired with a false ReadFile result.
- A zero-byte read frees the allocation. If the initial virtual Seek returns
  false, the function returns null **without freeing it**. With an invalid
  handle but read access, GetSize returns zero, allocation can succeed for size
  zero, Tell returns zero, and Seek fails: this path leaks the allocation.
- The maintained Seek wrapper ignores SetFilePointer's return value for a
  valid handle. A failed Windows seek therefore still yields virtual Seek
  success. Later cleanup observes the current handle field, including changes
  made during I/O callbacks.

Each comparison checks ordered Windows/allocator arguments and visible object
state, results, allocations and guards, file position, output preservation,
normal stack cleanup, preserved registers and restored FS:[0]. Successful
buffer contents and untouched tails are also checked against fixture bytes.
The test explicitly requires witnesses for the short-read, ignored-Boolean
and failed-Seek leak behavior above.

## Reproduction and limits

```sh
python3 matching2/tests/resource_loose_file_integration.py
```

Requires native Clang, the project's headers and Python Unicorn. The local
run used `matching2/build/lzss-compressor-recovery/venv/bin/python`. Windows
imports are deterministic collaborators, not live filesystem operations.
The script does not simulate exception dispatch or Open's stack-cookie
corruption, and the resolver's retail private entry ABI is still unrecovered.
Native MSVC region and whole-executable byte gates remain required.

Related notes: [Open/resolver](file_open_and_resolve.md),
[resource dispatch](resource_paths_004357d0_0043599d.md),
[resource-to-DAT integration](resource_archive_integration.md).
