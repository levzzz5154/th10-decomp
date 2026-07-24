#include "th10/game/score_cleanup.hpp"
#include "th10/render/image_alpha_transform.hpp"
#include "th10/render/transparent_pixel_fill.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>

static int g_cleaned;
static void Cleanup(ScoreCleanupNode* node) {
    ++g_cleaned;
    node->next = 0; // iteration must have cached the successor
}

static void TestScoreCleanup() {
    ScoreCleanupNode third = {0, 0, 0, 0};
    ScoreCleanupNode second = {0, 0, &third, 1};
    ScoreCleanupNode first = {0, 0, &second, 0};
    ScoreCleanupList list = {&first};
    g_cleaned = 0;
    assert(ScoreCleanup_Dispatch(&list, Cleanup) == 1);
    assert(g_cleaned == 2);
}

static void TestAlphaTransforms() {
    unsigned char bgra[8] = {1,2,3,0x00, 4,5,6,0xff};
    TransparentPixelSurface s32 = {0x15, 2, 1, 8, bgra};
    assert(Image_InvertAlpha(&s32, 1) == 1);
    assert(bgra[3] == 0xff && bgra[7] == 0x00);

    std::uint16_t a1[2] = {0x1234, 0x9234};
    TransparentPixelSurface s1555 = {0x19, 2, 1, 4, a1};
    Image_InvertAlpha(&s1555, 1);
    assert(a1[0] == 0x9234); // transparent becomes opaque, color retained
    assert(a1[1] == 0x0000); // opaque becomes transparent black

    std::uint16_t a4[2] = {0x0123, 0xf456};
    TransparentPixelSurface s4444 = {0x1a, 2, 1, 4, a4};
    Image_InvertAlpha(&s4444, 1);
    assert(a4[0] == 0xf123 && a4[1] == 0x0456);

    TransparentPixelSurface unsupported = {7, 0, 0, 0, bgra};
    assert(Image_InvertAlpha(&unsupported, 0) == 0);
}

static void TestLockedSurfaceColorFill() {
    unsigned char bgra[12] = {
        20,40,60,255, 0,0,0,0, 40,60,80,255
    };
    TransparentPixelSurface s32 = {0x15, 3, 1, 12, bgra};
    assert(Image_FillTransparentColors(&s32) == 1);
    assert(bgra[4] == 30 && bgra[5] == 50 && bgra[6] == 70);
    assert(bgra[7] == 0);

    std::uint16_t a1555[3] = {0xfc00, 0x0000, 0x801f};
    TransparentPixelSurface s1555 = {0x19, 3, 1, 6, a1555};
    Image_FillTransparentColors(&s1555);
    // Average (31,0,0) and (0,0,31) => (15,0,15), alpha stays zero.
    assert(a1555[1] == 0x3c0f);

    std::uint16_t a4444[3] = {0xfa00, 0x0000, 0xf00a};
    TransparentPixelSurface s4444 = {0x1a, 3, 1, 6, a4444};
    Image_FillTransparentColors(&s4444);
    // Unlike 0x00436DA0, this locked-surface path does not halve color.
    assert(a4444[1] == 0x0505);
}

int main() {
    TestScoreCleanup();
    TestAlphaTransforms();
    TestLockedSurfaceColorFill();
    return 0;
}
