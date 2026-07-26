// Direct retail-layout ANM mounting for the all-source PE32 runtime.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d9.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#include "th10/archive/resource_manager.hpp"
#include "th10/game/entity.hpp"
#include "th10/render/animation_manager.hpp"
#include "th10/render/anm_file.hpp"

extern void* g_pD3DDevice;

namespace {

struct RuntimeAnmResource {
    int slot;                         // +0x000
    char name[0x104];                 // +0x004
    unsigned char* image;             // +0x108
    unsigned int entry_count;         // +0x10C
    unsigned int script_count;        // +0x110
    unsigned int sprite_count;        // +0x114
    float* sprite_records;             // +0x118, 17 floats each
    const unsigned char** scripts;     // +0x11C
    unsigned int* textures;            // +0x120, four dwords each
    int loading;                       // +0x124
    unsigned int reserved[2];
};

static_assert(sizeof(RuntimeAnmResource) == 0x130,
              "retail ANM resource descriptor layout");

struct EntryTotals {
    unsigned int entries;
    unsigned int sprites;
    unsigned int scripts;
};

bool BuildAssetPath(const char* name, char output[260]) {
    if (name == nullptr)
        return false;
    if (std::strchr(name, '/') != nullptr ||
        std::strchr(name, '\\') != nullptr) {
        std::snprintf(output, 260, "%s", name);
    } else {
        std::snprintf(output, 260, "th10/%s", name);
    }
    return output[0] != '\0';
}

bool CountEntries(const unsigned char* image, unsigned int size,
                  EntryTotals* totals) {
    *totals = {};
    size_t offset = 0;
    for (;;) {
        AnmFileEntry entry;
        if (!AnmFile_ParseEntry(image, size, offset, &entry))
            return false;
        ++totals->entries;
        totals->sprites += entry.sprite_count;
        totals->scripts += entry.script_count;
        if (entry.next_offset == 0)
            return true;
        if (entry.next_offset > size - offset)
            return false;
        offset += entry.next_offset;
    }
}

IDirect3DTexture9* CreateTexture(const AnmFileEntry& entry) {
    if (g_pD3DDevice == nullptr)
        return nullptr;
    AnmTexturePayload payload;
    if (!AnmFile_GetTexture(&entry, &payload))
        return nullptr;
    const D3DFORMAT format =
        payload.format == 1 ? D3DFMT_A8R8G8B8 :
        payload.format == 5 ? D3DFMT_A4R4G4B4 : D3DFMT_UNKNOWN;
    if (format == D3DFMT_UNKNOWN)
        return nullptr;

    const unsigned int width = entry.width != 0 ?
        entry.width : payload.width;
    const unsigned int height = entry.height != 0 ?
        entry.height : payload.height;
    IDirect3DTexture9* texture = nullptr;
    auto* device = static_cast<IDirect3DDevice9*>(g_pD3DDevice);
    if (FAILED(device->CreateTexture(width, height, 1, 0, format,
                                     D3DPOOL_MANAGED, &texture, nullptr)))
        return nullptr;

    D3DLOCKED_RECT locked = {};
    if (FAILED(texture->LockRect(0, &locked, nullptr, 0))) {
        texture->Release();
        return nullptr;
    }
    const unsigned int bytes_per_pixel = payload.format == 1 ? 4u : 2u;
    const unsigned int source_pitch =
        payload.height == 0 ? 0 : payload.data_size / payload.height;
    const unsigned int rows =
        payload.height < height ? payload.height : height;
    unsigned int copy_pitch = width * bytes_per_pixel;
    if (copy_pitch > source_pitch)
        copy_pitch = source_pitch;
    if (copy_pitch > static_cast<unsigned int>(locked.Pitch))
        copy_pitch = static_cast<unsigned int>(locked.Pitch);
    for (unsigned int row = 0; row < rows; ++row) {
        std::memcpy(static_cast<unsigned char*>(locked.pBits) +
                        row * locked.Pitch,
                    payload.pixels + row * source_pitch, copy_pitch);
    }
    texture->UnlockRect(0);
    return texture;
}

void ReleaseResource(RuntimeAnmResource* resource) {
    if (resource == nullptr)
        return;
    if (resource->textures != nullptr) {
        for (unsigned int index = 0; index < resource->entry_count; ++index) {
            auto* texture = reinterpret_cast<IDirect3DTexture9*>(
                resource->textures[index * 4]);
            if (texture != nullptr)
                texture->Release();
        }
    }
    std::free(resource->textures);
    std::free(resource->scripts);
    std::free(resource->sprite_records);
    std::free(resource->image);
    std::free(resource);
}

RuntimeAnmResource* MountResource(
    int slot, unsigned char* manager, const char* name) {
    char path[260];
    if (!BuildAssetPath(name, path))
        return nullptr;
    const unsigned int size = Resource_GetFileSize(path);
    if (size == 0) {
        std::fprintf(stderr, "[th10] ANM size lookup failed: %s\n", path);
        return nullptr;
    }
    unsigned char* image = Resource_LoadFile(path, nullptr);
    if (image == nullptr) {
        std::fprintf(stderr, "[th10] ANM load failed: %s\n", path);
        return nullptr;
    }

    EntryTotals totals;
    if (!CountEntries(image, size, &totals)) {
        std::fprintf(stderr,
                     "[th10] ANM entry walk failed: %s (%u bytes)\n",
                     path, size);
        std::free(image);
        return nullptr;
    }
    auto* resource = static_cast<RuntimeAnmResource*>(
        std::calloc(1, sizeof(RuntimeAnmResource)));
    if (resource == nullptr) {
        std::free(image);
        return nullptr;
    }
    resource->slot = slot;
    std::snprintf(resource->name, sizeof(resource->name), "%s", name);
    resource->image = image;
    resource->entry_count = totals.entries;
    resource->script_count = totals.scripts;
    resource->sprite_count = totals.sprites;
    resource->sprite_records = static_cast<float*>(
        std::calloc(totals.sprites * 17u, sizeof(float)));
    resource->scripts = static_cast<const unsigned char**>(
        std::calloc(totals.scripts, sizeof(unsigned char*)));
    resource->textures = static_cast<unsigned int*>(
        std::calloc(totals.entries * 4u, sizeof(unsigned int)));
    if ((totals.sprites != 0 && resource->sprite_records == nullptr) ||
        (totals.scripts != 0 && resource->scripts == nullptr) ||
        (totals.entries != 0 && resource->textures == nullptr)) {
        ReleaseResource(resource);
        return nullptr;
    }

    size_t offset = 0;
    unsigned int sprite_base = 0;
    unsigned int script_base = 0;
    for (unsigned int entry_index = 0;
         entry_index < totals.entries; ++entry_index) {
        AnmFileEntry entry;
        if (!AnmFile_ParseEntry(image, size, offset, &entry)) {
            ReleaseResource(resource);
            return nullptr;
        }
        IDirect3DTexture9* texture = CreateTexture(entry);
        resource->textures[entry_index * 4] =
            static_cast<unsigned int>(reinterpret_cast<uintptr_t>(texture));
        resource->textures[entry_index * 4 + 3] =
            entry.format == 1 ? 4u : 2u;

        for (unsigned int index = 0; index < entry.sprite_count; ++index) {
            AnmFileSprite sprite;
            if (!AnmFile_GetSprite(&entry, index, &sprite))
                continue;
            float* record =
                resource->sprite_records + (sprite_base + index) * 17u;
            std::memcpy(record, &resource->slot, sizeof(unsigned int));
            record[1] = 0.0f;
            std::memcpy(record + 1,
                        &resource->textures[entry_index * 4],
                        sizeof(unsigned int));
            record[2] = sprite.x;
            record[3] = sprite.y;
            record[4] = sprite.x + sprite.width;
            record[5] = sprite.y + sprite.height;
            record[6] = static_cast<float>(entry.height);
            record[7] = static_cast<float>(entry.width);
            if (entry.width != 0 && entry.height != 0) {
                record[8] = record[2] / record[7];
                record[9] = record[3] / record[6];
                record[10] = record[4] / record[7];
                record[11] = record[5] / record[6];
            }
            record[12] = sprite.height;
            record[13] = sprite.width;
            record[14] = 1.0f;
            record[15] = 1.0f;
        }
        for (unsigned int index = 0; index < entry.script_count; ++index) {
            AnmFileScript script;
            if (AnmFile_GetScriptByIndex(&entry, index, &script))
                resource->scripts[script_base + index] =
                    script.instructions;
        }
        sprite_base += entry.sprite_count;
        script_base += entry.script_count;
        offset += entry.next_offset;
    }
    resource->loading = 0;
    *reinterpret_cast<RuntimeAnmResource**>(
        manager + 0x3AD06C + slot * 4) = resource;
    return resource;
}

RuntimeAnmResource* FindResource(
    int slot, void* manager_pointer, const char* name) {
    if (manager_pointer == nullptr || slot < 0 || slot >= 0x21)
        return nullptr;
    auto* manager = static_cast<unsigned char*>(manager_pointer);
    auto** location = reinterpret_cast<RuntimeAnmResource**>(
        manager + 0x3AD06C + slot * 4);
    if (*location != nullptr)
        return *location;
    return MountResource(slot, manager, name);
}

}  // namespace

