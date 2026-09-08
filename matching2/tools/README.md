# Tool ownership

Use the root `Makefile` for everyday matching development. Direct script paths
remain usable from other working directories; Python tools can also be invoked
as modules from the repository root, for example
`python3 -m matching2.tools.matching.progress`.

| Directory | Responsibility | Examples |
| --- | --- | --- |
| `matching/` | Current exact builds, packaging, compiler experiments and progress | `build_msvc.py`, `build_asm_text.py`, `pack_asm_pe.py`, `ltcg_semantic.py`, `progress.py` |
| `common/` | Imported helpers; no build or migration entry points | PE/COFF reading, COFF normalization, logged commands, Wine paths |
| `runtime/` | Experimental modern-runtime reports, fidelity checks and trace diagnostics | `coverage_report.py`, `retail_bounded_probe.sh`, `compare_runtime_trace.py` |
| `reference/` | Read and audit disassembly/reference evidence | `ida_export.py`, `asm_coverage.py` |
| `maintenance/` | Explicit source migration, historical recovery and the small assembly proof | `generate_msvc_project.py`, `generate_asm_text.py`, `recover_matches.py`, `build_asm_proof.py` |

The main MSVC build imports reusable helpers from `common/` and current
packaging/progress code from `matching/`. It does not import maintenance
scripts. The stricter LTCG PE/MAP parser remains inside its specialized tool:
its section model and validation contract differ from the common PE reader.

Maintenance generators can overwrite maintained source when explicitly invoked
with `--replace`; they are never part of a normal build. Historical recipes in
evidence files describe their original checkout, while current guides and shell
entry points use these paths.

`compare_obj.py` is an exploratory comparison that masks unresolved relocation
fields. Its result is not an exact-match acceptance check; use `make verify`.
