# CRT ANSI locale mapping worker at `0x0045EE1D`

## Boundary and ABI evidence

The live manifest assigns `0x0045EE1D..0x0045F1F2` (982 bytes) to
`src/unidentified/FUN_0045ee1d_0045ee1d.cpp`. Ghidra's live function analysis
reports a normal `__cdecl` function with eight stack arguments:

```text
int/uint map_locale(LCID, DWORD flags, LPCSTR source, int cchSource,
                    char* destination, int cchDestination,
                    UINT codePage, BOOL rejectInvalidMultibyte)
```

The recovered caller set is `___tolower_mt`, `__mbctoupper`, and
`FUN_0045cdae`; the four call xrefs are `0x0045CE7A`, `0x0045CEA2`,
`0x00460CB7`, and `0x00458D60`. The caller stack layout and Ghidra parameter
storage agree: arguments are at `[EBP+8]` through `[EBP+24h]`, and the result
is in EAX. There is no private-register entry ABI.

## Behavior from Ghidra

The routine lazily probes `LCMapStringW` and caches its mode in
`DAT_00477694`: `1` when wide mapping works, `2` when the probe fails with
`ERROR_CALL_NOT_IMPLEMENTED` (`120`), and `0` when the capability check did
not settle either way. For positive source counts it trims the count at the
first NUL; `-1` remains the Win32 NUL-terminated convention.

In mode `1`, it converts the source with `MultiByteToWideChar` (flags `1`, or
`1 | MB_ERR_INVALID_CHARS` (`9`) when the final argument is nonzero), maps
through `LCMapStringW`, and converts the result back with `WideCharToMultiByte`.
With `LCMAP_SORTKEY`
(`0x400`), it writes the wide API's byte result directly when the caller's
destination capacity is sufficient. Temporary buffers use stack allocation
with heap fallback and are freed on function exit.

In mode `0` or `2`, the function supplies default locale/code page values
from `DAT_00477654` and `DAT_00477664`. It gets the locale's ANSI code page via
`FUN_004601A1`; if that matches the requested page it calls `LCMapStringA`
directly. Otherwise it converts the source into the locale page with
`FUN_004601E8`, asks `LCMapStringA` for the mapped size, maps into a zeroed
temporary buffer, and converts back with `FUN_004601E8`. The helper's returned
pointer distinguishes a caller-owned destination from a temporary allocation.

The implementation in the owning source now expresses these paths as ordinary
C++ and uses the observed Win32 IAT entries and existing CRT conversion,
allocation, and free helpers. It retains the established linker symbol name so
the existing callers continue resolving. The original function's SEH cleanup
is represented with `__try`/`__finally` around heap-fallback cleanup. Each
dynamic stack probe also has an `__except(1)` recovery path that calls
`__resetstkoflw` before taking the observed heap fallback.

## Dependencies and remaining verification

Ghidra decompilation confirms `FUN_004601A1` obtains the locale code page,
`FUN_004601E8` performs code-page conversion, and `FUN_0045794D` returns a
zero-initialized allocation. `FUN_004601A1`, `malloc` at `0x00452706`, `free`
at `0x00452422`, and `memset` at `0x0045BED0` have semantic source
implementations. `FUN_004601E8`, `FUN_0045794D`, and `__resetstkoflw` at
`0x00458D91` remain assembly-backed dependencies, so this promotion removes
inline assembly from this function but not from its full call graph.

The source edit did not change shared configuration. Parent-level integration
has now updated `asm_symbols.hpp` to the same eight-argument
integer-returning ABI and classified the 982-byte region as `semantic` in
`regions.json`, retaining the established linker symbol. No build, probe, or
test was run; exact compiler output and runtime equivalence of exceptional
edge cases remain unverified.