int* ResourceManager_FindResource(
    int slot, void* manager, const char* name) {
    return reinterpret_cast<int*>(FindResource(slot, manager, name));
}

void* ResourceManager_FindResource(
    int slot, int manager, const char* name) {
    return FindResource(
        slot, reinterpret_cast<void*>(static_cast<uintptr_t>(manager)), name);
}

void ResourceManager_DestroyResource(void* manager, void* resource_pointer) {
    auto* resource = static_cast<RuntimeAnmResource*>(resource_pointer);
    if (resource == nullptr || resource->image == nullptr)
        return;
    AnimationManager_MarkResourceForRemoval(manager, resource);
    if (resource->textures != nullptr) {
        for (unsigned int index = 0; index < resource->entry_count; ++index) {
            auto* texture = reinterpret_cast<IDirect3DTexture9*>(
                resource->textures[index * 4]);
            if (texture != nullptr)
                texture->Release();
            void* external_image = reinterpret_cast<void*>(
                static_cast<uintptr_t>(
                    resource->textures[index * 4 + 1]));
            std::free(external_image);
        }
    }
    std::free(resource->textures);
    std::free(resource->sprite_records);
    std::free(resource->scripts);
    std::free(resource->image);
    resource->textures = nullptr;
    resource->sprite_records = nullptr;
    resource->scripts = nullptr;
    resource->image = nullptr;
}

