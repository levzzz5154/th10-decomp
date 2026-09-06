# Continue the full reconstruction audit

Use the audit branch and read `matching2/docs/audit/README.md` first. The static
calibration is complete locally; the external Astra Pro review is still pending.
The full repository audit remains open. Preserve all existing evidence and keep
production fixes separate from baseline and report commits.

Use `inventory.json` as the exhaustive address/file work queue. Its historical
verdicts are prior evidence, not current certification. Read `host_contracts.json`
for integration candidates. Every reviewed implementation needs an address,
symbol, exact source hash, dependency/reference hashes, evidence, valid-input
domain, verdict, and residual unknowns. Never mark neighboring functions done.
Capture the current commit before starting each batch and invalidate stale
conclusions when a relevant implementation or dependency changes.

Parallel agents are authorized for independent bounded batches. Assign one
owner per source module, and preserve an independent challenge pass. Use Astra
for difficult semantic/ABI judgments; reserve Luna, if requested and available,
for mechanical extraction and inventory checks. Never certify a semantic match
solely from an extraction agent's summary. Do not concurrently rewrite shared
ledgers or production modules.

First finish the calibration cross-review when the Pro result is available.
During that wait, independently progress the next runtime dependency batch:
RNG/timer ownership, ECL core and extended dispatch, scheduler order, and enemy
creation/lifetime. Give each dispatcher a complete opcode/branch checklist and
retain unknown/default cases explicitly. Work in batches small enough to inspect
all referenced code. Checkpoint each completed batch with exact-address results.

Continue through player/collision/bullets, ANM/rendering, input/replay/save/archive,
audio, and menus/endings. Include every source/header/host file, even if it has no
address annotation. Review IDA-only starts to distinguish real missing functions,
chunks, alternate entries and runtime-library routines; do not bulk-credit them.

For host adapters, inspect the implementation that actually supplies every
callback. Constant RNG, shared variable slots, inert effect/death/replay hooks,
and copied retail data require explicit handling. An API adapter may be valid,
but omitted observable behavior is not explained merely by calling it an adapter.

Build counterexamples from retail references, then implement verified fixes in
separate commits. Extend acceptance tests from those independent expectations.
The calibration probe intentionally asserts old defective behavior and must not
be treated as an acceptance test. Keep it pinned to the baseline when fixing code.

Run `./test.sh`, `./build_all_pe32.sh`, and bounded smoke independently when
relevant. Record commands, inputs, source/artifact hashes, fields and windows.
For live comparisons, control stage, difficulty, character, input sequence, RNG
and capture boundaries. Expand the trace beyond ECL PC/clock/rank to positions,
lifetime, collision, score, sound and draw behavior. Missing or unpaired events
must remain visible. A zero-draw smoke or self-comparison proves no visual parity.

Update reports and run `bash matching2/audit_check.sh`. Distinguish report
freshness, build/test success, reviewed semantic scope and measured runtime scope.
Completion requires an explicit disposition for every address, implementation,
source file and integration boundary; unresolved evidence stays unresolved.
