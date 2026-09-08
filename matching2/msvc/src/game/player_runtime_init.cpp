#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004247F0..0x00424938: FUN_004247f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004247f0_004247f0() {
    __asm {
    L_004247f0:
        mov eax,dword ptr [data_00474c68]
    L_004247f5:
        sub esp,0Ch
    L_004247f8:
        push ebp
    L_004247f9:
        xor ebp,ebp
    L_004247fb:
        cmp eax,ebp
    L_004247fd:
        mov eax,46E42Ch
    L_00424802:
        je short L_00424809
    L_00424804:
        mov eax,46E420h
    L_00424809:
        mov edx,dword ptr [data_00491c10]
    L_0042480f:
        push eax
    L_00424810:
        mov ecx,8
    L_00424815:
        call asm_Recovery_LoadCachedResource_00447280
    L_0042481a:
        cmp eax,ebp
    L_0042481c:
        mov dword ptr [ebx+10h],eax
    L_0042481f:
        jne short L_0042483b
    L_00424821:
        push 46E3ECh
    L_00424826:
        mov ecx,474F70h
    L_0042482b:
        call asm_TextLog_Append_0044b810
    L_00424830:
        add esp,4
    L_00424833:
        or eax,0FFFFFFFFh
    L_00424836:
        pop ebp
    L_00424837:
        add esp,0Ch
    L_0042483a:
        ret
    L_0042483b:
        mov eax,dword ptr [data_00491bf0]
    L_00424840:
        cmp eax,ebp
    L_00424842:
        push esi
    L_00424843:
        je asm_target_00424d4a
    L_00424849:
        mov dword ptr [ebx+45Ch],eax
    L_0042484f:
        mov dword ptr [data_00491bf0],ebp
    L_00424855:
        push edi
    L_00424856:
        push 426500h
    L_0042485b:
        call asm_SchedulerCallback_Create_00449ed0
    L_00424860:
        mov esi,eax
    L_00424862:
        mov edx,dword ptr [esi+4]
    L_00424865:
        mov eax,dword ptr [data_00491be4]
    L_0042486a:
        and edx,0FFFFFFFDh
    L_0042486d:
        push eax
    L_0042486e:
        mov edi,10h
    L_00424873:
        mov dword ptr [esi+20h],ebx
    L_00424876:
        mov dword ptr [esi+4],edx
    L_00424879:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042487e:
        push 426510h
    L_00424883:
        mov dword ptr [ebx+8],esi
    L_00424886:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042488b:
        mov ecx,dword ptr [data_00491be4]
    L_00424891:
        mov esi,eax
    L_00424893:
        and dword ptr [esi+4],0FFFFFFFDh
    L_00424897:
        push ecx
    L_00424898:
        mov edi,16h
    L_0042489d:
        mov dword ptr [esi+20h],ebx
    L_004248a0:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004248a5:
        mov edx,dword ptr [ebx+10h]
    L_004248a8:
        mov dword ptr [ebx+0Ch],esi
    L_004248ab:
        lea esi,[ebx+14h]
    L_004248ae:
        push edx
    L_004248af:
        xor eax,eax
    L_004248b1:
        call asm_FUN_00404f30_00404f30
    L_004248b6:
        mov esi,dword ptr [ebx+45Ch]
    L_004248bc:
        mov dword ptr [ebx+3C0h],ebp
    L_004248c2:
        mov dword ptr [ebx+3C4h],43C80000h
    L_004248cc:
        mov dword ptr [ebx+3CCh],ebp
    L_004248d2:
        mov dword ptr [ebx+3D0h],9C40h
    L_004248dc:
        fld dword ptr [esi+10h]
    L_004248df:
        fmul dword ptr [data_00470b44]
    L_004248e5:
        call asm_FUN_00463b2c_00463b2c
    L_004248ea:
        mov dword ptr [ebx+3D4h],eax
    L_004248f0:
        fld dword ptr [esi+14h]
    L_004248f3:
        fmul dword ptr [data_00470b44]
    L_004248f9:
        call asm_FUN_00463b2c_00463b2c
    L_004248fe:
        mov dword ptr [ebx+3D8h],eax
    L_00424904:
        fld dword ptr [esi+18h]
    L_00424907:
        fmul dword ptr [data_00470b44]
    L_0042490d:
        call asm_FUN_00463b2c_00463b2c
    L_00424912:
        mov dword ptr [ebx+3DCh],eax
    L_00424918:
        fld dword ptr [esi+1Ch]
    L_0042491b:
        fmul dword ptr [data_00470b44]
    L_00424921:
        call asm_FUN_00463b2c_00463b2c
    L_00424926:
        mov dword ptr [ebx+3E0h],eax
    L_0042492c:
        lea eax,[ebx+436Ch]
    L_00424932:
        mov ecx,21h
    L_00424937:
        TH10_REL8(0xeb, 0x00424937, VA_asm_FUN_004247f0_part_00424940)
    }
}

