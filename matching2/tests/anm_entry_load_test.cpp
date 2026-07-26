// Focused semantic tests for the ANM archive-entry loader (0x00447470) and
// the sprite-record arithmetic it shares with 0x00447940.
#include "th10/render/anm_entry_load.hpp"

#include <cassert>
#include <cmath>
#include <cstring>

namespace {

// --- Archive image scaffolding ----------------------------------------------
//
// One entry header followed by its sprite offset table, script table, sprite
// records, a name string and an embedded payload, all inside a single buffer
// so every offset in the header stays entry-relative like retail.

const int kSpriteTableOffset = 0x40;
const int kScriptTableOffset = 0x40 + 2 * 4;         // two sprites
const int kSpriteRecordsOffset = kScriptTableOffset + 2 * 2 * 4;
const int kNameOffset = 0x100;
const int kPayloadOffset = 0x140;
const int kScriptBodyOffset = 0x180;

unsigned char g_image[0x400];

AnmLoadEntry* BuildEntry(bool has_payload, const char* name) {
    std::memset(g_image, 0, sizeof(g_image));
    AnmLoadEntry* entry = (AnmLoadEntry*)g_image;
    entry->sprite_count = 2;
    entry->script_count = 2;
    entry->width = 128;
    entry->height = 64;
    entry->format = 3;
    entry->color_key = 0x00FF00FF;
    entry->name_offset = kNameOffset;
    entry->version = 4;
    entry->texture_priority = 7;
    entry->payload_offset = kPayloadOffset;
    entry->has_payload = has_payload ? 1 : 0;
    entry->next_offset = 0;

    int* sprite_offsets = (int*)(g_image + kSpriteTableOffset);
    sprite_offsets[0] = kSpriteRecordsOffset;
    sprite_offsets[1] = kSpriteRecordsOffset + 5 * 4;

    // Sprite records: {id, x, y, width, height}.
    float* sprite0 = (float*)(g_image + kSpriteRecordsOffset);
    sprite0[0] = 0.0f;
    sprite0[1] = 16.0f;
    sprite0[2] = 8.0f;
    sprite0[3] = 32.0f;
    sprite0[4] = 16.0f;
    float* sprite1 = (float*)(g_image + kSpriteRecordsOffset + 5 * 4);
    sprite1[0] = 1.0f;
    sprite1[1] = 0.0f;
    sprite1[2] = 0.0f;
    sprite1[3] = 128.0f;
    sprite1[4] = 64.0f;

    // Script table: {id, offset} pairs.
    int* script_table = (int*)(g_image + kScriptTableOffset);
    script_table[0] = 100;
    script_table[1] = kScriptBodyOffset;
    script_table[2] = 101;
    script_table[3] = kScriptBodyOffset + 0x20;

    std::strcpy((char*)(g_image + kNameOffset), name);
    return entry;
}

// --- Owner scaffolding -------------------------------------------------------

AnimationTextureRecord g_textures[4];
float g_sprite_records[8 * 17];
const void* g_script_slots[8];

AnmEntryLoadOwner MakeOwner() {
    std::memset(g_textures, 0, sizeof(g_textures));
    std::memset(g_sprite_records, 0, sizeof(g_sprite_records));
    std::memset(g_script_slots, 0, sizeof(g_script_slots));
    AnmEntryLoadOwner owner;
    owner.header_word = 0xABCD1234u;
    owner.sprite_records = g_sprite_records;
    owner.script_table = g_script_slots;
    owner.textures = g_textures;
    return owner;
}

// --- Hook scaffolding --------------------------------------------------------

int g_payload_calls;
int g_file_calls;
int g_blank_calls;
int g_payload_result;
int g_file_result;
const void* g_payload_seen;
const void* g_image_seen;
int g_color_key_seen;
int g_format_seen;
int g_width_seen;
int g_height_seen;

int g_priority_calls;
int g_priority_seen;
int g_preload_calls;
int g_desc_calls;
int g_desc_level_seen;
unsigned int g_surface_width = 256;
unsigned int g_surface_height = 128;
unsigned int g_texture_word = 0x00DEAD00u;

int g_log_calls;
const char* g_last_log;

int CreateFromPayload(void* context, AnimationTextureRecord* record,
                      int format, const void* payload, int width, int height) {
    (void)context;
    ++g_payload_calls;
    g_payload_seen = payload;
    g_format_seen = format;
    g_width_seen = width;
    g_height_seen = height;
    if (g_payload_result == 0) record->texture = g_texture_word;
    return g_payload_result;
}

int CreateFromFileImage(void* context, AnimationTextureRecord* record,
                        int format, const void* image, int color_key,
                        int width, int height) {
    (void)context;
    ++g_file_calls;
    g_image_seen = image;
    g_color_key_seen = color_key;
    g_format_seen = format;
    g_width_seen = width;
    g_height_seen = height;
    if (g_file_result == 0) record->texture = g_texture_word;
    return g_file_result;
}

void CreateBlank(void* context, AnimationTextureRecord* record, int format,
                 int width, int height) {
    (void)context;
    ++g_blank_calls;
    g_format_seen = format;
    g_width_seen = width;
    g_height_seen = height;
    record->texture = g_texture_word;
}

void SetPriority(void* context, AnimationTextureRecord* record, int priority) {
    (void)context;
    (void)record;
    ++g_priority_calls;
    g_priority_seen = priority;
}

void Preload(void* context, AnimationTextureRecord* record) {
    (void)context;
    (void)record;
    // Retail reads the interface out of the record again before this call,
    // so the texture must already be published by the creation path.
    assert(record->texture == g_texture_word);
    ++g_preload_calls;
}

void GetLevelDesc(void* context, AnimationTextureRecord* record, int level,
                  AnmSurfaceDesc* desc_out) {
    (void)context;
    (void)record;
    ++g_desc_calls;
    g_desc_level_seen = level;
    std::memset(desc_out, 0, sizeof(*desc_out));
    desc_out->width = g_surface_width;
    desc_out->height = g_surface_height;
}

void LogError(void* context, const char* text) {
    (void)context;
    ++g_log_calls;
    g_last_log = text;
}

AnmEntryLoadHooks MakeHooks() {
    g_payload_calls = 0;
    g_file_calls = 0;
    g_blank_calls = 0;
    g_payload_result = 0;
    g_file_result = 0;
    g_priority_calls = 0;
    g_preload_calls = 0;
    g_desc_calls = 0;
    g_log_calls = 0;
    g_last_log = 0;

    AnmEntryLoadHooks hooks;
    hooks.context = 0;
    hooks.create_from_payload = CreateFromPayload;
    hooks.create_from_file_image = CreateFromFileImage;
    hooks.create_blank = CreateBlank;
    hooks.set_priority = SetPriority;
    hooks.preload = Preload;
    hooks.get_level_desc = GetLevelDesc;
    hooks.log_error = LogError;
    return hooks;
}

bool Near(float value, float expected) {
    return std::fabs(value - expected) < 1.0e-5f;
}

float WordAsFloat(unsigned int word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}

// --- Tests -------------------------------------------------------------------

void TestRejectsMissingEntry() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, 0, &hooks) == -1);
    assert(g_log_calls == 1);
    assert(g_last_log == kAnmEntryMissingText);
    assert(g_payload_calls == 0 && g_file_calls == 0 && g_blank_calls == 0);
}

