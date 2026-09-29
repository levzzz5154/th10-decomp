# D3D resource/reset cluster recovery note

Historical attempt. On 2026-09-27, the complete 59-byte initializer and
82-byte list-release body were recovered and promoted as exact readable C++.
See `d3d_resource_manager_initialize_00449aa0_native_ltcg_2026-09-27.md` and
`d3d_resource_list_release_00449e50_native_ltcg_2026-09-27.md` for the current
sources and compiler contexts. The other functions below remain separate work.

Date: 2026-09-12

Scope: `0x00438880` (103 bytes), `0x00449E50` (82 bytes), `0x00449AA0` (59 bytes),
`0x00438A60` (111 bytes), and `0x004391F0` (236 bytes), 591 live bytes total.

## Final disposition

No region was promoted. The two edited production sources were restored to their
retail ASM bodies, the three task-local initializer/context/manifest files were
removed, and no `regions.json` or shared tooling file was edited.

The focused raw-ASM baseline passed for every owned source and extent:

| Region | Extent | Baseline |
| --- | ---: | --- |
| `0x00438880` `d3_d_resource_manager_destroy_00438880.cpp` | 103 | EXACT |
| `0x00449E50` `d3_d_resource_list_release_resources_00449e50.cpp` | 82 | EXACT |
| `0x00449AA0` `d3_d_resource_manager_initialize_00449aa0.cpp` | 59 | EXACT |
| `0x00438A60` `game_render_targets.cpp` | 111 | EXACT |
| `0x004391F0` `device_reset.cpp` | 236 | EXACT |

## Recovered semantics and ABI evidence

`D3DResourceManager_Initialize` receives the manager in EAX and returns with a
plain RET. It initializes both embedded 0x24-byte lists: clears the reserved,
pending, first, and last fields, clears flag bit 0, and makes each list owner
point to itself.

`D3DResourceList_ReleaseResources` receives the list in EAX, the owner on the
stack, and returns with `ret 4`. The retail loop reads each node's resource and
next pointers, enters the critical section at `0x00492274` through the import
pointer at `0x004660B0`, increments `0x0049231C`, calls the read-only
`Scheduler_Remove` dependency at `0x00449F60` with resource in ECX and owner in
EDX, leaves through `0x004660B4`, and decrements the counter. Retail keeps the
two import pointers in EBX/EBP and the node/resource state in EAX/ESI/EDI.

`D3DResourceManager_Destroy` has a frameless SEH setup, takes its manager as a
stack argument, stops the worker at `0x0044C150`, releases primary and secondary
lists through the EAX-list/stack-owner convention, then inlines the six pending
slot stores. This makes list release and its Scheduler/critical-section ABI a
hard dependency for a safe conversion.

`GameRenderTargets_Release` uses the target object in ESI. A nonnegative capture
handle calls `0x00448270` with its custom ECX/EBX/EAX/stack setup and then writes
`-1`; a nonnegative primary handle calls `0x00448450` with its EAX/stack setup
and then writes `-1`. These helper register conventions are not expressible by
ordinary isolated TU compilation.

`Device_Reset` tests the D3D device vtable at `0x00491C30` (`+0x44` cooperative
level and `+0x40` reset), destroys reset-sensitive entities, resets and
reinitializes the renderer, sets `0x00491FD4` to 2, releases render targets,
and optionally runs the snapshot-directory/path/existence loop before calling
the screenshot capture path. Its exact body depends on the render-target
helper, reset reinitializer, and screenshot/file custom ABIs.

## Exact native-LTCG attempt

The initializer was the only semantic body taken through a complete temporary
native-LTCG placement and byte probe. The manager-in-EAX context produced the
correct 59-byte compiler contribution at `0x00449AA0` and the declared context
placement, but its best readable candidate differed from retail at the first
byte offset `+0x10`:

```
candidate: 89 40 14
retail:   83 E1 FE
```

The candidate scheduled the primary owner/first/last stores before the primary
flag mask/store. Retail masks and stores the primary flags first, then computes
the secondary-list address and stores the primary owner/first/last fields. The
remaining candidate stream was structurally equivalent, but the focused gate
was therefore rejected. No candidate source or layout/context artifact was
retained.

The list-release semantic draft was constrained by the import-IAT and
`Scheduler_Remove` custom ABI, but was not retained without a complete exact
multi-source placement proof. The render-target and device-reset bodies were
left ASM because their helper/register and COM-vtable dependencies were not
bounded into an independently exact candidate during this pass.

## Best next dependency

First recover or reuse an exact native-LTCG cluster for the 82-byte list-release
body together with the already exact/read-only `Scheduler_Remove` at
`0x00449F60`, absolute IAT symbols `0x004660B0/0x004660B4`, critical-section
storage `0x00492274`, and depth byte `0x0049231C`. Then use that cluster as the
callee context for the 103-byte manager destroy body. Separately, bound the
custom call contexts for `0x00448270` and `0x00448450` before attempting
`0x00438A60`; only after that should `0x004391F0` be attempted with the D3D
device vtable and screenshot/file dependencies.
