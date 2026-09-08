# TH10 C++ reconstruction

Reconstruct `th10.exe` behavior from disassembly and compare the result with
retail. A successful build or host test is not evidence of full-game correctness.
See [runtime status](RUNTIME_FIDELITY_STATUS.md) for the unresolved behavior.
[Byte-matching evidence](docs/byte_matching.md) records the existing MSVC recipe,
the installed 6030 toolchain, and historical match recovery.

## Build and validate

From this directory:

```bash
./build.sh              # Compile all production sources into a PE32 executable
./test.sh               # Check source/reference integrity, then run host tests
./run.sh --smoke        # Run the bounded integration scenario under Wine
./run.sh                # Run interactively
```

The build requires a PE32 MinGW C++17 toolchain. Tests require g++, Python 3,
and i386 multilib support. Configure the host compiler with `CXX`; the same
compiler is used for the 32-bit tests. Wine runs the executable.

Set `TH10_GAME_DIR` to the retail game directory (default:
`$HOME/Games/TH10 - Mountain of Faith`). The build requires `th10.exe` and
embeds its `.rdata` and `.data`; it does not copy retail `.text` instructions.
Execution requires `th10.dat` and `thbgm.dat`.

Override the executable input with `TH10_RETAIL_EXE`. Toolchain overrides are
`TH10_PE32_CXX`, `TH10_PE32_CC`, `TH10_PE32_NM`, `TH10_PE32_WINDRES`, and
`LLVM_MINGW_ROOT`; see [build.sh](build.sh) for resolution order.
The output is `build/all-pe32/th10_all_sources.exe`. `run.sh` builds it when
missing; run `build.sh` explicitly after editing sources.

## Recover historical byte matches

```bash
python3 tools/recover_matches.py
```

This rebuilds the 397 historical entries with MSVC 13.10.6030 under Wine.
The pinned source snapshot, objects, compiler logs, and `report.json` go to
`build/recovered-matches/`. The command adapts two ECL callback typedefs and
four integer constants to C++98 in that generated snapshot. It preserves
historical assembly implementations for comparison. This is a separate
recovery baseline; it does not replace current production sources or produce
an independently linked executable. See the report for excluded relocation
bytes and agreement with saved Ghidra function boundaries.

Use `--toolkit`, `--exe`, and `--output` to override local paths.

The separate [assembly baseline](asm/README.md) rebuilds the entire supported
487,936-byte executable exactly. Run `./build_asm.sh`; the output is
`build/asm-baseline/full/th10.exe`. Its 117,397 instructions are assembled from
versioned source, with symbolic references and no relocation masks. Normal
builds do not read the retail executable. Data/resources and original PE
metadata are preserved. The [MSVC C++ project](msvc/README.md) now compiles all code from `.cpp` files, including 34 ordinary C++ functions
and inline assembly for the remaining bodies, under the same whole-file check. Run `./build_msvc.sh`;
its output is `build/msvc/th10.exe`.

## Development workflow

1. Locate the retail function in the [reference index](../decompiled/reference_coverage/README.md).
2. Change the subsystem implementation in `src/` and its layouts in `include/th10/`.
   Preserve address annotations so functions remain traceable to retail.
3. Run the relevant harness and the full `test.sh` suite. Harness source
   dependencies are listed in `tests/host_suites.sh`.
4. Build and compare a bounded runtime scenario using the
   [retail probe workflow](docs/retail_trace_probe.md). Record compared fields,
   duration, and remaining differences. Check live rendering separately.

`standalone/host_main.cpp` wires the platform and menus;
`standalone/host_stage.cpp` wires stage execution;
`standalone/host_trace.cpp` writes deterministic diagnostics independently of
platform setup. These adapters remain incomplete.

Known unimplemented operations must not report successful execution. Do not use
naked functions, inline assembly, copied instruction blobs, or calls into retail
code as implementations. Calling conventions and explicit object offsets are
appropriate where required by the recovered ABI.

## Source and reference checks

`./check.sh` runs source-report and original-reference integrity checks without
compiling the host tests or running the game. After changing source annotations,
regenerate the affected reports:

```bash
python3 tools/coverage_report.py --write
python3 tools/function_registry.py --write
python3 tools/standalone_readiness.py --write
python3 ../tools/audit_reference_corpus.py --write
./check.sh
```

`coverage.json` and `function_registry.json` are navigation and source-evidence
reports, not gameplay completion scores. Historical overlay membership comes
from `data/historical_overlays.json`, whose provenance names its original Git
revision; membership never establishes an implementation.
`standalone_readiness.json` describes a static startup/title call closure and
does not certify a fresh build, smoke pass, or independence from retail data.

The build also checks unresolved project symbols and the existing placeholder
and fidelity baselines. Passing those scans only establishes their configured
checks. A smoke with zero sprite draws provides no rendering evidence.
