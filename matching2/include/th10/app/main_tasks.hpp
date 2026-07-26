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

// Config image written to / read from th10.cfg (0x34 bytes on disk).
struct GameConfig {
    unsigned int magic;        // DAT_00491D48, must equal 0x100003
    unsigned int score_seed[5];// DAT_00491D4C..5C -> DAT_00474E88..98
    unsigned char reserved[2]; // DAT_00491D60..61
    unsigned char difficulty;  // DAT_00491D62, < 2
    unsigned char bgm_mode;    // DAT_00491D63, < 3
    unsigned char sfx_mode;    // DAT_00491D64, < 2
    unsigned char windowed;    // DAT_00491D65, < 2
    unsigned char skip_limit;  // DAT_00491D66, < 3
    unsigned char slow_mode;   // DAT_00491D67, < 3
    unsigned char reserved_tail[20]; // remainder of the 0x34-byte disk image
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
    void (*log_invalid)(void* context);   // &DAT_0046DE48 / &DAT_0046DE7C
    void (*log_flag_bits)(void* context, unsigned int flags);
    int (*write_file)(void* context, const char* name,
                      const GameConfig* config); // 0x0044B540
    void (*log_write_failure)(void* context);    // 0x0044B8E0 x2
};

int Config_LoadAndValidate(GameConfig* config, const char* file_name,
                           unsigned int* runtime_flags,
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
