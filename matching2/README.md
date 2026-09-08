# Matching development

The primary goal is byte-perfect recompilation of readable C++.
Edit `msvc/src/` and `msvc/include/`; see the
[matching project guide](msvc/README.md) and
[contribution workflow](../CONTRIBUTING.md).

From the repository root, run `make build`, `make test`, or `make verify`.
`build_msvc.sh` remains available for direct invocation and compiler options.

The [repository map](../README.md#repository-map) explains source ownership.
The [assembly baseline](asm/README.md) provides exact reference instructions.
The [modern runtime guide](docs/runtime_development.md) documents the secondary
`src/`, `include/`, and `standalone/` tree and its existing `build.sh`, `test.sh`,
`check.sh`, and `run.sh` commands.
