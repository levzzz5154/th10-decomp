#include "th10/game/sprite_test_overlay.hpp"
#include "th10/render/quad_build_anchored.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {
struct PrintCall { std::string format; std::string text; int x, y; };
std::vector<PrintCall> g_prints;
void Print(const char* format, const char* text, int x, int y) {
	g_prints.push_back({format, text ? text : "", x, y});
}
void TestDebugOverlayDraw() {
	unsigned color = 0;
	SpriteTestOverlayEnv env = {&color, Print};
	SpriteTestOverlay overlay = {1, 0, "stage.ecl", 0, 0};
	g_prints.clear();
	assert(DebugOverlay_Draw(&overlay, &env) == 1);
	assert(g_prints.size() == 5);
	assert(g_prints[1].format == "File not found.");
	assert(g_prints[2].format == "Ecl %s" && g_prints[2].text == "stage.ecl");
	assert(color == 0xFFFFFFFFu);

	overlay.state = 2; overlay.file_name = "test.spt";
	g_prints.clear(); color = 0;
	DebugOverlay_Draw(&overlay, &env);
	assert(g_prints.size() == 2 && g_prints[1].format == "Loading %s");
	assert(color == 0xFFFFFFFFu);

	overlay.state = 3; overlay.position_x = 12.9f; overlay.position_y = -4.2f;
	g_prints.clear(); color = 0;
	DebugOverlay_Draw(&overlay, &env);
	assert(g_prints[1].format == "Pos %.3d %.3d");
	assert(g_prints[1].x == 12 && g_prints[1].y == -4);
	assert(color == 0xFFFFFFFFu);
}

AnchoredQuadVertex g_vertices[4];
int g_mode;
float RoundEdge(float edge, float) { return (float)(int)(edge + 0.5f); }
void Render(const AnchoredQuadVertex vertices[4], int mode) {
	std::memcpy(g_vertices, vertices, sizeof(g_vertices)); g_mode = mode;
}
void TestQuadBuildAndRenderAnchored() {
	AnchoredQuadEnv env = {RoundEdge, Render};
	AnchoredQuadSource source = {};
	source.base_x = 10; source.layer_x = 2; source.offset_x = 1;
	source.base_y = 20; source.layer_y = -2; source.offset_y = 1;
	source.base_z = 3; source.layer_z = 4; source.offset_z = 5;
	source.scale_x = 2; source.scale_y = 0.5f;
	source.width = 4; source.height = 8;
	source.anchor_x = 1; source.anchor_y = 2;
	Quad_BuildAndRenderAnchored(&source, &env);
	assert(g_mode == 1);
	assert(g_vertices[0].x == 13 && g_vertices[1].x == 21);
	assert(g_vertices[0].y == 15 && g_vertices[2].y == 19);
	for (int i = 0; i < 4; ++i) {
		assert(g_vertices[i].z == 12 && g_vertices[i].w == 1);
	}

	source.anchor_x = 0; source.anchor_y = 0;
	Quad_BuildAndRenderAnchored(&source, &env);
	assert(g_vertices[0].x == 9 && g_vertices[1].x == 17);
	assert(g_vertices[0].y == 17 && g_vertices[2].y == 21);
}
} // namespace

int main() {
	TestDebugOverlayDraw();
	TestQuadBuildAndRenderAnchored();
	std::puts("BATCH17_TESTS_PASS");
	return 0;
}
