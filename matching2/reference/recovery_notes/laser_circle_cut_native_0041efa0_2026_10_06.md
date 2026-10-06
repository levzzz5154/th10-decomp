# Circular laser cutter 0041EFA0: complete 1,108-byte candidate, not promoted

The previous turn recovered and behaviorally tested the complete circular cutter but stopped at a 1,092-byte compiler contribution. This follow-up made progress: genuine typed animation interfaces and first-run counter lifetimes produce the required **1,108 bytes**, with 43 instruction difference groups and **433 differing bytes**. It also recovered the complete rectangular splitter at 0041EB00; its current result is documented separately. Neither cutter has been promoted. The full readable, byte-matching, inline-assembly-free C++ objective remains active and incomplete.

Production was unchanged in this follow-up. A fresh audit confirms all 487,936 executable bytes equal the oracle, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. All 1,483 selected functions across the manifest's 963 current native layouts have oracle-matching hashes; 3,968 distinct compiler input files were checked against current report hashes. Reports contain zero instruction changes, masks or reference bytes used for building. Ordinary exact C++ remains 2,254 regions / 199,062 bytes (61.9% of recoverable game code). After excluding the eight equivalent owners, 60 actual assembly regions / 89,245 bytes remain. The preceding turn's `make` and `make EXACT=1` passed; no production edit required rebuilding them here.

## Current sources and proof

The maintained source graph is `matching2/reference/semantic_candidates/laser_circle_cut_0041efa0/`. Its nine C++ modules, typed animation ID/resource interfaces and local layout snapshots contain no inline assembly or naked body. Supporting functions are complete actual routines. No synthetic caller, register bridge, dummy helper, shortened function or forced compiler register is used.

Live Ghidra MCP was revalidated against project `th10`, program `th10.exe`, PID 4123453. The preceding read-only circular decompilations remain in `evidence/`; a fresh rectangular decompilation informed this follow-up. No Ghidra prototype or project was changed.

The maintained graph was freshly rebuilt and executed. Its complete cutter bytes equal the chosen diagnostic snapshot and the fixed-address native PE body. The unchanged production verifier passes the full extent and structural checks in an isolated project; an independent raw comparison of all 1,108 bytes fails with 433 differing bytes. Candidate SHA-256 is `5368c0df617a81b0a54342808017726d86ce8c1fd95a84201bbf8bdd4d758a95`; retail SHA-256 is `06d97cb8369d484fed1cc7a91a5abcabe56e123a5210169d0c6edf082e9222d1`. Both structural success and raw failure are retained in `evidence/native_gate_receipt.json`, with the current native report and input hashes.

The complete 98-byte base constructor, 203-byte script loader and 118-byte primary-back registrar also match their retail bodies in this graph. These routines were already recovered in production and add no recovery credit. Other unselected supporting bodies still differ, so this is not a claim that the whole isolated graph matches the executable.

Reproduce from the repository root, with the existing MSVC toolchain and Unicorn 2.1.2 fixture dependency available:

```sh
python3 matching2/reference/semantic_candidates/laser_circle_cut_0041efa0/measure.py circle_current
python3 matching2/reference/semantic_candidates/laser_circle_cut_0041efa0/differential.py circle_current
python3 matching2/reference/semantic_candidates/laser_circle_cut_0041efa0/native_gate.py
```

The commands write ignored experiment output. The third copies production into an isolated project and reports `native_structural_gate_passed: true`, `raw_exact: false`; its exit status alone is not an equality check. Production remains unchanged. The obsolete 1,092-byte receipt and evidence, including its read-only register trace, are under `historical_1092/` and must not be treated as current proof.

## Behavior recovered from the executable

The original samples at six units from the origin and then every twelve units. A 256-byte stack mask records selected samples, and `/GS` protects this stack buffer. The sampling starts only when `12 < length` and continues while `progress + 6 < length`. This circular cutter initializes the step Z to zero before the public XY polar call, resets the initial point Z to zero, and subsequently performs all three point additions. These Z operations differ from the indeterminate third component in the previously recovered update routines and must not be silently conflated.

