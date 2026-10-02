# 0x004076A0 death shrink step

`PlayerDeathShrinkState_004076A0::AdvanceDeathShrink`, 209 bytes, promoted from
the anchor model in `bullet_runtime_caller`.

The model used `_ReadWriteBarrier` to stop the compiler forwarding the
normalised heading into the `SetPolar` argument. Two source shapes replace it:

- Store the heading through a pointer and read the member directly afterwards.
  The pointer store is not forwarded to the member read, so the field is
  reloaded, and because the member read cannot alias the speed store it is
  still hoisted between the `fld` and `fmul` as in retail. Reading through the
  same pointer instead leaves the load after the speed store.
- The slow timer path needs `*speed + elapsed` with the speed read as
  `const volatile float`, the same form as the ease step at 0x004078E0.

`#pragma optimize("p", on)` was tried and reloads every float, which retail
does not do.
