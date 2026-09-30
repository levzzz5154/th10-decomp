# 0041E260 counter context: full609, four-byte residual

The focused ordinary-C++ experiment is terminal and **not exact**. The original
609-byte E260 normal gate reached byte comparison with `failures: []`, emitted
609 bytes, and found four differing bytes. No new routine is promoted. The
previous allocator/E260 experiment and maintained inputs were preserved.

The canonical new scratch is
`matching2/build/experiments/item_allocator_schedule_2026_09_28/e260_counter_context_2026_09_28`.
Its `terminal_summary.json`, `terminal_input_hashes.json`, and `terminal_inputs/`
freeze the final result and all 14 native build inputs. The authoritative normal
report is `probe02.json`; its full native report is
`probe02/clusters/item_e260_counter_context_2026_09_28/report.json`.
`probe02_measurement.json` and `probe02_complete/` retain read-only comparisons of
every complete allocator and sweep contribution.

| Complete original | Emitted extent | Differing bytes | First difference | Status in this scratch |
| --- | ---: | ---: | --- | --- |
| E260 all-segment sweep | 609 / 609 | 4 | 0041E3A9 | Normal selected gate: NOT EXACT |
| BB00 allocator | 819 / 819 | 736 | 0041BB0E | Entire unselected contribution diagnostic |
| F400 bounded sweep | 623 / 623 | 0 | none | Entire unselected contribution diagnostic; earlier independent normal exact gate preserved |

The selected E260 normal gate has zero instruction-byte changes, zero
address-operand changes, zero masked bytes, and
`reference_bytes_used_for_build: false`. The only selected root is the original
public-ECX E260 method with one stack flag, RET4, and integer count in EAX. The
unselected dependencies retain their full emitted extents: configure204,
loader203, registrar114, positioned-create111, allocate165, line-polar30,
allocator819, and bounded-sweep623. No shortened register helper was introduced.

Two grounded representations were measured. `probe01.json` moves the real
visit-count increment before script/resource expressions and introduces a plain
pointer to the existing counter after publishing the new tail. This recovers
the remaining count/script and tail-store/counter-load scheduling differences
from the earlier 33-byte residual. `candidate04_plain_counter_source.cpp`
preserves that full source.

`probe02.json` replaces that counter expression with a complete force-inline
`Advance()` operation in a relative counter-region view. The view starts at
manager +6A1B20, so its +90934 integer is exactly the already-established
manager +732454 counter. An `offsetof` check verifies the relative layout. This
is a faithful field view; fresh evidence does not establish it as the original
class or subobject boundary. `candidate05_subrecord_source.cpp` preserves this
full source. It emits exactly the same complete E260 bytes as probe01.

Both forms preserve the primary-list links, new-tail publication,
zero-skipping counter increment, tested-copy correction, final counter memory
reload, animation load/configuration/position writes, optional item spawn,
vector advancement including the actual floating zero addition, retirement,
and returned visit count. No output-slot write was invented for E260.

The four differences are at **0041E3A9, 0041E3AE, 0041E3B0, and 0041E3B4**.
Retail loads/increments/stores the counter in ECX and copies it to EAX for the
zero test; native uses EDX for that counter with the same instruction order and
same EAX test/correction/reload. Everything else in the original609 bytes
matches. This is still a failed whole-routine gate; it supplies no partial
coverage or maintained recovery claim.

Final E260 body SHA-256:
`3e2329f7941f10e0a05c6b4455004ca9ab90242f12e522752f16c4305bbdd502`.
Retail E260 body SHA-256:
`0f407d65898d373dc40df48afc5f748b24a84dc543e9d14df6bd21cbaec02745`.
Final selected source SHA-256:
`78e4fc1498b94f250564dc32a8b95e0868e36f5f41dc20eca1df4b2b12b0133e`.
Retained F400 body SHA-256:
`f064ada0633637ffbd6631367e900d6d1415569100052bf52bae824735db874f`.
Retained allocator body SHA-256:
`6393e9877e1387e611de9fd74e1e64491346bc64f4bc5c9cb8b52a08faee4d59`.

Fresh live Ghidra disassembly from th10.exe on socket2136235 is retained in
`fresh_e260_disassembly.json`. The separate read-only analysis is
`anchor_read/counter_subrecord_analysis.md`. Retail consumes the old tail in
ECX through 0041E39F, publishes EAX as the new tail at 0041E3A2, and then reuses
ECX for the counter at 0041E3A8. The next concrete lever is the genuine full
inline-registrar source context and those tail/counter value lifetimes. Merely
changing to the relative +90934 view did not change register allocation. Any
future attempt must keep the recovered script/count schedule, final counter
reload, complete effects, and original609 normal gate. A future exact handoff
must use a unique E260 cluster, context, and header closure so that the existing
F400 maintained closure is preserved.

The older parent `terminal_summary.json`, `terminal_input_hashes.json`, and
`combined02.json` hashes were rechecked against `preserved_parent_state.json`
and remain unchanged. This scratch has no promotion proposal and makes no
maintained-input changes.
