#include "th10/platform/font_cache_init.hpp"
#include "th10/render/queued_anm_cleanup.hpp"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {
std::vector<int> g_formats, g_heights;
bool g_first_surface;
bool CreateSurface(int width, int height, int format) {
	assert(width == 0x400 && height == 0x40);
	g_formats.push_back(format);
	if (format == 0x1A) return g_first_surface;
	return true;
}
void* CreateFont(int height, int weight, unsigned char charset,
                 unsigned quality, unsigned pitch_family, const char* face) {
	assert(weight == 400 && charset == 0x80 && quality == 4 && pitch_family == 0x11);
	assert(std::strcmp(face, "font-face") == 0);
	g_heights.push_back(height);
	return (void*)(long)height;
}

void TestFontCacheInitialize() {
	unsigned char pixels[256] = {};
	void* fonts[15] = {};
	FontCacheRngState rng = {0x1234, 7};
	FontCacheInitEnv env = {CreateSurface, CreateFont, pixels, fonts, &rng,
	                          "font-face"};
	g_formats.clear(); g_heights.clear(); g_first_surface = false;
	FontCache_Initialize(&env);
	assert(g_formats.size() == 2 && g_formats[0] == 0x1A && g_formats[1] == 0x15);
	assert(rng.generations == 263);
	assert(g_heights.size() == 15);
	for (int i = 0; i < 15; ++i) {
		assert(g_heights[i] == 0x20 + i * 2);
		assert(fonts[i] == (void*)(long)(0x20 + i * 2));
	}
	// Deterministic first byte from the recovered 16-bit step.
	unsigned short value = (unsigned short)((0x1234u ^ 0x9630u) + 0x9AADu);
	short next = (short)((value >> 14) + value * 4);
	assert(pixels[0] == (unsigned char)((unsigned short)next >> 9));

	g_formats.clear(); g_heights.clear(); g_first_surface = true;
	FontCache_Initialize(&env);
	assert(g_formats.size() == 1 && g_formats[0] == 0x1A);
}

QueuedAnimationNode g_nodes[3];
QueuedAnimationNode* Resolve(int handle) {
	if (handle <= 0 || handle > 3) return 0;
	return &g_nodes[handle - 1];
}
void TestQueuedAnimationsCleanup() {
	std::memset(g_nodes, 0, sizeof(g_nodes));
	QueuedAnimationNode child_a = {}, child_b = {};
	QueuedAnimationLink link_b = {&child_b, 0};
	QueuedAnimationLink link_a = {&child_a, &link_b};
	g_nodes[0].children = &link_a;
	g_nodes[1].parent_marker = 1; // root stops, but its child list is skipped
	QueuedAnimationNode skipped_child = {};
	QueuedAnimationLink skipped_link = {&skipped_child, 0};
	g_nodes[1].children = &skipped_link;
	QueuedAnimations state = {1, {1, 2, 3}, 9};
	QueuedAnimationCleanupEnv env = {Resolve};
	QueuedAnimations_Cleanup(&state, &env);
	assert(state.cleanup_requested == 0 && state.shared_latch == 0);
	assert(state.handles[0] == 0 && state.handles[1] == 0 && state.handles[2] == 0);
	for (int i = 0; i < 3; ++i) assert(g_nodes[i].stop_frame == 1);
	assert(child_a.stop_frame == 1 && child_b.stop_frame == 1);
	assert(skipped_child.stop_frame == 0);

	state.cleanup_requested = 0;
	state.shared_latch = 1;
	g_nodes[0].stop_frame = 0;
	QueuedAnimations_Cleanup(&state, &env);
	assert(g_nodes[0].stop_frame == 0 && state.shared_latch == 0);
}
} // namespace

int main() {
	TestFontCacheInitialize();
	TestQueuedAnimationsCleanup();
	std::puts("BATCH16_TESTS_PASS");
	return 0;
}
