// 0x00432CB0..0x00433227: high score name entry of the title menu (and its
// four-entry phase table), shown after a game that was not a replay.
//
// Phase 0 starts the score music, shows the character, shot type and
// difficulty of the game and enters the score into its table.  With a rank
// the cursor goes to the new line and the name entered last time is
// proposed; without one there is nothing to type and any button leaves.
// Phase 1 waits seven frames.  Phase 2 moves over the character grid, 13
// cells a row: the last three cells are space, backspace and end, and end
// stores the name.  Phase 3 removes the screen after six frames.
//
// The dispatcher passes the room on the stack. The inlined keyboard update
// borrows that pointer slot, leaving a separate home for the animation handle.
#include "th10/game/name_entry_update.hpp"
#include "th10/game/title_score_file.hpp"

enum { GridColumns = 13, MaxNameLength = 8 };
enum NameEntryPhase { StartEntry, WaitForInput, EditName, CloseEntry };

// An empty menu retains the requested selection.
static __forceinline void SelectClampedItem(MenuCursor& cursor, int index) {
    if (cursor.item_count != 0)
        cursor.selection = index >= cursor.item_count ? cursor.item_count - 1 : ((index < 0) - 1) & index;
    else
        cursor.selection = index;
}

static __forceinline ScoreTable& CurrentScoreTable() {
    return g_score->shots[g_globals_character][g_globals_shot_type].table;
}

// A full-run score uses the end of the stage table, not a playable stage.
static __forceinline int InsertCompletedRunScore() {
    g_globals_stage = StageRouteCount;
    g_globals_stage_shown = StageRouteCount;
    g_stage_route_current = g_stage_routes + StageRouteCount;
    int rank = CurrentScoreTable().InsertScore();
    g_stage_route_current = g_stage_routes;
    g_globals_stage = 0;
    g_globals_stage_shown = 0;
    return rank;
}

static __forceinline void SaveSelectedName(const Title* title, const char* name) {
    strcpy(CurrentScoreTable().records[g_globals_difficulty][title->cursor.selection].name, name);
    strcpy(g_score->last_name, name);
}

static __forceinline void WriteNameCharacter(Title& title, const char& character, int gridSize) {
    if (title.keyboard.name_length < MaxNameLength) {
        title.keyboard.name[title.keyboard.name_length] = character;
        if (++title.keyboard.name_length >= MaxNameLength)
            UpdateBoundedCounter(gridSize - 1, reinterpret_cast<unsigned int*>(&title.keyboard.grid));
    } else {
        title.keyboard.name[title.keyboard.name_length - 1] = character;
    }
}

static __forceinline void EraseLastNameCharacter(Title& title) {
    title.keyboard.name[--title.keyboard.name_length] = ' ';
}

struct NameEntryScreen {
    Title* const& room;
};

static __forceinline int UpdateNameEntryScreen(const NameEntryScreen& screen) {
    Title* room = screen.room;
    void* handle;
    switch (room->phase) {
    case StartEntry: {
        room->cursor.item_count = 30;
        Music_Load2(0, "bgm/th10_17.wav");
        Music_Play2(0, 17);
        EnsureTitleMenuBackdrop(room, handle);
        RecoveryMusicInstallSlot(room, 104);
        room->SetTimerTarget(WaitForInput);
        RecoveryMusicInstallSlot(room, g_globals_character + 152);
        RecoveryMusicInstallSlot(room, g_globals_character * 3 + g_globals_shot_type + 154);
        RecoveryMusicInstallSlot(room, g_globals_difficulty + 160);
        int rank = InsertCompletedRunScore();
        if (rank >= 0) {
            room->timer.Set(0);
            room->cursor.wrap = 1;
            UpdateBoundedCounter(rank, reinterpret_cast<unsigned int*>(&room->cursor));
            MenuCursor* grid = &room->keyboard.grid;
            SelectClampedItem(*grid, 0);
            room->keyboard.grid.item_count = strlen(g_name_entry_grid);
            room->keyboard.grid.wrap = 1;
            strcpy(room->keyboard.name, g_score->last_name);
            if (strcmp(room->keyboard.name, "        ") != 0)
                grid->Advance(-1);
            int length;
            for (length = MaxNameLength; length > 0; --length) {
                if (room->keyboard.name[length - 1] != ' ')
                    break;
            }
            room->keyboard.name_length = length;
            room->keyboard.name_confirmed = 0;
        } else {
            SelectClampedItem(room->cursor, -1);
            room->keyboard.name_confirmed = 1;
        }
    }
    // Setup also runs the input-delay check on its first frame.
    case WaitForInput:
        if (room->timer.current > 6)
            room->SetTimerTarget(EditName);
        break;
    case EditName:
        if (room->keyboard.name_confirmed == 0) {
            KeyRepeatState* input = &g_input_keys_raw;
            MenuCursor* grid = &room->keyboard.grid;
            grid->previous_selection = grid->selection;
            if ((short)input->InputMaskActive(0x10)) grid->Advance(-GridColumns);
            if ((short)input->InputMaskActive(0x20)) grid->Advance(GridColumns);
            if ((short)input->InputMaskActive(0x40)) {
                if (grid->selection % GridColumns != 0)
                    grid->Advance(-1);
                else
                    grid->Advance(GridColumns - 1);
            }
            if ((short)input->InputMaskActive(0x80)) {
                if (grid->selection % GridColumns != GridColumns - 1)
                    grid->Advance(1);
                else
                    grid->Advance(1 - GridColumns);
            }
            if (grid->previous_selection != grid->selection)
                g_sound_manager.Queue(12, 0);
        }
        if (g_input_keys_held & 0x1001) {
            if (room->keyboard.name_confirmed == 0) {
                const char* characters = g_name_entry_grid;
                int count = strlen(characters);
                int cell = room->keyboard.grid.selection;
                if (cell < count - 3) {
                    WriteNameCharacter(*room, characters[cell], count);
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 3) {
                    WriteNameCharacter(*room, ' ', count);
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 2) {
                    if (room->keyboard.name_length == 0)
                        break;
                    EraseLastNameCharacter(*room);
                    g_sound_manager.Queue(10, 0);
                } else if (cell == count - 1) {
                    SaveSelectedName(room, room->keyboard.name);
                    room->SetTimerTarget(CloseEntry);
                    g_sound_manager.Queue(10, 0);
                } else {
                    g_sound_manager.Queue(10, 0);
                }
            } else {
                room->SetTimerTarget(CloseEntry);
                g_sound_manager.Queue(10, 0);
            }
        }
        if (g_input_keys_held & 0xa) {
            if (room->keyboard.name_confirmed == 0) {
                if (room->keyboard.name_length == 0)
                    break;
                g_sound_manager.Queue(11, 0);
                EraseLastNameCharacter(*room);
            } else {
                room->SetTimerTarget(CloseEntry);
                g_sound_manager.Queue(10, 0);
            }
        }
        break;
    case CloseEntry:
        if (room->timer.current >= 6) {
            room->ClearAnimationSlot(104);
            room->ClearAnimationSlot(g_globals_character + 152);
            room->ClearAnimationSlot(g_globals_character * 3 + g_globals_shot_type + 154);
            room->ClearAnimationSlot(g_globals_difficulty + 160);
            room->DisableTimerWithOwner(16);
        }
        break;
    }
    return 1;
}

#pragma code_seg(".text$00432cb0_fn")
__declspec(noinline) int __stdcall TitleNameEntry(Title* room) {
    NameEntryScreen screen = { room };
    return UpdateNameEntryScreen(screen);
}
#pragma code_seg()
