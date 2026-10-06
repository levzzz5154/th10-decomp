# Rectangular laser splitter 0041EB00: complete candidate, not promoted

This follow-up recovered the complete rectangular splitter as ordinary C++, using the circular cutter's genuine typed supporting graph and a fresh read-only Ghidra decompilation. The required and compiled extents are both **1,171 bytes**. The best maintained candidate has **four instruction difference groups / 27 differing bytes**, passes 199 bounded execution comparisons, and passes the unchanged native verifier's structural checks. Full raw equality fails; production remains assembly and this candidate adds zero recovery bytes. The full decompilation objective remains active.

## Sources and behavior

The maintained graph is `matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/`. Its ten C++ modules, local typed headers and source/layout snapshots contain no inline assembly or naked function. All supporting routines are complete actual bodies; there are no register bridges, synthetic callers, forced registers, dummy helpers or shortened contributions. `receipt.json` records the current source hashes, compilation and gate results. The Ghidra instance was revalidated as project `th10`, program `th10.exe`, PID 4123453; its decompilation is saved in `evidence/ghidra_41eb00.c`.

The routine keeps the original XYZ origin, clears a 256-byte stack mask, starts at six units, and samples every twelve units while `progress + 6 < length`. Sampling requires `12 < length`. The step's Z is explicitly zeroed before the public XY-only SetPolar call, and the initial sample Z is reset to zero. Later additions operate on all three components. A volatile float progress value preserves the observed x87 rounding and spill behavior.

The rectangle's half-size is computed in all three dimensions. Its lower corner is center minus half-size. The same half-size value is then reused as the upper corner by assigning `high = high + center`; this real value lifetime proved essential to recovering the stack locations. Selection tests X and Y inclusively, accepting unordered comparisons with the original negated rejection form. Z does not participate in selection. Negative sizes retain the executable's behavior rather than being normalized.

Each selected sample is marked in the mask. If items are requested and the actual public `IsPartiallyOutside(32,32)` member returns zero, a kind-8 item is spawned before the segment animation. The point pointer is reused across the viewport call and item spawn. The full resource `CreateOffset` member receives animation index `2 * script + 17` and the sample position. It allocates, sets the 40000000 flag and bucket zero, applies X +224 / Y +16, starts the script and registers the animation at the primary tail through the typed animation-ID return ABI.

The existing laser retains its first uncut run, or receives zero length if a cut prefix exists. Each subsequent uncut run uses the full native 41C510 spawner and a freshly zeroed 476-byte parameter record. Both length fields receive twelve times the run length; speed is 8. Position is the saved origin plus the full step times the run's start index, and remaining distance subtracts twelve times that index. Angle, width, type and script come from the original laser. The spawn selector is zero. This is not a clone operation.

## Compilation and verification

The initial complete candidate compiled to the correct extent but differed in 59 groups / 320 bytes. Mask-before-hit ordering and a first-run counter scoped inside the `else` block reduced this to 57 groups / 271 bytes. Reusing the point pointer for the viewport check and item call reduced it to 160 bytes. Assigning width before type reduced it to 119 bytes. Reusing the half-size value as the upper corner resolved the vector stack locations and left four groups / 27 bytes.

The final source was rebuilt from its maintained path. Its complete diagnostic body equals the chosen experimental snapshot and the fixed-address native body, SHA-256 `7889b1ce3e1bb3343022b0c483da5dcbf2370ae7a603613a68aa3409a66071fc`. Retail SHA-256 is `62a165c154f1b9f2ec3bdd366c1c2374722baa27e74c6922e37e962cfcf7d059`. An independent comparison of all 1,171 fixed-address native bytes confirms 27 differences. The normal production verifier was unchanged and used only in an isolated project with the complete actual 4187C0 StageUpdate wrapper as its unselected entry. Neither its structural acceptance nor the matching extent is a byte equality claim.

The native report records zero instruction changes, masks or reference bytes used for building. All reported input and compiler-include hashes were verified against current files. The complete public bounds member (91 bytes), base constructor (98), script loader (203), and registrar (118) match their original bytes in this graph. These were already recovered in production. Other unselected supporting routines differ and receive no new credit.

The remaining four groups concern two small regions: security-cookie/prologue instruction scheduling, and the post-sampling hit-count test relative to the zero initialization for the first run. Every rectangle corner, sample and origin stack location now matches. The final prefix-loop, run construction, spawn-record stores and return otherwise match the original instruction stream. The saved comparison gives the exact offsets at 13, 16, 2A2 and 2B2. Source controls for signed guards, early exits, cursor type, separate run scope, origin assignment and counter volatility do not improve this result; their evidence is retained. In-place upper-corner addition is shorter and fails badly, so the complete temporary and assignment must remain.

