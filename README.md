# Touhou 10 matching decompilation

The goal is readable C++ that compiles to a byte-exact `th10.exe`.
Development happens on `main`. The project currently combines recovered C++
with inline assembly that still needs to be replaced.

```sh
make             # Compile and require exact .text and whole-executable hashes
make progress    # Show C++ and remaining assembly counts
```

Requires Python 3.10+, Wine, MSVC 13.10.6030 with LINK 7.10.6030, and GNU
x86 PE binutils (`i686-w64-mingw32-ld`). The default MSVC toolkit directory is
`~/.local/share/th10-toolchains/msvc-13.10.6030/`, containing `bin/`, `include/`,
and `lib/`. Override it with `make MSVC_ARGS='--toolkit /path/to/toolkit'`.
Run `./matching2/build_msvc.sh --help` for build options.

The output is `matching2/build/msvc/th10.exe`. Every build checks all bytes;
`make verify` is an alias for the same build. To compare directly with a retail
copy and get detailed mismatch diagnostics, use
`make MSVC_ARGS='--verify /path/to/th10.exe'`.

`matching2/tools/matching/probe.py` gives the same byte gate for one
translation unit in about a second, which is how a single function is recovered
and checked without a full rebuild:

```sh
python3 matching2/tools/matching/probe.py --source src/game/score.cpp
```

It compiles the unit through the build's own compile path, requires every region
the unit owns to equal the retail bytes, and checks that each linker-filled field
resolves to the address retail points it at. A converted function replaces its
`__declspec(naked)` body and changes the region's `symbol` to the name MSVC emits;
`--proposal` applies a candidate region list before the comparison.

- `matching2/msvc/src/` and `include/`: matching implementations and types.
- `matching2/msvc/regions.json` and `layout/`: code placement and compiler settings.
- `matching2/msvc/pe_layout.json` and `matching2/reference/data/`: executable
  layout and preserved non-code bytes.
- `matching2/tools/`: compiler, linker, byte verification, and progress tools.
- `ida/`: original IDA disassembly and decompiler output.
- `decompiled/ghidra_augmented/`: supplementary disassembly, pseudocode, and
  address index (`index.tsv`). `ghidra_alternates/` preserves four alternate
  function boundaries.

Replace assembly with readable C++ while preserving the existing byte hashes.
The normal build uses maintained sources and data; it does not read a retail EXE
or the disassembly references.
