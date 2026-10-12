# D3DInitialize 0x00439890 as an equivalent C++ model (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 304 of 304 instructions identical.**
The model was rewritten from the retail disassembly (nested device-creation attempts with one
shared reference-device fallback, the camera set-up with float literals) and is linked against
the real text-log sources through `context_sources`. Everything below this paragraph describes
the earlier parked draft.

Region: 0x00439890..0x00439D16 (1159 bytes). The model lives in
`msvc/equivalent/game/d3d_initialize_00439890.cpp` with the present-
parameters view `msvc/include/th10/render/d3d_initialize_00439890.hpp`,
compiled in the `cl_0040dc70` context cluster and registered as
`layout/equivalent/d3d_initialize_00439890.json`.

## Semantics (all expressed)

The back-buffer format byte (0x491D62: 0xFF first boot → 32-bit), the
windowed/VSync decision (0x492518 / 0x491FDC), the three CreateDevice
attempts (slot 0x40: T&L HAL 0x40 → HAL 0x20 → mixed 2) each with its own
failure logging (T&L missing, refresh failed, async failed, the fatal
0x46F514 line with the D3D object release), the runtime flags (bit 0:
device type, bit 1: windowed, bit 2: 16-bit fallback decided through the
CheckFormat slot 0x28 probe), the view/projection setup
(D3DXMatrixLookAtLH with the eye (320, -240, 0) and the fptan-derived
-240/tan(π/12) slope; D3DXMatrixPerspectiveFovLH fov 30°, aspect 4:3,
near 100, far 10000), the SetTransform pair (slots 0xB0), the viewport and
render-state configuration (slots 0xC0/0x1C), the capability logs (no ADD
blending, no >512 textures, no A8R8G8B8), Renderer_ApplyDeviceDefaults,
ApplyDefaultViewport(0xFF000000) and the quit/presentation clears.

## Recorded differences (53 hunks, 232 instructions; 72 of 304 identical)

- 17 branch-target hunks: the three CreateDevice attempts merged into a
  different retry shape than retail's fall-through ladder.
- 8 register-choice hunks.
- 28 code-shape hunks: the interleaved logger scheduling (the model's
  Append calls carry their arguments in a different order), the frame
  offset of the present-parameters block (0x54 vs 0x70 locals), and the
  fptan sequence compiled as a tan() call.
