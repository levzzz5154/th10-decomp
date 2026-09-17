#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

void __cdecl operator delete(void*);
void* __cdecl operator new(unsigned int size);
extern "C" __declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE handle);

// The raw-pair release still lives in inline assembly, so it is called through its
// fixed retail prototype (one stack argument, callee cleans).
typedef void (__stdcall* RawPairReleaseFn)(void* pair);
// CRT heap release reached by the state teardown below.
extern "C" void __cdecl entry_free_004524a1(void* memory);

// 0x00401520..0x00401529: GameThread_RunQueueLeaf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_RunQueueLeaf_00401520() {
    __asm {
    L_00401520:
        push ebx
    L_00401521:
        mov ebx,ecx
    L_00401523:
        call asm_FUN_00401a50_00401a50
    L_00401528:
        pop ebx
    L_00401529:
        ret
    }
}
// 0x00405040..0x0040509D: Recovery_InitializeWordColor
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeWordColor_00405040() {
    __asm {
    L_00405040:
        mov eax,dword ptr [esp+4]
    L_00405044:
        fld dword ptr [esp+0Ch]
    L_00405048:
        mov ecx,dword ptr [esp+8]
    L_0040504c:
        mov edx,dword ptr [esp+0Ch]
    L_00405050:
        mov dword ptr [esi],eax
    L_00405052:
        mov eax,dword ptr [esp+10h]
    L_00405056:
        mov dword ptr [esi+4],ecx
    L_00405059:
        mov ecx,dword ptr [esp+14h]
    L_0040505d:
        mov dword ptr [esi+8],edx
    L_00405060:
        mov edx,dword ptr [esp+18h]
    L_00405064:
        mov dword ptr [esi+0Ch],eax
    L_00405067:
        mov dword ptr [esi+10h],ecx
    L_0040506a:
        mov dword ptr [esi+14h],edx
    L_0040506d:
        call asm_FUN_00463b2c_00463b2c
    L_00405072:
        fld dword ptr [esp+10h]
    L_00405076:
        mov byte ptr [esi+18h],al
    L_00405079:
        call asm_FUN_00463b2c_00463b2c
    L_0040507e:
        fld dword ptr [esp+14h]
    L_00405082:
        mov byte ptr [esi+19h],al
    L_00405085:
        call asm_FUN_00463b2c_00463b2c
    L_0040508a:
        fld dword ptr [esp+18h]
    L_0040508e:
        mov byte ptr [esi+1Ah],al
    L_00405091:
        call asm_FUN_00463b2c_00463b2c
    L_00405096:
        mov byte ptr [esi+1Bh],al
    L_00405099:
        mov eax,esi
    L_0040509b:
        ret 18h
    }
}

// 0x004056B0..0x00405704: Recovery_CreateFixedState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateFixedState_004056b0() {
    __asm {
    L_004056b0:
        push ebx
    L_004056b1:
        push 48h
    L_004056b3:
        call asm_operator_new_00452493
    L_004056b8:
        mov edx,eax
    L_004056ba:
        add esp,4
    L_004056bd:
        test edx,edx
    L_004056bf:
        je short L_004056df
    L_004056c1:
        and dword ptr [edx+24h],0FFFFFFFEh
    L_004056c5:
        push edi
    L_004056c6:
        xor eax,eax
    L_004056c8:
        mov ecx,12h
    L_004056cd:
        mov edi,edx
    L_004056cf:
        rep stosd
    L_004056d1:
        or dword ptr [edx],2
    L_004056d4:
        mov dword ptr [data_004776ec],edx
    L_004056da:
        mov ebx,edx
    L_004056dc:
        pop edi
    L_004056dd:
        jmp short L_004056e1
    L_004056df:
        xor ebx,ebx
    L_004056e1:
        call asm_Recovery_InstallPairSetFlags_004055c0
    L_004056e6:
        test eax,eax
    L_004056e8:
        je short L_00405701
    L_004056ea:
        test ebx,ebx
    L_004056ec:
        je short L_004056fd
    L_004056ee:
        push ebx
    L_004056ef:
        call asm_Recovery_ReleaseRawPairAndReset_00405620
    L_004056f4:
        push ebx
    L_004056f5:
        call asm_free_004524a1
    L_004056fa:
        add esp,4
    L_004056fd:
        xor eax,eax
    L_004056ff:
        pop ebx
    L_00405700:
        ret
    L_00405701:
        mov eax,ebx
    L_00405703:
        pop ebx
    L_00405704:
        ret
    }
}

// 0x0040B940..0x0040B9A2: Recovery_CreateSmallState
// Allocate the small recovery state, register it in the global slot and hand it
// to the pair installer. When the installer rejects it the state is torn down
// through its own release entry and returned to the CRT heap.
struct RecoverySmallState {
    unsigned int flags;             // +0x00, bit 1 marks a registered state
    unsigned int reserved_04[9];    // +0x04..+0x27

    RecoverySmallState();
};

RecoverySmallState::RecoverySmallState() {
    memset(this, 0, sizeof(*this));
    flags |= 2;
    *(void**)&data_00477700 = this;
}

// The installer takes the state as its only stack argument and cleans it, so
// the recovered call keeps the retail push/callee-clean shape.
typedef int (__stdcall* SmallStateInstallFn)(void* state);
typedef void (__stdcall* SmallStateReleaseFn)(void* state);

void* Recovery_CreateSmallState_0040b940() {
    RecoverySmallState* state = new RecoverySmallState;
    if (((SmallStateInstallFn)asm_FUN_0040b560_0040b560)(state)) {
        if (state) {
            ((SmallStateReleaseFn)asm_FUN_0040b7b0_0040b7b0)(state);
            entry_free_004524a1(state);
        }
        return 0;
    }
    return state;
}

// 0x0040B9F0..0x0040BA5E: Recovery_UpdateEmitterDecision
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_UpdateEmitterDecision_0040b9f0() {
    __asm {
    L_0040b9f0:
        push esi
    L_0040b9f1:
        mov esi,dword ptr [edi+18h]
    L_0040b9f4:
        call asm_Recovery_TickState_0040bd20
    L_0040b9f9:
        test eax,eax
    L_0040b9fb:
        je short L_0040ba1d
    L_0040b9fd:
        mov eax,dword ptr [data_00491ff4]
    L_0040ba02:
        and eax,1000h
    L_0040ba07:
        neg eax
    L_0040ba09:
        sbb eax,eax
    L_0040ba0b:
        and eax,0FFFFFFF3h
    L_0040ba0e:
        add eax,0Fh
    L_0040ba11:
        mov dword ptr [data_00491fb8],eax
    L_0040ba16:
        mov eax,1
    L_0040ba1b:
        pop esi
    L_0040ba1c:
        ret
    L_0040ba1d:
        mov esi,dword ptr [edi+24h]
    L_0040ba20:
        mov ecx,dword ptr [edi+18h]
    L_0040ba23:
        inc esi
    L_0040ba24:
        mov dword ptr [edi+24h],esi
    L_0040ba27:
        mov ecx,dword ptr [ecx+74h]
    L_0040ba2a:
        test cl,4
    L_0040ba2d:
        mov eax,esi
    L_0040ba2f:
        jne short L_0040ba58
    L_0040ba31:
        test byte ptr [edi+20h],2
    L_0040ba35:
        jne short L_0040ba58
    L_0040ba37:
        test cl,2
    L_0040ba3a:
        je short L_0040ba58
    L_0040ba3c:
        mov ecx,dword ptr [data_00474e30]
    L_0040ba42:
        test ch,1
    L_0040ba45:
        je short L_0040ba58
    L_0040ba47:
        cdq
    L_0040ba48:
        mov ecx,0Ch
    L_0040ba4d:
        idiv ecx
    L_0040ba4f:
        mov eax,6
    L_0040ba54:
        test edx,edx
    L_0040ba56:
        jne short L_0040ba5d
    L_0040ba58:
        mov eax,1
    L_0040ba5d:
        pop esi
    L_0040ba5e:
        ret
    }
}

// 0x0040BD20..0x0040BD7C: ?Recovery_TickState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_TickState_0040bd20() {
    __asm {
    L_0040bd20:
        push esi
    L_0040bd21:
        call asm_FUN_0040bd80_0040bd80
    L_0040bd26:
        test eax,eax
    L_0040bd28:
        je short L_0040bd30
    L_0040bd2a:
        mov eax,1
    L_0040bd2f:
        ret
    L_0040bd30:
        mov edx,dword ptr [esi+8]
    L_0040bd33:
        mov ecx,dword ptr [esi+10h]
    L_0040bd36:
        mov dword ptr [esi+4],edx
    L_0040bd39:
        fld dword ptr [ecx]
    L_0040bd3b:
        fcomp dword ptr [data_00470b68]
    L_0040bd41:
        fnstsw ax
    L_0040bd43:
        test ah,41h
    L_0040bd46:
        jne short L_0040bd6a
    L_0040bd48:
        fld dword ptr [ecx]
    L_0040bd4a:
        fcomp dword ptr [data_00470b64]
    L_0040bd50:
        fnstsw ax
    L_0040bd52:
        test ah,5
    L_0040bd55:
        jp short L_0040bd6a
    L_0040bd57:
        fld dword ptr [esi+0Ch]
    L_0040bd5a:
        inc edx
    L_0040bd5b:
        fadd dword ptr [data_00470afc]
    L_0040bd61:
        mov dword ptr [esi+8],edx
    L_0040bd64:
        xor eax,eax
    L_0040bd66:
        fstp dword ptr [esi+0Ch]
    L_0040bd69:
        ret
    L_0040bd6a:
        fld dword ptr [esi+0Ch]
    L_0040bd6d:
        fadd dword ptr [ecx]
    L_0040bd6f:
        fst dword ptr [esi+0Ch]
    L_0040bd72:
        call asm_FUN_00463b2c_00463b2c
    L_0040bd77:
        mov dword ptr [esi+8],eax
    L_0040bd7a:
        xor eax,eax
    L_0040bd7c:
        ret
    }
}

// 0x0040C9A0..0x0040C9CF: Recovery_ResetEmitter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ResetEmitter_0040c9a0() {
    __asm {
    L_0040c9a0:
        push esi
    L_0040c9a1:
        mov esi,eax
    L_0040c9a3:
        mov eax,dword ptr [edi]
    L_0040c9a5:
        test eax,eax
    L_0040c9a7:
        jle short L_0040c9c2
    L_0040c9a9:
        push 400CCCCDh
    L_0040c9ae:
        push 0BFC90FDBh
    L_0040c9b3:
        push 0FFFFFFFFh
    L_0040c9b5:
        push eax
    L_0040c9b6:
        mov eax,dword ptr [data_00477818]
    L_0040c9bb:
        mov ecx,esi
    L_0040c9bd:
        call asm_FUN_0041bb00_0041bb00
    L_0040c9c2:
        push edi
    L_0040c9c3:
        call asm_FUN_0040c9d0_0040c9d0
    L_0040c9c8:
        mov dword ptr [edi],0
    L_0040c9ce:
        pop esi
    L_0040c9cf:
        ret
    }
}

// 0x0040CC50 - scalar deleting destructor for the bullet object: destroy the
// bullet through its own release entry, then free it on request. The delete
// flag is the retail first stack argument, so the second __fastcall register
// argument (EDX) is unused. The bullet destructor still lives in inline
// assembly, so it is called through its fixed retail prototype.
typedef void (__stdcall* BulletDestroyFn)(void* bullet);

void* __fastcall Bullet_DeletingDestructor(void* bullet, unsigned int unused, unsigned int flags) {
    ((BulletDestroyFn)asm_FUN_0040dae0_0040dae0)(bullet);
    if (flags & 1)
        operator delete(bullet);
    return bullet;
}

// 0x00412720..0x0041274F: Ecl_SetResourceSlot
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ecl_SetResourceSlot_00412720() {
    __asm {
    L_00412720:
        mov eax,edx
    L_00412722:
        shl eax,4
    L_00412725:
        add eax,esi
    L_00412727:
        test ecx,ecx
    L_00412729:
        mov dword ptr [eax+2494h],ecx
    L_0041272f:
        jl short L_0041274d
    L_00412731:
        mov ecx,dword ptr [esp+4]
    L_00412735:
        add edx,24Ah
    L_0041273b:
        shl edx,4
    L_0041273e:
        mov dword ptr [eax+2498h],ecx
    L_00412744:
        mov dword ptr [eax+249Ch],edi
    L_0041274a:
        mov dword ptr [edx+esi],edi
    L_0041274d:
        ret 4
    }
}

// 0x00412AA0..0x00412AB9: Ecl_ForwardFloat
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Ecl_ForwardFloat_00412aa0() {
    __asm {
    L_00412aa0:
        mov ecx,dword ptr [esp+8]
    L_00412aa4:
        mov eax,dword ptr [eax+14D8h]
    L_00412aaa:
        mov eax,dword ptr [eax+4]
    L_00412aad:
        push ecx
    L_00412aae:
        mov ecx,dword ptr [esp+8]
    L_00412ab2:
        call asm_ECL_ResolveFloatValue_0044ff80
    L_00412ab7:
        ret 8
    }
}

// 0x00412ED0..0x00412EDF: Score_SetMode
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_SetMode_00412ed0() {
    __asm {
    L_00412ed0:
        cmp dword ptr [eax+44h],ecx
    L_00412ed3:
        mov dword ptr [eax+44h],ecx
    L_00412ed6:
        je short L_00412edf
    L_00412ed8:
        mov dword ptr [eax+4Ch],0
    L_00412edf:
        ret
    }
}

// 0x00413170 - Store an angle after folding it into the retail range.
void Score_SetNormalizedAngle(void* state, float angle) {
    *(float*)((unsigned char*)state + 0x1C) = Angle_Normalize(angle);
}

// 0x00413200..0x00413216: ScoreList_InsertAfter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreList_InsertAfter_00413200() {
    __asm {
    L_00413200:
        mov edx,dword ptr [ecx+4]
    L_00413203:
        test edx,edx
    L_00413205:
        je short L_00413210
    L_00413207:
        mov dword ptr [eax+4],edx
    L_0041320a:
        mov edx,dword ptr [ecx+4]
    L_0041320d:
        mov dword ptr [edx+8],eax
    L_00413210:
        mov dword ptr [ecx+4],eax
    L_00413213:
        mov dword ptr [eax+8],ecx
    L_00413216:
        ret
    }
}

