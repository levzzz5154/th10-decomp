// 0x00447280: SprtCtrl_LoadCachedResource
#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
struct AnmManagerCacheView {
    unsigned char pad_000000[0x3AD06C];
    CachedResource* entries[33];
};

CachedResource* __fastcall SprtCtrl_LoadCachedResource(int index, void* owner, const char* name) {
    CachedResource* entry = static_cast<AnmManagerCacheView*>(owner)->entries[index];
    if (entry != 0)
        return entry;
    entry = ((ResourceLoadFn)AnmManager_LoadFileEntry)(owner, index, name);
    if (entry == 0)
        return 0;
    SleepFn sleep = *(SleepFn*)&imp_Sleep;
    entry->busy = 1;
    do {
        if (g_app_flags & 0x80)
            break;
        sleep(1);
    } while (entry->busy != 0);
    return entry;
}
