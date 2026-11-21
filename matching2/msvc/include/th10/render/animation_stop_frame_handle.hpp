#ifndef TH10_RENDER_ANIMATION_STOP_FRAME_HANDLE_HPP
#define TH10_RENDER_ANIMATION_STOP_FRAME_HANDLE_HPP

struct StopFrameAnmHandle {
    unsigned int value;
    __declspec(noinline) void SetStopFrame(unsigned short frame);
};

#endif
