// BLOCKED (H3901): closest_byte_count=0/330; first_diff=0x00401110;
// residual_class=private EAX entry ABI and scheduler callback/register
// conventions coupled to the resource-object layout. Retail receives the
// game-thread object in EAX, threads it through three cached-resource loads,
// then preserves it across scheduler registration and two animation setup
// calls; a public-ABI C++ translation cannot express that entry shape.
// variants_tested=["exact retail naked baseline retained",
// "IDA semantic translation reviewed; no standalone readable candidate retained"];
// next_lever=caller-inclusive native-LTCG cluster rooted by 0x00401440
// (which allocates and invokes this entry), with Recovery_LoadCachedResource,
// SchedulerCallback_Create/Register*, InitializeEntity, and
// AnimationObject_ConfigureFromResource visible in one schema-2 link.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.

// 0x00401110..0x00401259: LoadGameThreadResources
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LoadGameThreadResources_00401110() {
    __asm {
    L_00401110:
        mov edx,dword ptr [data_00491c10]
    L_00401116:
        push ebx
    L_00401117:
        push 46CB80h
    L_0040111c:
        mov ecx,2
    L_00401121:
        mov ebx,eax
    L_00401123:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401128:
        test eax,eax
    L_0040112a:
        mov dword ptr [ebx+8994h],eax
    L_00401130:
        je short L_0040116d
    L_00401132:
        mov edx,dword ptr [data_00491c10]
    L_00401138:
        push 46CB5Ch
    L_0040113d:
        xor ecx,ecx
    L_0040113f:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401144:
        test eax,eax
    L_00401146:
        mov dword ptr [ebx+899Ch],eax
    L_0040114c:
        je short L_0040116d
    L_0040114e:
        mov edx,dword ptr [data_00491c10]
    L_00401154:
        push 46CB50h
    L_00401159:
        mov ecx,3
    L_0040115e:
        call asm_Recovery_LoadCachedResource_00447280
    L_00401163:
        test eax,eax
    L_00401165:
        mov dword ptr [ebx+8998h],eax
    L_0040116b:
        jne short L_00401184
    L_0040116d:
        push 46CB68h
    L_00401172:
        mov ecx,474F70h
    L_00401177:
        call asm_TextLog_Append_0044b810
    L_0040117c:
        add esp,4
    L_0040117f:
        or eax,0FFFFFFFFh
    L_00401182:
        pop ebx
    L_00401183:
        ret
    L_00401184:
        push esi
    L_00401185:
        push edi
    L_00401186:
        push 4014F0h
    L_0040118b:
        call asm_SchedulerCallback_Create_00449ed0
    L_00401190:
        mov esi,eax
    L_00401192:
        mov edi,dword ptr [esi+4]
    L_00401195:
        mov eax,dword ptr [data_00491be4]
    L_0040119a:
        and edi,0FFFFFFFDh
    L_0040119d:
        mov dword ptr [esi+4],edi
    L_004011a0:
        push eax
    L_004011a1:
        mov edi,4
    L_004011a6:
        mov dword ptr [esi+20h],ebx
    L_004011a9:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004011ae:
        push 401510h
    L_004011b3:
        mov dword ptr [ebx+0Ch],esi
    L_004011b6:
        call asm_SchedulerCallback_Create_00449ed0
    L_004011bb:
        mov ecx,dword ptr [data_00491be4]
    L_004011c1:
        mov esi,eax
    L_004011c3:
        mov eax,dword ptr [esi+4]
    L_004011c6:
        and eax,0FFFFFFFDh
    L_004011c9:
        push ecx
    L_004011ca:
        mov edi,30h
    L_004011cf:
        mov dword ptr [esi+20h],ebx
    L_004011d2:
        mov dword ptr [esi+4],eax
    L_004011d5:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004011da:
        push 401520h
    L_004011df:
        mov dword ptr [ebx+10h],esi
    L_004011e2:
        call asm_SchedulerCallback_Create_00449ed0
    L_004011e7:
        mov edx,dword ptr [data_00491be4]
    L_004011ed:
        mov esi,eax
    L_004011ef:
        mov ecx,dword ptr [esi+4]
    L_004011f2:
        and ecx,0FFFFFFFDh
    L_004011f5:
        push edx
    L_004011f6:
        mov edi,26h
    L_004011fb:
        mov dword ptr [esi+20h],ebx
    L_004011fe:
        mov dword ptr [esi+4],ecx
    L_00401201:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00401206:
        mov edi,dword ptr [ebx+8994h]
    L_0040120c:
        mov dword ptr [ebx+89A8h],esi
    L_00401212:
        lea esi,[ebx+14h]
    L_00401215:
        mov edx,esi
    L_00401217:
        call asm_InitializeEntity_00401de0
    L_0040121c:
        xor edx,edx
    L_0040121e:
        mov eax,esi
    L_00401220:
        mov ecx,edi
    L_00401222:
        mov dword ptr [esi+308h],edi
    L_00401228:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0040122d:
        lea esi,[ebx+3C0h]
    L_00401233:
        mov ebx,dword ptr [ebx+8994h]
    L_00401239:
        mov edx,esi
    L_0040123b:
        call asm_InitializeEntity_00401de0
    L_00401240:
        mov edx,62h
    L_00401245:
        mov eax,esi
    L_00401247:
        mov ecx,ebx
    L_00401249:
        mov dword ptr [esi+308h],ebx
    L_0040124f:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00401254:
        pop edi
    L_00401255:
        pop esi
    L_00401256:
        xor eax,eax
    L_00401258:
        pop ebx
    L_00401259:
        ret
    }
}
