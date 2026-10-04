# StartSpell: canonical sorting determines the residual SIB order

Status: resolved by the complete exact production recovery. The controls below are historical; see `player_hud_start_spell_00409280_2026_10_04.md` for current ownership and proof.


Production remains the validated equivalent C++ model. Its 2,432-byte contribution differs from retail in exactly one byte, at 0x004093A4: retail encodes `[ecx+edx]`, while the candidate encodes `[edx+ecx]`. The registrar remains an exact 118-byte ordinary C++ recovery. No diagnostic changes described here were promoted.

Read-only hardware-breakpoint and hardware-watchpoint tracing of the pinned compiler identifies the first reversal. `LoptCombineInductionVariables` initially constructs the desired `source_cursor + copy_offset`. Later, `FactCanonSort` calls `MscMergeSort`; the sorted operands are written back at compiler PC 0x107946F4, reversing this expression. AddrModes subsequently consumes that order. This refines the earlier pre-AddrModes observation in `player_hud_spell_sib_controls_2026_10_04.md`.

`OptCmpHashVal` compares operand complexity words in descending unsigned order. Both leaves have complexity level one. Their low-order hash is derived from compiler temporary-symbol ordinals. In the best candidate, the source cursor has symbol ordinal 0x1B and complexity 0x10360, while the copy offset has ordinal 0x75C and complexity 0x1D700. The offset therefore sorts first. The inspected symbol definitions are both null; this comparison is between leaves, rather than recursively different expressions.

A natural two-field animation script descriptor preserves the same one-byte candidate but changes the offset ordinal to 0x78A (complexity 0x1E280). Extracting the existing object preparation statements into a helper leaves the ordinals unchanged. A four-field resource/script/render-bucket/flags descriptor changes the offset ordinal to 0x81E (complexity 0x10780), demonstrating the hash wrap, but still sorts the offset first and changes six earlier bytes. This is evidence for a compiler-context influence, not an exact recovery.

The diagnostic scripts and artifacts are under `matching2/build/experiments/spell_goal_2026_10_04/`:

- `trace_induction_combine.py`, `induction_combine_trace/`: initial correct operand order.
- `trace_address_order_passes.py`, `address_order_pass_trace/`: reversal precedes Half and Opeq.
- `trace_address_order_watch.py`, `address_order_watch_trace/`: first causal reversal in FactCanonSort.
- `trace_canonical_weights.py`, `canonical_sort_weights/`: original leaf weights.
- `trace_scope_weights.py`, `canonical_scope_prepare_panel_object/`, `canonical_scope_panel_animation_descriptor/`, `canonical_scope_panel_full_descriptor/`: natural configuration controls and weights.
- `panel_configuration_controls.py`, `panel_constructor_controls.py`, `panel_inline_constructor_controls.py`: isolated source variants and authoritative probe results.

Traced native links reproduce the untraced native hashes. No compiler patches, output-byte rewriting, dummy padding fields, or unused-symbol padding were used. None of these controls passed the unmasked byte gate. Constructor controls that leave calls out of line change the function address and extent and are rejected.

At this diagnostic stage, exact recovery remained pending. The mechanism is now identified, but a readable source arrangement that reproduces all original bytes is still required.

A three-field resource/script/bucket descriptor also retains the one-byte residual, with offset ordinal 0x7C6. A four-field descriptor using a boolean persistence flag retains that residual at ordinal 0x830. Boolean ternary and bit-expression spellings do not improve the byte comparison. Constructor/helper force-inlining controls change function extent and allocation and are rejected. The isolated enum controls emitted the same six-byte result as the integer-field descriptor; unused alternate enum declarations in those diagnostic inputs were not promoted.

Typed lookup controls: the initial AnimationRef-only signature fails compilation because HUD panel and marker fields use distinct existing handle types. A templated GetAnimation accepting either existing handle type, together with a PositionScriptId-typed FindChild, compiles and reproduces the baseline one-byte result, both with and without the persistence descriptor. Neither variant was promoted.

## Follow-up: hash branches and real score types

The pinned `OptHashNode` implementation uses distinct branches. For a symbol tagged 3, PCs 0x107977C2..0x107977D0 calculate `(ordinal << 6) & 0xFFFF`; the other relevant branch uses a shift of five and a folded high component. Therefore the observed offset ordinal 0x81E gives hash 0x780, still above the source cursor hash 0x360. Merely crossing the ordinal wrap is insufficient. A two-field appearance value passed alongside resource and script produces offset ordinal 0x7F0 and the unchanged one-byte candidate. Naming the returned handle leaves that ordinal unchanged. Constructing a new handle from the returned integer changes allocation throughout the function and is rejected. Natural counter value/reference spellings preserve the residual in that appearance context. Standard register storage hints also preserve the residual.

The established `score_file.hpp` types prove that the old view omitted the score manager prefix and described just one record slot. Replacing it with the full shared score types preserves the native bytes, and this source correction was promoted to the maintained equivalent model and archived exact candidate. Both builds and the independent exact executable comparison passed again. The fresh exact candidate gate still rejects the one SIB byte; no descriptor, register hint, or counter experiment was promoted.

The single-field script-index and render-layer wrappers leave the appearance-context offset ordinal unchanged at 0x7F0; their identical output is explained by this unchanged sort input. The boolean flag with an `if` statement lowers the offset ordinal to 0x7E2 (hash 0xF880), preserving the residual. The corresponding ternary emits the same six-byte result as the four-field integer descriptor. These are isolated diagnostics only.

Returning the appearance preset by value from an additional helper changes the complete contribution to 2,704 or 2,776 bytes, with stack/allocation changes, and is rejected. The preset scripts, input snapshots, and probe results remain available for review; production continues to use the simpler shared-score-type model.

## Exact source arrangement and promotion

A by-value AnimationRef equality operand combined with the appearance value
puts the final offset at ordinal 0x80E (hash 0x380), just above the source cursor
hash 0x360. The first copy's offset is then 0x805 (hash 0x140), below its cursor
hash 0x2A0, explaining the two swapped SIB bytes in that control. Direct,
unscoped panel-name cursors restore the first copy's retail encoding and leave
only the final residual. Keeping the aggregate helper's destination and source
pointer values constant while advancing separate input and output cursors then
passes the complete unmasked 2,432-byte gate. The standalone registrar remains
exact at 118 bytes. These are meaningful value/cursor operations; no symbol or
layout padding was added.

The production probe and the archived replay select and verify both functions.
StartSpell now has ordinary C++ ownership, and the previous equivalent and
assembly files are preserved in the candidate archive. Both full builds pass;
the normal executable's complete target contributions equal retail, and the
EXACT executable matches retail in full. The recovery goal is complete. See the
current spell-start note and evidence JSON for the authoritative final proof.
