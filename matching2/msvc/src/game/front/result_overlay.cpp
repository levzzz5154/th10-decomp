// 0x004172E0: replace a result caption and display its eight-digit number.
// The complete 640-byte body and 28-byte compiler switch table match retail.
// Native LTCG keeps kind in EAX and state/number on the stack (RET 8).
#include "th10/game/result_overlay_004172e0.hpp"
__declspec(noinline) void* __fastcall ResultAnimation_Find(ResultAnimationLookup*,ResultAnimationId);
static __forceinline ResultAnimationId CreateDigit(void* resource, int index) {
    Entity* object = reinterpret_cast<ResultAnimationPool*>(g_sprt_ctrl)->Allocate();
    unsigned flags = object->flags_35C;
    object->render_bucket = 15;
    object->flags_35C = flags | 0x40000000u;
    reinterpret_cast<ResultAnimationResource*>(resource)->InitializeObject(object, index);
    return reinterpret_cast<ResultAnimationLists*>(g_sprt_ctrl)->RegisterPrimaryBack(object);
}
#pragma code_seg(".text$004172e0_fn")
void __stdcall ResultOverlay_SetMode(int kind, ResultOverlayState* front, int number) {
    switch (kind) {
    case 0: {
        front->caption.Release();
        front->caption.id = ResultAnimation_CreatePrimary(front->captions, 71, 15);
        int leading_digit_seen = 0;
        int remaining = number;
        int divisor = 10000000;
        // Keep the input in remaining while number tracks the digit position.
        for (number = 0; number < 8; ++number) {
            ResultAnimationId* digit = &front->digits[number];
            ResultAnimation_Retire(g_sprt_ctrl, *digit);
            digit->value = 0;
            *digit = CreateDigit(front->captions, 39 + number);
            int value = remaining / divisor;
            int remainder = remaining % divisor;
            if (value) leading_digit_seen = 1;
            Entity* object = reinterpret_cast<Entity*>(ResultAnimation_Find(g_sprt_ctrl, *digit));
            if (object) {
                AnimationObject_0043e5a0* vm = reinterpret_cast<AnimationObject_0043e5a0*>(object);
                vm->resource->ConfigureObject(vm, value + 8);
            }
            if (!leading_digit_seen) digit->Hide();
            else digit->Show();
            remaining = remainder;
            divisor /= 10;
        }
        break;
    }
    case 1:
        front->caption.Release();
        front->caption.id = ResultAnimation_CreatePrimary(front->captions, 72, 15);
        break;
    case 2:
        front->secondary.Release();
        front->secondary.id = ResultAnimation_CreatePrimary(front->captions, 73, 15);
        break;
    case 3:
        front->secondary.Release();
        front->secondary.id = ResultAnimation_CreatePrimary(front->captions, 74, 15);
        break;
    case 4:
        front->secondary.Release();
        front->secondary.id = ResultAnimation_CreatePrimary(front->captions, 75, 15);
        break;
    case 6:
        front->caption.Release();
        front->caption.id = ResultAnimation_CreatePrimary(front->captions, 76, 15);
        break;
    }
}
#pragma code_seg()
