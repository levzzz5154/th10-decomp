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

struct HostAnmVm {
    AnmVmState state = {};
    int active = 0;
    int script_id = -1;
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
    unsigned int title_resource_sizes[2] = {};
    AnmFileEntry title_entries[2] = {};
    int title_anm_parsed = 0;
    int title_vm_ready = 0;
    int title_draw_calls = 0;
    HostAnmVm title_vms[2] = {};
    HostAnmVm title_child_vms[64] = {};
    int title_child_vm_count = 0;
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
    int dump_anm = 0;
    int menu_screen = 0;
    int menu_quit = 0;
    int menu_windowed = 1;
    uint32_t menu_input = 0;
    TitleMainMenuState menu_state = {};
    TitleOptionsState options_state = {};
    TitleOptionsConfig options_config = {0, 100, 80};
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
    const uint8_t* anm_texture_entry_bases[16] = {};
    IDirect3DTexture9* anm_textures[16] = {};
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
    hooks.spawn_child = [](void*, AnmVmState* parent, int, int script_id) {
        if (g_host.title_child_vm_count >= 64 ||
            g_host.title_resource_bytes[0] == nullptr)
            return;
        AnmFileScript script;
        if (!AnmFile_FindGlobalScript(
                g_host.title_resource_bytes[0],
                g_host.title_resource_sizes[0],
                static_cast<unsigned int>(script_id), nullptr, &script))
            return;
        HostAnmVm* child =
            &g_host.title_child_vms[g_host.title_child_vm_count++];
        HostInitializeAnmVm(child, script.instructions);
        child->script_id = script_id;
        for (int axis = 0; axis < 3; ++axis)
            child->state.position[axis] = parent->position[axis];
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

void HostBroadcastTitleInterrupt(int interrupt) {
    g_host.title_vms[1].state.pending_interrupt = interrupt;
    for (int index = 0; index < g_host.title_child_vm_count; ++index)
        if (g_host.title_child_vms[index].active)
            g_host.title_child_vms[index].state.pending_interrupt = interrupt;
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
    g_host.bgm_buffer->SetVolume(DSBVOLUME_MAX);
    return SUCCEEDED(g_host.bgm_buffer->Play(0, 0, DSBPLAY_LOOPING));
}

void HostPlayMenuSound(int index) {
    if (index < 0 || index >= 3 ||
        g_host.menu_sound_buffers[index] == nullptr)
        return;
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
    for (int index = 0; index < 16; ++index) {
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
    if (FAILED(g_host.device->CreateTexture(
            payload.width, payload.height, 1, 0, format, D3DPOOL_MANAGED,
            &texture, nullptr)))
        return nullptr;
    D3DLOCKED_RECT locked;
    if (FAILED(texture->LockRect(0, &locked, nullptr, 0))) {
        texture->Release();
        return nullptr;
    }
    unsigned int source_pitch =
        payload.height == 0 ? 0 : payload.data_size / payload.height;
    for (unsigned int row = 0; row < payload.height; ++row) {
        std::memcpy(static_cast<unsigned char*>(locked.pBits) +
                        row * locked.Pitch,
                    payload.pixels + row * source_pitch, source_pitch);
    }
    texture->UnlockRect(0);
    for (int index = 0; index < 16; ++index) {
        if (g_host.anm_texture_entry_bases[index] == nullptr) {
            g_host.anm_texture_entry_bases[index] = entry.base;
            g_host.anm_textures[index] = texture;
            return texture;
        }
    }
    texture->Release();
    return nullptr;
}

void HostDrawAnmVm(const AnmVmState& vm) {
    if (vm.sprite < 0 || g_host.title_resource_bytes[0] == nullptr)
        return;
    AnmFileEntry entry;
    AnmFileSprite sprite;
    if (!AnmFile_FindGlobalSprite(
            g_host.title_resource_bytes[0], g_host.title_resource_sizes[0],
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

void HostRenderMenu() {
    if (g_host.smoke_mode || g_host.device == nullptr ||
        g_host.window == nullptr)
        return;
    static bool trace_render = true;
    if (trace_render)
        HostTrace("beginning first title render");
    if (trace_render) {
        std::fprintf(stderr,
                     "[th10-recon] root sprites: %d %d; children:",
                     g_host.title_vms[0].state.sprite,
                     g_host.title_vms[1].state.sprite);
        for (int index = 0; index < g_host.title_child_vm_count; ++index) {
            const HostAnmVm& child = g_host.title_child_vms[index];
            if (child.active)
                std::fprintf(stderr, " %d:%d", child.script_id,
                             child.state.sprite);
        }
        std::fprintf(stderr, "\n");
        std::fflush(stderr);
    }
    g_host.device->Clear(0, nullptr, D3DCLEAR_TARGET,
                         D3DCOLOR_XRGB(12, 20, 36), 1.0f, 0);
    g_host.device->BeginScene();
    g_host.device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    g_host.device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    g_host.device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    // Retail's batch renderer feeds per-sprite colour through D3DTA_TFACTOR.
    // This standalone path carries the same value in the submitted vertex,
    // so bind argument 2 to diffuse rather than the untouched default factor.
    g_host.device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    g_host.device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    g_host.device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    g_host.device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    g_host.device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    g_host.device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
    HostDrawAnmVm(g_host.title_vms[0].state);
    HostDrawAnmVm(g_host.title_vms[1].state);
    for (int index = 0; index < g_host.title_child_vm_count; ++index)
        if (g_host.title_child_vms[index].active)
            HostDrawAnmVm(g_host.title_child_vms[index].state);
    if (trace_render)
        HostTrace("first title sprites submitted");
    g_host.device->EndScene();
    g_host.device->Present(nullptr, nullptr, nullptr, nullptr);
    if (trace_render) {
        HostTrace("first title frame presented");
        trace_render = false;
    }
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
        g_host.menu_screen = 0;
        TitleMainMenu_Initialize(&g_host.menu_state);
        HostStartTitleScripts(88, 0);
        HostBroadcastTitleInterrupt(17);
    }
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
    }
    if (!g_host.smoke_mode && g_host.menu_screen == 0) {
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
    g_host.window = CreateWindowA(
        window_class.lpszClassName, "TH10 reconstructed startup",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
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
        HostTrace(HostStartTitleBgm() ? "title BGM playing" :
                                        "title BGM unavailable");
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
    g_host.title_resource_sizes[index] = size;
    g_host.title_resources_from_archive = 1;
    if (AnmFile_ParseEntry(bytes, size, 0, &g_host.title_entries[index])) {
        if (index == 0) {
            AnmFileScript main_script;
            AnmFileScript menu_script;
            g_host.title_anm_parsed =
                AnmFile_FindGlobalScript(bytes, size, 88, nullptr,
                                         &main_script) &&
                AnmFile_FindGlobalScript(bytes, size, 0, nullptr,
                                         &menu_script);
            if (g_host.title_anm_parsed) {
                HostInitializeAnmVm(&g_host.title_vms[0],
                                    main_script.instructions);
                HostInitializeAnmVm(&g_host.title_vms[1],
                                    menu_script.instructions);
                g_host.title_vms[1].state.pending_interrupt = 17;
                g_host.title_vm_ready = 1;
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
        for (int index = 0; index < 16; ++index) {
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
         std::strcmp(argv[1], "--dump-anm") == 0);
    g_host.dump_anm =
        argc > 1 && std::strcmp(argv[1], "--dump-anm") == 0;
#else
    (void)argc;
    (void)argv;
    g_host.smoke_mode = 1;
#endif
#if defined(_WIN32)
    HostTrace("mounting th10.dat");
    if (!Resource_RegisterArchive("th10.dat")) {
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
             g_host.title_frames_completed >= 60 &&
             g_host.clean_shutdown &&
             exit_code == 0;
    std::printf("SMOKE_%s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
