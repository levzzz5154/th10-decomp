#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420EA0..0x00420F15: FUN_00420ea0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420ea0_00420ea0() {
    __asm {
    L_00420ea0:
        push ebx
    L_00420ea1:
        push ebp
    L_00420ea2:
        mov ebp,dword ptr [esp+0Ch]
    L_00420ea6:
        push esi
    L_00420ea7:
        lea ebx,[edi+6DCh]
    L_00420ead:
        push ebx
    L_00420eae:
        call dword ptr [data_004660b0]
    L_00420eb4:
        mov dl,byte ptr [edi+6FAh]
    L_00420eba:
        inc dl
    L_00420ebc:
        lea esi,[edi+62Ch]
    L_00420ec2:
        mov byte ptr [edi+6FAh],dl
    L_00420ec8:
        call asm_Platform_StopWorker_0044c150
    L_00420ecd:
        mov ecx,dword ptr [esp+14h]
    L_00420ed1:
        lea eax,[esi+8]
    L_00420ed4:
        push eax
    L_00420ed5:
        push 0
    L_00420ed7:
        push ecx
    L_00420ed8:
        push ebp
    L_00420ed9:
        push 0
    L_00420edb:
        push 0
    L_00420edd:
        mov dword ptr [esi+18h],ebp
    L_00420ee0:
        mov dword ptr [esi+10h],1
    L_00420ee7:
        mov dword ptr [esi+0Ch],0
    L_00420eee:
        call asm_beginthreadex_00453683
    L_00420ef3:
        add esp,18h
    L_00420ef6:
        push ebx
    L_00420ef7:
        mov dword ptr [esi+4],eax
    L_00420efa:
        call dword ptr [data_004660b4]
    L_00420f00:
        mov al,byte ptr [edi+6FAh]
    L_00420f06:
        pop esi
    L_00420f07:
        dec al
    L_00420f09:
        pop ebp
    L_00420f0a:
        mov byte ptr [edi+6FAh],al
    L_00420f10:
        xor eax,eax
    L_00420f12:
        pop ebx
    L_00420f13:
        ret 8
    }
}
