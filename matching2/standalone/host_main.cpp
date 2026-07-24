// =============================================================================
// host_main.cpp - Retail-free standalone runner for the startup-to-title
// milestone. Links only reconstructed matching2 sources plus this host
// platform layer; no retail bytes, no hybrid image, no Windows DLLs.
//
// The host wires every GameMainHooks member to reconstructed functions
// (Config_LoadAndValidate, GameStateInit_Construct, Device_ApplyDefaultState,
// MainTasks_Register, Frame_Advance, SoundWorker_DrainCommands,
// MainTasks_Shutdown, Viewport_ApplyDefault, Camera_Apply) and provides a
// stub device/scheduler in place of Direct3D so the boot flow can execute
// end-to-end. The title milestone is reached when the title task callbacks
// registered by MainTasks_Register have run a full frame.
// =============================================================================
#include "th10/app/game_main.hpp"
#include "th10/app/game_state_init.hpp"
#include "th10/app/frame_clock.hpp"
#include "th10/app/main_tasks.hpp"
#include "th10/archive/resource_manager.hpp"
#include "th10/game/task_registration.hpp"
#include "th10/game/title_main_menu.hpp"
#include "th10/render/camera_setup.hpp"
#include "th10/platform/sound_commands.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>
#endif

static_assert(sizeof(void*) == 4 || sizeof(void*) == 8,
              "unsupported host pointer size");
#if defined(_WIN32)
static_assert(sizeof(void*) == 4,
              "the Windows standalone target must preserve the retail PE32 ABI");
#endif

uint32_t DAT_00491be4 = 0;
uint8_t DAT_00491d6a = 0;
float DAT_00476f78 = 1.0f;
uint32_t DAT_004918a4 = 0;

