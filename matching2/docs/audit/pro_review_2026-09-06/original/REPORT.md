# TH10 reconstruction audit — expanded evidence and explicit completion status

**The requested whole-repository semantic audit is not complete.** This report preserves additional concrete findings, fresh execution evidence when available, and a full-scope machine-readable work queue. Parsed, hashed, or inventoried rows are not marked semantically reviewed.

## Revision and scope

Repository: `levzzz5154/th10-decomp`; requested branch: `audit/recovery-calibration-2026-09-06`.
Audit input: `09835addae52e8eda47fc8c387a518ca7a0b4294`. Frozen production baseline: `895c4202387d1c6099cf0cec2e8798bdae6a1754`.

The preceding handoff records 722 implementation addresses, 551 source/header/standalone files, and 1,717 indexed reference starts. A successfully regenerated local full-scope ledger was not available to this consolidation; those counts must not be read as completed reviews.

The reference-start count is not a count of independently proved true functions. IDA collapsed/undecompiled entries, split/merged bodies, imported implementations, runtime-library boundaries, and augmented Ghidra discovery remain separate evidence limitations.

## Five additional scheduler defects

These are five independent contract failures, not five fully completed address reviews. They concern the shared walker and three retail entry-point contracts. The original null-function, retirement, restart, default, and retained-object-state behaviors are directly represented in the reference control/data flow.

### SCHED-01 — A null-function tail never advances the reconstructed walker.

**Severity:** high. **Verdict:** `confirmed_mismatch`. **Retail:** `0x00449C00`, `0x00449D40`.

**Trigger and smallest control case:** One terminal null-function callback. Retail skips to the cached null successor and returns zero. Source leaves node unchanged and revisits the same callback.

**Observable consequence:** Nontermination of the selected scheduler pass for this valid null-function branch.

**Correction:** Walk a cached successor as the retail code does. A null function must advance without incrementing the count.

**Positive control:** A normal linked callback and a nonterminal null-function callback should not stall.

**Source:** `matching2/src/game/scheduler.cpp` (Git blob `82e4e4d8ae580b3e162178b39a7274859e2db6b0`). Exact retrieved hashes and evidence-line matches are in `findings.json`.

**Reachability limit:** The scheduler is included in the all-source build. The triggering state has not been measured during a controlled live gameplay window. Native probes are not PE32 ABI or concurrency validation.

### SCHED-02 — Retiring a tail callback restarts traversal and repeats earlier work.

**Severity:** high. **Verdict:** `confirmed_mismatch`. **Retail:** `0x00449C00`, `0x00449D40`.

**Trigger and smallest control case:** A returns one; B returns zero. Retail executes A,B once and returns count two. Source restarts from the sentinel after B's removal, executes A again, and returns count three.

**Observable consequence:** Extra update or draw callback execution in one scheduler pass, and a wrong count.

**Correction:** Continue at the cached next node, including null meaning end-of-list; do not turn ordinary tail removal into restart.

**Positive control:** Two surviving callbacks execute once each and return two.

**Source:** `matching2/src/game/scheduler.cpp` (Git blob `82e4e4d8ae580b3e162178b39a7274859e2db6b0`). Exact retrieved hashes and evidence-line matches are in `findings.json`.

**Reachability limit:** The scheduler is included in the all-source build. The triggering state has not been measured during a controlled live gameplay window. Native probes are not PE32 ABI or concurrency validation.

### SCHED-03 — Primary restart code six does not reset the result count.

**Severity:** medium. **Verdict:** `confirmed_mismatch`. **Retail:** `0x00449C00`.

**Trigger and smallest control case:** A returns one; B returns six once, then one. Both implementations run A,B twice. Retail returns two after resetting the restarted pass's count; source returns three.

**Observable consequence:** Incorrect return value of the primary scheduler.

**Correction:** Reset the result count on the primary restart continuation, matching the original restart target.

**Positive control:** A pass with no restart retains the normal count.

**Source:** `matching2/src/game/scheduler.cpp` (Git blob `82e4e4d8ae580b3e162178b39a7274859e2db6b0`). Exact retrieved hashes and evidence-line matches are in `findings.json`.

**Reachability limit:** The scheduler is included in the all-source build. The triggering state has not been measured during a controlled live gameplay window. Native probes are not PE32 ABI or concurrency validation.

### SCHED-04 — The secondary walker inherits primary-only meanings for return codes six and seven.

**Severity:** medium. **Verdict:** `confirmed_mismatch`. **Retail:** `0x00449D40`.

**Trigger and smallest control case:** Code six should be an ordinary counted continuation, not a restart. Code seven should not invoke onResultSeven. The shared reconstructed walker does both.