// 0x00413270..0x0041328D: Vector2_SetEllipticPolar
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Vector2_SetEllipticPolar_00413270() {
    __asm {
    L_00413270:
        push ecx
    L_00413271:
        mov dword ptr [esp],ecx
    L_00413274:
        mov eax,dword ptr [esp]
    L_00413277:
        fld dword ptr [esp+8]
    L_0041327b:
        fsincos
    L_0041327d:
        fmul dword ptr [esp+0Ch]
    L_00413281:
        fstp dword ptr [eax]
    L_00413283:
        fmul dword ptr [esp+10h]
    L_00413287:
        fstp dword ptr [eax+4]
    L_0041328a:
        pop ecx
    L_0041328b:
        ret 0Ch
    }
}

// 0x00413450..0x004134A3: ?Platform_ReleaseOwnedHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_ReleaseOwnedHandle_00413450() {
    __asm {
    L_00413450:
        test ebx,ebx
    L_00413452:
        je short L_004134a3
    L_00413454:
        push esi
    L_00413455:
        mov esi,dword ptr [ebx+0Ch]
    L_00413458:
        test esi,esi
    L_0041345a:
        push edi
    L_0041345b:
        mov edi,dword ptr [data_00491be4]
    L_00413461:
        je short L_0041348e
    L_00413463:
        push 492274h
    L_00413468:
        call dword ptr [data_004660b0]
    L_0041346e:
        inc byte ptr [data_0049231c]
    L_00413474:
        mov ecx,esi
    L_00413476:
        mov edx,edi
    L_00413478:
        call asm_Scheduler_Remove_00449f60
    L_0041347d:
        push 492274h
    L_00413482:
        call dword ptr [data_004660b4]
    L_00413488:
        dec byte ptr [data_0049231c]
    L_0041348e:
        push ebx
    L_0041348f:
        mov dword ptr [data_00477708],0
    L_00413499:
        call asm_free_004524a1
    L_0041349e:
        add esp,4
    L_004134a1:
        pop edi
    L_004134a2:
        pop esi
    L_004134a3:
        ret
    }
}

// 0x00413790..0x004137CC: Animation_SetActiveCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Animation_SetActiveCount_00413790() {
    __asm {
    L_00413790:
        xor edx,edx
    L_00413792:
        test ecx,ecx
    L_00413794:
        push edi
    L_00413795:
        mov edi,eax
    L_00413797:
        jle short L_004137b5
    L_00413799:
        push esi
    L_0041379a:
        lea eax,[edi+4CDCh]
    L_004137a0:
        mov esi,ecx
    L_004137a2:
        mov edx,ecx
    L_004137a4:
        or dword ptr [eax],2
    L_004137a7:
        add eax,3ACh
    L_004137ac:
        dec esi
    L_004137ad:
        jne short L_004137a4
    L_004137af:
        cmp ecx,9
    L_004137b2:
        pop esi
    L_004137b3:
        TH10_REL8(0x7d, 0x004137b3, VA_asm_target_004137db)
    L_004137b5:
        mov eax,edx
    L_004137b7:
        imul eax,3ACh
    L_004137bd:
        mov ecx,9
    L_004137c2:
        lea eax,[eax+edi+4CDCh]
    L_004137c9:
        sub ecx,edx
    L_004137cb:
        TH10_REL8(0xeb, 0x004137cb, VA_asm_Animation_SetActiveCount_part_004137d0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004137d0:
        and dword ptr [eax],0FFFFFFFDh
    L_004137d3:
        add eax,3ACh
    L_004137d8:
        dec ecx
    L_004137d9:
        jne short L_004137d0
    L_004137db:
        pop edi
    L_004137dc:
        ret
    }
}

// 0x00414570..0x004145E8: Recovery_ReleaseCompositeState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseCompositeState_00414570() {
    __asm {
    L_00414570:
        push ebp
    L_00414571:
        push esi
    L_00414572:
        mov esi,dword ptr [ebx+9EB8h]
    L_00414578:
        xor ebp,ebp
    L_0041457a:
        cmp esi,ebp
    L_0041457c:
        je short L_00414592
    L_0041457e:
        call asm_AnimationSlot_ReleaseRetail_004136c0
    L_00414583:
        push esi
    L_00414584:
        call asm_free_004524a1
    L_00414589:
        add esp,4
    L_0041458c:
        mov dword ptr [ebx+9EB8h],ebp
    L_00414592:
        test byte ptr [data_00474ca0],9
    L_00414599:
        jne short L_004145e6
    L_0041459b:
        mov esi,dword ptr [data_00491c10]
    L_004145a1:
        add esi,3AD0DCh
    L_004145a7:
        push edi
    L_004145a8:
        mov edi,dword ptr [esi]
    L_004145aa:
        cmp edi,ebp
    L_004145ac:
        je short L_004145c0
    L_004145ae:
        call asm_FUN_00447810_00447810
    L_004145b3:
        mov eax,dword ptr [esi]
    L_004145b5:
        push eax
    L_004145b6:
        call asm_free_004524a1
    L_004145bb:
        add esp,4
    L_004145be:
        mov dword ptr [esi],ebp
    L_004145c0:
        mov eax,dword ptr [ebx+9EBCh]
    L_004145c6:
        cmp eax,ebp
    L_004145c8:
        mov dword ptr [ebx+9E80h],ebp
    L_004145ce:
        pop edi
    L_004145cf:
        je short L_004145e0
    L_004145d1:
        push eax
    L_004145d2:
        call asm_free_00452422
    L_004145d7:
        add esp,4
    L_004145da:
        mov dword ptr [ebx+9EBCh],ebp
    L_004145e0:
        mov dword ptr [ebx+9EBCh],ebp
    L_004145e6:
        pop esi
    L_004145e7:
        pop ebp
    L_004145e8:
        ret
    }
}

// 0x00417770..0x004177B1: RecoveryLinkedCleanup
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryLinkedCleanup_00417770() {
    __asm {
    L_00417770:
        push esi
    L_00417771:
        mov esi,dword ptr [eax+18h]
    L_00417774:
        test esi,esi
    L_00417776:
        je short L_004177b0
    L_00417778:
        push edi
    L_00417779:
        lea esp,[esp+force_disp32_zero]
    L_00417780:
        mov edx,dword ptr [esi]
    L_00417782:
        mov edi,dword ptr [esi+8]
    L_00417785:
        mov ecx,esi
    L_00417787:
        call dword ptr [edx+10h]
    L_0041778a:
        mov eax,dword ptr [esi+4]
    L_0041778d:
        mov ecx,dword ptr [esi+8]
    L_00417790:
        mov dword ptr [eax+8],ecx
    L_00417793:
        mov eax,dword ptr [esi+8]
    L_00417796:
        test eax,eax
    L_00417798:
        je short L_004177a0
    L_0041779a:
        mov edx,dword ptr [esi+4]
    L_0041779d:
        mov dword ptr [eax+4],edx
    L_004177a0:
        push esi
    L_004177a1:
        call asm_free_004524a1
    L_004177a6:
        add esp,4
    L_004177a9:
        test edi,edi
    L_004177ab:
        mov esi,edi
    L_004177ad:
        jne short L_00417780
    L_004177af:
        pop edi
    L_004177b0:
        pop esi
    L_004177b1:
        ret
    }
}

// 0x00417800..0x00417839: PathState_Reset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_PathState_Reset_00417800() {
    __asm {
    L_00417800:
        mov ecx,dword ptr [eax+50h]
    L_00417803:
        xor edx,edx
    L_00417805:
        test cl,1
    L_00417808:
        jne short L_00417824
    L_0041780a:
        or ecx,1
    L_0041780d:
        mov dword ptr [eax+44h],edx
    L_00417810:
        mov dword ptr [eax+40h],0FFF0BDC1h
    L_00417817:
        mov dword ptr [eax+48h],edx
    L_0041781a:
        mov dword ptr [eax+4Ch],476F78h
    L_00417821:
        mov dword ptr [eax+50h],ecx
    L_00417824:
        mov dword ptr [eax+44h],edx
    L_00417827:
        mov dword ptr [eax+48h],edx
    L_0041782a:
        mov dword ptr [eax+40h],0FFFFFFFFh
    L_00417831:
        mov dword ptr [eax+58h],edx
    L_00417834:
        mov dword ptr [eax+5Ch],edx
    L_00417837:
        xor eax,eax
    L_00417839:
        ret
    }
}

// 0x00418810..0x0041884F: Recovery_OffsetPoint
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_OffsetPoint_00418810() {
    __asm {
    L_00418810:
        mov dl,byte ptr [data_00497d8c]
    L_00418816:
        mov ecx,1
    L_0041881b:
        test dl,cl
    L_0041881d:
        jne short L_00418825
    L_0041881f:
        or dword ptr [data_00497d8c],ecx
    L_00418825:
        fld dword ptr [eax]
    L_00418827:
        fadd dword ptr [data_00470b4c]
    L_0041882d:
        fstp dword ptr [data_00497d80]
    L_00418833:
        fld dword ptr [eax+4]
    L_00418836:
        fadd dword ptr [data_00470b48]
    L_0041883c:
        fstp dword ptr [data_00497d84]
    L_00418842:
        mov eax,dword ptr [eax+8]
    L_00418845:
        mov dword ptr [data_00497d88],eax
    L_0041884a:
        mov eax,497D80h
    L_0041884f:
        ret
    }
}

// 0x004188A0..0x0041892C: Recovery_IncrementAnimationCount
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_IncrementAnimationCount_004188a0() {
    __asm {
    L_004188a0:
        push ecx
    L_004188a1:
        push esi
    L_004188a2:
        mov esi,dword ptr [eax+30h]
    L_004188a5:
        add esi,ecx
    L_004188a7:
        mov ecx,esi
    L_004188a9:
        cmp ecx,9
    L_004188ac:
        mov dword ptr [eax+30h],esi
    L_004188af:
        jle short L_004188cb
    L_004188b1:
        mov dword ptr [eax+30h],9
    L_004188b8:
        mov ecx,dword ptr [data_00474c70]
    L_004188be:
        mov eax,dword ptr [data_0047770c]
    L_004188c3:
        call asm_Animation_SetActiveCount_00413790
    L_004188c8:
        pop esi
    L_004188c9:
        pop ecx
    L_004188ca:
        ret
    L_004188cb:
        push edi
    L_004188cc:
        push 0
    L_004188ce:
        mov edi,2Ch
    L_004188d3:
        mov ecx,492590h
    L_004188d8:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004188dd:
        mov edi,dword ptr [data_0047770c]
    L_004188e3:
        mov edx,dword ptr [edi+9E18h]
    L_004188e9:
        lea esi,[edi+9E18h]
    L_004188ef:
        push edx
    L_004188f0:
        mov edx,dword ptr [data_00491c10]
    L_004188f6:
        call asm_AnimationManager_SetFlag_004492a0
    L_004188fb:
        push 0Fh
    L_004188fd:
        mov dword ptr [esi],0
    L_00418903:
        mov eax,dword ptr [edi+9EC8h]
    L_00418909:
        push 4Bh
    L_0041890b:
        push eax
    L_0041890c:
        lea edi,[esp+14h]
    L_00418910:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00418915:
        mov ecx,dword ptr [eax]
    L_00418917:
        mov eax,dword ptr [data_0047770c]
    L_0041891c:
        mov dword ptr [esi],ecx
    L_0041891e:
        mov ecx,dword ptr [data_00474c70]
    L_00418924:
        pop edi
    L_00418925:
        call asm_Animation_SetActiveCount_00413790
    L_0041892a:
        pop esi
    L_0041892b:
        pop ecx
    L_0041892c:
        ret
    }
}

// 0x00418A00..0x00418A40: Recovery_DecayCounter
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_DecayCounter_00418a00() {
    __asm {
    L_00418a00:
        mov ecx,dword ptr [eax+18h]
    L_00418a03:
        test ecx,ecx
    L_00418a05:
        push esi
    L_00418a06:
        jle short L_00418a17
    L_00418a08:
        push 0BF800000h
    L_00418a0d:
        lea esi,[eax+14h]
    L_00418a10:
        call asm_FrameTimer_Advance_0044bf40
    L_00418a15:
        pop esi
    L_00418a16:
        ret
    L_00418a17:
        mov ecx,dword ptr [eax+0Ch]
    L_00418a1a:
        mov esi,1388h
    L_00418a1f:
        cmp ecx,esi
    L_00418a21:
        jle short L_00418a3f
    L_00418a23:
        mov edx,dword ptr [eax+10h]
    L_00418a26:
        sub ecx,edx
    L_00418a28:
        cmp edx,12h
    L_00418a2b:
        mov dword ptr [eax+0Ch],ecx
    L_00418a2e:
        jge short L_00418a37
    L_00418a30:
        mov dword ptr [eax+10h],12h
    L_00418a37:
        cmp dword ptr [eax+0Ch],esi
    L_00418a3a:
        jge short L_00418a3f
    L_00418a3c:
        mov dword ptr [eax+0Ch],esi
    L_00418a3f:
        pop esi
    L_00418a40:
        ret
    }
}

// 0x00419040..0x0041908E: Recovery_ClearEightBuckets
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ClearEightBuckets_00419040() {
    __asm {
    L_00419040:
        push ebx
    L_00419041:
        push esi
    L_00419042:
        push edi
    L_00419043:
        mov edi,eax
    L_00419045:
        add edi,7Ch
    L_00419048:
        mov ebx,8
    L_0041904d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00419050:
        mov eax,dword ptr [edi-60h]
    L_00419053:
        test eax,eax
    L_00419055:
        je short L_0041906b
    L_00419057:
        mov esi,dword ptr [eax+4]
    L_0041905a:
        mov eax,dword ptr [eax]
    L_0041905c:
        push eax
    L_0041905d:
        call asm_free_004524a1
    L_00419062:
        add esp,4
    L_00419065:
        test esi,esi
    L_00419067:
        mov eax,esi
    L_00419069:
        jne short L_00419057
    L_0041906b:
        mov eax,dword ptr [edi]
    L_0041906d:
        test eax,eax
    L_0041906f:
        je short L_00419085
    L_00419071:
        mov ecx,dword ptr [eax]
    L_00419073:
        mov esi,dword ptr [eax+4]
    L_00419076:
        push ecx
    L_00419077:
        call asm_free_004524a1
    L_0041907c:
        add esp,4
    L_0041907f:
        test esi,esi
    L_00419081:
        mov eax,esi
    L_00419083:
        jne short L_00419071
    L_00419085:
        add edi,0Ch
    L_00419088:
        dec ebx
    L_00419089:
        jne short L_00419050
    L_0041908b:
        pop edi
    L_0041908c:
        pop esi
    L_0041908d:
        pop ebx
    L_0041908e:
        ret
    }
}

