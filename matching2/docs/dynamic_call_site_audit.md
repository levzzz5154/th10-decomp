# Dynamic call-site audit (startup-to-title slice)

Every `(**(code **)...)` indirect call site inside the 179-function
startup-to-title closure was classified by reading the raw pseudocode of the
containing function. Two categories exist, and both are safe for the
retail-free build:

1. **COM interface vtable calls** (Direct3D9, DirectSound, DirectInput,
   IDirectSoundNotify). The callee lives in a system DLL, not the retail
   image; the standalone host provides these objects (or stubs). Slot
   offsets are documented per site below.
2. **Game-owned callback pointers** (scheduler nodes, sound worker thread,
   config timer). Every stored target is one of the label callbacks already
   enumerated in the milestone root set (title initializer 0x0042CAA0 chain,
   LAB_004485D0..0x00448810, LAB_00420000/C0/D0, LAB_004201B0,
   LAB_0043CCF0), so no unreached retail code hides behind them.

| Function | Sites | Classification |
| --- | --- | --- |
| 0x00439D20 | 33 | All D3D device vtable: SetRenderState +0xE4 (19), SetTextureStageState +0x10C (8), SetSamplerState +0x114 (6) |
| 0x00439890 | 10 | Device chain: CreateDevice +0x40, GetDeviceCaps, GetBackBuffer +0x48, Release +0x8, plus device-format probes; all IDirect3D9/IDirect3DDevice9 slots |
| 0x0043DDF0 | 7 | DirectSoundBuffer slots: Stop +0x48, SetCurrentPosition +0x34, SetPan +0x40, SetVolume +0x3C, Play +0x30; streamer vtable(1) destructor (game-owned, target in closure) |
| 0x00420270 | 6 | COM Release on manager texture (+0x20/+0x8) x3 pairs; all system interface slots |
| 0x0043BC40 | 6 | Device: SetTransform +0xB0 (3), SetViewport +0xBC, SetRenderState +0xE4 (2) |
| 0x00438AD0 | 5 | Direct3DCreate9 result vtable (CreateDevice/Release), device Release chain, TestCooperativeLevel +0xC, Reset +0x40 |
| 0x0043A290 | 5 | midiOut function-pointer table (midiOutOpen/Prepare/Unprepare headers); system multimedia DLL |
| 0x0043D120 | 5 | DirectSound buffer Release +0x8 (x2 loops), IDirectSound Release, streamer vtable(1), notify Release |
| 0x00448450 | 5 | Device: GetBackBuffer +0x48, CreateTexture +0x70, CreateOffscreenPlainSurface +0x90 (x2), surface Release |
| 0x0044CBF0 | 5 | IDirectSound CreateSoundBuffer +0xC, QueryInterface, SetNotificationPositions +0xC, buffer Release, notify Release |
| 0x00439390 | 4 | Device: SetViewport +0xBC, EndScene +0xA4, SetTexture +0x104, BeginScene +0xA8 |
| 0x00442F50 | 4 | Device: SetTextureStageState +0x10C (2), SetFVF +0x164, DrawPrimitiveUP +0x14C |
| 0x00448270 | 4 | Device: GetBackBuffer +0x48, GetSurfaceLevel, surface Release x2 |
| 0x0044CF20 | 4 | Buffer Release +0x8, CreateSoundBuffer +0xC, QueryInterface notify, SetNotificationPositions +0xC |
| 0x00420670 | 3 | Surface LockRect/UnlockRect/Release for the screenshot copy |
| 0x0044D110 | 3 | Buffer Restore +0x24, Lock +0x2C, Unlock +0x4C |
| 0x0044D300 | 3 | Buffer Stop +0x48, SetCurrentPosition +0x34, Play +0x30 |
| 0x00421480 | 2 | Device SetTransform +0xB0 x2 |
| 0x00434DD0 | 2 | Archive extractor function-pointer pair from the pack-file table (game-owned decompressors, in closure) |
| 0x004391F0 | 2 | Device Present +0x44 and swap-chain Present |
| 0x00447F70 | 2 | Texture/surface Release +0x8 x2 |
| 0x00449C00 | 2 | Scheduler node function pointers (+0x8/+0xC): every registered target is an enumerated LAB_/FUN_ callback in the root set |
| 0x0044D4E0 | 2 | Buffer Stop +0x48, SetCurrentPosition +0x34 |
| 0x0044D550 | 2 | Buffer Stop +0x48, streamer reader close (game-owned, in closure) |
| 0x0044DAD0 | 2 | Buffer SetCurrentPosition +0x34, reader seek callback (game-owned 0x0044DD40, in closure) |
| 0x00409F90 | 1 | Enemy node release vtable slot +0x14 (game-owned dtors, all in closure) |
| 0x0041C1C0 | 1 | Child widget release vtable (game-owned, in closure) |
| 0x00420CD0 | 1 | Device SetRenderState +0xE4 (fog) |
| 0x00434D10 | 1 | DirectInput device Release |
| 0x00438A30 | 1 | Device EvictManagedResources +0x14 |
| 0x0043BCD0 | 1 | Device SetViewport +0xBC |
| 0x0043DAB0 | 1 | midiOut Reset/Close slot |
| 0x00445900 | 1 | Device SetSoftwareVertexProcessing +0x170 |
| 0x00447810 | 1 | Texture Release +0x8 |
| 0x00449D40 | 1 | Scheduler render-pass node pointer (same enumerated callback set as 0x00449C00) |
| 0x0044D370 | 1 | Buffer Play +0x30 |
| 0x0044D440 | 1 | Buffer SetVolume +0x3C |
| 0x0044D5B0 | 1 | Buffer Stop +0x48 (pause) |
| 0x0044D5D0 | 1 | Buffer Play +0x30 (resume) |
| 0x0044D600 | 1 | Buffer SetVolume +0x3C (fade) |
| 0x0044D6A0 | 1 | Buffer Lock +0x2C (initial fill) |

**Conclusion:** no indirect site can reach retail code outside the
179-function closure. COM slots are host-provided; every game-owned pointer
target is already a closure member or an explicitly enumerated root.
