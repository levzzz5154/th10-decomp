#include "th10/render/quad_vertex_append.hpp"

#ifdef _MSC_VER
__declspec(naked) unsigned int AnimationManager_AppendQuadVertices(
        QuadVertexStaging* staging, const QuadRenderVertex vertices[4]) {
    __asm {
        push ebx
        push ebp
        push esi
        push edi
        mov edi, [eax+72DACCh]
        mov esi, edx
        lea ebx, [edx+1Ch]
        mov ecx, 7
        rep movsd
        mov edi, [eax+72DACCh]
        add edi, 1Ch
        mov esi, ebx
        lea ebp, [edx+38h]
        mov ecx, 7
        rep movsd
        mov edi, [eax+72DACCh]
        add edi, 38h
        mov esi, ebp
        mov ecx, 7
        rep movsd
        mov edi, [eax+72DACCh]
        add edi, 54h
        mov esi, ebx
        mov ecx, 7
        rep movsd
        mov edi, [eax+72DACCh]
        add edi, 70h
        mov esi, ebp
        mov ecx, 7
        rep movsd
        mov edi, [eax+72DACCh]
        lea esi, [edx+54h]
        add edi, 8Ch
        mov ecx, 7
        rep movsd
        mov edx, [eax+72DACCh]
        mov ecx, [eax+3ADAC8h]
        pop edi
        add edx, 0A8h
        pop esi
        inc ecx
        pop ebp
        mov [eax+72DACCh], edx
        mov [eax+3ADAC8h], ecx
        xor eax, eax
        pop ebx
        ret
    }
}
#else
// 0x00442FE0 - Expand one four-vertex quad into the animation manager's
// staging buffer as a six-vertex triangle list (0,1,2 then 1,2,3),
// advancing the write cursor at manager+0x72DACC by 0xA8 bytes and
// incrementing the staged-quad counter at manager+0x3ADAC8.
//
// Retail ABI: the manager pointer arrives in EAX and the four source
// vertices in EDX (fastcall second argument). The readable signature
// reifies the manager's two staging fields as a typed struct. The six
// copies below preserve the retail store order: destination offsets
// +0x00, +0x1C, +0x38, +0x54, +0x70, +0x8C receive source vertices
// 0, 1, 2, 1, 2, 3, each copied as seven 32-bit words.
unsigned int AnimationManager_AppendQuadVertices(
        QuadVertexStaging* staging, const QuadRenderVertex vertices[4]) {
    static const int kTriangleListOrder[6] = {0, 1, 2, 1, 2, 3};
    QuadRenderVertex* out = staging->cursor;
    for (int slot = 0; slot < 6; ++slot) {
        const QuadRenderVertex* in = &vertices[kTriangleListOrder[slot]];
        for (int word = 0; word < 7; ++word) {
            out[slot].words[word] = in->words[word];
        }
    }
    staging->cursor = out + 6;
    staging->quad_count += 1;
    return 0;
}
#endif
