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

## Next experiments

1. Find a *body* change that raises the receiver's priority without changing the
   instruction sequence (the pressure family that worked for the accessors).
2. Consider a two-function batch: the two real callers at `0x00420B10` (73
   bytes, `int __stdcall(int)`) and `0x00420C00` (41 bytes, no arguments) are
   byte-simple and call this function with constants; if a batch forces the
   convention through an in-scope caller whose own ABI is fixed, both becomes
   landable together (218 bytes).
3. `tools/waves/shape.py` measures the 104-byte body at 0.774 register-normalised
   similarity (32 retail instructions against 30 compiled): the residual is the
   receiver/argument roles plus one `push`/`pop` pair the retail prologue keeps.
