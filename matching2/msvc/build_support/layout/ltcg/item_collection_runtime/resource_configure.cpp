// 0x0043E5A0 (356 bytes): configure one animation object from an archive
// resource record.

#include "th10/render/animation_object_0043e5a0.hpp"

#pragma code_seg(".text$f0043e5a0F")
__declspec(noinline) int Resource_0043e5a0::ConfigureObject(
    AnimationObject_0043e5a0* object, int index) {
    unsigned char* res = reinterpret_cast<unsigned char*>(this);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;

    object->record_index = static_cast<unsigned short>(index);
    object->resource = this;
    object->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    object->width = *reinterpret_cast<float*>(object->record + 0x34);
    object->height = *reinterpret_cast<float*>(object->record + 0x30);
    object->block_a.SetIdentity();
    object->block_b.SetIdentity();
    unsigned char* rec = object->record;
    object->block_a.values[0][0] = object->width * 0.00390625f;
    object->block_a.values[1][1] = object->height * 0.00390625f;
    object->block_b.values[0][0] =
        (*reinterpret_cast<float*>(rec + 0x38) /
         *reinterpret_cast<float*>(rec + 0x1C)) * object->width;
    object->block_b.values[1][1] =
        (*reinterpret_cast<float*>(rec + 0x3C) /
         *reinterpret_cast<float*>(rec + 0x18)) * object->height;
    object->block_copy = object->block_a;
    return 0;
}
#pragma code_seg()
