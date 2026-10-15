#include "th10/source_views/stage_anm_reload_93580a_0.hpp"
#include "th10/source_views/stage_anm_reload_93580a_1.hpp"
extern "C" unsigned int __cdecl Stage_ReloadAnmThread_0040c3a0() {
    g_ending->stage->ReloadAnm();
    return 0;
}


#include "../../../include/th10/source_views/stage_anm_reload_93580a_2.hpp"
#include "th10/source_views/stage_anm_reload_93580a_0.hpp"
#include "th10/source_views/stage_anm_reload_93580a_1.hpp"
#include "th10/source_views/stage_anm_reload_93580a_2.hpp"
int Stage_0040c3c0::ReloadAnm() {
    const char* name = anm_name;
    g_recovery_script_path[0] = 0;
    strcat(g_recovery_script_path, name);
    anm[header->anm_slot] =
        Recovery_LoadCachedResource(header->anm_slot + 0x1D, g_sprt_ctrl, g_recovery_script_path);
    flags &= ~4u;
    g_ascii_manager->StopLoadingSprite();
    return 0;
}

