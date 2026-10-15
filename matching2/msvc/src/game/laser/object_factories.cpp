// 0x0041C290..0x0041C2EA (91 bytes): asm_ScoreManager_CreateAndInitRetail_0041c290
//
// Allocates the 0x45C-byte score manager, initializes the embedded score object
// at +0x10, zeroes the whole block, publishes it through data_0047781C and then
// installs the score display tasks on it.  A failed installation tears the
// manager down again and frees it, and the factory reports NULL so callers can
// tell "not created" from "created".
//
// Retail keeps the manager in ESI across the whole body while the registration
// call receives it in EBX: the callee at 0x0041C120 takes its object in EBX and
// its own scheduler registrations keep the task in ESI and the priority in EDI,
// so the register is a whole-program agreement.  This source is therefore
// compiled in the same native-LTCG link as that callee chain (see
// layout/ltcg/bullet_manager_load_scripts_0040ae70.json).
#include <string.h>

struct ScoreObject;                     // the 0x424-byte score object

struct RawManager_0041c290 {
    unsigned char pad_000[0x08];
    void *primary_task_008;             // +0x008, primary display task
    void *secondary_task_00C;           // +0x00C, secondary display task
    unsigned char score_010[0x424];     // +0x010, embedded score object
    void *score_pointer_434;            // +0x434, address of the embedded object
    unsigned char pad_438[0x20];
    void *display_resource_458;         // +0x458, filled by the display tasks
};

typedef char RawManager_0041c290_size_must_be_45c[
    sizeof(RawManager_0041c290) == 0x45C ? 1 : -1];

void *__cdecl operator new(unsigned int size);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int size);
extern "C" void __cdecl entry_free_004524a1(void *block);
extern "C" RawManager_0041c290 *g_laser_manager;
ScoreObject *__fastcall ScoreObject_Initialize(void *, ScoreObject *self);
extern "C" int __stdcall asm_ScoreDisplay_RegisterTasksRetail_0041c120(
        RawManager_0041c290 *manager);
extern "C" void __stdcall asm_ScoreExtendedObject_DestroyRetail_0041c1c0(
        RawManager_0041c290 *manager);

extern "C" __declspec(noinline) void *__cdecl
asm_ScoreManager_CreateAndInitRetail_0041c290(void);
#pragma code_seg(".text$00gbscoremanager")
extern "C" __declspec(noinline) void *__cdecl
asm_ScoreManager_CreateAndInitRetail_0041c290(void) {
    RawManager_0041c290 *fresh = new RawManager_0041c290;
    RawManager_0041c290 *manager;
    if (fresh) {
        ScoreObject_Initialize(0, (ScoreObject *)fresh->score_010);
        memset(fresh, 0, sizeof(RawManager_0041c290));
        g_laser_manager = fresh;
        manager = fresh;
    } else {
        manager = 0;
    }
    if (asm_ScoreDisplay_RegisterTasksRetail_0041c120(manager) != 0) {
        if (manager) {
            asm_ScoreExtendedObject_DestroyRetail_0041c1c0(manager);
            entry_free_004524a1(manager);
        }
        return 0;
    }
    return manager;
}
#pragma code_seg()
