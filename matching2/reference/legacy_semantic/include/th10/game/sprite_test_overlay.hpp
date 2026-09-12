#pragma once

// Sprite-test debug overlay draw states (retail 0x0042C360, 0x0040A940).
// --- 0x0042C360 -------------------------------------------------------------
struct SpriteTestOverlay {
	int state;
	const char* file_name;
	const char* ecl_name;
	float position_x;
	float position_y;
};
struct SpriteTestOverlayEnv {
	unsigned int* text_color;
	void (*print)(const char* format, const char* text, int x, int y);
};
int DebugOverlay_Draw(const SpriteTestOverlay* overlay,
                      SpriteTestOverlayEnv* env);

// Retail function 0x0040A940.
struct SpriteViewPoint{float x,y,z;};struct SpriteView{int mode;const char*const*files;int file_index,file_present,selection,ecl_index;float position[2];unsigned flags;SpriteViewPoint gizmo_position;};struct SpriteViewEnv{unsigned*text_color;const char*(*resolve_ecl_name)(int);int(*current_enemy_index)();void(*draw_text)(const SpriteViewPoint*,const char*);void(*draw_gizmo)(SpriteView*);};int SpriteView_DrawDebugOverlay(SpriteView*,const SpriteViewEnv*);
