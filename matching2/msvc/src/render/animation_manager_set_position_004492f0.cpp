#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004492F0..0x00449349: ?AnimationManager_SetPosition@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_SetPosition_004492f0() {
    __asm {
    L_004492f0:
        mov eax,dword ptr [esp+4]
    L_004492f4:
        push eax
    L_004492f5:
        call asm_AnimationManager_Find_004491c0
    L_004492fa:
        test eax,eax
    L_004492fc:
        je short L_00449347
    L_004492fe:
        push edi
    L_004492ff:
        mov edx,esi
    L_00449301:
        mov edi,dword ptr [edx]
    L_00449303:
        lea ecx,[eax+340h]
    L_00449309:
        mov dword ptr [ecx],edi
    L_0044930b:
        mov edi,dword ptr [edx+4]
    L_0044930e:
        mov dword ptr [ecx+4],edi
    L_00449311:
        mov edx,dword ptr [edx+8]
    L_00449314:
        mov dword ptr [ecx+8],edx
    L_00449317:
        mov ecx,dword ptr [eax+18h]
    L_0044931a:
        test ecx,ecx
    L_0044931c:
        jne short L_00449346
    L_0044931e:
        mov eax,dword ptr [eax+14h]
    L_00449321:
        test eax,eax
    L_00449323:
        je short L_00449346
    L_00449325:
        mov ecx,dword ptr [eax]
    L_00449327:
        add ecx,340h
    L_0044932d:
        mov edx,esi
    L_0044932f:
        mov edi,dword ptr [edx]
    L_00449331:
        mov dword ptr [ecx],edi
    L_00449333:
        mov edi,dword ptr [edx+4]
    L_00449336:
        mov dword ptr [ecx+4],edi
    L_00449339:
        mov edx,dword ptr [edx+8]
    L_0044933c:
        mov dword ptr [ecx+8],edx
    L_0044933f:
        mov eax,dword ptr [eax+4]
    L_00449342:
        test eax,eax
    L_00449344:
        jne short L_00449325
    L_00449346:
        pop edi
    L_00449347:
        ret 4
    }
}
