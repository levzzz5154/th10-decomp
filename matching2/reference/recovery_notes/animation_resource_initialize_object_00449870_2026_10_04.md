# Exact animation resource initializer, 2026-10-04

The complete 217-byte `0x00449870` region is now ordinary C++ at `src/render/animation_resource_initialize_object_00449870.cpp`. It zeros the position, base position and render-offset vectors; sets the render-enabled flag; records the script index; initializes the two layer bytes; and invokes the preserving script loader. Its public entry uses resource ECX, object and index on the stack, RET 8.

A copied four-byte `AnimationFlagValue` keeps the flags value as a distinct compiler candidate across the first two vector assignments. The pinned compiler then produces retail's ESI/EDI vector copies, delays the resource ECX-to-EAX transfer until after the second vector, and interleaves the flag/index stores with the third vector exactly. The wrapper uses ordinary copy semantics and a bitwise-OR operation. The source adds no volatile access, compiler barrier, assumption, assembly or byte patch.

Controls in `matching2/build/experiments/initialize_object_2026_10_04/` demonstrate the distinction: direct scalar fields, integer-array views and constructing the wrapper from a scalar all preserve the previous mismatch. Copying the flag word through the wrapper and assigning that wrapper both pass all 217 bytes. The selected copy variant is preserved in `typed_flags_copy.cpp`.

The focused cluster co-compiles a complete 194-byte preserving-loader context at `0x0043E7E0`, verified directly against retail. This duplicate context is unselected and receives no additional recovery credit; the existing selected preserving-loader region remains owned by its original cluster. A synthetic 60-byte array caller provides the private loader convention, while rooting the real initializer preserves its public ABI.

Maintained native proof: `matching2/build/experiments/initialize_object_2026_10_04/production_probe/clusters/animation_resource_initialize_object_00449870/report.json`. Complete initializer SHA-256: `c4be92e1096f74b7be92e5fe32adee65afee5fa061b3775559c574a83ecc5267`. Both `make -j2` and `make EXACT=1 -j2` pass. The final executable checks confirm this initializer, the preserving loader, all four animation registrars, and the complete spell-card routine match retail in both outputs. The entire 487,936-byte EXACT executable equals the oracle, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The candidate archive `matching2/reference/semantic_candidates/animation_resource_initialize_object_00449870/` retains complete current inputs under `overlay/`, the replaced assembly under `before_exact_promotion/`, and hashed evidence. The legacy assembly symbol remains a static retail-address alias for existing callers.

Replay:

```sh
python3 matching2/tools/matching/probe.py --source src/render/animation_resource_initialize_object_00449870.cpp --output matching2/build/experiments/animation_resource_initialize_object_00449870_replay
```
