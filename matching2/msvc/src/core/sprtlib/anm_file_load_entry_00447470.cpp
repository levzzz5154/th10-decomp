// 0x00447470 (650 bytes): build everything one ANM entry contributes to its
// file: the texture (blank for an '@' name, from the preloaded image file, or
// from the embedded THTX block), then the entry's sprites scaled to the
// texture's real size, then its script pointers. Returns 1, or -1 after
// logging.
//
// The THTX address is spelled out at the call instead of using
// AnmEntryHeader::Thtx(): the inline accessor makes the compiler load the
// offset one argument too early.
//
// Native LTCG passes the entry index in EAX; the other five arguments stay on
// the stack. `manager` is only handed on to the texture loader.
#include "th10/render/anm_file_004470c0.hpp"

#pragma code_seg(".text$05r3entry")
int __stdcall AnmFile_LoadEntry_00447470(AnmUploadTag_00446c70 manager, AnmFile_004470c0* file,
                                         int sprite_base, int script_base,
                                         const AnmEntryHeader_00446c70* entry, int index) {
    if (!entry) {
        data_00474f70.AppendLine(data_00470274);
        return -1;
    }
    if (entry->version != 4) {
        data_00474f70.AppendLine(data_00470254);
        return -1;
    }
    if (!entry->has_data) {
        const char* name = entry->Name();
        if (name[0] == '@') {
            AnimationTextureCreate_00447050(entry->width, entry->height, &file->textures[index],
                                            entry->format);
        } else if (AnmTexture_CreateFromMemory_00446eb0(manager, &file->textures[index],
                                                        entry->format, entry->color_key,
                                                        entry->width, entry->height) != 0) {
            data_00474f70.AppendLine(data_004701b0, name);
            return -1;
        }
    } else if (AnmTexture_CreateAndUpload_00446f40(
                   &file->textures[index],
                   reinterpret_cast<const AnmThtxHeader_00446c70*>(
                       reinterpret_cast<const unsigned char*>(entry) + entry->thtx_offset),
                   entry->format, entry->width, entry->height) != 0) {
        data_00474f70.AppendLine(data_0047016c);
        return -1;
    }
    file->textures[index].texture->SetPriority(entry->priority);
    file->textures[index].texture->PreLoad();
    AnmSurfaceDesc_00446c70 desc;
    file->textures[index].texture->GetLevelDesc(0, &desc);

    const int* offset = entry->sprite_offsets;
    for (int i = 0; i < entry->sprite_count; ++i, ++offset) {
        AnimationPositionRecord_00447940 record;
        const AnmSpriteSource_00447470* sprite = reinterpret_cast<const AnmSpriteSource_00447470*>(
            reinterpret_cast<const unsigned char*>(entry) + *offset);
        record.header[0] = file->slot;
        record.header[1] = reinterpret_cast<unsigned int>(file->textures[index].texture);
        float texture_width = static_cast<float>(desc.width);
        record.width = texture_width / static_cast<float>(entry->width);
        float texture_height = static_cast<float>(desc.height);
        record.height = texture_height / static_cast<float>(entry->height);
        record.left = record.width * sprite->x;
        record.top = record.height * sprite->y;
        record.right = (sprite->width + sprite->x) * record.width;
        record.bottom = (sprite->height + sprite->y) * record.height;
        record.textureWidth = texture_width;
        record.textureHeight = texture_height;
        CopyPositionRecord_00447940(sprite_base,
                                    reinterpret_cast<AnimationPositionManager_00447940*>(file),
                                    &record);
        ++sprite_base;
    }

    const AnmScriptRef_00447470* script = reinterpret_cast<const AnmScriptRef_00447470*>(offset);
    for (int j = 0; j < entry->script_count; ++j, ++script) {
        file->scripts[script_base] = reinterpret_cast<const unsigned char*>(entry) + script->offset;
        ++script_base;
    }
    return 1;
}
#pragma code_seg()