// 0x00424940..0x00424D8A: FUN_004247f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004247f0_part_00424940() {
    __asm {
    L_00424940:
        mov edx,dword ptr [ebx+3CCh]
    L_00424946:
        mov dword ptr [eax],edx
    L_00424948:
        mov edx,dword ptr [ebx+3D0h]
    L_0042494e:
        mov dword ptr [eax+4],edx
    L_00424951:
        add eax,8
    L_00424954:
        dec ecx
    L_00424955:
        jne short L_00424940
    L_00424957:
        mov eax,dword ptr [ebx+470h]
    L_0042495d:
        test al,1
    L_0042495f:
        mov edx,0FFF0BDC1h
    L_00424964:
        mov ecx,476F78h
    L_00424969:
        jne short L_0042498c
    L_0042496b:
        or eax,1
    L_0042496e:
        mov dword ptr [ebx+464h],ebp
    L_00424974:
        mov dword ptr [ebx+460h],edx
    L_0042497a:
        mov dword ptr [ebx+468h],ebp
    L_00424980:
        mov dword ptr [ebx+46Ch],ecx
    L_00424986:
        mov dword ptr [ebx+470h],eax
    L_0042498c:
        mov dword ptr [ebx+468h],0BF800000h
    L_00424996:
        mov dword ptr [ebx+460h],0FFFFFFFEh
    L_004249a0:
        or esi,0FFFFFFFFh
    L_004249a3:
        mov dword ptr [ebx+464h],esi
    L_004249a9:
        mov edi,dword ptr [data_00474c68]
    L_004249af:
        mov edi,dword ptr [edi*4+476FB8h]
    L_004249b6:
        mov eax,dword ptr [ebx+45Ch]
    L_004249bc:
        mov dword ptr [eax+4],edi
    L_004249bf:
        mov edi,dword ptr [data_00474c68]
    L_004249c5:
        mov edi,dword ptr [edi*4+476FB0h]
    L_004249cc:
        mov eax,dword ptr [ebx+45Ch]
    L_004249d2:
        mov dword ptr [eax+0Ch],edi
    L_004249d5:
        mov edi,dword ptr [data_00474c68]
    L_004249db:
        mov edi,dword ptr [edi*4+476FA0h]
    L_004249e2:
        mov eax,dword ptr [ebx+45Ch]
    L_004249e8:
        mov dword ptr [eax+8],edi
    L_004249eb:
        mov eax,dword ptr [ebx+45Ch]
    L_004249f1:
        fld dword ptr [eax+4]
    L_004249f4:
        mov eax,40A00000h
    L_004249f9:
        fmul dword ptr [data_00470b0c]
    L_004249ff:
        mov dword ptr [ebx+424h],eax
    L_00424a05:
        fst dword ptr [ebx+420h]
    L_00424a0b:
        fstp dword ptr [ebx+41Ch]
    L_00424a11:
        mov edi,dword ptr [data_00474c68]
    L_00424a17:
        fld dword ptr [edi*4+476FB0h]
    L_00424a1e:
        mov dword ptr [ebx+430h],eax
    L_00424a24:
        fmul dword ptr [data_00470b0c]
    L_00424a2a:
        fst dword ptr [ebx+42Ch]
    L_00424a30:
        fstp dword ptr [ebx+428h]
    L_00424a36:
        mov edi,dword ptr [data_00474c68]
    L_00424a3c:
        fld dword ptr [edi*4+476FA8h]
    L_00424a43:
        mov dword ptr [ebx+43Ch],eax
    L_00424a49:
        fmul dword ptr [data_00470b0c]
    L_00424a4f:
        lea eax,[ebx+404h]
    L_00424a55:
        fst dword ptr [ebx+438h]
    L_00424a5b:
        fstp dword ptr [ebx+434h]
    L_00424a61:
        fld dword ptr [ebx+3C0h]
    L_00424a67:
        fsub dword ptr [ebx+41Ch]
    L_00424a6d:
        fstp dword ptr [esp+0Ch]
    L_00424a71:
        mov edi,dword ptr [esp+0Ch]
    L_00424a75:
        fld dword ptr [ebx+3C4h]
    L_00424a7b:
        fsub dword ptr [ebx+420h]
    L_00424a81:
        fstp dword ptr [esp+10h]
    L_00424a85:
        fld dword ptr [ebx+3C8h]
    L_00424a8b:
        fsub dword ptr [ebx+424h]
    L_00424a91:
        mov dword ptr [eax],edi
    L_00424a93:
        mov edi,dword ptr [esp+10h]
    L_00424a97:
        mov dword ptr [eax+4],edi
    L_00424a9a:
        fstp dword ptr [esp+14h]
    L_00424a9e:
        mov edi,dword ptr [esp+14h]
    L_00424aa2:
        mov dword ptr [eax+8],edi
    L_00424aa5:
        fld dword ptr [ebx+41Ch]
    L_00424aab:
        fadd dword ptr [ebx+3C0h]
    L_00424ab1:
        lea eax,[ebx+410h]
    L_00424ab7:
        fstp dword ptr [esp+0Ch]
    L_00424abb:
        mov edi,dword ptr [esp+0Ch]
    L_00424abf:
        fld dword ptr [ebx+420h]
    L_00424ac5:
        fadd dword ptr [ebx+3C4h]
    L_00424acb:
        fstp dword ptr [esp+10h]
    L_00424acf:
        fld dword ptr [ebx+424h]
    L_00424ad5:
        fadd dword ptr [ebx+3C8h]
    L_00424adb:
        mov dword ptr [eax],edi
    L_00424add:
        mov edi,dword ptr [esp+10h]
    L_00424ae1:
        mov dword ptr [eax+4],edi
    L_00424ae4:
        fstp dword ptr [esp+14h]
    L_00424ae8:
        mov edi,dword ptr [esp+14h]
    L_00424aec:
        mov dword ptr [eax+8],edi
    L_00424aef:
        fld dword ptr [ebx+3C0h]
    L_00424af5:
        fsub dword ptr [ebx+428h]
    L_00424afb:
        lea eax,[ebx+4324h]
    L_00424b01:
        fstp dword ptr [esp+0Ch]
    L_00424b05:
        mov edi,dword ptr [esp+0Ch]
    L_00424b09:
        fld dword ptr [ebx+3C4h]
    L_00424b0f:
        fsub dword ptr [ebx+42Ch]
    L_00424b15:
        fstp dword ptr [esp+10h]
    L_00424b19:
        fld dword ptr [ebx+3C8h]
    L_00424b1f:
        fsub dword ptr [ebx+430h]
    L_00424b25:
        mov dword ptr [eax],edi
    L_00424b27:
        mov edi,dword ptr [esp+10h]
    L_00424b2b:
        mov dword ptr [eax+4],edi
    L_00424b2e:
        fstp dword ptr [esp+14h]
    L_00424b32:
        mov edi,dword ptr [esp+14h]
    L_00424b36:
        mov dword ptr [eax+8],edi
    L_00424b39:
        fld dword ptr [ebx+428h]
    L_00424b3f:
        fadd dword ptr [ebx+3C0h]
    L_00424b45:
        lea eax,[ebx+4330h]
    L_00424b4b:
        fstp dword ptr [esp+0Ch]
    L_00424b4f:
        mov edi,dword ptr [esp+0Ch]
    L_00424b53:
        fld dword ptr [ebx+42Ch]
    L_00424b59:
        fadd dword ptr [ebx+3C4h]
    L_00424b5f:
        fstp dword ptr [esp+10h]
    L_00424b63:
        fld dword ptr [ebx+430h]
    L_00424b69:
        fadd dword ptr [ebx+3C8h]
    L_00424b6f:
        mov dword ptr [eax],edi
    L_00424b71:
        mov edi,dword ptr [esp+10h]
    L_00424b75:
        mov dword ptr [eax+4],edi
    L_00424b78:
        fstp dword ptr [esp+14h]
    L_00424b7c:
        mov edi,dword ptr [esp+14h]
    L_00424b80:
        mov dword ptr [eax+8],edi
    L_00424b83:
        fld dword ptr [ebx+3C0h]
    L_00424b89:
        fsub dword ptr [ebx+434h]
    L_00424b8f:
        lea eax,[ebx+433Ch]
    L_00424b95:
        fstp dword ptr [esp+0Ch]
    L_00424b99:
        mov edi,dword ptr [esp+0Ch]
    L_00424b9d:
        fld dword ptr [ebx+3C4h]
    L_00424ba3:
        fsub dword ptr [ebx+438h]
    L_00424ba9:
        fstp dword ptr [esp+10h]
    L_00424bad:
        fld dword ptr [ebx+3C8h]
    L_00424bb3:
        fsub dword ptr [ebx+43Ch]
    L_00424bb9:
        mov dword ptr [eax],edi
    L_00424bbb:
        mov edi,dword ptr [esp+10h]
    L_00424bbf:
        mov dword ptr [eax+4],edi
    L_00424bc2:
        fstp dword ptr [esp+14h]
    L_00424bc6:
        mov edi,dword ptr [esp+14h]
    L_00424bca:
        mov dword ptr [eax+8],edi
    L_00424bcd:
        fld dword ptr [ebx+434h]
    L_00424bd3:
        fadd dword ptr [ebx+3C0h]
    L_00424bd9:
        lea eax,[ebx+4348h]
    L_00424bdf:
        fstp dword ptr [esp+0Ch]
    L_00424be3:
        mov edi,dword ptr [esp+0Ch]
    L_00424be7:
        fld dword ptr [ebx+438h]
    L_00424bed:
        fadd dword ptr [ebx+3C4h]
    L_00424bf3:
        fstp dword ptr [esp+10h]
    L_00424bf7:
        fld dword ptr [ebx+43Ch]
    L_00424bfd:
        fadd dword ptr [ebx+3C8h]
    L_00424c03:
        mov dword ptr [eax],edi
    L_00424c05:
        mov edi,dword ptr [esp+10h]
    L_00424c09:
        mov dword ptr [eax+4],edi
    L_00424c0c:
        fstp dword ptr [esp+14h]
    L_00424c10:
        mov edi,dword ptr [esp+14h]
    L_00424c14:
        mov dword ptr [eax+8],edi
    L_00424c17:
        fld dword ptr [ebx+3C0h]
    L_00424c1d:
        fsub dword ptr [ebx+434h]
    L_00424c23:
        lea eax,[ebx+4354h]
    L_00424c29:
        fstp dword ptr [esp+0Ch]
    L_00424c2d:
        mov edi,dword ptr [esp+0Ch]
    L_00424c31:
        fld dword ptr [ebx+3C4h]
    L_00424c37:
        fsub dword ptr [ebx+438h]
    L_00424c3d:
        fstp dword ptr [esp+10h]
    L_00424c41:
        fld dword ptr [ebx+3C8h]
    L_00424c47:
        fsub dword ptr [ebx+43Ch]
    L_00424c4d:
        mov dword ptr [eax],edi
    L_00424c4f:
        mov edi,dword ptr [esp+10h]
    L_00424c53:
        mov dword ptr [eax+4],edi
    L_00424c56:
        fstp dword ptr [esp+14h]
    L_00424c5a:
        mov edi,dword ptr [esp+14h]
    L_00424c5e:
        mov dword ptr [eax+8],edi
    L_00424c61:
        fld dword ptr [ebx+434h]
    L_00424c67:
        fadd dword ptr [ebx+3C0h]
    L_00424c6d:
        lea eax,[ebx+4360h]
    L_00424c73:
        fstp dword ptr [esp+0Ch]
    L_00424c77:
        mov edi,dword ptr [esp+0Ch]
    L_00424c7b:
        fld dword ptr [ebx+438h]
    L_00424c81:
        fadd dword ptr [ebx+3C4h]
    L_00424c87:
        fstp dword ptr [esp+10h]
    L_00424c8b:
        fld dword ptr [ebx+43Ch]
    L_00424c91:
        fadd dword ptr [ebx+3C8h]
    L_00424c97:
        mov dword ptr [eax],edi
    L_00424c99:
        mov edi,dword ptr [esp+10h]
    L_00424c9d:
        mov dword ptr [eax+4],edi
    L_00424ca0:
        fstp dword ptr [esp+14h]
    L_00424ca4:
        mov edi,dword ptr [esp+14h]
    L_00424ca8:
        mov dword ptr [eax+8],edi
    L_00424cab:
        mov eax,dword ptr [ebx+484h]
    L_00424cb1:
        test al,1
    L_00424cb3:
        pop edi
    L_00424cb4:
        jne short L_00424cd7
    L_00424cb6:
        or eax,1
    L_00424cb9:
        mov dword ptr [ebx+478h],ebp
    L_00424cbf:
        mov dword ptr [ebx+474h],edx
    L_00424cc5:
        mov dword ptr [ebx+47Ch],ebp
    L_00424ccb:
        mov dword ptr [ebx+480h],ecx
    L_00424cd1:
        mov dword ptr [ebx+484h],eax
    L_00424cd7:
        mov dword ptr [ebx+478h],ebp
    L_00424cdd:
        mov dword ptr [ebx+47Ch],ebp
    L_00424ce3:
        mov dword ptr [ebx+474h],esi
    L_00424ce9:
        mov eax,dword ptr [ebx+431Ch]
    L_00424cef:
        test al,1
    L_00424cf1:
        jne short L_00424d14
    L_00424cf3:
        or eax,1
    L_00424cf6:
        mov dword ptr [ebx+4310h],ebp
    L_00424cfc:
        mov dword ptr [ebx+430Ch],edx
    L_00424d02:
        mov dword ptr [ebx+4314h],ebp
    L_00424d08:
        mov dword ptr [ebx+4318h],ecx
    L_00424d0e:
        mov dword ptr [ebx+431Ch],eax
    L_00424d14:
        mov dword ptr [ebx+4310h],78h
    L_00424d1e:
        mov dword ptr [ebx+4314h],42F00000h
    L_00424d28:
        mov dword ptr [ebx+430Ch],77h
    L_00424d32:
        push ebx
    L_00424d33:
        mov dword ptr [ebx+4308h],1Eh
    L_00424d3d:
        call asm_FUN_00426f70_00426f70
    L_00424d42:
        pop esi
    L_00424d43:
        xor eax,eax
    L_00424d45:
        pop ebp
    L_00424d46:
        add esp,0Ch
    L_00424d49:
        ret
    L_00424d4a:
        mov eax,dword ptr [data_00474c68]
    L_00424d4f:
        mov ecx,dword ptr [data_00474c6c]
    L_00424d55:
        lea edx,[ecx+eax*2]
    L_00424d58:
        add edx,eax
    L_00424d5a:
        mov eax,dword ptr [edx*4+476FC0h]
    L_00424d61:
        mov esi,ebx
    L_00424d63:
        call asm_ParameterFile_LoadAndRelocateRetail_00426520
    L_00424d68:
        test eax,eax
    L_00424d6a:
        je asm_target_00424855
    L_00424d70:
        push 46E3ECh
    L_00424d75:
        mov ecx,474F70h
    L_00424d7a:
        call asm_TextLog_Append_0044b810
    L_00424d7f:
        add esp,4
    L_00424d82:
        pop esi
    L_00424d83:
        or eax,0FFFFFFFFh
    L_00424d86:
        pop ebp
    L_00424d87:
        add esp,0Ch
    L_00424d8a:
        ret
    }
}

