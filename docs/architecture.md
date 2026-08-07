# TH10: Mountain of Faith - Decompilation Architecture

## Game Engine Overview

TH10 is built on a custom engine by ZUN (Team Shanghai Alice), using:

| Component     | Technology                    | Notes                              |
|---------------|-------------------------------|------------------------------------|
| Rendering     | Direct3D 9.0c + D3DX9_31     | 3D pipeline, 2D sprites as textured quads |
| Input         | DirectInput 8                 | Keyboard + Joystick                |
| Audio (SFX)   | DirectSound 8                 | WAV file playback                  |
| Audio (Music) | WinMM MIDI                    | MIDI synthesis for BGM             |
| Image Base    | 0x00400000                    | 32-bit PE, 1,382 functions          |
| Entry Point   | 0x004537DC (CRT)              | -> GameMain at 0x00438AD0           |
| Linker        | MSVC 7.10 (VS.NET 2003)       | `_malloc`, `_free` statically linked |
| Window        | "BASE" class, 640x480         | Direct3D fullscreen or windowed     |

## Main Game Loop (WinMain -> GameLoopFrame)

```
GameMain (0x438AD0)
  ├─ operator_new(0xA004)        // Allocate pointer array
  ├─ InitializeCriticalSection x7
  ├─ FUN_00439ff0()              // Config/data loading
  ├─ FUN_004392e0()              // Pre-init
  ├─ FUN_00420870()              // Subsystem init
  ├─ FUN_0043a1c0()              // More init
  ├─ CreateGameWindow (0x439730) // RegisterClass "BASE", 640x480 window
  ├─ Direct3DCreate9(32)         // -> g_pD3D9 (0x491C2C)
  ├─ FUN_00439890()              // Device setup -> g_pD3DDevice (0x491C30)
  ├─ CreateThread(sound/music)   // -> LAB_0043ccf0
  ├─ GameStateInit (0x445900)   // Allocates 0x732460 bytes -> g_pGameStateManager (0x491C10)
  ├─ FUN_0044a0c0(), FUN_0044b080()  // Post-init
  ├─ FUN_00420470()              // Title/menu setup
  │
  └─ MAIN LOOP:
       PeekMessageA -> TranslateMessage -> DispatchMessageA
       └─ GameLoopFrame (0x439390):
            ├─ FUN_00439540()       // timeGetTime wrapper (delta time)
            ├─ Sleep(0)             // if frame is early
            ├─ FUN_00442f50()       // PollInput (DInput8)
            ├─ FUN_00421480()       // Setup3DCamera (view+proj matrices)
            ├─ FUN_00449c00()       // GameUpdate (main game logic)
            │    ├─ D3DDevice::BeginScene
            │    ├─ Render all objects
            │    └─ D3DDevice::EndScene
            ├─ D3DDevice::Present
            ├─ FUN_00449d40()       // PostRender
            └─ FUN_004391f0()       // PreFrame
```

## Key Globals (from Ghidra MCP analysis)

| Address    | Name                   | Type     | Description                                  |
|------------|------------------------|----------|----------------------------------------------|
| 0x00491C10 | `g_pGameStateManager`  | void*    | 7.5MB game state singleton                   |
| 0x00491C30 | `g_pD3DDevice`         | void*    | IDirect3DDevice9 interface                   |
| 0x00491C2C | `g_pD3D9`              | void*    | IDirect3D9 interface                         |
| 0x004924F0 | `g_pWnd`               | void*    | Main window HWND                             |
| 0x004776E0 | `g_pGameThread`        | void*    | Game state object (~0x8984 bytes, 106 xrefs) |
| 0x00491BE0 | pointer array          | void*[0x2801] | Generic object pointer pool             |
| 0x00491BE4 | renderer/engine object | void*    | 0x48 bytes, passed to GameUpdate             |
| 0x00492590 | sound/music thread ctx | 0x52D0  | Thread parameter block                       |
| 0x00474C7C | difficulty setting     | int32    | 0-7 (Easy/L/N/H + Extra), used in spell func |

## Decompiled Function Map

### Core Lifecycle
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x004537DC | entry             | MSVC CRT startup -> `GameMain`                 |
| 0x00438AD0 | GameMain          | WinMain: window, D3D, game loop, cleanup       |
| 0x00439730 | CreateGameWindow  | RegisterClassEx "BASE", CreateWindowEx 640x480 |
| 0x00439390 | GameLoopFrame     | Per-frame: delta, input, update, render, present|
| 0x004391F0 | PreFrame          | Called before BeginScene each frame            |
| 0x00449D40 | PostRender        | Called after Present each frame                |

### Game State
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x00445900 | GameStateInit     | Allocates 0x732460-byte game state, linked lists|
| 0x00420270 | GameStateDestroy  | Cleanup at exit                                |
| 0x00420470 | GameStateEnter    | Title screen / game mode entry                 |

