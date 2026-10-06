# Trigger activation 0x00426CF0: byte-exact C++ recovery

`msvc/src/game/trigger_activation.cpp` now owns all 627 bytes as ordinary C++.
The old naked body was replaced, and the manifest selects the existing public
`_ActivateField_00426cf0@4` entry. It takes the field pointer on the stack and
returns with `RET 4`, as both previously recovered contact callers require.

The complete implementation sets mode four, creates one script-0x162 animation
and thirty-two script-0x163 animations, initializes their flags and layer,
registers them, and places them at the field's position plus (224, 16, 0).
It resets the first timer, queues sound four unless the scene suppresses it,
sets the activation timer to six, loads script zero into the embedded
animation, and clears the player's pending flags once sixty frames have
elapsed. Of the eight owned animation slots, slot two keeps its pending bit.
The position's z component is copied without an offset.

The source uses a view extending the smaller field layout already used by the
rotated-rectangle classifier. Compile-time checks cover the embedded animation,
position, mode, both timers, player entity stride, and the player's accessed
frame/flag/state offsets. Existing `OpenTimer::Set` supplies the retail timer
initialization and final current/elapsed/previous assignment order.

## Native helper graph

`layout/ltcg/trigger_activation_00426cf0.json` places the full allocator,
primary-back registrar, lookup, position setter, sound queue, and script loader
bodies at their retail addresses. These are compiler contexts, not new game
regions. The initializer at 0x00449870 has an ordinary public member boundary
and is bound directly. The selected activation's helper calls reproduce every
retail register handoff and call displacement.

The activation is explicitly rooted so native LTCG retains its public stdcall
boundary. The small direct compiler caller owns no game bytes. No assembly
wrapper, barrier, artificial volatile access, per-source flag, compiler-output
rewrite, oracle-byte inclusion, or equivalence allowance was added.

## Matching source shape

The first full C++ model already emitted the required 627 bytes, with 96 byte
differences. Using literals for the known 224.0f and 16.0f offsets corrected the
x87 operand order. Resetting timers in current/elapsed/previous order removed
the timer-store scheduling differences. Constructing a three-component position
value corrected the initial mode/position scheduling; separate component
assignments delayed the mode store. Declaring the position helper's inputs as
manager, position, ID corrected the final two EDX moves. Its native ABI remains
manager EDX, position ESI, ID on the stack.

All measured full candidates, sources, native maps/images and comparison
receipts are retained in
`matching2/build/experiments/trigger_activation_2026_10_06/`. The first equal
relocated model is `position_parameter_order/`; `native-probe/` proves the full
fixed-address contribution. `integrated-probe/` additionally checks the final
maintained source after formatting, offset assertions and reuse of the existing
scene and timer types. Scratch projection errors were corrected before any
promotion; unsuccessful compile/layout checks are not matching evidence.

Validation on 2026-10-06:

- Scratch and maintained strict probes: all 627 bytes EXACT, including every
  linker-filled reference and the complete native contribution extent.
- `make EXACT=1`: all 487,936 executable bytes exact with both this recovery and
  the WAVE-loader exact promotion.
- `make`: full-image and existing equivalence gates passed; eight other
  equivalent regions remain.
- `git diff --check`: passed.

Progress after both recoveries: 2,245 ordinary C++ regions / 189,790 bytes;
8 equivalent regions / 33,176 bytes; 69 remaining assembly regions / 98,517 bytes.
These changes add 1,311 byte-exact C++ bytes, remove the activation's assembly
body, and remove the WAVE loader's former equivalent/assembly pair. The full
readable, byte-exact, assembly-free objective remains incomplete.
