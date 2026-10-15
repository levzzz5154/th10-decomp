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
struct GameUi_004180e0 {
    unsigned char reserved_00[0x20];
    unsigned int flags_20;
    GameConfig config;
    unsigned int flags_58;
    unsigned int argument_5c;
    __forceinline GameUi_004180e0() {
        flags_20 &= ~1u;
        GameConfig_InitializeDefaults(0, &config);
        memset(this, 0, sizeof(*this));
    }
};
typedef char GameUiLayout_004180e0[(sizeof(GameUi_004180e0)==0x60 && offsetof(GameUi_004180e0, config)==0x24 && offsetof(GameUi_004180e0, argument_5c)==0x5c)?1:-1];
struct UiEvictionDevice_004180e0 {
    virtual void __stdcall Slot00() = 0;
    virtual void __stdcall Slot01() = 0;
    virtual void __stdcall Slot02() = 0;
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual long __stdcall EvictManagedResources() = 0;
};
extern "C" UiEvictionDevice_004180e0* data_00491c30;
extern "C" GameUi_004180e0* data_00477810;
extern "C" GameUiThreadHost data_00491c28;
extern "C" void __cdecl Stage_StartupThread(void);

#pragma code_seg(".text$00uicreate")
extern "C" __declspec(noinline) GameUi_004180e0* __stdcall GameUi_CreateAndPublish_004180e0(unsigned int argument) {
    GameUi_004180e0* ui = new GameUi_004180e0;
    data_00491c30->EvictManagedResources();
    ui->argument_5c = argument;
    data_00477810 = ui;
    ui->flags_58 |= 4;
    // Retail passes the no-argument thunk as the worker entry.
    data_00491c28.Spawn(reinterpret_cast<PlatformWorkerEntry>(Stage_StartupThread), 0);
    return ui;
}
#pragma code_seg()
