# Animation list registration leaves: ABI and codegen blocked

2026-09-13 experiment, revisited against all four live retail bodies: the
four registration leaves at `0x004489D0`, `0x00448A50`, `0x00448AC0`, and
`0x00448B40` total 460 bytes. The early lab models capture the list actions
but use incorrect per-variant node offsets; they are not ready for promotion.
The private entry convention and exact instruction schedule also remain open.

## What the disassembly fixes

All four are the same body with a different list and direction. Each takes
three register arguments: the object that receives the new id, the entity that
owns the embedded node, and the manager (`0x00491C10` at every call site).

| address | function | node | list head/tail | insert |
| --- | --- | --- | --- | --- |
| 0x004489D0 | RegisterPrimaryBack | `entity+0x04` | `manager+0x72DAD4` / `+0x72DAD8` | at the tail |
| 0x00448A50 | RegisterPrimaryFront | `entity+0x04` | `manager+0x72DAD4` / `+0x72DAD8` | at the head |
| 0x00448AC0 | RegisterSecondaryBack | `entity+0x04` | `manager+0x72DADC` / `+0x72DAE0` | at the tail |
| 0x00448B40 | RegisterSecondaryFront | `entity+0x04` | `manager+0x72DADC` / `+0x72DAE0` | at the head |

The body: clear the node, set `owner = entity`, link it into the list (both the
empty case and the non-empty case), store the new tail/head, then

```c
    uint32_t id = ++manager->next_id;    // +0x732454, wraps modulo 2^32
    if (id == 0) id = ++manager->next_id;
    entity->id = id;
    *out_id = id;
```

The front variants clear `node.next` before testing it in their nonempty-list
branch. A normal unaliased C++ model can fold the apparent always-zero arm;
the retail instruction sequence and possible aliasing must be preserved when
matching source is revisited.

`next_id` is `+0x732454`, four bytes before the fade block, and the four list
head/tail pointers fill `+0x72DAD4..+0x72DAE0` — both inside the manager header
the render batch already carries.

## The measured convention mismatch

Retail enters with the object in **EAX**, the entity in **EBX** and the manager
in **EDX**, keeping ECX/ESI/EDI for scratch (the append bodies push only ESI,
the head-insert bodies push ESI and EDI). That is exactly the shape of its
callers, e.g. `0x0042C670`:

```asm
mov  edx, dword_491C10     ; manager, reloaded per call
lea  eax, [esp+10h]        ; object, a fresh local address
; EBX still holds the entity from earlier in the caller
call 0x004489D0
```

With the synthetic context in the lab (a loop calling all four with
`&objects[i]`, `&entities[i]` and the manager global) LTCG chooses a different
set for the same sources: manager in ECX, entity in EDI, object in EBP, i.e. it
prefers callee-saved registers because the loop keeps both pointers live across
all four calls. Rooting a leaf only forces the public (stack) convention, so
the ABI cannot be pinned that way either.

## What is in the lab

`matching2/build/recovery-lab/animation-register/` holds the four sources, the
shared header (`include/th10/render/animation_lists.hpp`), the schema-1 manifest
(`animation_register_lists.json` with the layout split around the four
addresses) and the context driver. They build and link; only the entry
registers differ. The next experiment is to shape the driver like the retail
callers — one call per site, the entity live across the call, the object a
fresh local address and the manager loaded from `0x00491C10` at the call — so
that EAX/EBX/EDX become the cheapest assignment, or to recover two of the
twenty-odd real callers so the convention follows them.

Two harness facts learned here and now patched into
`matching2/build/pipeline-lab/lab.py`: cluster functions need
`__declspec(noinline)` or LINK inlines them into the context and `/OPT:REF`
discards the zero-length contributions, and layout gap chunks must stay under
about 128 KB or wine's cl.exe dies in pass 2 with a heap-space error.
