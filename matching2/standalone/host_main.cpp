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
#include "th10/game/title_options_menu.hpp"
#include "th10/render/camera_setup.hpp"
#include "th10/render/anm_file.hpp"
#include "th10/script/anm_vm_tick.hpp"
#include "th10/platform/sound_commands.hpp"

#include "host_stage.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

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

struct HostAnmVm {
    AnmVmState state = {};
    int active = 0;
    int script_id = -1;
    int resource_index = 0;
    const unsigned char* resource_bytes = nullptr;
    unsigned int resource_size = 0;
    HostAnmVm* parent = nullptr;
    int integer_variables[6] = {};
    float float_variables[4] = {};
    int integer_fallback = 0;
    float float_fallback = 0.0f;
};

// ---------------------------------------------------------------------------
// Host context: everything the stub platform layer needs.
// ---------------------------------------------------------------------------
struct HostContext {
    // Boot bookkeeping
    int log_open_count = 0;
    int critical_sections = 0;
    GameConfig config = {};
    GameStateMatrixGlobals game_state_matrices = {};
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
    unsigned char* title_resource_bytes[3] = {};
    unsigned int title_resource_sizes[3] = {};
    AnmFileEntry title_entries[3] = {};
    int title_anm_parsed = 0;
    int title_vm_ready = 0;
    int title_draw_calls = 0;
    HostAnmVm title_vms[2] = {};
    HostAnmVm title_version_vm = {};
    int title_version_vm_ready = 0;
    HostAnmVm title_child_vms[64] = {};
    int title_child_vm_count = 0;
    int title_frames_completed = 0;
    HostAnmVm stage_vms[32] = {};
    StageStdSubrecordView stage_subrecords[32] = {};
    int stage_vm_object_indices[32] = {};
    int stage_vm_count = 0;
    int stage_vms_ready = 0;
    unsigned char* player_anm_bytes = nullptr;
    unsigned int player_anm_size = 0;
    HostAnmVm player_vm = {};
    int player_vm_ready = 0;
    int player_vm_attempted = 0;
    float player_x = 224.0f;
    float player_y = 400.0f;
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
    int dump_anm = 0;
    int dump_stage = 0;
    int menu_screen = 0;
    int title_flow = 0; // 0=sig/loading, 1=press, 2=main/submenus
    int title_flow_frame = 0;
    int title_transition_frame = 0;
    int menu_quit = 0;
    int menu_windowed = 1;
    uint32_t menu_input = 0;
    TitleMainMenuState menu_state = {};
    TitleOptionsState options_state = {};
    TitleOptionsConfig options_config = {0, 100, 80};
    int difficulty_selection = 0;
    int character_selection = 0;
    int weapon_selection = 0;
    int selection_phase_frame = 0;
    const char* menu_status = "Arrow keys: move    Enter: select    Esc: back";
#if defined(_WIN32)
    CRITICAL_SECTION critical_section_storage[7] = {};
    HWND window = nullptr;
    LARGE_INTEGER performance_frequency = {};
    IDirect3D9* direct3d = nullptr;
    IDirect3DDevice9* device = nullptr;
    IDirectInput8A* direct_input = nullptr;
    IDirectInputDevice8A* keyboard = nullptr;
    unsigned char previous_keyboard[256] = {};
    IDirectSound8* direct_sound = nullptr;
    IDirectSoundBuffer* bgm_buffer = nullptr;
    IDirectSoundBuffer* menu_sound_buffers[3] = {};
    const uint8_t* anm_texture_entry_bases[32] = {};
    IDirect3DTexture9* anm_textures[32] = {};
#endif
};

HostContext g_host;

#if defined(_WIN32)
void HostTrace(const char* message) {
    std::fprintf(stderr, "[th10-recon] %s\n", message);
    std::fflush(stderr);
}

int HostAnmIntArg(void* context, AnmVmState*, const void* slot,
                  int is_variable) {
    int value;
    std::memcpy(&value, slot, sizeof(value));
    if (!is_variable)
        return value;
    HostAnmVm* runtime = static_cast<HostAnmVm*>(context);
    if (value >= 10000 && value <= 10003)
        return runtime->integer_variables[value - 10000];
    if (value >= 10008 && value <= 10009)
        return runtime->integer_variables[value - 10004];
    return value;
}

float HostAnmFloatArg(void* context, AnmVmState* vm, const void* slot,
                      int is_variable) {
    float value;
    std::memcpy(&value, slot, sizeof(value));
    if (!is_variable)
        return value;
    int id;
    std::memcpy(&id, slot, sizeof(id));
    HostAnmVm* runtime = static_cast<HostAnmVm*>(context);
    if (id >= 10004 && id <= 10007)
        return runtime->float_variables[id - 10004];
    if (id >= 10013 && id <= 10015)
        return vm->position[id - 10013];
    return value;
}

int* HostAnmIntSlot(void* context, AnmVmState*, int id) {
    HostAnmVm* runtime = static_cast<HostAnmVm*>(context);
    if (id >= 10000 && id <= 10003)
        return &runtime->integer_variables[id - 10000];
    if (id >= 10008 && id <= 10009)
        return &runtime->integer_variables[id - 10004];
    return &runtime->integer_fallback;
}

float* HostAnmFloatSlot(void* context, AnmVmState* vm, int id) {
    HostAnmVm* runtime = static_cast<HostAnmVm*>(context);
    if (id >= 10004 && id <= 10007)
        return &runtime->float_variables[id - 10004];
    if (id >= 10013 && id <= 10015)
        return &vm->position[id - 10013];
    return &runtime->float_fallback;
}

void HostAnmSetTime(void*, AnmVmState* vm, float value) {
    vm->time = static_cast<int>(value);
    vm->time_accumulator = value;
}

float HostAnmWrapAngle(void*, float value) {
    const float circle = 6.2831853f;
    while (value < 0.0f)
        value += circle;
    while (value >= circle)
        value -= circle;
    return value;
}

void HostInitializeAnmVm(HostAnmVm* runtime,
                         const unsigned char* instructions);

AnmVmHooks HostAnmHooks(HostAnmVm* runtime) {
    static const float scroll[3] = {};
    AnmVmHooks hooks = {};
    hooks.context = runtime;
    hooks.read_int_arg = HostAnmIntArg;
    hooks.read_float_arg = HostAnmFloatArg;
    hooks.int_var_slot = HostAnmIntSlot;
    hooks.float_var_slot = HostAnmFloatSlot;
    hooks.set_sprite = [](void*, AnmVmState* vm, int sprite) {
        vm->sprite = sprite;
    };
    hooks.set_time = HostAnmSetTime;
    hooks.rand_float = [](void*, int) { return 0.5f; };
    hooks.rand_u32 = [](void*, int) { return 0x80000000u; };
    hooks.wrap_angle = HostAnmWrapAngle;
    hooks.start_ring_mode = [](void*, AnmVmState*) {};
    hooks.spawn_child = [](void* context, AnmVmState*, int, int script_id) {
        HostAnmVm* parent = static_cast<HostAnmVm*>(context);
        int resource = parent->resource_index;
        const unsigned char* resource_bytes = parent->resource_bytes;
        unsigned int resource_size = parent->resource_size;
        if (resource_bytes == nullptr && resource >= 0 && resource < 3) {
            resource_bytes = g_host.title_resource_bytes[resource];
            resource_size = g_host.title_resource_sizes[resource];
        }
        if (resource_bytes == nullptr)
            return;
        AnmFileScript script;
        if (!AnmFile_FindGlobalScript(
                resource_bytes, resource_size,
                static_cast<unsigned int>(script_id), nullptr, &script))
            return;
        int slot = -1;
        for (int index = 0; index < g_host.title_child_vm_count; ++index)
            if (!g_host.title_child_vms[index].active) {
                slot = index;
                break;
            }
        if (slot < 0) {
            if (g_host.title_child_vm_count >= 64)
                return;
            slot = g_host.title_child_vm_count++;
        }
        HostAnmVm* child = &g_host.title_child_vms[slot];
        HostInitializeAnmVm(child, script.instructions);
        child->script_id = script_id;
        child->resource_index = resource;
        child->resource_bytes = resource_bytes;
        child->resource_size = resource_size;
        child->parent = parent;
    };
    hooks.update_ring_vertices = [](void*, AnmVmState*) {};
    hooks.set_blend_bits =
        [](void*, AnmVmState* vm, unsigned int mask, unsigned int value) {
            vm->flags = (vm->flags & ~mask) | (value & mask);
        };
    hooks.scroll_delta = scroll;
    return hooks;
}

void HostInitializeAnmVm(HostAnmVm* runtime,
                         const unsigned char* instructions) {
    *runtime = {};
    runtime->active = 1;
    runtime->state.script_base = instructions;
    runtime->state.pc = instructions;
    runtime->state.sprite = -1;
    runtime->state.scale[0] = 1.0f;
    runtime->state.scale[1] = 1.0f;
    runtime->state.scale[2] = 1.0f;
    runtime->state.color[0] = 0xFF;
    runtime->state.color[1] = 0xFF;
    runtime->state.color[2] = 0xFF;
    runtime->state.color[3] = 0xFF;
    runtime->state.speed = 1.0f;
}

