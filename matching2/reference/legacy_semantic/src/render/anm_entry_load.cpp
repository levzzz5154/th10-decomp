// 0x00447470 - Load one ANM archive entry.
//
// The entry is validated, a texture is created through one of three paths
// (embedded payload, blank '@' texture, or archive image), the texture is
// published through the priority/preload/describe sequence, and the sprite and
// script tables are filled at the caller's table bases. Every failure path
// reports the corresponding retail Shift-JIS diagnostic and returns -1.
#include "th10/render/anm_entry_load.hpp"

#include <cstring>

// 0x00470274: "アニメが読み込めません。"
const char kAnmEntryMissingText[] =
    "\x83\x41\x83\x6A\x83\x81\x82\xAA\x93\xC7\x82\xDD\x8D\x9E\x82\xDF"
    "\x82\xDC\x82\xB9\x82\xF1\x81\x42";
// 0x00470254: "アニメのバージョンが違います。"
const char kAnmEntryBadVersionText[] =
    "\x83\x41\x83\x6A\x83\x81\x82\xCC\x83\x6F\x81\x5B\x83\x57\x83\x87"
    "\x83\x93\x82\xAA\x88\341\x82\xA2\x82\xDC\x82\xB7\x81\x42";
// 0x0047016C: "テクスチャが作成できません。"
const char kAnmEntryPayloadFailText[] =
    "\x83\x65\x83\x4E\x83\x58\x83\x60\x83\x83\x82\xAA\x8D\xEC\x90\xAC"
    "\x82\xC5\x82\xAB\x82\xDC\x82\xB9\x82\xF1\x81\x42";
// 0x004701B0: the same stem with a trailing " %s" for the file name.
const char kAnmEntryFileFailText[] =
    "\x83\x65\x83\x4E\x83\x58\x83\x60\x83\x83\x82\xAA\x8D\xEC\x90\xAC"
    "\x82\xC5\x82\xAB\x82\xDC\x82\xB9\x82\xF1\x81\x42 %s";

namespace {

const int kSpriteTableOffset = 0x40;
const int kSpriteRecordFloats = 17;

// Retail copies these two words into the record as raw 32-bit values rather
// than converting them, so the float slots hold the original bit patterns.
float WordToFloat(unsigned int word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

const unsigned char* EntryBytes(const AnmLoadEntry* entry) {
    return (const unsigned char*)entry;
}

int ReportError(const AnmEntryLoadHooks* hooks, const char* text) {
    hooks->log_error(hooks->context, text);
    return -1;
}

}  // namespace

const int* AnmEntry_SpriteTable(const AnmLoadEntry* entry) {
    return (const int*)(EntryBytes(entry) + kSpriteTableOffset);
}

const int* AnmEntry_ScriptTable(const AnmLoadEntry* entry) {
    // The script pairs start immediately after the sprite offset table.
    return AnmEntry_SpriteTable(entry) + entry->sprite_count;
}

void AnmSprite_DeriveRecord(float* record) {
    // Slots 2..5 hold the scaled corners, slot 6 the surface height and slot 7
    // the surface width; slots 14 and 15 hold the per-axis scale factors.
    const float left = record[2];
    const float top = record[3];
    const float right = record[4];
    const float bottom = record[5];
    const float surface_height = record[6];
    const float surface_width = record[7];
    const float scale_x = record[14];
    const float scale_y = record[15];

    // Normalized texture coordinates.
    record[8] = left / surface_width;
    record[9] = top / surface_height;
    record[10] = right / surface_width;
    record[11] = bottom / surface_height;

    // Extents recovered in unscaled sprite space.
    record[13] = (right - left) / scale_x;
    record[12] = (bottom - top) / scale_y;
}

int AnmEntry_Load(int texture_index, const void* image,
                  AnmEntryLoadOwner* owner, int sprite_base, int script_base,
                  const AnmLoadEntry* entry, const AnmEntryLoadHooks* hooks) {
    if (entry == 0) {
        return ReportError(hooks, kAnmEntryMissingText);
    }
    // Version 4 is the only stamp the retail loader accepts.
    if (entry->version != 4) {
        return ReportError(hooks, kAnmEntryBadVersionText);
    }

    AnimationTextureRecord* record = owner->textures + texture_index;
    const unsigned char* entry_bytes = EntryBytes(entry);

    if (entry->has_payload != 0) {
        // The payload offset is entry-relative.
        const void* payload = entry_bytes + entry->payload_offset;
        if (hooks->create_from_payload(hooks->context, record, entry->format,
                                       payload, entry->width,
                                       entry->height) != 0) {
            return ReportError(hooks, kAnmEntryPayloadFailText);
        }
    } else {
        const char* name = (const char*)(entry_bytes + entry->name_offset);
        if (name[0] == '@') {
            // A '@'-prefixed name means an empty managed texture, which
            // cannot fail and therefore has no diagnostic.
            hooks->create_blank(hooks->context, record, entry->format,
                                entry->width, entry->height);
        } else if (hooks->create_from_file_image(
                       hooks->context, record, entry->format, image,
                       entry->color_key, entry->width, entry->height) != 0) {
            return ReportError(hooks, kAnmEntryFileFailText);
        }
    }

    // Retail re-reads the texture interface out of the record before each of
    // these three calls, so the creation path must publish it first.
    hooks->set_priority(hooks->context, record, entry->texture_priority);
    hooks->preload(hooks->context, record);

    AnmSurfaceDesc desc;
    hooks->get_level_desc(hooks->context, record, 0, &desc);

    // The surface may be padded up to power-of-two dimensions, so sprite
    // geometry is scaled by the ratio against the declared image size.
    const float scale_x =
        (float)((double)desc.width / (double)entry->width);
    const float scale_y =
        (float)((double)desc.height / (double)entry->height);

    const int* sprite_offsets = AnmEntry_SpriteTable(entry);
    for (int index = 0; index < entry->sprite_count; ++index) {
        const float* sprite =
            (const float*)(entry_bytes + sprite_offsets[index]);
        float* destination =
            owner->sprite_records + (sprite_base + index) * kSpriteRecordFloats;

        // Slots 0 and 1 are raw word copies, not arithmetic values.
        destination[0] = WordToFloat(owner->header_word);
        destination[1] = WordToFloat(record->texture);

        // The sprite record stores {id, x, y, width, height}.
        destination[2] = sprite[1] * scale_x;
        destination[3] = sprite[2] * scale_y;
        destination[4] = (sprite[3] + sprite[1]) * scale_x;
        destination[5] = (sprite[4] + sprite[2]) * scale_y;
        destination[6] = (float)desc.height;
        destination[7] = (float)desc.width;
        destination[14] = scale_x;
        destination[15] = scale_y;
        destination[16] = 0.0f;

        // 0x00447940 (arithmetic half) fills the remaining slots.
        AnmSprite_DeriveRecord(destination);
    }

    // Script entries are {id, offset} pairs; only the entry-relative offset is
    // published.
    const int* script_table = AnmEntry_ScriptTable(entry);
    for (int index = 0; index < entry->script_count; ++index) {
        owner->script_table[script_base + index] =
            entry_bytes + script_table[index * 2 + 1];
    }

    return 1;
}
