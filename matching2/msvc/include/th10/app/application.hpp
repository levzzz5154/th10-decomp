#ifndef TH10_APP_APPLICATION_HPP
#define TH10_APP_APPLICATION_HPP
#include <stddef.h>
#include "th10/game/large_initialization_state.hpp"
#include "th10/render/direct3d9_interfaces.hpp"

struct MidiOwner;

// The application object at 0x00491C28, as WinMain and the Direct3D start-up
// reach it. In `config`, field_1a is the colour depth (0 for 32 bits, 1 for
// 16, 0xFF before the first run), field_1d is set to run in a window, and
// the flags are 1 = 16-bit textures, 2 = reference rasteriser, 0x100 = ask
// at start-up.
struct Application {
    void* instance;                             // +0x000
    Direct3D* direct3d;                         // +0x004 (0x00491C2C)
    Direct3DDevice* device;                     // +0x008 (0x00491C30)
    unsigned char reserved_00c[0x4C - 0xC];
    Direct3DMatrix view;                        // +0x04C (0x00491C74)
    Direct3DMatrix projection;                  // +0x08C (0x00491CB4)
    Direct3DViewport viewport;                  // +0x0CC (0x00491CF4)
    Direct3DPresentParameters present_parameters;   // +0x0E4 (0x00491D0C)
    unsigned char reserved_11c[4];
    GameConfig config;                          // +0x120 (0x00491D48): th10.cfg
    unsigned char reserved_154[0x3AC - 0x154];
    int mode;                                   // +0x3AC (0x00491FD4)
    unsigned char reserved_3b0[4];
    int no_vsync;                               // +0x3B4 (0x00491FDC)
    int fixed_refresh;                          // +0x3B8 (0x00491FE0): 60 Hz was obtained
    int frames_presented;                       // +0x3BC (0x00491FE4)
    MidiOwner* midi;                   // +0x3C0 (0x00491FE8)
    unsigned char reserved_3c4[0x3CC - 0x3C4];
    // +0x3CC (0x00491FF4): 1 = hardware vertex processing, 2 = device created,
    // 4 = 32-bit textures, 0x10 = device was reset
    unsigned int flags;
    unsigned char reserved_3d0[8];
    Direct3DCaps caps;                          // +0x3D8 (0x00492000)
};
typedef char ApplicationView[offsetof(Application, view) == 0x4C ? 1 : -1];
typedef char ApplicationPresent[offsetof(Application, present_parameters) == 0xE4 ? 1 : -1];
typedef char ApplicationConfig[offsetof(Application, config) == 0x120 ? 1 : -1];
typedef char ApplicationMode[offsetof(Application, mode) == 0x3AC ? 1 : -1];
typedef char ApplicationFlags[offsetof(Application, flags) == 0x3CC ? 1 : -1];
typedef char ApplicationCaps[offsetof(Application, caps) == 0x3D8 ? 1 : -1];

// The window and frame-clock state at 0x004924F0.
struct MainWindow {
    void* window;                               // +0x00
    int quit;                                   // +0x04 (0x004924F4)
    void* instance;                             // +0x08 (0x004924F8)
    unsigned char reserved_0c[8];
    unsigned char cursor_state;                 // +0x14 (0x00492504)
    unsigned char reserved_15[0x28 - 0x15];
    unsigned char force_no_vsync;               // +0x28 (0x00492518)
    unsigned char reserved_29[3];
    unsigned int saved_parameters[3];           // +0x2C: the system settings to put back
    double target_time;                         // +0x38 (0x00492528)
    double start_time;                          // +0x40 (0x00492530)
    double frame_time;                          // +0x48 (0x00492538)
    double previous_time;                       // +0x50 (0x00492540)
};
typedef char MainWindowTarget[offsetof(MainWindow, target_time) == 0x38 ? 1 : -1];
#endif
