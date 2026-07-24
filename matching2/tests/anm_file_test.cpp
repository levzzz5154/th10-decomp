#include "th10/render/anm_file.hpp"

#include <cassert>
#include <cstring>

namespace {

void Write32(unsigned char* bytes, unsigned int value) {
    bytes[0] = static_cast<unsigned char>(value);
    bytes[1] = static_cast<unsigned char>(value >> 8);
    bytes[2] = static_cast<unsigned char>(value >> 16);
    bytes[3] = static_cast<unsigned char>(value >> 24);
}

void WriteFloat(unsigned char* bytes, float value) {
    unsigned int bits;
    std::memcpy(&bits, &value, sizeof(bits));
    Write32(bytes, bits);
}

} // namespace

int main() {
    unsigned char image[0xC0] = {};
    Write32(image + 0x00, 1);
    Write32(image + 0x04, 1);
    Write32(image + 0x0C, 64);
    Write32(image + 0x10, 16);
    Write32(image + 0x14, 5);
    Write32(image + 0x30, 0x90);
    Write32(image + 0x40, 0x60);
    Write32(image + 0x44, 88);
    Write32(image + 0x48, 0x78);
    Write32(image + 0x60, 7);
    WriteFloat(image + 0x64, 1.0f);
    WriteFloat(image + 0x68, 2.0f);
    WriteFloat(image + 0x6C, 32.0f);
    WriteFloat(image + 0x70, 8.0f);
    image[0x78] = 3;
    image[0x7A] = 8;
    Write32(image + 0x90, 0x58544854u);
    image[0x96] = 5;
    image[0x98] = 64;
    image[0x9A] = 16;
    Write32(image + 0x9C, 0x20);

    AnmFileEntry entry;
    assert(AnmFile_ParseEntry(image, sizeof(image), 0, &entry));
    assert(entry.sprite_count == 1 && entry.script_count == 1);
    AnmFileSprite sprite;
    assert(AnmFile_GetSprite(&entry, 0, &sprite));
    assert(sprite.id == 7 && sprite.x == 1.0f && sprite.height == 8.0f);
    AnmFileEntry global_entry;
    assert(AnmFile_FindGlobalSprite(image, sizeof(image), 0, &global_entry,
                                    &sprite));
    AnmFileScript script;
    assert(AnmFile_FindScript(&entry, 88, &script));
    assert(script.instructions == image + 0x78);
    AnmTexturePayload texture;
    assert(AnmFile_GetTexture(&entry, &texture));
    assert(texture.format == 5 && texture.width == 64 &&
           texture.height == 16 && texture.data_size == 0x20);
    assert(AnmFile_FindGlobalScript(image, sizeof(image), 0, &global_entry,
                                    &script));
    assert(script.id == 88);
    return 0;
}
