#include "th10/render/animation_manager.hpp"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

uint32_t Ptr32(const void* pointer) {
    return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(pointer));
}

uint32_t& Word(unsigned char* bytes, unsigned int offset) {
    return *reinterpret_cast<uint32_t*>(bytes + offset);
}

float& Float(unsigned char* bytes, unsigned int offset) {
    return *reinterpret_cast<float*>(bytes + offset);
}

}  // namespace

int main() {
    unsigned char object[0x3AC] = {};
    unsigned char resource[0x130] = {};
    float sprite[17] = {};
    uint32_t texture_words[4] = {};
    unsigned char image[1] = {1};

    Word(resource, 0x108) = Ptr32(image);
    Word(resource, 0x118) = Ptr32(sprite);
    Word(resource, 0x124) = 0;
    Word(reinterpret_cast<unsigned char*>(sprite), 0x04) =
        Ptr32(texture_words);
    Float(reinterpret_cast<unsigned char*>(sprite), 0x18) = 64.0f;
    Float(reinterpret_cast<unsigned char*>(sprite), 0x1C) = 64.0f;
    Float(reinterpret_cast<unsigned char*>(sprite), 0x30) = 16.0f;
    Float(reinterpret_cast<unsigned char*>(sprite), 0x34) = 16.0f;
    Float(reinterpret_cast<unsigned char*>(sprite), 0x38) = 32.0f;
    Float(reinterpret_cast<unsigned char*>(sprite), 0x3C) = 32.0f;
    texture_words[0] = 0x12345678u;

    assert(AnimationObject_ConfigureFromResource(object, resource, 0) == 0);
    assert(Word(object, 0x308) == Ptr32(resource));
    assert(Word(object, 0x394) == Ptr32(sprite));
    assert(Float(object, 0x4C) == 16.0f);
    assert(Float(object, 0x50) == 16.0f);
    assert(Word(object, 0x35C) == 0);

    unsigned char* first_object = object;
    assert(AnimationObject_ConfigureFromResource(object, resource, 0) == 0);
    assert(object == first_object);
    assert(Word(object, 0x394) == Ptr32(sprite));
    std::printf("TITLE_ANM_MANAGER_BRIDGE_PASS\n");
    return 0;
}
