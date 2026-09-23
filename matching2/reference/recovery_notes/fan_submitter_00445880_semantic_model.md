# 0x00445880 fan submitter: semantic source candidate

The source at `matching2/msvc/src/unidentified/FUN_00445880_00445880.cpp` now
models this region as a regular x86 C++ member function. This records the
semantic interpretation and the existing byte candidate; exact output remains
unverified.

## Behavior and ABI

The wrapper's retail instructions are:

```text
00445880  mov eax,ecx
00445882  mov ecx,[eax+0x358]
00445888  push 0x21
0044588a  push ecx
0044588b  mov ecx,[0x00491c10]
00445891  call 0x004450e0
00445896  xor eax,eax
00445898  ret
```

The wrapper receives its entity object in ECX, reads its dword at `+0x358`,
loads the animation manager from `data_00491c10`, calls `DrawFan` at
`0x004450E0` with count `0x21`, ignores the draw result, and returns zero. The
existing `RenderEntity` layout names `+0x358` `strip_vertices` and has the
entity texture at `+0x394`. The callee starts by saving ECX as its manager and
EAX as its entity; its decompilation reads the entity's `+0x394` texture field.
This supports modeling the call as `DrawFan(this, strip_vertices, 0x21)`.

The wrapper itself has no explicit arguments and is modeled as the
non-static `FanSubmitter_00445880::Run()` member, preserving the x86
`__thiscall` entry (`this` in ECX). At the target call, retail keeps the entity
pointer in EAX, places the fan data and count on the stack, and loads the
manager into ECX. The C++ body expresses the known three-part `DrawFan`
operation directly; whether this call spelling recreates its nonstandard
register placement is not established here.

`FanSubmitter_00445880` is a provisional zero-offset `RenderEntity` wrapper,
not a recovered original class name. `strip_vertices` is taken from the
existing shared layout; no further type claims are made about the field.

## Existing 23/25-byte candidate

The prior source experiment recorded in
[`render_state_primitives_004425a0_004450e0.md`](render_state_primitives_004425a0_004450e0.md)
used a two-argument manager ABI alias:

```cpp
int Object_00445880::Run() {
    ((Manager_00445880*)data_00491c10)->Issue(field_358, 0x21);
    return 0;
}
```

That candidate measured 23 bytes against the 25-byte retail wrapper. It began
with `mov eax,[ecx+0x358]`; retail begins with the missing transfer
`mov eax,ecx` (`8B C1`) and then loads the field through EAX. The old byte
comparison therefore identifies the two-byte length gap, but it does not
preserve the entity in EAX for the known `DrawFan` callee. It is retained here
as historical evidence, not as the semantic implementation now written in the
source file.

No build, probe, or test was run for this edit. The direct `DrawFan(this,
strip_vertices, 0x21)` C++ candidate has not been measured; exact output and
register placement remain unverified.

## Proposed symbol and manifest follow-up

The new member definition's proposed decorated symbol is
`?Run@FanSubmitter_00445880@@QAEHXZ`. A semantic promotion would change the
region entry to `name: semantic_FanSubmitter_00445880_Run_00445880`,
`source: src/unidentified/FUN_00445880_00445880.cpp`, that decorated symbol,
and `kind: semantic`, while keeping its address and size. The `symbols` map
would also bind `?Run@FanSubmitter_00445880@@QAEHXZ` to `0x00445880`. The
existing `?DrawFan@AnimationManager_00442F50@@QAEHPBURenderEntity@@PBXI@Z`
binding to `0x004450E0` is the intended call target; no extra `Issue` alias is
needed for the direct C++ spelling. No manifest or alias change was made here,
so the live entry remains `kind: "asm"` and does not yet register this source
as its implementation.
