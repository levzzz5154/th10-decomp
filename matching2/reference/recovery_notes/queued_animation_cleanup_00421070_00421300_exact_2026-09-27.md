# Queued cleanup and handle release: native-LTCG EXACT

Measured 2026-09-27. The complete `0x00421070..0x0042117B` body is **268/268
bytes EXACT**, and `0x00421300..0x0042140C` is **269/269 bytes EXACT**: 537
selected C++ bytes. All loop padding belongs to the compiler contributions;
no body was trimmed, masked, rewritten, or supplied from retail.

## Behavior and boundary evidence

Fresh Ghidra MCP disassembly of `th10.exe` is recorded in
`ghidra_00421070.json` and `ghidra_00421300.json`. Both public entries consume
one state pointer on the stack, ignore incoming ECX, and end in RET 4.

When the controller's +0x6FC dword is 1, each entry looks up the three queued
animation handles at 0x477824/0x477828/0x47782C in order, using the context
pointer at 0x491C10. For each object found, it sets the word at +0x304; when
its +0x18 child flag is zero, the same value goes to each object in the +0x14
child list. Child links have object and next pointers at +0 and +4. Cleanup
writes value 1 and clears the controller to 0; release writes value 2 and
sets the controller to 2. Both clear the three handle globals. Independently,
both clear the shared dword at 0x491BEC if it is nonzero.

## Compiler model

The public stdcall bodies are explicitly rooted so native LTCG preserves
that stack boundary. The full readable Find implementation is co-visible as
a uniquely named 73-byte anchor at 0x4491C0; it receives context in EDX and
a four-byte aggregate handle on the stack and ends in RET 4. It is unselected
and never exported into the recovered image, whose existing Find ownership
remains unchanged. Its complete native body also equals retail.

The handle globals are themselves four-byte aggregates, and each aggregate
is passed directly to Find. Reconstructing an aggregate from a scalar int
load changed register allocation, instruction forms, and the middle loop's
alignment: those earlier builds emitted 252/253-byte bodies. Direct aggregate
arguments reproduce ESI=1/EDI=0 in cleanup, EDI=0/ESI=2 in release, all three
compiler-aligned child loops, and the exact second/third handle loads in EDX.

The release model accesses its four final stores through volatile typed views
of the handle and controller records. This preserves retail's handle-reset,
handle-reset, handle-reset, controller-complete order and the subsequent ESI
pop. Ordinary stores were moved to complete the controller before clearing
the handles; the same 269-byte extent then differed only from offset +0xE1.
The final volatile form emits precisely the observed instructions without
additional accesses or instruction transformations.

## Promotion inputs

Copy these six files from scratch `msvc/` into the maintained project:

- `src/render/queued_anm_cleanup.cpp`
- `src/render/anm_handle_release.cpp`
- `include/th10/render/queued_cleanup_pair.hpp`
- `layout/ltcg/queued_cleanup_pair.json`
- `layout/ltcg/queued_cleanup_pair_context.cpp`
- `layout/ltcg/queued_cleanup_find_anchor.cpp`

Register `layout/ltcg/queued_cleanup_pair.json` atomically for both selected
regions. `proposal.json` records their symbols and owner metadata. The
unique Find anchor name avoids conflicts with the existing selected Find
cluster. The maintained project was untouched by this experiment.

## Verification

```text
python3 matching2/tools/matching/probe.py \
    --project matching2/build/experiments/queued_cleanup_pair/msvc \
    --source src/render/queued_anm_cleanup.cpp \
    --source src/render/anm_handle_release.cpp \
    --output matching2/build/experiments/queued_cleanup_pair/probe_08 \
    --write-proposal matching2/build/experiments/queued_cleanup_pair/proposal.json

0x00421070     268 bytes  _QueuedAnimationCleanup_00421070@4  EXACT
0x00421300     269 bytes  _ReleaseAnimationHandles_00421300@4  EXACT
EXACT
```

The paired probe independently rebuilds the cluster for each source, so both
complete bodies passed twice after the final readable source edits. The
native report is `probe_08/clusters/queued_cleanup_pair/report.json`;
`comparison.json` independently compares native and retail slices for both
selected bodies and the 73-byte Find anchor. `disassembly.txt` contains the
native selected instructions. Reports record zero masked bytes, zero changed
instruction bytes, and no reference bytes used for build.
