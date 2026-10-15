// Real body of the child search 0x004497D0 the difficulty selection screen
// 0x00430320 calls and, for its constant script id, inlines; unselected here
// and sharing the one lookup at 0x004491C0 of this link. The search is left
// free to inline, as it is in the screen's own translation unit.
#define SprtCtrl RecoveryLookup_0040bd80
#define AnimationLookupContext RecoveryLookupContext
#define AnimationScriptId RecoveryScriptId
#define noinline
#define code_seg(name) code_seg(".text$004497d0_fn")
#include "../../../../src/core/sprtlib/animation_manager_find_child_by_script_index_004497d0.cpp"
#undef code_seg
#undef noinline
#pragma code_seg()
