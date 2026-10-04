# Spell-card copy SIB order: compiler-stage evidence

Status: resolved by the complete exact production recovery. The controls below are historical; see `player_hud_start_spell_00409280_2026_10_04.md` for current ownership and proof.


The byte-exact goal remains active. The normal build's equivalent recovery is
unchanged: 2,432 bytes, one encoding difference at 0x004093A4. The following
controls were isolated in disposable projects; none passed the unmasked gate.

Seven argument-renaming controls, three dependency-order controls and three
input-pointer type controls produce the identical full-function SHA-256:
`45b893df56dd4c986a803c5d67eb2502ccd00fadfd3ecc6dc5b0d3b27dd6a779`.
The naming and link order hypotheses can be set aside. Packing records to one
or two bytes also preserves the residual; stronger alignment changes layout
constants or allocation and is unsuitable.

Typed byte assignment returning by value and a typed destination iterator
preserve the one-byte residual. Reference-returning byte assignment creates an
extra LEA/store pattern; source or combined typed iterators alter allocation.
Backward-displacement forms alter hundreds of bytes. Helper-level alias and
size optimization controls preserve the residual; disabling global optimization
changes the contribution and addresses. No experimental variant was promoted.

## Observed pass boundary

Read-only hardware-breakpoint traces of the pinned C2 compiler confirm that the
wrong order is already present before Riscify. All three traced native links
produce the same complete StartSpell hash as the ordinary untraced link.
The trace scripts and native PE/MAP files are preserved under
`matching2/build/experiments/spell_goal_2026_10_04/`.

The final copy has this symbolic sequence before AddrModes:

```
source_cursor = name
record_name = score_file + aggregate_record_offset
copy_offset = record_name - name
loop:
    byte = *source_cursor
    store_address = copy_offset + source_cursor
    *store_address = byte
    ++source_cursor
    test byte and branch
```

The symbolic add is opcode 0x278. AddrModes folds it into the indirect store
(opcode 0x263) using an address-mode operand 0x253 with `copy_offset` as base
and `source_cursor` as index. After register allocation these become EDX and
ECX. The pre-Riscify and post-Riscify store both have base EDX / index ECX.
The encoder therefore follows an address order chosen earlier, rather than
introducing the swap while encoding the store.

The early named trace is
`early_address_mode_names/trace.txt`; the physical register trace is
`address_mode_trace/trace.txt`. Initial raw early traces had incomplete symbol
name decoding, corrected in `trace_early_names.py`. Non-instruction metadata
operands are not fully decoded; the relevant load/add/store nodes and their
base/index operands are identified in the corrected trace.

The next useful investigation is the earlier loop-reduction pass that constructs
`copy_offset + source_cursor`. More parameter spelling or dependency-order
controls are not supported by the current evidence. This finding does not prove
that an exact ordinary C++ spelling is impossible.

Detailed control results and trace hashes are in
`player_hud_spell_sib_controls_2026_10_04_evidence.json`.
