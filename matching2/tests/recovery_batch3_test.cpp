#include "th10/game/asset_buffer.hpp"
#include "th10/render/transparent_pixel_fill.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>

static const char* g_loaded_path;
static int g_load_flags;
static int g_free_calls;
static unsigned char g_replacement[4];

static unsigned char* Load(const char* path, int flags) {
    static char captured[64];
    std::strcpy(captured, path);
    g_loaded_path = captured;
    g_load_flags = flags;
    return g_replacement;
}

static void Free(void*) { ++g_free_calls; }

static void TestAssetReplacement() {
    unsigned char old_data[1] = {0};
    AssetBufferSlot slot = {old_data};
    char path[64] = "data/";
    g_free_calls = 0;
    assert(AssetBuffer_ReplaceFromPath(
               &slot, path, "bullet.anm", Load, Free) == g_replacement);
    assert(std::strcmp(path, "data/bullet.anm") == 0);
    assert(std::strcmp(g_loaded_path, path) == 0);
    assert(g_load_flags == 0 && g_free_calls == 1);
    assert(slot.data == g_replacement);
}

static void TestBgraFill() {
    // Transparent center averages opaque left and right. Transparent corners
    // have no source on their first visit and remain black.
    unsigned char pixels[12] = {
        10, 20, 30, 255,
        0, 0, 0, 0,
        30, 40, 50, 255,
    };
    TransparentPixelSurface surface = {0x15, 3, 1, 12, pixels};
    assert(Image_FillTransparentPixels(&surface, 1) == 1);
    assert(pixels[4] == 20 && pixels[5] == 30 && pixels[6] == 40);
    assert(pixels[7] == 0);
}

static void TestBgraVerticalAndRowLimit() {
    unsigned char pixels[8] = {
        80, 60, 40, 255,
        0, 0, 0, 0,
    };
    TransparentPixelSurface surface = {0x15, 1, 2, 4, pixels};
    Image_FillTransparentPixels(&surface, 1);
    assert(pixels[4] == 0); // second row was not scanned
    Image_FillTransparentPixels(&surface, 2);
    assert(pixels[4] == 80 && pixels[5] == 60 && pixels[6] == 40);
}

static void TestA4R4G4B4Fill() {
    std::uint16_t pixels[3] = {0xfca8, 0x0000, 0xf864};
    TransparentPixelSurface surface = {0x1a, 3, 1, 6, pixels};
    Image_FillTransparentPixels(&surface, 1);
    // Average RGB nibbles: (12,10,8) and (8,6,4) => (10,8,6),
    // then halve as in the retail 16-bit conversion path.
    assert(pixels[1] == 0x0543);
}

int main() {
    TestAssetReplacement();
    TestBgraFill();
    TestBgraVerticalAndRowLimit();
    TestA4R4G4B4Fill();
    return 0;
}
