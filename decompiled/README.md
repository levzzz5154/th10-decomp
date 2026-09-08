# Decompiled reference corpus

For the complete available reference state, see
[reference coverage](reference_coverage/README.md). `ghidra_full/` exports all
saved database functions as C and addressed assembly. `ghidra_augmented/` adds
functions from a separate analysis seeded by IDA and reconstruction address claims. Both include full listings,
analysis-memory bytes, symbols, external declarations, memory maps and types.
The original IDA archive has collapsed/undecompiled bodies; the coverage index
keeps those limitations explicit.

`ghidra_raw/` contains one raw Ghidra pseudocode export for every game-code
address listed in `ghidra/tracking.csv`. These files are reference material,
not build inputs: Ghidra types, calling conventions, register parameters,
globals, and control flow must be corrected before code is promoted into the
subsystem-oriented `matching2/` tree.

Regenerate the corpus with:

```bash
./tools/export_ghidra.sh
```

`ghidra_raw/index.tsv` records successful exports and any addresses Ghidra could
not decompile as independent functions.
