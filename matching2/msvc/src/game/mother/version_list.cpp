// 0x00420DD0: VersionList::Match
extern "C" int __cdecl crt_strncmp(const char*, const char*, unsigned);
extern "C" int __cdecl crt_sscanf(const char*, const char*, ...);
extern "C" char* __cdecl crt_strchr(const char*, int);

extern const char version_debug[] = "debug";
extern const char version_0100a[] = "0100a";
extern const char version_format[] = "%d %d";

struct VersionList {
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
__declspec(noinline) int VersionList::Match(const char* tag, int first, int second) {
    const char* cursor = text;
    if (cursor == 0) return 0;
    unsigned int remaining = length;
    int result = crt_strncmp(tag, version_debug, 5);
    if (result == 0) return result;
    if (strcmp("0100a", "debug") == 0) return 0;
    while (remaining > 0) {
        if (crt_strncmp(tag, cursor, 5) == 0) {
            int parsed_first, parsed_second;
            cursor += 6;
            crt_sscanf(cursor, version_format, &parsed_first, &parsed_second);
            if (parsed_first == first && parsed_second == second) return 0;
        }
        const char* old = cursor;
        cursor = crt_strchr(cursor, 10) + 1;
        remaining += int(old - cursor);
    }
    return -1;
}
#pragma code_seg()
