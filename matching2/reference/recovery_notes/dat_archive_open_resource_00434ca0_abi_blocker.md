# `DatArchive_OpenResource` at `0x00434CA0`

Date: 2026-09-23

Historical ABI audit. A typed candidate now passes 97 resource-opening
comparisons and complete synthetic archive lifecycle tests; see
[the current opener recovery](dat_archive_open_00434c30_00434ca0.md).
The private ABI and MSVC byte gates remain outstanding, so the production
body is still assembly. The no-candidate/no-test statements below describe
the earlier audit only.

## Decision

Retain the naked body in `src/archive/dat_file.cpp`. Ghidra confirms the
allocation, field initialization, load, filename-copy, and failure-cleanup
behavior, but the entry and direct helper calls use private register
conventions that ordinary x86 C++ declarations do not express. No source body
change was made. No build, probe, or test was run.

## Ghidra evidence and references

The live `th10.exe` function spans `0x00434CA0..0x00434D03` inclusive (100
bytes), ending in a plain `RET`. Ghidra decompiles it as
`undefined4 __fastcall FUN_00434ca0(int param_1)` with `param_1` in ECX and a
phantom `in_EAX`; the machine body confirms the inputs are the archive object
in ECX and the path in EAX. The result is Boolean in AL (`1` on success, `0`
on failure); the upper EAX bits are not established on both exits.

Direct instructions reference:

| Address | Observed use |
| --- | --- |
| `0x00434D10` | Called twice as `CloseDatArchive`; archive receiver is kept in ESI. |
| `0x00452493` | Cdecl allocation of `0x10` bytes. |
| `0x00434F70` | Called with ESI holding the archive and the path pushed on the stack; callee returns AL and uses `RET 4`. |
| `0x00435220` | Called with the path in EDI; returns the copied string pointer in EAX. |

`get_function_callers`, `get_function_xrefs`, and xrefs-to-address report no
direct callers or references to `0x00434CA0`. Its outgoing call references
are the four addresses above. Nearby `0x00434C30` (`FUN_00434c30`) has the same
ECX archive / EAX path entry shape. Its two direct callers are
`0x00420100` and `0x004357D0`; both `0x00434C30` and this target call
`0x00434F70` and `0x00435220`.

The neighboring helpers confirm the ABI dependency:

- `0x00434D10` reads the receiver from ESI and returns with plain `RET`.
- `0x00434F70` keeps its archive receiver in ESI, receives a four-byte path
  argument on the stack, returns its Boolean in AL, and uses `RET 4`.
- `0x00435220` reads its source string from EDI and returns with plain `RET`.

The target's own control flow first closes the current archive, allocates a
16-byte file object, initializes its vtable at `0x0046F328` and clears the
remaining three DWORDs, then stores it at archive offset `+0x0C`. If the
allocation succeeds it loads the index; on success it duplicates the path and
stores that pointer at archive offset `+0x08`. A failed load or failed copy
closes the archive before returning false. Allocation failure returns false
after storing null at `+0x0C`.

## ABI blocker

The target's explicit path is in EAX at entry. MSVC x86 `__thiscall` would put
the archive in ECX and the path on the stack; `__fastcall` would put its first
explicit argument in EDX. Neither expresses ECX plus EAX. The direct calls
also rely on ESI- and EDI-held arguments for Close, LoadIndex, and string
duplication. Those register placements cannot be guaranteed by ordinary C++
function declarations or ordinary calls. In addition, LoadIndex remains a
naked function with its own ESI/stack ABI. These contracts need an ABI bridge
or caller-inclusive compiler-context proof before this function can be
represented as an ordinary C++ function.

## Names and aliases

Ghidra names the entry `FUN_00434ca0`; `DatArchive_OpenResource` is the local
source/comment label, not a recovered Ghidra symbol. The existing raw manifest
alias is `asm_DatArchive_OpenResource_00434ca0`, linked as
`_asm_DatArchive_OpenResource_00434ca0` at `0x00434CA0`. The corresponding
declaration and `VA_` macro are absent from `asm_symbols.hpp`; this audit did
not edit that shared header. No original decorated C++ name or verified
canonical semantic alias is present, so a `?DatArchive_OpenResource@@...`
symbol must not be inferred from the local label alone.
