# 0x00409270 `ScoreRuntimeState::RunArrayReleaseCallback`

Ghidra read-only inspection of `th10.exe` on 2026-09-23 confirms the callback
boundary, its owner argument, and its only direct call. The region is now
represented as semantic C++ in `regions.json`, with the former ASM record
preserved in `previous_record`.

## Boundary and body

The manifest row at `0x00409270` gives the region a size of 10 bytes and the next
record begins at `0x0040927A`. Ghidra's function record independently identifies
`00409270` as the entry and `00409270..00409279` as the body:

```asm
00409270  push ebx
00409271  mov  ebx,ecx
00409273  call 004091c0
00409278  pop  ebx
00409279  ret
```

This is a one-block function. The one direct callee is `FUN_004091c0`; there are
no direct callers in Ghidra's call graph because this callback is invoked through
a stored function pointer. Ghidra's default `void __stdcall FUN_00409270(void)`
prototype is incomplete: the entry reads `ECX` immediately and forwards that
value in `EBX` to the callee.

## Callback owner and indirect invocations

`FUN_004089c0` contains the sole static address xref to this entry, at `00408A11`:

```asm
00408A11  push 00409270
00408A16  mov  [ebx+0xc],esi
00408A19  call 00449ed0
...
00408A32  mov  [esi+0x20],ebx
```

`FUN_00449ed0` stores its stack argument at the returned callback node's `+8`
field. The two callback-list dispatchers, `FUN_00449c00` and `FUN_00449d40`,
invoke the stored function at `00449C70` and `00449DA6`; both load `ECX` from
callback-node `+0x20` immediately before the indirect call at node `+8`. In the
registration sequence above, that `+0x20` field is set to the owner retained in
`EBX`. This establishes the callback's entry receiver as the owner in `ECX`.

## Behavior and C++ recovery

The callee `FUN_004091c0` uses `EBX` as its runtime-state receiver, tests bit 0
of the byte at `+0x378C`, dispatches the two embedded entity arrays if set, and
returns `1` in `EAX` on either path. Therefore the wrapper preserves `EBX`, moves
the owner from `ECX` into `EBX`, calls that routine, restores `EBX`, and returns
the callee's result unchanged.

A plain C++ member model for the wrapper is:

```cpp
int ScoreRuntimeState_004091c0::RunArrayReleaseCallback() {
    return ReleaseFlaggedEntityArrays();
}
```

The adjacent recovery note `004091c0_00409230_wave13.md` records a prior
scratch measurement in which this member body emitted all 10 retail bytes when
`ReleaseFlaggedEntityArrays` was co-compiled as an unrooted definition in the
same `/LTCG` link, while the callee remained 95/95 bytes. Its measured model
preserves the private `EBX` call convention as a caller/callee pair. The two
source files and synthetic context now use the shared declaration
`include/th10/game/score_runtime_state_release.hpp`; the callback is a rooted
layout function while the synthetic context call continues to expose the
callee body without rooting its public `__thiscall` receiver. This note records
the earlier exact measurement; no build or probe was run for this source
integration. The manifest's live symbol is the decorated member
`?RunArrayReleaseCallback@ScoreRuntimeState_004091c0@@QAEHXZ`.
