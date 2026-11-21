// 0x0040C3A0..0x0040C3C0: Stage_ReloadAnmThread2, StageReloadView::ReloadAnm
#include "th10/source_views/stage_anm_reload_93580a_0.hpp"
#include "th10/source_views/stage_anm_reload_93580a_1.hpp"
extern "C" unsigned int __cdecl Stage_ReloadAnmThread2() {
    g_ending->stage->ReloadAnm();
    return 0;
}


#include "../../../include/th10/source_views/stage_anm_reload_93580a_2.hpp"
#include "th10/source_views/stage_anm_reload_93580a_0.hpp"
#include "th10/source_views/stage_anm_reload_93580a_1.hpp"
#include "th10/source_views/stage_anm_reload_93580a_2.hpp"
int StageReloadView::ReloadAnm() {
    const char* name = anm_name;
    g_archive_load_path[0] = 0;
    strcat(g_archive_load_path, name);
    anm[header->anm_slot] =
        SprtCtrl_LoadCachedResource(header->anm_slot + 0x1D, g_sprt_ctrl, g_archive_load_path);
    flags &= ~4u;
    g_ascii_manager->StopLoadingSprite();
    return 0;
}

