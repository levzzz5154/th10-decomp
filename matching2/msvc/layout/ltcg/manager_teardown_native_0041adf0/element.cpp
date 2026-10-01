#include "th10/game/manager_teardown_native_0041adf0.hpp"
static void ClearRegistration(uint32_t* flags) { *flags &= ~1u; }
#pragma code_seg(".text$00element_ctor")
NativeEffectElement_0041AD60::NativeEffectElement_0041AD60() {
 ClearRegistration(&flags_06C); ClearRegistration(&flags_0B0); ClearRegistration(&flags_0FC);
 ClearRegistration(&flags_128); ClearRegistration(&flags_174); ClearRegistration(&flags_1B0);
 ClearRegistration(&flags_1FC); ClearRegistration(&flags_228); ClearRegistration(&flags_378);
 memset(this,0,sizeof(Entity)); SpriteIndex()=-1; ClearRegistration(&Flags_3D8());
}
#pragma code_seg(".text$01element_dtor")
NativeEffectElement_0041AD60::~NativeEffectElement_0041AD60() { if(resource) entry_free_00452422(resource);resource=0; }
#pragma code_seg()
