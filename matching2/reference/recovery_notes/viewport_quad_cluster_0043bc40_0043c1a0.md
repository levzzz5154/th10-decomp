# Viewport, clear/present, and solid quad native-LTCG batch

Five complete game functions add 1,361 ordinary-C++ bytes. The existing 133-byte
AnimationManager batch flush remains exact. The initial five-function batch used schema 2: ColorViewport::Draw was the real
entry and ApplyDefaultViewport the only extra root. A subsequent expansion adds
the 501-byte DrawGradientQuad. The final cluster uses schema 1 with a gradient
caller context, and roots only the two real public callers. All six real bodies
are compiler-visible in one native /LTCG invocation; the five other sources are
separate /GL inputs. The previous synthetic flush caller is removed.

## Source and ABI findings

The real callers naturally establish the private conventions that prevented
isolated recovery: Flush receives its manager in ESI, DrawSolidQuad receives its
rectangle in EDI and color in EBX, and ClearAndPresentTwice receives color in ESI.
Only the two actual public callers retain their public entry conventions. Rooting
any of these private helpers would change their ABI and is unnecessary.

The quad uses four typed vertices and ordinary position constructors/assignments.
MSVC generates the retail 92-byte frame (80 bytes of vertices plus a 12-byte
position temporary), including its integer aggregate-copy scheduling. Its draw
and texture-state restoration use typed device calls. No manual instruction
encoding or synthetic copies are needed. The color-overlay caller constructs a
640x480 rectangle, sets the viewport, and combines color with shifted alpha.

The other public caller restores all six viewport fields, then calls the private
clear/present helper. The helper performs two clear/present cycles and resets the
device after a failed present. Both functions matched on their first native probe.

The gradient quad follows the same typed geometry construction, with one color
per vertex. Its rectangle arrives in EDI and its four colors remain on the stack
(RET 16). A pointer-array caller context produces this private convention while
the two real public callers retain their public entries. The first compiled body
was already the exact 501 bytes; only the initially estimated synthetic context
extent needed correction to the MAP-measured 65 bytes. Moving the shared vertex
types to the header leaves the solid quad unchanged. No context bytes count as
recovered game code.

## Validation

`python3 matching2/tools/matching/probe.py --source src/render/texture_stage_reset.cpp
--output matching2/build/probe_render_gradient` reports all six bodies exact.
`make verify MSVC_ARGS='--jobs 32'` passed with all 487,936 bytes identical.
Progress: 448 ordinary-C++ regions / 26,118 bytes; 2,137 assembly regions /
362,864 bytes. Whole executable SHA-256 remains
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

The native link uses no constant aliases, instruction changes, address operand
changes, masked bytes, or reference bytes as build input. Layout gaps contribute
zero recovered game-code bytes.

| Address | Function | Bytes | Native body SHA-256 |
| --- | --- | ---: | --- |
| 0x00442F50 | AnimationManager_00442F50_Flush | 133 | `a97acc3906f5866a83e0d11c2a842827d2da474b31fbccd35e0597d1fca55ad9` |
| 0x0043BDA0 | DrawSolidQuad | 483 | `c685125b4a4765d4082bd2ddd43932c0855bea37efaf94e36b472411ec4696da` |
| 0x0043C1A0 | ColorViewport_Draw | 134 | `db709f25eeb521c2df3232206722e504e9d7fcad221392e03119ec32168193ec` |
| 0x0043BC40 | ClearAndPresentTwice | 135 | `f651177efc102eaf1d29d62ce82f15f85272cc566d075319bc3b6555f332e36b` |
| 0x0043BCD0 | ApplyDefaultViewport | 108 | `41b7d3207e0b26ebe5568b0e835a0286c575be47810215b6aee99adc1e4dc013` |
| 0x0043BFA0 | DrawGradientQuad | 501 | `ea6d41a1d2a45eda8a4d11b13a458f1d75577bbb08db8a3769d3db7ef72b83bc` |
