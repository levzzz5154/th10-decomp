#include "th10/render/anm_file.hpp"

#include <cstring>

namespace {

uint16_t Read16(const uint8_t* data) {
    return static_cast<uint16_t>(data[0] | (data[1] << 8));
}

uint32_t Read32(const uint8_t* data) {
    return static_cast<uint32_t>(data[0]) |
           (static_cast<uint32_t>(data[1]) << 8) |
           (static_cast<uint32_t>(data[2]) << 16) |
           (static_cast<uint32_t>(data[3]) << 24);
}

float ReadFloat(const uint8_t* data) {
    uint32_t bits = Read32(data);
    float value;
    std::memcpy(&value, &bits, sizeof(value));
    return value;
}

bool RangeFits(size_t offset, size_t length, size_t available) {
    return offset <= available && length <= available - offset;
}

} // namespace

// Entry layout used by retail 0x004470C0/0x004472E0.
bool AnmFile_ParseEntry(const uint8_t* image, size_t image_size,
                        size_t entry_offset, AnmFileEntry* output) {
    if (image == nullptr || output == nullptr ||
        !RangeFits(entry_offset, 0x40, image_size))
        return false;
    const uint8_t* entry = image + entry_offset;
    output->base = entry;
    output->available = image_size - entry_offset;
    output->sprite_count = Read32(entry + 0x00);
    output->script_count = Read32(entry + 0x04);
    output->width = Read32(entry + 0x0C);
    output->height = Read32(entry + 0x10);
    output->format = Read32(entry + 0x14);
    output->name_offset = Read32(entry + 0x1C);
    output->texture_offset = Read32(entry + 0x30);
    output->next_offset = Read32(entry + 0x38);
    size_t table_size = static_cast<size_t>(output->sprite_count) * 4u +
                        static_cast<size_t>(output->script_count) * 8u;
    return RangeFits(0x40, table_size, output->available);
}

bool AnmFile_GetSprite(const AnmFileEntry* entry, uint32_t index,
                       AnmFileSprite* output) {
    if (entry == nullptr || output == nullptr || index >= entry->sprite_count)
        return false;
    uint32_t offset = Read32(entry->base + 0x40 + index * 4u);
    if (!RangeFits(offset, 20, entry->available))
        return false;
    const uint8_t* sprite = entry->base + offset;
    output->id = Read32(sprite);
    output->x = ReadFloat(sprite + 4);
    output->y = ReadFloat(sprite + 8);
    output->width = ReadFloat(sprite + 12);
    output->height = ReadFloat(sprite + 16);
    return true;
}

bool AnmFile_FindGlobalSprite(const uint8_t* image, size_t image_size,
                              uint32_t global_index, AnmFileEntry* entry_out,
                              AnmFileSprite* sprite_out) {
    size_t offset = 0;
    for (;;) {
        AnmFileEntry entry;
        if (!AnmFile_ParseEntry(image, image_size, offset, &entry))
            return false;
        if (global_index < entry.sprite_count) {
            if (!AnmFile_GetSprite(&entry, global_index, sprite_out))
                return false;
            if (entry_out != nullptr)
                *entry_out = entry;
            return true;
        }
        global_index -= entry.sprite_count;
        if (entry.next_offset == 0 ||
            entry.next_offset > image_size - offset)
            return false;
        offset += entry.next_offset;
    }
}

bool AnmFile_FindScript(const AnmFileEntry* entry, uint32_t id,
                        AnmFileScript* output) {
    if (entry == nullptr || output == nullptr)
        return false;
    const uint8_t* table =
        entry->base + 0x40 + entry->sprite_count * 4u;
    for (uint32_t index = 0; index < entry->script_count; ++index) {
        uint32_t script_id = Read32(table + index * 8u);
        uint32_t offset = Read32(table + index * 8u + 4u);
        if (script_id == id && RangeFits(offset, 8, entry->available)) {
            output->id = id;
            output->instructions = entry->base + offset;
            return true;
        }
    }
    return false;
}

bool AnmFile_GetScriptByIndex(const AnmFileEntry* entry, uint32_t index,
                              AnmFileScript* output) {
    if (entry == nullptr || output == nullptr || index >= entry->script_count)
        return false;
    const uint8_t* record =
        entry->base + 0x40 + entry->sprite_count * 4u + index * 8u;
    uint32_t offset = Read32(record + 4);
    if (!RangeFits(offset, 8, entry->available))
        return false;
    output->id = Read32(record);
    output->instructions = entry->base + offset;
    return true;
}

bool AnmFile_FindGlobalScript(const uint8_t* image, size_t image_size,
                              uint32_t global_index, AnmFileEntry* entry_out,
                              AnmFileScript* script_out) {
    size_t offset = 0;
    for (;;) {
        AnmFileEntry entry;
        if (!AnmFile_ParseEntry(image, image_size, offset, &entry))
            return false;
        if (global_index < entry.script_count) {
            if (!AnmFile_GetScriptByIndex(&entry, global_index, script_out))
                return false;
            if (entry_out != nullptr)
                *entry_out = entry;
            return true;
        }
        global_index -= entry.script_count;
        if (entry.next_offset == 0 ||
            entry.next_offset > image_size - offset)
            return false;
        offset += entry.next_offset;
    }
}

bool AnmFile_GetTexture(const AnmFileEntry* entry,
                        AnmTexturePayload* output) {
    if (entry == nullptr || output == nullptr ||
        !RangeFits(entry->texture_offset, 16, entry->available))
        return false;
    const uint8_t* texture = entry->base + entry->texture_offset;
    if (Read32(texture) != 0x58544854u) // "THTX"
        return false;
    output->format = Read16(texture + 6);
    output->width = Read16(texture + 8);
    output->height = Read16(texture + 10);
    output->data_size = Read32(texture + 12);
    if (!RangeFits(entry->texture_offset + 16, output->data_size,
                   entry->available))
        return false;
    output->pixels = texture + 16;
    return true;
}
