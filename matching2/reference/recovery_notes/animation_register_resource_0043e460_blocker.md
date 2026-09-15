# 0x0043E460 — resource registration: body recovered, ABI promotion blocked

2026-09-16. `AnimationManager_RegisterResource` (104 bytes, `this` in EAX, name
in EDX, resource and parameter on the stack, `ret 8`) was reconstructed
completely: the body is byte-for-byte the retail instruction sequence, and the
remaining blocker is that MSVC will not promote the receiver to EAX for this
shape. The region stays assembly; the scratch layout, context and source were
removed.

## Recovered body

`src/render/animation_manager_register_resource_0043e460.cpp`:

```cpp
struct AnimationResourceRecord {
    int resource;              // +0x00, 0 while the record is free
    int parameter;             // +0x04
    int unknown_08;            // +0x08, zeroed after the name copy
    char name[0x100];          // +0x0C
};

struct AnimationManager_0043e460 {
    unsigned char unknown_000[0x1F88];
    AnimationResourceRecord records[31];       // +0x1F88
    char* RegisterResource(const char* name, int resource, int parameter);
};

char* AnimationManager_0043e460::RegisterResource(const char* name, int resource,
                                                  int parameter) {
    int index = 0;
    for (; index < 31; ++index) {
        if (records[index].resource == 0) {
            records[index].resource = resource;
            records[index].parameter = parameter;
            char* out = records[index].name;
            const char* text = name;
            while ((*out++ = *text++) != 0) {
            }
            records[index].unknown_08 = 0;
            return out;
        }
    }
    return (char*)(long)index;      // retail's failure path returns the index in EAX
}
```

Compiled as an ordinary translation unit this is **exactly 104 bytes, the
retail extent**, with an instruction sequence that matches retail except for
the receiver/argument registers and `ret 0xC` against `ret 8`. The two
argument orders, the record-pointer walk and the `while ((*out++ = *text++))`
copy shape that produces retail's `sub esi,eax` strength reduction are all
confirmed.

## Measured: the promotion is body-driven and does not move

The function was built as a native-LTCG cluster with the head gap
`0x401000..0x43E460`, the function in `.text$01register` at `0x43E460` and a
synthetic context at `0x43E4D0`. Twelve configurations were measured — the
member form and a free-function form (manager as the first parameter), each with
six contexts (pointer-array loop with name array; constant manager/name
`0x492590`/`0x46DF98` as the retail callers use; hoisted manager/name locals;
mixed integer/pointer parameter list; two-call chain with a live `char*` result;
struct-argument request). **Every configuration produced the same callee**: 104
bytes, receiver in EDX, name in ECX, `ret 0xC`.

That matches the caller-independence the wave-8 note recorded for `0x00437750`
("promotion *is* body-driven"), and it puts this region in the same class as
`0x00450220`: the sequence is recovered, the ABI is not selectable from the
source. Note the contrast with the landed EAX-receiver clusters
(`0x00443B60`, `0x00401CB0`): all of them are members with **no** parameters,
where `this` in EAX is the whole convention; no landed cluster passes both EAX
and two stack arguments.

## Real-caller batch measured: the pair does not converge either

The next experiment above was run. A schema-1 batch with the cluster's `source`
= the callee, `additional_sources` = the *real* caller
`0x00420C00` (`src/game/game_state_dispatch_dummy_00420c00.cpp`, 41 bytes,
no arguments, `__declspec(noinline)`), a synthetic loop-array context and both
sections named in address order (`.text$01dispatch` at `0x420C00`,
`.text$03register` at `0x43E460`, gaps `0x401000..0x420C00`,
`0x420C29..0x43E460`, `0x43E4C8..0x43E4D0`) links natively with the callee at
its retail address. The convention still does not move:

```text
retail   0x420C00  mov edx,0x46DF98   push 0   mov eax,0x492590   je   push 4   call  (41 bytes)
compiled 0x420C00  mov edx,0x492590   push 0                  je   push 4   push 0x46DF98   call  (46 bytes)
```

The caller keeps the manager in EDX, passes the name on the stack, and the
callee's 104-byte body is byte-identical to the twelve-context result above. A
fixed-ABI caller in the same scope does not constrain the pair's convention, so
this region joins `0x00437750` and `0x00450220` in the class where the recovered
sequence cannot be expressed with the required register roles.

## Next experiments

1. Find a *body* change that raises the receiver's priority without changing the
   instruction sequence (the pressure family that worked for the accessors).
2. If a future toolkit or `/GL` invocation promotes a *pointer-first* parameter
   to EAX for a three-argument shape, retry this note's batch as-is; the sources
   and layout are recorded above and need no new reverse engineering.
3. `tools/waves/shape.py` measures the 104-byte body at 0.774 register-normalised
   similarity (32 retail instructions against 30 compiled): the residual is the
   receiver/argument roles plus one `push`/`pop` pair the retail prologue keeps.
