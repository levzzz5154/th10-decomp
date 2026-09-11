#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004224C0..0x00422653: FUN_004224c0
// Naked body preserves the retail register/stack ABI.

// 0x00423570..0x0042367C: FUN_00423570
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00423570_00423570() {
    __asm {
    L_00423570:
        mov eax,dword ptr [data_00474c7c]
    L_00423575:
        push ebp
    L_00423576:
        mov ebp,dword ptr [esp+8]
    L_0042357a:
        push esi
    L_0042357b:
        mov esi,7
    L_00423580:
        cmp eax,esi
    L_00423582:
        push edi
    L_00423583:
        jne short L_004235a8
    L_00423585:
        mov eax,dword ptr [ebp+1E4h]
    L_0042358b:
        test eax,eax
    L_0042358d:
        je short L_004235a8
    L_0042358f:
        mov eax,8
    L_00423594:
        mov dword ptr [data_00477848],474908h
    L_0042359e:
        mov dword ptr [data_00474c7c],eax
    L_004235a3:
        mov dword ptr [data_00474c80],eax
    L_004235a8:
        mov eax,dword ptr [data_00474c68]
    L_004235ad:
        mov ecx,dword ptr [data_00474c6c]
    L_004235b3:
        lea edx,[ecx+eax*2]
    L_004235b6:
        add edx,eax
    L_004235b8:
        mov eax,dword ptr [data_0047783c]
    L_004235bd:
        imul edx,437Ch
    L_004235c3:
        lea edi,[edx+eax+8]
    L_004235c7:
        call asm_FUN_00421fa0_00421fa0
    L_004235cc:
        cmp dword ptr [data_00474c7c],esi
    L_004235d2:
        jne short L_004235f4
    L_004235d4:
        mov ecx,dword ptr [ebp+1E4h]
    L_004235da:
        test ecx,ecx
    L_004235dc:
        je short L_004235f4
    L_004235de:
        mov dword ptr [data_00477848],4748D8h
    L_004235e8:
        mov dword ptr [data_00474c7c],esi
    L_004235ee:
        mov dword ptr [data_00474c80],esi
    L_004235f4:
        test eax,eax
    L_004235f6:
        jl asm_target_004236d9
    L_004235fc:
        mov esi,1
    L_00423601:
        mov dword ptr [ebp+2Ch],19h
    L_00423608:
        mov dword ptr [ebp+0F4h],esi
    L_0042360e:
        mov ecx,dword ptr [ebp+2Ch]
    L_00423611:
        test ecx,ecx
    L_00423613:
        je short L_0042361c
    L_00423615:
        cmp eax,ecx
    L_00423617:
        jl short L_0042361c
    L_00423619:
        lea eax,[ecx-1]
    L_0042361c:
        push ebx
    L_0042361d:
        lea ebx,[ebp+0FCh]
    L_00423623:
        mov dword ptr [ebp+24h],eax
    L_00423626:
        mov eax,dword ptr [ebx+8]
    L_00423629:
        test eax,eax
    L_0042362b:
        je short L_0042363a
    L_0042362d:
        jg short L_00423634
    L_0042362f:
        dec eax
    L_00423630:
        mov dword ptr [ebx],eax
    L_00423632:
        jmp short L_00423640
    L_00423634:
        xor eax,eax
    L_00423636:
        mov dword ptr [ebx],eax
    L_00423638:
        jmp short L_00423640
    L_0042363a:
        mov dword ptr [ebx],0
    L_00423640:
        mov ecx,dword ptr [data_004746d8]
    L_00423646:
        lea edx,[ecx+1]
    L_00423649:
        lea esp,[esp+force_disp32_zero]
    L_00423650:
        mov al,byte ptr [ecx]
    L_00423652:
        inc ecx
    L_00423653:
        test al,al
    L_00423655:
        jne short L_00423650
    L_00423657:
        sub ecx,edx
    L_00423659:
        mov dword ptr [ebp+104h],ecx
    L_0042365f:
        mov ecx,dword ptr [data_0047783c]
    L_00423665:
        mov dword ptr [ebp+1CCh],esi
    L_0042366b:
        lea esi,[ebp+2B4h]
    L_00423671:
        add ecx,1D878h
    L_00423677:
        mov edx,esi
    L_00423679:
        sub edx,ecx
    L_0042367b:
        TH10_REL8(0xeb, 0x0042367b, VA_asm_FUN_00423570_part_00423680)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00423680:
        mov al,byte ptr [ecx]
    L_00423682:
        mov byte ptr [edx+ecx],al
    L_00423685:
        inc ecx
    L_00423686:
        test al,al
    L_00423688:
        jne short L_00423680
    L_0042368a:
        mov edi,46E354h
    L_0042368f:
        mov ecx,9
    L_00423694:
        xor edx,edx
    L_00423696:
        mov dword ptr [ebp+1E0h],0
    L_004236a0:
        repe cmpsb
    L_004236a2:
        je short L_004236ad
    L_004236a4:
        push 0FFFFFFFFh
    L_004236a6:
        mov eax,ebx
    L_004236a8:
        call asm_MenuCursor_Advance_0044bea0
    L_004236ad:
        mov eax,8
    L_004236b2:
        mov cl,20h
    L_004236b4:
        pop ebx
    L_004236b5:
        cmp byte ptr [eax+ebp+2B3h],cl
    L_004236bc:
        jne short L_004236c3
    L_004236be:
        dec eax
    L_004236bf:
        test eax,eax
    L_004236c1:
        jg short L_004236b5
    L_004236c3:
        pop edi
    L_004236c4:
        pop esi
    L_004236c5:
        mov dword ptr [ebp+1E0h],eax
    L_004236cb:
        mov dword ptr [ebp+1E8h],0
    L_004236d5:
        pop ebp
    L_004236d6:
        ret 4
    L_004236d9:
        pop edi
    L_004236da:
        pop esi
    L_004236db:
        mov dword ptr [ebp+1E8h],1
    L_004236e5:
        pop ebp
    L_004236e6:
        ret 4
    }
}