bool HostStartTitleScripts(unsigned int first, unsigned int second) {
    if (g_host.title_resource_bytes[0] == nullptr)
        return false;
    AnmFileScript scripts[2];
    if (!AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[0], g_host.title_resource_sizes[0],
            first, nullptr, &scripts[0]) ||
        !AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[0], g_host.title_resource_sizes[0],
            second, nullptr, &scripts[1]))
        return false;
    g_host.title_child_vm_count = 0;
    std::memset(g_host.title_child_vms, 0,
                sizeof(g_host.title_child_vms));
    HostInitializeAnmVm(&g_host.title_vms[0], scripts[0].instructions);
    HostInitializeAnmVm(&g_host.title_vms[1], scripts[1].instructions);
    g_host.title_vm_ready = 1;
    return true;
}

bool HostStartSigScript() {
    AnmFileScript script;
    if (g_host.title_resource_bytes[2] == nullptr ||
        !AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[2],
            g_host.title_resource_sizes[2], 0, nullptr, &script))
        return false;
    g_host.title_child_vm_count = 0;
    std::memset(g_host.title_child_vms, 0,
                sizeof(g_host.title_child_vms));
    HostInitializeAnmVm(&g_host.title_vms[0], script.instructions);
    g_host.title_vms[0].resource_index = 2;
    g_host.title_vms[1] = {};
    g_host.title_vm_ready = 1;
    return true;
}

bool HostSwitchTitleOverlay(unsigned int script_id) {
    AnmFileScript script;
    if (!AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[0],
            g_host.title_resource_sizes[0], script_id, nullptr, &script))
        return false;
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* ancestor = g_host.title_child_vms[index].parent;
        while (ancestor != nullptr && ancestor != &g_host.title_vms[1])
            ancestor = ancestor->parent;
        if (ancestor == &g_host.title_vms[1]) {
            if (g_host.title_child_vms[index].script_id == 92)
                g_host.title_child_vms[index].parent = nullptr;
            else
                g_host.title_child_vms[index].active = 0;
        }
    }
    HostInitializeAnmVm(&g_host.title_vms[1], script.instructions);
    return true;
}

void HostBroadcastTitleInterrupt(int interrupt) {
    g_host.title_vms[1].state.pending_interrupt = interrupt;
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* ancestor = g_host.title_child_vms[index].parent;
        while (ancestor != nullptr && ancestor != &g_host.title_vms[1])
            ancestor = ancestor->parent;
        if (g_host.title_child_vms[index].active &&
            ancestor == &g_host.title_vms[1])
            g_host.title_child_vms[index].state.pending_interrupt = interrupt;
    }
}

void HostPrimeMainMenuOverlay() {
    // Script 0 creates the eight normal and eight selected menu-item VMs on
    // its first tick. Retail then sends interrupt 28 to put every child in
    // its inactive-but-visible state before interrupt 17 selects Game Start.
    AnmVmHooks hooks = HostAnmHooks(&g_host.title_vms[1]);
    AnmVm_Tick(&g_host.title_vms[1].state, &hooks);
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* ancestor = g_host.title_child_vms[index].parent;
        while (ancestor != nullptr && ancestor != &g_host.title_vms[1])
            ancestor = ancestor->parent;
        if (g_host.title_child_vms[index].active &&
            ancestor == &g_host.title_vms[1])
            g_host.title_child_vms[index].state.pending_interrupt = 28;
    }
}

bool HostAddIndependentTitleScript(unsigned int script_id) {
    AnmFileScript script;
    if (g_host.title_resource_bytes[0] == nullptr ||
        g_host.title_child_vm_count >= 64 ||
        !AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[0],
            g_host.title_resource_sizes[0], script_id, nullptr, &script))
        return false;
    HostAnmVm* vm =
        &g_host.title_child_vms[g_host.title_child_vm_count++];
    HostInitializeAnmVm(vm, script.instructions);
    vm->script_id = static_cast<int>(script_id);
    vm->resource_index = 0;
    return true;
}

void HostSetOverlayChildInterrupt(int script_id, int interrupt) {
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* child = &g_host.title_child_vms[index];
        if (child->script_id == script_id) {
            child->active = 1;
            child->state.pending_interrupt = interrupt;
        }
    }
}

bool HostStartSelectionScreen(unsigned int heading_script,
                              unsigned int overlay_script) {
    if (!HostStartTitleScripts(94, overlay_script) ||
        !HostAddIndependentTitleScript(heading_script))
        return false;
    AnmVmHooks hooks = HostAnmHooks(&g_host.title_vms[1]);
    AnmVm_Tick(&g_host.title_vms[1].state, &hooks);
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* child = &g_host.title_child_vms[index];
        AnmVmHooks child_hooks = HostAnmHooks(child);
        if (AnmVm_Tick(&child->state, &child_hooks) != 0)
            child->active = 0;
    }
    g_host.selection_phase_frame = 0;
    return true;
}

void HostStartDifficultySelection() {
    g_host.menu_screen = 6;
    g_host.difficulty_selection = 0;
    HostStartSelectionScreen(98, 119);
    HostSetOverlayChildInterrupt(109, 17);
    g_host.menu_status =
        "Difficulty: arrows move, Enter confirms, Esc returns";
}

void HostStartCharacterSelection() {
    g_host.menu_screen = 7;
    g_host.character_selection = 0;
    HostStartSelectionScreen(99, 125);
    HostSetOverlayChildInterrupt(121, 7);
    HostSetOverlayChildInterrupt(123, 7);
    g_host.menu_status =
        "Character: arrows choose Reimu/Marisa, Enter confirms, Esc returns";
}

void HostStartWeaponSelection() {
    g_host.menu_screen = 8;
    g_host.weapon_selection = 0;
    unsigned int overlay =
        g_host.character_selection == 0 ? 150u : 151u;
    HostStartSelectionScreen(100, overlay);
    int selected_script =
        g_host.character_selection == 0 ? 126 : 129;
    HostSetOverlayChildInterrupt(selected_script, 17);
    HostSetOverlayChildInterrupt(
        144 + g_host.character_selection * 3, 17);
    g_host.menu_status =
        "Weapon: arrows choose type, Enter accepts, Esc returns";
}

void HostRestoreMainMenuLogo() {
    AnmFileScript script;
    if (g_host.title_resource_bytes[0] == nullptr ||
        !AnmFile_FindGlobalScript(
            g_host.title_resource_bytes[0],
            g_host.title_resource_sizes[0], 92, nullptr, &script) ||
        g_host.title_child_vm_count >= 64)
        return;
    HostAnmVm logo;
    HostInitializeAnmVm(&logo, script.instructions);
    logo.script_id = 92;
    logo.resource_index = 0;
    AnmVmHooks hooks = HostAnmHooks(&logo);
    for (int frame = 0; frame <= 60; ++frame)
        AnmVm_Tick(&logo.state, &hooks);
    logo.state.pending_interrupt = 6;
    for (int frame = 0; frame <= 80; ++frame)
        AnmVm_Tick(&logo.state, &hooks);
    g_host.title_child_vms[g_host.title_child_vm_count++] = logo;
}

void HostReturnToMainMenu() {
    g_host.menu_screen = 0;
    TitleMainMenu_Initialize(&g_host.menu_state);
    HostStartTitleScripts(88, 0);
    HostRestoreMainMenuLogo();
    HostPrimeMainMenuOverlay();
}

void HostRefreshOptionsSprites() {
    int music = g_host.options_config.music_volume;
    int sound = g_host.options_config.sound_volume;
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* child = &g_host.title_child_vms[index];
        int digit = -1;
        int base = 51;
        switch (child->script_id) {
        case 37: digit = music / 100; break;
        case 38: digit = music / 10 % 10; break;
        case 39: digit = music % 10; break;
        case 41: digit = music / 100; base = 61; break;
        case 42: digit = music / 10 % 10; base = 61; break;
        case 43: digit = music % 10; base = 61; break;
        case 45: digit = sound / 100; break;
        case 46: digit = sound / 10 % 10; break;
        case 47: digit = sound % 10; break;
        case 49: digit = sound / 100; base = 61; break;
        case 50: digit = sound / 10 % 10; base = 61; break;
        case 51: digit = sound % 10; base = 61; break;
        default: break;
        }
        if (digit >= 0)
            child->state.sprite = base + digit;
    }
}

void HostRefreshCharacterVisual() {
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* child = &g_host.title_child_vms[index];
        bool reimu = child->script_id == 121 || child->script_id == 123;
        bool marisa = child->script_id == 122 || child->script_id == 124;
        if (!reimu && !marisa)
            continue;
        bool selected =
            (g_host.character_selection == 0 && reimu) ||
            (g_host.character_selection == 1 && marisa);
        child->state.color[3] = selected ? 255 : 0;
    }
}

void HostRefreshBgmModeVisual() {
    static const int interrupts[3][2] = {
        {46, 47}, {48, 49}, {44, 45},
    };
    for (int index = 0; index < g_host.title_child_vm_count; ++index) {
        HostAnmVm* child = &g_host.title_child_vms[index];
        if (child->script_id == 31)
            child->state.pending_interrupt =
                interrupts[g_host.options_config.bgm_mode][0];
        else if (child->script_id == 32)
            child->state.pending_interrupt =
                interrupts[g_host.options_config.bgm_mode][1];
    }
}

