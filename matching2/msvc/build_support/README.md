# Private build support

Maintained game code is in [`../src/`](../src/README.md), including the C++
implementations used by the default build. This directory holds the machinery
which places that code in the retail executable:

- `regions.json`: the complete `.text` partition, region ownership, compiler
  flags, private symbol bindings, native clusters and equivalent recoveries.
- `pe_layout.json`: PE headers and packing; non-code payloads remain in
  `matching2/reference/data/`.
- `layout/`: compiler profiles, native-LTCG manifests, ABI-only callers and
  helpers, and wrappers which preserve the original compiler scopes and order.
- `exact/`: the item update's assembly counterpart, used to validate the C++
  recovery and to build `EXACT=1`.
- `contexts/`: unselected compiler contexts and historical model collaborators.
- `include/`: private symbol bindings and copied ABI views.
- `imports/` and `data/`: import thunks and embedded data. The standard DOS
  stub comes from the freshly linked PE; the packer checks its size and hash.

The native manifests separate physical source ownership from compilation:
`source` and `additional_sources` identify compiler owners;
`owned_includes` maps an included maintained file to its compiler owner;
`compilation_units` optionally supplies a private wrapper for that owner.
Included implementations and headers remain declared, snapshotted and audited
against the compiler's include log. Every selected function still has an exact
address, extent and compiler contribution. A merge must preserve both the
retail owner and the established compiler unit.

The global `compilation_units` table serves the same purpose for ordinary
MSVC sources. The build normalizes only the functions attributed to each
maintained source, while compiling its preserved original context. Shared
runtime declarations are exposed under `include/th10/source_views/`.

Equivalent-recovery manifests name the public C++ implementations under `src/`;
their unselected ABI collaborators stay here. Verification-cache keys cover
project source, header and manifest contents, including these contexts.

## Following a build in the tools

Start in [`build_msvc.py`](../../tools/matching/build_msvc.py). `CompilationPlan`
turns region ownership into the list of sources to submit: a cluster compiles
its additional sources and owned includes, so they must not be submitted again.

- For a native cluster, `load_cluster` in [`ltcg_cluster.py`](../../tools/matching/ltcg_cluster.py)
  checks the sources, selected functions, call graph and native layout.
  `build_cluster` compiles that spec and exports the placed bodies.
- For an ordinary unit, `compile_raw` produces the object and `normalize_unit`
  selects the sections. [`coff.py`](../../tools/common/coff.py) reads sections,
  symbols and relocations for both the build and the probe;
  [`coff_regions.py`](../../tools/common/coff_regions.py) writes the normalized
  object without applying relocations. The GCC and Clang backends share their
  pin, dependency and emitted-object checks in [`_llvm_coff.py`](../../tools/matching/_llvm_coff.py).
- [`unit_cache.py`](../../tools/matching/unit_cache.py) caches normalized MSVC
  and cluster objects, not the link. `link_exact_text` checks the complete
  linked `.text` before [`equivalence.py`](../../tools/matching/equivalence.py)
  checks any C++ replacements. `--exact` changes which verified text is
  packaged, not which checks run.

Use the repository's top-level `make`, `make EXACT=1`, `make progress` and
validation targets. The tools also understand legacy scratch projects whose
metadata remains at the project root. Fifty-eight unreferenced cluster specs
were removed; four other unregistered specs are retained because active
recovery contexts still depend on them.
