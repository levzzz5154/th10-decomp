# Legacy semantic reconstruction references

This directory preserves the runtime-oriented C++ reconstruction that was
removed when the repository was narrowed to the byte-matching project in
commit `08b42b79385182bbe8df25f8b43d8f7436a28970`.

The archived files are copied from its immediate parent,
`b5fcd830e7f65911eb5ca97144072789ec2b0a55`. They are reference material only:
the active build does not compile anything under this directory.

## What is here

- `src/` and `include/` contain 269 implementation files and 265 headers from
  the former portable/runtime reconstruction.
- `coverage.json` maps 722 retail addresses to their former recovery status
  and source file.
- `function_registry.json`, `standalone_readiness.json`, and
  `RUNTIME_FIDELITY_STATUS.md` preserve the associated inventory and its known
  limitations.
- `data/historical_overlays.json` preserves older overlay provenance.

The old ledger called 710 functions `semantic`. That label meant that a source
implementation existed; it did **not** prove byte identity or complete runtime
parity. Its own evidence note explicitly warned that the status was inferred
from annotations. At the time this archive was restored, 140 of those entries
mapped to semantic regions in the exact project and 570 mapped to regions that
still used assembly.

## How to use it

Search by retail address or old source name, then treat the result as a
hypothesis to cross-check against IDA, Ghidra, callers, data layout, and the
retail instructions. For example:

```sh
rg "0x0044E1A0" matching2/reference/legacy_semantic
```

The code is especially useful for recovered names, structure sketches,
control-flow models, opcode behavior, and test ideas. Many implementations use
host-side hooks, substituted globals, simplified ownership, or known partial
paths, so they must not be copied into the matching project without review.

To promote a useful implementation, adapt it under `matching2/msvc/`, update
the corresponding region in `matching2/msvc/regions.json`, and require the
normal per-unit probe and full byte-exact build to pass. Do not add this
reference directory to the active translation-unit list.
