// 0x00450690..0x004506CF: ?ECL_PushScratchValue@@
// Reserve `size` bytes of the interpreter's scratch stack and hand the new
// frame base back. The frame rides in a buffer that starts at the object's own
// address, with the stack pointer at +0x1000 and the frame base at +0x1004;
// the previous frame base is pushed onto the buffer before the frame base
// moves to the old stack pointer. The frame arrives in EAX and the byte count
// in ECX, a convention only a native LTCG link chooses, so this region is
// compiled as a cluster.

struct EclFrame_00450690 {
    unsigned char scratch[0x1000];  // +0x0000
    int sp;                         // +0x1000
    int frame_base;                 // +0x1004
    __declspec(noinline) int Push(int size);
};
typedef char EclFrame_00450690_size_must_fit[sizeof(EclFrame_00450690) == 0x1008 ? 1 : -1];

#pragma code_seg(".text$01push")
int EclFrame_00450690::Push(int size) {
    int old = sp;
    int next = old + size;
    if (next >= 0x1000) {
        return -1;
    }
    sp = next;
    if (next + 4 < 0x1000) {
        *(int*)(scratch + next) = frame_base;
        sp = sp + 4;
    }
    frame_base = old;
    return 0;
}
#pragma code_seg()
