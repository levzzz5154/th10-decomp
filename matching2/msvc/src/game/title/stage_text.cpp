// 0x00434A80: (re)initialise one stage-text sprite record.

// Three consecutive floats. The record keeps four such vectors, all filled by
// StageText_Initialize: two from the object's own base position, two from the
// shared default triple at g_zero_vector3.
struct StageTextVector_00434a80 {
    float x;
    float y;
    float z;
};

// Shared default triple copied into the record's two colour/scale slots.
extern "C" StageTextVector_00434a80 g_zero_vector3;
// Default time scale; the record's +0x0AC slot points at it.
extern "C" float g_game_speed;

struct StageText_00434a80 {
    unsigned char unknown_000[0x70];
    StageTextVector_00434a80 vector_070;   // +0x070, copied from base_position
    StageTextVector_00434a80 vector_07C;   // +0x07C, copied from the caller's vector
    StageTextVector_00434a80 vector_088;   // +0x088, default triple
    StageTextVector_00434a80 vector_094;   // +0x094, default triple
    int field_0A0;                         // +0x0A0, timer reset to -1
    int field_0A4;                         // +0x0A4
    int field_0A8;                         // +0x0A8
    const float* field_0AC;                // +0x0AC, time scale
    unsigned int flags_0B0;                // +0x0B0, bit 0 marks "initialised"
    int field_0B4;                         // +0x0B4, caller-supplied mode
    unsigned int field_0B8;                // +0x0B8, caller-supplied byte
    unsigned char unknown_0BC[0x334 - 0x0BC];
    StageTextVector_00434a80 base_position; // +0x334

    __declspec(noinline) void Initialize(const StageTextVector_00434a80* base,
                                         const StageTextVector_00434a80* position,
                                         int mode, unsigned char flag);
};

#pragma code_seg(".text$01stagetext")
void StageText_00434a80::Initialize(const StageTextVector_00434a80* base,
                                    const StageTextVector_00434a80* position,
                                    int mode, unsigned char flag) {
    this->field_0B4 = mode;
    const StageTextVector_00434a80& defaults = g_zero_vector3;
    this->vector_088 = defaults;
    this->vector_094 = defaults;
    this->field_0B8 = flag;
    this->vector_070 = *base;
    this->vector_07C = *position;
    unsigned int flags = this->flags_0B0;
    if ((flags & 1) == 0) {
        this->field_0A4 = 0;
        this->field_0A0 = -999999;
        this->field_0A8 = 0;
        this->field_0AC = &g_game_speed;
        this->flags_0B0 = flags | 1;
    }
    this->field_0A4 = 0;
    this->field_0A8 = 0;
    this->field_0A0 = -1;
}
#pragma code_seg()
