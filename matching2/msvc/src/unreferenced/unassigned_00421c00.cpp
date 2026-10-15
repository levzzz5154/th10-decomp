// 0x00421C00..0x00421C49: claim an unused emitter slot and store its parameters.
struct EmitterSlot_00421c00 {
    int id;                                   // +0x00, negative while free
    unsigned char reserved_004[0x2C - 0x04];
    int mode;                                 // +0x2C
    float params[7];                          // +0x30..+0x48
    __declspec(noinline) int Claim(int new_id, int new_mode, float a, float b, float c,
                                   float d, float e, float f, float g);
};

#pragma code_seg(".text$01accessor")
int EmitterSlot_00421c00::Claim(int new_id, int new_mode, float a, float b, float c,
                                float d, float e, float f, float g) {
    if (id >= 0) {
        return -1;
    }
    id = new_id;
    mode = new_mode;
    params[0] = a;
    params[1] = b;
    params[2] = c;
    params[3] = d;
    params[4] = e;
    params[5] = f;
    params[6] = g;
    return 0;
}
#pragma code_seg()
