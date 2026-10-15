# Touhou 10 matching decompilation

The goal is readable C++ that compiles to a byte-exact `th10.exe`.
Development happens on `main`. Every game region is recovered C++; the default
build contains no inline assembly. 72.7% of the bytes are byte-exact; the rest
are *equivalent recoveries* (below), which `make EXACT=1` swaps back to their
retail assembly to produce the bit-identical executable.

```sh
make             # Compile what changed; exact everywhere except equivalent regions, built from C++
make EXACT=1     # The same with equivalent regions from their assembly: the bit-identical executable
make rebuild     # The same, recompiling every unit from scratch
make progress    # Show C++ and remaining assembly counts
make abi-check   # Equivalent models must pass retail callees the same register arguments
make behavior-check  # abi-check plus the Unicorn differential tests (see below)
```

## Validating the default build

The instruction comparison for equivalent recoveries is a structural check, not
proof of gameplay equivalence. Every runtime failure found so far sat at a seam
between a C++ model and the unchanged retail code around it: a helper called
with the wrong register convention (item update, projectile command Tick), a
missing `ret 4` (manager teardown), extraction that cut instructions or a jump
table (options refresh, hint save, replay submenu). See
[the investigation](matching2/reference/recovery_notes/equivalent_runtime_failures_2026_10_14.md).
Three checks now cover that:

* `make abi-check` (`matching2/tools/matching/callsite_abi.py`, needs
  `capstone`) pairs each model's calls into retail code with retail's and
  compares where every register argument comes from. Cases reviewed by hand as
  passing the same value are listed with their reason in
  `callsite_abi_reviewed.json`.
* `make behavior-check` also runs two Unicorn differential tests that execute
  the installed item update and replay submenu bodies against the real retail
  collaborators:

  ```sh
  python3 -m venv matching2/build/behavior-venv
  matching2/build/behavior-venv/bin/pip install unicorn==2.1.4
  make behavior-check BEHAVIOR_PYTHON=matching2/build/behavior-venv/bin/python
  ```

* `matching2/tests/replay_sync/` plays a replay in retail and in the build under
  the same Wine install and compares score, lives, power, stage, the gameplay
  RNG and the player block every frame. On 2026-10-14 three full replays were
  identical to retail for every frame: Normal all clear (86,200 frames), Easy
  all clear (48,428, where retail and the build both fault at the same frame)
  and Extra clear (43,353). Under this Wine setup retail itself drifts from the
  recordings late in those runs, so the build is compared with retail's trace.

## Equivalent recoveries

