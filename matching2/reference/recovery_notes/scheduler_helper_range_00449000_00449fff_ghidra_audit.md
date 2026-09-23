# Scheduler/helper range audit: `0x00449000`–`0x00449FFF`

Date: 2026-09-23. Read-only manifest/source review and live Ghidra review.
No source, manifest, or symbol-table changes were made. No build, probe, or
test was run.

## Result

No small `kind: asm` function in this range has both a conventional C++ entry
ABI and an entirely conventional set of callee ABIs. The closest short
candidate is the 11-byte tail wrapper at `0x00449440`, but it jumps to
`FUN_004451C0`, whose live Ghidra decompilation has an `in_EAX` receiver in
addition to its ECX parameter. The wrapper therefore carries an implicit EAX
input from its caller and cannot be represented by an ordinary no-argument
C++ function call.

The only scheduler-body candidate with a standard entry signature is
`0x00449C00` (`int __stdcall FUN_00449C00(int)` in Ghidra). It is a 273-byte
dispatcher with callback-driven control flow and a 35-byte compiler-local
switch table in its 308-byte manifest region. Its existing semantic attempt
and exact-output measurements are recorded in
[`scheduler_main_tasks_00420270_00420470_00420670_00420870_00449c00_00449d40.md`](scheduler_main_tasks_00420270_00420470_00420670_00420870_00449c00_00449d40.md);
the candidate did not match the retail extent/entry shape. It is not a small
helper suitable for a focused single-function conversion.

## Live Ghidra ABI evidence

| Address | Manifest size | Live entry/callee evidence | Decision |
| --- | ---: | --- | --- |
| `0x00449010`, `0x00449090`, `0x004490E0`, `0x00449140` | 73–118 each | The create-family bodies carry the manager in ESI to `FUN_00449950`, the animation object in EDI, and private-register arguments to `FUN_00449870`, `AnimationObject_LoadScript`, or a registration helper. | Reject as isolated C++ conversions; family/callee ABI work is already documented in [`animation_create_families.md`](animation_create_families.md). |
| `0x00449210`, `0x00449250`, `0x004492F0`, `0x00449350` | 54–111 | The stop-frame paths consume SI/DI live-ins; the position paths consume the vector through ESI. Ghidra also reports private values around the `AnimationManager_Find` and update calls. | Reject: formal C++ parameters do not describe these entry values. Existing family evidence is in [`animation_create_families.md`](animation_create_families.md). |
| `0x00449440` | 11 | The source is `mov ecx,[data_00491c10]; jmp 0x004451C0`. Ghidra identifies `FUN_004451C0` as `__fastcall` with ECX parameter 1 and a separate phantom `in_EAX` receiver. The wrapper does not establish EAX. | Best short near-miss; blocked by the helper's hidden EAX receiver. |
| `0x00449630` | 21 | Ghidra reports an ESI live-in which is dereferenced after calling `FUN_004492A0`. | Reject: ESI is not a formal parameter or ordinary C++ receiver. |
| `0x004496A0`, `0x004496D0` | 34, 36 | Ghidra reports phantom `in_EAX` in both functions. The decompilation uses it as a pointer to obtain the lookup key; ordinary arguments remain on the stack. | Reject: hidden EAX input. The `0x004496D0` compiler-ordering residual is also recorded in [`animation_create_families.md`](animation_create_families.md). |
| `0x004497D0` | 70 | Ghidra reports live-ins in ESI, EBX, and EDI in addition to the explicit ECX parameter. | Reject: multiple private entry values. |
| `0x00449700` | 111 | Ghidra has no function boundary or xrefs; the source/disassembly show a balanced local frame but the input texture pointer arrives in EAX and feeds several indirect surface calls. | Reject: private EAX input. The focused source note is [`texture_surface_clear_00449700.md`](texture_surface_clear_00449700.md). |
| `0x00449AA0` | 59 | Ghidra decompiles an `in_EAX` object pointer and no formal parameters; its body initializes two linked-list heads in that object. | Reject: private EAX receiver. The prior source attempt and caller evidence are in [`d3d_resource_reset_cluster_00438880_00449e50.md`](d3d_resource_reset_cluster_00438880_00449e50.md). |
| `0x00449E50` | 82 | Ghidra reports an `in_EAX` list receiver plus a stack argument. Its `Scheduler_Remove` call is ECX/EDX fastcall, but that does not repair the entry ABI. | Reject: private EAX receiver. Existing caller and exact-shape blocker are documented in [`d3d_resource_reset_cluster_00438880_00449e50.md`](d3d_resource_reset_cluster_00438880_00449e50.md). |
| `0x00449EB0` | 30 | The source fragment receives its object in EDI and calls `0x00449E50` twice; Ghidra has no function boundary at this entry. | Reject: fragment/private EDI entry. |

Other residual entries in the range are unassigned fragments or bodies with
no Ghidra function boundary (`0x00449770`, `0x00449780`, `0x00449820`,
`0x00449860`, `0x00449A50`, and `0x00449A70`). Their register/fragment
blockers are already described in [`0044xxxx_wave18.md`](0044xxxx_wave18.md)
and their source comments. The small scheduler leaf helpers around
`0x00449AE0`–`0x00449F60` are already semantic in the current manifest.

## Revisit condition

The short near-miss at `0x00449440` becomes eligible only if a source-level
model can legally supply `FUN_004451C0`'s EAX receiver without an assembly
shim. The scheduler dispatcher becomes a later cluster candidate if its
callback/register context and switch-table ownership are modeled together;
the existing exact-output attempt must be treated as failed evidence, not as
an exact C++ replacement.