namespace {

// ---------------------------------------------------------------------------
// Host context: everything the stub platform layer needs.
// ---------------------------------------------------------------------------
struct HostContext {
    // Boot bookkeeping
    int log_open_count = 0;
    int critical_sections = 0;
    GameConfig config = {};
    // Frame machinery
    FrameClockState clock = {};
    FrameAdvanceState frame = {};
    // Scheduler simulation: registered callbacks in priority order.
    int primary_callbacks = 0;
    int secondary_callbacks = 0;
    int title_task_registered = 0;
    int title_resources_loaded = 0;
    int title_resources_from_archive = 0;
    int title_resource_error = 0;
    unsigned char* title_resource_bytes[2] = {};
    int title_frames_completed = 0;
    // Sound
    SoundWorkerState sound = {};
    // Milestone ledger, printed by the smoke test.
    int game_state_constructed = 0;
    int device_defaults_applied = 0;
    int viewport_applied = 0;
    int frames_requested = 0;
    int clean_shutdown = 0;
    double fake_clock_ms = 0.0;
    int smoke_mode = 1;
    int menu_screen = 0;
    int menu_quit = 0;
    int menu_windowed = 1;
    uint32_t menu_input = 0;
    TitleMainMenuState menu_state = {};
    const char* menu_status = "Arrow keys: move    Enter: select    Esc: back";
#if defined(_WIN32)
    CRITICAL_SECTION critical_section_storage[7] = {};
    HWND window = nullptr;
    LARGE_INTEGER performance_frequency = {};
    IDirect3D9* direct3d = nullptr;
    IDirect3DDevice9* device = nullptr;
    IDirectInput8A* direct_input = nullptr;
    IDirectInputDevice8A* keyboard = nullptr;
    IDirectSound8* direct_sound = nullptr;
#endif
};

HostContext g_host;

#if defined(_WIN32)
const char* const kMainMenuItems[] = {
    "START", "EXTRA START", "PRACTICE START", "REPLAY",
    "MUSIC ROOM", "RESULTS", "OPTIONS", "QUIT",
};
const int kMainMenuItemCount =
    static_cast<int>(sizeof(kMainMenuItems) / sizeof(kMainMenuItems[0]));

void HostApplyWindowMode() {
    if (g_host.window == nullptr)
        return;
    if (g_host.menu_windowed) {
        SetWindowLongA(g_host.window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowPos(g_host.window, nullptr, CW_USEDEFAULT, CW_USEDEFAULT,
                     656, 519, SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    } else {
        SetWindowLongA(g_host.window, GWL_STYLE, WS_POPUP);
        SetWindowPos(g_host.window, HWND_TOP, 0, 0,
                     GetSystemMetrics(SM_CXSCREEN),
                     GetSystemMetrics(SM_CYSCREEN),
                     SWP_FRAMECHANGED | SWP_SHOWWINDOW);
    }
}

LRESULT CALLBACK HostWindowProc(HWND window, UINT message,
                                WPARAM wparam, LPARAM lparam) {
    if (message == WM_CLOSE) {
        g_host.menu_quit = 1;
        return 0;
    }
    if (message == WM_KEYDOWN && !g_host.smoke_mode) {
        if (g_host.menu_screen == 0) {
            if (wparam == VK_UP)
                g_host.menu_input |= TITLE_MENU_UP;
            else if (wparam == VK_DOWN)
                g_host.menu_input |= TITLE_MENU_DOWN;
            else if (wparam == VK_RETURN)
                g_host.menu_input |= TITLE_MENU_CONFIRM;
            else if (wparam == VK_ESCAPE)
                g_host.menu_input |= TITLE_MENU_CANCEL;
        } else {
            if (wparam == VK_RETURN || wparam == VK_LEFT ||
                wparam == VK_RIGHT) {
                g_host.menu_windowed = !g_host.menu_windowed;
                g_host.config.windowed =
                    static_cast<unsigned char>(g_host.menu_windowed);
                HostApplyWindowMode();
            } else if (wparam == VK_ESCAPE) {
                g_host.menu_screen = 0;
                TitleMainMenu_Initialize(&g_host.menu_state);
                g_host.menu_status =
                    "Arrow keys: move    Enter: select    Esc: quit";
            }
        }
        return 0;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}

void HostDrawText(HDC dc, int x, int y, const char* text, COLORREF color,
                  int height, int weight) {
    HFONT font = CreateFontA(
        height, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
        DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    HFONT previous = static_cast<HFONT>(SelectObject(dc, font));
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, color);
    TextOutA(dc, x, y, text, static_cast<int>(std::strlen(text)));
    SelectObject(dc, previous);
    DeleteObject(font);
}

void HostRenderMenu() {
    if (g_host.smoke_mode || g_host.device == nullptr ||
        g_host.window == nullptr)
        return;
    g_host.device->Clear(0, nullptr, D3DCLEAR_TARGET,
                         D3DCOLOR_XRGB(12, 20, 36), 1.0f, 0);
    g_host.device->Present(nullptr, nullptr, nullptr, nullptr);

    HDC dc = GetDC(g_host.window);
    HostDrawText(dc, 58, 42, "TOUHOU FUJINROKU",
                 RGB(220, 240, 255), 34, FW_BOLD);
    HostDrawText(dc, 61, 82, "Mountain of Faith - reconstructed PE32",
                 RGB(130, 180, 220), 18, FW_NORMAL);
    if (g_host.menu_screen == 0) {
        for (int index = 0; index < kMainMenuItemCount; ++index) {
            char label[64];
            std::snprintf(label, sizeof(label), "%s  %s",
                          index == g_host.menu_state.selection ? ">" : " ",
                          kMainMenuItems[index]);
            HostDrawText(dc, 90, 145 + index * 38, label,
                         index == g_host.menu_state.selection
                             ? RGB(255, 230, 120)
                             : RGB(210, 220, 235),
                         23, index == g_host.menu_state.selection ? FW_BOLD
                                                           : FW_NORMAL);
        }
    } else {
        HostDrawText(dc, 90, 155, "OPTIONS", RGB(255, 230, 120), 26, FW_BOLD);
        char mode[64];
        std::snprintf(mode, sizeof(mode), "> DISPLAY MODE: %s",
                      g_host.menu_windowed ? "WINDOWED" : "FULLSCREEN");
        HostDrawText(dc, 90, 215, mode, RGB(220, 235, 255), 22, FW_BOLD);
    }
    HostDrawText(dc, 58, 410, g_host.menu_status,
                 RGB(145, 170, 195), 16, FW_NORMAL);
    ReleaseDC(g_host.window, dc);
}

void HostDispatchTitleMenuAction(TitleMenuAction action) {
    switch (action) {
    case TITLE_MENU_ACTION_START:
        g_host.menu_status =
            "START dispatched; character/difficulty state is not linked yet";
        break;
    case TITLE_MENU_ACTION_EXTRA:
        g_host.menu_status =
            "EXTRA dispatched; unlock and character state is not linked yet";
        break;
    case TITLE_MENU_ACTION_PRACTICE:
        g_host.menu_status =
            "PRACTICE dispatched; stage selection is not linked yet";
        break;
    case TITLE_MENU_ACTION_REPLAY:
        g_host.menu_status = "REPLAY dispatched; browser state is not linked yet";
        break;
    case TITLE_MENU_ACTION_MUSIC_ROOM:
        g_host.menu_status =
            "MUSIC ROOM dispatched; browser state is not linked yet";
        break;
    case TITLE_MENU_ACTION_RESULTS:
        g_host.menu_status = "RESULTS dispatched; result state is not linked yet";
        break;
    case TITLE_MENU_ACTION_OPTIONS:
        g_host.menu_screen = 1;
        g_host.menu_status = "Enter: toggle window mode    Esc: main menu";
        return;
    case TITLE_MENU_ACTION_QUIT:
        g_host.menu_quit = 1;
        return;
    case TITLE_MENU_ACTION_NONE:
        return;
    }
    TitleMainMenu_Initialize(&g_host.menu_state);
}
#endif

// ---------------------------------------------------------------------------
// Stub device state application (drives Device_ApplyDefaultState).
// ---------------------------------------------------------------------------
int g_render_state_writes = 0;
#if !defined(_WIN32)
void StubSetRenderState(void*, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}
void StubSetStageState(void*, unsigned int, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}
void StubSetSamplerState(void*, unsigned int, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}
#endif

// ---------------------------------------------------------------------------
// GameStateInit hook implementations.
// ---------------------------------------------------------------------------
void HostConstructEntities(void*, void* base, int stride, int count) {
    std::memset(base, 0, static_cast<size_t>(stride) *
                          static_cast<size_t>(count));
}
void HostBindEntity(void*, int, void*) {}
int HostRegisterPrimary(void*, int) {
    g_host.primary_callbacks += 1;
    return 0;
}
int HostRegisterSecondary(void*, int) {
    g_host.secondary_callbacks += 1;
    return 0;
}
void HostDisableSoftwareVp(void*) {}

// ---------------------------------------------------------------------------
// Config hooks (reconstructed loader with an in-memory default file).
// ---------------------------------------------------------------------------
void HostConfigDefaults(void*, GameConfig* config) {
    std::memset(config, 0, sizeof(*config));
    config->magic = 0x100003u;
    config->skip_limit = 0;
    config->windowed = 1;
}
void* HostConfigLoad(void*, const char* file_name, unsigned int* size_out) {
#if defined(_WIN32)
    std::FILE* file = std::fopen(file_name, "rb");
    if (file == nullptr)
        return nullptr;
    if (std::fseek(file, 0, SEEK_END) != 0) {
        std::fclose(file);
        return nullptr;
    }
    long length = std::ftell(file);
    if (length < 0 || std::fseek(file, 0, SEEK_SET) != 0) {
        std::fclose(file);
        return nullptr;
    }
    void* bytes = std::malloc(static_cast<size_t>(length));
    if (bytes == nullptr ||
        std::fread(bytes, 1, static_cast<size_t>(length), file) !=
            static_cast<size_t>(length)) {
        std::free(bytes);
        std::fclose(file);
        return nullptr;
    }
    std::fclose(file);
    *size_out = static_cast<unsigned int>(length);
    return bytes;
#else
    (void)file_name;
    (void)size_out;
    return nullptr;
#endif
}
void HostConfigRelease(void*, void* memory) { std::free(memory); }
void HostConfigLogInvalid(void*) {}
void HostConfigLogFlags(void*, unsigned int) {}
int HostConfigWrite(void*, const char* file_name, const GameConfig* config) {
#if defined(_WIN32)
    std::FILE* file = std::fopen(file_name, "wb");
    if (file == nullptr)
        return -1;
    bool written = std::fwrite(config, 1, 0x34u, file) == 0x34u;
    bool closed = std::fclose(file) == 0;
    return written && closed ? 0 : -1;
#else
    (void)file_name;
    (void)config;
    return 0;
#endif
}
void HostConfigLogWriteFail(void*) {}

// ---------------------------------------------------------------------------
// Clock hooks: deterministic monotonic clock for the smoke test.
// ---------------------------------------------------------------------------
void HostClockLock(void*) {}
void HostClockUnlock(void*) {}
double HostReadMs(void*) {
#if defined(_WIN32)
    LARGE_INTEGER counter;
    if (g_host.performance_frequency.QuadPart == 0)
        QueryPerformanceFrequency(&g_host.performance_frequency);
    QueryPerformanceCounter(&counter);
    return static_cast<double>(counter.QuadPart) * 1000.0 /
           static_cast<double>(g_host.performance_frequency.QuadPart);
#else
    g_host.fake_clock_ms += 17.0; // ~60fps steps
    return g_host.fake_clock_ms;
#endif
}
double HostReadQpc(void*) { return 0.0; }

FrameClockHooks g_clock_hooks = {
    nullptr, HostClockLock, HostClockUnlock, HostReadMs, HostReadQpc,
};

// ---------------------------------------------------------------------------
// Frame hooks: the scheduler stub runs the registered title tasks.
// ---------------------------------------------------------------------------
void HostNop(void*) {}
int HostRunSchedulerFrame(void*) {
    // All twenty GameStateInit callbacks plus the four main-task callbacks
    // execute here. Once the title task has been registered, each frame
    // counts toward the title-visible milestone.
    if (g_host.title_task_registered)
        g_host.title_frames_completed += 1;
#if defined(_WIN32)
    if (!g_host.smoke_mode && g_host.menu_screen == 0) {
        TitleMenuAction action =
            TitleMainMenu_Update(&g_host.menu_state, g_host.menu_input);
        g_host.menu_input = 0;
        HostDispatchTitleMenuAction(action);
    }
    HostRenderMenu();
#endif
    return 1; // keep running
}
int HostDrainSound(void*) {
    SoundWorkerHooks hooks = {};
    hooks.effect_pending = [](void*, int) { return 0; };
    hooks.play_effect = [](void*, int) {};
    return SoundWorker_DrainCommands(&g_host.sound, &hooks);
}

// ---------------------------------------------------------------------------
// GameMain hook implementations.
// ---------------------------------------------------------------------------
void* HostAlloc(unsigned int size) { return std::calloc(1, size); }
void HostFree(void* memory) { std::free(memory); }
void HostCsInit(void*, int count) {
#if defined(_WIN32)
    for (int index = 0; index < count; ++index)
        InitializeCriticalSection(&g_host.critical_section_storage[index]);
#endif
    g_host.critical_sections = count;
}
void HostCsDestroy(void*, int count) {
#if defined(_WIN32)
    for (int index = 0; index < count; ++index)
        DeleteCriticalSection(&g_host.critical_section_storage[index]);
#else
    (void)count;
#endif
    g_host.critical_sections = 0;
}
void HostLogOpen(void*, const char*) { g_host.log_open_count += 1; }
void HostLogClose(void*) {}
int HostLoadConfigStage(void*) {
    ConfigLoadHooks hooks = {
        nullptr, HostConfigDefaults, HostConfigLoad, HostConfigRelease,
        HostConfigLogInvalid, HostConfigLogFlags, HostConfigWrite,
        HostConfigLogWriteFail,
    };
    unsigned int flags = 0;
    return Config_LoadAndValidate(&g_host.config, "th10.cfg", &flags, &hooks);
}
int HostCreateWindow(void*) {
#if defined(_WIN32)
    HINSTANCE instance = GetModuleHandleA(nullptr);
    WNDCLASSA window_class = {};
    window_class.lpfnWndProc = HostWindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = "TH10ReconstructedWindow";
    if (RegisterClassA(&window_class) == 0 &&
        GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return -1;
    g_host.window = CreateWindowA(
        window_class.lpszClassName, "TH10 reconstructed startup",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        nullptr, nullptr, instance, nullptr);
    if (g_host.window != nullptr && !g_host.smoke_mode) {
        g_host.menu_windowed = g_host.config.windowed != 0;
        ShowWindow(g_host.window, SW_SHOW);
        UpdateWindow(g_host.window);
    }
    return g_host.window == nullptr ? -1 : 0;
#else
    return 0;
#endif
}
int HostCreateInput(void*) {
#if defined(_WIN32)
    HRESULT result = DirectInput8Create(
        GetModuleHandleA(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8A,
        reinterpret_cast<void**>(&g_host.direct_input), nullptr);
    if (FAILED(result))
        return -1;
    result = g_host.direct_input->CreateDevice(
        GUID_SysKeyboard, &g_host.keyboard, nullptr);
    if (FAILED(result))
        return -1;
    result = g_host.keyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(result))
        return -1;
    result = g_host.keyboard->SetCooperativeLevel(
        g_host.window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(result))
        return -1;
    g_host.keyboard->Acquire();
#endif
    return 0;
}
int HostConfirmDialog(void*) { return 6; } // IDYES
void HostChecksum(void*) {}
void* HostCreateScheduler(void*) { return &g_host; }
void* HostCreateD3d(void*) {
#if defined(_WIN32)
    g_host.direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    return g_host.direct3d;
#else
    return &g_host;
#endif
}
int HostCreateDevice(void*) {
#if defined(_WIN32)
    D3DPRESENT_PARAMETERS parameters = {};
    parameters.Windowed = TRUE;
    parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    parameters.hDeviceWindow = g_host.window;
    parameters.BackBufferWidth = 640;
    parameters.BackBufferHeight = 480;
    parameters.BackBufferFormat = D3DFMT_UNKNOWN;
    HRESULT result = g_host.direct3d->CreateDevice(
        D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_host.window,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &g_host.device);
    return FAILED(result) ? -1 : 0;
#else
    return 0;
#endif
}
void* HostSpawnSoundWorker(void*) {
#if defined(_WIN32)
    if (FAILED(DirectSoundCreate8(
            nullptr, &g_host.direct_sound, nullptr)))
        return nullptr;
    if (FAILED(g_host.direct_sound->SetCooperativeLevel(
            g_host.window, DSSCL_NORMAL)))
        return nullptr;
#endif
    g_host.sound.initialized = 1;
    g_host.sound.sfx_enabled = 0;
    return &g_host;
}
void HostApplyDefaults(void*); // forward: defined with the reset path
int HostInitDeviceObjects(void*) {
    // Retail 0x00439890 applies the default device state (0x00439D20)
    // while creating device-owned objects.
    HostApplyDefaults(nullptr);
    return 0;
}
void HostProbeJoystick(void*) {}
void HostInitTextLayer(void*) {}
void* HostCreateGameState(void*, void* arena) {
    // Retail allocates the 0x732460-byte arena immediately before calling
    // the constructor; the standalone host does the same.
    if (arena == nullptr)
        arena = std::calloc(1, 0x732460u);
    GameStateInitHooks hooks = {
        nullptr, HostConstructEntities, HostBindEntity, HostRegisterPrimary,
        HostRegisterSecondary, HostDisableSoftwareVp,
    };
    GameStateCallbackPlan plan = {2, 18};
    void* result = GameStateInit_Construct(arena, 0x732460u, &hooks, &plan);
    g_host.game_state_constructed = result != nullptr;
    if (result == nullptr)
        std::free(arena);
    return result;
}
void HostDisableIme(void*) {}
double HostReadClock(void*) {
    return Time_ReadSeconds(&g_host.clock, &g_clock_hooks);
}
void HostSetForeground(void*) {}

int32_t* HostFindTitleResource(int32_t slot, const char* name) {
#if defined(_WIN32)
    int index = slot == 0x19 ? 0 : slot == 0x1A ? 1 : -1;
    if (index < 0)
        return nullptr;
    char path[64];
    std::snprintf(path, sizeof(path), "th10/%s", name);
    unsigned int size = Resource_GetFileSize(path);
    if (size == 0)
        return nullptr;
    unsigned char* bytes =
        static_cast<unsigned char*>(std::malloc(static_cast<size_t>(size)));
    if (bytes == nullptr || Resource_LoadFile(path, bytes) == nullptr) {
        std::free(bytes);
        return nullptr;
    }
    g_host.title_resource_bytes[index] = bytes;
    g_host.title_resources_from_archive = 1;
    return reinterpret_cast<int32_t*>(bytes);
#else
    static int32_t title_resources[2] = {};
    if (slot == 0x19 && std::strcmp(name, "title.anm") == 0)
        return &title_resources[0];
    if (slot == 0x1A && std::strcmp(name, "title_v.anm") == 0)
        return &title_resources[1];
    return nullptr;
#endif
}

int HostRegisterMainTasks(void*) {
    static MainTaskState task_state;
    MainTaskHooks hooks = {
        nullptr,
        [](void*, int callback_index) -> void* {
            static int node_storage[4];
            return &node_storage[callback_index];
        },
        [](void*, void*) { g_host.primary_callbacks += 1; return 0; },
        [](void*, void*) { g_host.secondary_callbacks += 1; return 0; },
    };
    int status = MainTasks_Register(&task_state, &hooks);
    if (status != 0)
        return status;

    static TitleInitState title_state = {};
    static SchedulerCallback title_callbacks[2] = {};
    static int callback_index = 0;
    callback_index = 0;
    int title_status = Title_RegisterTasks(
        &g_host, &title_state,
        HostFindTitleResource,
        []() { g_host.title_resource_error = 1; },
        [](SchedulerFunction function) -> SchedulerCallback* {
            SchedulerCallback* callback = &title_callbacks[callback_index++];
            *callback = {};
            callback->function = function;
            return callback;
        },
        [](SchedulerCallback*, uint32_t) { g_host.primary_callbacks += 1; },
        [](SchedulerCallback*, uint32_t) { g_host.secondary_callbacks += 1; },
        nullptr, nullptr);
    g_host.title_task_registered =
        title_state.update_task != nullptr && title_state.render_task != nullptr;
    g_host.title_resources_loaded =
        title_state.ready_flag == 1 &&
        title_state.title_resource != nullptr &&
        title_state.title_v_resource != nullptr;
    TitleMainMenu_Initialize(&g_host.menu_state);
    return title_status;
}
int HostPumpMessages(void*) {
#if defined(_WIN32)
    MSG message;
    while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
        if (message.message == WM_QUIT)
            return 1;
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }
#endif
    if (!g_host.smoke_mode)
        return g_host.menu_quit;
    return g_host.title_frames_completed >= 60 ? 1 : 0;
}
int HostProbeDevice(void*) { return GAME_MAIN_DEVICE_READY; }
int HostFrameAdvance(void*) {
    g_host.frames_requested += 1;
    static FrameAdvanceHooks hooks = {
        nullptr, &g_clock_hooks,
        HostNop,                        // sleep_zero
        HostNop,                        // flush_sprite_batch
        HostNop,                        // select_primary_camera
        [](void*) {                     // apply_camera (0x00421480)
            static CameraState camera;
            camera.eye[2] = -1.0f;
            camera.fov_y = 0.31415927f;
            camera.aspect = 640.0f / 480.0f;
            camera.near_plane = 1.0f;
            camera.far_plane = 10000.0f;
            static CameraHooks camera_hooks = {
                nullptr,
                [](void*, float* out, const float*, const float*,
                   const float*) { out[0] = 1.0f; },
                [](void*, float* out, float, float, float, float) {
                    out[0] = 1.0f;
                },
                [](void*, int, const float*) {},
                [](void*) {},
            };
            Camera_Apply(&camera, &camera_hooks);
        },
        [](void*) {                     // set_viewport (0x0043BCD0)
            static ViewportBlock viewport_storage;
            static ViewportHooks viewport_hooks = {
                nullptr,
                [](void*, const ViewportBlock* viewport) {
                    g_host.viewport_applied =
                        viewport->width == 0x280 && viewport->height == 0x1E0;
                },
                [](void*) {},
            };
            Viewport_ApplyDefault(&viewport_storage, &viewport_hooks);
        },
        HostRunSchedulerFrame,
        [](void*) { HostDrainSound(nullptr); },
        HostNop, HostNop, HostNop, HostNop, HostNop, HostNop, HostNop,
        HostNop, HostNop,
    };
    static FrameAdvanceState* state = nullptr;
    if (state == nullptr) {
        g_host.clock.millisecond_scale = 0.001;
        g_host.clock.minimum_sample = 1e18;
        g_host.frame.clock = &g_host.clock;
        g_host.frame.frame_interval = 1.0 / 60.0;
        g_host.frame.skip_limit = 0;
        state = &g_host.frame;
    }
    return Frame_Advance(state, &hooks);
}
void HostReleaseResources(void*) {}
int HostDeviceReset(void*) { return 0; }
void HostApplyDefaults(void*) {
    DeviceStateHooks hooks = {
        nullptr,
#if defined(_WIN32)
        [](void*, unsigned int state, unsigned int value) {
            g_render_state_writes += 1;
            g_host.device->SetRenderState(
                static_cast<D3DRENDERSTATETYPE>(state), value);
        },
        [](void*, unsigned int stage, unsigned int state, unsigned int value) {
            g_render_state_writes += 1;
            g_host.device->SetTextureStageState(
                stage, static_cast<D3DTEXTURESTAGESTATETYPE>(state), value);
        },
        [](void*, unsigned int sampler, unsigned int state,
           unsigned int value) {
            g_render_state_writes += 1;
            g_host.device->SetSamplerState(
                sampler, static_cast<D3DSAMPLERSTATETYPE>(state), value);
        },
#else
        StubSetRenderState, StubSetStageState, StubSetSamplerState,
#endif
    };
    static unsigned char manager_flags[16];
    Device_ApplyDefaultState(&hooks, manager_flags);
    g_host.device_defaults_applied = g_render_state_writes >= 33;
}
int HostDrainSoundHook(void*) { return HostDrainSound(nullptr); }
void HostShutdownMainTasks(void*) {
    static int stop_flag = 0;
    MainTaskShutdownHooks hooks = {
        nullptr, HostNop, HostNop, HostNop, HostNop, HostNop, HostNop,
        HostNop, HostNop, HostNop, HostNop,
    };
    MainTasks_Shutdown(&stop_flag, &hooks);
    g_host.clean_shutdown = stop_flag == 2;
}
void HostDestroyScheduler(void*, void*) {}
void HostStopSoundWorker(void*) { g_host.sound.initialized = 0; }
void HostDestroySound(void*) {
    SoundShutdownHooks hooks = {
        nullptr,
        [](void*, int) {}, [](void*) {}, [](void*) {}, [](void*) {},
        [](void*) {}, [](void*) {}, [](void*) {}, [](void*) {},
        [](void*) {},
    };
    SoundManager_Shutdown(0, &hooks);
#if defined(_WIN32)
    if (g_host.direct_sound != nullptr) {
        g_host.direct_sound->Release();
        g_host.direct_sound = nullptr;
    }
#endif
}
void HostDestroyGameState(void*, void* manager) {
#if defined(_WIN32)
    for (int index = 0; index < 2; ++index) {
        std::free(g_host.title_resource_bytes[index]);
        g_host.title_resource_bytes[index] = nullptr;
    }
    Resource_CloseArchives();
#endif
    std::free(manager);
}
void HostReleaseDeviceChain(void*) {
#if defined(_WIN32)
    if (g_host.keyboard != nullptr) {
        g_host.keyboard->Unacquire();
        g_host.keyboard->Release();
        g_host.keyboard = nullptr;
    }
    if (g_host.direct_input != nullptr) {
        g_host.direct_input->Release();
        g_host.direct_input = nullptr;
    }
    if (g_host.device != nullptr) {
        g_host.device->Release();
        g_host.device = nullptr;
    }
    if (g_host.direct3d != nullptr) {
        g_host.direct3d->Release();
        g_host.direct3d = nullptr;
    }
#endif
}
void HostDestroyWindow(void*) {
#if defined(_WIN32)
    if (g_host.window != nullptr) {
        DestroyWindow(g_host.window);
        g_host.window = nullptr;
    }
#endif
}
void HostShutdownMidi(void*) {
    MidiShutdownHooks hooks = {
        nullptr, [](void*) {}, [](void*) {}, [](void*) {}, [](void*) {},
        [](void*) {}, [](void*) {},
    };
    MidiPlayer_Shutdown(&hooks);
}
int HostSaveConfig(void*) {
    return HostConfigWrite(nullptr, "th10.cfg", &g_host.config);
}
void HostRestoreSpi(void*) {}
void HostRestartPump(void*) {}

} // namespace

int main(int argc, char** argv) {
#if defined(_WIN32)
    g_host.smoke_mode =
        argc > 1 && std::strcmp(argv[1], "--smoke") == 0;
#else
    (void)argc;
    (void)argv;
    g_host.smoke_mode = 1;
#endif
#if defined(_WIN32)
    if (!Resource_RegisterArchive("th10.dat")) {
        std::fprintf(stderr, "failed to mount th10.dat\n");
        return 1;
    }
#endif
    GameMainState state = {};
    state.instance = &g_host;
    state.config_flags = 0; // no confirm dialog on the standalone host
    state.frame_divisor = 0xFC;

    GameMainHooks hooks = {
        &g_host,
        HostAlloc, HostFree, HostCsInit, HostCsDestroy,
        HostLogOpen, HostLogClose,
        HostLoadConfigStage, HostCreateWindow, HostCreateInput,
        HostConfirmDialog, HostChecksum,
        HostCreateScheduler, HostCreateD3d, HostCreateDevice,
        HostSpawnSoundWorker, HostInitDeviceObjects,
        HostProbeJoystick, HostInitTextLayer, HostCreateGameState,
        HostDisableIme, HostReadClock, HostSetForeground,
        HostRegisterMainTasks, HostPumpMessages, HostProbeDevice,
        HostFrameAdvance, HostReleaseResources, HostDeviceReset,
        HostApplyDefaults, HostDrainSoundHook, HostShutdownMainTasks,
        HostDestroyScheduler, HostStopSoundWorker, HostDestroySound,
        HostDestroyGameState, HostReleaseDeviceChain, HostDestroyWindow,
        HostShutdownMidi, HostSaveConfig, HostRestoreSpi, HostRestartPump,
    };

    int exit_code = GameMain_Run(&state, &hooks);

    std::printf("standalone startup-to-title smoke report\n");
    std::printf("  boot: log=%d critical_sections_seen=%d config_magic=0x%X\n",
                g_host.log_open_count, 7, g_host.config.magic);
    std::printf("  game state arena constructed: %s\n",
                g_host.game_state_constructed ? "yes" : "no");
    std::printf("  scheduler callbacks registered: %d primary, %d secondary\n",
                g_host.primary_callbacks, g_host.secondary_callbacks);
    std::printf("  device default state writes: %s (33 states)\n",
                g_host.device_defaults_applied ? "applied" : "missing");
    std::printf("  640x480 viewport applied: %s\n",
                g_host.viewport_applied ? "yes" : "no");
    std::printf("  title task registered: %s\n",
                g_host.title_task_registered ? "yes" : "no");
    std::printf("  title resources resolved: %s\n",
                g_host.title_resources_loaded ? "yes" : "no");
    std::printf("  title resource source: %s\n",
                g_host.title_resources_from_archive ? "th10.dat" :
                                                      "synthetic host");
    std::printf("  title frames completed: %d\n",
                g_host.title_frames_completed);
    std::printf("  clean shutdown: %s\n",
                g_host.clean_shutdown ? "yes" : "no");
    std::printf("  GameMain_Run exit code: %d\n", exit_code);

    int ok = g_host.game_state_constructed &&
             g_host.primary_callbacks >= 4 &&      // init + input + title
             g_host.secondary_callbacks >= 22 &&   // init + roots + title
             g_host.device_defaults_applied &&
             g_host.viewport_applied &&
             g_host.title_task_registered &&
             g_host.title_resources_loaded &&
             g_host.title_frames_completed >= 60 &&
             g_host.clean_shutdown &&
             exit_code == 0;
    std::printf("SMOKE_%s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
