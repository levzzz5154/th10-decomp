// Runtime contracts shared by the all-source PE32 build.  These are ordinary
// implementations, not link-only storage: callers may execute every function
// in this file.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <stdexcept>

#include "th10/app/frame_clock.hpp"
#include "th10/game/recovery_leaves.hpp"
#include "th10/game/scheduler.hpp"
#include "th10/render/animation_manager.hpp"
#include "th10/render/camera_setup.hpp"
#include "th10/render/resource_manager.hpp"

void Directory_Create(const char* path) {
    if (path != nullptr && *path != '\0')
        CreateDirectoryA(path, nullptr);
}

int File_Exists(const char* path) {
    if (path == nullptr)
        return 0;
    const DWORD attributes = GetFileAttributesA(path);
    return attributes != INVALID_FILE_ATTRIBUTES &&
           (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

int File_ProbePath(const char* path) {
    return File_Exists(path);
}

void Platform_LogMessage(const char* message) {
    if (message == nullptr)
        return;
    std::fputs("[th10] ", stderr);
    std::fputs(message, stderr);
    std::fputc('\n', stderr);
    std::fflush(stderr);
}

void Logger_AppendFormatted(char* destination, const char* message) {
    if (destination == nullptr || message == nullptr)
        return;
    std::strcat(destination, message);
}

int D3DDevice_TestCooperativeLevel(void* device) {
    if (device == nullptr)
        return static_cast<int>(0x88760868u);  // D3DERR_DEVICELOST
    using Method = long(__stdcall*)(void*);
    auto** table = *reinterpret_cast<void***>(device);
    return static_cast<int>(reinterpret_cast<Method>(table[3])(device));
}

int D3DDevice_Reset(void* device) {
    if (device == nullptr)
        return static_cast<int>(0x8876086Cu);  // D3DERR_INVALIDCALL
    using Method = long(__stdcall*)(void*, void*);
    auto** table = *reinterpret_cast<void***>(device);
    extern float DAT_00491d0c[14];
    return static_cast<int>(
        reinterpret_cast<Method>(table[16])(device, DAT_00491d0c));
}

void Scheduler_UnregisterCallback(void* callback, int device) {
    Scheduler_Remove(static_cast<SchedulerCallback*>(callback),
                     reinterpret_cast<void*>(device));
}

namespace {

template <typename Method>
Method D3DMethod(void* device, unsigned int index) {
    return reinterpret_cast<Method>((*reinterpret_cast<void***>(device))[index]);
}

}  // namespace

void D3D_ApplyDefaultRenderState(int) {
    extern void* g_pD3DDevice;
    extern void* g_pGameStateManager;
    if (g_pD3DDevice == nullptr)
        return;
    DeviceStateHooks hooks = {};
    hooks.context = g_pD3DDevice;
    hooks.set_render_state = [](void* device, unsigned int state,
                                unsigned int value) {
        using Method = long(__stdcall*)(void*, unsigned int, unsigned int);
        D3DMethod<Method>(device, 57)(device, state, value);
    };
    hooks.set_texture_stage_state =
        [](void* device, unsigned int stage, unsigned int state,
           unsigned int value) {
            using Method =
                long(__stdcall*)(void*, unsigned int, unsigned int,
                                  unsigned int);
            D3DMethod<Method>(device, 67)(device, stage, state, value);
        };
    hooks.set_sampler_state =
        [](void* device, unsigned int sampler, unsigned int state,
           unsigned int value) {
            using Method =
                long(__stdcall*)(void*, unsigned int, unsigned int,
                                  unsigned int);
            D3DMethod<Method>(device, 69)(device, sampler, state, value);
        };
    unsigned char* flags = nullptr;
    if (g_pGameStateManager != nullptr)
        flags = static_cast<unsigned char*>(g_pGameStateManager) + 0x3ADA64;
    Device_ApplyDefaultState(&hooks, flags);
}

void D3D_InitializeViewport() {
    extern void* g_pD3DDevice;
    extern float DAT_00491cf4[4];
    if (g_pD3DDevice == nullptr)
        return;
    ViewportHooks hooks = {};
    hooks.context = g_pD3DDevice;
    hooks.set_viewport = [](void* device, const ViewportBlock* viewport) {
        using Method = long(__stdcall*)(void*, const ViewportBlock*);
        D3DMethod<Method>(device, 47)(device, viewport);
    };
    // Retail 0x0043BC40 runs two clear/present passes and resets the device
    // with the stored present parameters whenever a present fails.
    hooks.reset_clip_state = [](void* device) {
        Recovery_ResetDeviceStreams(
            device,
            [](void* target) {
                using Method = long(__stdcall*)(void*, unsigned long,
                                                const void*, unsigned long,
                                                unsigned long, float,
                                                unsigned long);
                D3DMethod<Method>(target, 43)(target, 0, nullptr, 3, 0,
                                              1.0f, 0);
            },
            [](void* target) -> int {
                using Method = long(__stdcall*)(void*, const void*,
                                                const void*, void*,
                                                const void*);
                return static_cast<int>(D3DMethod<Method>(target, 17)(
                    target, nullptr, nullptr, nullptr, nullptr));
            },
            [](void* target) {
                extern float DAT_00491d0c[14];
                using Method = long(__stdcall*)(void*, void*);
                D3DMethod<Method>(target, 16)(target, &DAT_00491d0c);
            });
    };
    Viewport_ApplyDefault(
        reinterpret_cast<ViewportBlock*>(DAT_00491cf4), &hooks);
}

void __fastcall AnimationManager_RemoveHandle(
    void*, void* manager, int handle) {
    int owned_handle = handle;
    AnimationManager_MarkForRemovalAndClearHandle(manager, &owned_handle);
}

void __fastcall D3DResource_Release(void* resource, void*) {
    if (resource == nullptr)
        return;
    using Release = unsigned long(__stdcall*)(void*);
    auto** table = *reinterpret_cast<void***>(resource);
    reinterpret_cast<Release>(table[2])(resource);
}

void DestroyEntityList(void* base);

void GameStateManager_DestroyEntitiesForReset(void* manager) {
    DestroyEntityList(manager);
}

void Render_ReinitializeAfterReset() {
    D3D_ApplyDefaultRenderState(0);
    D3D_InitializeViewport();
}

// 0x0044C150.  The retail worker object is a process-global block at
// 0x00492254; its handle and stop fields live at +4, +0xC, +0x10 and +0x18.
void D3DResourceWorker_Stop() {
    extern unsigned char DAT_00492254[];
    auto* state = DAT_00492254;
    HANDLE handle = *reinterpret_cast<HANDLE*>(state + 4);
    if (handle == nullptr)
        return;
    DWORD wait_result;
    do {
        *reinterpret_cast<unsigned int*>(state + 0x0C) = 1;
        *reinterpret_cast<unsigned int*>(state + 0x10) = 0;
        wait_result = WaitForSingleObject(handle, 200);
        if (wait_result == WAIT_TIMEOUT)
            Sleep(1);
    } while (wait_result == WAIT_TIMEOUT);
    CloseHandle(handle);
    *reinterpret_cast<HANDLE*>(state + 4) = nullptr;
    *reinterpret_cast<unsigned int*>(state + 0x18) = 0;
}

// 0x004054B0.  ESI is the retail manager owner; the cleaned call sites pass
// the three numeric inputs explicitly, so the global manager supplies ESI.
void Player_UpdatePowerDisplay(
    int, int major_value, int minor_value) {
    extern void* g_pGameStateManager;
    if (g_pGameStateManager == nullptr)
        return;
    auto* manager = static_cast<unsigned char*>(g_pGameStateManager);
    void* resource = *reinterpret_cast<void**>(manager + 0x9EC8);
    if (resource == nullptr)
        return;
    AnimationObject_ConfigureFromResource(
        manager + 0x6A8C, resource, major_value + 8);
    AnimationObject_ConfigureFromResource(
        manager + 0x71E4, resource, minor_value / 10 + 8);
    AnimationObject_ConfigureFromResource(
        manager + 0x7590, resource, minor_value % 10 + 8);
}

extern "C" long __stdcall D3DXSaveSurfaceToFileA(
    const char* destination, int image_format, void* surface,
    const void* palette, const void* source_rectangle);

// Retail builds the same 24-bit BMP through a worker.  The all-source runtime
// uses D3DX's synchronous BMP writer against the identical back-buffer
// surface.  This preserves the file result and avoids publishing half-built
// worker state during device reset.
void Screenshot_Capture(const char* path) {
    extern unsigned char DAT_00491c28[];
    if (path == nullptr)
        return;
    while (*reinterpret_cast<unsigned int*>(DAT_00491c28 + 0x50C) != 0)
        Sleep(10);
    void* surface = *reinterpret_cast<void**>(DAT_00491c28 + 8);
    if (surface != nullptr)
        D3DXSaveSurfaceToFileA(path, 0, surface, nullptr, nullptr);
}

void* ECL_FindScriptLabel(
    void* vm_pointer, const unsigned short* name);

// 0x0040DA17 is a call to the recovered 0x00450470 label lookup.  Retail
// supplies the lookup owner in EAX from config+0x54 and the UTF-16 name on
// the stack; expose that hidden input explicitly here.
int __fastcall ResourceManager_FindTexture(void* resource_name) {
    extern unsigned int DAT_00477704;
    const auto* config = reinterpret_cast<const unsigned char*>(
        static_cast<unsigned long>(DAT_00477704));
    if (config == nullptr || resource_name == nullptr)
        return 0;
    void* labels = *reinterpret_cast<void* const*>(config + 0x54);
    return static_cast<int>(reinterpret_cast<unsigned long>(
        ECL_FindScriptLabel(
            labels, static_cast<const unsigned short*>(resource_name))));
}

void ItemManager_CollectNearPlayer(
    void* item_manager, const float* position, float radius,
    int allow_effect) {
    if (item_manager == nullptr || position == nullptr)
        return;
    auto* manager = static_cast<unsigned char*>(item_manager);
    std::memcpy(manager + 0x440, position, sizeof(float) * 3);
    void* node = *reinterpret_cast<void**>(manager + 0x18);
    while (node != nullptr) {
        auto* bytes = static_cast<unsigned char*>(node);
        void* next = *reinterpret_cast<void**>(bytes + 8);
        if (*reinterpret_cast<int*>(bytes + 0x0C) != 1) {
            using Collect = int(__thiscall*)(
                void*, const float*, float, int);
            auto** table = *reinterpret_cast<void***>(node);
            reinterpret_cast<Collect>(table[7])(
                node, position, radius, allow_effect);
        }
        node = next;
    }
}

extern "C" void _eh_vector_constructor_iterator_(
    void* base, unsigned int element_size, unsigned int count,
    void* constructor, void* destructor) {
    using Constructor = void(__fastcall*)(void*);
    using Destructor = void(__fastcall*)(void*);
    auto construct = reinterpret_cast<Constructor>(constructor);
    auto destroy = reinterpret_cast<Destructor>(destructor);
    auto* bytes = static_cast<unsigned char*>(base);
    unsigned int completed = 0;
    try {
        for (; completed < count; ++completed)
            construct(bytes + completed * element_size);
    } catch (...) {
        while (completed != 0) {
            --completed;
            destroy(bytes + completed * element_size);
        }
        throw;
    }
}

extern "C" void _eh_vector_destructor_iterator_(
    void* base, unsigned int element_size, unsigned int count,
    void* destructor) {
    using Destructor = void(__fastcall*)(void*);
    auto destroy = reinterpret_cast<Destructor>(destructor);
    auto* bytes = static_cast<unsigned char*>(base);
    while (count != 0) {
        --count;
        destroy(bytes + count * element_size);
    }
}

extern "C" void LegacyString_ThrowLengthError() {
    throw std::length_error("legacy string length");
}

extern "C" void LegacyString_ThrowRangeError() {
    throw std::out_of_range("legacy string range");
}

extern "C" void* __cdecl _memmove(
    void* destination, const void* source, unsigned int size) {
    return std::memmove(destination, source, size);
}

extern "C" char* __cdecl _strrchr(const char* text, int character) {
    return const_cast<char*>(std::strrchr(text, character));
}

extern "C" int __cdecl __stricmp(const char* left, const char* right) {
    return _stricmp(left, right);
}

extern "C" int __cdecl _vsprintf(
    char* destination, const char* format, va_list arguments) {
    return std::vsprintf(destination, format, arguments);
}

namespace {

struct Vec3 {
    float x;
    float y;
    float z;
};

Vec3 Subtract(const float* left, const float* right) {
    return {left[0] - right[0], left[1] - right[1], left[2] - right[2]};
}

Vec3 Normalize(Vec3 value) {
    const float length =
        std::sqrt(value.x * value.x + value.y * value.y + value.z * value.z);
    if (length == 0.0f)
        return {};
    return {value.x / length, value.y / length, value.z / length};
}

Vec3 Cross(Vec3 left, Vec3 right) {
    return {
        left.y * right.z - left.z * right.y,
        left.z * right.x - left.x * right.z,
        left.x * right.y - left.y * right.x,
    };
}

float Dot(Vec3 left, const float* right) {
    return left.x * right[0] + left.y * right[1] + left.z * right[2];
}

}  // namespace

extern "C" void D3DXMatrixLookAtLH(
    float* output, float* eye, float* target, float* up) {
    const Vec3 forward = Normalize(Subtract(target, eye));
    const Vec3 right = Normalize(Cross({up[0], up[1], up[2]}, forward));
    const Vec3 actual_up = Cross(forward, right);
    const float matrix[16] = {
        right.x, actual_up.x, forward.x, 0.0f,
        right.y, actual_up.y, forward.y, 0.0f,
        right.z, actual_up.z, forward.z, 0.0f,
        -Dot(right, eye), -Dot(actual_up, eye), -Dot(forward, eye), 1.0f,
    };
    std::memcpy(output, matrix, sizeof(matrix));
}

extern "C" void D3DXMatrixPerspectiveFovLH(
    float* output, float fov_y, float aspect, float near_z, float far_z) {
    const float height = 1.0f / std::tan(fov_y * 0.5f);
    const float width = height / aspect;
    const float range = far_z / (far_z - near_z);
    const float matrix[16] = {
        width, 0.0f, 0.0f, 0.0f,
        0.0f, height, 0.0f, 0.0f,
        0.0f, 0.0f, range, 1.0f,
        0.0f, 0.0f, -near_z * range, 0.0f,
    };
    std::memcpy(output, matrix, sizeof(matrix));
}