// Direct normal-quad path from the 0x004451C0 dispatcher.  The exotic render
// modes still have dedicated reconstructed helpers, but the overwhelmingly
// common modes 0/1/2/3 share this sprite-record, anchor, rotation and texture
// path.
void AnimationObject_Render(void*, AnimationObject* animation) {
    if (animation == nullptr || g_pD3DDevice == nullptr)
        return;
    auto* object = reinterpret_cast<unsigned char*>(animation);
    const unsigned int flags =
        *reinterpret_cast<unsigned int*>(object + 0x35C);
    if ((flags & 3u) != 3u || object[0x2FF] == 0)
        return;
    const float* sprite =
        *reinterpret_cast<const float**>(object + 0x394);
    if (sprite == nullptr)
        return;
    auto* texture = reinterpret_cast<IDirect3DTexture9*>(
        static_cast<uintptr_t>(*reinterpret_cast<const unsigned int*>(
            sprite + 1)));
    if (texture == nullptr)
        return;

    const float center_x =
        *reinterpret_cast<float*>(object + 0x334) +
        *reinterpret_cast<float*>(object + 0x340) +
        *reinterpret_cast<float*>(object + 0x34C);
    const float center_y =
        *reinterpret_cast<float*>(object + 0x338) +
        *reinterpret_cast<float*>(object + 0x344) +
        *reinterpret_cast<float*>(object + 0x350);
    const float center_z =
        *reinterpret_cast<float*>(object + 0x33C) +
        *reinterpret_cast<float*>(object + 0x348) +
        *reinterpret_cast<float*>(object + 0x354);
    const float width = *reinterpret_cast<float*>(object + 0x4C) *
        *reinterpret_cast<float*>(object + 0x3C);
    const float height = *reinterpret_cast<float*>(object + 0x50) *
        *reinterpret_cast<float*>(object + 0x40);

    float left;
    float right;
    switch ((flags >> 18) & 3u) {
    case 1: left = 0.0f; right = width; break;
    case 2: left = -width; right = 0.0f; break;
    default: left = width * -0.5f; right = width * 0.5f; break;
    }
    float top;
    float bottom;
    switch ((flags >> 20) & 3u) {
    case 1: top = 0.0f; bottom = height; break;
    case 2: top = -height; bottom = 0.0f; break;
    default: top = height * -0.5f; bottom = height * 0.5f; break;
    }
    const float angle = *reinterpret_cast<float*>(object + 0x2C);
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    auto rotate_x = [=](float x, float y) {
        return x * cosine - y * sine + center_x;
    };
    auto rotate_y = [=](float x, float y) {
        return x * sine + y * cosine + center_y;
    };

    struct Vertex {
        float x;
        float y;
        float z;
        float rhw;
        unsigned int color;
        float u;
        float v;
    };
    const unsigned int color =
        *reinterpret_cast<unsigned int*>(object + 0x2FC);
    const float u0 = sprite[8];
    const float v0 = sprite[9];
    const float u1 = sprite[10];
    const float v1 = sprite[11];
    Vertex vertices[4] = {
        {rotate_x(left, top), rotate_y(left, top), center_z, 1.0f,
         color, u0, v0},
        {rotate_x(right, top), rotate_y(right, top), center_z, 1.0f,
         color, u1, v0},
        {rotate_x(left, bottom), rotate_y(left, bottom), center_z, 1.0f,
         color, u0, v1},
        {rotate_x(right, bottom), rotate_y(right, bottom), center_z, 1.0f,
         color, u1, v1},
    };
    auto* device = static_cast<IDirect3DDevice9*>(g_pD3DDevice);
    device->SetTexture(0, texture);
    device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    device->DrawPrimitiveUP(
        D3DPT_TRIANGLESTRIP, 2, vertices, sizeof(Vertex));
}

