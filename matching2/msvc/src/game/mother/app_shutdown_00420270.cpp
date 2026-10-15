// 0x00420270 (293 bytes): shut the application down. Stop both worker
// threads, release the global game states, the published block, the back
// buffer surface, the font cache, the input devices and the frame timer, and
// close the data archive.
//
// The application object arrives in EAX and almost every callee takes its
// argument in a register chosen by the whole-program link, so the body is
// compiled in the native-LTCG cluster build_support/layout/ltcg/app_shutdown_00420270.json.
#include "th10/platform/worker.hpp"
#include "th10/platform/win32_timer.hpp"
#include "th10/game/published_block.hpp"
#include "th10/render/resource_registrar_0043e460.hpp"

struct DatArchive {
    __declspec(noinline) void Close();
};

extern "C" void __cdecl DeleteFontCacheObjects_00437d10();
extern "C" void __cdecl asm_free_00452422(void* memory);
extern "C" void __cdecl asm_free_004524a1(void* memory);
void __stdcall Recovery_ReleaseGlobalStates();
__declspec(noinline) void DeletePublishedBlock(PublishedBlock* block);

// The part of a COM interface this routine uses: IUnknown::Release and, for
// the DirectInput devices, Unacquire.
struct ComObject_00420270 {
    struct Vtable {
        void* query_interface;
        void* add_ref;
        unsigned long (__stdcall* Release)(ComObject_00420270*);
        void* reserved_0c[5];
        long (__stdcall* Unacquire)(ComObject_00420270*);
    }* vtable;
};

struct AnimationManagerSurface_00420270 {
    unsigned char reserved_000000[0x3ada74];
    ComObject_00420270* back_buffer;            // +0x3ADA74
};

// The application object at 0x00491C28.
struct App_00420270 {
    unsigned char reserved_000[0x0c];
    ComObject_00420270* input;                  // +0x0C
    ComObject_00420270* keyboard;               // +0x10
    ComObject_00420270* joystick;               // +0x14
    unsigned char reserved_018[0x11c - 0x18];
    Win32Timer* timer;                          // +0x11C
    unsigned char reserved_120[0x62c - 0x120];
    PlatformWorker worker;                      // +0x62C
    unsigned char reserved_648[0x764 - 0x648];
    void* buffer_764;                           // +0x764

    __declspec(noinline) int Shutdown();
};

extern "C" App_00420270 g_application;
extern "C" PlatformWorker g_input_worker;
extern "C" int g_sound_init_status;
extern "C" AnimationManagerSurface_00420270* g_sprt_ctrl;
extern "C" AnimationManager_0043e460 g_sound_manager;
extern "C" DatArchive g_archive;
extern "C" const char str_dummy[];

static inline void DeleteTimer(Win32Timer* timer) {
    if (timer) {
        timer->Release();
        asm_free_004524a1(timer);
    }
}

#pragma code_seg(".text$10shutdown")
int App_00420270::Shutdown() {
    g_input_worker.Stop();
    g_sound_init_status = 2;
    g_application.worker.Stop();
    if (g_application.buffer_764) {
        asm_free_00452422(g_application.buffer_764);
        g_application.buffer_764 = 0;
    }
    Recovery_ReleaseGlobalStates();
    DeletePublishedBlock(g_fps);
    ComObject_00420270** back_buffer = &g_sprt_ctrl->back_buffer;
    if (*back_buffer) {
        (*back_buffer)->vtable->Release(*back_buffer);
        *back_buffer = 0;
    }
    g_sound_manager.RegisterResource(str_dummy, 4, 0);
    DeleteFontCacheObjects_00437d10();
    if (keyboard) {
        keyboard->vtable->Unacquire(keyboard);
        if (keyboard) {
            keyboard->vtable->Release(keyboard);
            keyboard = 0;
        }
    }
    if (joystick) {
        joystick->vtable->Unacquire(joystick);
        if (joystick) {
            joystick->vtable->Release(joystick);
            joystick = 0;
        }
    }
    if (input) {
        input->vtable->Release(input);
        input = 0;
    }
    if (g_application.timer) {
        g_application.timer->Cancel();
        DeleteTimer(g_application.timer);
        g_application.timer = 0;
    }
    g_archive.Close();
    return 0;
}
#pragma code_seg()
