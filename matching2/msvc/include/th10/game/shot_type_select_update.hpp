#ifndef TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#define TH10_SHOT_TYPE_SELECT_UPDATE_00430A60_HPP
#include "th10/game/difficulty_select_update.hpp"
#include "th10/game/recovery_script_executor_ascii_anchors.hpp"
#include "th10/game/stage_route.hpp"
#include "th10/game/title_score_file.hpp"

// A child reference seen as the handle whose hidden flag 0x004495E0 clears.
struct AnimationHandle12 {
    AnimationScriptId id;
    __declspec(noinline) void ClearFlag();
};

extern "C" {
extern int g_globals_shot_type;               // shot type
extern unsigned int g_globals_flags;      // game flags (0x10: practice)
extern int g_globals_stage, g_globals_stage_shown;    // stage, starting stage
extern int g_main_state;               // requested application mode
}

// 0x00420C30.
__declspec(noinline) int __stdcall Music_FadeOut(float frames);

__declspec(noinline) int __stdcall TitleMode8(Title* room);
#endif
