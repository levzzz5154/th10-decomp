// Find the handle's animation and change its current resource's script.
// Native LTCG keeps the handle in EAX and the index on the stack (RET4).
#include "th10/render/animation_script_change.hpp"
#pragma code_seg(".text$05wrapper")
void ScriptChangeHandle::ChangeScript(int index) {
    Entity* object = ((ScriptChangeManager*)0)->Find(g_sprt_ctrl, id);
    if (object) ChangeAnimationScript((ScriptChangeResource*)object->ScriptResource(), object, index);
}
#pragma code_seg()
