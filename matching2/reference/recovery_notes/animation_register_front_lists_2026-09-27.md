# Front-list registration leaves, 2026-09-27: complete real bodies, still not exact

The 112-byte leaves at `0x00448A50` and `0x00448B40` remain assembly. Nothing
from this wave was promoted. All experiment edits are under
`matching2/build/experiments/register_front_lists` and the independently owned
`register_front_lists_helper` directory. The maintained source and manifests
were not changed.

Fresh read-only Ghidra MCP decompilation/disassembly confirms both embedded
nodes begin at **entity + 4**. The old convention note's `entity + 0x14` and
`entity + 0x34` table entries are wrong. Primary head/tail are manager offsets
`0x72DAD4/0x72DAD8`; secondary uses `0x72DADC/0x72DAE0`; the shared counter is
`0x732454`. Both leaves take manager EDX, entity EBX, out EAX and return the out
record through EAX with plain RET.

## A complete real body preserves all four exact callers

The current registered ABI anchors capture the successor before clearing the
node. Retail clears `node->next`, then reads it in the nonempty branch. The
plain real body lets MSVC eliminate that read and changes the entry convention,
which breaks its already recovered creators. An instruction-free
`_ReadWriteBarrier()` at the start of the nonempty branch preserves those
retail reads and reestablishes the correct callee convention:

```cpp
node[0] = entity;
node[1] = 0;
node[2] = 0;
unsigned char* head = *(unsigned char**)(manager + head_offset);
if (head == 0) {
    *(void**)(manager + tail_offset) = node;
} else {
    _ReadWriteBarrier();
    if (node[1] != 0) {
        *(void**)(head + 4) = node[1];
        *(unsigned char**)((unsigned char*)node[1] + 8) = head;
    }
    node[1] = head;
    *(void**)(head + 8) = node;
}
*(void**)(manager + head_offset) = node;
int id = ++*(int*)(manager + 0x732454);
if (id == 0) *(int*)(manager + 0x732454) = id + 1;
*(int*)entity = *(int*)(manager + 0x732454);
*(int*)out = *(int*)(manager + 0x732454);
```

The final scratch project moves each real body into its own render source and
selects the complete 112-byte contribution rather than an ABI anchor. The
ordinary production probe covers both leaves and **all four creator
contributions** (73-byte bucket and 95-byte positioned creator for each list):

`matching2/build/experiments/register_front_lists/normal_full_probe.json`

- Primary registrar: 112/112 bytes, **34 differing**, first `+0x1C`.
- Secondary registrar: 112/112 bytes, **34 differing**, first `+0x1C`.
- All four creators: complete 73/73 or 95/95 bytes, **zero differences**.
- No compiler, ownership, extent, relocation or normalization failures.

The residual is the same local split decision as the back leaves: EDI holds
the counter instead of ESI, dragging its save/restore out of the nonempty arm.
A barrier after the head store fixes load/store scheduling but retains EDI,
112 bytes with 35 differences.

## Counter ESI and the entire prefix are now reachable

Two independent source shapes produce all of retail's first **87 bytes**,
including its EDI save/restore inside the nonempty arm and its complete
`load ESI / inc ESI / copy ECX / test ECX / store ESI / pop ESI / JNE` counter
sequence:

1. A barrier after the head store, then a barrier inside the zero arm before
   `counter = id + 1`.
2. A barrier after the head store, then `switch (id) { case 0: counter = id + 1;
   break; }`.

Both are **115 bytes versus retail 112**, 28 differing bytes, first `+0x57`.
The first difference is JNE's displacement (`0A` instead of `07`); the zero
arm emits a ten-byte `mov counter, 1` instead of seven bytes
`inc ECX; mov counter, ECX`. The two final reread stamps and RET are otherwise
retail's instructions, displaced by three bytes. Both twins reproduce this
identical residual while all four creators remain exact.

Preserved primary artifacts:

- `bodies/zero_rw_start.cpp`, `runs/zero_rw_start/result.json`
- `bodies/switch.cpp`, `runs/switch/result.json`
- `secondary_runs/secondary_zero_rw_start/result.json`
- `secondary_runs/secondary_switch/result.json`

Ghidra's old-value spelling (`old = counter; id = old + 1; counter = id; if
(!id) counter = old + 2`) plus the head-store barrier reaches the first
**74 bytes** exactly, including the ESI counter load. Its 114-byte body retains
the old value across the branch, emits `lea ECX,[ESI+1]` and `add ESI,2`, and
moves POP ESI to the end: 33 differing bytes, first `+0x4A`. It does not close
the split residual.

## Other measured families

Fine barriers between counter load, increment, copy and store; register/type
variants; volatile reads/stores; explicit copies; pointer casts; loop and goto
forms; old-value mutations; local optimization pragmas; and an inline C++ ID
class all fail. Barrier-before-RHS, barrier-after-RHS and barrier-after-increment
inside the zero arm all preserve the same 115-byte constant-folded form.

The independent helper sweep tested list-only, list+first-increment, inverse
zero-fixup, scalar/aggregate/pair returns, RAII, postfix return plus caller
preincrement, union/pointer conditions and casts. Postfix helper + caller
preincrement reaches the same 115-byte prefix-exact form. Its eight union and
pointer zero-expression variants all fold the zero correction to constant 1.
Several manual/RAII forms also change the manager entry to ESI and break
callers, so their smaller byte counts are not progress toward an exact leaf.

Do not promote any candidate from this wave. The remaining requirement is
**the ESI split with the seven-byte nonconstant zero-arm correction in the same
112-byte contribution**, while both existing creator contributions stay exact.
