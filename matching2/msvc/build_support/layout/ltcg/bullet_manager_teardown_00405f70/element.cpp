#include "th10/game/bullet_manager_teardown_00405f70.hpp"
#pragma code_seg(".text$01element_dtor")
BulletSlot_00405DE0::~BulletSlot_00405DE0() {
 if(secondary_resource) entry_free_00452422(secondary_resource);
 secondary_resource=0;
}
#pragma code_seg()
