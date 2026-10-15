// 0x0040B920..0x0040B93C (28 bytes): scalar deleting destructor of
// EndingTextView.
//
// Retail copies the object from ESI to EAX before the teardown at 0x0040B3A0,
// which reads its object from EAX, then frees the object when bit 0 of the
// incoming flags is set and returns it in EAX.  The object stays in ESI across
// the call, a receiver no C++ declaration names, so this body and 0x0040B3A0
// are compiled in the native-LTCG cluster build_support/layout/ltcg/dtor_delete_0040b920.json.
#include "th10/game/ending_text_view.hpp"

extern "C" void __cdecl crt_free_startup(void* block);

__declspec(noinline) void* Deletable_0040b920_Delete(EndingTextView* object, int flags);

#pragma code_seg(".text$03del")
void* Deletable_0040b920_Delete(EndingTextView* object, int flags) {
    object->Destroy();
    if ((flags & 1) != 0) {
        crt_free_startup(object);
    }
    return object;
}
#pragma code_seg()
