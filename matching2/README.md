# TH10 C++ reconstruction

This project reconstructs Touhou 10 game logic as readable C++ and compares
its behavior with the supported retail executable. The current deliverable is
an experimental PE32 runtime with focused tests and bounded retail comparisons.
Full-game correctness and visual equivalence have not been established.

The [audit handoff](docs/audit/README.md) contains the frozen baseline, complete
address/file inventory, validation evidence, and independent-review packets.

## Scope and rules

- Reconstruct executable behavior in C++. Do not use naked functions, inline
  assembly, copied instruction blobs, or calls into the retail executable as
  implementations. Calling conventions and explicit retail object offsets are
  acceptable where required by the recovered ABI. The build audit rejects common
  naked-function and inline-assembly syntax in production sources and headers.
- Keep platform adapters and incomplete gameplay behavior explicit. An operation
  known to be unimplemented must not report successful execution. The extended
  ECL dispatcher still needs an audit of its unclassified default cases.
- Treat source recovery, build integration, and behavioral fidelity as separate
  evidence. A source annotation, successful link, or deterministic self-comparison
  does not prove equivalence to retail.
- Prefer work that closes a demonstrated runtime divergence. Track the compared
  fields, scenario, duration, and remaining differences instead of claiming a
  percentage of the game is complete.

## Build and validate

From this directory:

```bash
./build_all_pe32.sh
./test.sh
./run_all_pe32.sh --smoke
```

The build uses a PE32 MinGW C++17 toolchain; tests need g++, Python 3, and i386
multilib support. Wine runs the executable. Configure the compiler with
`TH10_PE32_CXX` or `LLVM_MINGW_ROOT`; see the build script for other tool overrides.

**The build still requires the retail executable.** It embeds `.rdata` and
`.data` from `th10.exe` and supplies reconstructed C++ code. It does not import
retail `.text` instructions. The runtime also uses `th10.dat` and `thbgm.dat`.
Defaults point to `$HOME/Games/TH10 - Mountain of Faith`; override `TH10_GAME_DIR`
and, for the build's executable input, `TH10_RETAIL_EXE`.

`build_pe32.sh` delegates to the all-source build. The old `build.sh`, `run.sh`,
and `tools/build_hybrid.py` are legacy byte-overlay tools, outside the current
reconstruction acceptance path. A hybrid executable cannot demonstrate that
reconstructed code implements the game.

A smoke pass checks its bounded host scenario. Verify live rendering separately;
a pass with zero sprite draws provides no visual evidence. See
[RUNTIME_FIDELITY_STATUS.md](RUNTIME_FIDELITY_STATUS.md) for current boundaries
and [the retail probe workflow](docs/retail_trace_probe.md) for comparisons.

## Progress evidence

```bash
python3 tools/coverage_report.py --check
python3 tools/function_registry.py --check
python3 tools/standalone_readiness.py --check
```

These commands check reproducible source reports, not a fresh runtime execution.
The coverage inventory combines Ghidra functions with historical overlay
addresses. Historical membership never establishes an implementation. `semantic`
is a source-annotation classification, subject to explicit partial overrides;
it is not a claim of exhaustive behavioral parity. Missing provenance remains
unrecovered until reviewed. Byte weights cover tracked functions with known sizes,
not the entire executable.

The readiness report describes a conservative startup/title call closure. Its
indirect-site audit and source classifications are static evidence. Build and
smoke outcomes are marked unmeasured by this generator; retail-data independence
is explicitly false. No generated completion claim substitutes for fresh checks.

## Next milestones

1. Audit extended ECL dispatch defaults and remaining success-shaped placeholders;
   reconstruct reachable operations or stop with the opcode and missing dependency.
2. Close enemy-motion/lifetime differences with bounded retail comparisons, then
   expand beyond the current stage/script coverage.
3. Recover player collision/respawn and attached-effect ownership/callback behavior.
4. Validate live rendering and text layout against retail captures.
5. Replace imported retail data with documented, typed definitions if a build
   independent of `th10.exe` is pursued. Retail game assets remain a separate input.

Sources are organized under `src/` and `include/th10/` by subsystem. The
`standalone/` directory supplies platform and runtime integration, `tests/`
contains focused harnesses, and `tools/` contains reports and trace comparison.
Raw decompiler/disassembly references live outside this directory and are evidence,
not production build inputs.

Earlier recovery narratives are preserved as [historical notes](docs/recovery_history.md)
and [historical runtime observations](docs/runtime_fidelity_history.md). Their
completion claims are superseded by this scope and the current source reports.