Radius is squared in its argument slot. The circle rejection is `distance_squared > radius_squared`, so an unordered distance or radius is **accepted**. Item visibility uses negated viewport rejection tests, also retaining unordered behavior. Visible kind-8 items are spawned **before** their segment animation. The animation uses script `2 * script + 17`, position offsets X +224 / Y +16, the 40000000 flag, and primary-back registration.

A cut prefix makes the original laser length zero. Otherwise the original retains the first uncut run at twelve units per sample. Every later uncut run produces a **new laser through 41C510**, using a freshly zeroed 476-byte parameter record, rather than cloning the live object. Parameter offsets are position 00, angle 0C, length 10, length limit 14, remaining distance 18, width 1C, speed 20, type 24 and script 26. Speed is 8; the two length fields are equal to the run's length. Position is the saved original origin plus the full three-component step times the run start index, and remaining distance subtracts twelve times that index. The original width, type and script are retained. The spawn selector is zero.

This makes the archived legacy cutter draft unsuitable as an exact source: it uses a dynamic vector instead of the fixed stack mask, ordered circle/visibility comparisons, and a clone abstraction that misidentifies the second length field as width. Its sketches remain historical references, not byte or behavior proof.

## Bounded execution evidence

The saved final candidate passes **186 comparisons** against the complete original routine. The fixture executes the native full item allocator, laser spawner, constructors, animation allocator, loader and registrar, and the shared original raw polar and security-cookie routines. It uses shared scripted boundaries for script initialization, animation VM execution, operator new, and virtual laser Initialize. The loader itself executes normally. This is bounded behavioral evidence, not a game integration test or byte equality claim.

Cases include no samples, the strict 12-unit threshold, exact run boundaries, all / prefix / middle / no selection, viewport edges, positive and negative angles, disabled item creation, NaN and infinite radii, unordered centers, item ring occupancy/count tiers, identifier wrap, and deterministic random finite states. Comparisons cover complete owner, item, animation pool, laser manager and allocated-object state, all 476 bytes of each spawn record, callback order, return value, RET12 cleanup, callee-saved registers and x87 balance. There were 211 item calls, 637 effect calls and 43 spawned lasers. No machine instructions were patched for these tests.

## Compiler work in this follow-up

A nontrivial `CutAnimationId` returned by the actual `CutAnimationLists::RegisterPrimaryBack` member supplies the correct hidden-result ABI and makes the complete registrar exact. The full resource member `CreateOffset` uses the same typed return. These interfaces follow existing exact production source forms rather than manually modeling a hidden output argument as `void**`.

Writing the sample mask before incrementing the hit count, and keeping the first-run counter inside its own `else` scope, supplies the circular candidate's missing 16 bytes and improves its control flow. The same lifetime form also improves the rectangular cutter. Register, vector-operator, declaration-lifetime, creator-inlining, sampling-state, pointer-reuse and prefix-loop controls are retained as experiment evidence. Ordinary full MSVC polar calls were also tested as a graph control; the retail SetPolar itself remains an external actual boundary in the chosen graph. No compiler allocation data was modified.

The circular residue is still principally sampling-index/resource register allocation, vector temporary homes, origin-copy scheduling and loop details. The historical trace chose EDI for the old candidate's sample counter while retail uses EDX and preserves the resource in EDI; that trace is historical evidence, not a new trace of the current graph. The rectangle's improved source shows that reconstructing real value reuse can resolve stack homes without synthetic padding or address escapes. Its half-size value becomes the upper corner after the lower corner is calculated.

Full raw equality of every required cutter byte remains mandatory. The next work should address these concrete live ranges and the shared source forms of the four cutters, preserving the NaN behavior, stack mask and complete spawn parameters already recovered. This follow-up added zero production recovery bytes.
