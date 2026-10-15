// Out-of-line copies of small object methods whose receiver arrives in EAX.
// Each reads the object at the head of its entry state and takes no argument in
// a declaration-visible register, which only the native /LTCG pass chooses, so
// the family is compiled as one cluster (see build_support/layout/ltcg/unassigned_members_b_0044.json).
#include <math.h>

extern "C" void (__stdcall* data_00466130)(void*);

struct UnassignedData_0044bff0 {
    unsigned char pad_000[0x0C];
    float* value_00c;  // +0x000C
    __declspec(noinline) float Value() const;
};

struct UnassignedScale_0044c5f0 {
    float value_000;  // +0x0000
    __declspec(noinline) float Scaled(float scale) const;
};

struct UnassignedList_00449a50 {
    unsigned int flags_000;   // +0x0000
    unsigned int flags_004;   // +0x0004
    unsigned int field_008;   // +0x0008
    unsigned int field_00c;   // +0x000C
    unsigned int field_010;   // +0x0010
    UnassignedList_00449a50* self_014;  // +0x0014
    unsigned int field_018;   // +0x0018
    unsigned int field_01c;   // +0x001C
    __declspec(noinline) void Reset();
};

struct UnassignedVector_004452a0 {
    float x;  // +0x0000
    float y;  // +0x0004
    float z;  // +0x0008
    __declspec(noinline) float Length() const;
};

struct UnassignedSpan_00443680 {
    float x;  // +0x0000
    float y;  // +0x0004
    __declspec(noinline) void Transform(float a, float b, float c, float d, float e, float f);
};

struct UnassignedRecord_0044c6e0 {
    unsigned int field_000;  // +0x0000 .. +0x003C
    unsigned int field_004;
    unsigned int field_008;
    unsigned int field_00c;
    unsigned int field_010;
    unsigned int field_014;
    unsigned int field_018;
    unsigned int field_01c;
    unsigned int field_020;
    unsigned int field_024;
    unsigned int field_028;
    unsigned int field_02c;
    unsigned int field_030;
    unsigned int field_034;
    unsigned int field_038;
    unsigned int field_03c;
    __declspec(noinline) void Set(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3,
                                  unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7,
                                  unsigned int a8, unsigned int a9, unsigned int a10, unsigned int a11,
                                  unsigned int a12, unsigned int a13, unsigned int a14, unsigned int a15);
};

struct UnassignedClear_0044dbb0 {
    unsigned int field_000;              // +0x0000
    unsigned char pad_004[0x28];
    unsigned int field_02c;              // +0x002C
    unsigned char pad_030[0x4C];
    unsigned int field_07c;              // +0x007C
    unsigned char pad_080[0x10];
    unsigned int field_090;              // +0x0090
    __declspec(noinline) void Clear();
};

struct UnassignedHandle_0044c240 {
    unsigned char pad_000[4];
    void* handle_004;  // +0x0004
    __declspec(noinline) void Close();
};

struct UnassignedChain_0044c6b0 {
    unsigned int key_000;                    // +0x0000
    UnassignedChain_0044c6b0* next_004;      // +0x0004
    __declspec(noinline) UnassignedChain_0044c6b0* Find(unsigned int key);
};

struct UnassignedSeat_0044c6d0 {
    unsigned char pad_000[8];
    unsigned int field_008;  // +0x0008
    unsigned int field_00c;  // +0x000C
    unsigned int field_010;  // +0x0010
    __declspec(noinline) void Bind(unsigned int value);
};

struct UnassignedBlock_00442010 {
    unsigned char pad_000[0x10];
    unsigned int field_010;  // +0x0010
    unsigned int field_014;  // +0x0014
    unsigned int field_018;  // +0x0018
    unsigned int field_01c;  // +0x001C
    unsigned int flags_020;  // +0x0020
    __declspec(noinline) void Reset();
};

struct UnassignedBlock_004421e0 {
    unsigned char pad_000[0x30];
    unsigned int field_030;  // +0x0030
    unsigned int field_034;  // +0x0034
    unsigned int field_038;  // +0x0038
    unsigned int field_03c;  // +0x003C
    unsigned int flags_040;  // +0x0040
    __declspec(noinline) void Reset();
};
#pragma code_seg(".text$01")
void UnassignedBlock_00442010::Reset() {
    if (!(flags_020 & 1u)) {
        field_014 = 0;
        field_010 = 0xFFF0BDC1;
        field_018 = 0;
        field_01c = 0x00476F78;
        flags_020 |= 1u;
    }
    field_014 = 0;
    field_018 = 0;
    field_010 = 0xFFFFFFFF;
}
#pragma code_seg()

#pragma code_seg(".text$03")
void UnassignedBlock_004421e0::Reset() {
    if (!(flags_040 & 1u)) {
        field_034 = 0;
        field_030 = 0xFFF0BDC1;
        field_038 = 0;
        field_03c = 0x00476F78;
        flags_040 |= 1u;
    }
    field_034 = 0;
    field_038 = 0;
    field_030 = 0xFFFFFFFF;
}
#pragma code_seg()

#pragma code_seg(".text$05")
void UnassignedSpan_00443680::Transform(float a, float b, float c, float d, float e, float f) {
    x = a * d - b * c + e;
    y = a * c + b * d + f;
}
#pragma code_seg()

#pragma code_seg(".text$07")
float UnassignedVector_004452a0::Length() const {
    return sqrtf(x * x + y * y + z * z);
}
#pragma code_seg()

#pragma code_seg(".text$09")
float UnassignedData_0044bff0::Value() const {
    return *value_00c;
}
#pragma code_seg()

#pragma code_seg(".text$0B")
void UnassignedHandle_0044c240::Close() {
    void* handle = handle_004;
    if (handle != 0)
        data_00466130(handle);
}
#pragma code_seg()

#pragma code_seg(".text$0D")
float UnassignedScale_0044c5f0::Scaled(float scale) const {
    return scale * value_000;
}
#pragma code_seg()

#pragma code_seg(".text$0F")
UnassignedChain_0044c6b0* UnassignedChain_0044c6b0::Find(unsigned int key) {
    UnassignedChain_0044c6b0* node = this;
    while (node != 0) {
        if (node->key_000 == key)
            return node;
        node = node->next_004;
    }
    return 0;
}
#pragma code_seg()

#pragma code_seg(".text$11")
void UnassignedSeat_0044c6d0::Bind(unsigned int value) {
    field_008 = value;
    field_00c = 0;
    field_010 = 0;
}
#pragma code_seg()

#pragma code_seg(".text$13")
void UnassignedClear_0044dbb0::Clear() {
    field_090 = 0;
    field_000 = 0;
    field_02c = 0;
    field_07c = 0;
}
#pragma code_seg()

