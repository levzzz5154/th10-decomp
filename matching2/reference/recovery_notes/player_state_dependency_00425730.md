# Player-state dependency `0x00425730`

Historical checkpoint. The later [complete genuine player-state graph](player_state_genuine_00425730_2026_10_06.md)
reconstructs the entire owner at 3,024/3,112 bytes and passes 947 owner cases.
It also provides a complete raw-exact 174-byte sequence updater through the
real caller. The larger owner remains assembly-owned.

## Disposition

No semantic promotion was retained. The production owner
`matching2/msvc/src/game/fun_00425730_00425730.cpp` remains the retail naked
assembly, and `matching2/msvc/regions.json` was not edited. The focused
maintained-source probe is exact for the manifest extent: `3112/3112` bytes,
with all relocation targets resolving to their retail VAs.

The temporary raw-layout/native-LTCG candidate compiled to `780` bytes, not
the required `3112` bytes, so it failed the extent gate before byte
comparison. Its temporary layout, context, cluster manifest, proposal, and
probe outputs were removed.

## Recovered behavior

Ghidra's body ranges are `0x00425730..0x004257C7`,
`0x004257D0..0x0042580C`, `0x00425810..0x00425857`,
`0x00425860..0x00425A3C`, `0x00425A40..0x00425B38`, and
`0x00425B40..0x00426340` (`3060` instruction bytes). The live owner also
contains the in-text switch table/alignment tail through `0x00426357`, giving
the independently owned `0xC28`-byte extent.

The incoming stack object is the player record at `+0x458` state and
`+0x478` timer; the surrounding callback context may leave an unrelated
manager value in `ECX`. State behavior is:

- State 0 computes entry Y as `48000 - timer*8000/60`, writes the scaled
  position and four familiar-level words, shifts/prepends the 33-pair entry
  history, emits the early entry effects or the late enemy/bullet sweep, then
  transitions to state 1 at timer 60 and resets its timer aliases.
- State 1 drains 20 power on the focus/shot gate, refreshes attached effects
  and HUD timers, performs the early sweep, and calls movement.
- States 2 and 4 share the death path: at timer 3 state 2 drains 64 power and
  emits the seven-shot fan; at timer 30 it either enters game-over/stage-start
  or respawns with the effect pool and timer/position reset. State 4 first
  updates the hitbox after timer 8 and has the pre-8 revive drain path.
- State 3 performs the timer-15 sweep and bullet-list reset.
- The common tail updates all 32 indicator records, invulnerability blink,
  four rectangle sets, the embedded timers, the hold/frame counter/reset, and
  the final player-tail callback before returning 1.

## ABI and dependency evidence

At `0x00425A8A` the retail body executes `mov edi,ebp` immediately before
calling `0x004250B0`; this is the player-front movement helper's required
incoming-object edge. The target's own entry loads its stack player argument
after `sub esp,1C / push ebx / push ebp`, and returns with `ret 4`. The
animation/effect calls are not ordinary source-level calls:
`0x00426F70`, `0x004269D0`, `0x00427B50`, `0x00428280`, `0x00426610`,
`0x0041BB00`, and the indicator helpers share live register, x87 temporary,
and stack aliases. The candidate preserved the explicit `EDI` movement edge
and bounded calls to the read-only movement/effect/tail helpers, but normal
C++ scheduling produced a short independent body and could not reproduce the
retail x87/register schedule.

## Next dependency

Use a whole-program/native-LTCG cluster that includes this caller-faithful
state body, `0x004250B0`, `0x00426F70`, `0x004269D0`, and `0x00428280`, plus
the manager-owned animation/effect edges. That cluster must model the
stack-owned `ret 4` callback, the `mov edi,ebp` handoff at `0x00425A8A`, the
in-text state switch table, and the x87 indicator/rectangle temporaries before
another semantic candidate can be considered for an exact probe.
