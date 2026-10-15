// 0x0040B3A0..0x0040B45F: destroy a BulletAnimOwner: stop its worker, mark the
// five animations it names for removal and forget them, then run the worker's
// own teardown (base dispatch table, stop again).  The object arrives in EAX, a
// convention only a native LTCG link chooses; the region is compiled in the
// cluster of its deleting destructor (layout/ltcg/dtor_delete_0040b920.json).
#include "th10/game/bullet_anim_owner.hpp"
#include "th10/render/animation_mark_for_removal.hpp"

#pragma code_seg(".text$01destroy")
__declspec(noinline) void BulletAnimOwner::Destroy() {
    worker.Stop();
    for (int i = 0; i < 5; ++i) {
        MarkAnimationForRemoval(data_00491c10, animation_ids[i]);
        animation_ids[i] = 0;
    }
    worker.vtable = &platform_worker_vtable;
    worker.Stop();
}
#pragma code_seg()
