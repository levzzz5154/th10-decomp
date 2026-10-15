#pragma once

#include "th10/render/anm_texture_00446c70.hpp"

// The A1R5G5B5 (format 25) and A4R4G4B4 (format 26) pixel layouts. MSVC
// packs bitfields from the low bit up, so b is bits 0-4/0-3 and a the top
// bit/nibble; the compiler tests the alpha field with a byte sign/nibble
// test and extracts the channels with shifts and masks, as retail does.
struct Pixel1555_004465b0 {
    unsigned short b : 5;
    unsigned short g : 5;
    unsigned short r : 5;
    unsigned short a : 1;
};

struct Pixel4444_004465b0 {
    unsigned short b : 4;
    unsigned short g : 4;
    unsigned short r : 4;
    unsigned short a : 4;
};

// The locked-rectangle record LockRect fills. D3DLOCKED_RECT.
struct AnmLockedRect {
    int pitch;                                         // +0x00, bytes per row
    void* bits;                                        // +0x04, pixel data
};

// The Direct3D 9 surface interface as the transparent-pixel fill at 0x004465B0
// drives it: the slots AnmSurface already names, extended by
// LockRect (slot 13, vtable offset 0x34) and UnlockRect (slot 14, 0x38).
struct AnmSurfaceFill {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0;
    virtual void __stdcall Slot07() = 0;
    virtual void __stdcall Slot08() = 0;
    virtual void __stdcall Slot09() = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot11() = 0;
    virtual long __stdcall GetDesc(AnmSurfaceDesc* desc) = 0;
    virtual long __stdcall LockRect(AnmLockedRect* locked, const void* rect,
                                    unsigned int flags) = 0;
    virtual long __stdcall UnlockRect() = 0;
};
