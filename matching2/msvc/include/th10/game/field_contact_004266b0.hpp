#ifndef TH10_FIELD_CONTACT_004266B0_HPP
#define TH10_FIELD_CONTACT_004266B0_HPP
#include <stddef.h>
struct ContactVector2 { float x, y; };
struct TriggerFieldContact {
    unsigned char reserved_000[0x404];
    ContactVector2 minimum;                      // +0x404, +0x408
    unsigned char reserved_40c[4];
    ContactVector2 maximum;                      // +0x410, +0x414
    unsigned char reserved_418[0x40];
    int mode;                                   // +0x458
    unsigned char reserved_45c[0x3EB4];
    int activation_countdown;                   // +0x4310
};
struct FieldContactDialogue {
    unsigned char reserved_000[0x9EB8];
    int active;                                 // +0x9EB8
};
typedef char ContactVectorSize[sizeof(ContactVector2)==8 ? 1:-1];
typedef char ContactDialogueActiveOffset[offsetof(FieldContactDialogue,active)==0x9EB8 ? 1:-1];
typedef char ContactMinimumOffset[offsetof(TriggerFieldContact,minimum)==0x404 ? 1:-1];
typedef char ContactMaximumOffset[offsetof(TriggerFieldContact,maximum)==0x410 ? 1:-1];
typedef char ContactModeOffset[offsetof(TriggerFieldContact,mode)==0x458 ? 1:-1];
typedef char ContactCountdownOffset[offsetof(TriggerFieldContact,activation_countdown)==0x4310 ? 1:-1];
extern "C" const float data_00470b0c;
extern "C" const float data_00470be8;
extern "C" FieldContactDialogue* data_0047770c;
// Genuine activation entry takes only this pointer on the stack, and RET 4.
extern "C" void __stdcall ActivateField00426CF0(TriggerFieldContact* target);
// Native LTCG provides the retail position ECX, target EDX, size EAX ABI.
extern "C" __declspec(noinline) int __fastcall FieldContact004266B0(
    const ContactVector2* position, TriggerFieldContact* target,
    const ContactVector2* size);
#endif