LRESULT CALLBACK HostWindowProc(HWND window, UINT message,
                                WPARAM wparam, LPARAM lparam) {
    if (message == WM_CLOSE) {
        g_host.menu_quit = 1;
        return 0;
    }
    if (message == WM_KEYDOWN && !g_host.smoke_mode) {
        if (wparam == VK_UP)
            g_host.menu_input |= TITLE_MENU_UP;
        else if (wparam == VK_DOWN)
            g_host.menu_input |= TITLE_MENU_DOWN;
        else if (wparam == VK_LEFT)
            g_host.menu_input |= TITLE_OPTIONS_LEFT;
        else if (wparam == VK_RIGHT)
            g_host.menu_input |= TITLE_OPTIONS_RIGHT;
        else if (wparam == VK_RETURN)
            g_host.menu_input |= TITLE_MENU_CONFIRM;
        else if (wparam == VK_ESCAPE)
            g_host.menu_input |= TITLE_MENU_CANCEL;
        return 0;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}

unsigned int HostReadLe32(const unsigned char* bytes) {
    return static_cast<unsigned int>(bytes[0]) |
           (static_cast<unsigned int>(bytes[1]) << 8) |
           (static_cast<unsigned int>(bytes[2]) << 16) |
           (static_cast<unsigned int>(bytes[3]) << 24);
}

IDirectSoundBuffer* HostCreatePcmBuffer(const WAVEFORMATEX& format,
                                        const unsigned char* pcm,
                                        unsigned int size) {
    if (g_host.direct_sound == nullptr || pcm == nullptr || size == 0)
        return nullptr;
    DSBUFFERDESC description = {};
    description.dwSize = sizeof(description);
    description.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
    description.dwBufferBytes = size;
    description.lpwfxFormat = const_cast<WAVEFORMATEX*>(&format);
    IDirectSoundBuffer* buffer = nullptr;
    if (FAILED(g_host.direct_sound->CreateSoundBuffer(
            &description, &buffer, nullptr)))
        return nullptr;
    void* first = nullptr;
    void* second = nullptr;
    DWORD first_size = 0;
    DWORD second_size = 0;
    if (FAILED(buffer->Lock(0, size, &first, &first_size, &second,
                            &second_size, 0))) {
        buffer->Release();
        return nullptr;
    }
    std::memcpy(first, pcm, first_size);
    if (second != nullptr)
        std::memcpy(second, pcm + first_size, second_size);
    buffer->Unlock(first, first_size, second, second_size);
    return buffer;
}

IDirectSoundBuffer* HostLoadArchiveWave(const char* name) {
    char path[64];
    std::snprintf(path, sizeof(path), "th10/%s", name);
    unsigned int size = Resource_GetFileSize(path);
    if (size < 44)
        return nullptr;
    unsigned char* bytes =
        static_cast<unsigned char*>(std::malloc(size));
    if (bytes == nullptr || Resource_LoadFile(path, bytes) == nullptr) {
        std::free(bytes);
        return nullptr;
    }
    const unsigned char* format_chunk = nullptr;
    const unsigned char* pcm = nullptr;
    unsigned int pcm_size = 0;
    for (unsigned int offset = 12; offset + 8 <= size;) {
        unsigned int chunk_size = HostReadLe32(bytes + offset + 4);
        if (chunk_size > size - offset - 8)
            break;
        if (std::memcmp(bytes + offset, "fmt ", 4) == 0 &&
            chunk_size >= 16)
            format_chunk = bytes + offset + 8;
        else if (std::memcmp(bytes + offset, "data", 4) == 0) {
            pcm = bytes + offset + 8;
            pcm_size = chunk_size;
        }
        offset += 8 + ((chunk_size + 1) & ~1u);
    }
    IDirectSoundBuffer* result = nullptr;
    if (format_chunk != nullptr && pcm != nullptr) {
        WAVEFORMATEX format = {};
        std::memcpy(&format, format_chunk, 16);
        result = HostCreatePcmBuffer(format, pcm, pcm_size);
    }
    std::free(bytes);
    return result;
}

LONG HostDirectSoundVolume(int percent) {
    if (percent <= 0)
        return DSBVOLUME_MIN;
    if (percent >= 100)
        return DSBVOLUME_MAX;
    // DirectSound volume is measured in hundredths of a decibel. The retail
    // options store linear amplitude percentages, so convert 20*log10(p).
    double attenuation =
        2000.0 * std::log10(static_cast<double>(percent) / 100.0);
    if (attenuation < static_cast<double>(DSBVOLUME_MIN))
        attenuation = static_cast<double>(DSBVOLUME_MIN);
    return static_cast<LONG>(attenuation);
}

void HostApplyAudioVolumes() {
    if (g_host.bgm_buffer != nullptr)
        g_host.bgm_buffer->SetVolume(
            HostDirectSoundVolume(g_host.options_config.music_volume));
    LONG sound_volume =
        HostDirectSoundVolume(g_host.options_config.sound_volume);
    for (IDirectSoundBuffer* buffer : g_host.menu_sound_buffers)
        if (buffer != nullptr)
            buffer->SetVolume(sound_volume);
}

bool HostStartTitleBgm() {
    unsigned int fmt_size = Resource_GetFileSize("th10/thbgm.fmt");
    if (fmt_size < 52)
        return false;
    unsigned char* metadata =
        static_cast<unsigned char*>(std::malloc(fmt_size));
    if (metadata == nullptr ||
        Resource_LoadFile("th10/thbgm.fmt", metadata) == nullptr) {
        std::free(metadata);
        return false;
    }
    // First retail record is title track th10_02.wav.
    unsigned int offset = HostReadLe32(metadata + 0x10);
    unsigned int length = HostReadLe32(metadata + 0x14);
    WAVEFORMATEX format = {};
    std::memcpy(&format, metadata + 0x20, 16);
    std::free(metadata);

    std::FILE* file = std::fopen("thbgm.dat", "rb");
    if (file == nullptr || std::fseek(file, offset, SEEK_SET) != 0) {
        if (file != nullptr)
            std::fclose(file);
        return false;
    }
    unsigned char* pcm =
        static_cast<unsigned char*>(std::malloc(length));
    if (pcm == nullptr) {
        std::fclose(file);
        return false;
    }
    bool read = std::fread(pcm, 1, length, file) == length;
    std::fclose(file);
    if (read)
        g_host.bgm_buffer = HostCreatePcmBuffer(format, pcm, length);
    std::free(pcm);
    if (g_host.bgm_buffer == nullptr)
        return false;
    g_host.bgm_buffer->SetVolume(
        HostDirectSoundVolume(g_host.options_config.music_volume));
    return SUCCEEDED(g_host.bgm_buffer->Play(0, 0, DSBPLAY_LOOPING));
}

void HostPlayMenuSound(int index) {
    if (index < 0 || index >= 3 ||
        g_host.menu_sound_buffers[index] == nullptr)
        return;
    g_host.menu_sound_buffers[index]->SetVolume(
        HostDirectSoundVolume(g_host.options_config.sound_volume));
    g_host.menu_sound_buffers[index]->Stop();
    g_host.menu_sound_buffers[index]->SetCurrentPosition(0);
    g_host.menu_sound_buffers[index]->Play(0, 0, 0);
}

void HostPollKeyboard() {
    if (g_host.keyboard == nullptr)
        return;
    unsigned char keys[256] = {};
    HRESULT result = g_host.keyboard->GetDeviceState(sizeof(keys), keys);
    if (FAILED(result)) {
        g_host.keyboard->Acquire();
        result = g_host.keyboard->GetDeviceState(sizeof(keys), keys);
    }
    if (FAILED(result))
        return;
    if (HostStage_IsActive()) {
        float speed = (keys[DIK_LSHIFT] & 0x80) != 0 ? 2.0f : 4.0f;
        if ((keys[DIK_LEFT] & 0x80) != 0) g_host.player_x -= speed;
        if ((keys[DIK_RIGHT] & 0x80) != 0) g_host.player_x += speed;
        if ((keys[DIK_UP] & 0x80) != 0) g_host.player_y -= speed;
        if ((keys[DIK_DOWN] & 0x80) != 0) g_host.player_y += speed;
        if (g_host.player_x < 40.0f) g_host.player_x = 40.0f;
        if (g_host.player_x > 408.0f) g_host.player_x = 408.0f;
        if (g_host.player_y < 24.0f) g_host.player_y = 24.0f;
        if (g_host.player_y > 456.0f) g_host.player_y = 456.0f;
    }
    struct Binding { int key; uint32_t flag; };
    static const Binding bindings[] = {
        {DIK_UP, TITLE_MENU_UP}, {DIK_DOWN, TITLE_MENU_DOWN},
        {DIK_LEFT, TITLE_OPTIONS_LEFT}, {DIK_RIGHT, TITLE_OPTIONS_RIGHT},
        {DIK_RETURN, TITLE_MENU_CONFIRM}, {DIK_Z, TITLE_MENU_CONFIRM},
        {DIK_ESCAPE, TITLE_MENU_CANCEL}, {DIK_X, TITLE_MENU_CANCEL},
    };
    for (const Binding& binding : bindings)
        if ((keys[binding.key] & 0x80) != 0 &&
            (g_host.previous_keyboard[binding.key] & 0x80) == 0)
            g_host.menu_input |= binding.flag;
    std::memcpy(g_host.previous_keyboard, keys, sizeof(keys));
}

IDirect3DTexture9* HostTextureForAnmEntry(const AnmFileEntry& entry) {
    for (int index = 0; index < 32; ++index) {
        if (g_host.anm_texture_entry_bases[index] == entry.base)
            return g_host.anm_textures[index];
    }
    AnmTexturePayload payload;
    if (!AnmFile_GetTexture(&entry, &payload))
        return nullptr;
    D3DFORMAT format = payload.format == 1 ? D3DFMT_A8R8G8B8
                       : payload.format == 5 ? D3DFMT_A4R4G4B4
                                             : D3DFMT_UNKNOWN;
    if (format == D3DFMT_UNKNOWN)
        return nullptr;
    IDirect3DTexture9* texture = nullptr;
    unsigned int texture_width =
        entry.width != 0 ? entry.width : payload.width;
    unsigned int texture_height =
        entry.height != 0 ? entry.height : payload.height;
    HRESULT create_result = g_host.device->CreateTexture(
        texture_width, texture_height, 1, 0, format, D3DPOOL_MANAGED,
        &texture, nullptr);
    if (FAILED(create_result)) {
        std::fprintf(stderr,
                     "[th10-recon] texture creation failed: fmt=%u "
                     "%ux%u hr=%08lx\n",
                     payload.format, texture_width, texture_height,
                     static_cast<unsigned long>(create_result));
        std::fflush(stderr);
        return nullptr;
    }
    D3DLOCKED_RECT locked;
    if (FAILED(texture->LockRect(0, &locked, nullptr, 0))) {
        texture->Release();
        return nullptr;
    }
    unsigned int source_pitch =
        payload.height == 0 ? 0 : payload.data_size / payload.height;
    unsigned int bytes_per_pixel = payload.format == 1 ? 4u : 2u;
    unsigned int destination_pitch =
        texture_width * bytes_per_pixel;
    unsigned int rows =
        payload.height < texture_height ? payload.height : texture_height;
    unsigned int copy_pitch =
        source_pitch < destination_pitch ? source_pitch : destination_pitch;
    if (copy_pitch > static_cast<unsigned int>(locked.Pitch))
        copy_pitch = static_cast<unsigned int>(locked.Pitch);
    unsigned int clear_pitch =
        static_cast<unsigned int>(locked.Pitch) < destination_pitch
            ? static_cast<unsigned int>(locked.Pitch) : destination_pitch;
    for (unsigned int row = 0; row < texture_height; ++row)
        std::memset(static_cast<unsigned char*>(locked.pBits) +
                        row * locked.Pitch,
                    0, clear_pitch);
    for (unsigned int row = 0; row < rows; ++row) {
        std::memcpy(static_cast<unsigned char*>(locked.pBits) +
                        row * locked.Pitch,
                    payload.pixels + row * source_pitch, copy_pitch);
    }
    texture->UnlockRect(0);
    for (int index = 0; index < 32; ++index) {
        if (g_host.anm_texture_entry_bases[index] == nullptr) {
            g_host.anm_texture_entry_bases[index] = entry.base;
            g_host.anm_textures[index] = texture;
            return texture;
        }
    }
    texture->Release();
    return nullptr;
}

[[maybe_unused]] void HostDrawAnmVm(const HostAnmVm& runtime) {
    const AnmVmState& vm = runtime.state;
    int resource = runtime.resource_index;
    if (vm.sprite < 0 || resource < 0 || resource >= 3 ||
        g_host.title_resource_bytes[resource] == nullptr)
        return;
    AnmFileEntry entry;
    AnmFileSprite sprite;
    if (!AnmFile_FindGlobalSprite(
            g_host.title_resource_bytes[resource],
            g_host.title_resource_sizes[resource],
            static_cast<unsigned int>(vm.sprite), &entry, &sprite))
        return;
    IDirect3DTexture9* texture = HostTextureForAnmEntry(entry);
    if (texture == nullptr)
        return;

    struct Vertex {
        float x, y, z, rhw;
        unsigned int color;
        float u, v;
    };
    float left = vm.position[0];
    float top = vm.position[1];
    for (const HostAnmVm* parent = runtime.parent;
         parent != nullptr; parent = parent->parent) {
        left += parent->state.position[0];
        top += parent->state.position[1];
    }
    float right = left + sprite.width * vm.scale[0];
    float bottom = top + sprite.height * vm.scale[1];
    float u0 = sprite.x / static_cast<float>(entry.width);
    float v0 = sprite.y / static_cast<float>(entry.height);
    float u1 = (sprite.x + sprite.width) / static_cast<float>(entry.width);
    float v1 = (sprite.y + sprite.height) / static_cast<float>(entry.height);
    unsigned int color = D3DCOLOR_ARGB(
        vm.color[3], vm.color[2], vm.color[1], vm.color[0]);
    Vertex vertices[4] = {
        {left - 0.5f, top - 0.5f, 0.0f, 1.0f, color, u0, v0},
        {right - 0.5f, top - 0.5f, 0.0f, 1.0f, color, u1, v0},
        {left - 0.5f, bottom - 0.5f, 0.0f, 1.0f, color, u0, v1},
        {right - 0.5f, bottom - 0.5f, 0.0f, 1.0f, color, u1, v1},
    };
    g_host.device->SetTexture(0, texture);
    g_host.device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    g_host.device->DrawPrimitiveUP(
        D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex));
    g_host.title_draw_calls += 1;
}

