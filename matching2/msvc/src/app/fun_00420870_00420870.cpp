#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=8/534; first_diff=0x00420870;
// residual_class=private ECX config-default receiver, EBX path input, and EDI
// size input across FUN_0044B360/File_WriteWholeFile;
// variants_tested=live Ghidra decompile/callers (0x00420870, 0x00438AD0)
// and MSVC 13.10 readable config/state candidate (572-byte extent, 8 matching
// bytes); next_lever=schema2 native-LTCG over the real GameMain caller with
// config, allocator, and file-writer bodies visible.

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.

// 0x00420870..0x00420A85: FUN_00420870
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00420870_00420870() {
    __asm {
    L_00420870:
        push ebp
    L_00420871:
        mov ebp,dword ptr [esp+8]
    L_00420875:
        push edi
    L_00420876:
        mov edx,491D48h
    L_0042087b:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00420880:
        push 1
    L_00420882:
        lea eax,[esp+10h]
    L_00420886:
        push eax
    L_00420887:
        mov eax,ebx
    L_00420889:
        call asm_FUN_0044b360_0044b360
    L_0042088e:
        test eax,eax
    L_00420890:
        jne short L_0042089c
    L_00420892:
        push 46DE7Ch
    L_00420897:
        jmp asm_target_00420942
    L_0042089c:
        push esi
    L_0042089d:
        mov esi,eax
    L_0042089f:
        mov ecx,0Dh
    L_004208a4:
        mov edi,491D48h
    L_004208a9:
        push eax
    L_004208aa:
        rep movsd
    L_004208ac:
        call asm_free_00452422
    L_004208b1:
        mov al,byte ptr [data_00491d62]
    L_004208b6:
        add esp,4
    L_004208b9:
        cmp al,2
    L_004208bb:
        pop esi
    L_004208bc:
        jae short L_0042093d
    L_004208be:
        mov cl,byte ptr [data_00491d63]
    L_004208c4:
        mov al,3
    L_004208c6:
        cmp cl,al
    L_004208c8:
        jae short L_0042093d
    L_004208ca:
        cmp byte ptr [data_00491d64],2
    L_004208d1:
        jae short L_0042093d
    L_004208d3:
        cmp byte ptr [data_00491d65],2
    L_004208da:
        jae short L_0042093d
    L_004208dc:
        cmp byte ptr [data_00491d66],al
    L_004208e2:
        jae short L_0042093d
    L_004208e4:
        cmp byte ptr [data_00491d67],al
    L_004208ea:
        jae short L_0042093d
    L_004208ec:
        cmp dword ptr [data_00491d48],100003h
    L_004208f6:
        jne short L_0042093d
    L_004208f8:
        cmp dword ptr [esp+0Ch],34h
    L_004208fd:
        jne short L_0042093d
    L_004208ff:
        mov ecx,dword ptr [data_00491d4c]
    L_00420905:
        mov edx,dword ptr [data_00491d50]
    L_0042090b:
        mov eax,dword ptr [data_00491d54]
    L_00420910:
        mov dword ptr [data_00474e88],ecx
    L_00420916:
        mov ecx,dword ptr [data_00491d58]
    L_0042091c:
        mov dword ptr [data_00474e8c],edx
    L_00420922:
        mov dx,word ptr [data_00491d5c]
    L_00420929:
        mov dword ptr [data_00474e90],eax
    L_0042092e:
        mov dword ptr [data_00474e94],ecx
    L_00420934:
        mov word ptr [data_00474e98],dx
    L_0042093b:
        jmp short L_00420959
    L_0042093d:
        push 46DE48h
    L_00420942:
        mov ecx,474F70h
    L_00420947:
        call asm_TextLog_Append_0044b810
    L_0042094c:
        add esp,4
    L_0042094f:
        mov edx,491D48h
    L_00420954:
        call asm_GameConfig_InitializeDefaults_00418c40
    L_00420959:
        test byte ptr [ebp+150h],4
    L_00420960:
        mov dword ptr [ebp+3B4h],0
    L_0042096a:
        je short L_0042097e
    L_0042096c:
        push 46DE2Ch
    L_00420971:
        mov ecx,474F70h
    L_00420976:
        call asm_TextLog_Append_0044b810
    L_0042097b:
        add esp,4
    L_0042097e:
        test byte ptr [ebp+150h],1
    L_00420985:
        je short L_00420999
    L_00420987:
        push 46DE04h
    L_0042098c:
        mov ecx,474F70h
    L_00420991:
        call asm_TextLog_Append_0044b810
    L_00420996:
        add esp,4
    L_00420999:
        mov al,byte ptr [ebp+13Dh]
    L_0042099f:
        test al,al
    L_004209a1:
        je short L_004209b5
    L_004209a3:
        push 46DDE4h
    L_004209a8:
        mov ecx,474F70h
    L_004209ad:
        call asm_TextLog_Append_0044b810
    L_004209b2:
        add esp,4
    L_004209b5:
        test byte ptr [ebp+150h],2
    L_004209bc:
        je short L_004209d0
    L_004209be:
        push 46DDBCh
    L_004209c3:
        mov ecx,474F70h
    L_004209c8:
        call asm_TextLog_Append_0044b810
    L_004209cd:
        add esp,4
    L_004209d0:
        test byte ptr [ebp+150h],8
    L_004209d7:
        je short L_004209eb
    L_004209d9:
        push 46DD84h
    L_004209de:
        mov ecx,474F70h
    L_004209e3:
        call asm_TextLog_Append_0044b810
    L_004209e8:
        add esp,4
    L_004209eb:
        test byte ptr [ebp+150h],10h
    L_004209f2:
        je short L_00420a06
    L_004209f4:
        push 46DD64h
    L_004209f9:
        mov ecx,474F70h
    L_004209fe:
        call asm_TextLog_Append_0044b810
    L_00420a03:
        add esp,4
    L_00420a06:
        test byte ptr [ebp+150h],20h
    L_00420a0d:
        je short L_00420a2b
    L_00420a0f:
        push 46DD4Ch
    L_00420a14:
        mov ecx,474F70h
    L_00420a19:
        call asm_TextLog_Append_0044b810
    L_00420a1e:
        add esp,4
    L_00420a21:
        mov dword ptr [data_00491fdc],1
    L_00420a2b:
        test byte ptr [ebp+150h],40h
    L_00420a32:
        je short L_00420a46
    L_00420a34:
        push 46DD28h
    L_00420a39:
        mov ecx,474F70h
    L_00420a3e:
        call asm_TextLog_Append_0044b810
    L_00420a43:
        add esp,4
    L_00420a46:
        push 491D48h
    L_00420a4b:
        push ebx
    L_00420a4c:
        mov edi,34h
    L_00420a51:
        call asm_File_WriteWholeFile_0044b540
    L_00420a56:
        test eax,eax
    L_00420a58:
        je short L_00420a7f
    L_00420a5a:
        push ebx
    L_00420a5b:
        push 46DD08h
    L_00420a60:
        mov edi,474F70h
    L_00420a65:
        call asm_TextLog_AppendLine_0044b8e0
    L_00420a6a:
        push 46DCB0h
    L_00420a6f:
        call asm_TextLog_AppendLine_0044b8e0
    L_00420a74:
        add esp,0Ch
    L_00420a77:
        pop edi
    L_00420a78:
        or eax,0FFFFFFFFh
    L_00420a7b:
        pop ebp
    L_00420a7c:
        ret 4
    L_00420a7f:
        pop edi
    L_00420a80:
        xor eax,eax
    L_00420a82:
        pop ebp
    L_00420a83:
        ret 4
    }
}
