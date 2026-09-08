# Byte matching: toolchain evidence and current limits

Verified on 2026-09-07 against the working tree based on `dcf2b50` and the
historical matching sources at `51ff01381fbd097e9310510e7aa494cb24787fb9`.
The project already had a function-matching workflow. Its results need to be
separated into C++ code generation, handwritten assembly, and unmatched bodies.

## Executable and compiler identity

The local supported `th10.exe` hashes to
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`, matching
`decompiled/reference_bytes_validation.json`. Its PE linker version is 7.10.
Its Rich header decodes successfully and its calculated checksum matches the
stored XOR key, `0x3152A748`.

Relevant decoded records:

| Product ID | Meaning | Build | Count |
| --- | --- | --- | --- |
| `0x005A` | Linker 7.10 | 6030 | 1 |
| `0x005F` | C compiler 13.10 | 6030 | 131 |
| `0x0060` | C++ compiler 13.10 | 6030 | 15 |
| `0x0064` | C++ compiler 13.10, LTCG | 6030 | 52 |

Product names follow the [Rich product-ID reference, appendix B, PDF page 149](https://mediatum.ub.tum.de/doc/1510236/1510236.pdf#page=149).
The header also contains older-build records, including 2067, 2179, 3052,
4035 and 9178. Counts are linker provenance records, not function coverage;
they do not identify which individual game functions used each tool.
The decoding/checksum method is described in [the original Rich-header analysis](https://www.ntcore.com/files/richsign.htm).

The original 3052 toolkit is at
`$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003`.
Running its tools under Wine reports:

- `cl.exe`: **13.10.3052**
- `link.exe`: **7.10.3052**
- `cl.exe` SHA-256: `9e45887874de83876ada2adc9943daa9094d1c1f1f9c3d93eac5ad57a1cbee2a`

The compiler family is established. The installed 3052 build is not the 6030
build recorded for retail's linker and many compiler contributions. Targeting
13.10.6030/7.10.6030 is a strong inference from the executable, not proof that
all linked code came from a single compiler installation.

Build **13.10.6030 / 7.10.6030** is now installed separately at
`$HOME/.local/share/th10-toolchains/msvc-13.10.6030`. Its `cl` and `link`
wrappers configure Wine include/library paths. The installation overlays SP1
files onto a copy of the original toolkit; `installation.json` records the
archive URL, SHA-256, signature verification, and updated files. Normal and
`/GL` + `/LTCG` compile/link/run probes passed. The historical interval
function also matches retail at 29/29 bytes with 6030.

LTCG is material evidence. Microsoft's [LTCG documentation](https://learn.microsoft.com/en-us/cpp/build/reference/ltcg-link-time-code-generation)
describes cross-module inlining and optimized x86 calling conventions, including
register arguments and removal of unused parameters. Those mechanisms are a
plausible explanation for some unusual retail ABIs; this has not been proved
per function. The historical non-LTCG object recipe cannot settle those cases.

## What the old recipe actually reproduces

The historical flags were `/c /O2 /Gz /MT /Gy /G6 /GF`, with `/Dnullptr=0`
added in the later batch script. These are the project's established matching
recipe, not a recovered complete original command line.

Fresh compilation of the historical sources with installed 13.10.3052 and
comparison using `tools/matching/compare_obj.py` produced:

| Function | Address | Result | Meaning |
| --- | --- | --- | --- |
| `FrameCounterPair::AtInterval` | `0x00427C70` | 29/29 bytes, no relocations | Plain C++ code-generation match over the compared extent |
| `Entity_Destructor` | `0x00401FF0` | 30/30 compared bytes; 4 relocation bytes excluded | Plain C++ match excluding the call operand; target identity was not checked |
| `Entity_Constructor` | `0x00402050` | 88/88 bytes | The selected MSVC branch is naked inline assembly, not a C++ code-generation match |
| `Entity_Init` | `0x00401DE0` | 68/273 compared bytes | Unmatched; the historical documentation also excluded it from overlays |

Compilation of **current** `entity.cpp` and `frame_counter.cpp` fails before
comparison: `include/cstdint:3` uses `#include_next`, which MSVC 7.1 rejects
with C1021. Commit `0e84172` retired the MSVC integer compatibility headers
and assembly branches. The recent cleanup also removed the obsolete hybrid
build command. Neither the current tree nor old object files should be
presented as a freshly verified MSVC build.

