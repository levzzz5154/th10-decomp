# 0x0043AF30 — MIDI sequencer timer tick remains assembly

Live Ghidra inspection of `th10.exe` on 2026-09-23 confirms a 0x1D9-byte body at `0x0043AF30..0x0043B108` (manifest names it `asm_FUN_0043af30_0043af30`). I kept the existing naked body in `src/platform/midi_sequencer.cpp`: the tick itself is understandable, but one required helper edge carries private register and x87 state that an ordinary call cannot express.

## Entry and references

Ghidra decompiles the entry as `void __fastcall FUN_0043af30(int param_1)`: the sequencer pointer arrives in ECX and is copied to EDI. There is no direct-call xref; the only function xref is a data reference from `0x0046F80C`, the first slot of the timer target vtable. The timer callback source declares `MidiTimerTarget::OnTimer()` as a no-argument virtual returning `int`, but discards its return. The body itself returns without setting a meaningful EAX value on either return path.

## Recovered behavior

The entry computes an unsigned 64-bit event time as:

```
event_tick_base
    + (ticks_per_quarter_note * elapsed_timer_ticks * 1000)
      / tempo_microseconds
```

If fade is active and its position has reached its duration, it sets the fade volume at `+0x2C8` to zero and returns immediately without advancing the tick counter. Otherwise it stores `1.0f - position/duration` as the fade volume, converts its product with the float at `0x00470BF4` (bytes `00 00 00 43`, i.e. `128.0f`, corrected by live retail memory inspection on 2026-09-30) using the private x87 helper, compares that integer with `+0x2CC`, and conditionally applies channel volumes through `FUN_0043B7A0`. It then stores the step and increments fade position.

For each track at `+0x138` (count `+0x118`, stride `0x20`), an active track sets the “any active at tick entry” flag. While its signed next-event time at `+4` is no later than the computed unsigned 64-bit event time, `FUN_0043B110(this, track)` processes one event and the timer-derived event time is recomputed. The tick's 64-bit elapsed timer count at `+0x128` is incremented. If no track was active when the loop examined it, the routine resets all tracks through `FUN_0043ACE0`.

## ABI blocker

`FUN_0043B110` takes explicit stack arguments (sequencer, track) and returns with `ret 8`, so its boundary can be represented by a typed stdcall declaration (corrected 2026-09-30). The blocking fade edge is `FUN_0043B7A0`: the tick pushes one stack argument (zero), while the callee reads its receiver from EDI and returns with `ret 4`. It calls `FUN_00463B2C` with the scale already in x87 `ST(0)`; that helper consumes `ST(0)` and returns a 64-bit value in EDX:EAX, so a normal C++ prototype cannot describe either edge. The callee also emits per-channel WinMM messages through the fixed import slot at `0x00466298`. Preserving this helper call requires the original register/FPU sequence or a semantic/native rewrite of the helper and its dependencies, which is outside this function-only change. `FUN_0043ACE0` is also called with the receiver in EDI, though the project has a readable `MidiSequencer::ResetTracks()` implementation that could be integrated under a suitable native-LTCG cluster.

The entry signature needed at the virtual boundary is a no-explicit-argument receiver in ECX. For parent integration, a semantic definition needs a vtable-compatible alias replacing manifest symbol `_asm_FUN_0043af30_0043af30`; the current vtable stores the absolute address directly at `0x0046F80C`. The current `MidiSequencer` header does not declare this virtual method, while `MidiTimerTarget::OnTimer()` is declared as `int`. Any promotion must reconcile that declaration and the return contract; the callback currently ignores EAX.

No build, probe, or tests were run.

2026-09-30 follow-up: a joint tick/volume ordinary-C++ candidate now exists at
`reference/semantic_candidates/midi_tick_volume_0043af30.cpp`. The compiler's
native float-to-integer conversion can supply the x87 helper call; it must not
be represented by a fabricated ordinary prototype accepting a float. The EDI
receiver and exact instruction selection remain unproven until a native-LTCG
probe. See `midi_tick_volume_2026-09-30.md` for current evidence and remaining gates.