namespace {

unsigned short ReadU16(const unsigned char* source) {
    return static_cast<unsigned short>(
        source[0] | static_cast<unsigned short>(source[1] << 8));
}

int ReadI32(const unsigned char* source) {
    int value;
    std::memcpy(&value, source, sizeof(value));
    return value;
}

float ReadF32(const unsigned char* source) {
    float value;
    std::memcpy(&value, source, sizeof(value));
    return value;
}

int RuntimeIntArgument(
    AnimationObject* animation, const unsigned char* instruction,
    int index) {
    const int value = ReadI32(instruction + 8 + index * 4);
    if ((instruction[6] & (1u << index)) == 0)
        return value;
    return AnimationObject_ReadIntegerVariable(animation, value);
}

float RuntimeFloatArgument(
    AnimationObject* animation, const unsigned char* instruction,
    int index) {
    const float value = ReadF32(instruction + 8 + index * 4);
    if ((instruction[6] & (1u << index)) == 0)
        return value;
    int variable;
    std::memcpy(&variable, &value, sizeof(variable));
    float fallback = value;
    return *AnimationObject_ResolveFloatVariable(
        animation, variable, &fallback, true);
}

}  // namespace

// Executable core of 0x0043EE30.  This covers the control-flow, variable,
// sprite, transform, color, blend and flag instructions used by the title,
// front and stage archives. Interpolator/ring/child opcodes retain their
// state flags and are the next expansion tier.
int AnimationObject_ExecuteScript(AnimationObject* animation) {
    if (animation == nullptr)
        return 1;
    auto* object = reinterpret_cast<unsigned char*>(animation);
    auto*& cursor = *reinterpret_cast<unsigned char**>(object + 0x390);
    auto* script_base =
        *reinterpret_cast<unsigned char**>(object + 0x38C);
    if (cursor == nullptr)
        return 1;
    unsigned int& flags =
        *reinterpret_cast<unsigned int*>(object + 0x35C);
    if ((flags & 0x20000u) != 0)
        return 0;

    int& frame = *reinterpret_cast<int*>(object + 0x60);
    float& elapsed = *reinterpret_cast<float*>(object + 0x64);
    for (unsigned int budget = 0; budget != 4096; ++budget) {
        const unsigned short opcode = ReadU16(cursor);
        const unsigned short size = ReadU16(cursor + 2);
        const short instruction_time =
            static_cast<short>(ReadU16(cursor + 4));
        if (size < 8)
            return 1;
        if (instruction_time > frame)
            break;
        unsigned char* next = cursor + size;
        switch (opcode) {
        case 0xFFFF:
        case 1:
        case 2:
            cursor = nullptr;
            return 1;
        case 3: {
            const int sprite =
                RuntimeIntArgument(animation, cursor, 0);
            AnimationObject_ConfigureFromResource(
                animation,
                *reinterpret_cast<void**>(object + 0x308), sprite);
            break;
        }
        case 4:
            frame = RuntimeIntArgument(animation, cursor, 1);
            elapsed = static_cast<float>(frame);
            next = script_base +
                RuntimeIntArgument(animation, cursor, 0);
            break;
        case 6:
        case 8:
        case 0xA:
        case 0xC: {
            const int variable = ReadI32(cursor + 8);
            int fallback = 0;
            int* slot = AnimationObject_ResolveIntegerVariable(
                animation, variable, &fallback, true);
            const int value =
                RuntimeIntArgument(animation, cursor, 1);
            if (opcode == 6) *slot = value;
            else if (opcode == 8) *slot += value;
            else if (opcode == 0xA) *slot -= value;
            else *slot *= value;
            break;
        }
        case 7:
        case 9:
        case 0xB:
        case 0xD: {
            const int variable = ReadI32(cursor + 8);
            float fallback = 0.0f;
            float* slot = AnimationObject_ResolveFloatVariable(
                animation, variable, &fallback, true);
            const float value =
                RuntimeFloatArgument(animation, cursor, 1);
            if (opcode == 7) *slot = value;
            else if (opcode == 9) *slot += value;
            else if (opcode == 0xB) *slot -= value;
            else *slot *= value;
            break;
        }
        case 0x30: {
            const unsigned int position_offset =
                (flags & 0x100u) != 0 ? 0x34Cu : 0x334u;
            for (int axis = 0; axis != 3; ++axis)
                *reinterpret_cast<float*>(
                    object + position_offset + axis * 4) =
                    RuntimeFloatArgument(animation, cursor, axis);
            break;
        }
        case 0x31:
            *reinterpret_cast<float*>(object + 0x3C) =
                RuntimeFloatArgument(animation, cursor, 0);
            *reinterpret_cast<float*>(object + 0x40) =
                RuntimeFloatArgument(animation, cursor, 1);
            flags |= 4u;
            break;
        case 0x32:
            *reinterpret_cast<float*>(object + 0x4C) =
                RuntimeFloatArgument(animation, cursor, 0);
            *reinterpret_cast<float*>(object + 0x50) =
                RuntimeFloatArgument(animation, cursor, 1);
            flags |= 8u;
            break;
        case 0x33:
            object[0x2FF] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 0));
            break;
        case 0x34:
            object[0x2FE] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 0));
            object[0x2FD] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 1));
            object[0x2FC] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 2));
            break;
        case 0x35:
            *reinterpret_cast<float*>(object + 0x44) =
                RuntimeFloatArgument(animation, cursor, 0);
            *reinterpret_cast<float*>(object + 0x48) =
                RuntimeFloatArgument(animation, cursor, 1);
            break;
        case 0x3D:
            *reinterpret_cast<float*>(object + 0x4C) *= 0.5f;
            flags ^= 0x208u;
            break;
        case 0x3E:
            *reinterpret_cast<float*>(object + 0x50) *= 0.5f;
            flags ^= 0x408u;
            break;
        case 0x3F:
        case 0x45:
            if (*reinterpret_cast<int*>(object + 0x304) == 0) {
                flags |= 0x1000u;
                frame = -1;
                elapsed = -1.0f;
                cursor = next;
                return 0;
            }
            flags &= ~0x1000u;
            break;
        case 0x41:
            flags = (flags & ~(0xC0000u | 0x300000u)) |
                (static_cast<unsigned int>(
                    RuntimeIntArgument(animation, cursor, 0)) << 18) |
                (static_cast<unsigned int>(
                    RuntimeIntArgument(animation, cursor, 1)) << 20);
            break;
        case 0x42:
            flags = (flags & ~0x30u) |
                (static_cast<unsigned int>(
                    RuntimeIntArgument(animation, cursor, 0)) << 4);
            break;
        case 0x43:
            flags = (flags & ~0x3C00000u) |
                (static_cast<unsigned int>(
                    RuntimeIntArgument(animation, cursor, 0)) << 22);
            break;
        case 0x44:
            *reinterpret_cast<int*>(object + 0x20) =
                RuntimeIntArgument(animation, cursor, 0);
            break;
        case 0x46:
            *reinterpret_cast<float*>(object + 0x38) =
                RuntimeFloatArgument(animation, cursor, 0);
            break;
        case 0x47:
            *reinterpret_cast<float*>(object + 0x34) =
                RuntimeFloatArgument(animation, cursor, 0);
            break;
        case 0x4C:
            object[0x302] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 0));
            object[0x301] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 1));
            object[0x300] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 2));
            break;
        case 0x4D:
            object[0x303] = static_cast<unsigned char>(
                RuntimeIntArgument(animation, cursor, 0));
            break;
        case 0x51: {
            frame = *reinterpret_cast<int*>(object + 0x368);
            elapsed = *reinterpret_cast<float*>(object + 0x36C);
            *reinterpret_cast<int*>(object + 0x5C) =
                *reinterpret_cast<int*>(object + 0x370);
            next = *reinterpret_cast<unsigned char**>(object + 0x374);
            flags &= ~1u;
            break;
        }
        case 0x53:
            for (int axis = 0; axis != 3; ++axis) {
                *reinterpret_cast<float*>(object + 0x334 + axis * 4) +=
                    *reinterpret_cast<float*>(object + 0x340 + axis * 4);
                *reinterpret_cast<float*>(object + 0x340 + axis * 4) = 0.0f;
            }
            break;
        case 0x54:
            flags = (flags & 0xFE7FFFFFu) | 0x02400000u;
            break;
        case 0x58:
        case 0x5A:
        case 0x5B:
        case 0x5C: {
            extern void* g_pGameStateManager;
            void* resource = *reinterpret_cast<void**>(object + 0x308);
            const int script =
                RuntimeIntArgument(animation, cursor, 0);
            const int bucket = *reinterpret_cast<int*>(object + 0x20);
            if (opcode == 0x58) {
                AnimationManager_CreatePrimaryBack(
                    g_pGameStateManager, resource, script, bucket);
            } else if (opcode == 0x5A) {
                AnimationManager_CreateSecondaryBack(
                    g_pGameStateManager, resource, script, bucket);
            } else if (opcode == 0x5B) {
                AnimationManager_CreatePrimaryFront(
                    g_pGameStateManager, resource, script, bucket);
            } else {
                AnimationManager_CreateSecondaryFront(
                    g_pGameStateManager, resource, script, bucket);
            }
            break;
        }
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x50:
        case 0x52:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x59: {
            unsigned int shift = 0;
            switch (opcode) {
            case 0x49: shift = 11; break;
            case 0x4A: shift = 13; break;
            case 0x50: shift = 15; break;
            case 0x52: shift = 27; break;
            case 0x55: shift = 28; break;
            case 0x56: shift = 29; break;
            case 0x57: shift = 30; break;
            case 0x59: shift = 31; break;
            default: break;
            }
            const unsigned int mask = 1u << shift;
            if (RuntimeIntArgument(animation, cursor, 0) != 0)
                flags |= mask;
            else
                flags &= ~mask;
            break;
        }
        default:
            break;
        }
        cursor = next;
    }

    const float speed = *reinterpret_cast<float**>(object + 0x68) != nullptr ?
        **reinterpret_cast<float**>(object + 0x68) : 1.0f;
    *reinterpret_cast<float*>(object + 0x2C) +=
        *reinterpret_cast<float*>(object + 0x38) * speed;
    *reinterpret_cast<float*>(object + 0x28) +=
        *reinterpret_cast<float*>(object + 0x34) * speed;
    *reinterpret_cast<float*>(object + 0x3C) +=
        *reinterpret_cast<float*>(object + 0x44) * speed;
    *reinterpret_cast<float*>(object + 0x40) +=
        *reinterpret_cast<float*>(object + 0x48) * speed;
    *reinterpret_cast<int*>(object + 0x5C) = frame;
    elapsed += speed;
    frame = static_cast<int>(elapsed);
    return 0;
}
