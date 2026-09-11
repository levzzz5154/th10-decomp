#include <string.h>
#include "asm_encoding.hpp"

// Retail strrchr at 0x00452930 (cdecl: string, character).
extern "C" char* __cdecl asm_strrchr_00452930(const char* text, int character);

// 0x00417010..0x00417038: ?Path_DecodeXor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Path_DecodeXor_00417010() {
    __asm {
    L_00417010:
        push esi
    L_00417011:
        push edi
    L_00417012:
        mov edi,eax
    L_00417014:
        mov cl,77h
    L_00417016:
        mov dl,7
    L_00417018:
        mov esi,497D40h
    L_0041701d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00417020:
        mov al,byte ptr [edi]
    L_00417022:
        xor al,cl
    L_00417024:
        mov byte ptr [esi],al
    L_00417026:
        inc esi
    L_00417027:
        add cl,dl
    L_00417029:
        inc edi
    L_0041702a:
        add dl,10h
    L_0041702d:
        test al,al
    L_0041702f:
        jne short L_00417020
    L_00417031:
        pop edi
    L_00417032:
        mov eax,497D40h
    L_00417037:
        pop esi
    L_00417038:
        ret
    }
}

// 0x0043D2A0..0x0043D382: ?Path_FindBasenameSlot@@
// The object itself is the path string (ECX) and the stack argument owns the
// array of 0x34-byte entries hanging off its 0x1F84 slot; the basename after
// the last '/' or '\' indexes that array. The chosen slot is tested by
// re-forming the entry address from the index, which is what keeps the retail
// imul-per-iteration instead of a walked pointer.
struct PathName_0043d2a0 {
    char text[1];
    int FindBasenameSlot_0043d2a0(void* owner);
};

int PathName_0043d2a0::FindBasenameSlot_0043d2a0(void* owner) {
    char basename[128];
    int index = 0;
    char* separator = asm_strrchr_00452930(text, '/');
    if (!separator)
        separator = asm_strrchr_00452930(text, '\\');
    if (!separator)
        strcpy(basename, text);
    else
        strcpy(basename, separator + 1);
    char* table = *(char**)((char*)owner + 8068);
    if (*table) {
        do {
            if (strcmp(&table[index * 52], basename) == 0)
                break;
            ++index;
        } while (table[index * 52]);
    }
    int result = index;
    if (table[index * 52] == 0)
        result = 0;
    return result;
}