// 0x00419090..0x004190D2: Recovery_CreateResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateResourceState_00419090() {
    __asm {
    L_00419090:
        push ebx
    L_00419091:
        push 1A8h
    L_00419096:
        call asm_operator_new_00452493
    L_0041909b:
        add esp,4
    L_0041909e:
        test eax,eax
    L_004190a0:
        je short L_004190ad
    L_004190a2:
        mov edx,eax
    L_004190a4:
        call asm_StageTipManager_Construct_00418d40
    L_004190a9:
        mov ebx,eax
    L_004190ab:
        jmp short L_004190af
    L_004190ad:
        xor ebx,ebx
    L_004190af:
        call asm_StageTipRuntime_InitializeRetail_00418e30
    L_004190b4:
        test eax,eax
    L_004190b6:
        je short L_004190cf
    L_004190b8:
        test ebx,ebx
    L_004190ba:
        je short L_004190cb
    L_004190bc:
        push ebx
    L_004190bd:
        call asm_FUN_00418ee0_00418ee0
    L_004190c2:
        push ebx
    L_004190c3:
        call asm_free_004524a1
    L_004190c8:
        add esp,4
    L_004190cb:
        xor eax,eax
    L_004190cd:
        pop ebx
    L_004190ce:
        ret
    L_004190cf:
        mov eax,ebx
    L_004190d1:
        pop ebx
    L_004190d2:
        ret
    }
}

// 0x004198A0..0x004198A9: Recovery_InvokeVoid
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokeVoid_004198a0() {
    __asm {
    L_004198a0:
        push ebx
    L_004198a1:
        mov ebx,ecx
    L_004198a3:
        call asm_FUN_00419650_00419650
    L_004198a8:
        pop ebx
    L_004198a9:
        ret
    }
}

// 0x004198C0..0x00419921: Recovery_FindNamedValue
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_FindNamedValue_004198c0() {
    __asm {
    L_004198c0:
        mov eax,dword ptr [esp+8]
    L_004198c4:
        push ebx
    L_004198c5:
        push ebp
    L_004198c6:
        mov ebp,dword ptr [esp+0Ch]
    L_004198ca:
        push esi
    L_004198cb:
        push edi
    L_004198cc:
        xor edi,edi
    L_004198ce:
        test eax,eax
    L_004198d0:
        jle short L_0041990e
    L_004198d2:
        mov esi,dword ptr [ebp+edi*8]
    L_004198d6:
        mov eax,edx
    L_004198d8:
        mov bl,byte ptr [eax]
    L_004198da:
        mov cl,bl
    L_004198dc:
        cmp bl,byte ptr [esi]
    L_004198de:
        jne short L_004198fc
    L_004198e0:
        test cl,cl
    L_004198e2:
        je short L_004198f8
    L_004198e4:
        mov bl,byte ptr [eax+1]
    L_004198e7:
        mov cl,bl
    L_004198e9:
        cmp bl,byte ptr [esi+1]
    L_004198ec:
        jne short L_004198fc
    L_004198ee:
        add eax,2
    L_004198f1:
        add esi,2
    L_004198f4:
        test cl,cl
    L_004198f6:
        jne short L_004198d8
    L_004198f8:
        xor eax,eax
    L_004198fa:
        jmp short L_00419901
    L_004198fc:
        sbb eax,eax
    L_004198fe:
        sbb eax,0FFFFFFFFh
    L_00419901:
        test eax,eax
    L_00419903:
        je short L_00419917
    L_00419905:
        mov eax,dword ptr [esp+18h]
    L_00419909:
        inc edi
    L_0041990a:
        cmp edi,eax
    L_0041990c:
        jl short L_004198d2
    L_0041990e:
        pop edi
    L_0041990f:
        pop esi
    L_00419910:
        pop ebp
    L_00419911:
        xor eax,eax
    L_00419913:
        pop ebx
    L_00419914:
        ret 8
    L_00419917:
        mov eax,dword ptr [ebp+edi*8+4]
    L_0041991b:
        pop edi
    L_0041991c:
        pop esi
    L_0041991d:
        pop ebp
    L_0041991e:
        pop ebx
    L_0041991f:
        ret 8
    }
}

// 0x0041A050..0x0041A09A: Recovery_SplitResourcePath
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SplitResourcePath_0041a050() {
    __asm {
    L_0041a050:
        mov edx,edi
    L_0041a052:
        sub edx,eax
    L_0041a054:
        mov cl,byte ptr [eax]
    L_0041a056:
        mov byte ptr [edx+eax],cl
    L_0041a059:
        inc eax
    L_0041a05a:
        test cl,cl
    L_0041a05c:
        jne short L_0041a054
    L_0041a05e:
        push 3Ah
    L_0041a060:
        push edi
    L_0041a061:
        call asm_FUN_00452730_00452730
    L_0041a066:
        add esp,8
    L_0041a069:
        test eax,eax
    L_0041a06b:
        jne short L_0041a074
    L_0041a06d:
        mov eax,edi
    L_0041a06f:
        jmp asm_Recovery_TrimWhitespace_0041a0a0
    L_0041a074:
        push esi
    L_0041a075:
        lea ecx,[eax+1]
    L_0041a078:
        mov esi,ebx
    L_0041a07a:
        sub esi,ecx
    L_0041a07c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0041a080:
        mov dl,byte ptr [ecx]
    L_0041a082:
        mov byte ptr [esi+ecx],dl
    L_0041a085:
        inc ecx
    L_0041a086:
        test dl,dl
    L_0041a088:
        jne short L_0041a080
    L_0041a08a:
        mov byte ptr [eax],dl
    L_0041a08c:
        mov eax,edi
    L_0041a08e:
        call asm_Recovery_TrimWhitespace_0041a0a0
    L_0041a093:
        mov eax,ebx
    L_0041a095:
        pop esi
    L_0041a096:
        jmp asm_Recovery_TrimWhitespace_0041a0a0
    }
}

// 0x0041A0A0..0x0041A0DC: Recovery_TrimWhitespace
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_TrimWhitespace_0041a0a0() {
    __asm {
    L_0041a0a0:
        push esi
    L_0041a0a1:
        push edi
    L_0041a0a2:
        mov cl,byte ptr [eax]
    L_0041a0a4:
        cmp cl,20h
    L_0041a0a7:
        je short L_0041a0b8
    L_0041a0a9:
        cmp cl,9
    L_0041a0ac:
        je short L_0041a0b8
    L_0041a0ae:
        cmp cl,0Ah
    L_0041a0b1:
        je short L_0041a0b8
    L_0041a0b3:
        cmp cl,0Dh
    L_0041a0b6:
        jne short L_0041a0d6
    L_0041a0b8:
        mov ecx,eax
    L_0041a0ba:
        lea esi,[ecx+1]
    L_0041a0bd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0041a0c0:
        mov dl,byte ptr [ecx]
    L_0041a0c2:
        inc ecx
    L_0041a0c3:
        test dl,dl
    L_0041a0c5:
        jne short L_0041a0c0
    L_0041a0c7:
        sub ecx,esi
    L_0041a0c9:
        test ecx,ecx
    L_0041a0cb:
        jle short L_0041a0a2
    L_0041a0cd:
        lea esi,[eax+1]
    L_0041a0d0:
        mov edi,eax
    L_0041a0d2:
        rep movsb
    L_0041a0d4:
        jmp short L_0041a0a2
    L_0041a0d6:
        mov ecx,eax
    L_0041a0d8:
        lea esi,[ecx+1]
    L_0041a0db:
        TH10_REL8(0xeb, 0x0041a0db, VA_asm_Recovery_TrimWhitespace_part_0041a0e0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0041a0e0:
        mov dl,byte ptr [ecx]
    L_0041a0e2:
        inc ecx
    L_0041a0e3:
        test dl,dl
    L_0041a0e5:
        jne short L_0041a0e0
    L_0041a0e7:
        sub ecx,esi
    L_0041a0e9:
        lea edx,[ecx-1]
    L_0041a0ec:
        test edx,edx
    L_0041a0ee:
        pop edi
    L_0041a0ef:
        pop esi
    L_0041a0f0:
        jl short L_0041a111
    L_0041a0f2:
        mov cl,byte ptr [edx+eax]
    L_0041a0f5:
        cmp cl,20h
    L_0041a0f8:
        je short L_0041a109
    L_0041a0fa:
        cmp cl,9
    L_0041a0fd:
        je short L_0041a109
    L_0041a0ff:
        cmp cl,0Ah
    L_0041a102:
        je short L_0041a109
    L_0041a104:
        cmp cl,0Dh
    L_0041a107:
        jne short L_0041a111
    L_0041a109:
        dec edx
    L_0041a10a:
        mov byte ptr [edx+eax+1],0
    L_0041a10f:
        jns short L_0041a0f2
    L_0041a111:
        ret
    }
}

// 0x0041AB10..0x0041AB43: Recovery_AppendNode
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_AppendNode_0041ab10() {
    __asm {
    L_0041ab10:
        lea ecx,[eax+4]
    L_0041ab13:
        push esi
    L_0041ab14:
        cmp dword ptr [ecx],0
    L_0041ab17:
        je short L_0041ab2c
    L_0041ab19:
        lea esp,[esp+force_disp32_zero]
    L_0041ab20:
        mov eax,dword ptr [ecx]
    L_0041ab22:
        mov esi,dword ptr [eax+4]
    L_0041ab25:
        test esi,esi
    L_0041ab27:
        lea ecx,[eax+4]
    L_0041ab2a:
        jne short L_0041ab20
    L_0041ab2c:
        mov ecx,dword ptr [eax+4]
    L_0041ab2f:
        test ecx,ecx
    L_0041ab31:
        pop esi
    L_0041ab32:
        je short L_0041ab3d
    L_0041ab34:
        mov dword ptr [edx+4],ecx
    L_0041ab37:
        mov ecx,dword ptr [eax+4]
    L_0041ab3a:
        mov dword ptr [ecx+8],edx
    L_0041ab3d:
        mov dword ptr [eax+4],edx
    L_0041ab40:
        mov dword ptr [edx+8],eax
    L_0041ab43:
        ret
    }
}

// 0x0041AD90..0x0041ADE3: ?Recovery_InstallPairClearFlags@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallPairClearFlags_0041ad90() {
    __asm {
    L_0041ad90:
        push esi
    L_0041ad91:
        push edi
    L_0041ad92:
        push 41BA00h
    L_0041ad97:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041ad9c:
        mov esi,eax
    L_0041ad9e:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041ada2:
        mov eax,dword ptr [data_00491be4]
    L_0041ada7:
        push eax
    L_0041ada8:
        mov edi,15h
    L_0041adad:
        mov dword ptr [esi+20h],ebx
    L_0041adb0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0041adb5:
        push 41BA30h
    L_0041adba:
        mov dword ptr [ebx+8],esi
    L_0041adbd:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041adc2:
        mov esi,eax
    L_0041adc4:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041adc8:
        mov ecx,dword ptr [data_00491be4]
    L_0041adce:
        push ecx
    L_0041adcf:
        mov edi,19h
    L_0041add4:
        mov dword ptr [esi+20h],ebx
    L_0041add7:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0041addc:
        pop edi
    L_0041addd:
        mov dword ptr [ebx+0Ch],esi
    L_0041ade0:
        xor eax,eax
    L_0041ade2:
        pop esi
    L_0041ade3:
        ret
    }
}

// 0x0041F850..0x0041F8CF: Recovery_InitializeStateTable
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeStateTable_0041f850() {
    __asm {
    L_0041f850:
        mov dword ptr [esi+10h],4703E4h
    L_0041f857:
        lea edx,[esi+30h]
    L_0041f85a:
        xor eax,eax
    L_0041f85c:
        mov dword ptr [esi+14h],eax
    L_0041f85f:
        mov dword ptr [esi+18h],eax
    L_0041f862:
        mov dword ptr [esi+1Ch],eax
    L_0041f865:
        mov dword ptr [esi+20h],eax
    L_0041f868:
        mov ecx,dword ptr [edx+6Ch]
    L_0041f86b:
        mov eax,0FFFFFFFEh
    L_0041f870:
        and ecx,eax
    L_0041f872:
        mov dword ptr [edx+6Ch],ecx
    L_0041f875:
        push edi
    L_0041f876:
        and dword ptr [edx+0B0h],eax
    L_0041f87c:
        and dword ptr [edx+0FCh],eax
    L_0041f882:
        and dword ptr [edx+128h],eax
    L_0041f888:
        and dword ptr [edx+174h],eax
    L_0041f88e:
        and dword ptr [edx+1B0h],eax
    L_0041f894:
        and dword ptr [edx+1FCh],eax
    L_0041f89a:
        and dword ptr [edx+228h],eax
    L_0041f8a0:
        and dword ptr [edx+378h],eax
    L_0041f8a6:
        xor eax,eax
    L_0041f8a8:
        mov ecx,0EBh
    L_0041f8ad:
        mov edi,edx
    L_0041f8af:
        rep stosd
    L_0041f8b1:
        mov word ptr [edx+384h],0FFFFh
    L_0041f8ba:
        mov ecx,0FCh
    L_0041f8bf:
        mov edi,esi
    L_0041f8c1:
        rep stosd
    L_0041f8c3:
        or dword ptr [esi],2
    L_0041f8c6:
        mov dword ptr [data_00477820],esi
    L_0041f8cc:
        mov eax,esi
    L_0041f8ce:
        pop edi
    L_0041f8cf:
        ret
    }
}

// 0x0041F8D0..0x0041F921: ?Recovery_LoadStartupResources@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_LoadStartupResources_0041f8d0() {
    __asm {
    L_0041f8d0:
        mov edx,dword ptr [data_00491c10]
    L_0041f8d6:
        push 46D254h
    L_0041f8db:
        mov ecx,6
    L_0041f8e0:
        call asm_Recovery_LoadCachedResource_00447280
    L_0041f8e5:
        test eax,eax
    L_0041f8e7:
        jne short L_0041f8f0
    L_0041f8e9:
        push 46CB68h
    L_0041f8ee:
        jmp short L_0041f90e
    L_0041f8f0:
        mov edx,dword ptr [data_00491c10]
    L_0041f8f6:
        push 46CD88h
    L_0041f8fb:
        mov ecx,7
    L_0041f900:
        call asm_Recovery_LoadCachedResource_00447280
    L_0041f905:
        test eax,eax
    L_0041f907:
        jne short L_0041f91f
    L_0041f909:
        push 46CD54h
    L_0041f90e:
        mov ecx,474F70h
    L_0041f913:
        call asm_TextLog_Append_0044b810
    L_0041f918:
        add esp,4
    L_0041f91b:
        or eax,0FFFFFFFFh
    L_0041f91e:
        ret
    L_0041f91f:
        xor eax,eax
    L_0041f921:
        ret
    }
}

