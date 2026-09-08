# Touhou 10 matching decompilation

The goal is readable C++ that recompiles to the exact bytes of the supported
`th10.exe`. The maintained matching source is **`matching2/msvc/`**, using MSVC
**13.10.6030**. Each recovered function must preserve whole-file byte equality.

The separate [assembly baseline](matching2/asm/README.md) rebuilds the supported
original executable byte-for-byte: run `./matching2/build_asm.sh` to produce
`matching2/build/asm-baseline/full/th10.exe`. It assembles versioned instructions
and packages preserved data/resources without reading the retail EXE.

The [MSVC project](matching2/msvc/README.md) contains recovered ordinary C++
alongside inline assembly; [current counts](matching2/msvc/PROGRESS.md) are
generated from its manifest. Run `make progress` for live counts. Assembly is
scaffolding to replace, not completed C++ recovery. Preserved data and PE
metadata also remain build inputs.

## Build and verify

```bash
make build       # Compile the matching project and require exact output hashes
make test        # Test the byte-matching verification tools
make verify      # Run those tests, then rebuild and require exact output hashes
```

Requires Python 3, Wine, MSVC 13.10.6030, and GNU x86 PE binutils; see
[build options](matching2/msvc/README.md). Output goes to `matching2/build/msvc/`.
For direct retail comparison, use
`make build MSVC_ARGS='--verify "/path/to/retail/th10.exe"'`.
Read the [contribution workflow](CONTRIBUTING.md) before recovering a function.
`make help` lists secondary reference and runtime commands.

## Repository map

| Path | Purpose |
| --- | --- |
| `matching2/msvc/src/`, `matching2/msvc/include/` | Primary maintained matching implementations and types; edit these for C++ recovery |
| `matching2/msvc/regions.json`, `matching2/msvc/layout/` | Placement, classification and ownership evidence; update with source changes |
| `matching2/reference/data/` | Shared authenticated non-code inputs for both exact builds |
| `matching2/msvc/pe_layout.json`, `matching2/asm/pe_layout.json` | PE packaging layouts using the shared reference data |
| `matching2/src/`, `matching2/include/`, `matching2/standalone/` | Secondary experimental runtime and behavioral research; see the [runtime guide](matching2/docs/runtime_development.md) |
| `matching2/tests/` | Focused host tests and their source dependencies |
| `matching2/tools/` | [Tools grouped by purpose](matching2/tools/README.md): matching, runtime, reference, maintenance, and common libraries |
| `matching2/data/` | Historical address inventory used by source reports |
| `matching2/asm/` | Complete byte-exact assembly baseline, layout and data/resources |
| `ida/`, `decompiled/` | Original disassembly, decompiler exports and reference provenance |
| `ghidra/`, `tools/` | Reference export and integrity tools |
| `matching2/docs/` | Subsystem evidence, naming decisions and the retail probe workflow |
| `matching2/build/` | Ignored generated executables, objects, logs and reports; never maintained source |

Start reference lookup with the [address index](decompiled/reference_coverage/README.md).
Original IDA exports have missing bodies; the index distinguishes those gaps
from supplementary Ghidra analysis.

Existing directory names preserve script paths and evidence links. The modern
runtime is experimental; its [status](matching2/RUNTIME_FIDELITY_STATUS.md)
does not establish matching C++ completion.

Obsolete hybrid builds, frozen review packets, and superseded recovery reports
have been removed. Their history is available in Git.
