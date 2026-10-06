// 0x00432690: fill the ten text lines of the title's spell card record page.
//
// The page lists the spell cards of the selected difficulty, ten to a page.
// A card that has been met shows its name padded to a fixed width and the
// selected character's captures and attempts; a card never met shows a
// masked name. Lines beyond the last card are blanked.
//
// The menu arrives in ECX. Native LTCG passes each line's animation to the
// centred formatter in ESI.
#include <string.h>

#include "th10/game/right_aligned_text_context/recovery_script_executor_caller_00419120.hpp"
#include "th10/game/score_file.hpp"
#include "th10/game/title_menu_draw.hpp"

extern "C" void* data_00491c10;
// Existing retail strings; the diagnostic layout binds their original addresses.
// Named: "No.%3d %s %4d/%4d". Masked: "No.%3d ", twenty-one full-width
// question marks in Shift-JIS, then " %4d/%4d". Empty: one space.
extern "C" const char NamedCardFormat[];
extern "C" const char MaskedCardFormat[];
extern "C" const char EmptyCardText[];

static inline ScoreManager* Scores() { return reinterpret_cast<ScoreManager*>(data_0047783c); }

// The animation with this id, searching both of the manager's lists.
static inline RecoveryIndicatorVm_00419120* FindAnimation(void* manager, unsigned int id) {
    if (id == 0)
        return 0;
    RecoveryLookupContext_0040bd80* context = static_cast<RecoveryLookupContext_0040bd80*>(manager);
    for (RecoveryLookupNode_0040bd80* node = context->primary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
    for (RecoveryLookupNode_0040bd80* node = context->secondary; node != 0; node = node->next)
        if (*reinterpret_cast<unsigned int*>(node->object) == id)
            return reinterpret_cast<RecoveryIndicatorVm_00419120*>(node->object);
    return 0;
}

#pragma code_seg(".text$00432690_fn")
int TitleMenu_00431410::BuildSpellList() {
    char name[168];
    int spell = 0;
    for (int skipped = 0; skipped < spell_page * 10 - 10; ++spell) {
        if (g_spell_difficulty[spell] == difficulty)
            ++skipped;
    }
    listed_spells = 0;
    for (int line = 0; line < 10; ++line) {
        while (spell < SCORE_SPELL_COUNT && g_spell_difficulty[spell] != difficulty)
            ++spell;
        if (spell >= SCORE_SPELL_COUNT) {
            for (; line < 10; ++line) {
                void* manager = data_00491c10;
                RecoveryIndicatorVm_00419120* text = FindAnimation(manager, spell_lines[line]);
                if (text == 0)
                    spell_lines[line] = 0;
                text->FormatCentered(manager, 0xFFFFFFFF, EmptyCardText);
            }
            break;
        }
        if (Scores()->records[6].spells[spell].attempts != 0) {
            strcpy(name, Scores()->records[6].spells[spell].name);
            int length = strlen(name);
            if (length < 42) {
                size_t pad = 42 - length;
                memset(name + length, ' ', pad);
                length += pad;
            }
            name[length] = '\0';
            ScoreRecordSection* record = &Scores()->records[cursor];
            void* manager = data_00491c10;
            RecoveryIndicatorVm_00419120* text = FindAnimation(manager, spell_lines[line]);
            if (text == 0)
                spell_lines[line] = 0;
            text->FormatCentered(manager, record->spells[spell].captures != 0 ? 0xFFFF80 : 0xEFEFEF,
                                 NamedCardFormat, spell + 1, name,
                                 record->spells[spell].counts);
            ++spell;
        } else {
            ScoreRecordSection* record = &Scores()->records[cursor];
            void* manager = data_00491c10;
            RecoveryIndicatorVm_00419120* text = FindAnimation(manager, spell_lines[line]);
            if (text == 0)
                spell_lines[line] = 0;
            text->FormatCentered(
                manager, 0x808080,
                MaskedCardFormat, spell + 1, record->spells[spell].counts);
            ++spell;
        }
        ++listed_spells;
    }
    return 0;
}
#pragma code_seg()
