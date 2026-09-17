extern "C" int __cdecl asm_strncmp_00452f80(const char*, const char*, unsigned);
extern "C" int __cdecl asm_sscanf_00452fb9(const char*, const char*, ...);
extern "C" char* __cdecl asm_FUN_00452730_00452730(const char*, int);

extern const char version_debug_00420dd0[] = "debug";
extern const char version_0100a_00420dd0[] = "0100a";
extern const char version_format_00420dd0[] = "%d %d";

struct VersionList_00420dd0 {
    unsigned char pad[0x760];
    unsigned length;
    const char* text;
    int Match(const char* tag, int first, int second);
};

#pragma intrinsic(memcmp)
extern "C" int __cdecl memcmp(const void*, const void*, unsigned);
#pragma intrinsic(strcmp)
extern "C" int __cdecl strcmp(const char*, const char*);

#pragma code_seg(".text$01version")
__declspec(noinline) int VersionList_00420dd0::Match(const char* tag, int first, int second) {
    const char* cursor = text;
    if (cursor == 0) return 0;
    unsigned int remaining = length;
    int result = asm_strncmp_00452f80(tag, version_debug_00420dd0, 5);
    if (result == 0) return result;
    if (strcmp("0100a", "debug") == 0) return 0;
    while (remaining > 0) {
        if (asm_strncmp_00452f80(tag, cursor, 5) == 0) {
            int parsed_first, parsed_second;
            cursor += 6;
            asm_sscanf_00452fb9(cursor, version_format_00420dd0, &parsed_first, &parsed_second);
            if (parsed_first == first && parsed_second == second) return 0;
        }
        const char* old = cursor;
        cursor = asm_FUN_00452730_00452730(cursor, 10) + 1;
        remaining += int(old - cursor);
    }
    return -1;
}
#pragma code_seg()
