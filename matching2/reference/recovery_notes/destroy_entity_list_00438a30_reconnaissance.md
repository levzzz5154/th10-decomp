# 0x00438A30 DestroyEntityList - virtual dispatch through slot 2

2026-09-18. Found by `tools/waves/screen_regions.py --entry eax --calls`: 43
bytes, one call, entry in EAX.

```
push esi
mov esi,eax                 ; the base pointer arrives in EAX
push edi
add esi,3AD4E0h             ; the table is at base + 0x3AD4E0
mov edi,20h                 ; 32 slots
loop:
  mov eax,[esi]
  test eax,eax
  je  next
  mov ecx,[eax]             ; the object's vtable pointer
  push eax
  call dword ptr [ecx+8]    ; virtual call, slot 2
  mov dword [esi],0         ; clear the slot
next:
  ...                       ; advance and loop
```

So the source is a loop over thirty-two object pointers that calls each entry's
**third virtual function** and clears the slot. Two things are needed to express
it and neither is free:

- the callee is a **virtual** call, so the model needs a class whose virtual slot
  order puts the callee third (`call [ecx+8]` follows from the declaration
  regardless of the vtable's contents), and a class with virtuals makes the
  compiler emit a vtable it must not define here;
- the table base arrives in EAX, so the cluster path is required as well.

Worth noting that the screen's call-shape test passes this region even though the
call is indirect - `mov ecx,[eax]` and `push eax` do look like an ECX/EDX/stack
setup. A future version should treat `call dword ptr` as a separate class.

## Model attempted: 38 bytes against 43

With the class declared as above (three virtuals, never instantiated) and the
slot table reached as `(Entity**)((unsigned char*)this + 0x3AD4E0)` inside a
`for (i = 0; i < 0x20; i++)` loop that calls `Slot2()` and clears the entry, the
cluster emits **38 bytes against retail's 43** and diverges at the second byte
(`33` where retail has `8b`), so the loop's register and addressing shape differs
from the start - the model indexes the table while retail walks a pointer in ESI
with a separate counter in EDI (`add esi,4; dec edi; jne`). Rewriting the loop as
a pointer walk with a down counter is the first thing to try next.

## Pointer-walk rewrite: 42 bytes, one short, 19 differing

Rewriting the loop as a pointer walk with a down counter -

```cpp
    Entity_00438a30** slot = (Entity_00438a30**)((unsigned char*)this + 0x3AD4E0);
    for (int remaining = 0x20; remaining != 0; remaining--) {
        Entity_00438a30* entity = *slot;
        if (entity != 0) {
            entity->Slot2();
            *slot = 0;
        }
        slot++;
    }
```

- moves the emitted extent from 38 to **42 bytes against retail's 43** and the
  first difference from byte 1 to byte 0x11 (`0e` against `06`, a displacement),
  leaving 19 differing bytes. So the walk shape is right and what remains is the
  register assignment inside it (retail keeps the slot pointer in ESI, the counter
  in EDI and the entity in EAX) plus whatever accounts for the missing byte.
