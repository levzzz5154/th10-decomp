# CRT floor dispatcher at 0x00452FF0

Ghidra identifies `0x00452FF0` as the VS2003 CRT floor routine. It accepts one
8-byte `double` on the stack, uses cdecl caller cleanup, and returns its value
in x87 `ST(0)`. Ghidra's extra `undefined2` parameter is analysis noise; all
seven retail call sites push an 8-byte argument and consume the x87 result.

The routine uses an SSE2 path when the CRT's feature flag and floating point
control state permit it. It sends the other cases to `__floor_default` at
`0x00458C39`. Finite inputs receive mathematical floor, including negative
fractions; infinities pass through. NaNs follow the CRT matherr and exception
paths. A source replacement must preserve those special-value and floating
point environment behaviors as well as the ordinary numeric result.

The 21-byte wrapper at `0x00427C50` widens a float, calls the dispatcher, and
returns with `ret 4`, leaving the result in `ST(0)`. Its two retail callers
store that value as float. The current source models the value as an x87 side
channel by declaring the wrapper `void`; changing it to a normal C++ return
would need to retain the caller-visible float result and reproduce the wrapper
bytes.

No source region was promoted in this audit: the dispatcher and fallback stay
inline assembly until a C++ body can meet the repository's output and CRT
behavior requirements. This pass changed only the two C++ ABI declarations
and the wrapper comment. No build, probe, or test was run.
