#pragma once
#include <string.h>
#include "th10/render/anm_texture.hpp"
#include "th10/render/animation_position_record.hpp"

// One loaded ANM file: the chain of entries in the archive image plus the
// tables built from it.
struct AnmFile {
    int slot;                                          // +0x000
    char name[0x104];                                  // +0x004
    AnmEntryHeader2* header;                   // +0x108
    int entry_count;                                   // +0x10C
    int script_count;                                  // +0x110
    int sprite_count;                                  // +0x114
    AnimationPositionRecord* sprites;         // +0x118
    const void** scripts;                              // +0x11C
    AnmTexture* textures;                     // +0x120, one per entry
    // +0x124: one past the entry to load next; zero once the file is complete.
    // Re-read on every use, so the loading thread and its owner can share it.
    volatile int cursor;
    int release_pending;                               // +0x128
    void* auxiliary;                                   // +0x12C

    AnmFile() { memset(this, 0, sizeof(*this)); }
};
typedef char AnmFileSize[sizeof(AnmFile) == 0x130 ? 1 : -1];

// 0x004472E0
__declspec(noinline) int __stdcall AnmFile_PreloadEntryImage(
    AnmFile* file, const AnmEntryHeader2* entry, int index);

// The ANM manager as far as the loader reaches: its table of loaded files.
struct AnmManager2 {
    unsigned char reserved_000000[0x3AD06C];
    AnmFile* files[33];                       // +0x3AD06C
};

// 0x004470C0
__declspec(noinline) AnmFile* __stdcall AnmManager_LoadFile(
    AnmManager2* manager, int slot, const char* name);

// 0x00447470
__declspec(noinline) int __stdcall AnmFile_LoadEntry(
    AnmUploadTag manager, AnmFile* file, int sprite_base, int script_base,
    const AnmEntryHeader2* entry, int index);
// 0x004473C0
__declspec(noinline) AnmFile* __stdcall AnmManager_LoadNextEntry(
    AnmUploadTag manager, AnmFile* file);
// 0x00447080
__declspec(noinline) AnmFile* __stdcall AnmManager_LoadFileNow(
    AnmManager2* manager, int slot, const char* name);
// 0x00447700
extern "C" __declspec(noinline) int __stdcall AnmManager_ServicePending(AnmManager2* manager);
// 0x00447050
__declspec(noinline) int AnimationTextureCreate2(int width, int height, void* output,
                                                         int format_index);

// One sprite rectangle as an ANM entry stores it, in entry pixels.
struct AnmSpriteSource {
    int id;
    float x, y, width, height;
};
struct AnmScriptRef {
    int id;
    int offset;
};

extern "C" char str_texture_load_failed[], str_texture_create_failed_format[];

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

#ifndef SURFACE_LOADING_LOG_HPP
#define SURFACE_LOADING_LOG_HPP
struct TextLog5 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

extern "C" TextLog5 g_log;
#endif

extern "C" char str_texture_load_failed_format[], str_anm_version_mismatch[], str_anm_load_failed[], str_texture_slots_full[];
