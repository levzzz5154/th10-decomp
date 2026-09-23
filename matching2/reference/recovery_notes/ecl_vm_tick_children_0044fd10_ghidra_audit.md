# ECL child tick `0x0044FD10` Ghidra audit

**Result:** Keep the 146-byte region in its current exact assembly form. Its
control flow is recoverable, but its public entry depends on a private EDI
argument that ordinary MSVC x86 C++ cannot declare. Converting it in isolation
would require changing the callers or preserving assembly glue, so this needs
a wider compiled ECL execution cluster.

## Entry and callers

Ghidra's function body spans `0x0044FD10..0x0044FDA1` (146 bytes). The source
listing agrees with both return paths ending in `RET 4`. At entry:

- `EDI` is the owning ECL record.
- `[ESP+4]` is a float tick delta (one stack dword).
- `EAX` returns `0` after a normal pass or `-1` when the embedded/root
  interpreter returns nonzero.
- The callee removes the tick-delta argument.

Ghidra decompiles the delta as a `float` parameter and the owner as
`unaff_EDI`. That distinction matters: the inferred `__stdcall(float)`
signature is incomplete and cannot describe the live call contract.

There are three direct call sites:

| Call site | Owner in `EDI` | Tick delta | Caller behavior |
|---|---|---|---|
| `0x0040E0FE` | `[EBP+0x14D8]` in `FUN_0040DC80` | dword loaded from `*[ECX]`, where `ECX = [EBP+0x128]` | tests `EAX`; nonzero exits through the caller's failure/stop path |
| `0x0040E205` | same `FUN_0040DC80` field | same timer value | tests `EAX` the same way |
| `0x0042BFFE` | `[ESI+0x2DC]` in `FUN_0042BFC0` | immediate `0x3F800000` (`1.0f`) | continues into its record cleanup/transition path |

The two bullet-update calls are in the still-naked `0x0040DC80` body; the
third is in the still-naked `0x0042BFC0` body. A standalone C++ function with
the owner in ECX/EDX would change the call ABI, while a C++ function with an
explicit owner parameter has no way to require that MSVC place it in EDI.

## State traversal and updates

The `0x0040C730` reset note documents the record layout independently: the
active-instance cursor is at `record+4`, the embedded interpreter state is at
`record+8`, and the record's own list node is at `record+0x1030`. Each list node
is `{instance, next, previous}`.

`EclVm_TickChildren` starts at that embedded sentinel. For each node it saves
`next`, sets `record->active` (`+4`) to the node's `instance`, then calls
`0x0044E1A0` with the current state in EAX and the tick delta on the stack. The
first node represents the record's embedded/root state. If that interpreter
call returns nonzero, the function returns `-1` immediately. For subsequent
heap-backed child nodes, a nonzero interpreter result means the child is
finished: it frees the active state, splices the node out of the doubly linked
list by repairing `next->previous` and `previous->next`, clears both links,
and frees the node. It then continues from the saved `next` pointer.

After reaching the list end, it restores `record->active` to `record+8` and
returns zero. This matches the Ghidra decompilation, the retail instructions,
and the record/list fields documented by the reset and child-spawn routines.

## Conversion boundary

The direct callee `0x0044E1A0` also uses a private ABI: the active interpreter
state enters in EAX, the delta is stack-passed, and it returns with `RET 4`.
Its execution body calls the ECL operand/value resolvers, scratch-stack
helpers, child-spawn logic, and other private-register helpers. The adjacent
resolver notes for `0x0044FE40`, `0x0044FF80`, and `0x00450030` document the
same EAX/ESI/ECX register-flow constraints. These boundaries make a small
`0x0044FD10`-only native-C++ conversion unsupported by the observed ABI.

No source body or manifest mapping was changed for this audit; no build,
probe, or test was run.
