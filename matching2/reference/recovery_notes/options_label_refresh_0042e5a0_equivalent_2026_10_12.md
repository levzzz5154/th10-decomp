# Options label refresh 0x0042E5A0 — equivalent-model session 2026-10-12

Status: model and layout drafted, not yet registered.  The exact build is
unaffected (the asm region stays; the model files sit unregistered in the
tree until the blockers below are cleared).

## What the function does (fully mapped this session)

* Copies the music and sound volumes to 0x00497854 / 0x00497858 and the
  request queue call `RegisterResource(0x00492590, "bgm/th10_02.wav", 8, 0)`
  (custom ABI: EAX=this, EDX=name, stack resource+parameter, RET 8).
* Music DSP attenuation: `x = 1 - 0.01*music`; `-5000 - (int)((1-x^4)*-5000)`
  via `__ftol2`, or the constant -10000 while the music is off.
* Twelve digit labels (music 0x25/0x26/0x27 + 0x29/0x2A/0x2B, sound
  0x2D/0x2E/0x2F + 0x31/0x32/0x33) are each reconfigured with
  `ConfigureObject(obj, digit + 0x33 or 0x3D)` where digit = hundreds /
  (v/10)%10 / v%10.  ConfigureObject ABI: ECX=resource (obj+0x308),
  EAX=object, DX=index.
* Then two visibility trees (music, sound): below ten hides the hundreds and
  tens labels (&= ~2), one hundred shows all four (|= 2), in between shows
  the tens and hides the hundreds.  Walks use slot `animation_slots[1]`
  (room+0x2C8), script compare at +0x38A, fallback `Find(0)`.

The volume RMW in TitleOptions 0x0042D920 (its three call sites) is the
same goto-convergence shape that fixed the caller.

## Model files (unregistered)

* `msvc/equivalent/game/options_label_refresh_0042e5a0.cpp`
* `msvc/include/th10/game/options_label_refresh_0042e5a0.hpp`
* `msvc/layout/equivalent/options_label_refresh_0042e5a0.json`
  (context_cluster = the title cluster; entry = its compiler context)

## Blockers measured with tools/matching/equivalence.py

1. The model body is 3445 bytes — it FITS the 3999-byte region.  The tool
   rejects it anyway: `model_code` is derived from the first `ff /24` jump
   target inside `size + 0x400`, and TitleOptions' switch table (compiled
   into the same model link by the context) lands at +4388, past the region.
   A table-detection guard (a candidate table should be pointed at by a
   jump inside the compared window, or the window should stop at the
   function's own section) would let the comparison run.
2. c2 compiles the model's `ConfigureObject` calls as stack-thiscall
   (push sprite; push object) and reloads the manager global after every
   call, while retail uses the register form (EAX/EDX/ECX) with ESI live
   across it — +389 bytes if the two were merged, and ~24 recorded
   code-shape differences otherwise.  In-cluster callee compilation picks
   the register form only when c2's interprocedural pass sees the same
   caller shape as retail; the single-caller model link does not.

## Next levers

* Fix the table heuristic in tools/matching/equivalence.py, register the
  recovery, and record the configure-call differences (code-shape class
  explicitly covers "a read-modify-write folded or split" and shared-tail
  merges; a calling-convention difference needs the same class or a new
  listed one).
* Or make the title cluster compile the ConfigureObject body in-context
  (registrar.cpp-style anchor like pause_open_004231d0 does) so the real
  function can become a selected region and the ABI matches naturally.
