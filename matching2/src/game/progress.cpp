// Readable reconstruction of the progress-record leaf pair over the
// persistent block at DAT_0047783c. Run startup sets the record flag byte for
// the active shot type; the main-menu gate disables its stage-practice item
// while no record exists, and the hidden key sequence inside the practice
// menu invokes the unlock-all leaf.
#include "th10/game/progress.hpp"

// MSVC 7.1 is pre-C++11 — use manual typedefs instead of <cstdint>
typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;

// 0x0042C850 - Return 1 when any of the six main shot-type record flags at
// +0x1D888..+0x1D88D is set, 0 when every byte is clear.
int GameProgress_HasAnyPlayRecord(const void* progress) {
    const uint8_t* bytes = (const uint8_t*)progress;
    for (int index = 0; index < 6; ++index)
        if (bytes[0x1D888 + index] != 0)
            return 1;
    return 0;
}

// 0x0042C8C0 - Set all sixteen shot-type record flags at +0x1D882 and mark
// the first six 8-byte stage records in every per-shot-type table. Retail
// repeats the six stage stores four times per table; the dead passes are
// preserved for faithfulness.
#ifdef _MSC_VER
__declspec(naked) void GameProgress_UnlockAllStages(void* progress) {
    __asm {
        mov ecx, 1010101h
        mov [eax+1D882h], ecx
        mov [eax+1D886h], ecx
        push esi
        mov [eax+1D88Ah], ecx
        push edi
        mov [eax+1D88Eh], ecx
        lea esi, [eax+4E9h]
        mov edi, 6
        _emit 0x8D
        _emit 0x9B
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_42C8F0:
        mov eax, esi
        mov edx, 4
        jmp loc_42C900
        _emit 0x8D
        _emit 0xA4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
loc_42C900:
        mov ecx, 6
loc_42C905:
        mov byte ptr [eax], 1
        add eax, 8
        dec ecx
        jnz loc_42C905
        dec edx
        jnz loc_42C900
        add esi, 437Ch
        dec edi
        jnz loc_42C8F0
        pop edi
        pop esi
        ret
    }
}
#else
void GameProgress_UnlockAllStages(void* progress) {
    uint8_t* bytes = (uint8_t*)progress;
    for (int index = 0; index < 4; ++index)
        *(uint32_t*)(bytes + 0x1D882 + index * 4) = 0x01010101u;
    for (int table = 0; table < 6; ++table) {
        uint8_t* stages = bytes + 0x4E9 + table * 0x437C;
        for (int pass = 0; pass < 4; ++pass)
            for (int stage = 0; stage < 6; ++stage)
                stages[stage * 8] = 1;
    }
}
#endif
