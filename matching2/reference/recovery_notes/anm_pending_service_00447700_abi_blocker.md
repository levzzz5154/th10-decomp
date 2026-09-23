# Animation pending service at `0x00447700`: entry is standard, body is not yet safe to lift

Read-only live Ghidra audit on 2026-09-23. The source remains the retail naked
body. No manifest, header, caller, layout, or source changes were made; no
build, probe, or test was run.

## Entry ABI and control flow

Ghidra reports `int __thiscall FUN_00447700(void *this, int param_1)` over
`0x00447700..0x00447786` (135 bytes). `this` is in ECX, `param_1` is the one
stack argument at `[ESP+4]`, and both return paths end in `RET 4`. The only
incoming call is `FUN_0041FF80` at `0x0041FFB8`.

The function scans 33 pointer slots starting at `param_1 + 0x3AD06C`. A null
slot is skipped. If the record at `slot + 0x128` is zero and `slot + 0x124` is
nonzero, it calls `FUN_004473C0(param_1, slot)` and returns zero when that
helper returns nonzero, otherwise `-1`. If `slot + 0x128` is nonzero, it
calls `FUN_00447810`, frees the slot record, clears the slot, then attempts
another record-field write through the reloaded slot value. If that value
remains null, the path faults before continuing. Finishing all slots returns
zero.

## Why this is not an isolated C++ conversion

At `0x00447729`, the caller enters `FUN_00447810` with the slot record in EDI
and the outer ECX context still live. The recovered `AnimationResource::Release`
body at `0x00447810` is only emitted exactly in its existing native-LTCG
cluster, where callers establish its receiver in EDI; its C++ member prototype
alone does not describe that edge. The evidence and required whole-program
context are recorded in
[`animation_resource_release_00447810_unlock.md`](animation_resource_release_00447810_unlock.md).

The other direct call, `0x004473C0`, is still an assembly region. Its outer
entry uses two stack arguments and returns with `RET 8`, but the shared header
currently declares an untyped cdecl alias. Its own source records a private
EAX argument to `FUN_00447470` as an unresolved LTCG blocker. A readable caller
needs a typed stdcall boundary and the existing raw symbol alias must be
preserved during manifest/header integration.

There is also an unresolved control-flow hazard in the release path. The live
instructions at `0x00447739..0x00447741` store zero to `[ESI]`, immediately
reload `[ESI]` into ECX, then write zero to `[ECX+0x128]`. Since ESI addresses
the current slot, this appears to dereference address `0x128` after the slot
has been cleared. The release helper and allocator return before this sequence;
no instruction in this path restores the slot. Confirm whether this path is
reachable or whether the retail body intentionally faults before choosing a
source-level model for it.

## Revisit requirements

This is a strong near-miss because its own entry has an ordinary `__thiscall`
ABI and its scan/return behavior is small enough to express clearly. Revisit it
after the `0x00447810` LTCG caller context can include this caller, the
`0x004473C0` dependency has a typed callable alias, and the apparent null
dereference has a verified explanation. Until then, replacing the body with a
standalone C++ method would hide unresolved call-edge and fault behavior.
