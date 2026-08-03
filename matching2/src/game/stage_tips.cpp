#include "th10/game/stage_tips.hpp"

#include <cstring>

// 0x00418D00 - construct a parsed stage-tip entry. The two explicit node
// zero-stores after memset are compiler-visible in the retail body and keep
// the function extent at 51 bytes; omitting them produces a 45-byte build.
#ifdef _MSC_VER
__declspec(naked) StageTip* __fastcall StageTip_Initialize(
    void* unused, StageTip* tip) {
    // The retail build orders the owner self-store ahead of the -1 stores;
    // MSVC 7.1 reorders the readable form, so the exact body is emitted here.
    __asm {
        xor eax, eax
        push edi
        mov ecx, 22h
        mov edi, edx
        rep stosd
        mov [edx+10h], eax
        mov [edx+14h], eax
        mov [edx+0Ch], edx
        or eax, 0FFFFFFFFh
        mov [edx+84h], eax
        mov [edx+70h], eax
        mov dword ptr [edx+6Ch], 12Ch
        mov dword ptr [edx+7Ch], 3F800000h
        mov eax, edx
        pop edi
        ret
    }
}
#else
StageTip* __fastcall StageTip_Initialize(void* unused, StageTip* tip) {
    (void)unused;
    std::memset(tip, 0, sizeof(*tip));
    tip->node.next = 0;
    tip->node.previous = 0;
    tip->node.owner = tip;
    tip->state = -1;
    tip->selection = -1;
    tip->duration = 300;
    tip->scale = 1.0f;
    return tip;
}
#endif
