// 0x00412A10..0x00412A5A: hand back where the integer variable selected by
// the index in CL lives. The variable table marks the live slots with a
// 16-bit mask; a slot's displacement is either a non-negative offset into the
// interpreter's pooled frame or a negative one the value owner resolves. The
// interpreter arrives in EAX and the index in ECX, a convention only a native
// LTCG link chooses, so this region is compiled as a cluster.

struct EclVarTable {
    unsigned char pad_000[8];
    unsigned short valid_mask;  // +0x0008
    unsigned char pad_00a[6];
    int offsets[1];             // +0x0010
};

struct EclValueOwner {
    virtual void Reserved0();
    virtual void Reserved1();
    virtual int* Resolve(int displacement);
};

struct EclFrame2 {
    unsigned char pad_000[0x1004];
    int frame_base;                 // +0x1004
    unsigned char pad_1008[4];
    EclValueOwner* owner;  // +0x100C
};

struct EclVm2 {
    void* field_000;
    EclVarTable* table;  // +0x0004
    EclFrame2 frame;      // +0x0008
};

struct EclHandle {
    void* field_000;
    EclVm2* vm;  // +0x0004
};

struct EclInterpreter2 {
    unsigned char pad_000[0x14D8];
    EclHandle* handle;  // +0x14D8
    __declspec(noinline) int* ResolveIntDestination(int index);
};

#pragma code_seg(".text$01resolve")
int* EclInterpreter2::ResolveIntDestination(int index) {
    EclVm2* vm = handle->vm;
    EclVarTable* table = vm->table;
    if (table->valid_mask & (1 << index)) {
        const int& displacement = table->offsets[index];
        if (displacement >= 0) {
            EclFrame2* frame = &vm->frame;
            return (int*)((char*)frame + frame->frame_base + displacement);
        }
        return vm->frame.owner->Resolve(displacement);
    }
    return 0;
}
#pragma code_seg()
