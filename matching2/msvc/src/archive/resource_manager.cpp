#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED 00435800 (214 bytes): retain the naked body until its archive-read
// and FileHandle helper contracts can be compiled together. The live Ghidra
// ABI/caller audit and smallest useful cluster are recorded in
// matching2/reference/recovery_notes/resource_load_retail_00435800.md. The
// archive branch calls the still-private 00434DD0 reader; the disk branch
// depends on the custom path resolver and stack FileHandle lifecycle.

#include <string.h>

// 0x004356F0: find the packed-archive entry whose stored name matches the name
// this string object holds, with the directory prefix stripped and everything
// from the last '/' on replaced by the five-byte marker at 0x0046F274.

struct ArchiveEntry_004356f0 {
    unsigned int field_00;   // +0x00
    unsigned int field_04;   // +0x04
    const char* name;        // +0x08
    unsigned int field_0C;   // +0x0C
};

extern "C" ArchiveEntry_004356f0 data_004923b0[];

struct ArchiveName_004356f0 {
    char text[1];

    __declspec(noinline) const ArchiveEntry_004356f0* Find() const;
};

#pragma code_seg(".text$01find")
const ArchiveEntry_004356f0* ArchiveName_004356f0::Find() const {
    char buffer[0x104];
    const char* name = text;
    const char* slash = ((char* (__cdecl*)(const char*, int))asm_FUN_00452730_00452730)(name, '/');
    const char* base = slash ? slash + 1 : name;
    int length = (int)(base - name) - 1;
    strcpy(buffer, name);
    if (length >= 0) {
        char* suffix = buffer + length;
        *(unsigned int*)suffix = *(unsigned int*)&data_0046f274;
        suffix[4] = (char)*(unsigned char*)&data_0046f278;
    }
    ArchiveEntry_004356f0* entry = data_004923b0;
    for (int index = 0; index < *(int*)&data_00477850; index++, entry++) {
        if (strcmp(entry->name, buffer) == 0)
            return entry;
    }
    return 0;
}
#pragma code_seg()



// 0x00435800..0x004358D5: FUN_00435800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00435800_00435800() {
    __asm {
    L_00435800:
        mov eax,dword ptr fs:[0]
    L_00435806:
        push 0FFFFFFFFh
    L_00435808:
        push 4653A8h
    L_0043580d:
        push eax
    L_0043580e:
        mov dword ptr fs:[0],esp
    L_00435815:
        sub esp,0Ch
    L_00435818:
        push esi
    L_00435819:
        push edi
    L_0043581a:
        mov esi,ecx
    L_0043581c:
        call asm_FUN_004356f0_004356f0
    L_00435821:
        mov edi,eax
    L_00435823:
        test edi,edi
    L_00435825:
        je short L_00435859
    L_00435827:
        push 2Fh
    L_00435829:
        push esi
    L_0043582a:
        call asm_FUN_00452730_00452730
    L_0043582f:
        add esp,8
    L_00435832:
        test eax,eax
    L_00435834:
        lea ecx,[eax+1]
    L_00435837:
        jne short L_0043583b
    L_00435839:
        mov ecx,esi
    L_0043583b:
        mov eax,dword ptr [esp+24h]
    L_0043583f:
        push eax
    L_00435840:
        push edi
    L_00435841:
        call asm_DatArchive_Read_00434dd0
    L_00435846:
        pop edi
    L_00435847:
        pop esi
    L_00435848:
        mov ecx,dword ptr [esp+0Ch]
    L_0043584c:
        mov dword ptr fs:[0],ecx
    L_00435853:
        add esp,18h
    L_00435856:
        ret 4
    L_00435859:
        mov edi,46F230h
    L_0043585e:
        mov dword ptr [esp+8],edi
    L_00435862:
        mov dword ptr [esp+0Ch],0FFFFFFFFh
    L_0043586a:
        mov dword ptr [esp+10h],0
    L_00435872:
        mov dword ptr [esp+1Ch],0
    L_0043587a:
        mov ecx,dword ptr [data_00474908]
    L_00435880:
        push ecx
    L_00435881:
        push esi
    L_00435882:
        lea ecx,[esp+10h]
    L_00435886:
        call asm_FileHandle_OpenRetail_00435370
    L_0043588b:
        mov eax,dword ptr [esp+0Ch]
    L_0043588f:
        cmp eax,0FFFFFFFFh
    L_00435892:
        jne short L_00435898
    L_00435894:
        xor eax,eax
    L_00435896:
        jmp short L_004358a1
    L_00435898:
        push 0
    L_0043589a:
        push eax
    L_0043589b:
        call dword ptr [data_004660d8]
    L_004358a1:
        push eax
    L_004358a2:
        lea ecx,[esp+0Ch]
    L_004358a6:
        call asm_ReadWhole_FileHandle_00435580
    L_004358ab:
        mov esi,eax
    L_004358ad:
        mov eax,dword ptr [esp+0Ch]
    L_004358b1:
        cmp eax,0FFFFFFFFh
    L_004358b4:
        mov dword ptr [esp+8],edi
    L_004358b8:
        je short L_004358c1
    L_004358ba:
        push eax
    L_004358bb:
        call dword ptr [data_004660cc]
    L_004358c1:
        mov ecx,dword ptr [esp+14h]
    L_004358c5:
        pop edi
    L_004358c6:
        mov eax,esi
    L_004358c8:
        pop esi
    L_004358c9:
        mov dword ptr fs:[0],ecx
    L_004358d0:
        add esp,18h
    L_004358d3:
        ret 4
    }
}
