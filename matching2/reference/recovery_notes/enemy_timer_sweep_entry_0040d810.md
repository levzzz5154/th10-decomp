# Enemy timer sweep callback entry `0x0040D810`

The 10-byte source region in `matching2/msvc/regions.json` remains `kind: asm`.
`FUN_0040d810_0040d810.cpp` is intentionally unchanged: the callback entry
transfers its incoming object from ECX to EDI before tailing into the existing
retail helper, and the standard MSVC x86 C++ calling conventions cannot express
that EDI receiver for the helper call.

## Entry and callback registration

Ghidra's byte disassembly of `0x0040D810..0x0040D819` is:

```text
57                push edi
8b f9             mov edi,ecx
e8 38 ff ff ff    call 0x0040d750
5f                pop edi
c3                ret
```

There is no direct code caller. Ghidra reports the only static reference as a
data reference from `FUN_0040d280` at `0x0040D31C`: that initializer stores
`0x0040D810` at offset `+0x08` of a 0x24-byte scheduler callback record, stores
the manager (`EBX`) at `+0x20`, and registers it through `FUN_00449ae0` with
priority `0x12`. The primary dispatcher `FUN_00449c00` invokes callbacks
indirectly at `0x00449C70`; immediately beforehand it loads the record's owner
from `+0x20` into ECX and calls the function pointer at `+0x08`. Thus ECX is the
entry's callback-object argument. Ghidra has no function object at `0x0040D810`
and consequently reports no direct function callers.

## Behavior and ABI constraint

The entry preserves EDI, copies the callback object from ECX into EDI, invokes
`Enemy_TimerSweepRetail` at `0x0040D750`, restores EDI, and returns the helper's
result in EAX. The helper reads its manager through EDI, sweeps the list at
`manager+0x58`, clears an enemy flag on one path or calls an enemy virtual
function with argument `1` on the other, then advances the manager's timer and
counter fields (`+0x40`, `+0x44`, `+0x48`) using the value at `+0x4C`. Its
observed return value in EAX is `1`.

This is an ABI adapter, not a semantic wrapper that can be written as an
ordinary C++ call: `__thiscall`/`__fastcall` can pass an object in ECX, but the
existing helper has a private EDI receiver and no standard C++ convention
passes that argument in EDI. Keep the naked register transfer unless the helper
is recovered in a caller-inclusive compiler context that removes this private
ABI boundary.

## Native C++ recovery experiment (2026-09-30)

The semantic candidate now models the sweep as a free function taking the
manager pointer and the callback as a member that calls it. A schema-1 native
LTCG experiment also supplies a synthetic manager-array caller so the compiler
can choose the private register convention seen in the two retail regions.
Offline cluster-manifest and ownership validation passes for the scratch
experiment under `matching2/build/experiments/enemy_timer_sweep_0040d750_20260930`.

That check validates the declared candidate regions and their source ownership;
it does not compile the cluster or compare emitted bytes. The scratch link places
its synthetic caller at `0x0040D830`, which overlaps the maintained
`EnemyScriptEntity_Initialize_0040D830` region in the production manifest. The
caller exists only in the isolated scratch link and is not exported with the
recovered function bodies, so the production initializer remains untouched.
This scratch layout is evidence about the proposed source cluster, not a
whole-image integration result.

The candidate's list and object layout is now grounded by neighboring Ghidra
functions. `FUN_0040d830` stores the enemy's own pointer at `enemy+0x116C` and
initializes the forward/back links at `+0x1170` and `+0x1174`; `FUN_0040dae0`
uses that same embedded link to update the manager's head, tail, and count.
`FUN_0040d6b0` allocates a 0x68-byte manager, while `FUN_0040d280` initializes
the frame timer at `+0x40` and stores the callback records at `+0x08` and
`+0x0C`. The candidate header records these extents and asserts the recovered
offsets. The corresponding local link declaration in
`src/game/enemy_lifecycle.cpp` now names its first field `owner`. A Clang
MSVC-target rebuild produced the same sweep section bytes as the earlier, less
descriptive candidate, so this type refinement did not change that compiler's
output.

The native MSVC probe did not reach compilation in this environment:
`winepath` cannot start Wine because the sandbox rejects Wine's local Unix
socket bind with `Operation not permitted`. A Clang MSVC-target object was
compiled for diagnostic purposes only; it uses a different compiler and does
not establish byte equality. The production regions at `0x0040D750` and
`0x0040D810` remain assembly until a native MSVC probe proves both complete
bodies exact.
