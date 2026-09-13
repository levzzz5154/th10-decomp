# Sound queue and projectile deceleration

2026-09-13. The 123-byte sound queue at `0x0043DC90` and its 329-byte projectile
caller at `0x0041D170` are recovered together as readable C++98: 452 new bytes.
The queue was one of the roadmap's highest-leverage private-ABI callees, with
33 assembly callers at the start of this batch.

`layout/ltcg/sound_queue.json` uses schema 2, with `ProjectileDeceleration::Update`
as its real entry. Its source and `SoundQueue::Queue` compile separately with
`/GL` under one native `/LTCG` invocation. The queue is neither rooted nor
exported. Native code keeps the caller's ECX entry and chooses ECX for the
queue receiver, EDI for the sound ID, and one stack argument with `RET 4`.
The direct call at `0x0041D19E` is validated against both selected endpoints.

The queue groups pending requests into twelve slots, searches for a matching
sound ID or an unused slot, limits each group to 128 requests, and installs
the priority from the eight-byte sound-definition table for a new group.
The explicit post-search `slot < 12` check reproduces retail's bound check at
`0x0043DCE2`. This complete callee matched on the first native probe, including
its extent and all addresses. The earlier 108-byte candidate described in the
projectile runtime note did not reproduce this source/control-flow shape.

The projectile routine repeats angle/speed changes at a timer threshold,
queues its configured sound, tracks its iteration limit, linearly reduces
speed between changes, updates the polar velocity, and advances the timer.
The initial candidate emitted 326 bytes. Its remaining issues were narrowed
by instruction-aligned comparison:

- Capturing the initial speed once in a float local produces the duplicated
  x87 stack value and final pop in the deceleration expression. Reloading the
  field directly in both subexpressions had shortened this path by three bytes.
- The normal timer increment uses `1.0f`, yielding the compiler's own
  `__real@3f800000`. The normal `constants` layout places that literal at
  `0x00470AFC`; no constant alias or duplicate-definition override is needed.
- A volatile pointed-to time scale retains its load before the slow-path
  addition. The resulting x87 order is `fld [scale]; fadd [elapsed]`.
- Volatile speed and timer-flag accesses, with one explicit cached flag read,
  retain the speed store before inspecting the initialization flag. Without
  them the compiler hoisted the flag load/test across the x87 speed update,
  leaving 22 differing bytes despite identical extent and control flow.
  Making only the flag read follow the next-speed load reduced the difference
  to eleven bytes, but still put it before the speed store. The final source
  preserves the actual observed memory-access order.

Focused production proof:

```
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0041d170_0041d170.cpp \
  --output matching2/build/probe_sound_queue
```

Both complete contributions match, including the native call edge and literal
address. Body SHA-256 values:

```
0041D170  329  3f0bfe05038f1d04ffcd887ea8858d129e312309390fa5ac0c8a8056daf063db
0043DC90  123  29730584bd142aae7f8bb5fc12e03afd883a8d705186ef0719353c8c533249ff
```

The provenance report is
`matching2/build/probe_sound_queue/clusters/sound_queue/report.json`.

`make verify MSVC_ARGS='--jobs 32'` passes for the complete 487,936-byte
executable. SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Progress after this batch is 440 C++ regions / 23,542 bytes and 2,145 assembly
regions / 365,440 bytes. No LTCG infrastructure changed.
