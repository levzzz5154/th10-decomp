// 0x0043D2A0: PathName::FindBasenameSlot
#include <string.h>

// Retail strrchr at 0x00452930 (cdecl: string, character).
extern "C" char* __cdecl crt_strrchr(const char* text, int character);


// 0x0043D2A0..0x0043D382: ?Path_FindBasenameSlot@@
// The object itself is the path string (ECX) and the stack argument owns the
// array of 0x34-byte entries hanging off its 0x1F84 slot; the basename after
// the last '/' or '\' indexes that array. The chosen slot is tested by
// re-forming the entry address from the index, which is what keeps the retail
// imul-per-iteration instead of a walked pointer.
struct SoundPathTableOwner {
    unsigned char pad_0000[0x1F84];
    char* table;
};

struct PathName {
    char text[1];
    int FindBasenameSlot(void* owner);
};

int PathName::FindBasenameSlot(void* owner) {
    char basename[128];
    int index = 0;
    char* separator = crt_strrchr(text, '/');
    if (!separator)
        separator = crt_strrchr(text, '\\');
    if (!separator)
        strcpy(basename, text);
    else
        strcpy(basename, separator + 1);
    char* table = static_cast<SoundPathTableOwner*>(owner)->table;
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
