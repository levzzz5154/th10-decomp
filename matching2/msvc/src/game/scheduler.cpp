#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchDummy_00420c00() {
    __asm {
    L_00420c00:
        test byte ptr [data_00491d78],10h
    L_00420c07:
        mov edx,46DF98h
    L_00420c0c:
        push 0
    L_00420c0e:
        mov eax,492590h
    L_00420c13:
        je short L_00420c1f
    L_00420c15:
        push 4
    L_00420c17:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c1c:
        xor eax,eax
    L_00420c1e:
        ret
    L_00420c1f:
        push 3
    L_00420c21:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420c26:
        xor eax,eax
    L_00420c28:
        ret
    }
}

// 0x00421F60..0x00421F7B: ?GameState_UpdateFrameMaximum@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_UpdateFrameMaximum_00421f60() {
    __asm {
    L_00421f60:
        mov ecx,dword ptr [data_00474c44]
    L_00421f66:
        mov dword ptr [eax+9E78h],ecx
    L_00421f6c:
        mov eax,ecx
    L_00421f6e:
        cmp dword ptr [data_00474c40],eax
    L_00421f74:
        jge short L_00421f7b
    L_00421f76:
        mov dword ptr [data_00474c40],eax
    L_00421f7b:
        ret
    }
}

// 0x00422C30..0x00422C79: ?GameState_Unpause@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_Unpause_00422c30() {
    __asm {
    L_00422c30:
        mov eax,dword ptr [data_00477810]
    L_00422c35:
        mov ecx,dword ptr [eax+58h]
    L_00422c38:
        and ecx,0FFFFFFEFh
    L_00422c3b:
        push 0
    L_00422c3d:
        mov dword ptr [eax+58h],ecx
    L_00422c40:
        push 7
    L_00422c42:
        mov edx,46E0B8h
    L_00422c47:
        mov eax,492590h
    L_00422c4c:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00422c51:
        mov eax,dword ptr [esi+1DCh]
    L_00422c57:
        mov edx,dword ptr [data_00491c10]
    L_00422c5d:
        push eax
    L_00422c5e:
        call asm_AnimationManager_SetFlag_004492a0
    L_00422c63:
        mov dword ptr [esi+1DCh],0
    L_00422c6d:
        mov ecx,dword ptr [esi+2C0h]
    L_00422c73:
        mov dword ptr [data_00476f78],ecx
    L_00422c79:
        ret
    }
}

// 0x0042C730..0x0042C74A: ?GameState_DispatchAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlot_0042c730() {
    __asm {
    L_0042c730:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c737:
        push edi
    L_0042c738:
        push edx
    L_0042c739:
        mov edx,dword ptr [data_00491c10]
    L_0042c73f:
        mov edi,2
    L_0042c744:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c749:
        pop edi
    L_0042c74a:
        ret
    }
}

// 0x0042C750..0x0042C76A: ?GameState_DispatchAnimationSlotSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_DispatchAnimationSlotSecondary_0042c750() {
    __asm {
    L_0042c750:
        mov edx,dword ptr [eax+ecx*4+2C4h]
    L_0042c757:
        push edi
    L_0042c758:
        push edx
    L_0042c759:
        mov edx,dword ptr [data_00491c10]
    L_0042c75f:
        mov edi,3
    L_0042c764:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_0042c769:
        pop edi
    L_0042c76a:
        ret
    }
}

#include "th10/game/scheduler.hpp"
#include "th10/platform/thread_sync.hpp"

struct SchedulerTaskRaw_00449c00 {
    int priority;
    unsigned int flags;
    TaskRoutine on_tick;
    TaskRoutine on_register;
    TaskRoutine on_remove;
    TaskLink link;
    void* context;
};

static SchedulerTaskRaw_00449c00* raw_task_00449c00(TaskLink* link) {
    return (SchedulerTaskRaw_00449c00*)link->task;
}

