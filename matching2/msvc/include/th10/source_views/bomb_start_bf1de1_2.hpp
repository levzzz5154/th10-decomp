#pragma once


struct PlayerAnimationResources {
    unsigned char pad00[0x3E0B50];
    AnimationResourceFile* resource;
};
typedef PlayerFlags PlayerInitializeGlobal;
extern "C" PlayerAnimationResources* g_bullet_manager;
extern "C" PlayerInitializeGlobal* g_card;
extern "C" PowerDisplayOwner* g_front;
extern "C" int g_globals_character;
extern "C" short g_globals_power;
extern "C" int g_rank;
#pragma code_seg(".text$a04initialize")
