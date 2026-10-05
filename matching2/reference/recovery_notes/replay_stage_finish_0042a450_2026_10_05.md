# 0x0042A450 replay stage finish (recovered 2026-10-05)

`src/game/replay_stage_finish_0042a450.cpp` compiles to the retail 582 bytes
in its own cluster; `make` and `make EXACT=1` pass. Rig:
`build/experiments/replay_finish_42a450_claude`.

What the straightforward model missed:

* **Loop pointers 4 bytes off.** The option pairs are copied through a
  user-defined `operator=` (member by member). The compiler's block copy of
  the same 8-byte struct gives the same `mov` pairs but strength reduction
  anchors its pointers on a different reference (`+0x32DC`/`+0x154` instead of
  retail's `+0x32E0`/`+0x158`); separate `.x`/`.y` statements anchor on a
  third one (`+0x32D8`).
* **Record loop not unrolled.** The recording copy is a nested loop (options
  outside, value kinds inside); four explicit struct copies are unrolled
  completely. The playback copy is four explicit statements plus the
  conditional one, so all share one pointer pair.
* **Player kept in EDI across the boss gauge call.** With the callee's real
  body the pass knows EAX (its `this`) survives the call and keeps using it.
  Retail's caller did not know that. The cluster's stand-in for 0x00428E10
  returns a value, which keeps `this` in EAX but makes the caller save the
  player itself.
* The player pointer is read before the `stage` store and again (once) after
  the gauge call, before the block copy; the pointer global is address-escaped
  in the context.
