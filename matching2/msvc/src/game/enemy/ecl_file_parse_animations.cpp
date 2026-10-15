// 0x0040D400: load ANIM resources and then optional ECLI script names.
#include <string.h>
#include "th10/platform/text_log.hpp"
#include "th10/game/enemy_death_release_0040e5f0.hpp"

extern "C" void* g_sprt_ctrl;
extern "C" void* __fastcall Recovery_LoadCachedResource(
    int index, void* cache, const char* name);

struct CountedScriptChunk {
    unsigned int magic;
    unsigned int count;
    char names[1];
};
struct ScriptFileChunkContext {
    virtual int ParseScriptFile(char* data) = 0;
    virtual int ParseAnimationChunk(char* chunk);
    virtual int LoadScript(const char* name) = 0;
};

#pragma code_seg(".text$a01parser")
__declspec(noinline) int ScriptFileChunkContext::ParseAnimationChunk(char* chunk) {
    CountedScriptChunk* header = reinterpret_cast<CountedScriptChunk*>(chunk);
    if (header->magic != 0x4D494E41u)
        return 0;
    char* name = chunk + 8;
    unsigned int index = 0;
    if (index < header->count) {
        do {
            void* resource = Recovery_LoadCachedResource(index + 9,
                g_sprt_ctrl, name);
            g_enemy_ctrl->animation_files[index + 1] = resource;
            if (!resource) {
                reinterpret_cast<TextLog_0044b810*>(0x00474F70)->Append(
                    reinterpret_cast<char*>(0x0046CB68));
                return -1;
            }
            name += strlen(name) + 1;
            ++index;
        } while (index < header->count);
    }
    if ((name - chunk) % 4)
        name += 4 - (name - chunk) % 4;
    CountedScriptChunk* scripts = reinterpret_cast<CountedScriptChunk*>(name);
    if (scripts->magic == 0x494C4345u) {
        name += 8;
        for (unsigned int scriptIndex = 0; scriptIndex < scripts->count; ++scriptIndex) {
            LoadScript(name);
            name += strlen(name) + 1;
        }
    }
    return 0;
}
#pragma code_seg()
