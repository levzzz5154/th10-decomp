# Reconstruction audit handoff

For Pro auditing the **entire repository**, start with the root
[AUDIT_START_HERE.md](../../../AUDIT_START_HERE.md) and
[FULL_REPO_PRO_PROMPT.md](FULL_REPO_PRO_PROMPT.md). The expanded Ghidra corpora,
IDA archive provenance and function-level reference coverage are linked there.
The five-packet exercise below remains an optional bounded calibration.

The branch includes a bounded calibration, a [partial Pro review](pro_review_2026-09-06/README.md),
and [production fixes with regression evidence](fixes_2026-09-06/README.md).
The full repository audit and complete independent cross-review remain **open**.
Historical baseline evidence and calibration packets remain pinned to
`895c4202387d1c6099cf0cec2e8798bdae6a1754`; current production code has changed.

<a id="start-the-independent-pro-review"></a>

## Optional five-packet calibration

Give Astra Pro [PRO_REVIEW_PROMPT.md](PRO_REVIEW_PROMPT.md),
[pro_results_template.json](pro_results_template.json), and all five files in
[packets/](packets/). Alternatively upload [pro_review_bundle.zip](pro_review_bundle.zip),
which contains exactly those inputs and the packet hash manifest. The repository
is private: a plain URL is insufficient without repository access; attached
packets contain the evidence directly. Additional dependencies are linked to the
immutable baseline and should be requested when access is unavailable.

Have Pro save its independent verdicts before opening the Codex results. Then
compare both reports and return disagreements with exact evidence for local
verification. The six implementation rows cover five addresses. Packet 1 has two
different C++ implementations of one retail address. The packet format includes
full implementation files/headers, exact IDA and Ghidra references, relevant
constants, hashes, and caller navigation. It does not imply that unseen callers,
runtime activation or the live x87 environment have been established.

No Astra Pro run has been performed here. A separate Codex reviewer checked the
source references and ran a local probe; it had prior conversation context. The
Pro bundle excludes existing verdicts and probe results to support an independent
challenge. Model agreement alone will not establish correctness.

## Evidence map

| Artifact | What it establishes |
| --- | --- |
| [baseline.json](baseline.json) | Exact source revision, compiler/Wine versions, asset hashes, commands, exit codes and artifact hashes |
| [inventory.md](inventory.md), [JSON](inventory.json) | 722 addresses; all 551 files in src/include/standalone; source candidates and reference availability; separate historical verdicts |
| [host_contracts.md](host_contracts.md), [JSON](host_contracts.json) | 27 inert/constant/shared-slot candidates requiring manual contract review; neither exhaustive nor a bug count |
| [calibration_codex.md](calibration_codex.md), [JSON](calibration_codex.json) | Six implementation reviews, counterexamples, positive controls, ABI and precision boundaries |
| [comparison.json](comparison.json) | Corrected comparator results against archived retail and fresh baseline reconstruction traces |
| [CODEX_CONTINUATION.md](CODEX_CONTINUATION.md) | Instructions for subsequent subsystem batches and completion criteria |

The inventory preserves 539 IDA-only starts as boundary-review candidates,
including possible chunks, thunks and runtime-library functions. Its 280 addresses
with multiple candidate files include headers and incidental claims; this is not
a count of conflicting implementations. The historical review remains 57 checked
within its 708-address partition, plus five sparse checks; its original revision
was not recorded. Those labels are not automatically revalidated here.

## Fresh baseline validation

The detached baseline checkout passed `./test.sh`, `./build_all_pe32.sh`, and
`./run_all_pe32.sh --smoke --ecl 3600 --trace <output>/reconstruction_stage.jsonl`.
Build: 281 production translation units, 220 imported retail data symbols, zero
unresolved project edges. Smoke: 3,600 update/draw ticks, stage frame 3,570, clean
shutdown, **zero title sprite draws**. No new live graphics validation or retail
process capture was performed. Game assets and executable remain local inputs;
they are hashed but not redistributed.

The reconstruction trace contains 107,181 events and 76,558 ECL ticks. Its
[compressed artifact](evidence/reconstruction_stage.jsonl.gz) decompresses to the
exact captured bytes. The [retail reference](../../tests/retail_probe_evidence/retail_ecl_reference.jsonl)
is the pre-existing 17,694-event, 10,900-ECL-tick archive.

The strict all-VM comparison exits **1**: 63 retail VMs versus 158 reconstruction
VMs, only 16/63 equal paired VM tick counts, unmatched ticks on both sides, and
two unresolved retail PCs. All 10,127 paired ticks agree on compared fields.
Root-only comparison also exits 1: 1,536 paired ticks agree, with 2,034 extra
reconstruction ticks. These differently bounded captures do not establish equal
gameplay windows; VM-count differences alone do not prove a specific lifetime
bug. Matching paired fields does not cover omitted or unmatched behavior.

The comparator now requires nonempty complete evidence and matching counts in
the selected scope. Invalid inputs exit 2; mismatches/incomplete evidence exit 1.
`--prefix-ticks N` deliberately compares a stated prefix and reports excluded
tails. `--flat`, `--timeline` and `--self-check` print their restricted diagnostic
meaning. Retail PC resolution still depends on a documented 2 MiB candidate
window; unique mapping is not proof of the actual script allocation extent.

## Reproduce and continue

From the repository root:

```bash
bash matching2/audit_check.sh
bash matching2/test.sh
python3 matching2/tools/audit_packets.py --check
python3 matching2/tools/audit_host_contracts.py --strict
```

The last command intentionally exits 1 while candidate contracts are pending.
The first commands validate infrastructure, evidence freshness and host tests;
they do not certify game equivalence. No baseline was relaxed to hide findings.

To reproduce the recorded trace comparison:

```bash
gzip -dc matching2/docs/audit/evidence/reconstruction_stage.jsonl.gz > /tmp/th10-audit-reconstruction.jsonl
python3 matching2/tools/retail_vs_recon_stage.py \
  matching2/tests/retail_probe_evidence/retail_ecl_reference.jsonl \
  /tmp/th10-audit-reconstruction.jsonl
```

The calibration probe's pinned reproduction command is in its report. It intentionally
asserts observed baseline defects; its successful result is **not** an acceptance
test and it is excluded from `test.sh`. Future fixes need retail-derived tests
in separate commits. Preserve the old probe as baseline evidence.

Regenerate current-source inventories with `audit_inventory.py --write` and
`audit_host_contracts.py --write` after reviewing source changes. Packets always
read their named Git baseline. Keep review scope, source hashes, dependency
hashes and unresolved rows explicit when continuing the full audit.
