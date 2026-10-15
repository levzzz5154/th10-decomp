// 0x0041C290..0x0041C2EA (91 bytes): LaserManager_Create
//
// Allocates the 0x45C-byte laser manager (laser.cpp, LaserInf), initializes the embedded head laser (base Laser)
// at +0x10, zeroes the whole block, publishes it through data_0047781C and then
// installs the laser manager tasks on it.  A failed installation tears the
// manager down again and frees it, and the factory reports NULL so callers can
// tell "not created" from "created".
//
// Retail keeps the manager in ESI across the whole body while the registration
// call receives it in EBX: the callee at 0x0041C120 takes its object in EBX and
// its own scheduler registrations keep the task in ESI and the priority in EDI,
// so the register is a whole-program agreement.  This source is therefore
// compiled in the same native-LTCG link as that callee chain (see
// build_support/layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include <string.h>

struct LaserBaseView;                     // the 0x424-byte base Laser

struct LaserManagerView {
    unsigned char pad_000[0x08];
    void *primary_task_008;             // +0x008, primary display task
    void *secondary_task_00C;           // +0x00C, secondary display task
    unsigned char head_laser_010[0x424];     // +0x010, embedded head laser (base Laser)
    void *head_laser_pointer_434;            // +0x434, address of the embedded object
    unsigned char pad_438[0x20];
    void *display_resource_458;         // +0x458, filled by the display tasks
};

typedef char LaserManagerView_size_must_be_45c[
    sizeof(LaserManagerView) == 0x45C ? 1 : -1];

void *__cdecl operator new(unsigned int size);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void *block);
extern "C" LaserManagerView *g_laser_manager;
LaserBaseView *__fastcall Laser_Construct(void *, LaserBaseView *self);
extern "C" int __stdcall LaserManager_RegisterTasks(
        LaserManagerView *manager);
extern "C" void __stdcall asm_LaserManager_Destroy_0041c1c0(
        LaserManagerView *manager);

extern "C" __declspec(noinline) void *__cdecl
LaserManager_Create(void);
#pragma code_seg(".text$00gbscoremanager")
extern "C" __declspec(noinline) void *__cdecl
LaserManager_Create(void) {
    LaserManagerView *fresh = new LaserManagerView;
    LaserManagerView *manager;
    if (fresh) {
        Laser_Construct(0, (LaserBaseView *)fresh->head_laser_010);
        memset(fresh, 0, sizeof(LaserManagerView));
        g_laser_manager = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }
    if (LaserManager_RegisterTasks(manager) != 0) {
        if (manager) {
            asm_LaserManager_Destroy_0041c1c0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
