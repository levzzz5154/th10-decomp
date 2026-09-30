# Secondary-front animation factories: 0x00449090 and 0x004490E0

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

Recovered 168 bytes as readable C++ without inline assembly. Scratch only;
maintained `matching2/msvc` has not been changed by this agent.

## Evidence

Ghidra MCP active program: `th10.exe`. Read-only evidence confirms:

- `0x00449090..0x004490D8`: 73 bytes, EDI = out, stack = resource/index/bucket,
  calls `0x00449950`, `0x00449870`, `0x00448B40`; returns out with `ret 0xC`.
- `0x004490E0..0x0044913E`: 95 bytes, EDI = position, stack = resource/out/index,
  calls `0x00449950`, `0x0043E710`, `0x00448B40`; returns out with `ret 0xC`.
  Ghidra has no function definition at this entry, so the complete body was read
  with read-only `disassemble_bytes(dry_run=true)`.
- Retail secondary-front registrar starts `lea ecx,[ebx+4]`. Node is object+4,
  manager head/tail = `+0x72DADC/+0x72DAE0`, shared ID counter = `+0x732454`.
- The positioned factory has the same instructions as primary-front 0x00448E80,
  with call displacements adjusted to its address and secondary registration.

## Compiler recovery

Cloned the proven native-LTCG primary-front 95-byte factory and successor-first
front ABI anchor, and the proven primary-back 73-byte factory. Adapted both
selected factory symbols/addresses to secondary-front. The registration ABI
anchor shifts from `0x00448A50` to `0x00448B40`, manager list fields shift by +8,
and the array context calls both factories. The context contribution is 113
bytes; registrar anchor is 97, load-script anchor 207, allocator anchor 171.
Only the two factory contributions are selected; anchors/context are synthetic
and are never exported as recovered code. In particular, retail clears the
successor before reading it; the successor-first shape is only an ABI anchor.

Final scratch probe:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_004490e0_004490e0.cpp \
  --project matching2/build/experiments/animation_secondary_front/msvc \
  --output matching2/build/experiments/animation_secondary_front/probe_moved --json
```

`probe_moved.json`: exact true, no failures, both regions different_bytes 0,
relocations []. Native cluster report: masked_bytes 0, instruction_bytes_changed
0, address_operands_changed 0, reference_bytes_used_for_build false; each full
compiler contribution accepted by the native-LTCG loader.

| Address | Selected bytes | Native/retail SHA-256 |
|---|---:|---|
| 0x00449090 | 73 | `81212a921a308a37c1dd793f7178c3e619d53d410eb9ea3ccde2f5aee249a0cd` |
| 0x004490E0 | 95 | `3b4f269f19c1dbcddce52690fd64e513ed45b73ce0c687b0f44265f82808e54e` |

## Promotion artifacts

Copy only these four paths from `matching2/build/experiments/animation_secondary_front/msvc/`
to `matching2/msvc/`, then atomically register the layout and re-probe:

- `src/render/animation_manager_create_secondary_front_00449090.cpp`
- `src/unidentified/FUN_004490e0_004490e0.cpp`
- `layout/ltcg/positioned_secondary_front_004490e0.json`
- `layout/ltcg/positioned_secondary_front_004490e0_context.cpp`

```sh
python3 matching2/tools/waves/register_cluster.py \
  --project matching2/msvc \
  --layout layout/ltcg/positioned_secondary_front_004490e0.json --apply
```

Fresh recovery removes 168 maintained inline-assembly bytes after promotion.

Final absolute scratch root: `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front`.

Final promotion source files (absolute paths):

- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/msvc/src/render/animation_manager_create_secondary_front_00449090.cpp`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/msvc/src/unidentified/FUN_004490e0_004490e0.cpp`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/msvc/layout/ltcg/positioned_secondary_front_004490e0.json`
- `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/msvc/layout/ltcg/positioned_secondary_front_004490e0_context.cpp`

Fresh relocated verification: `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/probe_moved.json`; native report: `/home/levzzz/Games/th10Decomp/matching2/build/experiments/animation_secondary_front/probe_moved/clusters/positioned_secondary_front_004490e0/report.json`.

Integrated on 2026-09-27 by atomic registration of the two-region cluster. The current maintained-source probe and whole-executable build provide the integration gates.
