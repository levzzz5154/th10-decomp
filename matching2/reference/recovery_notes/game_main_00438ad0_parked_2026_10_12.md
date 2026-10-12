# GameMain 0x00438AD0: equivalent model parked (2026-10-12)

The readable model lives in `msvc/equivalent/game/game_main_00438ad0.cpp`
with the room view `msvc/include/th10/game/game_main_00438ad0.hpp` and a
draft registration in `msvc/layout/equivalent/game_main_00438ad0.json`
(unregistered; the region keeps its asm source for the exact build).

## What the model covers

The whole body is decoded and expressed: the 0xA004 replay buffer, the
seven critical sections, the single-instance check, the options dialog
(resource 0xCB, procedure 0x43A3A0), the D3D resource manager and object
creation with the Direct3D-failed log, the window creation, the sound
manager zeroing and streaming thread (entry 0x43CCF0), the animation
storage, the frame-time doubles (one x87 value stored to the four homes at
0x492528..0x492540), the frame loop with the message pump, the
device-lost recovery (ReleaseAll → Reset → ApplyDeviceDefaults →
flags |= 0x10), the three exits (restart 2, quit, error), the restart
pump (60 frames), the crash/config log writes (th10.cfg tail 0x34 bytes,
log.txt), the MIDI teardown, the critical-section deletions, the three
SystemParametersInfoA calls (0x11/0x55/0x56) and the replay buffer free.
The MessageBox at the log dump is MessageBoxA(0, log_text, "log", 0x10).

## Why it is parked

The compiled body is 1397 bytes against the retail 1389 — 8 bytes over,
and the equivalence tool hard-fails when the body exceeds the region. The
excess is not in one block: the per-block byte diff against retail shows
the growth spread over the restart plumbing (the settings-tail write is
guarded by `exit_code != 2` where retail uses an unconditional write
before the restart check at 0x438EFA, plus a `cmp byte [0x474F70],bl`
the model emits for the log-text first-byte test) and small register
choices around the exit-code arithmetic. The remaining levers are the
same c2 allocator traces used for StartChild
(`reference/compiler_traces/regalloc/trace_choose_physreg.py`), applied to
the GameMain compile inside `cl_0040dc70`'s context.

The layout JSON's absolute_symbols (79 entries: the import slots, the
globals and the callees with their exact decorations) is ready for the
next attempt; add `?GameMain_00438ad0@@YGHPAX0PADH@Z` to roots and
register in regions.json when the body fits.
