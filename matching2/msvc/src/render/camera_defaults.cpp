#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004216F0..0x004218C0: FUN_004216f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004216f0_004216f0() {
    __asm {
    L_004216f0:
        sub esp,0Ch
    L_004216f3:
        mov dword ptr [esp],0
    L_004216fa:
        mov eax,dword ptr [esp]
    L_004216fd:
        mov dword ptr [data_00491e94],eax
    L_00421702:
        mov dword ptr [esp+4],0
    L_0042170a:
        mov ecx,dword ptr [esp+4]
    L_0042170e:
        mov dword ptr [esp+8],447A0000h
    L_00421716:
        mov edx,dword ptr [esp+8]
    L_0042171a:
        mov dword ptr [data_00491e98],ecx
    L_00421720:
        mov dword ptr [data_00491e9c],edx
    L_00421726:
        mov dword ptr [esp],0
    L_0042172d:
        mov eax,dword ptr [esp]
    L_00421730:
        mov dword ptr [esp+4],0
    L_00421738:
        mov ecx,dword ptr [esp+4]
    L_0042173c:
        mov dword ptr [esp+8],0
    L_00421744:
        mov edx,dword ptr [esp+8]
    L_00421748:
        mov dword ptr [data_00491ea0],eax
    L_0042174d:
        mov dword ptr [esp],0
    L_00421754:
        mov eax,dword ptr [esp]
    L_00421757:
        mov dword ptr [data_00491ea4],ecx
    L_0042175d:
        mov dword ptr [data_00491ea8],edx
    L_00421763:
        mov dword ptr [esp+4],3F800000h
    L_0042176b:
        mov ecx,dword ptr [esp+4]
    L_0042176f:
        mov dword ptr [esp+8],0
    L_00421777:
        mov edx,dword ptr [esp+8]
    L_0042177b:
        mov dword ptr [data_00491eac],eax
    L_00421780:
        xor eax,eax
    L_00421782:
        mov dword ptr [data_00491eb0],ecx
    L_00421788:
        mov ecx,eax
    L_0042178a:
        mov dword ptr [data_00491eb4],edx
    L_00421790:
        mov edx,eax
    L_00421792:
        mov dword ptr [esp+4],eax
    L_00421796:
        mov dword ptr [esp+4],eax
    L_0042179a:
        mov dword ptr [esp+8],eax
    L_0042179e:
        mov dword ptr [data_00491ed0],ecx
    L_004217a4:
        mov dword ptr [data_00491ed4],edx
    L_004217aa:
        mov dword ptr [data_00491ed8],ecx
    L_004217b0:
        mov dword ptr [esp+8],447A0000h
    L_004217b8:
        mov dword ptr [data_00491d7c],edx
    L_004217be:
        mov edx,dword ptr [esp+8]
    L_004217c2:
        mov dword ptr [data_00491d80],ecx
    L_004217c8:
        mov dword ptr [esp+4],eax
    L_004217cc:
        mov dword ptr [data_00491d88],ecx
    L_004217d2:
        mov dword ptr [data_00491d90],ecx
    L_004217d8:
        mov dword ptr [esp+4],3F800000h
    L_004217e0:
        mov ecx,dword ptr [esp+4]
    L_004217e4:
        mov dword ptr [esp],eax
    L_004217e7:
        mov dword ptr [esp],eax
    L_004217ea:
        mov dword ptr [data_00491d84],edx
    L_004217f0:
        mov edx,eax
    L_004217f2:
        mov dword ptr [data_00491d98],ecx
    L_004217f8:
        mov dword ptr [esp],eax
    L_004217fb:
        mov dword ptr [esp+8],eax
    L_004217ff:
        mov ecx,eax
    L_00421801:
        mov dword ptr [esp],eax
    L_00421804:
        mov dword ptr [esp+8],eax
    L_00421808:
        mov dword ptr [data_00491edc],3F060A92h
    L_00421812:
        mov dword ptr [data_00491f60],eax
    L_00421817:
        mov dword ptr [data_00491f64],eax
    L_0042181c:
        mov dword ptr [data_00491f68],280h
    L_00421826:
        mov dword ptr [data_00491f6c],1E0h
    L_00421830:
        mov dword ptr [data_00491f70],eax
    L_00421835:
        mov dword ptr [data_00491f74],3F800000h
    L_0042183f:
        mov dword ptr [data_00491f78],1
    L_00421849:
        mov dword ptr [data_00491d8c],edx
    L_0042184f:
        mov dword ptr [data_00491d94],edx
    L_00421855:
        mov dword ptr [data_00491d9c],edx
    L_0042185b:
        mov dword ptr [data_00491dc4],3F060A92h
    L_00421865:
        mov dword ptr [data_00491e48],20h
    L_0042186f:
        mov dword ptr [data_00491e4c],10h
    L_00421879:
        mov dword ptr [data_00491e50],180h
    L_00421883:
        mov dword ptr [data_00491e54],1C0h
    L_0042188d:
        mov dword ptr [data_00491e58],eax
    L_00421892:
        mov dword ptr [data_00491e5c],3F800000h
    L_0042189c:
        mov dword ptr [data_00491e60],eax
    L_004218a1:
        mov dword ptr [esp],eax
    L_004218a4:
        mov dword ptr [esp+4],eax
    L_004218a8:
        mov dword ptr [esp+8],eax
    L_004218ac:
        mov dword ptr [data_00491db8],eax
    L_004218b1:
        mov dword ptr [data_00491dbc],ecx
    L_004218b7:
        mov dword ptr [data_00491dc0],edx
    L_004218bd:
        add esp,0Ch
    L_004218c0:
        ret
    }
}
