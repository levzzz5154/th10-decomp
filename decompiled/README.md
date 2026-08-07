# Decompiled reference corpus

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
