// Compiler context only; none of these bytes enter the image.
#include "../../../src/core/sprtanim/animation_start_byte_interpolation.cpp"

#pragma code_seg(".text$09context")
extern "C" int __stdcall AnimationStartByteInterpolationContext_00441f50(
        AnimationInterpolatedObject** objects, const unsigned char* bytes, int count) {
    for (int i = 0; i < count; ++i) {
        objects[i]->StartChannel108(count - i, bytes[i], bytes[i + 1], bytes[i + 2]);
        objects[i]->StartChannel208(count - i, bytes[i], bytes[i + 1], bytes[i + 2]);
        objects[i]->StartColor1BC(bytes + i, bytes + count, count - i, bytes[i + 3]);
        objects[i]->StartColor0BC(bytes + i, bytes + count, count - i, bytes[i + 3]);
    }
    return count;
}
#pragma code_seg()
