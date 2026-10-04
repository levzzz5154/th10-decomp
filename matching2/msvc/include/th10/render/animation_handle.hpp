// The four-byte animation handle shared by the co-compiled animation units.
//
// The handle holds the script id of the animation object it names; the
// StopAtFrame pair resolves that id through the animation lookup and drives the
// object's sprite word.  Declared once so the members of one cluster agree on
// the type, its size and the decorated names of the three entry points.
#ifndef TH10_RENDER_ANIMATION_HANDLE_HPP
#define TH10_RENDER_ANIMATION_HANDLE_HPP

struct AnimationHandle {
    unsigned int value;
    __declspec(noinline) int Validate();
    __declspec(noinline) void StopAtFrame1();
    __declspec(noinline) void StopAtFrame2();
    __declspec(noinline) void StopAtFrame3();
};

#endif