void HostDrawAnmVmSoftware(const HostAnmVm& runtime,
                           unsigned int* frame) {
    const AnmVmState& vm = runtime.state;
    int resource = runtime.resource_index;
    const unsigned char* resource_bytes = runtime.resource_bytes;
    unsigned int resource_size = runtime.resource_size;
    if (resource_bytes == nullptr && resource >= 0 && resource < 3) {
        resource_bytes = g_host.title_resource_bytes[resource];
        resource_size = g_host.title_resource_sizes[resource];
    }
    if (vm.sprite < 0 || resource_bytes == nullptr)
        return;
    AnmFileEntry entry;
    AnmFileSprite sprite;
    AnmTexturePayload payload;
    if (!AnmFile_FindGlobalSprite(
            resource_bytes, resource_size,
            static_cast<unsigned int>(vm.sprite), &entry, &sprite) ||
        !AnmFile_GetTexture(&entry, &payload))
        return;

    float origin_x = vm.position[0];
    float origin_y = vm.position[1];
    for (const HostAnmVm* parent = runtime.parent;
         parent != nullptr; parent = parent->parent) {
        origin_x += parent->state.position[0];
        origin_y += parent->state.position[1];
    }
    int width = static_cast<int>(sprite.width * vm.scale[0]);
    int height = static_cast<int>(sprite.height * vm.scale[1]);
    if (width <= 0 || height <= 0)
        return;
    int left = static_cast<int>(origin_x);
    int top = static_cast<int>(origin_y);
    int source_left = static_cast<int>(sprite.x);
    int source_top = static_cast<int>(sprite.y);
    int source_width = static_cast<int>(sprite.width);
    int source_height = static_cast<int>(sprite.height);
    unsigned int bytes_per_pixel = payload.format == 1 ? 4u :
                                   payload.format == 5 ? 2u : 0u;
    if (bytes_per_pixel == 0 || payload.height == 0)
        return;
    unsigned int source_pitch = payload.data_size / payload.height;

    for (int y = 0; y < height; ++y) {
        int destination_y = top + y;
        if (destination_y < 0 || destination_y >= 480)
            continue;
        int source_y = source_top + y * source_height / height;
        if (source_y < 0 || source_y >= payload.height)
            continue;
        for (int x = 0; x < width; ++x) {
            int destination_x = left + x;
            if (destination_x < 0 || destination_x >= 640)
                continue;
            int source_x = source_left + x * source_width / width;
            if (source_x < 0)
                continue;
            source_x %= payload.width;
            const unsigned char* pixel =
                payload.pixels + source_y * source_pitch +
                source_x * bytes_per_pixel;
            unsigned int blue, green, red, alpha;
            if (payload.format == 1) {
                blue = pixel[0];
                green = pixel[1];
                red = pixel[2];
                alpha = pixel[3];
            } else {
                unsigned int packed =
                    static_cast<unsigned int>(pixel[0]) |
                    (static_cast<unsigned int>(pixel[1]) << 8);
                blue = (packed & 0xF) * 17;
                green = ((packed >> 4) & 0xF) * 17;
                red = ((packed >> 8) & 0xF) * 17;
                alpha = ((packed >> 12) & 0xF) * 17;
            }
            blue = blue * vm.color[0] / 255;
            green = green * vm.color[1] / 255;
            red = red * vm.color[2] / 255;
            alpha = alpha * vm.color[3] / 255;
            unsigned int& destination =
                frame[destination_y * 640 + destination_x];
            unsigned int inverse = 255 - alpha;
            unsigned int destination_blue = destination & 0xFF;
            unsigned int destination_green = (destination >> 8) & 0xFF;
            unsigned int destination_red = (destination >> 16) & 0xFF;
            destination_blue =
                (blue * alpha + destination_blue * inverse + 127) / 255;
            destination_green =
                (green * alpha + destination_green * inverse + 127) / 255;
            destination_red =
                (red * alpha + destination_red * inverse + 127) / 255;
            destination = destination_blue |
                          (destination_green << 8) |
                          (destination_red << 16);
        }
    }
    g_host.title_draw_calls += 1;
}

void HostDrawAnmVmSoftwareAt(const HostAnmVm& source,
                             unsigned int* frame, float x, float y,
                             float scale_x, float scale_y) {
    HostAnmVm placed = source;
    placed.parent = nullptr;
    placed.state.position[0] = x;
    placed.state.position[1] = y;
    placed.state.scale[0] = scale_x;
    placed.state.scale[1] = scale_y;
    HostDrawAnmVmSoftware(placed, frame);
}

