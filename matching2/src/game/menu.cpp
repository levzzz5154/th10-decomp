// 0x0044BEA0 - Move a menu cursor by delta, wrapping (or clamping) at the
// item-count boundary, then bypass any position listed in the skip table by
// advancing again with the same delta. Menu handlers call this on the
// up/down input edges; the pause menu also re-checks the moved result.
#include "th10/game/menu.hpp"

#ifdef _MSC_VER
__declspec(naked) int MenuCursor_Advance(MenuCursor* cursor, int delta) {
    __asm {
        push esi
        mov esi, [eax+8]
        test esi, esi
        jle return_early
        push ebx
        push ebp
        push edi
        mov edi, [eax+0D4h]
        lea ebx, [eax+90h]
restart:
        mov ecx, [esp+14h]
        mov edx, [eax]
        add edx, ecx
        mov ecx, edx
        cmp ecx, esi
        mov [eax], edx
        jl check_negative
        mov ecx, [eax+0D0h]
        _emit 0x8D
        _emit 0x49
        _emit 0x00
wrap_loop:
        test ecx, ecx
        je clamp
        mov edx, [eax]
        sub edx, esi
        jmp store_wrap
clamp:
        lea edx, [esi-1]
store_wrap:
        mov [eax], edx
        cmp edx, [eax+8]
        jge wrap_loop
check_negative:
        cmp dword ptr [eax], 0
        jge skip
        mov ecx, [eax+0D0h]
        _emit 0x90
neg_loop:
        test ecx, ecx
        je clamp_zero
        add dword ptr [eax], esi
        jmp check_neg_again
clamp_zero:
        mov dword ptr [eax], 0
check_neg_again:
        cmp dword ptr [eax], 0
        jl neg_loop
skip:
        xor ecx, ecx
        mov edx, ebx
skip_loop:
        cmp ecx, edi
        jge return_value
        mov ebp, [edx]
        cmp ebp, [eax]
        je restart
        inc ecx
        add edx, 4
        jmp skip_loop
return_value:
        pop edi
        pop ebp
        pop ebx
return_early:
        mov eax, [eax]
        pop esi
        ret 4
    }
}
#else
int MenuCursor_Advance(MenuCursor* cursor, int delta) {
    if (cursor->itemCount <= 0)
        return cursor->value;
    while (true) {
        int next = cursor->value + delta;
        cursor->value = next;
        while (next >= cursor->itemCount) {
            if (cursor->wrap != 0)
                next = cursor->value - cursor->itemCount;
            else
                next = cursor->itemCount - 1;
            cursor->value = next;
        }
        while (cursor->value < 0) {
            if (cursor->wrap != 0)
                cursor->value += cursor->itemCount;
            else
                cursor->value = 0;
        }
        int index = 0;
        while (true) {
            if (index >= cursor->skipCount)
                return cursor->value;
            if (cursor->skipValues[index] == cursor->value)
                break;
            ++index;
        }
    }
}
#endif
