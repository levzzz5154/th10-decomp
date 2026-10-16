// 0x004043D0: enable an object's motion pair and store its two vectors.
struct Vec34 {
    float x, y, z;
};
struct Object {
    unsigned char unknown0000[0x1EEC];
    int enabled;
    Vec34 first;
    Vec34 second;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall SetVectors(Object* object, const Vec34* first, const Vec34* second) {
    object->enabled = 1;
    object->first = *first;
    object->second = *second;
}
#pragma code_seg()
