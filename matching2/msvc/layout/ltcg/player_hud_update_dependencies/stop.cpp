// Compiler context only: the real handle stop-frame setter 0x00449470, so the pass sees the callee's body and
// gives the update its private register convention. The macro moves the body
// into a section that sorts at its retail address here. Never selected from
// this cluster.
#define code_seg(name) code_seg(".text$a05stop")
#include "../../../src/render/animation_manager_set_stop_frame_from_handle_retail_00449470.cpp"
