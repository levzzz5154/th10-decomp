# Indexed animation resource release — 0x00447F70

Date: 2026-09-27

## Result

Recovered the complete 87-byte region as readable C++ without inline assembly.
The isolated normal probe is exact for all 87 bytes, with zero differing bytes
and no relocation masks. Three fresh native builds produce identical selected
bodies, SHA-256
`2691afa6fdc359aa5b128e9ae08f57983e45c2de720ac0b1e0e8dba79f004beb`.
Integration and the complete executable build remain the parent task's checks.

## Live evidence and behavior

Live Ghidra MCP `decompile_function` and `disassemble_function` were queried
for `th10.exe` at `0x00447F70` during this recovery. Both show the manager in
EDI and resource index in ESI, a saved EBX holding zero, and plain RET.
The first two arrays at `+0x3AD4E0` and `+0x3AD560` release nonnull COM objects
through vtable slot `+8`, then clear their indexed slots. The third array at
`+0x3AD5E0` conditionally calls cdecl free at `0x00452422`, clears that slot,
then clears it again unconditionally. The second clear is part of the owned
retail body and is preserved.

## Compiler recovery

The source represents the resource arrays as a typed COM interface with three
stdcall virtual slots. Calling `Release()` produces the retail EAX object,
ECX/EDX vtable temporaries, object push, and indirect vtable call lowering.
The heap release is a direct, explicitly cdecl external binding at the retail
free address. `_ReadWriteBarrier()` after the conditional final-array clear
prevents the compiler from eliminating that store; it emits no instruction.

The synthetic native-LTCG context takes one manager and a count and calls
`manager->Clear(i)` in an ascending integer loop. This establishes the EDI
manager and ESI index register convention. The context is compiler scaffolding
and is not selected as recovered game code. Its contribution is 35 bytes at
`0x00447FD0`; the selected function is 87 bytes at `0x00447F70`.

## Artifacts and verification

The scratch project is
`matching2/build/experiments/indexed_resource_release/msvc`.
Its source, layout, and context files are ready for parent integration:

* `src/render/animation_manager_clear_indexed_resources_00447f70.cpp`
* `layout/ltcg/indexed_resource_release.json`
* `layout/ltcg/indexed_resource_release_context.cpp`

The final normal probe command was:

```sh
python matching2/tools/matching/probe.py \
  --project matching2/build/experiments/indexed_resource_release/msvc \
  --source src/render/animation_manager_clear_indexed_resources_00447f70.cpp \
  --output matching2/build/experiments/indexed_resource_release/attempt03 \
  --json \
  --write-proposal matching2/build/experiments/indexed_resource_release/proposal.json
```

Report `attempt03.json` has `exact: true`. `attempt02.json` also passed the
normal probe. Attempt 01 already emitted the exact 87-byte function but failed
native validation because its provisional context extent was 60 bytes instead
of the measured 35 bytes. That context metadata was corrected; no instruction
or address operand was patched. The final source comments describe the field
offsets and the purpose of the compiler barrier.
