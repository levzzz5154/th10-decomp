# `FUN_00414900` semantic recovery status

Status: retain the retail definition in `matching2/msvc/src/game/fun_00414900_00414900.cpp`. The outer callback contract is now clear enough to describe in C++, but several direct callees depend on values carried in EAX, ESI, EDI, or x87 ST0 rather than on ordinary C++ parameters. Their effects and object layouts must be modeled before the body can be replaced without inline assembly.

## Live Ghidra evidence

The active program is `th10.exe` (x86 Windows PE). Ghidra identifies `FUN_00414900` at `0x00414900`, body `0x00414900..0x004157dc`, with 1,084 instructions, 307 basic blocks, 521 edges, 21 calls, and cyclomatic complexity 216. Its decompiler signature is `undefined8 __fastcall FUN_00414900(int param_1, uint param_2, int param_3)`. Variable storage confirms `param_1` in ECX, `param_2` in EDX, and `param_3` at `Stack[0x4]`.

The only direct code xref found is the tiny callback stub at `0x00415ae0`:

```asm
00415ae0  push ecx
00415ae1  call 00414900
00415ae6  ret
```

Ghidra does not recognize that stub as a function, so its function-callers query reports none; the raw xref query identifies the call at `0x00415ae1`. A data xref from `0x004139c1` shows `ItemFrontRuntime_InitializeRetail` registering the stub address through `SchedulerCallback_Create` and `Scheduler_RegisterPrimary`.

At `0x00414900`, the target saves ECX and EDI, reads the pushed callback value from the stack, restores ECX, and returns with `ret 4`. The wrapper therefore gives the target the callback context as its stack argument. The scheduler's primary dispatcher at `0x00449c00` loads the task context into ECX, indirectly calls the callback, and consumes only EAX as its status; it does not use ECX, EDX, or the full EDX:EAX pair afterward. The callback result is EAX = 1 on both target return paths. Thus the wrapper plus target can be represented at the outer boundary as a one-argument stdcall routine.

Direct callees reported by Ghidra are `FUN_00415e90`, `FUN_0043dc90`, `FUN_0043e5a0`, `FUN_0043ee30`, `FUN_00449870`, `FUN_00449950`, `FUN_00463b2c`, and `_free`. `FUN_0043ee30` is itself a large `ulonglong __fastcall` animation update, so the outer routine's register flow is coupled to its callee behavior.

The live decompiler and target call sites expose additional hidden inputs that block ordinary C++ calls:

- `FUN_0043e5a0` is decompiled as `__fastcall(int, int)`, but Ghidra identifies `in_EAX` as the animation record being mutated. At `0x00414a93..0x00414a98`, the caller puts that record in EAX immediately before the call.
- `FUN_00449950` is decompiled with no parameters but uses `unaff_ESI` as the animation manager/pool base. The target keeps that manager in ESI across its allocation paths.
- `FUN_0043dc90` is decompiled as `__thiscall(this, arg)`, but it reads `unaff_EDI` as the sound id. For example, the target sets EDI to `0x24`, ECX to `0x492590`, pushes zero, then calls it at `0x004154f5..0x00415501`.
- `FUN_00463b2c` is decompiled as a no-argument stdcall helper, but its body reads `in_ST0`; the target prepares that x87 value before calling it.

`FUN_0043ee30`'s decompilation references `param_1` only in its signature and `param_2` only in two early-return high-word values. The outer routine threads that high word into later animation ticks, and the scheduler ignores the final high word. This makes the inherited ECX/EDX values irrelevant to the callback's state changes; it is not the remaining blocker.

## Behavior visible in the decompilation

The body behaves like a front HUD/runtime update. It advances groups of animation records with `0x3ac` stride, changes seven repeated display states based on global player coordinates, refreshes numeric display records, updates progress and timing fields, and walks manager-owned entity lists to change status words and flags. It also allocates/configures entity records for missing display entries and clears/frees a stale group referenced at `state + 0x9eb8`. Most accesses are still raw offsets into the large state and entity layouts.

## Integration blocker

The target body can be called through a normal C++ stdcall entry, but a direct C++ translation cannot invoke the current `0x0043e5a0`, `0x00449950`, `0x0043dc90`, and `0x00463b2c` helpers with their observed hidden inputs. Replacing those calls with guessed signatures would lose the record, manager, sound-id, or x87 values. Inlining them instead requires recovering their full state effects and layouts; the `0x0043ee30` animation updater is itself a large state-mutating dependency. The 307-block body also operates on raw offsets into front-state, entity, and manager objects.

Next step: recover typed semantic equivalents for the hidden-register helpers and their object layouts, then integrate them with this body. Until those dependencies are modeled, keep the retail assembly definition and do not add an uncompiled semantic sidecar.
