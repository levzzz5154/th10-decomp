struct FrameInfo { void* object; FrameInfo* next; };
struct ThreadData { unsigned char padding[0x88]; FrameInfo* exceptions; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();

extern "C" FrameInfo* __cdecl asm_CreateFrameInfo_004629eb(FrameInfo* frame, void* object) {
    frame->object = object;
    frame->next = asm_getptd_00456357()->exceptions;
    asm_getptd_00456357()->exceptions = frame;
    return frame;
}
