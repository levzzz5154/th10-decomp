# Review fixes and validation — 2026-09-06

The eleven confirmed Pro findings are corrected, along with the earlier easing,
version-marker and FPS calibration defects. Related ANM destination, special-value,
interpolation and ECL local-address errors were also corrected. This closes the
listed defects, **not the whole-repository semantic audit**.

The original [Pro submission and pre-fix reproduction](../pro_review_2026-09-06/README.md)
and [calibration](../calibration_codex.md) remain available. Baseline packets still
refer to commit `895c420`; current-source inventories have been regenerated.

| Finding / area | Change | Regression evidence |
| --- | --- | --- |
| SCHED-01…05 | Advance through cached successors, terminate null tails, avoid replay after tail removal, reset primary restart counts, keep secondary 6/7 as ordinary continuation, clear removed callbacks while preserving unowned owner state | `scheduler_test.cpp`; all 12 original Pro probe modes now match reviewed contracts in [scheduler_results.json](scheduler_results.json) |
| RNG-001/002 | Correct DoubleStep low/high packing; unsigned generation counter wraps modulo 2^32 | `retail_math_contract_test.cpp`: all 65,536 seeds, both packings, wrap boundaries |
| TIMER-001/002 | Restore explicit decrement count; owner timer resets previous to -1 and lazily binds the shared speed; raw owner pointer stores retain PE32 width | Counts 0/1/2/-3, negative-count behavior, reset and pointer/flag preservation tests |
| FP-001/002 | Preserve wide Tick sum before integer conversion; preserve Advance product through the elapsed store and then reload for conversion | Controlled x87 precision 24/53/64 probes, native and 32-bit; no claim about the live retail control word |
| ANM-001/002 | Store six integer and four float registers per VM; bind title, bullet and digit providers to the same resolver; respect variable flags and mixed numeric reads | Actual `AnmVm_Tick` scripts verify destination writes, literal fallback, and per-VM separation |
| ANM float/destination follow-up | Decode float IDs numerically; avoid dereferencing destination IDs as source values; map mixed slots, base position, camera groups and correct RNG flavors; use imported normal/alternate RNG state instead of constants or `std::rand` | Integer/float writes, unknown-ID and clear-mask stores, special-ID and alternate-RNG controls; complete PE32 link and stage smoke |
| Easing / interpolation | Share the full easing selector; retain fractional clocks; use Hermite mode 8; fix integration order, completion and integer truncation order, including the scalar/vector distinction | Mode 11/12 dyadic controls; trajectory result 6; half-speed Hermite, acceleration, negative integer blends and per-term versus final truncation controls |
| Version marker / FPS | Probe `th10.dat`; read FPS after updating its average and pass position plus promoted value to the printer | Archive filename assertion; callback-mutated FPS, colour and `(590,470,0)` print-argument assertions |
| ECL local float destination | Remove the extra eight-byte bias: `scratch` already starts at retail VM+8 | Compared with `0x00450070` assembly and the existing core resolver contract; PE32 build and stage smoke. No new full negative-global resolver claim |

## Validation

- Full `bash matching2/test.sh`, including reference/audit integrity gates: passed.
- `bash matching2/build_all_pe32.sh`: passed; 281 production translation units,
  225 imported data symbols, zero unresolved project edges, no new/worsened fidelity gates.
- Scheduler, numeric and ANM/interpolator regressions also passed native 32-bit builds.
  Native numeric and ANM cases passed with UBSan.
- `bash matching2/run_all_pe32.sh --smoke --ecl 3600 --trace …`: passed;
  3,600 stage update/draw ticks, clean shutdown. Title sprite draws remain zero.
- Original Pro scheduler probe: 12/12 reviewed contracts pass, including both
  previously nonterminating null-tail modes.
- `python3 matching2/tools/run_baseline_calibration.py`: passed against the
  original Git snapshot, reproducing historical defects without modifying current code.
- Strict comparison of the new stage trace against the archived retail trace:
  exit 1, incomplete/mismatching coverage. The windows are differently bounded;
  this is not a gameplay-equivalence pass.

[validation.json](validation.json) records commands, source hashes and stored
artifact hashes. [cleanup_manifest.json](cleanup_manifest.json) records the
consolidation and retention decisions. Logs and the compressed stage trace are
under [evidence/](evidence/).

## Remaining scope

The full dispatcher and host-provider audit is still open. Bullet/digit child and
ring callbacks remain incomplete; this smoke does not prove their unreachability.
Other constant/no-op providers remain in the generated host-contract queue.
Arbitrary interpolation inputs, general x87 spill/rounding equivalence, live FP
state, all gameplay/graphics/audio/collision paths, and ECL global resolver behavior
are not certified by these regressions. The IDA export still contains collapsed
and undecompiled functions. Historical audit verdicts have not been relabeled as
current independent clearance.
