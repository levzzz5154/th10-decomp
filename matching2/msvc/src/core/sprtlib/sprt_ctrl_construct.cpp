// 0x00445900 (2,315 bytes): animation storage constructor, with the three
// compiler-generated unwind functions at 0x00465760/0x0046577C/0x0046578A and
// the frame handler at 0x004657A5.  The sprite pool, the middle sprite and the
// layer sprites are members with real constructors and destructors.
#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
extern "C" void __cdecl entry_free_00452422(void*);
#pragma code_seg(".text$00d_dtor")
struct AnmConstructedSprite : Entity {
    __forceinline AnmConstructedSprite();
    __declspec(dllexport) ~AnmConstructedSprite() {
        if (resource) entry_free_00452422(resource);
        resource = 0;
    }
};
#pragma code_seg(".text$00f_ctor")
static __forceinline void ClearSpriteRegistration(unsigned int* flags) { *flags &= ~1u; }
__forceinline AnmConstructedSprite::AnmConstructedSprite() {
    ClearSpriteRegistration(&flags_06C);
    ClearSpriteRegistration(&flags_0B0);
    ClearSpriteRegistration(&flags_0FC);
    ClearSpriteRegistration(&flags_128);
    ClearSpriteRegistration(&flags_174);
    ClearSpriteRegistration(&flags_1B0);
    ClearSpriteRegistration(&flags_1FC);
    ClearSpriteRegistration(&flags_228);
    ClearSpriteRegistration(&flags_378);
    memset(this, 0, sizeof(*this));
    SpriteIndex() = -1;
}
#pragma code_seg()
struct SprtCtrl {
    unsigned int first_id, second_id;
    unsigned char reserved_008[0x68 - 8];
    AnmConstructedSprite pool[4096];
    unsigned char pool_in_use[4096];
    unsigned char reserved_3ad068[0x3AD130 - 0x3AD068];
    AnmConstructedSprite middle;
    unsigned char reserved_3ad4dc[0x3ADA60 - 0x3AD4DC];
    int state;
    int counter;
    unsigned char flags[4];
    unsigned char marker;
    unsigned char reserved_3ada6d[7];
    int unknown_3ada74;
    unsigned char reserved_3ada78[0x72DAE4 - 0x3ADA78];
    AnmConstructedSprite layers[20];
    unsigned char reserved_732454[12];
    __declspec(noinline) SprtCtrl();
};
typedef char AnmConstructorSize[sizeof(SprtCtrl) == 0x732460 ? 1 : -1];
struct InitTask : SchedulerTask {
    InitTask() {
        on_tick = 0; on_register = 0; on_remove = 0;
        priority = 0; heap_owned = 0;
        InitializeLink(link, this);
    }
    static void InitializeLink(TaskLink& node, SchedulerTask* task) {
        node.task = task; node.next = 0; node.previous = 0;
    }
};
extern "C" FuncCtrl* g_func_ctrl;
inline void __fastcall Entity_Init(void* unused, Entity* sprite);
struct InitDevice;
typedef long (__stdcall *SetSoftwareVertexProcessing)(InitDevice*, int);
struct InitDeviceMethods { void* reserved[92]; SetSoftwareVertexProcessing software_vertex_processing; };
struct InitDevice { InitDeviceMethods* methods; };
extern "C" InitDevice* g_d3d_device;
inline void AddPrimaryTask(void* owner, TaskRoutine callback, int priority) {
    SchedulerTask* task = new InitTask;
    task->on_tick = callback; task->on_register = 0; task->on_remove = 0;
    task->context = owner; task->heap_owned = 1; task->reserved_flags |= 1;
    FuncCtrl_RegisterPrimary(g_func_ctrl, task, priority);
}
inline void AddSecondaryTask(void* owner, TaskRoutine callback, int priority) {
    SchedulerTask* task = new InitTask;
    task->on_tick = callback; task->on_register = 0; task->on_remove = 0;
    task->context = owner; task->heap_owned = 1; task->reserved_flags |= 1;
    FuncCtrl_RegisterSecondary(g_func_ctrl, task, priority);
}
extern "C" int __fastcall AnmCallback_004485d0(void*);
extern "C" int __fastcall AnmCallback_004485e0(void*);
extern "C" int __fastcall AnmCallback_004485f0(void*);
extern "C" int __fastcall AnmCallback_00448600(void*);
extern "C" int __fastcall AnmCallback_00448610(void*);
extern "C" int __fastcall AnmCallback_00448620(void*);
extern "C" int __fastcall AnmCallback_004486a0(void*);
extern "C" int __fastcall AnmCallback_004486b0(void*);
extern "C" int __fastcall AnmCallback_004486c0(void*);
extern "C" int __fastcall AnmCallback_004486d0(void*);
extern "C" int __fastcall AnmCallback_004486e0(void*);
extern "C" int __fastcall AnmCallback_004486f0(void*);
extern "C" int __fastcall AnmCallback_00448700(void*);
extern "C" int __fastcall AnmCallback_00448710(void*);
extern "C" int __fastcall AnmCallback_00448720(void*);
extern "C" int __fastcall AnmCallback_00448730(void*);
extern "C" int __fastcall AnmCallback_00448740(void*);
extern "C" int __fastcall AnmCallback_00448770(void*);
extern "C" int __fastcall AnmCallback_004487c0(void*);
extern "C" int __fastcall AnmCallback_00448810(void*);
extern "C" float matrix_004978b4;
extern "C" float matrix_0049789c;
extern "C" float matrix_00497884;
extern "C" float matrix_0049786c;
extern "C" float matrix_00497870;
extern "C" float matrix_00497874;
extern "C" float matrix_00497888;
extern "C" float matrix_0049788c;
extern "C" float matrix_004978a0;
extern "C" float matrix_004978a4;
extern "C" float matrix_004978b8;
extern "C" float matrix_004978bc;
extern "C" float matrix_00497920;
extern "C" float matrix_00497904;
extern "C" float matrix_004978e8;
extern "C" float matrix_004978cc;
extern "C" float matrix_004978d4;
extern "C" float matrix_004978d8;
extern "C" float matrix_004978f0;
extern "C" float matrix_004978f4;
extern "C" float matrix_0049790c;
extern "C" float matrix_00497910;
extern "C" float matrix_00497928;
extern "C" float matrix_0049792c;
#pragma code_seg(".text$01construct")
SprtCtrl::SprtCtrl() {
    memset(this, 0, sizeof(*this));
    matrix_004978b4 = 1.0f;
    matrix_0049789c = 1.0f;
    matrix_00497884 = 1.0f;
    matrix_0049786c = 1.0f;
    matrix_00497870 = 0.0f;
    matrix_00497874 = 0.0f;
    matrix_00497888 = 1.0f;
    matrix_0049788c = 0.0f;
    matrix_004978a0 = 0.0f;
    matrix_004978a4 = 1.0f;
    matrix_004978b8 = 1.0f;
    matrix_004978bc = 1.0f;
    matrix_00497920 = 1.0f;
    matrix_00497904 = 1.0f;
    matrix_004978e8 = 1.0f;
    matrix_004978cc = 1.0f;
    matrix_004978d4 = 0.0f;
    matrix_004978d8 = 0.0f;
    matrix_004978f0 = 1.0f;
    matrix_004978f4 = 0.0f;
    matrix_0049790c = 0.0f;
    matrix_00497910 = 1.0f;
    matrix_00497928 = 1.0f;
    matrix_0049792c = 1.0f;
    unknown_3ada74 = 0; counter = 0;
    flags[0] = 0; flags[1] = 0; state = 1;
    flags[2] = 0; marker = 0xFF; flags[3] = 0;
    second_id = -1; first_id = -1;
    AnmConstructedSprite* sprite = pool;
    int remaining = 4096;
    do { Entity_Init(0, sprite); ++sprite; } while (--remaining);
    AddPrimaryTask(this, AnmCallback_004485d0, 26);
    AddPrimaryTask(this, AnmCallback_004485e0, 8);
    AddSecondaryTask(this, AnmCallback_004485f0, 9);
    AddSecondaryTask(this, AnmCallback_00448600, 11);
    AddSecondaryTask(this, AnmCallback_00448610, 13);
    AddSecondaryTask(this, AnmCallback_00448620, 15);
    AddSecondaryTask(this, AnmCallback_004486a0, 16);
    AddSecondaryTask(this, AnmCallback_004486b0, 17);
    AddSecondaryTask(this, AnmCallback_004486c0, 18);
    AddSecondaryTask(this, AnmCallback_004486d0, 19);
    AddSecondaryTask(this, AnmCallback_004486e0, 21);
    AddSecondaryTask(this, AnmCallback_004486f0, 23);
    AddSecondaryTask(this, AnmCallback_00448700, 24);
    AddSecondaryTask(this, AnmCallback_00448710, 26);
    AddSecondaryTask(this, AnmCallback_00448720, 28);
    AddSecondaryTask(this, AnmCallback_00448730, 33);
    AddSecondaryTask(this, AnmCallback_00448740, 36);
    AddSecondaryTask(this, AnmCallback_00448770, 41);
    AddSecondaryTask(this, AnmCallback_004487c0, 42);
    AddSecondaryTask(this, AnmCallback_00448810, 45);
    InitDevice* device = g_d3d_device;
    device->methods->software_vertex_processing(device, 0);
}
#pragma code_seg()
