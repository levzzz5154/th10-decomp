# Archive entry reader `0x00434DD0`: complete native recovery

The complete 281-byte reader now passes the ordinary native LTCG probe with
literal retail bytes, including alignment, calls, and final `RET 8`. Its
exclusive maintained source remains
`matching2/msvc/src/archive/dat_archive_read_00434dd0.cpp`. The sole proposed
region is `0x00434DD0`, 281 bytes, `_DatArchiveRead@12`, semantic owner
`0x00434DD0`; whole-executable integration and its incremental byte gate are
handled separately by the root agent.

Native and retail reader SHA-256 are both
`ea3f00af1bf160767e8c98f070ad1fce8cf89f3a003f165db9708f7dd418f1dc`.
The normalizer changes zero instruction bytes and zero address operands,
masks zero bytes, and uses no reference bytes to build the function.

## Source and genuine caller graph

`TryReadEncrypted` is a complete inline C++ helper for buffer reuse or
allocation, seek/read, and failure cleanup. Its reference output is the
actual encrypted buffer consumed by the remainder of the reader. The helper
fully inlines and introduces no emitted function or extra code symbol.
Extracting the complete operation preserves the optimizer's reference flow
and produces the retail ESI stored count, EDI encrypted buffer, cached unpacked
size, early failure cleanup, and later pointer-comparison cleanup.

The dedicated layout is
`matching2/msvc/layout/ltcg/archive_read_00434dd0.json`; its driver is
`archive_read_00434dd0_context.cpp`. Complete local counterparts under
`layout/ltcg/archive_read_00434dd0/` are copied unchanged from the maintained
`native_archive_read` graph. The source declares the three logical reader
arguments as ordinary C++ parameters. Native `/GL` plus `/LTCG` derives name
in ECX, archive/output as two stack arguments, result in EAX, and `RET 8`.

The compiler graph contains actual game bodies and actual call edges:

- `ComputeExecutableChecksum` at `0x0043A1C0`, a genuine zero-argument entry,
  calls the loader at `0x0043A1FD` with its real filename, size pointer, and
  `fromDisk=1`.
- Complete `Archive_LoadFile` at `0x0044B360` calls the reader at `0x0044B410`
  with the global archive, looked-up basename, and allocated output.
- The reader calls Find at `0x00434DE9`, the cipher at `0x00434EAD`, and the
  decoder at `0x00434EC2`.

Only the reader is selected in this new scope. The existing Find53,
loader360, and checksum207 owners, sources, and layouts stay unchanged. Their
complete local copies and the complete cipher counterpart receive zero
additional recovery credit.

| Local body | Full native extent | Matching retail positions | Derived ABI |
| --- | ---: | ---: | --- |
| Reader | 281 | 281 | Name ECX; archive/output stack; EAX result; RET8 |
| Find | 53 | 53 | Archive EAX/name EBX; EAX result; plain RET |
| Loader | 360 | 360 | Name EAX; out-size/from-disk stack; EAX result; RET8 |
| Checksum | 207 | 207 | Real zero-argument entry; EAX result; plain RET |
| Cipher, unselected | 323 | 226 | Key AL; data/size/step/block/limit stack; EAX result; RET20 |

Every counterpart occupies its original address and has the complete natural
section extent in the native map. Cipher323 remains unmatched by 97 bytes;
its valid private ABI is used here without claiming its implementation exact.
The layout's post-reader gap begins at `0x00434EE9` and is 71 bytes. The older
279-byte model and its 73-byte gap remain untouched in other scopes.

The recovered source preserves the behavior documented in
[the September semantic receipt](dat_archive_read_00434dd0.md): low-byte Seek
success, any nonzero 32-bit Read result, reload of the file pointer after
Seek, stored name after I/O, unpacked size cached before I/O, ignored cipher
return, and both observed cleanup cases, including release of a reused output
on failure and the raw no-output path returning its released allocation.

## Proof and bounded experiments

The ordinary probe was run against the isolated production-shaped project:

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/archive_read_20261002/dedicated_project \
  --source src/archive/dat_archive_read_00434dd0.cpp \
  --output matching2/build/archive_read_20261002/dedicated_probe
```

The probe reports `EXACT` for all 281 bytes. The compiler receipt is
`matching2/build/archive_read_20261002/dedicated_probe/clusters/archive_read_00434dd0/report.json`.
An independent direct native-PE/retail comparison, extent and unchanged-owner
checks are saved in `matching2/build/archive_read_20261002/dedicated_read_receipt.json`;
`verify_dedicated.py` reproduces them. A second agent independently verified
all five full body extents, literal matches, genuine call targets, current
input hashes, and absence of emitted helper symbols without rebuilding.

Before the complete helper, name reuse and file getters stayed at 279 bytes
with only 34 matching positions. Mutating the output formal produced 305 bytes,
133 matching positions, and the wrong private entry ABI. An allocation-only
reference helper produced 303 bytes with 170 matching positions; combining
allocation acceptance with OR produced 289 bytes with 33 matching positions.
Adding the complete genuine ResourceLoad/BufferFileOpen caller closure did not
change the original 279-byte result. These bounded failures receive no credit;
their sources and measurements remain under
`matching2/build/archive_read_20261002/` and
`matching2/build/archive_read_helpers_20261002/`.

No inline assembly, raw instruction emission, instruction rewriting,
synthetic caller, extra ABI argument, volatile value, or artificial barrier
was introduced. Tools and shared game headers are unchanged. The unrelated
43-byte file bitmask helper has no known true caller and was excluded.

## Integrated whole-executable gate

Root integrated the maintained ownership metadata. The incremental build
passed with zero failures: 1,604 unchanged units reused, six compiled, and
150 toolkit library members extracted. All 487,936 output bytes match retail;
zero bytes are masked. Whole-executable SHA-256 is
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The three new recoveries replace 1,158 assembly bytes. Linked body/source/layout
hashes and package evidence are saved in
`matching2/build/experiments/quad_teardown_archive_2026_10_02_verification.json`.
The full inline-assembly-removal goal remains incomplete.
