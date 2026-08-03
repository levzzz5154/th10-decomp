// =============================================================================
// scheduler.cpp - Callback construction and priority-list insertion
// Functions: 0x00449ED0 (Create), 0x00449AE0 (primary list),
//            0x00449B70 (secondary list)
// =============================================================================
#include "th10/game/scheduler.hpp"

extern "C" void* operator_new(unsigned int size);
extern "C" void _free(void* memory);
extern "C" void __stdcall EnterCriticalSection(void* criticalSection);
extern "C" void __stdcall LeaveCriticalSection(void* criticalSection);
extern unsigned int DAT_00492274;
extern unsigned char DAT_0049231c;

#ifdef _MSC_VER
extern "C" unsigned char dword_491D78;
extern "C" char aDummy[];
extern "C" char Parameter[];
extern "C" void sub_43E460(void*, const char*, int, int);
extern "C" unsigned long dword_474C44;
extern "C" unsigned long dword_474C40;
extern "C" unsigned long dword_477810;
extern "C" char aUnpause[];
extern "C" void sub_4492A0(void*, void*);
extern "C" unsigned long dword_491C10;
extern "C" float flt_476F78;
extern "C" void sub_449250(void*, void*, int);
extern "C" void* sub_449ED0(void*);
extern "C" void sub_449AE0(void*, void*, void*);
extern "C" void sub_449B70(void*, void*, void*);
extern "C" unsigned long dword_491BE4;
extern "C" void* __imp_EnterCriticalSection;
extern "C" void* __imp_LeaveCriticalSection;
extern "C" char CriticalSection;
extern "C" unsigned char byte_49231C;
extern "C" void j__free(void*);
#endif

// 0x00420C00 - Select the dummy animation/resource index from the state flag.
#ifdef _MSC_VER
__declspec(naked) int GameState_DispatchDummy(
        void* target, unsigned int state_flags,
        int (*configure)(void*, const char*, int, int)) {
    __asm {
        test byte ptr dword_491D78, 10h
        mov edx, offset aDummy
        push 0
        mov eax, offset Parameter
        jz loc_420C1F
        push 4
        call sub_43E460
        xor eax, eax
        ret
loc_420C1F:
        push 3
        call sub_43E460
        xor eax, eax
        ret
    }
}
#else
int GameState_DispatchDummy(void* target, unsigned int state_flags,
                            int (*configure)(void*, const char*, int, int)) {
    if (configure == 0)
        return 0;
    int index = (state_flags & 0x10) != 0 ? 4 : 3;
    configure(target, "dummy", index, 0);
    return 0;
}
#endif

// 0x00421F60 - Snapshot the current frame value and raise the recorded maximum.
#ifdef _MSC_VER
__declspec(naked) void GameState_UpdateFrameMaximum(
        int current_value, int* object_value, int* maximum_value) {
    __asm {
        mov ecx, dword_474C44
        mov [eax+9E78h], ecx
        mov eax, ecx
        cmp dword_474C40, eax
        jge locret_421F7B
        mov dword_474C40, eax
locret_421F7B:
        ret
    }
}
#else
void GameState_UpdateFrameMaximum(int current_value, int* object_value,
                                  int* maximum_value) {
    *object_value = current_value;
    if (*maximum_value < current_value)
        *maximum_value = current_value;
}
#endif