void TestRejectsForeignVersion() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    entry->version = 3;
    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == -1);
    assert(g_last_log == kAnmEntryBadVersionText);
    assert(g_priority_calls == 0);

    // Version 4 is the only accepted value; 5 is rejected as well.
    entry->version = 5;
    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == -1);
    assert(g_log_calls == 2);
}

void TestEmbeddedPayloadPath() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");

    assert(AnmEntry_Load(2, g_image, &owner, 0, 0, entry, &hooks) == 1);
    assert(g_payload_calls == 1);
    assert(g_file_calls == 0 && g_blank_calls == 0);
    // The payload address is entry-relative, not image-relative.
    assert(g_payload_seen == (const void*)(g_image + kPayloadOffset));
    assert(g_format_seen == 3);
    assert(g_width_seen == 128 && g_height_seen == 64);
    // The texture record selected is the one at the requested index.
    assert(g_textures[2].texture == g_texture_word);
    assert(g_textures[0].texture == 0);
    // Priority, preload and the level-0 description all run once, in order.
    assert(g_priority_calls == 1 && g_priority_seen == 7);
    assert(g_preload_calls == 1);
    assert(g_desc_calls == 1 && g_desc_level_seen == 0);
    assert(g_log_calls == 0);
}

void TestPayloadFailureIsReported() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    g_payload_result = -1;

    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == -1);
    assert(g_last_log == kAnmEntryPayloadFailText);
    // No texture work and no sprite/script publication after a failed upload.
    assert(g_priority_calls == 0 && g_preload_calls == 0 && g_desc_calls == 0);
    assert(g_sprite_records[0] == 0.0f);
    assert(g_script_slots[0] == 0);
}

