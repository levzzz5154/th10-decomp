#include "th10/game/sprite_test_overlay.hpp"

#include <cstdio>

namespace {

const unsigned int kWhite = 0xffffffffu;
const unsigned int kLoadingColor = 0xffff4040u;
const unsigned int kPositionColor = 0xffa0a0a0u;
const unsigned int kDrawGizmo = 2;

void DrawText(const SpriteViewEnv* env, SpriteViewPoint point,
              const char* text) {
    env->draw_text(&point, text);
}

}  // namespace

// 0x0042C360 - draws the sprite-test debug overlay for idle, loading, and
// position-inspection states, preserving the retail color changes and reset.
int DebugOverlay_Draw(const SpriteTestOverlay* overlay,
                      SpriteTestOverlayEnv* env) {
	env->print("Spt Test\n", 0, 0, 0);
	if (overlay->state == 1) {
		env->print(overlay->file_name == 0 ? "File not found." : "File %s",
		           overlay->file_name, 0, 0);
		env->print(overlay->ecl_name == 0 ? "Ecl not load" : "Ecl %s",
		           overlay->ecl_name, 0, 0);
		env->print("Quit", 0, 0, 0);
		env->print(">", 0, 0, 0);
		*env->text_color = 0xFFFFFFFFu;
	} else if (overlay->state == 2) {
		*env->text_color = 0xFFFF4040u;
		env->print("Loading %s", overlay->file_name, 0, 0);
		*env->text_color = 0xFFFFFFFFu;
	} else if (overlay->state == 3) {
		*env->text_color = 0xFFA0A0A0u;
		env->print("Pos %.3d %.3d", 0, (int)overlay->position_x,
		           (int)overlay->position_y);
		*env->text_color = 0xFFFFFFFFu;
	}
	return 1;
}

// 0x0040A940 - Draw the sprite-test overlay for selection, loading, position,
// and enemy-inspection modes, then draw the optional centered gizmo.
int SpriteView_DrawDebugOverlay(SpriteView* view,
                                const SpriteViewEnv* env) {
    char buffer[160];
    DrawText(env, SpriteViewPoint{0.0f, 0.0f, 0.0f}, "SprtView\n");

    switch (view->mode) {
    case 1: {
        if (view->file_present) {
            std::snprintf(buffer, sizeof(buffer), "File %s",
                          view->files[view->file_index]);
            DrawText(env, SpriteViewPoint{42.0f, 16.0f, 0.0f}, buffer);
        } else {
            DrawText(env, SpriteViewPoint{42.0f, 16.0f, 0.0f},
                     "File not found.");
        }

        const char* ecl_name = env->resolve_ecl_name(view->ecl_index);
        if (ecl_name != 0) {
            std::snprintf(buffer, sizeof(buffer), "Ecl %s", ecl_name);
        } else {
            std::snprintf(buffer, sizeof(buffer), "Ecl %d",
                          view->ecl_index);
        }
        DrawText(env, SpriteViewPoint{42.0f, 26.0f, 0.0f}, buffer);
        DrawText(env, SpriteViewPoint{42.0f, 36.0f, 0.0f}, "Quit");
        DrawText(env,
                 SpriteViewPoint{32.0f,
                              16.0f + 10.0f * view->selection, 0.0f},
                 ">");
        *env->text_color = kWhite;
        break;
    }

    case 2:
        *env->text_color = kLoadingColor;
        std::snprintf(buffer, sizeof(buffer), "Loading %s",
                      view->files[view->file_index]);
        DrawText(env, SpriteViewPoint{32.0f, 16.0f, 0.0f}, buffer);
        *env->text_color = kWhite;
        return 1;

    case 3:
        *env->text_color = kPositionColor;
        std::snprintf(buffer, sizeof(buffer), "Pos %.3d %.3d",
                      static_cast<int>(view->position[0]),
                      static_cast<int>(view->position[1]));
        DrawText(env, SpriteViewPoint{32.0f, 16.0f, 0.0f}, buffer);
        *env->text_color = kWhite;
        break;

    case 4:
        std::snprintf(buffer, sizeof(buffer), "Enemy %d",
                      env->current_enemy_index());
        DrawText(env, SpriteViewPoint{500.0f, 240.0f, 0.0f}, buffer);
        return 1;

    default:
        return 1;
    }

    if (view->flags & kDrawGizmo) {
        view->gizmo_position = SpriteViewPoint{320.0f, 240.0f, 0.0f};
        env->draw_gizmo(view);
    }
    return 1;
}
