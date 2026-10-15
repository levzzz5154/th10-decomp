// The shared animation views of the replay-submenu cluster: the lookup
// context pointer, the id record and the four-byte handle/ref types.
#ifndef TH10_REPLAY_SUBMENU_004236F0_ANIMATION_HPP
#define TH10_REPLAY_SUBMENU_004236F0_ANIMATION_HPP

#include "th10/game/replay_submenu_004236f0/state.hpp"

struct AnimationLookupContext;
__declspec(noinline) void* __fastcall SubAnimFind_004236f0(
    AnimationLookupContext* context, AnimationScriptId id);
extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationTreeNode {
    AnimationTreeNode* object;              // +0x000
    AnimationTreeNode* next;                // +0x004
    unsigned char reserved_008[0x0C];
    AnimationTreeNode* children;            // +0x014
    int children_flagged;                   // +0x018
    unsigned char reserved_01c[0x2E8];
    unsigned short stop_frame;              // +0x304
};

#endif
