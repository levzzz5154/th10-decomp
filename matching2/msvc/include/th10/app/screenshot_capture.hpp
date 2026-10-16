#ifndef TH10_APP_SCREENSHOT_CAPTURE_00420670_HPP
#define TH10_APP_SCREENSHOT_CAPTURE_00420670_HPP
#include <stddef.h>

struct Direct3DSurface;
struct Direct3DDevice2;

struct LockedRect {
    int pitch;
    unsigned char* bits;
};

struct Direct3DSurfaceMethods {
    void* query_interface;
    void* add_ref;
    unsigned long (__stdcall* Release)(Direct3DSurface*);
    void* reserved_0c[(0x34 - 0x0C) / 4];
    long (__stdcall* LockRect)(Direct3DSurface*, LockedRect*, const void* rect,
                               unsigned long flags);
    long (__stdcall* UnlockRect)(Direct3DSurface*);
};
struct Direct3DSurface {
    Direct3DSurfaceMethods* methods;
};

struct Direct3DDeviceMethods {
    void* reserved_00[0x48 / 4];
    long (__stdcall* GetBackBuffer)(Direct3DDevice2*, unsigned int swap_chain, unsigned int index,
                                    unsigned int type, Direct3DSurface** surface);
};
struct Direct3DDevice2 {
    Direct3DDeviceMethods* methods;
};

#pragma pack(push, 2)
struct BitmapFileHeader {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int offset;
};
#pragma pack(pop)

// BITMAPINFOHEADER plus one spare word, as the game allocates it (0x2C bytes).
struct BitmapInfoHeader {
    unsigned int size;
    long width;
    long height;
    unsigned short planes;
    unsigned short bit_count;
    unsigned int compression;
    unsigned int image_size;
    long x_pixels_per_meter;
    long y_pixels_per_meter;
    unsigned int colors_used;
    unsigned int colors_important;
    unsigned int spare;
};

// The application object at 0x00491C28, as far as the screenshot capture
// reaches it.
struct GameApp {
    unsigned char reserved_000[8];
    Direct3DDevice2* device;        // +0x008
    unsigned char reserved_00c[0xEC - 0x0C];
    unsigned int back_buffer_format;        // +0x0EC (D3DFORMAT)
    unsigned char reserved_0f0[0x50C - 0xF0];
    unsigned long screenshot_thread;        // +0x50C (0x00492134), zero when no write is pending
    BitmapFileHeader file_header;  // +0x510
    unsigned char reserved_51e[2];
    BitmapInfoHeader* info_header; // +0x520
    unsigned char* pixels;                  // +0x524, bottom-up 640x480 BGR
    char filename[256];                     // +0x528

    // 0x00420670: copy the back buffer into a 24-bit bitmap and start the
    // thread that writes it. Returns 1 for an unknown back buffer format.
    __declspec(noinline) int CaptureScreenshot(const char* name);
};
typedef char GameAppFormatOffset[offsetof(GameApp, back_buffer_format) == 0xEC ? 1 : -1];
typedef char GameAppThreadOffset[offsetof(GameApp, screenshot_thread) == 0x50C ? 1 : -1];
typedef char GameAppHeaderOffset[offsetof(GameApp, file_header) == 0x510 ? 1 : -1];
typedef char GameAppInfoOffset[offsetof(GameApp, info_header) == 0x520 ? 1 : -1];
typedef char GameAppNameOffset[offsetof(GameApp, filename) == 0x528 ? 1 : -1];

// The 8 KiB diagnostic text log at 0x00474F70.
struct TextLog2 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;

    char* Append(char* format, ...);        // 0x0044B810
};

extern "C" {
extern GameApp g_application;
extern TextLog2 g_log;
extern char str_snapshot_alloc_failed[];      // Shift-JIS: "not enough memory for the screenshot"
extern char str_snapshot_16bit_unsupported[];      // Shift-JIS: "screenshots need a 32-bit display"
extern char str_mother_cpp_error[];      // "error ? .\\src\\game\\mother.cpp\r\n"

__declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);
void* __cdecl asm_malloc_00452706(unsigned int size);
unsigned long __cdecl asm_beginthread_00452eec(void (__cdecl* start)(void*), unsigned int stack_size,
                                               void* argument);
void __cdecl ScreenshotWriter(void* argument);
}

#endif
