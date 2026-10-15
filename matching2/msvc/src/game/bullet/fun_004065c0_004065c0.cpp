// 0x004065C0: re-arm the effect-slot table.
//
// The manager arrives in ESI and the body declares no parameters, so this is a
// native-LTCG cluster: only the internal convention of the /GL link keeps the
// manager in a callee-saved register. The result is the constant 1.
//
// Retail walks two pointers per slot: the slot record itself (passed to the
// re-arm helper and stored into the active list) and a second view 0x400 bytes
// into it, which carries the timer fields the body updates. The slot index is
// re-read from the slot after every store that could alias it, so it stays a
// memory operand here rather than a local.

extern "C" int __stdcall asm_FUN_00406240_00406240(const void* entry);  // 0x00406240
extern "C" float flt_1_01;    // normal upper bound
extern "C" float flt_0_99;    // normal lower bound

struct GameBulletView {
    unsigned char pad_00[0x58];
    unsigned int field_58;  // +0x58
};

extern "C" GameBulletView* g_game;

struct RecoverySlotTable_004065c0 {
    unsigned char pad_0000[0x14];
    void* heads[6];                     // +0x14
    void* tails[6];                     // +0x2C
    unsigned char pad_0044[0x5C - 0x44];
    int active;                         // +0x5C
    unsigned char slots[2000 * 0x7F0];  // +0x60

    __declspec(noinline) int Rearm();
};

#pragma code_seg(".text$01rearm")
int RecoverySlotTable_004065c0::Rearm() {
    active = 0;
    heads[5] = 0;
    heads[4] = 0;
    heads[3] = 0;
    heads[2] = 0;
    heads[1] = 0;
    heads[0] = 0;
    tails[5] = 0;
    tails[4] = 0;
    tails[3] = 0;
    tails[2] = 0;
    tails[1] = 0;
    tails[0] = 0;
    char* entry = (char*)slots;
    char* pose = entry + 0x400;
    int remaining = 2000;
    do {
        if (*(unsigned short*)(pose + 0x46) != 0) {
            if (!(g_game != 0 && (g_game->field_58 & 2) != 0
                  && (g_game->field_58 & 0x400) != 0)) {
                if (asm_FUN_00406240_00406240(entry) != 0)
                    goto next;
            }
            if (heads[*(int*)(pose + 0x60)] != 0)
                *(void**)((char*)tails[*(int*)(pose + 0x60)] + 0x44C) = entry;
            else
                heads[*(int*)(pose + 0x60)] = entry;
            tails[*(int*)(pose + 0x60)] = entry;
            *(void**)(pose + 0x4C) = 0;
            ++active;
            *(int*)(pose - 8) = *(int*)(pose - 4);
            if (**(float**)(pose + 4) > flt_0_99
                && **(float**)(pose + 4) < flt_1_01) {
                ++*(int*)(pose - 4);
                *(float*)pose += 1.0f;
            } else {
                *(int*)(pose - 4) = (int)(*(float*)pose += **(float**)(pose + 4));
            }
        }
next:
        entry += 0x7F0;
        pose += 0x7F0;
    } while (--remaining != 0);
    return 1;
}
#pragma code_seg()
