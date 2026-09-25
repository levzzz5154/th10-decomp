#include "asm_symbols.hpp"
#include <string.h>

// 0x00437D10..0x00437DA4: semantic model of FontCache_DeleteGdiObjectsRetail.
// The retail call to 0x00436A30 first sets ESI to 0x00474CB0; that helper
// reads its cache receiver from this private register. Spell its observed
// effects against an explicit receiver here, since an ordinary C++ call
// would not preserve that private ABI edge.
//
// The retail body is 149 bytes. A previous stand-alone candidate matched
// 5/149 bytes and emitted 196 bytes. This readable rewrite has not been
// compared to retail bytes, so it is a behavioral reconstruction only.

namespace {

typedef void* GdiHandle;
typedef GdiHandle (__stdcall *SelectObjectProc)(GdiHandle device_context,
                                                GdiHandle object);
typedef int (__stdcall *DeleteDcProc)(GdiHandle device_context);
typedef int (__stdcall *DeleteObjectProc)(GdiHandle object);

struct FontCacheFlushReceiver {
    unsigned char unknown_000[0x100];
    unsigned int field_100;
    unsigned int field_104;
    unsigned int field_108;
    unsigned char unknown_10c[8];
    GdiHandle device_context;       // +0x114
    GdiHandle previous_bitmap;      // +0x118
    GdiHandle font_object;          // +0x11C
    unsigned int field_120;
};

template <typename Function>
Function load_import_slot(unsigned char& slot) {
    // These x86 data symbols name IAT slots, rather than the imported APIs.
    void* imported_address = 0;
    memcpy(&imported_address, &slot, sizeof(imported_address));
    return reinterpret_cast<Function>(imported_address);
}

void flush_font_cache_surface(FontCacheFlushReceiver& cache) {
    if (cache.device_context == 0) {
        return;
    }

    const SelectObjectProc select_object =
        load_import_slot<SelectObjectProc>(data_0046602c);
    select_object(cache.device_context, cache.previous_bitmap);

    const DeleteDcProc delete_dc =
        load_import_slot<DeleteDcProc>(data_00466028);
    delete_dc(cache.device_context);

    const DeleteObjectProc delete_object =
        load_import_slot<DeleteObjectProc>(data_00466030);
    delete_object(cache.font_object);

    cache.field_104 = 0;
    cache.field_108 = 0;
    cache.device_context = 0;
    cache.font_object = 0;
    cache.previous_bitmap = 0;
    cache.field_120 = 0;
    cache.field_100 = 0xFFFFFFFFu;
}

void delete_object_at_slot(DeleteObjectProc delete_object,
                           const unsigned char* slot) {
    GdiHandle object = 0;
    memcpy(&object, slot, sizeof(object));
    delete_object(object);
}

} // namespace

extern "C" void __cdecl asm_FontCache_DeleteGdiObjectsRetail_00437d10() {
    FontCacheFlushReceiver& font_cache =
        *reinterpret_cast<FontCacheFlushReceiver*>(0x00474cb0UL);
    flush_font_cache_surface(font_cache);

    const unsigned char* const handle_slots[15] = {
        &data_00491868, &data_0049186c, &data_00491870,
        &data_00491874, &data_00491878, &data_0049187c,
        &data_00491880, &data_00491884, &data_00491888,
        &data_0049188c, &data_00491890, &data_00491894,
        &data_00491898, &data_0049189c, &data_004918a0,
    };
    const DeleteObjectProc delete_object =
        load_import_slot<DeleteObjectProc>(data_00466030);

    // Retail calls the shared DeleteObject import from slot 14 down to 0;
    // the global handle entries themselves are left unchanged.
    for (int slot = 14; slot >= 0; --slot) {
        delete_object_at_slot(delete_object, handle_slots[slot]);
    }
}
