#include "th10/game/result_overlay_004172e0.hpp"
struct CaptionFlagObject {
    unsigned char reserved[0x14];
    struct CaptionFlagLink* children;
    int children_flagged;
    unsigned char reserved_1c[0x35C-0x1C];
    unsigned flags;
};
struct CaptionFlagLink { CaptionFlagObject* object; CaptionFlagLink* next; };
__declspec(noinline) void* __fastcall ResultAnimation_Find(ResultAnimationLookup*,ResultAnimationId);

#pragma code_seg(".text$00449590_fn")
void ResultAnimationId::Show() {
    CaptionFlagObject* object = reinterpret_cast<CaptionFlagObject*>(ResultAnimation_Find(data_00491c10,*this));
    if (object) {
        object->flags |= 2u;
        if (!object->children_flagged)
            for (CaptionFlagLink* child=object->children;child;child=child->next)
                child->object->flags |= 2u;
    }
}
#pragma code_seg()

#pragma code_seg(".text$004495e0_fn")
void ResultAnimationId::Hide() {
    CaptionFlagObject* object = reinterpret_cast<CaptionFlagObject*>(ResultAnimation_Find(data_00491c10,*this));
    if (object) {
        object->flags &= ~2u;
        if (!object->children_flagged)
            for (CaptionFlagLink* child=object->children;child;child=child->next)
                child->object->flags &= ~2u;
    }
}
#pragma code_seg()
