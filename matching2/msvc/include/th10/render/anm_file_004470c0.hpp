#pragma once
#include <string.h>
#include "th10/render/anm_texture_00446c70.hpp"
#include "th10/render/animation_position_record_00447940.hpp"

// One loaded ANM file: the chain of entries in the archive image plus the
// tables built from it.
struct AnmFile_004470c0 {
    int slot;                                          // +0x000
    char name[0x104];                                  // +0x004
    AnmEntryHeader_00446c70* header;                   // +0x108
    int entry_count;                                   // +0x10C
    int script_count;                                  // +0x110
    int sprite_count;                                  // +0x114
    AnimationPositionRecord_00447940* sprites;         // +0x118
    const void** scripts;                              // +0x11C
    AnmTexture_00446c70* textures;                     // +0x120, one per entry
    // +0x124: one past the entry to load next; zero once the file is complete.
    // Re-read on every use, so the loading thread and its owner can share it.
    volatile int cursor;
    int release_pending;                               // +0x128
    void* auxiliary;                                   // +0x12C

    AnmFile_004470c0() { memset(this, 0, sizeof(*this)); }
};
typedef char AnmFileSize_004470c0[sizeof(AnmFile_004470c0) == 0x130 ? 1 : -1];

// 0x004472E0
__declspec(noinline) int __stdcall AnmFile_PreloadEntryImage_004472e0(
    AnmFile_004470c0* file, const AnmEntryHeader_00446c70* entry, int index);

// The ANM manager as far as the loader reaches: its table of loaded files.
struct AnmManager_004470c0 {
    unsigned char reserved_000000[0x3AD06C];
    AnmFile_004470c0* files[33];                       // +0x3AD06C
};

// 0x004470C0
__declspec(noinline) AnmFile_004470c0* __stdcall AnmManager_LoadFile_004470c0(
    AnmManager_004470c0* manager, int slot, const char* name);

// 0x00447470
__declspec(noinline) int __stdcall AnmFile_LoadEntry_00447470(
    AnmUploadTag_00446c70 manager, AnmFile_004470c0* file, int sprite_base, int script_base,
    const AnmEntryHeader_00446c70* entry, int index);
// 0x004473C0
__declspec(noinline) AnmFile_004470c0* __stdcall AnmManager_LoadNextEntry_004473c0(
    AnmUploadTag_00446c70 manager, AnmFile_004470c0* file);
// 0x00447080
__declspec(noinline) AnmFile_004470c0* __stdcall AnmManager_LoadFileNow_00447080(
    AnmManager_004470c0* manager, int slot, const char* name);
// 0x00447700
extern "C" __declspec(noinline) int __stdcall AnmManager_ServicePending_00447700(AnmManager_004470c0* manager);
// 0x00447050
__declspec(noinline) int AnimationTextureCreate_00447050(int width, int height, void* output,
                                                         int format_index);

// One sprite rectangle as an ANM entry stores it, in entry pixels.
struct AnmSpriteSource_00447470 {
    int id;
    float x, y, width, height;
};
struct AnmScriptRef_00447470 {
    int id;
    int offset;
};

extern "C" char data_0047016c[], data_004701b0[];

extern "C" void* __cdecl asm_malloc_00452706(unsigned int size);

#ifndef SURFACE_LOADING_LOG_HPP
#define SURFACE_LOADING_LOG_HPP
struct TextLog_0044b8e0 {
    char text[0x2000];
    char* cursor;
    unsigned char dirty;
    char* AppendLine(char* format, ...);
};

extern "C" TextLog_0044b8e0 data_00474f70;
#endif

extern "C" char data_00470210[], data_00470254[], data_00470274[], data_00470384[];
