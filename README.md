# Touhou 10 matching decompilation

Readable C++ that compiles, with ZUN's own toolchain (MSVC 7.1, `/LTCG`), back
into a byte-exact `th10.exe`.

![Project status](docs/status.png)

Every game function is recovered as C++ and the default build contains no
inline assembly. 83.8% of the game code bytes are byte-exact C++ (99.3%
counting the identical instructions of the remaining functions). The rest are
*equivalent recoveries* (below): C++ that differs from retail only by recorded,
reviewed compiler choices. `make EXACT=1` swaps those back to their retail
assembly and produces the bit-identical executable. Development happens on
`main`; [HANDOFF.md](HANDOFF.md) is the current state and how to continue.

## Building

```sh
make             # Compile what changed; equivalent regions built from their C++
make EXACT=1     # The same with equivalent regions from assembly: the bit-identical executable
make rebuild     # The same, recompiling every unit from scratch
make progress    # Region and byte counts per kind, without building
make abi-check   # Equivalent models must pass retail callees the same register arguments
make behavior-check  # abi-check plus the Unicorn differential tests (see below)
make ltcg-proof  # After make, or with LTCG_ARGS='--oracle /path/to/retail.exe'
```

The output is `matching2/build/msvc/th10.exe`. Every build ends with a line
like

```
Recovered: 100.0% of bytes (322,064 of 322,064), 100.0% of regions (2,322 of 2,322); byte-exact alone 83.8% of bytes, 99.3% counting identical instructions of equivalent regions
```

The last share credits each equivalent region with its fraction of identical
instructions, weighted by region bytes, so it is an estimate. The runtime
library and padding are not game code and are not counted.

Requires Python 3.10+, Wine, MSVC 13.10.6030 with LINK 7.10.6030, GNU x86 PE
binutils (`i686-w64-mingw32-ld`), and the pinned GCC, Clang and LLVM-MC
binaries of the optional compiler profiles. The default MSVC toolkit directory
is `~/.local/share/th10-toolchains/msvc-13.10.6030/` (with `bin/`, `include/`
and `lib/`); override it with `make MSVC_ARGS='--toolkit /path/to/toolkit'`.
Run `./matching2/build_msvc.sh --help` for build options.

The normal build uses maintained sources and data only; it does not read a
retail EXE or the disassembly references. Every build, incremental or not,
checks all bytes (`make verify` is an alias). To compare with a retail copy and
get detailed mismatch diagnostics, use `make MSVC_ARGS='--verify /path/to/th10.exe'`.

The build is incremental. Each compiled unit is kept in a content-addressed
cache under `matching2/build/msvc/cache/`, keyed by the build tools, the
toolkit binaries, the compiler flags, the unit's manifest entries and cluster
layout, and the contents of its sources and every project header they include.
The link and the whole-image comparison always run, so an incremental build
proves exactly what a full one does; a build with nothing to recompile takes a
few seconds. Editing any script under `matching2/tools/` invalidates the whole
cache. `make rebuild` (or `make MSVC_ARGS=--no-cache`) ignores the cache, and
deleting the cache directory is always safe.

## How the code is placed

`matching2/msvc/build_support/regions.json` partitions `.text` into regions and
names the authoritative source of each address. A second naked body in a
non-owning source does not contribute to the executable; remove such
duplicates rather than treating them as unrecovered.

**Single units.** `matching2/tools/matching/probe.py` gives the build's byte
gate for one translation unit, which is how a function is recovered and
checked before running `make`:

```sh
python3 matching2/tools/matching/probe.py --source src/game/score.cpp
```

It compiles the unit through the build's own compile path, requires every
region the unit owns to equal the retail bytes, and checks that each
linker-filled field resolves to the address retail points it at. A converted
function replaces its `__declspec(naked)` body and changes the region's
`symbol` to the name its compiler emits; `--proposal` applies a candidate
region list before the comparison.

**LTCG clusters.** Retail was linked with whole-program optimisation, so many
functions use private register conventions chosen at link time. A cluster
manifest under `build_support/layout/ltcg/` compiles a function together with
its real callers and callees (*anchors*, placed at their retail addresses) in
one native `/LTCG` link, then selects the complete function bytes without
rewriting them. See the
[whole-program LTCG experiment and pipeline](matching2/reference/whole_program_ltcg.md).
`make ltcg-proof` reproduces exact separate-source and combined-source builds,
five controls that retain the public ABI and a fresh-build repeat, with
commands, toolchain hashes, native PE/MAP files, disassembly and byte
comparisons.

