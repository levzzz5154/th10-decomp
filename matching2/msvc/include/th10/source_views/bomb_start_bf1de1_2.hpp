#pragma once


struct PlayerAnimationResources {
    unsigned char pad00[0x3E0B50];
    AnimationResource_0043e710* resource;
};
typedef PlayerFlags_00405500 PlayerInitializeGlobal;
extern "C" PlayerAnimationResources* data_004776f0;
extern "C" PlayerInitializeGlobal* g_card;
extern "C" PowerDisplayOwner_004054b0* g_front;
extern "C" int data_00474c68;
extern "C" short data_00474c48;
extern "C" int data_00474c98;
#pragma code_seg(".text$a04initialize")
