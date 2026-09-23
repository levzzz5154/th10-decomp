// Shared view of the ECL interpreter's scratch frame used by 0x00450690 and
// 0x004506D0. The interpreter passes &vm->frame in EAX at both entries.
#ifndef TH10_SCRIPT_ECL_SCRATCH_FRAME_00450690_HPP
#define TH10_SCRIPT_ECL_SCRATCH_FRAME_00450690_HPP

struct EclFrame_00450690 {
    unsigned char scratch[0x1000]; // +0x0000
    int sp;                        // +0x1000
    int frame_base;                // +0x1004

    __declspec(noinline) int Push(int size);
    __declspec(noinline) int PopScratchValue();
};

typedef char EclFrame_00450690_size_must_fit[
    sizeof(EclFrame_00450690) == 0x1008 ? 1 : -1];

#endif
