#include "th10/game/version_list.hpp"

#ifdef _MSC_VER
extern "C" int __cdecl _strncmp(const char*, const char*, int);
extern "C" int __cdecl _sscanf(const char*, const char*, ...);
extern "C" char* __cdecl _strchr(const char*, int);
#endif

#include <cstdio>
#include <cstring>

// 0x00420DD0 - Match a tag and integer pair against the version list.
// Retail also inlines a constant comparison of the strings "0100a" and
// "debug" (never equal, so the branch is dead) before scanning; only
// the strncmp(tag, "debug", 5) early-out is observable. The cursor
// walks line by line with the CRT strchr (retail 0x00452730),
// recomputing the remaining byte count exactly like the retail
// pointer arithmetic.
#ifdef _MSC_VER
__declspec(naked) int32_t VersionList_MatchRetail() {
    __asm {
        sub esp, 8
        push ebx
        mov ebx, [eax+764h]
        test ebx, ebx
        jnz loc_420DE7
        xor eax, eax
        pop ebx
        add esp, 8
        ret 0Ch
loc_420DE7:
        push ebp
        mov ebp, [eax+760h]
        mov eax, [esp+14h]
        push 5
        push 46DCA4h
        push eax
        call _strncmp
        add esp, 0Ch
        test eax, eax
        jnz loc_420E0E
        pop ebp
        pop ebx
        add esp, 8
        ret 0Ch
loc_420E0E:
        push esi
        push edi
        mov edi, 46DCA4h
        mov esi, 46DC9Ch
        mov ecx, 6
        xor edx, edx
        repe cmpsb
        jnz loc_420E31
loc_420E25:
        pop edi
        pop esi
        pop ebp
        xor eax, eax
        pop ebx
        add esp, 8
        ret 0Ch
loc_420E31:
        test ebp, ebp
        jbe loc_420E90
loc_420E35:
        mov eax, [esp+1Ch]
        push 5
        push ebx
        push eax
        call _strncmp
        add esp, 0Ch
        test eax, eax
        jnz loc_420E7A
        lea ecx, [esp+14h]
        push ecx
        lea edx, [esp+14h]
        push edx
        add ebx, 6
        push 46DC94h
        push ebx
        call _sscanf
        mov eax, [esp+30h]
        mov ecx, [esp+20h]
        add esp, 10h
        cmp ecx, eax
        jnz loc_420E7A
        mov ecx, [esp+24h]
        cmp [esp+14h], ecx
        jz loc_420E25
loc_420E7A:
        push 0Ah
        push ebx
        mov esi, ebx
        call _strchr
        add esp, 8
        inc eax
        mov ebx, eax
        sub esi, ebx
        add ebp, esi
        jnz loc_420E35
loc_420E90:
        pop edi
        pop esi
        pop ebp
        or eax, 0FFFFFFFFh
        pop ebx
        add esp, 8
        ret 0Ch
    }
}
#endif

int32_t VersionList_Match(const VersionList* list, const char* tag,
                          int32_t first, int32_t second) {
    const char* cursor = list->text;
    if (cursor == 0) {
        return 0;
    }
    int32_t remaining = list->length;
    if (strncmp(tag, "debug", 5) == 0) {
        return 0;
    }
    for (;;) {
        if (remaining == 0) {
            return -1;
        }
        if (strncmp(tag, cursor, 5) == 0) {
            int parsed_first = 0;
            int parsed_second = 0;
            sscanf(cursor + 6, "%d %d", &parsed_first, &parsed_second);
            if (parsed_first == first && parsed_second == second) {
                return 0;
            }
        }
        const char* newline = strchr(cursor, '\n');
        remaining = (int32_t)((cursor + remaining) - (newline + 1));
        cursor = newline + 1;
    }
}
