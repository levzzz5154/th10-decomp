#include "th10/game/item_manager_destructor.hpp"
static void ClearRegistration(uint32_t* flags) { *flags &= ~1u; }
#pragma code_seg(".text$00element_ctor")
Item::Item() {
 ClearRegistration(&flags_06C); ClearRegistration(&flags_0B0); ClearRegistration(&flags_0FC);
 ClearRegistration(&flags_128); ClearRegistration(&flags_174); ClearRegistration(&flags_1B0);
 ClearRegistration(&flags_1FC); ClearRegistration(&flags_228); ClearRegistration(&flags_378);
 memset(this,0,sizeof(Entity)); SpriteIndex()=-1; ClearRegistration(&Flags_3D8());
}
#pragma code_seg(".text$01element_dtor")
Item::~Item() { if(resource) entry_free_00452422(resource);resource=0; }
#pragma code_seg()
