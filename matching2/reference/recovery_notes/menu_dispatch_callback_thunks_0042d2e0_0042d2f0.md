# Menu dispatch callback thunk audit: `0x0042D2E0` and `0x0042D2F0`

Status: both manifest regions remain assembly. A fresh pinned GCC ordinary
probe now compiles both complete seven-byte adapters using a fastcall ECX
entry and a regparm(1) EAX dispatcher declaration. Both target relocations
pass; each body has exactly two differing instruction bytes: the assembler
emits `89 C8` for MOV EAX,ECX while retail uses `8B C1`. The ABI bridge itself
is now expressible without assembly, but equivalent MOV encodings do not
satisfy literal byte matching. No source, alias, or ownership was promoted.
The probe is under
`matching2/build/experiments/private_eax_callbacks_gcc_2026_10_01` and is
documented in [the compiler follow-up](remaining_compiler_constraints_2026-10-01.md).
The historical Ghidra/MSVC audit below establishes the original boundaries,
registration references, and private register contract; its ABI limitation
is superseded by this diagnostic, not by an exact integration.

## Ghidra evidence

`get_function_by_address`, `decompile_function`, and
`disassemble_function` report no function object at either thunk entry. The
byte-level `read_memory` and `disassemble_bytes` tools work at both addresses
and show the complete entries and their following padding:

```text
0x0042D2E0..0x0042D2E6  8B C1 E9 09 FB FF FF  MOV EAX,ECX; JMP 0x0042CDF0
0x0042D2E7..0x0042D2EF  CC CC CC CC CC CC CC CC CC  INT3 padding
0x0042D2F0..0x0042D2F6  8B C1 E9 69 FF FF FF  MOV EAX,ECX; JMP 0x0042D260
0x0042D2F7..0x0042D2FF  CC CC CC CC CC CC CC CC CC  INT3 padding
```

The current manifest independently assigns each thunk exactly seven bytes,
followed by a nine-byte padding region. Ghidra reports incoming address
references from `FUN_0042CAA0` at `0x0042CAA2` and `0x0042CACA`; its
decompilation shows these addresses supplied to `FUN_00449ED0` as callback
arguments.

The first destination, `FUN_0042CDF0`, begins by saving `EBX` and copying
`EAX` into `EBX`, then reads the receiver field at `[EBX+0x1C]`. Ghidra's
current prototype labels this function `__fastcall`, but its instructions
prove that the receiver actually arrives in `EAX`; that decompiler prototype
does not describe the machine-level entry ABI. The second destination at
`0x0042D260` begins `PUSH EDI; MOV EDI,EAX` and dispatches on the same
`[EDI+0x1C]` field. Both thunks therefore adapt an ECX callback receiver to
the private EAX receiver expected by their tail-jump targets.

## Promotion decision

The thunk operation is clear, but the higher-level callback type and private
EAX target contract are not represented by ordinary x86 C++ calling
conventions. Replacing either body with an ordinary function call would
change the tail-jump/register behavior, and the bodies contain no additional
state transition that could be recovered independently. Keep both as
assembly until the callback registration/invocation and the corresponding
dispatcher entry can be represented as a verified coupled cluster.

`0x0042BE10` is not part of this helper cluster: its source calls
`0x0042BE20` and operates through an ESI-held object, while these thunks are
registered by `FUN_0042CAA0` and tail-jump to the menu dispatchers above.