// 0x0041F930..0x0041F98A: ?Recovery_ReleasePair@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleasePair_0041f930() {
    __asm {
    L_0041f930:
        push esi
    L_0041f931:
        mov esi,dword ptr [data_00491c10]
    L_0041f937:
        add esi,3AD084h
    L_0041f93d:
        push edi
    L_0041f93e:
        mov edi,dword ptr [esi]
    L_0041f940:
        test edi,edi
    L_0041f942:
        je short L_0041f95a
    L_0041f944:
        call asm_FUN_00447810_00447810
    L_0041f949:
        mov eax,dword ptr [esi]
    L_0041f94b:
        push eax
    L_0041f94c:
        call asm_free_004524a1
    L_0041f951:
        add esp,4
    L_0041f954:
        mov dword ptr [esi],0
    L_0041f95a:
        mov esi,dword ptr [data_00491c10]
    L_0041f960:
        mov edi,dword ptr [esi+3AD088h]
    L_0041f966:
        add esi,3AD088h
    L_0041f96c:
        test edi,edi
    L_0041f96e:
        je short L_0041f986
    L_0041f970:
        call asm_FUN_00447810_00447810
    L_0041f975:
        mov ecx,dword ptr [esi]
    L_0041f977:
        push ecx
    L_0041f978:
        call asm_free_004524a1
    L_0041f97d:
        add esp,4
    L_0041f980:
        mov dword ptr [esi],0
    L_0041f986:
        pop edi
    L_0041f987:
        xor eax,eax
    L_0041f989:
        pop esi
    L_0041f98a:
        ret
    }
}

// 0x0041FAC0..0x0041FB4B: Recovery_StartWorker
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_StartWorker_0041fac0() {
    __asm {
    L_0041fac0:
        push esi
    L_0041fac1:
        push edi
    L_0041fac2:
        push 41FEB0h
    L_0041fac7:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041facc:
        mov esi,eax
    L_0041face:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041fad2:
        mov eax,dword ptr [data_00491be4]
    L_0041fad7:
        push eax
    L_0041fad8:
        mov edi,3
    L_0041fadd:
        mov dword ptr [esi+20h],ebx
    L_0041fae0:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0041fae5:
        push 41FEF0h
    L_0041faea:
        mov dword ptr [ebx+8],esi
    L_0041faed:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041faf2:
        mov esi,eax
    L_0041faf4:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041faf8:
        mov ecx,dword ptr [data_00491be4]
    L_0041fafe:
        push ecx
    L_0041faff:
        mov edi,2
    L_0041fb04:
        mov dword ptr [esi+20h],ebx
    L_0041fb07:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0041fb0c:
        mov dword ptr [ebx+0Ch],esi
    L_0041fb0f:
        lea esi,[ebx+10h]
    L_0041fb12:
        call asm_Platform_StopWorker_0044c150
    L_0041fb17:
        lea edx,[esi+8]
    L_0041fb1a:
        push edx
    L_0041fb1b:
        push 0
    L_0041fb1d:
        push ebx
    L_0041fb1e:
        push 41F990h
    L_0041fb23:
        push 0
    L_0041fb25:
        push 0
    L_0041fb27:
        mov dword ptr [esi+18h],41F990h
    L_0041fb2e:
        mov dword ptr [esi+10h],1
    L_0041fb35:
        mov dword ptr [esi+0Ch],0
    L_0041fb3c:
        call asm_beginthreadex_00453683
    L_0041fb41:
        add esp,18h
    L_0041fb44:
        mov dword ptr [esi+4],eax
    L_0041fb47:
        pop edi
    L_0041fb48:
        xor eax,eax
    L_0041fb4a:
        pop esi
    L_0041fb4b:
        ret
    }
}

// 0x004203F0..0x0042046F: Recovery_ReleaseGlobalStates
// Tear down every global state object the engine allocated for the running
// session: manager state, script state, resource state, the small state and the
// pending block. Each object is destroyed through its own release routine and
// then handed back to the CRT heap. The globals keep their stale values, just
// as the retail code leaves them.
typedef void (__stdcall* GlobalStateDestroyFn)(void*);

void Recovery_ReleaseGlobalStates() {
    void* manager_state = *(void**)&data_00477810;
    if (manager_state) {
        ((GlobalStateDestroyFn)asm_FUN_00417c80_00417c80)(manager_state);
        entry_free_004524a1(manager_state);
    }
    void* script_state = *(void**)&data_0047784c;
    if (script_state) {
        ((GlobalStateDestroyFn)asm_FUN_0042cb60_0042cb60)(script_state);
        entry_free_004524a1(script_state);
    }
    void* resource_state = *(void**)&data_00477820;
    if (resource_state) {
        ((GlobalStateDestroyFn)asm_FUN_0041fb50_0041fb50)(resource_state);
        entry_free_004524a1(resource_state);
    }
    void* small_state = *(void**)&data_00477700;
    if (small_state) {
        ((GlobalStateDestroyFn)asm_FUN_0040b7b0_0040b7b0)(small_state);
        entry_free_004524a1(small_state);
    }
    void* pending_block = *(void**)&data_00477838;
    if (pending_block) {
        ((GlobalStateDestroyFn)asm_FUN_004294a0_004294a0)(pending_block);
        entry_free_004524a1(pending_block);
    }
}

// 0x00420A90..0x00420B07: Recovery_ReplaceExtensionWav
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReplaceExtensionWav_00420a90() {
    __asm {
    L_00420a90:
        sub esp,104h
    L_00420a96:
        mov eax,dword ptr [data_00473660]
    L_00420a9b:
        xor eax,esp
    L_00420a9d:
        mov dword ptr [esp+100h],eax
    L_00420aa4:
        mov eax,dword ptr [esp+10Ch]
    L_00420aab:
        lea edx,[esp]
    L_00420aae:
        sub edx,eax
    L_00420ab0:
        mov cl,byte ptr [eax]
    L_00420ab2:
        mov byte ptr [edx+eax],cl
    L_00420ab5:
        inc eax
    L_00420ab6:
        test cl,cl
    L_00420ab8:
        jne short L_00420ab0
    L_00420aba:
        lea eax,[esp]
    L_00420abd:
        push 2Eh
    L_00420abf:
        push eax
    L_00420ac0:
        call asm_strrchr_00452930
    L_00420ac5:
        mov ecx,dword ptr [esp+110h]
    L_00420acc:
        add esp,8
    L_00420acf:
        push ecx
    L_00420ad0:
        mov byte ptr [eax+1],77h
    L_00420ad4:
        mov byte ptr [eax+2],61h
    L_00420ad8:
        mov byte ptr [eax+3],76h
    L_00420adc:
        push 1
    L_00420ade:
        lea edx,[esp+8]
    L_00420ae2:
        mov eax,492590h
    L_00420ae7:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00420aec:
        mov ecx,dword ptr [esp+100h]
    L_00420af3:
        xor ecx,esp
    L_00420af5:
        mov eax,1
    L_00420afa:
        call asm_security_check_cookie_00458ea5
    L_00420aff:
        add esp,104h
    L_00420b05:
        ret 8
    }
}

// 0x00421F00..0x00421F46: ?Recovery_InitializeLargeState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeLargeState_00421f00() {
    __asm {
    L_00421f00:
        push edi
    L_00421f01:
        lea edx,[esi+120h]
    L_00421f07:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00421f0c:
        xor eax,eax
    L_00421f0e:
        mov dword ptr [esi+630h],eax
    L_00421f14:
        mov dword ptr [esi+634h],eax
    L_00421f1a:
        mov dword ptr [esi+638h],eax
    L_00421f20:
        mov dword ptr [esi+63Ch],eax
    L_00421f26:
        mov dword ptr [esi+62Ch],4703E4h
    L_00421f30:
        mov ecx,1E1h
    L_00421f35:
        mov edi,esi
    L_00421f37:
        rep stosd
    L_00421f39:
        or dword ptr [esi+3CCh],140h
    L_00421f43:
        mov eax,esi
    L_00421f45:
        pop edi
    L_00421f46:
        ret
    }
}

// 0x004220E0..0x00422144: RecoveryState_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Initialize_004220e0() {
    __asm {
    L_004220e0:
        mov ecx,dword ptr [edx+20h]
    L_004220e3:
        xor eax,eax
    L_004220e5:
        and ecx,0FFFFFFFEh
    L_004220e8:
        mov dword ptr [edx+20h],ecx
    L_004220eb:
        mov dword ptr [edx+0B0h],eax
    L_004220f1:
        mov dword ptr [edx+24h],eax
    L_004220f4:
        mov dword ptr [edx+0F8h],eax
    L_004220fa:
        mov dword ptr [edx+0F4h],1
    L_00422104:
        mov ecx,3E7h
    L_00422109:
        mov dword ptr [edx+2Ch],ecx
    L_0042210c:
        mov dword ptr [edx+104h],ecx
    L_00422112:
        push edi
    L_00422113:
        mov dword ptr [edx+188h],eax
    L_00422119:
        mov dword ptr [edx+0FCh],eax
    L_0042211f:
        mov dword ptr [edx+1D0h],eax
    L_00422125:
        mov dword ptr [edx+1CCh],1
    L_0042212f:
        mov ecx,0B2h
    L_00422134:
        mov edi,edx
    L_00422136:
        rep stosd
    L_00422138:
        or dword ptr [edx],2
    L_0042213b:
        mov dword ptr [data_00477830],edx
    L_00422141:
        mov eax,edx
    L_00422143:
        pop edi
    L_00422144:
        ret
    }
}

// 0x00422360..0x004223A2: Recovery_CreateTimerState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateTimerState_00422360() {
    __asm {
    L_00422360:
        push ebx
    L_00422361:
        push 2C8h
    L_00422366:
        call asm_operator_new_00452493
    L_0042236b:
        add esp,4
    L_0042236e:
        test eax,eax
    L_00422370:
        je short L_0042237d
    L_00422372:
        mov edx,eax
    L_00422374:
        call asm_RecoveryState_Initialize_004220e0
    L_00422379:
        mov ebx,eax
    L_0042237b:
        jmp short L_0042237f
    L_0042237d:
        xor ebx,ebx
    L_0042237f:
        call asm_MainMenu_RegisterTasksRetail_00422150
    L_00422384:
        test eax,eax
    L_00422386:
        je short L_0042239f
    L_00422388:
        test ebx,ebx
    L_0042238a:
        je short L_0042239b
    L_0042238c:
        push ebx
    L_0042238d:
        call asm_FUN_00422220_00422220
    L_00422392:
        push ebx
    L_00422393:
        call asm_free_004524a1
    L_00422398:
        add esp,4
    L_0042239b:
        xor eax,eax
    L_0042239d:
        pop ebx
    L_0042239e:
        ret
    L_0042239f:
        mov eax,ebx
    L_004223a1:
        pop ebx
    L_004223a2:
        ret
    }
}

// 0x00422A90..0x00422A99: Recovery_InvokePair
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokePair_00422a90() {
    __asm {
    L_00422a90:
        push esi
    L_00422a91:
        mov esi,ecx
    L_00422a93:
        call asm_FUN_004223f0_004223f0
    L_00422a98:
        pop esi
    L_00422a99:
        ret
    }
}

// 0x00423510..0x00423568: ?Recovery_InitializeTimedState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeTimedState_00423510() {
    __asm {
    L_00423510:
        mov dword ptr [esi+4],0Dh
    L_00423517:
        mov eax,dword ptr [esi+20h]
    L_0042351a:
        xor ecx,ecx
    L_0042351c:
        test al,1
    L_0042351e:
        jne short L_0042353a
    L_00423520:
        or eax,1
    L_00423523:
        mov dword ptr [esi+14h],ecx
    L_00423526:
        mov dword ptr [esi+10h],0FFF0BDC1h
    L_0042352d:
        mov dword ptr [esi+18h],ecx
    L_00423530:
        mov dword ptr [esi+1Ch],476F78h
    L_00423537:
        mov dword ptr [esi+20h],eax
    L_0042353a:
        lea eax,[esi+1D8h]
    L_00423540:
        mov dword ptr [esi+14h],ecx
    L_00423543:
        mov dword ptr [esi+18h],ecx
    L_00423546:
        mov dword ptr [esi+10h],0FFFFFFFFh
    L_0042354d:
        call asm_FUN_00409e50_00409e50
    L_00423552:
        lea eax,[esi+1D4h]
    L_00423558:
        call asm_FUN_00409e50_00409e50
    L_0042355d:
        mov eax,dword ptr [esi+2C0h]
    L_00423563:
        mov dword ptr [data_00476f78],eax
    L_00423568:
        ret
    }
}

// 0x004243F0..0x00424430: Recovery_MarkAnimationTree
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_MarkAnimationTree_004243f0() {
    __asm {
    L_004243f0:
        mov eax,dword ptr [eax]
    L_004243f2:
        mov edx,dword ptr [data_00491c10]
    L_004243f8:
        push eax
    L_004243f9:
        call asm_AnimationManager_Find_004491c0
    L_004243fe:
        test eax,eax
    L_00424400:
        je short L_00424430
    L_00424402:
        mov edx,dword ptr [eax+18h]
    L_00424405:
        test edx,edx
    L_00424407:
        mov ecx,6
    L_0042440c:
        mov word ptr [eax+304h],cx
    L_00424413:
        jne short L_00424430
    L_00424415:
        mov eax,dword ptr [eax+14h]
    L_00424418:
        test eax,eax
    L_0042441a:
        je short L_00424430
    L_0042441c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00424420:
        mov edx,dword ptr [eax]
    L_00424422:
        mov word ptr [edx+304h],cx
    L_00424429:
        mov eax,dword ptr [eax+4]
    L_0042442c:
        test eax,eax
    L_0042442e:
        jne short L_00424420
    L_00424430:
        ret
    }
}

