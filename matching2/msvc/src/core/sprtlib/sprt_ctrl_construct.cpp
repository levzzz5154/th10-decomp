// 0x00445900 (2,315 bytes): animation storage constructor, with the three
// compiler-generated unwind functions at 0x00465760/0x0046577C/0x0046578A and
// the frame handler at 0x004657A5.  The sprite pool, the middle sprite and the
// layer sprites are members with real constructors and destructors.
#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/core/func_ctrl.hpp"
extern "C" void __cdecl crt_free(void*);
#pragma code_seg(".text$00d_dtor")
struct AnmConstructedSprite : Entity {
    __forceinline AnmConstructedSprite();
    __declspec(dllexport) ~AnmConstructedSprite() {
        if (resource) crt_free(resource);
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
extern "C" int __fastcall AnmCallback(void*);
extern "C" int __fastcall AnmCallback2(void*);
extern "C" int __fastcall AnmCallback3(void*);
extern "C" int __fastcall AnmCallback4(void*);
extern "C" int __fastcall AnmCallback5(void*);
extern "C" int __fastcall AnmCallback6(void*);
extern "C" int __fastcall AnmCallback7(void*);
extern "C" int __fastcall AnmCallback8(void*);
extern "C" int __fastcall AnmCallback9(void*);
extern "C" int __fastcall AnmCallback10(void*);
extern "C" int __fastcall AnmCallback11(void*);
extern "C" int __fastcall AnmCallback12(void*);
extern "C" int __fastcall AnmCallback13(void*);
extern "C" int __fastcall AnmCallback14(void*);
extern "C" int __fastcall AnmCallback15(void*);
extern "C" int __fastcall AnmCallback16(void*);
extern "C" int __fastcall AnmCallback17(void*);
extern "C" int __fastcall AnmCallback18(void*);
extern "C" int __fastcall AnmCallback19(void*);
extern "C" int __fastcall AnmCallback20(void*);
extern "C" float matrix11;
extern "C" float matrix8;
extern "C" float matrix5;
extern "C" float matrix2;
extern "C" float matrix3;
extern "C" float matrix4;
extern "C" float matrix6;
extern "C" float matrix7;
extern "C" float matrix9;
extern "C" float matrix10;
extern "C" float matrix12;
extern "C" float matrix13;
extern "C" float matrix23;
extern "C" float matrix20;
extern "C" float matrix17;
extern "C" float matrix14;
extern "C" float matrix15;
extern "C" float matrix16;
extern "C" float matrix18;
extern "C" float matrix19;
extern "C" float matrix21;
extern "C" float matrix22;
extern "C" float matrix24;
extern "C" float matrix25;
#pragma code_seg(".text$01construct")
SprtCtrl::SprtCtrl() {
    memset(this, 0, sizeof(*this));
    matrix11 = 1.0f;
    matrix8 = 1.0f;
    matrix5 = 1.0f;
    matrix2 = 1.0f;
    matrix3 = 0.0f;
    matrix4 = 0.0f;
    matrix6 = 1.0f;
    matrix7 = 0.0f;
    matrix9 = 0.0f;
    matrix10 = 1.0f;
    matrix12 = 1.0f;
    matrix13 = 1.0f;
    matrix23 = 1.0f;
    matrix20 = 1.0f;
    matrix17 = 1.0f;
    matrix14 = 1.0f;
    matrix15 = 0.0f;
    matrix16 = 0.0f;
    matrix18 = 1.0f;
    matrix19 = 0.0f;
    matrix21 = 0.0f;
    matrix22 = 1.0f;
    matrix24 = 1.0f;
    matrix25 = 1.0f;
    unknown_3ada74 = 0; counter = 0;
    flags[0] = 0; flags[1] = 0; state = 1;
    flags[2] = 0; marker = 0xFF; flags[3] = 0;
    second_id = -1; first_id = -1;
    AnmConstructedSprite* sprite = pool;
    int remaining = 4096;
    do { Entity_Init(0, sprite); ++sprite; } while (--remaining);
    AddPrimaryTask(this, AnmCallback, 26);
    AddPrimaryTask(this, AnmCallback2, 8);
    AddSecondaryTask(this, AnmCallback3, 9);
    AddSecondaryTask(this, AnmCallback4, 11);
    AddSecondaryTask(this, AnmCallback5, 13);
    AddSecondaryTask(this, AnmCallback6, 15);
    AddSecondaryTask(this, AnmCallback7, 16);
    AddSecondaryTask(this, AnmCallback8, 17);
    AddSecondaryTask(this, AnmCallback9, 18);
    AddSecondaryTask(this, AnmCallback10, 19);
    AddSecondaryTask(this, AnmCallback11, 21);
    AddSecondaryTask(this, AnmCallback12, 23);
    AddSecondaryTask(this, AnmCallback13, 24);
    AddSecondaryTask(this, AnmCallback14, 26);
    AddSecondaryTask(this, AnmCallback15, 28);
    AddSecondaryTask(this, AnmCallback16, 33);
    AddSecondaryTask(this, AnmCallback17, 36);
    AddSecondaryTask(this, AnmCallback18, 41);
    AddSecondaryTask(this, AnmCallback19, 42);
    AddSecondaryTask(this, AnmCallback20, 45);
    InitDevice* device = g_d3d_device;
    device->methods->software_vertex_processing(device, 0);
}
#pragma code_seg()
