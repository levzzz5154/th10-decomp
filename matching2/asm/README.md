# Assembly baseline

## Goal

Build the supported `th10.exe` byte-for-byte from assembled instructions and
versioned data/resources, without using the retail executable as a source of
code bytes during the build. Preserve the historical 397 comparisons and
replace assembly regions with matching C++ incrementally.

## Full assembly build

From the repository root:

```bash
./matching2/build_asm.sh
# Optional direct comparison with the original:
./matching2/build_asm.sh --verify "/path/to/retail/th10.exe"
```

Requires Python 3, GNU `i686-w64-mingw32-as`,
`i686-w64-mingw32-ld`, and `objcopy`. Ordinary builds use the versioned
`text/` assembly, DOS stub, PE layout, and non-code assets in `data/`.
They do not require Wine, MSVC, Ghidra, a decoder package, or the original EXE.

The output is `matching2/build/asm-baseline/full/th10.exe`. The assembler emits
x86 COFF; GNU ld resolves symbolic references at the original addresses.
The packer constructs the PE headers and inserts the assembled `.text` and
versioned data/resources. It never repairs instruction bytes. Both the entire
412,672-byte `.text` and the 487,936-byte executable must pass their recorded
SHA-256 gates, with no relocation masks. See [PE packaging](PE_PACKAGING.md).

The completed baseline contains 117,397 instructions (385,517 bytes),
11,267 bytes of embedded data, and 15,888 bytes of padding. The whole output
was compared directly with retail and rebuilt without the verification input;
both builds produced SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
A `strace -f -e trace=%file` run confirmed no retail-directory access during
the ordinary build. The assembly/coverage/packaging/pipeline suite passed
19 tests, including malformed-input and incorrect-boundary rejection.

`text/manifest.json` records instruction/data/padding counts, source hashes,
reference provenance, and address aliases. Build logs and the linked-text
verification report are in `matching2/build/asm-baseline/full/`.

## Regenerating the source

Regeneration is a development operation that reads the authenticated retail
file and the saved listings; it is separate from ordinary builds. It requires
`iced-x86` in the selected Python environment:

```bash
python3 matching2/tools/generate_asm_text.py \
  --recovery matching2/asm/text_code_recovery.json \
  --recovery matching2/asm/text_data_recovery.json \
  --recovery matching2/asm/text_small_code_recovery.json \
  --recovery matching2/asm/text_code_edges.json --replace
```

The base classification and recovery overlays must cover every byte without
unknown ranges or overlaps. Boundary corrections explicitly retire incorrect
export rows before adding replacement instructions; their evidence remains in
`text_code_edges.json`. A failed regeneration marks the source tree incomplete
and prevents a build from accidentally accepting stale generated files.

Physical source chunks preserve addresses; they do not reconstruct original
C++ classes or translation units. The [MSVC C++ project](../msvc/README.md)
now compiles the complete executable code from C++ sources, using ordinary C++
for 34 recovered functions and inline assembly for other bodies. This retains
the whole-file gate; this directory remains the complete assembly reference.

## Original coverage audit

```bash
python3 matching2/tools/asm_coverage.py
```

The audit compares the saved and augmented Ghidra exports with the authenticated
retail file and partitions every byte of `0x00401000..0x00465BFF`:

| Classification | Bytes |
| --- | ---: |
| Instruction evidence without classification conflict | 335,754 |
| Defined data | 4,372 |
| Undefined / possible padding | 51,981 |
| Disagreement between listing evidence | 19,383 |
| Overlapping listing evidence | 1,182 |
| **Total** | **412,672** |

There are no missing `.text` byte ranges or byte-validation errors. However,
the initial audit identified 72,546 bytes for classification review.
The versioned classification and recovery overlays record the subsequent review. A run of `CC`
or zero bytes is only a padding candidate, not proof of padding. Disagreement
here concerns analysis classifications, not different underlying byte values.

`matching2/build/asm-baseline/text_range_map.json` contains the complete range
partition, provenance, and validation results. `text_ranges.tsv` provides a
tabular view; `summary.json` records counts. Function-body coverage is reported
separately from the listing partition to avoid treating function discovery as
complete merely because all byte values are available.

Use the live `th10` Ghidra project as an additional analysis source when
reviewing those classifications. The current project has 1,383 functions,
distinct from both exports. For example, it associates `0x004436C0` and
`0x00443910` with the body of `FUN_004451c0` and records jumps to them from
`0x00445203` and `0x00445263`. Those references help explain the two overlap
regions; they should not automatically become separate function definitions.
Some large undefined export ranges also remain undefined in the live project.
Record references and body ranges when resolving ambiguities, and continue
using retail bytes as the final encoding oracle. Do not silently replace
uncertain boundaries merely because one analysis version assigned a function.

## Earlier MSVC linking proof

From the repository root:

```bash
python3 matching2/tools/build_asm_proof.py
```

Requires `i686-w64-mingw32-as`, Wine, and the installed
`~/.local/share/th10-toolchains/msvc-13.10.6030` toolkit. Use `--assembler`,
`--toolkit`, `--exe`, or `--output` to override paths.

The command assembles the versioned sources in `proof/` into x86 COFF objects,
links them with Microsoft's 7.10.6030 linker, compares the named regions with
the authenticated retail executable, and runs a separate test harness.
Retail is only a verification input; neither assembler nor linker reads it.
Outputs are in `matching2/build/asm-baseline/proof/`.

| Region | Address | Verified bytes |
| --- | --- | ---: |
| Entity destructor | `0x00401FF0` | 34 |
| Frame-counter interval | `0x00427C70` | 29 |

All 63 bytes match, with **no relocation masks**. The destructor's call to
`0x00452422` is resolved across two object files and its target is checked.
The function start/end symbols must equal the reference extents.

The runtime harness checks interval true/false cases, callee stack cleanup,
and the destructor's null path. The unrecovered `free` target has an `INT3`
guard, not an implementation, and is never executed. Other `.text` gaps also
contain synthetic `INT3` fill. Only the two named regions count as matches.

The linker emits a current timestamp; the command normalizes that one PE
header field to the reference timestamp for reproducibility. It never patches
linked instruction bytes. Repeated builds produced the same whole proof file.
The verifier also rejected a deliberately changed call operand and end symbol.

## Assembly and linking rules

- Use GNU assembler Intel syntax, `.code32`, and x86 COFF objects. The proof
  uses `{load}` on register-register instructions where the default equivalent
  encoding would differ from retail.
- Name addressable retail locations `_th10_XXXXXXXX`, using lowercase hex.
  Keep local branch labels local and record each region's original address,
  byte length, and reference listing in a manifest.
- Use symbolic calls and data references. Define unrecovered anchors in a
  section at their intended address. An absolute COFF symbol was insufficient:
  the MSVC proof linker added the image base when resolving the test's relative call.
- Keep layout directives separate from function bodies. Explicit slots make
  size drift fail assembly or verification instead of moving later functions.
  The proof controls `.text` contribution order through its link input order.
- Record unconverted gaps separately. Fill bytes that happen to equal retail
  are not recovered code. Do not use `incbin` or extract retail `.text` into
  the linked image.
- Assembly data directives are appropriate for identified data and padding.
  Unknown bytes remain unresolved until instruction/data boundaries have
  evidence; do not silently turn them into purported instructions.
- Compare final linked bytes and symbol extents. Never mask relocation fields
  in the assembly baseline's acceptance gate.

The recovered historical build remains available through
`python3 matching2/tools/recover_matches.py`. Its 397 results mix C++ and inline
assembly and include masked comparisons; they do not replace the stricter
linked-byte gate described here.
