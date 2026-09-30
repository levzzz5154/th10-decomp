# Native-LTCG recovery: `0x00415E30`

Integration verified 2026-09-27: the final maintained-source rebuild and
direct oracle comparison match all 487,936 executable bytes. The current
manifest and all 3,851 recorded source/input hashes agree with the build
report. This supersedes any pending-integration statement below. See
[the batch checkpoint](native_recoveries_2026-09-27.md).

Measured 2026-09-27. The complete 93-byte region at `0x00415E30..0x00415E8C`
is EXACT with readable C++ and no inline assembly. This scratch measurement
uses the production `probe.py` and the production native-LTCG build path.
The maintained project was not changed by the experiment.

Live Ghidra MCP confirms `th10.exe` and the complete instruction body in
`ghidra_00415e30.json`. The region is currently an unassigned code fragment,
so Ghidra's function-disassembly endpoint has no containing function; the
read-only `disassemble_bytes(dry_run=true)` endpoint yields all 33 instructions.

The source is a relocation-only twin of the landed free `__stdcall`
`TickRecoveryState_0040bd20` model. A synthetic array-walking caller permits
native LTCG to pass the state in ESI. The initial PUSH ESI supplies the query's
stack argument; the query at `0x00415E90` pops that argument. All three returns
are plain RET. A member-function model is the wrong compiler context.

The timer reads previous/current/elapsed/speed at +4/+8/+C/+10. Both normal
speed bounds retain absolute addresses `0x470B68` and `0x470B64`; the pooled
1.0 literal remains bound to `0x470AFC`; the x87 rounding helper is `0x463B2C`.
The guard returns 1, otherwise the timer advances and returns 0.

## Integration inputs

- `msvc/src/unidentified/unassigned_00415e30.cpp`
- `msvc/layout/ltcg/recovery_tick_state_00415e30.json`
- `msvc/layout/ltcg/recovery_tick_state_00415e30_context.cpp`
- `proposal.json` records the exact decorated name and extent.

Register the new layout after copying those three files to the maintained
project. Preserve existing owner metadata during manifest cutover.

## Verification

```text
python3 matching2/tools/matching/probe.py \
    --project matching2/build/experiments/tick_twin/msvc \
    --source src/unidentified/unassigned_00415e30.cpp \
    --output matching2/build/experiments/tick_twin/probe \
    --write-proposal matching2/build/experiments/tick_twin/proposal.json

0x00415e30      93 bytes  ?TickRecoveryState_00415e30@@YGHPAURecoveryTickState_00415e30@@@Z  EXACT
EXACT
```

The report is `probe/clusters/recovery_tick_state_00415e30/report.json`.
It records no masked bytes, no changed instruction bytes, and no reference
bytes used for build. `disassembly.txt` contains the emitted complete body.

Promoted on 2026-09-27 through `promote_scratch.py`; staged manifest and touched-cluster probe passed. Whole-executable integration gate remains pending.
