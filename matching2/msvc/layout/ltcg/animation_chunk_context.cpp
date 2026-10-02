// Genuine complete front.anm loader; used only as unselected logger caller.
#include "../../src/unidentified/FUN_0040d400_0040d400.cpp"
#include "animation_chunk_text_log.cpp"
#pragma code_seg(".text$a03front")
extern "C" __declspec(noinline) int __cdecl LoadFrontAnm_00413b50() {
    if (!Recovery_LoadCachedResource_00447280(6, data_00491c10,
            reinterpret_cast<const char*>(0x0046D254))) {
        reinterpret_cast<TextLog_0044b810*>(0x00474F70)->Append(
            reinterpret_cast<char*>(0x0046CB68));
        return -1;
    }
    return 0;
}
#pragma code_seg()
