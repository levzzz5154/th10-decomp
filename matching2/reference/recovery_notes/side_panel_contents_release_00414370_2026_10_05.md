# 0x00414370 side panel contents release (recovered 2026-10-05)

`src/game/side_panel_contents_release_00414370.cpp` compiles to the retail 476
bytes in the `side_panel_contents_release_00414370` cluster (stand-ins for
0x4136C0 / 0x447810, bodies of 0x4491C0 / 0x4492A0 / 0x4493E0). `make` and
`make EXACT=1` pass.

* Shape taken from the two recovered neighbours (0x414570 and the destructor
  0x4145F0): `Release` through the real setter for the three fixed
  animations, the expanded setter for the eight effects.
* The first fixed animation is released with the global manager pointer, the
  others with a local copy taken after it (retail reloads 0x491C10 into ESI
  after the first call).
* The ten counters are cleared with a pointer loop
  (`for (index = 10; index != 0; --index) *counter++ = 0;`). That gives ten
  `mov [ebp+disp], edx` with a fresh zero register; `memset` addresses them
  through `lea eax,[ebp+9E28h]`, and an indexed loop or ten statements reuse
  the function's zero register.
