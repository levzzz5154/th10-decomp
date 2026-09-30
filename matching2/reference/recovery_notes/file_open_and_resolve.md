# FileHandle Open and path resolution

2026-09-26. Assembly-free candidates for FileHandle Open (`0x00435370`, 239
bytes) and path resolution (`0x00435610`, 121 bytes) pass **239 opener and 315
resolver comparisons**, including **50 matching memory faults**. The sources
are `semantic_candidates/file_handle_open.cpp` and `file_resolve_path.cpp`.
Both remain outside the exact-build manifest.

## Recovered behavior

The saved Ghidra C and instruction listings for both addresses agree on the
following behavior, confirmed by executing the verified retail image.

Open calls the virtual Close method first. It scans the mode string until the
first lowercase `r`, `w` or `a`; all preceding characters are ignored. Read
selects access `0x80000000` and disposition 3. Write calls DeleteFileA on the
original input path, then selects access `0x40000000` and disposition 2.
Append selects write access and disposition 4. No supported character returns
false. DeleteFileA's result is ignored, and the selected mode character is
read again afterward before proceeding.

The resolver fills a 260-byte stack buffer. CreateFileA receives the resolved
path, the object's current access field, share mode 1, null security/template,
the selected disposition and attributes `0x08000080`. Its returned handle is
stored even when it is invalid. A handle other than -1 is success, including
zero. Append then calls SetFilePointer with distance zero and origin 2; its
result is ignored. Open returns canonical AL 0/1. Close and subsequent import
callbacks can change the caller's path/mode or object state; tests preserve
the observed ordering and reloads rather than caching these fields early.

The resolver tests for **any colon anywhere in the path**. If present, it
copies the current source bytes forward through the terminating NUL. It does
not validate drive-letter syntax. Otherwise it calls GetModuleFileNameA with
module zero and capacity 260, ignores the result, and finds the last backslash
in the output. It truncates immediately after that separator and appends the
source's current NUL-inclusive contents.

When no backslash exists, retail first clears output[0], then still writes a
zero byte to address 1. The candidate retains this unconditional write using
integer-address arithmetic and a volatile byte access. It does not silently
repair the fault. A test with a deliberately mapped null page also confirms
the write and subsequent append when that address happens to be writable.

Relative appends first measure the source, then locate the destination NUL,
then copy forward in four-byte snapshots followed by the remaining bytes.
This matters when the source and destination overlap or the module-name call
overwrites the source. The C++ source retains byte reads for the two scans to
avoid compiler substitution of a strlen that inspects bytes beyond the NUL.
It neither bounds the final append nor substitutes memmove.

## Validation

```sh
python3 matching2/tests/file_open_resolve_differential.py
```

The native-Clang x86 Windows modules contain 233 bytes for Open and 239 for
the resolver. Open calls the compiled resolver directly in candidate runs.
The actual retail virtual Close, first-byte search, strrchr and security-cookie
helper execute; Windows imports are scripted. Cases cover mode prefixes and
precedence, valid/invalid/zero handles, ignored import results, callback changes,
absolute and relative paths, empty names, colon placement, slash differences,
overlap in both copy branches, and seeded random paths beyond 260 bytes in the
standalone resolver. Boundary cases put terminators at the last mapped byte
and cross the destination boundary during appends. Fault kind, address, width,
value and preceding writes agree.

Comparisons cover ordered import arguments and state, AL results, file fields,
input/output bytes and guards, stack cleanup and preserved registers on normal
return. The local run used the installed Unicorn environment at
`matching2/build/lzss-compressor-recovery/venv/bin/python`.

Open's thiscall entry contract is already expressible with its typed class
method. The resolver candidate uses ordinary cdecl path/output parameters;
retail instead receives them in EAX/ECX and uses plain RET. The Clang fixture
disables stack protection, so it does not validate native MSVC's stack-cookie
frame, cookie-failure behavior or long-path corruption inside Open. Windows
imports and exception dispatch are not executed. Native MSVC byte matching and
whole-executable gates remain required before either source can be promoted.
