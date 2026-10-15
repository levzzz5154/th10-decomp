#pragma once

// The two Direct3D 9 interfaces the texture upload touches, reduced to the
// vtable slots it uses.
// D3DSURFACE_DESC.
struct AnmSurfaceDesc {
    int format, type, usage, pool, multisample_type, multisample_quality;
    unsigned int width, height;
};
struct AnmSurface {
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
};
struct AnmD3DTexture {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual void __stdcall Slot03() = 0;
    virtual void __stdcall Slot04() = 0;
    virtual void __stdcall Slot05() = 0;
    virtual void __stdcall Slot06() = 0;
    virtual unsigned int __stdcall SetPriority(unsigned int priority) = 0;
    virtual void __stdcall Slot08() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual void __stdcall Slot10() = 0;
    virtual void __stdcall Slot11() = 0;
    virtual void __stdcall Slot12() = 0;
    virtual void __stdcall Slot13() = 0;
    virtual void __stdcall Slot14() = 0;
    virtual void __stdcall Slot15() = 0;
    virtual void __stdcall Slot16() = 0;
    virtual long __stdcall GetLevelDesc(unsigned int level, AnmSurfaceDesc* desc) = 0;
    virtual long __stdcall GetSurfaceLevel(unsigned int level, AnmSurface** surface) = 0;
};

struct AnmRect {
    int left, top, right, bottom;
};

// The THTX block an ANM entry embeds its raw pixels in.
struct AnmThtxHeader {
    char magic[4];                                     // +0x00, "THTX"
    short zero;                                        // +0x04
    short format;                                      // +0x06, index into the format tables
    short width;                                       // +0x08
    short height;                                      // +0x0A
    int size;                                          // +0x0C
    unsigned char pixels[1];                           // +0x10
};

// An ANM entry header as far as the upload reads it.
struct AnmEntryHeader_00446c70 {
    int sprite_count;                                  // +0x00
    int script_count;                                  // +0x04
    unsigned char reserved_008[0x04];
    int width;                                         // +0x0C
    int height;                                        // +0x10
    int format;                                        // +0x14, index into the format tables
    unsigned int color_key;                            // +0x18
    int name_offset;                                   // +0x1C
    unsigned char reserved_020[0x08];
    int version;                                       // +0x28
    unsigned int priority;                             // +0x2C
    int thtx_offset;                                   // +0x30
    unsigned char has_data;                            // +0x34
    unsigned char reserved_035[0x03];
    int next_offset;                                   // +0x38, zero on the last entry
    unsigned char reserved_03c[0x04];
    int sprite_offsets[1];                             // +0x40, then {id, offset} per script

    AnmEntryHeader_00446c70* Next() {
        return reinterpret_cast<AnmEntryHeader_00446c70*>(
            reinterpret_cast<unsigned char*>(this) + next_offset);
    }
    const char* Name() const {
        return reinterpret_cast<const char*>(this) + name_offset;
    }

    const AnmThtxHeader* Thtx() const {
        return reinterpret_cast<const AnmThtxHeader*>(
            reinterpret_cast<const unsigned char*>(this) + thtx_offset);
    }
};

// A four-byte class-type argument the upload receives and never reads. Being
// a class type it keeps its stack slot, which is what retail's RET 8 shows.
struct AnmUploadTag {
    int value;
};

// One loaded ANM texture.
struct AnmTexture {
    AnmD3DTexture* texture;                   // +0x00
    void* file_data;                                   // +0x04
    int data_size;                                     // +0x08
    int bytes_per_pixel;                               // +0x0C

    // 0x004465B0
    __declspec(noinline) void FillTransparentPixels();
    // 0x00446B70
    __declspec(noinline) int LoadFile(int format, void* size_slot, const char* name, unsigned int color_key);
    // 0x00446C70
    __declspec(noinline) int Upload(AnmUploadTag tag, int format, const void* data, int size,
                                    int has_thtx);
};

// 0x00446EB0
__declspec(noinline) int __stdcall AnmTexture_CreateFromMemory(
    AnmUploadTag tag, AnmTexture* texture, int format, unsigned int color_key,
    int width, int height);
// 0x00446F40
__declspec(noinline) int __stdcall AnmTexture_CreateAndUpload(AnmTexture* texture, const AnmThtxHeader* thtx, int format, int width, int height);
// 0x00446D70
__declspec(noinline) int __stdcall AnmTexture_UploadAt(
    AnmUploadTag tag, AnmTexture* texture, int format, const void* data, int top,
    int size, int has_thtx);

extern "C" unsigned char g_sound_flags;                // renderer capability flags
extern "C" int g_texture_formats_a[];                        // D3DFORMAT per ANM format index
extern "C" int g_texture_formats_b[];                        // bytes per pixel per ANM format index

extern "C" unsigned int __stdcall asm_D3DXLoadSurfaceFromFileInMemory_004521d0(
    void* destination, const void* destination_palette, const void* destination_rect,
    const void* source, unsigned int source_size, const void* source_rect,
    unsigned int filter, unsigned int color_key, void* source_info);
extern "C" unsigned int __stdcall asm_D3DXLoadSurfaceFromMemory_004521a6(
    void* destination, const void* destination_palette, const void* destination_rect,
    const void* source, unsigned int format, unsigned int pitch,
    const void* source_palette, const void* source_rect, unsigned int filter,
    unsigned int color_key);

extern "C" void* g_d3d_device;                        // Direct3D device
extern "C" char str_string_format[];                       // "%s"
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
extern "C" void __cdecl crt_free(void*);
extern "C" unsigned int __stdcall asm_D3DXCreateTextureFromFileInMemoryEx_004521ca(
    void* device, const void* source, unsigned int source_size, unsigned int width,
    unsigned int height, unsigned int mip_levels, unsigned int usage, unsigned int format,
    unsigned int pool, unsigned int filter, unsigned int mip_filter, unsigned int color_key,
    void* source_info, void* palette, AnmD3DTexture** texture);
extern "C" int __stdcall asm_D3DXCreateTexture_004521a0(
    void* device, unsigned int width, unsigned int height, unsigned int mip_levels,
    unsigned int usage, unsigned int format, unsigned int pool, void** texture);
