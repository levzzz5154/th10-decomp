// 0x004065C0: update all 2000 bullet slots.
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

extern "C" int __stdcall BulletRuntime_Tick(const void* entry);  // 0x00406240
extern "C" float flt_1_01;    // normal upper bound
extern "C" float flt_0_99;    // normal lower bound

enum GameTickFlags {
    GAME_FLAG_PAUSED_OR_FROZEN = 0x2,
    GAME_FLAG_BULLETS_FROZEN = 0x400
};

struct GameBulletView {
    unsigned char pad_00[0x58];
    unsigned int flags;  // +0x58
};

extern "C" GameBulletView* g_game;

struct BulletSlotTimer {
    int previous;                // +0x3F8 (anchor - 0x08)
    int current;                 // +0x3FC (anchor - 0x04)
    float elapsed;               // +0x400 (anchor + 0x00)
    float* speed;                // +0x404 (anchor + 0x04)
};

// View of one 0x7F0-byte bullet slot anchored at +0x400 (`timer_elapsed`) so
// MSVC keeps retail's carried +0x400 loop pointer without adding a base adjustment.
struct BulletSlot;
struct BulletSlotPose {
    float timer_elapsed;         // +0x400 (anchor + 0x00)
    float* timer_speed;          // +0x404 (anchor + 0x04)
    unsigned char pad_408[0x3E]; // +0x408..+0x445
    unsigned short active_state; // +0x446 (anchor + 0x46)
    unsigned short pad_448[2];   // +0x448..+0x44B
    BulletSlot* next_in_layer;   // +0x44C (anchor + 0x4C)
    unsigned char pad_450[0x10]; // +0x450..+0x45F
    int render_layer;            // +0x460 (anchor + 0x60)
};

// MATCH: recovering the timer view via pointer subtraction on the +0x400 anchor
// folds into negative [edi-8]/[edi-4] displacements without a reference temporary.
#define BULLET_TIMER(pose) (reinterpret_cast<BulletSlotTimer*>(reinterpret_cast<char*>(pose) - 8))

struct BulletSlot {
    unsigned char pad_000[0x3F8];
    int timer_previous;          // +0x3F8
    int timer_current;           // +0x3FC
    BulletSlotPose pose;         // +0x400
    unsigned char pad_464[0x7F0 - 0x464];
};
typedef char BulletSlotSizeCheck[sizeof(BulletSlot) == 0x7F0 ? 1 : -1];

struct BulletManagerTable {
    unsigned char pad_0000[0x14];
    BulletSlot* heads[6];               // +0x14
    BulletSlot* tails[6];               // +0x2C
    unsigned char pad_0044[0x5C - 0x44];
    int active;                         // +0x5C
    BulletSlot slots[2000];             // +0x60

    __declspec(noinline) int UpdateBullets();
};

#pragma code_seg(".text$01rearm")
int BulletManagerTable::UpdateBullets() {
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
    BulletSlot* entry = slots;
    BulletSlotPose* pose = &entry->pose;
    int remaining = 2000;
    do {
        if (pose->active_state != 0) {
            if (!(g_game != 0 && (g_game->flags & GAME_FLAG_PAUSED_OR_FROZEN) != 0
                  && (g_game->flags & GAME_FLAG_BULLETS_FROZEN) != 0)) {
                if (BulletRuntime_Tick(entry) != 0)
                    goto next;
            }
            if (heads[pose->render_layer] != 0)
                tails[pose->render_layer]->pose.next_in_layer = entry;
            else
                heads[pose->render_layer] = entry;
            tails[pose->render_layer] = entry;
            pose->next_in_layer = 0;
            ++active;
            BULLET_TIMER(pose)->previous = BULLET_TIMER(pose)->current;
            if (*pose->timer_speed > flt_0_99 && *pose->timer_speed < flt_1_01) {
                ++BULLET_TIMER(pose)->current;
                pose->timer_elapsed += 1.0f;
            } else {
                BULLET_TIMER(pose)->current = (int)(pose->timer_elapsed += *pose->timer_speed);
            }
        }
next:
        ++entry;
        pose = reinterpret_cast<BulletSlotPose*>(reinterpret_cast<char*>(pose) + sizeof(BulletSlot));
    } while (--remaining != 0);
    return 1;
}
#pragma code_seg()
#undef BULLET_TIMER
