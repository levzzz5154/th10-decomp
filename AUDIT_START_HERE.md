# Full repository audit handoff

Use branch **`audit/recovery-calibration-2026-09-06`** in
`levzzz5154/th10-decomp`. The default `main` branch does not contain this handoff.
Record the resolved commit before reviewing. The reconstructed production code
is frozen at `895c4202387d1c6099cf0cec2e8798bdae6a1754`; later handoff commits
add reference exports, review infrastructure and evidence.

Give Pro [the full-repository prompt](matching2/docs/audit/FULL_REPO_PRO_PROMPT.md).
It includes a repository cleanup phase and a manifest of retained, consolidated,
archived, removed and unresolved files, with dependency and evidence checks.
The five-packet ZIP is only the optional calibration exercise; it is not the
input or scope limit for this full audit. Pro needs access to the private repo
and this branch, or a downloaded archive of this branch.

## Reference material

| Corpus | Contents |
| --- | --- |
| [ida/](ida/) | Original Hex-Rays C, IDA assembly and types, unchanged |
| [decompiled/ghidra_raw/](decompiled/ghidra_raw/) | Historical 703 tracked game-function pseudocode exports used by prior audits |
| [decompiled/ghidra_full/](decompiled/ghidra_full/) | All 1,196 functions from the saved Ghidra database, with separate C and addressed instruction/byte listings |
| [decompiled/ghidra_augmented/](decompiled/ghidra_augmented/) | 1,717 functions after supplementary analysis using explicit IDA starts and reconstruction address claims; changes discarded from the original database |
| [Reference coverage](decompiled/reference_coverage/README.md), [JSON](decompiled/reference_coverage/index.json) | Exact address navigation, source hashes, IDA line ranges, and unavailable evidence |

Both new Ghidra corpora include whole-program listings, complete initialized
analysis-memory hex dumps, memory maps, symbols, external signatures and types.
Each function index records disjoint body ranges, instruction counts, decompiler
status and diagnostics. Both exports had zero decompilation failures. The
supplementary corpus covers every IDA C-body address and every one of the 722
reconstruction addresses; its seed logs distinguish pre-existing and newly
created function definitions. This availability does not validate source claims.
Memory dumps describe Ghidra's loaded image, including
synthetic/zero-filled analysis regions; they are not runtime captures. The entire
412,672-byte `.text` raw section was compared against the local executable for
both corpora and matched. Executable SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

**The original IDA material is incomplete.** Its C export reports 1,906 functions
but only 1,224 decompiled bodies. Its assembly contains 1,237 expanded procedures
and 669 collapsed entries. The supplied `levzzz.zip` contains exactly the same
three files, verified byte for byte; see [archive provenance](decompiled/ida_archive_provenance.json).
There is no IDA database or fuller export in that archive. Completing the IDA
side requires an expanded listing and complete decompilation from IDA. Ghidra
supplements missing evidence but cannot establish an independent IDA result.

Do not equate either tool's function boundaries with the complete set of true
functions. Include split/merged bodies, tiny helpers, jump thunks, library code,
and imported routines in the boundary review. Imported DLL implementations are
outside the executable and have declarations rather than local function bodies.

## Reconstruction, tests and prior evidence

The current implementation, headers, host integration, build scripts, tests,
retail trace archive, and recovered data definitions are committed under
[matching2/](matching2/). The [audit handoff](matching2/docs/audit/README.md)
contains the 722-address/551-file implementation inventory, host contract queue,
baseline build/test/smoke evidence, comparator limitations and continuation rules.
That implementation inventory is not the total reference-function count.

Prior audit labels and the bounded Codex calibration are historical claims.
For independence, form first-pass verdicts from sources and assembly before
opening their findings. Passing host tests, matching decompilers, or agreeing on
paired ECL trace events does not certify gameplay equivalence.

Local dependencies for live reproduction are documented in baseline metadata:
the game executable/assets, toolchains and Wine are not bundled as runnable
installations. Static reference review requires neither IDA nor Ghidra installed.
The exports carry the evidence needed to inspect code, bytes, types and globals;
fresh analysis and runtime checks require the corresponding local tools/inputs.

Verify committed evidence with:

```bash
python3 tools/audit_reference_corpus.py --check
bash matching2/audit_check.sh
```

Regeneration commands, requiring the local Ghidra project, write into new empty
directories so historical evidence is preserved:

```bash
bash tools/export_full_audit.sh saved /tmp/th10-saved-reference
bash tools/export_full_audit.sh augmented /tmp/th10-augmented-reference
```
