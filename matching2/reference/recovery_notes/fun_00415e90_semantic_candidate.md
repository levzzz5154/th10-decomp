# 0x00415E90 semantic recovery candidate

## Decision

Keep [`fun_00415e90_00415e90.cpp`](../../msvc/src/game/fun_00415e90_00415e90.cpp) as the retail naked assembly definition for now. No semantic C++ replacement or uncompiled sidecar was added. The high-level operation is partly legible, but the state layout and several helper call ABIs are not yet reliable enough to preserve the behavior in ordinary C++.

## Live Ghidra evidence

Inspected the open `th10.exe` program (`x86:LE:32`, image base `0x00400000`). Ghidra identifies `FUN_00415e90` at `0x00415E90`, with body `0x00415E90..0x00416F61` and prototype `undefined4 __stdcall FUN_00415e90(int *param_1)`. The assembly epilogues at `0x00416F39` and `0x00416F5F` both use `ret 4`; normal return is zero and the opcode-zero exit returns `0xffffffff`. The source region is 4,480 bytes (`0x00415E90..0x0041700F`) and includes the dispatch data addressed at `0x00416F64` and `0x00416FC4` after the function epilogues.

The Ghidra function report gives 1,146 instructions, 146 basic blocks, 243 edges, 150 calls, cyclomatic complexity 99, and 24 distinct callees. The caller list names `FUN_00414900`; its call is at `0x0041514B`, after it pushes the state pointer from `[edi+0x9EB8]`. It branches on EAX: zero continues by updating the same state object, while nonzero skips that update. `get_xrefs_to(0x00415E90)` also finds a call at `0x00415E31`, in the immediately preceding `0x00415E30` fragment; Ghidra currently has no function defined at `0x00415E30`. That fragment pushes ESI, calls this entry, and then updates fields at `+0x04`, `+0x08`, and `+0x0C` using the float pointer at `+0x10`. The fragment's ownership is therefore still unresolved in the Ghidra function graph.

Ghidra lists these distinct callees: `0x0040C4D0`, `0x00409E50`, `0x00417010`, `0x00449670`, `0x00449470`, `0x0040AC90`, `0x0043C8B0`, `0x0043DC90`, `0x00420B10`, `0x00420C30`, `0x0044BF40`, `0x004175E0`, `0x00448D00`, `0x004496A0`, `0x004497D0`, `0x00423370`, `0x004492A0`, `0x00409D90`, `0x004491C0`, `0x00447A50`, `0x0040C480`, `0x004492F0`, `0x00404ED0`, and `0x00405410`.

## Behavioral model

The decompilation and retail control flow support a packed script-command dispatcher interpretation. `param_1[0x17]` (`+0x5C`) points at the current record; the dispatcher reads a 16-bit frame at record offset `+0`, an opcode byte at `+2`, a record-size byte at `+3`, and operands beginning at `+4`. It processes records whose frame is at or before `param_1[7]`, advances by `4 + record[3]`, and ticks the frame helper when the next record is not due. Opcode zero terminates with `-1`; other opcode paths return zero after updating runtime state.

The 24 opcode cases create and release animation handles, select sprites by script index, update positions and stop frames, change player/input state, trigger sound paths, and adjust score-related state. This describes the broad behavior only; the array indices remain offsets, not recovered semantic field names.

## Concrete blocker

The Ghidra prototype recovery is demonstrably wrong for helper call operands needed by this body. For example, Ghidra reports `FUN_00409E50` as `undefined __fastcall FUN_00409E50(undefined4 param_1)`, but a target call at `0x00416265` loads a state-field address into EAX and calls it with no stack argument; the callee at `0x00409E50` immediately dereferences `[EAX]`. Similarly, Ghidra reports `FUN_00417010` as `undefined1 * __stdcall FUN_00417010(void)`, while the target loads `record + 4` into EAX before calling it to decode the current record's payload. The decompiler consequently substitutes incidental register values into pseudocode calls (for example, the opcode value appears as an argument to `FUN_00409E50`) and omits the effective EAX input.

The target itself is still typed only as `int *`; Ghidra exposes 54 untyped/phantom stack locals, and the command-state fields and variable-length record schema have no recovered structure. With 24 callees and register-passed inputs that differ from the inferred prototypes, a readable rewrite now would have to guess both field meaning and call contracts. The next useful step is a caller-connected LTCG recovery of `0x00414900`, the `0x00415E30` fragment, `0x00415E90`, and the hidden-register helper ABIs, followed by incremental state-layout recovery.

No build, probe, or test was run for this pass.
