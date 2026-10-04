#pragma once

#include "th10/util/heap.hpp"

// The face name is a standard string. Destroying it frees a heap buffer and
// puts the string back into its empty inline state; where the object is going
// away the compiler keeps only the free. The out-of-line copy is 0x004381F0.
struct GdiFontFaceName : LegacyString {
    GdiFontFaceName() {
        capacity = 15;
        length = 0;
        storage.inline_data[0] = 0;
    }

    ~GdiFontFaceName() {
        if (capacity >= 16)
            operator delete(storage.heap_data);
        capacity = 15;
        length = 0;
        storage.inline_data[0] = 0;
    }

    const char* c_str() const {
        return capacity >= 16 ? storage.heap_data : storage.inline_data;
    }
};

extern "C" {
__declspec(dllimport) int __stdcall DeleteObject(void* object);
__declspec(dllimport) void* __stdcall CreateFontA(
    int height, int width, int escapement, int orientation, int weight,
    unsigned long italic, unsigned long underline, unsigned long strike_out,
    unsigned long char_set, unsigned long out_precision, unsigned long clip_precision,
    unsigned long quality, unsigned long pitch_and_family, const char* face);
}

// A GDI font description and the font made from it. The allocator cookie
// inside face remains uninitialized.
struct GdiFontState {
    void* handle;
    int width;
    int height;
    GdiFontFaceName face;
    int weight;

    // Bold 16-pixel "ＭＳ ゴシック"; nothing is created yet.
    GdiFontState();

    ~GdiFontState() {
        Release();
    }

    void Release() {
        if (handle) {
            DeleteObject(handle);
            handle = 0;
        }
    }

    void SetSize(int new_width, int new_height) {
        width = new_width;
        height = new_height;
    }

    // Replaces the font with one built from the current description.
    void Create() {
        Release();
        handle = CreateFontA(height, width, 0, 0, weight, 0, 0, 0,
                             1 /* DEFAULT_CHARSET */, 0, 0, 0,
                             0x30 /* FF_MODERN */, face.c_str());
    }
};

extern const char g_default_font_face_cp932[];

typedef char GdiFontFaceNameSizeCheck[sizeof(GdiFontFaceName) == 0x1c ? 1 : -1];
typedef char GdiFontStateSizeCheck[sizeof(GdiFontState) == 0x2c ? 1 : -1];
