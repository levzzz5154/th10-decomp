// 0x00441F50 (116 bytes): start a timed interpolation of an animation
// object's byte-valued channel at +0x208 from `initial` to `goal` over
// `end_time` frames with easing `mode`.
//
// Native LTCG passes the object in EAX, the duration in ECX and the mode in DL.
#include "th10/render/animation_byte_interpolator.hpp"

#pragma code_seg(".text$01channel208")
void AnimationInterpolatedObject::StartChannel208(int end_time, unsigned char mode,
                                                  unsigned char initial, unsigned char goal) {
    channel_208.end_time = end_time;
    channel_208.mode = mode;
    channel_208.initial = initial;
    channel_208.goal = goal;
    FrameTimer_Restart(&channel_208.timer);
}
#pragma code_seg()

// 0x00442050 and 0x00442220 (208 bytes each): start a timed interpolation of
// one of the object's two colours between the byte triples `initial` and
// `goal`. LTCG passes the object in EAX, `initial` in EDX and `goal` in ECX.
#pragma code_seg(".text$03color1bc")
void AnimationInterpolatedObject::StartColor1BC(const unsigned char* initial,
                                                const unsigned char* goal, int end_time,
                                                unsigned char mode) {
    color_1bc.end_time = end_time;
    color_1bc.control_1 = AnimationColorComponents(0, 0, 0);
    color_1bc.control_2 = AnimationColorComponents(0, 0, 0);
    color_1bc.mode = mode;
    AnimationColorComponents from(initial);
    AnimationColorComponents to(goal);
    color_1bc.initial = from;
    color_1bc.goal = to;
    FrameTimer_Restart(&color_1bc.timer);
}
#pragma code_seg()

#pragma code_seg(".text$05color0bc")
void AnimationInterpolatedObject::StartColor0BC(const unsigned char* initial,
                                                const unsigned char* goal, int end_time,
                                                unsigned char mode) {
    color_0bc.end_time = end_time;
    color_0bc.control_1 = AnimationColorComponents(0, 0, 0);
    color_0bc.control_2 = AnimationColorComponents(0, 0, 0);
    color_0bc.mode = mode;
    AnimationColorComponents from(initial);
    AnimationColorComponents to(goal);
    color_0bc.initial = from;
    color_0bc.goal = to;
    FrameTimer_Restart(&color_0bc.timer);
}
#pragma code_seg()
