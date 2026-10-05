# Item spawn (0x0041BB00) — parked one instruction short, 2026-10-05

The region stays assembly-owned. The model in
`layout/ltcg/item_spawn_caller_allocator_2026_09_28.cpp` (unselected anchor of
the `item_line_bounded_0041f400_2026_09_28` cluster) now compiles to the
retail size, 819 bytes including both switch tables, and differs from retail
in the placement of one instruction.

## What brought it from 235 differing lines to one residual

- **Visible polar setter.** The cluster now carries a stand-in body for
  `ItemPolarVelocity_0041bb00::SetPolar` at 0x0041BEB0 (30 bytes) whose
  address is published by the context, so it keeps the public thiscall
  convention. Retail knows the setter preserves EDX; with the setter as an
  opaque absolute symbol the kind-8 item had to live in a callee-saved
  register, which displaced the manager from ESI to EDI and cascaded through
  the whole function. Without the published address the stand-in gets a
  private convention (`this` in EAX) and everything moves again.
- **Position copy is a struct assignment** (`*location = *position` on a
  three-float POD), which gives retail's block copy through a temporary
  destination pointer (`mov eax,edi`). Three scalar stores do not.
- **Slot scan** is `do { if (!item->state) goto found; ++slot; ++item; }
  while (slot < 150); return 0;`. A counted `for` with `break` is unrolled
  six times and changes the argument convention.
- **`kind` is remapped in place** (no second local), and the switch lists
  cases 10/11 before 1/4.
- **No `_ReadWriteBarrier`.** The timer restart is a plain inline helper.
- The second `Configure` call passes the resource as a by-value struct read
  straight from `data_004776f0->item_animation`; a named `resource` local
  makes the member load reuse ECX.

## Residual

Retail loads the resource bank pointer before the `kind == 11` branch and
keeps it as a scratch temporary:

```
cmp ebp,0Bh
mov ecx,[004776F0h]
jne  L1
mov dword ptr [esi+3E4h],4
mov eax,17Ah
jmp  L2
L1: lea eax,[ebp+176h]
L2: mov edx,[ecx+3E0B50h]
push edx
```

The model emits `mov ecx,[004776F0h]` at `L2`. Everything else is identical.

Tried and rejected (each either leaves the load at `L2` or makes the bank a
register candidate, which then reuses ECX for the member load and rotates the
identifier load to EDX/ECX):

- a named `bank` local before the branch, also initialised in both arms, also
  shared with the `kind == 10` path, also through an inline accessor;
- the script as a conditional expression inside the call, in both argument
  orders, with and without an inline wrapper;
- separate `Configure` calls per arm (no tail merge: three full copies);
- letting the address of `data_004776f0` escape in the context: the load
  still sinks, and the first call's `display_kind = 1` store moves ahead of
  its own bank load, which retail does not have.

The registers show retail's bank pointer is a block-local scratch temporary
(ECX, then EDX for the member, EAX for the identifier), yet it sits in the
predecessor block. The mechanism that hoists it has not been identified; a
c2 trace of the late flow passes on this function is the next step.
