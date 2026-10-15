struct FrameInfo { void* object; FrameInfo* next; };
struct ThreadData { unsigned char padding[0x88]; FrameInfo* exceptions; };
extern "C" ThreadData* __cdecl asm_getptd_00456357();
extern "C" void __cdecl asm_inconsistency_004556e0();

extern "C" void __cdecl asm_FindAndUnlinkFrame_00462a34(FrameInfo* frame) {
    if (frame == asm_getptd_00456357()->exceptions) {
        asm_getptd_00456357()->exceptions = frame->next;
        return;
    }
    FrameInfo* current = asm_getptd_00456357()->exceptions;
    while (current->next) {
        if (frame == current->next) {
            current->next = frame->next;
            return;
        }
        current = current->next;
    }
    asm_inconsistency_004556e0();
}
