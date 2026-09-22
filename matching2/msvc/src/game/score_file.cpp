#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421FA0..0x00421FBC: FUN_00421fa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421fa0_00421fa0() {
    __asm {
    L_00421fa0:
        mov eax,dword ptr [data_00474c74]
    L_00421fa5:
        mov edx,dword ptr [data_00474c44]
    L_00421fab:
        push ebx
    L_00421fac:
        push esi
    L_00421fad:
        mov ecx,eax
    L_00421faf:
        xor esi,esi
    L_00421fb1:
        imul ecx,0F0h
    L_00421fb7:
        lea ecx,[ecx+edi+10h]
    L_00421fbb:
        TH10_REL8(0xeb, 0x00421fbb, VA_asm_FUN_00421fa0_part_00421fc0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00421fc0:
        cmp dword ptr [ecx],edx
    L_00421fc2:
        jle short L_00421fd3
    L_00421fc4:
        inc esi
    L_00421fc5:
        add ecx,18h
    L_00421fc8:
        cmp esi,0Ah
    L_00421fcb:
        jl short L_00421fc0
    L_00421fcd:
        pop esi
    L_00421fce:
        or eax,0FFFFFFFFh
    L_00421fd1:
        pop ebx
    L_00421fd2:
        ret
    L_00421fd3:
        cmp esi,0Ah
    L_00421fd6:
        jl short L_00421fde
    L_00421fd8:
        pop esi
    L_00421fd9:
        or eax,0FFFFFFFFh
    L_00421fdc:
        pop ebx
    L_00421fdd:
        ret
    L_00421fde:
        mov ecx,9
    L_00421fe3:
        cmp esi,ecx
    L_00421fe5:
        jge short L_0042202b
    L_00421fe7:
        lea edx,[eax+eax*4]
    L_00421fea:
        lea eax,[ecx+edx*2]
    L_00421fed:
        lea eax,[eax+eax*2]
    L_00421ff0:
        lea eax,[edi+eax*8]
    L_00421ff3:
        lea edx,[eax-8]
    L_00421ff6:
        mov ebx,dword ptr [edx]
    L_00421ff8:
        add eax,10h
    L_00421ffb:
        mov dword ptr [eax],ebx
    L_00421ffd:
        mov ebx,dword ptr [edx+4]
    L_00422000:
        mov dword ptr [eax+4],ebx
    L_00422003:
        mov ebx,dword ptr [edx+8]
    L_00422006:
        mov dword ptr [eax+8],ebx
    L_00422009:
        mov ebx,dword ptr [edx+0Ch]
    L_0042200c:
        mov dword ptr [eax+0Ch],ebx
    L_0042200f:
        mov ebx,dword ptr [edx+10h]
    L_00422012:
        mov dword ptr [eax+10h],ebx
    L_00422015:
        mov edx,dword ptr [edx+14h]
    L_00422018:
        dec ecx
    L_00422019:
        cmp ecx,esi
    L_0042201b:
        mov dword ptr [eax+14h],edx
    L_0042201e:
        mov eax,dword ptr [data_00474c74]
    L_00422023:
        jg short L_00421fe7
    L_00422025:
        mov edx,dword ptr [data_00474c44]
    L_0042202b:
        lea eax,[eax+eax*4]
    L_0042202e:
        lea eax,[esi+eax*2]
    L_00422031:
        lea ecx,[eax+eax*2]
    L_00422034:
        mov dword ptr [edi+ecx*8+10h],edx
    L_00422038:
        mov eax,dword ptr [data_00474c74]
    L_0042203d:
        mov cl,byte ptr [data_00474c90]
    L_00422043:
        lea edx,[eax+eax*4]
    L_00422046:
        lea eax,[esi+edx*2]
    L_00422049:
        lea eax,[eax+eax*2]
    L_0042204c:
        mov byte ptr [edi+eax*8+15h],cl
    L_00422050:
        mov eax,dword ptr [data_00474c74]
    L_00422055:
        mov cl,byte ptr [data_00474c7c]
    L_0042205b:
        lea edx,[eax+eax*4]
    L_0042205e:
        lea eax,[esi+edx*2]
    L_00422061:
        lea eax,[eax+eax*2]
    L_00422064:
        mov byte ptr [edi+eax*8+14h],cl
    L_00422068:
        mov eax,dword ptr [data_00474c74]
    L_0042206d:
        lea edx,[eax+eax*4]
    L_00422070:
        lea eax,[esi+edx*2]
    L_00422073:
        lea eax,[eax+eax*2]
    L_00422076:
        lea ecx,[edi+eax*8+20h]
    L_0042207a:
        push ecx
    L_0042207b:
        call asm_FID_conflict___time32_00452b71
    L_00422080:
        mov eax,dword ptr [data_00474c74]
    L_00422085:
        lea edx,[eax+eax*4]
    L_00422088:
        lea eax,[esi+edx*2]
    L_0042208b:
        mov edx,dword ptr [data_0046e354]
    L_00422091:
        lea eax,[eax+eax*2]
    L_00422094:
        lea ecx,[edi+eax*8+16h]
    L_00422098:
        mov dword ptr [ecx],edx
    L_0042209a:
        mov eax,dword ptr [data_0046e358]
    L_0042209f:
        mov dword ptr [ecx+4],eax
    L_004220a2:
        mov dl,byte ptr [data_0046e35c]
    L_004220a8:
        mov eax,dword ptr [data_00477708]
    L_004220ad:
        mov byte ptr [ecx+8],dl
    L_004220b0:
        fld qword ptr [eax+24h]
    L_004220b3:
        fdiv qword ptr [eax+2Ch]
    L_004220b6:
        mov eax,dword ptr [data_00474c74]
    L_004220bb:
        lea eax,[eax+eax*4]
    L_004220be:
        lea eax,[esi+eax*2]
    L_004220c1:
        add esp,4
    L_004220c4:
        lea ecx,[eax+eax*2]
    L_004220c7:
        mov eax,esi
    L_004220c9:
        pop esi
    L_004220ca:
        pop ebx
    L_004220cb:
        fmul dword ptr [data_00470b44]
    L_004220d1:
        fsubr dword ptr [data_00470b44]
    L_004220d7:
        fstp dword ptr [edi+ecx*8+24h]
    L_004220db:
        ret
    }
}