// 0x00449C00..0x00449D33: FUN_00449c00 and compiler-local switch table
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00449c00_00449c00() {
    __asm {
    L_00449c00:
        sub esp,8
    L_00449c03:
        push ebx
    L_00449c04:
        mov ebx,dword ptr [data_004660b0]
    L_00449c0a:
        push ebp
    L_00449c0b:
        push esi
    L_00449c0c:
        push edi
    L_00449c0d:
        push 492274h
    L_00449c12:
        call ebx
    L_00449c14:
        mov al,byte ptr [data_0049231c]
    L_00449c19:
        mov ebp,dword ptr [data_004660b4]
    L_00449c1f:
        inc al
    L_00449c21:
        mov byte ptr [data_0049231c],al
    L_00449c26:
        TH10_REL8(0xeb, 0x00449c26, VA_asm_FUN_00449c00_part_00449c30)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_00449c30:
        mov eax,dword ptr [esp+1Ch]
    L_00449c34:
        mov eax,dword ptr [eax+18h]
    L_00449c37:
        mov dword ptr [esp+10h],0
    L_00449c3f:
        nop
    L_00449c40:
        test eax,eax
    L_00449c42:
        je asm_target_00449cf0
    L_00449c48:
        mov ecx,dword ptr [eax+4]
    L_00449c4b:
        mov esi,dword ptr [eax]
    L_00449c4d:
        mov eax,dword ptr [esi+8]
    L_00449c50:
        test eax,eax
    L_00449c52:
        mov dword ptr [esp+14h],ecx
    L_00449c56:
        je short L_00449ccb
    L_00449c58:
        test byte ptr [esi+4],2
    L_00449c5c:
        je short L_00449cc7
    L_00449c5e:
        mov edi,edi
    L_00449c60:
        push 492274h
    L_00449c65:
        call ebp
    L_00449c67:
        dec byte ptr [data_0049231c]
    L_00449c6d:
        mov ecx,dword ptr [esi+20h]
    L_00449c70:
        call dword ptr [esi+8]
    L_00449c73:
        push 492274h
    L_00449c78:
        mov edi,eax
    L_00449c7a:
        call ebx
    L_00449c7c:
        mov cl,byte ptr [data_0049231c]
    L_00449c82:
        inc cl
    L_00449c84:
        cmp edi,7
    L_00449c87:
        mov byte ptr [data_0049231c],cl
    L_00449c8d:
        ja short L_00449cc7
    L_00449c8f:
        jmp dword ptr [edi*4+449D14h]
    L_00449c96:
        test byte ptr [esi+4],2
    L_00449c9a:
        jne short L_00449c60
    L_00449c9c:
        inc dword ptr [esp+10h]
    L_00449ca0:
        mov eax,dword ptr [esp+14h]
    L_00449ca4:
        jmp short L_00449c40
    L_00449ca6:
        mov edx,dword ptr [esp+1Ch]
    L_00449caa:
        mov ecx,esi
    L_00449cac:
        call asm_Scheduler_Remove_00449f60
    L_00449cb1:
        inc dword ptr [esp+10h]
    L_00449cb5:
        mov eax,dword ptr [esp+14h]
    L_00449cb9:
        jmp short L_00449c40
    L_00449cbb:
        mov eax,dword ptr [esi+10h]
    L_00449cbe:
        test eax,eax
    L_00449cc0:
        je short L_00449cc7
    L_00449cc2:
        mov ecx,dword ptr [esi+20h]
    L_00449cc5:
        call eax
    L_00449cc7:
        inc dword ptr [esp+10h]
    L_00449ccb:
        mov eax,dword ptr [esp+14h]
    L_00449ccf:
        jmp asm_target_00449c40
    L_00449cd4:
        mov dword ptr [esp+10h],0
    L_00449cdc:
        jmp short L_00449cf0
    L_00449cde:
        mov dword ptr [esp+10h],1
    L_00449ce6:
        jmp short L_00449cf0
    L_00449ce8:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_00449cf0:
        push 492274h
    L_00449cf5:
        call ebp
    L_00449cf7:
        mov al,byte ptr [data_0049231c]
    L_00449cfc:
        pop edi
    L_00449cfd:
        pop esi
    L_00449cfe:
        dec al
    L_00449d00:
        pop ebp
    L_00449d01:
        mov byte ptr [data_0049231c],al
    L_00449d06:
        mov eax,dword ptr [esp+4]
    L_00449d0a:
        pop ebx
    L_00449d0b:
        add esp,8
    L_00449d0e:
        ret 4
        // Compiler-local alignment and switch table, part of this /Gy contribution.
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0xa6
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0xc7
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0x96
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0xde
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0xd4
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0xe8
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0x30
        _emit 0x9c
        _emit 0x44
        _emit 0x00
        _emit 0xbb
        _emit 0x9c
        _emit 0x44
        _emit 0x00
    }
}

