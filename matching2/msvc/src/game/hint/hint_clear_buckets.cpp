// 0x00419040..0x0041908E: release every chain a manager holds in its two
// eight-way bucket arrays.
//
// The region is entered by the game's internal EAX convention rather than by
// the ordinary MSVC thiscall ABI.  The native-LTCG cluster in
// build_support/layout/ltcg/recovery_clear_eight_buckets.json supplies that
// convention while keeping the recovered operation readable.

extern "C" void __cdecl crt_free_startup(void* memory);   // 0x004524A1

#include "th10/game/resource_cleanup.hpp"

#ifndef TH10_CLEAR_BUCKETS_CODE_SEG
#define TH10_CLEAR_BUCKETS_CODE_SEG ".text$01accessor"
#endif
#pragma code_seg(TH10_CLEAR_BUCKETS_CODE_SEG)
void Manager3::ClearBuckets() {
    for (int index = 0; index < 8; ++index) {
        for (ChainNode* node = primary[index].head; node != 0; ) {
            ChainNode* next = node->next;
            crt_free_startup(node->block);
            node = next;
        }
        for (ChainNode* node = secondary[index].head; node != 0; ) {
            ChainNode* next = node->next;
            crt_free_startup(node->block);
            node = next;
        }
    }
}
#pragma code_seg()