void TestNamedFilePath() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(false, "stage01.png");

    assert(AnmEntry_Load(1, g_image, &owner, 0, 0, entry, &hooks) == 1);
    assert(g_file_calls == 1);
    assert(g_payload_calls == 0 && g_blank_calls == 0);
    // The whole archive image is handed to the loader, plus the color key.
    assert(g_image_seen == (const void*)g_image);
    assert(g_color_key_seen == 0x00FF00FF);
    assert(g_width_seen == 128 && g_height_seen == 64);

    g_file_result = -1;
    assert(AnmEntry_Load(1, g_image, &owner, 0, 0, entry, &hooks) == -1);
    assert(g_last_log == kAnmEntryFileFailText);
}

void TestBlankTexturePath() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    // A leading '@' selects the blank managed texture instead of a file load.
    AnmLoadEntry* entry = BuildEntry(false, "@blank");

    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == 1);
    assert(g_blank_calls == 1);
    assert(g_file_calls == 0 && g_payload_calls == 0);
    assert(g_format_seen == 3);
    assert(g_width_seen == 128 && g_height_seen == 64);
    // The blank path cannot fail, so nothing is ever logged for it.
    assert(g_log_calls == 0);

    // The payload flag wins over the name: '@' is only consulted when the
    // entry carries no embedded payload.
    hooks = MakeHooks();
    entry->has_payload = 1;
    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == 1);
    assert(g_blank_calls == 0 && g_payload_calls == 1);
}

void TestSpriteRecordsUseSurfaceScale() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    // A 128x64 declared image loaded into a 256x128 surface scales by 2.
    g_surface_width = 256;
    g_surface_height = 128;

    assert(AnmEntry_Load(0, g_image, &owner, 3, 0, entry, &hooks) == 1);

    // Sprites are published at sprite_base + index, leaving earlier slots
    // untouched.
    assert(g_sprite_records[0] == 0.0f);
    const float* record = g_sprite_records + 3 * 17;

    // Slots 0 and 1 carry the owner header word and the texture word
    // verbatim, as raw 32-bit copies rather than arithmetic values.
    assert(record[0] == WordAsFloat(0xABCD1234u));
    assert(record[1] == WordAsFloat(g_texture_word));

    // Corners: x/y scaled, then the far corner from x+width, y+height.
    assert(Near(record[2], 32.0f));    // 16 * 2
    assert(Near(record[3], 16.0f));    // 8 * 2
    assert(Near(record[4], 96.0f));    // (32 + 16) * 2
    assert(Near(record[5], 48.0f));    // (16 + 8) * 2

    // Slot 6 holds the surface height and slot 7 the surface width.
    assert(Near(record[6], 128.0f));
    assert(Near(record[7], 256.0f));

    // Normalized coordinates divide x by slot 7 and y by slot 6.
    assert(Near(record[8], 32.0f / 256.0f));
    assert(Near(record[9], 16.0f / 128.0f));
    assert(Near(record[10], 96.0f / 256.0f));
    assert(Near(record[11], 48.0f / 128.0f));

    // Slots 12 and 13 recover the unscaled sprite extents.
    assert(Near(record[13], 32.0f));
    assert(Near(record[12], 16.0f));

    // Slots 14 and 15 keep the per-axis scale factors.
    assert(Near(record[14], 2.0f));
    assert(Near(record[15], 2.0f));

    // The second sprite covers the whole declared image.
    const float* second = g_sprite_records + 4 * 17;
    assert(Near(second[2], 0.0f));
    assert(Near(second[4], 256.0f));
    assert(Near(second[5], 128.0f));
    assert(Near(second[8], 0.0f));
    assert(Near(second[10], 1.0f));
    assert(Near(second[11], 1.0f));
    assert(Near(second[13], 128.0f));
    assert(Near(second[12], 64.0f));
}

