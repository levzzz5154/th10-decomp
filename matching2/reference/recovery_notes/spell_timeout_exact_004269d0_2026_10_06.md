# Spell timeout 0x004269D0: byte-exact C++ recovery

`msvc/src/game/spell_timeout.cpp` now owns all 796 bytes as ordinary C++.
The old naked implementation and its obsolete D3407 blocker were replaced.
The public `_SpellTimeout_004269d0@4` takes one field pointer on the stack and
returns with `RET 4`; existing assembly aliases still bind to 0x004269D0.

The routine reduces power toward 5000, decrements the stock count, and publishes
nonnegative counts through the animation manager. It sets field mode two,
resets the first timer, sets the activation timer to 180, and loads script zero
into the embedded animation. Four slots clear their state and retire both
animation handles: lookup visits primary then secondary lists, and found
objects and their children receive stop-frame one unless child handling is
already flagged. It clears the active-slot count, creates an urgent `Caution!`
tip outside warning mode one, clears the player's pending state and flags after
sixty frames, and subtracts 1024 from the transition gauge before clamping it
between -1024 and 1024. Player animation slot two retains its pending bit.

The power adjustment deliberately retains `((power - 5000) / -3 * 10) / 10`.
Cancelling multiplication and division by ten changes the behavior of the
32-bit signed intermediate when it wraps. This recovery uses the existing
MSVC 13.10 target arithmetic behavior and reproduces both retail signed
divisions. It does not replace them with the simplified legacy semantic model.

Compile-time checks cover the animation-list and child fields, slot stride and
handles, embedded animation and position, field mode and timers, and the
player's entity stride, frame counter, flags and pending state. Existing
`OpenTimer::Set` supplies lazy initialization and the retail assignment order.

## Native context and source shape

`layout/ltcg/spell_timeout_004269d0.json` supplies complete ordinary C++ bodies
for the active-count updater, script loader, tip creator and urgent-tip wrapper.
The selected timeout is explicitly rooted; a direct compiler caller retains
its public stdcall boundary. Native LTCG derives the helper calls' private
register handoffs. Only the timeout owns new game bytes. The helpers remain
compiler contexts and retain their existing production region owners.

The first complete model emitted 812 bytes. Retaining the power value locally
corrected its global-store ordering. Capturing the slot-array base before the
arithmetic gave the field, manager and cursor their retail register allocation
without moving the cursor's address formation before the helper calls. This
reduced the complete contribution to the required 796 bytes and left seven
byte differences. Reading the first handle into a scalar before clearing the
slot state corrected the final load/test/store schedule: all 796 bytes then
matched, with zero instruction differences or base/index allowances.

Experiments, complete emitted bodies, maps, native images and comparison
receipts are retained in
`matching2/build/experiments/spell_timeout_2026_10_06/`. `id_before_state/` is the
first equal relocated model; `native-probe/` proves its fixed-address native
projection. `integrated-probe/` proves the final maintained source after
formatting, helper naming, offset assertions and public declaration changes.
Raw relocation diagnostics were not registered as an equivalence recovery.
Failed preparatory compile/layout checks are not matching evidence.

No assembly adapter, volatile access, barrier, per-source compiler flag,
compiler-output patch, oracle-byte inclusion or new equivalence allowance was
added to the maintained recovery.

Validation on 2026-10-06:

- Scratch and maintained strict probes: all 796 bytes EXACT, including complete
  contribution extent and every linker-filled target.
- `make`: full-image and the eight existing equivalence gates passed.
- `make EXACT=1`: all 487,936 executable bytes exact.
- `git diff --check`: passed.

Progress after this recovery: 2,246 ordinary C++ regions / 190,586 bytes;
8 equivalent regions / 33,176 bytes; 68 remaining assembly regions / 97,721 bytes.
The full readable, byte-exact, assembly-free objective remains incomplete.
