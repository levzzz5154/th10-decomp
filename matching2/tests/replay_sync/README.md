# Replay synchronization check

Plays a replay in retail and in a rebuilt executable under the same isolated Wine install and
compares per-frame game state. Any difference comes from code: both runs share the environment.

* `rtrace.c` — Win32 debugger: int3 at the item update 0x0041AFD0 (once per gameplay frame);
  each hit appends the score/globals block 0x00474C40, both RNGs 0x004918A8/0x004918B0 and the
  player block to a binary trace. Faults are logged with the stack's code return addresses.
  It also writes `<trace>.status` (mode, title submode/phase/cursor, hits) every 100 ms.
  Build: `i686-w64-mingw32-gcc -O2 -o ../../build/behavior/game/rtrace.exe rtrace.c`.
* `drive.py` — Xvfb/xdotool/Wine plumbing; menu input is gated on the title state read from the
  status file (the title starts an attract demo after a few idle seconds).
* `run_replay.py <exe> <list index> <stage row> <trace.bin>` — one full run with Ctrl held
  (about 4x speed); stops at the title, on a crash, or when frames stop.
* `compare.py <retail.bin> <candidate.bin>` — first diverging frame and fields. Ignores heap
  pointers, the clock-seeded RNG 0x004918A8, the obfuscated tail of the globals block, and two
  fields an attract demo leaves behind.

Executables and replays live in `build/behavior/game` (copies; `retail.exe` is the oracle).
Parallel instances need their own display, game copy and prefix:
`RS_DISPLAY=:92 RS_GAME=game2 RS_PREFIX=wineprefix2`.

Under this Wine setup retail itself drifts in Stage 6 of `th10_05` (the stage 1-5 end scores
match the replay file exactly), so traces are compared against retail's trace, not against the
scores recorded in the replay.
