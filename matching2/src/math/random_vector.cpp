#include "th10/math/random_vector.hpp"

#ifdef _MSC_VER
extern "C" void sub_463B2C(void);
#endif

// 0x00441E50 - Convert the current scalar animation value to the three
// repeated integer lanes consumed by the random-vector branch. The retail
// helper rounds through the x87 control word before narrowing to 32 bits.
#ifdef _MSC_VER
__declspec(naked) void RandomVector_StoreRoundedScalar(
        int output[3], double scalar) {
    __asm {
        fild dword ptr [edi+4]
        push ebx
        push ebp
        fmul dword ptr [esp+0Ch]
        call sub_463B2C
        fild dword ptr [edi+8]
        mov ebx, eax
        fmul dword ptr [esp+0Ch]
        call sub_463B2C
        fild dword ptr [edi]
        mov ebp, eax
        fmul dword ptr [esp+0Ch]
        call sub_463B2C
        mov [esi+8], ebp
        pop ebp
        mov [esi], eax
        mov [esi+4], ebx
        mov eax, esi
        pop ebx
        ret 4
    }
}
#else
void RandomVector_StoreRoundedScalar(int output[3], double scalar) {
    long long rounded = scalar >= 0.0
        ? (long long)(scalar + 0.5)
        : (long long)(scalar - 0.5);
    int value = (int)rounded;
    output[0] = value;
    output[1] = value;
    output[2] = value;
}
#endif