// 0x00426360..0x004264F8: FUN_00426360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426360_00426360() {
    __asm {
    L_00426360:
        sub esp,14h
    L_00426363:
        push edi
    L_00426364:
        mov edi,eax
    L_00426366:
        cmp dword ptr [edi+458h],2
    L_0042636d:
        je asm_target_004264ef
    L_00426373:
        fld dword ptr [edi+3C0h]
    L_00426379:
        mov ecx,dword ptr [data_00491c10]
    L_0042637f:
        fadd dword ptr [data_00470b4c]
    L_00426385:
        push ebx
    L_00426386:
        push esi
    L_00426387:
        fstp dword ptr [edi+354h]
    L_0042638d:
        fld dword ptr [edi+3C4h]
    L_00426393:
        fadd dword ptr [data_00470b48]
    L_00426399:
        fstp dword ptr [edi+358h]
    L_0042639f:
        mov eax,dword ptr [edi+3C8h]
    L_004263a5:
        mov dword ptr [edi+35Ch],eax
    L_004263ab:
        lea eax,[edi+14h]
    L_004263ae:
        call asm_FUN_004451c0_004451c0
    L_004263b3:
        lea esi,[edi+3334h]
    L_004263b9:
        mov ebx,4
    L_004263be:
        mov edi,edi
    L_004263c0:
        mov eax,dword ptr [esi]
    L_004263c2:
        test eax,eax
    L_004263c4:
        je short L_004263ce
    L_004263c6:
        lea ecx,[esi-94h]
    L_004263cc:
        call eax
    L_004263ce:
        add esi,98h
    L_004263d4:
        dec ebx
    L_004263d5:
        jne short L_004263c0
    L_004263d7:
        mov eax,dword ptr [data_00477810]
    L_004263dc:
        test eax,eax
    L_004263de:
        je asm_target_004264ed
    L_004263e4:
        mov cl,byte ptr [eax+54h]
    L_004263e7:
        test cl,cl
    L_004263e9:
        jns asm_target_004264ed
    L_004263ef:
        mov ecx,dword ptr [data_00477704]
    L_004263f5:
        test ecx,ecx
    L_004263f7:
        je asm_target_004264ed
    L_004263fd:
        mov eax,dword ptr [data_0047770c]
    L_00426402:
        test eax,eax
    L_00426404:
        je asm_target_004264ed
    L_0042640a:
        mov edx,dword ptr [ecx+10h]
    L_0042640d:
        test edx,edx
    L_0042640f:
        jne asm_target_004264ed
    L_00426415:
        mov ecx,dword ptr [eax+9EB8h]
    L_0042641b:
        test ecx,ecx
    L_0042641d:
        jne asm_target_004264ed
    L_00426423:
        mov ecx,dword ptr [data_00477830]
    L_00426429:
        mov eax,dword ptr [ecx+4]
    L_0042642c:
        test eax,eax
    L_0042642e:
        jne asm_target_004264ed
    L_00426434:
        mov eax,dword ptr [data_00474c58]
    L_00426439:
        test eax,eax
    L_0042643b:
        je asm_target_004264ed
    L_00426441:
        fld dword ptr [edi+3C0h]
    L_00426447:
        push ecx
    L_00426448:
        fadd dword ptr [data_00470cbc]
    L_0042644e:
        mov dword ptr [esp+10h],eax
    L_00426452:
        fsub dword ptr [data_00470b48]
    L_00426458:
        fstp dword ptr [esp]
    L_0042645b:
        call asm_Sound_ForwardFloatAsDouble_00427c50
    L_00426460:
        fstp dword ptr [esp+10h]
    L_00426464:
        push ecx
    L_00426465:
        fild dword ptr [esp+10h]
    L_00426469:
        fmul dword ptr [data_00470cb8]
    L_0042646f:
        fadd dword ptr [esp+14h]
    L_00426473:
        fstp dword ptr [esp+1Ch]
    L_00426477:
        fld dword ptr [edi+3C4h]
    L_0042647d:
        fadd dword ptr [data_00470cb4]
    L_00426483:
        fsub dword ptr [data_00470be8]
    L_00426489:
        fstp dword ptr [esp]
    L_0042648c:
        call asm_Sound_ForwardFloatAsDouble_00427c50
    L_00426491:
        fst dword ptr [esp+14h]
    L_00426495:
        mov ebx,80000000h
    L_0042649a:
        fadd dword ptr [data_00470b08]
    L_004264a0:
        lea edi,[esp+10h]
    L_004264a4:
        fstp dword ptr [esp+1Ch]
    L_004264a8:
        call asm_FUN_0043bda0_0043bda0
    L_004264ad:
        fld dword ptr [esp+10h]
    L_004264b1:
        or ebx,0FFFFFFFFh
    L_004264b4:
        fsub dword ptr [data_00470afc]
    L_004264ba:
        fstp dword ptr [esp+10h]
    L_004264be:
        fld dword ptr [esp+18h]
    L_004264c2:
        fsub dword ptr [data_00470afc]
    L_004264c8:
        fstp dword ptr [esp+18h]
    L_004264cc:
        fld dword ptr [esp+14h]
    L_004264d0:
        fsub dword ptr [data_00470afc]
    L_004264d6:
        fstp dword ptr [esp+14h]
    L_004264da:
        fld dword ptr [esp+1Ch]
    L_004264de:
        fsub dword ptr [data_00470afc]
    L_004264e4:
        fstp dword ptr [esp+1Ch]
    L_004264e8:
        call asm_FUN_0043bda0_0043bda0
    L_004264ed:
        pop esi
    L_004264ee:
        pop ebx
    L_004264ef:
        mov eax,1
    L_004264f4:
        pop edi
    L_004264f5:
        add esp,14h
    L_004264f8:
        ret
    }
}
