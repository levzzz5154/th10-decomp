// =============================================================================
// game_main.hpp - Boot orchestrator surface for the retail entry point
// Retail functions: 0x00438AD0 (GameMain), 0x00439540 (clock read),
//                   0x00439390 (frame advance), 0x00439D20 (device defaults)
// =============================================================================
#ifndef TH10_APP_GAME_MAIN_HPP
#define TH10_APP_GAME_MAIN_HPP

// Result of one cooperative-level probe inside the message pump.
enum GameMainDeviceProbe {
    GAME_MAIN_DEVICE_READY = 0,
    // Matches D3DERR_DEVICENOTRESET (0x88760869) routing in retail.
    GAME_MAIN_DEVICE_NEEDS_RESET = 1,
    // Device lost: skip rendering, keep pumping messages.
    GAME_MAIN_DEVICE_LOST = 2,
};

// Exit route selected by the run loop (retail local "exit mode").
enum GameMainExit {
    GAME_MAIN_EXIT_NORMAL = 0,
    GAME_MAIN_EXIT_BOOT_FAILURE = 1,
    // Retail value 2: skip config write-back and restart the whole boot.
    GAME_MAIN_EXIT_RESTART = 2,
};

// Mutable state mirroring the retail globals touched by GameMain.
struct GameMainState {
    void* instance;              // _DAT_004924f8 / _DAT_00491c28
    void* tracker_pool;          // DAT_00491be0 (0xA004-byte allocation pool)
    void* scheduler;             // DAT_00491be4
    void* direct3d;              // g_pD3D9
    void* device;                // g_pD3DDevice
    void* game_state_manager;    // g_pGameStateManager (0x732460-byte arena)
    void* sound_worker_thread;   // _DAT_004977a8
    int   sound_worker_stop;     // DAT_004977b4 (2 = shutdown request)
    int   quit_requested;        // DAT_004924f4
    unsigned int config_flags;   // DAT_00491d78 (bit 0x100 = confirm dialog)
    int   dialog_declined;       // DAT_00491d65 (1 = user declined / windowed)
    int   frame_divisor;         // DAT_00492504 (retail constant 0xFC)
    unsigned int device_flags;   // DAT_00491ff4 (bit 0x10 = device resetting)
    int   reset_grace_frames;    // _DAT_00491fd4 (3 after device reset)
    int   midi_active;           // DAT_00491fe8
    double clock_floor;          // _DAT_00492540 (lowest observed clock)
    double clock_samples[3];     // _DAT_00492538 / 28 / 30 seed values
    int   critical_sections;     // count initialised over &DAT_00492274
};

// Host services consumed by the orchestrator; every member must be non-null.
struct GameMainHooks {
    void* context;
    void* (*alloc)(unsigned int size);
    void  (*release)(void* memory);
    void  (*critical_sections_init)(void* context, int count);
    void  (*critical_sections_destroy)(void* context, int count);
    void  (*log_open)(void* context, const char* banner);
    void  (*log_flush_and_close)(void* context);
    int   (*load_config)(void* context);            // 0x00439FF0
    int   (*create_window)(void* context);          // 0x004392E0
    int   (*create_input)(void* context);           // 0x00420870
    int   (*confirm_startup_dialog)(void* context); // DialogBoxParamA(0xCB)
    void  (*checksum_executable)(void* context);    // 0x0043A1C0
    void* (*create_scheduler)(void* context);       // 0x00449AA0 over new(0x48)
    void* (*create_direct3d)(void* context);        // Direct3DCreate9(0x20)
    int   (*create_device)(void* context);          // 0x00439730
    void* (*spawn_sound_worker)(void* context);     // CreateThread(LAB_0043CCF0)
    int   (*init_device_objects)(void* context);    // 0x00439890
    void  (*probe_joystick)(void* context);         // 0x0044A0C0
    void  (*init_text_layer)(void* context);        // 0x0044B080
    void* (*create_game_state)(void* context, void* arena); // 0x00445900
    void  (*disable_ime_and_cursor)(void* context);
    double (*read_clock)(void* context);            // 0x00439540
    void  (*set_foreground_window)(void* context);
    int   (*register_main_tasks)(void* context);    // 0x00420470
    // Message pump: returns nonzero when WM_QUIT was consumed.
    int   (*pump_messages)(void* context);
    int   (*probe_device)(void* context);           // GameMainDeviceProbe
    int   (*frame_advance)(void* context);          // 0x00439390
    void  (*device_release_resources)(void* context); // 0x00438A30
    int   (*device_reset)(void* context);
    void  (*device_apply_default_state)(void* context); // 0x00439D20
    int   (*drain_sound_commands)(void* context);   // 0x0043DDF0
    void  (*shutdown_main_tasks)(void* context);    // 0x00420270
    void  (*destroy_scheduler)(void* context, void* scheduler); // 0x00438880
    void  (*stop_sound_worker)(void* context);      // 0x0043CC40
    void  (*destroy_sound)(void* context);          // 0x0043D120
    void  (*destroy_game_state)(void* context, void* manager); // 0x00446220
    void  (*release_device_chain)(void* context);   // Reset + Release + D3D9
    void  (*destroy_window)(void* context);
    void  (*shutdown_midi)(void* context);          // 0x0043AE20 + 0x0043A910
    int   (*save_config)(void* context);            // 0x0044B540("th10.cfg")
    void  (*restore_system_parameters)(void* context); // SPI 0x11/0x55/0x56
    void  (*restart_grace_pump)(void* context);     // 0x3C-iteration pump
};

int GameMain_Run(GameMainState* state, const GameMainHooks* hooks);

#endif // TH10_APP_GAME_MAIN_HPP
