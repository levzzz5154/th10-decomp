struct FrameInfo { void* object; FrameInfo* next; };
struct ThreadData { unsigned char padding[0x88]; FrameInfo* exceptions; };
extern "C" ThreadData* __cdecl crt_getptd();
extern "C" void __cdecl crt_inconsistency();

extern "C" void __cdecl crt_FindAndUnlinkFrame(FrameInfo* frame) {
    if (frame == crt_getptd()->exceptions) {
        crt_getptd()->exceptions = frame->next;
        return;
    }
    FrameInfo* current = crt_getptd()->exceptions;
    while (current->next) {
        if (frame == current->next) {
            current->next = frame->next;
            return;
        }
        current = current->next;
    }
    crt_inconsistency();
}
