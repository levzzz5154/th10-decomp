// Compiler context only: the callees of 0x0042A450, so the pass derives their
// register arguments. None of these bytes are selected.
#include "th10/game/replay_stage_finish_0042a450.hpp"
#include <stdlib.h>

extern "C" int __cdecl ReplayStageFinishEscape(void* pointer, int value);

// Stand-in for 0x00426F70 (still assembly): taking the parameter's address
// keeps it on the stack.
#pragma code_seg(".text$04refresh")
extern "C" __declspec(noinline) void __stdcall PlayerRefresh_00426f70(Player_0042a450* player) {
    ReplayStageFinishEscape(&player, 3);
    ReplayStageFinishEscape(player->state, 4);
    ReplayStageFinishEscape(&player->options[1], 5);
}

// The body of 0x00428E10 with a result: the caller must not learn that the
// player's register survives the call, which retail's caller did not know.
#pragma code_seg(".text$05gauge")
int Player_0042a450::SetBossGauge(const ReplayGaugeCounters_0042a6a0* source) {
    int* counters = &boss_gauge.value;
    counters[0] = source->value;
    counters[1] = source->maximum;
    *(float*)((char*)this + 0x3C0) = (float)boss_gauge.value * 0.01f;
    *(float*)((char*)this + 0x3C4) = (float)boss_gauge.maximum * 0.01f;
    for (int i = 0; i < 4; i++)
        options[i].flag = 1;
    return 0;
}

// One 0x6284-byte page of input records (th10/game/linked_pool_append.hpp).
struct ReplayPoolPage_0042a6a0 {
    unsigned char records[0x5460];
    ReplayPoolPage_0042a6a0* scratch_page;   // +0x5460
    unsigned char scratch[0xE10];
    unsigned char* scratch_cursor;           // +0x6274
    ReplayPoolLink_0042a6a0 link;            // +0x6278

    ReplayPoolPage_0042a6a0() {
        memset(this, 0, sizeof(*this));
        scratch_page = this;
        scratch_cursor = scratch;
        link.page = this;
        link.next = 0;
        link.previous = 0;
    }
};
typedef char ReplayPoolPageSize_0042a6a0[sizeof(ReplayPoolPage_0042a6a0) == 0x6284 ? 1 : -1];

// The body of 0x0042AA50.
#pragma code_seg(".text$07append")
ReplayPoolLink_0042a6a0* ReplayManager_0042a6a0::AppendPage(int stage) {
    ReplayPoolLink_0042a6a0* link = &(new ReplayPoolPage_0042a6a0)->link;
    ReplayPoolLink_0042a6a0* tail = &pools[stage];
    while (tail->next)
        tail = tail->next;
    if (tail->next) {
        link->next = tail->next;
        tail->next->previous = link;
    }
    tail->next = link;
    link->previous = tail;
    return link;
}

// The body of 0x0042AB20.
#pragma code_seg(".text$08clear")
extern "C" __declspec(noinline) void __stdcall
ReplayFinishClearPools_0042ab20(ReplayManager_0042a6a0* manager, int stage) {
    ReplayPoolLink_0042a6a0* current = manager->pools[stage].next;
    while (current) {
        ReplayPoolLink_0042a6a0* next = current->next;
        ReplayPoolPage_0042a6a0* pool = current->page;
        if (pool) {
            if (pool->link.next) pool->link.next->previous = pool->link.previous;
            if (pool->link.previous) pool->link.previous->next = pool->link.next;
            pool->link.next = 0;
            pool->link.previous = 0;
            free(pool);
        }
        current = next;
    }
}
#pragma code_seg()
