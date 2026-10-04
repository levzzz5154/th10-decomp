# 0x0040B110 (148 bytes): one scheduling swap left — parked

Not promoted; the region is still assembly.

## Candidate

Second function in the 0x0040B070 cluster, same body as `EffectFileOwner::SpawnEffect`
but taking the animation file directly:

    AnimationHandle __stdcall SpawnEffectFromFile(int kind /*EAX*/, AnimationResource* file, void* argument)

All 148 bytes match except the order of three instructions in the entry block:

    retail:  push esi / mov esi,[0x491c10] / shl eax,4
    ours:    shl eax,4 / push esi / mov esi,[0x491c10]

Source order of the manager load and the table index has no effect on this.

## Why (c2 list scheduler, traced)

`reference/compiler_traces/scheduler/` replays the cluster link under winedbg and dumps the
scheduler's ready list, picks and dependency edges.

priority = (critical path + successor count + 32 if the node is a load) << 10, ties to the
lower sequence number. In our build:

| node | path | successors | priority |
|---|---|---|---|
| shl eax,4 | 31 | add; anti edge to the call (EAX) | 33 |
| push esi | 30 | push edi; anti edge to mov esi | 32 |

Retail's order needs priority(push esi) >= priority(shl), i.e. one more successor on
`push esi` or one fewer on `shl`. With the final instructions identical, only the call's
register sets can supply that: an anti edge push esi -> call would exist if the call to
0x00449950 were considered to define ESI.

## Controls already run (do not repeat)

- Rough model of 0x00449950 versus the exact `AnimationPool::Allocate` body with the real
  `Entity_Init` callee: identical schedule.
- A callee that really writes its parameter: the pass moves the parameter to EAX, so the
  convention no longer matches retail.
- Retail's 0x00449950 only reads ESI. None of its 74 call sites reuses ESI after the call,
  which is consistent with (but does not prove) the call being treated as an ESI kill.
- Escaping `data_00491c10` (address taken) made the function worse.

## Open question

What makes retail's call to 0x00449950 carry an extra dependency from `push esi`. The
matched sibling 0x0040B070 is insensitive to that edge, so it gives no evidence either way.