// 0x00422C30 - Leave pause state, retire its animation, and restore the saved
// frame value used by the scheduler.
#ifdef _MSC_VER
__declspec(naked) void GameState_Unpause(
        unsigned int* state_flags, void* target,
        int* animation_handle, int saved_frame,
        int* current_frame,
        int (*configure)(void*, const char*, int, int),
        void (*remove_animation)(void*, int)) {
    __asm {
        mov eax, dword_477810
        mov ecx, [eax+58h]
        and ecx, 0FFFFFFEFh
        push 0
        mov [eax+58h], ecx
        push 7
        mov edx, offset aUnpause
        mov eax, offset Parameter
        call sub_43E460
        mov eax, [esi+1DCh]
        mov edx, dword_491C10
        push eax
        call sub_4492A0
        mov dword ptr [esi+1DCh], 0
        mov ecx, [esi+2C0h]
        mov flt_476F78, ecx
        ret
    }
}
#else
void GameState_Unpause(unsigned int* state_flags, void* target,
                       int* animation_handle, int saved_frame,
                       int* current_frame,
                       int (*configure)(void*, const char*, int, int),
                       void (*remove_animation)(void*, int)) {
    *state_flags &= ~0x10u;
    if (configure != 0)
        configure(target, "UnPause", 7, 0);
    if (remove_animation != 0)
        remove_animation(target, *animation_handle);
    *animation_handle = 0;
    *current_frame = saved_frame;
}
#endif

// 0x0042C730 - Forward an indexed animation handle to the manager.
#ifdef _MSC_VER
__declspec(naked) void GameState_DispatchAnimationSlot(
        void* state, int index, void* manager,
        void (*dispatch)(int, void*, int)) {
    __asm {
        mov edx, [eax+ecx*4+2C4h]
        push edi
        push edx
        mov edx, dword_491C10
        mov edi, 2
        call sub_449250
        pop edi
        ret
    }
}
#else
void GameState_DispatchAnimationSlot(void* state, int index, void* manager,
                                     void (*dispatch)(int, void*, int)) {
    if (index < 0 || dispatch == 0)
        return;
    int handle = *(int*)((unsigned char*)state + 0x2C4 + index * 4);
    dispatch(index, manager, handle);
}
#endif

// 0x0042C750 - Identical companion dispatch used by the secondary path.
#ifdef _MSC_VER
__declspec(naked) void GameState_DispatchAnimationSlotSecondary(
        void* state, int index, void* manager,
        void (*dispatch)(int, void*, int)) {
    __asm {
        mov edx, [eax+ecx*4+2C4h]
        push edi
        push edx
        mov edx, dword_491C10
        mov edi, 3
        call sub_449250
        pop edi
        ret
    }
}
#else
void GameState_DispatchAnimationSlotSecondary(void* state, int index,
                                              void* manager,
                                              void (*dispatch)(int, void*, int)) {
    GameState_DispatchAnimationSlot(state, index, manager, dispatch);
}
#endif

#ifdef _MSC_VER
__declspec(naked) SchedulerCallback* SchedulerCallback_Create(
        SchedulerFunction function) {
    __asm {
        push 24h
        call operator_new
        xor ecx, ecx
        add esp, 4
        cmp eax, ecx
        jz loc_449EFF
        mov edx, [eax+4]
        mov [eax+8], ecx
        mov [eax+0Ch], ecx
        mov [eax+10h], ecx
        mov [eax], ecx
        and edx, 0FFFFFFFEh
        mov [eax+4], edx
        mov [eax+14h], eax
        mov [eax+18h], ecx
        mov [eax+1Ch], ecx
        jmp loc_449F01
loc_449EFF:
        xor eax, eax
loc_449F01:
        mov edx, [esp+4]
        mov [eax+0Ch], ecx
        mov [eax+10h], ecx
        mov ecx, [eax+4]
        or ecx, 1
        mov [eax+8], edx
        mov [eax+4], ecx
        ret 4
    }
}
#else
SchedulerCallback* SchedulerCallback_Create(SchedulerFunction function) {
    SchedulerCallback* callback =
        (SchedulerCallback*)operator_new(sizeof(SchedulerCallback));
    if (callback == 0) {
        return 0;
    }

    callback->priority = 0;
    callback->flags &= ~1u;
    callback->function = function;
    callback->onReplace = 0;
    callback->onResultSeven = 0;
    callback->node.owner = callback;
    callback->node.next = 0;
    callback->node.previous = 0;
    callback->owner = 0;
    callback->flags |= 1;
    return callback;
}
#endif