void TestUnscaledSurfaceKeepsSpriteGeometry() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    g_surface_width = 128;
    g_surface_height = 64;

    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == 1);
    const float* record = g_sprite_records;
    assert(Near(record[14], 1.0f) && Near(record[15], 1.0f));
    assert(Near(record[2], 16.0f) && Near(record[3], 8.0f));
    assert(Near(record[4], 48.0f) && Near(record[5], 24.0f));
    assert(Near(record[13], 32.0f) && Near(record[12], 16.0f));
}

void TestNonUniformScale() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    // Only the height is padded up to the next power of two.
    g_surface_width = 128;
    g_surface_height = 256;

    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == 1);
    const float* record = g_sprite_records;
    assert(Near(record[14], 1.0f));
    assert(Near(record[15], 4.0f));
    assert(Near(record[2], 16.0f));
    assert(Near(record[3], 32.0f));
    assert(Near(record[5], 96.0f));
    // The recovered extents stay in unscaled sprite space on both axes.
    assert(Near(record[13], 32.0f));
    assert(Near(record[12], 16.0f));
}

void TestScriptPointersArePublished() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");

    assert(AnmEntry_Load(0, g_image, &owner, 0, 2, entry, &hooks) == 1);
    // Scripts land at script_base + index and resolve entry-relative.
    assert(g_script_slots[0] == 0 && g_script_slots[1] == 0);
    assert(g_script_slots[2] == (const void*)(g_image + kScriptBodyOffset));
    assert(g_script_slots[3] ==
           (const void*)(g_image + kScriptBodyOffset + 0x20));
}

void TestEmptyTables() {
    AnmEntryLoadHooks hooks = MakeHooks();
    AnmEntryLoadOwner owner = MakeOwner();
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    entry->sprite_count = 0;
    entry->script_count = 0;

    assert(AnmEntry_Load(0, g_image, &owner, 0, 0, entry, &hooks) == 1);
    // The texture is still created and described even with no tables.
    assert(g_payload_calls == 1 && g_desc_calls == 1);
    assert(g_sprite_records[0] == 0.0f);
    assert(g_script_slots[0] == 0);
}

void TestScriptTableFollowsSpriteTable() {
    AnmLoadEntry* entry = BuildEntry(true, "stage01.png");
    assert(AnmEntry_SpriteTable(entry) ==
           (const int*)(g_image + kSpriteTableOffset));
    // Two sprites means the script pairs begin two dwords later.
    assert(AnmEntry_ScriptTable(entry) ==
           (const int*)(g_image + kScriptTableOffset));

    entry->sprite_count = 5;
    assert(AnmEntry_ScriptTable(entry) ==
           (const int*)(g_image + kSpriteTableOffset + 5 * 4));
}

void TestDeriveRecordMatchesCopyPath() {
    // The arithmetic half shared with 0x00447940 operates purely on an
    // already-populated record.
    float record[17];
    std::memset(record, 0, sizeof(record));
    record[2] = 10.0f;
    record[3] = 20.0f;
    record[4] = 50.0f;
    record[5] = 60.0f;
    record[6] = 200.0f;
    record[7] = 100.0f;
    record[14] = 4.0f;
    record[15] = 8.0f;

    AnmSprite_DeriveRecord(record);
    assert(Near(record[8], 0.1f));
    assert(Near(record[10], 0.5f));
    assert(Near(record[9], 0.1f));
    assert(Near(record[11], 0.3f));
    assert(Near(record[13], 10.0f));
    assert(Near(record[12], 5.0f));
}

}  // namespace

int main() {
    TestRejectsMissingEntry();
    TestRejectsForeignVersion();
    TestEmbeddedPayloadPath();
    TestPayloadFailureIsReported();
    TestNamedFilePath();
    TestBlankTexturePath();
    TestSpriteRecordsUseSurfaceScale();
    TestUnscaledSurfaceKeepsSpriteGeometry();
    TestNonUniformScale();
    TestScriptPointersArePublished();
    TestEmptyTables();
    TestScriptTableFollowsSpriteTable();
    TestDeriveRecordMatchesCopyPath();
    return 0;
}
