// Readable reconstruction of the retail 16-bit linear-congruential generator.
// Every step transforms the state through ((seed ^ 0x9630) - 0x6553) followed
// by a multiply-and-fold step (value * 4 + (value >> 14)), all modulo 2^16.
// Callers pass the global state at 0x004918B0 explicitly; the animation
// interpreter (0x0043EE30), enemy-script helpers, and gameplay leaves share it.
#include "th10/math/rng.hpp"

extern float _DAT_00470b98;  // 2^32, added by the x87 unsigned-conversion path
extern float _DAT_00470bec;  // 2^-31
extern float _DAT_00470bf0;  // 2^-32
extern float _DAT_00470afc;  // 1.0f

#ifdef _MSC_VER
extern "C" float flt_470B98;
extern "C" float flt_470BF0;
extern "C" float flt_470BEC;
extern "C" float flt_470AFC;
extern "C" unsigned long ___security_cookie;
extern "C" void __stdcall security_check_cookie(unsigned long);
#endif

namespace {

// One 16-bit LCG step shared by all four retail entry points.
uint32_t Rng_Step(uint32_t value) {
    value = ((value ^ 0x9630u) - 0x6553u) & 0xFFFFu;
    return (value * 4u + (value >> 0x0E)) & 0xFFFFu;
}

// Retail converts the 32-bit result through the x87 signed-integer load:
// negative values gain 2^32, producing an exact unsigned conversion before
// the power-of-two scale. Computing in double reproduces the single final
// rounding of the FPU store.
double Rng_ToUnsignedDouble(uint32_t value) {
    double wide = (double)(int32_t)value;
    if ((int32_t)value < 0)
        wide += _DAT_00470b98;
    return wide;
}

} // namespace

// 0x0044B9E0 - Advance the generator twice and return both 16-bit outputs
// packed as (first << 16) | second. The generation counter increases by 2.
#ifdef _MSC_VER
__declspec(naked) uint32_t Rng_NextU32(RngState* state) {
    __asm {
        xor eax, eax
        mov ax, [ecx]
        xor ax, 9630h
        xor edx, edx
        push esi
        xor esi, esi
        sub eax, 6553h
        mov dx, ax
        shl eax, 2
        shr dx, 0Eh
        add edx, eax
        mov eax, edx
        xor eax, 9630h
        sub eax, 6553h
        mov si, ax
        shr si, 0Eh
        shl eax, 2
        mov [ecx], dx
        add esi, eax
        add dword ptr [ecx+4], 2
        mov [ecx], si
        movzx eax, dx
        movzx ecx, si
        shl eax, 10h
        or eax, ecx
        pop esi
        ret
    }
}
#else
uint32_t Rng_NextU32(RngState* state) {
    uint32_t first = Rng_Step(state->seed);
    uint32_t second = Rng_Step(first);
    state->seed = (uint16_t)second;
    state->generation += 2;
    return (first << 16) | second;
}
#endif

