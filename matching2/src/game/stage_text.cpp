#include "th10/game/stage_text.hpp"

#ifdef _MSC_VER
extern "C" unsigned long dword_491C14;
extern "C" unsigned long dword_491C18;
extern "C" unsigned long dword_491C1C;
#endif

// 0x004349E0 - Advance past the current text line and all immediately
// following CR/LF bytes while maintaining the parser's remaining-byte count.
#ifdef _MSC_VER
__declspec(naked) char* StageText_SkipLine(char* cursor, int* remaining) {
    __asm {
        mov cl, [eax]
        cmp cl, 0Ah
        jz loc_4349FD
loc_4349E7:
        cmp cl, 0Dh
        jz loc_4349FD
        mov ecx, [edx]
        test ecx, ecx
        jz locret_434A1A
        inc eax
        dec ecx
        mov [edx], ecx
        mov cl, [eax]
        cmp cl, 0Ah
        jnz loc_4349E7
loc_4349FD:
        cmp dword ptr [edx], 0
        jz locret_434A1A
loc_434A02:
        mov cl, [eax]
        cmp cl, 0Ah
        jz loc_434A0E
        cmp cl, 0Dh
        jnz locret_434A1A
loc_434A0E:
        mov ecx, [edx]
        test ecx, ecx
        jz locret_434A1A
        inc eax
        dec ecx
        mov [edx], ecx
        jmp loc_434A02
locret_434A1A:
        ret
    }
}
#else
char* StageText_SkipLine(char* cursor, int* remaining) {
    while (*remaining != 0 && *cursor != '\n' && *cursor != '\r') {
        ++cursor;
        --*remaining;
    }
    while (*remaining != 0 && (*cursor == '\n' || *cursor == '\r')) {
        ++cursor;
        --*remaining;
    }
    return cursor;
}
#endif

// 0x00434A20 - Extract one line in place and consume its CR/LF terminator.
#ifdef _MSC_VER
__declspec(naked) void StageText_ExtractLine(
        char* cursor, char* destination, int* remaining) {
    __asm {
        cmp byte ptr [ecx], 0Ah
        mov eax, ecx
        jz loc_434A3B
loc_434A27:
        cmp byte ptr [eax], 0Dh
        jz loc_434A3B
        mov edx, [edi]
        test edx, edx
        jz locret_434A79
        inc eax
        dec edx
        mov [edi], edx
        cmp byte ptr [eax], 0Ah
        jnz loc_434A27
loc_434A3B:
        cmp dword ptr [edi], 0
        jz locret_434A79
        push esi
        mov esi, [esp+4+4]
        mov byte ptr [eax], 0
        sub esi, ecx
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_434A50:
        mov dl, [ecx]
        mov [esi+ecx], dl
        inc ecx
        test dl, dl
        jnz loc_434A50
        mov ecx, [edi]
        inc eax
        dec ecx
        mov [edi], ecx
        mov edx, ecx
        pop esi
loc_434A63:
        mov cl, [eax]
        cmp cl, 0Ah
        jz loc_434A6F
        cmp cl, 0Dh
        jnz locret_434A79
loc_434A6F:
        test edx, edx
        jz locret_434A79
        inc eax
        dec edx
        mov [edi], edx
        jmp loc_434A63
locret_434A79:
        ret 4
    }
}
#else
void StageText_ExtractLine(char* cursor, char* destination, int* remaining) {
    char* end = cursor;
    while (*remaining != 0 && *end != '\n' && *end != '\r') {
        ++end;
        --*remaining;
    }
    if (*remaining == 0)
        return;
    *end = 0;
    char* source = cursor;
    char* output = destination;
    while ((*output++ = *source++) != 0) {}
    --*remaining;
    while (*remaining != 0 && (*++end == '\n' || *end == '\r'))
        --*remaining;
}
#endif

// 0x00434A80 - Initialize the stage-text layout and reset its parser state.
#ifdef _MSC_VER
__declspec(naked) void StageText_Initialize(
        StageTextState* state, const float* first, const float* second,
        int resource, unsigned char mode, const float* defaults) {
    __asm {
        push esi
        mov esi, [esp+8]
        mov [eax+0B4h], esi
        push edi
        mov edi, dword_491C14
        lea esi, [eax+88h]
        mov [esi], edi
        mov edi, dword_491C18
        mov [esi+4], edi
        mov edi, dword_491C1C
        mov [esi+8], edi
        mov edi, dword_491C14
        lea esi, [eax+94h]
        mov [esi], edi
        mov edi, dword_491C18
        mov [esi+4], edi
        mov edi, dword_491C1C
        mov [esi+8], edi
        movzx esi, byte ptr [esp+10h]
        mov [eax+0B8h], esi
        mov edi, [edx]
        lea esi, [eax+70h]
        mov [esi], edi
        mov edi, [edx+4]
        mov [esi+4], edi
        mov edx, [edx+8]
        mov [esi+8], edx
        mov esi, [ecx]
        lea edx, [eax+7Ch]
        mov [edx], esi
        mov esi, [ecx+4]
        mov [edx+4], esi
        mov ecx, [ecx+8]
        mov [edx+8], ecx
        mov ecx, [eax+0B0h]
        xor edx, edx
        test cl, 1
        pop edi
        pop esi
        jne skip_init
        or ecx, 1
        mov [eax+0A4h], edx
        mov dword ptr [eax+0A0h], 0FFF0BDC1h
        mov [eax+0A8h], edx
        mov dword ptr [eax+0ACh], 476F78h
        mov [eax+0B0h], ecx
skip_init:
        mov [eax+0A4h], edx
        mov [eax+0A8h], edx
        mov dword ptr [eax+0A0h], 0FFFFFFFFh
        ret 8
    }
}
#else
void StageText_Initialize(
        StageTextState* state, const float* first, const float* second,
        int resource, unsigned char mode, const float* defaults) {
    state->resource = resource;
    state->mode = mode;
    for (int index = 0; index != 3; ++index) {
        state->first[index] = first[index];
        state->second[index] = second[index];
        state->defaults_a[index] = defaults[index];
        state->defaults_b[index] = defaults[index];
    }
    state->current = 0;
    state->length = 0;
    state->selection = -1;
}
#endif
