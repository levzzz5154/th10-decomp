// Allocate and publish the UI before launching its worker.
#include <string.h>
#include <stddef.h>
#include "th10/game/ui_thread_host.hpp"

struct GameConfig;
__declspec(noinline) char __fastcall GameConfig_InitializeDefaults(int, GameConfig*);
#pragma code_seg(".text$01uiconfig")
#define TH10_GAME_CONFIG_KEEP_SECTION
#include "game_config_defaults.cpp"
#undef TH10_GAME_CONFIG_KEEP_SECTION
#pragma code_seg()

void* __cdecl operator new(unsigned int size);
struct Game {
    unsigned char reserved_00[0x20];
    unsigned int flags_20;
    GameConfig config;
    unsigned int flags_58;
    unsigned int argument_5c;
    __forceinline Game() {
        flags_20 &= ~1u;
        GameConfig_InitializeDefaults(0, &config);
        memset(this, 0, sizeof(*this));
    }
};
typedef char GameUiLayout_004180e0[(sizeof(Game)==0x60 && offsetof(Game, config)==0x24 && offsetof(Game, argument_5c)==0x5c)?1:-1];
struct UiEvictionDevice_004180e0 {
    virtual void __stdcall Slot00() = 0;
    virtual void __stdcall Slot01() = 0;
    virtual void __stdcall Slot02() = 0;
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual long __stdcall EvictManagedResources() = 0;
};
extern "C" UiEvictionDevice_004180e0* g_d3d_device;
extern "C" Game* g_game;
extern "C" GameUiThreadHost g_application;
extern "C" void __cdecl Game_LoadThread(void);

#pragma code_seg(".text$00uicreate")
extern "C" __declspec(noinline) Game* __stdcall Game_Create(unsigned int argument) {
    Game* ui = new Game;
    g_d3d_device->EvictManagedResources();
    ui->argument_5c = argument;
    g_game = ui;
    ui->flags_58 |= 4;
    // Retail passes the no-argument thunk as the worker entry.
    g_application.Spawn(reinterpret_cast<PlatformWorkerEntry>(Game_LoadThread), 0);
    return ui;
}
#pragma code_seg()
