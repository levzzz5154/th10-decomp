# Native-LTCG levers found while recovering 0x40C9A0/0x40C9D0, 0x42AA50, 0x4188A0

- A callee's implicit register input (0x40C9D0 reads the position from ESI)
  only appears when the real callee body is compiled in the same cluster. A
  small stand-in body picks other registers; recover caller and callee together.
- `float`-literal placement: use `data_aliases` (symbol `__real@<hex>`, retail
  address, little-endian bytes); `constants` entries do not rebind literals.
- x87 scheduling inside one block follows statement order of the integer
  loads: reading `position[2]` into a local between the unsigned-to-float
  conversion and its scaling delays the FP chain exactly as retail does.
- A handle passed **by value as a struct** is loaded and pushed before the
  other arguments are evaluated; an `int` parameter lets the manager load
  come first. 0x4492A0 therefore takes `AnimationHandle` by value.
- A pointer formed from a global (`&data_0047770c->extend_banner`) is kept in
  a register across calls, while the same pointer formed from a local copy of
  the global is folded back into base+displacement addressing.
- An `if/else` with one shared trailing call reproduces the duplicated tail
  with the callee-saved pop ahead of the call; an early `return` does not.
- The synthetic caller should pass the real global receiver when retail does:
  with arbitrary receivers the pass reorders a global read ahead of a store
  through `this`.

## Laser spawn and constructors (0x41C510, 0x41C5B0, 0x41C680)

- When the real body of a leaf callee is in the cluster, the pass knows which
  registers it leaves alone and keeps the caller's pointer in EDX across the
  call. Retail keeps it in EBX, so the common constructor 0x41C030 is anchored
  as a stand-in that forwards to an opaque absolute body: EDX stays the
  argument register and nothing is assumed to survive.
- A pointer used once after calls is passed on the stack, even as `this`.
  Using it in both switch cases (link + virtual set-up duplicated per case,
  then tail-merged by the compiler) moves it to EDI as in retail.
- Sprite flag clears go through a pointer helper to keep `and [mem],reg`.
