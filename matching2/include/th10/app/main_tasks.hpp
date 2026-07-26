// =============================================================================
// main_tasks.hpp - Main-task registration, shutdown, config, screenshots
// Retail functions: 0x00420470, 0x00420270, 0x00420870, 0x00420670
// =============================================================================
#ifndef TH10_APP_MAIN_TASKS_HPP
#define TH10_APP_MAIN_TASKS_HPP

struct MainTaskHooks {
    void* context;
    // Scheduler node creation (retail 0x00449ED0): wraps `callback_index`
    // (0 = input poll 0x0041FF80, 1..3 = LAB_00420000/C0/D0) into a node,
    // sets flag bit 1, and stores the owner pointer.
    void* (*create_node)(void* context, int callback_index);
    int (*register_primary)(void* context, void* node);   // 0x00449AE0
    int (*register_secondary)(void* context, void* node); // 0x00449B70
};

struct MainTaskState {
    int stage_counter;      // _DAT_00491FB4 (primed to -2)
    int mode;               // DAT_00491FB8
    int transition_pending; // _DAT_00491FC0
};

int MainTasks_Register(MainTaskState* state, const MainTaskHooks* hooks);

// Host-facing view of the fields read by the primary input callback at
// 0x0041FF80. The retail fields live at owner+0x3CC, +0x63C, and +0x648.
struct MainInputTaskState {
    signed char replay_state;
    void* replay_handle;
    int callback_result;
};

struct MainInputTaskHooks {
    void* context;
    int* mode; // DAT_00491FB8
    void (*advance_input)(void* context); // 0x00421E00
    void (*poll_devices)(void* context);  // 0x0044A5F0
    int (*resource_busy)(void* context);  // 0x00447700
    int (*apply_requested_mode)(void* context); // 0x004218D0
};

// Semantic reconstruction of the primary scheduler callback. Returns the
// retail scheduler status: 4 while resources/transition state are busy,
// 1 for a non-special callback result, or the mode-apply result otherwise.
int MainInputTask_Run(const MainInputTaskState* state,
                      const MainInputTaskHooks* hooks);

struct MainTaskShutdownHooks {
    void* context;
    void (*log_frame_marker)(void* context);        // 0x0044C150
    void (*release_tracked_block)(void* context);   // free(DAT_0049238C)
    void (*release_input_bindings)(void* context);  // 0x004203F0
    void (*release_text_objects)(void* context);    // 0x00413450
    void (*release_manager_texture)(void* context); // mgr+0x3ADA74 Release
    void (*queue_dummy_sound)(void* context);       // 0x0043E460("dummy",4,0)
    void (*release_font_cache)(void* context);      // 0x00437D10
    void (*release_device_surfaces)(void* context); // +0x10/+0x14/+0xC chain
    void (*kill_config_timer)(void* context);       // DAT_00491D44 timer kill
    void (*release_dinput)(void* context);          // 0x00434D10
};

int MainTasks_Shutdown(int* sound_worker_stop,
                       const MainTaskShutdownHooks* hooks);

// Config image written to / read from th10.cfg (0x34 bytes on disk). Retail
// keeps exactly one copy of it, the block at 0x00491D48, and every consumer
// addresses that block directly - which is why 0x00420870 loads into it in
// place instead of handing a copy back to its caller. The field offsets are
// the ones 0x00418C40 seeds and 0x00420870 range-checks.
struct GameConfig {
    unsigned int magic;             // +0x00 DAT_00491D48, must be 0x00100003
    unsigned int key_config[4];     // +0x04 published to DAT_00474E88..94
    unsigned short key_config_tail; // +0x14 published to DAT_00474E98
    unsigned short threshold_16;    // +0x16 axis threshold, default 600
    unsigned short threshold_18;    // +0x18 axis threshold, default 600
    unsigned char difficulty;  // +0x1A DAT_00491D62, < 2
    unsigned char bgm_mode;    // +0x1B DAT_00491D63, < 3 (default 1)
    unsigned char sfx_mode;    // +0x1C DAT_00491D64, < 2 (default 1)
    unsigned char windowed;    // +0x1D DAT_00491D65, < 2
    unsigned char skip_limit;  // +0x1E DAT_00491D66, < 3
    unsigned char slow_mode;   // +0x1F DAT_00491D67, < 3 (default 2)
    unsigned char music_volume;      // +0x20 DAT_00491D68, default 100
    unsigned char sound_volume;      // +0x21 DAT_00491D69, default 0x50
    unsigned char hint_mode;         // +0x22 DAT_00491D6A, default 0
    unsigned char reserved_23[13];   // +0x23..+0x2F cleared by 0x00418C40
    // +0x30 DAT_00491D78. 0x00420870 reads the runtime bits out of this word
    // (retail addresses it as appobj+0x150); 0x00418C40 defaults it to 0x100.
    unsigned int flags;
};

static_assert(sizeof(GameConfig) == 0x34,
              "GameConfig must preserve the retail on-disk layout");

struct ConfigLoadHooks {
    void* context;
    void (*apply_defaults)(void* context, GameConfig* config); // 0x00418C40
    // 0x0044B360 external-file path: returns malloc'd bytes or null.
    void* (*load_file)(void* context, const char* name,
                       unsigned int* size_out);
    void (*release)(void* context, void* memory);
    // 0x0044B810 with &DAT_0046DE7C - "config data not found, initialised".
    void (*log_missing)(void* context);
    // 0x0044B810 with &DAT_0046DE48 - "config data invalid, reinitialised".
    void (*log_invalid)(void* context);
    // An accepted image republishes its key block into the live input table
    // at 0x00474E88..0x00474E98.
    void (*publish_key_config)(void* context, const GameConfig* config);
    // The runtime-flag echo: clears 0x00491FDC, then logs the 0x04 / 0x01 /
    // windowed / 0x02 / 0x08 / 0x10 / 0x20 / 0x40 lines in retail's order.
    void (*log_runtime_flags)(void* context, const GameConfig* config);
    int (*write_file)(void* context, const char* name,
                      const GameConfig* config); // 0x0044B540
    // 0x0044B8E0 x2 - &DAT_0046DD08 takes the file name, &DAT_0046DCB0 does
    // not.
    void (*log_write_failure)(void* context, const char* name);
};

int Config_LoadAndValidate(GameConfig* config, const char* file_name,
                           const ConfigLoadHooks* hooks);

struct ScreenshotHooks {
    void* context;
    void (*wait_idle)(void* context);        // spin on ctx+0x50C with Sleep(10)
    void* (*alloc)(void* context, unsigned int size);
    void (*release)(void* context, void* memory);
    // Lock the back-buffer surface; returns pitch and BGRA rows via out.
    int (*lock_surface)(void* context, unsigned char** pixels, int* pitch);
    void (*unlock_surface)(void* context);
    void (*queue_writer_thread)(void* context, void* header, void* pixels);
    void (*log_error)(void* context, const char* stage);
};

int Screenshot_CaptureBmp(const char* file_name, int surface_format,
                          const ScreenshotHooks* hooks);

#endif // TH10_APP_MAIN_TASKS_HPP
