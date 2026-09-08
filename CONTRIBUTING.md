# Recovering matching C++

The acceptance target is readable C++ compiled to byte-identical executable
code. The maintained matching project is `matching2/msvc/`. Its existing inline
assembly keeps the executable buildable while functions are recovered.

## Recover one function

1. Find the address in `matching2/msvc/regions.json` and the
   [reference index](decompiled/reference_coverage/README.md). Follow the region's
   `source` field to the maintained implementation. Check ownership evidence:
   an address region can be a fragment, shared tail, or data rather than a whole
   source-level function.
2. Consult the disassembly, assembly baseline, recovered layouts, and modern
   runtime as evidence. Resolve disagreements against the authenticated bytes.
   A modern runtime implementation is a hypothesis to port, not proof of a match.
3. Replace the inline-assembly body with readable C++98. Recover meaningful
   names, types and control flow, preserving the calling convention and layout.
   Update declarations, selected compiler symbol, bindings, region classification,
   and translation-unit ownership together. Classify ordinary C++ as `semantic`;
   keep assembly, data, and padding separately classified.
4. Run `make progress-update` after changing region classifications, then
   `make verify`. It checks the generated progress document, tests the matching tools and rebuilds the executable
   with strict `.text` and whole-file hash checks. Inspect compiler output and
   the link map when a match fails. Never change reference hashes, mask relocation
   operands, substitute original code bytes, or relabel assembly to pass a gate.
5. Review source readability and the build's `port-report.json` for classifications
   and compiler provenance. Record the recovered function/address and validation
   in the change description. Add a focused regression test when changing a
   verification rule or parser.

Ordinary C++ recovery should not introduce inline assembly, instruction-emission
macros, or byte arrays used as executable implementations. Existing scaffolding
can remain for unrecovered regions. Exact output checks machine bytes;
classification and readability still require source review.

## What counts as progress

Report ordinary C++ regions and their compiled bytes separately from assembly,
embedded data, and padding. Whole-file byte equality is a required invariant,
not a percentage of readable C++ completion. Region counts are not necessarily
original function counts, and byte coverage does not measure readability.

The current build uses MSVC compilation, fixed-address COFF section placement,
GNU linking, and PE packaging with preserved data/metadata. A passing build
establishes exact output for that pipeline; recovering the original translation
units, LTCG settings, and native linker recipe remains separate work.

## Maintained source and generation

Edit the existing MSVC project directly. `generate_msvc_project.py --replace`
is a migration operation that overwrites sources; it is not a normal build step
and must not erase recovered C++ work. The assembly generator similarly belongs
to explicit reference maintenance. Generated objects and reports stay under
`matching2/build/`.

Tool ownership is described in the [tools guide](matching2/tools/README.md).
The modern runtime has a [separate workflow](matching2/docs/runtime_development.md).
Its host tests and smoke scenarios are useful behavioral evidence, but do not
replace byte checks. Public CI runs the matching-tool tests without MSVC; a
successful local `make verify` is still needed to establish the compiler and
executable match.