// 0x0042ACB0..0x0042ACE6: ScoreFile_InitializeDefaultsRetail
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3704): closest_byte_count=0/274; first_diff=0x0042ACB0;
// residual_class=retail __stdcall ret-4 ABI plus packed 0x437C-byte score
// layout and table data; variants_tested=["live Ghidra decompile at
// 0x0042ACB0", "live caller 0x0042AE60", "MSVC 13.10 schema-2 baseline
// probe"]; next_lever=typed packed ScoreFile layout in the real
// EffectManager_InitializePoolsRetail 0x0042AE60 native-LTCG caller scope.
extern "C" __declspec(naked) void __cdecl asm_ScoreFile_InitializeDefaultsRetail_0042acb0() {
    __asm {
    L_0042acb0:
        push ebx
    L_0042acb1:
        push ebp
    L_0042acb2:
        mov ebp,dword ptr [esp+0Ch]
    L_0042acb6:
        push esi
    L_0042acb7:
        push edi
    L_0042acb8:
        xor eax,eax
    L_0042acba:
        mov ecx,10DFh
    L_0042acbf:
        mov edi,ebp
    L_0042acc1:
        rep stosd
    L_0042acc3:
        xor edx,edx
    L_0042acc5:
        mov word ptr [ebp],5243h
    L_0042accb:
        mov word ptr [ebp+2],dx
    L_0042accf:
        mov dword ptr [ebp+8],437Ch
    L_0042acd6:
        lea eax,[ebp+14h]
    L_0042acd9:
        mov esi,5
    L_0042acde:
        mov edi,edi
    L_0042ace0:
        mov ecx,0F4240h
    L_0042ace5:
        TH10_REL8(0xeb, 0x0042ace5, VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042acf0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_0042acf0:
        mov dword ptr [eax-4],ecx
    L_0042acf3:
        mov byte ptr [eax],1
    L_0042acf6:
        mov ebx,dword ptr [data_0046e858]
    L_0042acfc:
        lea edi,[eax+2]
    L_0042acff:
        mov dword ptr [edi],ebx
    L_0042ad01:
        mov ebx,dword ptr [data_0046e85c]
    L_0042ad07:
        mov dword ptr [edi+4],ebx
    L_0042ad0a:
        mov bl,byte ptr [data_0046e860]
    L_0042ad10:
        mov dword ptr [eax+0Ch],edx
    L_0042ad13:
        mov byte ptr [eax+1],dl
    L_0042ad16:
        sub ecx,186A0h
    L_0042ad1c:
        add eax,18h
    L_0042ad1f:
        cmp ecx,edx
    L_0042ad21:
        mov byte ptr [edi+8],bl
    L_0042ad24:
        jg short L_0042acf0
    L_0042ad26:
        dec esi
    L_0042ad27:
        TH10_REL8(0x75, 0x0042ad27, VA_asm_target_0042ace0)
    L_0042ad29:
        xor esi,esi
    L_0042ad2b:
        mov edi,4743C0h
    L_0042ad30:
        mov edx,3
    L_0042ad35:
        mov ebx,4743C2h
    L_0042ad3a:
        dec edi
    L_0042ad3b:
        mov ecx,1
    L_0042ad40:
        lea eax,[ebp+628h]
    L_0042ad46:
        sub ebx,edx
    L_0042ad48:
        TH10_REL8(0xeb, 0x0042ad48, VA_asm_ScoreFile_InitializeDefaultsRetail_part_0042ad50)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0042ad50:
        mov dword ptr [eax-4],esi
    L_0042ad53:
        movsx ebp,byte ptr [ecx+edi]
    L_0042ad57:
        mov dword ptr [eax],ebp
    L_0042ad59:
        mov dword ptr [eax+8Ch],ecx
    L_0042ad5f:
        movsx ebp,byte ptr [ecx+4743C0h]
    L_0042ad66:
        mov dword ptr [eax+90h],ebp
    L_0042ad6c:
        lea ebp,[edx-1]
    L_0042ad6f:
        mov dword ptr [eax+11Ch],ebp
    L_0042ad75:
        movsx ebp,byte ptr [edx+ebx]
    L_0042ad79:
        mov dword ptr [eax+120h],ebp
    L_0042ad7f:
        mov dword ptr [eax+1ACh],edx
    L_0042ad85:
        movsx ebp,byte ptr [edx+4743C0h]
    L_0042ad8c:
        mov dword ptr [eax+1B0h],ebp
    L_0042ad92:
        lea ebp,[esi+4]
    L_0042ad95:
        mov dword ptr [eax+23Ch],ebp
    L_0042ad9b:
        movsx ebp,byte ptr [esi+4743C4h]
    L_0042ada2:
        mov dword ptr [eax+240h],ebp
    L_0042ada8:
        add ecx,5
    L_0042adab:
        add esi,5
    L_0042adae:
        add edx,5
    L_0042adb1:
        add eax,2D0h
    L_0042adb6:
        cmp ecx,6Fh
    L_0042adb9:
        jl short L_0042ad50
    L_0042adbb:
        pop edi
    L_0042adbc:
        pop esi
    L_0042adbd:
        pop ebp
    L_0042adbe:
        pop ebx
    L_0042adbf:
        ret 4
    }
}

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
