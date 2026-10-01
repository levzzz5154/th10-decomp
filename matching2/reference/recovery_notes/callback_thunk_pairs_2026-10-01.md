# Scheduler callback thunks recovered with their callees (2026-10-01)

The small `mov reg,ecx` adapters in front of private-register routines are
ordinary `__fastcall` callbacks whose only statement calls a member function.
Compiled in one native `/LTCG` link with the callee, and with their address
published by a context function the way the real initializers do, they come
out byte-exact together with the callee's private receiver register:

| callback | callee | receiver | source |
|---|---|---|---|
| `0x00403050` (`mov eax,ecx; jmp`) | `0x00402720` stage update | EAX | `src/game/stage_state_update_00402720.cpp` |
| `0x0040D810` (`push edi; mov edi,ecx; call`) | `0x0040D750` enemy sweep | EDI | `src/game/enemy_timer_sweep_retail_0040d750.cpp` |

`tools/waves/adopt_cluster.py` writes the layout (gaps computed from the
placed functions) and converts the regions from a short spec.

Two source details were needed. The stage update publishes its camera with
`memcpy`, which makes the frame counter reload after the copy. The enemy
sweep's timer reads its speed through an inline accessor and adds the elapsed
time to it (`elapsed = Speed() + elapsed`); that is the only spelling found
that loads the speed first on the slow path.

## Open: `0x00427950` -> `0x00427960` (ESI receiver)

The same recipe reproduces the thunk and the loop of the 359-byte routine.
The source shape is: copy the trail head into `position`; when not dragging
set `offset = position - cursor`, otherwise set the head to `cursor + offset`
and interpolate the seven trail points in eighths; then
`position = offset + cursor` on both paths. The remaining difference is that
retail recomputes the head address for the drag-path store, where every
spelling tried so far reuses the first address and so allocates registers
differently. Passing the two sums by value to an inline setter gives retail's
load order (`offset.y`, `cursor.y`, `offset.x`, `cursor.x`) but not the
recomputed address.

## Floating number pool (0x0042B780 / 0x0042B9B0 / 0x0042B9C0)

Cluster `floating_text_draw_0042b780`. Three source-shape levers were measured:

- **Duplicated tail statement.** The glyph loop picks one of three sprite
  ranges; retail keeps the fade alpha in EBX and spills the glyph cursor. That
  only reproduces when `sprite.alpha = alpha` is written in each of the three
  branches (the compiler tail-merges the stores back into one). With a single
  store after the branches the cursor wins EBX and the alpha is spilled.
- **Escaping render state.** The fog reset `fog_dirty = 0; device->State(...)`
  keeps retail's order (store between the constant pushes and the vtable load)
  only when the address of the render state `data_00491c28` escapes somewhere
  in the cluster. Otherwise whole-program analysis proves the store cannot
  alias the device and sinks it below the vtable load. The entity-draw stand-in
  passes `&data_00491c28` to an external for that reason.
- **Caller stand-in selects the argument registers.** The spawner's
  EAX/ESI/EDI convention came out of an ordinary `__thiscall` member once a
  stand-in for its only caller (0x0041AFD0) was co-compiled: the caller keeps
  the position live in a callee-saved register and reloads the pool global
  before each call.

The spawner's digit split needs the zero fix-up *after* the sign test
(`if (length == 0) { glyphs[0] = 0; length = 1; }` as a separate statement) so
the negative block is laid out after the return.

## Spt Test screen destructor (0x0042BC30, 0x0042BAD0, unwind 0x004653E0)

Cluster `script_viewer_teardown_0042bc30` (`exceptions: true`). The destructor
is an ordinary C++ destructor of a class with one destructible member (the
loader thread at +0x10); the compiler generates the unwind funclet and handler.

- The worker destructor must keep its public ECX receiver for the funclet's
  `jmp`. It cannot be a whole-program root (0x0044C130 belongs to another
  cluster), so the driver destroys a two-element worker array: the vector
  destructor iterator takes the destructor's address, which pins `__thiscall`.
- The parser vtable is bound with a data alias. The alias lies inside the
  `.rdata` filler that positions `.xdata$x`; `ltcg_cluster.py` now allows a
  data alias inside an `.rdata` gap (it contributes no bytes) while still
  rejecting overlap with real contributions.
- `adopt_cluster.py` passes `exceptions` and `native_data` through and adds the
  `.rdata$0before` gap up to the exception table.

## SprtView destructor (0x40A1A0) and update (0x40A450)

- A stand-in destructor only keeps its receiver on the stack when its body
  mirrors the real one: the two inlined scheduler removals keep all four
  callee-saved registers busy, so `this` is reloaded from the stack.
- `delete global;` loads the pointer into EAX and copies it; an inline helper
  taking `T* const&` and copying to a local loads straight into ESI.
- Two destructible array members in one stand-in struct give that stand-in its
  own EH funclets, which displace the real ones in `.text$x`; use one struct
  per array.
- Update: with no `roots` entry the member function takes its receiver on the
  stack (RET 4) and the fastcall task becomes `push ecx; call; ret`.
- A stand-in whose `this` must arrive in EAX (0x40CFB0) needs a `rep movs` in
  its body: ESI is then taken by the copy and the receiver moves EAX -> EBX.
- Parameter structs passed "in EAX after the pushes" are the callee's `this`
  (`spawn.Create(manager, name)`), not an argument.

## Spell card end (0x409C00)

- A stand-in keeps an argument on the stack when the argument's address is
  taken; do it after the dispatch so the argument is not loaded into EAX
  early, which leaves EAX to the register argument.
- A value that retail reloads after a store to a global means the global's
  address escapes somewhere in the program: pass `&global` to an extern in the
  context function.
- `lea esi,[edi+off]` next to a folded `[edi+off]` load: the code reads the
  global pointer directly, not through a local. The slot reference is bound
  before a call that may change the global, so the address has to survive in
  its own register while the global's cached value dies at the call.
- A callee whose "out" pointer arrives in a register after the pushes returns
  a small class by value (give the id type a constructor).

## Parked: animation list registrations (0x4489D0, 0x448A50, 0x448AC0, 0x448B40)

Manager in EDX, object in EBX, returned id slot in EAX (the id type has a
constructor). `node->InsertAfter(tail)` / `head->InsertAfter(&object->node)`
plus `int id = ++last_id; if (id == 0) { ++id; last_id = id; }` reproduces all
four bodies except one tie-break: retail keeps the incremented id in ESI and
saves EDI only inside the insert branch, the rebuild keeps it in EDI and saves
EDI at entry (9 differing lines per function). Id-expression variants, head or
tail locals, duplicated tail stores and by-reference list helpers did not move
it.
