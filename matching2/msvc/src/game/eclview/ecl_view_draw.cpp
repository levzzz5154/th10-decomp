// 0x0040A940: draw the "SprtView" debug screen's text for its current state
// and, while a sprite is shown, the sprite itself at the screen centre.
// Native LTCG keeps the viewer in EDI and passes the game thread in ESI and
// the text position in EBX to the marked-text writer.
// 0x0040ABF0: the scheduler callback, which forwards its ECX context.
#include "th10/game/ecl_view_draw.hpp"

#pragma code_seg(".text$05draw")
int EclView::Draw() {
    Vec32 position = {0.0f, 0.0f, 0.0f};
    AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "SprtView\n");
    switch (state) {
    case 2:
        g_ascii_manager->current_4c = 0xFFFF4040;
        position.x = 32.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Loading %s", script_names[file_cursor.selection]);
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        return 1;
    case 1:
        position.x = 42.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        if (script_count)
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "File %s", script_names[file_cursor.selection]);
        else
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "File not found.");
        position.y = 26.0f;
        if (g_enemy_ctrl)
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Ecl %s", g_enemy_ctrl->parser->entries[entry_cursor.selection].name);
        else
            AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Ecl %d", entry_cursor.selection);
        position.y = 36.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Quit");
        position.x = 32.0f;
        position.y = menu.selection * 10.0f + 16.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, ">");
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        break;
    case 4: {
        position.x = 500.0f;
        position.y = 240.0f;
        position.z = 0.0f;
        AsciiManager_AddFormattedMarked(g_ascii_manager, &position, "Enemy %d", g_enemy_ctrl->enemy_count);
        return 1;
    }
    case 3: {
        g_ascii_manager->current_4c = 0xFFA0A0A0;
        Vec32 status_position = {32.0f, 16.0f, 0.0f};
        AsciiManager_AddFormattedMarked(g_ascii_manager, &status_position, "Pos %.3d %.3d", int(position_x), int(position_y));
        g_ascii_manager->current_4c = 0xFFFFFFFF;
        break;
    }
    default:
        return 1;
    }
    if (flags & 2) {
        sprite.base_position = CameraVector(320.0f, 240.0f, 0.0f);
        EclView_DrawEntity(g_sprt_ctrl, &sprite);
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$06task")
int __fastcall EclView_DrawTask2(EclView* viewer) {
    return viewer->Draw();
}
#pragma code_seg()
