# ResourcePath::Load at `0x00435800`

The loader is now maintained C++ with an exact retained ordinary MSVC/LTCG
probe: its complete 214-byte body, generated 8-byte cleanup, and generated
10-byte exception handler match all **232 selected bytes**. Integrated
source hashes, aliases, full previous records, genuine 46-byte lifetime and
46-byte BufferFile caller anchors, and 36 bytes of exception metadata also
pass. See [the current resource and overlay checkpoint](resource_load_size_and_overlay_2026-10-01.md).
A fresh whole-project build remains pending. The historical audit below
predates this conversion; its unresolved-status statements are superseded.

The [file-opening checkpoint](file_open_and_resolve_2026-10-01.md) separately
verified the complete native opener and path resolver, including their
private call edge and security-cookie frame.

Historical live-Ghidra audit, updated for the first-slash correction. Readable
candidates now pass 518 resource/registration/size comparisons, including
stack-file unwind actions; see
[the current resource recovery](resource_paths_004357d0_0043599d.md).
The private ABIs and native MSVC bytes remain unverified.

## Live Ghidra boundary and ABI

The live Ghidra `th10.exe` listing places one function at `0x00435800`; the
maintained region is 214 bytes (`0x00435800..0x004358D5`, exclusive end
`0x004358D6`). Its final instruction is `ret 4`. Ghidra decompiles it as
`byte* __thiscall FUN_00435800(void *this, byte *param_1)`: the resource path
arrives in ECX, the optional destination buffer is the sole stack argument,
and the returned buffer is in EAX. The entry establishes an SEH registration
and saves ESI/EDI before using the path and archive record across calls.

Ghidra's direct xref points from `0x0043640C`. Disassembly of the complete
46-byte caller (`0x00436400..0x0043642D`) confirms that it pushes null, loads
the `BufferFile::Open` path into ECX, calls `0x00435800`, and stores EAX at
`BufferFile+0x0C`. It then calls `0x004358E0` with the same path in ECX, stores
that result at `+0x04`, copies the returned data pointer to `+0x08`, and returns
whether the pointer is non-null (`ret 8`). Thus this real call exercises the
allocate-buffer path, while the target's signature still accepts a caller
buffer.

## Behavior and direct callees

The function has two paths:

1. It calls `0x004356F0` with the path. If an archive record is found, it
   locates the first slash with `0x00452730`, chooses the suffix after the
   slash (or the full path when there is no slash), and calls
   `0x00434DD0` with the record and optional destination buffer. The suffix
   remains live in ECX for this call.
2. If there is no archive record, it initializes a 12-byte stack
   `FileHandle`-shaped object (vtable `0x0046F230`, invalid handle, zero
   access), then calls `0x00435370` with that object in ECX and the path and
   mode string `PTR_DAT_00474908` on the stack. It obtains the opened handle's
   size through the `GetFileSize` import at `0x004660D8`, passes the capacity
   to `0x00435580`, restores the object's base vtable, closes a valid handle
   through `CloseHandle` at `0x004660CC`, and returns the read buffer.

The direct helper contracts established from Ghidra are:

| Address | Observed contract |
| --- | --- |
| `0x004356F0` | Path in ECX, archive-entry pointer in EAX; scans the archive table after replacing the first slash and remaining suffix with the archive marker. |
| `0x00452730` | Cdecl string search: the path and `'/'` are pushed; the result pointer is in EAX. |
| `0x00434DD0` | Archive read/decode helper; the caller supplies a suffix in ECX and two stack values (entry and optional output buffer). The helper's maintained naked body and decompiler expose further private register/stack dependencies. |
| `0x00435370` | File open: stack `FileHandle*` in ECX, path and mode on stack, Boolean result in AL, `ret 8`. Its body also owns the security-cookie frame and calls the path resolver with a private EAX/ECX contract. |
| `GetFileSize` | Win32 import receives `(HANDLE, null high-size pointer)` and returns the low DWORD size in EAX. |
| `0x00435580` | Read whole file: `FileHandle*` in ECX and capacity on stack, buffer pointer in EAX, `ret 4`. It requires read access and uses the object's vtable slots for size, tell, seek, and read. |
| `CloseHandle` | Win32 import with the handle on stack; called only for a non-invalid handle. |

These observations match the live target listing, and the current
`FileHandle::ReadWhole` source documents its corresponding size check,
allocation, read, and position restoration. The existing source for
`0x00435370` records its unresolved path-resolver and security-cookie lowering;
the existing `0x00434DD0` source records unresolved member-call and codec ABI
details. This pass did not run a build or byte probe.

## Smallest useful conversion cluster

`0x00435800` is not self-contained. Converting only its source-level body would
hide the exact archive-reader calling convention on one branch and would still
depend on the unresolved `FileHandle_OpenRetail` / `ReadWhole` object sequence
and SEH cleanup on the other. The next coherent ordinary-C++ experiment
should retain the real caller `0x00436400` and both helper closures:

- Archive path: `0x00435800`, `0x004356F0`, `0x00434DD0`, and the reader's
  entry lookup / decrypt / decompress dependencies. The focused history for
  `0x00434DD0` and its codec dependencies is
  `archive_codec_cursor_00434d10_00434dd0_00434f30_00435dc0_0044b0d0_0044b220_0044dd40_0044de10.md`.
- Disk path: `0x00435800`, `0x00435370`, `0x00435610`, `0x00435580`, and the
  `FileHandle` vtable/lifecycle methods, with the import slots bound at their
  existing addresses.
- Shared caller context: `0x00436400` (`BufferFile::Open`). The adjacent
  `0x004358E0` size query is a useful second caller for an eventual native
  LTCG cluster, but is not a direct callee of this routine.

No region or symbol metadata was changed here; `0x00435800` remains naked
assembly until that combined ABI/frame work produces a readable candidate
that can be checked against retail bytes.