// 0x00425020..0x00425064: Recovery_CreateLargeResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateLargeResourceState_00425020() {
    __asm {
    L_00425020:
        push ebx
    L_00425021:
        push 4478h
    L_00425026:
        call asm_operator_new_00452493
    L_0042502b:
        add esp,4
    L_0042502e:
        test eax,eax
    L_00425030:
        je short L_0042503f
    L_00425032:
        push esi
    L_00425033:
        mov esi,eax
    L_00425035:
        call asm_FUN_004246c0_004246c0
    L_0042503a:
        mov ebx,eax
    L_0042503c:
        pop esi
    L_0042503d:
        jmp short L_00425041
    L_0042503f:
        xor ebx,ebx
    L_00425041:
        call asm_FUN_004247f0_004247f0
    L_00425046:
        test eax,eax
    L_00425048:
        je short L_00425061
    L_0042504a:
        test ebx,ebx
    L_0042504c:
        je short L_0042505d
    L_0042504e:
        push ebx
    L_0042504f:
        call asm_FUN_00424ed0_00424ed0
    L_00425054:
        push ebx
    L_00425055:
        call asm_free_004524a1
    L_0042505a:
        add esp,4
    L_0042505d:
        xor eax,eax
    L_0042505f:
        pop ebx
    L_00425060:
        ret
    L_00425061:
        mov eax,ebx
    L_00425063:
        pop ebx
    L_00425064:
        ret
    }
}

// 0x00427950..0x0042795B: Recovery_InvokeZero
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InvokeZero_00427950() {
    __asm {
    L_00427950:
        push esi
    L_00427951:
        mov esi,ecx
    L_00427953:
        call asm_FUN_00427960_00427960
    L_00427958:
        xor eax,eax
    L_0042795a:
        pop esi
    L_0042795b:
        ret
    }
}

// 0x00427AE0..0x00427B42: ?Recovery_SwitchPlaybackState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SwitchPlaybackState_00427ae0() {
    __asm {
    L_00427ae0:
        mov eax,dword ptr [data_00477834]
    L_00427ae5:
        push ebx
    L_00427ae6:
        mov ebx,dword ptr [eax+4474h]
    L_00427aec:
        test ebx,ebx
    L_00427aee:
        mov eax,dword ptr [edi+84h]
    L_00427af4:
        push esi
    L_00427af5:
        jne short L_00427b1d
    L_00427af7:
        test eax,eax
    L_00427af9:
        je short L_00427b08
    L_00427afb:
        lea eax,[edi+68h]
    L_00427afe:
        mov esi,6
    L_00427b03:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427b08:
        mov ecx,dword ptr [edi+3Ch]
    L_00427b0b:
        mov dword ptr [edi+4Ch],ecx
    L_00427b0e:
        mov edx,dword ptr [edi+40h]
    L_00427b11:
        mov dword ptr [edi+50h],edx
    L_00427b14:
        pop esi
    L_00427b15:
        mov dword ptr [edi+84h],ebx
    L_00427b1b:
        pop ebx
    L_00427b1c:
        ret
    L_00427b1d:
        test eax,eax
    L_00427b1f:
        jne short L_00427b2e
    L_00427b21:
        lea eax,[edi+68h]
    L_00427b24:
        mov esi,3
    L_00427b29:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00427b2e:
        mov eax,dword ptr [edi+4Ch]
    L_00427b31:
        mov dword ptr [edi+34h],eax
    L_00427b34:
        mov ecx,dword ptr [edi+50h]
    L_00427b37:
        mov dword ptr [edi+38h],ecx
    L_00427b3a:
        pop esi
    L_00427b3b:
        mov dword ptr [edi+84h],ebx
    L_00427b41:
        pop ebx
    L_00427b42:
        ret
    }
}

// 0x004281D0..0x0042827D: Recovery_UpdateStageSequence
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_UpdateStageSequence_004281d0() {
    __asm {
    L_004281d0:
        push ebx
    L_004281d1:
        push edi
    L_004281d2:
        mov edi,eax
    L_004281d4:
        mov eax,dword ptr [edi+458h]
    L_004281da:
        mov ebx,1
    L_004281df:
        cmp eax,ebx
    L_004281e1:
        jne asm_target_00428268
    L_004281e7:
        mov eax,dword ptr [edi+464h]
    L_004281ed:
        test eax,eax
    L_004281ef:
        jge short L_00428206
    L_004281f1:
        test byte ptr [data_00474e5c],bl
    L_004281f7:
        je short L_00428249
    L_004281f9:
        push 0
    L_004281fb:
        lea eax,[edi+460h]
    L_00428201:
        call asm_Player_SetSchedulerValue_00405410
    L_00428206:
        mov eax,dword ptr [edi+464h]
    L_0042820c:
        mov ecx,dword ptr [edi+460h]
    L_00428212:
        cmp eax,ecx
    L_00428214:
        push esi
    L_00428215:
        lea esi,[edi+460h]
    L_0042821b:
        je short L_0042822d
    L_0042821d:
        mov ebx,dword ptr [edi+464h]
    L_00428223:
        call asm_Recovery_DispatchSchedule_00428160
    L_00428228:
        mov ebx,1
    L_0042822d:
        cmp dword ptr [edi+464h],0Fh
    L_00428234:
        jl short L_0042825d
    L_00428236:
        test byte ptr [data_00474e5c],bl
    L_0042823c:
        je short L_0042824e
    L_0042823e:
        push 0C1700000h
    L_00428243:
        call asm_FrameTimer_Advance_0044bf40
    L_00428248:
        pop esi
    L_00428249:
        pop edi
    L_0042824a:
        xor eax,eax
    L_0042824c:
        pop ebx
    L_0042824d:
        ret
    L_0042824e:
        push 0FFFFFFFFh
    L_00428250:
        mov eax,esi
    L_00428252:
        call asm_Player_SetSchedulerValue_00405410
    L_00428257:
        pop esi
    L_00428258:
        pop edi
    L_00428259:
        xor eax,eax
    L_0042825b:
        pop ebx
    L_0042825c:
        ret
    L_0042825d:
        call asm_FrameTimer_Tick_00404ed0
    L_00428262:
        pop esi
    L_00428263:
        pop edi
    L_00428264:
        xor eax,eax
    L_00428266:
        pop ebx
    L_00428267:
        ret
    L_00428268:
        mov dword ptr [edi+3504h],0
    L_00428272:
        mov byte ptr [edi+3508h],0
    L_00428279:
        pop edi
    L_0042827a:
        xor eax,eax
    L_0042827c:
        pop ebx
    L_0042827d:
        ret
    }
}

// 0x004297B0..0x004297C1: ?Platform_DeletingDestructorWithRelease@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_DeletingDestructorWithRelease_004297b0() {
    __asm {
    L_004297b0:
        test esi,esi
    L_004297b2:
        je short L_004297c1
    L_004297b4:
        push esi
    L_004297b5:
        call asm_FUN_004294a0_004294a0
    L_004297ba:
        push esi
    L_004297bb:
        call asm_free_004524a1
    L_004297c0:
        pop ecx
    L_004297c1:
        ret
    }
}

// 0x0042A8A0..0x0042A8F4: Recovery_AppendPacket
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_AppendPacket_0042a8a0() {
    __asm {
    L_0042a8a0:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8a6:
        mov word ptr [ecx],dx
    L_0042a8a9:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8af:
        mov dx,word ptr [esp+4]
    L_0042a8b4:
        mov word ptr [ecx+2],dx
    L_0042a8b8:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8be:
        mov dx,word ptr [esp+8]
    L_0042a8c3:
        mov word ptr [ecx+4],dx
    L_0042a8c7:
        mov ecx,dword ptr [eax+5460h]
    L_0042a8cd:
        add ecx,6
    L_0042a8d0:
        mov dword ptr [eax+5460h],ecx
    L_0042a8d6:
        sub ecx,eax
    L_0042a8d8:
        mov eax,2AAAAAABh
    L_0042a8dd:
        imul ecx
    L_0042a8df:
        mov eax,edx
    L_0042a8e1:
        shr eax,1Fh
    L_0042a8e4:
        add eax,edx
    L_0042a8e6:
        xor ecx,ecx
    L_0042a8e8:
        cmp eax,0E10h
    L_0042a8ed:
        setge cl
    L_0042a8f0:
        mov eax,ecx
    L_0042a8f2:
        ret 8
    }
}

// 0x0042ADD0..0x0042AE5D - Recovery_InitializeRandomTable
//
// Fills a 0x448-byte string table: an 8-space blank entry, then 512 generated
// 16-bit words from the game's LCG. The recurrence matches RngState::NextWord
// but reads the seed as a whole 32-bit word and shifts the whole word left, so
// the source used a 32-bit local rather than the 16-bit field rng.hpp wraps.
// The loop head is 16-byte aligned by the compiler, which is where the jump
// over the alignment padding inside the region comes from.
extern "C" void __fastcall Recovery_InitializeRandomTable_0042add0(int unused, char* table) {
    memset(table, 0, 0x448);
    *(unsigned short*)(table + 2) = 0;
    *(unsigned short*)table = 0x5453;
    *(unsigned int*)(table + 8) = 0x448;
    memcpy(table + 12, &data_0046e354, 9);
    unsigned short* out = (unsigned short*)(table + 70);
    int remaining = 512;
    do {
        unsigned short word;
        unsigned int value = *(unsigned int*)&data_004918b0;
        value ^= 0x9630;
        value -= 0x6553;
        unsigned int high = ((unsigned short)value) >> 14;
        word = (unsigned short)(high + (value << 2));
        *(unsigned short*)&data_004918b0 = word;
        ++*(unsigned int*)&data_004918b4;
        *out++ = word;
        --remaining;
    } while (remaining);
}

// 0x0042B660..0x0042B6A6: Recovery_CreateHugeResourceState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateHugeResourceState_0042b660() {
    __asm {
    L_0042b660:
        push esi
    L_0042b661:
        push 0B884h
    L_0042b666:
        call asm_operator_new_00452493
    L_0042b66b:
        add esp,4
    L_0042b66e:
        test eax,eax
    L_0042b670:
        je short L_0042b67f
    L_0042b672:
        push ebx
    L_0042b673:
        mov ebx,eax
    L_0042b675:
        call asm_EffectManager_ResetAndPublishRetail_0042b430
    L_0042b67a:
        mov esi,eax
    L_0042b67c:
        pop ebx
    L_0042b67d:
        jmp short L_0042b681
    L_0042b67f:
        xor esi,esi
    L_0042b681:
        mov eax,esi
    L_0042b683:
        call asm_EffectManagerRuntime_InitializeRetail_0042b4d0
    L_0042b688:
        test eax,eax
    L_0042b68a:
        je short L_0042b6a3
    L_0042b68c:
        test esi,esi
    L_0042b68e:
        je short L_0042b69f
    L_0042b690:
        push esi
    L_0042b691:
        call asm_FUN_0042b570_0042b570
    L_0042b696:
        push esi
    L_0042b697:
        call asm_free_004524a1
    L_0042b69c:
        add esp,4
    L_0042b69f:
        xor eax,eax
    L_0042b6a1:
        pop esi
    L_0042b6a2:
        ret
    L_0042b6a3:
        mov eax,esi
    L_0042b6a5:
        pop esi
    L_0042b6a6:
        ret
    }
}

// 0x0042C670..0x0042C6CE: ?Recovery_InstallAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InstallAnimationSlot_0042c670() {
    __asm {
    L_0042c670:
        push ebx
    L_0042c671:
        push ebp
    L_0042c672:
        mov ebp,dword ptr [esp+0Ch]
    L_0042c676:
        mov eax,dword ptr [ebp+14h]
    L_0042c679:
        push esi
    L_0042c67a:
        mov esi,dword ptr [data_00491c10]
    L_0042c680:
        mov dword ptr [esp+10h],eax
    L_0042c684:
        call asm_FUN_00449950_00449950
    L_0042c689:
        mov ecx,dword ptr [esp+10h]
    L_0042c68d:
        mov ebx,eax
    L_0042c68f:
        mov edx,dword ptr [ebx+35Ch]
    L_0042c695:
        push edi
    L_0042c696:
        or edx,40000000h
    L_0042c69c:
        push ebx
    L_0042c69d:
        mov dword ptr [ebx+20h],0Fh
    L_0042c6a4:
        mov dword ptr [ebx+35Ch],edx
    L_0042c6aa:
        call asm_FUN_00449870_00449870
    L_0042c6af:
        mov edx,dword ptr [data_00491c10]
    L_0042c6b5:
        lea eax,[esp+10h]
    L_0042c6b9:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0042c6be:
        mov ecx,dword ptr [esp+10h]
    L_0042c6c2:
        pop esi
    L_0042c6c3:
        mov dword ptr [ebp+edi*4+2C4h],ecx
    L_0042c6ca:
        pop ebp
    L_0042c6cb:
        pop ebx
    L_0042c6cc:
        ret 4
    }
}

// 0x0042C6D0..0x0042C722: ?Recovery_ClearAnimationSlot@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ClearAnimationSlot_0042c6d0() {
    __asm {
    L_0042c6d0:
        mov eax,dword ptr [edi+esi*4+2C4h]
    L_0042c6d7:
        mov edx,dword ptr [data_00491c10]
    L_0042c6dd:
        push eax
    L_0042c6de:
        call asm_AnimationManager_Find_004491c0
    L_0042c6e3:
        xor ecx,ecx
    L_0042c6e5:
        cmp eax,ecx
    L_0042c6e7:
        je short L_0042c71b
    L_0042c6e9:
        push ebx
    L_0042c6ea:
        cmp dword ptr [eax+18h],ecx
    L_0042c6ed:
        mov edx,1
    L_0042c6f2:
        mov word ptr [eax+304h],dx
    L_0042c6f9:
        jne short L_0042c712
    L_0042c6fb:
        mov eax,dword ptr [eax+14h]
    L_0042c6fe:
        cmp eax,ecx
    L_0042c700:
        je short L_0042c712
    L_0042c702:
        mov ebx,dword ptr [eax]
    L_0042c704:
        mov word ptr [ebx+304h],dx
    L_0042c70b:
        mov eax,dword ptr [eax+4]
    L_0042c70e:
        cmp eax,ecx
    L_0042c710:
        jne short L_0042c702
    L_0042c712:
        mov dword ptr [edi+esi*4+2C4h],ecx
    L_0042c719:
        pop ebx
    L_0042c71a:
        ret
    L_0042c71b:
        mov dword ptr [edi+esi*4+2C4h],ecx
    L_0042c722:
        ret
    }
}

