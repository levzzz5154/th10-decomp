#pragma once

#include "th10/util/heap.hpp"

// Only this owning view introduces construction/destruction; LegacyString
// remains a storage view for existing callers. The destructor is the retail
// clear routine at 0x004381F0, with its ECX receiver preserved.
struct GdiFontFaceName : LegacyString {
    GdiFontFaceName() {
        capacity = 15;
        length = 0;
        storage.inline_data[0] = 0;
    }

    ~GdiFontFaceName();
};

// 0x004372A0 uses these fields for CreateFontA and the resulting GDI handle.
// The allocator cookie inside face remains uninitialized.
struct GdiFontState {
    void* handle;
    int width;
    int height;
    GdiFontFaceName face;
    int weight;

    __declspec(noinline) GdiFontState();
};

extern const char g_default_font_face_cp932[];

typedef char GdiFontFaceNameSizeCheck[sizeof(GdiFontFaceName) == 0x1c ? 1 : -1];
typedef char GdiFontStateSizeCheck[sizeof(GdiFontState) == 0x2c ? 1 : -1];
