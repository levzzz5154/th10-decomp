#include "th10/platform/font_texture_draw.hpp"
#include "th10/render/special_quad.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {

struct Draw { int x, y, length; unsigned color; };
std::vector<Draw> g_draws;
std::vector<int> g_rows;
unsigned g_color;
int g_prepare;
void* g_selected;
int g_restores, g_repairs, g_acquires, g_uploads, g_releases;

void Prepare(unsigned color) { ++g_prepare; g_color = color; }
void* Select(void* font) { g_selected = font; return (void*)0x777; }
void Background() {}
void SetColor(unsigned color) { g_color = color; }
void DrawText(int x, int y, const char*, int length) {
	g_draws.push_back({x, y, length, g_color});
}
void Restore(void* font) { assert(font == (void*)0x777); ++g_restores; }
void Invert(int rows) { g_rows.push_back(rows); }
void Repair(int rows) { assert(rows == g_rows.back()); ++g_repairs; }
void* Acquire(void* texture) { assert(texture == (void*)0x123); ++g_acquires; return (void*)0x456; }
void Upload(void* surface, void* texture, const unsigned char*, int rows) {
	assert(surface == (void*)0x456 && texture == (void*)0x123);
	assert(rows == g_rows.back());
	++g_uploads;
}
void Release(void* surface) { assert(surface == (void*)0x456); ++g_releases; }

FontTextureUploadEnv MakeEnv(unsigned char* bitmap, std::size_t size) {
	FontTextureUploadEnv env;
	std::memset(&env, 0, sizeof(env));
	for (int i = 0; i < 15; ++i) env.fonts[i] = (void*)(long)(i + 1);
	env.bitmap = bitmap;
	env.bitmap_size = size;
	env.prepare_color = Prepare;
	env.select_font = Select;
	env.set_transparent_background = Background;
	env.set_text_color = SetColor;
	env.draw_text = DrawText;
	env.restore_font = Restore;
	env.invert_alpha = Invert;
	env.repair_transparent_pixels = Repair;
	env.acquire_surface = Acquire;
	env.upload_bitmap = Upload;
	env.release_surface = Release;
	return env;
}

void Reset() {
	g_draws.clear(); g_rows.clear(); g_prepare = g_restores = g_repairs = 0;
	g_acquires = g_uploads = g_releases = 0; g_selected = 0; g_color = 0;
}

void TestShadowed() {
	unsigned char bitmap[16];
	std::memset(bitmap, 0xAB, sizeof(bitmap));
	FontTextureUploadEnv env = MakeEnv(bitmap, sizeof(bitmap));
	Reset();
	FontTexture_DrawShadowed((void*)0x123, 4, 10, 0x112233, "abc", &env);
	for (unsigned char value : bitmap) assert(value == 0);
	assert(g_selected == (void*)1); // size clamps to 17
	assert(g_prepare == 0 && g_draws.size() == 2);
	assert(g_draws[0].x == 10 && g_draws[0].y == 2 && g_draws[0].color == 0);
	assert(g_draws[1].x == 8 && g_draws[1].y == 0 && g_draws[1].color == 0x112233);
	assert(g_draws[0].length == 3 && g_rows.size() == 2);
	assert(g_rows[0] == 40 && g_rows[1] == 40);
	assert(g_restores == 2 && g_repairs == 1);
	assert(g_acquires == 1 && g_uploads == 1 && g_releases == 1);
}

void TestPlain() {
	unsigned char bitmap[4] = {1, 2, 3, 4};
	FontTextureUploadEnv env = MakeEnv(bitmap, sizeof(bitmap));
	Reset();
	FontTexture_DrawPlain((void*)0x123, 2, 99, 0xABCDEF, "xy", &env);
	assert(bitmap[0] == 1); // plain path does not clear the shared DIB
	assert(g_selected == (void*)15); // size clamps to 31
	assert(g_prepare == 1 && g_draws.size() == 1);
	assert(g_draws[0].x == 4 && g_draws[0].y == 0);
	assert(g_draws[0].color == 0xABCDEF && g_draws[0].length == 2);
	assert(g_rows[0] == 68 && g_rows[1] == 68);
}

int g_special_draws;
void SpecialDraw() { ++g_special_draws; }
void TestSpecialCallback() {
	g_special_draws = 0;
	assert(Renderer_RunSpecialQuadCallback(SpecialDraw) == 1);
	assert(g_special_draws == 1);
}

} // namespace

int main() {
	TestShadowed();
	TestPlain();
	TestSpecialCallback();
	std::puts("BATCH15_TESTS_PASS");
	return 0;
}
