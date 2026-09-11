#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421FA0..0x00421FBC: FUN_00421fa0
// Naked body preserves the retail register/stack ABI.

// 0x0042B030..0x0042B1D6: FUN_0042b030
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042b030_0042b030() {
    __asm {
    L_0042b030:
        push ecx
    L_0042b031:
        mov eax,dword ptr [ebx]
    L_0042b033:
        test eax,eax
    L_0042b035:
        push ebp
    L_0042b036:
        push esi
    L_0042b037:
        push edi
    L_0042b038:
        je asm_target_0042b198
    L_0042b03e:
        cmp dword ptr [eax],30314854h
    L_0042b044:
        jne asm_target_0042b183
    L_0042b04a:
        cmp word ptr [eax+8],3
    L_0042b04f:
        jne asm_target_0042b183
    L_0042b055:
        mov ecx,dword ptr [eax+10h]
    L_0042b058:
        push ecx
    L_0042b059:
        push 10h
    L_0042b05b:
        push 35h
    L_0042b05d:
        add eax,18h
    L_0042b060:
        push ecx
    L_0042b061:
        push eax
    L_0042b062:
        mov al,0ACh
    L_0042b064:
        call asm_DecryptDatBuffer_0044b0d0
    L_0042b069:
        mov eax,dword ptr [ebx]
    L_0042b06b:
        lea esi,[eax+18h]
    L_0042b06e:
        mov eax,dword ptr [eax+14h]
    L_0042b071:
        shl eax,2
    L_0042b074:
        push eax
    L_0042b075:
        call asm_malloc_00452706
    L_0042b07a:
        mov ecx,dword ptr [ebx]
    L_0042b07c:
        add esp,4
    L_0042b07f:
        mov dword ptr [ebx+4],eax
    L_0042b082:
        mov edx,dword ptr [ecx+14h]
    L_0042b085:
        push edx
    L_0042b086:
        push eax
    L_0042b087:
        mov eax,dword ptr [ecx+10h]
    L_0042b08a:
        push eax
    L_0042b08b:
        push esi
    L_0042b08c:
        call asm_DecompressDatLzss_00435dc0
    L_0042b091:
        mov ecx,dword ptr [ebx]
    L_0042b093:
        mov eax,dword ptr [ecx+14h]
    L_0042b096:
        test eax,eax
    L_0042b098:
        mov edx,dword ptr [ebx+4]
    L_0042b09b:
        mov dword ptr [esp+0Ch],eax
    L_0042b09f:
        jle asm_target_0042b1d0
    L_0042b0a5:
        mov ax,word ptr [edx]
    L_0042b0a8:
        cmp ax,5243h
    L_0042b0ac:
        jne short L_0042b10f
    L_0042b0ae:
        cmp word ptr [edx+2],0
    L_0042b0b3:
        jne asm_target_0042b161
    L_0042b0b9:
        xor ecx,ecx
    L_0042b0bb:
        lea eax,[edx+0Ch]
    L_0042b0be:
        mov esi,0B3Eh
    L_0042b0c3:
        movzx ebp,byte ptr [eax-3]
    L_0042b0c7:
        movzx edi,byte ptr [eax-4]
    L_0042b0cb:
        add edi,ebp
    L_0042b0cd:
        movzx ebp,byte ptr [eax-2]
    L_0042b0d1:
        add edi,ebp
    L_0042b0d3:
        movzx ebp,byte ptr [eax-1]
    L_0042b0d7:
        add edi,ebp
    L_0042b0d9:
        movzx ebp,byte ptr [eax+1]
    L_0042b0dd:
        add edi,ebp
    L_0042b0df:
        movzx ebp,byte ptr [eax]
    L_0042b0e2:
        add ebp,ecx
    L_0042b0e4:
        add eax,6
    L_0042b0e7:
        dec esi
    L_0042b0e8:
        lea ecx,[edi+ebp]
    L_0042b0eb:
        jne short L_0042b0c3
    L_0042b0ed:
        cmp ecx,dword ptr [edx+4]
    L_0042b0f0:
        jne short L_0042b161
    L_0042b0f2:
        cmp dword ptr [edx+8],437Ch
    L_0042b0f9:
        jne short L_0042b161
    L_0042b0fb:
        mov eax,dword ptr [edx+0Ch]
    L_0042b0fe:
        imul eax,437Ch
    L_0042b104:
        mov ecx,10DFh
    L_0042b109:
        lea edi,[eax+ebx+8]
    L_0042b10d:
        jmp short L_0042b15d
    L_0042b10f:
        cmp ax,5453h
    L_0042b113:
        jne short L_0042b183
    L_0042b115:
        cmp word ptr [edx+2],0
    L_0042b11a:
        jne short L_0042b161
    L_0042b11c:
        xor ecx,ecx
    L_0042b11e:
        lea eax,[edx+0Ah]
    L_0042b121:
        mov esi,110h
    L_0042b126:
        movzx ebp,byte ptr [eax-1]
    L_0042b12a:
        movzx edi,byte ptr [eax-2]
    L_0042b12e:
        add edi,ebp
    L_0042b130:
        movzx ebp,byte ptr [eax+1]
    L_0042b134:
        add edi,ebp
    L_0042b136:
        movzx ebp,byte ptr [eax]
    L_0042b139:
        add ebp,ecx
    L_0042b13b:
        add eax,4
    L_0042b13e:
        dec esi
    L_0042b13f:
        lea ecx,[edi+ebp]
    L_0042b142:
        jne short L_0042b126
    L_0042b144:
        cmp ecx,dword ptr [edx+4]
    L_0042b147:
        jne short L_0042b161
    L_0042b149:
        cmp dword ptr [edx+8],448h
    L_0042b150:
        jne short L_0042b161
    L_0042b152:
        lea edi,[ebx+1D86Ch]
    L_0042b158:
        mov ecx,112h
    L_0042b15d:
        mov esi,edx
    L_0042b15f:
        rep movsd
    L_0042b161:
        mov ecx,dword ptr [esp+0Ch]
    L_0042b165:
        mov eax,dword ptr [edx+8]
    L_0042b168:
        sub ecx,eax
    L_0042b16a:
        mov dword ptr [esp+0Ch],ecx
    L_0042b16e:
        js short L_0042b183
    L_0042b170:
        add edx,eax
    L_0042b172:
        mov eax,ecx
    L_0042b174:
        test eax,eax
    L_0042b176:
        jg asm_target_0042b0a5
    L_0042b17c:
        pop edi
    L_0042b17d:
        pop esi
    L_0042b17e:
        xor eax,eax
    L_0042b180:
        pop ebp
    L_0042b181:
        pop ecx
    L_0042b182:
        ret
    L_0042b183:
        mov eax,dword ptr [ebx]
    L_0042b185:
        test eax,eax
    L_0042b187:
        je short L_0042b198
    L_0042b189:
        push eax
    L_0042b18a:
        call asm_free_00452422
    L_0042b18f:
        add esp,4
    L_0042b192:
        mov dword ptr [ebx],0
    L_0042b198:
        push 18h
    L_0042b19a:
        call asm_malloc_00452706
    L_0042b19f:
        mov dword ptr [ebx],eax
    L_0042b1a1:
        add esp,4
    L_0042b1a4:
        xor ecx,ecx
    L_0042b1a6:
        mov dword ptr [eax],ecx
    L_0042b1a8:
        mov dword ptr [eax+4],ecx
    L_0042b1ab:
        mov dword ptr [eax+8],ecx
    L_0042b1ae:
        mov dword ptr [eax+0Ch],ecx
    L_0042b1b1:
        mov dword ptr [eax+10h],ecx
    L_0042b1b4:
        mov dword ptr [eax+14h],ecx
    L_0042b1b7:
        mov edx,dword ptr [ebx]
    L_0042b1b9:
        mov dword ptr [edx],30314854h
    L_0042b1bf:
        mov eax,dword ptr [ebx]
    L_0042b1c1:
        mov word ptr [eax+8],3
    L_0042b1c7:
        mov ecx,dword ptr [ebx]
    L_0042b1c9:
        mov dword ptr [ecx+0Ch],100h
    L_0042b1d0:
        pop edi
    L_0042b1d1:
        pop esi
    L_0042b1d2:
        xor eax,eax
    L_0042b1d4:
        pop ebp
    L_0042b1d5:
        pop ecx
    L_0042b1d6:
        ret
    }
}
