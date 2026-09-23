// 0x004187F0..0x0041880C: translate a 3D point into the playfield coordinate
// frame. The retail body adds (224, 16) to x/y and preserves z.
//
// This is a semantic C++ model for the unreferenced fragment. The proposed
// native-LTCG member-return ABI is this/source in ECX and the aggregate result
// buffer in EAX; exact code generation has not been verified.
struct Vector3_004187F0 {
    float x;
    float y;
    float z;

    __declspec(noinline) Vector3_004187F0 Translate() const;
};

#pragma code_seg(".text$01translate_187f0")
Vector3_004187F0 Vector3_004187F0::Translate() const {
    Vector3_004187F0 translated;
    translated.x = x + 224.0f;
    translated.y = y + 16.0f;
    translated.z = z;
    return translated;
}
#pragma code_seg()