To reproduce the plain-C++ interval probe without modifying current sources,
run from the repository root:

```bash
probe_dir="$(mktemp -d /tmp/th10-match.XXXXXX)"
git archive 51ff01381fbd097e9310510e7aa494cb24787fb9 \
  matching2/include matching2/src/game/frame_counter.cpp | tar -x -C "$probe_dir"
toolkit_dir="$HOME/.wine/drive_c/Program Files (x86)/Microsoft Visual C++ Toolkit 2003"
WINEDEBUG=-all INCLUDE="$(winepath -w "$toolkit_dir/include")" \
  wine "$toolkit_dir/bin/cl.exe" /nologo /c /O2 /Gz /MT /Gy /G6 /GF \
  "/I$(winepath -w "$probe_dir/matching2/include")" \
  "/Fo$(winepath -w "$probe_dir/frame_counter.obj")" \
  "$(winepath -w "$probe_dir/matching2/src/game/frame_counter.cpp")"
python3 matching2/tools/matching/compare_obj.py \
  "$probe_dir/frame_counter.obj" AtInterval 0x00427C70
```

## Limits of the existing comparison gate

`compare_obj.py` remains useful for investigation, but cannot certify a
complete reconstructed function by itself:

- It masks `DIR32`/`REL32` operands without checking the referenced symbol or
  resolved target. Calling the wrong callee can therefore escape comparison.
- It compares from the requested symbol to its COFF section end, without an
  independently established retail function extent. A matching prefix can pass;
  shared sections can also include subsequent code.
- Its executable mapping assumes this image's fixed `.text` layout and does
  not authenticate the executable hash. The removed hybrid builder checked
  that hash, but the standalone comparison command does not.

The old hybrid builder required equality for unmasked bytes, then wrote those
same bytes back while preserving retail relocation operands. Its identical
output hash was expected; it was not evidence of independently linked code.
Historical overlay membership includes assembly implementations and does not
establish current source validity.

## Recovered baseline

Run `python3 matching2/tools/maintenance/recover_matches.py` from the repository root.
It exports the 90 required source files and headers from
`2b8f23229ab45b9e8cdcfda5ac12689204897a5a`, the parent of the shim-removal
commit. The generated snapshot retains historical inline assembly. Two ECL
callback aliases and four local integer constants require C++98 spelling;
those exact substitutions are recorded in the report, and current production
sources are not changed.

Fresh runs with both 6030 and the original 3052 toolkit reproduced all
**397 historical comparisons**:

| Result | 6030 | 3052 |
| --- | ---: | ---: |
| Equal compared bytes, no relocation masks | 90 | 90 |
| Equal after excluding relocation operands | 307 | 307 |
| Compile failures or differing comparisons | 0 | 0 |

These are comparison results, not 397 proven complete C++ functions. Many
historical implementations use inline assembly. Of the 397 compared ranges,
358 exactly equal a single contiguous saved-Ghidra function body; the other
39 have missing, split, or different analysis boundaries. The report records
those ranges for review. Relocation targets remain unchecked.

Objects, recovered source, build logs, toolchain hashes, and per-function
results are in `matching2/build/recovered-matches/`. The 3052 control is in
`matching2/build/recovered-matches-3052/`; recreate it with `--toolkit` pointing
to the old toolkit and `--output` selecting that directory. The command checks
the retail executable hash and removes old objects before recompiling, so
failed compilations cannot reuse stale objects.

The next matching step is to resolve function boundaries and relocation
targets, then develop an independently linked baseline. Current-source MSVC
compatibility and `/GL` + `/LTCG` matching remain separate work.
