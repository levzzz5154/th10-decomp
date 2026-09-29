# Sound worker setup at `0x0043D080` — live Ghidra ABI audit

Date: 2026-09-23. Read-only review of the live `th10.exe` Ghidra program.

2026-09-26 follow-up: the [tested producer recovery](sound_preload_worker_0043d080.md)
now connects this routine to the maintained cached loader and recovered DAT
read/decode closure. The original ABI audit below remains relevant to native
matching; its closure requirement is now met for behavioral testing.

## Function and call behavior

Ghidra places one function at `0x0043D080..0x0043D0EA` (107 bytes). Its
decompilation shows a no-argument worker that scans 0x25 resource names from
the table at `0x00474B40`, stores returned buffers in the pointer table at
`0x004977C0`, and consults the state dword at `0x004977B4`. It returns
immediately when the state is 2, logs a filename and returns if a load fails,
and after all 37 loads polls the state with `Sleep(1)` until it changes.
Ghidra reports no direct function caller; its xref at `0x004201F3` is the
thread-start address passed to `CreateThread` from the startup path.

The entry body itself is small and has no declared inputs. The blocking ABI is
the loader call at `0x0043D097`:

```text
0043D08C  mov eax,[esi*4+0x474B40]  ; selected resource path
0043D093  push 0                    ; mode = archive lookup
0043D095  push 0                    ; no output-size pointer
0043D097  call 0x0044B360
```

Live Ghidra decompiles `0x0044B360` as
`byte* __stdcall FUN_0044B360(size_t* out_size, int mode)`, but its path input
is actually live in EAX at entry. With this call's mode set to zero, the helper
does not use its ordinary disk-file branch. It enters the archive branch:

1. It holds the critical section at `0x004922A4` and updates the active-reader
   count at `0x0049231E`.
2. It searches for a final forward slash after the last backslash; when none
   exists it uses the original path, including any backslashes. It scans the cached archive records at
   `0x00497990` (`0x00497994` is the count), comparing names case-insensitively.
3. It takes the uncompressed size from the matching record, allocates that
   buffer, and calls `0x00434DD0` to read and decode the archived payload.

The `0x00434DD0` read path is not a plain Win32 file open. It receives the
archive base and output buffer on the stack plus the basename in ECX; it finds
the archive entry, reads the stored range through the archive object's virtual
methods, decrypts the data, and conditionally LZSS-decompresses it. Its private
entry and codec contracts are recorded in
[`archive_codec_cursor_00434d10_00434dd0_00434f30_00435dc0_0044b0d0_0044b220_0044dd40_0044de10.md`](archive_codec_cursor_00434d10_00434dd0_00434f30_00435dc0_0044b0d0_0044b220_0044dd40_0044de10.md).

The other worker calls are also visible in Ghidra: the wait path calls the
`Sleep` import through `0x004660AC`, and the error path calls
`0x0044B810` with `ECX=0x00474F70`, the format string at `0x0046FDD4`, and the
selected path as a stack value.

## Conversion boundary

Replacing `0x0044B360` with direct `CreateFileA`/`ReadFile` calls inside this
worker would change behavior. The worker explicitly selects mode zero, which
searches the DAT archive cache and runs the archive read/decrypt/decompress
path; it is not the helper's nonzero mode that opens a filesystem path.

A readable conversion therefore needs either an ABI-preserving native context
that supplies the path in EAX and retains the helper's real calls, or a C++
conversion of the mode-zero loader together with the archive read/decode
closure rooted at `0x00434DD0`. Substituting ordinary Win32 open/read calls is
not a complete conversion boundary for these 37 resources. No source or
manifest promotion was made in this audit.
