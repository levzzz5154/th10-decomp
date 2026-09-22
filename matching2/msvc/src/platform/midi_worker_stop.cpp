#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
 
// BLOCKED (D3405): closest_byte_count=20/176; first_diff=0x0043DAB0;
// residual_class=hidden-ESI receiver, imported PostThreadMessageA/
// WaitForSingleObject/CloseHandle slots, and virtual interface release ABI;
// variants_tested=live Ghidra decompile/callers/callees (0x0043D120,
// 0x0043D690, 0x0043DDF0; AggregatePlatformInterfaces and WinAPI imports)
// and MSVC 13.10 readable state-layout cdecl candidate (179-byte extent,
// 20 matching bytes); next_lever=co-compile the three real MIDI stop callers
// with AggregatePlatformInterfaces and the virtual release body in native
// LTCG so the ESI receiver and imported-slot call shapes are selected.

// 0x0043DAB0..0x0043DB5F: MidiWorker_StopRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MidiWorker_StopRetail_0043dab0() {
    __asm {
    L_0043dab0:
        push edi
    L_0043dab1:
        mov edi,dword ptr [esi+5208h]
    L_0043dab7:
        test edi,edi
    L_0043dab9:
        je asm_target_0043db5e
    L_0043dabf:
        call asm_Platform_AggregateInterfaces_0044d550
    L_0043dac4:
        mov eax,dword ptr [esi+618h]
    L_0043daca:
        test eax,eax
    L_0043dacc:
        je short L_0043db44
    L_0043dace:
        mov eax,dword ptr [esi+614h]
    L_0043dad4:
        mov edi,dword ptr [data_00466210]
    L_0043dada:
        push ebx
    L_0043dadb:
        push 0
    L_0043dadd:
        push 0
    L_0043dadf:
        push 12h
    L_0043dae1:
        push eax
    L_0043dae2:
        call edi
    L_0043dae4:
        mov ecx,dword ptr [esi+618h]
    L_0043daea:
        mov ebx,dword ptr [data_0046611c]
    L_0043daf0:
        push 100h
    L_0043daf5:
        push ecx
    L_0043daf6:
        call ebx
    L_0043daf8:
        test eax,eax
    L_0043dafa:
        je short L_0043db21
    L_0043dafc:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043db00:
        mov edx,dword ptr [esi+614h]
    L_0043db06:
        push 0
    L_0043db08:
        push 0
    L_0043db0a:
        push 12h
    L_0043db0c:
        push edx
    L_0043db0d:
        call edi
    L_0043db0f:
        mov eax,dword ptr [esi+618h]
    L_0043db15:
        push 100h
    L_0043db1a:
        push eax
    L_0043db1b:
        call ebx
    L_0043db1d:
        test eax,eax
    L_0043db1f:
        jne short L_0043db00
    L_0043db21:
        mov ecx,dword ptr [esi+618h]
    L_0043db27:
        mov edi,dword ptr [data_004660cc]
    L_0043db2d:
        push ecx
    L_0043db2e:
        call edi
    L_0043db30:
        mov edx,dword ptr [esi+520Ch]
    L_0043db36:
        push edx
    L_0043db37:
        call edi
    L_0043db39:
        mov dword ptr [esi+618h],0
    L_0043db43:
        pop ebx
    L_0043db44:
        mov ecx,dword ptr [esi+5208h]
    L_0043db4a:
        test ecx,ecx
    L_0043db4c:
        je short L_0043db5e
    L_0043db4e:
        mov eax,dword ptr [ecx]
    L_0043db50:
        push 1
    L_0043db52:
        call dword ptr [eax]
    L_0043db54:
        mov dword ptr [esi+5208h],0
    L_0043db5e:
        pop edi
    L_0043db5f:
        ret
    }
}
