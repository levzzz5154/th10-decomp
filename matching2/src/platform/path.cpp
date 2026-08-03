#include "th10/platform/file.hpp"
#include "th10/platform/path.hpp"
#include "th10/archive/resource_manager.hpp"

#ifdef _MSC_VER
extern "C" char unk_497D40[];
#endif

// 0x00417010 - Decode bytes with the advancing retail XOR key sequence.
#ifdef _MSC_VER
__declspec(naked) const char* Path_DecodeXor(const unsigned char* encoded,
                                             char* decoded) {
    __asm {
        push esi
        push edi
        mov edi, eax
        mov cl, 77h
        mov dl, 7
        mov esi, offset unk_497D40
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_417020:
        mov al, [edi]
        xor al, cl
        mov [esi], al
        inc esi
        add cl, dl
        inc edi
        add dl, 10h
        test al, al
        jnz loc_417020
        pop edi
        mov eax, offset unk_497D40
        pop esi
        ret
    }
}
#else
const char* Path_DecodeXor(const unsigned char* encoded, char* decoded) {
    unsigned char key = 0x77;
    unsigned char key_step = 7;
    unsigned char* out = (unsigned char*)decoded;
    do {
        unsigned char value = *encoded++ ^ key;
        *out++ = value;
        key = (unsigned char)(key + key_step);
        key_step = (unsigned char)(key_step + 0x10);
        if (value == 0)
            break;
    } while (true);
    return decoded;
}
#endif

// 0x0043D2A0 - Find a path basename in a fixed-stride resource-name table.
unsigned int Path_FindBasenameSlot(const char* path, const char* table,
                                   unsigned int count, unsigned int stride) {
    const char* slash = path;
    const char* cursor = path;
    while (*cursor != 0) {
        if (*cursor == '/' || *cursor == '\\')
            slash = cursor + 1;
        ++cursor;
    }
    for (unsigned int index = 0; index < count; ++index) {
        const char* entry = table + index * stride;
        const char* left = slash;
        const char* right = entry;
        while (*left == *right && *left != 0) {
            ++left;
            ++right;
        }
        if (*left == 0 && *right == 0)
            return index;
    }
    return 0;
}

// Clean conventional-ABI form of 0x004356D0.
const char* File_AfterFirstSlash(const char* path) {
    const char* cursor = path;
    while (*cursor != 0) {
        if (*cursor == '/') {
            return cursor + 1;
        }
        ++cursor;
    }
    return path;
}

// Path normalization performed by retail 0x004356F0: an asset such as
// "th10/stage01.ecl" belongs to the archive named "th10.dat".
void Resource_ArchivePathForAsset(
        const char* asset_path, char archive_path[260]) {
    uint32_t index = 0;
    int32_t slash = -1;
    while (asset_path[index] != 0 && index < 259) {
        archive_path[index] = asset_path[index];
        if (slash < 0 && asset_path[index] == '/') {
            slash = (int32_t)index;
        }
        ++index;
    }
    archive_path[index] = 0;
    if (slash >= 0) {
        archive_path[slash + 0] = '.';
        archive_path[slash + 1] = 'd';
        archive_path[slash + 2] = 'a';
        archive_path[slash + 3] = 't';
        archive_path[slash + 4] = 0;
    }
}
