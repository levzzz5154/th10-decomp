#include "th10/game/smoll_score_destructor.hpp"
#pragma code_seg(".text$01element_dtor")
inline EffectAnimation_00401FF0::~EffectAnimation_00401FF0() {
 void* owned=resource;
 if(owned) entry_free_00452422(owned);
 resource=0;
}
#pragma code_seg()
