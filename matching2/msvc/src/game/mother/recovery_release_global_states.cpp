#include "th10/source_views/recovery_leaves_f39a06_0.hpp"
#include "th10/source_views/recovery_leaves_f39a06_1.hpp"
#include "th10/source_views/recovery_leaves_f39a06_2.hpp"
#include "th10/source_views/recovery_leaves_f39a06_3.hpp"
#include "th10/source_views/recovery_leaves_f39a06_4.hpp"
void Recovery_ReleaseGlobalStates() {
    void* manager_state = *(void**)&g_game;
    if (manager_state) {
        ((GlobalStateDestroyFn)asm_FUN_00417c80_00417c80)(manager_state);
        crt_free_startup(manager_state);
    }
    void* script_state = *(void**)&g_title;
    if (script_state) {
        ((GlobalStateDestroyFn)asm_Title_Destroy)(script_state);
        crt_free_startup(script_state);
    }
    void* resource_state = *(void**)&g_loading;
    if (resource_state) {
        ((GlobalStateDestroyFn)Loading_Release)(resource_state);
        crt_free_startup(resource_state);
    }
    void* small_state = *(void**)&g_ending;
    if (small_state) {
        ((GlobalStateDestroyFn)asm_FUN_0040b7b0_0040b7b0)(small_state);
        crt_free_startup(small_state);
    }
    void* pending_block = *(void**)&g_replay;
    if (pending_block) {
        ((GlobalStateDestroyFn)asm_FUN_004294a0_004294a0)(pending_block);
        crt_free_startup(pending_block);
    }
}
