// 0x0040A450: run the "SprtView" debug screen. State 0 lists the script files
// and resets the three menus, state 1 is the menu (reload the managers for a
// file on the loader thread, spawn an entry of the loaded script as an enemy,
// or quit), state 4 polls the keys itself and returns to the menu on key 8.
// 0x0040ABE0: the scheduler callback, which forwards its ECX context.
#include "th10/game/sprite_viewer_update_0040a450.hpp"

#pragma code_seg(".text$b1update")
int SpriteViewer_0040a940::Update() {
    SpriteViewerFindData_0040a450 find;
    switch (state) {
    case 4:
        data_00474e30.previous_keys = data_00474e30.held_keys;
        data_00474e30.held_keys = data_00474e30.raw;
        data_00474e30.Update();
        data_00474e30.new_press = data_00474e30.repeated;
        if (data_00474e30.new_press & 8) {
            data_00477834->Resume();
            data_00477834->Reset();
            data_004776f0->Resume();
            data_004776f0->Reset();
            data_00477704->Resume();
            data_00477704->Clear();
            data_00477818->Resume();
            memset(data_00477818->slots, 0, sizeof(data_00477818->slots));
            state = 1;
        }
        break;
    case 1:
        SpriteViewer_Remember(&menu);
        if (data_00474e30.Active(0x20)) menu.Advance(1);
        if (data_00474e30.Active(0x10)) menu.Advance(-1);
        switch (menu.selection) {
        case 2:
            if (data_00474e30.repeated & 0x1001)
                SpriteViewer_SetGameMode_0040ac90(&data_00491c28, 3);
            break;
        case 1:
            if (data_00477704) {
                SpriteViewer_Remember(&entry_cursor);
                if (data_00474e30.MaskActive(0x80)) entry_cursor.Advance(1);
                if (data_00474e30.MaskActive(0x40)) entry_cursor.Advance(-1);
                if (data_00474e30.pressed & 0x1001) {
                    data_00477834->SuspendAndStop();
                    data_00477834->Reset();
                    data_004776f0->Suspend();
                    data_004776f0->Reset();
                    data_00477704->SuspendTasks();
                    data_00477704->Clear();
                    data_0047770c->Reset();
                    data_00477818->Suspend();
                    memset(data_00477818->slots, 0, sizeof(data_00477818->slots));
                    SpriteViewerSpawn_0040a450 spawn;
                    memset(&spawn, 0, sizeof(spawn));
                    spawn.x = 0.0f;
                    spawn.y = 0.0f;
                    spawn.z = 0.0f;
                    spawn.life = 10000;
                    spawn.Create(data_00477704, data_00477704->parser->entries[entry_cursor.selection].name);
                    state = 4;
                }
            }
            break;
        case 0:
            SpriteViewer_Remember(&file_cursor);
            if (data_00474e30.Active(0x80)) file_cursor.Advance(1);
            if (data_00474e30.Active(0x40)) file_cursor.Advance(-1);
            if (data_00474e30.repeated & 0x1001) {
                SpriteViewer_Release(data_0047770c);
                SpriteViewer_Release(data_00477834);
                SpriteViewer_Release(data_004776f0);
                SpriteViewer_Release(data_004776ec);
                SpriteViewer_Release(data_00477818);
                SpriteViewer_Release(data_00477840);
                SpriteViewer_Release(data_00477704);
                flags &= ~2u;
                reinterpret_cast<PlatformWorker*>(&worker)->Start(this, SpriteViewer_LoadThread_0040a340);
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
        SpriteViewer_Select(menu, 0);
        file_cursor.item_count = count;
        file_cursor.wrap = 1;
        SpriteViewer_Select(file_cursor, 0);
        entry_cursor.item_count = 1;
        entry_cursor.wrap = 1;
        SpriteViewer_Select(entry_cursor, 0);
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
int __fastcall SpriteViewer_UpdateTask_0040abe0(SpriteViewer_0040a940* viewer) {
    return viewer->Update();
}
#pragma code_seg()
