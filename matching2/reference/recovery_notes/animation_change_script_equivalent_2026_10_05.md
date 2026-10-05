# Animation script-change C++ equivalence recovery, 2026-10-05

The complete 287-byte routine at `0x0043E8B0` is now covered by
`layout/equivalent/animation_change_script_0043e8b0.json`. The default build
uses the ordinary C++ model in `equivalent/render/`; the exact build retains
the original assembly. The existing exact handle wrapper and lookup retain
their ownership. Their source is included in this compiler context to derive
the changer's private entry: resource EDX, object EAX, index ECX, plain RET.
The existing `RunChangeScriptVm` call binds to `0x0043EE30`.

The model is the ordinary scalar/float source from
`script_change_ordinary_type_controls_2026_10_04.md`, without its experimental
volatile scale read. The full comparison reports 66 instructions, 49
identical, and eight explicitly recorded hunks. There are no frame-offset,
base/index, or unproven branch-target allowances.

Seven hunks are one consistent ESI/EDI allocation change:

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

The hunk at `+0x3F` combines that register mapping with reversed multiplication
operands: retail loads `object.scale_x` then multiplies by the float at
`0x00470B60`; C++ loads that global then multiplies by `object.scale_x`.
The global is the finite exact constant -1.0f. There is no intervening memory
write or call between these reads. Both perform one x87 multiplication with
the same operands and one identical store, preserving rounding, signed zero,
and finite/infinite results. There is only one potentially NaN operand, so
this is not a swap between competing NaN payloads. As with native floating
instruction scheduling, equivalence here concerns ordinary execution rather
than exception-handler/debugger snapshots between operations.

The full gate follows every branch, checks the entry and return instructions,
verifies all other instructions and addresses, and rejects any difference
outside these exact eight hunks. No compiler flag, verifier rule, assembly
instruction, or region extent was changed to admit the candidate.
