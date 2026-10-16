#include "th10/game/bullet_manager_teardown.hpp"
#pragma code_seg(".text$01element_dtor")
BulletSlot::~BulletSlot() {
 if(secondary_resource) crt_free(secondary_resource);
 secondary_resource=0;
}
#pragma code_seg()
