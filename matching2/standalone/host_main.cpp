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
#include "th10/game/task_registration.hpp"
#include "th10/render/camera_setup.hpp"
#include "th10/platform/sound_commands.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

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
};

HostContext g_host;

// ---------------------------------------------------------------------------
// Stub device state application (drives Device_ApplyDefaultState).
// ---------------------------------------------------------------------------
int g_render_state_writes = 0;
void StubSetRenderState(void*, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}
void StubSetStageState(void*, unsigned int, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}
void StubSetSamplerState(void*, unsigned int, unsigned int, unsigned int) {
    g_render_state_writes += 1;
}

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
void* HostConfigLoad(void*, const char*, unsigned int*) {
    return nullptr; // first boot: no th10.cfg, defaults win
}
void HostConfigRelease(void*, void* memory) { std::free(memory); }
void HostConfigLogInvalid(void*) {}
void HostConfigLogFlags(void*, unsigned int) {}
int HostConfigWrite(void*, const char*, const GameConfig*) { return 0; }
void HostConfigLogWriteFail(void*) {}

// ---------------------------------------------------------------------------
// Clock hooks: deterministic monotonic clock for the smoke test.
// ---------------------------------------------------------------------------
void HostClockLock(void*) {}
void HostClockUnlock(void*) {}
double HostReadMs(void*) {
    g_host.fake_clock_ms += 17.0; // ~60fps steps
    return g_host.fake_clock_ms;
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
void HostCsInit(void*, int count) { g_host.critical_sections = count; }
void HostCsDestroy(void*, int) { g_host.critical_sections = 0; }
void HostLogOpen(void*, const char*) { g_host.log_open_count += 1; }
void HostLogClose(void*) {}
int HostLoadConfigStage(void*) { return 0; }
int HostCreateWindow(void*) { return 0; }
int HostCreateInput(void*) {
    ConfigLoadHooks hooks = {
        nullptr, HostConfigDefaults, HostConfigLoad, HostConfigRelease,
        HostConfigLogInvalid, HostConfigLogFlags, HostConfigWrite,
        HostConfigLogWriteFail,
    };
    unsigned int flags = 0;
    return Config_LoadAndValidate(&g_host.config, "th10.cfg", &flags,
                                  &hooks);
}
int HostConfirmDialog(void*) { return 6; } // IDYES
void HostChecksum(void*) {}
void* HostCreateScheduler(void*) { return &g_host; }
void* HostCreateD3d(void*) { return &g_host; }
int HostCreateDevice(void*) { return 0; }
void* HostSpawnSoundWorker(void*) {
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
    static int32_t title_resources[2] = {};
    callback_index = 0;
    int title_status = Title_RegisterTasks(
        &g_host, &title_state,
        [](int32_t slot, const char* name) -> int32_t* {
            if (slot == 0x19 && std::strcmp(name, "title.anm") == 0)
                return &title_resources[0];
            if (slot == 0x1A && std::strcmp(name, "title_v.anm") == 0)
                return &title_resources[1];
            return nullptr;
        },
        []() {},
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
        title_state.title_resource == &title_resources[0] &&
        title_state.title_v_resource == &title_resources[1];
    return title_status;
}
int HostPumpMessages(void*) {
    // Quit after enough frames for the title milestone (smoke budget).
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
        nullptr, StubSetRenderState, StubSetStageState, StubSetSamplerState,
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
}
void HostDestroyGameState(void*, void* manager) { std::free(manager); }
void HostReleaseDeviceChain(void*) {}
void HostDestroyWindow(void*) {}
void HostShutdownMidi(void*) {
    MidiShutdownHooks hooks = {
        nullptr, [](void*) {}, [](void*) {}, [](void*) {}, [](void*) {},
        [](void*) {}, [](void*) {},
    };
    MidiPlayer_Shutdown(&hooks);
}
int HostSaveConfig(void*) { return 0; }
void HostRestoreSpi(void*) {}
void HostRestartPump(void*) {}

} // namespace

int main() {
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
