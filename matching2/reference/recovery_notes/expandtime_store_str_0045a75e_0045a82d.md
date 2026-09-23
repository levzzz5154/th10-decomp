# CRT time-format cluster recovery

## Live Ghidra findings

The open `th10.exe` program labels `0x0045A75E`, `0x0045A82D`, and
`0x0045AA93` as Visual Studio 2003 CRT `__store_str`, `__expandtime`, and
`__store_winword`. The live caller query confirms that `__expandtime` has two
direct callers, `FUN_0045AF1D` and `__store_winword`; `__store_str` is only
called by `__expandtime`.

Ghidra's current decompilation and instruction listing expose these register
inputs:

| Routine | Retail inputs |
| --- | --- |
| `__store_str` | `ECX` = output-cursor address; `EDX` = source; `EAX` = remaining-capacity address |
| `__expandtime` | `AL` = conversion; `ECX` = output-cursor address; `EBX` = remaining-capacity address; stack = CRT locale, time record, locale time data, alternate-format flag |

The time record is nine 32-bit fields (`tm_sec` through `tm_isdst`, offsets
`0x00..0x20`). The locale time data starts with abbreviated/full weekday and
month names and AM/PM strings at `0x00..0x9c`; its date patterns, time pattern,
LCID, and Windows-formatter selector are at `0xa0`, `0xa4`, `0xa8`, `0xac`,
and `0xb0`. The CRT locale object supplies the byte classification table at
`+0x48`; the default locale time-data pointer is at `+0x4c`.

`__store_winword` first asks `GetDateFormatA` or `GetTimeFormatA` to render the
selected locale pattern. If that path is disabled or fails, it parses the
locale pattern itself, including repeated `d`, `H`, `M`, `h`, `m`, `s`, `t`,
and `y` fields, quoted literals, and DBCS lead bytes. `__expandtime` handles
the strftime conversion letters, calls the formatter for `%c`, `%x`, and `%X`,
and refreshes the time-zone names for `%z` and `%Z`.

## Integrated source interfaces

The four manifest-backed region files now define their original region
symbols as ordinary C++ functions with explicit source-local interfaces:

- `asm_store_str_0045a75e(cursor, remaining, source)` copies bytes up to NUL or
  exhausted capacity and does not append a terminator.
- `asm_expandtime_0045a82d(conversion, cursor, remaining, locale, time, locale_time_data, alternate)` contains the readable conversion dispatch and numeric/locale formatting logic.
- `asm_store_winword_0045aa93(locale, format_kind, time, cursor, remaining, locale_time_data)` implements the Win32 formatter and the CRT pattern fallback.
- `asm_FUN_0045af1d_0045af1d(locale, output, capacity, format, time, locale_time_data)` implements the outer format scan and calls the typed expansion routine.

This gives the cluster a normal C++ call graph while preserving every
manifest symbol. `FUN_0045AF1D` still resolves a null locale-time-data argument
through the CRT locale's `+0x4c` pointer. Its `%` and `%#` handling passes the
token and alternate-format flag explicitly, and its DBCS literal path retains
the retail capacity behavior.

The files `semantic_store_str_0045a75e.cpp` and
`semantic_expandtime_0045a82d.cpp` were earlier detached models. The
manifest-backed region implementations now contain the integrated code and
do not call those model symbols.

No build, probe, or test was run for this source change, so compiler output and
byte equivalence remain unverified.
