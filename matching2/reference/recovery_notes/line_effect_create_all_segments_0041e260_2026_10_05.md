# Line effect: create all segments (0x0041E260) — exact

`LineEffectSweep_0041e260::CreateAllSegments` is byte-exact (609 bytes) in
`src/game/line_effect_create_all_segments_0041e260.cpp`, compiled as an
additional source of the `item_line_bounded_0041f400_2026_09_28` cluster.
`make` and `make EXACT=1` pass.

The earlier candidate was 601 bytes. What closed it:

- Retail has the list registrar of 0x004489D0 expanded in place. The model
  now calls an inline member written like the recovered registrar: the id is
  a small class with `operator++` and a by-value `operator==`, used as
  `++next_id; if (next_id == 0) ++next_id;`. The by-value comparison is what
  produces retail's `inc ecx; mov eax,ecx; test eax,eax` copy; a plain
  `int` counter gives `inc dword ptr [mem]`.
- `++count` is the first statement of the loop body (before the script index
  and the resource load).
- The position is written through `float* out = &object->position.x` as
  `out[0]`, `out[2]`, `out[1]`, which orders the flag and bucket stores
  against the x87 stores.
- `point.z` is advanced through a `volatile float&` like the bounded sibling
  at 0x0041F400, which keeps `fld point.z; fadd step.z`.