// 0x0043BC40..0x0043BCC6: Recovery_ResetDeviceStreams
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ResetDeviceStreams_0043bc40() {
    __asm {
    L_0043bc40:
        mov eax,dword ptr [data_00491c30]
    L_0043bc45:
        mov ecx,dword ptr [eax]
    L_0043bc47:
        push 0
    L_0043bc49:
        push 3F800000h
    L_0043bc4e:
        push esi
    L_0043bc4f:
        push 3
    L_0043bc51:
        push 0
    L_0043bc53:
        push 0
    L_0043bc55:
        push eax
    L_0043bc56:
        call dword ptr [ecx+0ACh]
    L_0043bc5c:
        mov eax,dword ptr [data_00491c30]
    L_0043bc61:
        mov edx,dword ptr [eax]
    L_0043bc63:
        push 0
    L_0043bc65:
        push 0
    L_0043bc67:
        push 0
    L_0043bc69:
        push 0
    L_0043bc6b:
        push eax
    L_0043bc6c:
        call dword ptr [edx+44h]
    L_0043bc6f:
        test eax,eax
    L_0043bc71:
        jge short L_0043bc83
    L_0043bc73:
        mov eax,dword ptr [data_00491c30]
    L_0043bc78:
        mov ecx,dword ptr [eax]
    L_0043bc7a:
        push 491D0Ch
    L_0043bc7f:
        push eax
    L_0043bc80:
        call dword ptr [ecx+40h]
    L_0043bc83:
        mov eax,dword ptr [data_00491c30]
    L_0043bc88:
        mov edx,dword ptr [eax]
    L_0043bc8a:
        push 0
    L_0043bc8c:
        push 3F800000h
    L_0043bc91:
        push esi
    L_0043bc92:
        push 3
    L_0043bc94:
        push 0
    L_0043bc96:
        push 0
    L_0043bc98:
        push eax
    L_0043bc99:
        call dword ptr [edx+0ACh]
    L_0043bc9f:
        mov eax,dword ptr [data_00491c30]
    L_0043bca4:
        mov ecx,dword ptr [eax]
    L_0043bca6:
        push 0
    L_0043bca8:
        push 0
    L_0043bcaa:
        push 0
    L_0043bcac:
        push 0
    L_0043bcae:
        push eax
    L_0043bcaf:
        call dword ptr [ecx+44h]
    L_0043bcb2:
        test eax,eax
    L_0043bcb4:
        jge short L_0043bcc6
    L_0043bcb6:
        mov eax,dword ptr [data_00491c30]
    L_0043bcbb:
        mov edx,dword ptr [eax]
    L_0043bcbd:
        push 491D0Ch
    L_0043bcc2:
        push eax
    L_0043bcc3:
        call dword ptr [edx+40h]
    L_0043bcc6:
        ret
    }
}

// 0x0043C870..0x0043C889: Platform_DeletingDestructorNoReturn
// Scalar deleting destructor for the platform-owned raw pair: release the pair,
// return the object to the CRT heap and report success in EAX. The object
// arrives in ECX, matching the retail thunk ABI.
int __fastcall Platform_DeletingDestructorNoReturn(void* pair) {
    if (pair) {
        ((RawPairReleaseFn)asm_Recovery_ReleaseRawPair_0043cb00)(pair);
        entry_free_004524a1(pair);
    }
    return 0;
}

// 0x0043CB00..0x0043CB7E: ?Recovery_ReleaseRawPair@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseRawPair_0043cb00() {
    __asm {
    L_0043cb00:
        mov eax,dword ptr [esp+4]
    L_0043cb04:
        push ebx
    L_0043cb05:
        mov ebx,dword ptr [data_004660b0]
    L_0043cb0b:
        push ebp
    L_0043cb0c:
        mov ebp,dword ptr [data_004660b4]
    L_0043cb12:
        push esi
    L_0043cb13:
        mov esi,dword ptr [eax+8]
    L_0043cb16:
        test esi,esi
    L_0043cb18:
        push edi
    L_0043cb19:
        mov edi,dword ptr [data_00491be4]
    L_0043cb1f:
        je short L_0043cb44
    L_0043cb21:
        push 492274h
    L_0043cb26:
        call ebx
    L_0043cb28:
        inc byte ptr [data_0049231c]
    L_0043cb2e:
        mov ecx,esi
    L_0043cb30:
        mov edx,edi
    L_0043cb32:
        call asm_Scheduler_Remove_00449f60
    L_0043cb37:
        push 492274h
    L_0043cb3c:
        call ebp
    L_0043cb3e:
        dec byte ptr [data_0049231c]
    L_0043cb44:
        mov ecx,dword ptr [esp+14h]
    L_0043cb48:
        mov esi,dword ptr [ecx+0Ch]
    L_0043cb4b:
        test esi,esi
    L_0043cb4d:
        mov edi,dword ptr [data_00491be4]
    L_0043cb53:
        je short L_0043cb78
    L_0043cb55:
        push 492274h
    L_0043cb5a:
        call ebx
    L_0043cb5c:
        inc byte ptr [data_0049231c]
    L_0043cb62:
        mov ecx,esi
    L_0043cb64:
        mov edx,edi
    L_0043cb66:
        call asm_Scheduler_Remove_00449f60
    L_0043cb6b:
        push 492274h
    L_0043cb70:
        call ebp
    L_0043cb72:
        dec byte ptr [data_0049231c]
    L_0043cb78:
        pop edi
    L_0043cb79:
        pop esi
    L_0043cb7a:
        pop ebp
    L_0043cb7b:
        pop ebx
    L_0043cb7c:
        ret 4
    }
}

// 0x0043D790..0x0043D7C6: ?Recovery_SelectArchiveEntry@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_SelectArchiveEntry_0043d790() {
    __asm {
    L_0043d790:
        push esi
    L_0043d791:
        mov esi,eax
    L_0043d793:
        mov eax,dword ptr [esi+5208h]
    L_0043d799:
        test eax,eax
    L_0043d79b:
        jne short L_0043d7a2
    L_0043d79d:
        or eax,0FFFFFFFFh
    L_0043d7a0:
        pop esi
    L_0043d7a1:
        ret
    L_0043d7a2:
        push esi
    L_0043d7a3:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043d7a8:
        mov ecx,eax
    L_0043d7aa:
        mov eax,dword ptr [esi+1F84h]
    L_0043d7b0:
        imul ecx,34h
    L_0043d7b3:
        add ecx,eax
    L_0043d7b5:
        mov eax,dword ptr [esi+5208h]
    L_0043d7bb:
        mov esi,dword ptr [eax+0Ch]
    L_0043d7be:
        call asm_Platform_SelectStreamRecord_0044dca0
    L_0043d7c3:
        xor eax,eax
    L_0043d7c5:
        pop esi
    L_0043d7c6:
        ret
    }
}

// 0x00441EF0..0x00441F0D: Vector2_SetAnimationPolar
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Vector2_SetAnimationPolar_00441ef0() {
    __asm {
    L_00441ef0:
        push ecx
    L_00441ef1:
        mov dword ptr [esp],ecx
    L_00441ef4:
        mov eax,dword ptr [esp]
    L_00441ef7:
        fld dword ptr [esp+8]
    L_00441efb:
        fsincos
    L_00441efd:
        fmul dword ptr [esp+0Ch]
    L_00441f01:
        fstp dword ptr [eax]
    L_00441f03:
        fmul dword ptr [esp+0Ch]
    L_00441f07:
        fstp dword ptr [eax+4]
    L_00441f0a:
        pop ecx
    L_00441f0b:
        ret 8
    }
}

// 0x00441F50..0x00441FC3: ?RecoveryState_Configure41F50@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Configure41F50_00441f50() {
    __asm {
    L_00441f50:
        movzx edx,dl
    L_00441f53:
        mov dword ptr [eax+230h],edx
    L_00441f59:
        movzx edx,byte ptr [esp+8]
    L_00441f5e:
        mov dword ptr [eax+22Ch],ecx
    L_00441f64:
        movzx ecx,byte ptr [esp+4]
    L_00441f69:
        mov dword ptr [eax+20Ch],edx
    L_00441f6f:
        mov dword ptr [eax+208h],ecx
    L_00441f75:
        mov ecx,dword ptr [eax+228h]
    L_00441f7b:
        xor edx,edx
    L_00441f7d:
        test cl,1
    L_00441f80:
        jne short L_00441fab
    L_00441f82:
        or ecx,1
    L_00441f85:
        mov dword ptr [eax+21Ch],edx
    L_00441f8b:
        mov dword ptr [eax+218h],0FFF0BDC1h
    L_00441f95:
        mov dword ptr [eax+220h],edx
    L_00441f9b:
        mov dword ptr [eax+224h],476F78h
    L_00441fa5:
        mov dword ptr [eax+228h],ecx
    L_00441fab:
        mov dword ptr [eax+21Ch],edx
    L_00441fb1:
        mov dword ptr [eax+220h],edx
    L_00441fb7:
        mov dword ptr [eax+218h],0FFFFFFFFh
    L_00441fc1:
        ret 8
    }
}

// 0x00442220..0x004422EF: ConfigureColorPlaybackState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ConfigureColorPlaybackState_00442220() {
    __asm {
    L_00442220:
        sub esp,0Ch
    L_00442223:
        push ebx
    L_00442224:
        push ebp
    L_00442225:
        push esi
    L_00442226:
        mov esi,dword ptr [esp+1Ch]
    L_0044222a:
        mov dword ptr [eax+100h],esi
    L_00442230:
        xor esi,esi
    L_00442232:
        push edi
    L_00442233:
        xor edi,edi
    L_00442235:
        lea ebp,[eax+0D4h]
    L_0044223b:
        mov dword ptr [ebp],esi
    L_0044223e:
        mov dword ptr [ebp+4],edi
    L_00442241:
        xor ebx,ebx
    L_00442243:
        mov dword ptr [ebp+8],ebx
    L_00442246:
        lea ebp,[eax+0E0h]
    L_0044224c:
        mov dword ptr [ebp],esi
    L_0044224f:
        movzx esi,byte ptr [esp+24h]
    L_00442254:
        mov dword ptr [ebp+4],edi
    L_00442257:
        mov dword ptr [ebp+8],ebx
    L_0044225a:
        mov dword ptr [eax+104h],esi
    L_00442260:
        movzx ebx,byte ptr [ecx+2]
    L_00442264:
        movzx ebp,byte ptr [ecx+1]
    L_00442268:
        movzx ecx,byte ptr [ecx]
    L_0044226b:
        movzx esi,byte ptr [edx+2]
    L_0044226f:
        movzx edi,byte ptr [edx+1]
    L_00442273:
        movzx edx,byte ptr [edx]
    L_00442276:
        mov dword ptr [esp+10h],ecx
    L_0044227a:
        lea ecx,[eax+0BCh]
    L_00442280:
        mov dword ptr [ecx],edx
    L_00442282:
        mov dword ptr [ecx+4],edi
    L_00442285:
        mov dword ptr [ecx+8],esi
    L_00442288:
        mov ecx,dword ptr [esp+10h]
    L_0044228c:
        lea edx,[eax+0C8h]
    L_00442292:
        mov dword ptr [edx],ecx
    L_00442294:
        mov dword ptr [edx+4],ebp
    L_00442297:
        pop edi
    L_00442298:
        mov dword ptr [edx+8],ebx
    L_0044229b:
        mov ecx,dword ptr [eax+0FCh]
    L_004422a1:
        pop esi
    L_004422a2:
        pop ebp
    L_004422a3:
        xor edx,edx
    L_004422a5:
        test cl,1
    L_004422a8:
        pop ebx
    L_004422a9:
        jne short L_004422d4
    L_004422ab:
        or ecx,1
    L_004422ae:
        mov dword ptr [eax+0F0h],edx
    L_004422b4:
        mov dword ptr [eax+0ECh],0FFF0BDC1h
    L_004422be:
        mov dword ptr [eax+0F4h],edx
    L_004422c4:
        mov dword ptr [eax+0F8h],476F78h
    L_004422ce:
        mov dword ptr [eax+0FCh],ecx
    L_004422d4:
        mov dword ptr [eax+0F0h],edx
    L_004422da:
        mov dword ptr [eax+0F4h],edx
    L_004422e0:
        mov dword ptr [eax+0ECh],0FFFFFFFFh
    L_004422ea:
        add esp,0Ch
    L_004422ed:
        ret 8
    }
}

// 0x00442300..0x00442381: RecoveryState_Configure42300
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RecoveryState_Configure42300_00442300() {
    __asm {
    L_00442300:
        mov dword ptr [eax+12Ch],ecx
    L_00442306:
        movzx ecx,byte ptr [esp+4]
    L_0044230b:
        mov dword ptr [eax+130h],ecx
    L_00442311:
        movzx ecx,byte ptr [esp+8]
    L_00442316:
        mov dword ptr [eax+108h],ecx
    L_0044231c:
        movzx ecx,byte ptr [esp+0Ch]
    L_00442321:
        xor edx,edx
    L_00442323:
        mov dword ptr [eax+110h],edx
    L_00442329:
        mov dword ptr [eax+114h],edx
    L_0044232f:
        mov dword ptr [eax+10Ch],ecx
    L_00442335:
        mov ecx,dword ptr [eax+128h]
    L_0044233b:
        test cl,1
    L_0044233e:
        jne short L_00442369
    L_00442340:
        or ecx,1
    L_00442343:
        mov dword ptr [eax+11Ch],edx
    L_00442349:
        mov dword ptr [eax+118h],0FFF0BDC1h
    L_00442353:
        mov dword ptr [eax+120h],edx
    L_00442359:
        mov dword ptr [eax+124h],476F78h
    L_00442363:
        mov dword ptr [eax+128h],ecx
    L_00442369:
        mov dword ptr [eax+11Ch],edx
    L_0044236f:
        mov dword ptr [eax+120h],edx
    L_00442375:
        mov dword ptr [eax+118h],0FFFFFFFFh
    L_0044237f:
        ret 0Ch
    }
}

