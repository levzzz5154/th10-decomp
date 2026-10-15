#include <string.h>
#include "../../../build_support/include/asm_encoding.hpp"

// Retail strrchr at 0x00452930 (cdecl: string, character).
extern "C" char* __cdecl asm_strrchr_00452930(const char* text, int character);


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
