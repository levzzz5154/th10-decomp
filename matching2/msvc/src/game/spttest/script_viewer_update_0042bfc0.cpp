// 0x0042BFC0: run the "Spt Test" debug screen. State 0 lists the script
// files and resets the three menus, state 1 is the menu (load a file on the
// loader thread, run an entry of the loaded script, or quit), state 4 steps
// the running entry until it ends.
// 0x0042C580: the scheduler callback, a tail jump with the screen in ECX.
#include "th10/game/script_viewer_update_0042bfc0.hpp"

#pragma code_seg(".text$b1update")
int ScriptViewer_0042be20::Update() {
    ScriptViewerFindData_0042bfc0 find;
    switch (state) {
    case 4:
        ScriptViewer_TickVm_0044fd10(resource, 1.0f);
        if (resource && resource->active->running) break;
        if (resource) resource->Retire(1);
        resource = 0;
        state = 1;
        break;
    case 1:
        ScriptViewer_Remember(&menu);
        if (data_00474e30.Active(0x20)) menu.Advance(1);
        if (data_00474e30.Active(0x10)) menu.Advance(-1);
        switch (menu.selection) {
        case 2:
            if (data_00474e30.repeated & 0x1001)
                ScriptViewer_SetGameMode_0040ac90(&data_00491c28, 3);
            break;
        case 1:
            if (parser) {
                ScriptViewer_Remember(&entry_cursor);
                if (data_00474e30.MaskActive(0x80)) entry_cursor.Advance(1);
                if (data_00474e30.MaskActive(0x40)) entry_cursor.Advance(-1);
                if (data_00474e30.pressed & 0x1001) {
                    if (resource) {
                        resource->Retire(1);
                        resource = 0;
                    }
                    const char* name = parser->entries[entry_cursor.selection].name;
                    resource = parser->CreateVm(name);
                    state = 4;
                }
            }
            break;
        case 0:
            ScriptViewer_Remember(&file_cursor);
            if (data_00474e30.Active(0x80)) file_cursor.Advance(1);
            if (data_00474e30.Active(0x40)) file_cursor.Advance(-1);
            if (data_00474e30.repeated & 0x1001) {
                flags &= ~2u;
                reinterpret_cast<PlatformWorker*>(&worker)->Start(this, ScriptViewer_LoadThread_0042be10);
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
        ScriptViewer_Select(menu, 0);
        file_cursor.item_count = count;
        file_cursor.wrap = 1;
        ScriptViewer_Select(file_cursor, 0);
        entry_cursor.item_count = 1;
        entry_cursor.wrap = 1;
        ScriptViewer_Select(entry_cursor, 0);
        state = 1;
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
int __fastcall ScriptViewer_UpdateTask_0042c580(ScriptViewer_0042be20* viewer) {
    return viewer->Update();
}
#pragma code_seg()
