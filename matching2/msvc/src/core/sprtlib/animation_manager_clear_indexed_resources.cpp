#include "th10/render/native_render_targets.hpp"
#pragma code_seg(".text$a12clear")
void SprtCtrlTargetsView::Clear(int index) {
    if (primary[index]) { primary[index]->methods->Release(primary[index]);primary[index]=0; }
    if (secondary[index]) { secondary[index]->methods->Release(secondary[index]);secondary[index]=0; }
    if (memory[index]) { crt_free(memory[index]);memory[index]=0; }
    memory[index]=0;
}
#pragma code_seg()
