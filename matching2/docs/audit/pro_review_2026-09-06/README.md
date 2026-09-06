# Pro report intake and local reconciliation

This records the pre-fix intake. See [subsequent fixes](../fixes_2026-09-06/README.md)
for current dispositions and validation; the supplied evidence below stays historical.

The supplied report is a **partial audit**, not a completed whole-repository audit
or cleanup. Original files are preserved unchanged under [original/](original/).
All eight supplied SHA-256 entries verified. [intake.json](intake.json) records
archive identity, source checks and locally reconciled evidence lines.

## What was verified locally

All five new scheduler contract findings are supported by inspected original
assembly and the supplied probe compiled against unchanged local source.
The scheduler source, header and reference blobs match Pro's recorded identities.
Across the expanded report, 47 of 48 recorded path/blob identities match locally;
`AUDIT_START_HERE.md` differs. Pro's reported newer commits and CI artifacts were
not fetched or independently verified during this intake.

| Finding | Local observation | Original contract |
| --- | --- | --- |
| SCHED-01 | Primary and secondary null-tail modes each timed out after 1 second; source branch revisits the same node | Advance to cached null successor and finish |
| SCHED-02 | Both tail-removal modes call A twice, B once, return 3 | Call each once, return 2 |
| SCHED-03 | Primary restart calls A/B twice but returns 3 | Restart resets count; return 2 |
| SCHED-04 | Secondary code 6 calls A twice; code 7 calls the auxiliary handler | Ordinary counted continuation for both codes |
| SCHED-05 | Unowned removal preserves the function and loses the owner | Clear function and preserve owner |

Four supplied controls (ordinary traversal, repeat code 2, inactive callback,
primary code 7) behaved as expected. See
[local execution results](local_scheduler_results_corrected_command.json).
The first compile attempt omitted the native `__fastcall` compatibility define;
its diagnostics are retained separately. The corrected command compiled cleanly.
The probe itself was not edited. Native x86-64 observations do not establish
PE32 layout/calling conventions, locking, concurrent mutation or live activation.
Timeout alone is not a proof of nontermination; the inspected unchanged-node
branch supplies that control-flow evidence.

## Report limitations and remaining work

- Pro reports six earlier confirmed defects: RNG word order and counter overflow,
  two timer contracts, and two bullet ANM variable-provider contracts. These remain
  inherited findings here, not six additional locally revalidated results.
- Its four continuation items include unresolved interpolation/ECL concerns and a
  rejected ECL-offset suspicion. They are not new confirmed bugs.
- `scope_ledger.json` is referenced but absent from the supplied ZIP. The older
  checkpoint ledger exists; it does not replace the missing expanded scope ledger.
- The supplied fresh execution records contain no compile/run results: setup
  failed on a missing session file. Scheduler source/reference evidence-line
  arrays in the expanded JSON are also empty; local matches are recorded separately.
- Pro did not independently revalidate the six original calibration bodies.
- The cleanup manifest records no deletions or moves, and only a README heading
  clarification as applied cleanup. Whole-tree cleanup remains incomplete.

The immediate supported fix batch is the scheduler walker/removal contracts, with
retail-derived regression tests. Next reconcile the earlier RNG/timer/ANM findings
and recover the missing scope ledger and claimed CI/probe artifacts. No production
fixes, repository cleanup, or full-audit completion are claimed by this intake.