## Bounded execution evidence and reproduction

The final maintained source passes **199 comparisons** against the complete original function. The fixture executes full native supporting bodies and shared raw retail SetPolar/security-cookie routines. Script initialization, animation VM execution, operator new and virtual laser Initialize are shared scripted boundaries; the loader itself executes normally. This is bounded behavioral evidence, not a full game integration test or raw byte proof.

Cases cover strict sampling thresholds, no/all/prefix/middle selection, rectangular edges and corners, degenerate and negative sizes, unordered and infinite size/center values, viewport limits, nonzero Z, positive/negative angles, disabled items, occupied item rings, count tiers, identifier wrap and deterministic random states. The unused `radius` fixture field is inherited from the circular fixture and supplies no rectangle-radius coverage. Comparisons check complete owner/item/pool/manager/allocated-object state, all 476 spawn-parameter bytes, callback order, return value, RET12 cleanup, preserved registers and x87 state. The final fixture observed 243 item calls, 588 effects and 47 spawned lasers; no instructions were patched.

Run from the repository root with the existing MSVC toolchain and Unicorn 2.1.2 available:

```sh
python3 matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/measure.py rectangle_current
python3 matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/differential.py rectangle_current
python3 matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/native_gate.py
```

Outputs are ignored experiment artifacts. The native-gate command copies production into an isolated project and reports structural success and `raw_exact: false`; its exit code alone does not establish equality. Production is unchanged. A fresh audit confirms its 487,936-byte executable still exactly matches the oracle; all 1,483 selected functions across 963 current layouts retain matching hashes. Exact ordinary C++ remains 199,062 bytes / 61.9%, with 60 actual assembly regions remaining after excluding equivalent owners.

The next useful work is the small hit-count/first-run live range and cookie scheduling residue. Promotion requires equality of all 1,171 bytes, followed by the normal complete production builds and audit. This candidate must not be reported as recovered merely because only 27 bytes remain.

## Read-only scheduler follow-up

The following goal turn revalidated the current source receipt and replayed its real native LTCG link using `reference/compiler_traces/scheduler/trace_target_link.py`. The c2.dll fingerprint is `7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5` (13.10.6030). Four hardware breakpoints observe function entry and scheduling; no compiler data, register choice or generated instruction is written. The trace completed with 656 events over 29 graphs. All 1,171 traced native bytes equal the uninstrumented native contribution, SHA-256 `c676de1bc5131cbc175f209b80af257121e3432fc943e3b3b08b1fd3b2a7419e` before diagnostic address binding. Current fixed-address cutter SHA remains `7889b1ce3e1bb3343022b0c483da5dcbf2370ae7a603613a68aa3409a66071fc`.

In graph 0 at cycle 2, cookie-store sequence 3 and EBX-push sequence 4 are simultaneously ready with equal priority 102400. The lower sequence cookie store wins. The size-argument load, sequence 10, then becomes ready with priority 124928 and also precedes the EBX push. Retail instead places the push and receiver copy before the cookie store and size load. This proves the current compiler's scheduling decision; it does not reconstruct the original dependency graph or justify changing a scheduler preference.

Graph 11 already contains the zero-producing `XOR EAX,EAX` (sequence 2) and `CMP ECX,EAX` (sequence 4) before scheduling. The later TEST-EAX versus CMP difference therefore originates before this scheduler, rather than in instruction encoding. Named boolean/inline predicate/switch forms, literal-zero early returns, pointer/reference qualifiers and mask types were measured and do not improve the 27-byte residue. The proof, complete event log and exact replay command are saved under `evidence/scheduler_*`.

Reproduce after the current diagnostic measure command:

```sh
python3 matching2/reference/compiler_traces/scheduler/trace_target_link.py matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current/commands.json matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_scheduler_trace CutRectangle
```

The related line-laser trimmers are now maintained and tested; see `laser_trim_native_0041d880_0041dd80_2026_10_06.md`. Their rectangle candidate narrows the shared scheduling residue to 13 prologue bytes. Neither trim has been promoted, and production recovery coverage remains unchanged.

### Earlier flow follow-up

The next [shared-family follow-up](laser_cutter_family_followup_2026_10_06.md) traces the same complete 1171-byte body at Riscify, late-flow and code-motion entry. The hit test already reuses EAX zero at Riscify entry, before the observed late passes or scheduling. Five phase dumps complete normally, with hardware breakpoints only and identical traced/untraced bytes. The responsible earlier pass remains open; `evidence/late_flow_*` is the current proof.
