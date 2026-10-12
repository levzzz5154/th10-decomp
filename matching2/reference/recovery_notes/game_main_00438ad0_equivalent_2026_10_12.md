# GameMain 0x00438AD0 as an equivalent C++ model (2026-10-12)

Region: 0x00438AD0..0x0043900C (1389 bytes). The model lives in
`msvc/equivalent/game/game_main_00438ad0.cpp` with the header
`msvc/include/th10/game/game_main_00438ad0.hpp`, compiled in the
`cl_0040dc70` context cluster and registered as
`layout/equivalent/game_main_00438ad0.json`.

## Semantics (all expressed in the model)

WinMain: the 0xA004 replay buffer allocation and zeroing, the seven
critical sections (0x492274 + 0x18·i), the replay-log banner, the
single-instance check (0x00439FF0), the settings save (0x004392E0), the
configuration load (0x00420870, `th10.cfg`), the options dialog (resource
0xCB, procedure 0x43A3A0, `data_00491D65` set when the dialog rejects),
the checksum (0x0043A1C0), the D3D resource manager (0x00449AA0 on a
0x48-byte allocation) and the Direct3D object (0x00452176, with the
failure log line at 0x0046F6A0), the window (0x00439730), the sound
manager (0x14B4 bytes zeroed at 0x492590, owner word, streaming thread on
0x0043CCF0), the D3D device init (0x00439890), the input probes, the
animation storage (0x732460 bytes, constructor 0x00445900), the IME/cursor
state when the dialog never ran, the frame-time quadruple (one x87 value
stored to 0x492528..0x492540 from the FrameTimer_GetDelta return), the
frame loop (PeekMessage pump; TestCooperativeLevel slot 3; on
D3DERR_DEVICELOST: ReleaseAll 0x00438A30 → Reset slot 16 →
ApplyDeviceDefaults 0x00439D20 → flags |= 0x10; GameFrameAdvance 0x00439390
with the three exits), the settings-tail write (0x34 bytes at
0x00491D48 → `th10.cfg`), App::Shutdown (0x00420270), the resource-manager
destructor, the wave-command drain, the sound stop/cleanup, the animation
storage teardown, the device Reset/Release pair, the window destruction,
the restart pump (60 frames) with the restart-required log line
(0x0046F6F0), the crash-log write (`./log.txt` via a do-while strlen), the
MessageBox(0, log_text, "log", 0x10), the MIDI teardown, the
critical-section deletions, the three SystemParametersInfoA calls
(0x11/0x55/0x56), and the replay-buffer free.

## Recorded differences (111 hunks, 185 instructions; 219 of 404 identical)

- 28 branch-target hunks: the compiler reordered the window-creation and
  teardown blocks (the model reaches the shared failure exits through
  different merge points than retail's fall-throughs).
- 25 register-choice hunks: EBX/EBP swap for the zero register, the
  instance copy living in ESI vs [esp+0x34].
- 58 code-shape hunks: the `exit_code != 2` guard compiled as arithmetic
  (setne/dec/and) where retail jumps, the interleaved x87 stores, and the
  empty-string fast path the model dropped from the log strlen.
