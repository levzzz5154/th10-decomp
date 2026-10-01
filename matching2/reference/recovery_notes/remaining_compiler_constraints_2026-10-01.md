# Remaining compiler constraints: native diagnostics and player-update candidate

This follow-up adds **zero verified code bytes**. Main ownership remains at
1,868 semantic regions / 100,461 bytes and 432 assembly regions / 222,457
bytes. Five semantic regions still contain x87 assembly. The work below
narrows concrete compiler constraints and prepares a complete player-update
experiment; no failed or uncompiled candidate is promoted.

## Retained candidate inventory

A pruned audit examined 443 retained result/probe JSON files against current
main ownership. No unintegrated ordinary-production exact semantic candidate
was found in that corpus. Three otherwise matching carve probes retain naked
assembly. The complete 202-byte ArchiveCursor_Read diagnostic match already
has a separate production-probe project prepared, pending Wine availability.

ReadBitMaskFlag at `0044A160` has a complete 43-byte native match, with its
original MAP extent and retained PE hashes verified. However, the matching
source shifts by an unmasked nonnegative signed-short index. C++ leaves shifts
of 32 or more undefined, whereas the original hardware masks the count to
five bits. This remains a semantic rejection despite literal native equality.
Frozen source/context copies and inventory evidence are under
`matching2/build/experiments/retained_candidate_inventory_2026_10_01`.

## Defined flag-reader shift

Two fresh native Linux compiler experiments express
`1u << (static_cast<unsigned int>(index) & 31u)` within the complete guarded
flag reader. They preserve the output OR and conditional return. The pinned
backends assemble compiler-generated assembly unchanged; their input, tool,
framework, and artifact hashes are retained. They use no oracle bytes during
compilation and perform no emitted-code rewriting or masked comparison.

GCC emits 44 bytes and eliminates the explicit count-mask instruction,
lowering the defined expression to hardware SHL. Its standard fastcall ABI
places bit and mask on the stack and uses RET8, while the original expects
bit in SI, mask on the stack, and RET4. It also changes branches, save/restore,
and conditional selection. This proves the count-mask instruction is not
inherent to a defined C++ spelling; it does not prove the complete body exact.

Clang regcall with unused AX/DI argument slots derives CX index, EDX output,
SI bit, and mask on the stack from a source-level calling-convention attribute.
The resulting complete body is 33 bytes and uses plain RET, plus different
comparison, conditional selection, and zero-initialization instructions. Its
register placement alone is insufficient: return cleanup and all instruction
bytes must match before any integration. Both original and native full
disassemblies are retained. The independent verifier is
`matching2/build/experiments/defined_mask_gcc_2026_10_01/verify_retained.py`.

## Rotated quad: comparison ISA experiment

The earlier full assembly-free intrinsic candidate emitted 599 bytes at O1,
versus the original complete 591-byte function. A fresh baseline reproduces
all 599 bytes. Forcing `-march=i586` removes FUCOMI but yields 603 bytes;
adding `-mtune=pentium` produces an identical 603-byte body. This deliberately
tests older comparison lowering, rather than reproducing the original MSVC
`/G6` option. Only an isolated backend's flag allowlist was extended; the
generator, C++ source, headers, and compiler plugin remain unchanged.

The original FUCOMPP pops both operands and reloads the angle. GCC retains
the angle while emitting FUCOM/FNSTSW/FSTP and a different status-word test.
The stack frame, switch edges, floating-point schedule, and native callee
conventions also differ. GCC introduces a quiet-NaN initializer beside -0.5f
in a constant section whose contiguous payload has no original counterpart.
All bodies fail the complete extent gate; the ordinary relocation/literal
gate is not reached. No artificial data binding or code rewrite is used.
The measurements and exact allowlist diff are under
`matching2/build/experiments/x87_comparison_isa_2026_10_01`.
ISA selection and tuning alone cannot remove the retained x87 assembly.

## Native callback bridges

Fresh GCC source-level fastcall entries and regparm(1) dispatcher declarations
also express the complete ECX-to-EAX menu callback bridge without assembly.
At Oz, GCC uses one-byte XCHG and emits six bytes. Switching to O2 specifically
tests that size-saving substitution; both complete functions then have the
original seven-byte extent, MOV EAX,ECX followed by a tail JMP. The maintained
ordinary probe runs through the pinned native GCC backend without Wine and
checks the two real dispatcher target bindings. Both targets pass, but each
function differs at two bytes: `89 C8` versus original `8B C1` for the same MOV.
The original complete literal gate therefore rejects both callbacks. Nothing
is patched or promoted. Full provenance, raw disassemblies, and the ordinary
probe result are under
`matching2/build/experiments/private_eax_callbacks_gcc_2026_10_01`.
This replaces a vague ABI-only blocker with a measured encoding residual;
an equivalent instruction still cannot count as byte matching.

## Complete player-update closure candidate

The previous UpdatePlayer candidate was 220 bytes versus 223, with 209
reported differences. Its Draw helper was 120 versus 124 bytes and called
the collision boundary with an ordinary ECX receiver and an extra stack
position argument. The original collision convention is owner EAX, position
EBX, three stack arguments, and RET12. Four complete old anchors were exact:
timer 72, score evaluation 76, position lookup 73, and position setter 90.
All twelve old native input hashes remain intact.

The new isolated candidate adds the full 260-byte collision-loop model,
199-byte activation model, 91-byte playfield bounds model, and complete
item/animation helper models. Typed layouts assert the 0x7F0 record stride,
2000-record array at manager+0x60, and observed member offsets. The collision
predicate preserves the original unordered path with a negated ordered
comparison. The source now expresses Z displacement that cached Ghidra
omits, but its materialization remains unproven: LTCG may remove the unused
component. Native verification must inspect the full Z subtraction/store
and vector-copy sequence, operand order, and complete helper contributions.

Ten Windows i686 Clang syntax checks and offset assertions pass. The new
source/header closure has no assembly, naked functions, or byte emission.
Syntax checks do not prove MSVC instruction bytes. The full experiment,
provenance, ordinary-probe command, and repeatable preparation audit are at
`matching2/build/experiments/player_update_continuation_2026_10_01`.
Its selected region remains the original complete 223 bytes. Context and
fourteen full anchors are unselected, with no recovered-byte credit.

Wine still reports `wineserver: bind: Operation not permitted`. The fresh
native GCC/Clang experiments above remain available, while MSVC probes,
the player closure's code-generation gate, ArchiveCursor_Read's ordinary
probe, and the current whole-project rebuild await Wine availability.
Fresh Ghidra MCP calls require approval under a never-approval policy;
this follow-up uses retained analyses and original disassembly.

[The follow-up evidence](remaining_compiler_constraints_2026-10-01.evidence.json)
records every experiment evidence hash and confirms the maintained manifest
is identical to the preceding integration checkpoint.
