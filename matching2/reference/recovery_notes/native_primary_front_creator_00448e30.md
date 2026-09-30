# Native primary-front bucket creator at `0x00448E30`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. The complete 73-byte primary-front bucket creator now has an ordinary C++ native-LTCG implementation. The isolated `matching2/build/experiments/animation_primary_front/final.json` probe reports zero differing bytes for both selected functions: the new 73-byte `0x00448E30` and the existing 95-byte positioned creator `0x00448E80`. Both are complete compiler contributions, and extraction reports zero instruction/address operand changes. Source and body hashes are recorded in `exact-summary.json`.

The source adapts the landed primary-back 73-byte creator, changing its type/function names and final call to `AnimationManager_RegisterPrimaryFront_00448a50`. It allocates an object through `0x00449950`, stores the supplied render bucket at `+0x20`, sets `0x40000000` in the flags at `+0x35C`, initializes the script through `AnimationResource_00449870::InitializeObject` at `0x00449870`, then registers the object at the front of the primary list. Live Ghidra MCP confirms the field writes, calls and primary-front registrar's `+0x72DAD4/+0x72DAD8` list fields.

The private creator entry receives its output slot in EDI, with resource, index and render bucket on the stack. The output slot is returned in EAX and RET cleans twelve bytes. The already-registered `positioned_primary_front_00448e80_wave12` cluster supplies the registrar, allocator and script-loader ABI anchors. Their bodies remain unchanged and are never selected as recovered code.

The cluster gains the bucket creator as an additional source/selected function, a declaration and call before the existing positioned call in the compiler context, and the opaque `InitializeObject` binding at `0x00449870`. The context grows from 92 to 113 bytes. Its old pre-positioned gap is split around the new complete 73-byte contribution, ending at `0x00448E79`, followed by seven gap bytes to `0x00448E80`. No existing selected source or anchor changes.

The scratch project is `matching2/build/experiments/animation_primary_front/project`. `promotion.diff` contains the new creator source and changed registered layout/context; `promotion.json` records the region symbol update. Integrate the three files while preserving concurrent edits, mark `0x00448E30` semantic with `?AnimationManager_CreatePrimaryFront_00448e30@@YGPAPAXPAXPAPAXHH@Z`, and retain the existing cluster registration. The new source already owns that single region, so no carve or new registration is required. Maintained-project probe and whole-executable gates remain the integration step. Maintained files were untouched by the experiment.

The exact probe command was:

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/animation_primary_front/project \
  --source src/render/animation_manager_create_primary_front_00448e30.cpp \
  --output matching2/build/experiments/animation_primary_front/final --json
```

Integrated on 2026-09-27 into the existing registered front cluster. A maintained cluster probe and the full executable rebuild provide the integration gates.
