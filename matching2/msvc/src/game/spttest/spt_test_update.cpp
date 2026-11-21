// 0x0042BFC0: run the "Spt Test" debug screen. State 0 lists the script
// files and resets the three menus, state 1 is the menu (load a file on the
// loader thread, run an entry of the loaded script, or quit), state 4 steps
// the running entry until it ends.
// 0x0042C580: the scheduler callback, a tail jump with the screen in ECX.
#include "th10/game/spt_test_update.hpp"

enum SptTestState {
    SPTTEST_STATE_INIT = 0,
    SPTTEST_STATE_MENU = 1,
    SPTTEST_STATE_LOADING = 2,
    SPTTEST_STATE_RUNNING = 4
};

enum SptTestMenuItem {
    SPTTEST_ITEM_FILE = 0,
    SPTTEST_ITEM_ENTRY = 1,
    SPTTEST_ITEM_QUIT = 2
};

enum SptTestKeyMask {
    SPTTEST_KEY_UP = 0x0010,
    SPTTEST_KEY_DOWN = 0x0020,
    SPTTEST_KEY_LEFT = 0x0040,
    SPTTEST_KEY_RIGHT = 0x0080,
    SPTTEST_KEY_CONFIRM = 0x1001
};

#pragma code_seg(".text$b1update")
int SptTest2::Update() {
    SptTestFindData find;
    switch (state) {
    case SPTTEST_STATE_RUNNING:
        SptTest_TickVm(resource, 1.0f);
        if (resource && resource->active->running) break;
        if (resource) resource->Retire(1);
        resource = 0;
        state = SPTTEST_STATE_MENU;
        break;
    case SPTTEST_STATE_MENU:
        SptTest_Remember(&menu);
        if (g_input_keys_raw.Active(SPTTEST_KEY_DOWN)) menu.Advance(1);
        if (g_input_keys_raw.Active(SPTTEST_KEY_UP)) menu.Advance(-1);
        switch (menu.selection) {
        case SPTTEST_ITEM_QUIT:
            if (g_input_keys_raw.repeated & SPTTEST_KEY_CONFIRM)
                SptTest_SetGameMode(&g_application, 3);
            break;
        case SPTTEST_ITEM_ENTRY:
            if (parser) {
                SptTest_Remember(&entry_cursor);
                if (g_input_keys_raw.MaskActive(SPTTEST_KEY_RIGHT)) entry_cursor.Advance(1);
                if (g_input_keys_raw.MaskActive(SPTTEST_KEY_LEFT)) entry_cursor.Advance(-1);
                if (g_input_keys_raw.pressed & SPTTEST_KEY_CONFIRM) {
                    if (resource) {
                        resource->Retire(1);
                        resource = 0;
                    }
                    const char* name = parser->entries[entry_cursor.selection].name;
                    resource = parser->CreateVm(name);
                    state = SPTTEST_STATE_RUNNING;
                }
            }
            break;
        case SPTTEST_ITEM_FILE:
            SptTest_Remember(&file_cursor);
            if (g_input_keys_raw.Active(SPTTEST_KEY_RIGHT)) file_cursor.Advance(1);
            if (g_input_keys_raw.Active(SPTTEST_KEY_LEFT)) file_cursor.Advance(-1);
            if (g_input_keys_raw.repeated & SPTTEST_KEY_CONFIRM) {
                flags &= ~2u;
                reinterpret_cast<PlatformWorker*>(&worker)->Start(this, SptTest_LoadThread);
                state = SPTTEST_STATE_LOADING;
            }
            break;
        }
        break;
    case SPTTEST_STATE_INIT: {
        ClearScriptNames();
        int count = 0;
        void* search = FindFirstFileA("../../data/*.ecl", &find);
        if (search != reinterpret_cast<void*>(-1)) {
            do {
                count++;
            } while (FindNextFileA(search, &find));
        }
        FindClose(search);
        script_count = count;
        if (count) {
            script_names = static_cast<const char**>(malloc(count * 4));
            search = FindFirstFileA("../../data/*.ecl", &find);
            for (int i = 0; i < count; i++) {
                script_names[i] = static_cast<char*>(malloc(strlen(find.name) + 1));
                strcpy(const_cast<char*>(script_names[i]), find.name);
                if (!FindNextFileA(search, &find)) break;
            }
            FindClose(search);
        }
        menu.item_count = 3;
        menu.wrap = 1;
        SptTest_Select(menu, 0);
        file_cursor.item_count = count;
        file_cursor.wrap = 1;
        SptTest_Select(file_cursor, 0);
        entry_cursor.item_count = 1;
        entry_cursor.wrap = 1;
        SptTest_Select(entry_cursor, 0);
        state = SPTTEST_STATE_MENU;
        position_x = 0.0f;
        position_y = 32.0f;
        position_z = 0.0f;
        field_2d0 = 1000;
        break;
    }
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$b2task")
int __fastcall SptTest_UpdateTask2(SptTest2* viewer) {
    return viewer->Update();
}
#pragma code_seg()
