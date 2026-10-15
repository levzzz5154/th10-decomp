#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
#include "th10/source_views/recovery_leaves_f39a06_5.hpp"
CachedResource* __fastcall Recovery_LoadCachedResource(int index, void* owner, const char* name) {
    CachedResource* entry = *(CachedResource**)((char*)owner + 0x3AD06C + index * 4);
    if (entry != 0)
        return entry;
    entry = ((ResourceLoadFn)asm_FUN_004470c0_004470c0)(owner, index, name);
    if (entry == 0)
        return 0;
    SleepFn sleep = *(SleepFn*)&data_004660ac;
    entry->busy = 1;
    do {
        if (data_00491ff4 & 0x80)
            break;
        sleep(1);
    } while (entry->busy != 0);
    return entry;
}
