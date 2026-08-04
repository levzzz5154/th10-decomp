#include "th10/game/faith_gauge.hpp"

#ifdef _MSC_VER
extern "C" void sub_4492A0(void*, void*);
extern "C" void* sub_448D00(void*, int, int);
extern "C" unsigned long dword_491C10;
extern "C" void* dword_47770C;
#endif

#include <cstring>

extern uint32_t* DAT_0047770c;  // front UI manager (entity block pool)

namespace {

uint32_t ReadU32(const uint8_t* bytes) {
    uint32_t value;
    memcpy(&value, bytes, sizeof(value));
    return value;
}

void WriteU32(uint8_t* bytes, uint32_t value) {
    memcpy(bytes, &value, sizeof(value));
}

}  // namespace

// 0x00418930 - Add to a faith gauge level. Retail keeps the gauge in
// EAX and the release context in ECX; the resource pointer at +0x9EC8
// travels as a 32-bit word on the host image, so the spawn edge takes
// the truncated token. The boundary test divides the final level and
// the final level minus the added amount by 0x14 (20) with C
// truncation, exactly as retail.
#ifdef _MSC_VER
__declspec(naked) bool FaithGauge_AddRetail() {
    __asm {
        push ebp
        mov ebp, [esp+8]
        push esi
        mov esi, eax
        mov ax, [esi+8]
        cmp ax, 64h
        jl loc_418949
        pop esi
        xor eax, eax
        pop ebp
        ret 4
loc_418949:
        add eax, ebp
        cmp ax, 64h
        mov [esi+8], ax
        jle loc_41899B
        mov edx, dword ptr [dword_491C10]
        push ebx
        push edi
        mov edi, dword ptr [dword_47770C]
        mov word ptr [esi+8], 64h
        mov eax, [edi+9E18h]
        lea ebx, [edi+9E18h]
        push eax
        call sub_4492A0
        push 0Fh
        mov dword ptr [ebx], 0
        mov ecx, [edi+9EC8h]
        push 49h
        push ecx
        lea edi, [esp+20h]
        call sub_448D00
        mov edx, [eax]
        pop edi
        mov [ebx], edx
        pop ebx
loc_41899B:
        movsx esi, word ptr [esi+8]
        movsx eax, bp
        mov ecx, esi
        sub ecx, eax
        mov eax, 66666667h
        imul ecx
        sar edx, 3
        mov ecx, edx
        shr ecx, 1Fh
        add ecx, edx
        mov eax, 66666667h
        imul esi
        sar edx, 3
        mov eax, edx
        shr eax, 1Fh
        add eax, edx
        xor edx, edx
        cmp ecx, eax
        setnz dl
        pop esi
        pop ebp
        mov eax, edx
        ret 4
    }
}
#endif

bool FaithGauge_Add(int16_t* level, int16_t amount, void* context,
                    void (*release_anm)(void* context, uint32_t handle),
                    const uint32_t* (*spawn_anm)(uint32_t resource,
                                                 int32_t script,
                                                 int32_t layer)) {
    if (*level > 99) {
        return false;
    }
    const int16_t value = (int16_t)(*level + amount);
    *level = value;
    uint8_t* manager = (uint8_t*)DAT_0047770c;
    if (value > 100) {
        *level = 100;
        if (release_anm != 0) {
            release_anm(context, ReadU32(manager + 0x9E18));
        }
        WriteU32(manager + 0x9E18, 0);
        if (spawn_anm != 0) {
            const uint32_t* handle =
                spawn_anm(ReadU32(manager + 0x9EC8), 0x49, 0xF);
            WriteU32(manager + 0x9E18, *handle);
        }
    }
    return ((int32_t)*level - (int32_t)amount) / 0x14 !=
           (int32_t)*level / 0x14;
}
