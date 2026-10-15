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
- `exact/`: exact-only counterparts for the default C++ recoveries.
- `contexts/`: unselected compiler contexts and historical model collaborators.
- `include/`: private assembly bindings, encoding helpers and copied ABI views.
- `imports/`, `data/` and `pe/`: import thunks, embedded bytes and the DOS stub.

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

Use the repository's top-level `make`, `make EXACT=1`, `make progress` and
validation targets. The tools also understand legacy scratch projects whose
metadata remains at the project root. Fifty-eight unreferenced cluster specs
were removed; four other unregistered specs are retained because active
recovery contexts still depend on them.
