// 0x0043E5A0 (356 bytes): configure one animation object from an archive
// resource record.

struct Resource_0043e5a0 {
    unsigned char reserved[0x200];
};

struct Matrix4x4_0043e5a0 {
    float values[4][4];

    __forceinline void SetIdentity();
};

struct AnimationObject_0043e5a0 {
    unsigned char reserved_0000[0x04C];
    float width;                                       // +0x04C
    float height;                                      // +0x050
    unsigned char reserved_054[0x23C - 0x054];
    Matrix4x4_0043e5a0 block_a;                        // +0x23C
    Matrix4x4_0043e5a0 block_copy;                     // +0x27C
    Matrix4x4_0043e5a0 block_b;                        // +0x2BC
    unsigned char reserved_2fc[0x308 - 0x2FC];
    Resource_0043e5a0* resource;                       // +0x308
    unsigned char reserved_30c[0x384 - 0x30C];
    unsigned short record_index;                       // +0x384
    unsigned char reserved_386[0x394 - 0x386];
    unsigned char* record;                             // +0x394

    __declspec(noinline) int ConfigureFromResource(Resource_0043e5a0* resource,
                                                   int index);
};

__forceinline void Matrix4x4_0043e5a0::SetIdentity() {
    values[3][2] = 0.0f;
    values[3][1] = 0.0f;
    values[3][0] = 0.0f;
    values[2][3] = 0.0f;
    values[2][1] = 0.0f;
    values[2][0] = 0.0f;
    values[1][3] = 0.0f;
    values[1][2] = 0.0f;
    values[1][0] = 0.0f;
    values[0][3] = 0.0f;
    values[0][2] = 0.0f;
    values[0][1] = 0.0f;
    values[3][3] = 1.0f;
    values[2][2] = 1.0f;
    values[1][1] = 1.0f;
    values[0][0] = 1.0f;
}

#pragma code_seg(".text$01configure")
__declspec(noinline) int AnimationObject_0043e5a0::ConfigureFromResource(
    Resource_0043e5a0* resource, int index) {
    unsigned char* res = reinterpret_cast<unsigned char*>(resource);
    if (*reinterpret_cast<void**>(res + 0x108) == 0 ||
        *reinterpret_cast<unsigned int*>(res + 0x124) != 0)
        return -1;

    this->record_index = static_cast<unsigned short>(index);
    this->resource = resource;
    this->record = *reinterpret_cast<unsigned char**>(res + 0x118) + index * 0x44;
    this->width = *reinterpret_cast<float*>(this->record + 0x34);
    this->height = *reinterpret_cast<float*>(this->record + 0x30);
    this->block_a.SetIdentity();
    this->block_b.SetIdentity();
    unsigned char* rec = this->record;
    this->block_a.values[0][0] = this->width * 0.00390625f;
    this->block_a.values[1][1] = this->height * 0.00390625f;
    this->block_b.values[0][0] =
        (*reinterpret_cast<float*>(rec + 0x38) /
         *reinterpret_cast<float*>(rec + 0x1C)) * this->width;
    this->block_b.values[1][1] =
        (*reinterpret_cast<float*>(rec + 0x3C) /
         *reinterpret_cast<float*>(rec + 0x18)) * this->height;
    this->block_copy = this->block_a;
    return 0;
}
#pragma code_seg()