// 0x00446EB0..0x00446F33: Recovery_CreateTextureFromMemory
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_CreateTextureFromMemory_00446eb0() {
    __asm {
    L_00446eb0:
        push edi
    L_00446eb1:
        mov edi,eax
    L_00446eb3:
        test byte ptr [data_00491d78],1
    L_00446eba:
        je short L_00446edd
    L_00446ebc:
        mov eax,dword ptr [edi*4+46F288h]
    L_00446ec3:
        cmp eax,15h
    L_00446ec6:
        je short L_00446ed8
    L_00446ec8:
        test eax,eax
    L_00446eca:
        je short L_00446ed8
    L_00446ecc:
        cmp eax,14h
    L_00446ecf:
        jne short L_00446edd
    L_00446ed1:
        mov edi,3
    L_00446ed6:
        jmp short L_00446edd
    L_00446ed8:
        mov edi,5
    L_00446edd:
        mov eax,dword ptr [esp+0Ch]
    L_00446ee1:
        mov ecx,dword ptr [edi*4+46F288h]
    L_00446ee8:
        push esi
    L_00446ee9:
        push 0
    L_00446eeb:
        push 0
    L_00446eed:
        push eax
    L_00446eee:
        mov eax,dword ptr [esp+20h]
    L_00446ef2:
        push 0FFFFFFFFh
    L_00446ef4:
        push 1
    L_00446ef6:
        push 1
    L_00446ef8:
        push ecx
    L_00446ef9:
        mov ecx,dword ptr [esi+8]
    L_00446efc:
        push 0
    L_00446efe:
        push 0
    L_00446f00:
        push edx
    L_00446f01:
        mov edx,dword ptr [esi+4]
    L_00446f04:
        push eax
    L_00446f05:
        mov eax,dword ptr [data_00491c30]
    L_00446f0a:
        push ecx
    L_00446f0b:
        push edx
    L_00446f0c:
        push eax
    L_00446f0d:
        call asm_D3DXCreateTextureFromFileInMemoryEx_004521ca
    L_00446f12:
        test eax,eax
    L_00446f14:
        je short L_00446f1d
    L_00446f16:
        or eax,0FFFFFFFFh
    L_00446f19:
        pop edi
    L_00446f1a:
        ret 0Ch
    L_00446f1d:
        mov eax,esi
    L_00446f1f:
        call asm_FUN_004465b0_004465b0
    L_00446f24:
        mov ecx,dword ptr [edi*4+46F2A0h]
    L_00446f2b:
        mov dword ptr [esi+0Ch],ecx
    L_00446f2e:
        xor eax,eax
    L_00446f30:
        pop edi
    L_00446f31:
        ret 0Ch
    }
}

// 0x00447280..0x004472D1: Recovery_LoadCachedResource
// Return the resource cached for the given index, loading it through 0x004470C0
// when the slot is still empty. The load runs on a worker thread: the entry is
// flagged busy (+0x124) and this side waits a millisecond at a time until the
// worker clears the flag. A progress byte with its sign bit set at 0x00491FF4
// aborts the wait. The index arrives in ECX and the cache table in EDX, with the
// resource name on the stack, matching the retail __fastcall layout.
struct CachedResource {
    unsigned char unknown_000[0x124];
    int busy;                    // +0x124, one while a loader still owns the entry
};

typedef CachedResource* (__stdcall* ResourceLoadFn)(void* owner, int index, const char* name);
// kernel32!Sleep through the import slot the image keeps, loaded once.
typedef void (__stdcall* SleepFn)(unsigned long milliseconds);

CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name) {
    CachedResource* entry = *(CachedResource**)((char*)owner + 0x3AD06C + index * 4);
    if (entry != 0)
        return entry;
    entry = ((ResourceLoadFn)asm_FUN_004470c0_004470c0)(owner, index, name);
    if (entry == 0)
        return 0;
    SleepFn sleep = *(SleepFn*)&data_004660ac;
    entry->busy = 1;
    do {
        if (data_00491ff4 & 0x80)
            break;
        sleep(1);
    } while (entry->busy != 0);
    return entry;
}

// 0x004479D0..0x00447A4E: Recovery_DispatchRandomText
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_DispatchRandomText_004479d0() {
    __asm {
    L_004479d0:
        sub esp,10h
    L_004479d3:
        push ebp
    L_004479d4:
        mov ebp,dword ptr [esp+20h]
    L_004479d8:
        push esi
    L_004479d9:
        mov esi,eax
    L_004479db:
        test esi,esi
    L_004479dd:
        jg short L_004479e6
    L_004479df:
        mov esi,11h
    L_004479e4:
        jmp short L_004479eb
    L_004479e6:
        cmp esi,8
    L_004479e9:
        jle short L_00447a47
    L_004479eb:
        fld dword ptr [edi+8]
    L_004479ee:
        call asm_FUN_00463b2c_00463b2c
    L_004479f3:
        fld dword ptr [edi+0Ch]
    L_004479f6:
        mov dword ptr [esp+8],eax
    L_004479fa:
        call asm_FUN_00463b2c_00463b2c
    L_004479ff:
        fld dword ptr [edi+10h]
    L_00447a02:
        mov dword ptr [esp+0Ch],eax
    L_00447a06:
        call asm_FUN_00463b2c_00463b2c
    L_00447a0b:
        fld dword ptr [edi+14h]
    L_00447a0e:
        mov dword ptr [esp+10h],eax
    L_00447a12:
        call asm_FUN_00463b2c_00463b2c
    L_00447a17:
        mov ecx,dword ptr [esp+20h]
    L_00447a1b:
        mov dword ptr [esp+14h],eax
    L_00447a1f:
        mov eax,dword ptr [esp+28h]
    L_00447a23:
        test eax,eax
    L_00447a25:
        mov eax,dword ptr [esp+1Ch]
    L_00447a29:
        push eax
    L_00447a2a:
        push ebx
    L_00447a2b:
        push ebp
    L_00447a2c:
        push esi
    L_00447a2d:
        lea edx,[esp+18h]
    L_00447a31:
        push ecx
    L_00447a32:
        push edx
    L_00447a33:
        jne short L_00447a42
    L_00447a35:
        call asm_FUN_00437db0_00437db0
    L_00447a3a:
        pop esi
    L_00447a3b:
        pop ebp
    L_00447a3c:
        add esp,10h
    L_00447a3f:
        ret 10h
    L_00447a42:
        call asm_FUN_00437fe0_00437fe0
    L_00447a47:
        pop esi
    L_00447a48:
        pop ebp
    L_00447a49:
        add esp,10h
    L_00447a4c:
        ret 10h
    }
}

// 0x00447A50..0x00447ADC: Recovery_MarkLogState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_MarkLogState_00447a50() {
    __asm {
    L_00447a50:
        sub esp,84h
    L_00447a56:
        mov eax,dword ptr [data_00473660]
    L_00447a5b:
        mov ecx,dword ptr [esp+90h]
    L_00447a62:
        xor eax,esp
    L_00447a64:
        push ebx
    L_00447a65:
        push ebp
    L_00447a66:
        movzx ebp,byte ptr [esi+3A0h]
    L_00447a6d:
        mov dword ptr [esp+88h],eax
    L_00447a74:
        push edi
    L_00447a75:
        lea eax,[esp+0A0h]
    L_00447a7c:
        push eax
    L_00447a7d:
        push ecx
    L_00447a7e:
        lea edx,[esp+14h]
    L_00447a82:
        push edx
    L_00447a83:
        call asm_vsprintf_004524a6
    L_00447a88:
        mov eax,dword ptr [esi+360h]
    L_00447a8e:
        mov ecx,dword ptr [esp+0A4h]
    L_00447a95:
        mov edi,dword ptr [esi+394h]
    L_00447a9b:
        mov edx,dword ptr [edi+4]
    L_00447a9e:
        add esp,0Ch
    L_00447aa1:
        shr eax,1
    L_00447aa3:
        and eax,1
    L_00447aa6:
        push eax
    L_00447aa7:
        push ecx
    L_00447aa8:
        push 0
    L_00447aaa:
        push edx
    L_00447aab:
        lea ebx,[esp+1Ch]
    L_00447aaf:
        mov eax,ebp
    L_00447ab1:
        call asm_Recovery_DispatchRandomText_004479d0
    L_00447ab6:
        mov eax,dword ptr [esi+35Ch]
    L_00447abc:
        mov ecx,dword ptr [esp+8Ch]
    L_00447ac3:
        pop edi
    L_00447ac4:
        pop ebp
    L_00447ac5:
        or eax,1
    L_00447ac8:
        pop ebx
    L_00447ac9:
        xor ecx,esp
    L_00447acb:
        mov dword ptr [esi+35Ch],eax
    L_00447ad1:
        call asm_security_check_cookie_00458ea5
    L_00447ad6:
        add esp,84h
    L_00447adc:
        ret
    }
}

// 0x0044CE80..0x0044CEF5: Recovery_InitializeInterfaceArray
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeInterfaceArray_0044ce80() {
    __asm {
    L_0044ce80:
        push ebx
    L_0044ce81:
        mov ebx,eax
    L_0044ce83:
        lea eax,[edi*4]
    L_0044ce8a:
        push eax
    L_0044ce8b:
        mov dword ptr [esi],4705D8h
    L_0044ce91:
        call asm_operator_new_00452493
    L_0044ce96:
        mov dword ptr [esi+4],eax
    L_0044ce99:
        add esp,4
    L_0044ce9c:
        xor eax,eax
    L_0044ce9e:
        test edi,edi
    L_0044cea0:
        jbe short L_0044ceb0
    L_0044cea2:
        mov edx,dword ptr [ebx+eax*4]
    L_0044cea5:
        mov ecx,dword ptr [esi+4]
    L_0044cea8:
        mov dword ptr [ecx+eax*4],edx
    L_0044ceab:
        inc eax
    L_0044ceac:
        cmp eax,edi
    L_0044ceae:
        jb short L_0044cea2
    L_0044ceb0:
        mov eax,dword ptr [esp+8]
    L_0044ceb4:
        mov ecx,dword ptr [esp+0Ch]
    L_0044ceb8:
        mov edx,dword ptr [esi+4]
    L_0044cebb:
        mov dword ptr [esi+8],eax
    L_0044cebe:
        mov dword ptr [esi+10h],edi
    L_0044cec1:
        mov dword ptr [esi+0Ch],ecx
    L_0044cec4:
        mov eax,dword ptr [edx]
    L_0044cec6:
        push 0
    L_0044cec8:
        push eax
    L_0044cec9:
        mov eax,esi
    L_0044cecb:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044ced0:
        xor ebx,ebx
    L_0044ced2:
        test edi,edi
    L_0044ced4:
        jbe short L_0044cee9
    L_0044ced6:
        mov ecx,dword ptr [esi+4]
    L_0044ced9:
        mov eax,dword ptr [ecx+ebx*4]
    L_0044cedc:
        mov edx,dword ptr [eax]
    L_0044cede:
        push 0
    L_0044cee0:
        push eax
    L_0044cee1:
        call dword ptr [edx+34h]
    L_0044cee4:
        inc ebx
    L_0044cee5:
        cmp ebx,edi
    L_0044cee7:
        jb short L_0044ced6
    L_0044cee9:
        mov dword ptr [esi+30h],0
    L_0044cef0:
        mov eax,esi
    L_0044cef2:
        pop ebx
    L_0044cef3:
        ret 8
    }
}

// 0x0044CF00 - scalar deleting destructor for the owned-array object: release
// the owned interfaces first, then free the object when the caller asks for it.
// The delete flag is the retail first stack argument, so the second __fastcall
// register argument (EDX) is unused.
void* __fastcall PlatformOwnedArray_DeletingDestructor(PlatformOwnedArray* owner,
                                                       unsigned int unused, unsigned int flags) {
    Platform_ReleaseOwnedArray(owner);
    if (flags & 1)
        operator delete(owner);
    return owner;
}

// 0x0044D080 - release everything the owned-array object holds: every interface
// in the owned array, the array itself, and the playback device. The object
// returns to the base table at 0x004705D8 first.
//
// th10/platform/sound_buffer.hpp names only the vtable prefix that the
// sound-buffer leaves touch, so the complete layout used here is declared
// locally.
struct OwnedInterface {
    virtual unsigned long __stdcall QueryInterface(void* id, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
};

struct OwnedPlaybackDevice {
    unsigned int reserved_00[0x1E];   // +0x00..+0x77
    unsigned int state;               // +0x78, one while the handle is owned
    unsigned int reserved_7C[4];      // +0x7C..+0x8B
    HANDLE handle;                    // +0x8C
};

struct PlatformOwnedArrayFields {
    void* vtable;                     // +0x00
    OwnedInterface** elements;        // +0x04, owned interface pointers
    unsigned int reserved_08;         // +0x08
    OwnedPlaybackDevice* device;      // +0x0C, owned playback device
    unsigned int element_count;       // +0x10
};

void __fastcall Platform_ReleaseOwnedArray(PlatformOwnedArray* owner) {
    PlatformOwnedArrayFields* fields = (PlatformOwnedArrayFields*)owner;
    fields->vtable = (void*)0x004705D8;
    for (unsigned int index = 0; index < fields->element_count; ++index) {
        if (fields->elements[index]) {
            fields->elements[index]->Release();
            fields->elements[index] = 0;
        }
    }
    if (fields->elements) {
        operator delete(fields->elements);
        fields->elements = 0;
    }
    OwnedPlaybackDevice* device = fields->device;
    if (device) {
        if (device->state == 1) {
            CloseHandle(device->handle);
            device->handle = (HANDLE)-1;
        }
        operator delete(device);
        fields->device = 0;
    }
}

// 0x0044D300..0x0044D361: ?Platform_RunInterface@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_RunInterface_0044d300() {
    __asm {
    L_0044d300:
        push ecx
    L_0044d301:
        test esi,esi
    L_0044d303:
        jne short L_0044d30c
    L_0044d305:
        mov eax,800401F0h
    L_0044d30a:
        pop ecx
    L_0044d30b:
        ret
    L_0044d30c:
        test ebx,ebx
    L_0044d30e:
        je short L_0044d316
    L_0044d310:
        mov dword ptr [ebx],0
    L_0044d316:
        mov eax,dword ptr [esi]
    L_0044d318:
        lea ecx,[esp]
    L_0044d31b:
        push ecx
    L_0044d31c:
        push esi
    L_0044d31d:
        call dword ptr [eax+24h]
    L_0044d320:
        test eax,eax
    L_0044d322:
        jl short L_0044d360
    L_0044d324:
        test byte ptr [esp],2
    L_0044d328:
        je short L_0044d35b
    L_0044d32a:
        push edi
    L_0044d32b:
        mov edi,dword ptr [data_004660ac]
    L_0044d331:
        mov edx,dword ptr [esi]
    L_0044d333:
        push esi
    L_0044d334:
        call dword ptr [edx+50h]
    L_0044d337:
        cmp eax,88780096h
    L_0044d33c:
        jne short L_0044d342
    L_0044d33e:
        push 0Ah
    L_0044d340:
        call edi
    L_0044d342:
        mov eax,dword ptr [esi]
    L_0044d344:
        push esi
    L_0044d345:
        call dword ptr [eax+50h]
    L_0044d348:
        test eax,eax
    L_0044d34a:
        jne short L_0044d331
    L_0044d34c:
        test ebx,ebx
    L_0044d34e:
        pop edi
    L_0044d34f:
        je short L_0044d357
    L_0044d351:
        mov dword ptr [ebx],1
    L_0044d357:
        xor eax,eax
    L_0044d359:
        pop ecx
    L_0044d35a:
        ret
    L_0044d35b:
        mov eax,1
    L_0044d360:
        pop ecx
    L_0044d361:
        ret
    }
}

