# Native secondary-back animation creators

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

2026-09-27. `0x00448F60` (73 bytes) and `0x00448FB0` (95 bytes) now have ordinary C++ models compiled with native MSVC `/GL` and `/LTCG`. The isolated `matching2/build/experiments/animation_secondary_back/first.json` probe reports zero differing bytes for both complete selected contributions. Extraction changes zero instruction bytes and zero address operands. Detailed source/body hashes are in `exact-summary.json`.

The registered `layout/ltcg/positioned_primary_00448d50_wave10.json` is the working primary-back reference. Its selected 73-byte and 95-byte source shapes are reused with secondary-back names, unique position/object types, distinct selected sections and registrar `0x00448AC0`. The earlier lazy-primary layout is not the registered cluster and was not used. Every existing registered layout stays intact; the scratch manifest adds a separate two-source cluster `positioned_secondary_back_00448fb0`.

The bucket creator allocates a pooled object, stores the supplied render bucket at `+0x20`, sets flag `0x40000000` at `+0x35C`, initializes its script through `0x00449870`, and registers it at the secondary-back list. Its private entry receives the output slot in EDI, with resource, index and render bucket on the stack; it returns the output slot in EAX and cleans twelve stack bytes.

The positioned creator allocates the same object, sets the same flag, clears the render bucket, copies the twelve-byte XYZ position into `+0x340`, loads the script through `0x0043E710`, and invokes the same secondary-back registrar. Its private entry receives position in EDI, with resource, output slot and index on the stack; it returns the output slot in EAX and cleans twelve stack bytes.

The synthetic array context makes both private conventions agree with retail. Its compiled allocator and script-loader ABI anchors are unchanged from the proven primary-back cluster and remain at their retail addresses. The final registrar anchor changes to `AnimationManager_RegisterSecondaryBack_00448ac0`, placed at `0x00448AC0`, with manager fields changed from `+0x72DAD4/+0x72DAD8` to `+0x72DADC/+0x72DAE0`. It earns manager in EDX, entity in EBX, and output slot in EAX. Anchors are excluded from recovered code; the simplified 103-byte registrar anchor is not a byte recovery of the 118-byte retail registrar.

Live Ghidra MCP decompilation confirms the bucket creator calls `0x00448AC0` and confirms that registrar's secondary-back head/tail fields `+0x72DADC/+0x72DAE0`. The live database does not define a function at `0x00448FB0`; its maintained retail instruction listing and the unmasked complete-byte oracle proof establish the positioned twin's calls and field writes.

Promotion artifacts are `promotion.diff` and `promotion.json` under `matching2/build/experiments/animation_secondary_back`. The four files are the two maintained source paths plus new `layout/ltcg/positioned_secondary_back_00448fb0.json` and its `_context.cpp` driver. Set the two region entries to `kind: "semantic"` with the provided decorated symbols, then append the new layout registration. No headers or existing layouts need changes. Maintained-project probe and whole-executable gates remain the integration step. Maintained files were untouched during experimentation.

The exact isolated probe command was:

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/animation_secondary_back/project \
  --source src/unidentified/FUN_00448fb0_00448fb0.cpp \
  --output matching2/build/experiments/animation_secondary_back/first --json
```

Integrated on 2026-09-27 using the four explicit artifacts and atomic cluster registration. The maintained probe is `matching2/build/experiments/animation_secondary_back/maintained.json`; the whole-executable integration gate is pending.
