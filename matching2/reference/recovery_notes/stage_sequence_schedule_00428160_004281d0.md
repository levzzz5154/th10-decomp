# Stage sequence schedule (0x00428160, 0x004281D0)

2026-10-02. `src/game/stage_sequence_schedule.cpp` owns both functions as
ordinary C++ in the `frame_timer` native-LTCG cluster (the timer helpers at
0x00404ED0, 0x00405410 and 0x0044BF40 already live there). The synthetic
caller calls `Update`; `Update` calls `Dispatch`. That alone yields retail's
private conventions: sequence in EAX for `Update`, sequence in EDI and frame
in EBX for `Dispatch`. Incremental `make` verifies the whole EXE exactly.

Two source shapes decide the last bytes of `Update`:

* **Bitfield flag keeps a constant in a register.** Retail holds `1` in EBX
  (`cmp eax,ebx`, `test byte ptr [0x474e5c],bl`). Writing the flag test as
  `data & 1` on a char or int global always produced immediates. Declaring the
  global as a struct with `unsigned int repeat : 1` and testing `.repeat`
  produced the hoisted constant. A local `int one = 1`, a never-written
  static, a `switch`, a non-iterating `while`, and a parameter passed as 1 by
  the only caller did not (LTCG here does not propagate constant arguments).
* **Inline helper prevents reuse of the compared value.** Retail compares
  `current` with `previous`, then reads `current` from memory again for the
  dispatch argument. `if (timer.current != timer.previous) Dispatch(timer.current)`
  reuses the register. Moving the comparison into an inline helper that takes
  the timer by reference (or comparing through a local `FrameTimer*` while the
  argument uses the member directly) gives the second read.

Every path returns explicitly (`return 0` after the tick, then the reset
block); a shared trailing return saves ESI at entry instead of where the timer
address is first needed.