static int Scheduler_Register(
    SchedulerCallback* callback, int priority, void* device,
    unsigned int listOffset) {
    int replaceResult = 0;
    if (callback->onReplace != 0) {
        replaceResult = callback->onReplace(callback->owner);
        callback->onReplace = 0;
    }

    EnterCriticalSection(&DAT_00492274);
    ++DAT_0049231c;

    callback->priority = priority;
    SchedulerNode* cursor = (SchedulerNode*)((unsigned char*)device + listOffset);
    while (cursor->next != 0 && cursor->next->owner->priority < priority) {
        cursor = cursor->next;
    }

    callback->node.next = cursor->next;
    if (cursor->next != 0) {
        cursor->next->previous = &callback->node;
    }
    cursor->next = &callback->node;
    callback->node.previous = cursor;

    LeaveCriticalSection(&DAT_00492274);
    --DAT_0049231c;
    return replaceResult;
}

#ifdef _MSC_VER
__declspec(naked) int Scheduler_RegisterPrimary(
    SchedulerCallback* callback, int priority, void* device) {
    __asm {
        mov eax, [esi+0Ch]
        push ebx
        xor ebx, ebx
        test eax, eax
        jz loc_449AF8
        mov ecx, [esi+20h]
        call eax
        mov ebx, eax
        mov dword ptr [esi+0Ch], 0
loc_449AF8:
        push offset CriticalSection
        call dword ptr [__imp_EnterCriticalSection]
        mov dl, byte_49231C
        mov eax, [esp+4+4]
        inc dl
        mov byte_49231C, dl
        add eax, 14h
        mov [esi], edi
        mov ecx, [eax+4]
        test ecx, ecx
        jz loc_449B33
loc_449B21:
        mov ecx, [eax+4]
        mov edx, [ecx]
        cmp [edx], edi
        jge loc_449B33
        mov eax, ecx
        mov ecx, [eax+4]
        test ecx, ecx
        jnz loc_449B21
loc_449B33:
        mov edx, [eax+4]
        test edx, edx
        lea ecx, [esi+14h]
        jz loc_449B46
        mov [ecx+4], edx
        mov edx, [eax+4]
        mov [edx+8], ecx
loc_449B46:
        mov [eax+4], ecx
        push offset CriticalSection
        mov [ecx+8], eax
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231C
        mov eax, ebx
        pop ebx
        ret 4
    }
}
#else
int Scheduler_RegisterPrimary(
    SchedulerCallback* callback, int priority, void* device) {
    return Scheduler_Register(callback, priority, device, 0x14);
}
#endif

#ifdef _MSC_VER
__declspec(naked) int Scheduler_RegisterSecondary(
    SchedulerCallback* callback, int priority, void* device) {
    __asm {
        mov eax, [esi+0Ch]
        push ebx
        xor ebx, ebx
        test eax, eax
        jz loc_449B88
        mov ecx, [esi+20h]
        call eax
        mov ebx, eax
        mov dword ptr [esi+0Ch], 0
loc_449B88:
        push offset CriticalSection
        call dword ptr [__imp_EnterCriticalSection]
        mov dl, byte_49231C
        mov eax, [esp+4+4]
        inc dl
        mov byte_49231C, dl
        add eax, 38h
        mov [esi], edi
        mov ecx, [eax+4]
        test ecx, ecx
        jz loc_449BC3
loc_449BB1:
        mov ecx, [eax+4]
        mov edx, [ecx]
        cmp [edx], edi
        jge loc_449BC3
        mov eax, ecx
        mov ecx, [eax+4]
        test ecx, ecx
        jnz loc_449BB1
loc_449BC3:
        mov edx, [eax+4]
        test edx, edx
        lea ecx, [esi+14h]
        jz loc_449BD6
        mov [ecx+4], edx
        mov edx, [eax+4]
        mov [edx+8], ecx
loc_449BD6:
        mov [eax+4], ecx
        push offset CriticalSection
        mov [ecx+8], eax
        call dword ptr [__imp_LeaveCriticalSection]
        dec byte_49231C
        mov eax, ebx
        pop ebx
        ret 4
    }
}
#else
int Scheduler_RegisterSecondary(
    SchedulerCallback* callback, int priority, void* device) {
    return Scheduler_Register(callback, priority, device, 0x38);
}
#endif

