#pragma once

#include <cstddef>
#include <cstdint>

struct AnmFileEntry {
    const uint8_t* base;
    size_t available;
    uint32_t sprite_count;
    uint32_t script_count;
    uint32_t width;
    uint32_t height;
    uint32_t format;
    uint32_t name_offset;
    uint32_t texture_offset;
    uint32_t next_offset;
};

struct AnmFileSprite {
    uint32_t id;
    float x;
    float y;
    float width;
    float height;
};

struct AnmFileScript {
    uint32_t id;
    const uint8_t* instructions;
};

struct AnmTexturePayload {
    uint16_t format;
    uint16_t width;
    uint16_t height;
    uint32_t data_size;
    const uint8_t* pixels;
};

bool AnmFile_ParseEntry(const uint8_t* image, size_t image_size,
                        size_t entry_offset, AnmFileEntry* output);
bool AnmFile_GetSprite(const AnmFileEntry* entry, uint32_t index,
                       AnmFileSprite* output);
bool AnmFile_FindGlobalSprite(const uint8_t* image, size_t image_size,
                              uint32_t global_index, AnmFileEntry* entry_out,
                              AnmFileSprite* sprite_out);
bool AnmFile_FindScript(const AnmFileEntry* entry, uint32_t id,
                        AnmFileScript* output);
bool AnmFile_GetScriptByIndex(const AnmFileEntry* entry, uint32_t index,
                              AnmFileScript* output);
bool AnmFile_FindGlobalScript(const uint8_t* image, size_t image_size,
                              uint32_t global_index, AnmFileEntry* entry_out,
                              AnmFileScript* script_out);
bool AnmFile_GetTexture(const AnmFileEntry* entry,
                        AnmTexturePayload* output);
