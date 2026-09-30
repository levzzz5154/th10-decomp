# `DatArchive_FindSize` at `0x00434EF0`

`DatArchive_FindSize` is now recovered as ordinary C++ and matches its 51-byte
retail body exactly. It receives the archive in EAX and the requested name in
EBX, scans the archive's 16-byte entries using the existing case-insensitive
comparison helper, and returns the matching entry's uncompressed size from
offset 8, or zero if there is no match.

The implementation is in
[`dat_archive_find_size_00434ef0.cpp`](../../msvc/src/archive/dat_archive_find_size_00434ef0.cpp).
The archive and entry layouts are shared with the other archive recoveries in
[`dat_archive_types.hpp`](../../msvc/include/th10/archive/dat_archive_types.hpp).
The C++ declaration uses ordinary parameters, but the generated body preserves
the retail register interface and plain `RET`.

## Native LTCG context

MSVC 13.10.6030 initially generated the correct 51-byte extent with a 12-byte
register-allocation difference. Reusing the typed archive layout and changing
the successful-match path to a label outside the scan loop produced the exact
body. The production cluster is described by
[`archive_find_size_native.json`](../../msvc/layout/ltcg/archive_find_size_native.json).
Its synthetic caller keeps the return value live to establish the compiler
context; that caller is not recovered application code and contributes no
selected bytes.

The focused probe reports all 51 bytes exact, zero differing bytes, no
relocations, no masking, and the expected ABI. The function body SHA-256 is
`50e729e597b4fbe49a9d5b5c32d71f84a441000ca0ecf84e9bfd46781b8d091c`.
Its report is under
`matching2/build/probe_archive_find_size_exact_20260930`.

The complete build compiled all 1,945 maintained sources and reproduced the
exact 487,936-byte executable with SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The failed first attempt was a transient Wine launch error for an unrelated
cluster; the retry completed without compile failures.
