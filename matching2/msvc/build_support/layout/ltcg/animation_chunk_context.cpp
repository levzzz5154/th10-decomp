// Genuine complete front.anm loader; used only as unselected logger caller.
#include "../../../src/game/enemy/ecl_file_parse_animations.cpp"
#include "animation_chunk_text_log.cpp"
#pragma code_seg(".text$a03front")
extern "C" __declspec(noinline) int __cdecl LoadFrontAnm() {
    if (!Recovery_LoadCachedResource(6, g_sprt_ctrl,
            reinterpret_cast<const char*>(0x0046D254))) {
        reinterpret_cast<TextLog4*>(0x00474F70)->Append(
            reinterpret_cast<char*>(0x0046CB68));
        return -1;
    }
    return 0;
}
#pragma code_seg()
