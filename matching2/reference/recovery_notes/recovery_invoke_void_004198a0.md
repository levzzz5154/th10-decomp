# Recovery note: scheduler callback adapter at `0x004198A0`

Date: 2026-09-23. The focused review used read-only Ghidra analysis of
`th10.exe`. Keep the current naked body in
`matching2/msvc/src/game/recovery_invoke_void_004198a0.cpp`: its direct call
depends on a private `EBX` receiver that an ordinary C++ call cannot express.

## Boundary and body

Ghidra reports one function from `0x004198A0` through `0x004198A9` (10 bytes):

```asm
004198a0  push ebx
004198a1  mov  ebx,ecx
004198a3  call 0x00419650
004198a8  pop  ebx
004198a9  ret
```

This is a small adapter. The callback's context arrives in `ECX`; the adapter
preserves the caller's nonvolatile `EBX`, copies the context there for the
fixed callee, restores `EBX`, and returns the callee's `EAX` unchanged.

## Callback use and direct calls

Ghidra found no direct function callers for `0x004198A0`. Its only incoming
cross-reference is a data reference at `0x00418E32` in `FUN_00418E30`. That
function registers `InvokeVoidCallback` with `FUN_00449ED0` and stores its
manager pointer in the task's context slot at `+0x20`. The scheduler runner at
`0x00449C00` loads the callback from `[ESI+0x10]`, loads the context from
`[ESI+0x20]` into `ECX`, then calls the callback through `EAX`. This confirms
the wrapper's callback entry convention and explains why the target address
escapes as data rather than appearing as a direct call.

`0x00419650` has only this wrapper as a direct caller. Its decompilation uses
`unaff_EBX`, and the first instruction reads `[EBX+0xD8]`; the function
continues using that register as its manager/state receiver. It finishes by
setting `EAX` to `1` and returning. The adapter does not alter that result.
This callback is registered on the primary scheduler list, whose runner
ignores the callback result on this path. Despite the old
`Recovery_InvokeVoid` label, this callback returns an integer status; it is
not a `void (*)(void)` forwarding function.

## Recovery decision

The outer entry can be described as an integer callback receiving one context
pointer in `ECX`, but its direct call is not an ordinary ABI call: the callee
expects the same pointer in `EBX` and takes no stack arguments. Declaring the
callee with a normal `__fastcall` or `__thiscall` prototype would pass its
receiver in `ECX`, while a no-argument prototype loses the required receiver
entirely. Preserve the naked adapter until the callee's implementation and
register contract can be recovered in a form the compiler can emit. No source
edit or manifest change was made for this address.
