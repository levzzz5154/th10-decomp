#include "th10/platform/file.hpp"
#include "th10/platform/path.hpp"
#include "th10/archive/resource_manager.hpp"

#ifdef _MSC_VER
extern "C" char unk_497D40[];
extern "C" void* sub_452930(void*, int);
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
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
#ifdef _MSC_VER
__declspec(naked) unsigned int Path_FindBasenameSlot(
        const char* path, const char* table,
        unsigned int count, unsigned int stride) {
    __asm {
        sub esp, 84h
        mov eax, ___security_cookie
        xor eax, esp
        push ebp
        push esi
        mov esi, ecx
        push 2Fh
        push esi
        mov [esp+90h], eax
        xor ebp, ebp
        call sub_452930
        add esp, 8
        test eax, eax
        jne have_slash
        push 5Ch
        push esi
        call sub_452930
        add esp, 8
        test eax, eax
        jne have_slash
        lea edx, [esp+8]
        mov eax, esi
        sub edx, esi
copy_full:
        mov cl, [eax]
        mov [edx+eax], cl
        inc eax
        test cl, cl
        jne copy_full
        jmp compare
have_slash:
        inc eax
        lea edx, [esp+8]
        sub edx, eax
copy_slash:
        mov cl, [eax]
        mov [edx+eax], cl
        inc eax
        test cl, cl
        jne copy_slash
compare:
        mov eax, [esp+90h]
        push edi
        mov edi, [eax+1F84h]
        cmp byte ptr [edi], 0
        je no_table
        mov eax, edi
        push ebx
loop_reload:
        lea esi, [esp+10h]
outer_loop:
        mov dl, [eax]
        mov bl, [esi]
        mov cl, dl
        cmp dl, bl
        jne mismatch
        test cl, cl
        je equal_zero
        mov dl, [eax+1]
        mov bl, [esi+1]
        mov cl, dl
        cmp dl, bl
        jne mismatch
        add eax, 2
        add esi, 2
        test cl, cl
        jne outer_loop
equal_zero:
        xor eax, eax
        jmp compare_result
mismatch:
        sbb eax, eax
        sbb eax, 0FFFFFFFFh
compare_result:
        test eax, eax
        je found
        inc ebp
        mov eax, ebp
        imul eax, eax, 34h
        mov cl, [eax+edi]
        add eax, edi
        test cl, cl
        jne loop_reload
found:
        pop ebx
no_table:
        mov ecx, ebp
        imul ecx, ecx, 34h
        cmp byte ptr [ecx+edi], 0
        pop edi
        jne return_ebp
        xor eax, eax
        jmp epilogue
return_ebp:
        mov eax, ebp
epilogue:
        mov ecx, [esp+88h]
        pop esi
        pop ebp
        xor ecx, esp
        call security_check_cookie
        add esp, 84h
        ret 4
    }
}
#else
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
#endif

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