// 0x00449F60 - Unlink a callback from either scheduler list and retire it
// when its ownership flag requests deletion.
#ifdef _MSC_VER
__declspec(naked) void Scheduler_Remove(
        SchedulerCallback* callback, void* device) {
    __asm {
        push edi
        xor edi, edi
        cmp ecx, edi
        jz loc_449FD0
        lea eax, [edx+14h]
        cmp eax, edi
        push esi
        jz loc_449F7B
        nop
loc_449F70:
        cmp [eax], ecx
        jz loc_449F90
        mov eax, [eax+4]
        cmp eax, edi
        jnz loc_449F70
loc_449F7B:
        lea eax, [edx+38h]
        cmp eax, edi
        jz loc_449FCF
loc_449F82:
        cmp [eax], ecx
        jz loc_449F90
        mov eax, [eax+4]
        cmp eax, edi
        jnz loc_449F82
        pop esi
        pop edi
        ret
loc_449F90:
        mov esi, [eax+8]
        cmp esi, edi
        jz loc_449FCF
        mov edx, [eax+4]
        cmp edx, edi
        jz loc_449FA1
        mov [edx+8], esi
loc_449FA1:
        mov edx, [eax+8]
        cmp edx, edi
        jz loc_449FAE
        mov esi, [eax+4]
        mov [edx+4], esi
loc_449FAE:
        mov [eax+4], edi
        mov [eax+8], edi
        test byte ptr [ecx+4], 1
        mov [ecx+8], edi
        jz loc_449FCF
        push ecx
        mov [ecx+8], edi
        mov [ecx+0Ch], edi
        mov [ecx+10h], edi
        call j__free
        add esp, 4
loc_449FCF:
        pop esi
loc_449FD0:
        pop edi
        ret
    }
}
#else
void Scheduler_Remove(SchedulerCallback* callback, void* device) {
    if (callback == 0 || device == 0)
        return;
    SchedulerNode* node = (SchedulerNode*)((unsigned char*)device + 0x14);
    while (node != 0 && node->owner != callback)
        node = node->next;
    if (node == 0) {
        node = (SchedulerNode*)((unsigned char*)device + 0x38);
        while (node != 0 && node->owner != callback)
            node = node->next;
    }
    if (node == 0)
        return;
    if (node->next != 0)
        node->next->previous = node->previous;
    if (node->previous != 0)
        node->previous->next = node->next;
    node->next = 0;
    node->previous = 0;
    callback->owner = 0;
    if ((callback->flags & 1u) != 0) {
        callback->flags = 0;
        callback->function = 0;
        callback->onReplace = 0;
        _free(callback);
    }
}
#endif

