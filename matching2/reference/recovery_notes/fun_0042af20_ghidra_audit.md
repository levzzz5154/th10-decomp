# Effect manager allocation at `0x0042AF20`

## Disposition

Keep `src/game/fun_0042af20_0042af20.cpp` as the exact naked assembly overlay.
Ghidra establishes the high-level operation, but the initializer is called
through a private EAX receiver/result convention and the function installs a
function-specific SEH frame. A normal C++ constructor call would use a
different x86 receiver convention; reproducing this entry as ordinary C++
would cross the initializer and exception-lowering boundaries that this
function currently preserves.

## Caller and entry ABI

`get_function_callers(0x0042AF20)` reports one direct caller: `FUN_0041F990`
at `0x0041F990`, with its call instruction at `0x0041FAB1`. The caller uses a
plain `call`, passes no stack arguments, and ignores EAX afterward. Ghidra
reports a zero-parameter `__stdcall` entry. Since it has no arguments, the
existing source declaration's `__cdecl` spelling has the same call-site stack
effect; the body itself returns with plain `ret`.

## Body and callees

The function spans 97 bytes (`0x0042AF20..0x0042AF80`, exclusive end
`0x0042AF81`). It pushes the SEH state `-1`, records handler address
`0x004655AB`, links a registration record through `fs:[0]`, and changes the
state to zero after the allocator returns. Both exits restore the previous
`fs:[0]` value and discard the 16-byte local frame.

It calls `operator_new` at `0x00452493` with `0x1DCB4` on the stack, then
cleans that four-byte argument. The callee decompiles as Visual Studio's
`operator new(unsigned int)` wrapper around `__nh_malloc`. The returned EAX is
tested. On null, the function writes zero to `DAT_0047783C` and returns. On
success, it calls `FUN_0042AE60` directly with the allocation pointer still
in EAX; it does not copy the pointer into ECX or push it as an argument. The
initializer uses EAX as its base pointer, initializes the manager storage,
and returns the same pointer in EAX (`MOV EAX,EBX` at `0x0042AEDF`). The
caller then stores that result to `DAT_0047783C`.

The initializer's work is consistent with constructing the published effect
manager: it clears `0x772D` dwords (`0x1DCB4` bytes), initializes a score
record and manager subobject, initializes seven score-file slots, calls
`FUN_0042B030`, and returns the original base pointer. Its current assembly
symbol alias is `asm_EffectManager_InitializePoolsRetail_0042ae60`; that
declaration intentionally does not describe the live EAX-based ABI.

## Symbol aliases and next useful evidence

The entry alias already in use by `FUN_0041F990` is
`asm_FUN_0042af20_0042af20` at `0x0042AF20`. The other live aliases used by
the body are `asm_operator_new_00452493` and
`asm_EffectManager_InitializePoolsRetail_0042ae60`; none needs a manifest or
header edit for this retained-assembly disposition.

Revisit a C++ replacement only when a caller-inclusive native-LTCG layout can
preserve the initializer's EAX receiver/result flow and this entry's SEH
lowering, then compare the whole 97-byte region. No build, probe, or test was
run for this audit.
