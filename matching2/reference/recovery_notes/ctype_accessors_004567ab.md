# CRT ctype accessors at 0x004567AB

The former ASM extent at `0x004567AB` contains three consecutive cdecl
accessors. Each accepts one `int` character argument on the stack and returns
the classification mask/result in EAX. The source now expresses those bodies
as ordinary C++ wrappers in `msvc/src/unidentified/unassigned_004567ab.cpp`.

| Entry | Size | Behavior |
| --- | ---: | --- |
| `0x004567AB` | 63 bytes | `isalpha` classification, mask `0x103`, 16-bit table read |
| `0x004567EA` | 58 bytes | `isupper` classification, mask `0x01`, 8-bit table read |
| `0x00456824` | 58 bytes | `islower` classification, mask `0x02`, 8-bit table read |

Each wrapper obtains the thread locale through `asm_getptd_00456357`, updates
it with `asm_updatetlocinfo_00455ade` when it differs from the default locale,
and calls `asm_isctype_mt_00455752(locale, c, mask)` when `categories > 1`.
The helper ABI is cdecl with three stack arguments: its call sites push the
mask, character, and locale pointer, then reclaim 12 bytes after the call.
For the simple locale path, the original table offset is `c * 2`; the alpha
entry reads a word while upper/lower read a byte. Return values retain the
masked bits rather than being normalized to booleans.

Ghidra identifies the first entry as `FUN_004567ab` and shows a direct call
from the `iscsymf` wrapper at `0x00456A5B`. Its automatic caller listing was
empty despite that instruction reference. The other two starts were verified
from their separate ret-terminated instruction sequences. All three use the
same cdecl one-argument ABI.

`regions.json` now registers these as three semantic C++ regions at their
observed entry addresses, with the original first-entry symbol retained as an
alias. Their exact compiler output and final image byte equivalence are
unverified; no build, probe, or tests were run for this recovery.
