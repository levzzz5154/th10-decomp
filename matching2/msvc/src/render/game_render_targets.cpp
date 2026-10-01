#include "th10/render/native_render_targets.hpp"
#include "../../layout/ltcg/native_render_targets/dependencies.cpp"
#include "animation_manager_clear_indexed_resources_00447f70.cpp"
#include "../../layout/ltcg/native_render_targets/capture_context.cpp"
#include "../../layout/ltcg/native_render_targets/prepare_context.cpp"
#pragma code_seg(".text$a04targets")
void NativeRenderManager::FinishTargets() {
    if (capture_bank>=0) {
        Capture(capture_bank,capture_index,capture_source.x,capture_source.y,capture_source.width,capture_source.height,
                capture_destination.x,capture_destination.y,capture_destination.width,capture_destination.height);
        capture_bank=-1;
    }
    if (primary_index>=0) {
        Prepare(primary_index,primary_source.x,primary_source.y,primary_source.width,primary_source.height,
                primary_destination.x,primary_destination.y,primary_destination.width,primary_destination.height);
        primary_index=-1;
    }
}
#pragma code_seg()
