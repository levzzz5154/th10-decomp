# CRT region screen: `0x0045287B`, `0x00453783`, `0x00453A1C`

Read-only Ghidra checks and source inspection were performed for the three
assembly regions listed in `0045xxxx_0046xxxx_wave18.md`. No build, probe, or
test was run.

## `0x0045287B`: ordinary C++ recovery

The live Ghidra function lookup does not create a `Function` object at this
address and reports no incoming function references. The byte listing does,
however, decode a complete 167-byte instruction sequence from `0x0045287B`
through the final `RET` at `0x00452921`, matching the manifest extent. The
sequence saves and restores EBX, EBP, ESI, and EDI; reads one pointer argument
from `[ESP+0x14]` after four pushes; returns the 64-bit accumulator in EDX:EAX;
and uses a plain `RET`. This supports the raw call contract
`__cdecl(const char*) -> __int64`.

The body obtains the current thread locale, skips locale-classified whitespace,
accepts one optional sign, accumulates decimal digits in a wrapping 64-bit
value, and applies two-word negation for a leading minus. Its behavior and
placement beside `_atol` strongly indicate the CRT `_atoi64` routine; that
name remains an inference because Ghidra has no function symbol or callers for
this entry. `src/unidentified/unassigned_0045287b.cpp` expresses this behavior
in ordinary C++ while retaining the existing raw C symbol and call ABI. The
manifest classifies the 167-byte region as semantic and the shared header
declares its inferred cdecl signature.

## `0x00453783`: overlapping tail and unowned body

Ghidra resolves `0x00453783` inside `fast_error_exit` at `0x00453762`, whose
body includes the three-byte `POP ECX; POP ECX; RET` tail at `0x00453783` through
`0x00453785`. The assembly region then continues at `0x00453786` with a
separate PE-header check ending in `RET` at `0x004537DB`; Ghidra finds no
function at `0x00453786` and no incoming reference to the region start. Thus
the 89-byte manifest extent combines another function's epilogue with an
unidentified code body. One ordinary C++ function cannot own that whole
extent without a manifest split and a recovered boundary for the second body.

## `0x00453A1C`: globals and callback ABI unresolved

Ghidra finds no function at `0x00453A1C` and no incoming references to the
entry. The 127-byte listing reaches a `RET` at `0x00453A9A`, but the body is a
global-state loop that calls function pointers loaded from `0x00466188`,
`0x004661E8`, and `0x00466190`, while walking records rooted at
`0x0049932C`. The current source and available neighboring code do not
establish those globals' types, callback signatures, or the intended entry
contract. Leave it in assembly until those dependencies and its ownership are
resolved.
