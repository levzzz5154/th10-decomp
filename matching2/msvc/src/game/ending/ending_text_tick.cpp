// 0x0040BD20..0x0040BD7C: EndingText_Tick
//
// The state this runs on is the ending/credits script object constructed at
// 0x0040BA90. At +0x04 it carries the FrameTimer shape shared by the whole
// image: a previous/current integer pair (+0x04/+0x08), an elapsed float
// (+0x0C) and a pointer (+0x10) to the shared game speed. Retail, in order:
//
//     push esi                 ; the state arrives in ESI; the push is the
//     call 0x0040BD80          ; argument to the finished? query, which pops it
//     test eax,eax / je
//     mov eax,1 / ret          ; finished -> report 1
//     mov edx,[esi+8]          ; current
//     mov ecx,[esi+10h]        ; speed
//     mov [esi+4],edx          ; previous = current
//     ...
//     xor eax,eax / ret        ; still running -> 0
//
// The timer body at +0x04 is the usual frame tick: at normal speed it advances
// the frame counter and adds 1.0 to the elapsed field, otherwise it converts
// the elapsed accumulation of the speed pointer into the new counter.

extern float g_frame_timer_normal_lower;  // 0x00470B68
extern float g_frame_timer_normal_upper;  // 0x00470B64

extern "C" int __stdcall asm_FUN_0040bd80_0040bd80(void* state);

struct EndingTextTickView {
    int pad_00;             // +0x00
    int previous;           // +0x04
    int current;            // +0x08
    float elapsed;          // +0x0C
    const float* speed;     // +0x10
};

#pragma code_seg(".text$01tick")
__declspec(noinline) int __stdcall EndingText_Tick(EndingTextTickView* state) {
    if (asm_FUN_0040bd80_0040bd80(state))
        return 1;

    state->previous = state->current;
    if (*state->speed > g_frame_timer_normal_lower &&
        *state->speed < g_frame_timer_normal_upper) {
        ++state->current;
        state->elapsed += 1.0f;
    } else {
        state->current = int(state->elapsed += *state->speed);
    }
    return 0;
}
#pragma code_seg()
