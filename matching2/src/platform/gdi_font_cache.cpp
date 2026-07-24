#include "th10/platform/gdi_font_cache.hpp"

// GDI font/bitmap handle table (retail 0x00491868..0x004918A0).
void* DAT_00491868[15];

// 0x00437D10 - Delete the fifteen cached GDI objects. Retail flushes
// the font cache first (0x00436A30) and then calls DeleteObject on each
// handle starting from the highest slot (0x004918A0) down to the lowest
// (0x00491868), leaving the slots untouched.
void FontCache_DeleteGdiObjects(void (*flush)(),
                                void (*delete_object)(void*)) {
    if (flush != 0) {
        flush();
    }
    if (delete_object == 0) {
        return;
    }
    for (int slot = 14; slot >= 0; --slot) {
        delete_object(DAT_00491868[slot]);
    }
}
