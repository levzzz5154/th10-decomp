#include "th10/render/edge_strips.hpp"

// Both fillers walk the strip two vertices at a time (0x38 bytes), first
// writing the even vertices and then the odd ones, so a strip of N
// vertices alternates between the two border edges. Retail carries the
// vertex count in EAX and the vertex base in EBX; the readable
// signatures reify both.

// 0x00444B10 - Horizontal border strip. The u coordinate starts at
// base_x + rect.right and steps toward the left edge in
// (count + 1) / 2 - 1 increments; even vertices take the top edge's v
// and odd vertices the bottom edge's v (both offset by base_y).
int32_t RenderTarget_FillHorizontalEdgeStrip(const EdgeStripSurface* surface,
                                             int32_t count,
                                             EdgeStripVertex* vertices) {
    if (count <= 2) {
        return -1;
    }
    const EdgeStripRect* rect = surface->rect;
    const float u_start = surface->base_x + rect->right;
    const float step =
        (rect->right - rect->left) / (float)((count + 1) / 2 - 1);

    float u = u_start;
    const float v_even = rect->top + surface->base_y;
    const int32_t even_count = (int32_t)(((uint32_t)(count - 1) >> 1) + 1);
    for (int32_t index = 0; index < even_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u;
        vertex->v = v_even;
        u -= step;
    }

    u = u_start;
    const float v_odd = rect->bottom + surface->base_y;
    const int32_t odd_count = (int32_t)(((uint32_t)(count - 2) >> 1) + 1);
    for (int32_t index = 0; index < odd_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2 + 1];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u;
        vertex->v = v_odd;
        u -= step;
    }
    return 0;
}

// 0x00444BE0 - Vertical border strip. The v coordinate starts at
// base_y + rect.bottom and steps toward the top edge in
// (count + 1) / 2 - 1 increments; even vertices take the left edge's u
// and odd vertices the right edge's u (both offset by base_x).
#ifdef _MSC_VER
__declspec(naked) int32_t RenderTarget_FillVerticalEdgeStripRetail() {
    __asm {
        sub esp, 8
        push esi
        mov esi, eax
        cmp esi, 3
        jge loc_444BF3
        or eax, 0FFFFFFFFh
        pop esi
        add esp, 8
        ret
loc_444BF3:
        mov eax, [ecx+394h]
        fld dword ptr [ecx+58h]
        fadd dword ptr [eax+2Ch]
        push edi
        fld dword ptr [eax+20h]
        mov edi, 3F800000h
        fadd dword ptr [ecx+54h]
        fstp dword ptr [esp+8]
        fld dword ptr [eax+2Ch]
        fsub dword ptr [eax+24h]
        lea eax, [esi+1]
        cdq
        sub eax, edx
        sar eax, 1
        dec eax
        test esi, esi
        mov [esp+0Ch], eax
        fidiv dword ptr [esp+0Ch]
        fstp dword ptr [esp+0Ch]
        fld st(0)
        jle loc_444C60
        lea edx, [esi-1]
        shr edx, 1
        lea eax, [ebx+14h]
        inc edx
        push ebp
        _emit 8Dh
        _emit 9Bh
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
loc_444C40:
        mov ebp, [esp+0Ch]
        fst dword ptr [eax+4]
        fsub dword ptr [esp+10h]
        mov [eax], ebp
        mov ebp, [ecx+2FCh]
        mov [eax-4], ebp
        mov [eax-8], edi
        add eax, 38h
        dec edx
        jnz loc_444C40
        pop ebp
loc_444C60:
        cmp esi, 1
        fstp st(0)
        mov eax, [ecx+394h]
        fld dword ptr [eax+28h]
        fadd dword ptr [ecx+54h]
        fstp dword ptr [esp+8]
        jle loc_444C9F
        lea edx, [esi-2]
        shr edx, 1
        lea eax, [ebx+30h]
        inc edx
loc_444C80:
        mov esi, [esp+8]
        fst dword ptr [eax+4]
        fsub dword ptr [esp+0Ch]
        mov [eax], esi
        mov esi, [ecx+2FCh]
        mov [eax-4], esi
        mov [eax-8], edi
        add eax, 38h
        dec edx
        jnz loc_444C80
loc_444C9F:
        pop edi
        fstp st(0)
        xor eax, eax
        pop esi
        add esp, 8
        ret
    }
}
#endif

int32_t RenderTarget_FillVerticalEdgeStrip(const EdgeStripSurface* surface,
                                           int32_t count,
                                           EdgeStripVertex* vertices) {
    if (count <= 2) {
        return -1;
    }
    const EdgeStripRect* rect = surface->rect;
    const float v_start = surface->base_y + rect->bottom;
    const float step =
        (rect->bottom - rect->top) / (float)((count + 1) / 2 - 1);

    float v = v_start;
    const float u_even = rect->left + surface->base_x;
    const int32_t even_count = (int32_t)(((uint32_t)(count - 1) >> 1) + 1);
    for (int32_t index = 0; index < even_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u_even;
        vertex->v = v;
        v -= step;
    }

    v = v_start;
    const float u_odd = rect->right + surface->base_x;
    const int32_t odd_count = (int32_t)(((uint32_t)(count - 2) >> 1) + 1);
    for (int32_t index = 0; index < odd_count; ++index) {
        EdgeStripVertex* vertex = &vertices[index * 2 + 1];
        vertex->rhw = 1.0f;
        vertex->color = surface->color;
        vertex->u = u_odd;
        vertex->v = v;
        v -= step;
    }
    return 0;
}
