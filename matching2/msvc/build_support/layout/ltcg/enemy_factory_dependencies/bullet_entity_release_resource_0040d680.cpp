// 0x0040D680..0x0040D6A3: restore a bullet entity's vtable and release its
// owned resource.  The native-LTCG cluster preserves the retail this pointer
// in ESI, so this remains an ordinary named member implementation.

extern "C" void __cdecl crt_free(void* memory);

#include "th10/game/enemy_manager_dependencies_0040d530.hpp"

#pragma code_seg(".text$03b")
void BulletEntity_0040d680::ReleaseResource() {
    void* const resource = owned_resource;
    vtable = 0x0046D0F0;
    if (resource != 0) {
        crt_free(resource);
        owned_resource = 0;
    }
}
#pragma code_seg()
