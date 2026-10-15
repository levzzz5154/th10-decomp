// 0x004043D0: enable an object's motion pair and store its two vectors.
struct Vec3_004043d0 {
    float x, y, z;
};
struct Object_004043d0 {
    unsigned char unknown0000[0x1EEC];
    int enabled;
    Vec3_004043d0 first;
    Vec3_004043d0 second;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) void __stdcall SetVectors_004043d0(Object_004043d0* object, const Vec3_004043d0* first, const Vec3_004043d0* second) {
    object->enabled = 1;
    object->first = *first;
    object->second = *second;
}
#pragma code_seg()
