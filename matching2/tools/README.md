# Matching & verification tools

Scripts under `matching2/tools/` fall into two groups: active build/verification tools used by the top-level `Makefile`, and historical recovery/migration scripts kept for reference.

## Active build & verification (`common/`, `matching/`)

| Path | Role |
| --- | --- |
| `matching/build_msvc.py` | Main build driver (`make`, `make EXACT=1`, `make rebuild`, `make verify-cpp`): plans units, runs MSVC/LTCG/GCC/Clang builds, links `.text`, verifies exact parity (and any active equivalent replacements), and packages `th10.exe`. |
| `matching/ltcg_cluster.py` | Validates and compiles native `/LTCG` clusters from `build_support/layout/ltcg/*.json`, verifying anchors, gaps, relocations and selected bytes. |
| `matching/probe.py` | Single-unit byte gate used during recovery and refactoring (`python3 matching2/tools/matching/probe.py --source src/...`). |
| `matching/equivalence.py` | Instruction-level verifier for equivalent C++ recoveries (`build_support/layout/equivalent/*.json`; 0 currently active). |
| `matching/callsite_abi.py` | `make abi-check` (requires `capstone`): checks that any active equivalent models pass retail callees their expected register arguments. |
| `matching/progress.py` | `make progress` and `make verify-cpp` region/byte reporting and inline-assembly audit. |
| `matching/unit_cache.py` | Content-addressed per-unit build cache (`matching2/build/msvc/cache/`). |
| `matching/_llvm_coff.py`, `gcc_llvm_backend.py`, `clang_llvm_backend.py` | Pinned GCC/Clang/LLVM-MC backends for the 9 optional-compiler sources in `regions.json`. |
| `matching/pack_asm_pe.py` | Packages the verified `.text` image with preserved non-code sections (`pe_layout.json`). |
| `matching/experiment_ltcg.py` | `make ltcg-proof`: reproduces positive/negative LTCG compiler controls. |
| `common/coff.py`, `coff_regions.py`, `library.py`, `pe.py`, `project_paths.py`, `wine.py` | Shared COFF/PE readers, region normalization, toolkit library extraction and Wine execution helpers. |

### Diagnostic & sweep helpers (`matching/`)

`byte_exact_survey.py`, `context_probe.py`, `diff_dump.py`, `else_swap_sweep.py`, `literal_sweep.py`, `ltcg_semantic.py`, `mismatch.py`, `param_order_sweep.py`, `predicate_sweep.py`, `psearch.py`, `retail.py`, and `variant.py` support targeted byte-matching investigations without modifying the default build.

### Unit tests

Run the tool unit tests with:

```sh
python3 -m unittest \
  matching2/tools/common/test_project_paths.py \
  matching2/tools/matching/test_equivalence.py \
  matching2/tools/matching/test_gcc_llvm_backend.py \
  matching2/tools/matching/test_ltcg_cluster.py \
  matching2/tools/matching/test_source_ownership.py
```

## Historical migration & scratch scripts (`waves/`, `scratch/`)

- `waves/`: batch recovery, CRT library adoption, cluster carving and promotion scripts from the multi-wave recovery campaign (see `waves/ROADMAP.md` and `waves/briefs/`). Not used during normal builds.
- `scratch/`: one-off diagnostic scripts (`diff_gfr.py`, `fix_gfr_gaps.py`).