### Rendering
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x00421480 | Setup3DCamera     | D3DXMatrixLookAtLH + D3DXMatrixPerspectiveFovLH|
| 0x00449C00 | GameUpdate        | Main per-frame rendering + game logic          |
| 0x00420CD0 | RenderPresent     | Final render pass / compositing               |

### Data Loading
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x00434DD0 | FileLoad          | Load file from DAT archive (vtable-based I/O)  |
| 0x00434F30 | FileOpen          | Open file entry from archive                   |
| 0x0044B0D0 | DataDecrypt       | Type-based decryption (th_decrypt)            |
| 0x00435DC0 | DataDecompress    | LZSS decompression                            |

### Game Logic
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x00409280 | SpellCardSetup    | Spell card name formatting + entity creation   |
| 0x0044FDB0 | EntityGetField    | Property accessor (bitmask + vtable dispatch)  |
| 0x00449950 | EntityCreate      | Object allocator + linked list insertion       |
| 0x00449870 | EntityInit        | Entity subtype initialization                  |

### Input
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x00442F50 | PollInput         | DirectInput8 polling + game state update       |

### System
| Address   | Name              | Description                                    |
|-----------|-------------------|------------------------------------------------|
| 0x004522706| _malloc           | MSVC 2003 malloc (statically linked)           |
| 0x004522422| _free             | MSVC 2003 free                                 |
| 0x00439540 | GetTime           | High-precision timer wrapper                   |

## GameStateManager Structure (0x732460 bytes)

Based on cross-references:

```
Offset  | Size    | Description
--------|---------|------------------------------------
+0x000  | 4       | Root pointer / vtable
+0x004  | ?       | Entity list head
+0x05C  | 4       | Viewport width (from camera)
+0x060  | 4       | Viewport height (from camera)
+0x768  | 4       | Spell card entity ID
+0x76C  | 4       | Spell card entity ID 2
+0x770  | 4       | Spell card entity ID 3
+0x774  | 4       | Effect entity ID
+0x3734 | 4       | Spell card RNG state (init: 0xFFF0BDC1)
+0x3738 | 4       | Spell card counter
+0x373C | 4       | Spell card timer
+0x3740 | 4       | Pointer to spell string table (0x476F78)
+0x3744 | 4       | Spell card flags
+0x3790 | 4       | Max score value
+0x3794 | 4       | Score display value (capped at 99999999)
+0x3798 | 4       | Spell card bonus parameter
+...
+0x3ADACC| 4      | Linked list head (rendering queue)
+0x3ADAC8| 4      | Linked list sentinel
+0x72DACC| 4      | List head copy (after switch)
+0x72DAD0| 4      | List tail copy
+...
```

## ECL Interpreter Architecture

The ECL bytecode interpreter lives primarily in functions around 0x0044XXXX.
Instructions are 8-byte aligned: {uint16 time, uint16 id, uint16 size, uint16 param_count, data[]}.

Known opcodes:
- ins_1() - END (return from subroutine)
- ins_258() - SET_ANGLE (set enemy angle)
- ins_262() - SET_SPEED (set movement speed)
- ins_330() - SET_ANIM (set animation state)
- ins_??_ - MOVE (move to position)
- ins_??_ - SHOOT (fire bullet pattern)
- ins_??_ - WAIT (delay execution)

## Reimplementation Roadmap

### Phase 1: Data Layer (current)
- [x] DAT archive extraction
- [x] MSG10 decoder
- [x] ECL decompiler (via thtk)
- [x] ANM06 format docs
- [x] Ghidra analysis of th10.exe (1,382 functions)
- [x] IDA exports checked in (`ida/th10.exe.{c,asm,h}`) - the static
      pseudocode/listing/type evidence the fidelity gate measures against;
      query with `matching2/tools/ida_export.py` (decompile/callers/asm/types)
- [x] Key function decompilation + globals identified

### Phase 2: Engine Core
- [ ] Implement DAT archive reader (LZSS + th_decrypt)
- [ ] Implement game loop (SDL2 + OpenGL)
- [ ] Implement .msg decoder
- [ ] Implement .anm texture loader
- [ ] Implement .ecl bytecode interpreter
- [ ] Port key game logic functions

### Phase 3: Complete Reimplementation
- [ ] Render pipeline (sprite batching, text, effects)
- [ ] Audio pipeline (WAV + MIDI playback)
- [ ] Input system (keyboard mapping, replay recording)
- [ ] Full game state machine (title, menu, stage, boss, ending)
- [ ] Enemy AI (ECL VM execution)
- [ ] Bullet system (shot data + patterns)
- [ ] Spell card system
