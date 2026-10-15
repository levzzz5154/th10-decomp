// 0x0040AE70..0x0040AEF5 (134 bytes) - Effect_Initialize (effect.cpp, EffectInf)
//
// Loads the effect sprites from bullet.anm, then creates and registers the two
// scheduler callbacks that drive it.  Retail keeps the manager in EBX, the
// callback under construction in ESI and the registration priority in EDI;
// those are whole-program register agreements, so this source is compiled in
// the same native-LTCG link as the scheduler registration functions it calls
// and as the constant-log formatter it reports a failure through.
#include "th10/core/func_ctrl.hpp"

struct Effect {
    unsigned flags;                 // +0x00
    unsigned reserved_004;          // +0x04
    void *primary_callback;         // +0x08
    void *secondary_callback;       // +0x0C
    void *bullet_resource;          // +0x10
    unsigned reserved_014;          // +0x14
};

struct BulletResourceCache;

// Declared here exactly as the co-compiled TextLog translation unit defines it,
// so the whole-program pass can pick the register agreement retail used.
struct TextLog_0044b810 {
    char text[0x2000];
    char *cursor;
    unsigned char dirty;
    char *Append(char *format, ...);
};

extern "C" void * __fastcall Recovery_LoadCachedResource(
        int id, BulletResourceCache *cache, const char *name);
extern "C" SchedulerTask * __stdcall SchedulerTask_Create(void *callback);
extern "C" BulletResourceCache *g_sprt_ctrl;
extern "C" FuncCtrl *g_func_ctrl;

#pragma code_seg(".text$00a_loadscripts")
extern "C" __declspec(noinline) int __stdcall Effect_Initialize(
        Effect *state) {
    void *resource = Recovery_LoadCachedResource(
            7, g_sprt_ctrl, (const char *)0x46CD88);
    state->bullet_resource = resource;
    if (!resource) {
        ((TextLog_0044b810 *)0x474F70)->Append((char *)0x46CF74);
        return -1;
    }

    SchedulerTask *primary = SchedulerTask_Create((void *)0x40B050);
    primary->reserved_flags &= ~1u;
    primary->context = state;
    FuncCtrl_RegisterPrimary(g_func_ctrl, primary, 0x17);
    state->primary_callback = primary;

    SchedulerTask *secondary = SchedulerTask_Create((void *)0x40B060);
    secondary->reserved_flags &= ~1u;
    secondary->context = state;
    FuncCtrl_RegisterSecondary(g_func_ctrl, secondary, 0x20);
    state->secondary_callback = secondary;
    return 0;
}
#pragma code_seg()
