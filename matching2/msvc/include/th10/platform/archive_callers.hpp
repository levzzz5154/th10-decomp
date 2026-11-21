#ifndef TH10_ARCHIVE_CALLERS_HPP
#define TH10_ARCHIVE_CALLERS_HPP
#include "th10/platform/archive_file.hpp"
struct AssetBuffer { char reserved[0x14]; char* data; };
__declspec(noinline) char* __stdcall LoadAsset(const char* name, AssetBuffer* buffer);
struct MapResource {
    char reserved[0x110];
    int sprite_count, script_count;
    char reserved_118[0x12C - 0x118];
    unsigned int* map;
    __declspec(noinline) void LoadMap(const char* name);
};
struct ShotDefinitionRecord {
    signed char kind;
    char reserved[0x24 - 1];
    unsigned int command, easing, variable, callback;
};
struct ShotGroupEntry { union { unsigned int offset; ShotDefinitionRecord* records; }; int reserved; };
struct ShotFileHeader {
    unsigned short version, group_count;
    char reserved[0x10 - 4];
    float width, height, projected_width, projected_height;
    char reserved_020[0x110 - 0x20];
    ShotGroupEntry groups[1];
};
struct PlayerShotLoader {
    char reserved[0x45C];
    ShotFileHeader* file;
    __declspec(noinline) int Load(const char* name);
};
#endif