bool HostEnsureStageVms() {
    if (g_host.stage_vms_ready)
        return true;
    const HostStageRuntimeView& runtime = HostStage_GetRuntimeView();
    if (runtime.std_view == nullptr ||
        runtime.companion_anm_data == nullptr) {
        HostTrace("Stage 1 VM init missing runtime resources");
        return false;
    }
    g_host.stage_vm_count = 0;
    for (uint16_t object_index = 0;
         object_index < runtime.std_view->count_00; ++object_index) {
        StageStdObjectView object = {};
        if (!StageStd_GetObject(
                runtime.std_view, object_index, &object)) {
            HostTrace("Stage 1 VM init rejected an STD object");
            return false;
        }
        for (uint16_t subrecord_index = 0;; ++subrecord_index) {
            StageStdSubrecordView subrecord = {};
            if (!StageStd_GetSubrecord(
                    &object, subrecord_index, &subrecord))
                break;
            if (g_host.stage_vm_count >= 32) {
                HostTrace("Stage 1 VM set exceeds host capacity");
                return false;
            }
            AnmFileScript script = {};
            if (!AnmFile_FindGlobalScript(
                    runtime.companion_anm_data,
                    runtime.companion_anm_size, subrecord.field_04,
                    nullptr, &script)) {
                std::fprintf(
                    stderr,
                    "[th10-recon] Stage 1 ANM script %u missing\n",
                    subrecord.field_04);
                return false;
            }
            const int slot = g_host.stage_vm_count++;
            HostAnmVm* vm = &g_host.stage_vms[slot];
            HostInitializeAnmVm(vm, script.instructions);
            vm->script_id = subrecord.field_04;
            vm->resource_index = -1;
            vm->resource_bytes = runtime.companion_anm_data;
            vm->resource_size = runtime.companion_anm_size;
            g_host.stage_subrecords[slot] = subrecord;
            g_host.stage_vm_object_indices[slot] = object_index;
            AnmVmHooks hooks = HostAnmHooks(vm);
            AnmVm_Tick(&vm->state, &hooks);
        }
    }
    g_host.stage_vms_ready =
        g_host.stage_vm_count ==
        static_cast<int>(runtime.std_view->count_02);
    if (g_host.stage_vms_ready)
        HostTrace("Stage 1 ANM VM set initialized from stage01.std");
    else
        std::fprintf(stderr,
                     "[th10-recon] Stage 1 VM count mismatch: %d/%u\n",
                     g_host.stage_vm_count, runtime.std_view->count_02);
    return g_host.stage_vms_ready;
}

bool HostEnsurePlayerVm() {
    if (g_host.player_vm_ready)
        return true;
    if (g_host.player_vm_attempted)
        return false;
    g_host.player_vm_attempted = 1;
    const char* name =
        g_host.character_selection == 0 ? "pl00.anm" : "pl01.anm";
    char candidate0[64], candidate1[64];
    std::snprintf(candidate0, sizeof(candidate0), "th10/%s", name);
    std::snprintf(candidate1, sizeof(candidate1), "th10/player/%s", name);
    const char* path = candidate0;
    unsigned int size = Resource_GetFileSize(path);
    if (size == 0) {
        path = candidate1;
        size = Resource_GetFileSize(path);
    }
    if (size == 0) {
        std::fprintf(stderr, "[th10-recon] player ANM missing: %s\n", path);
        return false;
    }
    unsigned char* bytes =
        static_cast<unsigned char*>(std::malloc(size));
    if (bytes == nullptr || Resource_LoadFile(path, bytes) == nullptr) {
        std::fprintf(stderr, "[th10-recon] player ANM load failed: %s\n", path);
        std::free(bytes);
        return false;
    }
    g_host.player_anm_bytes = bytes;
    g_host.player_anm_size = size;
    AnmFileScript script = {};
    if (!AnmFile_FindGlobalScript(bytes, size, 0, nullptr, &script))
        return false;
    HostInitializeAnmVm(&g_host.player_vm, script.instructions);
    g_host.player_vm.script_id = 0;
    g_host.player_vm.resource_index = -1;
    g_host.player_vm.resource_bytes = bytes;
    g_host.player_vm.resource_size = size;
    AnmVmHooks hooks = HostAnmHooks(&g_host.player_vm);
    AnmVm_Tick(&g_host.player_vm.state, &hooks);
    g_host.player_vm_ready = g_host.player_vm.state.sprite >= 0;
    if (g_host.player_vm_ready)
        std::fprintf(stderr,
                     "[th10-recon] selected player ANM VM initialized "
                     "(script %d sprite %d)\n",
                     g_host.player_vm.script_id,
                     g_host.player_vm.state.sprite);
    else
        std::fprintf(stderr,
                     "[th10-recon] no visible player script found in %s "
                     "(%u bytes)\n", path, size);
    return g_host.player_vm_ready;
}

bool HostProjectStagePoint(const float world[3], float* screen_x,
                           float* screen_y, float* scale) {
    const HostStageRuntimeView& runtime = HostStage_GetRuntimeView();
    if (runtime.camera == nullptr)
        return false;
    const HostStageCameraView& camera = *runtime.camera;
    float forward[3] = {
        camera.target[0] - camera.eye[0],
        camera.target[1] - camera.eye[1],
        camera.target[2] - camera.eye[2],
    };
    float forward_length = std::sqrt(
        forward[0] * forward[0] + forward[1] * forward[1] +
        forward[2] * forward[2]);
    if (forward_length <= 0.0001f)
        return false;
    for (float& component : forward) component /= forward_length;
    float right[3] = {
        forward[1] * camera.up[2] - forward[2] * camera.up[1],
        forward[2] * camera.up[0] - forward[0] * camera.up[2],
        forward[0] * camera.up[1] - forward[1] * camera.up[0],
    };
    float right_length = std::sqrt(
        right[0] * right[0] + right[1] * right[1] +
        right[2] * right[2]);
    if (right_length <= 0.0001f)
        return false;
    for (float& component : right) component /= right_length;
    float up[3] = {
        right[1] * forward[2] - right[2] * forward[1],
        right[2] * forward[0] - right[0] * forward[2],
        right[0] * forward[1] - right[1] * forward[0],
    };
    float delta[3] = {
        world[0] - camera.eye[0],
        world[1] - camera.eye[1],
        world[2] - camera.eye[2],
    };
    float camera_x =
        delta[0] * right[0] + delta[1] * right[1] +
        delta[2] * right[2];
    float camera_y =
        delta[0] * up[0] + delta[1] * up[1] + delta[2] * up[2];
    float camera_z =
        delta[0] * forward[0] + delta[1] * forward[1] +
        delta[2] * forward[2];
    if (camera_z <= 1.0f)
        return false;
    const float focal =
        224.0f / std::tan(camera.field_of_view * 0.5f);
    *scale = focal / camera_z;
    *screen_x = 224.0f + camera_x * *scale;
    *screen_y = 240.0f - camera_y * *scale;
    return true;
}

void HostRenderStage(unsigned int* frame) {
    if (!HostEnsureStageVms())
        return;
    const HostStageRuntimeView& runtime = HostStage_GetRuntimeView();
    for (int placement_index = 0;; ++placement_index) {
        StageStdPlacementView placement = {};
        if (!StageStd_GetPlacement(
                runtime.std_view,
                static_cast<uint16_t>(placement_index), &placement))
            break;
        StageStdObjectView object = {};
        if (!StageStd_GetObject(
                runtime.std_view,
                static_cast<uint16_t>(placement.object_index), &object))
            continue;
        for (int slot = 0; slot < g_host.stage_vm_count; ++slot) {
            if (g_host.stage_vm_object_indices[slot] !=
                    placement.object_index ||
                g_host.stage_subrecords[slot].kind != 0)
                continue;
            const StageStdSubrecordView& subrecord =
                g_host.stage_subrecords[slot];
            float world[3];
            for (int axis = 0; axis < 3; ++axis)
                world[axis] = placement.position[axis] +
                              object.position[axis] +
                              subrecord.position[axis];
            float x = 0.0f, y = 0.0f, projection_scale = 0.0f;
            if (!HostProjectStagePoint(
                    world, &x, &y, &projection_scale))
                continue;
            AnmFileEntry entry = {};
            AnmFileSprite sprite = {};
            const HostAnmVm& vm = g_host.stage_vms[slot];
            if (vm.state.sprite < 0 ||
                !AnmFile_FindGlobalSprite(
                    vm.resource_bytes, vm.resource_size,
                    static_cast<unsigned int>(vm.state.sprite),
                    &entry, &sprite))
                continue;
            float width = subrecord.size[0] * projection_scale;
            float height = subrecord.size[1] * projection_scale;
            HostDrawAnmVmSoftwareAt(
                vm, frame, x - width * 0.5f, y - height * 0.5f,
                width / sprite.width, height / sprite.height);
        }
    }
    if (HostEnsurePlayerVm() && g_host.player_vm.state.sprite >= 0) {
        AnmFileEntry entry = {};
        AnmFileSprite sprite = {};
        if (AnmFile_FindGlobalSprite(
                g_host.player_vm.resource_bytes,
                g_host.player_vm.resource_size,
                static_cast<unsigned int>(g_host.player_vm.state.sprite),
                &entry, &sprite))
            HostDrawAnmVmSoftwareAt(
                g_host.player_vm, frame,
                g_host.player_x - sprite.width * 0.5f,
                g_host.player_y - sprite.height * 0.5f, 1.0f, 1.0f);
    }
    for (int y = 0; y < 480; ++y)
        for (int x = 0; x < 640; ++x)
            if (x < 32 || x >= 416 || y < 16 || y >= 464)
                frame[y * 640 + x] = 0;
}

