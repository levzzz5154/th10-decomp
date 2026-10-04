# Floating text drain 0x00419120 (2026-10-03)

Byte-exact as `RecoveryIndicatorLink_00419120::Drain` in
`src/game/effect_indicator_queue.cpp`, selected in the LTCG cluster
`layout/ltcg/recovery_mark_text_and_dispatcher_004479d0.json` together with its
caller `Update` (0x00419650) and the scheduler callback (0x004198A0).

## What the last 15 instructions needed

For a while the model differed from retail only in scratch registers around the
three animation-create calls (333 of 348 instructions). Three source details
decided them:

- The slot index is not cached in a local. Each branch reads `state->slot`
  again for the script number (`state->slot + 2` / `+ 12`); the optimiser
  hoists the load above the intensity compare by itself, into ECX.
- The animation file pointer is a local of its own in each branch
  (`void* animations = data_004776e0->text_animations;`), which is what puts it
  in EAX before the script number is pushed.
- The handle is copied straight out of the pointer the create call returns
  (`handles[slot] = *AsHandle(Create(...))`). Wrapping the call in a
  `__forceinline` helper that returns the handle by value adds a temporary and
  moves the result to EAX/EDX instead of EDX/ECX.

Declaring the create helper as a member returning the handle by value gives the
same caller code, but its body then no longer fits the 118 bytes at 0x00448DB0
unless the registrar at 0x004489D0 also returns by value, which would change
every other caller in the cluster context. The pointer-returning form is kept.
