# Virtual dispatch in a recovered region emits no vtable

2026-09-18. The engine dispatches through object vtables in many regions - the
`screen_regions.py` worklist surfaced two in the first handful
(`0x00438A30` `call [ecx+8]`, `0x0041C850` `call [edx+14h]`). Those looked
unreachable because a class with virtual functions normally makes the compiler
emit a vtable of its own, which the image must not gain.

Measured in a throwaway copy: declaring the class with virtuals that are **never
defined** and **never instantiated** in the translation unit produces exactly the
call retail has and **no vtable at all**. The probe:

```cpp
struct ScoreNode_0041c850 {
    void* field_000;                     // +0x00  the vptr-holding object
    void* field_008;                     // +0x08
    int field_00C;                       // +0x0C
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
};

void Owner_0041c850::Walk() {
    ...
    if (node->field_00C == 1) {
        ((ScoreNode_0041c850*)node->field_000)->Slot5();
    }
    ...
}
```

compiles to

```
8b 40 04        mov eax,[eax+0x4]     ; the object holding the vptr
8b 10           mov edx,[eax]         ; its vtable pointer
8b c8           mov ecx,eax           ; this
ff 52 14        call [edx+0x14]       ; slot 5 - retail's target
```

and the object file contains no `??_7` symbol.

## What this means for the region family

A virtual-dispatch region is expressible provided

1. the class's virtuals are declared in the order retail's vtable uses, so the
   call lands on the right slot offset;
2. no object of the class is constructed in the model (construction would need
   the vtable);
3. the surrounding body is otherwise expressible - the entry register still has
   to be EAX/ECX/stack, which `screen_regions.py --entry` checks.

The remaining mismatch in the probe above is the argument setup around the call
(retail pushes a live-in register before `call [edx+0x14]`), which is the same
"register the source cannot set" class the other families hit; the *dispatch*
itself is no longer an obstacle.
