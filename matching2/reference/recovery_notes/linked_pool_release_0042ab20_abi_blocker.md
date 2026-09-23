# 0x0042AB20 — linked pool release remains assembly

2026-09-23. Keep `matching2/msvc/src/game/linked_pool_release.cpp` as the
naked assembly body. The canonical Ghidra name is `FUN_0042ab20`; the current
source identifier is `asm_FUN_0042ab20_0042ab20`, with raw linker symbol
`_asm_FUN_0042ab20_0042ab20`.

## Boundary

Live Ghidra inspection of project `th10`, program `th10.exe`, identifies
`FUN_0042ab20` at `0x0042AB20` with body `0x0042AB20..0x0042AB7C` inclusive
(93 bytes). The final instruction is the one-byte `RET` at `0x0042AB7C`.
The next three bytes, `0x0042AB7D..0x0042AB7F`, are `INT3` padding; Ghidra
reports no function at `0x0042AB7D`. The live manifest agrees: a 93-byte
`asm` region starts at `0x0042AB20`, followed by a three-byte padding region.

## Callers and ABI

Ghidra reports exactly three direct callers and call xrefs:

- `FUN_00428f60` at `0x00428F7D` loads the selector from
  `DAT_00474c7c` into EAX, loads its owner from EBX into ECX, and calls the
  helper. It pushes no argument and resumes without stack cleanup.
- `FUN_004294a0` at `0x004294D6` copies its loop counter (0 through 7) from
  ESI to EAX, loads its owner from EDI into ECX, and calls the helper. It
  pushes no argument and increments the selector after return.
- `FUN_0042a450` at `0x0042A48F` loads the selector from
  `DAT_00474c7c` into EAX, loads its owner from EBX into ECX, and calls the
  helper. It pushes no argument and resumes without stack cleanup.

The decompiler renders the entry as `void __fastcall FUN_0042ab20(int
param_1)` but exposes the selector separately as `int in_EAX`; it does not
recover it as a formal parameter. This is not the ordinary x86 C++ fastcall
contract for two arguments, which would put the second argument in EDX. A
thiscall or cdecl/stdcall source function with an explicit selector would
expect a stack argument and corresponding cleanup. Retail instead consumes
the owner in ECX and selector in EAX, with a plain `RET`. The naked assembly
alias is therefore needed to preserve the live call contract unless a future
caller/LTCG integration changes how the function is placed.

## Behavior and cleanup

The entry scales incoming EAX by 12 and reads a list pointer from
`owner + 0x40 + selector * 12`. In each iteration it saves `[node + 4]` as
the next link before loading the payload from `[node]`. For each non-null
payload, it reads the next link at payload offset `0x627C` and the previous
link at `0x6280`. When present, it patches the next neighbor's `+8` field to
the previous link and the previous neighbor's `+4` field to the next link,
zeros both payload link fields, then calls `_free` at `0x004524A1`. The saved
next pointer is used to continue after freeing the payload.

The function has no return value contract: it restores ESI and EDI and ends
with a plain `RET`; the callers do not consume EAX. The only direct callee is
`_free`. Its payload argument is pushed by this function and reclaimed with
`ADD ESP, 4` after the call. Retail does not write zero back to the selected
owner head slot.

That last detail differs from the older sketch in
`matching2/reference/legacy_semantic/src/game/linked_pool_release.cpp`, which
stores zero to `*head_slot` after traversal. The sketch is not an exact
replacement for this body even apart from its ordinary-ABI mismatch.

## Decision

Keep the current 93-byte assembly region. Its pool selector is a private
incoming-EAX value established at all three live call sites, and a normal
C++ definition cannot express that input register while retaining the current
call sites and plain-return cleanup. No source, manifest, shared declaration,
caller, or layout was changed. No build, probe, or test was run for this
audit.
