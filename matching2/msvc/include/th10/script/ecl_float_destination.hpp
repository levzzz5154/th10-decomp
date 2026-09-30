#pragma once

// ECL VM view used by the variable lookups at 0x00450030 (integer) and
// 0x00450070 (float) and the forwarders that reach them.

struct EclVarTable_00450070 {
    unsigned char pad_000[8];
    unsigned short valid_mask;  // +0x0008
    unsigned char pad_00a[6];
    union {                     // +0x0010: one slot per variable index
        float displacements[1]; // float variables
        int offsets[1];         // integer variables
    };
};

struct EclValueOwner_00450070 {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual int* ResolveExternalInt(int offset);
    virtual void Reserved3();
    virtual float* ResolveExternalFloat(int displacement);
};

struct EclFrame_00450070 {
    unsigned char pad_000[0x1004];
    int frame_base;                 // +0x1004
    unsigned char pad_1008[4];
    EclValueOwner_00450070* owner;  // +0x100C
};

struct EclVm_00450070 {
    void* field_000;
    EclVarTable_00450070* table;  // +0x0004
    EclFrame_00450070 frame;      // +0x0008
    __declspec(noinline) int* ResolveIntDestination(int index);
    __declspec(noinline) float* ResolveFloatDestination(int index);
};
