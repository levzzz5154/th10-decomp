# Scheduler secondary flag-clear wrapper at `0x0044A090`

## Boundary and references

Live Ghidra disassembly of `th10.exe` gives a 43-byte straight-line body from
`0x0044A090` through the three-byte `RET 4` at `0x0044A0B8..0x0044A0BA`.
`0x0044A0BB..0x0044A0BF` is five `INT3` bytes, and the next function starts at
`0x0044A0C0`.

Ghidra does not define a function at `0x0044A090`. `get_function_callers` and
`get_function_xrefs` therefore cannot resolve an entry function, and direct
xref queries report no references to the entry. A bulk check of every
instruction start in `0x0044A090..0x0044A0B8` also returned no incoming
references. Searching the executable for the little-endian address
`90 A0 44 00` found no immediate-address match. There is no identified direct
caller or callback registration at this address in the current Ghidra database.

## Entry contract and behavior

The retail body consumes the callback from EAX (`PUSH EAX` before calling
`0x00449ED0`), reads the context from the original `[ESP+4]` argument after
the callback allocator returns, and returns the allocated task in EAX. EDI is
not overwritten; `0x00449B70` consumes the priority from its EDI live-in. The
wrapper saves and restores ESI and ends in `RET 4`.

The body then stores the context at task offset `+0x20`, loads the scheduler
from `0x00491BE4`, clears mask `0x2` in the task word at `+0x04`, pushes the
scheduler pointer, and calls the secondary-list registrar at `0x00449B70`.
The following `MOV EAX,ESI` returns the allocated task.

Live Ghidra decompilation of `0x00449ED0` confirms allocation and initialization
of a `0x24`-byte task with the callback stored at `+0x08`. Its decompiler
signature is `void`, but this wrapper's immediate use of EAX as the task
pointer establishes the returned value. The `0x00449B70` decompilation uses
`unaff_ESI` as the task and `unaff_EDI` as the priority, then inserts the task
link into the scheduler's secondary list at `+0x38` under the scheduler
critical section.

The C++ model in `src/unidentified/unassigned_0044a090.cpp` expresses this
operation as `SchedulerCreateSecondaryClearFlag_0044A090::Create`. The flag
update now uses `SchedulerTask::reserved_flags &= ~1u`; the low bit of that
31-bit field is raw task flag bit 1, so this clears raw mask `0x2` while
preserving `heap_owned` in raw bit 0.

## Conversion blocker

The behavior is simple and has an ordinary C++ model, but the current source
does not establish a replacement-compatible call contract. Retail receives
the callback in EAX and priority in EDI, while a normal MSVC member method
receives `this` in ECX and its explicit parameters on the stack. The secondary
registrar call also relies on task in ESI and priority in EDI, with only the
scheduler pointer on the stack; the current typed source call is a normal
three-argument `__stdcall` call. No direct caller or callback reference was
found to validate an alternate call-site model or an LTCG context that would
preserve those register inputs.

Keep the manifest row at `0x0044A090` as assembly until a caller-inclusive
semantic integration establishes both the entry values and the private
registrar call contract. The C++ source is a readable behavioral model, not
evidence that the current 43-byte region can be replaced by it. No manifest or
shared-symbol changes were made; no build, probe, or test was run.