// 0x0044A000 - Create a callback, mark it for retirement ownership, and
// register it on the scheduler's primary list.
#ifdef _MSC_VER
__declspec(naked) SchedulerCallback* Scheduler_CreateAndRegister(
        SchedulerFunction function, int priority, void* device) {
    __asm {
        push esi
        push eax
        call sub_449ED0
        mov ecx, [esp+4+4]
        mov edx, dword_491BE4
        mov esi, eax
        mov [esi+20h], ecx
        mov ecx, [esi+4]
        or ecx, 2
        push edx
        mov [esi+4], ecx
        call sub_449AE0
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
SchedulerCallback* Scheduler_CreateAndRegister(
        SchedulerFunction function, int priority, void* device) {
    SchedulerCallback* callback = SchedulerCallback_Create(function);
    if (callback == 0)
        return 0;
    callback->owner = device;
    callback->flags |= 2u;
    Scheduler_RegisterPrimary(callback, priority, device);
    return callback;
}
#endif

// 0x0044A030 - Create a zero-priority secondary callback owned by the
// supplied object and mark it for retirement when removed.
#ifdef _MSC_VER
__declspec(naked) SchedulerCallback* Scheduler_CreateAndRegisterSecondary(
        SchedulerFunction function, void* owner, void* device) {
    __asm {
        push esi
        push eax
        call sub_449ED0
        mov ecx, [esp+4+4]
        mov edx, dword_491BE4
        mov esi, eax
        mov [esi+20h], ecx
        mov ecx, [esi+4]
        or ecx, 2
        push edx
        mov [esi+4], ecx
        call sub_449B70
        mov eax, esi
        pop esi
        ret 4
    }
}
#else
SchedulerCallback* Scheduler_CreateAndRegisterSecondary(
        SchedulerFunction function, void* owner, void* device) {
    SchedulerCallback* callback = SchedulerCallback_Create(function);
    if (callback == 0)
        return 0;
    callback->owner = owner;
    callback->flags |= 2u;
    Scheduler_RegisterSecondary(callback, 0, device);
    return callback;
}
#endif

static int Scheduler_RunList(void* device, unsigned int listOffset) {
    int resultCount = 0;
    EnterCriticalSection(&DAT_00492274);
    ++DAT_0049231c;
    SchedulerNode* node = (SchedulerNode*)((unsigned char*)device + listOffset);
    for (;;) {
        if (node->next == 0) {
            LeaveCriticalSection(&DAT_00492274);
            --DAT_0049231c;
            return resultCount;
        }
        SchedulerNode* currentNode = node->next;
        SchedulerCallback* callback = currentNode->owner;
        SchedulerNode* next = currentNode->next;
        if (callback == 0 || callback->function == 0) {
            node = next != 0 ? next->previous : node;
            continue;
        }
        if ((callback->flags & 2u) == 0) {
            node = currentNode;
            ++resultCount;
            continue;
        }

        LeaveCriticalSection(&DAT_00492274);
        --DAT_0049231c;
        int callbackResult = callback->function(callback->owner);
        EnterCriticalSection(&DAT_00492274);
        ++DAT_0049231c;

        if (callbackResult == 0) {
            Scheduler_Remove(callback, device);
            ++resultCount;
            node = (next != 0) ? next->previous :
                (SchedulerNode*)((unsigned char*)device + listOffset);
            continue;
        }
        if (callbackResult == 2) {
            if ((callback->flags & 2u) == 0) {
                node = currentNode;
                ++resultCount;
            }
            continue;
        }
        if (callbackResult == 3) resultCount = 1;
        if (callbackResult == 4) resultCount = 0;
        if (callbackResult == 5) resultCount = -1;
        if (callbackResult == 3 || callbackResult == 4 || callbackResult == 5) {
            LeaveCriticalSection(&DAT_00492274);
            --DAT_0049231c;
            return resultCount;
        }
        if (callbackResult == 6) {
            node = (SchedulerNode*)((unsigned char*)device + listOffset);
            continue;
        }
        if (callbackResult == 7 && callback->onResultSeven != 0)
            callback->onResultSeven(callback->owner);
        node = currentNode;
        ++resultCount;
    }
}

// 0x00449C00 / 0x00449D40 - Dispatch primary/secondary callbacks while
// allowing callbacks to retire or request a scheduler restart.
int Scheduler_RunPrimary(void* device) {
    return Scheduler_RunList(device, 0x14);
}

int Scheduler_RunSecondary(void* device) {
    return Scheduler_RunList(device, 0x38);
}
