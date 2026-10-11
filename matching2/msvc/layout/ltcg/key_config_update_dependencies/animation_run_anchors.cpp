// Real bodies of the animation restart 0x00449250 and the pad button poll
// 0x0044A4E0 the key configuration screen 0x0042F540 calls, unselected here.
#define code_seg(name) code_seg(".text$00449250_fn")
#include "../../../src/render/animation_manager_set_stop_frame_and_run_00449250.cpp"
#undef code_seg
#pragma code_seg(".text$0044a4e0_fn")
#include "../../../src/game/input_poll_joystick_buttons_0044a4e0.cpp"
#pragma code_seg()
