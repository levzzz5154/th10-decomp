# CRT ctype accessors at 0x00456911

The former ASM extent at `0x00456911` contains nine consecutive cdecl entry
points. Each takes one `int` character argument on the stack and returns its
result in EAX. The source now expresses those bodies as ordinary C++ wrappers
in `msvc/src/unidentified/unassigned_00456911.cpp`.

| Entry | Size | Behavior |
| --- | ---: | --- |
| `0x00456911` | 58 bytes | `ispunct`, mask `0x10`, 8-bit table read |
| `0x0045694B` | 63 bytes | `isalnum`, mask `0x107`, 16-bit table read |
| `0x0045698A` | 63 bytes | `isprint`, mask `0x157`, 16-bit table read |
| `0x004569C9` | 63 bytes | `isgraph`, mask `0x117`, 16-bit table read |
| `0x00456A08` | 58 bytes | `iscntrl`, mask `0x20`, 8-bit table read |
| `0x00456A42` | 13 bytes | `isascii`, unsigned comparison against `0x80` |
| `0x00456A4F` | 8 bytes | `toascii`, `c & 0x7F` |
| `0x00456A57` | 26 bytes | `iscsymf`, alpha result or underscore, returns 0/1 |
| `0x00456A71` | 26 bytes | `iscsym`, alnum result or underscore, returns 0/1 |

The locale-backed accessors use the same thread-locale path as nearby CRT
helpers: obtain thread data, update a non-default locale, and dispatch to
`asm_isctype_mt_00455752(locale, c, mask)` for `categories > 1`. Otherwise
they index the table at byte offset `c * 2`, preserving the observed byte or
word read width and returning the masked table value. The two symbol names
retained for existing aliases are `asm_unassigned_00456911` and
`asm_target_0045694b`.

The helper ABI is cdecl with three stack arguments. The retail callers push
mask, character, and locale pointer and clean 12 bytes after returning;
Ghidra's earlier automatic `thiscall` guess did not match those instructions.

Ghidra's direct call sites include `iscsymf` at `0x00456A5B` calling the alpha
entry at `0x004567AB`, and `iscsym` at `0x00456A75` calling the alnum entry at
`0x0045694B`. Its caller enumeration was empty for those callees despite the
instruction references. The other entry boundaries and cdecl stack argument
were confirmed from the separate ret-terminated instruction sequences.

`regions.json` now registers these as nine semantic C++ regions at their
observed entry addresses, with the original first-entry and second-entry
symbols retained as aliases. The shared declarations for those two aliases
are now `int __cdecl name(int c)`, matching their observed one-argument
classification ABI. Exact compiler output and final image byte equivalence are
unverified; no build, probe, or tests were run for this recovery.