Some functions have C++ accepted with recorded instruction differences,
including compiler choices such as which of two registers is encoded as base
and which as index. These are called *equivalent recoveries*:
`equivalent_recoveries` in `matching2/msvc/build_support/regions.json` names
a layout under `build_support/layout/equivalent/` for the maintained C++ in
the corresponding retail folder under `matching2/msvc/src/`. Exact-only
counterparts live under `build_support/exact/`. Every `make` first links the whole image from
exact sources (the region's inline assembly included) and requires the retail
`.text` hash, then compiles the C++, relocates it to the region's address, and
compares it with the exact bytes instruction by instruction. The executable
`make` produces contains the C++ build of these regions; `make EXACT=1` keeps
the assembly and produces the bit-identical image. Base/index swaps are accepted
by rule and counted; every other difference must be listed verbatim in the
layout with a reviewed class, and any drift fails the build. Listing a
difference does not make it acceptable: whatever the layout records, the build
fails when the C++ calls a function or names an image address that retail does
not (or the reverse), when a difference swaps one callee for another, when a
difference of a tie-break class changes calls or branches, or when the
differences exceed their budget (structural classes, `block-order`,
`branch-target` and `code-shape`, over an eighth of the region's instructions;
all classes over a third). A model outside those limits is a draft: its layout
stays under `build_support/layout/equivalent/` without an `equivalent_recoveries` entry, it is
not built into the executable and not counted, and
`python3 matching2/tools/matching/equivalence.py --layout build_support/layout/equivalent/<name>.json`
prints its differences and what keeps it out. The gate does not prove that a
call site loads the registers its callee expects, so a model's link context
must carry the callee bodies that give retail's private conventions;
`make abi-check` catches the cases where it does not. Progress reports
them on their own line and gives the byte-exact share separately.
`python3 matching2/tools/matching/equivalence.py --record` prints the current
differences when preparing a layout.

The build is incremental by default. Each compiled unit is kept in a
content-addressed cache under `matching2/build/msvc/cache/`, keyed by the
build tools, the toolkit binaries, the compiler flags, the unit's manifest
entries and cluster layout, and the contents of its sources and every project
header they include. An unchanged unit is reused; anything else is recompiled.
The link and the whole-image comparison always run, so an incremental build
proves exactly what a full one does. A build with nothing to recompile takes a
few seconds; editing any script under `matching2/tools/` invalidates the whole
cache. `make rebuild` (or `make MSVC_ARGS=--no-cache`) ignores the cache, and
deleting the cache directory is always safe.

Requires Python 3.10+, Wine, MSVC 13.10.6030 with LINK 7.10.6030, GNU
x86 PE binutils (`i686-w64-mingw32-ld`), and the pinned GCC, Clang, and
LLVM-MC binaries required by the selected optional compiler profiles. The
default MSVC toolkit directory is `~/.local/share/th10-toolchains/msvc-13.10.6030/`,
containing `bin/`, `include/`, and `lib/`. Override it with
`make MSVC_ARGS='--toolkit /path/to/toolkit'`.
Run `./matching2/build_msvc.sh --help` for build options.

The output is `matching2/build/msvc/th10.exe`. Every build, incremental or
not, checks all bytes; `make verify` is an alias for the same build. To compare directly with a retail
copy and get detailed mismatch diagnostics, use
`make MSVC_ARGS='--verify /path/to/th10.exe'`.

`matching2/tools/matching/probe.py` gives the same byte gate for one
translation unit, which is how a single function is recovered and checked
before running `make`:

```sh
python3 matching2/tools/matching/probe.py --source src/game/score.cpp
```

It compiles the unit through the build's own compile path, requires every region
the unit owns to equal the retail bytes, and checks that each linker-filled field
resolves to the address retail points it at. A converted function replaces its
`__declspec(naked)` body and changes the region's `symbol` to the name its
selected compiler emits; `--proposal` applies a candidate region list before
the comparison.

`regions.json` identifies the authoritative source for each address. A second
naked body in a non-owning source does not contribute to the executable; remove
such duplicates rather than treating their presence as an unrecovered region.

`regions.json` selects per-source GCC/LLVM-COFF or Clang/LLVM-COFF profiles
under `source_compilers` when MSVC cannot express a recovered register ABI.
Each profile pins its compiler and assembler binaries; the build assembles
the compiler's output unchanged and applies the same exact-byte gate.

The statically linked C/C++ runtime is not transcribed. A `library` region
names a whole section of a member of the toolkit's own `libcmt.lib`,
`libcpmt.lib`, `libc.lib` or `libcp.lib` (translation unit
`lib/<library>/<member>`), and the build links that section at its retail
address, as the original linker did. `matching2/tools/waves/adopt_crt_library.py`
finds sections equal to retail outside their relocation fields, derives each
relocation target's address into the manifest symbol table, and replaces the
assembly transcription. See the
[runtime library note](matching2/reference/recovery_notes/runtime_library_sections_2026-09-28.md).

Caller/callee pairs with private LTCG register conventions can now be recovered
together. A schema-2 LTCG manifest compiles each real source with `/GL`, links
them in one native `/LTCG` scope, retains explicitly rooted callers, checks the
internal calls, and selects every complete function without rewriting bytes.
The worker shutdown cluster is the first example; probing any member checks
the whole batch. See the
[whole-program LTCG experiment and pipeline](matching2/reference/whole_program_ltcg.md).

```sh
make ltcg-proof  # After make, or with LTCG_ARGS='--oracle /path/to/retail.exe'
```

This reproduces exact separate-source and combined-source builds, five controls
that retain the public ABI, and a fresh-build repeat. It records commands,
toolchain hashes, native PE/MAP files, disassembly, and byte comparisons.

- `matching2/msvc/src/` and `include/`: maintained implementations and types,
  organized by ZUN's retail files; see [the source map](matching2/msvc/src/README.md).
- `matching2/msvc/build_support/`: placement manifests, private compiler units,
  exact-only counterparts, ABI contexts, import thunks and embedded data.
  See [the build-support guide](matching2/msvc/build_support/README.md).
- `matching2/reference/data/`: preserved non-code executable bytes.
- `matching2/reference/legacy_semantic/`: archived runtime-oriented C++ models
  for reverse-engineering reference; they are not exact-build inputs.
- `matching2/tools/`: compiler, linker, byte verification, and progress tools.
- `ida/`: original IDA disassembly and decompiler output.
- `decompiled/ghidra_augmented/`: supplementary disassembly, pseudocode, and
  address index (`index.tsv`). `ghidra_alternates/` preserves four alternate
  function boundaries.

Replace assembly with readable C++ while preserving the existing byte hashes.
The normal build uses maintained sources and data; it does not read a retail EXE
or the disassembly references.
