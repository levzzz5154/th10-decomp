// 0x0040A450: run the "SprtView" debug screen. State 0 lists the script files
// and resets the three menus, state 1 is the menu (reload the managers for a
// file on the loader thread, spawn an entry of the loaded script as an enemy,
// or quit), state 4 polls the keys itself and returns to the menu on key 8.
// 0x0040ABE0: the scheduler callback, which forwards its ECX context.
#include "th10/game/ecl_view_update.hpp"

#pragma code_seg(".text$b1update")
int EclView::Update() {
    EclViewFindData find;
    switch (state) {
    case 4:
        g_input_keys_raw.previous_keys = g_input_keys_raw.held_keys;
        g_input_keys_raw.held_keys = g_input_keys_raw.raw;
        g_input_keys_raw.Update();
        g_input_keys_raw.new_press = g_input_keys_raw.repeated;
        if (g_input_keys_raw.new_press & 8) {
            g_player->Resume();
            g_player->Reset();
            g_bullet_manager->Resume();
            g_bullet_manager->Reset();
            g_enemy_ctrl->Resume();
            g_enemy_ctrl->Clear();
            g_item_manager->Resume();
            memset(g_item_manager->slots, 0, sizeof(g_item_manager->slots));
            state = 1;
        }
        break;
    case 1:
        EclView_Remember(&menu);
        if (g_input_keys_raw.Active(0x20)) menu.Advance(1);
        if (g_input_keys_raw.Active(0x10)) menu.Advance(-1);
        switch (menu.selection) {
        case 2:
            if (g_input_keys_raw.repeated & 0x1001)
                EclView_SetGameMode(&g_application, 3);
            break;
        case 1:
            if (g_enemy_ctrl) {
                EclView_Remember(&entry_cursor);
                if (g_input_keys_raw.MaskActive(0x80)) entry_cursor.Advance(1);
                if (g_input_keys_raw.MaskActive(0x40)) entry_cursor.Advance(-1);
                if (g_input_keys_raw.pressed & 0x1001) {
                    g_player->SuspendAndStop();
                    g_player->Reset();
                    g_bullet_manager->Suspend();
                    g_bullet_manager->Reset();
                    g_enemy_ctrl->SuspendTasks();
                    g_enemy_ctrl->Clear();
                    g_front->Reset();
                    g_item_manager->Suspend();
                    memset(g_item_manager->slots, 0, sizeof(g_item_manager->slots));
                    EclViewSpawn spawn;
                    memset(&spawn, 0, sizeof(spawn));
                    spawn.x = 0.0f;
                    spawn.y = 0.0f;
                    spawn.z = 0.0f;
                    spawn.life = 10000;
                    spawn.Create(g_enemy_ctrl, g_enemy_ctrl->parser->entries[entry_cursor.selection].name);
                    state = 4;
                }
            }
            break;
        case 0:
            EclView_Remember(&file_cursor);
            if (g_input_keys_raw.Active(0x80)) file_cursor.Advance(1);
            if (g_input_keys_raw.Active(0x40)) file_cursor.Advance(-1);
            if (g_input_keys_raw.repeated & 0x1001) {
                EclView_Release(g_front);
                EclView_Release(g_player);
                EclView_Release(g_bullet_manager);
                EclView_Release(g_bomb);
                EclView_Release(g_item_manager);
                EclView_Release(g_smoll_score);
                EclView_Release(g_enemy_ctrl);
                flags &= ~2u;
                reinterpret_cast<PlatformWorker*>(&worker)->Start(this, EclView_LoadThread_0040a340);
                state = 2;
            }
            break;
        }
        break;
    case 0: {
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
        EclView_Select(menu, 0);
        file_cursor.item_count = count;
        file_cursor.wrap = 1;
        EclView_Select(file_cursor, 0);
        entry_cursor.item_count = 1;
        entry_cursor.wrap = 1;
        EclView_Select(entry_cursor, 0);
        state = 1;
        position_x = 0.0f;
        position_y = 32.0f;
        position_z = 0.0f;
        field_680 = 1000;
        break;
    }
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$b2task")
int __fastcall EclView_UpdateTask_0040abe0(EclView* viewer) {
    return viewer->Update();
}
#pragma code_seg()
