// 0x00450070..0x004500CC: hand back where the float variable selected by the
// index in CL lives. The variable table marks the live slots with a 16-bit
// mask; a slot's displacement is stored as a float and is either a
// non-negative offset into the pooled frame or a negative one the value owner
// resolves through its fourth virtual. The VM arrives in EAX and the index in
// ECX, a convention only a native LTCG link chooses, so this region is
// compiled as a cluster.

struct EclVarTable_00450070 {
    unsigned char pad_000[8];
    unsigned short valid_mask;  // +0x0008
    unsigned char pad_00a[6];
    float displacements[1];     // +0x0010
};

struct EclValueOwner_00450070 {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual void Reserved2();
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
    __declspec(noinline) float* ResolveFloatDestination(int index);
};

#pragma code_seg(".text$01accessor")
float* EclVm_00450070::ResolveFloatDestination(int index) {
    if (table->valid_mask & (1 << index)) {
        const float& displacement = table->displacements[index];
        if (displacement >= 0.0f) {
            EclFrame_00450070* frame = &this->frame;
            return (float*)((char*)frame + frame->frame_base + (int)displacement);
        }
        return this->frame.owner->ResolveExternalFloat((int)displacement);
    }
    return 0;
}
#pragma code_seg()
