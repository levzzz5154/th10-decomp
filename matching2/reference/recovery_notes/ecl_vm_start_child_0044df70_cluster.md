# EclVm_StartChildRetail at 0x0044DF70

Updated 2026-10-01: a complete readable native candidate now measures 549 bytes against retail's 550, with 416 differences including the extent. It supplies unselected compiler scope for the newly exact 142-byte SpawnChild. StartChild remains assembly-owned in the final EXE. The genuine int, float-value, and script resolver bodies are exact in that scope. See [current recovery and verification](resource_cleanup_and_ecl_spawn_2026-10-01.md). The earlier audit below predates this measured candidate.

## Decision

Keep the 550-byte exact inline-assembly body while the semantic implementation is recovered as part of the ECL caller/resolver cluster. This is not an isolated `__stdcall` function: Ghidra's nominal prototype omits the live EAX receiver. No readable body has been measured against the retail bytes.

## Ghidra boundary, callers, and ABI

Ghidra reports entry `0x0044DF70`, body through `0x0044E195` (550 bytes), 165 instructions, 31 basic blocks, and four direct calls. The epilogue is `RET 8` on both paths. The machine-level inputs are:

- EAX: destination ECL VM (the newly allocated child on the spawn path).
- stack argument 1: source VM/frame whose `+4` field points at the operand table.
- stack argument 2: operand index/selector used to begin reading the current instruction's operands.

Ghidra renders the two stack arguments as `undefined4*` and `float*`; that type guess does not describe the private EAX receiver or the integer index. The two callers establish the ABI:

- `0x0044E360` in the dispatcher pushes EBP and ESI, then copies ESI to EAX. Thus this path uses the same VM as both source and destination.
- `0x00450154` in `EclVm_SpawnChild` pushes the original index and `[EDI+4]` as source, then copies the newly allocated child pointer from ESI to EAX. `SpawnChild` receives its parent context in EDI, allocates a `0x1024` VM and `0xC` list node, copies the parent's mask byte to child `+0x101C`, and links the node before calling this routine.

These call sequences were read directly from Ghidra's live disassembly. The caller list contains exactly `0x0044E1A0` and `0x004500D0`.

## Recovered behavior

The source VM's `+4` pointer identifies the current instruction/operand record. Ghidra shows a byte-valued loop limit at `+0x0B`, packed parameter data beginning at `+0x10`, and a script label string at `+0x14`. The routine visits operands from `index + 1` up to (but excluding) that byte-valued limit and writes their resolved values into the destination VM's value stack, whose cursor is at `+0x1008` and whose payload begins at `+0x8`. Operand kinds `'f'` and `'g'` use the float resolver; other kinds use the integer resolver. The second kind byte selects whether a value remains floating point or is converted through the x87 helper at `0x00463B2C`.

The routine then reads a manager/context pointer from `source+0x1014` and temporarily places the destination VM in that object's `+4` field. It resolves the source label through the manager's script table at `+0x102C`, writes the returned address to the destination VM's `+4` field, and clears the destination VM's `+0` time word. If the resulting address is null, it clears `source+4` and returns `-1`; otherwise it restores the prior manager `+4` value and returns `0`. Stack-slot boundary checks at `0x1000` are part of this behavior and must be retained in a semantic translation.

## Required semantic cluster

A useful compiler-visible cluster needs the real call and object relationships, not just a duplicate standalone function body:

1. The `0x0044E1A0` dispatcher call edge, which supplies EAX/ESI, EBP, and ESI in the direct-start path.
2. `0x004500D0` SpawnChild, which supplies the other caller path, allocates and links the destination VM, and carries the parent's private EDI context.
3. The current ECL operand-table, VM-stack, and variable-context layout represented in `ecl_core_interpreter.cpp` and the neighboring accessor models. These definitions currently live in separate translation units, so a later cluster needs one consistent class/layout declaration.
4. Operand resolvers `0x0044FF00` and `0x0044FF80`, plus the x87 conversion helper `0x00463B2C`. Their live call sites use private register and x87 conventions; ordinary C++ prototypes alone do not express those edges.
5. `ScriptTable::Resolve` at `0x00450470`. Its existing layout in `script_resolver_00450470.hpp` and implementation in `final_script_runtime.cpp` already model the private table-in-EAX / label-on-stack convention and sorted lookup.

The start-child routine's Ghidra call list is exactly `0x0044FF00`, `0x0044FF80`, `0x00463B2C`, and `0x00450470`. The dispatcher is very large (Ghidra reports 329 blocks and 126 calls), so it is the difficult caller root; `SpawnChild` alone does not cover the direct-dispatch path. Any candidate should first model the complete value-stack/child-link/label-lookup behavior above, then be byte-rechecked with both caller paths in scope.

## Validation limits

No build, probe, or test was run. This note records live Ghidra boundary, disassembly, and caller evidence plus source-layout inspection; it does not claim that a semantic candidate is byte exact.
