// Compiler context and ABI anchor only; none of these bytes enter the image.
#include "../../src/core/sprtlib/anm_texture_upload_00446c70.cpp"
#include "th10/platform/archive_file.hpp"
#include "th10/render/anm_file_004470c0.hpp"

extern "C" void __stdcall entry_external_00446c70(void*, int);

// 0x004465B0 is provided by the equivalent model source of this context;
// the stand-in that used to pin its first 13 bytes is not part of the model link.

#pragma code_seg(".text$05scontext")
extern "C" int __stdcall AnmTextureUploadContext_00446c70(
        AnmTexture_00446c70** textures, const void** data, int count) {
    int result = 0;
    for (int i = 0; i < count; ++i) {
        AnmUploadTag_00446c70 tag = { count ^ i };
        int loaded_size = 0;
        result += *Archive_LoadFile(static_cast<const char*>(data[i]), &loaded_size, i & 1);
        result += loaded_size;
        result += textures[i]->LoadFile(count - i, textures[i]->file_data, static_cast<const char*>(data[i]), count | i);
        result += AnmTexture_UploadAt_00446d70(tag, textures[i], i, data[i], count + i, count - i, count & i);
        result += AnmTexture_CreateFromMemory_00446eb0(tag, textures[i], i, count | i, count * i, count + 2 * i);
        result += AnmTexture_CreateAndUpload_00446f40(
            textures[i], static_cast<const AnmEntryHeader_00446c70*>(data[i])->Thtx(), i, count * i, count + 3 * i);
        result += AnmManager_LoadFileNow_00447080(
            reinterpret_cast<AnmManager_004470c0*>(textures[i]), count - i,
            static_cast<const char*>(data[i]))->slot;
        result += AnmManager_LoadNextEntry_004473c0(
            tag, reinterpret_cast<AnmFile_004470c0*>(textures[i]))->slot;
        result += AnmManager_LoadFile_004470c0(
            reinterpret_cast<AnmManager_004470c0*>(textures[i]), i,
            static_cast<const char*>(data[i]))->slot;
        result += AnmFile_PreloadEntryImage_004472e0(
            reinterpret_cast<AnmFile_004470c0*>(textures[i]),
            static_cast<const AnmEntryHeader_00446c70*>(data[i]), i);
        result += textures[i]->Upload(tag, i, data[i], count - i, count & i);
    }
    return result;
}
#pragma code_seg()

// The two already recovered callees of the entry loader, at their addresses.
#define ANIMATION_TEXTURE_CREATE_SECTION ".text$04wanim"
#define COPY_POSITION_RECORD_SECTION ".text$05r5copy"
#include "../../src/core/sprtlib/animation_texture_create_00447050.cpp"
#include "../../src/core/sprtlib/animation_manager_copy_position_record_00447940.cpp"

// Complete real archive closure, supplying the actual internal reader contract.
#define ARCHIVE_READ_SECTION ".text$00bread"
#define ARCHIVE_FIND_SECTION ".text$00dfind"
#define ARCHIVE_DECRYPT_SECTION ".text$06decrypt"
#define ARCHIVE_LOAD_SECTION ".text$07load"
#include "native_archive_read/read.cpp"
#include "native_archive_read/find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "native_archive_read/load.cpp"
#include "resource_surface_loading_log.cpp"