**Observable consequence:** Additional callback execution or an extra auxiliary callback, depending on the return code.

**Correction:** Parameterize or separate the walkers so secondary codes greater than five follow its default continuation.

**Positive control:** Primary code seven invokes its auxiliary callback once; ordinary secondary code one simply advances.

**Source:** `matching2/src/game/scheduler.cpp` (Git blob `82e4e4d8ae580b3e162178b39a7274859e2db6b0`). Exact retrieved hashes and evidence-line matches are in `findings.json`.

**Reachability limit:** The scheduler is included in the all-source build. The triggering state has not been measured during a controlled live gameplay window. Native probes are not PE32 ABI or concurrency validation.

### SCHED-05 — Unowned callback removal clears the owner instead of the function.

**Severity:** medium. **Verdict:** `confirmed_mismatch`. **Retail:** `0x00449F60`.

**Trigger and smallest control case:** Retail unlinks and clears the function at +8 while preserving owner at +0x20. Source unlinks, zeroes owner, and leaves function nonnull.

**Observable consequence:** The retained callback object's observable state is wrong; later reuse observes a lost owner and an uncleared function.

**Correction:** Clear function unconditionally after valid unlinking and preserve owner as retail does. Separately preserve the original guard against unlinking a sentinel.

**Positive control:** An unlinked callback is not removed again, and owned nodes are retired exactly once.

**Source:** `matching2/src/game/scheduler.cpp` (Git blob `82e4e4d8ae580b3e162178b39a7274859e2db6b0`). Exact retrieved hashes and evidence-line matches are in `findings.json`.

**Reachability limit:** The scheduler is included in the all-source build. The triggering state has not been measured during a controlled live gameplay window. Native probes are not PE32 ABI or concurrency validation.

## Executions

The continuation obtained GitHub Actions run `34041338912`, artifact `9991778528`, from the pinned checkout. The prior execution record reports reference integrity, audit integrity, and the full host tests passing, with strict host-contract review still failing. The raw CI results were not successfully located by this consolidation, so the available remote artifact and previous execution record must be retained rather than replacing them with invented logs.

Fresh local compilation/execution attempts, outputs, compiler versions, errors, and timeouts are preserved in `scheduler_probe_results.json` and `execution_results.json`. A timeout is not a successful acceptance test. The null-tail source branch independently explains the absence of progress.

The existing calibration probe intentionally reproduces baseline defects. Its successful rerun, when recorded, does not certify reconstruction equivalence. Re-comparing archived traces is likewise not a new retail capture.

## Previously established findings

The earlier checkpoint ledger is embedded verbatim in `findings.json` and, when available, supplied under `previous_checkpoint/`. It includes RNG word ordering and signed-counter overflow, timer argument/reset contracts, bullet ANM shared-variable storage and ignored integer-variable resolution, plus conditional floating-point boundaries. Those findings are not expanded into whole-function or whole-game correctness claims.

## Other continuation work

The preceding continuation recorded interpolation-curve, speed, rounding, and ECL float-destination concerns, and rejected a stale ECL instruction-offset warning. These are retained as explicit follow-up items in the JSON. They are not promoted into the newly verified scheduler defect count without full reconciliation of their exact probe artifacts and evidence lines.

## Cleanup

The previously committed README heading clarification is retained at `09835addae52e8eda47fc8c387a518ca7a0b4294`. Two audit-only workflow commits were created during this continuation: `e8fdb51b01aeddae8f240262e85c45df4599f46b` for pinned-checkout evidence collection and `0b309864646e568463d45998123bf573a1abe3d1` for offline parser dependencies. No behavioral fix or speculative evidence deletion is claimed.

`cleanup_manifest.json` records retention and candidates. Byte-identical files are not automatically redundant; the three Ghidra corpora must retain their distinct provenance and coverage. Mechanical missing-link candidates require historical/generator/context checks before correction.

## Exact remaining work and resumption

Read `findings.json` first for concrete counterexamples and the immutable source identities. Then use `scope_ledger.json`: `review_level` explicitly separates mechanical inventory, a demonstrated contract mismatch, and work that has not received complete semantic review. No function is deemed correct merely because its file was hashed, parsed, compiled, or covered by a passing host test.

Close the remaining scheduler contracts and callback activation analysis; reconcile the interpolation and ECL binding probes; then complete the full ECL opcode/default/provider matrix and each remaining dependency batch: enemy lifetime, player/collision/bullets, ANM/drawing, replay/input/save/archive, audio, menus/endings/shutdown, global data and ABI boundaries. All unavailable IDA evidence and unmeasured live behavior must retain their explicit dispositions.

**Semantic completion and cleanup completion remain false.** The deliverable is a resumable expanded audit, not the completed whole-repository audit requested.
