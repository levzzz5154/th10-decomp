# 0x00413A20 — exact score task resource setup

2026-09-27. The entire 289-byte region emits exactly under native MSVC
13.10.6030 `/GL` + LINK `/LTCG`. Its recovered C-linkage entry is
`ScoreTask_Setup_00413a20`, rooted to retain the public stdcall pointer argument
and `RET 4`; success returns zero, resource failure logs and returns -1.

## Evidence and source

Fresh Ghidra MCP decompilation, disassembly and a 289-byte memory read from
`th10.exe` are retained in the experiment directory. Ghidra memory equals the
retail oracle, whose region SHA-256 is
`6f60e2c85900703edb846990661b420f784e8247dfcfb3161c3e05c1ed8bb0a4`.
The resource-row memory response shows path pointers at +0x18/+0x1C and the
cached-resource name at +0x20. The source uses a padded, checked view of those
fields and named global types, clock fields, frame-speed float, log object and
error string. It contains no raw-offset pointer accesses, casts, inline
assembly, naked functions, emitted byte data, or instruction rewriting.

The cached-resource call uses the existing ECX index/EDX owner/stack name
fastcall declaration. The archive call shares the established native-LTCG
`load_archive_file` cluster so that its filename remains in EAX, with two zero
stack arguments and `RET 8`. The logger uses the existing genuine Append body
as an unselected ABI anchor, retaining ECX and caller cleanup. Existing archive
sources, anchors and synthetic context are unchanged.

A local reference to the cached-resource field keeps the state pointer in EBP
before the first call. Direct cached-call argument expressions produce the
retail ECX name temporary and the archive branch's EDX/EAX temporary homes.
The clock is modeled as the common 20-byte registered clock. Two compiler
barriers, each emitting no instructions, preserve the final schedule: after
the two zero stores in the inlined reset, and after the reset before reading
the source counter. The variant without them differed in 21 bytes; with both,
the complete region is exact.

## Verification

A fresh normal `probe.py` run reports every one of the extended cluster's nine
selected regions exact: the new 289-byte callback and all eight previously
recovered archive functions. The generated native logger anchor also equals
all 201 retail bytes. Native normalization reports zero changed instruction
bytes, address operands, masks, relocations, or reference bytes as build inputs.
The synthetic caller and ABI anchors contribute zero recovered code.

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/score_task_setup/msvc \
  --source src/game/score_tasks.cpp \
  --output matching2/build/experiments/score_task_setup/final_probe --json
```

Evidence: `final_probe.json` and
`final_probe/clusters/score_task_setup_00413a20/report.json`.

## Promotion

Copy the experiment's `msvc/src/game/score_tasks.cpp`. Extend the existing
`layout/ltcg/load_archive_file.json` using `promotion_delta.json`, retaining its
name, driver and other current contents. The experiment's uniquely named full
layout is an isolated copy, not an additional parallel registration for the
same eight functions. Register the extended archive layout, select the new
`_ScoreTask_Setup_00413a20@4` symbol for 0x00413A20, and retain the legacy assembly
name as a fixed-address caller alias. No archive driver or dependency source
changes are required.
