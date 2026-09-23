# Vector helpers at `0x00441DD0`

Ghidra MCP shows that the 37-byte assembly overlay contains two separate
functions, each with its own return instruction:

* `0x00441DD0` is a 16-byte Vec2 difference operation. It writes
  `out.x = *(EDX + 0) - *(ECX + 0)` and
  `out.y = *(EDX + 4) - *(ECX + 4)` through the output pointer in EAX, then
  uses plain `RET`.
* `0x00441DE0` is a 21-byte Vec2 scaling operation. It multiplies the two
  components of the ECX input by the stack float at `+4`, writes the result
  through EAX, and returns with `RET 4`.

Neither function has callers or incoming references in the current Ghidra
view. The maintained source and manifest now split the former 37-byte overlay
into two semantic C++ candidates at 16 and 21 bytes. The source models the
first as `operand - this` and the second as `this * scale`, using separate
native-LTCG sections and a synthetic caller in
`layout/ltcg/vector_ops_00441dd0.json`. The context's 241-byte extent is
provisional; no build or probe was run, so neither contribution is
byte-verified. Original operator names and roles remain inferred from register
use.

Existing native-LTCG examples to adapt are
[`unassigned_00427d50.cpp`](../../msvc/src/unidentified/unassigned_00427d50.cpp)
with `m2703_pair_difference_00427d50.json`, and
[`cell_pair_scale_00427d80.cpp`](../../msvc/src/game/cell_pair_scale_00427d80.cpp)
with `cell_pair_scale_00427d80.json`. The instruction shapes are close, but
the float Vec2 candidate remains unverified.
