# `AnimationSlot_ReleaseRetail` at `0x004136C0`: keep the ESI ABI bridge

Read-only live-Ghidra audit, 2026-09-23. No build or candidate measurement was
run for this audit.

## Boundary and symbols

Ghidra's `th10.exe` program has one function beginning at `0x004136C0` and
ending with `RET` at `0x00413720`. The inclusive instruction range is
`0x004136C0..0x00413720` (97 bytes, exclusive end `0x00413721`). The raw
Ghidra symbol is `FUN_004136c0`; the recovered name is
`AnimationSlot_ReleaseRetail`; its maintained assembly entry is
`asm_AnimationSlot_ReleaseRetail_004136c0`.

## Caller ABI confirmed in retail code

This entry takes no stack argument. Its slot pointer is already in `ESI`:

- `FUN_00414370` loads `[EBP+0x9EB8]` into `ESI`, tests it, then calls
  `0x004136C0` at `0x004143CD`. After the call it still uses `ESI` as the
  argument to `free`.
- `FUN_00414570` loads `[EBX+0x9EB8]` into `ESI`, tests it, then calls at
  `0x0041457E`. It also uses `ESI` after the call to free the slot.
- A third direct call is at `0x00414553`: the bytes there save `ESI`, load it
  from `EAX`, call the release entry, then use `ESI` and restore it. Ghidra
  reports this cross-reference but does not define a function at `0x00414550`.

The release body reads and writes through `ESI` without changing it. It saves
only `EBX` and `EDI`, and returns without stack cleanup. Its slot input and
preserved-`ESI` behavior are therefore part of the live caller contract, not
just a decompiler guess. An ordinary x86 MSVC function declaration cannot
receive this pointer in `ESI` with no stack argument; using source-level C++
would need an assembly bridge or caller changes.

## Dependencies and behavior

The routine loads the manager/context pointer once from `data_00491c10` into
`EDI`. For each word at slot offsets `0x40`, `0x44`, `0x48`, `0x4C`, `0x50`,
and `0x54`, it pushes the current handle, places that global pointer in `EDX`,
and calls `0x004492A0`; it then clears that word. It makes all six calls,
including for zero handles.

The raw helper is `FUN_004492a0` (`asm_AnimationManager_SetFlag_004492a0` in
the maintained assembly interface). It forwards the stack handle to
`FUN_004491c0`, which uses `EDX` to walk the two lookup lists at manager
offsets `0x72DAD4` and `0x72DADC`; the lookup replaces `ECX` from the stack
handle before comparing. For a match, the helper sets flag `0x04000000` on
the returned object and, when its `+0x18` field is zero, on its child-list
objects at `+0x14`. `FUN_004492a0` returns with `RET 4`, cleaning the pushed
handle. The high-level flag-and-clear operation is expressible in C++, but
its raw helper calls have this EDX-plus-stack shape, and the entry's ESI-only
receiver remains the decisive ABI blocker.

Ghidra identifies the target as `FUN_004136c0` with an unreliable
`__fastcall(undefined4)` prototype and reports `ESI` as an unassociated
register. The two function callers plus the third code cross-reference show
why that prototype must not be used to promote the routine. Retain the naked
body until a caller-inclusive native-LTCG form can preserve the ESI contract
and the helper calls together.
