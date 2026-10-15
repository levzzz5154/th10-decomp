// 0x0042C360: draw the "Spt Test" debug screen's text for its current state.
// Native LTCG keeps the viewer in EDI and passes the game thread in ESI and
// the text position in EBX to the marked-text writer.
// 0x0042C590: the scheduler callback, which forwards its ECX context.
#include "th10/game/script_viewer_load_0042be20.hpp"
#include "th10/game/game_thread_queue_native.hpp"

extern "C" GameThread_00401530* g_ascii_manager;

#pragma code_seg(".text$05draw")
int ScriptViewer_0042be20::Draw() {
    Vec3_00401530 position = {0.0f, 0.0f, 0.0f};
    AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Spt Test\n");
    switch (state) {
    case 1:
        position.x = 42.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        if (script_count)
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "File %s", script_names[file_cursor.selection]);
        else
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "File not found.");
        position.y = 26.0f;
        if (parser)
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Ecl %s", parser->entries[entry_cursor.selection].name);
        else
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Ecl not load");
        position.y = 36.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Quit");
        position.x = 32.0f;
        position.y = menu.selection * 10.0f + 16.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, ">");
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        break;
    case 2:
        g_ascii_manager->current_4c = 0xFFFF4040;
        position.x = 32.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Loading %s", script_names[file_cursor.selection]);
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        break;
    case 3: {
        g_ascii_manager->current_4c = 0xFFA0A0A0;
        Vec3_00401530 status_position = {32.0f, 16.0f, 0.0f};
        AsciiManager_AddFormattedMarked(g_ascii_manager, &status_position, "Pos %.3d %.3d", int(position_x), int(position_y));
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        break;
    }
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$06task")
int __fastcall ScriptViewer_DrawTask_0042c590(ScriptViewer_0042be20* viewer) {
    return viewer->Draw();
}
#pragma code_seg()
