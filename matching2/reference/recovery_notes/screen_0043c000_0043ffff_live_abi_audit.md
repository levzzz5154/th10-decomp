# Live ABI screen: `0x0043C000–0x0043FFFF`

Audit date: 2026-09-23. Read-only review of the live Ghidra `th10.exe`
program and the current manifest. The range contains 17 assembly rows. No new
standalone C++ conversion was justified in this pass: the small callbacks and
sound helpers either receive state through private registers, or call another
private-register helper. The semantic and cluster notes below contain the
recovered behavior for those rows.

## Focused live checks

* Ghidra has no function object at `0x0043C550` or `0x0043C710`. Its raw
  disassembly confirms both start by capturing ECX as the callback object.
  Their only xrefs are **data** references from the callback registration
  switch in `FUN_0043C970` (`0x0043C9AE` and `0x0043CA64`), so these addresses
  are indirect scheduler callbacks rather than ordinary direct-call leaves.
  `0x0043C550` feeds a live x87 value to `0x00463B2C`; `0x0043C710` calls
  `FrameTimer_Tick` with its embedded receiver in ESI and later uses the
  scheduler's register-based store. See
  [`frame_timer_cursor_cluster_0043c230.md`](frame_timer_cursor_cluster_0043c230.md),
  [`frame_timer_cursor_cluster_0043c460.md`](frame_timer_cursor_cluster_0043c460.md),
  and [`0043a9b0_wave13.md`](0043a9b0_wave13.md).
* `FUN_0043C970` decompiles as a five-stack-argument `__stdcall`, but the body
  dispatches callback pointers and uses the manager in live ESI. Its callback
  registration and scheduler calls are part of the private-register manager
  cluster. See [`ascii_manager_factory_0043c8b0.md`](ascii_manager_factory_0043c8b0.md).
* `FUN_0043CD30` is an ordinary `__thiscall` entry with an HWND stack argument.
  The 786-byte DirectInput/device initializer still calls the private-entry
  resource loader and the DirectSound parser, and a seven-byte call-setup site
  remains compiler-blocked. See [`0043cd30_wave11.md`](0043cd30_wave11.md) and
  the source audit in `msvc/src/platform/sound_device_init.cpp`.
* `FUN_0043D080` has a no-argument thread-start boundary, but its archive-load
  call supplies the path in EAX. Ghidra's xref is the `CreateThread` start
  address in `FUN_0043CCF0`, not a normal call. See
  [`sound_worker_setup_0043d080_ghidra_audit.md`](sound_worker_setup_0043d080_ghidra_audit.md).
* `FUN_0043D390` is the clearest apparent leaf: Ghidra reports
  `undefined4 __fastcall FUN_0043d390(int index, undefined4* manager,
  undefined4 resource_name)`, one direct caller at `0x0043CD30`, and a body
  ending at `0x0043D63B`. Its entry values are explicit (ECX, EDX, one stack
  argument). The obstacle is downstream: calls to `Resource_FindChunk` carry
  size/data/output in EAX/ECX/EDI, then the function builds DirectSound buffer
  structures and invokes COM vtable slots. The prior 281-byte readable model
  did not match the 684-byte row. The source blocker comment now records that
  the entry ABI itself is expressible; no replacement was promoted without a
  new checked model. See [`sound_streaming_cluster_0043a910_0043d120_0043d7d0_0043d950_0043ddf0_0044cbf0_0044cf20_0044d110_0044dad0.md`](sound_streaming_cluster_0043a910_0043d120_0043d7d0_0043d950_0043ddf0_0044cbf0_0044cf20_0044d110_0044dad0.md).
* Ghidra's nominal signatures are misleading for the remaining sound worker
  entries: `0x0043D120` is typed as no-argument `__stdcall` but reads incoming
  EAX; `0x0043D690` takes a path on the stack and a manager in EAX; `0x0043D7D0`
  uses path in EAX and manager in ESI; `0x0043D950` uses index in EAX and
  manager in ESI; `0x0043DAB0` uses manager in ESI; `0x0043DB60` uses manager
  in EBX; and `0x0043DD10` uses index/manager in EBX/ESI plus x87 ST(0). These
  rows need caller-inclusive register contexts. Existing evidence is in the
  sound-streaming note above, [`platform_tail_cluster_0043d790_0044d6a0.md`](platform_tail_cluster_0043d790_0044d6a0.md),
  and [`sound_queue_deceleration_0041d170_0043dc90.md`](sound_queue_deceleration_0041d170_0043dc90.md).
* `0x0043DDF0` has a one-pointer stack boundary but dispatches a 94-entry
  command table and installs register-based callback values. `0x0043E460`
  uses the receiver in EAX, name in EDX, and stack values; `0x0043E8B0` uses
  object/resource/index in EAX/EDX/ECX; `0x0043EE30` is the 532-block ANM
  interpreter whose helper calls use private GPR and x87 inputs. See
  [`00439390_wave12.md`](00439390_wave12.md),
  [`animation_register_resource_0043e460_blocker.md`](animation_register_resource_0043e460_blocker.md),
  [`animation_object_change_script_0043e8b0.md`](animation_object_change_script_0043e8b0.md),
  and [`anm_vm_tick_0043ee30_dependency_audit.md`](anm_vm_tick_0043ee30_dependency_audit.md).

## Disposition

The explicit `__fastcall` at `0x0043D390` is worth revisiting after its helper
and DirectSound call shapes can be represented together. The other assembly
rows in this address band do not expose a safe standalone conversion cut based
on the live callers and callees reviewed here. No manifest or shared-header
change was made. No build, probe, or test was run.
