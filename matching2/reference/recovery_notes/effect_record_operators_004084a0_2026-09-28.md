# 004084A0: complete vector-operator models and measured copy topology

The maintained 370-byte record sweep remains assembly. Three complete readable C++ models were compiled in the isolated project `matching2/build/experiments/effect_record_operators_2026_09_28/`; none passed the normal production gate, and none was promoted. The selected extent remained the original 370 bytes in every probe. The third model was one focused structural experiment, not a source-spelling sweep.

Fresh Ghidra MCP evidence retains all 370 bytes and 126 instructions in `004084A0_disassemble_bytes.json` and `004084A0_listing.txt`. `fresh_raw_comparison.json` confirms that the complete bounded Ghidra bytes equal the oracle body. Its SHA-256 is `5aa3899c37e8865763cde5c7cb04970e5c3d2dea1445d1d4879ee4a0aa04e39c`; the full oracle executable SHA-256 is `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. Missing Ghidra Function objects and incoming-reference results are retained; no function head or prototype was invented.

## Complete native results

| Model | Complete native contribution | Literal differences in the 370-byte overlap | Normal calibrated probe |
|---|---:|---:|---|
| 01: full Vec3 returned-value arithmetic, initialized Z, legal ordinary corner copies, Vec2 difference/length | 483 B | 319 | Rejected: contribution is not the declared 370 B |
| 02: direct diagonal corner constructors, initialized Z, legal ordinary corner copies, Vec2 difference/length | 446 B | 300 | Rejected: contribution is not the declared 370 B |
| 03: model 02 with an explicit typed component copy constructor | 372 B | 248 | Rejected: contribution is not the declared 370 B |

The first probe of each model reported `native cluster image base or entry address differs`: changing the routine's compiler contribution moved the synthetic context entry. Calibration changed only the context address and the following layout-gap address to the actual map positions. It did not change source behavior, the selected 370-byte routine extent, or its address. The calibrated gates then reached the substantive whole-contribution check and rejected every model. Initial and calibrated builds have identical complete routine hashes for each model.

`measure_full_contributions.py` reads the entire named `.text$01sweep` compiler contribution from its mapped public symbol through the final `RET 4`, writes complete body/disassembly artifacts, and compares the overlap only as a diagnostic. It neither changes the selection nor trims, rewrites, or masks bytes. `measured_full_contributions.json` records map/image/probe/body hashes, actual extents, gate errors, and `full_extent_exact: false`. Its SHA-256 is `08cd17050c32fad60505426651725bfb421864fe5fe18fdb71d0fa10c597faf5`.

Complete body hashes:

- Model 01: `2692eea76c03c90d87076656460f6205c5450ddf66a86928547a6e78a3d19409`.
- Model 02: `4b257b5b64c2352d57cb423c2b21c890e3b2ebef1e1bbc97b2036920c089dc73`.
- Model 03: `1acdd943190854650ee7a5dda89d44b2fb6790f76c273b0469d4fde10eb72695`.

Source/header snapshots are `model01_full_vector_operators.cpp`, `model01_header.hpp`, `model02_direct_corner_constructors.cpp`, `model02_header.hpp`, `model03_component_copy_constructors.cpp`, and `model03_component_copy_header.hpp`. Model 03 adds only `SweepVector_004084a0(const SweepVector_004084a0& other) : x(other.x), y(other.y), z(other.z) {}` to model 02's header. The source and selected layout extents are unchanged. `source_and_evidence_sha256.json` records the preserved snapshots, current isolated compile inputs, calibrated layout, and evidence hashes.

Independent read-only review (`component_copy_review.json`) confirms initialized Z, valid local copies, unchanged geometry and entry signature, and complete-section extraction. The user-defined constructor makes the vector nontrivially copyable and can change compiler treatment of unused returned-value operators; this model introduces no external by-value vector boundary. Typed float copies can also change generated rounding and NaN/exception behavior, so legality does not substitute for the rejected byte gate.

## What the structural model establishes

Model 02 preserves a 0x30-byte local frame but emits zero-Z stores and integer aggregate copies for the four corner objects. These copies prevent the compiler from tracking the common X component and retaining useful floating-point values. Its first 41 bytes match literally, with the first difference a length-dependent branch displacement; the first substantive geometry difference is the zero-Z store at native `004084D9`, where retail multiplies the width.

The explicit typed copy constructor in model 03 removes those dead zero-Z stores and integer corner-copy sequences, reducing the contribution by 74 bytes. The original entry ABI and loop setup remain intact. The complete resulting 372-byte body is **identical** to the earlier inline scalar-distance-helper `attempt10` in `record_sweep_004084a0_2026_09_27/measured_variants.json`. Legal typed value copies therefore converge on an already measured compiler shape; this is not a new byte-matching solution.

The remaining problem includes real x87 precision and lifetime differences. At retail `004084F2`, `FST [ESP+18]` rounds left-top Y for the first corner test while retaining its extended value. That live value plus full height produces left-bottom Y at `[ESP+24]`. Model 03 instead emits `FSTP`, then reloads rounded Y before the addition. Retail also writes right-bottom Y to both `[ESP+0C]` and `[ESP+30]`, then mutates `[ESP+0C]` by subtracting full height. Model 03 retains only one original store and later places the mutated value at `[ESP+30]`.

Retail rounds the first Y difference through `[ESP+3C]` and retains the shared left-X square on the x87 stack for the first two short-circuit tests. Model 03 retains the shared X difference and recomputes its square, keeping the first Y difference live. The eventual classification/iteration tail is the same instruction structure after accounting for the two-byte geometry shift, but the whole body is not exact. Equal mathematical expressions and a small extent difference do not establish retail floating-point behavior.

The retail corner slots and 0x30-byte frame are consistent with four 12-byte vector objects at `[ESP+08]`, `+14`, `+20`, and `+2C`. This supports, but does not prove, Vec3 source topology with dead Z components. Adjacent maintained `src/game/entity_region_sweep.cpp` at `00408210` is still a 585-byte assembly body. Its owner-bound construction separately materializes and copies full three-component temporary values. It supplies topology evidence, not an exact semantic implementation to reuse.

Exact maintained constructor-return examples are `src/unidentified/unassigned_00404e70.cpp` (31 B), `unassigned_00405240.cpp` (25 B), and `unassigned_00405260.cpp` (25 B), compiled by `layout/ltcg/vector_private_abi_a.json`. The sixth checkpoint's `native_recoveries_2026-09-28_sixth_port_report.json` records their complete native contributions with zero masks and zero instruction/address rewriting. Their constructor-return source controls the z/y/x evaluation and x/y/z stores. The subtraction bytes compute EDX minus ECX; its layout's descriptive left/right register labels should not be interpreted as the source operands' actual order.

## ABI and next lever

`004084A0` receives owner ECX, point EDI, and radius at `[ESP+4]`, returns the accumulated integer EAX via ESI, and ends in `RET 4`. It scans 2,000 records of stride 0x7F0, skipping states 0 and 3. The field mapping, NaN-sensitive comparison choices, corner order, and separate 8/16/32/64 classification tests are retained from the prior complete bounded evidence. This routine contains no calls; newly introduced external vector/distance helper calls would change its actual body.

Adjacent `00408210` receives owner EBX and a stack flag, returns zero, and ends in `RET 4`. Its complete dependencies remain `0041BB00` (819 B, manager EAX, position ECX, four stack values, `RET 16`), `00448DB0` (118 B, position EDI, three stack values, result EAX, `RET 12`), and exact semantic `004491C0` (73 B, context EDX, ID stack, unused receiver, result EAX, `RET 4`). None is claimed recovered by this investigation.

The next useful evidence must distinguish the original **assignment/return and distance-operation boundaries** that create retail's asymmetric rounding: a stored left-top Y reused at extended precision for one corner, an independently rounded right-bottom copy, a rounded first Y difference, and retained shared X square. Additional generic constructors, legal component-copy spellings, arbitrary ABI changes, or helper-type renaming repeat solved or rejected shapes. A genuine caller or full adjacent routine representation that exposes those boundaries is a concrete next direction; any new candidate must still pass the complete original 370-byte gate. Maintained assembly and full-image recovery counts are unchanged.
