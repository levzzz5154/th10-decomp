#include <stddef.h>
#include <string.h>
#include "th10/game/name_entry_queue_00401530.hpp"

struct NameEntryState_004224c0 {
    unsigned char reserved_000[0xFC];
    int selected_glyph;
    unsigned char reserved_100[0x1E0 - 0x100];
    int name_length;
    unsigned char reserved_1e4[0x2B4 - 0x1E4];
    char name[12];
};

typedef char NameEntry_selection_is_fc[offsetof(NameEntryState_004224c0, selected_glyph) == 0xFC ? 1 : -1];
typedef char NameEntry_length_is_1e0[offsetof(NameEntryState_004224c0, name_length) == 0x1E0 ? 1 : -1];
typedef char NameEntry_name_is_2b4[offsetof(NameEntryState_004224c0, name) == 0x2B4 ? 1 : -1];
typedef char NameEntry_position_is_12[sizeof(Vec3_00401530) == 12 ? 1 : -1];

extern "C" {
extern const char* g_name_entry_grid;
extern GameThread_00401530* g_ascii_manager;
extern const char str_string_format[];
extern const char str_underscore[];
extern const char str_char_format[];
}

#pragma code_seg(".text$04characters")
extern "C" __declspec(noinline) void __stdcall DrawNameEntry_004224c0(
    NameEntryState_004224c0* state, Vec3_00401530 position) {
    int character_count = static_cast<int>(strlen(g_name_entry_grid));
    AsciiManager_AddFormatted(&position, g_ascii_manager, str_string_format, state->name);
    position.x += static_cast<float>(state->name_length * 9);
    if (state->name_length == 8)
        position.x -= 9.0f;
    g_ascii_manager->current_4c = 0xFFFFFF00;
    AsciiManager_AddFormatted(&position, g_ascii_manager, str_underscore);
    g_ascii_manager->current_4c = 0xFFFFFFFF;

    position.x = 112.0f;
    position.y = 320.0f;
    position.z = 0.0f;
    for (int index = 0; index < character_count; ++index) {
        g_ascii_manager->current_4c = state->selected_glyph == index ? 0xFFFFFF00 : 0xFF808080;
        if (index < character_count - 3)
            AsciiManager_AddFormatted(&position, g_ascii_manager, str_char_format, g_name_entry_grid[index]);
        else
            AsciiManager_AddFormatted(&position, g_ascii_manager, str_char_format,
                index == character_count - 3 ? 0x81 :
                index == character_count - 2 ? 0x7F : 0x80);
        if (static_cast<unsigned int>(index) % 13 == 12) {
            position.x = 112.0f;
            position.y += 16.0f;
        } else {
            position.x += 18.0f;
        }
    }
    g_ascii_manager->current_4c = 0xFFFFFFFF;
}
#pragma code_seg()
