// 0x0043E9D0: load an optional .map companion and relocate its offsets.
#include <stdio.h>
#include <string.h>
#include "th10/platform/archive_callers.hpp"
extern "C" const char str_string_format[];
extern "C" int __stdcall ProbeFileExists(const char*);
#pragma code_seg(".text$04map")
void MapResource::LoadMap(const char* name) {
    char path[260];
    int size;
    sprintf(path, str_string_format, name);
    char* end = path + strlen(path);
    end[-3] = 'm';
    end[-2] = 'a';
    end[-1] = 'p';
    if (ProbeFileExists(path)) {
        map = (unsigned int*)Archive_LoadFile(path, &size, 1);
        for (int i = 0; i < sprite_count + script_count; ++i)
            map[i] += (unsigned int)map;
    } else {
        map = 0;
    }
}
#pragma code_seg()
