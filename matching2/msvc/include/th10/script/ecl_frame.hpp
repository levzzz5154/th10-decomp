#pragma once

// The interpreter's scratch stack: a buffer that starts at the object's own
// address, with the stack pointer at +0x1000 and the frame base at +0x1004.
struct EclFrame_00450690 {
    unsigned char scratch[0x1000];  // +0x0000
    int sp;                         // +0x1000
    int frame_base;                 // +0x1004

    __declspec(noinline) int Push(int size);
    __declspec(noinline) int Pop();
};
typedef char EclFrame_00450690_size_must_fit[sizeof(EclFrame_00450690) == 0x1008 ? 1 : -1];
