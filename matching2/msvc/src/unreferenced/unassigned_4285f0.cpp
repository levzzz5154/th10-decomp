// 0x004285F0 - the two corners of an axis-aligned box centred on this vector,
// given the box size.  Retail's x87 body is, in order,
//
//     D9 00        fld  dword ptr [eax]        ; size->x
//     D8 0D ..     fmul dword ptr [0x470B0C]   ; * 0.5f
//     D8 29        fsubr dword ptr [ecx]       ; centre.x - half
//     D9 1E        fstp dword ptr [esi]        ; min->x
//     ...          (same for y, then the two adds into edx)
//     C3           ret
//
// The shared 0.5f pool slot at 0x470B0C is the literal every other function
// in the image uses.  The size arrives in EAX, the centred receiver in ECX,
// the minimum in ESI and the maximum in EDX, so the model is compiled as a
// native-LTCG cluster.
#pragma code_seg(".text$01bounds")
struct Vector2 {
    float x;
    float y;

    __declspec(noinline) void GetBounds(const Vector2* size, Vector2* min, Vector2* max) const;
};

void Vector2::GetBounds(const Vector2* size, Vector2* min, Vector2* max) const {
    min->x = x - size->x * 0.5f;
    min->y = y - size->y * 0.5f;
    max->x = x + size->x * 0.5f;
    max->y = y + size->y * 0.5f;
}
#pragma code_seg()