void HostRenderMenu() {
    if (g_host.smoke_mode || g_host.device == nullptr ||
        g_host.window == nullptr)
        return;
    static bool trace_render = true;
    static unsigned int frame[640 * 480];
    for (unsigned int& pixel : frame)
        pixel = 0x000C1424u;
    if (HostStage_IsActive()) {
        HostRenderStage(frame);
    } else {
    const HostAnmVm* draw_list[67] = {};
    int draw_count = 0;
    draw_list[draw_count++] = &g_host.title_vms[0];
    draw_list[draw_count++] = &g_host.title_vms[1];
    for (int index = 0; index < g_host.title_child_vm_count; ++index)
        if (g_host.title_child_vms[index].active)
            draw_list[draw_count++] = &g_host.title_child_vms[index];
    if (g_host.title_flow != 0 && g_host.title_version_vm_ready)
        draw_list[draw_count++] = &g_host.title_version_vm;
    for (int index = 1; index < draw_count; ++index) {
        const HostAnmVm* item = draw_list[index];
        int insertion = index;
        while (insertion > 0 &&
               draw_list[insertion - 1]->state.layer >
                   item->state.layer) {
            draw_list[insertion] = draw_list[insertion - 1];
            --insertion;
        }
        draw_list[insertion] = item;
    }
    for (int index = 0; index < draw_count; ++index)
        HostDrawAnmVmSoftware(*draw_list[index], frame);
    }
    BITMAPINFO bitmap = {};
    bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth = 640;
    bitmap.bmiHeader.biHeight = -480;
    bitmap.bmiHeader.biPlanes = 1;
    bitmap.bmiHeader.biBitCount = 32;
    bitmap.bmiHeader.biCompression = BI_RGB;
    HDC dc = GetDC(g_host.window);
    int presented = SetDIBitsToDevice(
        dc, 0, 0, 640, 480, 0, 0, 0, 480, frame, &bitmap,
        DIB_RGB_COLORS);
    ReleaseDC(g_host.window, dc);
    if (trace_render) {
        HostTrace(presented != 0 ? "software title renderer presenting" :
                                  "software title renderer failed");
        trace_render = false;
    }
}

void HostDispatchTitleMenuAction(TitleMenuAction action) {
    switch (action) {
    case TITLE_MENU_ACTION_START:
        HostStartDifficultySelection();
        return;
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
        g_host.menu_screen = 4;
        TitleOptions_Initialize(&g_host.options_state);
        HostStartTitleScripts(88, 1);
        HostBroadcastTitleInterrupt(17);
        g_host.menu_status =
            "Options: arrows adjust, Enter selects, Esc returns";
        return;
    case TITLE_MENU_ACTION_QUIT:
        g_host.menu_quit = 1;
        return;
    case TITLE_MENU_ACTION_NONE:
        return;
    }
    TitleMainMenu_Initialize(&g_host.menu_state);
}

void HostDispatchOptionsAction(TitleOptionsAction action) {
    if (action == TITLE_OPTIONS_ACTION_VALUE_CHANGED ||
        action == TITLE_OPTIONS_ACTION_DEFAULTS) {
        g_host.config.bgm_mode =
            static_cast<unsigned char>(g_host.options_config.bgm_mode);
        HostApplyAudioVolumes();
        HostRefreshOptionsSprites();
        HostRefreshBgmModeVisual();
        return;
    }
    if (action == TITLE_OPTIONS_ACTION_KEY_CONFIG) {
        // Retail dispatcher state 5 is the key-configuration handler
        // (0x0042F540), whose reconstruction is the next child state.
        g_host.menu_screen = 5;
        HostStartTitleScripts(88, 2);
        g_host.menu_status =
            "Key configuration state entered; Esc returns to Options";
        return;
    }
    if (action == TITLE_OPTIONS_ACTION_RETURN) {
        HostReturnToMainMenu();
    }
}

