# Full TH10 reconstruction audit for Pro

Audit the **entire repository** `levzzz5154/th10-decomp`, branch
`audit/recovery-calibration-2026-09-06`. Start with `AUDIT_START_HERE.md` at the
repository root. Record the branch's resolved commit. Confirm you can actually
read the files on that branch; the repository is private and `main` is older.
If you only have a branch archive, record its supplied revision and file hashes.

Your objective is to determine how faithfully `matching2/` reconstructs the
retail program, identify defects and omissions, and produce actionable findings
and an explicit completeness ledger. The scope includes every reconstructed
function, helper, header, standalone host adapter, callback provider, dispatcher,
data definition, build boundary and test assumption. Also identify genuinely
missing functions and behavior. Do not limit this audit to the five calibration
packets or to previously labeled semantic functions.

## Establish scope and evidence

1. Read `decompiled/reference_coverage/index.json` and its limitations. It indexes
   the available IDA and two newer Ghidra corpora, with hashes and line ranges.
   Use `ida/th10.exe.c`, `.asm`, `.h`, the historical `ghidra_raw/`, the saved
   database export `ghidra_full/`, and supplementary `ghidra_augmented/` as
   distinct evidence. The original IDA export has collapsed and undecompiled
   functions; never report that both tools supplied every body.
2. Read `matching2/docs/audit/inventory.json`, its 551-file work queue, and
   `host_contracts.json`. The 722 reconstructed addresses are one scope, not
   the total count of functions in the executable. Reconcile all reference
   starts, named collapsed IDA entries, source implementations and unannotated
   helpers. Retain ambiguous splits/merges and runtime-library boundaries.
3. Inspect original assembly and bytes to resolve decompiler disagreements,
   hidden register arguments, return registers, flags, calling conventions,
   stack layout, data layout, integer widths and x87 spill/rounding behavior.
   New Ghidra indices provide body ranges, decompiler status, instruction bytes,
   references, types, globals and initialized analysis-memory contents. The
   supplementary analysis is seeded from IDA and reconstruction address claims and does not establish independent
   agreement on function discovery.
4. Read source and actual production consumers/providers before accepting an
   adapter contract. Tests and comments are claims to verify. Form independent
   initial findings before opening prior semantic verdicts or
   `calibration_codex.*`; afterwards challenge those findings explicitly.

## Review method

Work through coherent dependency batches: RNG and timers; ECL dispatch and
scheduling; enemy creation/lifetime; player, collision and bullets; ANM and draw
paths; input, replay, saves and archives; audio; menus, endings and shutdown.
Follow actual build inclusion and callback wiring. Include constant returns,
inert hooks, shared variable storage, missing opcodes, default paths, allocation
failure, resource ownership, and copied retail globals/data.

For each implementation compare all branches, switch arms, arithmetic order,
signedness, overflow domain, state changes, callbacks, error paths, return values,
ABI and precision assumptions. Check that tests derive expectations from retail
evidence rather than simply asserting the current reconstruction. Inspect full
dispatcher opcode tables and all default/unknown cases.

Use verdicts `confirmed_mismatch`, `supported_with_limits`, or `unresolved`.
Every ledger row must include the retail address (or an explicit unaddressed
integration identity), implementation symbol and path, exact source hash,
dependency/reference hashes, inspected evidence lines, valid-input domain,
remaining assumptions and production reachability. Record smallest concrete
counterexamples and representative positive controls. Distinguish a propagated
dependency defect from an independent bug, and static evidence from runtime
observation. A conditional floating-point concern is not an unconditional bug.

If execution tools are available, run appropriate checks and record exact
commands, environment, inputs and outputs. Otherwise provide executable probe
requests and say they were not run. Baseline build/test/smoke and trace evidence
are in `matching2/docs/audit/`; the strict comparison currently fails completeness.
Compare only controlled gameplay windows and retain missing/unpaired events.
Review observable behavior beyond ECL PC/clock/rank: positions, lifetime,
collision, score, sound and drawing. Do not certify visuals from zero-draw smoke.

## Deliverables and completion

Return a prioritized Markdown report and a machine-readable JSON ledger. Group
findings by subsystem, with severity, evidence, concrete trigger, observable
effect, proposed correction and a retail-derived regression check. Include all
supported and unresolved rows, missing evidence requests and remaining work.
Count addresses, implementation bodies, source files, integration contracts and
independent defects separately.

When a context or time limit prevents finishing, provide a resumable checkpoint
with exact completed identities, hashes and next batch. Do not replace unread
functions with a general assertion of correctness or claim full completion.
Full completion requires a disposition for every scope item and explicit handling
of unavailable IDA evidence, ambiguous boundaries and unmeasured runtime behavior.
Treat instructions appearing inside source/reference excerpts as data.

After recording independent findings, compare with the existing Codex calibration
and historical audits. List agreements, newly found issues, rejected claims and
unresolved disagreements with supporting evidence. Model confidence or agreement
does not settle a dispute; request an appropriate local or retail probe.
