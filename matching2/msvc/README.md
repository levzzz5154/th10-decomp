# Primary matching C++ project

This is the maintained source for readable C++ that recompiles byte-for-byte.
Follow the [contribution workflow](../../CONTRIBUTING.md). From the repository
root, `make verify` runs the matching-tool tests and this build. Existing inline
assembly is scaffolding to replace with ordinary C++.

This project compiles every executable instruction from `.cpp` files with MSVC
**13.10.6030**. The result must match all **487,936 bytes** of the supported
`th10.exe`. Normal builds do not read the original executable, assembly sources,
or prebuilt objects.

```bash
./matching2/build_msvc.sh
# Optional direct comparison:
./matching2/build_msvc.sh --verify "/path/to/retail/th10.exe"
```

The build uses Wine, the compiler at
`~/.local/share/th10-toolchains/msvc-13.10.6030`, and GNU x86 PE binutils.
`--toolkit`, `--project`, `--output`, and `--jobs` override defaults. Outputs are
in `matching2/build/msvc/`, including `th10.exe`, `port-report.json`, compiler
logs, COFF objects, the linker script and map. This is a Linux build pipeline;
a native Visual Studio solution is not supplied.

## Source organization

- `src/game`, `render`, `script`, `app`, `archive`, `math`, `platform`, and `util`
  group recovered functions by their known subsystem and source ownership.
- `src/unidentified` holds bodies whose source ownership is still unknown.
  A file may represent a physical fragment of a function with shared or
  noncontiguous code; the address does not imply a recovered function boundary.
- `src/data` contains initialized C++ arrays for embedded data and padding.
- `include/th10` contains recovered types and layouts. `asm_symbols.hpp` names
  fixed address targets; `asm_encoding.hpp` preserves unusual instruction forms
  that MSVC's inline assembler otherwise rewrites.
- `regions.json` records every selected compiler symbol, address, extent,
  relocation binding, and source file. `layout/function_ownership.json` records
  naming and ownership evidence.
- `../reference/data` and `pe_layout.json` preserve non-code PE data, resources, and metadata.
  The DOS instructions and message compile from `src/platform/dos_stub.cpp`.

The [generated progress report](PROGRESS.md) counts ordinary C++ regions and bytes,
including historical recovered functions and `FrameCounterPair::AtInterval`. These definitions
live alongside their subsystem's remaining inline-assembly bodies. Remaining
executable code uses named naked functions with MSVC `__asm` instructions.
This is complete compiler-input coverage, with readable C++ recovery still ongoing.
The separate modern runtime remains under `matching2/src`.

See [resource-file lifetime recovery](RESOURCE_LIFETIME.md) for the loader and
destructor's ABI evidence, preserved failure behavior, tests, and remaining
assembly dependencies.

See [keyboard input recovery](KEYBOARD_INPUT.md) for the refresh/normalization
contract, register evidence, DirectInput boundary, and stack-cookie requirement.

See [playfield boundary recovery](PLAYFIELD_BOUNDS.md) for the point layout,
inclusive edge contract, x87 unordered behavior, and adjacent compiler limits.

## Replacing inline assembly with ordinary C++

Edit the appropriate subsystem source and its matching `regions.json` record.
Preserve the verified ABI and object layouts; use C++98 syntax for this compiler.
Supply the exact decorated symbol, address, and compiler section extent.
Declare callees/globals and record verified external targets in `symbols`.
Definitions already selected from compiler output resolve through the linker.

A translation unit may emit multiple functions. The COFF normalizer selects
whole function/data sections and adjusts section/symbol metadata for fixed
placement. It preserves instruction bytes and relocation offsets/types; the
linker resolves operands. Link assertions check each slot and symbol, followed
by strict hashes of all 412,672 `.text` bytes and the whole executable.
A mismatch fails the build and removes stale success outputs. There are no
relocation masks, original-code substitutions, or assembly fallbacks.

For a linked byte mismatch, the error identifies the first affected region,
source and symbol, then shows expected/actual bytes and the containing
instructions (using GNU objdump when available). Run `make reference` once to
provide the assembly baseline for these diagnostics, or supply `--verify`.
The diagnostic reference must pass the recorded `.text` hash; it is read only
after a failed byte gate and is never substituted into the output. Data and
padding mismatches show bytes without interpreting them as instructions.

`tools/maintenance/generate_msvc_project.py` is a one-time migration utility, outside the
normal build. Its `--replace` option overwrites generated source files, so
ordinary recovery work should edit the existing project directly.