// 0x00449D40..0x00449E4B: Scheduler_RunSecondary and compiler-local switch table
extern "C" __declspec(noinline) int __stdcall Scheduler_RunSecondary_00449d40(
        Scheduler* scheduler) {
    EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
    ++g_thread_synchronization.scheduler_lock_depth;
    int processed = 0;
    TaskLink* node = scheduler->secondary.link.next;
    while (node) {
        TaskLink* next = node->next;
        SchedulerTaskRaw_00449c00* task = raw_task_00449c00(node);
        if (task->on_tick) {
repeat_secondary:
            if (task->flags & 2) {
                LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
                --g_thread_synchronization.scheduler_lock_depth;
                int result = task->on_tick(task->context);
                EnterCriticalSection(&g_thread_synchronization.critical_sections[0]);
                ++g_thread_synchronization.scheduler_lock_depth;
                switch (result) {
                case 0:
                    Scheduler_RemoveTask((SchedulerTask*)task, scheduler);
                    break;
                case 1:
                    break;
                case 2:
                    if (task->flags & 2) goto repeat_secondary;
                    break;
                case 4:
                    processed = 0;
                    goto done_secondary;
                case 3:
                    processed = 1;
                    goto done_secondary;
                case 5:
                    processed = -1;
                    goto done_secondary;
                }
            }
            ++processed;
        }
        node = next;
    }
done_secondary:
    LeaveCriticalSection(&g_thread_synchronization.critical_sections[0]);
    --g_thread_synchronization.scheduler_lock_depth;
    return processed;
}

// 0x00449ED0..0x00449F19: ?SchedulerCallback_Create@@
// The retail allocator is the project's recovered global operator new.
void* __cdecl operator new(unsigned int size);

extern "C" int* __stdcall SchedulerCallback_Create_00449ed0(
    int callback) {
    int* result;
    int final_flags;
    result = (int*)
        ::operator new(0x24);
    if (result) {
        __asm {
            mov edx, dword ptr [eax+4]
        }
        *(volatile int*)&result[2] = 0;
        *(volatile int*)&result[3] = 0;
        *(volatile int*)&result[4] = 0;
        *(volatile int*)&result[0] = 0;
        __asm {
            and edx, 0FFFFFFFEh
            mov dword ptr [eax+4], edx
        }
        result[5] = (int)result;
        result[6] = 0;
        result[7] = 0;
    } else {
        result = 0;
    }
    result[3] = 0;
    result[4] = 0;
    final_flags = *(volatile int*)&result[1] | 1;
    result[2] = callback;
    result[1] = final_flags;
    return result;
}

// 0x0044A000..0x0044A02A: ?Scheduler_CreateAndRegister@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Scheduler_CreateAndRegister_0044a000() {
    __asm {
    L_0044a000:
        push esi
    L_0044a001:
        push eax
    L_0044a002:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a007:
        mov ecx,dword ptr [esp+8]
    L_0044a00b:
        mov edx,dword ptr [data_00491be4]
    L_0044a011:
        mov esi,eax
    L_0044a013:
        mov dword ptr [esi+20h],ecx
    L_0044a016:
        mov ecx,dword ptr [esi+4]
    L_0044a019:
        or ecx,2
    L_0044a01c:
        push edx
    L_0044a01d:
        mov dword ptr [esi+4],ecx
    L_0044a020:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0044a025:
        mov eax,esi
    L_0044a027:
        pop esi
    L_0044a028:
        ret 4
    }
}

// 0x0044A030..0x0044A05A: ?Scheduler_CreateAndRegisterSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Scheduler_CreateAndRegisterSecondary_0044a030() {
    __asm {
    L_0044a030:
        push esi
    L_0044a031:
        push eax
    L_0044a032:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a037:
        mov ecx,dword ptr [esp+8]
    L_0044a03b:
        mov edx,dword ptr [data_00491be4]
    L_0044a041:
        mov esi,eax
    L_0044a043:
        mov dword ptr [esi+20h],ecx
    L_0044a046:
        mov ecx,dword ptr [esi+4]
    L_0044a049:
        or ecx,2
    L_0044a04c:
        push edx
    L_0044a04d:
        mov dword ptr [esi+4],ecx
    L_0044a050:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0044a055:
        mov eax,esi
    L_0044a057:
        pop esi
    L_0044a058:
        ret 4
    }
}
