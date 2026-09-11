#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.

// 0x00420670..0x00420867: FUN_00420670
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420670_00420670() {
    __asm {
    L_00420670:
        sub esp,0Ch
    L_00420673:
        push ebx
    L_00420674:
        push ebp
    L_00420675:
        push edi
    L_00420676:
        mov edi,eax
    L_00420678:
        mov eax,dword ptr [esi+50Ch]
    L_0042067e:
        xor ebp,ebp
    L_00420680:
        cmp eax,ebp
    L_00420682:
        je short L_0042069c
    L_00420684:
        mov ebx,dword ptr [data_004660ac]
    L_0042068a:
        lea ebx,[ebx+force_disp32_zero]
    L_00420690:
        push 0Ah
    L_00420692:
        call ebx
    L_00420694:
        cmp dword ptr [esi+50Ch],ebp
    L_0042069a:
        jne short L_00420690
    L_0042069c:
        mov eax,dword ptr [esi+8]
    L_0042069f:
        lea edx,[esp+0Ch]
    L_004206a3:
        push edx
    L_004206a4:
        push ebp
    L_004206a5:
        push ebp
    L_004206a6:
        push ebp
    L_004206a7:
        mov dword ptr [esp+1Ch],ebp
    L_004206ab:
        mov ecx,dword ptr [eax]
    L_004206ad:
        push eax
    L_004206ae:
        call dword ptr [ecx+48h]
    L_004206b1:
        lea eax,[esi+510h]
    L_004206b7:
        xor ecx,ecx
    L_004206b9:
        mov edx,eax
    L_004206bb:
        mov dword ptr [edx],ecx
    L_004206bd:
        mov dword ptr [edx+4],ecx
    L_004206c0:
        mov dword ptr [edx+8],ecx
    L_004206c3:
        mov word ptr [edx+0Ch],cx
    L_004206c7:
        mov word ptr [eax],4D42h
    L_004206cc:
        mov eax,36h
    L_004206d1:
        mov ecx,esi
    L_004206d3:
        sub ecx,edi
    L_004206d5:
        mov dword ptr [esi+51Ah],eax
    L_004206db:
        mov dword ptr [esi+512h],eax
    L_004206e1:
        mov eax,edi
    L_004206e3:
        lea edx,[ecx+528h]
    L_004206e9:
        lea esp,[esp+force_disp32_zero]
    L_004206f0:
        mov cl,byte ptr [eax]
    L_004206f2:
        mov byte ptr [edx+eax],cl
    L_004206f5:
        inc eax
    L_004206f6:
        test cl,cl
    L_004206f8:
        jne short L_004206f0
    L_004206fa:
        mov eax,dword ptr [esi+0ECh]
    L_00420700:
        sub eax,16h
    L_00420703:
        je short L_00420738
    L_00420705:
        dec eax
    L_00420706:
        mov ecx,474F70h
    L_0042070b:
        je short L_00420726
    L_0042070d:
        push 46DEB0h
    L_00420712:
        call asm_TextLog_Append_0044b810
    L_00420717:
        add esp,4
    L_0042071a:
        pop edi
    L_0042071b:
        pop ebp
    L_0042071c:
        mov eax,1
    L_00420721:
        pop ebx
    L_00420722:
        add esp,0Ch
    L_00420725:
        ret
    L_00420726:
        push 46DF38h
    L_0042072b:
        call asm_TextLog_Append_0044b810
    L_00420730:
        add esp,4
    L_00420733:
        jmp asm_target_00420851
    L_00420738:
        push 2Ch
    L_0042073a:
        call asm_malloc_00452706
    L_0042073f:
        mov edi,eax
    L_00420741:
        add esp,4
    L_00420744:
        cmp edi,ebp
    L_00420746:
        mov dword ptr [esi+520h],edi
    L_0042074c:
        jne short L_00420765
    L_0042074e:
        push 46DEF0h
    L_00420753:
        mov ecx,474F70h
    L_00420758:
        call asm_TextLog_Append_0044b810
    L_0042075d:
        add esp,4
    L_00420760:
        jmp asm_target_00420851
    L_00420765:
        xor eax,eax
    L_00420767:
        mov ecx,0Bh
    L_0042076c:
        push 0E1000h
    L_00420771:
        rep stosd
    L_00420773:
        call asm_malloc_00452706
    L_00420778:
        add esp,4
    L_0042077b:
        cmp eax,ebp
    L_0042077d:
        mov dword ptr [esi+524h],eax
    L_00420783:
        je short L_0042074e
    L_00420785:
        add dword ptr [esi+512h],0E1000h
    L_0042078f:
        mov edx,dword ptr [esi+520h]
    L_00420795:
        mov word ptr [edx+0Eh],18h
    L_0042079b:
        mov eax,dword ptr [esi+520h]
    L_004207a1:
        mov dword ptr [eax],28h
    L_004207a7:
        mov ecx,dword ptr [esi+520h]
    L_004207ad:
        mov dword ptr [ecx+4],280h
    L_004207b4:
        mov edx,dword ptr [esi+520h]
    L_004207ba:
        mov dword ptr [edx+8],1E0h
    L_004207c1:
        mov eax,dword ptr [esi+520h]
    L_004207c7:
        mov word ptr [eax+0Ch],1
    L_004207cd:
        mov ecx,dword ptr [esi+520h]
    L_004207d3:
        push ebp
    L_004207d4:
        mov dword ptr [ecx+10h],ebp
    L_004207d7:
        mov eax,dword ptr [esp+10h]
    L_004207db:
        mov edx,dword ptr [eax]
    L_004207dd:
        push ebp
    L_004207de:
        lea ecx,[esp+18h]
    L_004207e2:
        push ecx
    L_004207e3:
        push eax
    L_004207e4:
        call dword ptr [edx+34h]
    L_004207e7:
        mov ebp,1DFh
    L_004207ec:
        xor edx,edx
    L_004207ee:
        mov edi,edi
    L_004207f0:
        mov eax,dword ptr [esp+10h]
    L_004207f4:
        mov ecx,dword ptr [esi+524h]
    L_004207fa:
        imul eax,ebp
    L_004207fd:
        mov edi,dword ptr [esp+14h]
    L_00420801:
        add ecx,edx
    L_00420803:
        add eax,edi
    L_00420805:
        mov edi,280h
    L_0042080a:
        lea ebx,[ebx+force_disp32_zero]
    L_00420810:
        mov bx,word ptr [eax]
    L_00420813:
        mov word ptr [ecx],bx
    L_00420816:
        mov bl,byte ptr [eax+2]
    L_00420819:
        mov byte ptr [ecx+2],bl
    L_0042081c:
        add eax,4
    L_0042081f:
        add ecx,3
    L_00420822:
        dec edi
    L_00420823:
        jne short L_00420810
    L_00420825:
        dec ebp
    L_00420826:
        add edx,780h
    L_0042082c:
        cmp ebp,0FFFFFFFFh
    L_0042082f:
        jg short L_004207f0
    L_00420831:
        mov eax,dword ptr [esp+0Ch]
    L_00420835:
        mov edx,dword ptr [eax]
    L_00420837:
        push eax
    L_00420838:
        call dword ptr [edx+38h]
    L_0042083b:
        push 0
    L_0042083d:
        push 0
    L_0042083f:
        push 420540h
    L_00420844:
        call asm_beginthread_00452eec
    L_00420849:
        add esp,0Ch
    L_0042084c:
        mov dword ptr [data_00492134],eax
    L_00420851:
        mov eax,dword ptr [esp+0Ch]
    L_00420855:
        test eax,eax
    L_00420857:
        je short L_0042085f
    L_00420859:
        mov ecx,dword ptr [eax]
    L_0042085b:
        push eax
    L_0042085c:
        call dword ptr [ecx+8]
    L_0042085f:
        pop edi
    L_00420860:
        pop ebp
    L_00420861:
        xor eax,eax
    L_00420863:
        pop ebx
    L_00420864:
        add esp,0Ch
    L_00420867:
        ret
    }
}
