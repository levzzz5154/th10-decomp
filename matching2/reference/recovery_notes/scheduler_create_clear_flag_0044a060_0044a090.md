# Scheduler callback wrappers with flag bit 1 clear

## Regions and disposition

This note records ordinary C++ semantic models for two 43-byte regions:

| Address | Candidate source | Retail extent | List |
| --- | --- | ---: | --- | --- |
| `0x0044A060` | `matching2/reference/semantic_candidates/unassigned_0044a060.cpp` | 43 | primary |
| `0x0044A090` | `matching2/reference/semantic_candidates/unassigned_0044a090.cpp` | 43 | secondary |

Both bodies create a scheduler callback task, store its context at `+0x20`,
clear raw task flag mask `0x2` (bit 1), register it, and return the task
pointer. The primary wrapper uses `Scheduler_RegisterPrimary`; the secondary
wrapper uses `Scheduler_RegisterSecondary`. The models follow the neighboring semantic
wrappers at `0x0044A000` and `0x0044A030`, which perform the same sequence but
set raw flag bit 1.

The maintained source files retain the retail assembly and the manifest rows
remain `kind=asm` with their existing symbols. The readable models are archived
under `matching2/reference/semantic_candidates`; no byte comparison or build
was run.

## ABI evidence

Live Ghidra `th10.exe` disassembly of `0x0044A060..0x0044A08A` shows a
43-byte body: it saves ESI, pushes EAX as the callback argument to
`0x00449ED0`, loads the original stack argument from `[ESP+8]` after the
stdcall call into the task's `+0x20` context field, clears flag mask `0x2`,
and calls `0x00449AE0` with the task in ESI and scheduler pointer on the
stack. EDI passes unchanged through that call. The helper decompilation uses
`unaff_EDI` to assign the task priority, confirming EDI's role. The wrapper
returns the task in EAX, restores ESI, and ends in `RET 4`; Ghidra disassembles
`INT3` fill starting at `0x0044A08B`.

Ghidra has no function object at `0x0044A060`, and `get_xrefs_to` reports no
incoming references to the entry. Thus there is no direct caller available to
independently confirm this address's contract. As corroborating context only,
the sibling wrappers at `0x0044A000` and `0x0044A030` are called from
`FUN_0043C970`; their call sites load callback into EAX, set priority in EDI,
and push context. Those sibling xrefs do not establish a caller for
`0x0044A060`.

Ghidra's decompilation of `0x00449ED0` confirms that it allocates a `0x24`-byte
task, initializes its callback/list fields, stores the callback at `+0x08`,
and returns the task pointer. Ghidra's decompilations of `0x00449AE0` and
`0x00449B70` expose the task as an ESI live-in, priority as an EDI live-in,
and scheduler as the single stack parameter. Both optionally invoke and clear
the task's register callback, update the task priority, and insert its link in
a priority-ordered list under the scheduler critical section. The primary
helper uses the head at scheduler `+0x14`; the secondary helper uses `+0x38`.

The C++ models clear the raw flag word at task offset `+0x04` with `&= ~2u`,
which is mask `0xFFFFFFFD`: it clears bit 1 and preserves the heap-owned bit
at mask `0x1`. In the `SchedulerTask` declaration, this is the low bit of the
31-bit `reserved_flags` field following `heap_owned`. This is the inverse of
the `|= 2u` operation in the already semantic siblings.

## Semantic model and limitations

The C++ methods model the callback as the method receiver (`this`), with
`context` and `priority` as the two method arguments. This matches the
neighboring `SchedulerCreatePrimary_0044A000::Create` and
`SchedulerCreateSecondary_0044A030::Create` source shape. The operation is
ordinary C++; no inline assembly is used.

For `0x0044A060`, the current model is not a drop-in ordinary C++ definition
for the observed entry ABI. `SchedulerCreatePrimaryClearFlag_0044A060::Create`
is a default MSVC `__thiscall` method: its receiver is expected in ECX and
both declared arguments are stack-passed. Retail instead consumes callback
from EAX, context from the sole stack argument, and priority from EDI. Ghidra
has no function object at this entry and reports no incoming xrefs, so there
is no known caller that could be adapted to call a separately declared C++
helper. The source method's entry convention cannot be fixed by changing its
parameter types; a compatible bridge would need special register handling.
Keep this region as `asm` until a pure-C++ entry strategy can be evidenced.
No build, probe, or test was run, and no byte-equivalence claim is made.
