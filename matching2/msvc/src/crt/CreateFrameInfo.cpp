struct FrameInfo { void* object; FrameInfo* next; };
struct ThreadData { unsigned char padding[0x88]; FrameInfo* exceptions; };
extern "C" ThreadData* __cdecl crt_getptd();

extern "C" FrameInfo* __cdecl crt_CreateFrameInfo(FrameInfo* frame, void* object) {
    frame->object = object;
    frame->next = crt_getptd()->exceptions;
    crt_getptd()->exceptions = frame;
    return frame;
}
