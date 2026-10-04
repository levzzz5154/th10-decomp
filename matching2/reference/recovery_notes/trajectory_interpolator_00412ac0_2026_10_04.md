# Exact trajectory interpolator at 0x00412AC0

The complete 652-byte function is now generated from the shared readable
`Interpolator<T>::Step` template, instantiated for `TrajectoryVec2` in
`src/game/trajectory_interpolator.cpp`. The old naked assembly translation
`src/game/fun_00412ac0_00412ac0.cpp` is removed.

The retail bodies at 0x00412AC0 and 0x00441AD0 have identical instruction bytes
except for the relative calls to the same floating-point conversion and easing
functions. Comparing the two complete 652-byte bodies found six differing bytes,
all in those two displacement fields. This suggested reusing the existing
interpolator implementation instead of transcribing the older trajectory model.

Live Ghidra decompilation of 0x00412AC0 independently confirms the same field
layout and modes: frame timer at +0x20, duration at +0x34, mode at +0x38;
finish returns target except in accumulating mode 7, mode 17 accelerates,
mode 8 computes four Hermite terms, and the remaining modes use the easing
function. The receiver arrives in ESI and the output pointer in EDI; the output
pointer is also returned in EAX with a plain RET.

The two-component trajectory vector has its own named type and the same
component-wise arithmetic as Vec2. Keeping distinct types gives native LTCG
two independently placed template instantiations, as the retail image requires.
This is a source model that reproduces the binary, not proof of the original
source's type names.

The existing easing cluster now includes the trajectory source. Its compiler
context advances one trajectory instance alongside the other instances. Only
complete compiler contributions are selected; the 262-byte context is unselected.
No compiled instruction bytes or operands are rewritten.

Validation:

```sh
python3 matching2/tools/matching/probe.py --source src/game/trajectory_interpolator.cpp
make EXACT=1
make
```

The integrated probe reports all six cluster functions EXACT, including the
previous int, Vec2, Vec3, Int3, and easing recoveries.
