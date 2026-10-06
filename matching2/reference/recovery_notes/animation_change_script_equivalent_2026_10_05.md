# Animation script-change C++ equivalence recovery, 2026-10-05

The complete 287-byte routine at `0x0043E8B0` is now covered by
`layout/equivalent/animation_change_script_0043e8b0.json`. The default build
uses the ordinary C++ model in `equivalent/render/`; the exact build retains
the original assembly. The existing exact handle wrapper and lookup retain
their ownership. Their source is included in this compiler context to derive
the changer's private entry: resource EDX, object EAX, index ECX, plain RET.
The existing `RunChangeScriptVm` call binds to `0x0043EE30`.

The model uses ordinary scalar/float source without a volatile scale read.
The 2026-10-06 refinement uses the known -1.0f literal instead of reading its
global alias. The full comparison reports 66 instructions, 51 identical,
and nine explicitly recorded register-choice hunks, with 22 differing bytes
instead of the preceding 32. There are no frame-offset,
base/index, or unproven branch-target allowances.

All nine hunks are one consistent ESI/EDI allocation change:

| Value and lifetime | Retail | C++ |
| --- | --- | --- |
| incoming index, through the 16-bit ScriptIndex store | EDI/DI | ESI/SI |
| script pointer, from lookup through both +0x38C/+0x390 stores | ESI | EDI |
| flags after the index dies | EDI | ESI |
| previous-frame reset constant after the flags die | EDI | ESI |

The null-script compare follows the script-pointer register, the flag test
and mutations follow the flags register, and all consumers follow the same
mapping. Both callee-saved registers are saved before their first overwrite
and restored on every exit. The C++ moves its index copy and table-pointer
load before the second push; neither operation uses ESP or changes the
original EDI being saved. The read order, resource/loading check, and object
stores otherwise agree. The flags word and script pointer have distinct live
ranges/registers in both bodies, with no value lost across a use or call.

The literal now emits retail's exact `fld object.scale_x` followed by
`fmul [0x00470B60]`, including its position around the intervening flag
operations. The pooled compiler literal `__real@bf800000` binds to that
existing float address. Its value is -1.0f; this remains an x87 multiply,
rather than a sign-change instruction. The former operand-order allowance
has been removed. The two smaller hunks at `+0x42` and `+0x4B` cover only
the register operands in the OR and XOR/store instructions.

The full gate follows every branch, checks the entry and return instructions,
verifies all other instructions and addresses, and rejects any difference
outside these exact nine hunks. No compiler flag, verifier rule, assembly
instruction, or region extent was changed to admit the candidate.

The exact handle caller's compiler context uses the same ordinary literal
source, replacing its old volatile read. Its layout positions and verifies
the compiler's actual four-byte constant at `0x00470B60`; the added `.rdata`
gap remains unselected layout data. The caller's complete 36 bytes and the
lookup anchor's 73 bytes remain exact. The changer remains equivalent,
with exact-build ownership still in its original assembly region.

Sources, six logical-parameter-order controls, native PE/MAP files and
strict maintained probe/equivalence reports are preserved under
`build/experiments/script_change_exact_2026_10_06/`. Parameter permutations
did not change the ESI/EDI mismatch; the prior candidate-priority trace still
describes that unresolved allocation.