void HostUpdateSelectionScreen() {
    if (++g_host.selection_phase_frame <= 10) {
        g_host.menu_input = 0;
        return;
    }
    bool cancel = (g_host.menu_input & TITLE_MENU_CANCEL) != 0;
    bool confirm = (g_host.menu_input & TITLE_MENU_CONFIRM) != 0;
    int direction = 0;
    if ((g_host.menu_input &
         (TITLE_MENU_UP | TITLE_OPTIONS_LEFT)) != 0)
        direction = -1;
    if ((g_host.menu_input &
         (TITLE_MENU_DOWN | TITLE_OPTIONS_RIGHT)) != 0)
        direction = 1;

    if (g_host.menu_screen == 6) {
        if (cancel) {
            HostPlayMenuSound(2);
            HostReturnToMainMenu();
        } else if (confirm) {
            HostPlayMenuSound(1);
            HostStartCharacterSelection();
        } else if (direction != 0) {
            int old = g_host.difficulty_selection;
            g_host.difficulty_selection =
                (g_host.difficulty_selection + direction + 4) % 4;
            HostSetOverlayChildInterrupt(109 + old, 27);
            HostSetOverlayChildInterrupt(
                109 + g_host.difficulty_selection,
                17 + g_host.difficulty_selection);
            HostPlayMenuSound(0);
        }
    } else if (g_host.menu_screen == 7) {
        if (cancel) {
            HostPlayMenuSound(2);
            HostStartDifficultySelection();
        } else if (confirm) {
            HostPlayMenuSound(1);
            HostStartWeaponSelection();
        } else if (direction != 0) {
            int old = g_host.character_selection;
            g_host.character_selection =
                (g_host.character_selection + direction + 2) % 2;
            HostSetOverlayChildInterrupt(121 + old, 3);
            HostSetOverlayChildInterrupt(123 + old, 3);
            HostSetOverlayChildInterrupt(
                121 + g_host.character_selection,
                7 + g_host.character_selection);
            HostSetOverlayChildInterrupt(
                123 + g_host.character_selection,
                7 + g_host.character_selection);
            HostPlayMenuSound(0);
        }
    } else if (g_host.menu_screen == 8) {
        int base = g_host.character_selection == 0 ? 126 : 129;
        int description_base =
            144 + g_host.character_selection * 3;
        if (cancel) {
            HostPlayMenuSound(2);
            HostStartCharacterSelection();
        } else if (confirm) {
            HostPlayMenuSound(1);
            int result = HostStage_ConfirmWeapon(
                g_host.character_selection, g_host.weapon_selection,
                g_host.difficulty_selection);
            if (result == 0) {
                g_host.stage_vms_ready = 0;
                g_host.stage_vm_count = 0;
                g_host.player_vm_ready = 0;
                g_host.player_vm_attempted = 0;
                g_host.player_x = 224.0f;
                g_host.player_y = 400.0f;
            }
            g_host.menu_status = result == 0
                ? "Stage 1 resources loaded; gameplay scheduler active"
                : "Stage 1 bridge failed";
        } else if (direction != 0) {
            int old = g_host.weapon_selection;
            g_host.weapon_selection =
                (g_host.weapon_selection + direction + 3) % 3;
            HostSetOverlayChildInterrupt(base + old, 27);
            HostSetOverlayChildInterrupt(description_base + old, 27);
            HostSetOverlayChildInterrupt(
                base + g_host.weapon_selection,
                17 + g_host.weapon_selection);
            HostSetOverlayChildInterrupt(
                description_base + g_host.weapon_selection,
                17 + g_host.weapon_selection);
            HostPlayMenuSound(0);
        }
    }
    g_host.menu_input = 0;
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
    if (g_host.smoke_mode) {
        g_host.fake_clock_ms += 17.0;
        return g_host.fake_clock_ms;
    }
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
#if defined(_WIN32)
    static bool traced_first_frame = false;
    if (!traced_first_frame) {
        HostTrace("first reconstructed scheduler frame");
        traced_first_frame = true;
    }
#endif
    // All twenty GameStateInit callbacks plus the four main-task callbacks
    // execute here. Once the title task has been registered, each frame
    // counts toward the title-visible milestone.
    if (g_host.title_task_registered)
        g_host.title_frames_completed += 1;
    if (g_host.smoke_mode && g_host.title_frames_completed == 60 &&
        HostStage_GetReport().archive_available &&
        !HostStage_GetReport().confirm_invoked) {
        HostStage_ConfirmWeapon(0, 0, 1);
        HostStage_RunFrames(120);
#if defined(_WIN32)
        HostEnsureStageVms();
        HostEnsurePlayerVm();
#endif
    }
#if defined(_WIN32)
    if (!g_host.smoke_mode && g_host.title_frames_completed == 60) {
        std::fprintf(
            stderr,
            "[th10-recon] title entry complete: background alpha=%u, "
            "child VMs=%d\n",
            g_host.title_vms[0].state.color[3],
            g_host.title_child_vm_count);
        std::fflush(stderr);
    }
    if (!g_host.smoke_mode)
        HostPollKeyboard();
    if (!g_host.smoke_mode && HostStage_IsActive()) {
        HostStage_RunFrames(1);
        if (HostEnsureStageVms()) {
            for (int index = 0; index < g_host.stage_vm_count; ++index) {
                HostAnmVm* vm = &g_host.stage_vms[index];
                if (!vm->active)
                    continue;
                AnmVmHooks hooks = HostAnmHooks(vm);
                if (AnmVm_Tick(&vm->state, &hooks) != 0)
                    vm->active = 0;
            }
        }
        if (HostEnsurePlayerVm() && g_host.player_vm.active) {
            AnmVmHooks hooks = HostAnmHooks(&g_host.player_vm);
            if (AnmVm_Tick(&g_host.player_vm.state, &hooks) != 0)
                g_host.player_vm.active = 0;
        }
    }
    if (g_host.title_vm_ready) {
        for (int index = 0; index < 2; ++index) {
            AnmVmHooks hooks = HostAnmHooks(&g_host.title_vms[index]);
            AnmVm_Tick(&g_host.title_vms[index].state, &hooks);
        }
        for (int index = 0; index < g_host.title_child_vm_count; ++index) {
            HostAnmVm* child = &g_host.title_child_vms[index];
            if (!child->active)
                continue;
            AnmVmHooks hooks = HostAnmHooks(child);
            if (AnmVm_Tick(&child->state, &hooks) != 0)
                child->active = 0;
        }
        if (g_host.menu_screen == 4)
            HostRefreshOptionsSprites();
        else if (g_host.menu_screen == 7)
            HostRefreshCharacterVisual();
    }
    if (g_host.title_flow != 0 && g_host.title_version_vm_ready) {
        AnmVmHooks hooks = HostAnmHooks(&g_host.title_version_vm);
        AnmVm_Tick(&g_host.title_version_vm.state, &hooks);
    }
    if (g_host.title_flow == 0) {
        g_host.title_flow_frame += 1;
        int sig_frames = g_host.smoke_mode ? 1 : 90;
        if (g_host.title_flow_frame >= sig_frames) {
            HostStartTitleScripts(88, 90);
            if (!g_host.smoke_mode)
                HostTrace(HostStartTitleBgm() ? "title BGM playing" :
                                                "title BGM unavailable");
            if (!g_host.smoke_mode)
                HostTrace("entered Press Any Button title phase");
            g_host.title_flow = 1;
            g_host.title_flow_frame = 0;
            g_host.menu_input = 0;
        }
    } else if (g_host.title_flow == 1) {
        g_host.title_flow_frame += 1;
        bool pressed = g_host.menu_input != 0 ||
                       (g_host.smoke_mode &&
                        g_host.title_flow_frame >= 1);
        if (g_host.title_transition_frame == 0 && pressed) {
            HostBroadcastTitleInterrupt(6);
            if (!g_host.smoke_mode)
                HostPlayMenuSound(1);
            g_host.title_transition_frame = 1;
        } else if (g_host.title_transition_frame > 0) {
            g_host.title_transition_frame += 1;
            if (g_host.title_transition_frame >= 30) {
                HostSwitchTitleOverlay(0);
                HostPrimeMainMenuOverlay();
                TitleMainMenu_Initialize(&g_host.menu_state);
                g_host.title_flow = 2;
                g_host.title_flow_frame = 0;
                g_host.title_transition_frame = 0;
                if (!g_host.smoke_mode)
                    HostTrace("entered interactive main-menu phase");
            }
        }
        g_host.menu_input = 0;
    } else if (!g_host.smoke_mode && g_host.menu_screen == 0) {
        int old_selection = g_host.menu_state.selection;
        int old_phase = g_host.menu_state.phase;
        TitleMenuAction action =
            TitleMainMenu_Update(&g_host.menu_state, g_host.menu_input);
        if (old_selection != g_host.menu_state.selection &&
            g_host.menu_state.phase == 2 &&
            g_host.title_vm_ready) {
            int interrupt = g_host.menu_state.selection + 7;
            HostBroadcastTitleInterrupt(interrupt);
            HostPlayMenuSound(0);
        }
        if (old_phase == 1 && g_host.menu_state.phase == 2)
            HostBroadcastTitleInterrupt(
                g_host.menu_state.selection + 17);
        if (old_phase == 2 && g_host.menu_state.phase == 4)
            HostPlayMenuSound(
                (g_host.menu_input & TITLE_MENU_CANCEL) != 0 ? 2 : 1);
        g_host.menu_input = 0;
        HostDispatchTitleMenuAction(action);
    } else if (!g_host.smoke_mode && g_host.menu_screen == 4) {
        int old_selection = g_host.options_state.selection;
        int old_phase = g_host.options_state.phase;
        TitleOptionsAction action = TitleOptions_Update(
            &g_host.options_state, &g_host.options_config,
            g_host.menu_input);
        if (old_selection != g_host.options_state.selection &&
            g_host.options_state.phase == 2) {
            HostBroadcastTitleInterrupt(
                g_host.options_state.selection + 7);
            HostPlayMenuSound(0);
        }
        if (old_phase == 1 && g_host.options_state.phase == 2)
            HostBroadcastTitleInterrupt(
                g_host.options_state.selection + 17);
        if (old_phase == 2 && g_host.options_state.phase == 4)
            HostPlayMenuSound(
                (g_host.menu_input & TITLE_OPTIONS_CANCEL) != 0 ? 2 : 1);
        g_host.menu_input = 0;
        HostDispatchOptionsAction(action);
    } else if (!g_host.smoke_mode && g_host.menu_screen == 5) {
        if ((g_host.menu_input & TITLE_OPTIONS_CANCEL) != 0) {
            g_host.menu_screen = 4;
            TitleOptions_Initialize(&g_host.options_state);
            HostStartTitleScripts(88, 1);
            HostBroadcastTitleInterrupt(17);
        }
        g_host.menu_input = 0;
    } else if (!g_host.smoke_mode && g_host.menu_screen >= 6 &&
               g_host.menu_screen <= 8) {
        HostUpdateSelectionScreen();
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
    if (g_host.smoke_mode)
        return 0;
    HostTrace("creating Win32 window");
    HINSTANCE instance = GetModuleHandleA(nullptr);
    WNDCLASSA window_class = {};
    window_class.lpfnWndProc = HostWindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName = "TH10ReconstructedWindow";
    if (RegisterClassA(&window_class) == 0 &&
        GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return -1;
    RECT window_rect = {0, 0, 640, 480};
    AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, FALSE);
    g_host.window = CreateWindowA(
        window_class.lpszClassName, "TH10 reconstructed startup",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        window_rect.right - window_rect.left,
        window_rect.bottom - window_rect.top,
        nullptr, nullptr, instance, nullptr);
    if (g_host.window != nullptr && !g_host.smoke_mode) {
        g_host.menu_windowed = g_host.config.windowed != 0;
        ShowWindow(g_host.window, SW_SHOW);
        UpdateWindow(g_host.window);
    }
    HostTrace(g_host.window == nullptr ? "window creation failed" :
                                        "window created");
    return g_host.window == nullptr ? -1 : 0;
#else
    return 0;
#endif
}
int HostCreateInput(void*) {
#if defined(_WIN32)
    if (g_host.smoke_mode)
        return 0;
    HostTrace("creating DirectInput keyboard");
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
    HostTrace("DirectInput keyboard ready");
#endif
    return 0;
}
int HostConfirmDialog(void*) { return 6; } // IDYES
void HostChecksum(void*) {}
void* HostCreateScheduler(void*) { return &g_host; }
void* HostCreateD3d(void*) {
#if defined(_WIN32)
    if (g_host.smoke_mode)
        return &g_host;
    HostTrace("creating Direct3D9 interface");
    g_host.direct3d = Direct3DCreate9(D3D_SDK_VERSION);
    HostTrace(g_host.direct3d == nullptr ? "Direct3D9 interface failed" :
                                          "Direct3D9 interface ready");
    return g_host.direct3d;
#else
    return &g_host;
#endif
}
int HostCreateDevice(void*) {
#if defined(_WIN32)
    if (g_host.smoke_mode)
        return 0;
    HostTrace("creating Direct3D9 HAL device");
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
    HostTrace(FAILED(result) ? "Direct3D9 HAL device failed" :
                               "Direct3D9 HAL device ready");
    return FAILED(result) ? -1 : 0;
#else
    return 0;
#endif
}
void* HostSpawnSoundWorker(void*) {
#if defined(_WIN32)
    if (!g_host.smoke_mode) {
        HostTrace("creating DirectSound device");
        if (FAILED(DirectSoundCreate8(
                nullptr, &g_host.direct_sound, nullptr)))
            return nullptr;
        if (FAILED(g_host.direct_sound->SetCooperativeLevel(
                g_host.window, DSSCL_NORMAL)))
            return nullptr;
        g_host.menu_sound_buffers[0] =
            HostLoadArchiveWave("se_select00.wav");
        g_host.menu_sound_buffers[1] =
            HostLoadArchiveWave("se_ok00.wav");
        g_host.menu_sound_buffers[2] =
            HostLoadArchiveWave("se_cancel00.wav");
    }
    if (!g_host.smoke_mode)
        HostTrace("DirectSound device ready");
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
    void* result = GameStateInit_Construct(
        arena, 0x732460u, &hooks, &plan, &g_host.game_state_matrices);
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

#if defined(_WIN32)
bool HostLoadSigResource() {
    unsigned int size = Resource_GetFileSize("th10/sig.anm");
    if (size == 0)
        return false;
    unsigned char* bytes =
        static_cast<unsigned char*>(std::malloc(size));
    if (bytes == nullptr ||
        Resource_LoadFile("th10/sig.anm", bytes) == nullptr) {
        std::free(bytes);
        return false;
    }
    AnmFileEntry entry;
    if (!AnmFile_ParseEntry(bytes, size, 0, &entry)) {
        std::free(bytes);
        return false;
    }
    g_host.title_resource_bytes[2] = bytes;
    g_host.title_resource_sizes[2] = size;
    g_host.title_entries[2] = entry;
    if (g_host.dump_anm) {
        std::FILE* dump = std::fopen("sig.anm", "wb");
        if (dump != nullptr) {
            std::fwrite(bytes, 1, size, dump);
            std::fclose(dump);
        }
    }
    return true;
}
#endif

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
    g_host.title_resource_sizes[index] = size;
    g_host.title_resources_from_archive = 1;
    if (AnmFile_ParseEntry(bytes, size, 0, &g_host.title_entries[index])) {
        if (index == 0) {
            AnmFileScript main_script;
            AnmFileScript press_script;
            AnmFileScript menu_script;
            g_host.title_anm_parsed =
                AnmFile_FindGlobalScript(bytes, size, 88, nullptr,
                                         &main_script) &&
                AnmFile_FindGlobalScript(bytes, size, 90, nullptr,
                                         &press_script) &&
                AnmFile_FindGlobalScript(bytes, size, 0, nullptr,
                                         &menu_script);
        } else {
            AnmFileScript version_script;
            if (AnmFile_FindGlobalScript(
                    bytes, size, 0, nullptr, &version_script)) {
                HostInitializeAnmVm(&g_host.title_version_vm,
                                    version_script.instructions);
                g_host.title_version_vm.resource_index = 1;
                g_host.title_version_vm_ready = 1;
            }
        }
    }
    if (g_host.dump_anm) {
        std::FILE* dump = std::fopen(name, "wb");
        if (dump != nullptr) {
            std::fwrite(bytes, 1, size, dump);
            std::fclose(dump);
        }
    }
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
    g_host.title_flow = 0;
    g_host.title_flow_frame = 0;
#if defined(_WIN32)
    if (!HostLoadSigResource() || !HostStartSigScript())
        return -1;
    if (!g_host.smoke_mode)
        HostTrace("entered sig.anm loading phase");
#endif
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
    if (g_host.smoke_mode) {
        // The deterministic smoke path deliberately owns no D3D device.
        // Device_ApplyDefaultState performs 51 retail-derived state writes;
        // record their successful logical application without entering Wine's
        // graphics stack.
        g_render_state_writes = 51;
        g_host.device_defaults_applied = 1;
        return;
    }
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
    if (g_host.bgm_buffer != nullptr) {
        g_host.bgm_buffer->Stop();
        g_host.bgm_buffer->Release();
        g_host.bgm_buffer = nullptr;
    }
    for (int index = 0; index < 3; ++index) {
        if (g_host.menu_sound_buffers[index] != nullptr) {
            g_host.menu_sound_buffers[index]->Release();
            g_host.menu_sound_buffers[index] = nullptr;
        }
    }
    if (g_host.direct_sound != nullptr) {
        g_host.direct_sound->Release();
        g_host.direct_sound = nullptr;
    }
#endif
}
void HostDestroyGameState(void*, void* manager) {
#if defined(_WIN32)
    for (int index = 0; index < 3; ++index) {
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
        for (int index = 0; index < 32; ++index) {
            if (g_host.anm_textures[index] != nullptr) {
                g_host.anm_textures[index]->Release();
                g_host.anm_textures[index] = nullptr;
                g_host.anm_texture_entry_bases[index] = nullptr;
            }
        }
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
    HostTrace("process entry");
    g_host.smoke_mode = argc > 1 &&
        (std::strcmp(argv[1], "--smoke") == 0 ||
         std::strcmp(argv[1], "--dump-anm") == 0 ||
         std::strcmp(argv[1], "--dump-stage") == 0);
    g_host.dump_anm =
        argc > 1 && std::strcmp(argv[1], "--dump-anm") == 0;
    g_host.dump_stage =
        argc > 1 && std::strcmp(argv[1], "--dump-stage") == 0;
#else
    (void)argc;
    (void)argv;
    g_host.smoke_mode = 1;
#endif
    const int archive_available =
        Resource_RegisterArchive("th10.dat") ? 1 : 0;
    HostStage_SetArchiveAvailable(archive_available);
#if defined(_WIN32)
    if (!archive_available) {
        std::fprintf(stderr, "failed to mount th10.dat\n");
        return 1;
    }
    HostTrace("th10.dat mounted");
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
    std::printf("  retail title ANM layout: %s\n",
                g_host.title_anm_parsed ? "scripts 88/0 ready" :
                                          "not parsed");
    std::printf("  retail title VM sprites: %d / %d\n",
                g_host.title_vms[0].state.sprite,
                g_host.title_vms[1].state.sprite);
    std::printf("  retail title child VMs spawned: %d\n",
                g_host.title_child_vm_count);
    std::printf("  retail title sprite draws: %d\n",
                g_host.title_draw_calls);
    std::printf("  title frames completed: %d\n",
                g_host.title_frames_completed);
    std::printf("  ordered title flow reached: %s\n",
                g_host.title_flow == 2 ? "main menu" : "incomplete");
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
             g_host.title_anm_parsed &&
             g_host.title_child_vm_count >= 3 &&
             g_host.title_flow == 2 &&
             g_host.title_frames_completed >= 60 &&
             g_host.clean_shutdown &&
             exit_code == 0;
#if defined(_WIN32)
    if (g_host.dump_stage && HostStage_IsActive()) {
        static unsigned int stage_frame[640 * 480] = {};
        HostRenderStage(stage_frame);
        std::FILE* output = std::fopen("stage1.ppm", "wb");
        if (output != nullptr) {
            std::fprintf(output, "P6\n640 480\n255\n");
            for (unsigned int pixel : stage_frame) {
                const unsigned char rgb[3] = {
                    static_cast<unsigned char>((pixel >> 16) & 0xFF),
                    static_cast<unsigned char>((pixel >> 8) & 0xFF),
                    static_cast<unsigned char>(pixel & 0xFF),
                };
                std::fwrite(rgb, 1, sizeof(rgb), output);
            }
            std::fclose(output);
            HostTrace("wrote stage1.ppm");
        }
    }
#endif
    std::printf("SMOKE_%s\n", ok ? "PASS" : "FAIL");
    const HostStageReport& stage = HostStage_GetReport();
    const int stage_ok =
        archive_available && stage.mode_apply_result == 1 &&
        stage.leave_gameplay_fired && stage.enter_result == 0 &&
        stage.update_task_registered && stage.draw_task_registered &&
        stage.std_raw_view_valid && stage.std_geometry_valid &&
        stage.timeline_initialized &&
        stage.timeline_decoded > 0 && stage.timeline_rejected == 0 &&
        stage.std_size == 2536u &&
        stage.std_objects == 8 &&
        stage.std_quads == 19 && stage.ecl_size == 47924u &&
        stage.ecl_sub_count == 68 && stage.frames_run == 120 &&
        stage.update_ticks == 120 && stage.draw_ticks == 120 &&
        stage.stage_frame == 120;
    std::printf(
        "stage bridge: enter=%d factory_wrappers=%d resources=%u/%u "
        "ticks=%d/%d frame=%d\n",
        stage.enter_result, stage.factories_created, stage.std_size,
        stage.ecl_size, stage.update_ticks, stage.draw_ticks,
        stage.stage_frame);
    std::printf("stage std raw view: valid=%d\n",
                stage.std_raw_view_valid);
    std::printf("stage geometry: valid=%d subrecords=%d placements=%d\n",
                stage.std_geometry_valid, stage.std_subrecords,
                stage.std_placements);
    std::printf(
        "stage timeline: initialized=%d decoded=%u stopped=%u jumps=%u "
        "max_access=%zu max_extent=%zu rejected=%u budget_rejected=%u "
        "histogram=",
        stage.timeline_initialized, stage.timeline_decoded,
        stage.timeline_stopped_events, stage.timeline_cursor_jumps,
        stage.timeline_maximum_accessed_offset,
        stage.timeline_maximum_record_extent, stage.timeline_rejected,
        stage.timeline_budget_rejections);
    for (int opcode = 0; opcode < 15; ++opcode)
        std::printf("%s%u", opcode != 0 ? "," : "",
                    stage.timeline_opcode_histogram[opcode]);
    std::printf("\n");
    const HostStageRuntimeView& runtime = HostStage_GetRuntimeView();
    if (runtime.camera != nullptr)
        std::printf(
            "stage camera: eye=%.2f,%.2f,%.2f target=%.2f,%.2f,%.2f "
            "up=%.2f,%.2f,%.2f fov=%.6f\n",
            runtime.camera->eye[0], runtime.camera->eye[1],
            runtime.camera->eye[2], runtime.camera->target[0],
            runtime.camera->target[1], runtime.camera->target[2],
            runtime.camera->up[0], runtime.camera->up[1],
            runtime.camera->up[2], runtime.camera->field_of_view);
    std::printf("STAGE_BRIDGE_%s\n", stage_ok ? "PASS" : "FAIL");
#if defined(_WIN32)
    return ok && stage_ok ? 0 : 1;
#else
    // The portable host intentionally has no title renderer. Its independent
    // gate is the real DAT-backed stage bridge.
    return stage_ok ? 0 : 1;
#endif
}