// 0x0044D370..0x0044D3D6: ?Platform_FindAvailable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_FindAvailable_0044d370() {
    __asm {
    L_0044d370:
        push ecx
    L_0044d371:
        mov eax,dword ptr [edi+4]
    L_0044d374:
        test eax,eax
    L_0044d376:
        jne short L_0044d37c
    L_0044d378:
        xor eax,eax
    L_0044d37a:
        pop ecx
    L_0044d37b:
        ret
    L_0044d37c:
        mov eax,dword ptr [edi+10h]
    L_0044d37f:
        push esi
    L_0044d380:
        xor esi,esi
    L_0044d382:
        test eax,eax
    L_0044d384:
        jbe short L_0044d3b6
    L_0044d386:
        mov eax,dword ptr [edi+4]
    L_0044d389:
        cmp dword ptr [eax+esi*4],0
    L_0044d38d:
        je short L_0044d3ae
    L_0044d38f:
        mov ecx,eax
    L_0044d391:
        mov dword ptr [esp+4],0
    L_0044d399:
        mov eax,dword ptr [ecx+esi*4]
    L_0044d39c:
        mov edx,dword ptr [eax]
    L_0044d39e:
        lea ecx,[esp+4]
    L_0044d3a2:
        push ecx
    L_0044d3a3:
        push eax
    L_0044d3a4:
        call dword ptr [edx+24h]
    L_0044d3a7:
        test byte ptr [esp+4],1
    L_0044d3ac:
        je short L_0044d3b6
    L_0044d3ae:
        mov eax,dword ptr [edi+10h]
    L_0044d3b1:
        inc esi
    L_0044d3b2:
        cmp esi,eax
    L_0044d3b4:
        jb short L_0044d386
    L_0044d3b6:
        cmp esi,dword ptr [edi+10h]
    L_0044d3b9:
        je short L_0044d3c4
    L_0044d3bb:
        mov edx,dword ptr [edi+4]
    L_0044d3be:
        mov eax,dword ptr [edx+esi*4]
    L_0044d3c1:
        pop esi
    L_0044d3c2:
        pop ecx
    L_0044d3c3:
        ret
    L_0044d3c4:
        call asm_rand_0045371b
    L_0044d3c9:
        xor edx,edx
    L_0044d3cb:
        div dword ptr [edi+10h]
    L_0044d3ce:
        mov eax,dword ptr [edi+4]
    L_0044d3d1:
        pop esi
    L_0044d3d2:
        mov eax,dword ptr [eax+edx*4]
    L_0044d3d5:
        pop ecx
    L_0044d3d6:
        ret
    }
}

// 0x0044D4E0..0x0044D549: ?Platform_SetOperationDeadline@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_SetOperationDeadline_0044d4e0() {
    __asm {
    L_0044d4e0:
        mov ecx,dword ptr [data_00497854]
    L_0044d4e6:
        test ecx,ecx
    L_0044d4e8:
        je short L_0044d537
    L_0044d4ea:
        fild dword ptr [data_00497854]
    L_0044d4f0:
        mov ecx,dword ptr [esp+4]
    L_0044d4f4:
        mov eax,dword ptr [eax+4]
    L_0044d4f7:
        add ecx,1388h
    L_0044d4fd:
        fmul dword ptr [data_00470b00]
    L_0044d503:
        mov dword ptr [esp+4],ecx
    L_0044d507:
        push esi
    L_0044d508:
        mov esi,dword ptr [eax]
    L_0044d50a:
        fsubr dword ptr [data_00470afc]
    L_0044d510:
        push edi
    L_0044d511:
        mov edi,dword ptr [esi]
    L_0044d513:
        fld st(0)
    L_0044d515:
        fmul st,st(1)
    L_0044d517:
        fsubr dword ptr [data_00470afc]
    L_0044d51d:
        fimul dword ptr [esp+0Ch]
    L_0044d521:
        call asm_FUN_00463b2c_00463b2c
    L_0044d526:
        fstp st(0)
    L_0044d528:
        sub eax,1388h
    L_0044d52d:
        push eax
    L_0044d52e:
        push esi
    L_0044d52f:
        call dword ptr [edi+3Ch]
    L_0044d532:
        pop edi
    L_0044d533:
        pop esi
    L_0044d534:
        ret 4
    L_0044d537:
        mov edx,dword ptr [eax+4]
    L_0044d53a:
        mov eax,dword ptr [edx]
    L_0044d53c:
        mov ecx,dword ptr [eax]
    L_0044d53e:
        push 0FFFFD8F0h
    L_0044d543:
        push eax
    L_0044d544:
        call dword ptr [ecx+3Ch]
    L_0044d547:
        ret 4
    }
}

// 0x0044D550..0x0044D5A1: ?Platform_AggregateInterfaces@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_AggregateInterfaces_0044d550() {
    __asm {
    L_0044d550:
        mov eax,dword ptr [edi+4]
    L_0044d553:
        test eax,eax
    L_0044d555:
        jne short L_0044d55d
    L_0044d557:
        mov eax,800401F0h
    L_0044d55c:
        ret
    L_0044d55d:
        mov eax,dword ptr [edi+10h]
    L_0044d560:
        push ebx
    L_0044d561:
        push esi
    L_0044d562:
        xor ebx,ebx
    L_0044d564:
        xor esi,esi
    L_0044d566:
        test eax,eax
    L_0044d568:
        mov dword ptr [edi+30h],ebx
    L_0044d56b:
        jbe short L_0044d596
    L_0044d56d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0044d570:
        mov eax,dword ptr [edi+4]
    L_0044d573:
        mov eax,dword ptr [eax+esi*4]
    L_0044d576:
        mov ecx,dword ptr [eax]
    L_0044d578:
        push eax
    L_0044d579:
        call dword ptr [ecx+48h]
    L_0044d57c:
        mov edx,dword ptr [edi+4]
    L_0044d57f:
        or ebx,eax
    L_0044d581:
        mov eax,dword ptr [edx+esi*4]
    L_0044d584:
        mov ecx,dword ptr [eax]
    L_0044d586:
        push 0
    L_0044d588:
        push eax
    L_0044d589:
        call dword ptr [ecx+34h]
    L_0044d58c:
        or ebx,eax
    L_0044d58e:
        mov eax,dword ptr [edi+10h]
    L_0044d591:
        inc esi
    L_0044d592:
        cmp esi,eax
    L_0044d594:
        jb short L_0044d570
    L_0044d596:
        pop esi
    L_0044d597:
        mov eax,ebx
    L_0044d599:
        mov dword ptr [edi+1Ch],0
    L_0044d5a0:
        pop ebx
    L_0044d5a1:
        ret
    }
}

// 0x0044D5D0..0x0044D5F8: Platform_InvokeConfigured
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_InvokeConfigured_0044d5d0() {
    __asm {
    L_0044d5d0:
        mov ecx,dword ptr [eax+4]
    L_0044d5d3:
        test ecx,ecx
    L_0044d5d5:
        jne short L_0044d5dd
    L_0044d5d7:
        mov eax,800401F0h
    L_0044d5dc:
        ret
    L_0044d5dd:
        mov ecx,dword ptr [ecx]
    L_0044d5df:
        push esi
    L_0044d5e0:
        mov esi,dword ptr [eax+24h]
    L_0044d5e3:
        mov dword ptr [eax+30h],1
    L_0044d5ea:
        mov eax,dword ptr [eax+20h]
    L_0044d5ed:
        mov edx,dword ptr [ecx]
    L_0044d5ef:
        push esi
    L_0044d5f0:
        push eax
    L_0044d5f1:
        push 0
    L_0044d5f3:
        push ecx
    L_0044d5f4:
        call dword ptr [edx+30h]
    L_0044d5f7:
        pop esi
    L_0044d5f8:
        ret
    }
}

// 0x0044D600..0x0044D63C: ?Platform_QueryInterfaces@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_QueryInterfaces_0044d600() {
    __asm {
    L_0044d600:
        mov eax,dword ptr [edi+4]
    L_0044d603:
        test eax,eax
    L_0044d605:
        jne short L_0044d60d
    L_0044d607:
        mov eax,800401F0h
    L_0044d60c:
        ret
    L_0044d60d:
        mov eax,dword ptr [edi+10h]
    L_0044d610:
        push ebx
    L_0044d611:
        push esi
    L_0044d612:
        xor ebx,ebx
    L_0044d614:
        xor esi,esi
    L_0044d616:
        test eax,eax
    L_0044d618:
        jbe short L_0044d638
    L_0044d61a:
        lea ebx,[ebx+force_disp32_zero]
    L_0044d620:
        mov eax,dword ptr [edi+4]
    L_0044d623:
        mov eax,dword ptr [eax+esi*4]
    L_0044d626:
        mov ecx,dword ptr [eax]
    L_0044d628:
        push 0
    L_0044d62a:
        push eax
    L_0044d62b:
        call dword ptr [ecx+34h]
    L_0044d62e:
        or ebx,eax
    L_0044d630:
        mov eax,dword ptr [edi+10h]
    L_0044d633:
        inc esi
    L_0044d634:
        cmp esi,eax
    L_0044d636:
        jb short L_0044d620
    L_0044d638:
        pop esi
    L_0044d639:
        mov eax,ebx
    L_0044d63b:
        pop ebx
    L_0044d63c:
        ret
    }
}

// 0x0044D6A0..0x0044D70C: Recovery_InitializeSingleInterface
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeSingleInterface_0044d6a0() {
    __asm {
    L_0044d6a0:
        push edi
    L_0044d6a1:
        push 4
    L_0044d6a3:
        mov dword ptr [esi],4705D8h
    L_0044d6a9:
        call asm_operator_new_00452493
    L_0044d6ae:
        mov ecx,dword ptr [esp+0Ch]
    L_0044d6b2:
        mov edx,dword ptr [esp+10h]
    L_0044d6b6:
        mov dword ptr [esi+4],eax
    L_0044d6b9:
        mov dword ptr [eax],ecx
    L_0044d6bb:
        mov eax,dword ptr [esp+14h]
    L_0044d6bf:
        mov ecx,dword ptr [esi+4]
    L_0044d6c2:
        add esp,4
    L_0044d6c5:
        mov dword ptr [esi+0Ch],eax
    L_0044d6c8:
        mov dword ptr [esi+8],edx
    L_0044d6cb:
        mov dword ptr [esi+10h],1
    L_0044d6d2:
        mov edx,dword ptr [ecx]
    L_0044d6d4:
        xor edi,edi
    L_0044d6d6:
        push edi
    L_0044d6d7:
        push edx
    L_0044d6d8:
        mov eax,esi
    L_0044d6da:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044d6df:
        mov eax,dword ptr [esi+4]
    L_0044d6e2:
        mov eax,dword ptr [eax]
    L_0044d6e4:
        mov ecx,dword ptr [eax]
    L_0044d6e6:
        push edi
    L_0044d6e7:
        push eax
    L_0044d6e8:
        call dword ptr [ecx+34h]
    L_0044d6eb:
        mov edx,dword ptr [esp+14h]
    L_0044d6ef:
        mov dword ptr [esi+30h],edi
    L_0044d6f2:
        mov dword ptr [esi+5Ch],edi
    L_0044d6f5:
        mov dword ptr [esi+60h],edi
    L_0044d6f8:
        mov dword ptr [esi+64h],edi
    L_0044d6fb:
        mov dword ptr [esi+68h],edi
    L_0044d6fe:
        mov dword ptr [esi],4705D4h
    L_0044d704:
        mov dword ptr [esi+6Ch],edx
    L_0044d707:
        mov eax,esi
    L_0044d709:
        pop edi
    L_0044d70a:
        ret 10h
    }
}

// 0x0044D710 - scalar deleting destructor for the sound-buffer object: restore
// the derived table through its base destructor, then free the object on
// request. The delete flag is the retail first stack argument, so the second
// __fastcall register argument (EDX) is unused.
void* __fastcall SoundBuffer_DeletingDestructor(SoundBuffer* sound_buffer, unsigned int unused,
                                                unsigned int flags) {
    SoundBuffer_DestructBaseRetail(sound_buffer);
    if (flags & 1)
        operator delete(sound_buffer);
    return sound_buffer;
}

// 0x0044DCA0..0x0044DCED: ?Platform_SelectStreamRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_SelectStreamRecord_0044dca0() {
    __asm {
    L_0044dca0:
        mov eax,dword ptr [esi+7Ch]
    L_0044dca3:
        test eax,eax
    L_0044dca5:
        jne short L_0044dcb2
    L_0044dca7:
        mov eax,dword ptr [esi+8Ch]
    L_0044dcad:
        cmp eax,0FFFFFFFFh
    L_0044dcb0:
        jne short L_0044dcb8
    L_0044dcb2:
        mov eax,80004005h
    L_0044dcb7:
        ret
    L_0044dcb8:
        test eax,eax
    L_0044dcba:
        mov dword ptr [esi+90h],ecx
    L_0044dcc0:
        je short L_0044dce5
    L_0044dcc2:
        mov ecx,dword ptr [ecx+10h]
    L_0044dcc5:
        mov edx,dword ptr [data_004977a4]
    L_0044dccb:
        push 0
    L_0044dccd:
        push 0
    L_0044dccf:
        add ecx,edx
    L_0044dcd1:
        push ecx
    L_0044dcd2:
        push eax
    L_0044dcd3:
        call dword ptr [data_004660c8]
    L_0044dcd9:
        mov edx,dword ptr [esi+90h]
    L_0044dcdf:
        mov eax,dword ptr [edx+1Ch]
    L_0044dce2:
        mov dword ptr [esi+8],eax
    L_0044dce5:
        mov ecx,dword ptr [esi+8]
    L_0044dce8:
        mov dword ptr [esi+2Ch],ecx
    L_0044dceb:
        xor eax,eax
    L_0044dced:
        ret
    }
}
