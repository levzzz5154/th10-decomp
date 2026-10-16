// Complete pause timer/animation reset, 0x00424D90..0x00424EA0.
// Source declaration is ordinary C++; native LTCG selects the observed ESI
// owner and plain RET. The active-count dependency below is the complete
// genuine 77-byte routine at 0x00413790, not an abbreviated ABI anchor.
#include <stddef.h>
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct PauseFrameTimer {
    int previous;
    int current;
    float elapsed;
    const float* speed;
    unsigned int flags;
};
struct PauseState2 {
    unsigned char reserved_000[0x458];
    int state;
    unsigned char reserved_45c[4];
    PauseFrameTimer timers[3];
    unsigned char reserved_49c[0x329c-0x49c];
    int animation_handle;
};
typedef char PauseFrameTimerSize[sizeof(PauseFrameTimer)==0x14?1:-1];
typedef char PauseResetTimerOffset[offsetof(PauseState2,timers)==0x460?1:-1];
typedef char PauseResetHandleOffset[offsetof(PauseState2,animation_handle)==0x329c?1:-1];

struct PauseAnimationRecord {
    unsigned int flags;
    unsigned char reserved_004[0x3ac-4];
};
struct PauseAnimationCountManager {
    unsigned char reserved_000[0x4cdc];
    PauseAnimationRecord records[9];
    __declspec(noinline) void SetActiveCount(int count);
};
#pragma code_seg(".text$01count")
void PauseAnimationCountManager::SetActiveCount(int count) {
    int index=0;
    for (;index<count;++index) records[index].flags|=2;
    if (index>=9) return;
    for (;index<9;++index) records[index].flags&=~2u;
}
#pragma code_seg()

struct PauseAnimationLookupContext;
// Genuine public fastcall contract: EDX contains the lookup context, one ID
// is on the stack, and the helper returns with RET4. ECX is an ignored value.
extern "C" void* __fastcall PauseMarkAnimation(
    const void* ignored_ecx, PauseAnimationLookupContext* context, int id);
extern "C" {
extern float pause_timer_speed;
extern PauseAnimationLookupContext* pause_animation_context;
extern PauseAnimationCountManager* pause_count_manager;
extern int pause_active_count;
}

#pragma code_seg(".text$03pause")
extern "C" __declspec(noinline) void __stdcall ReplayPauseReset(PauseState2* owner) {
    int* state=&owner->state;
    state[0]=1;
    unsigned int flags=owner->timers[0].flags;
    if (!(flags&1)) {
        flags|=1;
        owner->timers[0].current=0;
        owner->timers[0].previous=(int)0xfff0bdc1;
        owner->timers[0].elapsed=0;
        owner->timers[0].speed=&pause_timer_speed;
        owner->timers[0].flags=flags;
    }
    _ReadWriteBarrier();
    owner->timers[0].current=-1;
    owner->timers[0].elapsed=-1.0f;
    owner->timers[0].previous=-2;
    _ReadWriteBarrier();
    flags=owner->timers[1].flags;
    if (!(flags&1)) {
        flags|=1;
        owner->timers[1].current=0;
        owner->timers[1].previous=(int)0xfff0bdc1;
        owner->timers[1].elapsed=0;
        owner->timers[1].speed=&pause_timer_speed;
        owner->timers[1].flags=flags;
    }
    _ReadWriteBarrier();
    owner->timers[1].current=0;
    owner->timers[1].elapsed=0;
    owner->timers[1].previous=-1;
    _ReadWriteBarrier();
    flags=owner->timers[2].flags;
    if (!(flags&1)) {
        flags|=1;
        owner->timers[2].current=0;
        owner->timers[2].previous=(int)0xfff0bdc1;
        owner->timers[2].elapsed=0;
        owner->timers[2].speed=&pause_timer_speed;
        owner->timers[2].flags=flags;
    }
    _ReadWriteBarrier();
    PauseAnimationLookupContext* context=pause_animation_context;
    _ReadWriteBarrier();
    owner->timers[2].current=0;
    owner->timers[2].elapsed=0;
    owner->timers[2].previous=-1;
    _ReadWriteBarrier();
    PauseMarkAnimation(&pause_timer_speed,context,owner->animation_handle);
    PauseAnimationCountManager* manager=pause_count_manager;
    _ReadWriteBarrier();
    owner->animation_handle=0;
    _ReadWriteBarrier();
    owner->animation_handle=0;
    _ReadWriteBarrier();
    manager->SetActiveCount(pause_active_count);
}
#pragma code_seg()