// 0x0044BA80 - Advance the generator four times but return only the first
// pair of outputs. Equivalent to calling Rng_NextU32 twice and keeping the
// first result; retail bumps the generation counter by 4. No retail caller
// remains, so this documents the complete generator family.
#ifdef _MSC_VER
__declspec(naked) uint32_t Rng_NextU32DoubleStep(RngState* state) {
    __asm {
        sub esp, 0Ch
        mov eax, ___security_cookie
        xor eax, esp
        mov [esp+8], eax
        xor eax, eax
        mov ax, [ecx]
        xor ax, 9630h
        xor edx, edx
        sub eax, 6553h
        mov dx, ax
        shl eax, 2
        shr dx, 0Eh
        add eax, edx
        mov [ecx], ax
        mov word ptr [esp], ax
        xor eax, 9630h
        sub eax, 6553h
        xor edx, edx
        mov dx, ax
        shr dx, 0Eh
        shl eax, 2
        add eax, edx
        mov [ecx], ax
        mov word ptr [esp+2], ax
        xor eax, 9630h
        sub eax, 6553h
        mov edx, eax
        xor eax, eax
        mov ax, dx
        shr ax, 0Eh
        shl edx, 2
        add eax, edx
        xor eax, 9630h
        sub eax, 6553h
        xor edx, edx
        mov dx, ax
        shr dx, 0Eh
        shl eax, 2
        add edx, eax
        add dword ptr [ecx+4], 4
        mov eax, [esp]
        mov [ecx], dx
        mov ecx, [esp+8]
        xor ecx, esp
        add esp, 0Ch
        jmp security_check_cookie
    }
}
#else
uint32_t Rng_NextU32DoubleStep(RngState* state) {
    uint32_t first = Rng_Step(state->seed);
    uint32_t second = Rng_Step(first);
    uint32_t third = Rng_Step(second);
    uint32_t fourth = Rng_Step(third);
    state->seed = (uint16_t)fourth;
    state->generation += 4;
    return (first << 16) | second;
}
#endif

// 0x0044BB20 - Uniform float in [0, 1) from the next 32-bit output.
#ifdef _MSC_VER
__declspec(naked) float Rng_NextFloat(RngState* state) {
    __asm {
        push ecx
        xor eax, eax
        mov ax, [ecx]
        xor ax, 9630h
        xor edx, edx
        push esi
        xor esi, esi
        sub eax, 6553h
        mov dx, ax
        shr dx, 0Eh
        shl eax, 2
        add edx, eax
        mov eax, edx
        xor eax, 9630h
        sub eax, 6553h
        mov si, ax
        shr si, 0Eh
        shl eax, 2
        mov [ecx], dx
        add eax, esi
        mov esi, [ecx+4]
        add esi, 2
        mov [ecx], ax
        mov [ecx+4], esi
        movzx ecx, dx
        movzx edx, ax
        shl ecx, 10h
        or ecx, edx
        test ecx, ecx
        mov [esp+8-4], ecx
        fild dword ptr [esp+8-4]
        jge loc_44BB84
        fadd dword ptr [flt_470B98]
loc_44BB84:
        fmul dword ptr [flt_470BF0]
        pop esi
        pop ecx
        ret
    }
}
#else
float Rng_NextFloat(RngState* state) {
    return (float)(Rng_ToUnsignedDouble(Rng_NextU32(state)) * _DAT_00470bf0);
}
#endif

// 0x0044BB90 - Uniform float in [-1, 1) from the next 32-bit output.
#ifdef _MSC_VER
__declspec(naked) float Rng_NextFloatSigned(RngState* state) {
    __asm {
        push ecx
        xor eax, eax
        mov ax, [ecx]
        xor ax, 9630h
        xor edx, edx
        push esi
        xor esi, esi
        sub eax, 6553h
        mov dx, ax
        shr dx, 0Eh
        shl eax, 2
        add edx, eax
        mov eax, edx
        xor eax, 9630h
        sub eax, 6553h
        mov si, ax
        shr si, 0Eh
        shl eax, 2
        mov [ecx], dx
        add eax, esi
        mov esi, [ecx+4]
        add esi, 2
        mov [ecx], ax
        mov [ecx+4], esi
        movzx ecx, dx
        movzx edx, ax
        shl ecx, 10h
        or ecx, edx
        test ecx, ecx
        mov [esp+8-4], ecx
        fild dword ptr [esp+8-4]
        jge loc_44BBF4
        fadd dword ptr [flt_470B98]
loc_44BBF4:
        fmul dword ptr [flt_470BEC]
        pop esi
        fsub dword ptr [flt_470AFC]
        pop ecx
        ret
    }
}
#else
float Rng_NextFloatSigned(RngState* state) {
    return (float)(Rng_ToUnsignedDouble(Rng_NextU32(state)) * _DAT_00470bec -
                   _DAT_00470afc);
}
#endif
