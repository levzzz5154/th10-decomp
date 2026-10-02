# 0x0040B320 polar motion step / 0x0044C2A0 advance

## 0x0040B320 (recovered)

`PolarMotion::Step`, 73 bytes: the inline `Update()` (whose out-of-line copy
is 0x0044C260) followed by `Advance()`. No caller remains in retail; the
record arrives in EAX. Cluster `polar_motion_step_0040b320`, context compiled
under `#pragma inline_depth(0)`.

## 0x0044C2A0 (still assembly; model is the cluster's ABI anchor)

Record layout: position (+0x00), velocity (+0x0C), speed, angle, radius,
radius step, flags (+0x28).

    PolarVec3 offset;                      // function scope, see below
    if (!(flags & 1)) { position += velocity (three member adds) }
    else { offset.SetPolar(angle, radius); offset.z = 0;
           position = offset + velocity; }
    position.x = floor(position.x * 100) * 0.01;  (and y)

- `offset` must be declared at function scope: in an inner block its dead
  `z = 0` store is removed, at function scope the later `floor` calls keep it
  alive, as in retail.
- `operator+` returning a local gives retail's stack temporary and the copy
  through EAX.

Two differences remain with literals (171 bytes, 14 diff lines):

- retail adds the x pair as `fld position.x; fadd velocity.x`; every spelling
  tried gives `fld velocity.x; fadd position.x` (y and z match);
- retail releases the `floor` argument (`add esp, 8`) before the last store
  and the frame separately; the model merges them into `add esp, 0x20`.
