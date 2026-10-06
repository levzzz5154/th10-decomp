# Script-change ordinary-type controls, 2026-10-04

The 2026-10-06 refinement in
`animation_change_script_equivalent_2026_10_05.md` uses the known -1.0f
literal. It removes the operand-order mismatch without a volatile read,
leaving 22 differing bytes and the unresolved ESI/EDI allocation. The
global-scalar and type-wrapper results below remain historical evidence.

The complete 287-byte script changer at `0x0043E8B0` remains assembly. Eight fresh isolated controls were compiled against the current production project and measured directly from their native PE/MAP contributions. No candidate passed; production source, headers, manifest and ownership were unchanged.

The previous anchor uses a volatile scale read to force `fld object.scale_x; fmul global_factor`. Removing that volatile read, for either multiplication operand order, produces `fld global_factor; fmul object.scale_x`. The multiplier at `0x00470B60` is exactly -1.0f. The ordinary candidate has 32 differing bytes rather than the old volatile anchor's 22, but retains the 287-byte extent and its already-exact 36-byte handle caller.

Scalar flags, copied flag value type, constructed flag value type, a script pointer record, and reference-returning flag operators all generate the same complete 287 native bytes (SHA-256 `0e907e894b372c616dc6446b241e19d090e89ff9059440392251409fcc7e736e`). Thus the copy-type technique that solved the object initializer does not alter this function's allocation; repeating these flag/pointer spellings is ruled out.

An inlined boolean `Has` predicate instead introduces a shift/test sequence, changes the resource/index entry registers and shrinks the body to 279 bytes. A mutable flag-word reference also emits 279 bytes. A by-value script-index record emits 291 bytes and changes the entry convention. These are extent/ABI failures, not near-exact replacements.

All sources, header control, compiler logs, native executables and normal-probe reports are preserved under `matching2/build/experiments/script_change_2026_10_04/`. `measurements.json` records actual native extents, hashes and differing overlapping bytes; no address or instruction bytes are rewritten. The disposable project is restored to the coherent ordinary scalar baseline.

Next useful work on this target must address the script-versus-flags live-range priority (already explained by the prior c2 trace) and natural x87 operand ordering together. These measured type wrappers alone do neither. Other remaining production functions can be advanced independently; this is not an external blocker on the ongoing decompilation goal.