**Other compilers.** `source_compilers` in `regions.json` selects per-source
GCC/LLVM-COFF or Clang/LLVM-COFF profiles where MSVC cannot express a recovered
register ABI. Each profile pins its compiler and assembler; the build
assembles the compiler's output unchanged and applies the same byte gate.

**Runtime library.** The statically linked C/C++ runtime is not transcribed.
A `library` region names a whole section of a member of the toolkit's own
`libcmt.lib`, `libcpmt.lib`, `libc.lib` or `libcp.lib` (translation unit
`lib/<library>/<member>`), linked at its retail address as the original linker
did. `matching2/tools/waves/adopt_crt_library.py` finds such sections; see the
[runtime library note](matching2/reference/recovery_notes/runtime_library_sections_2026-09-28.md).

## Equivalent recoveries

Some functions have C++ accepted with recorded instruction differences, such
as which of two registers is encoded as base and which as index.
`equivalent_recoveries` in `regions.json` names a layout under
`build_support/layout/equivalent/` for the maintained C++ under
`matching2/msvc/src/`; the exact-only assembly lives under
`build_support/exact/`.

Every `make` first links the whole image from exact sources (the region's
assembly included) and requires the retail `.text` hash, then compiles the
C++, relocates it to the region's address and compares it with the exact bytes
instruction by instruction. Base/index swaps are accepted by rule and counted;
every other difference must be listed verbatim in the layout with a reviewed
class, and any drift fails the build. Listing a difference does not make it
acceptable: the build fails when the C++ calls a function or names an image
address that retail does not (or the reverse), when a difference swaps one
callee for another, when a difference of a tie-break class changes calls or
branches, or when the differences exceed their budget (structural classes —
`block-order`, `branch-target`, `code-shape` — over an eighth of the region's
instructions; all classes over a third).

A model outside those limits is a draft: its layout stays under
`build_support/layout/equivalent/` without an `equivalent_recoveries` entry and
is neither built nor counted.
`python3 matching2/tools/matching/equivalence.py --layout build_support/layout/equivalent/<name>.json`
prints its differences and what keeps it out; `--record` prints the current
differences when preparing a layout. The gate does not prove that a call site
loads the registers its callee expects, so a model's link context must carry
the callee bodies that give retail's private conventions; `make abi-check`
catches the cases where it does not.

An equivalent model with no recorded differences can still differ from retail
in its bytes, because the gate accepts a branch to an identical copy of the
same tail. Once the relocated model matches retail byte for byte, it is
promoted: an LTCG cluster selects it with the model's context as anchors, its
region becomes `semantic`, and the equivalent layout and assembly are removed.
See [the 0x0042E5A0 promotion](matching2/reference/recovery_notes/options_label_refresh_0042e5a0_exact_2026_10_16.md).

## Validating the default build

The instruction comparison is a structural check, not proof of gameplay
equivalence. Every runtime failure found so far sat at a seam between a C++
model and the retail code around it: a helper called with the wrong register
convention, a missing `ret 4`, extraction that cut instructions or a jump
table. See
[the investigation](matching2/reference/recovery_notes/equivalent_runtime_failures_2026_10_14.md).
Three checks cover that:

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

## Repository layout

- `matching2/msvc/src/` and `include/`: maintained implementations and types,
  organised by ZUN's retail files; see [the source map](matching2/msvc/src/README.md).
- `matching2/msvc/build_support/`: placement manifests, private compiler units,
  exact-only counterparts, ABI contexts, import thunks and embedded data; see
  [the build-support guide](matching2/msvc/build_support/README.md).
- `matching2/reference/recovery_notes/`: one note per recovered or parked
  region, with what moved it and what is left.
- `matching2/reference/compiler_traces/`: gdb tracers for c2.dll internals
  (register allocation, scheduling, flow graph, stack packing, operand order).
- `matching2/reference/data/`: preserved non-code executable bytes.
- `matching2/reference/legacy_semantic/`: archived runtime-oriented C++ models
  for reverse-engineering reference; not build inputs.
- `matching2/tools/`: compiler, linker, byte verification and progress tools.
- `ida/`: original IDA disassembly and decompiler output.
- `decompiled/ghidra_augmented/`: supplementary disassembly, pseudocode and
  address index (`index.tsv`); `ghidra_alternates/` preserves four alternate
  function boundaries.
- `docs/status.svg`: source of the status image (`rsvg-convert -z 2` renders
  `status.png`).
