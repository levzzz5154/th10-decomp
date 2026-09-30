# Native startup-resource recovery at `0x0041F8D0`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. The complete 82-byte function now has an ordinary C++ native-LTCG implementation. The isolated probe `matching2/build/experiments/resource_cache_0041f8d0/separate.json` reports zero differing bytes for all 25 selected contributions in the expanded `bullet_manager_load_scripts_0040ae70` cluster. This includes all 24 pre-existing contributions and the actual 201-byte `TextLog_0044b810::Append`; no prior function changes its retail bytes. Extraction reports zero changed instruction bytes or address operands.

The live Ghidra MCP decompilation confirms the two ordered loads: `front.anm` into resource slot six, then `bullet.anm` into slot seven. The first failure logs the corresponding existing message through the log at `0x00474F70` and returns `-1`; two successful loads return zero. The resource loader is an opaque `__fastcall` callee bound at `0x00447280`, receiving ID in ECX, cache in EDX, filename on the stack. Native LTCG sees the real variadic logger body, selecting log receiver in ECX, caller-cleaned format on the stack, and plain RET. This resolves the previous 91/93-byte opaque-logger attempts.

A shared local message pointer emitted 83 bytes: each branch loaded its message into EAX, followed by a common `push eax`. It also moved all later cluster code by a byte, which made the strict entry-address check fail. The successful source instead calls `Append` separately in each failure branch and returns `-1` from each branch. LTCG merges the common logger tail while keeping the two immediate PUSH instructions, reproducing retail's 82 bytes exactly. This is readable source with no inline assembly or encoded instruction data.

The original assembly region was carved from `src/game/recovery_leaves.cpp` in an isolated copied project using `tools/waves/carve_region.py`'s `carve_source` implementation. Both the reduced parent and the carved assembly source probed exact (`carve-probe.json`, 17 regions). The recovered source replaces the carved body in `src/game/load_startup_resources_0041f8d0.cpp`.

The scratch project is `matching2/build/experiments/resource_cache_0041f8d0/project`. `promotion.diff` contains the reduced parent, new source, and extension to the existing logger layout. `promotion.json` identifies the region update and exact cluster coverage. Integration must preserve any concurrent edits to the maintained parent or logger layout, add the new source to translation units, and set region `0x0041F8D0` to the new semantic source/symbol `_LoadStartupResources_0041f8d0`. The logger cluster gains the new source, whole-program root, function entry, and a split of its old gap from `0x0041C2EB` to `0x00449AE0`. No driver, headers or absolute bindings change.

The exact cluster probe command was:

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/resource_cache_0041f8d0/project \
  --source src/game/load_startup_resources_0041f8d0.cpp \
  --output matching2/build/experiments/resource_cache_0041f8d0/separate --json
```

Integrated through `promote_scratch.py` on 2026-09-27. The staged manifest and all 25 touched-cluster probes passed against current maintained sources. The obsolete assembly body has been removed from `src/game/recovery_leaves.cpp`; its other regions remain selected there. A whole-executable rebuild remains required for the final integration gate.
