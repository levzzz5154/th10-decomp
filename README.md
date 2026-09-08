# Touhou 10 executable reconstruction

Reverse engineering `th10.exe` and reconstructing its behavior in C++.
The runtime is experimental and does not yet establish working gameplay or
retail-equivalent graphics.

The separate [assembly baseline](matching2/asm/README.md) rebuilds the supported
original executable byte-for-byte: run `./matching2/build_asm.sh` to produce
`matching2/build/asm-baseline/full/th10.exe`. It assembles versioned instructions
and packages preserved data/resources without reading the retail EXE.

The [complete MSVC C++ project](matching2/msvc/README.md) compiles all code
from C++ files with MSVC 13.10.6030: 34 ordinary C++ functions and inline
assembly for the remaining bodies, under the same whole-file check. Build it with `./matching2/build_msvc.sh`.

## Build and run

```bash
./matching2/build.sh
./matching2/test.sh
./matching2/run.sh --smoke
```

Use `./matching2/run.sh` for interactive execution. See
[the project guide](matching2/README.md) for dependencies, environment overrides,
and the development workflow. [Runtime status](matching2/RUNTIME_FIDELITY_STATUS.md)
describes known gaps.

## Repository map

| Path | Purpose |
| --- | --- |
| `matching2/src/`, `matching2/include/` | Reconstructed functions and recovered layouts, grouped by subsystem |
| `matching2/standalone/` | Platform integration, runtime wiring and trace output |
| `matching2/tests/` | Focused host tests and their source dependencies |
| `matching2/tools/` | Current source reports and retail comparison tools |
| `matching2/data/` | Historical address inventory used by source reports |
| `matching2/asm/` | Complete byte-exact assembly baseline, layout and data/resources |
| `ida/`, `decompiled/` | Original disassembly, decompiler exports and reference provenance |
| `ghidra/`, `tools/` | Reference export and integrity tools |
| `matching2/docs/` | Subsystem evidence, naming decisions and the retail probe workflow |

Start reference lookup with the [address index](decompiled/reference_coverage/README.md).
Original IDA exports have missing bodies; the index distinguishes those gaps
from supplementary Ghidra analysis.

Obsolete hybrid builds, frozen review packets, and superseded recovery reports
have been removed. Their history is available in Git.
