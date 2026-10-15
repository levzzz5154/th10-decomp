#include "th10/game/smoll_score_destructor.hpp"
#pragma code_seg(".text$05owned_delete")
__declspec(noinline) void __stdcall SmollScore_DestroyOwned_0042B6D0(SmollScoreDestructorView* manager) {
 if(manager) { manager->~SmollScoreDestructorView(); ::operator delete(manager); }
}
#pragma code_seg()
