// 0x0040A940: draw the "SprtView" debug screen's text for its current state
// and, while a sprite is shown, the sprite itself at the screen centre.
// Native LTCG keeps the viewer in EDI and passes the game thread in ESI and
// the text position in EBX to the marked-text writer.
// 0x0040ABF0: the scheduler callback, which forwards its ECX context.
#include "th10/game/sprite_viewer_draw_0040a940.hpp"

#pragma code_seg(".text$05draw")
int SpriteViewer_0040a940::Draw() {
    Vec3_00401530 position = {0.0f, 0.0f, 0.0f};
    AppendMarked_00401690(data_004776e0, &position, "SprtView\n");
    switch (state) {
    case 2:
        data_004776e0->current_4c = 0xFFFF4040;
        position.x = 32.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        AppendMarked_00401690(data_004776e0, &position, "Loading %s", script_names[script_index]);
        data_004776e0->current_4c = 0xFFFFFFFF;
        return 1;
    case 1:
        position.x = 42.0f;
        position.y = 16.0f;
        position.z = 0.0f;
        if (script_count)
            AppendMarked_00401690(data_004776e0, &position, "File %s", script_names[script_index]);
        else
            AppendMarked_00401690(data_004776e0, &position, "File not found.");
        position.y = 26.0f;
        if (data_00477704)
            AppendMarked_00401690(data_004776e0, &position, "Ecl %s", data_00477704->parser->entries[selection].name);
        else
            AppendMarked_00401690(data_004776e0, &position, "Ecl %d", selection);
        position.y = 36.0f;
        AppendMarked_00401690(data_004776e0, &position, "Quit");
        position.x = 32.0f;
        position.y = menu_row * 10.0f + 16.0f;
        AppendMarked_00401690(data_004776e0, &position, ">");
        data_004776e0->current_4c = 0xFFFFFFFF;
        break;
    case 4: {
        position.x = 500.0f;
        position.y = 240.0f;
        position.z = 0.0f;
        AppendMarked_00401690(data_004776e0, &position, "Enemy %d", data_00477704->enemy_count);
        return 1;
    }
    case 3: {
        data_004776e0->current_4c = 0xFFA0A0A0;
        Vec3_00401530 status_position = {32.0f, 16.0f, 0.0f};
        AppendMarked_00401690(data_004776e0, &status_position, "Pos %.3d %.3d", int(position_x), int(position_y));
        data_004776e0->current_4c = 0xFFFFFFFF;
        break;
    }
    default:
        return 1;
    }
    if (flags & 2) {
        sprite.base_position = CameraVector(320.0f, 240.0f, 0.0f);
        SpriteViewer_DrawEntity_00443080(data_00491c10, &sprite);
    }
    return 1;
}
#pragma code_seg()

#pragma code_seg(".text$06task")
int __fastcall SpriteViewer_DrawTask_0040abf0(SpriteViewer_0040a940* viewer) {
    return viewer->Draw();
}
#pragma code_seg()
