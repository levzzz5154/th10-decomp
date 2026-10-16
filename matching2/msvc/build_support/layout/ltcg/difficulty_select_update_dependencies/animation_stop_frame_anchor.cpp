// Real body of the handle stop-frame setter 0x00449470 the difficulty
// selection screen 0x00430320 calls, unselected here, sharing the one lookup
// at 0x004491C0 of this link.
#define SprtCtrl RecoveryLookup
#define AnimationLookupContext RecoveryLookupContext
#define AnimationScriptId RecoveryScriptId
#define code_seg(name) code_seg(".text$00449470_fn")
#include "../../../../src/core/sprtlib/animation_manager_set_stop_frame_from_handle_retail.cpp"
#undef code_seg
#pragma code_seg()
