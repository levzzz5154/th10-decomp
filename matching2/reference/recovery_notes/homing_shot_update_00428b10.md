# Homing shot update 0x00428B10

2026-10-02. Ordinary C++ in `layout/ltcg/homing_shot_update_00428b10.json`;
the whole EXE is exact.

* The function is only named by the callback table slot at 0x0047477C (its
  neighbours there are 0x00428AD0 and 0x00428C20), so it keeps plain
  `__fastcall` registers: shot in EDX, ECX unused. The context calls through
  that slot.
* Retail keeps the speed on the x87 stack across the call to
  `Angle_Normalize`. A separately compiled unit spills it; the pass only keeps
  it when it can see the callee, so both angle helpers are modelled as anchors
  at their retail addresses.
* Which `return 0` owns the shared epilogue decides the tail. Retail's shared
  one follows the plain acceleration, so that code comes last in the source
  and the steering block returns on its own.
