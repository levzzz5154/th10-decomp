# CRT locale value helper at `0x0046041E`

## Boundary and ABI

Live Ghidra analysis identifies one function from `0x0046041E` through
`0x0046054D` inclusive (304 bytes). Its prototype is a normal four-argument
`__cdecl` function returning an integer in EAX:

```text
int helper(int mode, LCID locale_id, LCTYPE locale_type, void *output)
```

The 63 call xrefs come from `__get_lc_time`, `FUN_0045bb33`,
`___init_numeric`, and `___init_monetary`. Caller assembly pushes mode, locale,
locale type, and output pointer right-to-left; callers clean the four arguments
and consume the EAX status. The callees are the CRT ANSI and wide locale-info
wrappers, `GetLastError`, `_malloc`, `_free`, `_strncpy`, `_isdigit`, and the
security-cookie check. No input or output is carried in a private register ABI.

The shared `asm_symbols.hpp` still has a legacy `void helper()` declaration,
because its callers refer to this function from inline assembly. The recovered
definition locally masks that one declaration and gives the same C-linkage
symbol its observed four-argument type; it does not alter shared headers,
aliases, or the region manifest.

## Behavior

`mode == 1` retrieves an ANSI locale string. It first asks the CRT wrapper to
write into a 128-byte local buffer. If that fails with `ERROR_INSUFFICIENT_BUFFER`
(`122`), it queries the needed length, allocates a temporary buffer, and retries.
It then allocates the result buffer, stores that pointer through `output`, and
copies exactly the returned length with `_strncpy`. A retry buffer is freed on
both retry failure and after the copy. Failures before result allocation leave
`*output` untouched; result-allocation failure stores null before returning
`-1`. Success returns `0`; failure returns `-1`.

`mode == 0` asks the wide wrapper to write up to four UTF-16 code units at the
shared buffer `0x004776C4`. On API failure it returns `-1`. On success it sets
the output byte to zero, then consumes the low byte of each of at most four
wide characters while `_isdigit` accepts it, accumulating decimal digits in
that byte (including byte-width wraparound). A nondigit ends the scan, and the
function returns `0`. Any other mode returns `-1` without touching output.

The wrappers at `0x00461695` and `0x00461565` take five stack slots. Their
first four slots implement the locale ID/type/output/capacity call; the fifth
is the code-page fallback input used by the ANSI/wide conversion wrapper. These
call shapes are visible at this function's call sites and are retained by the
typed replacement.

## Integration status

`matching2/msvc/src/unidentified/FUN_0046041e_0046041e.cpp` contains the
readable C++ implementation. The manifest now marks the 304-byte region
semantic while preserving `_asm_FUN_0046041e_0046041e` as its entry symbol for
the existing assembly callers. The shared header declares the recovered
four-argument helper ABI and the five-argument ANSI/wide locale-wrapper ABIs;
the wrapper bodies themselves remain assembly.

No build, probe, or test was run, so the generated code and final `.text`
placement have not been verified.
