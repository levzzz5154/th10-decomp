# C++ recovery checkpoint, 2026-09-28, seventh checkpoint

**Verified:** six complete routines totaling **388 bytes** are integrated with
exact maintained normal probes and passed independent source/ABI/ownership
reviews. The combined build passes **2,241 / 2,241 units**, with all **487,936 bytes**
exact to retail. The current-input audit passes **4,005 files**, **4,613 manifest
regions**, **691 native clusters** and **2,365 translation units**. Cumulative
recovery is **58 routines / 13,236 bytes** across seven checkpoints.

| Integrated entry | Bytes | Recovered operation | Detail |
| --- | ---: | --- | --- |
| 0x00408750 | 30 | Set gameplay score vector from angle and scale | [Polar recovery](gcc_home_reservation_2026-09-28.md) |
| 0x0041BEB0 | 30 | Set item vector from angle and scale | [Polar recovery](gcc_home_reservation_2026-09-28.md) |
| 0x0041F800 | 30 | Set path vector from angle and scale | [Polar recovery](gcc_home_reservation_2026-09-28.md) |
| 0x004458B0 | 30 | Set animation vector from angle and scale | [Polar recovery](gcc_home_reservation_2026-09-28.md) |
| 0x004479D0 | 127 | Validate font, convert text coordinates and choose a full drawing call | [Text recovery](marktext_dispatcher_exact_268_2026-09-28.md) |
| 0x00447A50 | 141 | Format variadic text, dispatch drawing and update dirty state | [Text recovery](marktext_dispatcher_exact_268_2026-09-28.md) |

The two text routines compile as one native-LTCG unit. The four polar setters
share one ordinary GCC/LLVM COFF source unit under the new compiler profile.
The ownerless `vector.cpp` translation unit is removed and its replacement
combined unit added; original source files, previous records, aliases and all
other owners remain intact. Unselected full contexts and dependencies add no
recovered bytes. The new text source preserves the complete original dispatcher record from shared `recovery_leaves.cpp` and original MarkText
record under `previous_record`; fifteen other shared-source owners and aliases
remain intact. All 38 new copy/native inputs and report/object hashes match the
final 268-byte normal gate. The existing 148-byte slot pair's 37 inputs are unchanged
and its co-visible models are excluded from new recovered output.

Fresh full caller/lifetime evidence establishes dispatcher resource EDI,
font height EAX, text EBX and four stack arguments, RET16. The ordinary parameter
tuple follows the actual drawing arguments consistently across all three full
callers. It preserves both signed font guards, four conversions in left/top/right/
bottom order, all six drawing arguments, and true unsigned EAX/RET24 draw-result
contracts. Callers ignore the dispatcher result; the historical intended return
type is not inferred from incidental EAX. MarkText retains font read before
formatting, actual variadic homes, 128-byte buffer, complete payloads, color after
formatting, resource/flags reloads, dirty update and cookie. No forced registers,
shortened helpers, instruction edits or comparison masks are used.

The maintained GCC route uses a general guarded RTL stack-home rule with GCC 16.2.0,
then passes its generated assembly untouched to LLVM 22.1.8 MC. All four original
polar bodies in the table produce complete 30-byte code sections with zero
relocations and body SHA-256
`ee204b7afd1b942c09db2fb55b55a65701e35832fd7d1b7a039a1b854eaeca35`.
They keep ECX receiver, two stack floats, RET8 and EDX preservation; extended
sine/cosine scaling rounds only at destination float stores. The pass selects
the upcoming private local initializer for stack reservation without changing
the explicit volatile store. It contains no target names, addresses, expected
bytes, assembly templates or oracle reads. Nine generic tests and unwind variants
verify conservative rejection guards and unchanged 50 CFI directives/272-byte
frame data. The frozen pass source is
`1c15cdad3b2785c53a8f6e7a49c5e9e480cff1975760cd33a636f8555e6da72c`.
The normal profile gate also passes all four original 30-byte sections. Explicit
pointer return models the retained EAX destination without claiming historical
caller consumption. Final backend framework review and 57 archived tests passed.
Final source, ABI and artifact/ownership review passed the three promotion files, 477 inputs, four
framework hashes, eight tool pins and 611 SDK files. The four original 30-byte
maintained normal gates and final whole-executable/current-input proof pass. The
audit verifies the reviewed framework/profile/tool/pass hashes and 22 archived
GCC artifacts. All four raw and normalized sections are exact at offset zero with
zero relocations.
[Compiler evidence](gcc_home_reservation_2026-09-28.md).

