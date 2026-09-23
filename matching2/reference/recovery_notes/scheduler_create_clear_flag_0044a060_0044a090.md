# Scheduler callback wrappers with flag bit 1 clear

## Regions and disposition

This note records ordinary C++ semantic models for two 43-byte regions:

| Address | Source | Retail extent | List |
| --- | --- | ---: | --- |
| `0x0044A060` | `matching2/msvc/src/unidentified/unassigned_0044a060.cpp` | 43 | primary |
| `0x0044A090` | `matching2/msvc/src/unidentified/unassigned_0044a090.cpp` | 43 | secondary |

Both bodies create a scheduler callback task, store its context at `+0x20`,
clear raw task flag mask `0x2` (bit 1), register it, and return the task
pointer. The primary wrapper uses `Scheduler_RegisterPrimary`; the secondary
wrapper uses `Scheduler_RegisterSecondary`. The models follow the neighboring semantic
wrappers at `0x0044A000` and `0x0044A030`, which perform the same sequence but
set raw flag bit 1.

The manifest was not changed: both regions remain `kind=asm` with their prior
unassigned symbols. No byte comparison or build was run for these models.

## ABI evidence

Live Ghidra disassembly of `0x0044A060..0x0044A08A` and
`0x0044A090..0x0044A0BA` confirms matching instruction shapes. At entry the
callback value is in EAX, the priority is live in EDI, and the task context is
the single stack argument at `[ESP+4]`. Each wrapper saves/restores ESI,
returns the task in EAX, and ends in `RET 4`.

The callback is pushed for `SchedulerCallback_Create` at `0x00449ED0`; its
stdcall cleanup leaves the wrapper's context argument available for the later
load into ECX. The wrapper places that context in the returned task's `+0x20`
field, then loads the scheduler pointer from `0x00491BE4`. The registration
call receives the task in ESI, priority in EDI, and scheduler pointer on the
stack. The primary body calls `0x00449AE0`; the secondary body calls
`0x00449B70`.

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

Ghidra does not define either candidate address as a function, and reports no
incoming xrefs to either start. Therefore the EAX/EDI entry values and context
argument are supported by the observed instruction flow and analogy with the
semantic siblings, but no real caller was available to independently validate
them. The method declarations are a source-level model, not proof that the
compiler will retain the private EAX/EDI convention or emit the retail
`RET 4` sequence. A future native-LTCG context and byte probe are required
before promotion; no exactness claim is made here.
