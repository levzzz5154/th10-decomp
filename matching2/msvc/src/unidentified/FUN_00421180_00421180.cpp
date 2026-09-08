#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421180..0x004212F0: FUN_00421180
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421180_00421180() {
    __asm {
    L_00421180:
        push ebp
    L_00421181:
        mov ebp,dword ptr [esp+8]
    L_00421185:
        mov eax,dword ptr [ebp+6FCh]
    L_0042118b:
        test eax,eax
    L_0042118d:
        push edi
    L_0042118e:
        jne asm_target_004212b6
    L_00421194:
        mov edi,dword ptr [ebp+3C8h]
    L_0042119a:
        push ebx
    L_0042119b:
        push esi
    L_0042119c:
        mov esi,dword ptr [data_00491c10]
    L_004211a2:
        call asm_FUN_00449950_00449950
    L_004211a7:
        mov ebx,eax
    L_004211a9:
        mov eax,dword ptr [ebx+35Ch]
    L_004211af:
        push 0
    L_004211b1:
        or eax,40000000h
    L_004211b6:
        push ebx
    L_004211b7:
        mov ecx,edi
    L_004211b9:
        mov dword ptr [ebx+20h],0Fh
    L_004211c0:
        mov dword ptr [ebx+35Ch],eax
    L_004211c6:
        call asm_FUN_00449870_00449870
    L_004211cb:
        mov esi,dword ptr [data_00491c10]
    L_004211d1:
        lea eax,[esp+14h]
    L_004211d5:
        mov edx,esi
    L_004211d7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_004211dc:
        mov eax,dword ptr [esp+14h]
    L_004211e0:
        mov dword ptr [data_00477824],eax
    L_004211e5:
        mov edi,dword ptr [ebp+3C8h]
    L_004211eb:
        call asm_FUN_00449950_00449950
    L_004211f0:
        mov ebx,eax
    L_004211f2:
        mov ecx,dword ptr [ebx+35Ch]
    L_004211f8:
        or ecx,40000000h
    L_004211fe:
        push 1
    L_00421200:
        mov dword ptr [ebx+35Ch],ecx
    L_00421206:
        push ebx
    L_00421207:
        mov ecx,edi
    L_00421209:
        mov dword ptr [ebx+20h],0Fh
    L_00421210:
        call asm_FUN_00449870_00449870
    L_00421215:
        mov esi,dword ptr [data_00491c10]
    L_0042121b:
        lea eax,[esp+14h]
    L_0042121f:
        mov edx,esi
    L_00421221:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00421226:
        mov ecx,dword ptr [esp+14h]
    L_0042122a:
        mov dword ptr [data_00477828],ecx
    L_00421230:
        mov edi,dword ptr [ebp+3C8h]
    L_00421236:
        call asm_FUN_00449950_00449950
    L_0042123b:
        mov ebx,eax
    L_0042123d:
        mov edx,dword ptr [ebx+35Ch]
    L_00421243:
        push 2
    L_00421245:
        or edx,40000000h
    L_0042124b:
        push ebx
    L_0042124c:
        mov ecx,edi
    L_0042124e:
        mov dword ptr [ebx+20h],0Fh
    L_00421255:
        mov dword ptr [ebx+35Ch],edx
    L_0042125b:
        call asm_FUN_00449870_00449870
    L_00421260:
        mov edi,dword ptr [data_00491c10]
    L_00421266:
        lea eax,[esp+14h]
    L_0042126a:
        mov edx,edi
    L_0042126c:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00421271:
        mov edx,dword ptr [esp+14h]
    L_00421275:
        mov esi,dword ptr [esp+18h]
    L_00421279:
        mov dword ptr [data_0047782c],edx
    L_0042127f:
        mov dword ptr [ebp+6FCh],1
    L_00421289:
        mov eax,dword ptr [data_00477824]
    L_0042128e:
        push eax
    L_0042128f:
        mov edx,edi
    L_00421291:
        call asm_AnimationManager_SetPosition_004492f0
    L_00421296:
        mov ecx,dword ptr [data_00477828]
    L_0042129c:
        push ecx
    L_0042129d:
        mov edx,edi
    L_0042129f:
        call asm_AnimationManager_SetPosition_004492f0
    L_004212a4:
        mov edx,dword ptr [data_0047782c]
    L_004212aa:
        push edx
    L_004212ab:
        mov edx,edi
    L_004212ad:
        call asm_AnimationManager_SetPosition_004492f0
    L_004212b2:
        pop esi
    L_004212b3:
        pop ebx
    L_004212b4:
        jmp short L_004212bc
    L_004212b6:
        mov edi,dword ptr [data_00491c10]
    L_004212bc:
        mov ecx,dword ptr [edi]
    L_004212be:
        xor eax,eax
    L_004212c0:
        cmp ecx,eax
    L_004212c2:
        jge short L_004212ec
    L_004212c4:
        mov edx,280h
    L_004212c9:
        mov ecx,1E0h
    L_004212ce:
        mov dword ptr [edi],8
    L_004212d4:
        mov dword ptr [edi+2Ch],eax
    L_004212d7:
        mov dword ptr [edi+30h],eax
    L_004212da:
        mov dword ptr [edi+34h],edx
    L_004212dd:
        mov dword ptr [edi+38h],ecx
    L_004212e0:
        mov dword ptr [edi+3Ch],eax
    L_004212e3:
        mov dword ptr [edi+40h],eax
    L_004212e6:
        mov dword ptr [edi+44h],edx
    L_004212e9:
        mov dword ptr [edi+48h],ecx
    L_004212ec:
        pop edi
    L_004212ed:
        pop ebp
    L_004212ee:
        ret 8
    }
}
