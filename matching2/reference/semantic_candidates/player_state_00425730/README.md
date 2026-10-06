# Complete player-state update at 0x00425730

Ordinary C++ for the complete 3,112-byte player-state owner, including its five
switch states, 33-point history, collision/bullet sweeps, revive/death/respawn
paths, 32 indicators, invulnerability blink, four collision bounds, timers,
sequence updater and final effect update. The native owner is 3,024 bytes,
including its 20-byte switch table, with 2,812 differing overlapping bytes in
136 instruction groups. It remains assembly-owned in production.

This [source](player_state.cpp) extends the shared scheduled-effect graph to
28 genuine complete functions. Twenty-four functions / 2,731 bytes are
diagnostic-exact after address-only rebinding. Twenty-six prior diagnostic
bodies are unchanged; sequence Update is the one changed prior body.

The real outer owner naturally gives sequence Update its retail EAX receiver.
The complete 174-byte sequence updater now passes the unchanged normal
fixed-address raw-equality probe, without instruction edits, masking, constant
aliases or synthetic callers. The isolated fixed graph has 21 raw-exact bodies
out of 28. Sequence Update was already selected C++ under the production
frame_timer cluster's synthetic context. This candidate has not replaced that
production context and earns zero new recovered bytes.

All 3,953 bounded cases pass: 1,965 pickup/helper cases, 215 effect cases,
328 shared effect/pickup sequences, 186 spawn cases, 312 sequence cases and
947 new full player-state cases. Tests compare whole player, collision pool,
bullet/front state, animation manager/objects and relevant globals, normalized
external call inputs/order, return values, register preservation, stack cleanup,
x87 balance and control word. The new cases cover all five states and important
frame thresholds, focus/power gates, death/respawn variants, both indicator
motion modes, first/last indicator slots, three speeds and precision controls,
blink, missing/disabled configuration, hold-counter saturation, history levels
and repeated updates.

Collision/activation, bullet operations, movement, contact, familiar refresh,
player initialization, power display, angle return, item creation, gauge,
scene/input mode and VM are explicitly scripted external boundaries in the
full-owner tests. Their public native declarations do not yet establish all
retail private conventions. The complete native timer, motion, indicator,
sequence and effect graph executes. No entry or instruction bytes are patched.
These tests prove bounded owner behavior under the stated collaborators, not
complete game integration or the unmatched owner's raw equivalence.

Reproduce from the repository root:

```sh
python matching2/reference/semantic_candidates/player_state_00425730/audit_receipt.py
python matching2/reference/semantic_candidates/player_state_00425730/measure.py corrected_graph --fresh
python matching2/reference/semantic_candidates/player_state_00425730/player_differential.py corrected_graph
python matching2/reference/semantic_candidates/player_state_00425730/differential.py corrected_graph
python matching2/reference/semantic_candidates/player_state_00425730/effect_differential.py --candidate matching2/build/experiments/player_state_2026_10_06/corrected_graph/model.exe --output matching2/build/experiments/player_state_2026_10_06/corrected_graph/effect_differential.json
python matching2/reference/semantic_candidates/player_state_00425730/sequence_differential.py corrected_graph
python matching2/reference/semantic_candidates/player_state_00425730/spawn_differential.py corrected_graph
python matching2/reference/semantic_candidates/player_state_00425730/schedule_differential.py corrected_graph
python matching2/reference/semantic_candidates/player_state_00425730/prepare_fixed_probe.py corrected_graph
python -m matching2.tools.matching.probe --project matching2/build/experiments/player_state_2026_10_06/sequence_fixed_gate/project --source graph/schedule_update.cpp --output matching2/build/experiments/player_state_2026_10_06/sequence_fixed_gate/probe --oracle matching2/build/oracle/th10.exe --json
```

The archived compiler trace observes 109 events and preserves all 28 complete
native bodies plus the entire 9,216-byte code section. Evidence and limits are
described in the [recovery note](../../recovery_notes/player_state_genuine_00425730_2026_10_06.md).