The preserved sixth checkpoint proves the earlier **52 routines / 12,848 cumulative
bytes**: all 3,964 inputs, 690 clusters, 2,365 translation units, 2,241 build units and
the complete 487,936-byte executable passed. Its executable SHA-256 is
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`,
and `.text` is
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.
The seventh combined proof independently verifies the new text/backend
integration against the same full executable and `.text` hashes. All current
source inputs and compiler framework hashes agree. Post-emission instruction changes, address
operand changes and comparison masks are zero; no retail executable bytes are
used to build. Six existing Ghidra Function heads received plate annotations,
then the program was saved and all six comments were read back successfully.
No Function heads were created. The sixth checkpoint and frozen pre-integration
handoff notes remain preserved.

Substantive terminal residuals now have stronger full-original normal evidence:

- Item allocator 0x0041BB00 reaches the complete 819-byte original gate with 736
  differences, first 0x0041BB0E. E260 now reaches all 609 bytes with four register
  differences, first 0x0041E3A9; its prior 609/33 gate is preserved separately.
  These are actual unmasked normal comparisons with no compiler/
  extent failures. Exact 623-byte F400 remains unchanged and already counted in
  checkpoint six. The allocator levers are allocation search/manager lifetimes
  and genuine polar EDX preservation with stack-kind agreement. E260's ordering
  and counter-subrecord changes reduced the earlier 33-byte residual to four
  register encodings; its remaining lever is the full inline registrar's old-tail
  ECX lifetime across the counter update.
  [Item residual](item_allocator_schedule_residual_2026-09-28.md).
- New genuine vector-operator geometry models emit 483/446/372 versus 370, with
  319/300/248 diagnostic overlap differences. All three calibrated original 370
  gates reject extents. The 372-byte typed-copy result is identical to historical
  scalar-distance attempt10; the earlier 368/370 model remains preserved. The next
  evidence must distinguish true assignment/return/distance boundaries producing
  retail asymmetric x87 rounding, via a full adjacent routine or genuine caller.
  No new geometry match is claimed.
  [Operator evidence](effect_record_operators_004084a0_2026-09-28.md).
- Latest full text-context executor 1500/1568, indicator 1343/1317 and music 2764/2796
  have 1257/1198/2590 raw overlap differences. They remain unselected diagnostics,
  with full semantics and original extents preserved. Exact text callees now give
  grounded context for interpreter state/register and by-value handle-local
  recovery; genuine 571-byte indicator and 4,480-byte text callers remain leads.
  [Context evidence](marktext_dispatcher_exact_268_2026-09-28.md).

The focused E260 counter-subrecord gate is terminal at 609/609 with four differing
ECX-versus-EDX encodings at 0x0041E3A9/0x0041E3AE/0x0041E3B0/0x0041E3B4. A plain
counter pointer with reordered count/script work and the genuine +0x90934
subrecord Advance() produce the same complete body. The next lever is the full
inline registrar's old-tail ECX lifetime across the counter update. The prior
609/33 source/normal snapshot remains preserved; no E260 bytes are promoted.
[Current counter evidence](item_e260_counter_context_residual_2026-09-28.md).

The final raw ledger counts **1,665 semantic regions / 83,569 bytes** and
**1,113 assembly regions / 305,529 bytes**. The selected-source audit counts
**1,659 fully C++ semantic regions / 79,044 bytes** and **1,119 regions containing
assembly / 310,054 bytes**. The difference is six partial semantic bodies,
totaling 4,525 bytes, which retain FRNDINT, FSINCOS and callback register assembly.
Complete GCC polar proofs do not establish the 17-byte FRNDINT helper's binary64 stack frame or recover the larger render bodies. Prior
checkpoints and all earlier residuals remain preserved. The full readable,
byte-matching, assembly-free C++ goal remains active.

Artifacts under `matching2/build/experiments/`:

- `native_recoveries_2026-09-28_seventh_reviews.json`
- `native_recoveries_2026-09-28_seventh_next_leads.json` and `.md`
- `marktext_dispatcher_2026_09_28/final/probe_final02.json`, `promotion_delta.json`
  and `handoff_verification.json`
- `gcc_home_reservation_2026_09_28/promotion_four/probe01.json` and `handoff.json`,
  plus `whole_polar_probe.json` and `generic_rule_probe.json`
- `native_recoveries_2026-09-28_seventh_port_report.json`,
  `native_recoveries_2026-09-28_seventh_verified.json` and
  `native_recoveries_2026-09-28_seventh_integration.json`: final combined build and
  current-input audit
- `native_recoveries_2026-09-28_seventh_ghidra_verified.json`: six existing
  Function annotations saved and read back
- `native_recoveries_2026-09-28_seventh_gcc_artifacts/` and
  `native_recoveries_2026-09-28_seventh_backend_tests.log`: frozen compiler evidence
  and 57 passed framework tests
