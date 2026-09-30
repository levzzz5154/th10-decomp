# Resource object initializer — 0x00449870

Date: 2026-09-27

## Result

The complete 217-byte C++ candidate reaches the normal probe and native
contribution gate, but differs in 93 bytes, first at `0x00449878`. It is not
exact and must not be promoted. Production code and region ownership were
not changed by this task.

The real preserving loader at `0x0043E7E0` is co-visible in the focused
cluster and emits all 194 retail bytes exactly, with the correct private
EAX resource, EDX object, ECX index convention. This removes the loader ABI
as an unresolved dependency for the next initializer attempt.

## Live evidence

Live Ghidra MCP decompilation of `th10.exe` at `0x00449870` and disassembly
of the preserving loader at `0x0043E7E0` were queried during this attempt.
The initializer's retail assembly and callers show public ECX resource,
stack object/index, and RET 8. It zeros position at `+0x340`, base position
at `+0x334`, and render offset at `+0x34C`; sets `+0x35C` bit `0x40000000`;
sets the short script index at `+0x38A`; writes `0x10` to bytes `+0x3A1`
then `+0x3A0`; and invokes the preserving loader.

## Source and compiler evidence

Ordinary by-value three-float constructor temporaries with implicit copy
assignment naturally emit the retail 12-byte scratch area and all nine
stack-zero/load/store chains. The initial source emits 207 bytes because
it folds the flags update into an OR against memory and saves only ESI.
A staged volatile flags read before the third vector assignment produces
the correct register flags update and the complete 217-byte extent.
`_ReadWriteBarrier()` between the second vector assignment and that flags
read improves the instruction scheduling without emitting an instruction.

The best source retains a named object layout with vector, flags, script
index, and trailing byte fields. A public rooted member has the same
decorated signature as the landed creators' initializer declaration:
`?InitializeObject@AnimationResource_00449870@@QAEPAXPAXH@Z`.
Its co-visible loader model explicitly returns the already present manager
pointer on success and zero on failure. That return signature emits the
same 194 loader bytes as the existing void declaration; the loader is an
ABI anchor only, never selected game code in this focused cluster.

The remaining differences are localized source/allocation choices:

* Retail saves ESI and EDI at `0x00449877`/`0x00449878` and keeps the first
  two vector destinations in ESI and their component-copy temporary in EDI.
  The candidate initially uses ECX destination and ESI copy, saving EDI
  later at `0x004498DB`.
* Retail delays `mov eax,ecx` until `0x004498DD`. The candidate moves the
  resource from ECX to EAX at `0x00449878` to free ECX for those first two
  vector destinations.
* The tail differs only in the ordering of the short script-index write
  and the third vector's final z write. Retail writes the index first;
  the candidate writes z first.

## Bounded measurements and artifacts

The scratch project is
`matching2/build/experiments/resource_initialize_object/msvc`.
Its best source is restored from `attempt07.cpp`; its unique layout,
context, and preserving-loader anchor files are under `layout/ltcg`.

| Attempt | Main lever | Native extent | Differing bytes |
| --- | --- | ---: | ---: |
| 01 | Ordinary ctor temporary assignments | 207 | 182 including extent difference |
| 02 | Staged ordinary flags read | 207 | 182 including extent difference |
| 03 | Staged volatile flags read | 217 | 98 |
| 04 | Barrier after second vector | 217 | 93 |
| 05 | Creator-compatible pointer return; exact pointer-return loader anchor | 217 | 93 |
| 06 | Disable global optimization locally | 221 | 214; displaced entry and outlined helpers rejected |
| 07 | Named object/vector layout | 217 | 93 |
| 08 | Default zero vector constructor | 217 | 93 |
| 09 | Public fastcall form with unread EDX slot | 217 | 93 |
| 10 | Reuse one destination-vector pointer variable | 217 | 135 |

Attempts 05, 07, and 08 reached the full normal probe. Earlier provisional
context extents failed metadata validation only; all measurements above
read complete compiler contributions from the native PE/MAP. The context
is 60 bytes at `0x00449950`; the selected function remains 217 bytes at
`0x00449870`. No instruction or address operand was patched.

`attempt07.json` records the best normal-probe result. Additional compact
evidence is in `bounded_measurements.json` and
`best_candidate_disassembly.txt` in the lab directory. The best selected
body SHA-256 is
`493fdec54ff8a533cdd192b339e1d29ced1a6d1ec2de8261a4835f751f973c11`.

The next useful lever is a source or constructor/copy topology that keeps
the first two vector destinations and component temporary in the same
ESI/EDI variables as the third, delaying the resource ECX-to-EAX transfer.
Repeating the unchanged helper or context does not address that residual.
